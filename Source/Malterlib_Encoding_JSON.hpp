// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib
{
	namespace NEncoding
	{
		namespace NPrivate
		{
			template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
			TCJSONValueBase<t_TCValue, t_CTypes>::TCJSONValueBase(TCJSONValueBase const &_Value)
				: mp_Value(_Value.mp_Value)
			{
			}

			template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
			TCJSONValueBase<t_TCValue, t_CTypes>::TCJSONValueBase(TCJSONValueBase &_Value)
				: mp_Value(_Value.mp_Value)
			{
			}

			template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
			TCJSONValueBase<t_TCValue, t_CTypes>::TCJSONValueBase(TCJSONValueBase &&_Value)
				: mp_Value(fg_Move(_Value.mp_Value))
			{
			}

			template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
			TCJSONValueBase<t_TCValue, t_CTypes>::TCJSONValueBase(bool _Value)
				: mp_Value(CJSONBoolean(_Value))
			{
			}
			
			template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
			TCJSONValueBase<t_TCValue, t_CTypes>::TCJSONValueBase(pfp64 _Value)
				: mp_Value(fp64(_Value))
			{
			}
			
			template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
			TCJSONValueBase<t_TCValue, t_CTypes>::TCJSONValueBase(pfp32 _Value)
				: mp_Value(fp64(_Value))
			{
			}

			template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
			TCJSONValueBase<t_TCValue, t_CTypes>::TCJSONValueBase(fp32 _Value)
				: mp_Value(fp64(_Value))
			{
			}
			

			template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
			TCJSONValueBase<t_TCValue, t_CTypes>::TCJSONValueBase()
			{
			}
			
			template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
			TCJSONValueBase<t_TCValue, t_CTypes>::~TCJSONValueBase()
			{
			}
			
			template <typename t_CJSONValue>
			TCObjectEntry<t_CJSONValue>::TCObjectEntry()
			{
			}

			template <typename t_CJSONValue>
			NStr::CStr const &TCObjectEntry<t_CJSONValue>::f_Name() const
			{
				return this->mp_Name;
			}

			template <typename t_CJSONValue>
			t_CJSONValue &TCObjectEntry<t_CJSONValue>::f_Value()
			{
				return mp_Value;
			}

			template <typename t_CJSONValue>
			t_CJSONValue const &TCObjectEntry<t_CJSONValue>::f_Value() const
			{
				return mp_Value;
			}

			template <typename t_CJSONValue>
			bool TCObjectEntry<t_CJSONValue>::operator == (TCObjectEntry const &_Right) const
			{
				if (mp_Name != _Right.mp_Name)
					return false;
				return mp_Value == _Right.mp_Value;
			}

			template <typename t_CJSONValue>
			bool TCObjectEntry<t_CJSONValue>::operator < (TCObjectEntry const &_Right) const
			{
				if (mp_Name < _Right.mp_Name)
					return true;
				else if (mp_Name > _Right.mp_Name)
					return false;
				return mp_Value < _Right.mp_Value;
			}
		}
	}
}

#include "Malterlib_Encoding_JSON_Value.hpp"
#include "Malterlib_Encoding_JSON_Object.hpp"
