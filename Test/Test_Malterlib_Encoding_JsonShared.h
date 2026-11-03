// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Encoding/Json>
#include <Mib/Test/Exception>

namespace
{
	template <typename tf_CIterator>
	aint fg_IteratorCount(tf_CIterator _Iterator);

	template <typename t_CJson>
	struct TCJsonTests
	{
		TCJsonTests
			(
				t_CJson const &_Reference
				, NMib::NStr::CStr const &_ReferenceText
				, NMib::NFunction::TCFunction<t_CJson (NMib::NStr::CStr const &_ToParse, NMib::NStr::CStr const &_FileName)> const &_fParse
			)
		;

		void f_DoTests();

	private:
		void fp_TestParseError(NMib::NStr::CStr const &_ToParse, NMib::NContainer::TCVector<NMib::NStr::CParseError> const &_ExpectedErrors);

		NMib::NStr::CStr mp_TestFilePath;
		t_CJson mp_JsonReference;
		NMib::NStr::CStr mp_JsonReferenceText;
		NMib::NFunction::TCFunction<t_CJson (NMib::NStr::CStr const &_ToParse, NMib::NStr::CStr const &_FileName)> mp_fParse;
	};
}

#include "Test_Malterlib_Encoding_JsonShared.hpp"
