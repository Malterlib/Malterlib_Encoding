// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

#include <Mib/CommandLine/AnsiEncoding>
#include <Mib/String/Appender>

namespace NMib::NEncoding
{
	namespace NPrivate
	{
		using namespace NStr;
		using namespace NCommandLine;

		template <typename t_CParseContext>
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

			void f_AddPrefix(NStr::CStr &o_String, umint _Depth, ch8 const *_pPrettySeparator)
			{
				for (umint i = 0; i < _Depth; ++i)
					o_String += _pPrettySeparator;
			}

			void f_AppendJsonTrivia(NStr::CStr &o_String, NStr::CStr const &_Trivia, bool _bNextStartsWithLineTerminator)
			{
				auto const *pTrivia = _Trivia.f_GetStr();
				bool bOpenLineComment = false;

				for (umint i = 0; i < _Trivia.f_GetLen(); )
				{
					if (pTrivia[i] == '/' && i + 1 < _Trivia.f_GetLen() && pTrivia[i + 1] == '/')
					{
						umint iStart = i;
						i += 2;
						while (i < _Trivia.f_GetLen() && !NJson::fg_IsJsonLineTerminator<t_CParseContext>(reinterpret_cast<uch8 const *>(pTrivia + i)))
							++i;

						bOpenLineComment = i == _Trivia.f_GetLen();
						o_String += f_Color(NStr::CStr(pTrivia + iStart, i - iStart), ESyntaxColor::ESyntaxColor_Comment);
						continue;
					}

					if (pTrivia[i] == '/' && i + 1 < _Trivia.f_GetLen() && pTrivia[i + 1] == '*')
					{
						umint iStart = i;
						i += 2;
						while (i + 1 < _Trivia.f_GetLen() && !(pTrivia[i] == '*' && pTrivia[i + 1] == '/'))
							++i;

						bool bClosed = i + 1 < _Trivia.f_GetLen();
						if (bClosed)
							i += 2;

						NStr::CStr Comment(pTrivia + iStart, i - iStart);
						if (!bClosed)
							Comment += "*/";
						o_String += f_Color(Comment, ESyntaxColor::ESyntaxColor_Comment);
						continue;
					}

					o_String.f_AddChar(pTrivia[i]);
					++i;
				}

				if (bOpenLineComment && !_bNextStartsWithLineTerminator)
					o_String += "\n";
			}

			void f_AppendJsonTrailing
				(
					NStr::CStr &o_String
					, NStr::CStr const &_Trailing
					, bool _bHasComma
					, bool _bNeedSeparatorAfter
					, bool _bLast
					, bool _bAllowTrailingCommas
					, bool _bNextStartsWithLineTerminator
				)
			{
				auto iComma = NJson::fg_FindTopLevelCommaInTrailing<t_CParseContext>(_Trailing);
				if (_bLast && !_bAllowTrailingCommas && iComma >= 0)
				{
					NStr::CStr StrippedTrailing(_Trailing.f_GetStr(), iComma);
					StrippedTrailing += NStr::CStr(_Trailing.f_GetStr() + iComma + 1, _Trailing.f_GetLen() - iComma - 1);
					f_AppendJsonTrivia(o_String, StrippedTrailing, _bNextStartsWithLineTerminator);
					return;
				}

				if ((_bNeedSeparatorAfter || (_bLast && _bAllowTrailingCommas && _bHasComma)) && iComma < 0)
					o_String += ',';
				f_AppendJsonTrivia(o_String, _Trailing, _bNextStartsWithLineTerminator);
			}

			template <typename tf_CSourceString>
			CStr f_GenerateJsonString(tf_CSourceString const &_Value)
			{
				CStr String;
				{
					CStr::CAppender StringAppender(String);
					t_CParseContext::template fs_GenerateString<t_CParseContext>(StringAppender, _Value);
				}
				return f_Color(String, ESyntaxColor::ESyntaxColor_String);
			}

			template <typename tf_CSourceString>
			CStr f_GenerateJsonKeyString(tf_CSourceString const &_Key)
			{
				CStr String;
				{
					CStr::CAppender StringAppender(String);
					t_CParseContext::template fs_GenerateKeyString<t_CParseContext>(StringAppender, _Key);
				}
				return f_Color(String, ESyntaxColor::ESyntaxColor_MemberVariable);
			}

			CStr f_GenerateJsonInteger(int64 _Value)
			{
				CStr String;
				{
					CStr::CAppender StringAppender(String);
					using CFormatType = typename TCStringFormatterAll<CStr::CFormat, int64>::CFormatType;
					auto Committed = StringAppender.f_Commit();
					aint CurrentLen = Committed.m_String.f_GetLen();
					CFormatType::fs_AddToStrStatic(Committed.m_String, CurrentLen, typename CFormatType::CType(_Value));
					Committed.m_String.f_SetStrLen(CurrentLen);
				}
				return f_Color(String, ESyntaxColor::ESyntaxColor_Number);
			}

