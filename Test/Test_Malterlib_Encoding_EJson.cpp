
#include <Mib/Encoding/EJson>
#include <Mib/Encoding/JsonShortcuts>
#include <Mib/Test/Exception>
#include <Mib/Stream/ByteVector>
#include "Test_Malterlib_Encoding_JsonShared.h"

namespace
{
	using namespace NMib;
	using namespace NMib::NEncoding;
	class CEJson_Tests : public NTest::CTest
	{
		NStr::CStr mp_TestFilePath;
	public:
		CEJson_Tests()
		{
			mp_TestFilePath = NFile::CFile::fs_GetProgramDirectory() + "/TestEJson.json";
		}

		static CEJsonOrdered fs_GetEJson()
		{
			CEJsonOrdered ToReturn(EJsonType_Object);

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
		
		static NStr::CStr fs_GetEJsonTextOrdered()
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

		static NStr::CStr fs_GetEJsonTextSorted()
		{
			return
				"{\n"
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
				"	\"KeyBinary\": {\n"
				"		\"$binary\": \"AAECAwQFBgc=\"\n"
				"	},\n"
				"	\"KeyDate\": {\n"
				"		\"$date\": 477139811000\n"
				"	},\n"
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
				"	\"KeyTrue\": true,\n"
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
				"	}\n"
				"}\n"
			;
		}

		void fp_TestParseError(NStr::CStr const &_ToParse, NStr::CStr const &_ExpectedError)
		{
			fg_TestAddCleanupPath(mp_TestFilePath);

			NFile::CFile::fs_WriteStringToFile(mp_TestFilePath, _ToParse);
			NException::CException Exception = fg_Move(DMibErrorInstance(""));
			try
			{
				CEJsonSorted::fs_FromString(_ToParse, mp_TestFilePath);
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

			CEJsonSorted Test;
			CEJsonOrdered Test2(CEJsonOrdered::fs_FromCompatible(Test));
			CEJsonSorted Test3(CEJsonSorted::fs_FromCompatible(Test2));

			CJsonSorted Test4;
			CJsonOrdered Test5(CJsonOrdered::fs_FromCompatible(Test4));
			CJsonSorted Test6(CJsonSorted::fs_FromCompatible(Test5));

			DMibTestCategory("Shared Sorted")
			{
				TCJsonTests<CEJsonSorted> SharedTests
					(
						CEJsonSorted::fs_FromCompatible(fs_GetEJson())
						, fs_GetEJsonTextSorted()
						, [](NStr::CStr const &_ToParse, NStr::CStr const &_FileName) -> CEJsonSorted
						{
							return CEJsonSorted::fs_FromString(_ToParse, _FileName);
						}
					)
				;
				SharedTests.f_DoTests();
			};

			DMibTestCategory("Shared Ordered")
			{
				TCJsonTests<CEJsonOrdered> SharedTests
					(
						fs_GetEJson()
						, fs_GetEJsonTextOrdered()
						, [](NStr::CStr const &_ToParse, NStr::CStr const &_FileName) -> CEJsonOrdered
						{
							return CEJsonOrdered::fs_FromString(_ToParse, _FileName);
						}
					)
				;
				SharedTests.f_DoTests();
			};

			DMibTestCategoryFlags("Parse Exceptions", ETestCategoryFlag_DisableExceptionFilter | ETestCategoryFlag_Tests)
			{
				{
					DMibTestPath("User type");
					fp_TestParseError("{ \"$type\": 5, \"$value\": 6 }\n", "Invalid EJSON: $type value must be a string");
				}
				{
					DMibTestPath("Escape type");
					fp_TestParseError("{ \"$escape\": 5 }\n", "Invalid EJSON: $escape value must be an object");
				}
				{
					DMibTestPath("Date type");
					fp_TestParseError("{ \"$date\": \"5\" }\n", "Invalid EJSON: $date value must be an integer");
				}
				{
					DMibTestPath("Binary type");
					fp_TestParseError("{ \"$binary\": 5 }\n", "Invalid EJSON: $binary value must be a string");
				}
			};
			DMibTestSuite("Shortcuts")
			{
				CEJsonSorted Value =
					{
						"Key"_= "Value"
						, "KeyTrue"_= true
						, "KeyFalse"_= false
						, "KeyNull"_= nullptr
						, "KeyInt"_= 25
						, "KeyFloat"_= 167.6
						, "KeyDate"_= NTime::CTimeConvert::fs_CreateTime(1985, 2, 13, 10, 50, 11)
						, "KeyBinary"_= NContainer::fg_CreateVector<uint8>(0, 1, 2, 3, 4, 5, 6, 7)
						, "UserType"_= fg_UserTypeSorted("TestType", {"TestValue1"_j= "Test1", "TestValue2"_j= 2})
						, "UserTypeSimple"_= fg_UserTypeSorted("oid", "e86c9bc324bbba92f0fd4014")
						, "Escape1"_=
						{
							"$escape"_= 5
						}
						, "Escape2"_=
						{
							"$date"_= 6
						}
						, "Escape3"_=
						{
							"$binary"_= 7
						}
						, "Escape4"_=
						{
							"$type"_= 8
							, "$value"_= 9
						}
						, "NonEscape1"_=
						{
							"$escape"_= 10
							, "OtherKey"_= 10
						}
						, "NonEscape2"_=
						{
							"$date"_= 11
							, "OtherKey"_= 11
						}
						, "NonEscape3"_=
						{
							"$binary"_= 12
							, "OtherKey"_= 12
						}
						, "NonEscape4"_= 
						{
							"$type"_= 13
							, "$value"_= 13
							, "OtherKey"_= 13
						}
						, "RecursiveEscape"_=
						{
							"$escape"_= NContainer::fg_CreateVector<uint8>(0, 1, 2, 3, 4, 5, 6, 7)
						}
						, "KeyObject"_=
						{
							"Key"_= "Value"
							, "KeyTrue"_= true
							, "KeyFalse"_= false
							, "KeyNull"_= nullptr
							, "KeyInt"_= 25
							, "KeyFloat"_= 167.6
							, "KeyArray"_= _[]
							, "KeyObject"_= {}
						}
						, "KeyArray"_= _
						[
							25
							, 167.6
							, true
							, false
							, _[]
							, _=
							{
								"KeyInt"_= 25
								, "KeyFloat"_= 167.6
							}
						]
					}
				;
				
				DMibExpect(Value, ==, CEJsonSorted::fs_FromCompatible(fs_GetEJson()));

				auto ConstToJson = Value.f_ToJson();
				DMibExpect(CEJsonSorted::fs_FromJson(ConstToJson), ==, CEJsonSorted::fs_FromCompatible(fs_GetEJson()));

				auto MoveToJson = fg_Move(Value).f_ToJson();
				DMibExpect(CEJsonSorted::fs_FromJson(fg_Move(MoveToJson)), ==, CEJsonSorted::fs_FromCompatible(fs_GetEJson()));

				DMibExpectTrue((_= {}).f_IsObject());
				DMibExpectFalse((CEJsonSorted{}).f_IsValid());
			};
			DMibTestSuite("Stream")
			{
				DMibExpect(NStream::fg_FromByteVector<CEJsonSorted>(NStream::fg_ToByteVector(fs_GetEJson())), ==, CEJsonSorted::fs_FromCompatible(fs_GetEJson()));
			};
			DMibTestSuite("Date")
			{
				auto fTestTimeConversion = [](NTime::CTime const &_Time)
					{
						auto OriginalTime = _Time;
						OriginalTime = NTime::CTimeConvert::fs_FromUnixMilliseconds(NTime::CTimeConvert(OriginalTime).f_UnixMilliseconds());
						CEJsonSorted OriginalEJson;
						OriginalEJson = OriginalTime;
						CEJsonSorted ConvertedEJson = CEJsonSorted::fs_FromJson(OriginalEJson.f_ToJson());
						DMibExpect(ConvertedEJson.f_Date(), == , OriginalTime);
					}
				;
				{
					DMibTestPath("0.999...");
					fTestTimeConversion(NTime::CTimeConvert::fs_CreateTime(2019, 04, 20, 18, 17, 05, 0.9999999999999999));
				}
				{
					DMibTestPath("0.1");
					fTestTimeConversion(NTime::CTimeConvert::fs_CreateTime(2019, 04, 20, 18, 17, 05, 0.1));
				}
				{
					DMibTestPath("Bug1");
					fTestTimeConversion(NTime::CTime::fs_Create(constant_int64(237148623722908912), constant_uint64(7627728670263724032)));
				}
				{
					DMibTestPath("Bug2");
					fTestTimeConversion(NTime::CTime::fs_Create(constant_int64(237148623722908912), constant_uint64(7627728670263725056)));
				}
			};
			DMibTestSuite("JsonNoConvert")
			{
				auto Json = CJsonSorted::fs_FromString(fs_GetEJsonTextOrdered());
				auto EnhancedJson = CEJsonSorted::fs_FromJsonNoConvert(Json);
				DMibExpect(EnhancedJson, !=, CEJsonSorted::fs_FromCompatible(fs_GetEJson()));
				auto ToJson = EnhancedJson.f_ToJsonNoConvert();
				DMibExpect(ToJson, ==, Json);
			};
			DMibTestSuite("JsonNoConvert Move")
			{
				auto Json = CJsonSorted::fs_FromString(fs_GetEJsonTextOrdered());
				auto OriginalJson = Json;
				auto EnhancedJson = CEJsonSorted::fs_FromJsonNoConvert(fg_Move(Json));
				DMibExpect(EnhancedJson, !=, CEJsonSorted::fs_FromCompatible(fs_GetEJson()));
				auto OriginalEnhancedJson = EnhancedJson;
				auto ToJson = fg_Move(EnhancedJson).f_ToJsonNoConvert();
				DMibExpect(EnhancedJson, !=, OriginalEnhancedJson);
				DMibExpect(ToJson, ==, OriginalJson);
			};
		}
	};

	DMibTestRegister(CEJson_Tests, Malterlib::Encoding);
}
