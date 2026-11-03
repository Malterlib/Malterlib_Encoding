// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NEncoding
{
	template <typename t_CJson>
	t_CJson const &TCJsonConstants<t_CJson>::operator = (t_CJson const &_Convert) const
	{
		return _Convert;
	}

	template <typename t_CJson>
	t_CJson &&TCJsonConstants<t_CJson>::operator = (t_CJson &&_Convert) const
	{
		return fg_Move(_Convert);
	}

	template <typename t_CJson>
	t_CJson TCJsonConstants<t_CJson>::operator = (std::initializer_list<CVoidTag> const &_Initializer) const
	{
		return EJsonType_Object;
	}

	template <typename t_CJson>
	template <typename ...tfp_CValue>
	t_CJson TCJsonConstants<t_CJson>::operator [] (tfp_CValue && ...p_Values) const
	{
		t_CJson Return;

		auto &ReturnArray = Return.f_Array();
		((void)ReturnArray.f_Insert(fg_Forward<tfp_CValue>(p_Values)), ...);

		return Return;
	}
}
