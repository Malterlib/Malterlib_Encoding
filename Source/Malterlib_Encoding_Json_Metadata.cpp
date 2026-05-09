// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding::NPrivate
{
	void CYamlValueMetadataSlots::f_ClearScalarMetadata()
	{
		if (m_pStringMetadata)
		{
			m_pStringMetadata->m_TagHandle = {};
			m_pStringMetadata->m_TagSuffix = {};
			m_pStringMetadata->m_TagResolved = {};
			f_PruneStringMetadata();
		}
		m_ScalarStyle = EYamlScalarStyle_Unspecified;
		m_ChompIndicator = 0;
		m_BlockIndentHint = -1;
	}

	bool CYamlValueStringMetadata::f_IsEmpty() const
	{
		return
			m_AnchorName.f_IsEmpty()
			&& m_AliasName.f_IsEmpty()
			&& m_TagHandle.f_IsEmpty()
			&& m_TagSuffix.f_IsEmpty()
			&& m_TagResolved.f_IsEmpty()
			&& m_LeadingComment.f_IsEmpty()
			&& m_LineComment.f_IsEmpty()
			&& m_TrailingComment.f_IsEmpty()
			&& m_DocumentTagHandles.f_IsEmpty()
		;
	}

	CYamlValueMetadataSlots::CYamlValueMetadataSlots(CYamlValueMetadataSlots const &_Other)
		: m_ScalarStyle(_Other.m_ScalarStyle)
		, m_NodeStyle(_Other.m_NodeStyle)
		, m_ChompIndicator(_Other.m_ChompIndicator)
		, m_BlockIndentHint(_Other.m_BlockIndentHint)
	{
		if (_Other.m_pStringMetadata)
			m_pStringMetadata = fg_Construct<CYamlValueStringMetadata>(*_Other.m_pStringMetadata);
	}

	CYamlValueMetadataSlots &CYamlValueMetadataSlots::operator = (CYamlValueMetadataSlots const &_Other)
	{
		m_ScalarStyle = _Other.m_ScalarStyle;
		m_NodeStyle = _Other.m_NodeStyle;
		m_ChompIndicator = _Other.m_ChompIndicator;
		m_BlockIndentHint = _Other.m_BlockIndentHint;
		if (_Other.m_pStringMetadata)
			m_pStringMetadata = fg_Construct<CYamlValueStringMetadata>(*_Other.m_pStringMetadata);
		else
			m_pStringMetadata = nullptr;
		return *this;
	}

	CYamlValueStringMetadata const &CYamlValueMetadataSlots::f_StringMetadata() const
	{
		// All metadata members are constexpr-constructible, so this can stay in static storage without runtime setup.
		constexpr static CYamlValueStringMetadata c_Empty;
		return m_pStringMetadata ? *m_pStringMetadata : c_Empty;
	}

	CYamlValueStringMetadata &CYamlValueMetadataSlots::f_StringMetadata()
	{
		if (!m_pStringMetadata)
			m_pStringMetadata = fg_Construct<CYamlValueStringMetadata>();
		return *m_pStringMetadata;
	}

	void CYamlValueMetadataSlots::f_PruneStringMetadata()
	{
		if (m_pStringMetadata && m_pStringMetadata->f_IsEmpty())
			m_pStringMetadata = nullptr;
	}

	bool CYamlKeyStringMetadata::f_IsEmpty() const
	{
		return
			m_AnchorName.f_IsEmpty()
			&& m_AliasName.f_IsEmpty()
			&& m_TagHandle.f_IsEmpty()
			&& m_TagSuffix.f_IsEmpty()
			&& m_TagResolved.f_IsEmpty()
			&& m_LeadingComment.f_IsEmpty()
			&& m_LineComment.f_IsEmpty()
		;
	}

	CYamlKeyMetadataSlots::CYamlKeyMetadataSlots(CYamlKeyMetadataSlots const &_Other)
		: m_ScalarStyle(_Other.m_ScalarStyle)
	{
		if (_Other.m_pStringMetadata)
			m_pStringMetadata = fg_Construct<CYamlKeyStringMetadata>(*_Other.m_pStringMetadata);
	}

	CYamlKeyMetadataSlots &CYamlKeyMetadataSlots::operator = (CYamlKeyMetadataSlots const &_Other)
	{
		m_ScalarStyle = _Other.m_ScalarStyle;
		if (_Other.m_pStringMetadata)
			m_pStringMetadata = fg_Construct<CYamlKeyStringMetadata>(*_Other.m_pStringMetadata);
		else
			m_pStringMetadata = nullptr;
		return *this;
	}

	CYamlKeyStringMetadata const &CYamlKeyMetadataSlots::f_StringMetadata() const
	{
		// All metadata members are constexpr-constructible, so this can stay in static storage without runtime setup.
		constexpr static CYamlKeyStringMetadata c_Empty;
		return m_pStringMetadata ? *m_pStringMetadata : c_Empty;
	}

	CYamlKeyStringMetadata &CYamlKeyMetadataSlots::f_StringMetadata()
	{
		if (!m_pStringMetadata)
			m_pStringMetadata = fg_Construct<CYamlKeyStringMetadata>();
		return *m_pStringMetadata;
	}

	void CYamlKeyMetadataSlots::f_PruneStringMetadata()
	{
		if (m_pStringMetadata && m_pStringMetadata->f_IsEmpty())
			m_pStringMetadata = nullptr;
	}
}
