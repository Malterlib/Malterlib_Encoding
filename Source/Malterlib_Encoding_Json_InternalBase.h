// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
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

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

	protected:
		template <typename t_CObjectEntry2>
		friend struct NEncoding::TCJsonKeyTriviaConstView;
		template <typename t_CObjectEntry2>
		friend struct NEncoding::TCJsonKeyTriviaView;

		t_CJsonValue mp_Value;
		DMibNoUniqueAddress TCConditional<mc_bPreserveComments, CJsonKeyTriviaSlots, CEmpty> mp_KeyTrivia;
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
