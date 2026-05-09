// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NEncoding::NYaml
{
	template <typename tf_CStr, typename tf_CValue>
	void fg_GenerateYamlSingleQuotedString(tf_CStr &o_String, tf_CValue const &_Value)
	{
		o_String += '\'';

		auto pValueScan = _Value.f_GetStr();
		auto pValueEnd = pValueScan + _Value.f_GetLen();
		while (pValueScan != pValueEnd)
		{
			auto pValueRangeStart = pValueScan;
			while (pValueScan != pValueEnd && *pValueScan && *pValueScan != '\'')
				++pValueScan;

			o_String.f_AddString(pValueRangeStart, pValueScan - pValueRangeStart);

			if (pValueScan == pValueEnd)
				break;

			DMibFastCheck(*pValueScan != 0); // Null characters not supported in this implementation

			if (*pValueScan == '\'')
			{
				o_String += "''";
				++pValueScan;
			}
		}

		o_String += '\'';
	}

	template <typename tf_CValue>
	inline bool fg_IsYamlSingleQuotedSafe(tf_CValue const &_Value)
	{
		auto pValue = _Value.f_GetStr();
		auto pValueEnd = pValue + _Value.f_GetLen();
		for (; pValue != pValueEnd; ++pValue)
		{
			if (uch8(*pValue) < 0x20 || uch8(*pValue) == 0x7f)
				return false;
		}

		return true;
	}

	template <typename tf_CStr, typename tf_CValue>
	void fg_GenerateYamlQuotedString(tf_CStr &o_String, tf_CValue const &_Value)
	{
		o_String += '"';

		auto pValue = _Value.f_GetStr();
		auto pValueEnd = pValue + _Value.f_GetLen();
		while (pValue != pValueEnd)
		{
			auto pValueRangeStart = pValue;
			while (pValue != pValueEnd && uch8(*pValue) >= 0x20 && uch8(*pValue) != 0x7f && *pValue != '"' && *pValue != '\\')
				++pValue;

			o_String.f_AddString(pValueRangeStart, pValue - pValueRangeStart);

			if (pValue == pValueEnd)
				break;

			switch (*pValue)
			{
			case '\0': DMibError("Null characters not supported in this implementation");
			case '\a': o_String += "\\a"; break;
			case '\b': o_String += "\\b"; break;
			case '"': o_String += "\\\""; break;
			case '\\': o_String += "\\\\"; break;
			case '\n': o_String += "\\n"; break;
			case '\r': o_String += "\\r"; break;
			case '\t': o_String += "\\t"; break;
			case '\v': o_String += "\\v"; break;
			case '\f': o_String += "\\f"; break;
			default:
				if (uch8(*pValue) < 0x20 || uch8(*pValue) == 0x7f)
					o_String += typename tf_CStr::CString::CFormat("\\x{nfh,sf0,sj2}") << uch8(*pValue);
				break;
			}

			++pValue;
		}

		o_String += '"';
	}

	inline bool fg_IsYamlPlainSafe(NStr::CStr const &_Value)
	{
		auto pValue = _Value.f_GetStr();
		auto Length = _Value.f_GetLen();

		auto fSyntaxSafe = [&]
			{
				if (!Length)
					return false;

				if (pValue[0] == ' ' || pValue[0] == '\t' || pValue[Length - 1] == ' ' || pValue[Length - 1] == '\t')
					return false;

				if
				(
					(Length >= 3 && pValue[0] == '-' && pValue[1] == '-' && pValue[2] == '-' && (Length == 3 || fg_IsYamlSeparation(uch8(pValue[3]))))
					|| (Length >= 3 && pValue[0] == '.' && pValue[1] == '.' && pValue[2] == '.' && (Length == 3 || fg_IsYamlSeparation(uch8(pValue[3]))))
				)
				{
					return false;
				}

				switch (pValue[0])
				{
				case ',':
				case '[':
				case ']':
				case '{':
				case '}':
				case '&':
				case '*':
				case '!':
				case '|':
				case '>':
				case '\'':
				case '"':
				case '%':
				case '@':
				case '`':
				case '#':
					return false;
				case '-':
				case '?':
				case ':':
					if (Length == 1 || fg_IsYamlSeparation(uch8(pValue[1])))
						return false;

					break;
				}

				for (auto pValueScan = pValue; pValueScan != pValue + Length; ++pValueScan)
				{
					if (uch8(*pValueScan) < 0x20 || uch8(*pValueScan) == 0x7f || *pValueScan == ',' || *pValueScan == '[' || *pValueScan == ']' || *pValueScan == '{' || *pValueScan == '}')
						return false;

					if (*pValueScan == ':' && (pValueScan + 1 == pValue + Length || fg_IsYamlSeparation(uch8(pValueScan[1]))))
						return false;

					if (*pValueScan == ' ' && pValueScan + 1 != pValue + Length && pValueScan[1] == '#')
						return false;
				}

				return true;
			}
		;

		if (!fSyntaxSafe())
			return false;

		if (Length == 1 && pValue[0] == '~')
			return false;

		if
		(
			Length == 4
			&&
			(
				(pValue[0] == 'n' && pValue[1] == 'u' && pValue[2] == 'l' && pValue[3] == 'l')
				|| (pValue[0] == 'N' && pValue[1] == 'u' && pValue[2] == 'l' && pValue[3] == 'l')
				|| (pValue[0] == 'N' && pValue[1] == 'U' && pValue[2] == 'L' && pValue[3] == 'L')
				|| (pValue[0] == 't' && pValue[1] == 'r' && pValue[2] == 'u' && pValue[3] == 'e')
				|| (pValue[0] == 'T' && pValue[1] == 'r' && pValue[2] == 'u' && pValue[3] == 'e')
				|| (pValue[0] == 'T' && pValue[1] == 'R' && pValue[2] == 'U' && pValue[3] == 'E')
				||
				(
					pValue[0] == '.'
					&&
					(
						(pValue[1] == 'i' && pValue[2] == 'n' && pValue[3] == 'f')
						|| (pValue[1] == 'I' && pValue[2] == 'n' && pValue[3] == 'f')
						|| (pValue[1] == 'I' && pValue[2] == 'N' && pValue[3] == 'F')
					)
				)
				||
				(
					pValue[0] == '.'
					&&
					(
						(pValue[1] == 'n' && pValue[2] == 'a' && pValue[3] == 'n')
						|| (pValue[1] == 'N' && pValue[2] == 'a' && pValue[3] == 'N')
						|| (pValue[1] == 'N' && pValue[2] == 'A' && pValue[3] == 'N')
					)
				)
			)
		)
		{
			return false;
		}

		if
		(
			Length == 5
			&&
			(
				(pValue[0] == 'f' && pValue[1] == 'a' && pValue[2] == 'l' && pValue[3] == 's' && pValue[4] == 'e')
				|| (pValue[0] == 'F' && pValue[1] == 'a' && pValue[2] == 'l' && pValue[3] == 's' && pValue[4] == 'e')
				|| (pValue[0] == 'F' && pValue[1] == 'A' && pValue[2] == 'L' && pValue[3] == 'S' && pValue[4] == 'E')
				||
				(
					(pValue[0] == '+' || pValue[0] == '-')
					&& pValue[1] == '.'
					&&
					(
						(pValue[2] == 'i' && pValue[3] == 'n' && pValue[4] == 'f')
						|| (pValue[2] == 'I' && pValue[3] == 'n' && pValue[4] == 'f')
						|| (pValue[2] == 'I' && pValue[3] == 'N' && pValue[4] == 'F')
					)
				)
			)
		)
		{
			return false;
		}

		if (NStr::fg_CharIsNumber(*pValue) || *pValue == '+' || *pValue == '-' || *pValue == '.')
		{
			auto pValueEnd = pValue + Length;
			auto pValueScan = pValue;
			if (pValueScan != pValueEnd && (*pValueScan == '+' || *pValueScan == '-'))
				++pValueScan;

			umint nDigits = 0;

			while (pValueScan != pValueEnd && *pValueScan >= '0' && *pValueScan <= '9')
			{
				++nDigits;
				++pValueScan;
			}

			if (pValueScan != pValueEnd && *pValueScan == '.')
			{
				++pValueScan;
				while (pValueScan != pValueEnd && *pValueScan >= '0' && *pValueScan <= '9')
				{
					++nDigits;
					++pValueScan;
				}
			}

			if (pValueScan != pValueEnd && (*pValueScan == 'e' || *pValueScan == 'E') && nDigits)
			{
				++pValueScan;
				if (pValueScan != pValueEnd && (*pValueScan == '+' || *pValueScan == '-'))
					++pValueScan;

				umint nExponentDigits = 0;
				while (pValueScan != pValueEnd && *pValueScan >= '0' && *pValueScan <= '9')
				{
					++nExponentDigits;
					++pValueScan;
				}

				if (!nExponentDigits)
					nDigits = 0;
			}

			if (nDigits && pValueScan == pValueEnd)
				return false;
		}

		return true;
	}

	inline bool fg_IsYamlPlainSyntaxSafe(NStr::CStr const &_Value)
	{
		auto pValue = _Value.f_GetStr();
		auto Length = _Value.f_GetLen();

		if (!Length)
			return false;

		if (pValue[0] == ' ' || pValue[0] == '\t' || pValue[Length - 1] == ' ' || pValue[Length - 1] == '\t')
			return false;

		if
		(
			(Length >= 3 && pValue[0] == '-' && pValue[1] == '-' && pValue[2] == '-' && (Length == 3 || fg_IsYamlSeparation(uch8(pValue[3]))))
			|| (Length >= 3 && pValue[0] == '.' && pValue[1] == '.' && pValue[2] == '.' && (Length == 3 || fg_IsYamlSeparation(uch8(pValue[3]))))
		)
		{
			return false;
		}

		switch (pValue[0])
		{
		case ',':
		case '[':
		case ']':
		case '{':
		case '}':
		case '&':
		case '*':
		case '!':
		case '|':
		case '>':
		case '\'':
		case '"':
		case '%':
		case '@':
		case '`':
		case '#':
			return false;
		case '-':
		case '?':
		case ':':
			if (Length == 1 || fg_IsYamlSeparation(uch8(pValue[1])))
				return false;
			break;
		}

		for (auto pValueScan = pValue; *pValueScan; ++pValueScan)
		{
			if (uch8(*pValueScan) < 0x20 || uch8(*pValueScan) == 0x7f || *pValueScan == ',' || *pValueScan == '[' || *pValueScan == ']' || *pValueScan == '{' || *pValueScan == '}')
				return false;

			if (*pValueScan == ':' && fg_IsYamlSeparation(uch8(pValueScan[1])))
				return false;

			if (*pValueScan == ' ' && pValueScan[1] == '#')
				return false;
		}

		return true;
	}

	template <typename tf_CStr, typename tf_CValue, typename tf_CYaml>
	void fg_GenerateYamlStyledScalarString(tf_CStr &o_String, tf_CValue const &_Value, tf_CYaml const &_Yaml)
	{
		if (_Yaml.f_ScalarStyle() == EYamlScalarStyle_SingleQuoted && fg_IsYamlSingleQuotedSafe(_Value))
			fg_GenerateYamlSingleQuotedString(o_String, _Value);
		else if (_Yaml.f_ScalarStyle() == EYamlScalarStyle_DoubleQuoted)
			fg_GenerateYamlQuotedString(o_String, _Value);
		else
			o_String += _Value;
	}

	template <typename tf_CJson>
	struct TCYamlGenerationAnchor
	{
		NStr::CStr m_Name;
		tf_CJson m_Value;
		umint m_Position = 0;
	};

	template <typename tf_CJson>
	struct TCYamlGenerationState
	{
		NContainer::TCMap<NStr::CStr, NContainer::TCVector<TCYamlGenerationAnchor<tf_CJson>>> m_Anchors;
		NContainer::TCMap<NStr::CStr, NStr::CStr> const *m_pDocumentTagHandles = nullptr;
		umint m_Position = 0;
	};

	template <typename tf_CJson, typename tf_CValue>
	void fg_AddYamlGenerationAnchor(TCYamlGenerationState<tf_CJson> &o_State, NStr::CStr const &_Name, tf_CValue const &_Value, umint _Position)
	{
		auto &Anchors = o_State.m_Anchors[_Name];
		auto &Anchor = Anchors.f_Insert();
		Anchor.m_Name = _Name;
		Anchor.m_Value = _Value;
		Anchor.m_Position = _Position;
	}

	template <typename tf_CJson>
	void fg_PrepassYamlGenerationValue(TCYamlGenerationState<tf_CJson> &o_State, tf_CJson const &_Value)
	{
		umint Position = o_State.m_Position++;

		if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
		{
			if (_Value.f_Yaml().f_HasAnchor())
				fg_AddYamlGenerationAnchor(o_State, _Value.f_Yaml().f_Anchor(), _Value, Position);
		}

		if constexpr (requires { _Value.f_EType(); _Value.f_UserType(); })
		{
			if (_Value.f_IsUserType())
			{
				fg_PrepassYamlGenerationValue(o_State, fg_GetYamlUserTypeValue(_Value.f_UserType()));

				return;
			}
		}

		if (_Value.f_IsObject())
		{
			for (auto &Child : _Value.f_Object())
			{
				if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
				{
					if (Child.f_KeyYaml().f_HasAnchor())
						fg_AddYamlGenerationAnchor(o_State, Child.f_KeyYaml().f_Anchor(), Child.f_Name(), o_State.m_Position);
				}

				++o_State.m_Position;
				fg_PrepassYamlGenerationValue(o_State, Child.f_Value());
			}
		}
		else if (_Value.f_IsArray())
		{
			for (auto &Child : _Value.f_Array())
				fg_PrepassYamlGenerationValue(o_State, Child);
		}
	}

	template <typename tf_CJson>
	bool fg_ShouldEmitYamlAlias(TCYamlGenerationState<tf_CJson> *o_pState, tf_CJson const &_Value, NStr::CStr const &_Alias)
	{
		if (!o_pState)
			return !_Alias.f_IsEmpty();

		umint Position = o_pState->m_Position++;
		if (_Alias.f_IsEmpty())
			return false;

		auto const *pAnchors = o_pState->m_Anchors.f_FindEqual(_Alias);
		if (!pAnchors)
			return false;

		TCYamlGenerationAnchor<tf_CJson> const *pFound = nullptr;
		for (auto const &Anchor : *pAnchors)
		{
			if (Anchor.m_Position < Position && (!pFound || Anchor.m_Position > pFound->m_Position))
				pFound = &Anchor;
		}

		// yaml-desgin.md requires inlining aliases for redefined anchor names. YAML parsing is last-wins, but after edits/reordering the per-node
		// alias name alone cannot prove which duplicate definition was intended.
		if (!pFound || pAnchors->f_GetLen() != 1)
			return false;

		return _Value == pFound->m_Value;
	}

	template <typename tf_CJson>
	bool fg_ShouldEmitYamlKeyAlias(TCYamlGenerationState<tf_CJson> *o_pState, NStr::CStr const &_Value, NStr::CStr const &_Alias)
	{
		if (!o_pState)
			return !_Alias.f_IsEmpty();

		if (_Alias.f_IsEmpty())
			return false;

		umint Position = o_pState->m_Position++;

		auto const *pAnchors = o_pState->m_Anchors.f_FindEqual(_Alias);
		if (!pAnchors)
			return false;

		TCYamlGenerationAnchor<tf_CJson> const *pFound = nullptr;
		for (auto const &Anchor : *pAnchors)
		{
			if (Anchor.m_Position < Position && (!pFound || Anchor.m_Position > pFound->m_Position))
				pFound = &Anchor;
		}

		// Keep key aliases aligned with value aliases: duplicate anchor names are emitted inline for data-correct, unambiguous round-trips.
		if (pAnchors->f_GetLen() != 1)
			return false;

		return pFound && pFound->m_Value.f_IsString() && _Value == pFound->m_Value.f_String();
	}

	template <typename tf_CStr, typename tf_CJson, typename tf_CGenerationState>
	void fg_GenerateYamlNode(tf_CStr &o_String, tf_CJson const &_Value, EJsonDialectFlag _Flags, tf_CGenerationState *o_pState, bool _bSuppressAlias = false, bool _bEmitComments = true);

	template <typename tf_CStr, typename tf_CJson, typename tf_CGenerationState>
	void fg_GenerateYamlObject(tf_CStr &o_String, tf_CJson const &_Value, EJsonDialectFlag _Flags, tf_CGenerationState *o_pState);

	template <typename tf_CStr, typename tf_CJson, typename tf_CGenerationState>
	void fg_GenerateYamlUserTypePayload(tf_CStr &o_String, tf_CJson const &_Value, EJsonDialectFlag _Flags, tf_CGenerationState *o_pState)
	{
		TCYamlGenerationState<tf_CJson> State;
		umint StartPosition = 0;

		if (o_pState)
		{
			StartPosition = o_pState->m_Position;
			State.m_Position = StartPosition;
			State.m_pDocumentTagHandles = o_pState->m_pDocumentTagHandles;

			for (auto const &OuterAnchors : o_pState->m_Anchors)
			{
				for (auto const &OuterAnchor : OuterAnchors)
				{
					auto &Anchors = State.m_Anchors.f_Insert(OuterAnchor.m_Name);
					auto &Anchor = Anchors.f_Insert();

					Anchor.m_Name = OuterAnchor.m_Name;

					if constexpr (requires { Anchor.m_Value = OuterAnchor.m_Value; })
						Anchor.m_Value = OuterAnchor.m_Value;
					else if constexpr (requires { OuterAnchor.m_Value.f_ToJson(); })
						Anchor.m_Value = OuterAnchor.m_Value.f_ToJson();
					else
						Anchor.m_Value = OuterAnchor.m_Value;

					Anchor.m_Position = OuterAnchor.m_Position;
				}
			}
		}

		if (!o_pState)
			fg_PrepassYamlGenerationValue(State, _Value);

		State.m_Position = StartPosition;

		fg_GenerateYamlNode(o_String, _Value, _Flags, &State);

		if (o_pState)
			o_pState->m_Position = State.m_Position;
	}

	template <typename tf_CStr, typename tf_CUserType, typename tf_CGenerationState>
	void fg_GenerateYamlUserTypeStoredPayload(tf_CStr &o_String, tf_CUserType const &_Value, EJsonDialectFlag _Flags, tf_CGenerationState *o_pState)
	{
		fg_GenerateYamlUserTypePayload(o_String, fg_GetYamlUserTypeValue(_Value), _Flags, o_pState);
	}

	template <typename tf_CStr, typename tf_CYamlMetadata, typename tf_CGenerationState>
	void fg_GenerateYamlMetadataPrefix(tf_CStr &o_String, tf_CYamlMetadata const &_Yaml, tf_CGenerationState *o_pState, bool _bEmitTag = true, bool _bTrailingSpace = true)
	{
		if (_bEmitTag && (!_Yaml.f_TagHandle().f_IsEmpty() || !_Yaml.f_TagResolved().f_IsEmpty()))
		{
			bool bUseHandle = !_Yaml.f_TagHandle().f_IsEmpty();
			if (bUseHandle)
			{
				NStr::CStr Prefix;
				if (o_pState && o_pState->m_pDocumentTagHandles)
				{
					if (auto *pPrefix = o_pState->m_pDocumentTagHandles->f_FindEqual(_Yaml.f_TagHandle()))
						Prefix = *pPrefix;
				}

				if (Prefix.f_IsEmpty())
				{
					if (_Yaml.f_TagHandle() == NStr::gc_Str<"!">.m_Str)
						Prefix = NStr::gc_Str<"!">.m_Str;
					else if (_Yaml.f_TagHandle() == NStr::gc_Str<"!!">.m_Str)
						Prefix = NStr::gc_Str<"tag:yaml.org,2002:">.m_Str;
				}

				bUseHandle = !Prefix.f_IsEmpty();
				if (bUseHandle && !_Yaml.f_TagResolved().f_IsEmpty())
				{
					auto const &TagSuffix = _Yaml.f_TagSuffix();
					auto const &TagResolved = _Yaml.f_TagResolved();
					bUseHandle = Prefix.f_GetLen() + TagSuffix.f_GetLen() == TagResolved.f_GetLen() && TagResolved.f_StartsWith(Prefix) && TagResolved.f_EndsWith(TagSuffix);
				}
			}

			if (_Yaml.f_TagHandle() == NStr::gc_Str<"!">.m_Str && _Yaml.f_TagSuffix() == _Yaml.f_TagResolved() && !_Yaml.f_TagResolved().f_IsEmpty())
			{
				o_String += "!<";
				o_String += _Yaml.f_TagResolved();
				o_String += ">";
			}
			else if (bUseHandle)
			{
				o_String += _Yaml.f_TagHandle();
				o_String += _Yaml.f_TagSuffix();
			}
			else
			{
				o_String += "!<";
				o_String += _Yaml.f_TagResolved();
				o_String += ">";
			}

			if (_bTrailingSpace)
				o_String += ' ';
		}

		if (_Yaml.f_HasAnchor())
		{
			o_String += '&';
			o_String += _Yaml.f_Anchor();
			o_String += ' ';
		}
	}

	template <typename tf_CGenerationState>
	bool fg_CanGenerateYamlCoreTags(tf_CGenerationState *o_pState)
	{
		if (!o_pState || !o_pState->m_pDocumentTagHandles)
			return true;

		auto *pCoreHandle = o_pState->m_pDocumentTagHandles->f_FindEqual(NStr::gc_Str<"!!">.m_Str);
		return !pCoreHandle || *pCoreHandle == NStr::gc_Str<"tag:yaml.org,2002:">.m_Str;
	}

	template <typename tf_CGenerationState>
	bool fg_CanGenerateYamlPrimaryTags(tf_CGenerationState *o_pState)
	{
		if (!o_pState || !o_pState->m_pDocumentTagHandles)
			return true;

		auto *pPrimaryHandle = o_pState->m_pDocumentTagHandles->f_FindEqual(NStr::gc_Str<"!">.m_Str);
		return !pPrimaryHandle || *pPrimaryHandle == NStr::gc_Str<"!">.m_Str;
	}

	template <typename tf_CStr, typename tf_CJson, typename tf_CGenerationState>
	void fg_GenerateYamlUserTypeTag(tf_CStr &o_String, tf_CJson const &_Value, tf_CGenerationState *o_pState)
	{
		if (_Value.f_UserType().m_Type.f_StartsWith(NStr::gc_Str<"!">.m_Str) && fg_CanGenerateYamlPrimaryTags(o_pState))
			o_String += _Value.f_UserType().m_Type;
		else if (fg_CanGenerateYamlPrimaryTags(o_pState) && fg_IsYamlLocalTagSafe(_Value.f_UserType().m_Type))
		{
			o_String += '!';
			o_String += _Value.f_UserType().m_Type;
		}
		else
		{
			o_String += "!<";
			o_String += _Value.f_UserType().m_Type;
			o_String += '>';
		}
	}

	template <typename tf_CJson>
	bool fg_ShouldEmitYamlTag(tf_CJson const &_Value)
	{
		if constexpr (!tf_CJson::mc_bPreserveYamlMetadata)
			return true;
		else
		{
			auto const &Tag = _Value.f_Yaml().f_TagResolved();
			if (Tag.f_IsEmpty())
				return true;

			if (Tag == "tag:yaml.org,2002:str")
				return _Value.f_IsString();

			if (Tag == "tag:yaml.org,2002:int")
				return _Value.f_IsInteger();

			if (Tag == "tag:yaml.org,2002:float")
				return _Value.f_IsFloat();

			if (Tag == "tag:yaml.org,2002:bool")
				return _Value.f_IsBoolean();

			if (Tag == "tag:yaml.org,2002:null")
				return _Value.f_IsNull();

			if (Tag == "tag:yaml.org,2002:seq")
				return _Value.f_IsArray();

			if (Tag == "tag:yaml.org,2002:map")
				return _Value.f_IsObject();

			if constexpr (requires (tf_CJson const &Value) { Value.f_EType(); Value.f_UserType(); Value.f_Binary(); Value.f_Date(); })
			{
				if (Tag == "tag:yaml.org,2002:binary")
					return _Value.f_EType() == EEJsonType_Binary;

				if (Tag == "tag:yaml.org,2002:timestamp")
					return _Value.f_EType() == EEJsonType_Date && _Value.f_Date().f_IsValid();

				return _Value.f_EType() == EEJsonType_UserType && _Value.f_UserType().m_Type == Tag;
			}

			return true;
		}
	}

	template <typename tf_CStr, typename tf_CJson>
	void fg_GenerateYamlNode(tf_CStr &o_String, tf_CJson const &_Value, EJsonDialectFlag _Flags)
	{
		fg_GenerateYamlNode(o_String, _Value, _Flags, static_cast<TCYamlGenerationState<tf_CJson> *>(nullptr), false, true);
	}

	template <typename tf_CStr, typename tf_CJson, typename tf_CGenerationState>
	void fg_GenerateYamlArray(tf_CStr &o_String, tf_CJson const &_Value, EJsonDialectFlag _Flags, tf_CGenerationState *o_pState)
	{
		o_String += '[';

		bool bFirst = true;
		for (auto const &Child : _Value)
		{
			if (!bFirst)
				o_String += ", ";

			fg_GenerateYamlNode(o_String, Child, _Flags, o_pState);
			bFirst = false;
		}

		o_String += ']';
	}

	template <typename tf_CStr>
	void fg_GenerateYamlBlockComment(tf_CStr &o_String, NStr::CStr const &_Comment, umint _Depth, ch8 const *_pPrettySeparator);

	template <typename tf_CYamlView>
	NStr::CStr const &fg_YamlLeadingCommentForGeneration(tf_CYamlView const &_Yaml)
	{
		return _Yaml.f_LeadingComment();
	}

	template <typename tf_CYamlView>
	NStr::CStr const &fg_YamlLineCommentForGeneration(tf_CYamlView const &_Yaml)
	{
		return _Yaml.f_LineComment();
	}

	template <typename tf_CYamlView>
	NStr::CStr const &fg_YamlTrailingCommentForGeneration(tf_CYamlView const &_Yaml)
	{
		return _Yaml.f_TrailingComment();
	}

	template <typename tf_CStr, typename tf_CYamlView>
	void fg_GenerateYamlLineComment(tf_CStr &o_String, tf_CYamlView const &_Yaml)
	{
		auto const &LineComment = _Yaml.f_LineComment();
		if (!LineComment.f_IsEmpty())
		{
			if (LineComment[0] != ' ' && LineComment[0] != '\t')
				o_String += ' ';
			o_String += LineComment;
		}
	}

	template <typename tf_CStr, typename tf_CJson, typename tf_CGenerationState>
	void fg_GenerateYamlObject(tf_CStr &o_String, tf_CJson const &_Value, EJsonDialectFlag _Flags, tf_CGenerationState *o_pState)
	{
		o_String += '{';

		bool bFirst = true;
		for (auto const &Child : _Value)
		{
			if (!bFirst)
				o_String += ", ";

			bool bConsumedKeyPosition = false;
			if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
			{
				if (!Child.f_KeyYaml().f_LeadingComment().f_IsEmpty() || !Child.f_KeyYaml().f_LineComment().f_IsEmpty())
				{
					o_String += '\n';

					if (!Child.f_KeyYaml().f_LeadingComment().f_IsEmpty())
						fg_GenerateYamlBlockComment(o_String, fg_YamlLeadingCommentForGeneration(Child.f_KeyYaml()), 0, "  ");

					if (!Child.f_KeyYaml().f_LineComment().f_IsEmpty())
						fg_GenerateYamlBlockComment(o_String, fg_YamlLineCommentForGeneration(Child.f_KeyYaml()), 0, "  ");
				}

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

					bool bTaggedPlainKey = Child.f_KeyYaml().f_ScalarStyle() == EYamlScalarStyle_Plain && Child.f_KeyYaml().f_HasTag();

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

			o_String += ": ";
			if (o_pState && !bConsumedKeyPosition)
				++o_pState->m_Position;

			fg_GenerateYamlNode(o_String, Child.f_Value(), _Flags, o_pState);
			bFirst = false;
		}

		o_String += '}';
	}

	template <typename tf_CStr, typename tf_CJson, typename tf_CGenerationState>
	void fg_GenerateYamlNode(tf_CStr &o_String, tf_CJson const &_Value, EJsonDialectFlag _Flags, tf_CGenerationState *o_pState, bool _bSuppressAlias, bool _bEmitComments)
	{
		bool bInlineAlias = _bSuppressAlias;
		bool bEmittedYamlTag = false;
		if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
		{
			if (_bEmitComments && !_Value.f_Yaml().f_LeadingComment().f_IsEmpty())
			{
				auto const &LeadingComment = fg_YamlLeadingCommentForGeneration(_Value.f_Yaml());
				o_String += LeadingComment;

				if
				(
					LeadingComment.f_IsEmpty()
					||
					(
						LeadingComment[LeadingComment.f_GetLen() - 1] != '\n'
						&& LeadingComment[LeadingComment.f_GetLen() - 1] != '\r'
					)
				)
				{
					o_String += '\n';
				}
			}

			if (!_bSuppressAlias && !_Value.f_Yaml().f_Alias().f_IsEmpty())
			{
				if (fg_ShouldEmitYamlAlias(o_pState, _Value, _Value.f_Yaml().f_Alias()))
				{
					if (_Value.f_Yaml().f_HasAnchor() || _Value.f_Yaml().f_HasTag())
						fg_GenerateYamlMetadataPrefix(o_String, _Value.f_Yaml(), o_pState, fg_ShouldEmitYamlTag(_Value));

					o_String += '*';
					o_String += _Value.f_Yaml().f_Alias();
					goto l_EmitComments;
				}

				bInlineAlias = true;
			}
			else if (o_pState && !(_bSuppressAlias && !_Value.f_Yaml().f_Alias().f_IsEmpty()))
				++o_pState->m_Position;

			bool bEmitYamlTag = fg_ShouldEmitYamlTag(_Value);

			if
			(
				!bInlineAlias
				&&
				(
					(bEmitYamlTag && _Value.f_Yaml().f_HasTag())
					|| _Value.f_Yaml().f_HasAnchor()
				)
			)
			{
				bEmittedYamlTag = bEmitYamlTag && _Value.f_Yaml().f_HasTag();
				fg_GenerateYamlMetadataPrefix(o_String, _Value.f_Yaml(), o_pState, bEmitYamlTag);
			}
		}

		switch (_Value.f_Type())
		{
		case EJsonType_Null:
			o_String += NStr::gc_Str<"null">.m_Str;
			break;
		case EJsonType_String:
			if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
			{
				if (_Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_SingleQuoted && fg_IsYamlSingleQuotedSafe(_Value.f_String()))
					fg_GenerateYamlSingleQuotedString(o_String, _Value.f_String());
				else if
				(
					_Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_Plain
					&& (fg_IsYamlPlainSafe(_Value.f_String()) || (bEmittedYamlTag && fg_IsYamlPlainSyntaxSafe(_Value.f_String())))
				)
				{
					o_String += _Value.f_String();
				}
				else
					fg_GenerateYamlQuotedString(o_String, _Value.f_String());
			}
			else
			{
				if (fg_IsYamlPlainSafe(_Value.f_String()))
					o_String += _Value.f_String();
				else
					fg_GenerateYamlQuotedString(o_String, _Value.f_String());
			}
			break;
		case EJsonType_Integer:
			{
				auto Text = NStr::CFStr32::fs_ToStr(int64(_Value.f_Integer()));
				if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
					fg_GenerateYamlStyledScalarString(o_String, Text, _Value.f_Yaml());
				else
					o_String += Text;
			}
			break;
		case EJsonType_Float:
			{
				NStr::CFStr128 Text;
				auto Value = fp64(_Value.f_Float());

				if (Value.f_IsInfinity())
				{
					if (Value.f_GetSign() < 0)
						Text = "-.inf";
					else
						Text = ".inf";
				}
				else if (Value.f_IsNan())
					Text = ".nan";
				else
					Text = NStr::CFStr128::fs_ToStr(fp64(Value));

				if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
					fg_GenerateYamlStyledScalarString(o_String, Text, _Value.f_Yaml());
				else
					o_String += Text;
			}
			break;
		case EJsonType_Boolean:
			if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
				fg_GenerateYamlStyledScalarString(o_String, _Value.f_Boolean() ? NStr::gc_Str<"true">.m_Str : NStr::gc_Str<"false">.m_Str, _Value.f_Yaml());
			else
				o_String += _Value.f_Boolean() ? NStr::gc_Str<"true">.m_Str : NStr::gc_Str<"false">.m_Str;
			break;
		case EJsonType_Object:
			fg_GenerateYamlObject(o_String, _Value.f_Object(), _Flags, o_pState);
			break;
		case EJsonType_Array:
			fg_GenerateYamlArray(o_String, _Value.f_Array(), _Flags, o_pState);
			break;
		default:
			if constexpr (requires (tf_CJson const &Value) { Value.f_EType(); Value.f_Binary(); })
			{
				if (_Value.f_EType() == EEJsonType_UserType)
				{
					if (_Value.f_UserType().m_Type.f_StartsWith("tag:yaml.org,2002:"))
					{
						if (bEmittedYamlTag)
						{
							fg_GenerateYamlUserTypeStoredPayload(o_String, _Value.f_UserType(), _Flags, o_pState);
							break;
						}

						auto TagSuffix = _Value.f_UserType().m_Type.f_Extract(sizeof("tag:yaml.org,2002:") - 1);

						if
						(
							fg_CanGenerateYamlCoreTags(o_pState)
							&& fg_IsYamlLocalTagSafe(TagSuffix)
							&& TagSuffix != "str"
							&& TagSuffix != "int"
							&& TagSuffix != "float"
							&& TagSuffix != "bool"
							&& TagSuffix != "null"
							&& TagSuffix != "binary"
							&& TagSuffix != "timestamp"
							&& TagSuffix != "seq"
							&& TagSuffix != "map"
						)
						{
							o_String += "!!";
							o_String += TagSuffix;
							o_String += ' ';
							fg_GenerateYamlUserTypeStoredPayload(o_String, _Value.f_UserType(), _Flags, o_pState);
							break;
						}

						o_String += "!<";
						o_String += _Value.f_UserType().m_Type;
						o_String += "> ";
						fg_GenerateYamlUserTypeStoredPayload(o_String, _Value.f_UserType(), _Flags, o_pState);
						break;
					}

					if (!bEmittedYamlTag)
					{
						if (_Value.f_UserType().m_Type.f_StartsWith(NStr::gc_Str<"!">.m_Str) && fg_CanGenerateYamlPrimaryTags(o_pState))
						{
							if (!fg_IsYamlLocalTagSafe(_Value.f_UserType().m_Type.f_Extract(1)))
							{
								o_String += "!<";
								o_String += _Value.f_UserType().m_Type;
								o_String += ">";
							}
							else
								o_String += _Value.f_UserType().m_Type;
						}
						else if (fg_CanGenerateYamlPrimaryTags(o_pState) && fg_IsYamlLocalTagSafe(_Value.f_UserType().m_Type))
						{
							o_String += '!';
							o_String += _Value.f_UserType().m_Type;
						}
						else
						{
							o_String += "!<";
							o_String += _Value.f_UserType().m_Type;
							o_String += ">";
						}

						o_String += ' ';
					}

					fg_GenerateYamlUserTypeStoredPayload(o_String, _Value.f_UserType(), _Flags, o_pState);
				}
				else if (_Value.f_EType() == EEJsonType_Binary)
				{
					if (!bEmittedYamlTag)
					{
						if (fg_CanGenerateYamlCoreTags(o_pState))
							o_String += "!!binary ";
						else
							o_String += "!<tag:yaml.org,2002:binary> ";
					}

					o_String += fg_Base64Encode(_Value.f_Binary());
				}
				else if (_Value.f_EType() == EEJsonType_Date)
				{
					if (_Value.f_Date().f_IsValid())
					{
						if (!bEmittedYamlTag)
						{
							if (fg_CanGenerateYamlCoreTags(o_pState))
								o_String += "!!timestamp ";
							else
								o_String += "!<tag:yaml.org,2002:timestamp> ";
						}

						if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
						{
							if (_Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_SingleQuoted || _Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_DoubleQuoted)
							{
								auto Timestamp = NEncoding::fg_FormatYamlTimestamp(_Value.f_Date());
								if (_Value.f_Yaml().f_ScalarStyle() == EYamlScalarStyle_SingleQuoted && fg_IsYamlSingleQuotedSafe(Timestamp))
									fg_GenerateYamlSingleQuotedString(o_String, Timestamp);
								else
									fg_GenerateYamlQuotedString(o_String, Timestamp);
							}
							else
								fg_FormatYamlTimestamp(o_String, _Value.f_Date());
						}
						else
							fg_FormatYamlTimestamp(o_String, _Value.f_Date());
					}
					else
					{
						if (!bEmittedYamlTag)
						{
							if (fg_CanGenerateYamlCoreTags(o_pState))
								o_String += "!!timestamp ";
							else
								o_String += "!<tag:yaml.org,2002:timestamp> ";
						}

						o_String += "null";
					}
				}
				else
					o_String += NStr::gc_Str<"null">.m_Str;
			}
			else
				o_String += NStr::gc_Str<"null">.m_Str;

			break;
		}

	l_EmitComments:
		if constexpr (tf_CJson::mc_bPreserveYamlMetadata)
		{
			if (_bEmitComments && !_Value.f_Yaml().f_LineComment().f_IsEmpty())
			{
				fg_GenerateYamlLineComment(o_String, _Value.f_Yaml());
				o_String += '\n';
			}

			if (_bEmitComments && !_Value.f_Yaml().f_TrailingComment().f_IsEmpty())
			{
				if (_Value.f_Yaml().f_LineComment().f_IsEmpty())
					o_String += '\n';
				o_String += fg_YamlTrailingCommentForGeneration(_Value.f_Yaml());
			}
		}
	}

}
