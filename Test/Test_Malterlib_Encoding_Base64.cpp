// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Encoding/Base64>

namespace
{
	struct CBase64_Tests : public NMib::NTest::CTest
	{
		void f_DoTests()
		{
			DMibTestSuite("Roundtrip")
			{
				for (auto nBytes = 0; nBytes < 4096 + 1024; ++nBytes)
				{
					NMib::NContainer::CByteVector ToEncode;
					ToEncode.f_SetLen(nBytes);

					NMib::NStr::CStr Encoded = NMib::NEncoding::fg_Base64Encode(ToEncode);
					Encoded += "\n";
					NMib::NContainer::CByteVector Decoded;
					NMib::NStr::CStr ToDecode = NMib::NStr::fg_GetStrSep(Encoded, "\n");
					NMib::NEncoding::fg_Base64Decode(ToDecode, Decoded);

					DMibTest(DMibExpr(ToEncode) == DMibExpr(Decoded))(ETestFlag_Aggregated | ETestFlag_NoValues);
				}
			};
		}
	};

	DMibTestRegister(CBase64_Tests, Malterlib::Encoding);
}
