
#include <Mib/Encoding/EJSON>
#include <Mib/Test/Exception>
#include "Test_Malterlib_Encoding_JSONShared.h"

namespace
{
	using namespace NMib;
	using namespace NMib::NEncoding;
	class CEJSON_Tests : public NTest::CTest
	{
		NStr::CStr mp_TestFilePath;
	public:
		CEJSON_Tests()
		{
			mp_TestFilePath = NFile::CFile::fs_GetProgramDirectory() + "/Test.json";
		}

		static CEJSON fs_GetEJSON()
		{
			CEJSON ToReturn(EJSONType_Object);

			ToReturn["Key"] = "Value";
			ToReturn["KeyTrue"] = true;
			ToReturn["KeyFalse"] = false;
			ToReturn["KeyNull"] = nullptr;
			ToReturn["KeyInt"] = 25;
			ToReturn["KeyFloat"] = 167.6;
			ToReturn["KeyDate"] = NTime::CTimeConvert::fs_CreateTime(1985, 2, 13, 10, 50, 11);
			ToReturn["KeyBinary"] = NContainer::fg_CreateVector<uint8>(0, 1, 2, 3, 4, 5, 6, 7);

			auto &UserType = ToReturn["UserType"].f_UserType();
			UserType.m_Type = "TestType";
			UserType.m_Value["TestValue1"] = "Test1";
			UserType.m_Value["TestValue2"] = 2;

			auto &UserTypeSimple = ToReturn["UserTypeSimple"].f_UserType();
			UserTypeSimple.m_Type = "oid";
			UserTypeSimple.m_Value = "e86c9bc324bbba92f0fd4014";

			ToReturn["Escape1"]["$escape"] = 5;

			ToReturn["Escape2"]["$date"] = 6;

			ToReturn["Escape3"]["$binary"] = 7;

			ToReturn["Escape4"]["$type"] = 8;
			ToReturn["Escape4"]["$value"] = 9;

			ToReturn["NonEscape1"]["$escape"] = 10;
			ToReturn["NonEscape1"]["OtherKey"] = 10;

			ToReturn["NonEscape2"]["$date"] = 11;
			ToReturn["NonEscape2"]["OtherKey"] = 11;

			ToReturn["NonEscape3"]["$binary"] = 12;
			ToReturn["NonEscape3"]["OtherKey"] = 12;

			ToReturn["NonEscape4"]["$type"] = 13;
			ToReturn["NonEscape4"]["$value"] = 13;
			ToReturn["NonEscape4"]["OtherKey"] = 13;

			ToReturn["RecursiveEscape"]["$escape"] = NContainer::fg_CreateVector<uint8>(0, 1, 2, 3, 4, 5, 6, 7);

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
		
		static NStr::CStr fs_GetEJSONText()
		{
			return
				"{\n"
				"	\"Key\": \"Value\",\n"
				"	\"KeyTrue\": true,\n"
				"	\"KeyFalse\": false,\n"
				"	\"KeyNull\": null,\n"
				"	\"KeyInt\": 25,\n"
				"	\"KeyFloat\": 167.6,\n"
				"	\"KeyDate\": {\n"
				"		\"$date\": 477139811000\n"
				"	},\n"
				"	\"KeyBinary\": {\n"
				"		\"$binary\": \"AAECAwQFBgc=\"\n"
				"	},\n"
				"	\"UserType\": {\n"
				"		\"$type\": \"TestType\",\n"
				"		\"$value\": {\n"
				"			\"TestValue1\": \"Test1\",\n"
				"			\"TestValue2\": 2\n"
				"		}\n"
				"	},\n"
				"	\"UserTypeSimple\": {\n"
				"		\"$type\": \"oid\",\n"
				"		\"$value\": \"e86c9bc324bbba92f0fd4014\"\n"
				"	},\n"
				"	\"Escape1\": {\n"
				"		\"$escape\": {\n"
				"			\"$escape\": 5\n"
				"		}\n"
				"	},\n"
				"	\"Escape2\": {\n"
				"		\"$escape\": {\n"
				"			\"$date\": 6\n"
				"		}\n"
				"	},\n"
				"	\"Escape3\": {\n"
				"		\"$escape\": {\n"
				"			\"$binary\": 7\n"
				"		}\n"
				"	},\n"
				"	\"Escape4\": {\n"
				"		\"$escape\": {\n"
				"			\"$type\": 8,\n"
				"			\"$value\": 9\n"
				"		}\n"
				"	},\n"
				"	\"NonEscape1\": {\n"
				"		\"$escape\": 10,\n"
				"		\"OtherKey\": 10\n"
				"	},\n"
				"	\"NonEscape2\": {\n"
				"		\"$date\": 11,\n"
				"		\"OtherKey\": 11\n"
				"	},\n"
				"	\"NonEscape3\": {\n"
				"		\"$binary\": 12,\n"
				"		\"OtherKey\": 12\n"
				"	},\n"
				"	\"NonEscape4\": {\n"
				"		\"$type\": 13,\n"
				"		\"$value\": 13,\n"
				"		\"OtherKey\": 13\n"
				"	},\n"
				"	\"RecursiveEscape\": {\n"
				"		\"$escape\": {\n"
				"			\"$escape\": {\n"
				"				\"$binary\": \"AAECAwQFBgc=\"\n"
				"			}\n"
				"		}\n"
				"	},\n"
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

		void fp_TestParseError(NStr::CStr const &_ToParse, NStr::CStr const &_ExpectedError)
		{
			NFile::CFile::fs_WriteStringToFile(mp_TestFilePath, _ToParse);
			NException::CException Exception = fg_Move(DMibErrorInstance(""));
			try
			{
				CEJSON::fs_FromString(_ToParse, mp_TestFilePath);
			}
			catch (NException::CException const &_Exception)
			{
				Exception = _Exception;
			}
			
			auto ErrorStr = Exception.f_GetErrorStr();
			DMibExpect(ErrorStr, ==, _ExpectedError);
		}
		
		void f_DoTests()
		{
			using namespace NMib;
			using namespace NMib::NStr;
			using namespace NMib::NContainer;
			TCJSONTests<CEJSON> SharedTests
				(
					fs_GetEJSON()
					, fs_GetEJSONText()
					, [](NStr::CStr const &_ToParse, NStr::CStr const &_FileName) -> CEJSON
					{
						return CEJSON::fs_FromString(_ToParse, _FileName);
					}
				)
			;
			SharedTests.f_DoTests();

			DMibTestCategory("Parse Exceptions")
			{
				DMibTestSuite("User type")
				{
					fp_TestParseError("{ \"$type\": 5, \"$value\": 6 }\n", "Invalid EJSON: $type value must be a string");
				};
				DMibTestSuite("Escape type")
				{
					fp_TestParseError("{ \"$escape\": 5 }\n", "Invalid EJSON: $escape value must be an object");
				};
				DMibTestSuite("Date type")
				{
					fp_TestParseError("{ \"$date\": \"5\" }\n", "Invalid EJSON: $date value must be an integer");
				};
				DMibTestSuite("Binary type")
				{
					fp_TestParseError("{ \"$binary\": 5 }\n", "Invalid EJSON: $binary value must be a string");
				};
			};
		}
	};

	DMibTestRegister(CEJSON_Tests, Malterlib::Encoding);
}
