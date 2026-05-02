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
			if constexpr (tf_CParseContext::mc_bAllowExtendedEscapes)
			{
				if (fg_Unsigned(pParse[0]) == 0xE2 && fg_Unsigned(pParse[1]) == 0x80 && (fg_Unsigned(pParse[2]) == 0xA8 || fg_Unsigned(pParse[2]) == 0xA9))
				{
					if (fg_Unsigned(pParse[2]) == 0xA8)
						o_String += "\\u2028";
					else
						o_String += "\\u2029";
					pParse += 3;
					continue;
				}
			}

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

	template <typename tf_CParseContext>
	inline smint fg_FindTopLevelCommaInTrailing(NStr::CStr const &_Trailing)
	{
		auto TrailingLen = _Trailing.f_GetLen();
		auto const *pParse = _Trailing.f_GetStr();
		for (umint i = 0; i < TrailingLen; ++i)
		{
			if (pParse[i] == '/' && pParse[i + 1] == '/')
			{
				i += 2;
				while (i < TrailingLen && !fg_IsJsonLineTerminator<tf_CParseContext>(reinterpret_cast<uch8 const *>(pParse + i)))
					++i;
				--i;
				continue;
			}
			if (pParse[i] == '/' && pParse[i + 1] == '*')
			{
				i += 2;
				while (i + 1 < TrailingLen && !(pParse[i] == '*' && pParse[i + 1] == '/'))
					++i;
				++i;
				continue;
			}
			if (pParse[i] == '\"' || pParse[i] == '\'')
			{
				auto Quote = pParse[i++];
				while (i < TrailingLen)
				{
					if (pParse[i] == '\\')
					{
						++i;
						continue;
					}
					if (pParse[i] == Quote)
						break;
					++i;
				}
				continue;
			}
			if (pParse[i] == ',')
				return smint(i);
		}
		return -1;
	}

	template <typename tf_CParseContext>
	inline void fg_GetJsonTriviaOpenCommentState(NStr::CStr const &_Trivia, bool &o_bLineComment, bool &o_bBlockComment)
	{
		o_bLineComment = false;
		o_bBlockComment = false;

		auto TriviaLen = _Trivia.f_GetLen();

		auto const *pParse = _Trivia.f_GetStr();
		for (umint i = 0; i < TriviaLen; ++i)
		{
			if (o_bLineComment)
			{
				auto pLineTerminator = reinterpret_cast<uch8 const *>(pParse + i);
				if (fg_ParseJsonLineTerminator<tf_CParseContext>(pLineTerminator))
				{
					o_bLineComment = false;
					i = (reinterpret_cast<ch8 const *>(pLineTerminator) - pParse) - 1;
				}
				continue;
			}

			if (o_bBlockComment)
			{
				if (pParse[i] == '*' && i + 1 < TriviaLen && pParse[i + 1] == '/')
				{
					o_bBlockComment = false;
					++i;
				}
				continue;
			}

			if (pParse[i] == '/' && i + 1 < TriviaLen)
			{
				if (pParse[i + 1] == '/')
				{
					o_bLineComment = true;
					++i;
				}
				else if (pParse[i + 1] == '*')
				{
					o_bBlockComment = true;
					++i;
				}
			}
		}
	}

	template <typename tf_CParseContext>
	inline bool fg_JsonTriviaStartsWithLineTerminator(NStr::CStr const &_Trivia)
	{
		if (_Trivia.f_IsEmpty())
			return false;
		return fg_IsJsonLineTerminator<tf_CParseContext>(reinterpret_cast<uch8 const *>(_Trivia.f_GetStr()));
	}

	template <typename tf_CParseContext, typename tf_CStr>
	static void fg_AppendJsonTrivia(tf_CStr &o_String, NStr::CStr const &_Trivia, bool _bNextStartsWithLineTerminator)
	{
		o_String += _Trivia;

		bool bLineComment = false;
		bool bBlockComment = false;
		fg_GetJsonTriviaOpenCommentState<tf_CParseContext>(_Trivia, bLineComment, bBlockComment);
		if (bBlockComment)
			o_String += "*/";
		if (bLineComment && !_bNextStartsWithLineTerminator)
			o_String += "\n";
	}

	template <typename tf_CParseContext, typename tf_CStr>
	static void fg_AppendJsonTrailing
		(
			tf_CStr &o_String
			, NStr::CStr const &_Trailing
			, bool _bHasComma
			, bool _bNeedSeparatorAfter
			, bool _bLast
			, bool _bAllowTrailingCommas
			, bool _bNextStartsWithLineTerminator
		)
	{
		auto iComma = fg_FindTopLevelCommaInTrailing<tf_CParseContext>(_Trailing);
		if (_bLast && !_bAllowTrailingCommas && iComma >= 0)
		{
			NStr::CStr StrippedTrailing(_Trailing.f_GetStr(), iComma);
			StrippedTrailing += NStr::CStr(_Trailing.f_GetStr() + iComma + 1, _Trailing.f_GetLen() - iComma - 1);
			fg_AppendJsonTrivia<tf_CParseContext>(o_String, StrippedTrailing, _bNextStartsWithLineTerminator);
			return;
		}

		if ((_bNeedSeparatorAfter || (_bLast && _bAllowTrailingCommas && _bHasComma)) && iComma < 0)
			o_String += ',';
		fg_AppendJsonTrivia<tf_CParseContext>(o_String, _Trailing, _bNextStartsWithLineTerminator);
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

		bool bFirstLeading = false;
		if constexpr (tf_CJson::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
			bFirstLeading = iChild->f_KeyTrivia().f_IsLeadingSet();

		if (_pPrettySeparator && !bFirstLeading)
			o_String += "{\n";
		else
			o_String += "{";

		bool bUseLeadingCommaForAutomaticSeparators = false;
		if constexpr (tf_CJson::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
		{
			bool bFirstChild = true;
			for (auto iStyleChild = _Value.f_OrderedIterator(); iStyleChild; ++iStyleChild)
			{
				if
				(
					!bFirstChild
					&& (iStyleChild->f_KeyTrivia().f_HasLeadingComma() || fg_FindTopLevelCommaInTrailing<tf_CParseContext>(iStyleChild->f_KeyTrivia().f_Leading()) >= 0)
				)
				{
					bUseLeadingCommaForAutomaticSeparators = true;
					break;
				}
				bFirstChild = false;
			}
		}

		bool bFirstChild = true;
		while (iChild)
		{
			auto &Child = *iChild;
			++iChild;
			bool bLast = !iChild;
			bool bChildCommaInLeading = false;
			bool bNextLeadingSet = false;
			bool bNextCommaInLeading = false;
			bool bNextLeadingStartsWithLineTerminator = false;
			if constexpr (tf_CJson::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
			{
				bChildCommaInLeading = fg_FindTopLevelCommaInTrailing<tf_CParseContext>(Child.f_KeyTrivia().f_Leading()) >= 0;
				if (iChild)
				{
					bNextLeadingSet = iChild->f_KeyTrivia().f_IsLeadingSet();
					bNextCommaInLeading = fg_FindTopLevelCommaInTrailing<tf_CParseContext>(iChild->f_KeyTrivia().f_Leading()) >= 0;
					bNextLeadingStartsWithLineTerminator = bNextLeadingSet && fg_JsonTriviaStartsWithLineTerminator<tf_CParseContext>(iChild->f_KeyTrivia().f_Leading());
				}
			}

			bool bWroteLeading = false;
			if constexpr (tf_CJson::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
			{
				if (Child.f_KeyTrivia().f_IsLeadingSet())
				{
					fg_AppendJsonTrivia<tf_CParseContext>(o_String, Child.f_KeyTrivia().f_Leading(), false);
					bWroteLeading = true;
				}
			}
			if (_pPrettySeparator && !bWroteLeading)
			{
				fg_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);
			}
			if (bUseLeadingCommaForAutomaticSeparators && !bFirstChild && !bChildCommaInLeading)
			{
				o_String += ",";
				if (_pPrettySeparator)
					o_String += " ";
			}

			tf_CParseContext::template fs_GenerateKeyString<tf_CParseContext>(o_String, Child.f_Name());

			bool bWroteTrailingKey = false;
			if constexpr (tf_CJson::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
			{
				if (Child.f_KeyTrivia().f_IsTrailingSet())
				{
					fg_AppendJsonTrivia<tf_CParseContext>(o_String, Child.f_KeyTrivia().f_Trailing(), false);
					bWroteTrailingKey = true;
				}
			}
			o_String += ":";

			bool bWroteLeadingValue = false;
			if constexpr (tf_CJson::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
			{
				if (Child.f_Value().f_Trivia().f_IsLeadingSet())
				{
					fg_AppendJsonTrivia<tf_CParseContext>(o_String, Child.f_Value().f_Trivia().f_Leading(), false);
					bWroteLeadingValue = true;
				}
			}
			if (_pPrettySeparator && !bWroteTrailingKey && !bWroteLeadingValue)
				o_String += " ";

			fg_GenerateJsonValue<tf_CParseContext>(o_String, Child.f_Value(), _Depth + 1, _pPrettySeparator, _Flags);

			bool bWroteTrailing = false;
			if constexpr (tf_CJson::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
			{
				if (Child.f_Value().f_Trivia().f_IsTrailingSet())
				{
					fg_AppendJsonTrailing<tf_CParseContext>
						(
							o_String
							, Child.f_Value().f_Trivia().f_Trailing()
							, Child.f_Value().f_Trivia().f_HasTrailingComma()
							, iChild && !(bNextCommaInLeading || bUseLeadingCommaForAutomaticSeparators)
							, bLast
							, tf_CParseContext::mc_bAllowTrailingCommas
							, bNextLeadingStartsWithLineTerminator
						)
					;
					bWroteTrailing = true;
				}
			}
			if (!bWroteTrailing && _pPrettySeparator)
			{
				if (iChild)
				{
					if (!bNextLeadingSet)
					{
						if (!(bNextCommaInLeading || bUseLeadingCommaForAutomaticSeparators))
							o_String += ",";
						o_String += "\n";
					}
					else if (!(bNextCommaInLeading || bUseLeadingCommaForAutomaticSeparators))
						o_String += ",";
				}
				else
					o_String += "\n";
			}
			else if (!bWroteTrailing && iChild)
			{
				if (!(bNextCommaInLeading || bUseLeadingCommaForAutomaticSeparators))
					o_String += ",";
			}
			bFirstChild = false;
		}

		bool bLastTrailing = false;
		if constexpr (tf_CJson::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
		{
			auto iLast = _Value.f_OrderedIterator();
			while (iLast)
			{
				auto &Last = *iLast;
				++iLast;
				if (!iLast)
					bLastTrailing = Last.f_Value().f_Trivia().f_IsTrailingSet();
			}
		}
		if (_pPrettySeparator && !bLastTrailing)
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

		bool bFirstLeading = false;
		if constexpr (tf_CJson::CData::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
			bFirstLeading = (*iChild).f_Trivia().f_IsLeadingSet();

		if (_pPrettySeparator && !bFirstLeading)
			o_String += "[\n";
		else
			o_String += "[";
		bool bUseLeadingCommaForAutomaticSeparators = false;
		if constexpr (tf_CJson::CData::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
		{
			bool bFirstChild = true;
			for (auto iStyleChild = _Value.f_GetIterator(); iStyleChild; ++iStyleChild)
			{
				if
					(
						!bFirstChild
						&& ((*iStyleChild).f_Trivia().f_HasLeadingComma() || fg_FindTopLevelCommaInTrailing<tf_CParseContext>((*iStyleChild).f_Trivia().f_Leading()) >= 0)
					)
				{
					bUseLeadingCommaForAutomaticSeparators = true;
					break;
				}
				bFirstChild = false;
			}
		}

		bool bFirstChild = true;
		while (iChild)
		{
			auto &Child = *iChild;
			++iChild;
			bool bLast = !iChild;
			bool bChildCommaInLeading = false;
			bool bNextLeadingSet = false;
			bool bNextCommaInLeading = false;
			bool bNextLeadingStartsWithLineTerminator = false;
			if constexpr (tf_CJson::CData::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
			{
				bChildCommaInLeading = fg_FindTopLevelCommaInTrailing<tf_CParseContext>(Child.f_Trivia().f_Leading()) >= 0;
				if (iChild)
				{
					bNextLeadingSet = (*iChild).f_Trivia().f_IsLeadingSet();
					bNextCommaInLeading = fg_FindTopLevelCommaInTrailing<tf_CParseContext>((*iChild).f_Trivia().f_Leading()) >= 0;
					bNextLeadingStartsWithLineTerminator = bNextLeadingSet && fg_JsonTriviaStartsWithLineTerminator<tf_CParseContext>((*iChild).f_Trivia().f_Leading());
				}
			}
			bool bWroteLeading = false;
			if constexpr (tf_CJson::CData::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
			{
				if (Child.f_Trivia().f_IsLeadingSet())
				{
					fg_AppendJsonTrivia<tf_CParseContext>(o_String, Child.f_Trivia().f_Leading(), false);
					bWroteLeading = true;
				}
			}
			if (_pPrettySeparator && !bWroteLeading)
			{
				fg_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);
			}
			if (bUseLeadingCommaForAutomaticSeparators && !bFirstChild && !bChildCommaInLeading)
			{
				o_String += ",";
				if (_pPrettySeparator)
					o_String += " ";
			}

			fg_GenerateJsonValue<tf_CParseContext>(o_String, Child, _Depth + 1, _pPrettySeparator, _Flags);

			bool bWroteTrailing = false;
			if constexpr (tf_CJson::CData::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
			{
				if (Child.f_Trivia().f_IsTrailingSet())
				{
					fg_AppendJsonTrailing<tf_CParseContext>
						(
							o_String
							, Child.f_Trivia().f_Trailing()
							, Child.f_Trivia().f_HasTrailingComma()
							, iChild && !(bNextCommaInLeading || bUseLeadingCommaForAutomaticSeparators)
							, bLast
							, tf_CParseContext::mc_bAllowTrailingCommas
							, bNextLeadingStartsWithLineTerminator
						)
					;
					bWroteTrailing = true;
				}
			}
			if (!bWroteTrailing && _pPrettySeparator)
			{
				if (iChild)
				{
					if (!bNextLeadingSet)
					{
						if (!(bNextCommaInLeading || bUseLeadingCommaForAutomaticSeparators))
							o_String += ",";
						o_String += "\n";
					}
					else if (!(bNextCommaInLeading || bUseLeadingCommaForAutomaticSeparators))
						o_String += ",";
				}
				else
					o_String += "\n";
			}
			else if (!bWroteTrailing && iChild)
			{
				if (!(bNextCommaInLeading || bUseLeadingCommaForAutomaticSeparators))
					o_String += ",";
			}
			bFirstChild = false;
		}

		bool bLastTrailing = false;
		if constexpr (tf_CJson::CData::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
		{
			auto iLast = _Value.f_GetIterator();
			while (iLast)
			{
				auto &Last = *iLast;
				++iLast;
				if (!iLast)
					bLastTrailing = Last.f_Trivia().f_IsTrailingSet();
			}
		}
		if (_pPrettySeparator && !bLastTrailing)
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

		if constexpr (tf_CJson::mc_bPreserveComments && tf_CParseContext::mc_bAllowComments)
		{
			if (JsonValue.f_IsObject() && JsonValue.f_Object().f_IsEmpty() && !JsonValue.f_Trivia().f_Interior().f_IsEmpty())
			{
				o_String += "{";
				fg_AppendJsonTrivia<tf_CParseContext>(o_String, JsonValue.f_Trivia().f_Interior(), false);
				o_String += "}";
				return;
			}
			if (JsonValue.f_IsArray() && JsonValue.f_Array().f_IsEmpty() && !JsonValue.f_Trivia().f_Interior().f_IsEmpty())
			{
				o_String += "[";
				fg_AppendJsonTrivia<tf_CParseContext>(o_String, JsonValue.f_Trivia().f_Interior(), false);
				o_String += "]";
				return;
			}
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
				if constexpr (tf_CParseContext::mc_bAllowSignAndSpecial)
				{
					if (Float.f_IsInfinity())
					{
						if (Float.f_GetSign() < 0)
							o_String += "-Infinity";
						else
							o_String += "Infinity";
						break;
					}
					if (Float.f_IsNan())
					{
						if (Float.f_GetSign() < 0)
							o_String += "-NaN";
						else
							o_String += "NaN";
						break;
					}
				}
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
	template <typename t_CParseContext>
	NStr::CStr TCJsonValue<t_CParent>::f_ToString(ch8 const * _pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		using namespace NStr;

		CStr Return;
		{
			CStr::CAppender StringAppender(Return);

			if constexpr (CValue::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
				NJson::fg_AppendJsonTrivia<t_CParseContext>(StringAppender, this->f_Trivia().f_Leading(), false);

			NJson::fg_GenerateJsonValue<t_CParseContext>(StringAppender, *this, 0, _pPrettySeparator, _Flags);

			bool bWroteRootTrailing = false;
			if constexpr (CValue::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
			{
				if (this->f_Trivia().f_IsTrailingSet())
				{
					NJson::fg_AppendJsonTrivia<t_CParseContext>(StringAppender, this->f_Trivia().f_Trailing(), true);
					bWroteRootTrailing = true;
				}
			}

			if
				(
					_pPrettySeparator
					&& !(_Flags & EJsonDialectFlag_TrimWhitespace)
					&& !bWroteRootTrailing
					&& !(CValue::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
				)
				StringAppender += "\n";
		}
		return Return;
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_ToString(ch8 const * _pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		return f_ToString<NJson::CParseContext>(_pPrettySeparator, _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringJsonC(ch8 const * _pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		if constexpr (CValue::mc_bPreserveComments)
			return f_ToString<NJson::CJsonCRecordingParseContext>(_pPrettySeparator, _Flags);
		else
			return f_ToString<NJson::CJsonCParseContext>(_pPrettySeparator, _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringJson5(ch8 const * _pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		if constexpr (CValue::mc_bPreserveComments)
			return f_ToString<NJson::CJson5RecordingParseContext>(_pPrettySeparator, _Flags);
		else
			return f_ToString<NJson::CJson5ParseContext>(_pPrettySeparator, _Flags);
	}

	template <typename t_CParent>
	template <typename t_CParseContext>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		return NPrivate::fg_JsonGenerateColored<t_CParseContext>(*this, _pPrettySeparator, _AnsiFlags, _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		return NPrivate::fg_JsonGenerateColored(*this, _pPrettySeparator, _AnsiFlags, _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringColoredJsonC(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		if constexpr (CValue::mc_bPreserveComments)
			return NPrivate::fg_JsonGenerateColored<NJson::CJsonCRecordingParseContext>(*this, _pPrettySeparator, _AnsiFlags, _Flags);
		else
			return NPrivate::fg_JsonGenerateColored<NJson::CJsonCParseContext>(*this, _pPrettySeparator, _AnsiFlags, _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		if constexpr (CValue::mc_bPreserveComments)
			return NPrivate::fg_JsonGenerateColored<NJson::CJson5RecordingParseContext>(*this, _pPrettySeparator, _AnsiFlags, _Flags);
		else
			return NPrivate::fg_JsonGenerateColored<NJson::CJson5ParseContext>(*this, _pPrettySeparator, _AnsiFlags, _Flags);
	}
}
