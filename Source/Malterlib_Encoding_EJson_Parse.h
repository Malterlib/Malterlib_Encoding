// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_EJson.h"
#include "Malterlib_Encoding_Json_Parse.h"
#include "Malterlib_Encoding_Json_Generate.h"

namespace NMib::NEncoding::NPrivate
{
	struct CEJsonParseContext : public NJson::CParseContext
	{
		using CJsonContext = NJson::CParseContext;

		static constexpr bool mc_bCustomParse = true;
		static constexpr bool mc_bCustomGenerate = true;

		NContainer::TCVector<umint> m_InEscapeParseDepth;

		template <typename tf_CParseContext, typename tf_CJson, typename tf_CStr>
		static bool fs_GenerateValue(tf_CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags)
		{
			switch (_Value.f_EType())
			{
			case EEJsonType_Date:
				{
					typename tf_CJson::CJsonType TempObject;
					auto &Date = _Value.f_Date();
					auto &DateValue = TempObject[CEJsonConstStrings::mc_Date];
					if (!Date.f_IsValid())
						DateValue = nullptr;
					else
						DateValue = NTime::CTimeConvert(Date).f_UnixMilliseconds();

					if constexpr (tf_CParseContext::mc_bAllowComments && tf_CJson::mc_bPreserveComments && tf_CJson::CJsonType::mc_bPreserveComments)
						fsp_SetGeneratedSemanticValueTrivia<tf_CParseContext>(DateValue, _Value);

					NJson::fg_GenerateJsonObject<typename tf_CParseContext::CJsonContext>(o_String, TempObject.f_Object(), _Depth, _pPrettySeparator, _Flags);
					return true;
				}
			case EEJsonType_Binary:
				{
					typename tf_CJson::CJsonType TempObject;
					auto &BinaryValue = TempObject[CEJsonConstStrings::mc_Binary];
					BinaryValue = NEncoding::fg_Base64Encode(_Value.f_Binary());

					if constexpr (tf_CParseContext::mc_bAllowComments && tf_CJson::mc_bPreserveComments && tf_CJson::CJsonType::mc_bPreserveComments)
						fsp_SetGeneratedSemanticValueTrivia<tf_CParseContext>(BinaryValue, _Value);

					NJson::fg_GenerateJsonObject<typename tf_CParseContext::CJsonContext>(o_String, TempObject.f_Object(), _Depth, _pPrettySeparator, _Flags);
					return true;
				}
			case EEJsonType_UserType:
				{
					typename tf_CJson::CJsonType TempObject;

					auto &UserType = _Value.f_UserType();
					TempObject[CEJsonConstStrings::mc_Type] = UserType.m_Type;
					auto &UserValue = TempObject[CEJsonConstStrings::mc_Value];
					UserValue = UserType.m_Value;

					if constexpr (tf_CParseContext::mc_bAllowComments && tf_CJson::mc_bPreserveComments && tf_CJson::CJsonType::mc_bPreserveComments)
						fsp_SetGeneratedSemanticValueTrivia<tf_CParseContext>(UserValue, _Value);

					NJson::fg_GenerateJsonObject<typename tf_CParseContext::CJsonContext>(o_String, TempObject.f_Object(), _Depth, _pPrettySeparator, _Flags);
					return true;
				}
			case EEJsonType_Object:
				{
					if (_Flags & EJsonDialectFlag_Internal_InEscapeGenerate)
						return false;

					auto iMember = _Value.f_Object().f_OrderedIterator();
					if (!iMember)
						return false;

					auto &Member = *iMember;
					++iMember;
					auto &Name = Member.f_Name();

					if (!Name.f_StartsWith("$"))
						return false;

					if (!iMember)
					{
						if (!(Name == CEJsonConstStrings::mc_Escape || Name == CEJsonConstStrings::mc_Date || Name == CEJsonConstStrings::mc_Binary))
							return false;
					}
					else
					{
						if
						(
							(Name == CEJsonConstStrings::mc_Type && iMember->f_Name() == CEJsonConstStrings::mc_Value)
							|| (Name == CEJsonConstStrings::mc_Value && iMember->f_Name() == CEJsonConstStrings::mc_Type)
						)
						{
							auto iNext = iMember;
							++iNext;
							if (iNext)
								return false;
						}
						else
							return false;
					}

					if (_pPrettySeparator)
					{
						o_String += "{\n";
						NJson::fg_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);
					}
					else
						o_String += "{";

					tf_CParseContext::template fs_GenerateKeyString<tf_CParseContext>(o_String, CEJsonConstStrings::mc_Escape);

					if (_pPrettySeparator)
						o_String += ": ";
					else
						o_String += ":";

					NJson::fg_GenerateJsonValue<tf_CParseContext>(o_String, _Value, _Depth + 1, _pPrettySeparator, _Flags | EJsonDialectFlag_Internal_InEscapeGenerate);

					if (_pPrettySeparator)
					{
						o_String += "\n";
						NJson::fg_AddPrefix(o_String, _Depth, _pPrettySeparator);
					}
					o_String += "}";

					return true;
				}
			default:
				break;
			}
			return false;
		}

