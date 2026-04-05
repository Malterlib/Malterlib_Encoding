// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json_Parse.h"

#include <Mib/String/Appender>

namespace NMib::NEncoding::NJson
{
	template <typename tf_CStr>
	static void fg_AddPrefix(tf_CStr &o_String, umint _Depth, ch8 const *_pPrettySeparator)
	{
		umint SeparatorLength = NStr::fg_StrLen(_pPrettySeparator);
		for (umint i = 0; i < _Depth; ++i)
			o_String.f_AddString(_pPrettySeparator, SeparatorLength);
	}

	template <ch8 t_QuoteCharacter, typename tf_CParseContext, bool tf_bAddQuotes, typename tf_CStr, typename tf_CSourceString>
	static void fg_GenerateJsonString(tf_CStr &o_String, tf_CSourceString const &_Value)
	{
		using namespace NStr;

		umint StartOfLine = o_String.f_GetStrLen();

		if constexpr (tf_bAddQuotes)
			o_String += t_QuoteCharacter;
		else
			--StartOfLine;

		ch8 const *pParse = _Value;

		typename tf_CStr::CString::CString PreWhitespace;
		bool bInitPreWhitespace = false;
		auto fAddPreWhitespace = [&]()
			{
				if constexpr (tf_CParseContext::mc_ParseJsonStringFlags & EParseJsonStringFlag_AllowMultiLine)
				{
					if (!bInitPreWhitespace)
					{
						auto Committed = o_String.f_Commit();

						bInitPreWhitespace = true;
						auto iPrevLine = Committed.m_String.f_FindCharReverse('\n', StartOfLine);
						if (iPrevLine >= 0)
							PreWhitespace = Committed.m_String.f_Extract(iPrevLine + 1, StartOfLine - (iPrevLine + 1));
						else
							PreWhitespace = Committed.m_String.f_Extract(0, StartOfLine);
					}

					for (auto UTFIterator = PreWhitespace.f_GetUnicodeIterator(); UTFIterator; ++UTFIterator)
					{
						if (fg_CharIsWhiteSpace(*UTFIterator))
						{
							DMibFastCheck(*UTFIterator < 127);
							o_String += ch8(*UTFIterator);
						}
						else
							o_String += ' ';
					}
				}
			}
		;

		while (*pParse)
		{
			auto UnsignedChar = fg_Unsigned(*pParse);
			switch (UnsignedChar)
			{
			case t_QuoteCharacter:
				o_String += '\\';
				o_String += t_QuoteCharacter;
				break;
			case '\\':
				o_String += "\\\\";
				break;
			case 0x08:
				o_String += "\\b";
				break;
			case 0x0C:
				o_String += "\\f";
				break;
			case 0x0A:
			case 0x0D:
				if (UnsignedChar == 0x0A)
				{
					o_String += "\\n";
				}
				else
				{
					o_String += "\\r";
				}

				if constexpr (tf_CParseContext::mc_ParseJsonStringFlags & EParseJsonStringFlag_AllowMultiLine)
				{
					if (fg_StrStartsWith(pParse, "\r\n"))
					{
						o_String += "\\n";
						++pParse;
					}
					o_String += t_QuoteCharacter;
					o_String += "\\\n";
					fAddPreWhitespace();
					o_String += t_QuoteCharacter;
				}
				break;
			case 0x09:
				o_String += "\\t";
				break;
			default:
				if (UnsignedChar < 32)
				{
					auto Committed = o_String.f_Commit();
					Committed.m_String += typename tf_CStr::CString::CFormat("\\u{nfh,sf0,sj4}") << UnsignedChar; // Control character, add as hex
				}
				else
					o_String += *pParse;
				break;
			}
			++pParse;
		}

		if constexpr (tf_bAddQuotes)
			o_String += t_QuoteCharacter;
	}

	template <typename tf_CParseContext, typename tf_CStr, typename tf_CJson>
	static void fg_GenerateJsonObject(tf_CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags)
	{
		auto iChild = _Value.f_OrderedIterator();
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
				fg_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);

			tf_CParseContext::template fs_GenerateKeyString<tf_CParseContext>(o_String, Child.f_Name());

			if (_pPrettySeparator)
				o_String += ": ";
			else
				o_String += ":";

