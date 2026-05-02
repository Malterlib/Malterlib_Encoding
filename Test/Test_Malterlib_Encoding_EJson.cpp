// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Encoding/EJson>
#include <Mib/Encoding/JsonShortcuts>
#include <Mib/CommandLine/AnsiEncodingParse>
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
		static umint fs_CountForegroundColorChanges(NStr::CStr const &_Text)
		{
			umint nForegroundColors = 0;
			NCommandLine::CAnsiEncodingParse::fs_Parse
				(
					_Text
					, [](NStr::CStr const &) -> bool
					{
						return true;
					}
					, [&](NCommandLine::CAnsiEncodingParse::CPropertyChange const &_Property)
					{
						if (_Property.f_IsOfType<NCommandLine::CAnsiEncodingParse::CForegroundColor>())
							++nForegroundColors;
					}
				)
			;
			return nForegroundColors;
		}

		static umint fs_CountForegroundColorChanges(NStr::CStr const &_Text, uint8 _Red, uint8 _Green, uint8 _Blue)
		{
			umint nForegroundColors = 0;
			NCommandLine::CAnsiEncodingParse::fs_Parse
				(
					_Text
					, [](NStr::CStr const &) -> bool
					{
						return true;
					}
					, [&](NCommandLine::CAnsiEncodingParse::CPropertyChange const &_Property)
					{
						if (auto const *pForeground = _Property.f_TryGetAsType<NCommandLine::CAnsiEncodingParse::CForegroundColor>())
						{
							if (pForeground->m_bEnabled && pForeground->m_Red == _Red && pForeground->m_Green == _Green && pForeground->m_Blue == _Blue)
								++nForegroundColors;
						}
					}
				)
			;
			return nForegroundColors;
		}

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

			DMibTestSuite("Compatible Comments")
			{
				CEJsonSorted Test;
				CEJsonOrdered Test2(CEJsonOrdered::fs_FromCompatible(Test));
				CEJsonSorted Test3(CEJsonSorted::fs_FromCompatible(Test2));

				CJsonSorted Test4;
				CJsonOrdered Test5(CJsonOrdered::fs_FromCompatible(Test4));
				CJsonSorted Test6(CJsonSorted::fs_FromCompatible(Test5));

				CEJsonOrderedWithComments TestComments = int64(1);
				CEJsonSortedWithComments TestSortedComments(CEJsonSortedWithComments::fs_FromCompatible(TestComments));
				DMibExpect(TestSortedComments.f_Integer(), ==, 1);
				DMibExpect(CEJsonOrdered::fs_FromCompatible(TestComments).f_Integer(), ==, 1);
				DMibExpect(CEJsonSorted::fs_FromCompatible(TestComments).f_Integer(), ==, 1);
				DMibExpect(CEJsonOrderedWithComments::fs_FromCompatible(Test3).f_IsValid(), ==, false);
				DMibExpect(CEJsonOrderedWithComments::fs_FromCompatible(TestSortedComments).f_Integer(), ==, 1);
				DMibExpect(CEJsonSortedWithComments::fs_FromCompatible(Test2).f_IsValid(), ==, false);
			};

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
			DMibTestSuite("JSONC")
			{
				NStr::CStr DateText =
					"// file\n"
					"{\n"
					"\t\"$date\": 12345 // keep\n"
					"}\n"
					"// eof\n"
				;
				auto CollapsedDate = CEJsonOrderedWithComments::fs_FromStringJsonC(DateText);
				DMibExpectTrue(CollapsedDate.f_IsDate());
				DMibExpect(CollapsedDate.f_Date(), ==, NTime::CTimeConvert::fs_FromUnixMilliseconds(12345));
				DMibExpect(CollapsedDate.f_ToStringJsonC(), ==, DateText);
				DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(CollapsedDate.f_ToStringColoredJsonC(NCommandLine::EAnsiEncodingFlag_AllFeatures)), ==, DateText);
				DMibExpect(CollapsedDate.f_ToJson().f_ToStringJsonC(), ==, DateText);

				auto NonRecording = CEJsonOrdered::fs_FromStringJsonC(DateText);
				DMibExpectTrue(NonRecording.f_IsDate());
				DMibExpect(NonRecording.f_ToStringJsonC().f_Find("keep"), <, 0);

				auto TrailingComma = CEJsonOrdered::fs_FromStringJsonC("{\"$date\":12345,}");
				DMibExpectTrue(TrailingComma.f_IsDate());
			};
			DMibTestSuite("JSON5 Comment Recording")
			{
				NStr::CStr DateText =
					"{\n"
					"	$date: 12345 // keep\n"
					"}"
				;
				auto CollapsedDate = CEJsonOrderedWithComments::fs_FromStringJson5(DateText);
				DMibExpectTrue(CollapsedDate.f_IsDate());
				DMibExpect(CollapsedDate.f_Date(), ==, NTime::CTimeConvert::fs_FromUnixMilliseconds(12345));
				DMibExpect
					(
						CollapsedDate.f_ToStringJson5()
						, ==
						, "{\n"
						"	\"$date\": 12345 // keep\n"
						"}"
					)
				;
				DMibExpect(CollapsedDate.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_None), ==, CollapsedDate.f_ToStringJson5());
				DMibExpect(CollapsedDate.f_ToJson().f_ToStringJson5(), ==, CollapsedDate.f_ToStringJson5());
				auto CollapsedDateMove = CEJsonOrderedWithComments::fs_FromStringJson5(DateText);
				DMibExpect(fg_Move(CollapsedDateMove).f_ToJson().f_ToStringJson5(), ==, CollapsedDate.f_ToStringJson5());
				auto CollapsedDateJson = CJsonOrderedWithComments::fs_FromStringJson5(DateText);
				DMibExpect(CEJsonOrderedWithComments::fs_FromJson(CollapsedDateJson).f_ToStringJson5(), ==, CollapsedDate.f_ToStringJson5());
				auto CollapsedDateMoveJson = CJsonOrderedWithComments::fs_FromStringJson5(DateText);
				DMibExpect(CEJsonOrderedWithComments::fs_FromJson(fg_Move(CollapsedDateMoveJson)).f_ToStringJson5(), ==, CollapsedDate.f_ToStringJson5());
				auto SortedCollapsedDate = CEJsonSortedWithComments::fs_FromStringJson5(DateText);
				DMibExpectTrue(SortedCollapsedDate.f_IsDate());
				DMibExpect(SortedCollapsedDate.f_ToStringJson5(), ==, CollapsedDate.f_ToStringJson5());
				auto SortedStreamedDate = NStream::fg_FromByteVector<CEJsonSortedWithComments>(NStream::fg_ToByteVector(SortedCollapsedDate));
				DMibExpect(SortedStreamedDate.f_ToStringJson5(), ==, CollapsedDate.f_ToStringJson5());

				NStr::CStr BinaryText =
					"{\n"
					"	$binary: 'AAECAw==' // keep\n"
					"}"
				;
				auto CollapsedBinary = CEJsonOrderedWithComments::fs_FromStringJson5(BinaryText);
				DMibExpectTrue(CollapsedBinary.f_IsBinary());
				DMibExpect(CollapsedBinary.f_Binary().f_GetLen(), ==, 4);
				DMibExpect
					(
						CollapsedBinary.f_ToStringJson5()
						, ==
						, "{\n"
						"	\"$binary\": \"AAECAw==\" // keep\n"
						"}"
					)
				;
				DMibExpect(CollapsedBinary.f_ToJson().f_ToStringJson5(), ==, CollapsedBinary.f_ToStringJson5());
				auto CollapsedBinaryJson = CJsonOrderedWithComments::fs_FromStringJson5(BinaryText);
				DMibExpect(CEJsonOrderedWithComments::fs_FromJson(CollapsedBinaryJson).f_ToStringJson5(), ==, CollapsedBinary.f_ToStringJson5());
				auto CollapsedBinaryMoveJson = CJsonOrderedWithComments::fs_FromStringJson5(BinaryText);
				DMibExpect(CEJsonOrderedWithComments::fs_FromJson(fg_Move(CollapsedBinaryMoveJson)).f_ToStringJson5(), ==, CollapsedBinary.f_ToStringJson5());

				NStr::CStr UserTypeText =
					"{\n"
					"	$type: 'Custom',\n"
					"	$value: {\n"
					"		// payload\n"
					"		inner: 5,\n"
					"	},\n"
					"}"
				;
				auto CollapsedUserType = CEJsonOrderedWithComments::fs_FromStringJson5(UserTypeText);
				DMibExpectTrue(CollapsedUserType.f_IsUserType());
				DMibExpect(CollapsedUserType.f_UserType().m_Type, ==, "Custom");
				DMibExpect(CollapsedUserType.f_UserType().m_Value["inner"].f_Integer(), ==, 5);
				auto iRecordedPayload = CollapsedUserType.f_UserType().m_Value.f_Object().f_OrderedIterator();
				DMibExpect(iRecordedPayload->f_KeyTrivia().f_Leading(), ==, "\n\t\t// payload\n\t\t");
				DMibExpect(iRecordedPayload->f_Name(), ==, "inner");
				DMibExpect(iRecordedPayload->f_Value().f_Trivia().f_Trailing(), ==, ",\n\t");
				DMibExpect
					(
						CollapsedUserType.f_ToStringJson5()
						, ==
						, "{\n"
						"	\"$type\": 'Custom',\n"
						"	\"$value\": {\n"
						"		// payload\n"
						"		inner: 5,\n"
						"	}\n"
						"}"
					)
				;
				auto StreamedUserType = NStream::fg_FromByteVector<CEJsonOrderedWithComments>(NStream::fg_ToByteVector(CollapsedUserType));
				DMibExpect(StreamedUserType.f_ToStringJson5(), ==, CollapsedUserType.f_ToStringJson5());
				auto SortedCollapsedUserType = CEJsonSortedWithComments::fs_FromStringJson5(UserTypeText);
				auto SortedStreamedUserType = NStream::fg_FromByteVector<CEJsonSortedWithComments>(NStream::fg_ToByteVector(SortedCollapsedUserType));
				DMibExpect(SortedStreamedUserType.f_ToStringJson5(), ==, SortedCollapsedUserType.f_ToStringJson5());

				NStr::CStr UserTypeValueCommentText =
					"{\n"
					"	$type: 'Custom',\n"
					"	$value: { inner: 5 } // keep\n"
					"}"
				;
				auto CollapsedUserTypeValueComment = CEJsonOrderedWithComments::fs_FromStringJson5(UserTypeValueCommentText);
				DMibExpectTrue(CollapsedUserTypeValueComment.f_IsUserType());
				DMibExpect(CollapsedUserTypeValueComment.f_ToJson().f_ToStringJson5(), ==, CollapsedUserTypeValueComment.f_ToStringJson5());
				auto CollapsedUserTypeValueCommentJson = CJsonOrderedWithComments::fs_FromStringJson5(UserTypeValueCommentText);
				DMibExpect(CEJsonOrderedWithComments::fs_FromJson(CollapsedUserTypeValueCommentJson).f_ToStringJson5(), ==, CollapsedUserTypeValueComment.f_ToStringJson5());
				auto CollapsedUserTypeValueCommentMoveJson = CJsonOrderedWithComments::fs_FromStringJson5(UserTypeValueCommentText);
				DMibExpect(CEJsonOrderedWithComments::fs_FromJson(fg_Move(CollapsedUserTypeValueCommentMoveJson)).f_ToStringJson5(), ==, CollapsedUserTypeValueComment.f_ToStringJson5());

				NStr::CStr EscapeText =
					"{\n"
					"	$escape: { value: 1 } // keep\n"
					"}"
				;
				auto CollapsedEscape = CEJsonOrderedWithComments::fs_FromStringJson5(EscapeText);
				DMibExpectTrue(CollapsedEscape.f_IsObject());
				DMibExpect(CollapsedEscape["value"].f_Integer(), ==, 1);
				DMibExpect
					(
						CollapsedEscape.f_ToStringJson5()
						, ==
						, "{ value: 1 // keep\n"
						"}"
					)
				;
				NStr::CStr EmptyEscapedObjectText = "{ $escape: { /* keep */ } }";
				auto EmptyEscapedObject = CEJsonOrderedWithComments::fs_FromStringJson5(EmptyEscapedObjectText);
				DMibExpectTrue(EmptyEscapedObject.f_IsObject());
				DMibExpect(EmptyEscapedObject.f_Object().f_IsEmpty(), ==, true);
				DMibExpect(EmptyEscapedObject.f_ToStringJson5(), ==, "{ /* keep */ }");
				DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(EmptyEscapedObject.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_AllFeatures)), ==, "{ /* keep */ }");
				auto EmptyEscapedObjectJson = CJsonOrderedWithComments::fs_FromStringJson5(EmptyEscapedObjectText);
				DMibExpect(CEJsonOrderedWithComments::fs_FromJson(EmptyEscapedObjectJson).f_ToStringJson5(), ==, EmptyEscapedObject.f_ToStringJson5());
				auto EmptyEscapedObjectMoveJson = CJsonOrderedWithComments::fs_FromStringJson5(EmptyEscapedObjectText);
				DMibExpect(CEJsonOrderedWithComments::fs_FromJson(fg_Move(EmptyEscapedObjectMoveJson)).f_ToStringJson5(), ==, EmptyEscapedObject.f_ToStringJson5());
				auto EmptyEscapedObjectColoredJson = CJsonOrderedWithComments::fs_FromStringJson5(EmptyEscapedObjectText);
				DMibExpect
					(
						NCommandLine::CAnsiEncodingParse::fs_StripEncoding(CEJsonOrderedWithComments::fs_FromJson(EmptyEscapedObjectColoredJson).f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_AllFeatures))
						, ==
						, EmptyEscapedObject.f_ToStringJson5()
					)
				;
				NStr::CStr RootTrailingLineCommentText = "{ value: 1 }// eof";
				auto RootTrailingLineComment = CEJsonOrderedWithComments::fs_FromStringJson5(RootTrailingLineCommentText);
				DMibExpect(RootTrailingLineComment.f_ToStringJson5(), ==, RootTrailingLineCommentText);
				DMibExpect
					(
						NCommandLine::CAnsiEncodingParse::fs_StripEncoding(RootTrailingLineComment.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_AllFeatures))
						, ==
						, RootTrailingLineCommentText
					)
				;

				CEJsonOrderedWithComments NativeDate;
				NativeDate = NTime::CTimeConvert::fs_FromUnixMilliseconds(12345);
				auto NativeDateText = NativeDate.f_ToStringJson5(nullptr);
				DMibExpect(NativeDateText, ==, "{\"$date\":12345}");
				auto NativeRecordedDate = CEJsonOrderedWithComments::fs_FromStringJson5(NativeDateText);
				DMibExpectTrue(NativeRecordedDate.f_IsDate());

				CEJsonOrderedWithComments NativeBinary;
				NativeBinary = NContainer::fg_CreateVector<uint8>(0, 1, 2, 3);
				auto NativeBinaryText = NativeBinary.f_ToStringJson5(nullptr);
				DMibExpect(NativeBinaryText, ==, "{\"$binary\":\"AAECAw==\"}");
				auto NativeRecordedBinary = CEJsonOrderedWithComments::fs_FromStringJson5(NativeBinaryText);
				DMibExpectTrue(NativeRecordedBinary.f_IsBinary());

				CEJsonOrderedWithComments NativeUserType;
				auto &UserType = NativeUserType.f_UserType();
				UserType.m_Type = "Commented";
				UserType.m_Value = EJsonType_Object;
				NStr::CStr PayloadKey("inner");
				PayloadKey.f_SetUserData(EJsonStringType_NoQuote);
				auto &PayloadEntry = UserType.m_Value.f_Object().f_CreateMemberEntry(fg_Move(PayloadKey));
				PayloadEntry.f_KeyTrivia().f_SetLeading("\n\t\t// payload\n\t\t", false);
				PayloadEntry.f_Value() = 5;
				PayloadEntry.f_Value().f_Trivia().f_SetTrailing("\n\t", false);
				auto NativeUserTypeText = NativeUserType.f_ToStringJson5("\t");
				DMibExpect
					(
						NativeUserTypeText
						, ==
						, "{\n"
						"	\"$type\": \"Commented\",\n"
						"	\"$value\": {\n"
						"		// payload\n"
						"		inner: 5\n"
						"	}\n"
						"}"
					)
				;
				auto NativeUserTypeRoundTrip = CEJsonOrderedWithComments::fs_FromStringJson5(NativeUserTypeText);
				DMibExpectTrue(NativeUserTypeRoundTrip.f_IsUserType());
				DMibExpect(NativeUserTypeRoundTrip.f_UserType().m_Value["inner"].f_Integer(), ==, 5);

				CEJsonOrderedWithComments CommentedConversion(EJsonType_Object);
				CommentedConversion.f_Trivia().f_SetLeading("// root\n", false);
				NStr::CStr CommentedConversionKey("a");
				CommentedConversionKey.f_SetUserData(EJsonStringType_NoQuote);
				auto &CommentedConversionEntry = CommentedConversion.f_Object().f_CreateMemberEntry(fg_Move(CommentedConversionKey));
				CommentedConversionEntry.f_KeyTrivia().f_SetLeading("\n\t// key\n\t", false);
				CommentedConversionEntry.f_Value().f_Trivia().f_SetLeading(" ", false);
				CommentedConversionEntry.f_Value() = EJsonType_Array;
				auto &CommentedConversionArrayEntry = CommentedConversionEntry.f_Value().f_Insert();
				CommentedConversionArrayEntry.f_Trivia().f_SetLeading("\n\t\t// elem\n\t\t", false);
				CommentedConversionArrayEntry = 1;
				CommentedConversionArrayEntry.f_Trivia().f_SetTrailing("\n\t", false);
				CommentedConversionEntry.f_Value().f_Trivia().f_SetTrailing("\n", false);
				NStr::CStr CommentedConversionText =
					"// root\n"
					"{\n"
					"	// key\n"
					"	a: [\n"
					"		// elem\n"
					"		1\n"
					"	]\n"
					"}"
				;
				DMibExpect(CommentedConversion.f_ToStringJson5(), ==, CommentedConversionText);
				auto CommentedConversionJson = CommentedConversion.f_ToJson();
				DMibExpect(CommentedConversionJson.f_ToStringJson5(), ==, CommentedConversionText);
				DMibExpect(CEJsonOrderedWithComments::fs_FromJson(CommentedConversionJson).f_ToStringJson5(), ==, CommentedConversionText);
				auto CommentedConversionNoConvertJson = CommentedConversion.f_ToJsonNoConvert();
				DMibExpect(CommentedConversionNoConvertJson.f_ToStringJson5(), ==, CommentedConversionText);
				DMibExpect(CEJsonOrderedWithComments::fs_FromJsonNoConvert(CommentedConversionNoConvertJson).f_ToStringJson5(), ==, CommentedConversionText);

				CEJsonOrderedWithComments ReservedObject(EJsonType_Object);
				NStr::CStr ReservedObjectKey("$date");
				ReservedObjectKey.f_SetUserData(EJsonStringType_NoQuote);
				auto &ReservedObjectEntry = ReservedObject.f_Object().f_CreateMemberEntry(fg_Move(ReservedObjectKey));
				ReservedObjectEntry.f_KeyTrivia().f_SetLeading("\n\t\t// shape\n\t\t", false);
				ReservedObjectEntry.f_Value() = 6;
				ReservedObjectEntry.f_Value().f_Trivia().f_SetTrailing(" // keep\n\t", false);
				NStr::CStr ReservedObjectText =
					"{\n"
					"	\"$escape\": {\n"
					"		// shape\n"
					"		$date: 6 // keep\n"
					"	}\n"
					"}"
				;
				DMibExpect(ReservedObject.f_ToStringJson5(), ==, ReservedObjectText);
				DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(ReservedObject.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_AllFeatures)), ==, ReservedObjectText);
				auto ReservedObjectRoundTrip = CEJsonOrderedWithComments::fs_FromStringJson5(ReservedObjectText);
				DMibExpectTrue(ReservedObjectRoundTrip.f_IsObject());
				DMibExpectFalse(ReservedObjectRoundTrip.f_IsDate());
				DMibExpect(ReservedObjectRoundTrip["$date"].f_Integer(), ==, 6);
				auto CommentedConversionColored = CommentedConversion.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_AllFeatures);
				DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(CommentedConversionColored), ==, CommentedConversionText);
				DMibExpect(fs_CountForegroundColorChanges(CommentedConversionColored), >, 0);
				DMibExpect(fs_CountForegroundColorChanges(CommentedConversionColored, 0x89, 0x89, 0x89), ==, 3);

				CEJsonOrdered NonCommentColor(EJsonType_Object);
				NonCommentColor["a"] = 1;
				auto NonCommentColorText = NonCommentColor.f_ToStringJson5();
				auto NonCommentColorColored = NonCommentColor.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_Color);
				DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(NonCommentColorColored), ==, NonCommentColorText);
				DMibExpect(fs_CountForegroundColorChanges(NonCommentColorColored), >, 0);

				CEJsonOrdered NestedEscape(EJsonType_Object);
				NestedEscape["Unknown"]["$unknown"] = 1;
				NestedEscape["DateShape"]["$date"] = 6;
				auto NestedEscapeText = NestedEscape.f_ToString();
				DMibExpect
					(
						NestedEscapeText
						, ==
						, "{\n"
						"	\"Unknown\": {\n"
						"		\"$unknown\": 1\n"
						"	},\n"
						"	\"DateShape\": {\n"
						"		\"$escape\": {\n"
						"			\"$date\": 6\n"
						"		}\n"
						"	}\n"
						"}\n"
					)
				;
				DMibExpect(CEJsonOrdered::fs_FromString(NestedEscapeText), ==, NestedEscape);

				CEJsonOrdered EscapedNested(EJsonType_Object);
				EscapedNested["$date"]["Nested"]["$date"] = 6;
				auto EscapedNestedText = EscapedNested.f_ToStringJson5();
				auto EscapedNestedColored = EscapedNested.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_AllFeatures);
				DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(EscapedNestedColored), ==, EscapedNestedText);
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
