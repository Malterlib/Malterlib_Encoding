// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Encoding/Json>
#include <Mib/Test/Exception>

namespace
{
	// Helper to count elements in an iterator with operator bool() and operator++()
	template <typename t_CIterator>
	aint fsg_IteratorCount(t_CIterator _Iterator)
	{
		aint nCount = 0;
		for (; _Iterator; ++_Iterator)
			++nCount;
		return nCount;
	}

	template <typename t_CJson>
	class TCJsonTests
	{
	public:
		TCJsonTests
			(
				t_CJson const &_Reference
				, NMib::NStr::CStr const &_ReferenceText
				, NMib::NFunction::TCFunction<t_CJson (NMib::NStr::CStr const &_ToParse, NMib::NStr::CStr const &_FileName)> const &_fParse
			)
			: mp_JsonReference(_Reference)
			, mp_JsonReferenceText(_ReferenceText)
			, mp_fParse(_fParse)
		{
			using namespace NMib::NStr;

			mp_TestFilePath = NMib::NFile::CFile::fs_GetProgramDirectory() / ("Test{nfh}.json"_f << NMib::fg_GetTypeHash<t_CJson>());
		}

		void f_DoTests()
		{
			using namespace NMib;
			using namespace NMib::NStr;
			using namespace NMib::NEncoding;
			using namespace NMib::NContainer;
			DMibTestSuite("Functionality")
			{
				{
					DMibTestPath("Generating");
					t_CJson Json = mp_JsonReference;

					CStr GeneratedJsonText = Json.f_ToString();

					DMibExpect(GeneratedJsonText, ==, mp_JsonReferenceText);
				}
				{
					DMibTestPath("Copy");
					t_CJson Json = mp_JsonReference;

					t_CJson JsonCopy(Json);

					CStr GeneratedJsonText = JsonCopy.f_ToString();

					DMibExpect(GeneratedJsonText, ==, mp_JsonReferenceText);
				}
				{
					DMibTestPath("Move");
					t_CJson Json = mp_JsonReference;

					t_CJson JsonCopy(fg_Move(Json));

					CStr GeneratedJsonText = JsonCopy.f_ToString();

					DMibExpect(GeneratedJsonText, ==, mp_JsonReferenceText);
				}
				{
					DMibTestPath("Assign");
					t_CJson Json = mp_JsonReference;

					t_CJson JsonCopy;
					JsonCopy = Json;

					CStr GeneratedJsonText = JsonCopy.f_ToString();

					DMibExpect(GeneratedJsonText, ==, mp_JsonReferenceText);
				}
				{
					DMibTestPath("MoveAssign");
					t_CJson Json = mp_JsonReference;

					t_CJson JsonCopy;
					JsonCopy = fg_Move(Json);

					CStr GeneratedJsonText = JsonCopy.f_ToString();

					DMibExpect(GeneratedJsonText, ==, mp_JsonReferenceText);
				}
				{
					DMibTestPath("AssignTree");
					t_CJson Json = mp_JsonReference;

					t_CJson JsonCopy = Json;
					JsonCopy["TreeCopy"] = Json;

					CStr GeneratedJsonText = JsonCopy.f_ToString();

					DMibExpect(GeneratedJsonText, !=, mp_JsonReferenceText);
				}
				{
					DMibTestPath("Get member");
					t_CJson Json = mp_JsonReference;

					DMibAssertTrue(Json.f_GetMember("Key"));
					DMibExpect(Json.f_GetMember("Key")->f_String(), ==, "Value");

					DMibAssertTrue(fg_Const(Json).f_GetMember("Key"));
					DMibExpect(fg_Const(Json).f_GetMember("Key")->f_String(), ==, "Value");

					DMibExpectFalse(Json.f_GetMember("NonExistingKey"));
				}
				{
					DMibTestPath("Comparison");
					DMibExpect(mp_JsonReference, ==, mp_JsonReference);
					DMibTest(!(DMibExpr(mp_JsonReference) < DMibExpr(mp_JsonReference)));
				}
				{
					DMibTestPath("Parsing");
					t_CJson Json = mp_fParse(mp_JsonReferenceText, CStr());

					DMibExpect(Json, ==, mp_JsonReference);
				}
				{
					DMibTestPath("Json roundtrip");
					t_CJson Json = mp_fParse(mp_JsonReferenceText, CStr());
					CStr GeneratedJsonText = Json.f_ToString();

					DMibExpect(GeneratedJsonText, ==, mp_JsonReferenceText);
				}
				{
					DMibTestPath("Json roundtrip no whitespace");
					CStr JsonText = mp_JsonReferenceText.f_Replace("\n", "").f_Replace(" ", "").f_Replace("\t", "");
					t_CJson Json = mp_fParse(JsonText, CStr());
					CStr GeneratedJsonText = Json.f_ToString(nullptr);

					DMibExpect(GeneratedJsonText, ==, JsonText);
				}
				{
					DMibTestPath("Remove by string");
					t_CJson Json;

					Json["Test0"] = "52";
					Json["Test1"] = "53";

					Json.f_RemoveMember("Test0");

					t_CJson JsonRemoved;
					JsonRemoved["Test1"] = "53";

					DMibExpect(Json, ==, JsonRemoved);
				}
				if constexpr (t_CJson::mc_bOrdered)
				{
					DMibTestPath("Remove by ordered const iterator");
					t_CJson Json;

					Json["Test0"] = "52";
					Json["Test1"] = "53";
					Json["Test2"] = "54";

					auto iMember = fg_Const(Json).f_Object().f_OrderedIterator();

					++iMember;
					Json.f_Object().f_RemoveMember(iMember);

					DMibExpect(iMember->f_Value().f_String(), ==, "54");

					t_CJson JsonRemoved;
					JsonRemoved["Test0"] = "52";
					JsonRemoved["Test2"] = "54";

					DMibExpect(Json, ==, JsonRemoved);
				}
				{
					DMibTestPath("Remove by ordered iterator");
					t_CJson Json;

					Json["Test0"] = "52";
					Json["Test1"] = "53";
					Json["Test2"] = "54";

					auto iMember = Json.f_Object().f_OrderedIterator();

					++iMember;
					Json.f_Object().f_RemoveMember(iMember);

					DMibExpect(iMember->f_Value().f_String(), ==, "54");

					t_CJson JsonRemoved;
					JsonRemoved["Test0"] = "52";
					JsonRemoved["Test2"] = "54";

					DMibExpect(Json, ==, JsonRemoved);
				}
				if constexpr (t_CJson::mc_bOrdered)
				{
					DMibTestPath("Remove by sorted iterator");
					t_CJson Json;

					Json["Test3"] = "54";
					Json["Test1"] = "52";
					Json["Test2"] = "53";

					auto iMember = Json.f_Object().f_SortedIterator();

					++iMember;
					Json.f_Object().f_RemoveMember(iMember);

					DMibExpect(iMember->f_Value().f_String(), ==, "54");

					t_CJson JsonRemoved;
					JsonRemoved["Test3"] = "54";
					JsonRemoved["Test1"] = "52";

					DMibExpect(Json, ==, JsonRemoved);
				}
				{
					DMibTestPath("Get as string");
					t_CJson Json;

					Json["TestNull"] = nullptr;
					Json["TestString"] = "String";
					Json["TestInt"] = 54;
					Json["TestFloat"] = fp32(5.5);
					Json["TestBool"] = true;
					t_CJson Object;
					Object["5"] = 6;
					Json["TestObject"] = Object;
					t_CJson Array;
					Array.f_Insert(6);
					Json["TestArray"] = Array;
					Json["TestInvalid"];


					DMibExpect(Json["TestNull"].f_AsString(), ==, "null");
					DMibExpect(Json["TestString"].f_AsString(), ==, "String");
					DMibExpect(Json["TestInt"].f_AsString(), ==, "54");
					DMibExpect(Json["TestFloat"].f_AsString(), ==, "5.5");
					DMibExpect(Json["TestBool"].f_AsString(), ==, "true");
					DMibExpect(Json["TestObject"].f_AsString(), ==, Object.f_ToString());
					DMibExpect(Json["TestArray"].f_AsString(), ==, Array.f_ToString());
					DMibExpectException(Json["TestInvalid"].f_AsString(), DMibErrorInstance("JSON type cannot be converted to string"));
				}
				{
					DMibTestPath("Get as integer");
					t_CJson Json;

					Json["TestNull"] = nullptr;
					Json["TestString"] = "66";
					Json["TestInt"] = 54;
					Json["TestFloat"] = fp32(5.5);
					Json["TestBool"] = true;
					t_CJson Object;
					Object["5"] = 6;
					Json["TestObject"] = Object;
					t_CJson Array;
					Array.f_Insert(6);
					Json["TestArray"] = Array;
					Json["TestInvalid"];


					DMibExpectException(Json["TestNull"].f_AsInteger(), DMibErrorInstance("JSON type cannot be converted to integer"));
					DMibExpect(Json["TestString"].f_AsInteger(), ==, 66);
					DMibExpect(Json["TestInt"].f_AsInteger(), ==, 54);
					DMibExpect(Json["TestFloat"].f_AsInteger(), ==, 6);
					DMibExpect(Json["TestBool"].f_AsInteger(), ==, 1);
					DMibExpectException(Json["TestObject"].f_AsInteger(), DMibErrorInstance("JSON type cannot be converted to integer"));
					DMibExpectException(Json["TestArray"].f_AsInteger(), DMibErrorInstance("JSON type cannot be converted to integer"));
					DMibExpectException(Json["TestInvalid"].f_AsInteger(), DMibErrorInstance("JSON type cannot be converted to integer"));
				}
				{
					DMibTestPath("Get as float");
					t_CJson Json;

					Json["TestNull"] = nullptr;
					Json["TestString"] = "66.5";
					Json["TestInt"] = 54;
					Json["TestFloat"] = fp32(5.5);
					Json["TestBool"] = true;
					t_CJson Object;
					Object["5"] = 6;
					Json["TestObject"] = Object;
					t_CJson Array;
					Array.f_Insert(6);
					Json["TestArray"] = Array;
					Json["TestInvalid"];

					DMibExpectException(Json["TestNull"].f_AsFloat(), DMibErrorInstance("JSON type cannot be converted to float"));
					DMibExpect(Json["TestString"].f_AsFloat(), ==, 66.5);
					DMibExpect(Json["TestInt"].f_AsFloat(), ==, 54.0);
					DMibExpect(Json["TestFloat"].f_AsFloat(), ==, 5.5);
					DMibExpect(Json["TestBool"].f_AsFloat(), ==, 1.0);
					DMibExpectException(Json["TestObject"].f_AsFloat(), DMibErrorInstance("JSON type cannot be converted to float"));
					DMibExpectException(Json["TestArray"].f_AsFloat(), DMibErrorInstance("JSON type cannot be converted to float"));
					DMibExpectException(Json["TestInvalid"].f_AsFloat(), DMibErrorInstance("JSON type cannot be converted to float"));
				}
				{
					DMibTestPath("Get as boolean");
					t_CJson Json;

					Json["TestNull"] = nullptr;
					Json["TestString0"] = "true";
					Json["TestString1"] = "false";
					Json["TestString2"] = "1";
					Json["TestString3"] = "4";
					Json["TestString4"] = "0";
					Json["TestString5"] = "0.5";
					Json["TestInt"] = 54;
					Json["TestFloat"] = fp32(5.5);
					Json["TestBool"] = true;
					t_CJson Object;
					Object["5"] = 6;
					Json["TestObject"] = Object;
					t_CJson Array;
					Array.f_Insert(6);
					Json["TestArray"] = Array;
					Json["TestInvalid"];

					DMibExpectException(Json["TestNull"].f_AsBoolean(), DMibErrorInstance("JSON type cannot be converted to boolean"));
					DMibExpectTrue(Json["TestString0"].f_AsBoolean());
					DMibExpectFalse(Json["TestString1"].f_AsBoolean());
					DMibExpectTrue(Json["TestString2"].f_AsBoolean());
					DMibExpectTrue(Json["TestString3"].f_AsBoolean());
					DMibExpectFalse(Json["TestString4"].f_AsBoolean());
					DMibExpectFalse(Json["TestString5"].f_AsBoolean());
					DMibExpectTrue(Json["TestInt"].f_AsBoolean());
					DMibExpectTrue(Json["TestFloat"].f_AsBoolean());
					DMibExpectTrue(Json["TestBool"].f_AsBoolean());
					DMibExpectException(Json["TestObject"].f_AsBoolean(), DMibErrorInstance("JSON type cannot be converted to boolean"));
					DMibExpectException(Json["TestArray"].f_AsBoolean(), DMibErrorInstance("JSON type cannot be converted to boolean"));
					DMibExpectException(Json["TestInvalid"].f_AsBoolean(), DMibErrorInstance("JSON type cannot be converted to boolean"));
				}
				{
					DMibTestPath("Get as string default");
					t_CJson Json;

					Json["TestNull"] = nullptr;
					Json["TestString"] = "String";
					Json["TestInt"] = 54;
					Json["TestFloat"] = fp32(5.5);
					Json["TestBool"] = true;
					t_CJson Object;
					Object["5"] = 6;
					Json["TestObject"] = Object;
					t_CJson Array;
					Array.f_Insert(6);
					Json["TestArray"] = Array;
					Json["TestInvalid"];


					DMibExpect(Json["TestNull"].f_AsString("Default"), ==, "null");
					DMibExpect(Json["TestString"].f_AsString("Default"), ==, "String");
					DMibExpect(Json["TestInt"].f_AsString("Default"), ==, "54");
					DMibExpect(Json["TestFloat"].f_AsString("Default"), ==, "5.5");
					DMibExpect(Json["TestBool"].f_AsString("Default"), ==, "true");
					DMibExpect(Json["TestObject"].f_AsString("Default"), ==, Object.f_ToString());
					DMibExpect(Json["TestArray"].f_AsString("Default"), ==, Array.f_ToString());
					DMibExpect(Json["TestInvalid"].f_AsString("Default"), ==, "Default");
				}
				{
					DMibTestPath("Get as integer default");
					t_CJson Json;

					Json["TestNull"] = nullptr;
					Json["TestString"] = "66";
					Json["TestInt"] = 54;
					Json["TestFloat"] = fp32(5.5);
					Json["TestBool"] = true;
					t_CJson Object;
					Object["5"] = 6;
					Json["TestObject"] = Object;
					t_CJson Array;
					Array.f_Insert(6);
					Json["TestArray"] = Array;
					Json["TestInvalid"];


					DMibExpect(Json["TestNull"].f_AsInteger(77), ==, 77);
					DMibExpect(Json["TestString"].f_AsInteger(77), ==, 66);
					DMibExpect(Json["TestInt"].f_AsInteger(77), ==, 54);
					DMibExpect(Json["TestFloat"].f_AsInteger(77), ==, 6);
					DMibExpect(Json["TestBool"].f_AsInteger(77), ==, 1);
					DMibExpect(Json["TestObject"].f_AsInteger(77), ==, 77);
					DMibExpect(Json["TestArray"].f_AsInteger(77), ==, 77);
					DMibExpect(Json["TestInvalid"].f_AsInteger(77), ==, 77);
				}
				{
					DMibTestPath("Get as float default");
					t_CJson Json;

					Json["TestNull"] = nullptr;
					Json["TestString"] = "66.5";
					Json["TestInt"] = 54;
					Json["TestFloat"] = fp32(5.5);
					Json["TestBool"] = true;
					t_CJson Object;
					Object["5"] = 6;
					Json["TestObject"] = Object;
					t_CJson Array;
					Array.f_Insert(6);
					Json["TestArray"] = Array;
					Json["TestInvalid"];

					DMibExpect(Json["TestNull"].f_AsFloat(77.7), ==, 77.7);
					DMibExpect(Json["TestString"].f_AsFloat(77.7), ==, 66.5);
					DMibExpect(Json["TestInt"].f_AsFloat(77.7), ==, 54.0);
					DMibExpect(Json["TestFloat"].f_AsFloat(77.7), ==, 5.5);
					DMibExpect(Json["TestBool"].f_AsFloat(77.7), ==, 1.0);
					DMibExpect(Json["TestObject"].f_AsFloat(77.7), ==, 77.7);
					DMibExpect(Json["TestArray"].f_AsFloat(77.7), ==, 77.7);
					DMibExpect(Json["TestInvalid"].f_AsFloat(77.7), ==, 77.7);
				}
				{
					DMibTestPath("Get as boolean default");
					t_CJson Json;

					Json["TestNull"] = nullptr;
					Json["TestString0"] = "true";
					Json["TestString1"] = "false";
					Json["TestString2"] = "1";
					Json["TestString3"] = "4";
					Json["TestString4"] = "0";
					Json["TestString5"] = "0.5";
					Json["TestInt"] = 54;
					Json["TestFloat"] = fp32(5.5);
					Json["TestBool"] = true;
					t_CJson Object;
					Object["5"] = 6;
					Json["TestObject"] = Object;
					t_CJson Array;
					Array.f_Insert(6);
					Json["TestArray"] = Array;
					Json["TestInvalid"];

					DMibExpectTrue(Json["TestNull"].f_AsBoolean(true));
					DMibExpectTrue(Json["TestString0"].f_AsBoolean(true));
					DMibExpectFalse(Json["TestString1"].f_AsBoolean(true));
					DMibExpectTrue(Json["TestString2"].f_AsBoolean(true));
					DMibExpectTrue(Json["TestString3"].f_AsBoolean(true));
					DMibExpectFalse(Json["TestString4"].f_AsBoolean(true));
					DMibExpectFalse(Json["TestString5"].f_AsBoolean(true));
					DMibExpectTrue(Json["TestInt"].f_AsBoolean(true));
					DMibExpectTrue(Json["TestFloat"].f_AsBoolean(true));
					DMibExpectTrue(Json["TestBool"].f_AsBoolean(true));
					DMibExpectTrue(Json["TestObject"].f_AsBoolean(true));
					DMibExpectTrue(Json["TestArray"].f_AsBoolean(true));
					DMibExpectTrue(Json["TestInvalid"].f_AsBoolean(true));
				}
			};

			DMibTestSuite("Generate Exceptions")
			{
				{
					DMibTestPath("Invalid type");
					t_CJson Json;

					Json["Test"];

					DMibExpectException(Json.f_ToString(), DMibErrorInstance("Invalid JSON type in value node"));
				}
			};

			DMibTestSuite("Destructive Iterators")
			{
				// Test ordered destructive iterator
				{
					DMibTestPath("OrderedDestructiveIterator");
					t_CJson Source;
					Source["a"] = 1;
					Source["b"] = 2;
					Source["c"] = 3;

					TCVector<CStr> Keys;
					TCVector<int64> Values;

					for (auto Iter = fg_Move(Source.f_Object()).f_OrderedDestructiveIterator(); Iter; ++Iter)
					{
						if constexpr (t_CJson::mc_bOrdered)
						{
							Keys.f_InsertLast(Iter->f_Name());
							Values.f_InsertLast(Iter->f_Value().f_Integer());
						}
						else
						{
							Keys.f_InsertLast(Iter->f_Key());
							Values.f_InsertLast(Iter->f_Value().f_Value().f_Integer());
						}
					}

					DMibExpect(Keys.f_GetLen(), ==, 3u);
					// Source should be empty after destructive iteration
					DMibExpectTrue(Source.f_Object().f_IsEmpty());
				}
				// Test sorted destructive iterator
				{
					DMibTestPath("SortedDestructiveIterator");
					t_CJson Source;
					Source["c"] = 3;
					Source["a"] = 1;
					Source["b"] = 2;

					TCVector<CStr> Keys;

					for (auto Iter = fg_Move(Source.f_Object()).f_SortedDestructiveIterator(); Iter; ++Iter)
					{
						Keys.f_InsertLast(Iter->f_Key());
					}

					// Should be in sorted order for both ordered and sorted
					DMibExpect(Keys.f_GetLen(), ==, 3u);
					DMibExpect(Keys[0], ==, CStr("a"));
					DMibExpect(Keys[1], ==, CStr("b"));
					DMibExpect(Keys[2], ==, CStr("c"));

					DMibExpectTrue(Source.f_Object().f_IsEmpty());
				}
				// Test sorted iterator extraction with sorted order preserved
				{
					DMibTestPath("Sorted Extract and Insert");
					t_CJson Source;
					Source["zebra"] = 5;
					Source["alpha"] = 1;
					Source["mango"] = 3;
					Source["beta"] = 2;
					Source["omega"] = 4;

					t_CJson Dest;
					Dest = EJsonType_Object;

					TCVector<CStr> ExtractOrder;

					for (auto Iter = fg_Move(Source.f_Object()).f_SortedDestructiveIterator(); Iter; )
					{
						ExtractOrder.f_InsertLast(Iter->f_Key());
						auto Handle = Iter.f_ExtractNode();
						Dest.f_Object().f_Insert(fg_Move(Handle));
					}

					// Verify extraction happened in sorted order
					DMibExpect(ExtractOrder.f_GetLen(), ==, 5u);
					DMibExpect(ExtractOrder[0], ==, CStr("alpha"));
					DMibExpect(ExtractOrder[1], ==, CStr("beta"));
					DMibExpect(ExtractOrder[2], ==, CStr("mango"));
					DMibExpect(ExtractOrder[3], ==, CStr("omega"));
					DMibExpect(ExtractOrder[4], ==, CStr("zebra"));

					// Verify destination has all values
					DMibExpectTrue(Source.f_Object().f_IsEmpty());
					DMibExpect(Dest["alpha"].f_Integer(), ==, 1);
					DMibExpect(Dest["beta"].f_Integer(), ==, 2);
					DMibExpect(Dest["mango"].f_Integer(), ==, 3);
					DMibExpect(Dest["omega"].f_Integer(), ==, 4);
					DMibExpect(Dest["zebra"].f_Integer(), ==, 5);
				}
				// Test sorted partial extraction
				{
					DMibTestPath("Sorted partial extraction");
					t_CJson Source;
					Source["d"] = 4;
					Source["a"] = 1;
					Source["c"] = 3;
					Source["b"] = 2;
					Source["e"] = 5;

					t_CJson Dest;
					Dest = EJsonType_Object;

					// Extract only values less than 3 (in sorted key order)
					for (auto Iter = fg_Move(Source.f_Object()).f_SortedDestructiveIterator(); Iter; )
					{
						int64 Value;
						if constexpr (t_CJson::mc_bOrdered)
							Value = Iter->f_Value().f_Integer();
						else
							Value = Iter->f_Value().f_Value().f_Integer();

						if (Value < 3)
						{
							auto Handle = Iter.f_ExtractNode();
							Dest.f_Object().f_Insert(fg_Move(Handle));
						}
						else
						{
							++Iter;
						}
					}

					// Source should be empty (destructive iterator clears remaining)
					DMibExpectTrue(Source.f_Object().f_IsEmpty());

					// Dest should have a=1 and b=2
					DMibExpect(Dest["a"].f_Integer(), ==, 1);
					DMibExpect(Dest["b"].f_Integer(), ==, 2);
					DMibExpect(Dest.f_Object().f_GetMember("c"), ==, nullptr);
				}
				// Test sorted iterator with complex nested values
				{
					DMibTestPath("Sorted transfer complex values");
					t_CJson Source;
					Source["z"]["deep"]["value"] = 100;
					Source["a"]["array"].f_Insert("first");
					Source["a"]["array"].f_Insert("second");
					Source["m"]["number"] = 42;

					t_CJson Dest;
					Dest = EJsonType_Object;

					TCVector<CStr> Order;
					for (auto Iter = fg_Move(Source.f_Object()).f_SortedDestructiveIterator(); Iter; )
					{
						Order.f_InsertLast(Iter->f_Key());
						auto Handle = Iter.f_ExtractNode();
						Dest.f_Object().f_Insert(fg_Move(Handle));
					}

					// Verify sorted order
					DMibExpect(Order[0], ==, CStr("a"));
					DMibExpect(Order[1], ==, CStr("m"));
					DMibExpect(Order[2], ==, CStr("z"));

					// Verify source is empty after full extraction
					DMibExpectTrue(Source.f_Object().f_IsEmpty());

					// Verify complex values transferred correctly
					DMibExpect(Dest["a"]["array"].f_Array()[0].f_String(), ==, CStr("first"));
					DMibExpect(Dest["a"]["array"].f_Array()[1].f_String(), ==, CStr("second"));
					DMibExpect(Dest["m"]["number"].f_Integer(), ==, 42);
					DMibExpect(Dest["z"]["deep"]["value"].f_Integer(), ==, 100);
				}
				// Test sorted handle value access (ordered only)
				if constexpr (t_CJson::mc_bOrdered)
				{
					DMibTestPath("Sorted handle value access");
					t_CJson Source;
					Source["beta"] = "second";
					Source["alpha"] = "first";
					Source["gamma"] = "third";

					TCVector<CStr> Names;
					TCVector<CStr> Values;

					for (auto Iter = fg_Move(Source.f_Object()).f_SortedDestructiveIterator(); Iter; )
					{
						auto Handle = Iter.f_ExtractNode();
						Names.f_InsertLast(Handle.f_Name());
						Values.f_InsertLast(Handle.f_Value().f_String());
					}

					// Verify sorted order and values
					DMibExpect(Names[0], ==, CStr("alpha"));
					DMibExpect(Values[0], ==, CStr("first"));
					DMibExpect(Names[1], ==, CStr("beta"));
					DMibExpect(Values[1], ==, CStr("second"));
					DMibExpect(Names[2], ==, CStr("gamma"));
					DMibExpect(Values[2], ==, CStr("third"));

					// Verify source is empty after full extraction
					DMibExpectTrue(Source.f_Object().f_IsEmpty());
				}
				// Test extraction and reinsertion
				{
					DMibTestPath("Extract and Insert");
					t_CJson Source;
					Source["a"] = 1;
					Source["b"] = 2;
					Source["c"] = 3;

					t_CJson Dest;
					Dest = EJsonType_Object;

					for (auto Iter = fg_Move(Source.f_Object()).f_OrderedDestructiveIterator(); Iter; )
					{
						auto Handle = Iter.f_ExtractNode();
						Dest.f_Object().f_Insert(fg_Move(Handle));
					}

					DMibExpectTrue(Source.f_Object().f_IsEmpty());
					DMibExpectFalse(Dest.f_Object().f_IsEmpty());
					DMibExpect(Dest["a"].f_Integer(), ==, 1);
					DMibExpect(Dest["b"].f_Integer(), ==, 2);
					DMibExpect(Dest["c"].f_Integer(), ==, 3);
				}
				// Test partial extraction
				{
					DMibTestPath("Partial extraction");
					t_CJson Source;
					Source["a"] = 1;
					Source["b"] = 2;
					Source["c"] = 3;
					Source["d"] = 4;

					t_CJson Dest;
					Dest = EJsonType_Object;

					for (auto Iter = fg_Move(Source.f_Object()).f_OrderedDestructiveIterator(); Iter; )
					{
						int64 Value;
						if constexpr (t_CJson::mc_bOrdered)
							Value = Iter->f_Value().f_Integer();
						else
							Value = Iter->f_Value().f_Value().f_Integer();

						if (Value % 2 == 0)
						{
							auto Handle = Iter.f_ExtractNode();
							Dest.f_Object().f_Insert(fg_Move(Handle));
						}
						else
						{
							++Iter;
						}
					}

					// Source should be empty (destructive iterator clears remaining)
					DMibExpectTrue(Source.f_Object().f_IsEmpty());

					// Dest should have even values
					DMibExpect(Dest["b"].f_Integer(), ==, 2);
					DMibExpect(Dest["d"].f_Integer(), ==, 4);
				}
				// Test handle value access (ordered only has named accessors)
				if constexpr (t_CJson::mc_bOrdered)
				{
					DMibTestPath("Handle value access");
					t_CJson Source;
					Source["key"] = "value";

					auto Iter = fg_Move(Source.f_Object()).f_OrderedDestructiveIterator();
					auto Handle = Iter.f_ExtractNode();

					DMibExpect(Handle.f_Name(), ==, CStr("key"));
					DMibExpect(Handle.f_Value().f_String(), ==, CStr("value"));
				}
				// Test transfer preserves complex values
				{
					DMibTestPath("Transfer complex values");
					t_CJson Source;
					Source["obj"]["nested"] = "value";
					Source["arr"].f_Insert(1);
					Source["arr"].f_Insert(2);

					t_CJson Dest;
					Dest = EJsonType_Object;

					for (auto Iter = fg_Move(Source.f_Object()).f_OrderedDestructiveIterator(); Iter; )
					{
						auto Handle = Iter.f_ExtractNode();
						Dest.f_Object().f_Insert(fg_Move(Handle));
					}

					DMibExpectTrue(Source.f_Object().f_IsEmpty());
					DMibExpect(Dest["obj"]["nested"].f_String(), ==, CStr("value"));
					DMibExpect(Dest["arr"].f_Array()[0].f_Integer(), ==, 1);
					DMibExpect(Dest["arr"].f_Array()[1].f_Integer(), ==, 2);
				}
				// Test f_Insert with duplicate key keeps existing value
				{
					DMibTestPath("Insert duplicate key keeps existing");
					t_CJson Source;
					Source["a"] = 100;

					t_CJson Dest;
					Dest["a"] = 1;
					Dest["b"] = 2;

					for (auto Iter = fg_Move(Source.f_Object()).f_OrderedDestructiveIterator(); Iter; )
					{
						auto Handle = Iter.f_ExtractNode();
						Dest.f_Object().f_Insert(fg_Move(Handle));
					}

					DMibExpectTrue(Source.f_Object().f_IsEmpty());
					// Value should NOT be replaced
					DMibExpect(Dest["a"].f_Integer(), ==, 1);
					// Other values should be unchanged
					DMibExpect(Dest["b"].f_Integer(), ==, 2);
				}
				// Test f_InsertOrAssign with duplicate key replaces value
				{
					DMibTestPath("InsertOrAssign duplicate key replaces value");
					t_CJson Source;
					Source["a"] = 100;

					t_CJson Dest;
					Dest["a"] = 1;
					Dest["b"] = 2;

					for (auto Iter = fg_Move(Source.f_Object()).f_OrderedDestructiveIterator(); Iter; )
					{
						auto Handle = Iter.f_ExtractNode();
						Dest.f_Object().f_InsertOrAssign(fg_Move(Handle));
					}

					DMibExpectTrue(Source.f_Object().f_IsEmpty());
					// Value should be replaced
					DMibExpect(Dest["a"].f_Integer(), ==, 100);
					// Other values should be unchanged
					DMibExpect(Dest["b"].f_Integer(), ==, 2);
				}
				// Test sorted f_Insert with duplicate key keeps existing
				if constexpr (t_CJson::mc_bOrdered)
				{
					DMibTestPath("Sorted Insert duplicate key keeps existing");
					t_CJson Source;
					Source["b"] = 200;
					Source["c"] = 300;

					t_CJson Dest;
					Dest["a"] = 1;
					Dest["b"] = 2;
					Dest["c"] = 3;

					for (auto Iter = fg_Move(Source.f_Object()).f_SortedDestructiveIterator(); Iter; )
					{
						auto Handle = Iter.f_ExtractNode();
						Dest.f_Object().f_Insert(fg_Move(Handle));
					}

					DMibExpectTrue(Source.f_Object().f_IsEmpty());
					// All values should be unchanged (f_Insert keeps existing)
					DMibExpect(Dest["a"].f_Integer(), ==, 1);
					DMibExpect(Dest["b"].f_Integer(), ==, 2);
					DMibExpect(Dest["c"].f_Integer(), ==, 3);
				}
				// Test sorted f_InsertOrAssign with duplicate key replaces
				if constexpr (t_CJson::mc_bOrdered)
				{
					DMibTestPath("Sorted InsertOrAssign duplicate key replaces value");
					t_CJson Source;
					Source["b"] = 200;
					Source["c"] = 300;

					t_CJson Dest;
					Dest["a"] = 1;
					Dest["b"] = 2;
					Dest["c"] = 3;

					for (auto Iter = fg_Move(Source.f_Object()).f_SortedDestructiveIterator(); Iter; )
					{
						auto Handle = Iter.f_ExtractNode();
						Dest.f_Object().f_InsertOrAssign(fg_Move(Handle));
					}

					DMibExpectTrue(Source.f_Object().f_IsEmpty());
					// Original value unchanged
					DMibExpect(Dest["a"].f_Integer(), ==, 1);
					// Values should be replaced
					DMibExpect(Dest["b"].f_Integer(), ==, 200);
					DMibExpect(Dest["c"].f_Integer(), ==, 300);
				}
				// Test f_ExtractAll basic usage
				{
					DMibTestPath("ExtractAll basic");
					t_CJson Source;
					Source["a"] = 1;
					Source["b"] = 2;
					Source["c"] = 3;

					t_CJson Dest;
					Dest = EJsonType_Object;

					Source.f_Object().f_ExtractAll
						(
							[&](auto &&_Handle)
							{
								Dest.f_Object().f_Insert(fg_Move(_Handle));
							}
						)
					;

					DMibExpectTrue(Source.f_Object().f_IsEmpty());
					DMibExpect(fsg_IteratorCount(Dest.f_Object().f_OrderedIterator()), ==, 3u);
					DMibExpect(Dest["a"].f_Integer(), ==, 1);
					DMibExpect(Dest["b"].f_Integer(), ==, 2);
					DMibExpect(Dest["c"].f_Integer(), ==, 3);
				}
				// Test f_ExtractAll with empty object
				{
					DMibTestPath("ExtractAll empty");
					t_CJson Source;
					Source = EJsonType_Object;

					aint nCallCount = 0;
					Source.f_Object().f_ExtractAll
						(
							[&](auto &&_Handle)
							{
								++nCallCount;
							}
						)
					;

					DMibExpect(nCallCount, ==, 0);
					DMibExpectTrue(Source.f_Object().f_IsEmpty());
				}
				// Test f_ExtractAll with InsertOrAssign for duplicates
				{
					DMibTestPath("ExtractAll with InsertOrAssign");
					t_CJson Source;
					Source["a"] = 100;
					Source["b"] = 200;

					t_CJson Dest;
					Dest = EJsonType_Object;
					Dest["a"] = 1;
					Dest["c"] = 3;

					Source.f_Object().f_ExtractAll
						(
							[&](auto &&_Handle)
							{
								Dest.f_Object().f_InsertOrAssign(fg_Move(_Handle));
							}
						)
					;

					DMibExpectTrue(Source.f_Object().f_IsEmpty());
					DMibExpect(fsg_IteratorCount(Dest.f_Object().f_OrderedIterator()), ==, 3u);
					// a should be replaced
					DMibExpect(Dest["a"].f_Integer(), ==, 100);
					// b should be added
					DMibExpect(Dest["b"].f_Integer(), ==, 200);
					// c should be unchanged
					DMibExpect(Dest["c"].f_Integer(), ==, 3);
				}
				// Test f_ExtractAll with complex values
				{
					DMibTestPath("ExtractAll complex values");
					t_CJson Source;
					Source["obj"]["nested"] = "value";
					Source["arr"].f_Insert(1);
					Source["arr"].f_Insert(2);
					Source["str"] = "text";

					t_CJson Dest;
					Dest = EJsonType_Object;

					Source.f_Object().f_ExtractAll
						(
							[&](auto &&_Handle)
							{
								Dest.f_Object().f_Insert(fg_Move(_Handle));
							}
						)
					;

					DMibExpectTrue(Source.f_Object().f_IsEmpty());
					DMibExpect(Dest["obj"]["nested"].f_String(), ==, CStr("value"));
					DMibExpect(Dest["arr"].f_Array()[0].f_Integer(), ==, 1);
					DMibExpect(Dest["arr"].f_Array()[1].f_Integer(), ==, 2);
					DMibExpect(Dest["str"].f_String(), ==, CStr("text"));
				}
				// Test f_ExtractAll selective insertion
				{
					DMibTestPath("ExtractAll selective");
					t_CJson Source;
					Source["keep1"] = 1;
					Source["skip2"] = 2;
					Source["keep3"] = 3;
					Source["skip4"] = 4;
					Source["keep5"] = 5;

					t_CJson Dest;
					Dest = EJsonType_Object;

					Source.f_Object().f_ExtractAll
						(
							[&](auto &&_Handle)
							{
								// Only insert entries with odd values
								int64 Value;
								if constexpr (t_CJson::mc_bOrdered)
									Value = _Handle.f_Value().f_Integer();
								else
									Value = _Handle.f_Value().f_Value().f_Integer();

								if (Value % 2 == 1)
									Dest.f_Object().f_Insert(fg_Move(_Handle));
								// Even-valued handles are destroyed when lambda exits
							}
						)
					;

					DMibExpectTrue(Source.f_Object().f_IsEmpty());
					DMibExpect(fsg_IteratorCount(Dest.f_Object().f_OrderedIterator()), ==, 3u);
					DMibExpect(Dest["keep1"].f_Integer(), ==, 1);
					DMibExpect(Dest["keep3"].f_Integer(), ==, 3);
					DMibExpect(Dest["keep5"].f_Integer(), ==, 5);
				}
			};

			DMibTestCategoryFlags("Parse Exceptions", ETestCategoryFlag_DisableExceptionFilter | ETestCategoryFlag_Tests)
			{
				{
					DMibTestPath("Key quoting");
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
				}
				{
					DMibTestPath("End of key missing");
					CStr Data = "{ \"Key";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();

					Error.m_Error = "End of string character \" not found for key name string";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 3;
					Error.m_Location.m_Character = 2;

					fp_TestParseError(Data, Errors);
				}
				{
					DMibTestPath("Newline in string");
					CStr Data = "{ \"Key\n";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();

					Error.m_Error = "Control characters or new lines not allowed in string. Use escaped characters.";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 7;
					Error.m_Location.m_Character = 6;

					fp_TestParseError(Data, Errors);
				}
				{
					DMibTestPath("Key value separator");
					CStr Data = "{ \"Key\" \"Value\" }";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();

					Error.m_Error = "Expected : to follow key name in object";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 9;
					Error.m_Location.m_Character = 8;

					fp_TestParseError(Data, Errors);
				}
				{
					DMibTestPath("Invalid escape value");
					CStr Data = "\"Escaped: \\g\"";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();

					Error.m_Error = "Invalid escape value";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 12;
					Error.m_Location.m_Character = 11;

					fp_TestParseError(Data, Errors);
				}
				{
					DMibTestPath("Too short UTF16");
					CStr Data = "\"Escaped: \\u05";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();

					Error.m_Error = "Too short escaped UTF16 value";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 13;
					Error.m_Location.m_Character = 12;

					fp_TestParseError(Data, Errors);
				}
				{
					DMibTestPath("Invalid UTF16");
					CStr Data = "\"Escaped: \\u05tt\"";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();

					Error.m_Error = "Invalid escaped UTF16 value";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 13;
					Error.m_Location.m_Character = 12;

					fp_TestParseError(Data, Errors);
				}
				{
					DMibTestPath("Null character");
					CStr Data = "\"Null: \\u0000\"";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();

					Error.m_Error = "Null characters not supported in this implementation";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 10;
					Error.m_Location.m_Character = 9;

					fp_TestParseError(Data, Errors);
				}
				{
					DMibTestPath("Missing object close");
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
				}
				{
					DMibTestPath("Missing array close");
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
				}
				{
					DMibTestPath("String without end");
					CStr Data = "\"String without end";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();

					Error.m_Error = "End of string character \" not found for string";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 1;
					Error.m_Location.m_Character = 0;

					fp_TestParseError(Data, Errors);
				}
				{
					DMibTestPath("Invalid literal");
					CStr Data = "55ueeu";

					TCVector<CParseError> Errors;
					auto &Error = Errors.f_Insert();

					Error.m_Error = "Invalid literal starting with: 55ue";
					Error.m_Location.m_File = mp_TestFilePath;
					Error.m_Location.m_Line = 1;
					Error.m_Location.m_Column = 1;
					Error.m_Location.m_Character = 0;

					fp_TestParseError(Data, Errors);
				}
				{
					DMibTestPath("Unexpected character after root value");
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
				}
			};
		}

	private:
		void fp_TestParseError(NMib::NStr::CStr const &_ToParse, NMib::NContainer::TCVector<NMib::NStr::CParseError> const &_ExpectedErrors)
		{
			NMib::NStr::CExceptionParse Exception = DMibImpExceptionInstanceSpecific(NMib::NStr::CExceptionParse, "Json Error", NMib::fg_Default());
			try
			{
				fg_TestAddCleanupPath(mp_TestFilePath);

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
		t_CJson mp_JsonReference;
		NMib::NStr::CStr mp_JsonReferenceText;
		NMib::NFunction::TCFunction<t_CJson (NMib::NStr::CStr const &_ToParse, NMib::NStr::CStr const &_FileName)> mp_fParse;
	};
}
