// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON_Generate.h"

namespace NMib::NEncoding::NJSON
{
	inline NStr::CParseLocation CParseContext::f_GetLocation(uch8 const *_pParse) const
	{
		using namespace NStr;
		CParseLocation Location;
		Location.m_File = m_FileName;
		Location.m_Character = (_pParse - m_pStartParse) + m_StartCharacter;

		uint32 StartColumn = m_StartColumn;

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
				StartColumn = 0;
				++Line;
				pLastLine = pParse;
			}
		}

		Location.m_Line = Line + m_StartLine;
		if (_pParse >= pLastLine)
			Location.m_Column = (_pParse - pLastLine) + StartColumn + 1;
		else
			Location.m_Column = StartColumn + 1;

		return Location;
	}

	template <typename tf_CParseContext>
	void CParseContext::f_ParseKey(NStr::CStr &o_Key, uch8 const *&o_pParse)
	{
		using namespace NStr;

		auto pParse = o_pParse;
		if (*pParse == '"')
		{
			auto pStartString = pParse;
			if (!fg_ParseJSONString<'\"', tf_CParseContext::mc_bAllowMultilineString>(o_Key, pParse, *this))
				f_ThrowError("End of string character \" not found for key name string", pStartString);
			o_pParse = pParse;
			return;
		}

		if constexpr (tf_CParseContext::mc_bAllowSingleQuote)
		{
			if (*pParse == '\'')
			{
				auto pStartString = pParse;
				if (!fg_ParseJSONString<'\'', tf_CParseContext::mc_bAllowMultilineString>(o_Key, pParse, *this))
					f_ThrowError("End of string character ' not found for key name string", pStartString);
				o_pParse = pParse;
				return;
			}
		}

		if constexpr (tf_CParseContext::mc_bAllowKeyWithoutQuote)
		{
			if (fg_CharIsAlphabetical(*pParse) || fg_StrFindChar(tf_CParseContext::mc_AllowedKeyWithoutQuoteCharacters, *pParse) >= 0)
			{
				auto pStartString = pParse;
				while (fg_CharIsAlphabetical(*pParse) || fg_CharIsNumber(*pParse) || fg_StrFindChar(tf_CParseContext::mc_AllowedKeyWithoutQuoteCharacters, *pParse) >= 0)
					++pParse;
				o_Key = CStr(pStartString, pParse - pStartString);
				o_Key.f_SetUserData(EJSONStringType_NoQuote);
				o_pParse = pParse;
				return;
			}
		}

		CStr StartCharacters = "\"";
		if constexpr (tf_CParseContext::mc_bAllowSingleQuote)
			StartCharacters += " or '";

		f_ThrowError("Expected {} to start object key name"_f << StartCharacters, pParse);
	}

	template <typename tf_CParseContext, typename tf_CStr, typename tf_CSourceStr>
	void CParseContext::fs_GenerateString(tf_CStr &o_String, tf_CSourceStr const &_Value)
	{
		if constexpr (tf_CParseContext::mc_bAllowSingleQuote)
		{
			if (_Value.f_GetUserData() == EJSONStringType_SingleQuote)
			{
				fg_GenerateJSONString<'\'', tf_CParseContext>(o_String, _Value);
				return;
			}
		}
		fg_GenerateJSONString<'\"', tf_CParseContext>(o_String, _Value);
	}

	template <typename tf_CParseContext, typename tf_CStr, typename tf_CSourceStr>
	void CParseContext::fs_GenerateKeyString(tf_CStr &o_String, tf_CSourceStr const &_Key)
	{
		using namespace NStr;
		if constexpr (tf_CParseContext::mc_bAllowKeyWithoutQuote)
		{
			if (_Key.f_GetUserData() == EJSONStringType_NoQuote)
			{
				auto *pParse = _Key.f_GetStr();
				if (fg_CharIsAlphabetical(*pParse) || fg_StrFindChar(tf_CParseContext::mc_AllowedKeyWithoutQuoteCharacters, *pParse) >= 0)
				{
					while (fg_CharIsAlphabetical(*pParse) || fg_CharIsNumber(*pParse) || fg_StrFindChar(tf_CParseContext::mc_AllowedKeyWithoutQuoteCharacters, *pParse) >= 0)
						++pParse;

					if (!*pParse)
					{
						o_String += _Key;
						return;
					}
				}
			}
		}

		return tf_CParseContext::template fs_GenerateString<tf_CParseContext>(o_String, _Key);
	}

	template <typename tf_CParseContext>
	static void fg_ParseJSONArray(CJSON &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context)
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

			DMibCheck(Child.f_Type() != EJSONType_Invalid || _Context.m_bAllowUndefined);

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

	template <typename tf_CParseContext>
	static void fg_ParseJSONObject(CJSON &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context)
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

			CStr KeyName;

			auto pKeyStart = pParse;
			_Context.template f_ParseKey<tf_CParseContext>(KeyName, pParse);

			fg_ParseWhiteSpace(pParse);

			if (*pParse != ':')
				_Context.f_ThrowError("Expected : to follow key name in object", pParse);

			++pParse;
			fg_ParseWhiteSpace(pParse);

			if constexpr (!tf_CParseContext::mc_bAllowDuplicateKeys)
			{
				if (Object.f_GetMember(KeyName))
					_Context.f_ThrowError("Duplicate keys not allowed", pKeyStart);
			}

			auto &Child = Object.f_CreateMember(KeyName);
			fg_ParseJSONValue(Child, pParse, _Context);
			DMibCheck(Child.f_Type() != EJSONType_Invalid || _Context.m_bAllowUndefined);

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

	template <uch8 t_QuoteCharacter, bool t_bAllowMultilineString, typename tf_CParseContext>
	static bool fg_ParseJSONString(NStr::CStr &o_String, uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		using namespace NStr;
		uch8 const *pParse = o_pParse;
		auto Cleanup = g_OnScopeExit > [&]
			{
				o_pParse = pParse;
				switch (t_QuoteCharacter)
				{
					case '\"': o_String.f_SetUserData(EJSONStringType_DoubleQuote); break;
					case '\'': o_String.f_SetUserData(EJSONStringType_SingleQuote); break;
					default: o_String.f_SetUserData(EJSONStringType_Custom); break;
				}
			}
		;

		DMibRequire(*pParse == t_QuoteCharacter);
		++pParse;

		auto fAddChar = [&](uch8 _Character)
			{
				o_String.f_AddChar(_Character);
				if constexpr (tf_CParseContext::mc_bRecordStringMap)
					_Context.f_MapCharacter(o_String.f_GetLen() - 1, pParse - _Context.m_pStartParse, 1);
			}
		;

		while (*pParse)
		{
			if (*pParse == t_QuoteCharacter)
			{
				++pParse;
				if constexpr (t_bAllowMultilineString)
				{
					if (*pParse == '\\')
					{
						++pParse;
						fg_ParseWhiteSpace(pParse);
						if (*pParse != t_QuoteCharacter)
							_Context.f_ThrowError("Expected continuation of string", pParse);
						++pParse;
					}
					else
						return true;
				}
				else
					return true;
			}
			else if(*pParse == '\\')
			{
				++pParse;
				switch (*pParse)
				{
				case '\\':
				case '/':
				case t_QuoteCharacter:
					fAddChar(*pParse);
					++pParse;
					break;
				case 'b':
					fAddChar(0x08);
					++pParse;
					break;
				case 'f':
					fAddChar(0x0C);
					++pParse;
					break;
				case 'n':
					fAddChar(0x0A);
					++pParse;
					break;
				case 'r':
					fAddChar(0x0D);
					++pParse;
					break;
				case 't':
					fAddChar(0x09);
					++pParse;
					break;
				case 'u':
					{
						[[maybe_unused]] auto pStart = pParse;
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
								_Context.f_ThrowError("Too short escaped UTF16 value", pParseStart);

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
								_Context.f_ThrowError("Invalid escaped UTF16 value", pParseStart);

							if (HexDigit == 0)
							{
								if (_Context.m_bConvertNullToSpace)
									EscapedUTF16String.f_AddChar(' ');
								else
									_Context.f_ThrowError("Null characters not supported in this implementation", pParseStart);
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

						if constexpr (tf_CParseContext::mc_bRecordStringMap)
						{
							auto StartLen = o_String.f_GetLen();
							o_String += EscapedUTF16String;
							_Context.f_MapCharacter(StartLen, pStart - o_pParse, o_String.f_GetLen());
						}
						else
							o_String += EscapedUTF16String;
					}
					break;
				default:
					_Context.f_ThrowError("Invalid escape value", pParse);
					break;
				}
			}
			else
			{
				auto Character = *pParse;
				if (Character < 32)
				{
					bool bAllowCharacter = false;
					if constexpr (sizeof(tf_CParseContext::mc_AllowedControlCharacters) > 1)
					{
						for (auto AllowdCharacter : tf_CParseContext::mc_AllowedControlCharacters)
						{
							if (!AllowdCharacter)
								continue;

							if (Character == AllowdCharacter)
							{
								bAllowCharacter = true;
								break;
							}
						}
					}
					if (!bAllowCharacter)
						_Context.f_ThrowError("Control characters or new lines not allowed in string. Use escaped characters.", pParse);
				}
				fAddChar(Character);
				++pParse;
			}
		}

		return false;
	}

	template <typename tf_CParseContext>
	static void fg_ParseJSONValue(CJSON &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context)
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
						_Context.f_ThrowErrors(Errors);
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
						_Context.f_ThrowErrors(Errors);
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
					if (!fg_ParseJSONString<'\"', tf_CParseContext::mc_bAllowMultilineString>(ParsedString, pParse, _Context))
						_Context.f_ThrowError("End of string character \" not found for string", pParseStart);

					o_Value = ParsedString;
					return;
				}
				break;
			default:
				{
					if constexpr (tf_CParseContext::mc_bAllowSingleQuote)
					{
						if (Char == '\'')
						{
							// String
							CStr ParsedString;
							auto pParseStart = pParse;
							if (!fg_ParseJSONString<'\'', tf_CParseContext::mc_bAllowMultilineString>(ParsedString, pParse, _Context))
								_Context.f_ThrowError("End of string character ' not found for string", pParseStart);

							o_Value = ParsedString;
							return;
						}
					}
					auto pParseStart = pParse;
					if (fg_StrStartsWith(pParse, "true"))
					{
						pParse += 4;
						if (!(*pParse) || fg_StrFindChar(tf_CParseContext::mc_ConstantEndCharacters, *pParse) >= 0 || fg_CharIsWhiteSpace(*pParse))
						{
							o_Value = true;
							return;
						}
					}
					else if (fg_StrStartsWith(pParse, "false"))
					{
						pParse += 5;
						if (!(*pParse) || fg_StrFindChar(tf_CParseContext::mc_ConstantEndCharacters, *pParse) >= 0 || fg_CharIsWhiteSpace(*pParse))
						{
							o_Value = false;
							return;
						}
					}
					else if (fg_StrStartsWith(pParse, "null"))
					{
						pParse += 4;
						if (!(*pParse) || fg_StrFindChar(tf_CParseContext::mc_ConstantEndCharacters, *pParse) >= 0 || fg_CharIsWhiteSpace(*pParse))
						{
							o_Value = nullptr;
							return;
						}
					}
					else if (_Context.m_bAllowUndefined && fg_StrStartsWith(pParse, "undefined"))
					{
						pParse += 9;
						if (!(*pParse) || fg_StrFindChar(tf_CParseContext::mc_ConstantEndCharacters, *pParse) >= 0 || fg_CharIsWhiteSpace(*pParse))
						{
							o_Value = CJSON();
							return;
						}
					}

					bool bFailed = false;
					uch8 const *pTryParse = pParse;
					int64 Number = fg_StrToIntParse
						(
							pTryParse
							, int64(0)
							, tf_CParseContext::mc_ConstantEndCharacters
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
							, tf_CParseContext::mc_ConstantEndCharacters
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

					if constexpr (tf_CParseContext::mc_bCustomParse)
					{
						if (_Context.f_ParseValue(o_Value, pParse))
							return;
					}

					_Context.f_ThrowError(fg_Format("Invalid literal starting with: {}", CStr(pParse, 4)), pParseStart);
				}
				break;
			}
		}
	}
}
