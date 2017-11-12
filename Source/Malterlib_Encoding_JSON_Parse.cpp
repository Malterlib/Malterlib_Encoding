// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_JSON.h"

namespace NMib
{
	namespace NEncoding
	{
		namespace NPrivate
		{
			struct CParseContext
			{
				NStr::CStr m_FileName;
				uch8 const *m_pStartParse;
				bool m_bConvertNullToSpace = false;
				
				NStr::CParseLocation f_GetLocation(uch8 const *_pParse) const
				{
					using namespace NStr;
					CParseLocation Location;
					Location.m_File = m_FileName;
					Location.m_Character = _pParse - m_pStartParse;
					
					auto *pParse = m_pStartParse;
					mint Line = 1;
					auto *pLastLine = pParse;
					while (*pParse)
					{
						fg_ParseToEndOfLine(pParse);
							
						if (pParse > _pParse)
							break;

						if (fg_ParseEndOfLine(pParse))
						{
							++Line;
							pLastLine = pParse;
						}
					}
					
					Location.m_Line = Line;
					if (_pParse >= pLastLine)
						Location.m_Column = (_pParse - pLastLine) + 1;
					else
						Location.m_Column = 1;
					
					return Location;					
				}
			};

			void fg_ThrowErrors(NContainer::TCVector<NStr::CParseError> const &_Errors)
			{
				NStr::CStr Description = NStr::CStr::CFormat("JSON parse error:{\n}");
				for (auto &Error : _Errors)
				{
					Description
						+= NStr::CStr::CFormat(DMibPFileLineColumnFormat " {}{\n}") 
						<< Error.m_Location.m_File
						<< Error.m_Location.m_Line
						<< Error.m_Location.m_Column
						<< Error.m_Error
					;
				}
				DMibErrorParse(Description, _Errors);
			}
			
			void fg_ThrowError(CParseContext const &_Context, NStr::CStr const &_Error, uch8 const *_pLocation)
			{
				NContainer::TCVector<NStr::CParseError> Errors;
				auto &Error = Errors.f_Insert();
				Error.m_Location = _Context.f_GetLocation(_pLocation);
				Error.m_Error = _Error;
				fg_ThrowErrors(Errors);
			}

			
			bool fg_ParseJSONString(NStr::CStr &o_String, uch8 const *&o_pParse, CParseContext const &_Context);
			void fg_ParseJSONArray(CJSON &o_Value, uch8 const *&o_pParse, CParseContext const &_Context);
			void fg_ParseJSONObject(CJSON &o_Value, uch8 const *&o_pParse, CParseContext const &_Context);
			void fg_ParseJSONValue(CJSON &o_Value, uch8 const *&o_pParse, CParseContext const &_Context);
			
			
			void fg_ParseJSONArray(CJSON &o_Value, uch8 const *&o_pParse, CParseContext const &_Context)
			{
				using namespace NStr;
				DMibRequire(o_Value.f_Type() == EJSONType_Array);

				auto &Array = o_Value.f_Array();
				
				uch8 const *pParse = o_pParse;
				auto Cleanup = g_OnScopeExit > [&]
					{
						o_pParse = pParse;
					}
				;
				
				while (*pParse)
				{
					fg_ParseWhiteSpace(pParse);
					
					if (*pParse == ']')
						return; // Finished
					
					auto &Child = Array.f_Insert();
					fg_ParseJSONValue(Child, pParse, _Context);
					
					DMibCheck(Child.f_Type() != EJSONType_Invalid);
					
					fg_ParseWhiteSpace(pParse);
					if (*pParse == ',')
					{
						// Another value
						++pParse;
						continue;
					}
					else
						break;						
				}					
			}

			void fg_ParseJSONObject(CJSON &o_Value, uch8 const *&o_pParse, CParseContext const &_Context)
			{
				using namespace NStr;
				DMibRequire(o_Value.f_Type() == EJSONType_Object);

				auto &Object = o_Value.f_Object();

				uch8 const *pParse = o_pParse;
				auto Cleanup = g_OnScopeExit > [&]
					{
						o_pParse = pParse;
					}
				;
				
				while (*pParse)
				{
					fg_ParseWhiteSpace(pParse);
					
					if (*pParse == '}')
						return; // Finished

					if (*pParse != '"')
						fg_ThrowError(_Context, "Expected \" to start object key name", pParse);
					CStr KeyName;
					auto pStartString = pParse;
					if (!fg_ParseJSONString(KeyName, pParse, _Context))
						fg_ThrowError(_Context, "End of string character '\"' not found for key name string", pStartString);
					
					fg_ParseWhiteSpace(pParse);
					
					if (*pParse != ':')
						fg_ThrowError(_Context, "Expected : to follow key name in object", pParse);
					
					++pParse;
					fg_ParseWhiteSpace(pParse);
					
					auto &Child = Object.f_CreateMember(KeyName);
					fg_ParseJSONValue(Child, pParse, _Context);
					DMibCheck(Child.f_Type() != EJSONType_Invalid);
					
					fg_ParseWhiteSpace(pParse);
					
					if (*pParse == ',')
					{
						// Another value
						++pParse;
						continue;
					}
					else
						break;						
				}					
			}
			
