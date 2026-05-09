// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NEncoding
{
	template <typename t_CValueBase>
	TCYamlConstView<t_CValueBase>::TCYamlConstView(t_CValueBase const &_Value)
		: mp_Value(_Value)
	{
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlConstView<t_CValueBase>::f_Anchor() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_AnchorName;
	}

	template <typename t_CValueBase>
	bool TCYamlConstView<t_CValueBase>::f_HasAnchor() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		auto const &Metadata = mp_Value.mp_ValueYamlMetadata;
		return Metadata.m_pStringMetadata && !Metadata.m_pStringMetadata->m_AnchorName.f_IsEmpty();
	}

	template <typename t_CValueBase>
	bool TCYamlConstView<t_CValueBase>::f_HasTag() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		auto const &Metadata = mp_Value.mp_ValueYamlMetadata;
		return Metadata.m_pStringMetadata && (!Metadata.m_pStringMetadata->m_TagHandle.f_IsEmpty() || !Metadata.m_pStringMetadata->m_TagResolved.f_IsEmpty());
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlConstView<t_CValueBase>::f_Alias() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_AliasName;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlConstView<t_CValueBase>::f_TagHandle() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_TagHandle;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlConstView<t_CValueBase>::f_TagSuffix() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_TagSuffix;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlConstView<t_CValueBase>::f_TagResolved() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_TagResolved;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlConstView<t_CValueBase>::f_LeadingComment() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_LeadingComment;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlConstView<t_CValueBase>::f_LineComment() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_LineComment;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlConstView<t_CValueBase>::f_TrailingComment() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_TrailingComment;
	}

	template <typename t_CValueBase>
	EYamlScalarStyle TCYamlConstView<t_CValueBase>::f_ScalarStyle() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return EYamlScalarStyle(mp_Value.mp_ValueYamlMetadata.m_ScalarStyle);
	}

	template <typename t_CValueBase>
	EYamlNodeStyle TCYamlConstView<t_CValueBase>::f_NodeStyle() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return EYamlNodeStyle(mp_Value.mp_ValueYamlMetadata.m_NodeStyle);
	}

	template <typename t_CValueBase>
	uch8 TCYamlConstView<t_CValueBase>::f_ChompIndicator() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.m_ChompIndicator;
	}

	template <typename t_CValueBase>
	smint TCYamlConstView<t_CValueBase>::f_BlockIndentHint() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.m_BlockIndentHint;
	}

	template <typename t_CValueBase>
	NContainer::TCMap<NStr::CStr, NStr::CStr> const &TCYamlConstView<t_CValueBase>::f_DocumentTagHandles() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_DocumentTagHandles;
	}

	template <typename t_CValueBase>
	NPrivate::CYamlValueMetadataSlots const &TCYamlConstView<t_CValueBase>::f_MetadataSlots() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata;
	}

	template <typename t_CValueBase>
	TCYamlView<t_CValueBase>::TCYamlView(t_CValueBase &_Value)
		: mp_Value(_Value)
	{
	}

	template <typename t_CValueBase>
	TCYamlView<t_CValueBase>::operator TCYamlConstView<t_CValueBase>() const
	{
		return TCYamlConstView<t_CValueBase>(mp_Value);
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlView<t_CValueBase>::f_Anchor() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_AnchorName;
	}

	template <typename t_CValueBase>
	bool TCYamlView<t_CValueBase>::f_HasAnchor() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		auto const &Metadata = mp_Value.mp_ValueYamlMetadata;
		return Metadata.m_pStringMetadata && !Metadata.m_pStringMetadata->m_AnchorName.f_IsEmpty();
	}

	template <typename t_CValueBase>
	bool TCYamlView<t_CValueBase>::f_HasTag() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		auto const &Metadata = mp_Value.mp_ValueYamlMetadata;
		return Metadata.m_pStringMetadata && (!Metadata.m_pStringMetadata->m_TagHandle.f_IsEmpty() || !Metadata.m_pStringMetadata->m_TagResolved.f_IsEmpty());
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlView<t_CValueBase>::f_Alias() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_AliasName;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlView<t_CValueBase>::f_TagHandle() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_TagHandle;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlView<t_CValueBase>::f_TagSuffix() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_TagSuffix;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlView<t_CValueBase>::f_TagResolved() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_TagResolved;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlView<t_CValueBase>::f_LeadingComment() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_LeadingComment;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlView<t_CValueBase>::f_LineComment() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_LineComment;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCYamlView<t_CValueBase>::f_TrailingComment() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_TrailingComment;
	}

	template <typename t_CValueBase>
	EYamlScalarStyle TCYamlView<t_CValueBase>::f_ScalarStyle() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return EYamlScalarStyle(mp_Value.mp_ValueYamlMetadata.m_ScalarStyle);
	}

	template <typename t_CValueBase>
	EYamlNodeStyle TCYamlView<t_CValueBase>::f_NodeStyle() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return EYamlNodeStyle(mp_Value.mp_ValueYamlMetadata.m_NodeStyle);
	}

	template <typename t_CValueBase>
	uch8 TCYamlView<t_CValueBase>::f_ChompIndicator() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.m_ChompIndicator;
	}

	template <typename t_CValueBase>
	smint TCYamlView<t_CValueBase>::f_BlockIndentHint() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.m_BlockIndentHint;
	}

	template <typename t_CValueBase>
	NContainer::TCMap<NStr::CStr, NStr::CStr> &TCYamlView<t_CValueBase>::f_DocumentTagHandles()
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_DocumentTagHandles;
	}

	template <typename t_CValueBase>
	NPrivate::CYamlValueMetadataSlots const &TCYamlView<t_CValueBase>::f_MetadataSlots() const
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return mp_Value.mp_ValueYamlMetadata;
	}

	template <typename t_CValueBase>
	NPrivate::CYamlValueMetadataSlots &&TCYamlView<t_CValueBase>::f_MoveMetadataSlots()
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		return fg_Move(mp_Value.mp_ValueYamlMetadata);
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetMetadataSlots(NPrivate::CYamlValueMetadataSlots const &_Value)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		mp_Value.mp_ValueYamlMetadata = _Value;
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetMetadataSlots(NPrivate::CYamlValueMetadataSlots &&_Value)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		mp_Value.mp_ValueYamlMetadata = fg_Move(_Value);
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_ResetMetadataSlots()
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		mp_Value.mp_ValueYamlMetadata = {};
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetAnchor(NStr::CStr &&_Value)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		if (_Value.f_IsEmpty() && !mp_Value.mp_ValueYamlMetadata.m_pStringMetadata)
			return;

		mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_AnchorName = fg_Move(_Value);
		mp_Value.mp_ValueYamlMetadata.f_PruneStringMetadata();
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetAlias(NStr::CStr &&_Value)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		if (_Value.f_IsEmpty() && !mp_Value.mp_ValueYamlMetadata.m_pStringMetadata)
			return;

		mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_AliasName = fg_Move(_Value);
		mp_Value.mp_ValueYamlMetadata.f_PruneStringMetadata();
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetTag(NStr::CStr &&_Handle, NStr::CStr &&_Suffix, NStr::CStr &&_Resolved)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		if (_Handle.f_IsEmpty() && _Suffix.f_IsEmpty() && _Resolved.f_IsEmpty() && !mp_Value.mp_ValueYamlMetadata.m_pStringMetadata)
			return;

		auto &Strings = mp_Value.mp_ValueYamlMetadata.f_StringMetadata();
		Strings.m_TagHandle = fg_Move(_Handle);
		Strings.m_TagSuffix = fg_Move(_Suffix);
		Strings.m_TagResolved = fg_Move(_Resolved);
		mp_Value.mp_ValueYamlMetadata.f_PruneStringMetadata();
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetLeadingComment(NStr::CStr &&_Value)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		if (_Value.f_IsEmpty() && !mp_Value.mp_ValueYamlMetadata.m_pStringMetadata)
			return;

		mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_LeadingComment = fg_Move(_Value);
		mp_Value.mp_ValueYamlMetadata.f_PruneStringMetadata();
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetLineComment(NStr::CStr &&_Value)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		if (_Value.f_IsEmpty() && !mp_Value.mp_ValueYamlMetadata.m_pStringMetadata)
			return;

		mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_LineComment = fg_Move(_Value);
		mp_Value.mp_ValueYamlMetadata.f_PruneStringMetadata();
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetTrailingComment(NStr::CStr &&_Value)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		if (_Value.f_IsEmpty() && !mp_Value.mp_ValueYamlMetadata.m_pStringMetadata)
			return;

		mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_TrailingComment = fg_Move(_Value);
		mp_Value.mp_ValueYamlMetadata.f_PruneStringMetadata();
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetScalarStyle(EYamlScalarStyle _Value)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		mp_Value.mp_ValueYamlMetadata.m_ScalarStyle = uint8(_Value);
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetNodeStyle(EYamlNodeStyle _Value)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		mp_Value.mp_ValueYamlMetadata.m_NodeStyle = uint8(_Value);
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetChompIndicator(uch8 _Value)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		mp_Value.mp_ValueYamlMetadata.m_ChompIndicator = _Value;
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetBlockIndentHint(smint _Value)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		mp_Value.mp_ValueYamlMetadata.m_BlockIndentHint = int8(_Value);
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_SetDocumentTagHandles(NContainer::TCMap<NStr::CStr, NStr::CStr> &&_Value)
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		if (_Value.f_IsEmpty() && !mp_Value.mp_ValueYamlMetadata.m_pStringMetadata)
			return;
		mp_Value.mp_ValueYamlMetadata.f_StringMetadata().m_DocumentTagHandles = fg_Move(_Value);
		mp_Value.mp_ValueYamlMetadata.f_PruneStringMetadata();
	}

	template <typename t_CValueBase>
	void TCYamlView<t_CValueBase>::f_ResetYamlMetadata()
		requires (t_CValueBase::mc_bPreserveYamlMetadata)
	{
		mp_Value.mp_ValueYamlMetadata = {};

		auto &Value = static_cast<typename t_CValueBase::CValue &>(mp_Value);

		if (Value.f_IsArray())
		{
			for (auto &Child : Value.f_Array())
				Child.f_Yaml().f_ResetYamlMetadata();
		}
		else if (Value.f_IsObject())
		{
			for (auto &Child : Value.f_Object())
			{
				Child.f_KeyYaml().f_ResetMetadataSlots();
				Child.f_Value().f_Yaml().f_ResetYamlMetadata();
			}
		}
		else if constexpr (requires { Value.f_EType(); Value.f_UserType(); })
		{
			if (Value.f_EType() == EEJsonType_UserType)
				Value.f_UserType().m_Value.f_Yaml().f_ResetYamlMetadata();
		}
	}

	template <typename t_CObjectEntry>
	TCYamlKeyConstView<t_CObjectEntry>::TCYamlKeyConstView(t_CObjectEntry const &_Entry)
		: mp_Entry(_Entry)
	{
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyConstView<t_CObjectEntry>::f_Anchor() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_AnchorName;
	}

	template <typename t_CObjectEntry>
	bool TCYamlKeyConstView<t_CObjectEntry>::f_HasAnchor() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		auto const &Metadata = mp_Entry.mp_KeyYamlMetadata;
		return Metadata.m_pStringMetadata && !Metadata.m_pStringMetadata->m_AnchorName.f_IsEmpty();
	}

	template <typename t_CObjectEntry>
	bool TCYamlKeyConstView<t_CObjectEntry>::f_HasTag() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		auto const &Metadata = mp_Entry.mp_KeyYamlMetadata;
		return Metadata.m_pStringMetadata && (!Metadata.m_pStringMetadata->m_TagHandle.f_IsEmpty() || !Metadata.m_pStringMetadata->m_TagResolved.f_IsEmpty());
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyConstView<t_CObjectEntry>::f_Alias() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_AliasName;
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyConstView<t_CObjectEntry>::f_TagHandle() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_TagHandle;
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyConstView<t_CObjectEntry>::f_TagSuffix() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_TagSuffix;
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyConstView<t_CObjectEntry>::f_TagResolved() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_TagResolved;
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyConstView<t_CObjectEntry>::f_LeadingComment() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_LeadingComment;
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyConstView<t_CObjectEntry>::f_LineComment() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_LineComment;
	}

	template <typename t_CObjectEntry>
	EYamlScalarStyle TCYamlKeyConstView<t_CObjectEntry>::f_ScalarStyle() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return EYamlScalarStyle(mp_Entry.mp_KeyYamlMetadata.m_ScalarStyle);
	}

	template <typename t_CObjectEntry>
	NPrivate::CYamlKeyMetadataSlots const &TCYamlKeyConstView<t_CObjectEntry>::f_MetadataSlots() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata;
	}

	template <typename t_CObjectEntry>
	TCYamlKeyView<t_CObjectEntry>::TCYamlKeyView(t_CObjectEntry &_Entry)
		: mp_Entry(_Entry)
	{
	}

	template <typename t_CObjectEntry>
	TCYamlKeyView<t_CObjectEntry>::operator TCYamlKeyConstView<t_CObjectEntry>() const
	{
		return TCYamlKeyConstView<t_CObjectEntry>(mp_Entry);
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyView<t_CObjectEntry>::f_Anchor() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_AnchorName;
	}

	template <typename t_CObjectEntry>
	bool TCYamlKeyView<t_CObjectEntry>::f_HasAnchor() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		auto const &Metadata = mp_Entry.mp_KeyYamlMetadata;
		return Metadata.m_pStringMetadata && !Metadata.m_pStringMetadata->m_AnchorName.f_IsEmpty();
	}

	template <typename t_CObjectEntry>
	bool TCYamlKeyView<t_CObjectEntry>::f_HasTag() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		auto const &Metadata = mp_Entry.mp_KeyYamlMetadata;
		return Metadata.m_pStringMetadata && (!Metadata.m_pStringMetadata->m_TagHandle.f_IsEmpty() || !Metadata.m_pStringMetadata->m_TagResolved.f_IsEmpty());
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyView<t_CObjectEntry>::f_Alias() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_AliasName;
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyView<t_CObjectEntry>::f_TagHandle() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_TagHandle;
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyView<t_CObjectEntry>::f_TagSuffix() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_TagSuffix;
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyView<t_CObjectEntry>::f_TagResolved() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_TagResolved;
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyView<t_CObjectEntry>::f_LeadingComment() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_LeadingComment;
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCYamlKeyView<t_CObjectEntry>::f_LineComment() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_LineComment;
	}

	template <typename t_CObjectEntry>
	EYamlScalarStyle TCYamlKeyView<t_CObjectEntry>::f_ScalarStyle() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return EYamlScalarStyle(mp_Entry.mp_KeyYamlMetadata.m_ScalarStyle);
	}

	template <typename t_CObjectEntry>
	NPrivate::CYamlKeyMetadataSlots const &TCYamlKeyView<t_CObjectEntry>::f_MetadataSlots() const
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return mp_Entry.mp_KeyYamlMetadata;
	}

	template <typename t_CObjectEntry>
	NPrivate::CYamlKeyMetadataSlots &&TCYamlKeyView<t_CObjectEntry>::f_MoveMetadataSlots()
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		return fg_Move(mp_Entry.mp_KeyYamlMetadata);
	}

	template <typename t_CObjectEntry>
	void TCYamlKeyView<t_CObjectEntry>::f_SetMetadataSlots(NPrivate::CYamlKeyMetadataSlots const &_Value)
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		mp_Entry.mp_KeyYamlMetadata = _Value;
	}

	template <typename t_CObjectEntry>
	void TCYamlKeyView<t_CObjectEntry>::f_SetMetadataSlots(NPrivate::CYamlKeyMetadataSlots &&_Value)
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		mp_Entry.mp_KeyYamlMetadata = fg_Move(_Value);
	}

	template <typename t_CObjectEntry>
	void TCYamlKeyView<t_CObjectEntry>::f_ResetMetadataSlots()
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		mp_Entry.mp_KeyYamlMetadata = {};
	}

	template <typename t_CObjectEntry>
	void TCYamlKeyView<t_CObjectEntry>::f_SetAnchor(NStr::CStr &&_Value)
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		if (_Value.f_IsEmpty() && !mp_Entry.mp_KeyYamlMetadata.m_pStringMetadata)
			return;

		mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_AnchorName = fg_Move(_Value);
		mp_Entry.mp_KeyYamlMetadata.f_PruneStringMetadata();
	}

	template <typename t_CObjectEntry>
	void TCYamlKeyView<t_CObjectEntry>::f_SetAlias(NStr::CStr &&_Value)
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		if (_Value.f_IsEmpty() && !mp_Entry.mp_KeyYamlMetadata.m_pStringMetadata)
			return;

		mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_AliasName = fg_Move(_Value);
		mp_Entry.mp_KeyYamlMetadata.f_PruneStringMetadata();
	}

	template <typename t_CObjectEntry>
	void TCYamlKeyView<t_CObjectEntry>::f_SetTag(NStr::CStr &&_Handle, NStr::CStr &&_Suffix, NStr::CStr &&_Resolved)
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		if (_Handle.f_IsEmpty() && _Suffix.f_IsEmpty() && _Resolved.f_IsEmpty() && !mp_Entry.mp_KeyYamlMetadata.m_pStringMetadata)
			return;

		auto &Strings = mp_Entry.mp_KeyYamlMetadata.f_StringMetadata();
		Strings.m_TagHandle = fg_Move(_Handle);
		Strings.m_TagSuffix = fg_Move(_Suffix);
		Strings.m_TagResolved = fg_Move(_Resolved);
		mp_Entry.mp_KeyYamlMetadata.f_PruneStringMetadata();
	}

	template <typename t_CObjectEntry>
	void TCYamlKeyView<t_CObjectEntry>::f_SetLeadingComment(NStr::CStr &&_Value)
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		if (_Value.f_IsEmpty() && !mp_Entry.mp_KeyYamlMetadata.m_pStringMetadata)
			return;

		mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_LeadingComment = fg_Move(_Value);
		mp_Entry.mp_KeyYamlMetadata.f_PruneStringMetadata();
	}

	template <typename t_CObjectEntry>
	void TCYamlKeyView<t_CObjectEntry>::f_SetLineComment(NStr::CStr &&_Value)
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		if (_Value.f_IsEmpty() && !mp_Entry.mp_KeyYamlMetadata.m_pStringMetadata)
			return;

		mp_Entry.mp_KeyYamlMetadata.f_StringMetadata().m_LineComment = fg_Move(_Value);
		mp_Entry.mp_KeyYamlMetadata.f_PruneStringMetadata();
	}

	template <typename t_CObjectEntry>
	void TCYamlKeyView<t_CObjectEntry>::f_SetScalarStyle(EYamlScalarStyle _Value)
		requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
	{
		mp_Entry.mp_KeyYamlMetadata.m_ScalarStyle = uint8(_Value);
	}
}