		template <typename tf_CParseContext, typename tf_CJson, typename tf_CGenerator>
		static bool fs_GenerateColoredValue
			(
				tf_CGenerator &_Generator
				, NStr::CStr &o_String
				, tf_CJson const &_Value
				, umint _Depth
				, ch8 const *_pPrettySeparator
				, EJsonDialectFlag _Flags
				, tf_CParseContext &_Context
			)
		{
			switch (_Value.f_EType())
			{
			case EEJsonType_Date:
				{
					typename tf_CJson::CJsonType TempObject;
					auto &Date = _Value.f_Date();
					auto &DateValue = TempObject[CEJsonConstStrings::mc_Date];
					if (!Date.f_IsValid())
						DateValue = nullptr;
					else
						DateValue = NTime::CTimeConvert(Date).f_UnixMilliseconds();

					if constexpr (tf_CParseContext::mc_bAllowComments && tf_CJson::mc_bPreserveComments && tf_CJson::CJsonType::mc_bPreserveComments)
						fsp_SetGeneratedSemanticValueTrivia<tf_CParseContext>(DateValue, _Value);

					TCJsonColorGenerator<typename tf_CParseContext::CJsonContext> JsonGenerator;
					JsonGenerator.m_Flags = _Flags;
					JsonGenerator.m_AnsiFlags = _Generator.m_AnsiFlags;
					JsonGenerator.m_Context.m_Flags = _Context.m_Flags;
					JsonGenerator.f_GenerateJsonObject(o_String, TempObject.f_Object(), _Depth, _pPrettySeparator);
					return true;
				}
			case EEJsonType_Binary:
				{
					typename tf_CJson::CJsonType TempObject;
					auto &BinaryValue = TempObject[CEJsonConstStrings::mc_Binary];
					BinaryValue = NEncoding::fg_Base64Encode(_Value.f_Binary());

					if constexpr (tf_CParseContext::mc_bAllowComments && tf_CJson::mc_bPreserveComments && tf_CJson::CJsonType::mc_bPreserveComments)
						fsp_SetGeneratedSemanticValueTrivia<tf_CParseContext>(BinaryValue, _Value);

					TCJsonColorGenerator<typename tf_CParseContext::CJsonContext> JsonGenerator;
					JsonGenerator.m_Flags = _Flags;
					JsonGenerator.m_AnsiFlags = _Generator.m_AnsiFlags;
					JsonGenerator.m_Context.m_Flags = _Context.m_Flags;
					JsonGenerator.f_GenerateJsonObject(o_String, TempObject.f_Object(), _Depth, _pPrettySeparator);
					return true;
				}
			case EEJsonType_UserType:
				{
					typename tf_CJson::CJsonType TempObject;

					auto &UserType = _Value.f_UserType();
					TempObject[CEJsonConstStrings::mc_Type] = UserType.m_Type;
					auto &UserValue = TempObject[CEJsonConstStrings::mc_Value];
					UserValue = UserType.m_Value;

					if constexpr (tf_CParseContext::mc_bAllowComments && tf_CJson::mc_bPreserveComments && tf_CJson::CJsonType::mc_bPreserveComments)
						fsp_SetGeneratedSemanticValueTrivia<tf_CParseContext>(UserValue, _Value);

					TCJsonColorGenerator<typename tf_CParseContext::CJsonContext> JsonGenerator;
					JsonGenerator.m_Flags = _Flags;
					JsonGenerator.m_AnsiFlags = _Generator.m_AnsiFlags;
					JsonGenerator.m_Context.m_Flags = _Context.m_Flags;
					JsonGenerator.f_GenerateJsonObject(o_String, TempObject.f_Object(), _Depth, _pPrettySeparator);
					return true;
				}
			case EEJsonType_Object:
				{
					if (_Flags & EJsonDialectFlag_Internal_InEscapeGenerate)
						return false;

					auto iMember = _Value.f_Object().f_OrderedIterator();
					if (!iMember)
						return false;

					auto &Member = *iMember;
					++iMember;
					auto &Name = Member.f_Name();

					if (!Name.f_StartsWith("$"))
						return false;

					if (!iMember)
					{
						if (!(Name == CEJsonConstStrings::mc_Escape || Name == CEJsonConstStrings::mc_Date || Name == CEJsonConstStrings::mc_Binary))
							return false;
					}
					else
					{
						if
						(
							(Name == CEJsonConstStrings::mc_Type && iMember->f_Name() == CEJsonConstStrings::mc_Value)
							|| (Name == CEJsonConstStrings::mc_Value && iMember->f_Name() == CEJsonConstStrings::mc_Type)
						)
						{
							auto iNext = iMember;
							++iNext;
							if (iNext)
								return false;
						}
						else
							return false;
					}

					if (_pPrettySeparator)
					{
						o_String += "{\n";
						_Generator.f_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);
					}
					else
						o_String += "{";

					o_String += _Generator.f_GenerateJsonKeyString(CEJsonConstStrings::mc_Escape);

					if (_pPrettySeparator)
						o_String += ": ";
					else
						o_String += ":";

					auto OldFlags = _Generator.m_Flags;
					_Generator.m_Flags |= EJsonDialectFlag_Internal_InEscapeGenerate;
					auto Cleanup = g_OnScopeExit / [&]
						{
							_Generator.m_Flags = OldFlags;
						}
					;
					_Generator.f_GenerateJsonValue(o_String, _Value, _Depth + 1, _pPrettySeparator);

					if (_pPrettySeparator)
					{
						o_String += "\n";
						_Generator.f_AddPrefix(o_String, _Depth, _pPrettySeparator);
					}
					o_String += "}";

					return true;
				}
			default:
				break;
			}
			return false;
		}

		template <typename tf_CParseContext, typename tf_CJson>
		bool f_ParseValue(tf_CJson &o_Value, uch8 const *&o_pParse)
		{
			return false;
		}

		template <typename tf_CParseContext>
		void f_ParseKey(NStr::CStr &o_Key, uch8 const *&o_pParse)
		{
			NJson::CParseContext::f_ParseKey<tf_CParseContext>(o_Key, o_pParse);

			if (o_Key != CEJsonConstStrings::mc_Escape)
				return;

			if (!m_InEscapeParseDepth.f_IsEmpty() && m_InEscapeParseDepth.f_GetLast() == (m_ObjectArrayParseDepth - 1))
				return;

			m_InEscapeParseDepth.f_Insert(m_ObjectArrayParseDepth);
		}

		template <typename tf_CParseContext, typename tf_CJson>
		void f_PreParse(tf_CJson &o_Value, uch8 const *&o_pParse)
		{
		}

		template <typename tf_CParseContext, typename tf_CJson>
		void f_PostParse(tf_CJson &o_Value, uch8 const *&o_pParse)
		{
		}

		template <typename tf_CParseContext, typename tf_CJson>
		void f_ParseAfterValue(tf_CJson &o_Value, uch8 const *&o_pParse)
		{
			if (!o_Value.f_IsObject())
				return;

			auto iMember = o_Value.f_Object().f_OrderedIterator();
			if (!iMember)
				return;

			auto &Member = *iMember;
			++iMember;
			auto &Name = Member.f_Name();
			auto &Value = Member.f_Value();

			if (!iMember)
			{
				if (Name == CEJsonConstStrings::mc_Escape)
				{
					if (m_InEscapeParseDepth.f_IsEmpty())
						return;

					if (m_InEscapeParseDepth.f_GetLast() != (m_ObjectArrayParseDepth + 1))
						return;

					m_InEscapeParseDepth.f_Remove(m_InEscapeParseDepth.f_GetLen() - 1);

					if (Value.f_Type() != EJsonType_Object)
						DMibError("Invalid EJSON: $escape value must be an object");

					TCConditional<tf_CParseContext::mc_bRecordComments, NStr::CStr, CEmpty> ComposedTrivia;
					if constexpr (tf_CParseContext::mc_bRecordComments)
						fsp_AppendEntryCommentTrivia(ComposedTrivia, Member);

					auto ValueTemp = fg_Move(Value);
					tf_CJson SourceValue = fg_Move(o_Value);
					o_Value = tf_CJson();
					o_Value = EJsonType_Object;

					if constexpr (tf_CParseContext::mc_bRecordComments)
						fsp_CopyValueLeadingTrivia(o_Value, SourceValue);

					if constexpr (tf_CParseContext::mc_bRecordComments)
					{
						if (ValueTemp.f_Object().f_IsEmpty() && !ValueTemp.f_Trivia().f_Interior().f_IsEmpty())
							o_Value.f_Trivia().f_SetInterior(ValueTemp.f_Trivia().f_MoveInterior());
					}
					for (auto iMember = ValueTemp.f_Object().f_OrderedIterator(); iMember; ++iMember)
					{
						auto &DestEntry = o_Value.f_Object().f_CreateMemberEntry(iMember->f_Name());
						if constexpr (tf_CParseContext::mc_bRecordComments)
						{
							if (iMember->f_KeyTrivia().f_IsLeadingSet())
								DestEntry.f_KeyTrivia().f_SetLeading(fg_TempCopy(iMember->f_KeyTrivia().f_Leading()), iMember->f_KeyTrivia().f_HasLeadingComma());
							else
								DestEntry.f_KeyTrivia().f_UnsetLeading();
							if (iMember->f_KeyTrivia().f_IsTrailingSet())
								DestEntry.f_KeyTrivia().f_SetTrailing(fg_TempCopy(iMember->f_KeyTrivia().f_Trailing()));
							else
								DestEntry.f_KeyTrivia().f_UnsetTrailing();
						}
						DestEntry.f_Value() = fg_Move(iMember->f_Value());
					}
					if constexpr (tf_CParseContext::mc_bRecordComments)
						fsp_AppendComposedTriviaToLastObjectValue(o_Value, fg_Move(ComposedTrivia));

					return;
				}
				else if (Name == CEJsonConstStrings::mc_Date)
				{
					if (!m_InEscapeParseDepth.f_IsEmpty() && m_InEscapeParseDepth.f_GetLast() == m_ObjectArrayParseDepth)
						return;

					if (Value.f_IsNull())
					{
						if constexpr (tf_CParseContext::mc_bRecordComments)
						{
							tf_CJson Temp{NTime::CTime()};
							NStr::CStr ComposedTrivia;
							fsp_AppendEntryCommentTrivia(ComposedTrivia, Member);
							fsp_CopyValueLeadingTrivia(Temp, o_Value);
							fsp_SetComposedTrivia(Temp, fg_Move(ComposedTrivia));
							o_Value = fg_Move(Temp);
						}
						else
							o_Value = NTime::CTime();
						return;
					}
					if (Value.f_Type() != EJsonType_Integer)
						DMibError("Invalid EJSON: $date value must be an integer");

					{
						if constexpr (tf_CParseContext::mc_bRecordComments)
						{
							tf_CJson Temp(NTime::CTimeConvert::fs_FromUnixMilliseconds(Value.f_Integer()));
							NStr::CStr ComposedTrivia;
							fsp_AppendEntryCommentTrivia(ComposedTrivia, Member);
							fsp_CopyValueLeadingTrivia(Temp, o_Value);
							fsp_SetComposedTrivia(Temp, fg_Move(ComposedTrivia));
							o_Value = fg_Move(Temp);
						}
						else
							o_Value = NTime::CTimeConvert::fs_FromUnixMilliseconds(Value.f_Integer());
					}
					return;
				}
				else if (Name == CEJsonConstStrings::mc_Binary)
				{
					if (!m_InEscapeParseDepth.f_IsEmpty() && m_InEscapeParseDepth.f_GetLast() == m_ObjectArrayParseDepth)
						return;

					if (Value.f_Type() != EJsonType_String)
						DMibError("Invalid EJSON: $binary value must be a string");

					NContainer::CByteVector Binary;
					NEncoding::fg_Base64Decode(Value.f_String(), Binary);
					if constexpr (tf_CParseContext::mc_bRecordComments)
					{
						tf_CJson Temp(fg_Move(Binary));
						NStr::CStr ComposedTrivia;
						fsp_AppendEntryCommentTrivia(ComposedTrivia, Member);
						fsp_CopyValueLeadingTrivia(Temp, o_Value);
						fsp_SetComposedTrivia(Temp, fg_Move(ComposedTrivia));
						o_Value = fg_Move(Temp);
					}
					else
						o_Value = fg_Move(Binary);
					return;
				}
			}
			else
			{
				if (!m_InEscapeParseDepth.f_IsEmpty() && m_InEscapeParseDepth.f_GetLast() == m_ObjectArrayParseDepth)
					return;

				if
					(
						(Name == CEJsonConstStrings::mc_Type && iMember->f_Name() == CEJsonConstStrings::mc_Value)
						|| (Name == CEJsonConstStrings::mc_Value && iMember->f_Name() == CEJsonConstStrings::mc_Type)
					)
				{
					++iMember;
					if (!iMember)
					{
						tf_CJson Temp;
						auto &UserType = Temp.f_UserType();

						TCConditional<tf_CParseContext::mc_bRecordComments, NStr::CStr, CEmpty> ComposedTrivia;
						if constexpr (tf_CParseContext::mc_bRecordComments)
						{
							for (auto iComposeMember = o_Value.f_Object().f_OrderedIterator(); iComposeMember; ++iComposeMember)
								fsp_AppendEntryCommentTrivia(ComposedTrivia, *iComposeMember);
						}

						auto *pType = o_Value.f_GetMember(CEJsonConstStrings::mc_Type);
						auto *pValue = o_Value.f_GetMember(CEJsonConstStrings::mc_Value);
						DMibCheck(pType);
						DMibCheck(pValue);
						if (pType->f_Type() != EJsonType_String)
							DMibError("Invalid EJSON: $type value must be a string");

						UserType.m_Type = fg_Move(pType->f_String());
						UserType.m_Value = fg_Move(*pValue).f_ToJsonNoConvert();

						if constexpr (tf_CParseContext::mc_bRecordComments)
						{
							UserType.m_Value.f_Trivia().f_UnsetLeading();
							UserType.m_Value.f_Trivia().f_UnsetTrailing();
							fsp_CopyValueLeadingTrivia(Temp, o_Value);
							fsp_SetComposedTrivia(Temp, fg_Move(ComposedTrivia));
						}

						o_Value = fg_Move(Temp);
						return;
					}
				}
			}
		}

	private:
		static bool fsp_HasComment(NStr::CStr const &_Trivia)
		{
			return NStr::fg_StrFind(_Trivia, "//") >= 0 || NStr::fg_StrFind(_Trivia, "/*") >= 0;
		}

		static bool fsp_HasLineTerminator(NStr::CStr const &_Trivia)
		{
			return NStr::fg_StrFindChars(_Trivia, "\n\r") >= 0;
		}

		static void fsp_AppendCommentTrivia(NStr::CStr &o_Trivia, NStr::CStr const &_Trivia)
		{
			if (fsp_HasComment(_Trivia))
				o_Trivia += _Trivia;
		}

		template <typename tf_CObjectEntry>
		static void fsp_AppendEntryCommentTrivia(NStr::CStr &o_Trivia, tf_CObjectEntry const &_Entry)
		{
			if (_Entry.f_KeyTrivia().f_IsLeadingSet())
				fsp_AppendCommentTrivia(o_Trivia, _Entry.f_KeyTrivia().f_Leading());

			fsp_AppendCommentTrivia(o_Trivia, _Entry.f_KeyTrivia().f_Trailing());

			auto const &Value = _Entry.f_Value();
			if (Value.f_Trivia().f_IsLeadingSet())
				fsp_AppendCommentTrivia(o_Trivia, Value.f_Trivia().f_Leading());

			fsp_AppendCommentTrivia(o_Trivia, Value.f_Trivia().f_Trailing());
		}

		template <typename tf_CJson>
		static void fsp_CopyValueLeadingTrivia(tf_CJson &o_Dest, tf_CJson const &_Source)
		{
			if (_Source.f_Trivia().f_IsLeadingSet())
				o_Dest.f_Trivia().f_SetLeading(fg_TempCopy(_Source.f_Trivia().f_Leading()), _Source.f_Trivia().f_HasLeadingComma());
			else
				o_Dest.f_Trivia().f_UnsetLeading();
		}

		template <typename tf_CJson>
		static void fsp_SetComposedTrivia(tf_CJson &o_Value, NStr::CStr &&_Trivia)
		{
			if (!_Trivia.f_IsEmpty())
				o_Value.f_Trivia().f_SetInterior(fg_Move(_Trivia));
			else
				o_Value.f_Trivia().f_UnsetInterior();
		}

		template <typename tf_CJson>
		static void fsp_AppendComposedTriviaToLastObjectValue(tf_CJson &o_Value, NStr::CStr &&_Trivia)
		{
			if (_Trivia.f_IsEmpty())
				return;

			auto iLast = o_Value.f_Object().f_OrderedIterator();
			if (!iLast)
			{
				o_Value.f_Trivia().f_SetInterior(fg_Move(_Trivia));
				return;
			}

			while (true)
			{
				auto iNext = iLast;
				++iNext;
				if (!iNext)
					break;
				iLast = iNext;
			}

			auto &LastValue = iLast->f_Value();

			NStr::CStr Trailing = LastValue.f_Trivia().f_Trailing();
			if (fsp_HasComment(Trailing) || fsp_HasLineTerminator(Trailing))
				Trailing += _Trivia;
			else
				Trailing = fg_Move(_Trivia);

			LastValue.f_Trivia().f_SetTrailing(fg_Move(Trailing), LastValue.f_Trivia().f_HasTrailingComma());
		}

		template <typename tf_CParseContext, typename tf_CJson, typename tf_CGeneratedValue>
		static void fsp_SetGeneratedSemanticValueTrivia(tf_CGeneratedValue &o_Value, tf_CJson const &_Source)
		{
			if constexpr (tf_CParseContext::mc_bAllowComments && tf_CJson::mc_bPreserveComments && tf_CGeneratedValue::mc_bPreserveComments)
			{
				if (!_Source.f_Trivia().f_Interior().f_IsEmpty())
					o_Value.f_Trivia().f_SetTrailing(fg_TempCopy(_Source.f_Trivia().f_Interior()), false);
			}
		}
	};

	struct CEJson5ParseContext : public CEJsonParseContext
	{
		using CJsonContext = NJson::CJson5ParseContext;
		static constexpr bool mc_bAllowComments = true;
		static constexpr bool mc_bAllowTrailingCommas = true;
		static constexpr bool mc_bAllowSingleQuote = true;
		static constexpr bool mc_bAllowKeyWithoutQuote = true;
		static constexpr bool mc_bAllowHexNumbers = true;
		static constexpr bool mc_bAllowLeadingDecimal = true;
		static constexpr bool mc_bAllowSignAndSpecial = true;
		static constexpr bool mc_bAllowExtendedEscapes = true;
		static constexpr bool mc_bAllowExtendedWhitespace = true;
	};

	struct CEJsonStrictParseContext : public CEJsonParseContext
	{
		using CJsonContext = NJson::CStrictParseContext;
		static constexpr bool mc_bAllowTrailingCommas = false;
	};

	struct CEJsonCParseContext : public CEJsonParseContext
	{
		using CJsonContext = NJson::CJsonCParseContext;
		static constexpr bool mc_bAllowComments = true;
		static inline constexpr ch8 mc_ConstantEndCharacters[] = ",}]/";
	};

	struct CEJson5RecordingParseContext : public CEJson5ParseContext
	{
		using CJsonContext = NJson::CJson5RecordingParseContext;
		static constexpr bool mc_bRecordComments = true;
	};

	struct CEJsonCRecordingParseContext : public CEJsonCParseContext
	{
		using CJsonContext = NJson::CJsonCRecordingParseContext;
		static constexpr bool mc_bRecordComments = true;
	};
}

