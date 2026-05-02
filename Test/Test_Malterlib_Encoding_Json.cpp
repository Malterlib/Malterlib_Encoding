// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Encoding/Json>
#include <Mib/Encoding/JsonShortcuts>
#include <Mib/CommandLine/AnsiEncodingParse>
#include <Mib/Test/Exception>
#include <Mib/Stream/ByteVector>
#include "Test_Malterlib_Encoding_JsonShared.h"

namespace
{
	using namespace NMib;
	using namespace NMib::NEncoding;

	struct CJsonTrailingCommaOnlyParseContext : public CJsonStrictParseContext
	{
		static constexpr bool mc_bAllowTrailingCommas = true;
	};

	struct CJsonCommentsOnlyParseContext : public CJsonStrictParseContext
	{
		static constexpr bool mc_bAllowComments = true;
		static inline constexpr ch8 mc_ConstantEndCharacters[] = ",}]/";
	};

	struct CJsonExtendedWhitespaceOnlyParseContext : public CJsonStrictParseContext
	{
		static constexpr bool mc_bAllowExtendedWhitespace = true;
	};

	struct CJsonExtendedEscapesOnlyParseContext : public CJsonStrictParseContext
	{
		static constexpr bool mc_bAllowExtendedEscapes = true;
	};

	struct CJson5NoTrailingCommaParseContext : public CJson5ParseContext
	{
		static constexpr bool mc_bAllowTrailingCommas = false;
	};

	struct CJson5ConvertNullToSpace : public CJson5ParseContext
	{
		static constexpr bool mc_bConvertNullToSpace = true;
	};

	class CJson_Tests : public NTest::CTest
	{
	public:
		static NStr::CExceptionParse fs_MakeParseException(NStr::CStr const &_Error, uint32 _Line, uint32 _Column, uint32 _Character)
		{
			NContainer::TCVector<NStr::CParseError> Errors;
			auto &Error = Errors.f_Insert();
			Error.m_Error = _Error;
			Error.m_Location.m_Line = _Line;
			Error.m_Location.m_Column = _Column;
			Error.m_Location.m_Character = _Character;

			return DMibExceptionInstanceParse(NStr::CParseError::fs_ToString(Errors), Errors);
		}

		template <typename t_CParseContext>
		static void fs_ExpectParseError(NStr::CStr const &_Case, NStr::CStr const &_Text, NStr::CStr const &_Error, uint32 _Line, uint32 _Column, uint32 _Character)
		{
			DMibTestPath(_Case);
			DMibExpectException(CJsonOrdered::fs_FromString<t_CParseContext>(_Text), fs_MakeParseException(_Error, _Line, _Column, _Character));
		}

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

		static void fs_ExpectTrailingRootTriviaPreserved(NStr::CStr const &_Case, NStr::CStr const &_Trailing)
		{
			DMibTestPath(_Case);

			NStr::CStr Text =
				"{\n"
				"	a: 1\n"
				"}"
			;
			Text += _Trailing;

			auto Json = CJsonOrderedWithComments::fs_FromStringJson5(Text);
			DMibExpect(Json.f_Trivia().f_Trailing(), ==, _Trailing);
			DMibExpect(Json.f_ToStringJson5(), ==, Text);
			DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(Json.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_AllFeatures)), ==, Text);

			Json["b"] = 2;
			NStr::CStr Expected =
				"{\n"
				"	a: 1,\n"
				"	\"b\": 2\n"
				"}"
			;
			Expected += _Trailing;

