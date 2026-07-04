// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding::NPrivate
{
	// Helpers translating between JSONC comment trivia (raw whitespace/comment text spans using
	// // and /* */ markers) and YAML comment metadata ('#'-prefixed lines terminated by '\n',
	// blank lines stored as bare '\n', line comments stored as " # ..." without terminator).

	inline void fg_JsonCommentAppendIndent(NStr::CStr::CAppender &o_Trivia, umint _Depth)
	{
		for (umint i = 0; i < _Depth; ++i)
			o_Trivia += '\t';
	}

	inline void fg_JsonTriviaAppendYamlComments(NStr::CStr::CAppender &o_Comment, ch8 const *_pParse, ch8 const *_pEnd)
	{
		auto const *pParse = _pParse;
		auto const *pEnd = _pEnd;

		bool bFirstLine = true;
		bool bLineHadComment = false;

		while (pParse < pEnd)
		{
			if (pParse[0] == '/' && pParse + 1 < pEnd && pParse[1] == '/')
			{
				pParse += 2;

				auto const *pPayload = pParse;
				while (pParse < pEnd && *pParse != '\n' && *pParse != '\r')
					++pParse;

				o_Comment += '#';
				o_Comment.f_AddString(pPayload, pParse - pPayload);
				o_Comment += '\n';
				bLineHadComment = true;

				continue;
			}

			if (pParse[0] == '/' && pParse + 1 < pEnd && pParse[1] == '*')
			{
				pParse += 2;

				auto const *pPayload = pParse;
				while (pParse + 1 < pEnd && !(pParse[0] == '*' && pParse[1] == '/'))
					++pParse;

				auto const *pPayloadEnd = pParse + 1 < pEnd ? pParse : pEnd;
				pParse = pParse + 1 < pEnd ? pParse + 2 : pEnd;

				while (pPayload < pPayloadEnd)
				{
					auto const *pLine = pPayload;
					while (pPayload < pPayloadEnd && *pPayload != '\n' && *pPayload != '\r')
						++pPayload;

					auto const *pLineEnd = pPayload;
					while (pLine < pLineEnd && (*pLine == ' ' || *pLine == '\t'))
						++pLine;
					while (pLineEnd > pLine && (pLineEnd[-1] == ' ' || pLineEnd[-1] == '\t' || pLineEnd[-1] == '\r'))
						--pLineEnd;

					o_Comment += '#';
					if (pLine < pLineEnd)
					{
						o_Comment += ' ';
						o_Comment.f_AddString(pLine, pLineEnd - pLine);
					}
					o_Comment += '\n';

					if (pPayload < pPayloadEnd && *pPayload == '\r' && pPayload + 1 < pPayloadEnd && pPayload[1] == '\n')
						++pPayload;
					if (pPayload < pPayloadEnd)
						++pPayload;
				}

				bLineHadComment = true;

				continue;
			}

			if (*pParse == '\n' || *pParse == '\r')
			{
				if (!bFirstLine && !bLineHadComment && o_Comment.f_GetStrLen() > 0)
					o_Comment += '\n';

				if (pParse[0] == '\r' && pParse + 1 < pEnd && pParse[1] == '\n')
					++pParse;
				++pParse;

				bFirstLine = false;
				bLineHadComment = false;

				continue;
			}

			++pParse;
		}
	}

	inline void fg_JsonTriviaAppendYamlComments(NStr::CStr::CAppender &o_Comment, NStr::CStr const &_Trivia)
	{
		fg_JsonTriviaAppendYamlComments(o_Comment, _Trivia.f_GetStr(), _Trivia.f_GetStr() + _Trivia.f_GetLen());
	}

	inline umint fg_JsonTriviaFindSameLineEnd(NStr::CStr const &_Trivia)
	{
		auto const *pParse = _Trivia.f_GetStr();
		auto const *pStart = pParse;
		auto const *pEnd = pParse + _Trivia.f_GetLen();

		while (pParse < pEnd)
		{
			if (pParse[0] == '/' && pParse + 1 < pEnd && pParse[1] == '*')
			{
				pParse += 2;
				while (pParse + 1 < pEnd && !(pParse[0] == '*' && pParse[1] == '/'))
					++pParse;
				pParse = pParse + 1 < pEnd ? pParse + 2 : pEnd;
				continue;
			}

			if (*pParse == '\n' || *pParse == '\r')
				return pParse - pStart;

			++pParse;
		}

		return _Trivia.f_GetLen();
	}

	inline void fg_JsonTriviaAppendYamlLineComment(NStr::CStr::CAppender &o_LineComment, ch8 const *_pParse, ch8 const *_pEnd)
	{
		auto const *pParse = _pParse;
		auto const *pEnd = _pEnd;

		while (pParse < pEnd)
		{
			auto const *pPayload = pParse;
			auto const *pPayloadEnd = pParse;

			if (pParse[0] == '/' && pParse + 1 < pEnd && pParse[1] == '/')
			{
				pParse += 2;
				pPayload = pParse;
				while (pParse < pEnd && *pParse != '\n' && *pParse != '\r')
					++pParse;
				pPayloadEnd = pParse;
			}
			else if (pParse[0] == '/' && pParse + 1 < pEnd && pParse[1] == '*')
			{
				pParse += 2;
				pPayload = pParse;
				while (pParse + 1 < pEnd && !(pParse[0] == '*' && pParse[1] == '/'))
					++pParse;
				pPayloadEnd = pParse + 1 < pEnd ? pParse : pEnd;
				pParse = pParse + 1 < pEnd ? pParse + 2 : pEnd;
			}
			else
			{
				++pParse;
				continue;
			}

			while (pPayloadEnd > pPayload && (pPayloadEnd[-1] == ' ' || pPayloadEnd[-1] == '\t' || pPayloadEnd[-1] == '\r'))
				--pPayloadEnd;

			if (o_LineComment.f_GetStrLen() == 0)
			{
				o_LineComment += " #";
				o_LineComment.f_AddString(pPayload, pPayloadEnd - pPayload);
			}
			else
			{
				while (pPayload < pPayloadEnd && (*pPayload == ' ' || *pPayload == '\t'))
					++pPayload;

				o_LineComment += ' ';
				o_LineComment.f_AddString(pPayload, pPayloadEnd - pPayload);
			}
		}
	}

	inline void fg_YamlLineCommentAppendCommentLine(NStr::CStr::CAppender &o_Comment, NStr::CStr const &_LineComment)
	{
		if (_LineComment.f_IsEmpty())
			return;

		auto const *pParse = _LineComment.f_GetStr();
		auto const *pEnd = pParse + _LineComment.f_GetLen();
		while (pParse < pEnd && (*pParse == ' ' || *pParse == '\t'))
			++pParse;

		if (pParse >= pEnd)
			return;

		o_Comment.f_AddString(pParse, pEnd - pParse);
		o_Comment += '\n';
	}

	inline void fg_YamlCommentAppendJsonLeadingTrivia(NStr::CStr::CAppender &o_Trivia, NStr::CStr const &_Comment, umint _Depth, bool _bRoot)
	{
		auto const *pParse = _Comment.f_GetStr();
		auto const *pEnd = pParse + _Comment.f_GetLen();

		bool bFirst = true;
		while (pParse < pEnd)
		{
			auto const *pLine = pParse;
			while (pParse < pEnd && *pParse != '\n')
				++pParse;

			auto const *pLineEnd = pParse;
			if (pParse < pEnd)
				++pParse;

			while (pLine < pLineEnd && (*pLine == ' ' || *pLine == '\t'))
				++pLine;
			while (pLineEnd > pLine && pLineEnd[-1] == '\r')
				--pLineEnd;

			if (pLine >= pLineEnd)
			{
				o_Trivia += '\n';
				bFirst = false;
				continue;
			}

			if (!_bRoot || !bFirst)
			{
				o_Trivia += '\n';
				fg_JsonCommentAppendIndent(o_Trivia, _Depth);
			}

			o_Trivia += "//";
			if (*pLine == '#')
				++pLine;
			o_Trivia.f_AddString(pLine, pLineEnd - pLine);

			bFirst = false;
		}

		o_Trivia += '\n';
		if (!_bRoot)
			fg_JsonCommentAppendIndent(o_Trivia, _Depth);
	}

	inline void fg_YamlLineCommentAppendJsonComment(NStr::CStr::CAppender &o_Trivia, NStr::CStr const &_LineComment)
	{
		auto const *pParse = _LineComment.f_GetStr();
		auto const *pEnd = pParse + _LineComment.f_GetLen();
		while (pParse < pEnd && (*pParse == ' ' || *pParse == '\t'))
			++pParse;
		if (pParse < pEnd && *pParse == '#')
			++pParse;

		auto const *pPayloadEnd = pEnd;
		while (pPayloadEnd > pParse && (pPayloadEnd[-1] == '\r' || pPayloadEnd[-1] == '\n'))
			--pPayloadEnd;

		o_Trivia += " //";
		o_Trivia.f_AddString(pParse, pPayloadEnd - pParse);
	}

	inline void fg_YamlCommentAppendJsonTrailingLines(NStr::CStr::CAppender &o_Trivia, NStr::CStr const &_Comment, umint _Depth)
	{
		auto const *pParse = _Comment.f_GetStr();
		auto const *pEnd = pParse + _Comment.f_GetLen();

		while (pParse < pEnd)
		{
			auto const *pLine = pParse;
			while (pParse < pEnd && *pParse != '\n')
				++pParse;

			auto const *pLineEnd = pParse;
			if (pParse < pEnd)
				++pParse;

			while (pLine < pLineEnd && (*pLine == ' ' || *pLine == '\t'))
				++pLine;
			while (pLineEnd > pLine && pLineEnd[-1] == '\r')
				--pLineEnd;

			if (pLine >= pLineEnd)
			{
				o_Trivia += '\n';
				continue;
			}

			o_Trivia += '\n';
			fg_JsonCommentAppendIndent(o_Trivia, _Depth);
			o_Trivia += "//";
			if (*pLine == '#')
				++pLine;
			o_Trivia.f_AddString(pLine, pLineEnd - pLine);
		}
	}

	template <typename t_CSrcValue>
	bool fg_YamlCommentValueIsNonEmptyContainer(t_CSrcValue const &_Src)
	{
		if (_Src.f_IsObject())
			return !_Src.f_Object().f_IsEmpty();
		if (_Src.f_IsArray())
			return _Src.f_Array().f_GetLen() > 0;
		return false;
	}

	// Comments are converted in two phases so the value conversion itself can move from the
	// source: first the intact source tree is walked, recording one translated record per value
	// in traversal order, then the records are replayed onto the converted tree in the same
	// order. Empty strings mean the slot is absent.
	struct CJsonConvertedComments
	{
		NStr::CStr m_KeyLeading;
		NStr::CStr m_ValueLeading;
		NStr::CStr m_ValueLine;
		NStr::CStr m_ValueTrailing;
	};

	template <bool t_bDstOrdered, typename t_CSrcValue>
	void fg_RecordJsonCommentsAsYaml(t_CSrcValue const &_Src, NStr::CStr &&_KeyLeading, bool _bSkipValueLeading, NContainer::TCVector<CJsonConvertedComments> &o_Records)
	{
		{
			auto &Record = o_Records.f_Insert();
			Record.m_KeyLeading = fg_Move(_KeyLeading);

			auto SrcTrivia = _Src.f_Trivia();
			if (!_bSkipValueLeading && SrcTrivia.f_IsLeadingSet())
			{
				NStr::CStr::CAppender Appender(Record.m_ValueLeading);
				fg_JsonTriviaAppendYamlComments(Appender, SrcTrivia.f_Leading());
			}

			if (!SrcTrivia.f_Interior().f_IsEmpty() || SrcTrivia.f_IsTrailingSet())
			{
				NStr::CStr::CAppender TrailingAppender(Record.m_ValueTrailing);

				if (!SrcTrivia.f_Interior().f_IsEmpty())
					fg_JsonTriviaAppendYamlComments(TrailingAppender, SrcTrivia.f_Interior());

				if (SrcTrivia.f_IsTrailingSet())
				{
					auto const &TrailingTrivia = SrcTrivia.f_Trailing();
					auto SameLineEnd = fg_JsonTriviaFindSameLineEnd(TrailingTrivia);

					{
						NStr::CStr::CAppender LineAppender(Record.m_ValueLine);
						fg_JsonTriviaAppendYamlLineComment(LineAppender, TrailingTrivia.f_GetStr(), TrailingTrivia.f_GetStr() + SameLineEnd);
					}

					fg_JsonTriviaAppendYamlComments(TrailingAppender, TrailingTrivia.f_GetStr() + SameLineEnd, TrailingTrivia.f_GetStr() + TrailingTrivia.f_GetLen());
				}
			}
		}

		if (_Src.f_IsObject())
		{
			auto const &SrcObject = _Src.f_Object();

			auto fRecordEntries = [&](auto _iSrc)
				{
					while (_iSrc)
					{
						auto const &SrcEntry = *_iSrc;

						// Comments before the key, between the key and ':', and between ':' and the
						// value are all folded into the key leading comment. The YAML generator only
						// shows one leading comment block per entry, so keeping them together makes
						// every one of them survive a full conversion cycle.
						NStr::CStr KeyLeading;
						{
							NStr::CStr::CAppender Appender(KeyLeading);
							if (SrcEntry.f_KeyTrivia().f_IsLeadingSet())
								fg_JsonTriviaAppendYamlComments(Appender, SrcEntry.f_KeyTrivia().f_Leading());
							if (SrcEntry.f_KeyTrivia().f_IsTrailingSet())
								fg_JsonTriviaAppendYamlComments(Appender, SrcEntry.f_KeyTrivia().f_Trailing());
							if (SrcEntry.f_Value().f_Trivia().f_IsLeadingSet())
								fg_JsonTriviaAppendYamlComments(Appender, SrcEntry.f_Value().f_Trivia().f_Leading());
						}

						fg_RecordJsonCommentsAsYaml<t_bDstOrdered>(SrcEntry.f_Value(), fg_Move(KeyLeading), true, o_Records);

						++_iSrc;
					}
				}
			;

			constexpr bool c_bSrcOrdered = NTraits::TCRemoveReferenceAndQualifiers<decltype(SrcObject)>::mc_bOrdered;
			if constexpr (c_bSrcOrdered && !t_bDstOrdered)
				fRecordEntries(SrcObject.f_SortedIterator());
			else
				fRecordEntries(SrcObject.f_OrderedIterator());
		}
		else if (_Src.f_IsArray())
		{
			auto const &SrcArray = _Src.f_Array();
			for (umint i = 0; i < SrcArray.f_GetLen(); ++i)
				fg_RecordJsonCommentsAsYaml<t_bDstOrdered>(SrcArray[i], NStr::CStr(), false, o_Records);
		}

		if constexpr (requires { _Src.f_UserType(); })
		{
			if (_Src.f_IsUserType())
				fg_RecordJsonCommentsAsYaml<t_bDstOrdered>(_Src.f_UserType().m_Value, NStr::CStr(), false, o_Records);
		}
	}

	template <bool t_bDstOrdered, typename t_CSrcValue>
	void fg_RecordYamlCommentsAsJson
		(
			t_CSrcValue const &_Src
			, umint _Depth
			, NStr::CStr &&_KeyLeading
			, NStr::CStr &&_ValueLeading
			, NStr::CStr &&_ValueTrailing
			, NContainer::TCVector<CJsonConvertedComments> &o_Records
		)
	{
		{
			auto &Record = o_Records.f_Insert();
			Record.m_KeyLeading = fg_Move(_KeyLeading);
			Record.m_ValueLeading = fg_Move(_ValueLeading);
			Record.m_ValueTrailing = fg_Move(_ValueTrailing);
		}

		if (_Src.f_IsObject())
		{
			auto const &SrcObject = _Src.f_Object();

			auto fRecordEntries = [&](auto _iSrc)
				{
					while (_iSrc)
					{
						auto const &SrcEntry = *_iSrc;

						++_iSrc;
						bool bLast = !_iSrc;

						auto const &SrcValue = SrcEntry.f_Value();
						auto SrcValueYaml = SrcValue.f_Yaml();
						auto SrcKeyYaml = SrcEntry.f_KeyYaml();

						bool bContainerValue = fg_YamlCommentValueIsNonEmptyContainer(SrcValue);

						// The YAML generator emits the key leading comment or, when that is empty, the
						// value leading comment. Mirror that so shared comments are not duplicated.
						NStr::CStr LeadingComment = SrcKeyYaml.f_LeadingComment();
						if (LeadingComment.f_IsEmpty())
							LeadingComment = SrcValueYaml.f_LeadingComment();

						NStr::CStr LineComment;
						if (bContainerValue)
						{
							NStr::CStr::CAppender LeadingAppender(LeadingComment);
							fg_YamlLineCommentAppendCommentLine(LeadingAppender, SrcKeyYaml.f_LineComment());
							fg_YamlLineCommentAppendCommentLine(LeadingAppender, SrcValueYaml.f_LineComment());
						}
						else
						{
							if (!SrcKeyYaml.f_LineComment().f_IsEmpty())
								LineComment = SrcKeyYaml.f_LineComment();
							if (!SrcValueYaml.f_LineComment().f_IsEmpty())
							{
								if (LineComment.f_IsEmpty())
									LineComment = SrcValueYaml.f_LineComment();
								else
								{
									NStr::CStr::CAppender LineAppender(LineComment);
									fg_YamlLineCommentAppendCommentLine(LineAppender, SrcValueYaml.f_LineComment());
								}
							}
						}

						NStr::CStr KeyLeadingTrivia;
						if (!LeadingComment.f_IsEmpty())
						{
							NStr::CStr::CAppender Appender(KeyLeadingTrivia);
							fg_YamlCommentAppendJsonLeadingTrivia(Appender, LeadingComment, _Depth + 1, false);
						}

						NStr::CStr TrailingTrivia;
						auto const &TrailingComment = SrcValueYaml.f_TrailingComment();
						if (!LineComment.f_IsEmpty() || !TrailingComment.f_IsEmpty())
						{
							NStr::CStr::CAppender Appender(TrailingTrivia);
							if (!LineComment.f_IsEmpty())
								fg_YamlLineCommentAppendJsonComment(Appender, LineComment);
							fg_YamlCommentAppendJsonTrailingLines(Appender, TrailingComment, _Depth + 1);
							if (bLast)
							{
								Appender += '\n';
								fg_JsonCommentAppendIndent(Appender, _Depth);
							}
						}

						fg_RecordYamlCommentsAsJson<t_bDstOrdered>(SrcValue, _Depth + 1, fg_Move(KeyLeadingTrivia), NStr::CStr(), fg_Move(TrailingTrivia), o_Records);
					}
				}
			;

			constexpr bool c_bSrcOrdered = NTraits::TCRemoveReferenceAndQualifiers<decltype(SrcObject)>::mc_bOrdered;
			if constexpr (c_bSrcOrdered && !t_bDstOrdered)
				fRecordEntries(SrcObject.f_SortedIterator());
			else
				fRecordEntries(SrcObject.f_OrderedIterator());
		}
		else if (_Src.f_IsArray())
		{
			auto const &SrcArray = _Src.f_Array();

			auto Count = SrcArray.f_GetLen();
			for (umint i = 0; i < Count; ++i)
			{
				auto const &SrcElement = SrcArray[i];
				auto SrcElementYaml = SrcElement.f_Yaml();

				bool bLast = i + 1 == Count;
				bool bContainerValue = fg_YamlCommentValueIsNonEmptyContainer(SrcElement);

				NStr::CStr LeadingComment = SrcElementYaml.f_LeadingComment();

				NStr::CStr LineComment;
				if (bContainerValue)
				{
					NStr::CStr::CAppender LeadingAppender(LeadingComment);
					fg_YamlLineCommentAppendCommentLine(LeadingAppender, SrcElementYaml.f_LineComment());
				}
				else
					LineComment = SrcElementYaml.f_LineComment();

				NStr::CStr LeadingTrivia;
				if (!LeadingComment.f_IsEmpty())
				{
					NStr::CStr::CAppender Appender(LeadingTrivia);
					fg_YamlCommentAppendJsonLeadingTrivia(Appender, LeadingComment, _Depth + 1, false);
				}

				NStr::CStr TrailingTrivia;
				auto const &TrailingComment = SrcElementYaml.f_TrailingComment();
				if (!LineComment.f_IsEmpty() || !TrailingComment.f_IsEmpty())
				{
					NStr::CStr::CAppender Appender(TrailingTrivia);
					if (!LineComment.f_IsEmpty())
						fg_YamlLineCommentAppendJsonComment(Appender, LineComment);
					fg_YamlCommentAppendJsonTrailingLines(Appender, TrailingComment, _Depth + 1);
					if (bLast)
					{
						Appender += '\n';
						fg_JsonCommentAppendIndent(Appender, _Depth);
					}
				}

				fg_RecordYamlCommentsAsJson<t_bDstOrdered>(SrcElement, _Depth + 1, NStr::CStr(), fg_Move(LeadingTrivia), fg_Move(TrailingTrivia), o_Records);
			}
		}

		if constexpr (requires { _Src.f_UserType(); })
		{
			if (_Src.f_IsUserType())
				fg_RecordYamlCommentsAsJson<t_bDstOrdered>(_Src.f_UserType().m_Value, _Depth, NStr::CStr(), NStr::CStr(), NStr::CStr(), o_Records);
		}
	}

	template <bool t_bDstOrdered, typename t_CSrcValue>
	void fg_RecordYamlCommentsAsJsonRoot(t_CSrcValue const &_Src, NContainer::TCVector<CJsonConvertedComments> &o_Records)
	{
		auto SrcYaml = _Src.f_Yaml();

		NStr::CStr LeadingTrivia;
		if (!SrcYaml.f_LeadingComment().f_IsEmpty())
		{
			NStr::CStr::CAppender Appender(LeadingTrivia);
			fg_YamlCommentAppendJsonLeadingTrivia(Appender, SrcYaml.f_LeadingComment(), 0, true);
		}

		NStr::CStr TrailingTrivia;
		auto const &LineComment = SrcYaml.f_LineComment();
		auto const &TrailingComment = SrcYaml.f_TrailingComment();
		if (!LineComment.f_IsEmpty() || !TrailingComment.f_IsEmpty())
		{
			NStr::CStr::CAppender Appender(TrailingTrivia);
			if (!LineComment.f_IsEmpty())
				fg_YamlLineCommentAppendJsonComment(Appender, LineComment);
			fg_YamlCommentAppendJsonTrailingLines(Appender, TrailingComment, 0);
			Appender += '\n';
		}

		fg_RecordYamlCommentsAsJson<t_bDstOrdered>(_Src, 0, NStr::CStr(), fg_Move(LeadingTrivia), fg_Move(TrailingTrivia), o_Records);
	}

	template <typename t_CDstValue, typename t_CSrcValue>
	constexpr bool gc_JsonNeedsCommentConversion =
		(t_CDstValue::mc_bPreserveYamlMetadata && t_CSrcValue::mc_bPreserveComments)
		|| (t_CDstValue::mc_bPreserveComments && t_CSrcValue::mc_bPreserveYamlMetadata)
	;

	template <typename t_CDstValue, typename t_CSrcValue>
	void fg_RecordCompatibleComments(t_CSrcValue const &_Src, NContainer::TCVector<CJsonConvertedComments> &o_Records)
	{
		if constexpr (t_CDstValue::mc_bPreserveYamlMetadata && t_CSrcValue::mc_bPreserveComments)
			fg_RecordJsonCommentsAsYaml<t_CDstValue::mc_bOrdered>(_Src, NStr::CStr(), false, o_Records);
		else if constexpr (t_CDstValue::mc_bPreserveComments && t_CSrcValue::mc_bPreserveYamlMetadata)
			fg_RecordYamlCommentsAsJsonRoot<t_CDstValue::mc_bOrdered>(_Src, o_Records);
	}

	template <typename t_CDstValue>
	void fg_ApplyConvertedComments(t_CDstValue &o_Dst, NContainer::TCVector<CJsonConvertedComments> &_Records, umint &_iRecord)
	{
		auto &Record = _Records[_iRecord];
		++_iRecord;

		if constexpr (t_CDstValue::mc_bPreserveYamlMetadata)
		{
			auto DstYaml = o_Dst.f_Yaml();
			if (!Record.m_ValueLeading.f_IsEmpty())
				DstYaml.f_SetLeadingComment(fg_Move(Record.m_ValueLeading));
			if (!Record.m_ValueLine.f_IsEmpty())
				DstYaml.f_SetLineComment(fg_Move(Record.m_ValueLine));
			if (!Record.m_ValueTrailing.f_IsEmpty())
				DstYaml.f_SetTrailingComment(fg_Move(Record.m_ValueTrailing));
		}
		else
		{
			auto DstTrivia = o_Dst.f_Trivia();
			if (!Record.m_ValueLeading.f_IsEmpty())
				DstTrivia.f_SetLeading(fg_Move(Record.m_ValueLeading), false);
			if (!Record.m_ValueTrailing.f_IsEmpty())
				DstTrivia.f_SetTrailing(fg_Move(Record.m_ValueTrailing), false);
		}

		if (o_Dst.f_IsObject())
		{
			for (auto iDst = o_Dst.f_Object().f_OrderedIterator(); iDst; ++iDst)
			{
				auto &DstEntry = *iDst;

				auto &ChildRecord = _Records[_iRecord];
				if (!ChildRecord.m_KeyLeading.f_IsEmpty())
				{
					if constexpr (t_CDstValue::mc_bPreserveYamlMetadata)
						DstEntry.f_KeyYaml().f_SetLeadingComment(fg_Move(ChildRecord.m_KeyLeading));
					else
						DstEntry.f_KeyTrivia().f_SetLeading(fg_Move(ChildRecord.m_KeyLeading), false);
				}

				fg_ApplyConvertedComments(DstEntry.f_Value(), _Records, _iRecord);
			}
		}
		else if (o_Dst.f_IsArray())
		{
			auto &DstArray = o_Dst.f_Array();
			for (umint i = 0; i < DstArray.f_GetLen(); ++i)
				fg_ApplyConvertedComments(DstArray[i], _Records, _iRecord);
		}

		if constexpr (requires { o_Dst.f_UserType(); })
		{
			if (o_Dst.f_IsUserType())
				fg_ApplyConvertedComments(o_Dst.f_UserType().m_Value, _Records, _iRecord);
		}
	}

	template <typename t_CDstValue>
	void fg_ApplyCompatibleComments(t_CDstValue &o_Dst, NContainer::TCVector<CJsonConvertedComments> &_Records)
	{
		umint iRecord = 0;
		fg_ApplyConvertedComments(o_Dst, _Records, iRecord);
	}

	template <typename t_CDstValue, typename t_CSrcValue>
	void fg_ConvertCompatibleComments(t_CDstValue &o_Dst, t_CSrcValue const &_Src)
	{
		if constexpr (gc_JsonNeedsCommentConversion<t_CDstValue, t_CSrcValue>)
		{
			NContainer::TCVector<CJsonConvertedComments> Records;
			fg_RecordCompatibleComments<t_CDstValue>(_Src, Records);
			fg_ApplyCompatibleComments(o_Dst, Records);
		}
	}
}
