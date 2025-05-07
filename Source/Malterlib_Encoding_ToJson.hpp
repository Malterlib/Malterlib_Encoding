// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NEncoding
{
	template <typename tf_CValue>
	CEJsonSorted fg_ToJson(tf_CValue &&_Value)
		requires requires(tf_CValue &&_Value)
		{
			fg_Forward<tf_CValue>(_Value).f_ToJson();
		}
	{
		return _Value.f_ToJson();
	}

	template <typename tf_CValue>
	CEJsonSorted fg_ToJson(tf_CValue &&_Value)
		requires (NTraits::TCIsEnum<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CValue>::CType>::mc_Value)
	{
		return int64(_Value);
	}

	template <typename tf_CValue>
	CEJsonSorted fg_ToJson(NStorage::TCOptional<tf_CValue> const &_Value)
	{
		if (_Value)
			return fg_ToJson(*_Value);
		return nullptr;
	}

	template <typename tf_CValue>
	CEJsonSorted fg_ToJson(NContainer::TCVector<tf_CValue> const &_Value)
	{
		CEJsonSorted Return = EJsonType_Array;

		for (auto &Value : _Value)
			Return.f_Insert(fg_ToJson(Value));

		return Return;
	}

	template <typename tf_CValue>
	CEJsonSorted fg_ToJson(NContainer::TCMap<NStr::CStr, tf_CValue> const &_Value)
	{
		CEJsonSorted Return = EJsonType_Object;

		for (auto &Value : _Value)
			Return[_Value.fs_GetKey(Value)] = fg_ToJson(Value);

		return Return;
	}

	template <typename tf_CKey, typename tf_CValue>
	CEJsonSorted fg_ToJson(NContainer::TCMap<tf_CKey, tf_CValue> const &_Value)
	{
		CEJsonSorted Return = EJsonType_Array;

		for (auto &Value : _Value)
		{
			auto &OutValue = Return.f_Insert();
			OutValue["Key"] = fg_ToJson(_Value.fs_GetKey(Value));
			OutValue["Value"] = fg_ToJson(Value);
		}

		return Return;
	}

	template <typename tf_CKey>
	CEJsonSorted fg_ToJson(NContainer::TCSet<tf_CKey> const &_Value)
	{
		CEJsonSorted Return = EJsonType_Array;

		for (auto &Value : _Value)
			Return.f_Insert(fg_ToJson(Value));
		
		return Return;
	}
}
