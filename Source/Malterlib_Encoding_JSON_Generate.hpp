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
		for (mint i = 0; i < _Depth; ++i)
			o_String += _pPrettySeparator;
	}

	template <ch8 t_QuoteCharacter, typename tf_CParseContext, bool tf_bAddQuotes, typename tf_CStr, typename tf_CSourceString>
	static void fg_GenerateJSONString(tf_CStr &o_String, tf_CSourceString const &_Value)
	{
		using namespace NStr;

		mint StartOfLine = o_String.f_GetLen();

		typename tf_CStr::CAppender StringAppender(o_String);

		if constexpr (tf_bAddQuotes)
			StringAppender += t_QuoteCharacter;
		else
			--StartOfLine;

		ch8 const *pParse = _Value;

		typename tf_CStr::CDynamicStr PreWhitespace;
		bool bInitPreWhitespace = false;
		auto fAddPreWhitespace = [&]()
			{
				if constexpr (tf_CParseContext::mc_ParseJSONStringFlags & EParseJSONStringFlag_AllowMultiLine)
				{
					if (!bInitPreWhitespace)
					{
						StringAppender.f_Commit();

						bInitPreWhitespace = true;
						auto iPrevLine = o_String.f_FindCharReverse('\n', StartOfLine);
						if (iPrevLine >= 0)
							PreWhitespace = o_String.f_Extract(iPrevLine + 1, StartOfLine - (iPrevLine + 1));
						else
							PreWhitespace = o_String.f_Extract(0, StartOfLine);
					}

					for (auto UTFIterator = PreWhitespace.f_GetUnicodeIterator(); UTFIterator; ++UTFIterator)
					{
						if (fg_CharIsWhiteSpace(*UTFIterator))
						{
							DMibFastCheck(*UTFIterator < 127);
							StringAppender += ch8(*UTFIterator);
						}
						else
							StringAppender += ' ';
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
				StringAppender += '\\';
				StringAppender += t_QuoteCharacter;
				break;
			case '\\':
				StringAppender += '\\';
				StringAppender += '\\';
				break;
			case 0x08:
				StringAppender += '\\';
				StringAppender += 'b';
				break;
			case 0x0C:
				StringAppender += '\\';
				StringAppender += 'f';
				break;
			case 0x0A:
			case 0x0D:
				if (UnsignedChar == 0x0A)
				{
					StringAppender += '\\';
					StringAppender += 'n';
				}
				else
				{
					StringAppender += '\\';
					StringAppender += 'r';
				}

				if constexpr (tf_CParseContext::mc_ParseJSONStringFlags & EParseJSONStringFlag_AllowMultiLine)
				{
					if (fg_StrStartsWith(pParse, "\r\n"))
					{
						StringAppender += '\\';
						StringAppender += 'n';
						++pParse;
					}
					StringAppender += t_QuoteCharacter;
					StringAppender += '\\';
					StringAppender += '\n';
					fAddPreWhitespace();
					StringAppender += t_QuoteCharacter;
				}
				break;
			case 0x09:
				StringAppender += '\\';
				StringAppender += 't';
				break;
			default:
				if (UnsignedChar < 32)
				{
					StringAppender.f_Commit();
					o_String += typename tf_CStr::CFormat("\\u{nfh,sf0,sj4}") << UnsignedChar; // Control character, add as hex
					StringAppender.f_Reset();
				}
				else
					StringAppender += *pParse;
				break;
			}
			++pParse;
		}

		if constexpr (tf_bAddQuotes)
			StringAppender += t_QuoteCharacter;
	}

	template <typename tf_CParseContext, typename tf_CStr>
	static void fg_GenerateJSONObject(tf_CStr &o_String, CJSON const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags)
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

	template <typename tf_CParseContext, typename tf_CStr>
	static void fg_GenerateJSONArray(tf_CStr &o_String, CJSON const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags)
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

	template <typename tf_CParseContext, typename tf_CStr>
	static void fg_GenerateJSONValue(tf_CStr &o_String, CJSON const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags)
	{
		using namespace NStr;

		auto &JSONValue = _Value;

		if constexpr (tf_CParseContext::mc_bCustomGenerate)
		{
			if (tf_CParseContext::template fs_GenerateValue<tf_CParseContext>(o_String, _Value, _Depth, _pPrettySeparator))
				return;
		}

		switch (JSONValue.f_Type())
		{
		case EJSONType_String:
			tf_CParseContext::template fs_GenerateString<tf_CParseContext>(o_String, JSONValue.f_String());
			break;
		case EJSONType_Integer:
			o_String += CStr::fs_ToStr(JSONValue.f_Integer());
			break;
		case EJSONType_Float:
			{
				auto &Float = JSONValue.f_Float();
				if (Float.f_IsInvalid() && !(_Flags & EJSONDialectFlag_AllowInvalidFloat))
					o_String += "null"; // QNaN, Inf etc is not representable in JSON
				else
					o_String += CStr::fs_ToStr(JSONValue.f_Float());
			}
			break;
		case EJSONType_Object:
			fg_GenerateJSONObject<tf_CParseContext>(o_String, _Value, _Depth, _pPrettySeparator, _Flags);
			break;
		case EJSONType_Array:
			fg_GenerateJSONArray<tf_CParseContext>(o_String, _Value, _Depth, _pPrettySeparator, _Flags);
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