			fg_GenerateJsonValue<tf_CParseContext>(o_String, Child.f_Value(), _Depth + 1, _pPrettySeparator, _Flags);

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
			fg_AddPrefix(o_String, _Depth, _pPrettySeparator);
		o_String += "}";
	}

	template <typename tf_CParseContext, typename tf_CStr, typename tf_CJson>
	static void fg_GenerateJsonArray(tf_CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags)
	{
		auto iChild = _Value.f_GetIterator();
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
				fg_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);

			fg_GenerateJsonValue<tf_CParseContext>(o_String, Child, _Depth + 1, _pPrettySeparator, _Flags);

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
			fg_AddPrefix(o_String, _Depth, _pPrettySeparator);
		o_String += "]";
	}

	template <typename tf_CParseContext, typename tf_CStr, typename tf_CJson>
	static void fg_GenerateJsonValue(tf_CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags)
	{
		using namespace NStr;

		auto &JsonValue = _Value;

		if constexpr (tf_CParseContext::mc_bCustomGenerate)
		{
			if (tf_CParseContext::template fs_GenerateValue<tf_CParseContext>(o_String, _Value, _Depth, _pPrettySeparator, _Flags))
				return;
		}

		switch (JsonValue.f_Type())
		{
		case EJsonType_String:
			tf_CParseContext::template fs_GenerateString<tf_CParseContext>(o_String, JsonValue.f_String());
			break;
		case EJsonType_Integer:
			{
				using CFormatType = typename TCStringFormatterAll<typename tf_CStr::CString::CFormat, int64>::CFormatType;
				auto Committed = o_String.f_Commit();
				aint CurrentLen = Committed.m_String.f_GetLen();
				CFormatType::fs_AddToStrStatic(Committed.m_String, CurrentLen, typename CFormatType::CType(JsonValue.f_Integer()));
				Committed.m_String.f_SetStrLen(CurrentLen);
			}
			break;
		case EJsonType_Float:
			{
				auto &Float = JsonValue.f_Float();
				if (Float.f_IsInvalid() && !(_Flags & EJsonDialectFlag_AllowInvalidFloat))
					o_String += "null"; // QNaN, Inf etc is not representable in Json
				else
				{
					auto Committed = o_String.f_Commit();
					using CFormatType = typename TCStringFormatterAll<typename tf_CStr::CString::CFormat, fp64>::CFormatType;
					aint CurrentLen = Committed.m_String.f_GetLen();

					typename CFormatType::COptionsFloat Options;
					Options.m_FloatFormat = CFormatType::COptionsFloat::EFloatFormat_ShortestLowerCase;
					if (_Flags & EJsonDialectFlag_HighPrecisionFloat)
						Options.m_MinDigits = -2;

					CFormatType::fs_AddToStrStatic(Committed.m_String, CurrentLen, typename CFormatType::CType(JsonValue.f_Float()), Options);
					Committed.m_String.f_SetStrLen(CurrentLen);
				}
			}
			break;
		case EJsonType_Object:
			fg_GenerateJsonObject<tf_CParseContext>(o_String, _Value.f_Object(), _Depth, _pPrettySeparator, _Flags & EJsonDialectFlag_All);
			break;
		case EJsonType_Array:
			fg_GenerateJsonArray<tf_CParseContext>(o_String, _Value.f_Array(), _Depth, _pPrettySeparator, _Flags & EJsonDialectFlag_All);
			break;
		case EJsonType_Null:
			o_String += "null";
			break;
		case EJsonType_Boolean:
			if (JsonValue.f_Boolean())
				o_String += "true";
			else
				o_String += "false";
			break;
		case EJsonType_Invalid:
			if (_Flags & EJsonDialectFlag_AllowUndefined)
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

}

namespace NMib::NEncoding
{
	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_ToString(ch8 const * _pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		using namespace NStr;

		CStr Return;
		{
			CStr::CAppender StringAppender(Return);

			NJson::fg_GenerateJsonValue<NJson::CParseContext>(StringAppender, *this, 0, _pPrettySeparator, _Flags);

			if (_pPrettySeparator && !(_Flags & EJsonDialectFlag_TrimWhitespace))
				StringAppender += "\n";
		}
		return Return;
	}
}
