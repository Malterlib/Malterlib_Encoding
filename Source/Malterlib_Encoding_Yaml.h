// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json_Parse.h"
#include "Malterlib_Encoding_Json_Generate.h"
#include "Malterlib_Encoding_EJson.h"

#include <Mib/Encoding/Base64>

namespace NMib::NEncoding
{
	inline NTime::CTime fg_ParseYamlTimestamp(NStr::CStr const &_String);
	inline NStr::CStr fg_FormatYamlTimestamp(NTime::CTime const &_Time);

	template <typename t_CValueBase>
	struct TCYamlConstView
	{
		explicit TCYamlConstView(t_CValueBase const &_Value);

		NStr::CStr const &f_Anchor() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		bool f_HasAnchor() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		bool f_HasTag() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_Alias() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TagHandle() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TagSuffix() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TagResolved() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_LeadingComment() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_LineComment() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TrailingComment() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		EYamlScalarStyle f_ScalarStyle() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		EYamlNodeStyle f_NodeStyle() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		uch8 f_ChompIndicator() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		smint f_BlockIndentHint() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NContainer::TCMap<NStr::CStr, NStr::CStr> const &f_DocumentTagHandles() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NPrivate::CYamlValueMetadataSlots const &f_MetadataSlots() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;

	private:
		t_CValueBase const &mp_Value;
	};

	template <typename t_CValueBase>
	struct TCYamlView
	{
		explicit TCYamlView(t_CValueBase &_Value);

		operator TCYamlConstView<t_CValueBase>() const;

		NStr::CStr const &f_Anchor() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		bool f_HasAnchor() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		bool f_HasTag() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_Alias() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TagHandle() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TagSuffix() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TagResolved() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_LeadingComment() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_LineComment() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TrailingComment() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		EYamlScalarStyle f_ScalarStyle() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		EYamlNodeStyle f_NodeStyle() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		uch8 f_ChompIndicator() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		smint f_BlockIndentHint() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NContainer::TCMap<NStr::CStr, NStr::CStr> &f_DocumentTagHandles()
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NPrivate::CYamlValueMetadataSlots const &f_MetadataSlots() const
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		NPrivate::CYamlValueMetadataSlots &&f_MoveMetadataSlots()
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_SetMetadataSlots(NPrivate::CYamlValueMetadataSlots const &_Value)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_SetMetadataSlots(NPrivate::CYamlValueMetadataSlots &&_Value)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_ResetMetadataSlots()
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;

		void f_SetAnchor(NStr::CStr &&_Value)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_SetAlias(NStr::CStr &&_Value)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_SetTag(NStr::CStr &&_Handle, NStr::CStr &&_Suffix, NStr::CStr &&_Resolved)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_SetLeadingComment(NStr::CStr &&_Value)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_SetLineComment(NStr::CStr &&_Value)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_SetTrailingComment(NStr::CStr &&_Value)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_SetScalarStyle(EYamlScalarStyle _Value)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_SetNodeStyle(EYamlNodeStyle _Value)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_SetChompIndicator(uch8 _Value)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_SetBlockIndentHint(smint _Value)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_SetDocumentTagHandles(NContainer::TCMap<NStr::CStr, NStr::CStr> &&_Value)
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;
		void f_ResetYamlMetadata()
			requires (t_CValueBase::mc_bPreserveYamlMetadata)
		;

	private:
		t_CValueBase &mp_Value;
	};

	template <typename t_CObjectEntry>
	struct TCYamlKeyConstView
	{
		explicit TCYamlKeyConstView(t_CObjectEntry const &_Entry);

		NStr::CStr const &f_Anchor() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		bool f_HasAnchor() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		bool f_HasTag() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_Alias() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TagHandle() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TagSuffix() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TagResolved() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_LeadingComment() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_LineComment() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		EYamlScalarStyle f_ScalarStyle() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NPrivate::CYamlKeyMetadataSlots const &f_MetadataSlots() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;

	private:
		t_CObjectEntry const &mp_Entry;
	};

	template <typename t_CObjectEntry>
	struct TCYamlKeyView
	{
		explicit TCYamlKeyView(t_CObjectEntry &_Entry);

		operator TCYamlKeyConstView<t_CObjectEntry>() const;

		NStr::CStr const &f_Anchor() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		bool f_HasAnchor() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		bool f_HasTag() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_Alias() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TagHandle() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TagSuffix() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_TagResolved() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_LeadingComment() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NStr::CStr const &f_LineComment() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		EYamlScalarStyle f_ScalarStyle() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NPrivate::CYamlKeyMetadataSlots const &f_MetadataSlots() const
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		NPrivate::CYamlKeyMetadataSlots &&f_MoveMetadataSlots()
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		void f_SetMetadataSlots(NPrivate::CYamlKeyMetadataSlots const &_Value)
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		void f_SetMetadataSlots(NPrivate::CYamlKeyMetadataSlots &&_Value)
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		void f_ResetMetadataSlots()
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		void f_SetAnchor(NStr::CStr &&_Value)
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		void f_SetAlias(NStr::CStr &&_Value)
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		void f_SetTag(NStr::CStr &&_Handle, NStr::CStr &&_Suffix, NStr::CStr &&_Resolved)
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		void f_SetLeadingComment(NStr::CStr &&_Value)
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		void f_SetLineComment(NStr::CStr &&_Value)
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;
		void f_SetScalarStyle(EYamlScalarStyle _Value)
			requires (t_CObjectEntry::mc_bPreserveYamlMetadata)
		;

	private:
		t_CObjectEntry &mp_Entry;
	};
}

namespace NMib::NEncoding::NYaml
{
	struct CParseContext : public NJson::CParseContext
	{
		NContainer::TCMap<NStr::CStr, NStr::CStr> m_TagHandles;
		NContainer::TCMap<NStr::CStr, NStr::CStr> m_DocumentTagHandles;
		umint m_nFlowDepth = 0;

		static constexpr bool mc_bRecordYamlMetadata = false;
		static constexpr bool mc_bAllowBlockStyle = true;
		static constexpr bool mc_bAllowFlowStyle = true;
		static constexpr bool mc_bAllowDuplicateKeys = false;
	};

	struct CRecordingParseContext : public CParseContext
	{
		static constexpr bool mc_bRecordYamlMetadata = true;
	};

	struct CBlockOnlyParseContext : public CParseContext
	{
		static constexpr bool mc_bAllowFlowStyle = false;
	};

	struct CBlockOnlyRecordingParseContext : public CRecordingParseContext
	{
		static constexpr bool mc_bAllowFlowStyle = false;
	};

	struct CFlowOnlyParseContext : public CParseContext
	{
		static constexpr bool mc_bAllowBlockStyle = false;
	};

	struct CFlowOnlyRecordingParseContext : public CRecordingParseContext
	{
		static constexpr bool mc_bAllowBlockStyle = false;
	};
}

#include "Malterlib_Encoding_Yaml.hpp"
