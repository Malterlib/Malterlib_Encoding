#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib::NEncoding
{
	template <typename t_CJSONValue, bool t_bOrdered>
	struct TCJSONObject;
}

namespace NMib::NEncoding::NPrivate
{
	struct CObjectEntryBase
	{
		template <typename t_CJSONValue, bool t_bOrdered>
		friend struct NEncoding::TCJSONObject;

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

	template <typename t_CJSONValue, bool t_bOrdered>
	struct TCObjectEntry : public TCChooseType<t_bOrdered, CObjectEntryBase, CEmpty>::CType
	{
		template <typename t_CJSONValue2, bool t_bOrdered2>
		friend struct NEncoding::TCJSONObject;

	public:
		TCObjectEntry();
		~TCObjectEntry() = default;

		bool operator == (TCObjectEntry const &_Right) const;
		COrdering_Partial operator <=> (TCObjectEntry const &_Right) const;

		NStr::CStr const &f_Name() const;
		t_CJSONValue &f_Value();
		t_CJSONValue const &f_Value() const;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

	protected:
		t_CJSONValue mp_Value;
	};
}
