// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib::NEncoding
{
	namespace NPrivate
	{
		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJSONValueBase(TCJSONValueBase const &_Value)
			: mp_Value(_Value.mp_Value)
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJSONValueBase(TCJSONValueBase &_Value)
			: mp_Value(_Value.mp_Value)
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJSONValueBase(TCJSONValueBase &&_Value)
			: mp_Value(fg_Move(_Value.mp_Value))
		{
			_Value.mp_Value.template f_Set<EJSONType_Invalid>();
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJSONValueBase(bool _Value)
			: mp_Value(CJSONBoolean(_Value))
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJSONValueBase(pfp64 _Value)
			: mp_Value(fp64(_Value))
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJSONValueBase(pfp32 _Value)
			: mp_Value(fp64(_Value))
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJSONValueBase(fp32 _Value)
			: mp_Value(fp64(_Value))
		{
		}


		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJSONValueBase()
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::~TCJSONValueBase()
		{
		}

		template <typename t_CJSONValue, bool t_bOrdered>
		TCObjectEntry<t_CJSONValue, t_bOrdered>::TCObjectEntry()
		{
		}

		template <typename t_CJSONValue, bool t_bOrdered>
		NStr::CStr const &TCObjectEntry<t_CJSONValue, t_bOrdered>::f_Name() const
		{
			if constexpr (t_bOrdered)
				return this->mp_Name;
			else
				return NContainer::TCMap<NStr::CStr, TCObjectEntry>::fs_GetKey(*this);
		}

		template <typename t_CJSONValue, bool t_bOrdered>
		t_CJSONValue &TCObjectEntry<t_CJSONValue, t_bOrdered>::f_Value()
		{
			return mp_Value;
		}

		template <typename t_CJSONValue, bool t_bOrdered>
		t_CJSONValue const &TCObjectEntry<t_CJSONValue, t_bOrdered>::f_Value() const
		{
			return mp_Value;
		}

		template <typename t_CJSONValue, bool t_bOrdered>
		bool TCObjectEntry<t_CJSONValue, t_bOrdered>::operator == (TCObjectEntry const &_Right) const
		{
			if (f_Name() != _Right.f_Name())
				return false;
			return mp_Value == _Right.mp_Value;
		}

		template <typename t_CJSONValue, bool t_bOrdered>
		COrdering_Partial TCObjectEntry<t_CJSONValue, t_bOrdered>::operator <=> (TCObjectEntry const &_Right) const
		{
			if (auto Result = f_Name() <=> _Right.f_Name(); Result != 0)
				return Result;

			return mp_Value <=> _Right.mp_Value;
		}
	}
}

#include "Malterlib_Encoding_JSON_Value.hpp"
#include "Malterlib_Encoding_JSON_Object.hpp"
