// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Encoding/JSON>
#include <Mib/Encoding/EJSON>

namespace NMib::NEncoding
{
	template <typename tf_CValue>
	CEJSONSorted fg_ToJson(tf_CValue &&_Value)
		requires requires(tf_CValue &&_Value)
		{
			fg_Forward<tf_CValue>(_Value).f_ToJson();
		}
	;

	template <typename tf_CValue>
	CEJSONSorted fg_ToJson(tf_CValue &&_Value)
		requires (NTraits::TCIsEnum<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CValue>::CType>::mc_Value)
	;

	CEJSONSorted fg_ToJson(CJSONSorted const &_Value);
	CEJSONSorted fg_ToJson(NStr::CStr const &_Value);
	CEJSONSorted fg_ToJson(int64 _Value);
	CEJSONSorted fg_ToJson(uint64 _Value);
	CEJSONSorted fg_ToJson(bool _Value);
	CEJSONSorted fg_ToJson(uint32 _Value);
	CEJSONSorted fg_ToJson(int32 _Value);
	CEJSONSorted fg_ToJson(int16 _Value);
	CEJSONSorted fg_ToJson(uint16 _Value);
	CEJSONSorted fg_ToJson(int8 _Value);
	CEJSONSorted fg_ToJson(uint8 _Value);
	CEJSONSorted fg_ToJson(fp64 _Value);
	CEJSONSorted fg_ToJson(fp32 _Value);
	CEJSONSorted fg_ToJson(NTime::CTime const &_Value);
	CEJSONSorted fg_ToJson(NTime::CTimeSpan const &_Value);
	CEJSONSorted fg_ToJson(NContainer::CByteVector const &_Value);

	template <typename tf_CValue>
	CEJSONSorted fg_ToJson(NStorage::TCOptional<tf_CValue> const &_Value);

	template <typename tf_CValue>
	CEJSONSorted fg_ToJson(NContainer::TCVector<tf_CValue> const &_Value);

	template <typename tf_CValue>
	CEJSONSorted fg_ToJson(NContainer::TCMap<NStr::CStr, tf_CValue> const &_Value);

	template <typename tf_CKey, typename tf_CValue>
	CEJSONSorted fg_ToJson(NContainer::TCMap<tf_CKey, tf_CValue> const &_Value);

	template <typename tf_CKey>
	CEJSONSorted fg_ToJson(NContainer::TCSet<tf_CKey> const &_Value);
}

#include "Malterlib_Encoding_ToJson.hpp"
