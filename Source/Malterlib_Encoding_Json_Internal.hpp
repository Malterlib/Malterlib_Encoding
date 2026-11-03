// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NEncoding
{
	template <typename tf_CJsonObject>
	bool fg_ValidateType(tf_CJsonObject const *_pObject, EJsonType _Type)
	{
		return _pObject && _pObject->f_Type() == _Type;
	}
}
