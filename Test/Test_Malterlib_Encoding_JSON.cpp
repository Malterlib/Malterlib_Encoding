// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Encoding/JSON>
#include <Mib/Test/Exception>
#include "Test_Malterlib_Encoding_JSONShared.h"

namespace
{
	using namespace NMib;
	using namespace NMib::NEncoding;
	class CJSON_Tests : public NTest::CTest
	{
		NStr::CStr mp_TestFilePath;
	public:
		CJSON_Tests()
		{
			mp_TestFilePath = NFile::CFile::fs_GetProgramDirectory() + "/Test.json";
		}

		static CJSON fs_GetJSON()
		{
			CJSON ToReturn(EJSONType_Object);

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
			Object["KeyArray"] = EJSONType_Array;
			Object["KeyObject"] = EJSONType_Object;

			auto &Array = ToReturn["KeyArray"];
			Array.f_Insert(25);
			Array.f_Insert(167.6);
			Array.f_Insert(true);
			Array.f_Insert(false);
			Array.f_Insert(EJSONType_Array);

			auto &ArrayObject = Array.f_Insert();
			ArrayObject["KeyInt"] = 25;
			ArrayObject["KeyFloat"] = 167.6;

			return fg_Move(ToReturn);
		}
		
		static NStr::CStr fs_GetJSONText()
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

		void f_DoTests()
		{
			TCJSONTests<CJSON> SharedTests
				(
					fs_GetJSON()
					, fs_GetJSONText()
					, [](NStr::CStr const &_ToParse, NStr::CStr const &_FileName) -> CJSON
					{
						return CJSON::fs_FromString(_ToParse, _FileName);
					}
				)
			;
			SharedTests.f_DoTests();
		}
	};

	DMibTestRegister(CJSON_Tests, Malterlib::Encoding);
}