			bool fg_ParseJSONString(NStr::CStr &o_String, uch8 const *&o_pParse, CParseContext const &_Context)
			{
				using namespace NStr;
				uch8 const *pParse = o_pParse;
				auto Cleanup = g_OnScopeExit > [&]
					{
						o_pParse = pParse;
					}
				;
				
				DMibRequire(*pParse == '\"');
				++pParse;
				
				while (*pParse)
				{
					if (*pParse == '\"')
					{
						++pParse;
						return true;
					}
					else if(*pParse == '\\')
					{
						++pParse;
						switch (*pParse)
						{
						case '\\':
						case '/':
						case '\"':
							o_String.f_AddChar(*pParse);
							++pParse;
							break;
						case 'b':
							o_String.f_AddChar(0x08);
							++pParse;
							break;
						case 'f':
							o_String.f_AddChar(0x0C);
							++pParse;
							break;
						case 'n':
							o_String.f_AddChar(0x0A);
							++pParse;
							break;
						case 'r':
							o_String.f_AddChar(0x0D);
							++pParse;
							break;
						case 't':
							o_String.f_AddChar(0x09);
							++pParse;
							break;
						case 'u':
							{
								++pParse;
								CWStr EscapedUTF16String;
									
								while (true)
								{
									bool bFailed = false;
									uch8 ToParse[5];
									mint iToParse = 0;
									auto pParseStart = pParse;
									while (*pParse && iToParse < 4)
									{
										ToParse[iToParse] = *pParse;
										++pParse;
										++iToParse;
									}
										
									if (iToParse < 4)
										fg_ThrowError(_Context, "Too short escaped UTF16 value", pParseStart);
										
									ToParse[4] = 0;
										
									uch8 const *pParseHex = ToParse;
										
									ch16 HexDigit = fg_StrToIntParse
										(
											pParseHex
											, uint16(0)
											, (uch8 const *)nullptr
											, false
											, EStrToIntParseMode_Hex
											, &bFailed
										)
									;
									
									if (bFailed || *pParseHex)
										fg_ThrowError(_Context, "Invalid escaped UTF16 value", pParseStart);

									if (HexDigit == 0)
									{
										if (_Context.m_bConvertNullToSpace)
											EscapedUTF16String.f_AddChar(' ');
										else
											fg_ThrowError(_Context, "Null characters not supported in this implementation", pParseStart);
									}
									else
										EscapedUTF16String.f_AddChar(HexDigit);
									
									if (pParse[0] == '\\' && pParse[1] == 'u')
									{
										// Another escaped UTF16 character
										pParse += 2;
										continue;
									}
									break;
								}
								o_String += EscapedUTF16String;
							}
							break;
						default:
							fg_ThrowError(_Context, "Invalid escape value", pParse);
							break;
						}
					}
					else
					{
						if (*pParse < 32)
							fg_ThrowError(_Context, "Control characters or new lines not allowed in string. Use escaped characters.", pParse);
						o_String.f_AddChar(*pParse);
						++pParse;
					}
				}
				
				return false;				
			}
			
