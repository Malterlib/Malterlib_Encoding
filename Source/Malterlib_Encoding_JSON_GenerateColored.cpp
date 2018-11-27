// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_JSON.h"

#include <Mib/CommandLine/AnsiEncoding>

namespace NMib
{
	namespace NEncoding
	{
		namespace NPrivate
		{
			using namespace NStr;
			using namespace NCommandLine;

			struct CJSONColorGenerator
			{
				enum EColor
				{
					EColor_Number
					, EColor_String
					, EColor_Constant
					, EColor_Date
					, EColor_Binary
				};

				static CStr fs_Color(CStr const &_String, EColor _Color)
				{
					switch (_Color)
					{
					case EColor_String: return "{}{}{}"_f << CAnsiEncoding::fs_ForegroundRGB(0x00, 0x9e, 0xff) << _String << CAnsiEncoding::ms_Default;
					case EColor_Number: return "{}{}{}"_f << CAnsiEncoding::fs_ForegroundRGB(0xff, 0x00, 0x80) << _String << CAnsiEncoding::ms_Default;
					case EColor_Constant: return "{}{}{}"_f << CAnsiEncoding::fs_ForegroundRGB(0xff, 0x8a, 0xc5) << _String << CAnsiEncoding::ms_Default;
					case EColor_Date: return "{}{}{}"_f << CAnsiEncoding::fs_ForegroundRGB(0xff, 0x5b, 0xad) << _String << CAnsiEncoding::ms_Default;
					case EColor_Binary: return "{}{}{}"_f << CAnsiEncoding::fs_ForegroundRGB(0x80, 0x80, 0x80) << _String << CAnsiEncoding::ms_Default;
					default: return _String;
					}
				}

				void f_AddPrefix(NStr::CStr &o_String, mint _Depth, ch8 const *_pPrettySeparator)
				{
					for (mint i = 0; i < _Depth; ++i)
						o_String += _pPrettySeparator;
				}

				CStr f_GenerateJSONString(NStr::CStr const &_Value)
				{
					using namespace NStr;

					CStr String;

					String += "\"";

					ch8 const *pParse = _Value;

					while (*pParse)
					{
						auto UnsignedChar = fg_Unsigned(*pParse);
						switch (UnsignedChar)
						{
						case '\"':
							String += "\\\"";
							break;
						case '\\':
							String += "\\\\";
							break;
						case 0x08:
							String += "\\b";
							break;
						case 0x0C:
							String += "\\f";
							break;
						case 0x0A:
							String += "\\n";
							break;
						case 0x0D:
							String += "\\r";
							break;
						case 0x09:
							String += "\\t";
							break;
						default:
							if (UnsignedChar < 32)
								String += "\\u{nfh,sf0,sj4}"_f << UnsignedChar; // Control character, add as hex
							else
								String.f_AddChar(*pParse);
							break;
						}
						++pParse;
					}

					String += "\"";

					return fs_Color(String, EColor_String);
				}

				void f_GenerateJSONObject(NStr::CStr &o_String, CJSON const &_Value, mint _Depth, ch8 const *_pPrettySeparator)
				{
					auto iChild = _Value.f_Object().f_OrderedIterator();
					if (!iChild)
					{
						// Empty object
						o_String += "{}";
						return;
					}

					if (_pPrettySeparator)
						o_String += "{\n";
					else
						o_String += "{";

					while (iChild)
					{
						auto &Child = *iChild;
						++iChild;
						if (_pPrettySeparator)
							f_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);
						o_String += f_GenerateJSONString(Child.f_Name());
						if (_pPrettySeparator)
							o_String += ": ";
						else
							o_String += ":";
						f_GenerateJSONValue(o_String, Child.f_Value(), _Depth + 1, _pPrettySeparator);
						if (_pPrettySeparator)
						{
							if (iChild)
								o_String += ",\n";
							else
								o_String += "\n";
						}
						else if (iChild)
							o_String += ",";
					}
					if (_pPrettySeparator)
						f_AddPrefix(o_String, _Depth, _pPrettySeparator);
					o_String += "}";
				}

				void f_GenerateJSONArray(NStr::CStr &o_String, CJSON const &_Value, mint _Depth, ch8 const *_pPrettySeparator)
				{
					auto iChild = _Value.f_Array().f_GetIterator();
					if (!iChild)
					{
						// Empty array
						o_String += "[]";
						return;
					}

					if (_pPrettySeparator)
						o_String += "[\n";
					else
						o_String += "[";
					while (iChild)
					{
						auto &Child = *iChild;
						++iChild;
						if (_pPrettySeparator)
							f_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);
						f_GenerateJSONValue(o_String, Child, _Depth + 1, _pPrettySeparator);
						if (_pPrettySeparator)
						{
							if (iChild)
								o_String += ",\n";
							else
								o_String += "\n";
						}
						else if (iChild)
							o_String += ",";
					}
					if (_pPrettySeparator)
						f_AddPrefix(o_String, _Depth, _pPrettySeparator);
					o_String += "]";
				}

				void f_GenerateJSONValue(NStr::CStr &o_String, CJSON const &_Value, mint _Depth, ch8 const *_pPrettySeparator)
				{
					using namespace NStr;

					auto &JSONValue = _Value;

					switch (JSONValue.f_Type())
					{
					case EJSONType_String:
						o_String += f_GenerateJSONString(JSONValue.f_String());
						break;
					case EJSONType_Integer:
						o_String += fs_Color(CStr::fs_ToStr(JSONValue.f_Integer()), EColor_Number);
						break;
					case EJSONType_Float:
						{
							auto &Float = JSONValue.f_Float();
							if (Float.f_IsInvalid())
								o_String += fs_Color("null", EColor_Number); // QNaN, Inf etc is not representable in JSON
							else
								o_String += fs_Color(CStr::fs_ToStr(JSONValue.f_Float()), EColor_Number);
						}
						break;
					case EJSONType_Object:
						f_GenerateJSONObject(o_String, _Value, _Depth, _pPrettySeparator);
						break;
					case EJSONType_Array:
						f_GenerateJSONArray(o_String, _Value, _Depth, _pPrettySeparator);
						break;
					case EJSONType_Null:
						o_String += fs_Color("null", EColor_Constant);
						break;
					case EJSONType_Boolean:
						if (JSONValue.f_Boolean())
							o_String += fs_Color("true", EColor_Constant);
						else
							o_String += fs_Color("false", EColor_Constant);
						break;
					default:
						DMibError("Invalid JSON type in value node");
					break;
					}
				}

				NStr::CStr f_ToString(CJSON const &_JSON, ch8 const *_pPrettySeparator)
				{
					using namespace NStr;

					CStr Return;

					f_GenerateJSONValue(Return, _JSON, 0, _pPrettySeparator);

					if (_pPrettySeparator)
						Return += "\n";

					return Return;
				}
			};

			NStr::CStr fg_JSONGenerateColored(CJSON const &_JSON, ch8 const *_pPrettySeparator)
			{
				CJSONColorGenerator Generator;
				return Generator.f_ToString(_JSON, _pPrettySeparator);
			}
		}
	}
}
