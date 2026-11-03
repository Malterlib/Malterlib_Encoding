// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NEncoding::NPrivate
{
	inline NStr::CStr const &CObjectEntryBase::CCompare::operator () (CObjectEntryBase const &_Node) const
	{
		return _Node.mp_Name;
	}
}
