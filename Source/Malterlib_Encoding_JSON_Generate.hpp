// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON_Parse.h"

#include <Mib/String/Appender>

namespace NMib::NEncoding::NJSON
{
	template <typename tf_CStr>
	static void fg_AddPrefix(tf_CStr &o_String, mint _Depth, ch8 const *_pPrettySeparator)
	{
		mint SeparatorLength = NStr::fg_StrLen(_pPrettySeparator);
		for (mint i = 0; i < _Depth; ++i)
			o_String.f_AddString(_pPrettySeparator, SeparatorLength);
	}

	template <ch8 t_QuoteCharacter, typename tf_CParseContext, bool tf_bAddQuotes, typename tf_CStr, typename tf_CSourceString>
	static void fg_GenerateJSONString(tf_CStr &o_String, tf_CSourceString const &_Value)
	{
		using namespace NStr;

		mint StartOfLine = o_String.f_GetStrLen();

		if constexpr (tf_bAddQuotes)
			o_String += t_QuoteCharacter;
		else
			--StartOfLine;

		ch8 const *pParse = _Value;

		typename tf_CStr::CString::CDynamicStr PreWhitespace;
		bool bInitPreWhitespace = false;
		auto fAddPreWhitespace = [&]()
			{
				if constexpr (tf_CParseContext::mc_ParseJSONStringFlags & EParseJSONStringFlag_AllowMultiLine)
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

				if constexpr (tf_CParseContext::mc_ParseJSONStringFlags & EParseJSONStringFlag_AllowMultiLine)
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
	static void fg_GenerateJSONObject(tf_CStr &o_String, tf_CJson const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags)
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
				fg_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);

			tf_CParseContext::template fs_GenerateKeyString<tf_CParseContext>(o_String, Child.f_Name());

			if (_pPrettySeparator)
				o_String += ": ";
			else
				o_String += ":";

			fg_GenerateJSONValue<tf_CParseContext>(o_String, Child.f_Value(), _Depth + 1, _pPrettySeparator, _Flags);

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
	static void fg_GenerateJSONArray(tf_CStr &o_String, tf_CJson const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags)
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
				fg_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);

			fg_GenerateJSONValue<tf_CParseContext>(o_String, Child, _Depth + 1, _pPrettySeparator, _Flags);

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
	static void fg_GenerateJSONValue(tf_CStr &o_String, tf_CJson const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags)
	{
		using namespace NStr;

		auto &JSONValue = _Value;

		if constexpr (tf_CParseContext::mc_bCustomGenerate)
		{
			if (tf_CParseContext::template fs_GenerateValue<tf_CParseContext>(o_String, _Value, _Depth, _pPrettySeparator, _Flags))
				return;
		}

		switch (JSONValue.f_Type())
		{
		case EJSONType_String:
			tf_CParseContext::template fs_GenerateString<tf_CParseContext>(o_String, JSONValue.f_String());
			break;
		case EJSONType_Integer:
			{
				typedef typename TCStringFormatterAll<typename tf_CStr::CString::CFormat, int64>::CFormatType CFormatType;
				auto Committed = o_String.f_Commit();
				aint CurrentLen = Committed.m_String.f_GetLen();
				CFormatType::fs_AddToStrStatic(Committed.m_String, CurrentLen, typename CFormatType::CType(JSONValue.f_Integer()));
				Committed.m_String.f_SetStrLen(CurrentLen);
			}
			break;
		case EJSONType_Float:
			{
				auto &Float = JSONValue.f_Float();
				if (Float.f_IsInvalid() && !(_Flags & EJSONDialectFlag_AllowInvalidFloat))
					o_String += "null"; // QNaN, Inf etc is not representable in JSON
				else
				{
					auto Committed = o_String.f_Commit();
					typedef typename TCStringFormatterAll<typename tf_CStr::CString::CFormat, fp64>::CFormatType CFormatType;
					aint CurrentLen = Committed.m_String.f_GetLen();

					typename CFormatType::COptionsFloat Options;
					Options.m_FloatFormat = CFormatType::COptionsFloat::EFloatFormat_ShortestLowerCase;
					if (_Flags & EJSONDialectFlag_HighPrecisionFloat)
						Options.m_MinDigits = -2;

					CFormatType::fs_AddToStrStatic(Committed.m_String, CurrentLen, typename CFormatType::CType(JSONValue.f_Float()), Options);
					Committed.m_String.f_SetStrLen(CurrentLen);
				}
			}
			break;
		case EJSONType_Object:
			fg_GenerateJSONObject<tf_CParseContext>(o_String, _Value, _Depth, _pPrettySeparator, _Flags & EJSONDialectFlag_All);
			break;
		case EJSONType_Array:
			fg_GenerateJSONArray<tf_CParseContext>(o_String, _Value, _Depth, _pPrettySeparator, _Flags & EJSONDialectFlag_All);
			break;
		case EJSONType_Null:
			o_String += "null";
			break;
		case EJSONType_Boolean:
			if (JSONValue.f_Boolean())
				o_String += "true";
			else
				o_String += "false";
			break;
		case EJSONType_Invalid:
			if (_Flags & EJSONDialectFlag_AllowUndefined)
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