			DMibExpect(Json.f_ToStringJson5(), ==, Expected);
			DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(Json.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_AllFeatures)), ==, Expected);
		}

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
			DMibTestSuite("JSONC")
			{
				NStr::CStr Text =
					"// file\n"
					"{\n"
					"\t\"a\": 1, // keep\n"
					"\t\"b\": [true, false]\n"
					"}\n"
					"// eof\n"
				;
				auto Json = CJsonOrderedWithComments::fs_FromStringJsonC(Text);
				DMibExpect(Json["a"].f_Integer(), ==, 1);
				auto iArray = Json["b"].f_Array().f_GetIterator();
				DMibExpectTrue((*iArray).f_Boolean());
				++iArray;
				DMibExpectFalse((*iArray).f_Boolean());
				DMibExpect(Json.f_ToStringJsonC(), ==, Text);
				auto ColoredText = Json.f_ToStringColoredJsonC(NCommandLine::EAnsiEncodingFlag_AllFeatures);
				DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(ColoredText), ==, Text);

				auto NonRecording = CJsonOrdered::fs_FromStringJsonC(Text);
				DMibExpect(NonRecording["a"].f_Integer(), ==, 1);
				DMibExpect(NonRecording.f_ToStringJsonC().f_Find("keep"), <, 0);

				auto TrailingComma = CJsonOrderedWithComments::fs_FromStringJsonC("{\"a\":[1,]}");
				DMibExpect(TrailingComma["a"].f_Array().f_GetLen(), ==, 1);
				DMibExpect(TrailingComma.f_ToStringJsonC(), ==, "{\"a\":[1,]}");
				DMibExpectException(CJsonOrdered::fs_FromStringJsonC("{a:1}"), fs_MakeParseException("Expected \" to start object key name", 1, 2, 1));
				DMibExpectException(CJsonOrdered::fs_FromStringJsonC("{\"a\":'x'}"), fs_MakeParseException("Invalid literal starting with: 'x'}", 1, 6, 5));
				DMibExpectException(CJsonOrdered::fs_FromStringJsonC("{}" "\xE2" "\x80" "\xA8"), fs_MakeParseException("Unexpected character after root value", 1, 3, 2));
			};
			DMibTestSuite("JSON5")
			{
				NStr::CStr Text =
					"{\n"
					"	// accepted and discarded\n"
					"	/* block accepted */\n"
					"	unquoted: 'single',\n"
					"	$schema: \"draft\",\n"
					"	_private: 'hidden',\n"
					"	key123: 123,\n"
					"	singleEscapedQuote: 'it\\'s',\n"
					"	doubleEscapedSingle: \"\\'\",\n"
					"	doubleQuoteInSingle: '\\\"',\n"
					"	hex: 0xFF,\n"
					"	upperHex: 0X1A,\n"
					"	negativeHex: -0x10,\n"
					"	maxHex: 0x7FFFFFFFFFFFFFFF,\n"
					"	minHex: -0x8000000000000000,\n"
					"	leading: .5,\n"
					"	negativeLeading: -.25,\n"
					"	trailingFloat: 1.,\n"
					"	exponentAfterTrailing: 1.e2,\n"
					"	overflowFloat: 1e10000,\n"
					"	signed: +1,\n"
					"	signedFloat: +1.25,\n"
					"	inf: Infinity,\n"
					"	posInf: +Infinity,\n"
					"	negInf: -Infinity,\n"
					"	nan: NaN,\n"
					"	posNan: +NaN,\n"
					"	negNan: -NaN,\n"
					"	escaped: '\\v\\x42\\a\\B',\n"
					"	lineContinuationLf: 'line\\\n"
					"continued',\n"
					"	lineContinuationCrLf: 'line\\\r\n"
					"continued',\n"
					"	lineContinuationLs: 'line\\" "\xE2" "\x80" "\xA8" "continued',\n"
					"	trailingArray: [1, 2,],\n"
					"	trailingObject: { nested: true, },\n"
					"}\n"
				;

				auto Json = CJsonOrdered::fs_FromStringJson5(Text);
				DMibExpect(Json["unquoted"].f_String(), ==, "single");
				DMibExpect(Json["$schema"].f_String(), ==, "draft");
				DMibExpect(Json["_private"].f_String(), ==, "hidden");
				DMibExpect(Json["key123"].f_Integer(), ==, 123);
				DMibExpect(Json["singleEscapedQuote"].f_String(), ==, "it's");
				DMibExpect(Json["doubleEscapedSingle"].f_String(), ==, "'");
				DMibExpect(Json["doubleQuoteInSingle"].f_String(), ==, "\"");
				DMibExpect(Json["hex"].f_Integer(), ==, 255);
				DMibExpect(Json["upperHex"].f_Integer(), ==, 26);
				DMibExpect(Json["negativeHex"].f_Integer(), ==, -16);
				DMibExpect(Json["maxHex"].f_Integer(), ==, TCLimitsInt<int64>::mc_Max);
				DMibExpect(Json["minHex"].f_Integer(), ==, TCLimitsInt<int64>::mc_Min);
				DMibExpect(Json["leading"].f_Float(), ==, 0.5);
				DMibExpect(Json["negativeLeading"].f_Float(), ==, -0.25);
				DMibExpect(Json["trailingFloat"].f_Float(), ==, 1.0);
				DMibExpect(Json["exponentAfterTrailing"].f_Float(), ==, 100.0);
				DMibExpectTrue(Json["overflowFloat"].f_Float().f_IsInfinity());
				DMibExpect(Json["overflowFloat"].f_Float().f_GetSign(), >, 0);
				DMibExpect(Json["signed"].f_Integer(), ==, 1);
				DMibExpect(Json["signedFloat"].f_Float(), ==, 1.25);
				DMibExpectTrue(Json["inf"].f_Float().f_IsInfinity());
				DMibExpect(Json["inf"].f_Float().f_GetSign(), >, 0);
				DMibExpectTrue(Json["posInf"].f_Float().f_IsInfinity());
				DMibExpect(Json["posInf"].f_Float().f_GetSign(), >, 0);
				DMibExpectTrue(Json["negInf"].f_Float().f_IsInfinity());
				DMibExpect(Json["negInf"].f_Float().f_GetSign(), <, 0);
				DMibExpectTrue(Json["nan"].f_Float().f_IsNan());
				DMibExpectTrue(Json["posNan"].f_Float().f_IsNan());
				DMibExpectTrue(Json["negNan"].f_Float().f_IsNan());
				DMibExpect(Json["negNan"].f_Float().f_GetSign(), <, 0);
				DMibExpect(Json["escaped"].f_String(), ==, NStr::CStr("\vBaB"));
				DMibExpect(Json["lineContinuationLf"].f_String(), ==, "linecontinued");
				DMibExpect(Json["lineContinuationCrLf"].f_String(), ==, "linecontinued");
				DMibExpect(Json["lineContinuationLs"].f_String(), ==, "linecontinued");
				DMibExpect(Json["trailingArray"].f_Array().f_GetLen(), ==, 2);
				DMibExpectTrue(Json["trailingObject"]["nested"].f_Boolean());

				auto RoundTrip = Json.f_ToStringJson5();
				DMibExpect(RoundTrip.f_Find("accepted and discarded"), <, 0);
				DMibExpect(RoundTrip.f_Find("unquoted"), >=, 0);
				DMibExpect(RoundTrip.f_Find("$schema"), >=, 0);
				DMibExpect(RoundTrip.f_Find("'single'"), >=, 0);
				DMibExpect(RoundTrip.f_Find("Infinity"), >=, 0);
				DMibExpect(RoundTrip.f_Find("NaN"), >=, 0);
				DMibExpect(RoundTrip.f_Find("-NaN"), >=, 0);
				DMibExpect(CJsonOrdered::fs_FromStringJson5(RoundTrip)["hex"].f_Integer(), ==, 255);
				DMibExpect(Json.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_None), ==, RoundTrip);
				auto ColoredRoundTrip = Json.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_Color);
				DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(ColoredRoundTrip), ==, RoundTrip);
				DMibExpect(fs_CountForegroundColorChanges(ColoredRoundTrip), >, 0);

				NStr::CStr UnquotedKeyText =
					"{\n"
					"	key: 1\n"
					"}\n"
				;
				auto UnquotedKeyJson = CJsonOrdered::fs_FromStringJson5(UnquotedKeyText);
				DMibExpect(UnquotedKeyJson["key"].f_Integer(), ==, 1);
				DMibExpect(UnquotedKeyJson.f_ToStringJson5(), ==, UnquotedKeyText);
				auto UnquotedKeyColored = UnquotedKeyJson.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_AllFeatures);
				DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(UnquotedKeyColored), ==, UnquotedKeyText);
				DMibExpect(fs_CountForegroundColorChanges(UnquotedKeyColored, 0xff, 0xa6, 0x00), ==, 1);

				NStr::CStr DoubleQuotedKeyText =
					"{\n"
					"	\"key\": 1\n"
					"}\n"
				;
				auto DoubleQuotedKeyJson = CJsonOrdered::fs_FromStringJson5(DoubleQuotedKeyText);
				DMibExpect(DoubleQuotedKeyJson["key"].f_Integer(), ==, 1);
				DMibExpect(DoubleQuotedKeyJson.f_ToStringJson5(), ==, DoubleQuotedKeyText);
				auto DoubleQuotedKeyColored = DoubleQuotedKeyJson.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_AllFeatures);
				DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(DoubleQuotedKeyColored), ==, DoubleQuotedKeyText);
				DMibExpect(fs_CountForegroundColorChanges(DoubleQuotedKeyColored, 0xff, 0xa6, 0x00), ==, 1);

				NStr::CStr SingleQuotedKeyText =
					"{\n"
					"	'key': 1\n"
					"}\n"
				;
				auto SingleQuotedKeyJson = CJsonOrdered::fs_FromStringJson5(SingleQuotedKeyText);
				DMibExpect(SingleQuotedKeyJson["key"].f_Integer(), ==, 1);
				DMibExpect(SingleQuotedKeyJson.f_ToStringJson5(), ==, SingleQuotedKeyText);
				auto SingleQuotedKeyColored = SingleQuotedKeyJson.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_AllFeatures);
				DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(SingleQuotedKeyColored), ==, SingleQuotedKeyText);
				DMibExpect(fs_CountForegroundColorChanges(SingleQuotedKeyColored, 0xff, 0xa6, 0x00), ==, 1);

				NStr::CStr WhiteSpaceText =
					"{"
					"\x0B" "\"vertical\"" "\x0C" ":" "\xC2" "\xA0" "1,"
					"\xE2" "\x80" "\xA8" "\"ls\":2,"
					"\xE2" "\x80" "\xA9" "\"ps\":3,"
					"\xEF" "\xBB" "\xBF" "\"bom\":4"
					"}"
				;
				auto WhiteSpaceJson = CJsonOrdered::fs_FromStringJson5(WhiteSpaceText);
				DMibExpect(WhiteSpaceJson["vertical"].f_Integer(), ==, 1);
				DMibExpect(WhiteSpaceJson["ls"].f_Integer(), ==, 2);
				DMibExpect(WhiteSpaceJson["ps"].f_Integer(), ==, 3);
				DMibExpect(WhiteSpaceJson["bom"].f_Integer(), ==, 4);
				auto LineSeparatorCommentJson = CJsonOrdered::fs_FromStringJson5("// comment" "\xE2" "\x80" "\xA8" "{ value: 5 }");
				DMibExpect(LineSeparatorCommentJson["value"].f_Integer(), ==, 5);

				auto NullJson = CJsonOrdered::fs_FromString<CJson5ConvertNullToSpace>("{ nul: '\\0', hexNul: '\\x00' }");
				DMibExpect(NullJson["nul"].f_String(), ==, " ");
				DMibExpect(NullJson["hexNul"].f_String(), ==, " ");
				fs_ExpectParseError<CJson5ParseContext>
					(
						"Json5NullEscape"
						, "{ nul: '\\0' }"
						, "Null characters not supported in this implementation"
						, 1
						, 10
						, 9
					)
				;

				auto AccentJson = CJsonOrdered::fs_FromStringJson5("{ accent: '\\xE9' }");
				DMibExpect(AccentJson["accent"].f_String(), ==, NStr::CStr("\xC3" "\xA9"));

				CJsonOrdered Generated(EJsonType_Object);
				Generated["lineSeparators"] = NStr::CStr("a" "\xE2" "\x80" "\xA8" "b" "\xE2" "\x80" "\xA9" "c");
				auto GeneratedText = Generated.f_ToStringJson5();
				DMibExpect(GeneratedText.f_Find("\\u2028"), >=, 0);
				DMibExpect(GeneratedText.f_Find("\\u2029"), >=, 0);
				DMibExpect(CJsonOrdered::fs_FromStringJson5(GeneratedText)["lineSeparators"].f_String(), ==, Generated["lineSeparators"].f_String());
				DMibExpect(CJsonOrdered::fs_FromStringJson5("{nan: -NaN}").f_ToStringJson5(nullptr), ==, "{nan:-NaN}");

				fs_ExpectParseError<NJson::CParseContext>
					(
						"DefaultComment"
						, "// comment\n"
						"{}"
						, "Invalid literal starting with: // c"
						, 1
						, 1
						, 0
					)
				;
				DMibExpectNoException(CJsonOrdered::fs_FromString("[1,]"));
				fs_ExpectParseError<CJsonStrictParseContext>("StrictArrayTrailingComma", "[1,]", "Trailing comma not allowed", 1, 4, 3);
			};
			DMibTestSuite("JSON5 Rejections")
			{
				fs_ExpectParseError<CJsonStrictParseContext>
					(
						"StrictComment"
						, "// comment\n"
						"{}"
						, "Invalid literal starting with: // c"
						, 1
						, 1
						, 0
					)
				;
				fs_ExpectParseError<CJsonStrictParseContext>("StrictUnquotedKey", "{a:1}", "Expected \" to start object key name", 1, 2, 1);
				fs_ExpectParseError<CJsonStrictParseContext>("StrictSingleQuote", "{\"a\":'x'}", "Invalid literal starting with: 'x'}", 1, 6, 5);
				fs_ExpectParseError<CJsonStrictParseContext>("StrictHex", "{\"a\":0x10}", "Hex literals not allowed in strict JSON", 1, 6, 5);
				fs_ExpectParseError<CJsonStrictParseContext>("StrictLeadingDecimal", "{\"a\":.5}", "Leading '.' not allowed in strict JSON", 1, 6, 5);
				fs_ExpectParseError<CJsonStrictParseContext>("StrictPlus", "{\"a\":+1}", "Leading '+' not allowed in strict JSON", 1, 6, 5);
				fs_ExpectParseError<CJsonStrictParseContext>("StrictInfinity", "{\"a\":Infinity}", "Invalid literal starting with: Infi", 1, 6, 5);
				fs_ExpectParseError<CJsonStrictParseContext>("StrictTrailingDecimal", "{\"a\":1.}", "Decimal point must be followed by a digit", 1, 6, 5);
				fs_ExpectParseError<CJsonStrictParseContext>("StrictLeadingZero", "{\"a\":01}", "Leading zeros not allowed", 1, 6, 5);
				fs_ExpectParseError<CJsonStrictParseContext>("StrictBinary", "{\"a\":0b10}", "Binary/octal literals not allowed", 1, 6, 5);
				fs_ExpectParseError<CJsonStrictParseContext>("StrictVerticalEscape", "{\"a\":\"\\v\"}", "Invalid escape value", 1, 8, 7);
				fs_ExpectParseError<CJsonStrictParseContext>("StrictNonEscape", "{\"a\":\"\\a\"}", "Invalid escape value", 1, 8, 7);

				fs_ExpectParseError<CJson5ParseContext>("Json5LeadingZero", "{a: 01}", "Leading zeros not allowed", 1, 5, 4);
				fs_ExpectParseError<CJson5ParseContext>("Json5Binary", "{a: 0b10}", "Binary/octal literals not allowed", 1, 5, 4);
				fs_ExpectParseError<CJson5ParseContext>("Json5Octal", "{a: 0o10}", "Binary/octal literals not allowed", 1, 5, 4);
				fs_ExpectParseError<CJson5ParseContext>("Json5EmptyHex", "{a: 0x}", "Hex literal must contain at least one digit", 1, 5, 4);
				fs_ExpectParseError<CJson5ParseContext>("Json5HexOverflow", "{a: 0x8000000000000000}", "Number out of range", 1, 5, 4);
				fs_ExpectParseError<CJson5ParseContext>("Json5HexOverflow2", "{a: 0xFFFFFFFFFFFFFFFF}", "Number out of range", 1, 5, 4);
				fs_ExpectParseError<CJson5ParseContext>("Json5HexOverflow3", "{a: 0xFFFFFFFFFFFFFFFFF}", "Number out of range", 1, 5, 4);
				fs_ExpectParseError<CJson5ParseContext>("Json5NegativeHexOverflow", "{a: -0x8000000000000001}", "Number out of range", 1, 5, 4);
				fs_ExpectParseError<CJsonStrictParseContext>("StrictDecimalOverflow", "{\"a\":9223372036854775808}", "Number out of range", 1, 6, 5);
				fs_ExpectParseError<CJsonStrictParseContext>("StrictNegativeDecimalOverflow", "{\"a\":-9223372036854775809}", "Number out of range", 1, 6, 5);
				DMibExpect(CJsonOrdered::fs_FromString("{\"a\":9223372036854775807}")["a"].f_Integer(), ==, TCLimitsInt<int64>::mc_Max);
				DMibExpect(CJsonOrdered::fs_FromString("{\"a\":-9223372036854775808}")["a"].f_Integer(), ==, TCLimitsInt<int64>::mc_Min);
				fs_ExpectParseError<CJson5ParseContext>("Json5EmptyLeadingDecimal", "{a: .e1}", "'.' must be followed by a digit", 1, 5, 4);
				fs_ExpectParseError<CJson5ParseContext>("Json5EmptyExponent", "{a: 1e}", "Exponent must be followed by a digit", 1, 5, 4);
				fs_ExpectParseError<CJson5ParseContext>("Json5BadExponentSign", "{a: 1e+-2}", "Exponent must be followed by a digit", 1, 5, 4);
				fs_ExpectParseError<CJson5ParseContext>("Json5EscapeEOF", "{a:'abc\\", "Invalid escape value", 1, 9, 8);
				fs_ExpectParseError<CJson5ParseContext>("Json5TruncatedWhitespace", "{}" "\xE2", "Unexpected character after root value", 1, 3, 2);
				fs_ExpectParseError<CJson5ParseContext>("Json5LineSeparatorLocation", "{}" "\xE2" "\x80" "\xA8" "x", "Unexpected character after root value", 2, 1, 5);
				fs_ExpectParseError<CJson5ParseContext>("Json5ParagraphSeparatorLocation", "{}" "\xE2" "\x80" "\xA9" "x", "Unexpected character after root value", 2, 1, 5);
				fs_ExpectParseError<CJson5ParseContext>("Json5InfinitySuffix", "{a: +Infinityx}", "Invalid literal starting with: +Inf", 1, 5, 4);
				fs_ExpectParseError<NJson::CParseContext>("DefaultOverflowFloat", "{\"a\":1e10000}", "Invalid float value", 1, 6, 5);
				auto InvalidFloat = CJsonOrdered::fs_FromString("{\"a\":1e10000}", {}, EJsonDialectFlag_AllowInvalidFloat);
				DMibExpectTrue(InvalidFloat["a"].f_Float().f_IsInfinity());
				fs_ExpectParseError<CJson5ParseContext>
					(
						"Json5RawLf"
						, "['raw\n"
						"line']"
						, "Raw line terminators are not allowed in strings. Use escaped line continuation."
						, 1
						, 6
						, 5
					)
				;
				fs_ExpectParseError<CJson5ParseContext>("Json5RawLs", "['raw" "\xE2" "\x80" "\xA8" "line']", "Raw line terminators are not allowed in strings. Use escaped line continuation.", 1, 6, 5);

				DMibExpectNoException(CJsonOrdered::fs_FromString<CJsonTrailingCommaOnlyParseContext>("{\"a\":[1,]}"));
				fs_ExpectParseError<CJsonTrailingCommaOnlyParseContext>("TrailingOnlyUnquotedKey", "{a:1}", "Expected \" to start object key name", 1, 2, 1);
				fs_ExpectParseError<CJsonTrailingCommaOnlyParseContext>("TrailingOnlyPlus", "{\"a\":+1}", "Leading '+' not allowed in strict JSON", 1, 6, 5);
				DMibExpectNoException(CJsonOrdered::fs_FromString<CJsonCommentsOnlyParseContext>("{\"a\": true/*comment*/}"));
				fs_ExpectParseError<CJsonCommentsOnlyParseContext>("CommentsOnlyJson5Whitespace", "{}" "\xE2" "\x80" "\xA8", "Unexpected character after root value", 1, 3, 2);
				fs_ExpectParseError<CJsonCommentsOnlyParseContext>("CommentsOnlyTrailingComma", "{\"a\":[1,]}", "Trailing comma not allowed", 1, 9, 8);
				auto ExtendedWhitespaceOnlyJson = CJsonOrdered::fs_FromString<CJsonExtendedWhitespaceOnlyParseContext>("{\"a\":1" "\xE2" "\x80" "\xA8" "}");
				DMibExpect(ExtendedWhitespaceOnlyJson["a"].f_Integer(), ==, 1);
				fs_ExpectParseError<CJsonExtendedWhitespaceOnlyParseContext>("ExtendedWhitespaceOnlyComment", "// comment\n{}", "Invalid literal starting with: // c", 1, 1, 0);
				auto ExtendedEscapesOnlyJson = CJsonOrdered::fs_FromString<CJsonExtendedEscapesOnlyParseContext>("{\"a\":\"before" "\xE2" "\x80" "\xA8" "after\"}");
				DMibExpect(ExtendedEscapesOnlyJson["a"].f_String(), ==, "before" "\xE2" "\x80" "\xA8" "after");
			};
			DMibTestSuite("Comments")
			{
				fs_ExpectTrailingRootTriviaPreserved("RootTrailingNone", "");
				fs_ExpectTrailingRootTriviaPreserved("RootTrailingNewline", "\n");
				fs_ExpectTrailingRootTriviaPreserved("RootTrailingDoubleNewline", "\n\n");
				fs_ExpectTrailingRootTriviaPreserved("RootTrailingTripleNewline", "\n\n\n");
				fs_ExpectTrailingRootTriviaPreserved("RootTrailingLineCommentEOF", "// eof");
				fs_ExpectTrailingRootTriviaPreserved("RootTrailingSpacedLineCommentEOF", " // eof");

				NStr::CStr Text =
					"// file\n"
					"{\n"
					"	// describes a\n"
					"	a /*key*/: 1, // inline-a\n"
					"	// describes b\n"
					"	b: [\n"
					"		1,\n"
					"		// inner\n"
					"		2,\n"
					"	],\n"
					"	emptyObject: { /* keep */ },\n"
					"	emptyArray: [// keep\n"
					"	],\n"
					"	/* multi\n"
					"	   block */\n"
					"	c: 3,\n"
					"	 emptyArray2 :  [    ] , \n"
					"/*a*/ emptyArray3 /*b*/ : /*C*/ [ /*c*/ ] /*d*/ ,  /*e*/ \n"
					"}\n"
					"// eof\n"
				;

				auto Json = CJsonOrderedWithComments::fs_FromStringJson5(Text);
				DMibExpect(Json.f_ToStringJson5(), ==, Text);
				auto ColoredText = Json.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_AllFeatures);
				DMibExpect(NCommandLine::CAnsiEncodingParse::fs_StripEncoding(ColoredText), ==, Text);
				DMibExpect(fs_CountForegroundColorChanges(ColoredText, 0x89, 0x89, 0x89), ==, 16);
				DMibExpect(Json.f_Trivia().f_Leading(), ==, "// file\n");
				DMibExpect(Json.f_Trivia().f_Trailing(), ==, "\n// eof\n");

				auto iMember = Json.f_Object().f_OrderedIterator();
				{
					DMibTestPath("MemberA");
					DMibExpect(iMember->f_Name(), ==, "a");
					DMibExpect(iMember->f_KeyTrivia().f_Leading(), ==, "\n\t// describes a\n\t");
					DMibExpect(iMember->f_KeyTrivia().f_Trailing(), ==, " /*key*/");
					DMibExpect(iMember->f_Value().f_Trivia().f_Leading(), ==, " ");
					DMibExpect(iMember->f_Value().f_Trivia().f_Trailing(), ==, ", // inline-a\n\t// describes b");
					DMibExpect(iMember->f_Value().f_Trivia().f_HasTrailingComma(), ==, true);
				}
				++iMember;
				{
					DMibTestPath("MemberB");
					DMibExpect(iMember->f_Name(), ==, "b");
					DMibExpect(iMember->f_KeyTrivia().f_Leading(), ==, "\n\t");
					DMibExpect(iMember->f_KeyTrivia().f_Trailing(), ==, "");
					DMibExpect(iMember->f_Value().f_Trivia().f_Leading(), ==, " ");
					DMibExpect(iMember->f_Value().f_Trivia().f_Trailing(), ==, ",");
					DMibExpect(iMember->f_Value().f_Trivia().f_HasTrailingComma(), ==, true);
					auto iArray = iMember->f_Value().f_Array().f_GetIterator();
					{
						DMibTestPath("Array0");
						DMibExpect((*iArray).f_Trivia().f_Leading(), ==, "\n\t\t");
						DMibExpect((*iArray).f_Trivia().f_Trailing(), ==, ",\n\t\t// inner");
						DMibExpect((*iArray).f_Trivia().f_HasTrailingComma(), ==, true);
					}
					++iArray;
					{
						DMibTestPath("Array1");
						DMibExpect((*iArray).f_Trivia().f_Leading(), ==, "\n\t\t");
						DMibExpect((*iArray).f_Trivia().f_Trailing(), ==, ",\n\t");
					}
				}
				++iMember;
				{
					DMibTestPath("EmptyObject");
					DMibExpect(iMember->f_Name(), ==, "emptyObject");
					DMibExpect(iMember->f_KeyTrivia().f_Leading(), ==, "\n\t");
					DMibExpect(iMember->f_KeyTrivia().f_Trailing(), ==, "");
					DMibExpect(iMember->f_Value().f_Trivia().f_Leading(), ==, " ");
					DMibExpect(iMember->f_Value().f_Trivia().f_Interior(), ==, " /* keep */ ");
					DMibExpect(iMember->f_Value().f_Trivia().f_Trailing(), ==, ",");
					DMibExpect(iMember->f_Value().f_Trivia().f_HasTrailingComma(), ==, true);
				}
				++iMember;
				{
					DMibTestPath("EmptyArray");
					DMibExpect(iMember->f_Name(), ==, "emptyArray");
					DMibExpect(iMember->f_KeyTrivia().f_Leading(), ==, "\n\t");
					DMibExpect(iMember->f_KeyTrivia().f_Trailing(), ==, "");
					DMibExpect(iMember->f_Value().f_Trivia().f_Leading(), ==, " ");
					DMibExpect(iMember->f_Value().f_Trivia().f_Interior(), ==, "// keep\n\t");
					DMibExpect(iMember->f_Value().f_Trivia().f_Trailing(), ==, ",\n\t/* multi\n\t   block */");
				}
				++iMember;
				{
					DMibTestPath("MemberC");
					DMibExpect(iMember->f_Name(), ==, "c");
					DMibExpect(iMember->f_KeyTrivia().f_Leading(), ==, "\n\t");
					DMibExpect(iMember->f_KeyTrivia().f_Trailing(), ==, "");
					DMibExpect(iMember->f_Value().f_Trivia().f_Leading(), ==, " ");
					DMibExpect(iMember->f_Value().f_Trivia().f_Trailing(), ==, ",");
					DMibExpect(iMember->f_Value().f_Trivia().f_HasTrailingComma(), ==, true);
				}
				++iMember;
				{
					DMibTestPath("EmptyArray2");
					DMibExpect(iMember->f_Name(), ==, "emptyArray2");
					DMibExpect(iMember->f_KeyTrivia().f_Leading(), ==, "\n\t ");
					DMibExpect(iMember->f_KeyTrivia().f_Trailing(), ==, " ");
					DMibExpect(iMember->f_Value().f_Trivia().f_Leading(), ==, "  ");
					DMibExpect(iMember->f_Value().f_Trivia().f_Interior(), ==, "    ");
					DMibExpect(iMember->f_Value().f_Trivia().f_Trailing(), ==, " , ");
					DMibExpect(iMember->f_Value().f_Trivia().f_HasTrailingComma(), ==, true);
				}
				++iMember;
				{
					DMibTestPath("EmptyArray3");
					DMibExpect(iMember->f_Name(), ==, "emptyArray3");
					DMibExpect(iMember->f_KeyTrivia().f_Leading(), ==, "\n/*a*/ ");
					DMibExpect(iMember->f_KeyTrivia().f_Trailing(), ==, " /*b*/ ");
					DMibExpect(iMember->f_Value().f_Trivia().f_Leading(), ==, " /*C*/ ");
					DMibExpect(iMember->f_Value().f_Trivia().f_Interior(), ==, " /*c*/ ");
					DMibExpect(iMember->f_Value().f_Trivia().f_Trailing(), ==, " /*d*/ ,  /*e*/ \n");
				}

				NStr::CStr BlockPromotionText =
					"{\n"
					"	a: 1,\n"
					"	/* about b */\n"
					"	b: 2\n"
					"}\n"
				;
				auto BlockPromotion = CJsonOrderedWithComments::fs_FromStringJson5(BlockPromotionText);
				DMibExpect(BlockPromotion.f_ToStringJson5(), ==, BlockPromotionText);
				auto iBlockPromotion = BlockPromotion.f_Object().f_OrderedIterator();
				DMibExpect(iBlockPromotion->f_Value().f_Trivia().f_Trailing(), ==, ",\n\t/* about b */");
				DMibExpect(iBlockPromotion->f_Value().f_Trivia().f_HasTrailingComma(), ==, true);
				++iBlockPromotion;
				DMibExpect(iBlockPromotion->f_KeyTrivia().f_Leading(), ==, "\n\t");

				NStr::CStr PreCommaText =
					"{\n"
					"	a: 1\n"
					"	// before comma\n"
					"	, b: 2\n"
					"}\n"
				;
				auto PreComma = CJsonOrderedWithComments::fs_FromStringJson5(PreCommaText);
				DMibExpect(PreComma.f_ToStringJson5(), ==, PreCommaText);
				auto iPreComma = PreComma.f_Object().f_OrderedIterator();
				DMibExpect(iPreComma->f_Value().f_Trivia().f_Trailing(), ==, "\n\t// before comma");
				DMibExpect(iPreComma->f_Value().f_Trivia().f_HasTrailingComma(), ==, false);
				++iPreComma;
				DMibExpect(iPreComma->f_KeyTrivia().f_Leading(), ==, "\n\t, ");
				DMibExpect(iPreComma->f_KeyTrivia().f_HasLeadingComma(), ==, true);

				NStr::CStr TrailingCommaText =
					"{\n"
					"	a: 1, // trailing comma\n"
					"}\n"
				;
				auto TrailingComma = CJsonOrderedWithComments::fs_FromStringJson5(TrailingCommaText);
				DMibExpect(TrailingComma.f_ToStringJson5(), ==, TrailingCommaText);
				DMibExpect(TrailingComma.f_Object().f_OrderedIterator()->f_Value().f_Trivia().f_Trailing(), ==, ", // trailing comma\n");

				auto Removed = Json;
				Removed.f_RemoveMember("b");
				auto RemovedText = Removed.f_ToStringJson5();
				DMibExpect(RemovedText.f_Find("describes b"), >=, 0);
				DMibExpect(RemovedText.f_Find("inline-a"), >=, 0);

				auto MutatedLast = CJsonOrderedWithComments::fs_FromStringJson5
					(
						"{\n"
						"	a: 1,\n"
						"	b: 2\n"
						"}\n"
					)
				;
				MutatedLast.f_RemoveMember("b");
				auto MutatedLastText = MutatedLast.f_ToString<CJson5NoTrailingCommaParseContext>();
				DMibExpect(MutatedLastText.f_Find("1,"), <, 0);
				DMibExpectNoException(CJsonOrdered::fs_FromString<CJson5NoTrailingCommaParseContext>(MutatedLastText));

				auto MutatedNonLast = CJsonOrderedWithComments::fs_FromStringJson5
					(
						"{\n"
						"	a: 1 // eof\n"
						"}\n"
					)
				;
				MutatedNonLast["b"] = 2;
				DMibExpectNoException(CJsonOrdered::fs_FromStringJson5(MutatedNonLast.f_ToStringJson5()));

				NStr::CStr AddObjectEntryText =
					"{\n"
					"/*a*/ existing /*b*/ : /*C*/ [ /*c*/ ] /*d*/ ,  /*e*/ \n"
					"}\n"
				;
				auto AddedObjectEntry = CJsonOrderedWithComments::fs_FromStringJson5(AddObjectEntryText);
				AddedObjectEntry["newObjectEntry"] = 4;
				DMibExpect
					(
						AddedObjectEntry.f_ToStringJson5()
						, ==
						, "{\n"
						"/*a*/ existing /*b*/ : /*C*/ [ /*c*/ ] /*d*/ ,  /*e*/ \n"
						"	\"newObjectEntry\": 4\n"
						"}\n"
					)
				;

				NStr::CStr AddArrayEntryText =
					"[\n"
					"/*a*/ 1 /*b*/ ,  /*e*/ \n"
					"]\n"
				;
				auto AddedArrayEntry = CJsonOrderedWithComments::fs_FromStringJson5(AddArrayEntryText);
				AddedArrayEntry.f_Insert(2);
				DMibExpect
					(
						AddedArrayEntry.f_ToStringJson5()
						, ==
						, "[\n"
						"/*a*/ 1 /*b*/ ,  /*e*/ \n"
						"	2\n"
						"]\n"
					)
				;

				auto AddedTrailingCommaObjectEntry = CJsonOrderedWithComments::fs_FromStringJson5
					(
						"{\n"
						"	a: 1,\n"
						"	b: 2\n"
						"}\n"
					)
				;
				AddedTrailingCommaObjectEntry["c"] = 3;
				DMibExpect
					(
						AddedTrailingCommaObjectEntry.f_ToStringJson5()
						, ==
						, "{\n"
						"	a: 1,\n"
						"	b: 2,\n"
						"	\"c\": 3\n"
						"}\n"
					)
				;

				auto AddedLeadingCommaObjectEntry = CJsonOrderedWithComments::fs_FromStringJson5
					(
						"{\n"
						"	a: 1\n"
						"	, b: 2\n"
						"}\n"
					)
				;
				AddedLeadingCommaObjectEntry["c"] = 3;
				DMibExpect
					(
						AddedLeadingCommaObjectEntry.f_ToStringJson5()
						, ==
						, "{\n"
						"	a: 1\n"
						"	, b: 2\n"
						"	, \"c\": 3\n"
						"}\n"
					)
				;

				auto AddedTrailingCommaArrayEntry = CJsonOrderedWithComments::fs_FromStringJson5
					(
						"[\n"
						"	1,\n"
						"	2\n"
						"]\n"
					)
				;
				AddedTrailingCommaArrayEntry.f_Insert(3);
				DMibExpect
					(
						AddedTrailingCommaArrayEntry.f_ToStringJson5()
						, ==
						, "[\n"
						"	1,\n"
						"	2,\n"
						"	3\n"
						"]\n"
					)
				;

				auto AddedLeadingCommaArrayEntry = CJsonOrderedWithComments::fs_FromStringJson5
					(
						"[\n"
						"	1\n"
						"	, 2\n"
						"]\n"
					)
				;
				AddedLeadingCommaArrayEntry.f_Insert(3);
				DMibExpect
					(
						AddedLeadingCommaArrayEntry.f_ToStringJson5()
						, ==
						, "[\n"
						"	1\n"
						"	, 2\n"
						"	, 3\n"
						"]\n"
					)
				;

				auto TrailingCommaObjectHeadSource = CJsonOrderedWithComments::fs_FromStringJson5
					(
						"{\n"
						"	a: 1,\n"
						"	b: 2\n"
						"}\n"
					)
				;
				CJsonOrderedWithComments AddedTrailingCommaObjectHead(EJsonType_Object);
				AddedTrailingCommaObjectHead["head"] = 0;
				AddedTrailingCommaObjectHead.f_Trivia().f_SetTrailing(fg_TempCopy(TrailingCommaObjectHeadSource.f_Trivia().f_Trailing()), TrailingCommaObjectHeadSource.f_Trivia().f_HasTrailingComma());
				TrailingCommaObjectHeadSource.f_Object().f_ExtractAll
					(
						[&](auto &&_Handle)
						{
							AddedTrailingCommaObjectHead.f_Object().f_Insert(fg_Move(_Handle));
						}
					)
				;
				DMibExpect
					(
						AddedTrailingCommaObjectHead.f_ToStringJson5()
						, ==
						, "{\n"
						"	\"head\": 0,\n"
						"	a: 1,\n"
						"	b: 2\n"
						"}\n"
					)
				;

				auto LeadingCommaObjectHeadSource = CJsonOrderedWithComments::fs_FromStringJson5
					(
						"{\n"
						"	a: 1\n"
						"	, b: 2\n"
						"}\n"
					)
				;
				CJsonOrderedWithComments AddedLeadingCommaObjectHead(EJsonType_Object);
				AddedLeadingCommaObjectHead["head"] = 0;
				AddedLeadingCommaObjectHead.f_Trivia().f_SetTrailing(fg_TempCopy(LeadingCommaObjectHeadSource.f_Trivia().f_Trailing()), LeadingCommaObjectHeadSource.f_Trivia().f_HasTrailingComma());
				LeadingCommaObjectHeadSource.f_Object().f_ExtractAll
					(
						[&](auto &&_Handle)
						{
							AddedLeadingCommaObjectHead.f_Object().f_Insert(fg_Move(_Handle));
						}
					)
				;
				DMibExpect
					(
						AddedLeadingCommaObjectHead.f_ToStringJson5()
						, ==
						, "{\n"
						"	\"head\": 0\n"
						"	, a: 1\n"
						"	, b: 2\n"
						"}\n"
					)
				;

				auto AddedTrailingCommaArrayHead = CJsonOrderedWithComments::fs_FromStringJson5
					(
						"[\n"
						"	1,\n"
						"	2\n"
						"]\n"
					)
				;
				AddedTrailingCommaArrayHead.f_Array().f_InsertFirst() = 0;
				DMibExpect
					(
						AddedTrailingCommaArrayHead.f_ToStringJson5()
						, ==
						, "[\n"
						"	0,\n"
						"	1,\n"
						"	2\n"
						"]\n"
					)
				;

				auto AddedLeadingCommaArrayHead = CJsonOrderedWithComments::fs_FromStringJson5
					(
						"[\n"
						"	1\n"
						"	, 2\n"
						"]\n"
					)
				;
				AddedLeadingCommaArrayHead.f_Array().f_InsertFirst() = 0;
				DMibExpect
					(
						AddedLeadingCommaArrayHead.f_ToStringJson5()
						, ==
						, "[\n"
						"	0\n"
						"	, 1\n"
						"	, 2\n"
						"]\n"
					)
				;

				auto StrictText = Json.f_ToString();
				DMibExpect(StrictText.f_Find("//"), <, 0);
				DMibExpect(StrictText.f_Find("/*"), <, 0);
				DMibExpectNoException(CJsonOrdered::fs_FromString(StrictText));
				DMibExpect(Json.f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag_None), ==, Text);

				auto Copy = Json;
				DMibExpect(Copy.f_ToStringJson5(), ==, Text);
				CJsonOrderedWithComments Assigned;
				Assigned = Json;
				DMibExpect(Assigned.f_ToStringJson5(), ==, Text);
				auto StrictCompatible = CJsonOrdered::fs_FromCompatible(Json);
				DMibExpect(StrictCompatible["a"].f_Integer(), ==, 1);
				auto CommentCompatible = CJsonOrderedWithComments::fs_FromCompatible(StrictCompatible);
				DMibExpect(CommentCompatible.f_Trivia().f_Leading().f_IsEmpty(), ==, true);
				DMibExpect(CommentCompatible["a"].f_Trivia().f_Trailing().f_IsEmpty(), ==, true);
				auto SortedStrictCompatible = CJsonSorted::fs_FromCompatible(StrictCompatible);
				DMibExpect(SortedStrictCompatible["a"].f_Integer(), ==, 1);
				auto SortedCommentCompatible = CJsonSortedWithComments::fs_FromCompatible(Json);
				DMibExpect(SortedCommentCompatible["a"].f_Integer(), ==, 1);
				DMibExpect(CJsonOrdered::fs_FromCompatible(SortedCommentCompatible)["a"].f_Integer(), ==, 1);
				DMibExpect(CJsonSorted::fs_FromCompatible(Json)["a"].f_Integer(), ==, 1);
				DMibExpect(CJsonOrderedWithComments::fs_FromCompatible(SortedStrictCompatible)["a"].f_Integer(), ==, 1);
				DMibExpect(CJsonOrderedWithComments::fs_FromCompatible(SortedCommentCompatible)["a"].f_Integer(), ==, 1);
				DMibExpect(CJsonSortedWithComments::fs_FromCompatible(StrictCompatible)["a"].f_Integer(), ==, 1);
				NStr::CStr MoveCompatibleText =
					"{\n"
					"	// moved\n"
					"	a: {\n"
					"		// interior\n"
					"	} // tail\n"
					"}\n"
				;
				auto SortedMoveCompatible = CJsonSortedWithComments::fs_FromStringJson5(MoveCompatibleText);
				auto OrderedMoveCompatible = CJsonOrderedWithComments::fs_FromCompatible(fg_Move(SortedMoveCompatible));
				DMibExpect(OrderedMoveCompatible.f_ToStringJson5(), ==, MoveCompatibleText);

				CJsonOrderedWithComments Manual(EJsonType_Object);
				NStr::CStr ManualKey("manual");
				ManualKey.f_SetUserData(EJsonStringType_NoQuote);
				auto &ManualEntry = Manual.f_Object().f_CreateMemberEntry(fg_Move(ManualKey));
				ManualEntry.f_KeyTrivia().f_SetLeading
					(
						"\n"
						"	// manual\n"
						"	"
						, false
					)
				;
				ManualEntry.f_KeyTrivia().f_SetTrailing(" /*key*/ ");
				ManualEntry.f_Value().f_Trivia().f_SetLeading(" /*value*/ ", false);
				ManualEntry.f_Value() = 7;
				ManualEntry.f_Value().f_Trivia().f_SetTrailing("\n", false);
				DMibExpect
					(
						Manual.f_ToStringJson5()
						, ==
						, "{\n"
						"	// manual\n"
						"	manual /*key*/ : /*value*/ 7\n"
						"}"
					)
				;

				CJsonOrderedWithComments ManualInvalidTrivia(EJsonType_Object);
				NStr::CStr InvalidTriviaKey("a");
				InvalidTriviaKey.f_SetUserData(EJsonStringType_NoQuote);
				auto &InvalidTriviaEntry = ManualInvalidTrivia.f_Object().f_CreateMemberEntry(fg_Move(InvalidTriviaKey));
				InvalidTriviaEntry.f_KeyTrivia().f_SetLeading("// leading", false);
				InvalidTriviaEntry.f_KeyTrivia().f_SetTrailing("// key");
				InvalidTriviaEntry.f_Value().f_Trivia().f_SetLeading("// value", false);
				InvalidTriviaEntry.f_Value() = 1;
				InvalidTriviaEntry.f_Value().f_Trivia().f_SetTrailing("// trailing", false);
				ManualInvalidTrivia["b"] = 2;
				auto ManualInvalidTriviaText = ManualInvalidTrivia.f_ToStringJson5();
				DMibExpect
					(
						ManualInvalidTriviaText
						, ==
						, "{// leading\n"
						"a// key\n"
						":// value\n"
						"1,// trailing\n"
						"	\"b\": 2\n"
						"}"
					)
				;
				DMibExpectNoException(CJsonOrderedWithComments::fs_FromStringJson5(ManualInvalidTriviaText));

				CJsonOrderedWithComments ManualInvalidBlockTrivia(EJsonType_Object);
				NStr::CStr InvalidBlockTriviaKey("a");
				InvalidBlockTriviaKey.f_SetUserData(EJsonStringType_NoQuote);
				auto &InvalidBlockTriviaEntry = ManualInvalidBlockTrivia.f_Object().f_CreateMemberEntry(fg_Move(InvalidBlockTriviaKey));
				InvalidBlockTriviaEntry.f_KeyTrivia().f_SetLeading("/* leading", false);
				InvalidBlockTriviaEntry.f_KeyTrivia().f_SetTrailing(" /* key");
				InvalidBlockTriviaEntry.f_Value().f_Trivia().f_SetLeading(" /* value", false);
				InvalidBlockTriviaEntry.f_Value() = 1;
				InvalidBlockTriviaEntry.f_Value().f_Trivia().f_SetTrailing(" /* trailing", false);
				ManualInvalidBlockTrivia["b"] = 2;
				auto ManualInvalidBlockTriviaText = ManualInvalidBlockTrivia.f_ToStringJson5();
				DMibExpect
					(
						ManualInvalidBlockTriviaText
						, ==
						, "{/* leading*/a /* key*/: /* value*/1, /* trailing*/\t\"b\": 2\n"
						"}"
					)
				;
				DMibExpectNoException(CJsonOrderedWithComments::fs_FromStringJson5(ManualInvalidBlockTriviaText));

				CJsonOrderedWithComments ManualMixedTrailingTrivia(EJsonType_Array);
				auto &ManualMixedTrailingFirst = ManualMixedTrailingTrivia.f_Insert();
				ManualMixedTrailingFirst = 1;
				ManualMixedTrailingFirst.f_Trivia().f_SetTrailing(" /* closed */ // line", false);
				ManualMixedTrailingTrivia.f_Insert(2);
				auto ManualMixedTrailingTriviaText = ManualMixedTrailingTrivia.f_ToStringJson5();
				DMibExpect
					(
						ManualMixedTrailingTriviaText
						, ==
						, "[\n"
						"	1, /* closed */ // line\n"
						"	2\n"
						"]"
					)
				;
				DMibExpectNoException(CJsonOrderedWithComments::fs_FromStringJson5(ManualMixedTrailingTriviaText));

				CJsonOrderedWithComments CommentsOnlyLineSeparatorTrivia(EJsonType_Array);
				auto &CommentsOnlyLineSeparatorFirst = CommentsOnlyLineSeparatorTrivia.f_Insert();
				CommentsOnlyLineSeparatorFirst = 1;
				CommentsOnlyLineSeparatorFirst.f_Trivia().f_SetTrailing("// comment" "\xE2" "\x80" "\xA8", false);
				CommentsOnlyLineSeparatorTrivia.f_Insert(2);
				auto CommentsOnlyLineSeparatorTriviaText = CommentsOnlyLineSeparatorTrivia.f_ToString<CJsonCommentsOnlyParseContext>();
				DMibExpect
					(
						CommentsOnlyLineSeparatorTriviaText
						, ==
						, "[\n"
						"\t1,// comment" "\xE2" "\x80" "\xA8" "\n"
						"\t2\n"
						"]"
					)
				;
				DMibExpectNoException(CJsonOrderedWithComments::fs_FromString<CJsonCommentsOnlyParseContext>(CommentsOnlyLineSeparatorTriviaText));

				CJsonOrderedWithComments ManualLineThenBlockTrivia(EJsonType_Array);
				auto &ManualLineThenBlockFirst = ManualLineThenBlockTrivia.f_Insert();
				ManualLineThenBlockFirst = 1;
				ManualLineThenBlockFirst.f_Trivia().f_SetTrailing("// line\n/* block", false);
				ManualLineThenBlockTrivia.f_Insert(2);
				auto ManualLineThenBlockTriviaText = ManualLineThenBlockTrivia.f_ToStringJson5();
				DMibExpect
					(
						ManualLineThenBlockTriviaText
						, ==
						, "[\n"
						"	1,// line\n"
						"/* block*/	2\n"
						"]"
					)
				;
				DMibExpectNoException(CJsonOrderedWithComments::fs_FromStringJson5(ManualLineThenBlockTriviaText));

				CJsonOrderedWithComments ManualRootAndInteriorInvalidTrivia(EJsonType_Array);
				ManualRootAndInteriorInvalidTrivia.f_Trivia().f_SetLeading("/* root */ // root", false);
				ManualRootAndInteriorInvalidTrivia.f_Trivia().f_SetInterior("// interior /* stays line");
				ManualRootAndInteriorInvalidTrivia.f_Trivia().f_SetTrailing("/* eof", false);
				auto ManualRootAndInteriorInvalidTriviaText = ManualRootAndInteriorInvalidTrivia.f_ToStringJson5(nullptr);
				DMibExpect
					(
						ManualRootAndInteriorInvalidTriviaText
						, ==
						, "/* root */ // root\n"
						"[// interior /* stays line\n"
						"]/* eof*/"
					)
				;
				DMibExpectNoException(CJsonOrderedWithComments::fs_FromStringJson5(ManualRootAndInteriorInvalidTriviaText));

				CJsonOrderedWithComments ManualLeadingCommaMetadata(EJsonType_Array);
				ManualLeadingCommaMetadata.f_Insert(1);
				auto &ManualLeadingCommaValue = ManualLeadingCommaMetadata.f_Insert();
				ManualLeadingCommaValue.f_Trivia().f_SetLeading("\n\t", true);
				ManualLeadingCommaValue = 2;
				DMibExpect
					(
						ManualLeadingCommaMetadata.f_ToStringJson5()
						, ==
						, "[\n"
						"	1\n"
						"	, 2\n"
						"]"
					)
				;

				CJsonOrderedWithComments ManualTrailingCommaMetadata(EJsonType_Array);
				auto &ManualTrailingCommaValue = ManualTrailingCommaMetadata.f_Insert();
				ManualTrailingCommaValue = 1;
				ManualTrailingCommaValue.f_Trivia().f_SetTrailing("\n", true);
				DMibExpect
					(
						ManualTrailingCommaMetadata.f_ToStringJson5()
						, ==
						, "[\n"
						"	1,\n"
						"]"
					)
				;

				CJsonOrderedWithComments ManualEmptyArray(EJsonType_Array);
				ManualEmptyArray.f_Trivia().f_SetInterior("// empty\n");
				DMibExpect(ManualEmptyArray.f_ToStringJson5(nullptr), ==, "[// empty\n]");

				CJsonOrderedWithComments ManualInvalidEmptyArray(EJsonType_Array);
				ManualInvalidEmptyArray.f_Trivia().f_SetInterior("// empty");
				DMibExpect(ManualInvalidEmptyArray.f_ToStringJson5(nullptr), ==, "[// empty\n]");

				auto Streamed = NStream::fg_FromByteVector<CJsonOrderedWithComments>(NStream::fg_ToByteVector(Json));
				DMibExpect(Streamed.f_ToStringJson5(), ==, Text);
				NStr::CStr SingleQuotedValueText = "{a: 'x'}\n";
				auto SingleQuotedValue = CJsonOrderedWithComments::fs_FromStringJson5(SingleQuotedValueText);
				auto SingleQuotedValueRoundTripText = SingleQuotedValue.f_ToStringJson5();
				DMibExpect(SingleQuotedValueRoundTripText.f_Find("'x'"), >=, 0);
				auto StreamedSingleQuotedValue = NStream::fg_FromByteVector<CJsonOrderedWithComments>(NStream::fg_ToByteVector(SingleQuotedValue));
				DMibExpect(StreamedSingleQuotedValue.f_ToStringJson5(), ==, SingleQuotedValueRoundTripText);

				NStr::CStr SortedText =
					"{\n"
					"	// a\n"
					"	a: 1,\n"
					"	// b\n"
					"	b: 2,\n"
					"}\n"
				;
				auto SortedJson = CJsonSortedWithComments::fs_FromStringJson5(SortedText);
				DMibExpect(SortedJson.f_ToStringJson5(), ==, SortedText);
				auto SortedStreamed = NStream::fg_FromByteVector<CJsonSortedWithComments>(NStream::fg_ToByteVector(SortedJson));
				DMibExpect(SortedStreamed.f_ToStringJson5(), ==, SortedText);
				auto SortedSingleQuotedValue = CJsonSortedWithComments::fs_FromStringJson5(SingleQuotedValueText);
				auto SortedSingleQuotedValueRoundTripText = SortedSingleQuotedValue.f_ToStringJson5();
				DMibExpect(SortedSingleQuotedValueRoundTripText.f_Find("'x'"), >=, 0);
				auto SortedStreamedSingleQuotedValue = NStream::fg_FromByteVector<CJsonSortedWithComments>(NStream::fg_ToByteVector(SortedSingleQuotedValue));
				DMibExpect(SortedStreamedSingleQuotedValue.f_ToStringJson5(), ==, SortedSingleQuotedValueRoundTripText);

				DMibTestPath("UnterminatedBlockComment");
				DMibExpectException
					(
						CJsonOrderedWithComments::fs_FromStringJson5("/* unterminated")
						, fs_MakeParseException("Unterminated block comment", 1, 1, 0)
					)
				;
			};
			DMibTestSuite("Stream")
			{
				DMibExpect(NStream::fg_FromByteVector<CJsonSorted>(NStream::fg_ToByteVector(fs_GetJson())), ==, CJsonSorted::fs_FromCompatible(fs_GetJson()));
			};
		}
	};

	DMibTestRegister(CJson_Tests, Malterlib::Encoding);
}
