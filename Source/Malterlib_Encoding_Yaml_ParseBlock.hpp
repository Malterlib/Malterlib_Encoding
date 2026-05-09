// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NEncoding::NYaml
{
	template <typename tf_CParseContext>
	umint fg_GetYamlLineIndent(uch8 const *_pParse, tf_CParseContext &_Context)
	{
		umint nIndent = 0;
		while (_pParse[nIndent] == ' ')
			++nIndent;

		if (_pParse[nIndent] == '\t')
			fg_ThrowYamlParseError(_Context, "Tabs are not allowed in YAML block indentation", _pParse + nIndent);

		return nIndent;
	}

	inline bool fg_AtYamlLineStart(uch8 const *_pParse, uch8 const *_pStart)
	{
		return _pParse == _pStart || _pParse[-1] == '\n' || _pParse[-1] == '\r';
	}

	template <typename tf_CParseContext, typename tf_CLeadingComment, typename tf_CTrailingComment>
	void fg_SkipYamlBlockBlankLines
		(
			uch8 const *&o_pParse
			, tf_CParseContext &_Context
			, tf_CLeadingComment &o_LeadingComment
			, umint _MinCommentIndent
			, tf_CTrailingComment &o_TrailingCommentBeforeBlank
		)
	{
		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		while (*pParse)
		{
			auto pRawLine = pParse;
			auto pLine = pParse;
			auto nIndent = fg_GetYamlLineIndent(pLine, _Context);

			while (*pLine == ' ' || *pLine == '\t')
				++pLine;

			if (*pLine == '#')
			{
				if (nIndent < _MinCommentIndent)
					break;

				while (*pLine && *pLine != '\n')
					++pLine;

				if constexpr (!NTraits::cIsSame<tf_CLeadingComment, CEmpty>)
				{
					NStr::CStr::CAppender Appender(o_LeadingComment);
					Appender.f_AddString(reinterpret_cast<ch8 const *>(pRawLine), pLine - pRawLine);
					Appender += '\n';
				}

				if (*pLine == '\n')
					++pLine;

				pParse = pLine;

				continue;
			}

			if (*pLine == '\r' || *pLine == '\n')
			{
				if constexpr (!NTraits::cIsSame<tf_CLeadingComment, CEmpty> && !NTraits::cIsSame<tf_CTrailingComment, CEmpty>)
				{
					if (!o_LeadingComment.f_IsEmpty())
					{
						o_TrailingCommentBeforeBlank += o_LeadingComment;
						o_LeadingComment = {};
					}
				}

				if constexpr (!NTraits::cIsSame<tf_CTrailingComment, CEmpty>)
				{
					if (!o_TrailingCommentBeforeBlank.f_IsEmpty())
						o_TrailingCommentBeforeBlank += '\n';
					else if constexpr (!NTraits::cIsSame<tf_CLeadingComment, CEmpty>)
						o_LeadingComment += '\n';
				}
				else if constexpr (!NTraits::cIsSame<tf_CLeadingComment, CEmpty>)
					o_LeadingComment += '\n';

				if (*pLine == '\r' && pLine[1] == '\n')
					pLine += 2;
				else
					++pLine;

				pParse = pLine;

				continue;
			}

			break;
		}
	}

	template <typename tf_CParseContext, typename tf_CLeadingComment>
	void fg_SkipYamlBlockBlankLines(uch8 const *&o_pParse, tf_CParseContext &_Context, tf_CLeadingComment &o_LeadingComment, umint _MinCommentIndent = 0)
	{
		CEmpty TrailingCommentBeforeBlank;
		fg_SkipYamlBlockBlankLines(o_pParse, _Context, o_LeadingComment, _MinCommentIndent, TrailingCommentBeforeBlank);
	}

	template <typename tf_CParseContext>
	void fg_SkipYamlBlockBlankLines(uch8 const *&o_pParse, tf_CParseContext &_Context, umint _MinCommentIndent = 0)
	{
		CEmpty LeadingComment;
		CEmpty TrailingCommentBeforeBlank;
		fg_SkipYamlBlockBlankLines(o_pParse, _Context, LeadingComment, _MinCommentIndent, TrailingCommentBeforeBlank);
	}

	template <typename tf_CParseContext, typename tf_CLineComment>
	void fg_ConsumeYamlLineEnd(uch8 const *&o_pParse, tf_CParseContext &_Context, tf_CLineComment &o_LineComment)
	{
		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		auto pRawComment =
			pParse > _Context.m_pStartParse && (*pParse == '#') && (pParse[-1] == ' ' || pParse[-1] == '\t')
			? pParse - 1
			: pParse
		;

		while (*pParse == ' ' || *pParse == '\t')
			++pParse;

		if (*pParse == '#')
		{
			while (*pParse && *pParse != '\n' && *pParse != '\r')
				++pParse;

			if constexpr (!NTraits::cIsSame<tf_CLineComment, CEmpty>)
			{
				NStr::CStr::CAppender Appender(o_LineComment);
				Appender.f_AddString(reinterpret_cast<ch8 const *>(pRawComment), pParse - pRawComment);
			}
		}

		NStr::fg_ParseEndOfLine(pParse);
	}

	template <typename tf_CParseContext>
	void fg_ConsumeYamlLineEnd(uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		CEmpty LineComment;
		fg_ConsumeYamlLineEnd(o_pParse, _Context, LineComment);
	}

	template <typename tf_CParseContext>
	NStr::CStr fg_TakeYamlLineCommentRaw(uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		NStr::CStr LineComment;
		fg_ConsumeYamlLineEnd(pParse, _Context, LineComment);

		return LineComment;
	}

	inline void fg_NormalizeYamlLineCommentForStorage(NStr::CStr &o_Comment)
	{
		NStr::fg_StrTrimRight(o_Comment, "\r\n");
	}

	template <typename tf_CParseContext, typename tf_CLineComment>
	NStr::CStr fg_ParseYamlBlockScalar(uch8 const *&o_pParse, tf_CParseContext &_Context, umint _ParentIndent, bool _bFolded, uch8 &o_ChompIndicator, smint &o_BlockIndentHint, tf_CLineComment &o_LineComment)
	{
		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		++pParse;
		o_ChompIndicator = 0;
		o_BlockIndentHint = -1;
		while (*pParse == '+' || *pParse == '-' || (*pParse >= '1' && *pParse <= '9'))
		{
			if (*pParse == '+' || *pParse == '-')
				o_ChompIndicator = *pParse++;
			else
				o_BlockIndentHint = *pParse++ - '0';
		}

		fg_ConsumeYamlLineEnd(pParse, _Context, o_LineComment);

		NStr::CStr Return;
		umint ChildIndent = _ParentIndent + (o_BlockIndentHint >= 0 ? umint(o_BlockIndentHint) : 2);

		if (o_BlockIndentHint < 0)
		{
			auto pScan = pParse;
			while (*pScan)
			{
				umint nIndent = 0;
				while (pScan[nIndent] == ' ')
					++nIndent;

				auto pLine = pScan + nIndent;
				if (*pLine != '\r' && *pLine != '\n')
				{
					if (nIndent > _ParentIndent)
						ChildIndent = nIndent;

					break;
				}

				fg_ConsumeYamlLineEnd(pScan, _Context);
			}
		}

		{
			NStr::CStr::CAppender Appender(Return);
			bool bFirst = true;
			bool bPreviousFoldKeptLineBreak = false;

			while (*pParse)
			{
				umint nIndent = 0;
				while (pParse[nIndent] == ' ')
					++nIndent;

				auto pLine = pParse + nIndent;
				if (nIndent < ChildIndent && *pLine != '\r' && *pLine != '\n')
					break;

				bool bMoreIndented = nIndent > ChildIndent;
				if (nIndent >= ChildIndent)
					pLine = pParse + ChildIndent;

				auto pLineStart = pLine;
				while (*pLine && *pLine != '\r' && *pLine != '\n')
					++pLine;
				auto nLineLen = pLine - pLineStart;

				if (_bFolded)
				{
					if (bMoreIndented)
					{
						if (!bFirst && !bPreviousFoldKeptLineBreak)
							Appender += '\n';

						Appender.f_AddString(reinterpret_cast<ch8 const *>(pLineStart), nLineLen);
						Appender += '\n';

						bPreviousFoldKeptLineBreak = true;
					}
					else
					{
						if (!bFirst)
						{
							if (nLineLen == 0)
							{
								Appender += '\n';
								bPreviousFoldKeptLineBreak = true;
							}
							else if (!bPreviousFoldKeptLineBreak)
								Appender += ' ';
						}

						Appender.f_AddString(reinterpret_cast<ch8 const *>(pLineStart), nLineLen);

						if (nLineLen > 0)
							bPreviousFoldKeptLineBreak = false;
					}
				}
				else
				{
					Appender.f_AddString(reinterpret_cast<ch8 const *>(pLineStart), nLineLen);
					Appender += '\n';
				}

				bFirst = false;
				pParse = pLine;

				fg_ConsumeYamlLineEnd(pParse, _Context);
			}
		}

		if (o_ChompIndicator == '-')
		{
			umint nLen = Return.f_GetLen();
			auto pReturn = Return.f_GetStr();

			while (nLen > 0 && pReturn[nLen - 1] == '\n')
				--nLen;

			Return.f_GetStrWritable()[nLen] = 0;
			Return.f_SetStrLen(nLen);
		}
		else if (o_ChompIndicator != '+')
		{
			umint nLen = Return.f_GetLen();
			auto pReturn = Return.f_GetStr();
			while (nLen > 0 && pReturn[nLen - 1] == '\n')
				--nLen;

			if (nLen < Return.f_GetLen())
			{
				auto pReturnWritable = Return.f_GetStrWritable();
				pReturnWritable[nLen] = '\n';
				pReturnWritable[nLen + 1] = 0;

				Return.f_SetStrLen(nLen + 1);
			}
			else
				Return += '\n';
		}
		else if (_bFolded && (Return.f_IsEmpty() || Return.f_GetStr()[Return.f_GetLen() - 1] != '\n'))
			Return += '\n';

		return Return;
	}

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_ParseYamlBlockNode(tf_CValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context, TCYamlAnchors<tf_CValue> &_Anchors, umint _Indent, bool _bStandaloneNode = true);

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_SetYamlValueLeadingComment(tf_CValue &o_Value, NStr::CStr &&_Comment)
	{
		if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			o_Value.f_Yaml().f_SetLeadingComment(fg_Move(_Comment));
	}

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_SetYamlValueLineComment(tf_CValue &o_Value, NStr::CStr &&_Comment)
	{
		if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			o_Value.f_Yaml().f_SetLineComment(fg_Move(_Comment));
	}

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_SetYamlValueTrailingComment(tf_CValue &o_Value, NStr::CStr &&_Comment)
	{
		if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
		{
			NStr::CStr Comment = fg_Move(_Comment);
			if (!o_Value.f_Yaml().f_TrailingComment().f_IsEmpty())
				Comment = o_Value.f_Yaml().f_TrailingComment() + Comment;

			o_Value.f_Yaml().f_SetTrailingComment(fg_Move(Comment));
		}
	}

	template <typename tf_CObjectEntry, typename tf_CParseContext>
	void fg_SetYamlKeyLeadingComment(tf_CObjectEntry &o_Entry, NStr::CStr &&_Comment)
	{
		if constexpr (tf_CParseContext::mc_bRecordYamlMetadata)
			o_Entry.f_KeyYaml().f_SetLeadingComment(fg_Move(_Comment));
	}

	template <typename tf_CObjectEntry, typename tf_CParseContext>
	void fg_SetYamlKeyLineComment(tf_CObjectEntry &o_Entry, NStr::CStr &&_Comment)
	{
		if constexpr (tf_CParseContext::mc_bRecordYamlMetadata)
			o_Entry.f_KeyYaml().f_SetLineComment(fg_Move(_Comment));
	}

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_AttachYamlLeadingCommentToFirstChildOrValue(tf_CValue &o_Value, NStr::CStr &&_LeadingComment)
	{
		if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
		{
			if (_LeadingComment.f_IsEmpty())
				return;

			if (o_Value.f_IsArray() && o_Value.f_Array().f_GetLen() > 0)
			{
				fg_SetYamlValueLeadingComment<tf_CValue, tf_CParseContext>(o_Value.f_Array()[0], fg_Move(_LeadingComment));

				return;
			}
			else if (o_Value.f_IsObject())
			{
				auto iFirst = o_Value.f_Object().f_OrderedIterator();
				if (iFirst)
				{
					fg_SetYamlKeyLeadingComment<decltype(*iFirst), tf_CParseContext>(*iFirst, fg_TempCopy(_LeadingComment));
					fg_SetYamlValueLeadingComment<tf_CValue, tf_CParseContext>(iFirst->f_Value(), fg_Move(_LeadingComment));

					return;
				}
			}

			fg_SetYamlValueLeadingComment<tf_CValue, tf_CParseContext>(o_Value, fg_Move(_LeadingComment));
		}
	}

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_ParseYamlInlineOrNestedBlockValue(tf_CValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context, TCYamlAnchors<tf_CValue> &_Anchors, umint _Indent)
	{
		using CMetadataString = TCConditional<tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata, NStr::CStr, CEmpty>;

		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		while (*pParse == ' ' || *pParse == '\t')
			++pParse;

		CMetadataString TagHandle;
		CMetadataString TagSuffix;
		NStr::CStr TagResolved;
		NStr::CStr AnchorName;
		uch8 const *pPropertyLineCommentWhitespaceStart = nullptr;

		while (*pParse == '!' || *pParse == '&')
		{
			if (*pParse == '!')
			{
				if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
					fg_ParseYamlTag(pParse, _Context, TagHandle, TagSuffix, TagResolved);
				else
				{
					NStr::CStr ScratchHandle;
					NStr::CStr ScratchSuffix;
					fg_ParseYamlTag(pParse, _Context, ScratchHandle, ScratchSuffix, TagResolved);
				}
			}
			else
			{
				++pParse;
				AnchorName = fg_ParseYamlName(pParse, _Context);
			}

			auto pWhitespaceStart = pParse;
			while (*pParse == ' ' || *pParse == '\t')
				++pParse;

			if (*pParse == '#')
			{
				pPropertyLineCommentWhitespaceStart = pWhitespaceStart;

				break;
			}
		}

		bool bCloseAnchor = false;
		umint iAnchor = 0;
		if (!AnchorName.f_IsEmpty())
		{
			iAnchor = _Anchors.f_GetLen();
			fg_AddAnchor(_Anchors, AnchorName);
			bCloseAnchor = true;
		}

		auto CloseAnchor = g_OnScopeExit / [&]
			{
				if (bCloseAnchor)
				{
					auto &Anchor = _Anchors[iAnchor];
					Anchor.m_Value = o_Value;
					Anchor.m_bOpen = false;
				}
			}
		;

		auto fApplyMetadata = [&]
			{
				if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
				{
					if (!AnchorName.f_IsEmpty())
						o_Value.f_Yaml().f_SetAnchor(fg_TempCopy(AnchorName));

					if (!TagHandle.f_IsEmpty() || !TagResolved.f_IsEmpty())
						o_Value.f_Yaml().f_SetTag(fg_TempCopy(TagHandle), fg_TempCopy(TagSuffix), fg_TempCopy(TagResolved));
				}
			}
		;

		if (*pParse == '*')
		{
			if (!AnchorName.f_IsEmpty() || !TagResolved.f_IsEmpty())
				fg_ThrowYamlParseError(_Context, "YAML alias node must not specify properties", pParse);

			++pParse;
			auto AliasName = fg_ParseYamlName(pParse, _Context);
			auto *pAliasAnchor = fg_FindAnchor(_Anchors, AliasName);

			if (!pAliasAnchor)
				fg_ThrowYamlParseError(_Context, "Unknown YAML alias", pParse);

			if (pAliasAnchor->m_bOpen)
				fg_ThrowYamlParseError(_Context, "cyclic alias not supported", pParse);

			o_Value = pAliasAnchor->m_Value;

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				o_Value.f_Yaml().f_ResetYamlMetadata();
				o_Value.f_Yaml().f_SetAlias(fg_Move(AliasName));
			}

			fApplyMetadata();

			CMetadataString LineComment;
			fg_ConsumeYamlLineEnd(pParse, _Context, LineComment);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (!LineComment.f_IsEmpty())
					fg_SetYamlValueLineComment<tf_CValue, tf_CParseContext>(o_Value, fg_Move(LineComment));
			}

			return;
		}

		if (!*pParse || *pParse == '\r' || *pParse == '\n' || *pParse == '#')
		{
			CMetadataString LineComment;
			if (*pParse)
			{
				auto pLineCommentParse = pPropertyLineCommentWhitespaceStart ? pPropertyLineCommentWhitespaceStart : pParse;
				fg_ConsumeYamlLineEnd(pLineCommentParse, _Context, LineComment);
				pParse = pLineCommentParse;
			}

			auto pBlockStart = pParse;
			fg_SkipYamlBlockBlankLines(pBlockStart, _Context);

			auto nIndent = *pBlockStart ? fg_GetYamlLineIndent(pBlockStart, _Context) : 0;
			if (!*pBlockStart || nIndent <= _Indent)
				o_Value = nullptr;
			else
				fg_ParseYamlBlockNode(o_Value, pParse, _Context, _Anchors, nIndent, TagResolved.f_IsEmpty());

			fg_ApplyYamlTag(o_Value, TagResolved, {});
			fApplyMetadata();

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (!TagResolved.f_IsEmpty() && (o_Value.f_IsObject() || o_Value.f_IsArray()))
					o_Value.f_Yaml().f_SetNodeStyle(EYamlNodeStyle_Unspecified);
			}

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata && requires { o_Value.f_EType(); o_Value.f_UserType(); })
			{
				if (!TagResolved.f_IsEmpty() && o_Value.f_EType() == EEJsonType_UserType)
					o_Value.f_Yaml().f_SetNodeStyle(EYamlNodeStyle_Unspecified);
			}

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (!LineComment.f_IsEmpty())
					fg_SetYamlValueLineComment<tf_CValue, tf_CParseContext>(o_Value, fg_Move(LineComment));
			}

			return;
		}

		if (*pParse == '|')
		{
			uch8 ChompIndicator;
			smint BlockIndentHint;
			CMetadataString LineComment;

			auto RawScalar = fg_ParseYamlBlockScalar(pParse, _Context, _Indent, false, ChompIndicator, BlockIndentHint, LineComment);
			o_Value = RawScalar;

			fg_ApplyYamlTag(o_Value, TagResolved, RawScalar);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				o_Value.f_Yaml().f_SetScalarStyle(EYamlScalarStyle_Literal);
				o_Value.f_Yaml().f_SetChompIndicator(ChompIndicator);
				o_Value.f_Yaml().f_SetBlockIndentHint(BlockIndentHint);

				if (!LineComment.f_IsEmpty())
					fg_SetYamlValueLineComment<tf_CValue, tf_CParseContext>(o_Value, fg_Move(LineComment));
			}

			fApplyMetadata();

			return;
		}

		if (*pParse == '>')
		{
			uch8 ChompIndicator;
			smint BlockIndentHint;
			NStr::CStr LineComment;

			auto RawScalar = fg_ParseYamlBlockScalar(pParse, _Context, _Indent, true, ChompIndicator, BlockIndentHint, LineComment);
			o_Value = RawScalar;

			fg_ApplyYamlTag(o_Value, TagResolved, RawScalar);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				o_Value.f_Yaml().f_SetScalarStyle(EYamlScalarStyle_Folded);
				o_Value.f_Yaml().f_SetChompIndicator(ChompIndicator);
				o_Value.f_Yaml().f_SetBlockIndentHint(BlockIndentHint);

				if (!LineComment.f_IsEmpty())
					fg_SetYamlValueLineComment<tf_CValue, tf_CParseContext>(o_Value, fg_Move(LineComment));
			}

			fApplyMetadata();

			return;
		}

		if (*pParse == '{' || *pParse == '[')
		{
			fg_ParseYamlNode(o_Value, pParse, _Context, _Anchors);
			fg_ApplyYamlTag(o_Value, TagResolved, {});

			fApplyMetadata();

			CMetadataString LineComment;
			fg_ConsumeYamlLineEnd(pParse, _Context, LineComment);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (!LineComment.f_IsEmpty())
					fg_SetYamlValueLineComment<tf_CValue, tf_CParseContext>(o_Value, fg_Move(LineComment));
			}

			return;
		}

		if (*pParse == '-' && fg_IsYamlSeparation(pParse[1]))
		{
			auto pLineStart = pParse;
			while (pLineStart > _Context.m_pStartParse && pLineStart[-1] != '\n' && pLineStart[-1] != '\r')
				--pLineStart;

			auto nCurrentIndent = umint(pParse - pLineStart);
			auto nSequenceIndent = fg_Min(nCurrentIndent, _Indent + 2);

			if (nCurrentIndent == nSequenceIndent)
				fg_ParseYamlBlockSequence(o_Value, pParse, _Context, _Anchors, nSequenceIndent);
			else
			{
				o_Value.f_SetType(EJsonType_Array);

				if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
					o_Value.f_Yaml().f_SetNodeStyle(EYamlNodeStyle_Block);

				CMetadataString PendingLeadingComment;
				while (*pParse)
				{
					auto pLine = pParse;
					while (*pLine == ' ' || *pLine == '\t')
						++pLine;

					if (pLine[0] != '-' || !fg_IsYamlSeparation(pLine[1]))
						break;

					pParse = pLine + 1;
					auto &Child = o_Value.f_Insert();
					fg_ParseYamlInlineOrNestedBlockValue(Child, pParse, _Context, _Anchors, nSequenceIndent);

					if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
					{
						if (!PendingLeadingComment.f_IsEmpty())
							Child.f_Yaml().f_SetLeadingComment(fg_Move(PendingLeadingComment));
					}

					fg_SkipYamlBlockBlankLines(pParse, _Context, PendingLeadingComment, nSequenceIndent);

					if (!*pParse || fg_GetYamlLineIndent(pParse, _Context) != nSequenceIndent)
						break;
				}
			}
			fg_ApplyYamlTag(o_Value, TagResolved, {});

			fApplyMetadata();

			return;
		}

		if (*pParse == '\'' && !fg_YamlQuotedScalarStartsCompactMapping(pParse, '\''))
		{
			NStr::CStr String;
			fg_ParseYamlSingleQuotedScalar(String, pParse, _Context);

			NStr::CStr RawScalar = String;
			o_Value = fg_Move(String);
			fg_ApplyYamlTag(o_Value, TagResolved, RawScalar);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
				o_Value.f_Yaml().f_SetScalarStyle(EYamlScalarStyle_SingleQuoted);

			fApplyMetadata();

			CMetadataString LineComment;
			fg_ConsumeYamlLineEnd(pParse, _Context, LineComment);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (!LineComment.f_IsEmpty())
					fg_SetYamlValueLineComment<tf_CValue, tf_CParseContext>(o_Value, fg_Move(LineComment));
			}

			return;
		}

		if (*pParse == '"' && !fg_YamlQuotedScalarStartsCompactMapping(pParse, '"'))
		{
			NStr::CStr String;
			fg_ParseYamlDoubleQuotedScalar(String, pParse, _Context);

			NStr::CStr RawScalar = String;
			o_Value = fg_Move(String);
			fg_ApplyYamlTag(o_Value, TagResolved, RawScalar);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
				o_Value.f_Yaml().f_SetScalarStyle(EYamlScalarStyle_DoubleQuoted);

			fApplyMetadata();

			CMetadataString LineComment;
			fg_ConsumeYamlLineEnd(pParse, _Context, LineComment);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (!LineComment.f_IsEmpty())
					fg_SetYamlValueLineComment<tf_CValue, tf_CParseContext>(o_Value, fg_Move(LineComment));
			}

			return;
		}

		auto fParseCompactMappingEntry = [&] (auto _LeadingComment) -> bool
			{
				auto pKeyStart = pParse;
				auto pColon = pParse;
				while (*pColon && *pColon != '\r' && *pColon != '\n' && *pColon != '#')
				{
					if (*pColon == '\'' || *pColon == '"')
					{
						auto Quote = *pColon++;
						while (*pColon && *pColon != '\r' && *pColon != '\n')
						{
							if (*pColon == Quote)
							{
								if (Quote == '\'' && pColon[1] == '\'')
								{
									pColon += 2;

									continue;
								}

								++pColon;

								break;
							}

							if (Quote == '"' && *pColon == '\\' && pColon[1])
								pColon += 2;
							else
								++pColon;
						}

						continue;
					}

					if (*pColon == ':')
						break;

					++pColon;
				}

				if (*pColon != ':' || !fg_IsYamlSeparation(pColon[1]))
					return false;

				NStr::CStr Key;
				NStr::CStr KeyAnchorName;
				NStr::CStr KeyAliasName;
				NStr::CStr KeyTagHandle;
				NStr::CStr KeyTagSuffix;
				NStr::CStr KeyTagResolved;
				EYamlScalarStyle KeyScalarStyle = EYamlScalarStyle_Plain;
				bool bQuotedKey = false;

				while (*pParse == '!' || *pParse == '&')
				{
					if (*pParse == '!')
						fg_ParseYamlTag(pParse, _Context, KeyTagHandle, KeyTagSuffix, KeyTagResolved);
					else
					{
						++pParse;
						KeyAnchorName = fg_ParseYamlName(pParse, _Context);
					}

					while (*pParse == ' ' || *pParse == '\t')
						++pParse;
				}

				if (*pParse == '\'')
				{
					bQuotedKey = true;
					KeyScalarStyle = EYamlScalarStyle_SingleQuoted;

					fg_ParseYamlSingleQuotedScalar(Key, pParse, _Context);
				}
				else if (*pParse == '"')
				{
					bQuotedKey = true;
					KeyScalarStyle = EYamlScalarStyle_DoubleQuoted;

					fg_ParseYamlDoubleQuotedScalar(Key, pParse, _Context);
				}
				else if (*pParse == '*')
				{
					if (!KeyAnchorName.f_IsEmpty() || !KeyTagResolved.f_IsEmpty())
						fg_ThrowYamlParseError(_Context, "YAML alias node must not specify properties", pKeyStart);

					++pParse;
					KeyAliasName = fg_ParseYamlName(pParse, _Context);

					auto *pAnchor = fg_FindAnchor(_Anchors, KeyAliasName);
					if (!pAnchor || !pAnchor->m_Value.f_IsString())
						fg_ThrowYamlParseError(_Context, "YAML mapping key alias must resolve to a string", pKeyStart);

					Key = pAnchor->m_Value.f_String();
					bQuotedKey = true;
				}
				else
				{
					auto pKeyTextStart = pParse;
					while (*pParse && *pParse != ':' && *pParse != '\r' && *pParse != '\n')
						++pParse;

					Key = fg_MakeYamlTrimmedString(pKeyTextStart, pParse);
				}

				if (*pParse != ':' || !fg_IsYamlSeparation(pParse[1]))
					return false;

				if (!KeyTagResolved.f_IsEmpty())
				{
					tf_CValue KeyValue;
					KeyValue = Key;

					fg_ApplyYamlTag(KeyValue, KeyTagResolved, Key);

					if (!KeyValue.f_IsString())
						fg_ThrowYamlParseError(_Context, "YAML mapping key must be a string", pKeyStart);

					Key = KeyValue.f_String();
					bQuotedKey = true;
				}

				if (!KeyAnchorName.f_IsEmpty())
				{
					auto &Anchor = fg_AddAnchor(_Anchors, KeyAnchorName);
					Anchor.m_Value = Key;
					Anchor.m_bOpen = false;
				}

				fg_ValidateYamlMappingKeyString<tf_CValue>(Key, bQuotedKey, _Context, pKeyStart);

				if (!o_Value.f_IsObject())
				{
					o_Value.f_SetType(EJsonType_Object);

					if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
						o_Value.f_Yaml().f_SetNodeStyle(EYamlNodeStyle_Block);
				}

				if constexpr (!tf_CParseContext::mc_bAllowDuplicateKeys)
				{
					if (o_Value.f_Object().f_GetMember(Key))
						fg_ThrowYamlParseError(_Context, "Duplicate YAML mapping key", pKeyStart);
				}

				auto &Entry = o_Value.f_Object().f_CreateMemberEntry(Key);
				if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
				{
					if (!_LeadingComment.f_IsEmpty())
						Entry.f_KeyYaml().f_SetLeadingComment(fg_TempCopy(_LeadingComment));

					if (!KeyAnchorName.f_IsEmpty())
						Entry.f_KeyYaml().f_SetAnchor(fg_Move(KeyAnchorName));

					if (!KeyAliasName.f_IsEmpty())
						Entry.f_KeyYaml().f_SetAlias(fg_Move(KeyAliasName));

					if (!KeyTagHandle.f_IsEmpty() || !KeyTagResolved.f_IsEmpty())
						Entry.f_KeyYaml().f_SetTag(fg_Move(KeyTagHandle), fg_Move(KeyTagSuffix), fg_Move(KeyTagResolved));

					Entry.f_KeyYaml().f_SetScalarStyle(KeyScalarStyle);
				}

				++pParse;

				fg_ParseYamlInlineOrNestedBlockValue(Entry.f_Value(), pParse, _Context, _Anchors, _Indent + 2);

				if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
				{
					if (!_LeadingComment.f_IsEmpty())
						Entry.f_Value().f_Yaml().f_SetLeadingComment(fg_Move(_LeadingComment));
				}

				return true;
			}
		;

		if (fParseCompactMappingEntry(CMetadataString{}))
		{
			while (*pParse)
			{
				CMetadataString LeadingComment;
				fg_SkipYamlBlockBlankLines(pParse, _Context, LeadingComment, _Indent + 2);

				auto nIndent = fg_GetYamlLineIndent(pParse, _Context);
				if (nIndent != _Indent + 2)
					break;

				auto pLine = pParse + nIndent;
				if (pLine[0] == '-' && fg_IsYamlSeparation(pLine[1]))
					break;

				pParse = pLine;

				if (!fParseCompactMappingEntry(fg_Move(LeadingComment)))
					break;
			}

			fApplyMetadata();

			return;
		}

		auto pTokenStart = pParse;
		while (*pParse && *pParse != '\r' && *pParse != '\n')
		{
			if (*pParse == '#' && (pParse == pTokenStart || pParse[-1] == ' ' || pParse[-1] == '\t'))
				break;

			++pParse;
		}

		auto TokenRange = fg_MakeYamlTrimmedStringPtr(pTokenStart, pParse);
		NStr::CStr Token;
		bool bHasTokenString = false;

		while (*pParse == '\r' || *pParse == '\n')
		{
			auto pNext = pParse;
			if (*pNext == '\r' && pNext[1] == '\n')
				pNext += 2;
			else
				++pNext;

			auto nNextIndent = *pNext ? fg_GetYamlLineIndent(pNext, _Context) : 0;
			if (!*pNext || nNextIndent <= _Indent)
				break;

			pParse = pNext + nNextIndent;

			if (!bHasTokenString)
			{
				Token = TokenRange;
				bHasTokenString = true;
			}

			auto pContinuationStart = pParse;
			while (*pParse && *pParse != '\r' && *pParse != '\n')
			{
				if (*pParse == '#' && (pParse == pContinuationStart || pParse[-1] == ' ' || pParse[-1] == '\t'))
					break;

				++pParse;
			}

			auto Continuation = fg_MakeYamlTrimmedStringPtr(pContinuationStart, pParse);

			if (!Continuation.f_IsEmpty())
			{
				if (!Token.f_IsEmpty())
				{
					NStr::CStr::CAppender Appender(Token);
					Appender += ' ';
					Appender += Continuation;
				}
				else
					Token = fg_Move(Continuation);
			}
		}

		if (!TagResolved.f_IsEmpty())
		{
			if (!bHasTokenString)
				Token = TokenRange;
			o_Value = Token;
		}
		else if (bHasTokenString)
			fg_SetYamlPlainScalar(o_Value, Token);
		else
			fg_SetYamlPlainScalar(o_Value, TokenRange);

		if (!TagResolved.f_IsEmpty())
			fg_ApplyYamlTag(o_Value, TagResolved, Token);

		if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			o_Value.f_Yaml().f_SetScalarStyle(EYamlScalarStyle_Plain);

		fApplyMetadata();

		if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
		{
			while (pParse > pTokenStart && (pParse[-1] == ' ' || pParse[-1] == '\t'))
				--pParse;

			CMetadataString LineComment;
			fg_ConsumeYamlLineEnd(pParse, _Context, LineComment);
			if (!LineComment.f_IsEmpty())
				fg_SetYamlValueLineComment<tf_CValue, tf_CParseContext>(o_Value, fg_Move(LineComment));
		}
		else
			fg_ConsumeYamlLineEnd(pParse, _Context);
	}

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_ParseYamlBlockSequence(tf_CValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context, TCYamlAnchors<tf_CValue> &_Anchors, umint _Indent)
	{
		using CMetadataString = TCConditional<tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata, NStr::CStr, CEmpty>;

		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		o_Value.f_SetType(EJsonType_Array);
		++_Context.m_ObjectArrayParseDepth;
		auto DepthCleanup = g_OnScopeExit / [&]
			{
				--_Context.m_ObjectArrayParseDepth;
			}
		;

		if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			o_Value.f_Yaml().f_SetNodeStyle(EYamlNodeStyle_Block);

		tf_CValue *pLastChild = nullptr;
		while (*pParse)
		{
			CMetadataString LeadingComment;
			CMetadataString TrailingCommentBeforeBlank;

			fg_SkipYamlBlockBlankLines(pParse, _Context, LeadingComment, _Indent, TrailingCommentBeforeBlank);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (pLastChild && !TrailingCommentBeforeBlank.f_IsEmpty())
					fg_SetYamlValueTrailingComment<tf_CValue, tf_CParseContext>(*pLastChild, fg_Move(TrailingCommentBeforeBlank));
			}

			if (!*pParse)
			{
				if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
				{
					if (pLastChild && !LeadingComment.f_IsEmpty())
						fg_SetYamlValueTrailingComment<tf_CValue, tf_CParseContext>(*pLastChild, fg_Move(LeadingComment));
				}

				break;
			}

			auto nIndent = fg_GetYamlLineIndent(pParse, _Context);
			if (nIndent != _Indent)
			{
				if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
				{
					if (pLastChild && !LeadingComment.f_IsEmpty())
						fg_SetYamlValueTrailingComment<tf_CValue, tf_CParseContext>(*pLastChild, fg_Move(LeadingComment));
				}

				break;
			}

			auto pLine = pParse + nIndent;
			if (!(pLine[0] == '-' && (pLine[1] == ' ' || pLine[1] == '\t' || pLine[1] == '\r' || pLine[1] == '\n' || pLine[1] == 0)))
				break;

			pParse = pLine + 1;
			auto &Child = o_Value.f_Insert();
			pLastChild = &Child;

			fg_ParseYamlInlineOrNestedBlockValue(Child, pParse, _Context, _Anchors, _Indent);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (!LeadingComment.f_IsEmpty())
					fg_SetYamlValueLeadingComment<tf_CValue, tf_CParseContext>(Child, fg_Move(LeadingComment));
			}
		}
	}

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_ParseYamlBlockMapping(tf_CValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context, TCYamlAnchors<tf_CValue> &_Anchors, umint _Indent)
	{
		using CMetadataString = TCConditional<tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata, NStr::CStr, CEmpty>;

		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		o_Value.f_SetType(EJsonType_Object);

		++_Context.m_ObjectArrayParseDepth;
		auto DepthCleanup = g_OnScopeExit / [&]
			{
				--_Context.m_ObjectArrayParseDepth;
			}
		;

		if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			o_Value.f_Yaml().f_SetNodeStyle(EYamlNodeStyle_Block);

		tf_CValue *pLastValue = nullptr;
		while (*pParse)
		{
			CMetadataString LeadingComment;
			CMetadataString TrailingCommentBeforeBlank;

			fg_SkipYamlBlockBlankLines(pParse, _Context, LeadingComment, _Indent, TrailingCommentBeforeBlank);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (pLastValue && !TrailingCommentBeforeBlank.f_IsEmpty())
					fg_SetYamlValueTrailingComment<tf_CValue, tf_CParseContext>(*pLastValue, fg_Move(TrailingCommentBeforeBlank));
			}

			if (!*pParse)
			{
				if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
				{
					if (pLastValue && !LeadingComment.f_IsEmpty())
						fg_SetYamlValueTrailingComment<tf_CValue, tf_CParseContext>(*pLastValue, fg_Move(LeadingComment));
				}

				break;
			}

			auto nIndent = fg_GetYamlLineIndent(pParse, _Context);
			if (nIndent != _Indent)
			{
				if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
				{
					if (pLastValue && !LeadingComment.f_IsEmpty())
						fg_SetYamlValueTrailingComment<tf_CValue, tf_CParseContext>(*pLastValue, fg_Move(LeadingComment));
				}

				break;
			}

			auto pLine = pParse + nIndent;
			bool bExplicitKey = false;
			if (*pLine == '?' && fg_IsYamlSeparation(pLine[1]))
			{
				bExplicitKey = true;
				++pLine;
				while (*pLine == ' ' || *pLine == '\t')
					++pLine;
			}

			NStr::CStr Key;
			auto pKeyStart = pLine;
			NStr::CStr KeyAnchorName;
			NStr::CStr KeyAliasName;
			NStr::CStr KeyTagHandle;
			NStr::CStr KeyTagSuffix;
			NStr::CStr KeyTagResolved;
			EYamlScalarStyle KeyScalarStyle = EYamlScalarStyle_Plain;
			bool bQuotedKey = false;

			while (*pLine == '!' || *pLine == '&')
			{
				if (*pLine == '!')
					fg_ParseYamlTag(pLine, _Context, KeyTagHandle, KeyTagSuffix, KeyTagResolved);
				else
				{
					++pLine;
					KeyAnchorName = fg_ParseYamlName(pLine, _Context);
				}

				while (*pLine == ' ' || *pLine == '\t')
					++pLine;
			}

			if (*pLine == '\'')
			{
				bQuotedKey = true;
				KeyScalarStyle = EYamlScalarStyle_SingleQuoted;

				fg_ParseYamlSingleQuotedScalar(Key, pLine, _Context);
			}
			else if (*pLine == '"')
			{
				bQuotedKey = true;
				KeyScalarStyle = EYamlScalarStyle_DoubleQuoted;

				fg_ParseYamlDoubleQuotedScalar(Key, pLine, _Context);
			}
			else if (*pLine == '*')
			{
				if (!KeyAnchorName.f_IsEmpty() || !KeyTagResolved.f_IsEmpty())
					fg_ThrowYamlParseError(_Context, "YAML alias node must not specify properties", pKeyStart);

				++pLine;
				KeyAliasName = fg_ParseYamlName(pLine, _Context);

				auto *pAnchor = fg_FindAnchor(_Anchors, KeyAliasName);
				if (!pAnchor)
					fg_ThrowYamlParseError(_Context, "Unknown YAML alias", pKeyStart);

				if (pAnchor->m_bOpen)
					fg_ThrowYamlParseError(_Context, "cyclic alias not supported", pKeyStart);

				if (!pAnchor->m_Value.f_IsString())
					fg_ThrowYamlParseError(_Context, "YAML mapping key must be a string", pKeyStart);

				Key = pAnchor->m_Value.f_String();
				bQuotedKey = true;
			}
			else
			{
				if (bExplicitKey && (*pLine == '[' || *pLine == '{' || (*pLine == '-' && fg_IsYamlSeparation(pLine[1]))))
					fg_ThrowYamlParseError(_Context, "complex YAML keys not supported", pLine);

				auto pKeyTextStart = pLine;
				while (*pLine && *pLine != '\r' && *pLine != '\n')
				{
					if (*pLine == ':' && fg_IsYamlSeparation(pLine[1]))
						break;
					++pLine;
				}

				Key = fg_MakeYamlTrimmedString(pKeyTextStart, pLine);
			}

			while (*pLine == ' ' || *pLine == '\t')
				++pLine;

			if (bExplicitKey && (*pLine == '\r' || *pLine == '\n'))
			{
				fg_ConsumeYamlLineEnd(pLine, _Context);
				fg_SkipYamlBlockBlankLines(pLine, _Context, LeadingComment, _Indent);

				if (fg_GetYamlLineIndent(pLine, _Context) != _Indent)
					break;

				pLine += _Indent;

				while (*pLine == ' ' || *pLine == '\t')
					++pLine;
			}

			if (*pLine != ':' || !fg_IsYamlSeparation(pLine[1]))
				break;

			if (!KeyTagResolved.f_IsEmpty())
			{
				tf_CValue KeyValue;
				KeyValue = Key;

				fg_ApplyYamlTag(KeyValue, KeyTagResolved, Key);

				if (!KeyValue.f_IsString())
					fg_ThrowYamlParseError(_Context, "YAML mapping key must be a string", pKeyStart);

				Key = KeyValue.f_String();
				bQuotedKey = true;
			}

			if (!KeyAnchorName.f_IsEmpty())
			{
				auto &Anchor = fg_AddAnchor(_Anchors, KeyAnchorName);
				Anchor.m_Value = Key;
				Anchor.m_bOpen = false;
			}

			fg_ValidateYamlMappingKeyString<tf_CValue>(Key, bQuotedKey, _Context, pKeyStart);

			if constexpr (!tf_CParseContext::mc_bAllowDuplicateKeys)
			{
				if (o_Value.f_Object().f_GetMember(Key))
					fg_ThrowYamlParseError(_Context, "Duplicate YAML mapping key", pKeyStart);
			}

			pParse = pLine + 1;
			auto &Entry = o_Value.f_Object().f_CreateMemberEntry(Key);
			pLastValue = &Entry.f_Value();

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (!KeyAnchorName.f_IsEmpty())
					Entry.f_KeyYaml().f_SetAnchor(fg_Move(KeyAnchorName));

				if (!KeyAliasName.f_IsEmpty())
					Entry.f_KeyYaml().f_SetAlias(fg_Move(KeyAliasName));

				if (!KeyTagHandle.f_IsEmpty() || !KeyTagResolved.f_IsEmpty())
					Entry.f_KeyYaml().f_SetTag(fg_Move(KeyTagHandle), fg_Move(KeyTagSuffix), fg_Move(KeyTagResolved));

				Entry.f_KeyYaml().f_SetScalarStyle(KeyScalarStyle);

				if (!LeadingComment.f_IsEmpty())
				{
					fg_SetYamlKeyLeadingComment<decltype(Entry), tf_CParseContext>(Entry, fg_TempCopy(LeadingComment));
					fg_SetYamlValueLeadingComment<tf_CValue, tf_CParseContext>(Entry.f_Value(), fg_Move(LeadingComment));
				}
			}

			auto pCommentStart = pParse;
			while (*pParse == ' ' || *pParse == '\t')
				++pParse;

			if (*pParse == '#')
			{
				pParse = pCommentStart;

				CMetadataString KeyLineComment;
				fg_ConsumeYamlLineEnd(pParse, _Context, KeyLineComment);

				if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
				{
					if (!KeyLineComment.f_IsEmpty())
						fg_SetYamlKeyLineComment<decltype(Entry), tf_CParseContext>(Entry, fg_Move(KeyLineComment));
				}

				CMetadataString LeadingComment;
				fg_SkipYamlBlockBlankLines(pParse, _Context, LeadingComment, _Indent + 2);

				auto nValueIndent = *pParse ? fg_GetYamlLineIndent(pParse, _Context) : 0;
				if (!*pParse || nValueIndent <= _Indent)
					Entry.f_Value() = nullptr;
				else
					fg_ParseYamlBlockNode(Entry.f_Value(), pParse, _Context, _Anchors, nValueIndent);

				if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
					fg_AttachYamlLeadingCommentToFirstChildOrValue<tf_CValue, tf_CParseContext>(Entry.f_Value(), fg_Move(LeadingComment));
			}
			else
				fg_ParseYamlInlineOrNestedBlockValue(Entry.f_Value(), pParse, _Context, _Anchors, _Indent);
		}
	}

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_ParseYamlBlockNode(tf_CValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context, TCYamlAnchors<tf_CValue> &_Anchors, umint _Indent, bool _bStandaloneNode)
	{
		using CMetadataString = TCConditional<tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata, NStr::CStr, CEmpty>;

		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		if constexpr (!tf_CParseContext::mc_bAllowBlockStyle)
			fg_ThrowYamlParseError(_Context, "Block-style YAML is not allowed in this context", pParse);

		CMetadataString LeadingComment;
		auto pBeforeLeadingComments = pParse;
		fg_SkipYamlBlockBlankLines(pParse, _Context, LeadingComment, _Indent);

		auto nIndent = fg_GetYamlLineIndent(pParse, _Context);
		if (nIndent < _Indent)
		{
			if (!_bStandaloneNode || pBeforeLeadingComments != pParse)
				_Indent = nIndent;
			else
				fg_ThrowYamlParseError(_Context, "Expected indented YAML block node", pParse);
		}

		auto pLine = pParse + nIndent;
		if (pLine[0] == '-' && (pLine[1] == ' ' || pLine[1] == '\t' || pLine[1] == '\r' || pLine[1] == '\n' || pLine[1] == 0))
			fg_ParseYamlBlockSequence(o_Value, pParse, _Context, _Anchors, nIndent);
		else if (pLine[0] == '{' || pLine[0] == '[')
		{
			pParse = pLine;
			fg_ParseYamlInlineOrNestedBlockValue(o_Value, pParse, _Context, _Anchors, _Indent);
		}
		else if
		(
			[&]
			{
				for (auto pLineScan = pLine; *pLineScan && *pLineScan != '\r' && *pLineScan != '\n'; ++pLineScan)
				{
					if (*pLineScan == '\'' || *pLineScan == '"')
					{
						auto Quote = *pLineScan++;
						while (*pLineScan && *pLineScan != '\r' && *pLineScan != '\n')
						{
							if (*pLineScan == '\\' && Quote == '"' && pLineScan[1])
								pLineScan += 2;
							else if (*pLineScan++ == Quote)
								break;
						}
						if (!*pLineScan || *pLineScan == '\r' || *pLineScan == '\n')
							break;
					}
					if (*pLineScan == ':' && fg_IsYamlSeparation(pLineScan[1]))
						return true;
				}
				return false;
			}()
		)
		{
			fg_ParseYamlBlockMapping(o_Value, pParse, _Context, _Anchors, nIndent);
		}
		else
		{
			pParse = pLine;

			fg_ParseYamlInlineOrNestedBlockValue(o_Value, pParse, _Context, _Anchors, _Indent);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata && requires { o_Value.f_EType(); o_Value.f_UserType(); })
			{
				if (_bStandaloneNode && o_Value.f_EType() == EEJsonType_UserType)
					o_Value.f_Yaml().f_SetNodeStyle(EYamlNodeStyle_Block);
			}

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (_bStandaloneNode && (o_Value.f_IsObject() || o_Value.f_IsArray()) && o_Value.f_Yaml().f_HasTag())
					o_Value.f_Yaml().f_SetNodeStyle(EYamlNodeStyle_Block);
			}
		}

		if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			fg_AttachYamlLeadingCommentToFirstChildOrValue<tf_CValue, tf_CParseContext>(o_Value, fg_Move(LeadingComment));

	}
}
