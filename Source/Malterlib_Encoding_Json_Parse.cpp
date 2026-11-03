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

	inline_always_lto void CDiscardCommentSink::f_Reset()
	{
	}

	inline_always_lto void CDiscardCommentSink::f_AppendVerbatim(uch8 const *_pStart, uch8 const *_pEnd)
	{
	}

	inline_always_lto void CDiscardCommentSink::f_AppendComment(uch8 const *_pStart, uch8 const *_pEnd, bool _bIsBlock)
	{
	}

	inline_always_lto void CDiscardCommentSink::f_AppendChar(ch8 _Char)
	{
	}
}
