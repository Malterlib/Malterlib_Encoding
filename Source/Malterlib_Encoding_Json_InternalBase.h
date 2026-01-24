// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
	template <typename t_CJsonValue, bool t_bOrdered>
	struct TCJsonObject;

	template <typename t_CParent>
	struct TCJsonValue;

	template <typename t_CParent>
	struct TCEJsonValue;
}

namespace NMib::NEncoding::NPrivate
{
	struct CObjectEntryBase
	{
		template <typename t_CJsonValue, bool t_bOrdered>
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

	template <typename t_CJsonValue, bool t_bOrdered>
	struct TCObjectEntry : public TCConditional<t_bOrdered, CObjectEntryBase, CEmpty>
	{
		template <typename t_CJsonValue2, bool t_bOrdered2>
		friend struct NEncoding::TCJsonObject;

	public:
		TCObjectEntry();
		~TCObjectEntry() = default;

		bool operator == (TCObjectEntry const &_Right) const;
		COrdering_Partial operator <=> (TCObjectEntry const &_Right) const;

		NStr::CStr const &f_Name() const;
		NStr::CStr const &f_Key() const;
		t_CJsonValue &f_Value();
		t_CJsonValue const &f_Value() const;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

	protected:
		t_CJsonValue mp_Value;
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
