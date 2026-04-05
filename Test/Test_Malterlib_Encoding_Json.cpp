// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Encoding/Json>
#include <Mib/Encoding/JsonShortcuts>
#include <Mib/Test/Exception>
#include <Mib/Stream/ByteVector>
#include "Test_Malterlib_Encoding_JsonShared.h"

namespace
{
	using namespace NMib;
	using namespace NMib::NEncoding;
	class CJson_Tests : public NTest::CTest
	{
	public:
		static CJsonOrdered fs_GetJson()
		{
			CJsonOrdered ToReturn(EJsonType_Object);

			ToReturn["Key"] = "Value";
			ToReturn["KeyTrue"] = true;
			ToReturn["KeyFalse"] = false;
			ToReturn["KeyNull"] = nullptr;
			ToReturn["KeyInt"] = 25;
			ToReturn["KeyFloat"] = 167.6;

			auto &Object = ToReturn["KeyObject"];
			Object["Key"] = "Value";
			Object["KeyTrue"] = true;
			Object["KeyFalse"] = false;
			Object["KeyNull"] = nullptr;
			Object["KeyInt"] = 25;
			Object["KeyFloat"] = 167.6;
			Object["KeyArray"] = EJsonType_Array;
			Object["KeyObject"] = EJsonType_Object;

			auto &Array = ToReturn["KeyArray"];
			Array.f_Insert(25);
			Array.f_Insert(167.6);
			Array.f_Insert(true);
			Array.f_Insert(false);
			Array.f_Insert(EJsonType_Array);

			auto &ArrayObject = Array.f_Insert();
			ArrayObject["KeyInt"] = 25;
			ArrayObject["KeyFloat"] = 167.6;

			return fg_Move(ToReturn);
		}

		static NStr::CStr fs_GetJsonTextOrdered()
		{
			return
				"{\n"
				"	\"Key\": \"Value\",\n"
				"	\"KeyTrue\": true,\n"
				"	\"KeyFalse\": false,\n"
				"	\"KeyNull\": null,\n"
				"	\"KeyInt\": 25,\n"
				"	\"KeyFloat\": 167.6,\n"
				"	\"KeyObject\": {\n"
				"		\"Key\": \"Value\",\n"
				"		\"KeyTrue\": true,\n"
				"		\"KeyFalse\": false,\n"
				"		\"KeyNull\": null,\n"
				"		\"KeyInt\": 25,\n"
				"		\"KeyFloat\": 167.6,\n"
				"		\"KeyArray\": [],\n"
				"		\"KeyObject\": {}\n"
				"	},\n"
				"	\"KeyArray\": [\n"
				"		25,\n"
				"		167.6,\n"
				"		true,\n"
				"		false,\n"
				"		[],\n"
				"		{\n"
				"			\"KeyInt\": 25,\n"
				"			\"KeyFloat\": 167.6\n"
				"		}\n"
				"	]\n"
				"}\n"
			;
		}

		static NStr::CStr fs_GetJsonTextSorted()
		{
			return
				"{\n"
				"	\"Key\": \"Value\",\n"
				"	\"KeyArray\": [\n"
				"		25,\n"
				"		167.6,\n"
				"		true,\n"
				"		false,\n"
				"		[],\n"
				"		{\n"
				"			\"KeyFloat\": 167.6,\n"
				"			\"KeyInt\": 25\n"
				"		}\n"
				"	],\n"
				"	\"KeyFalse\": false,\n"
				"	\"KeyFloat\": 167.6,\n"
				"	\"KeyInt\": 25,\n"
				"	\"KeyNull\": null,\n"
				"	\"KeyObject\": {\n"
				"		\"Key\": \"Value\",\n"
				"		\"KeyArray\": [],\n"
				"		\"KeyFalse\": false,\n"
				"		\"KeyFloat\": 167.6,\n"
				"		\"KeyInt\": 25,\n"
				"		\"KeyNull\": null,\n"
				"		\"KeyObject\": {},\n"
				"		\"KeyTrue\": true\n"
				"	},\n"
				"	\"KeyTrue\": true\n"
				"}\n"
			;
		}

		void f_DoTests()
		{
			DMibTestCategory("Shared Sorted")
			{
				TCJsonTests<CJsonSorted> SharedTests
					(
						CJsonSorted::fs_FromCompatible(fs_GetJson())
						, fs_GetJsonTextSorted()
						, [](NStr::CStr const &_ToParse, NStr::CStr const &_FileName) -> CJsonSorted
						{
							return CJsonSorted::fs_FromString(_ToParse, _FileName);
						}
					)
				;
				SharedTests.f_DoTests();
			};
			DMibTestCategory("Shared Ordered")
			{
				TCJsonTests<CJsonOrdered> SharedTests
					(
						fs_GetJson()
						, fs_GetJsonTextOrdered()
						, [](NStr::CStr const &_ToParse, NStr::CStr const &_FileName) -> CJsonOrdered
						{
							return CJsonOrdered::fs_FromString(_ToParse, _FileName);
						}
					)
				;
				SharedTests.f_DoTests();
			};

			DMibTestSuite("Shortcuts")
			{
				CJsonSorted Value =
					{
						"Key"_j= "Value"
						, "KeyTrue"_j= true
						, "KeyFalse"_j= false
						, "KeyNull"_j= nullptr
						, "KeyInt"_j= 25
						, "KeyFloat"_j= 167.6
						, "KeyObject"_j=
						{
							"Key"_j= "Value"
							, "KeyTrue"_j= true
							, "KeyFalse"_j= false
							, "KeyNull"_j= nullptr
							, "KeyInt"_j= 25
							, "KeyFloat"_j= 167.6
							, "KeyArray"_j= _j[]
							, "KeyObject"_j= {}
						}
						, "KeyArray"_j= _j
						[
							25
							, 167.6
							, true
							, false
							, EJsonType_Array
							, _j=
							{
								"KeyInt"_j= 25
								, "KeyFloat"_j= 167.6
							}
						]
					}
				;

				DMibExpect(Value, ==, CJsonSorted::fs_FromCompatible(fs_GetJson()));

				DMibExpectTrue((_j= {}).f_IsObject());
				DMibExpectFalse((CJsonSorted{}).f_IsValid());
			};
			DMibTestSuite("Stream")
			{
				DMibExpect(NStream::fg_FromByteVector<CJsonSorted>(NStream::fg_ToByteVector(fs_GetJson())), ==, CJsonSorted::fs_FromCompatible(fs_GetJson()));
			};
		}
	};

	DMibTestRegister(CJson_Tests, Malterlib::Encoding);
}
