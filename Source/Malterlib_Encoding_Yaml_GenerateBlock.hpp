// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NEncoding::NYaml
{
	template <typename tf_CStr>
	void fg_AddYamlBlockIndent(tf_CStr &o_String, umint _Depth, ch8 const *_pPrettySeparator)
	{
		if (_pPrettySeparator[0] == ' ' && _pPrettySeparator[1] == ' ' && _pPrettySeparator[2] == 0)
		{
			static constexpr ch8 c_Spaces[] = "                                ";
			umint nSpaces = _Depth * 2;
			while (nSpaces > 0)
			{
				auto nAdd = fg_Min(nSpaces, sizeof(c_Spaces) - 1);
				o_String.f_AddString(c_Spaces, nAdd);
				nSpaces -= nAdd;
			}
		}
		else
		{
			for (umint i = 0; i < _Depth; ++i)
				o_String += _pPrettySeparator;
		}
	}

	template <typename tf_CStr>
	void fg_AddYamlBlockIndentHint(tf_CStr &o_String, smint _IndentHint)
	{
		DMibFastCheck(_IndentHint <= 9);
		static constexpr ch8 c_Spaces[] = "         ";
		if (_IndentHint > 0)
			o_String.f_AddString(c_Spaces, _IndentHint);
	}

	template <typename tf_CStr>
	void fg_GenerateYamlBlockComment(tf_CStr &o_String, NStr::CStr const &_Comment, umint _Depth, ch8 const *_pPrettySeparator)
	{
		auto pComment = _Comment.f_GetStr();
		while (*pComment)
		{
			if (*pComment != ' ' && *pComment != '\t' && *pComment != '\r' && *pComment != '\n')
				fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);

			auto pCommentLineStart = pComment;
			NStr::fg_ParseToEndOfLine(pComment);

			o_String.f_AddString(pCommentLineStart, pComment - pCommentLineStart);
			o_String += '\n';

			NStr::fg_ParseEndOfLine(pComment);
		}
	}

	template <typename tf_CJson>
	bool fg_YamlStringNeedsBlockScalar(tf_CJson const &_Value)
	{
		if (!_Value.f_IsString())
			return false;

		if (_Value.f_String().f_FindChar('\n') >= 0)
			return true;

		if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
			return _Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Literal || _Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Folded;
		else
			return false;
	}

	template <typename tf_CJson>
	bool fg_YamlUserTypeStoredPayloadIsObjectOrArray(tf_CJson const &_Value)
	{
		if constexpr (requires (tf_CJson const &Value) { Value.f_EType(); Value.f_UserType(); })
		{
			if (_Value.f_EType() == EEJsonType_UserType)
			{
				auto const &Payload = _Value.f_UserType().m_Value;
				if (Payload.f_IsArray())
					return true;

				if (!Payload.f_IsObject())
					return false;

				auto iMember = Payload.f_Object().f_OrderedIterator();
				if (!iMember)
					return true;

				auto const &FirstName = iMember->f_Name();
				++iMember;
				if (!iMember)
				{
					if (FirstName == CEJsonConstStrings::mc_Escape)
						return true;
					if (FirstName == CEJsonConstStrings::mc_Date || FirstName == CEJsonConstStrings::mc_Binary)
						return false;
					return true;
				}

				auto const &SecondName = iMember->f_Name();
				++iMember;
				if
				(
					!iMember
					&&
					(
						(FirstName == CEJsonConstStrings::mc_Type && SecondName == CEJsonConstStrings::mc_Value)
						|| (FirstName == CEJsonConstStrings::mc_Value && SecondName == CEJsonConstStrings::mc_Type)
					)
				)
				{
					return false;
				}

				return true;
			}
		}

		return false;
	}

	template <typename tf_CJson>
	bool fg_YamlUserTypeStoredPayloadHasBlockStyle(tf_CJson const &_Value)
	{
		if constexpr (tf_CJson::mc_bPreserveYamlMetadata && requires (tf_CJson const &Value) { Value.f_EType(); Value.f_UserType(); })
		{
			if (fg_YamlUserTypeStoredPayloadIsObjectOrArray(_Value))
			{
				return
					_Value.f_Yaml().f_NodeStyle() == EYamlNodeStyle_Block
					|| _Value.f_UserType().m_Value.f_Yaml().f_NodeStyle() == EYamlNodeStyle_Block
				;
			}
		}

		return false;
	}

	template <typename tf_CJson>
	bool fg_YamlValueNeedsBlockLine(tf_CJson const &_Value)
	{
		if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
		{
			if (!_Value.f_Yaml().f_Alias().f_IsEmpty())
				return false;

			if ((_Value.f_IsObject() || _Value.f_IsArray()) && _Value.f_Yaml().f_NodeStyle() == EYamlNodeStyle_Flow)
				return false;

			if ((_Value.f_IsObject() || _Value.f_IsArray()) && _Value.f_Yaml().f_NodeStyle() == EYamlNodeStyle_Block)
				return true;

			if (_Value.f_IsString() && (_Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Literal || _Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Folded))
				return true;

			if (fg_YamlUserTypeStoredPayloadHasBlockStyle(_Value))
				return true;

			if (_Value.f_Yaml().f_HasAnchor() || (_Value.f_Yaml().f_HasTag() && !_Value.f_IsObject() && !_Value.f_IsArray()))
				return false;

			if constexpr (requires (tf_CJson const &Value) { Value.f_EType(); Value.f_Binary(); })
			{
				if (_Value.f_EType() == EEJsonType_Binary && (_Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Literal || _Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Folded))
					return true;
			}
		}

		return _Value.f_IsObject() || _Value.f_IsArray() || (_Value.f_IsString() && _Value.f_String().f_FindChar('\n') >= 0);
	}

	template <typename tf_CStr, typename tf_CJson, typename tf_CGenerationState>
	void fg_GenerateYamlBlockNode(tf_CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags, tf_CGenerationState *o_pState);

	inline ch8 fg_GetYamlDefaultChompIndicator(NStr::CStr const &_Text)
	{
		if (_Text.f_IsEmpty())
			return '-';

		umint nLineBreaks = 0;

		auto pText = _Text.f_GetStr();
		for (auto iText = _Text.f_GetLen(); iText > 0; --iText)
		{
			if (pText[iText - 1] != '\n' && pText[iText - 1] != '\r')
				break;

			++nLineBreaks;
		}

		if (!nLineBreaks)
			return '-';

		if (nLineBreaks > 1)
			return '+';

		return 0;
	}

	template <typename tf_CStr, typename tf_CJson>
	void fg_GenerateYamlBlockScalar(tf_CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator)
	{
		if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
		{
			if (_Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Folded)
				o_String += '>';
			else
				o_String += '|';

			bool bEndsWithLineBreak =
				!_Value.f_String().f_IsEmpty()
				&& (_Value.f_String()[_Value.f_String().f_GetLen() - 1] == '\n' || _Value.f_String()[_Value.f_String().f_GetLen() - 1] == '\r')
			;

			if (_Value.f_Yaml().f_ChompIndicator())
				o_String += ch8(_Value.f_Yaml().f_ChompIndicator());
			else if (!bEndsWithLineBreak)
				o_String += '-';

			auto IndentHint = _Value.f_Yaml().f_BlockIndentHint();
			if (IndentHint >= 0)
				o_String += ch8('0' + IndentHint);

			if (!_Value.f_Yaml().f_LineComment().f_IsEmpty())
				fg_GenerateYamlLineComment(o_String, _Value.f_Yaml());

			o_String += '\n';
		}
		else
		{
			o_String += '|';

			if (auto ChompIndicator = fg_GetYamlDefaultChompIndicator(_Value.f_String()))
				o_String += ChompIndicator;

			o_String += '\n';
		}

		NStr::CStr Text = _Value.f_String();
		auto pLine = Text.f_GetStr();

		auto fAddBlockScalarContentIndent = [&]
			{
				if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
				{
					auto IndentHint = _Value.f_Yaml().f_BlockIndentHint();
					if (IndentHint >= 0)
					{
						fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);
						fg_AddYamlBlockIndentHint(o_String, IndentHint);

						return;
					}
				}
				fg_AddYamlBlockIndent(o_String, _Depth + 1, _pPrettySeparator);
			}
		;

		while (*pLine)
		{
			fAddBlockScalarContentIndent();

			auto pLineStart = pLine;
			NStr::fg_ParseToEndOfLine(pLine);

			o_String.f_AddString(pLineStart, pLine - pLineStart);
			o_String += '\n';

			NStr::fg_ParseEndOfLine(pLine);
		}
	}

	template <typename tf_CStr, typename tf_CJson, typename tf_CGenerationState>
	void fg_GenerateYamlBlockSequence(tf_CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags, tf_CGenerationState *o_pState)
	{
		for (auto const &Child : _Value)
		{
			if constexpr (requires { Child.f_Yaml().f_LeadingComment(); })
			{
				if (!Child.f_Yaml().f_LeadingComment().f_IsEmpty())
					fg_GenerateYamlBlockComment(o_String, fg_YamlLeadingCommentForGeneration(Child.f_Yaml()), _Depth, _pPrettySeparator);
			}

			fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);

			o_String += "-";

			if (fg_YamlValueNeedsBlockLine(Child))
			{
				if constexpr (requires { Child.f_Yaml().f_Anchor(); })
				{
					if (Child.f_IsObject() || Child.f_IsArray())
					{
						o_String += ' ';
						fg_GenerateYamlMetadataPrefix(o_String, Child.f_Yaml(), o_pState, fg_ShouldEmitYamlTag(Child));
					}

					if
					(
						!Child.f_Yaml().f_LineComment().f_IsEmpty()
						&&
						!
						(
							Child.f_IsString()
							&& (Child.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Literal || Child.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Folded)
						)
					)
					{
						fg_GenerateYamlLineComment(o_String, Child.f_Yaml());
					}
				}

				o_String += '\n';

				fg_GenerateYamlBlockNode(o_String, Child, _Depth + 1, _pPrettySeparator, _Flags, o_pState);
			}
			else
			{
				o_String += ' ';

				fg_GenerateYamlNode(o_String, Child, _Flags, o_pState, false, false);

				if constexpr (requires { Child.f_Yaml().f_LineComment(); })
				{
					if (!Child.f_Yaml().f_LineComment().f_IsEmpty())
						fg_GenerateYamlLineComment(o_String, Child.f_Yaml());
				}

				o_String += '\n';
			}

			if constexpr (requires { Child.f_Yaml().f_TrailingComment(); })
			{
				if (!Child.f_Yaml().f_TrailingComment().f_IsEmpty())
					fg_GenerateYamlBlockComment(o_String, fg_YamlTrailingCommentForGeneration(Child.f_Yaml()), _Depth, _pPrettySeparator);
			}
		}
	}

	template <typename tf_CStr, typename tf_CJson, typename tf_CGenerationState>
	void fg_GenerateYamlBlockObject(tf_CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags, tf_CGenerationState *o_pState)
	{
		for (auto const &Child : _Value)
		{
			if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
			{
				if (!Child.f_KeyYaml().f_LeadingComment().f_IsEmpty())
					fg_GenerateYamlBlockComment(o_String, fg_YamlLeadingCommentForGeneration(Child.f_KeyYaml()), _Depth, _pPrettySeparator);
				else if (!Child.f_Value().f_Yaml().f_LeadingComment().f_IsEmpty())
					fg_GenerateYamlBlockComment(o_String, fg_YamlLeadingCommentForGeneration(Child.f_Value().f_Yaml()), _Depth, _pPrettySeparator);
			}

			fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);
			bool bConsumedKeyPosition = false;
			if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
			{
				bool bEmitKeyAlias = false;
				if (!Child.f_KeyYaml().f_Alias().f_IsEmpty())
				{
					bEmitKeyAlias = fg_ShouldEmitYamlKeyAlias(o_pState, Child.f_Name(), Child.f_KeyYaml().f_Alias());
					bConsumedKeyPosition = true;
				}

				if (bEmitKeyAlias)
				{
					o_String += '*';
					o_String += Child.f_KeyYaml().f_Alias();
				}
				else
				{
					fg_GenerateYamlMetadataPrefix(o_String, Child.f_KeyYaml(), o_pState);
					bool bTaggedPlainKey =
						Child.f_KeyYaml().f_ScalarStyle() == EYamlScalarStyle_Plain
						&& Child.f_KeyYaml().f_HasTag()
					;

					if (Child.f_KeyYaml().f_ScalarStyle() == EYamlScalarStyle_SingleQuoted && fg_IsYamlSingleQuotedSafe(Child.f_Name()))
						fg_GenerateYamlSingleQuotedString(o_String, Child.f_Name());
					else if (Child.f_KeyYaml().f_ScalarStyle() == EYamlScalarStyle_DoubleQuoted)
						fg_GenerateYamlQuotedString(o_String, Child.f_Name());
					else if (fg_IsYamlPlainSafe(Child.f_Name()) || (bTaggedPlainKey && fg_IsYamlPlainSyntaxSafe(Child.f_Name())))
						o_String += Child.f_Name();
					else
						fg_GenerateYamlQuotedString(o_String, Child.f_Name());
				}
			}
			else if (fg_IsYamlPlainSafe(Child.f_Name()))
				o_String += Child.f_Name();
			else
				fg_GenerateYamlQuotedString(o_String, Child.f_Name());

			o_String += ":";

			if (o_pState && !bConsumedKeyPosition)
				++o_pState->m_Position;

			if (fg_YamlValueNeedsBlockLine(Child.f_Value()))
			{
				bool bKeyLineComment = false;

				if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
				{
					if (!Child.f_KeyYaml().f_LineComment().f_IsEmpty())
					{
						fg_GenerateYamlLineComment(o_String, Child.f_KeyYaml());
						bKeyLineComment = true;
					}
				}

				if (Child.f_Value().f_IsString())
				{
					if (bKeyLineComment)
					{
						o_String += '\n';
						fg_AddYamlBlockIndent(o_String, _Depth + 1, _pPrettySeparator);

						if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
						{
							if (Child.f_Value().f_Yaml().f_HasAnchor() || Child.f_Value().f_Yaml().f_HasTag())
								fg_GenerateYamlMetadataPrefix(o_String, Child.f_Value().f_Yaml(), o_pState, fg_ShouldEmitYamlTag(Child.f_Value()));
						}

						fg_GenerateYamlBlockScalar(o_String, Child.f_Value(), _Depth + 1, _pPrettySeparator);
					}
					else
					{
						o_String += ' ';

						if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
						{
							if (Child.f_Value().f_Yaml().f_HasAnchor() || Child.f_Value().f_Yaml().f_HasTag())
								fg_GenerateYamlMetadataPrefix(o_String, Child.f_Value().f_Yaml(), o_pState, fg_ShouldEmitYamlTag(Child.f_Value()));
						}

						fg_GenerateYamlBlockScalar(o_String, Child.f_Value(), _Depth, _pPrettySeparator);
					}
				}
				else
				{
					if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
					{
						if
						(
							(Child.f_Value().f_IsObject() || Child.f_Value().f_IsArray())
							&& Child.f_Value().f_Yaml().f_NodeStyle() == EYamlNodeStyle_Block
							&& Child.f_Value().f_Yaml().f_HasTag()
						)
						{
							o_String += '\n';

							fg_AddYamlBlockIndent(o_String, _Depth + 1, _pPrettySeparator);
							fg_GenerateYamlMetadataPrefix(o_String, Child.f_Value().f_Yaml(), o_pState, fg_ShouldEmitYamlTag(Child.f_Value()), false);

							if (!Child.f_Value().f_Yaml().f_LineComment().f_IsEmpty())
								fg_GenerateYamlLineComment(o_String, Child.f_Value().f_Yaml());

							o_String += '\n';

							fg_GenerateYamlBlockNode(o_String, Child.f_Value(), _Depth + 2, _pPrettySeparator, _Flags, o_pState);

							if (!Child.f_Value().f_Yaml().f_TrailingComment().f_IsEmpty())
								fg_GenerateYamlBlockComment(o_String, fg_YamlTrailingCommentForGeneration(Child.f_Value().f_Yaml()), _Depth, _pPrettySeparator);

							continue;
						}
					}

					if constexpr (tf_CJson::mc_bPreserveYamlMetadata && requires { Child.f_Value().f_EType(); Child.f_Value().f_UserType(); })
					{
						if (fg_YamlUserTypeStoredPayloadHasBlockStyle(Child.f_Value()) && Child.f_Value().f_Yaml().f_NodeStyle() == EYamlNodeStyle_Block)
						{
							o_String += '\n';

							fg_GenerateYamlBlockNode(o_String, Child.f_Value(), _Depth + 1, _pPrettySeparator, _Flags, o_pState);

							if (!Child.f_Value().f_Yaml().f_TrailingComment().f_IsEmpty())
								fg_GenerateYamlBlockComment(o_String, fg_YamlTrailingCommentForGeneration(Child.f_Value().f_Yaml()), _Depth, _pPrettySeparator);

							continue;
						}

						if (fg_YamlUserTypeStoredPayloadIsObjectOrArray(Child.f_Value()) && Child.f_Value().f_Yaml().f_NodeStyle() != EYamlNodeStyle_Flow)
						{
							auto Payload = fg_GetYamlUserTypeValue(Child.f_Value().f_UserType());

							o_String += ' ';

							fg_GenerateYamlUserTypeTag(o_String, Child.f_Value(), o_pState);

							if (!Child.f_Value().f_Yaml().f_LineComment().f_IsEmpty())
								fg_GenerateYamlLineComment(o_String, Child.f_Value().f_Yaml());

							o_String += '\n';

							fg_GenerateYamlBlockNode(o_String, Payload, _Depth + 1, _pPrettySeparator, _Flags, o_pState);

							if (!Child.f_Value().f_Yaml().f_TrailingComment().f_IsEmpty())
								fg_GenerateYamlBlockComment(o_String, fg_YamlTrailingCommentForGeneration(Child.f_Value().f_Yaml()), _Depth, _pPrettySeparator);

							continue;
						}
					}

					if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
					{
						if (Child.f_Value().f_IsObject() || Child.f_Value().f_IsArray())
						{
							if (Child.f_Value().f_Yaml().f_HasAnchor() || Child.f_Value().f_Yaml().f_HasTag())
							{
								o_String += ' ';
								fg_GenerateYamlMetadataPrefix(o_String, Child.f_Value().f_Yaml(), o_pState, fg_ShouldEmitYamlTag(Child.f_Value()), false);
							}
						}

						if (!Child.f_Value().f_Yaml().f_LineComment().f_IsEmpty())
							fg_GenerateYamlLineComment(o_String, Child.f_Value().f_Yaml());
					}

					o_String += '\n';

					fg_GenerateYamlBlockNode(o_String, Child.f_Value(), _Depth + 1, _pPrettySeparator, _Flags, o_pState);

					if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
					{
						if (!Child.f_Value().f_Yaml().f_TrailingComment().f_IsEmpty())
							fg_GenerateYamlBlockComment(o_String, fg_YamlTrailingCommentForGeneration(Child.f_Value().f_Yaml()), _Depth, _pPrettySeparator);
					}
				}
			}
			else
			{
				o_String += ' ';

				fg_GenerateYamlNode(o_String, Child.f_Value(), _Flags, o_pState, false, false);

				if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
				{
					if (!Child.f_Value().f_Yaml().f_LineComment().f_IsEmpty())
						fg_GenerateYamlLineComment(o_String, Child.f_Value().f_Yaml());
				}

				o_String += '\n';

				if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
				{
					if (!Child.f_Value().f_Yaml().f_TrailingComment().f_IsEmpty())
						fg_GenerateYamlBlockComment(o_String, fg_YamlTrailingCommentForGeneration(Child.f_Value().f_Yaml()), _Depth, _pPrettySeparator);
				}
			}
		}
	}

	template <typename tf_CStr, typename tf_CJson, typename tf_CGenerationState>
	void fg_GenerateYamlBlockNode(tf_CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags, tf_CGenerationState *o_pState)
	{
		bool bInlineAlias = false;
		umint ContentDepth = _Depth;
		if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
		{
			if (_Depth == 0 && !_Value.f_Yaml().f_LeadingComment().f_IsEmpty())
				fg_GenerateYamlBlockComment(o_String, fg_YamlLeadingCommentForGeneration(_Value.f_Yaml()), _Depth, _pPrettySeparator);

			if (!_Value.f_Yaml().f_Alias().f_IsEmpty())
			{
				if (fg_ShouldEmitYamlAlias(o_pState, _Value, _Value.f_Yaml().f_Alias()))
				{
					fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);

					o_String += '*';
					o_String += _Value.f_Yaml().f_Alias();
					o_String += '\n';

					return;
				}

				bInlineAlias = true;
			}
			else if (o_pState)
				++o_pState->m_Position;

			bool bEmitYamlTag = fg_ShouldEmitYamlTag(_Value);

			if
			(
				_Depth == 0
				&& !bInlineAlias
				&& (_Value.f_IsObject() || _Value.f_IsArray())
				&&
				(
					(bEmitYamlTag && _Value.f_Yaml().f_HasTag())
					|| _Value.f_Yaml().f_HasAnchor()
				)
			)
			{
				fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);
				fg_GenerateYamlMetadataPrefix(o_String, _Value.f_Yaml(), o_pState, bEmitYamlTag, false);

				o_String += '\n';
				ContentDepth = _Depth + 1;
			}
		}

		if constexpr (tf_CJson::mc_bPreserveYamlMetadata && requires (tf_CJson const &Value) { Value.f_EType(); Value.f_UserType(); })
		{
			if (fg_YamlUserTypeStoredPayloadHasBlockStyle(_Value))
			{
				auto Payload = fg_GetYamlUserTypeValue(_Value.f_UserType());

				fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);
				fg_GenerateYamlUserTypeTag(o_String, _Value, o_pState);

				if (_Depth > 0 && !_Value.f_Yaml().f_LineComment().f_IsEmpty())
					fg_GenerateYamlLineComment(o_String, _Value.f_Yaml());

				o_String += '\n';

				fg_GenerateYamlBlockNode(o_String, Payload, Payload.f_IsArray() ? _Depth : _Depth + 1, _pPrettySeparator, _Flags, o_pState);

				if (!_Value.f_Yaml().f_TrailingComment().f_IsEmpty())
					fg_GenerateYamlBlockComment(o_String, fg_YamlTrailingCommentForGeneration(_Value.f_Yaml()), _Depth, _pPrettySeparator);

				return;
			}
		}

		if (_Value.f_IsObject() && _Value.f_Object().f_IsEmpty())
		{
			fg_AddYamlBlockIndent(o_String, ContentDepth, _pPrettySeparator);

			o_String += "{}\n";
		}
		else if (_Value.f_IsObject())
			fg_GenerateYamlBlockObject(o_String, _Value.f_Object(), ContentDepth, _pPrettySeparator, _Flags, o_pState);
		else if (_Value.f_IsArray() && _Value.f_Array().f_IsEmpty())
		{
			fg_AddYamlBlockIndent(o_String, ContentDepth, _pPrettySeparator);

			o_String += "[]\n";
		}
		else if (_Value.f_IsArray())
			fg_GenerateYamlBlockSequence(o_String, _Value.f_Array(), ContentDepth, _pPrettySeparator, _Flags, o_pState);
		else if (fg_YamlStringNeedsBlockScalar(_Value))
		{
			fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);

			if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
			{
				if (_Value.f_Yaml().f_HasAnchor() || _Value.f_Yaml().f_HasTag())
					fg_GenerateYamlMetadataPrefix(o_String, _Value.f_Yaml(), o_pState, fg_ShouldEmitYamlTag(_Value));
			}

			fg_GenerateYamlBlockScalar(o_String, _Value, _Depth, _pPrettySeparator);
		}
		else if constexpr (tf_CJson::mc_bPreserveYamlMetadata && requires (tf_CJson const &Value) { Value.f_EType(); Value.f_Binary(); })
		{
			if
			(
				_Value.f_EType() == EEJsonType_Binary
				&& (_Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Literal || _Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Folded)
			)
			{
				fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);

				bool bHasExplicitTag = _Value.f_Yaml().f_HasTag();

				if (_Value.f_Yaml().f_HasAnchor() || bHasExplicitTag)
					fg_GenerateYamlMetadataPrefix(o_String, _Value.f_Yaml(), o_pState, fg_ShouldEmitYamlTag(_Value));
				else if (fg_CanGenerateYamlCoreTags(o_pState))
					o_String += "!!binary ";
				else
					o_String += "!<tag:yaml.org,2002:binary> ";

				tf_CJson BinaryText(fg_Base64Encode(_Value.f_Binary()));
				BinaryText.f_Yaml().f_SetScalarStyle(_Value.f_Yaml().f_ScalarStyle());
				BinaryText.f_Yaml().f_SetChompIndicator(_Value.f_Yaml().f_ChompIndicator());
				BinaryText.f_Yaml().f_SetBlockIndentHint(_Value.f_Yaml().f_BlockIndentHint());
				BinaryText.f_Yaml().f_SetLineComment(fg_TempCopy(_Value.f_Yaml().f_LineComment()));

				fg_GenerateYamlBlockScalar(o_String, BinaryText, _Depth, _pPrettySeparator);
			}
			else
			{
				bool bGeneratedBlockStyledScalar = false;
				if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
				{
					if (_Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Literal || _Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Folded)
					{
						NStr::CFStr128 ScalarText;
						if (_Value.f_IsNull())
							ScalarText = "null";
						else if (_Value.f_IsInteger())
							ScalarText = NStr::CFStr128::fs_ToStr(_Value.f_Integer());
						else if (_Value.f_IsFloat())
						{
							if (_Value.f_Float().f_IsInfinity())
								ScalarText = _Value.f_Float().f_GetSign() < 0 ? "-.inf" : ".inf";
							else if (_Value.f_Float().f_IsNan())
								ScalarText = ".nan";
							else
								ScalarText = NStr::CFStr128::fs_ToStr(_Value.f_Float());
						}
						else if (_Value.f_IsBoolean())
							ScalarText = _Value.f_Boolean() ? "true" : "false";

						if (!ScalarText.f_IsEmpty())
						{
							fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);
							fg_GenerateYamlMetadataPrefix(o_String, _Value.f_Yaml(), o_pState, fg_ShouldEmitYamlTag(_Value));
							tf_CJson ScalarValue(ScalarText);
							ScalarValue.f_Yaml().f_SetScalarStyle(_Value.f_Yaml().f_ScalarStyle());
							ScalarValue.f_Yaml().f_SetChompIndicator(_Value.f_Yaml().f_ChompIndicator());
							ScalarValue.f_Yaml().f_SetBlockIndentHint(_Value.f_Yaml().f_BlockIndentHint());
							ScalarValue.f_Yaml().f_SetLineComment(fg_TempCopy(_Value.f_Yaml().f_LineComment()));
							fg_GenerateYamlBlockScalar(o_String, ScalarValue, _Depth, _pPrettySeparator);
							bGeneratedBlockStyledScalar = true;
						}
					}
				}

				if (!bGeneratedBlockStyledScalar)
				{
					fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);

					if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
					{
						bool bEmitComments = _Depth != 0;
						fg_GenerateYamlNode(o_String, _Value, _Flags, o_pState, !_Value.f_Yaml().f_Alias().f_IsEmpty(), bEmitComments);
						if (!bEmitComments && !_Value.f_Yaml().f_LineComment().f_IsEmpty())
							fg_GenerateYamlLineComment(o_String, _Value.f_Yaml());
					}
					else
						fg_GenerateYamlNode(o_String, _Value, _Flags, static_cast<tf_CGenerationState *>(nullptr), false, true);

					o_String += '\n';
				}
			}
		}
		else
		{
			bool bGeneratedBlockStyledScalar = false;
			if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
			{
				if (_Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Literal || _Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Folded)
				{
					NStr::CFStr128 ScalarText;

					if (_Value.f_IsNull())
						ScalarText = "null";
					else if (_Value.f_IsInteger())
						ScalarText = NStr::CFStr128::fs_ToStr(_Value.f_Integer());
					else if (_Value.f_IsFloat())
					{
						if (_Value.f_Float().f_IsInfinity())
							ScalarText = _Value.f_Float().f_GetSign() < 0 ? "-.inf" : ".inf";
						else if (_Value.f_Float().f_IsNan())
							ScalarText = ".nan";
						else
							ScalarText = NStr::CFStr128::fs_ToStr(_Value.f_Float());
					}
					else if (_Value.f_IsBoolean())
						ScalarText = _Value.f_Boolean() ? "true" : "false";

					if (!ScalarText.f_IsEmpty())
					{
						fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);
						fg_GenerateYamlMetadataPrefix(o_String, _Value.f_Yaml(), o_pState, fg_ShouldEmitYamlTag(_Value));

						tf_CJson ScalarValue(ScalarText);
						ScalarValue.f_Yaml().f_SetScalarStyle(_Value.f_Yaml().f_ScalarStyle());
						ScalarValue.f_Yaml().f_SetChompIndicator(_Value.f_Yaml().f_ChompIndicator());
						ScalarValue.f_Yaml().f_SetBlockIndentHint(_Value.f_Yaml().f_BlockIndentHint());
						ScalarValue.f_Yaml().f_SetLineComment(fg_TempCopy(_Value.f_Yaml().f_LineComment()));

						fg_GenerateYamlBlockScalar(o_String, ScalarValue, _Depth, _pPrettySeparator);

						bGeneratedBlockStyledScalar = true;
					}
				}
			}

			if (!bGeneratedBlockStyledScalar)
			{
				fg_AddYamlBlockIndent(o_String, _Depth, _pPrettySeparator);

				if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
				{
					bool bEmitComments = _Depth != 0;
					fg_GenerateYamlNode(o_String, _Value, _Flags, o_pState, !_Value.f_Yaml().f_Alias().f_IsEmpty(), bEmitComments);
					if (!bEmitComments && !_Value.f_Yaml().f_LineComment().f_IsEmpty())
						fg_GenerateYamlLineComment(o_String, _Value.f_Yaml());
				}
				else
					fg_GenerateYamlNode(o_String, _Value, _Flags, static_cast<tf_CGenerationState *>(nullptr), false, true);

				o_String += '\n';
			}
		}

		if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
		{
			if (_Depth == 0 && !bInlineAlias && !_Value.f_Yaml().f_TrailingComment().f_IsEmpty())
				fg_GenerateYamlBlockComment(o_String, fg_YamlTrailingCommentForGeneration(_Value.f_Yaml()), _Depth, _pPrettySeparator);
		}
	}
}