namespace NMib::NEncoding
{
	using CEJson5ParseContext = NPrivate::CEJson5ParseContext;
	using CEJsonStrictParseContext = NPrivate::CEJsonStrictParseContext;
	using CEJsonCParseContext = NPrivate::CEJsonCParseContext;
	using CEJsonCRecordingParseContext = NPrivate::CEJsonCRecordingParseContext;
	using CEJson5RecordingParseContext = NPrivate::CEJson5RecordingParseContext;

	template <typename t_CParent>
	template <typename t_CParseContext>
	TCEJsonValue<t_CParent> TCEJsonValue<t_CParent>::fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName, EJsonDialectFlag _Flags)
	{
		using namespace NStr;
		static_assert
			(
				!t_CParseContext::mc_bRecordComments || CValue::mc_bPreserveComments
				, "recording JSON5 comments requires a comment-preserving alias (e.g. CEJsonOrderedWithComments)"
			)
		;
		TCEJsonValue<t_CParent> Output;
		CStr ToParse = _String;

		uch8 const *pParse = reinterpret_cast<uch8 const *>(ToParse.f_GetStr());

		t_CParseContext Context;
		Context.m_pStartParse = pParse;
		Context.m_FileName = _FileName;
		Context.m_Flags = _Flags;

		using CSink = TCConditional<t_CParseContext::mc_bRecordComments, NJson::CCommentSink, NJson::CDiscardCommentSink>;
		CSink Sink;
		Sink.f_Reset();
		NJson::fg_ParseWhiteSpaceAndComments(pParse, Context, Sink);
		if constexpr (t_CParseContext::mc_bRecordComments)
		{
			auto Leading = Sink.f_TakeAndClear();
			Output.f_Trivia().f_SetLeading(fg_Move(Leading.m_Text), Leading.m_bHasComma);
		}

		// Any value is allowed at root
		NJson::fg_ParseJsonValue(Output, pParse, Context);

		Sink.f_Reset();
		NJson::fg_ParseWhiteSpaceAndComments(pParse, Context, Sink);
		if constexpr (t_CParseContext::mc_bRecordComments)
		{
			auto Trailing = Sink.f_TakeAndClear();
			Output.f_Trivia().f_SetTrailing(fg_Move(Trailing.m_Text), Trailing.m_bHasComma);
		}

		if (*pParse)
			NJson::fg_ThrowJsonParseError<t_CParseContext>(Context, "Unexpected character after root value", pParse);

		return fg_Move(Output);
	}

	template <typename t_CParent>
	TCEJsonValue<t_CParent> TCEJsonValue<t_CParent>::fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName, EJsonDialectFlag _Flags)
	{
		return fs_FromString<NPrivate::CEJsonParseContext>(_String, _FileName, _Flags);
	}

	template <typename t_CParent>
	TCEJsonValue<t_CParent> TCEJsonValue<t_CParent>::fs_FromStringStrict(NStr::CStr const &_String, NStr::CStr const &_FileName, EJsonDialectFlag _Flags)
	{
		return fs_FromString<NPrivate::CEJsonStrictParseContext>(_String, _FileName, _Flags);
	}

	template <typename t_CParent>
	TCEJsonValue<t_CParent> TCEJsonValue<t_CParent>::fs_FromStringJsonC(NStr::CStr const &_String, NStr::CStr const &_FileName, EJsonDialectFlag _Flags)
	{
		if constexpr (CValue::mc_bPreserveComments)
			return fs_FromString<NPrivate::CEJsonCRecordingParseContext>(_String, _FileName, _Flags);
		else
			return fs_FromString<NPrivate::CEJsonCParseContext>(_String, _FileName, _Flags);
	}

	template <typename t_CParent>
	TCEJsonValue<t_CParent> TCEJsonValue<t_CParent>::fs_FromStringJson5(NStr::CStr const &_String, NStr::CStr const &_FileName, EJsonDialectFlag _Flags)
	{
		if constexpr (CValue::mc_bPreserveComments)
			return fs_FromString<NPrivate::CEJson5RecordingParseContext>(_String, _FileName, _Flags);
		else
			return fs_FromString<NPrivate::CEJson5ParseContext>(_String, _FileName, _Flags);
	}
}