			void fg_ParseJSONValue(CJSON &o_Value, uch8 const *&o_pParse, CParseContext const &_Context)
			{
				using namespace NStr;
				
				uch8 const *pParse = o_pParse;
				auto Cleanup = g_OnScopeExit > [&]
					{
						o_pParse = pParse;
					}
				;
				while (*pParse)
				{
					fg_ParseWhiteSpace(pParse);
					
					auto Char = *pParse;
					
					switch (Char)
					{
					case '{':
						{
							// Object
							auto pParseStart = pParse;
							++pParse;
							o_Value.f_SetType(EJSONType_Object);
							fg_ParseJSONObject(o_Value, pParse, _Context);
							
							fg_ParseWhiteSpace(pParse);
							
							if (*pParse != '}')
							{
								NContainer::TCVector<NStr::CParseError> Errors;
								{
									auto &Error = Errors.f_Insert();
									Error.m_Error = "Missing closing } for object";
									Error.m_Location = _Context.f_GetLocation(pParse);
								}
								{
									auto &Error = Errors.f_Insert();
									Error.m_Error = "See opening { for object";
									Error.m_Location = _Context.f_GetLocation(pParseStart);
								}
								fg_ThrowErrors(Errors);
							}

							++pParse;
							return;
						}
						break;
					case '[':
						{
							// Array
							auto pParseStart = pParse;
							++pParse;
							o_Value.f_SetType(EJSONType_Array);
							fg_ParseJSONArray(o_Value, pParse, _Context);
			
							fg_ParseWhiteSpace(pParse);
							
							if (*pParse != ']')
							{
								NContainer::TCVector<NStr::CParseError> Errors;
								{
									auto &Error = Errors.f_Insert();
									Error.m_Error = "Missing closing ] for array";
									Error.m_Location = _Context.f_GetLocation(pParse);
								}
								{
									auto &Error = Errors.f_Insert();
									Error.m_Error = "See opening [ for array";
									Error.m_Location = _Context.f_GetLocation(pParseStart);
								}
								fg_ThrowErrors(Errors);
							}
							
							++pParse;
							return;
						}
						break;
					case '\"':
						{
							// String
							CStr ParsedString;
							auto pParseStart = pParse;
							if (!fg_ParseJSONString(ParsedString, pParse, _Context))
								fg_ThrowError(_Context, "End of string character '\"' not found for string", pParseStart);
							
							o_Value = ParsedString;
							return;
						}
						break;
					default:
						{
							auto pParseStart = pParse;
							if (fg_StrStartsWith(pParse, "true"))
							{
								pParse += 4;
								if (!(*pParse) || *pParse == ',' || *pParse == '}' || *pParse == ']' || fg_CharIsWhiteSpace(*pParse))
								{
									o_Value = true;
									return;
								}
							}
							else if (fg_StrStartsWith(pParse, "false"))
							{
								pParse += 5;
								if (!(*pParse) || *pParse == ',' || *pParse == '}' || *pParse == ']'  || fg_CharIsWhiteSpace(*pParse))
								{
									o_Value = false;
									return;
								}
							}
							else if (fg_StrStartsWith(pParse, "null"))
							{
								pParse += 4;
								if (!(*pParse) || *pParse == ',' || *pParse == '}' || *pParse == ']'  || fg_CharIsWhiteSpace(*pParse))
								{
									o_Value = nullptr;
									return;
								}
							}

							bool bFailed = false;
							uch8 const *pTryParse = pParse;
							int64 Number = fg_StrToIntParse
								(
									pTryParse
									, int64(0)
									, ",}]"
									, false
									, EStrToIntParseMode_Base10
									, &bFailed
								)
							;
							
							if (!bFailed)
							{
								pParse = pTryParse;
								o_Value = Number;
								return;								
							}

							pTryParse = pParse;
							fp64 FloatNumber = fg_StrToFloatParse
								(
									pTryParse
									, fp64::fs_Inf()
									, ",}]"
									, false
									, "."
								)
							;
							
							if (FloatNumber != fp64::fs_Inf())
							{
								pParse = pTryParse;
								o_Value = FloatNumber;
								return;								
							}
							
							fg_ThrowError(_Context, fg_Format("Invalid literal starting with: {}", CStr(pParse, 4)), pParseStart);
						}
						break;
					}
				}
			}

			CJSON fg_JSONParse(NStr::CStr const &_String, NStr::CStr const &_FileName, bool _bConvertNullToSpace)
			{
				using namespace NStr;
				CJSON Output;
				CStr ToParse = _String;

				uch8 const *pParse = reinterpret_cast<uch8 const *>(ToParse.f_GetStr());

				CParseContext Context;
				Context.m_pStartParse = pParse;
				Context.m_FileName = _FileName;
				Context.m_bConvertNullToSpace = _bConvertNullToSpace;

				fg_ParseWhiteSpace(pParse);

				// Any value is allowed at root
				fg_ParseJSONValue(Output, pParse, Context);

				fg_ParseWhiteSpace(pParse);
				
				if (*pParse)
					fg_ThrowError(Context, "Unexpected character after root value", pParse);
				
				return fg_Move(Output);
			}
		}
	}
}
