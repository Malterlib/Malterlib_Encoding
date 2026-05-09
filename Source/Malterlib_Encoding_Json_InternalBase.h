// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"
#include <Mib/Storage/UniquePointer>

namespace NMib::NEncoding
{
	enum EYamlScalarStyle : uint8
	{
		EYamlScalarStyle_Unspecified = 0
		, EYamlScalarStyle_Plain
		, EYamlScalarStyle_SingleQuoted
		, EYamlScalarStyle_DoubleQuoted
		, EYamlScalarStyle_Literal
		, EYamlScalarStyle_Folded
	};

	enum EYamlNodeStyle : uint8
	{
		EYamlNodeStyle_Unspecified = 0
		, EYamlNodeStyle_Block
		, EYamlNodeStyle_Flow
	};

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	struct TCJsonObject;

	template <typename t_CParent>
	struct TCJsonValue;

	template <typename t_CParent>
	struct TCEJsonValue;

	template <typename t_CValueBase>
	struct TCYamlConstView;

	template <typename t_CValueBase>
	struct TCYamlView;

	template <typename t_CValueBase>
	struct TCJsonTriviaConstView;

	template <typename t_CValueBase>
	struct TCJsonTriviaView;

	template <typename t_CObjectEntry>
	struct TCJsonKeyTriviaConstView;

	template <typename t_CObjectEntry>
	struct TCJsonKeyTriviaView;

	template <typename t_CValueBase>
	struct TCYamlConstView;

	template <typename t_CValueBase>
	struct TCYamlView;

	template <typename t_CObjectEntry>
	struct TCYamlKeyConstView;

	template <typename t_CObjectEntry>
	struct TCYamlKeyView;
}

namespace NMib::NEncoding::NPrivate
{
	struct CJsonValueTriviaSlots
	{
		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

		NStr::CStr m_Leading;
		NStr::CStr m_Trailing;
		NStr::CStr m_Interior;
		bool m_bLeadingSet = false;
		bool m_bTrailingSet = false;
		bool m_bLeadingHasComma = false;
		bool m_bTrailingHasComma = false;
	};

	struct CJsonKeyTriviaSlots
	{
		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

		NStr::CStr m_Leading;
		NStr::CStr m_Trailing;
		bool m_bLeadingSet = false;
		bool m_bTrailingSet = false;
		bool m_bLeadingHasComma = false;
	};

	struct CYamlMetadataEmpty
	{
	};

	struct CYamlValueStringMetadata
	{
		bool f_IsEmpty() const;

		NStr::CStr m_AnchorName;
		NStr::CStr m_AliasName;
		NStr::CStr m_TagHandle;
		NStr::CStr m_TagSuffix;
		NStr::CStr m_TagResolved;
		NStr::CStr m_LeadingComment;
		NStr::CStr m_LineComment;
		NStr::CStr m_TrailingComment;
		NContainer::TCMap<NStr::CStr, NStr::CStr> m_DocumentTagHandles;
	};

	struct CYamlKeyStringMetadata
	{
		bool f_IsEmpty() const;

		NStr::CStr m_AnchorName;
		NStr::CStr m_AliasName;
		NStr::CStr m_TagHandle;
		NStr::CStr m_TagSuffix;
		NStr::CStr m_TagResolved;
		NStr::CStr m_LeadingComment;
		NStr::CStr m_LineComment;
	};

	struct CYamlValueMetadataSlots
	{
		CYamlValueMetadataSlots() = default;
		CYamlValueMetadataSlots(CYamlValueMetadataSlots const &_Other);
		CYamlValueMetadataSlots(CYamlValueMetadataSlots &&_Other) = default;
		CYamlValueMetadataSlots &operator = (CYamlValueMetadataSlots const &_Other);
		CYamlValueMetadataSlots &operator = (CYamlValueMetadataSlots &&_Other) = default;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

		void f_ClearScalarMetadata();
		CYamlValueStringMetadata const &f_StringMetadata() const;
		CYamlValueStringMetadata &f_StringMetadata();
		void f_PruneStringMetadata();

		NStorage::TCUniquePointer<CYamlValueStringMetadata> m_pStringMetadata;
		uint8 m_ScalarStyle = EYamlScalarStyle_Unspecified;
		uint8 m_NodeStyle = EYamlNodeStyle_Unspecified;
		uint8 m_ChompIndicator = 0;
		int8 m_BlockIndentHint = -1;
	};

