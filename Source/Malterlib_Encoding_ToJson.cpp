// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_ToJson.h"

namespace NMib::NEncoding
{
	CEJSON fg_ToJson(CEJSON const &_Value)
	{
		return _Value;
	}

	CEJSON fg_ToJson(CJSON const &_Value)
	{
		return CEJSON::fs_FromJsonNoConvert(_Value);
	}

	CEJSON fg_ToJson(NStr::CStr const &_Value)
	{
		return _Value;
	}

	CEJSON fg_ToJson(int64 _Value)
	{
		return _Value;
	}

	CEJSON fg_ToJson(uint64 _Value)
	{
		if (_Value > uint64(TCLimitsInt<int64>::mc_Max))
			return fp64(_Value);
		else
			return int64(_Value);
	}

	CEJSON fg_ToJson(bool _Value)
	{
		return _Value;
	}

	CEJSON fg_ToJson(uint32 _Value)
	{
		return int64(_Value);
	}

	CEJSON fg_ToJson(int32 _Value)
	{
		return int64(_Value);
	}

	CEJSON fg_ToJson(int16 _Value)
	{
		return int64(_Value);
	}

	CEJSON fg_ToJson(uint16 _Value)
	{
		return int64(_Value);
	}

	CEJSON fg_ToJson(int8 _Value)
	{
		return int64(_Value);
	}

	CEJSON fg_ToJson(uint8 _Value)
	{
		return int64(_Value);
	}

	CEJSON fg_ToJson(fp64 _Value)
	{
		return _Value;
	}

	CEJSON fg_ToJson(fp32 _Value)
	{
		return fp64(_Value);
	}

	CEJSON fg_ToJson(NTime::CTime const &_Value)
	{
		return _Value;
	}

	CEJSON fg_ToJson(NTime::CTimeSpan const &_Value)
	{
		return _Value.f_GetSecondsFraction();
	}

	CEJSON fg_ToJson(NContainer::CByteVector const &_Value)
	{
		return _Value;
	}
}
