// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Encoding/Base64>

namespace
{
	class CBase64_Tests : public NMib::NTest::CTest
	{
	public:

		void f_DoTests()
		{
			DMibTestSuite("Roundtrip")
			{
				for (auto i = 0; i < 4096+1024; ++i)
				{
					NMib::NContainer::CByteVector ToEncode;
					ToEncode.f_SetLen(i);

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
