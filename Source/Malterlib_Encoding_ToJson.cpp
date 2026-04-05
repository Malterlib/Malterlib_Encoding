// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Encoding_ToJson.h"

namespace NMib::NEncoding
{
	CEJsonSorted fg_ToJson(CJsonSorted const &_Value)
	{
		return CEJsonSorted::fs_FromJsonNoConvert(_Value);
	}

	CEJsonSorted fg_ToJson(NStr::CStr const &_Value)
	{
		return _Value;
	}

	CEJsonSorted fg_ToJson(int64 _Value)
	{
		return _Value;
	}

	CEJsonSorted fg_ToJson(uint64 _Value)
	{
		if (_Value > uint64(TCLimitsInt<int64>::mc_Max))
			return fp64(_Value);
		else
			return int64(_Value);
	}

	CEJsonSorted fg_ToJson(bool _Value)
	{
		return _Value;
	}

	CEJsonSorted fg_ToJson(uint32 _Value)
	{
		return int64(_Value);
	}

	CEJsonSorted fg_ToJson(int32 _Value)
	{
		return int64(_Value);
	}

	CEJsonSorted fg_ToJson(int16 _Value)
	{
		return int64(_Value);
	}

	CEJsonSorted fg_ToJson(uint16 _Value)
	{
		return int64(_Value);
	}

	CEJsonSorted fg_ToJson(int8 _Value)
	{
		return int64(_Value);
	}

	CEJsonSorted fg_ToJson(uint8 _Value)
	{
		return int64(_Value);
	}

	CEJsonSorted fg_ToJson(fp64 _Value)
	{
		return _Value;
	}

	CEJsonSorted fg_ToJson(fp32 _Value)
	{
		return fp64(_Value);
	}

	CEJsonSorted fg_ToJson(NTime::CTime const &_Value)
	{
		return _Value;
	}

	CEJsonSorted fg_ToJson(NTime::CTimeSpan const &_Value)
	{
		return _Value.f_GetSecondsFraction();
	}

	CEJsonSorted fg_ToJson(NContainer::CByteVector const &_Value)
	{
		return _Value;
	}
}
