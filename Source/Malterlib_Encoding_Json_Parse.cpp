// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Encoding_Json.h"
#include "Malterlib_Encoding_Json_Parse.h"

namespace NMib::NEncoding::NJson
{
	void CParseContext::f_ThrowErrors(NContainer::TCVector<NStr::CParseError> const &_Errors) const
	{
		NStr::CStr Description = NStr::CParseError::fs_ToString(_Errors);

		if (Description.f_IsEmpty())
			Description = "JSON Parse error";

		DMibErrorParse(Description, _Errors);
	}
}
