// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NEncoding::NYaml
{
	template <typename tf_CValue, typename tf_CParseContext>
	void fg_ParseYamlFlowSequence(tf_CValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context, TCYamlAnchors<tf_CValue> &_Anchors)
	{
		using CMetadataString = TCConditional<tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata, NStr::CStr, CEmpty>;

		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		if constexpr (!tf_CParseContext::mc_bAllowFlowStyle)
			fg_ThrowYamlParseError(_Context, "Flow-style YAML is not allowed in this context", pParse);

		++pParse;

		++_Context.m_nFlowDepth;
		++_Context.m_ObjectArrayParseDepth;
		auto DepthCleanup = g_OnScopeExit / [&]
			{
				--_Context.m_nFlowDepth;
				--_Context.m_ObjectArrayParseDepth;
			}
		;

		o_Value.f_SetType(EJsonType_Array);

		if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			o_Value.f_Yaml().f_SetNodeStyle(EYamlNodeStyle_Flow);

		CMetadataString PendingLeadingComment;
		fg_ParseYamlWhiteSpaceAndComments(pParse, _Context, PendingLeadingComment);

		while (*pParse && *pParse != ']')
		{
			auto &Child = o_Value.f_Insert();

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (!PendingLeadingComment.f_IsEmpty())
					Child.f_Yaml().f_SetLeadingComment(fg_Move(PendingLeadingComment));
			}

			fg_ParseYamlNode(Child, pParse, _Context, _Anchors);

			CMetadataString PostComment;
			fg_ParseYamlWhiteSpaceAndComments(pParse, _Context, PostComment);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				fg_NormalizeYamlLineCommentForStorage(PostComment);

				if (!PostComment.f_IsEmpty())
					Child.f_Yaml().f_SetLineComment(fg_Move(PostComment));
			}

			if (*pParse == ',')
			{
				++pParse;
				fg_ParseYamlWhiteSpaceAndComments(pParse, _Context, PendingLeadingComment);

				continue;
			}

			break;
		}

		if (*pParse != ']')
			fg_ThrowYamlParseError(_Context, "Missing closing ] for YAML sequence", pParse);

		++pParse;
	}

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_ParseYamlFlowMapping(tf_CValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context, TCYamlAnchors<tf_CValue> &_Anchors)
	{
		using CMetadataString = TCConditional<tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata, NStr::CStr, CEmpty>;

		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		if constexpr (!tf_CParseContext::mc_bAllowFlowStyle)
			fg_ThrowYamlParseError(_Context, "Flow-style YAML is not allowed in this context", pParse);

		++pParse;

		++_Context.m_nFlowDepth;
		++_Context.m_ObjectArrayParseDepth;
		auto DepthCleanup = g_OnScopeExit / [&]
			{
				--_Context.m_nFlowDepth;
				--_Context.m_ObjectArrayParseDepth;
			}
		;

		o_Value.f_SetType(EJsonType_Object);

		if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			o_Value.f_Yaml().f_SetNodeStyle(EYamlNodeStyle_Flow);

		CMetadataString PendingLeadingComment;
		fg_ParseYamlWhiteSpaceAndComments(pParse, _Context, PendingLeadingComment);

		while (*pParse && *pParse != '}')
		{
			auto pKeyStart = pParse;
			if (*pParse == '?' && fg_IsYamlSeparation(pParse[1]))
				fg_ThrowYamlParseError(_Context, "complex YAML keys not supported", pParse);

			NStr::CStr Key;
			bool bQuotedKey = false;
			NStr::CStr KeyAnchorName;
			NStr::CStr KeyAliasName;
			NStr::CStr KeyTagHandle;
			NStr::CStr KeyTagSuffix;
			NStr::CStr KeyTagResolved;
			EYamlScalarStyle KeyScalarStyle = EYamlScalarStyle_Plain;

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
				auto pKeyTextStart = pParse;

				while (*pParse && *pParse != '}' && *pParse != ']' && *pParse != ',' && *pParse != '[' && *pParse != '{')
				{
					if (*pParse == ':' && fg_IsYamlSeparation(pParse[1]))
						break;
					++pParse;
				}

				Key = fg_MakeYamlTrimmedString(pKeyTextStart, pParse);
			}

			fg_ParseYamlFlowWhiteSpaceAndCommentsNoMetadata(pParse);

			if (*pParse != ':' || (!bQuotedKey && !fg_IsYamlSeparation(pParse[1])))
				fg_ThrowYamlParseError(_Context, "Expected ':' after YAML mapping key", pParse);

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

			++pParse;

			fg_ParseYamlFlowWhiteSpaceAndCommentsNoMetadata(pParse);

			auto &Entry = o_Value.f_Object().f_CreateMemberEntry(fg_Move(Key));
			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (!PendingLeadingComment.f_IsEmpty())
					Entry.f_KeyYaml().f_SetLeadingComment(fg_Move(PendingLeadingComment));

				if (!KeyAnchorName.f_IsEmpty())
					Entry.f_KeyYaml().f_SetAnchor(fg_Move(KeyAnchorName));

				if (!KeyAliasName.f_IsEmpty())
					Entry.f_KeyYaml().f_SetAlias(fg_Move(KeyAliasName));

				if (!KeyTagHandle.f_IsEmpty() || !KeyTagResolved.f_IsEmpty())
					Entry.f_KeyYaml().f_SetTag(fg_Move(KeyTagHandle), fg_Move(KeyTagSuffix), fg_Move(KeyTagResolved));

				Entry.f_KeyYaml().f_SetScalarStyle(KeyScalarStyle);
			}

			{
				if (*pParse == ',' || *pParse == '}')
					Entry.f_Value() = nullptr;
				else
					fg_ParseYamlNode(Entry.f_Value(), pParse, _Context, _Anchors);
			}

			CMetadataString PostComment;
			fg_ParseYamlWhiteSpaceAndComments(pParse, _Context, PostComment);
			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				fg_NormalizeYamlLineCommentForStorage(PostComment);

				if (!PostComment.f_IsEmpty())
					Entry.f_Value().f_Yaml().f_SetLineComment(fg_Move(PostComment));
			}

			if (*pParse == ',')
			{
				++pParse;
				fg_ParseYamlWhiteSpaceAndComments(pParse, _Context, PendingLeadingComment);

				continue;
			}

			break;
		}

		if (*pParse != '}')
			fg_ThrowYamlParseError(_Context, "Missing closing } for YAML mapping", pParse);

		++pParse;
	}

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_ParseYamlNode(tf_CValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context, TCYamlAnchors<tf_CValue> &_Anchors)
	{
		using CMetadataString = TCConditional<tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata, NStr::CStr, CEmpty>;

		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		bool bSuccessful = false;
		if constexpr (tf_CParseContext::mc_bCustomParse)
			_Context.template f_PreParse<tf_CParseContext>(o_Value, pParse);

		auto CustomParseCleanup = g_OnScopeExitWithException / [&]
			{
				if constexpr (tf_CParseContext::mc_bCustomParse)
				{
					if (bSuccessful)
						_Context.template f_ParseAfterValue<tf_CParseContext>(o_Value, pParse);
					_Context.template f_PostParse<tf_CParseContext>(o_Value, pParse);
				}
			}
		;

		CMetadataString LeadingComment;
		fg_ParseYamlWhiteSpaceAndComments(pParse, _Context, LeadingComment);

		if constexpr (tf_CParseContext::mc_bAllowBlockStyle)
		{
			if (fg_AtYamlLineStart(pParse, _Context.m_pStartParse))
			{
				auto pLine = pParse + fg_GetYamlLineIndent(pParse, _Context);
				bool bHasColonOnLine = false;

				for (auto pColonScan = pLine; *pColonScan && *pColonScan != '\r' && *pColonScan != '\n'; ++pColonScan)
				{
					if (*pColonScan == '#' && (pColonScan == pLine || pColonScan[-1] == ' ' || pColonScan[-1] == '\t'))
						break;

					if (*pColonScan == '\'' || *pColonScan == '"')
					{
						auto Quote = *pColonScan++;

						while (*pColonScan && *pColonScan != '\r' && *pColonScan != '\n')
						{
							if (*pColonScan == '\\' && Quote == '"' && pColonScan[1])
								pColonScan += 2;
							else if (*pColonScan++ == Quote)
								break;
						}

						if (!*pColonScan || *pColonScan == '\r' || *pColonScan == '\n')
							break;
					}

					if (*pColonScan == ':' && fg_IsYamlSeparation(pColonScan[1]))
					{
						bHasColonOnLine = true;
						break;
					}
				}

				bool bPrefixedFlowNode = false;
				bool bPrefixedBlockNode = false;

				if (*pLine == '!' || *pLine == '&')
				{
					auto pAfterProperties = pLine;
					while (*pAfterProperties == '!' || *pAfterProperties == '&')
					{
						if (*pAfterProperties == '!')
						{
							++pAfterProperties;

							if (*pAfterProperties == '<')
							{
								while (*pAfterProperties && *pAfterProperties != '>' && *pAfterProperties != '\r' && *pAfterProperties != '\n')
									++pAfterProperties;

								if (*pAfterProperties == '>')
									++pAfterProperties;
							}
							else
							{
								while (*pAfterProperties && !fg_IsYamlSeparation(*pAfterProperties))
									++pAfterProperties;
							}
						}
						else
						{
							++pAfterProperties;

							while (fg_IsNameChar(*pAfterProperties))
								++pAfterProperties;
						}

						while (*pAfterProperties == ' ' || *pAfterProperties == '\t')
							++pAfterProperties;
					}

					bPrefixedFlowNode = *pAfterProperties == '{' || *pAfterProperties == '[';
					bPrefixedBlockNode = (*pAfterProperties == '-' && fg_IsYamlSeparation(pAfterProperties[1])) || *pAfterProperties == '|' || *pAfterProperties == '>';
				}

				if
				(
					(pLine[0] == '-' && fg_IsYamlSeparation(pLine[1]))
					|| pLine[0] == '|'
					|| pLine[0] == '>'
					|| bPrefixedBlockNode
					|| (*pLine && *pLine != '{' && *pLine != '[' && *pLine != '*' && !bPrefixedFlowNode && bHasColonOnLine)
				)
				{
					fg_ParseYamlBlockNode(o_Value, pParse, _Context, _Anchors, fg_GetYamlLineIndent(pParse, _Context));

					if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
					{
						if (!LeadingComment.f_IsEmpty())
							o_Value.f_Yaml().f_SetLeadingComment(fg_Move(LeadingComment));
					}

					bSuccessful = true;
					return;
				}
			}
		}
		else
		{
			if (fg_AtYamlLineStart(pParse, _Context.m_pStartParse))
			{
				auto pLine = pParse + fg_GetYamlLineIndent(pParse, _Context);
				if (*pLine == '|' || *pLine == '>')
					fg_ThrowYamlParseError(_Context, "Block-style YAML is not allowed in this context", pParse);

				if (*pLine && *pLine != '{' && *pLine != '[' && *pLine != '!' && *pLine != '&')
				{
					if (*pLine == '-' && fg_IsYamlSeparation(pLine[1]))
						fg_ThrowYamlParseError(_Context, "Block-style YAML is not allowed in this context", pParse);

					for (auto pColonScan = pLine; *pColonScan && *pColonScan != '\r' && *pColonScan != '\n'; ++pColonScan)
					{
						if (*pColonScan == ':' && fg_IsYamlSeparation(pColonScan[1]))
							fg_ThrowYamlParseError(_Context, "Block-style YAML is not allowed in this context", pParse);
					}
				}
			}
		}

		NStr::CStr AnchorName;
		NStr::CStr TagHandle;
		NStr::CStr TagSuffix;
		NStr::CStr TagResolved;
		NStr::CStr RawScalar;
		EYamlScalarStyle RecordedScalarStyle = EYamlScalarStyle_Unspecified;

		while (*pParse == '!' || *pParse == '&')
		{
			if (*pParse == '!')
				fg_ParseYamlTag(pParse, _Context, TagHandle, TagSuffix, TagResolved);
			else
			{
				++pParse;
				AnchorName = fg_ParseYamlName(pParse, _Context);
			}

			while (*pParse == ' ' || *pParse == '\t')
				++pParse;
		}

		if (*pParse == '*')
		{
			if (!AnchorName.f_IsEmpty() || !TagResolved.f_IsEmpty())
				fg_ThrowYamlParseError(_Context, "YAML alias node must not specify properties", pParse);

			++pParse;
			auto AliasName = fg_ParseYamlName(pParse, _Context);
			auto *pAnchor = fg_FindAnchor(_Anchors, AliasName);

			if (!pAnchor)
				fg_ThrowYamlParseError(_Context, "Unknown YAML alias", pParse);

			if (pAnchor->m_bOpen)
				fg_ThrowYamlParseError(_Context, "cyclic alias not supported", pParse);

			o_Value = pAnchor->m_Value;

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				o_Value.f_Yaml().f_ResetYamlMetadata();
				o_Value.f_Yaml().f_SetAlias(fg_Move(AliasName));

				if (!LeadingComment.f_IsEmpty())
					o_Value.f_Yaml().f_SetLeadingComment(fg_Move(LeadingComment));
			}

			bSuccessful = true;
			return;
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

		if (*pParse == '\r' || *pParse == '\n' || *pParse == '#')
		{
			if constexpr (!tf_CParseContext::mc_bAllowBlockStyle)
				fg_ThrowYamlParseError(_Context, "Block-style YAML is not allowed in this context", pParse);

			fg_ConsumeYamlLineEnd(pParse, _Context);
			fg_ParseYamlBlockNode(o_Value, pParse, _Context, _Anchors, fg_GetYamlLineIndent(pParse, _Context));
			fg_ApplyYamlTag(o_Value, TagResolved, RawScalar);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				if (!AnchorName.f_IsEmpty())
					o_Value.f_Yaml().f_SetAnchor(fg_Move(AnchorName));

				if (!TagHandle.f_IsEmpty() || !TagResolved.f_IsEmpty())
					o_Value.f_Yaml().f_SetTag(fg_Move(TagHandle), fg_Move(TagSuffix), fg_Move(TagResolved));

				if (!LeadingComment.f_IsEmpty())
					o_Value.f_Yaml().f_SetLeadingComment(fg_Move(LeadingComment));
			}

			bSuccessful = true;
			return;
		}

		if (*pParse == '{')
			fg_ParseYamlFlowMapping(o_Value, pParse, _Context, _Anchors);
		else if (*pParse == '[')
			fg_ParseYamlFlowSequence(o_Value, pParse, _Context, _Anchors);
		else if (*pParse == '\'')
		{
			NStr::CStr String;
			fg_ParseYamlSingleQuotedScalar(String, pParse, _Context);

			if (!TagResolved.f_IsEmpty())
				RawScalar = String;
			o_Value = fg_Move(String);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				RecordedScalarStyle = EYamlScalarStyle_SingleQuoted;
				o_Value.f_Yaml().f_SetScalarStyle(RecordedScalarStyle);
			}
		}
		else if (*pParse == '"')
		{
			NStr::CStr String;
			fg_ParseYamlDoubleQuotedScalar(String, pParse, _Context);

			if (!TagResolved.f_IsEmpty())
				RawScalar = String;
			o_Value = fg_Move(String);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				RecordedScalarStyle = EYamlScalarStyle_DoubleQuoted;
				o_Value.f_Yaml().f_SetScalarStyle(RecordedScalarStyle);
			}
		}
		else
		{
			NStr::CStr Token;
			auto pTokenStart = pParse;
			bool bNeedsFoldedScalar = false;
			while (*pParse && *pParse != ',' && *pParse != ']' && *pParse != '}')
			{
				if (*pParse == '\r' || *pParse == '\n')
				{
					bNeedsFoldedScalar = true;
					break;
				}

				if (*pParse == '#' && (pParse == pTokenStart || pParse[-1] == ' ' || pParse[-1] == '\t'))
					break;

				if (*pParse == '[' || *pParse == '{')
					fg_ThrowYamlParseError(_Context, "YAML flow plain scalar cannot contain a flow indicator", pParse);

				if (*pParse == ':' && fg_IsYamlSeparation(pParse[1]))
					fg_ThrowYamlParseError(_Context, "YAML flow plain scalar cannot contain a mapping separator", pParse);

				++pParse;
			}

			if (!bNeedsFoldedScalar)
			{
				auto TokenPtr = fg_MakeYamlTrimmedStringPtr(pTokenStart, pParse);
				if (TokenPtr.f_IsEmpty())
				{
					o_Value = nullptr;
					if (!TagResolved.f_IsEmpty())
						RawScalar = TokenPtr;
					goto l_ParsedValue;
				}

				if (!TagResolved.f_IsEmpty())
				{
					Token = TokenPtr;
					RawScalar = Token;
					o_Value = Token;
				}
				else
					fg_SetYamlPlainScalar(o_Value, TokenPtr);

				if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
				{
					RecordedScalarStyle = EYamlScalarStyle_Plain;
					o_Value.f_Yaml().f_SetScalarStyle(RecordedScalarStyle);
				}

				goto l_ParsedValue;
			}
			else
			{
				pParse = pTokenStart;
				NStr::CStr::CAppender Appender(Token);
				bool bHasTokenOutput = false;
				ch8 LastTokenChar = 0;

				auto fAppendTokenRange = [&] (uch8 const *_pStart, uch8 const *_pEnd)
					{
						if (_pStart == _pEnd)
							return;

						Appender.f_AddString(reinterpret_cast<ch8 const *>(_pStart), _pEnd - _pStart);
						bHasTokenOutput = true;
						LastTokenChar = ch8(_pEnd[-1]);
					}
				;

				auto fAppendTokenChar = [&] (uch8 _Character)
					{
						Appender += _Character;
						bHasTokenOutput = true;
						LastTokenChar = ch8(_Character);
					}
				;

				while (*pParse && *pParse != ',' && *pParse != ']' && *pParse != '}')
				{
					auto pRangeStart = pParse;
					while
					(
						*pParse
						&& *pParse != ','
						&& *pParse != ']'
						&& *pParse != '}'
						&& *pParse != '\r'
						&& *pParse != '\n'
						&& *pParse != '#'
						&& *pParse != '['
						&& *pParse != '{'
						&& *pParse != ':'
					)
					{
						++pParse;
					}

					fAppendTokenRange(pRangeStart, pParse);

					if (!*pParse || *pParse == ',' || *pParse == ']' || *pParse == '}')
						break;

					if (*pParse == '\r' || *pParse == '\n')
					{
						auto pNextLine = pParse;
						if (*pNextLine == '\r')
							++pNextLine;

						if (*pNextLine == '\n')
							++pNextLine;

						if
						(
							(pNextLine[0] == '-' && pNextLine[1] == '-' && pNextLine[2] == '-')
							|| (pNextLine[0] == '.' && pNextLine[1] == '.' && pNextLine[2] == '.')
						)
						{
							if (fg_IsYamlSeparation(pNextLine[3]))
								break;
						}

						if (bHasTokenOutput && LastTokenChar != ' ')
							fAppendTokenChar(' ');

						pParse = pNextLine;
						while (*pParse == ' ' || *pParse == '\t')
							++pParse;

						continue;
					}

					if (*pParse == '#' && (pParse == pTokenStart || pParse[-1] == ' ' || pParse[-1] == '\t'))
						break;

					if (*pParse == '[' || *pParse == '{')
						fg_ThrowYamlParseError(_Context, "YAML flow plain scalar cannot contain a flow indicator", pParse);

					if (*pParse == ':' && fg_IsYamlSeparation(pParse[1]))
						fg_ThrowYamlParseError(_Context, "YAML flow plain scalar cannot contain a mapping separator", pParse);

					fAppendTokenChar(*pParse++);
				}
			}

			if (bNeedsFoldedScalar)
				Token = Token.f_Trim();

			if (Token.f_IsEmpty())
			{
				o_Value = nullptr;

				if (!TagResolved.f_IsEmpty())
					RawScalar = Token;

				goto l_ParsedValue;
			}

			if (!TagResolved.f_IsEmpty())
				RawScalar = Token;

			if (!TagResolved.f_IsEmpty())
				o_Value = Token;
			else
				fg_SetYamlPlainScalar(o_Value, Token);

			if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
			{
				RecordedScalarStyle = EYamlScalarStyle_Plain;
				o_Value.f_Yaml().f_SetScalarStyle(RecordedScalarStyle);
			}
		}

	l_ParsedValue:
		fg_ApplyYamlTag(o_Value, TagResolved, RawScalar);

		if constexpr (tf_CValue::mc_bPreserveYamlMetadata && tf_CParseContext::mc_bRecordYamlMetadata)
		{
			if (!AnchorName.f_IsEmpty())
				o_Value.f_Yaml().f_SetAnchor(fg_Move(AnchorName));

			if (RecordedScalarStyle != EYamlScalarStyle_Unspecified)
				o_Value.f_Yaml().f_SetScalarStyle(RecordedScalarStyle);

			if (!TagHandle.f_IsEmpty() || !TagResolved.f_IsEmpty())
				o_Value.f_Yaml().f_SetTag(fg_Move(TagHandle), fg_Move(TagSuffix), fg_Move(TagResolved));

			if (!LeadingComment.f_IsEmpty())
				o_Value.f_Yaml().f_SetLeadingComment(fg_Move(LeadingComment));
		}

		bSuccessful = true;
	}

}