	struct CYamlKeyMetadataSlots
	{
		CYamlKeyMetadataSlots() = default;
		CYamlKeyMetadataSlots(CYamlKeyMetadataSlots const &_Other);
		CYamlKeyMetadataSlots(CYamlKeyMetadataSlots &&_Other) = default;
		CYamlKeyMetadataSlots &operator = (CYamlKeyMetadataSlots const &_Other);
		CYamlKeyMetadataSlots &operator = (CYamlKeyMetadataSlots &&_Other) = default;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

		CYamlKeyStringMetadata const &f_StringMetadata() const;
		CYamlKeyStringMetadata &f_StringMetadata();
		void f_PruneStringMetadata();

		NStorage::TCUniquePointer<CYamlKeyStringMetadata> m_pStringMetadata;
		uint8 m_ScalarStyle = EYamlScalarStyle_Unspecified;
	};

	struct CObjectEntryBase
	{
		template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
		friend struct NEncoding::TCJsonObject;

	protected:

		NStr::CStr mp_Name;
		NIntrusive::TCAVLLink<> mp_Link;

		CObjectEntryBase();
		CObjectEntryBase(CObjectEntryBase const &_Other);
		CObjectEntryBase(CObjectEntryBase &&_Other);

		struct CCompare
		{
		public:
			inline_small NStr::CStr const &operator () (CObjectEntryBase const &_Node) const
			{
				return _Node.mp_Name;
			}
		};
	};

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	struct TCObjectEntry : public TCConditional<TCJsonContainerFlagTraits<t_ContainerFlags>::mc_bOrdered, CObjectEntryBase, CEmpty>
	{
		static constexpr EJsonContainerFlag mc_ContainerFlags = t_ContainerFlags;
		static constexpr bool mc_bOrdered = TCJsonContainerFlagTraits<t_ContainerFlags>::mc_bOrdered;
		static constexpr bool mc_bPreserveComments = TCJsonContainerFlagTraits<t_ContainerFlags>::mc_bPreserveComments;
		static constexpr bool mc_bPreserveYamlMetadata = TCJsonContainerFlagTraits<t_ContainerFlags>::mc_bPreserveYamlMetadata;

		template <typename t_CJsonValue2, EJsonContainerFlag t_ContainerFlags2>
		friend struct NEncoding::TCJsonObject;

	public:
		TCObjectEntry();
		~TCObjectEntry() = default;

		bool operator == (TCObjectEntry const &_Right) const noexcept;
		COrdering_Partial operator <=> (TCObjectEntry const &_Right) const noexcept;

		NStr::CStr const &f_Name() const;
		NStr::CStr const &f_Key() const;
		t_CJsonValue &f_Value();
		t_CJsonValue const &f_Value() const;

		TCJsonKeyTriviaView<TCObjectEntry> f_KeyTrivia()
			requires (mc_bPreserveComments)
		;
		TCJsonKeyTriviaConstView<TCObjectEntry> f_KeyTrivia() const
			requires (mc_bPreserveComments)
		;

		TCYamlKeyView<TCObjectEntry> f_KeyYaml()
			requires (mc_bPreserveYamlMetadata)
		;
		TCYamlKeyConstView<TCObjectEntry> f_KeyYaml() const
			requires (mc_bPreserveYamlMetadata)
		;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

	protected:
		template <typename t_CObjectEntry2>
		friend struct NEncoding::TCJsonKeyTriviaConstView;
		template <typename t_CObjectEntry2>
		friend struct NEncoding::TCJsonKeyTriviaView;

		template <typename t_CValueBase>
		friend struct NEncoding::TCYamlConstView;
		template <typename t_CValueBase>
		friend struct NEncoding::TCYamlView;
		template <typename t_CObjectEntry2>
		friend struct NEncoding::TCYamlKeyConstView;
		template <typename t_CObjectEntry2>
		friend struct NEncoding::TCYamlKeyView;

		t_CJsonValue mp_Value;
		DMibNoUniqueAddress TCConditional<mc_bPreserveComments, CJsonKeyTriviaSlots, CEmpty> mp_KeyTrivia;
		DMibNoUniqueAddress TCConditional<mc_bPreserveYamlMetadata, CYamlKeyMetadataSlots, CYamlMetadataEmpty> mp_KeyYamlMetadata;
	};

	template <typename t_CType>
	struct TCIsTCJsonValue
	{
		constexpr static bool mc_Value = false;
	};

	template <typename t_CParent>
	struct TCIsTCJsonValue<TCJsonValue<t_CParent>>
	{
		constexpr static bool mc_Value = true;
	};

	template <typename t_CType>
	struct TCIsTCEJsonValue
	{
		constexpr static bool mc_Value = false;
	};

	template <typename t_CParent>
	struct TCIsTCEJsonValue<TCEJsonValue<t_CParent>>
	{
		constexpr static bool mc_Value = true;
	};
}