			template <typename tf_CFloat>
			CStr f_GenerateJsonFloat(tf_CFloat const &_Value)
			{
				if constexpr (t_CParseContext::mc_bAllowSignAndSpecial)
				{
					if (_Value.f_IsInfinity())
					{
						if (_Value.f_GetSign() < 0)
							return f_Color("-Infinity", ESyntaxColor::ESyntaxColor_Number);
						return f_Color("Infinity", ESyntaxColor::ESyntaxColor_Number);
					}
					if (_Value.f_IsNan())
					{
						if (_Value.f_GetSign() < 0)
							return f_Color("-NaN", ESyntaxColor::ESyntaxColor_Number);
						return f_Color("NaN", ESyntaxColor::ESyntaxColor_Number);
					}
				}
				if (_Value.f_IsInvalid() && !(m_Flags & EJsonDialectFlag_AllowInvalidFloat))
					return f_Color("null", ESyntaxColor::ESyntaxColor_Constant);

				CStr String;
				{
					CStr::CAppender StringAppender(String);
					auto Committed = StringAppender.f_Commit();
					using CFormatType = typename TCStringFormatterAll<CStr::CFormat, fp64>::CFormatType;
					aint CurrentLen = Committed.m_String.f_GetLen();

					typename CFormatType::COptionsFloat Options;
					Options.m_FloatFormat = CFormatType::COptionsFloat::EFloatFormat_ShortestLowerCase;
					if (m_Flags & EJsonDialectFlag_HighPrecisionFloat)
						Options.m_MinDigits = -2;

					CFormatType::fs_AddToStrStatic(Committed.m_String, CurrentLen, typename CFormatType::CType(_Value), Options);
					Committed.m_String.f_SetStrLen(CurrentLen);
				}
				return f_Color(String, ESyntaxColor::ESyntaxColor_Number);
			}

