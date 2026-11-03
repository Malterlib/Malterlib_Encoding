// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Encoding_EJson.h"
#include "Malterlib_Encoding_EJson.hpp"
#include "Malterlib_Encoding_EJson_Parse.h"

namespace NMib::NEncoding::NPrivate
{
	bool CEJsonParseContext::fsp_HasComment(NStr::CStr const &_Trivia)
	{
		return NStr::fg_StrFind(_Trivia, "//") >= 0 || NStr::fg_StrFind(_Trivia, "/*") >= 0;
	}

	bool CEJsonParseContext::fsp_HasLineTerminator(NStr::CStr const &_Trivia)
	{
		return NStr::fg_StrFindChars(_Trivia, "\n\r") >= 0;
	}

	void CEJsonParseContext::fsp_AppendCommentTrivia(NStr::CStr &o_Trivia, NStr::CStr const &_Trivia)
	{
		if (fsp_HasComment(_Trivia))
			o_Trivia += _Trivia;
	}
}
