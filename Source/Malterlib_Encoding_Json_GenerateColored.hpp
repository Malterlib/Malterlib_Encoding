// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_Json.h"

#include <Mib/CommandLine/AnsiEncoding>

namespace NMib::NEncoding
{
	namespace NPrivate
	{
		using namespace NStr;
		using namespace NCommandLine;

		template <typename t_CJson>
		struct TCJsonColorGenerator
		{
			using ESyntaxColor = CAnsiEncoding::ESyntaxColor;

			CStr f_Color(CStr const &_String, ESyntaxColor _Color)
			{
				if (!(m_AnsiFlags & EAnsiEncodingFlag_Color))
					return _String;

				CAnsiEncoding AnsiEncoding(m_AnsiFlags);
				return AnsiEncoding.f_SyntaxColor(_Color, _String);
			}

			void f_AddPrefix(NStr::CStr &o_String, mint _Depth, ch8 const *_pPrettySeparator)
			{
				for (mint i = 0; i < _Depth; ++i)
					o_String += _pPrettySeparator;
			}

			CStr f_GenerateJsonString(NStr::CStr const &_Value)
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

				return f_Color(String, ESyntaxColor::ESyntaxColor_String);
			}

			void f_GenerateJsonObject(NStr::CStr &o_String, t_CJson const &_Value, mint _Depth, ch8 const *_pPrettySeparator)
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
					o_String += f_GenerateJsonString(Child.f_Name());
					if (_pPrettySeparator)
						o_String += ": ";
					else
						o_String += ":";
					f_GenerateJsonValue(o_String, Child.f_Value(), _Depth + 1, _pPrettySeparator);
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

			void f_GenerateJsonArray(NStr::CStr &o_String, t_CJson const &_Value, mint _Depth, ch8 const *_pPrettySeparator)
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
					f_GenerateJsonValue(o_String, Child, _Depth + 1, _pPrettySeparator);
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

			void f_GenerateJsonValue(NStr::CStr &o_String, t_CJson const &_Value, mint _Depth, ch8 const *_pPrettySeparator)
			{
				using namespace NStr;

				auto &JsonValue = _Value;

				switch (JsonValue.f_Type())
				{
				case EJsonType_String:
					o_String += f_GenerateJsonString(JsonValue.f_String());
					break;
				case EJsonType_Integer:
					o_String += f_Color(CStr::fs_ToStr(JsonValue.f_Integer()), ESyntaxColor::ESyntaxColor_Number);
					break;
				case EJsonType_Float:
					{
						auto &Float = JsonValue.f_Float();
						if (Float.f_IsInvalid() && !(m_Flags & EJsonDialectFlag_AllowInvalidFloat))
							o_String += f_Color("null", ESyntaxColor::ESyntaxColor_Number); // QNaN, Inf etc is not representable in Json
						else
						{
							if (m_Flags & EJsonDialectFlag_HighPrecisionFloat)
								o_String += f_Color(CStr(CStr::CFormat("{ffs,fdb}") << JsonValue.f_Float()), ESyntaxColor::ESyntaxColor_Number);
							else
								o_String += f_Color(CStr(CStr::CFormat("{ffs}") << JsonValue.f_Float()), ESyntaxColor::ESyntaxColor_Number);
						}
					}
					break;
				case EJsonType_Object:
					f_GenerateJsonObject(o_String, _Value, _Depth, _pPrettySeparator);
					break;
				case EJsonType_Array:
					f_GenerateJsonArray(o_String, _Value, _Depth, _pPrettySeparator);
					break;
				case EJsonType_Null:
					o_String += f_Color("null", ESyntaxColor::ESyntaxColor_Constant);
					break;
				case EJsonType_Boolean:
					if (JsonValue.f_Boolean())
						o_String += f_Color("true", ESyntaxColor::ESyntaxColor_Constant);
					else
						o_String += f_Color("false", ESyntaxColor::ESyntaxColor_Constant);
					break;
				case EJsonType_Invalid:
					if (m_Flags & EJsonDialectFlag_AllowUndefined)
					{
						o_String += "undefined";
						break;
					}
					[[fallthrough]];
				default:
					DMibError("Invalid JSON type in value node");
				break;
				}
			}

			NStr::CStr f_ToString(t_CJson const &_Json, ch8 const *_pPrettySeparator)
			{
				using namespace NStr;

				CStr Return;

				f_GenerateJsonValue(Return, _Json, 0, _pPrettySeparator);

				if (_pPrettySeparator && !(m_Flags & EJsonDialectFlag_TrimWhitespace))
					Return += "\n";

				return Return;
			}

			EJsonDialectFlag m_Flags;
			NCommandLine::EAnsiEncodingFlag m_AnsiFlags;
		};

		template <typename tf_CJson>
		NStr::CStr fg_JsonGenerateColored(tf_CJson const &_Json, ch8 const *_pPrettySeparator, NCommandLine::EAnsiEncodingFlag _AnsiFlags, EJsonDialectFlag _Flags)
		{
			TCJsonColorGenerator<tf_CJson> Generator;
			Generator.m_Flags = _Flags;
			Generator.m_AnsiFlags = _AnsiFlags;

			return Generator.f_ToString(_Json, _pPrettySeparator);
		}
	}
}