			template <typename tf_CJson>
			void f_GenerateJsonObject(NStr::CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator)
			{
				auto iChild = _Value.f_OrderedIterator();
				if (!iChild)
				{
					o_String += "{}";
					return;
				}

				bool bFirstLeading = false;
				if constexpr (tf_CJson::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
					bFirstLeading = iChild->f_KeyTrivia().f_IsLeadingSet();

				if (_pPrettySeparator && !bFirstLeading)
					o_String += "{\n";
				else
					o_String += "{";

				bool bUseLeadingCommaForAutomaticSeparators = false;
				if constexpr (tf_CJson::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
				{
					bool bFirstChild = true;
					for (auto iStyleChild = _Value.f_OrderedIterator(); iStyleChild; ++iStyleChild)
					{
						if
						(
							!bFirstChild
							&& (iStyleChild->f_KeyTrivia().f_HasLeadingComma() || NJson::fg_FindTopLevelCommaInTrailing<t_CParseContext>(iStyleChild->f_KeyTrivia().f_Leading()) >= 0)
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
					if constexpr (tf_CJson::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
					{
						bChildCommaInLeading = NJson::fg_FindTopLevelCommaInTrailing<t_CParseContext>(Child.f_KeyTrivia().f_Leading()) >= 0;
						if (iChild)
						{
							bNextLeadingSet = iChild->f_KeyTrivia().f_IsLeadingSet();
							bNextCommaInLeading = NJson::fg_FindTopLevelCommaInTrailing<t_CParseContext>(iChild->f_KeyTrivia().f_Leading()) >= 0;
							bNextLeadingStartsWithLineTerminator = bNextLeadingSet && NJson::fg_JsonTriviaStartsWithLineTerminator<t_CParseContext>(iChild->f_KeyTrivia().f_Leading());
						}
					}

					bool bWroteLeading = false;
					if constexpr (tf_CJson::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
					{
						if (Child.f_KeyTrivia().f_IsLeadingSet())
						{
							f_AppendJsonTrivia(o_String, Child.f_KeyTrivia().f_Leading(), false);
							bWroteLeading = true;
						}
					}
					if (_pPrettySeparator && !bWroteLeading)
						f_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);

					if (bUseLeadingCommaForAutomaticSeparators && !bFirstChild && !bChildCommaInLeading)
					{
						o_String += ",";
						if (_pPrettySeparator)
							o_String += " ";
					}

					o_String += f_GenerateJsonKeyString(Child.f_Name());

					bool bWroteTrailingKey = false;
					if constexpr (tf_CJson::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
					{
						if (Child.f_KeyTrivia().f_IsTrailingSet())
						{
							f_AppendJsonTrivia(o_String, Child.f_KeyTrivia().f_Trailing(), false);
							bWroteTrailingKey = true;
						}
					}
					o_String += ":";

					bool bWroteLeadingValue = false;
					if constexpr (tf_CJson::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
					{
						if (Child.f_Value().f_Trivia().f_IsLeadingSet())
						{
							f_AppendJsonTrivia(o_String, Child.f_Value().f_Trivia().f_Leading(), false);
							bWroteLeadingValue = true;
						}
					}
					if (_pPrettySeparator && !bWroteTrailingKey && !bWroteLeadingValue)
						o_String += " ";

					f_GenerateJsonValue(o_String, Child.f_Value(), _Depth + 1, _pPrettySeparator);

					bool bWroteTrailing = false;
					if constexpr (tf_CJson::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
					{
						if (Child.f_Value().f_Trivia().f_IsTrailingSet())
						{
							f_AppendJsonTrailing
								(
									o_String
									, Child.f_Value().f_Trivia().f_Trailing()
									, Child.f_Value().f_Trivia().f_HasTrailingComma()
									, iChild && !(bNextCommaInLeading || bUseLeadingCommaForAutomaticSeparators)
									, bLast
									, t_CParseContext::mc_bAllowTrailingCommas
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
				if constexpr (tf_CJson::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
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
					f_AddPrefix(o_String, _Depth, _pPrettySeparator);
				o_String += "}";
			}

			template <typename tf_CJson>
			void f_GenerateJsonArray(NStr::CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator)
			{
				auto iChild = _Value.f_GetIterator();
				if (!iChild)
				{
					o_String += "[]";
					return;
				}

				bool bFirstLeading = false;
				if constexpr (tf_CJson::CData::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
					bFirstLeading = (*iChild).f_Trivia().f_IsLeadingSet();

				if (_pPrettySeparator && !bFirstLeading)
					o_String += "[\n";
				else
					o_String += "[";

				bool bUseLeadingCommaForAutomaticSeparators = false;
				if constexpr (tf_CJson::CData::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
				{
					bool bFirstChild = true;
					for (auto iStyleChild = _Value.f_GetIterator(); iStyleChild; ++iStyleChild)
					{
						if
						(
							!bFirstChild
							&& ((*iStyleChild).f_Trivia().f_HasLeadingComma() || NJson::fg_FindTopLevelCommaInTrailing<t_CParseContext>((*iStyleChild).f_Trivia().f_Leading()) >= 0)
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
					if constexpr (tf_CJson::CData::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
					{
						bChildCommaInLeading = NJson::fg_FindTopLevelCommaInTrailing<t_CParseContext>(Child.f_Trivia().f_Leading()) >= 0;
						if (iChild)
						{
							bNextLeadingSet = (*iChild).f_Trivia().f_IsLeadingSet();
							bNextCommaInLeading = NJson::fg_FindTopLevelCommaInTrailing<t_CParseContext>((*iChild).f_Trivia().f_Leading()) >= 0;
							bNextLeadingStartsWithLineTerminator = bNextLeadingSet && NJson::fg_JsonTriviaStartsWithLineTerminator<t_CParseContext>((*iChild).f_Trivia().f_Leading());
						}
					}

					bool bWroteLeading = false;
					if constexpr (tf_CJson::CData::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
					{
						if (Child.f_Trivia().f_IsLeadingSet())
						{
							f_AppendJsonTrivia(o_String, Child.f_Trivia().f_Leading(), false);
							bWroteLeading = true;
						}
					}
					if (_pPrettySeparator && !bWroteLeading)
						f_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);

					if (bUseLeadingCommaForAutomaticSeparators && !bFirstChild && !bChildCommaInLeading)
					{
						o_String += ",";
						if (_pPrettySeparator)
							o_String += " ";
					}

					f_GenerateJsonValue(o_String, Child, _Depth + 1, _pPrettySeparator);

					bool bWroteTrailing = false;
					if constexpr (tf_CJson::CData::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
					{
						if (Child.f_Trivia().f_IsTrailingSet())
						{
							f_AppendJsonTrailing
								(
									o_String
									, Child.f_Trivia().f_Trailing()
									, Child.f_Trivia().f_HasTrailingComma()
									, iChild && !(bNextCommaInLeading || bUseLeadingCommaForAutomaticSeparators)
									, bLast
									, t_CParseContext::mc_bAllowTrailingCommas
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
				if constexpr (tf_CJson::CData::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
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
					f_AddPrefix(o_String, _Depth, _pPrettySeparator);
				o_String += "]";
			}

			template <typename tf_CJson>
			void f_GenerateJsonValue(NStr::CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator)
			{
				auto &JsonValue = _Value;

				if constexpr (t_CParseContext::mc_bCustomGenerate)
				{
					if constexpr
					(
						requires
						{
							t_CParseContext::template fs_GenerateColoredValue<t_CParseContext>(*this, o_String, _Value, _Depth, _pPrettySeparator, m_Flags, m_Context);
						}
					)
					{
						if (t_CParseContext::template fs_GenerateColoredValue<t_CParseContext>(*this, o_String, _Value, _Depth, _pPrettySeparator, m_Flags, m_Context))
							return;
					}
				}

				if constexpr (tf_CJson::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
				{
					if (JsonValue.f_IsObject() && JsonValue.f_Object().f_IsEmpty() && !JsonValue.f_Trivia().f_Interior().f_IsEmpty())
					{
						o_String += "{";
						f_AppendJsonTrivia(o_String, JsonValue.f_Trivia().f_Interior(), false);
						o_String += "}";
						return;
					}

					if (JsonValue.f_IsArray() && JsonValue.f_Array().f_IsEmpty() && !JsonValue.f_Trivia().f_Interior().f_IsEmpty())
					{
						o_String += "[";
						f_AppendJsonTrivia(o_String, JsonValue.f_Trivia().f_Interior(), false);
						o_String += "]";
						return;
					}
				}

				switch (JsonValue.f_Type())
				{
				case EJsonType_String:
					o_String += f_GenerateJsonString(JsonValue.f_String());
					break;
				case EJsonType_Integer:
					o_String += f_GenerateJsonInteger(JsonValue.f_Integer());
					break;
				case EJsonType_Float:
					o_String += f_GenerateJsonFloat(JsonValue.f_Float());
					break;
				case EJsonType_Object:
					{
						auto OldFlags = m_Flags;
						m_Flags &= EJsonDialectFlag_All;
						auto Cleanup = g_OnScopeExit / [&]
							{
								m_Flags = OldFlags;
							}
						;
						f_GenerateJsonObject(o_String, _Value.f_Object(), _Depth, _pPrettySeparator);
					}
					break;
				case EJsonType_Array:
					{
						auto OldFlags = m_Flags;
						m_Flags &= EJsonDialectFlag_All;
						auto Cleanup = g_OnScopeExit / [&]
							{
								m_Flags = OldFlags;
							}
						;
						f_GenerateJsonArray(o_String, _Value.f_Array(), _Depth, _pPrettySeparator);
					}
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
						o_String += f_Color("undefined", ESyntaxColor::ESyntaxColor_Constant);
						break;
					}
					[[fallthrough]];
				default:
					DMibError("Invalid JSON type in value node");
				break;
				}
			}

			template <typename tf_CJson>
			NStr::CStr f_ToString(tf_CJson const &_Json, ch8 const *_pPrettySeparator)
			{
				CStr Return;

				if constexpr (tf_CJson::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
					f_AppendJsonTrivia(Return, _Json.f_Trivia().f_Leading(), false);

				f_GenerateJsonValue(Return, _Json, 0, _pPrettySeparator);

				bool bWroteRootTrailing = false;
				if constexpr (tf_CJson::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
				{
					if (_Json.f_Trivia().f_IsTrailingSet())
					{
						f_AppendJsonTrivia(Return, _Json.f_Trivia().f_Trailing(), true);
						bWroteRootTrailing = true;
					}
				}

				if
					(
						_pPrettySeparator
						&& !(m_Flags & EJsonDialectFlag_TrimWhitespace)
						&& !bWroteRootTrailing
						&& !(tf_CJson::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
					)
					Return += "\n";

				return Return;
			}

			t_CParseContext m_Context;
			EJsonDialectFlag m_Flags;
			NCommandLine::EAnsiEncodingFlag m_AnsiFlags;
		};

		template <typename tf_CParseContext, typename tf_CJson>
		NStr::CStr fg_JsonGenerateColored(tf_CJson const &_Json, ch8 const *_pPrettySeparator, NCommandLine::EAnsiEncodingFlag _AnsiFlags, EJsonDialectFlag _Flags)
		{
			TCJsonColorGenerator<tf_CParseContext> Generator;
			Generator.m_Flags = _Flags;
			Generator.m_AnsiFlags = _AnsiFlags;
			Generator.m_Context.m_Flags = _Flags;

			return Generator.f_ToString(_Json, _pPrettySeparator);
		}

		template <typename tf_CJson>
		NStr::CStr fg_JsonGenerateColored(tf_CJson const &_Json, ch8 const *_pPrettySeparator, NCommandLine::EAnsiEncodingFlag _AnsiFlags, EJsonDialectFlag _Flags)
		{
			return fg_JsonGenerateColored<NJson::CParseContext>(_Json, _pPrettySeparator, _AnsiFlags, _Flags);
		}
	}
}
