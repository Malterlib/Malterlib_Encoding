// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
	namespace NPrivate
	{
		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJsonValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJsonValueBase(TCJsonValueBase const &_Value)
			: mp_Value(_Value.mp_Value)
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJsonValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJsonValueBase(TCJsonValueBase &_Value)
			: mp_Value(_Value.mp_Value)
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJsonValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJsonValueBase(TCJsonValueBase &&_Value)
			: mp_Value(fg_Move(_Value.mp_Value))
		{
			_Value.mp_Value.template f_Set<EJsonType_Invalid>();
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, bool tf_bOrdered>
		TCJsonValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJsonValueBase(TCJsonValueBase<tf_TCValue, tf_CTypes, tf_bOrdered> const &_Value)
		{
			_Value.mp_Value.f_Visit
				(
					[&](auto &&_Value)
					{
						if constexpr (NTraits::cIsSame<NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>, CVoidTag>)
							mp_Value.template f_Set<EJsonType_Invalid>();
						else if constexpr (NContainer::NPrivate::TCIsVector<NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>>::mc_bValue)
						{
							auto &OutArray = mp_Value.template f_Set<EJsonType_Array>();
							for (auto &Value : _Value)
								OutArray.f_Insert(CValue(Value));
						}
						else
							mp_Value = _Value;
					}
				)
			;
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, bool tf_bOrdered>
		TCJsonValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJsonValueBase(TCJsonValueBase<tf_TCValue, tf_CTypes, tf_bOrdered> &_Value)
		{
			_Value.mp_Value.f_Visit
				(
					[&](auto &&_Value)
					{
						if constexpr (NTraits::cIsSame<NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>, CVoidTag>)
							mp_Value.template f_Set<EJsonType_Invalid>();
						else if constexpr (NContainer::NPrivate::TCIsVector<NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>>::mc_bValue)
						{
							auto &OutArray = mp_Value.template f_Set<EJsonType_Array>();
							for (auto &Value : _Value)
								OutArray.f_Insert(CValue(Value));
						}
						else
							mp_Value = _Value;
					}
				)
			;
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, bool tf_bOrdered>
		TCJsonValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJsonValueBase(TCJsonValueBase<tf_TCValue, tf_CTypes, tf_bOrdered> &&_Value)
		{
			_Value.mp_Value.f_Visit
				(
					[&](auto &&_Value)
					{
						if constexpr (NTraits::cIsSame<NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>, CVoidTag>)
							mp_Value.template f_Set<EJsonType_Invalid>();
						else if constexpr (NContainer::NPrivate::TCIsVector<NTraits::TCRemoveReferenceAndQualifiers<decltype(_Value)>>::mc_bValue)
						{
							auto &OutArray = mp_Value.template f_Set<EJsonType_Array>();
							for (auto &Value : _Value)
								OutArray.f_Insert(CValue(fg_Move(Value)));
						}
						else
							mp_Value = fg_Move(_Value);
					}
				)
			;
			_Value.mp_Value.template f_Set<EJsonType_Invalid>();
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJsonValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJsonValueBase(bool _Value)
			: mp_Value(CJsonBoolean(_Value))
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJsonValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJsonValueBase(pfp64 _Value)
			: mp_Value(fp64(_Value))
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJsonValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJsonValueBase(pfp32 _Value)
			: mp_Value(fp64(_Value))
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJsonValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJsonValueBase(fp32 _Value)
			: mp_Value(fp64(_Value))
		{
		}


		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJsonValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJsonValueBase()
		{
		}

		template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
		TCJsonValueBase<t_TCValue, t_CTypes, t_bOrdered>::~TCJsonValueBase()
		{
		}

		template <typename t_CJsonValue, bool t_bOrdered>
		TCObjectEntry<t_CJsonValue, t_bOrdered>::TCObjectEntry()
		{
		}

		template <typename t_CJsonValue, bool t_bOrdered>
		NStr::CStr const &TCObjectEntry<t_CJsonValue, t_bOrdered>::f_Name() const
		{
			if constexpr (t_bOrdered)
				return this->mp_Name;
			else
				return NContainer::TCMap<NStr::CStr, TCObjectEntry>::fs_GetKey(*this);
		}

		template <typename t_CJsonValue, bool t_bOrdered>
		NStr::CStr const &TCObjectEntry<t_CJsonValue, t_bOrdered>::f_Key() const
		{
			return f_Name();
		}

		template <typename t_CJsonValue, bool t_bOrdered>
		t_CJsonValue &TCObjectEntry<t_CJsonValue, t_bOrdered>::f_Value()
		{
			return mp_Value;
		}

		template <typename t_CJsonValue, bool t_bOrdered>
		t_CJsonValue const &TCObjectEntry<t_CJsonValue, t_bOrdered>::f_Value() const
		{
			return mp_Value;
		}

		template <typename t_CJsonValue, bool t_bOrdered>
		bool TCObjectEntry<t_CJsonValue, t_bOrdered>::operator == (TCObjectEntry const &_Right) const noexcept
		{
			if (f_Name() != _Right.f_Name())
				return false;
			return mp_Value == _Right.mp_Value;
		}

		template <typename t_CJsonValue, bool t_bOrdered>
		COrdering_Partial TCObjectEntry<t_CJsonValue, t_bOrdered>::operator <=> (TCObjectEntry const &_Right) const noexcept
		{
			if (auto Result = f_Name() <=> _Right.f_Name(); Result != 0)
				return Result;

			return mp_Value <=> _Right.mp_Value;
		}
	}
}

#include "Malterlib_Encoding_Json_Value.hpp"
#include "Malterlib_Encoding_Json_Object.hpp"
