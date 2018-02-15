
#include <Mib/Encoding/JSON>
#include <Mib/Test/Exception>

namespace
{
	template <typename t_CJSON>
	class TCJSONTests
	{
	public:
		TCJSONTests
			(
				t_CJSON const &_Reference
				, NMib::NStr::CStr const &_ReferenceText
				, NMib::NFunction::TCFunction<t_CJSON (NMib::NStr::CStr const &_ToParse, NMib::NStr::CStr const &_FileName)> const &_fParse
			)
			: mp_JSONReference(_Reference)
			, mp_JSONReferenceText(_ReferenceText)
			, mp_fParse(_fParse)
		{
			mp_TestFilePath = NMib::NFile::CFile::fs_GetProgramDirectory() + "/Test.json";
		}

		void f_DoTests()
		{
			using namespace NMib;
			using namespace NMib::NStr;
			using namespace NMib::NEncoding;
			using namespace NMib::NContainer;
			DMibTestCategory("Functionality")
			{
				DMibTestSuite("Generating")
				{
					t_CJSON JSON = mp_JSONReference;

					CStr GeneratedJSONText = JSON.f_ToString();
					
					DMibExpect(GeneratedJSONText, ==, mp_JSONReferenceText);
				};
				DMibTestSuite("Copy")
				{
					t_CJSON JSON = mp_JSONReference;

					t_CJSON JSONCopy(JSON);

					CStr GeneratedJSONText = JSONCopy.f_ToString();
					
					DMibExpect(GeneratedJSONText, ==, mp_JSONReferenceText);
				};
				DMibTestSuite("Move")
				{
					t_CJSON JSON = mp_JSONReference;

					t_CJSON JSONCopy(fg_Move(JSON));

					CStr GeneratedJSONText = JSONCopy.f_ToString();
					
					DMibExpect(GeneratedJSONText, ==, mp_JSONReferenceText);
				};
				DMibTestSuite("Assign")
				{
					t_CJSON JSON = mp_JSONReference;

					t_CJSON JSONCopy;
					JSONCopy = JSON;

					CStr GeneratedJSONText = JSONCopy.f_ToString();
					
					DMibExpect(GeneratedJSONText, ==, mp_JSONReferenceText);
				};
				DMibTestSuite("MoveAssign")
				{
					t_CJSON JSON = mp_JSONReference;

					t_CJSON JSONCopy;
					JSONCopy = fg_Move(JSON);

					CStr GeneratedJSONText = JSONCopy.f_ToString();
					
					DMibExpect(GeneratedJSONText, ==, mp_JSONReferenceText);
				};
				DMibTestSuite("AssignTree")
				{
					t_CJSON JSON = mp_JSONReference;

					t_CJSON JSONCopy = JSON;
					JSONCopy["TreeCopy"] = JSON;

					CStr GeneratedJSONText = JSONCopy.f_ToString();
					
					DMibExpect(GeneratedJSONText, !=, mp_JSONReferenceText);
				};
				DMibTestSuite("Get member")
				{
					t_CJSON JSON = mp_JSONReference;

					DMibAssertTrue(JSON.f_GetMember("Key"));
					DMibExpect(JSON.f_GetMember("Key")->f_String(), ==, "Value");

					DMibAssertTrue(fg_Const(JSON).f_GetMember("Key"));
					DMibExpect(fg_Const(JSON).f_GetMember("Key")->f_String(), ==, "Value");

					DMibExpectFalse(JSON.f_GetMember("NonExistingKey"));
				};
				DMibTestSuite("Comparison")
				{
					DMibExpect(mp_JSONReference, ==, mp_JSONReference);
					DMibTest(!(DMibExpr(mp_JSONReference) < DMibExpr(mp_JSONReference)));
				};
				DMibTestSuite("Parsing")
				{
					t_CJSON JSON = mp_fParse(mp_JSONReferenceText, CStr());

					DMibExpect(JSON, ==, mp_JSONReference);
				};
				DMibTestSuite("JSON roundtrip")
				{
					t_CJSON JSON = mp_fParse(mp_JSONReferenceText, CStr());
					CStr GeneratedJSONText = JSON.f_ToString();
					
					DMibExpect(GeneratedJSONText, ==, mp_JSONReferenceText);
				};
				DMibTestSuite("JSON roundtrip no whitespace")
				{
					CStr JSONText = mp_JSONReferenceText.f_Replace("\n", "").f_Replace(" ", "").f_Replace("\t", "");
					t_CJSON JSON = mp_fParse(JSONText, CStr());
					CStr GeneratedJSONText = JSON.f_ToString(nullptr);
					
					DMibExpect(GeneratedJSONText, ==, JSONText);
				};
				DMibTestSuite("Remove by string")
				{
					t_CJSON JSON;
					
					JSON["Test0"] = "52";
					JSON["Test1"] = "53";

					JSON.f_RemoveMember("Test0");
					
					t_CJSON JSONRemoved;
					JSONRemoved["Test1"] = "53";
					
					DMibExpect(JSON, ==, JSONRemoved);
				};
				DMibTestSuite("Remove by ordered const iterator")
				{
					t_CJSON JSON;
					
					JSON["Test0"] = "52";
					JSON["Test1"] = "53";
					JSON["Test2"] = "54";
					
					auto iMember = fg_Const(JSON).f_Object().f_OrderedIterator();
					
					++iMember;
					JSON.f_Object().f_RemoveMember(iMember);
					
					DMibExpect(iMember->f_Value().f_String(), ==, "54");
					
					t_CJSON JSONRemoved;
					JSONRemoved["Test0"] = "52";
					JSONRemoved["Test2"] = "54";
					
					DMibExpect(JSON, ==, JSONRemoved);
				};
				DMibTestSuite("Remove by ordered iterator")
				{
					t_CJSON JSON;
					
					JSON["Test0"] = "52";
					JSON["Test1"] = "53";
					JSON["Test2"] = "54";
					
					auto iMember = JSON.f_Object().f_OrderedIterator();
					
					++iMember;
					JSON.f_Object().f_RemoveMember(iMember);
					
					DMibExpect(iMember->f_Value().f_String(), ==, "54");
					
					t_CJSON JSONRemoved;
					JSONRemoved["Test0"] = "52";
					JSONRemoved["Test2"] = "54";
					
					DMibExpect(JSON, ==, JSONRemoved);
				};
				DMibTestSuite("Remove by sorted iterator")
				{
					t_CJSON JSON;
					
					JSON["Test3"] = "54";
					JSON["Test1"] = "52";
					JSON["Test2"] = "53";
					
					auto iMember = JSON.f_Object().f_SortedIterator();
					
					++iMember;
					JSON.f_Object().f_RemoveMember(iMember);
					
					DMibExpect(iMember->f_Value().f_String(), ==, "54");
					
					t_CJSON JSONRemoved;
					JSONRemoved["Test3"] = "54";
					JSONRemoved["Test1"] = "52";
					
					DMibExpect(JSON, ==, JSONRemoved);
				};
				DMibTestSuite("Get as string")
				{
					t_CJSON JSON;
					
					JSON["TestNull"] = nullptr;
					JSON["TestString"] = "String";
					JSON["TestInt"] = 54;
					JSON["TestFloat"] = fp32(5.5);
					JSON["TestBool"] = true;
					t_CJSON Object;
					Object["5"] = 6;
					JSON["TestObject"] = Object;
					t_CJSON Array;
					Array.f_Insert(6);
					JSON["TestArray"] = Array;
					JSON["TestInvalid"];
					
					
					DMibExpect(JSON["TestNull"].f_AsString(), ==, "null");
					DMibExpect(JSON["TestString"].f_AsString(), ==, "String");
					DMibExpect(JSON["TestInt"].f_AsString(), ==, "54");
					DMibExpect(JSON["TestFloat"].f_AsString(), ==, "5.5");
					DMibExpect(JSON["TestBool"].f_AsString(), ==, "true");
					DMibExpect(JSON["TestObject"].f_AsString(), ==, Object.f_ToString());
					DMibExpect(JSON["TestArray"].f_AsString(), ==, Array.f_ToString());
					DMibExpectException(JSON["TestInvalid"].f_AsString(), DMibErrorInstance("JSON type cannot be converted to string"));
				};
				DMibTestSuite("Get as integer")
				{
					t_CJSON JSON;
					
					JSON["TestNull"] = nullptr;
					JSON["TestString"] = "66";
					JSON["TestInt"] = 54;
					JSON["TestFloat"] = fp32(5.5);
					JSON["TestBool"] = true;
					t_CJSON Object;
					Object["5"] = 6;
					JSON["TestObject"] = Object;
					t_CJSON Array;
					Array.f_Insert(6);
					JSON["TestArray"] = Array;
					JSON["TestInvalid"];
					
					
					DMibExpectException(JSON["TestNull"].f_AsInteger(), DMibErrorInstance("JSON type cannot be converted to integer"));
					DMibExpect(JSON["TestString"].f_AsInteger(), ==, 66);
					DMibExpect(JSON["TestInt"].f_AsInteger(), ==, 54);
					DMibExpect(JSON["TestFloat"].f_AsInteger(), ==, 6);
					DMibExpect(JSON["TestBool"].f_AsInteger(), ==, 1);
					DMibExpectException(JSON["TestObject"].f_AsInteger(), DMibErrorInstance("JSON type cannot be converted to integer"));
					DMibExpectException(JSON["TestArray"].f_AsInteger(), DMibErrorInstance("JSON type cannot be converted to integer"));
					DMibExpectException(JSON["TestInvalid"].f_AsInteger(), DMibErrorInstance("JSON type cannot be converted to integer"));
				};
				DMibTestSuite("Get as float")
				{
					t_CJSON JSON;
					
					JSON["TestNull"] = nullptr;
					JSON["TestString"] = "66.5";
					JSON["TestInt"] = 54;
					JSON["TestFloat"] = fp32(5.5);
					JSON["TestBool"] = true;
					t_CJSON Object;
					Object["5"] = 6;
					JSON["TestObject"] = Object;
					t_CJSON Array;
					Array.f_Insert(6);
					JSON["TestArray"] = Array;
					JSON["TestInvalid"];
					
					DMibExpectException(JSON["TestNull"].f_AsFloat(), DMibErrorInstance("JSON type cannot be converted to float"));
					DMibExpect(JSON["TestString"].f_AsFloat(), ==, 66.5);
					DMibExpect(JSON["TestInt"].f_AsFloat(), ==, 54.0);
					DMibExpect(JSON["TestFloat"].f_AsFloat(), ==, 5.5);
					DMibExpect(JSON["TestBool"].f_AsFloat(), ==, 1.0);
					DMibExpectException(JSON["TestObject"].f_AsFloat(), DMibErrorInstance("JSON type cannot be converted to float"));
					DMibExpectException(JSON["TestArray"].f_AsFloat(), DMibErrorInstance("JSON type cannot be converted to float"));
					DMibExpectException(JSON["TestInvalid"].f_AsFloat(), DMibErrorInstance("JSON type cannot be converted to float"));
				};
				DMibTestSuite("Get as boolean")
				{
					t_CJSON JSON;
					
					JSON["TestNull"] = nullptr;
					JSON["TestString0"] = "true";
					JSON["TestString1"] = "false";
					JSON["TestString2"] = "1";
					JSON["TestString3"] = "4";
					JSON["TestString4"] = "0";
					JSON["TestString5"] = "0.5";
					JSON["TestInt"] = 54;
					JSON["TestFloat"] = fp32(5.5);
					JSON["TestBool"] = true;
					t_CJSON Object;
					Object["5"] = 6;
					JSON["TestObject"] = Object;
					t_CJSON Array;
					Array.f_Insert(6);
					JSON["TestArray"] = Array;
					JSON["TestInvalid"];
					
					DMibExpectException(JSON["TestNull"].f_AsBoolean(), DMibErrorInstance("JSON type cannot be converted to boolean"));
					DMibExpectTrue(JSON["TestString0"].f_AsBoolean());
					DMibExpectFalse(JSON["TestString1"].f_AsBoolean());
					DMibExpectTrue(JSON["TestString2"].f_AsBoolean());
					DMibExpectTrue(JSON["TestString3"].f_AsBoolean());
					DMibExpectFalse(JSON["TestString4"].f_AsBoolean());
					DMibExpectFalse(JSON["TestString5"].f_AsBoolean());
					DMibExpectTrue(JSON["TestInt"].f_AsBoolean());
					DMibExpectTrue(JSON["TestFloat"].f_AsBoolean());
					DMibExpectTrue(JSON["TestBool"].f_AsBoolean());
					DMibExpectException(JSON["TestObject"].f_AsBoolean(), DMibErrorInstance("JSON type cannot be converted to boolean"));
					DMibExpectException(JSON["TestArray"].f_AsBoolean(), DMibErrorInstance("JSON type cannot be converted to boolean"));
					DMibExpectException(JSON["TestInvalid"].f_AsBoolean(), DMibErrorInstance("JSON type cannot be converted to boolean"));
				};
				DMibTestSuite("Get as string default")
				{
					t_CJSON JSON;
					
					JSON["TestNull"] = nullptr;
					JSON["TestString"] = "String";
					JSON["TestInt"] = 54;
					JSON["TestFloat"] = fp32(5.5);
					JSON["TestBool"] = true;
					t_CJSON Object;
					Object["5"] = 6;
					JSON["TestObject"] = Object;
					t_CJSON Array;
					Array.f_Insert(6);
					JSON["TestArray"] = Array;
					JSON["TestInvalid"];
					
					
					DMibExpect(JSON["TestNull"].f_AsString("Default"), ==, "null");
					DMibExpect(JSON["TestString"].f_AsString("Default"), ==, "String");
					DMibExpect(JSON["TestInt"].f_AsString("Default"), ==, "54");
					DMibExpect(JSON["TestFloat"].f_AsString("Default"), ==, "5.5");
					DMibExpect(JSON["TestBool"].f_AsString("Default"), ==, "true");
					DMibExpect(JSON["TestObject"].f_AsString("Default"), ==, Object.f_ToString());
					DMibExpect(JSON["TestArray"].f_AsString("Default"), ==, Array.f_ToString());
					DMibExpect(JSON["TestInvalid"].f_AsString("Default"), ==, "Default");
				};
				DMibTestSuite("Get as integer default")
				{
					t_CJSON JSON;
					
					JSON["TestNull"] = nullptr;
					JSON["TestString"] = "66";
					JSON["TestInt"] = 54;
					JSON["TestFloat"] = fp32(5.5);
					JSON["TestBool"] = true;
					t_CJSON Object;
					Object["5"] = 6;
					JSON["TestObject"] = Object;
					t_CJSON Array;
					Array.f_Insert(6);
					JSON["TestArray"] = Array;
					JSON["TestInvalid"];
					
					
					DMibExpect(JSON["TestNull"].f_AsInteger(77), ==, 77);
					DMibExpect(JSON["TestString"].f_AsInteger(77), ==, 66);
					DMibExpect(JSON["TestInt"].f_AsInteger(77), ==, 54);
					DMibExpect(JSON["TestFloat"].f_AsInteger(77), ==, 6);
					DMibExpect(JSON["TestBool"].f_AsInteger(77), ==, 1);
					DMibExpect(JSON["TestObject"].f_AsInteger(77), ==, 77);
					DMibExpect(JSON["TestArray"].f_AsInteger(77), ==, 77);
					DMibExpect(JSON["TestInvalid"].f_AsInteger(77), ==, 77);
				};
				DMibTestSuite("Get as float default")
				{
					t_CJSON JSON;
					
					JSON["TestNull"] = nullptr;
					JSON["TestString"] = "66.5";
					JSON["TestInt"] = 54;
					JSON["TestFloat"] = fp32(5.5);
					JSON["TestBool"] = true;
					t_CJSON Object;
					Object["5"] = 6;
					JSON["TestObject"] = Object;
					t_CJSON Array;
					Array.f_Insert(6);
					JSON["TestArray"] = Array;
					JSON["TestInvalid"];
					
					DMibExpect(JSON["TestNull"].f_AsFloat(77.7), ==, 77.7);
					DMibExpect(JSON["TestString"].f_AsFloat(77.7), ==, 66.5);
					DMibExpect(JSON["TestInt"].f_AsFloat(77.7), ==, 54.0);
					DMibExpect(JSON["TestFloat"].f_AsFloat(77.7), ==, 5.5);
					DMibExpect(JSON["TestBool"].f_AsFloat(77.7), ==, 1.0);
					DMibExpect(JSON["TestObject"].f_AsFloat(77.7), ==, 77.7);
					DMibExpect(JSON["TestArray"].f_AsFloat(77.7), ==, 77.7);
					DMibExpect(JSON["TestInvalid"].f_AsFloat(77.7), ==, 77.7);
				};
				DMibTestSuite("Get as boolean default")
				{
					t_CJSON JSON;
					
					JSON["TestNull"] = nullptr;
					JSON["TestString0"] = "true";
					JSON["TestString1"] = "false";
					JSON["TestString2"] = "1";
					JSON["TestString3"] = "4";
					JSON["TestString4"] = "0";
					JSON["TestString5"] = "0.5";
					JSON["TestInt"] = 54;
					JSON["TestFloat"] = fp32(5.5);
					JSON["TestBool"] = true;
					t_CJSON Object;
					Object["5"] = 6;
					JSON["TestObject"] = Object;
					t_CJSON Array;
					Array.f_Insert(6);
					JSON["TestArray"] = Array;
					JSON["TestInvalid"];
					
					DMibExpectTrue(JSON["TestNull"].f_AsBoolean(true));
					DMibExpectTrue(JSON["TestString0"].f_AsBoolean(true));
					DMibExpectFalse(JSON["TestString1"].f_AsBoolean(true));
					DMibExpectTrue(JSON["TestString2"].f_AsBoolean(true));
					DMibExpectTrue(JSON["TestString3"].f_AsBoolean(true));
					DMibExpectFalse(JSON["TestString4"].f_AsBoolean(true));
					DMibExpectFalse(JSON["TestString5"].f_AsBoolean(true));
					DMibExpectTrue(JSON["TestInt"].f_AsBoolean(true));
					DMibExpectTrue(JSON["TestFloat"].f_AsBoolean(true));
					DMibExpectTrue(JSON["TestBool"].f_AsBoolean(true));
					DMibExpectTrue(JSON["TestObject"].f_AsBoolean(true));
					DMibExpectTrue(JSON["TestArray"].f_AsBoolean(true));
					DMibExpectTrue(JSON["TestInvalid"].f_AsBoolean(true));
				};
			};

			DMibTestCategory("Generate Exceptions")
			{
				DMibTestSuite("Invalid type")
				{
					t_CJSON JSON;
					
					JSON["Test"];
					
					DMibExpectException(JSON.f_ToString(), DMibErrorInstance("Invalid JSON type in value node"));
				};
			};
			
			DMibTestCategoryFlags("Parse Exceptions", ETestCategoryFlag_DisableExceptionFilter)
			{
				DMibTestSuite("Key quoting")
				{
					CStr Data;
					Data = 
						"    \n"
						"    \n"
						"    \n"
						"    \n"
						"{ Key Value }\n"
					;

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();
					
					Error.m_Error = "Expected \" to start object key name";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 5;
					Error.m_Location.m_Column = 3;
					Error.m_Location.m_Character = 22;
					
					fp_TestParseError(Data, Errors);
				};
				DMibTestSuite("End of key missing")
				{
					CStr Data = "{ \"Key";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();
					
					Error.m_Error = "End of string character '\"' not found for key name string";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 3;
					Error.m_Location.m_Character = 2;
					
					fp_TestParseError(Data, Errors);
				};
				DMibTestSuite("Newline in string")
				{
					CStr Data = "{ \"Key\n";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();
					
					Error.m_Error = "Control characters or new lines not allowed in string. Use escaped characters.";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 2;
					Error.m_Location.m_Column = 1;
					Error.m_Location.m_Character = 6;
					
					fp_TestParseError(Data, Errors);
				};
				DMibTestSuite("Key value separator")
				{
					CStr Data = "{ \"Key\" \"Value\" }";
					
					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();
					
					Error.m_Error = "Expected : to follow key name in object";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 9;
					Error.m_Location.m_Character = 8;
					
					fp_TestParseError(Data, Errors);
				};
				DMibTestSuite("Invalid escape value")
				{
					CStr Data = "\"Escaped: \\g\"";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();
					
					Error.m_Error = "Invalid escape value";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 12;
					Error.m_Location.m_Character = 11;
					
					fp_TestParseError(Data, Errors);
				};
				DMibTestSuite("Too short UTF16")
				{
					CStr Data = "\"Escaped: \\u05";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();
					
					Error.m_Error = "Too short escaped UTF16 value";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 13;
					Error.m_Location.m_Character = 12;
					
					fp_TestParseError(Data, Errors);
				};
				DMibTestSuite("Invalid UTF16")
				{
					CStr Data = "\"Escaped: \\u05tt\"";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();
					
					Error.m_Error = "Invalid escaped UTF16 value";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 13;
					Error.m_Location.m_Character = 12;
					
					fp_TestParseError(Data, Errors);
				};
				DMibTestSuite("Null character")
				{
					CStr Data = "\"Null: \\u0000\"";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();
					
					Error.m_Error = "Null characters not supported in this implementation";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 10;
					Error.m_Location.m_Character = 9;
					
					fp_TestParseError(Data, Errors);
				};
				DMibTestSuite("Missing object close")
				{
					CStr Data =
						"{ \"Key\": \"Value\",\n"
						"\n"
						"\"Key\": \"Value\"\n"
					;

					TCVector<CParseError> Errors;
					{
						auto &Error = Errors.f_Insert();
						
						Error.m_Error = "Missing closing } for object";
						Error.m_Location.m_File = mp_TestFilePath;
						Error.m_Location.m_Line = 4;
						Error.m_Location.m_Column = 1;
						Error.m_Location.m_Character = 34;
					}
					{
						auto &Error = Errors.f_Insert();
						
						Error.m_Error = "See opening { for object";
						Error.m_Location.m_File = mp_TestFilePath;
						Error.m_Location.m_Line = 1;
						Error.m_Location.m_Column = 1;
						Error.m_Location.m_Character = 0;
					}
					
					fp_TestParseError(Data, Errors);
				};
				DMibTestSuite("Missing array close")
				{
					CStr Data =
						"[ 5, 6,\n"
						"\n"
						"5, 7, 8"
					;

					TCVector<CParseError> Errors;
					
					{
						auto &Error = Errors.f_Insert();
						Error.m_Error = "Missing closing ] for array";
						Error.m_Location.m_File = mp_TestFilePath;
						Error.m_Location.m_Line = 3;
						Error.m_Location.m_Column = 8;
						Error.m_Location.m_Character = 16;
					}
					{
						auto &Error = Errors.f_Insert();
						Error.m_Error = "See opening [ for array";
						Error.m_Location.m_File = mp_TestFilePath;
						Error.m_Location.m_Line = 1;
						Error.m_Location.m_Column = 1;
						Error.m_Location.m_Character = 0;
					}
					
					fp_TestParseError(Data, Errors);
				};
				DMibTestSuite("String without end")
				{
					CStr Data = "\"String without end";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();
					
					Error.m_Error = "End of string character '\"' not found for string";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 1;
					Error.m_Location.m_Character = 0;
					
					fp_TestParseError(Data, Errors);
				};
				DMibTestSuite("Invalid literal")
				{
					CStr Data = "55ueeu";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();
					
					Error.m_Error = "Invalid literal starting with: 55ue";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 1;
					Error.m_Location.m_Character = 0;
					
					fp_TestParseError(Data, Errors);
				};
				DMibTestSuite("Unexpected character after root value")
				{
					CStr Data =
						"{\n"
						"\"Key\": \"Value\"\n"
						"}\n"
						"55\n"
					;

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();
					
					Error.m_Error = "Unexpected character after root value";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 4;
					Error.m_Location.m_Column = 1;
					Error.m_Location.m_Character = 19;
					
					fp_TestParseError(Data, Errors);
				};
			};
		}
		
	private:
		void fp_TestParseError(NMib::NStr::CStr const &_ToParse, NMib::NContainer::TCVector<NMib::NStr::CParseError> const &_ExpectedErrors)
		{
			NMib::NStr::CExceptionParse Exception = DMibImpExceptionInstanceSpecific(NMib::NStr::CExceptionParse, "JSON Error", NMib::fg_Default());
			try
			{
				mp_fParse(_ToParse, mp_TestFilePath);
			}
			catch (NMib::NStr::CExceptionParse const &_Exception)
			{
				Exception = _Exception;
			}
			
			auto &Errors = Exception.f_GetSpecific();
			if (Errors != _ExpectedErrors)
				NMib::NFile::CFile::fs_WriteStringToFile(mp_TestFilePath, _ToParse);
			DMibExpect(Errors, ==, _ExpectedErrors);
		}

		NMib::NStr::CStr mp_TestFilePath;
		t_CJSON mp_JSONReference;
		NMib::NStr::CStr mp_JSONReferenceText;
		NMib::NFunction::TCFunction<t_CJSON (NMib::NStr::CStr const &_ToParse, NMib::NStr::CStr const &_FileName)> mp_fParse;
	};
}
