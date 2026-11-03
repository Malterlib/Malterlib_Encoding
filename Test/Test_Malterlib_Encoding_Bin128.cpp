// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Encoding/Bin128>

namespace
{
	struct CBin128_Tests : public NMib::NTest::CTest
	{
		void f_DoTests()
		{
			DMibTestSuite("Roundtrip")
			{
				fp_TestRoundtrip(false);
			};
			DMibTestSuite("Roundtrip Use Upper")
			{
				fp_TestRoundtrip(true);
			};
		}

	private:
		void fp_TestRoundtrip(bool _bUseUpper)
		{
			NMib::NContainer::CByteVector ToEncode;
			for (auto iByte = 0; iByte < 4096 + 1024; ++iByte)
			{
				auto Encoded = NMib::NEncoding::fg_Bin128Encode(ToEncode, _bUseUpper);
				auto Decoded = NMib::NEncoding::fg_Bin128Decode(Encoded, _bUseUpper);

				DMibExpect(Decoded, ==, ToEncode)(ETestFlag_Aggregated);

				ToEncode.f_Insert(uint8(iByte));
			}
		}
	};

	DMibTestRegister(CBin128_Tests, Malterlib::Encoding);
}
