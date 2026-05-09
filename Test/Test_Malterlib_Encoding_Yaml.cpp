// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Encoding/Yaml>
#include <Mib/Test/Exception>

namespace
{
	using namespace NMib;
	using namespace NMib::NEncoding;

	struct CYamlFlowConvertNullToSpace : public NYaml::CFlowOnlyParseContext
	{
		static constexpr bool mc_bConvertNullToSpace = true;
	};

	struct CYaml_Tests : public NTest::CTest
	{
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

		template <bool tf_bOrdered>
		void f_DoTestsImpl(NStr::CStr const &_Description)
		{
			using CJsonWithMeta = TCConditional<tf_bOrdered, CJsonOrderedYaml, CJsonSortedYaml>;
			using CJsonWithoutMeta = TCConditional<tf_bOrdered, CJsonOrdered, CJsonSorted>;
			using CEJsonWithMeta = TCConditional<tf_bOrdered, CEJsonOrderedYaml, CEJsonSortedYaml>;
			using CEJsonWithoutMeta = TCConditional<tf_bOrdered, CEJsonOrdered, CEJsonSorted>;

			DMibTestSuite(_Description)
			{
				DMibTestCategory("Flow")
				{
					auto Json = CJsonWithoutMeta::fs_FromStringYamlFlow("{a: 1, b: [2, 3], c: true, d: null}");
					DMibExpect(Json.f_IsObject(), ==, true);
					DMibExpect(Json["a"].f_Integer(), ==, 1);
					DMibExpect(Json["b"][0].f_Integer(), ==, 2);
					DMibExpect(Json["b"][1].f_Integer(), ==, 3);
					DMibExpect(Json["c"].f_Boolean(), ==, true);
					DMibExpect(Json["d"].f_IsNull(), ==, true);

					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("'it''s'").f_String(), ==, "it's");
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("\"line\\nfeed\"").f_String(), ==, "line\nfeed");
					DMibExpect(CJsonWithMeta::fs_FromStringYamlFlow("{a: [1]}").f_Yaml().f_NodeStyle(), ==, EYamlNodeStyle_Flow);

					auto FlowValueComment = CJsonWithMeta::fs_FromStringYamlFlow
						(
							"{a: 1 # a line\n"
							", b: 2}"
						)
					;
					DMibExpect(FlowValueComment["a"].f_Yaml().f_LineComment(), ==, " # a line");
					DMibExpect(FlowValueComment.f_ToStringYamlFlow(), ==, "{a: 1 # a line\n, b: 2}");

					auto FlowSequenceValueComment = CJsonWithMeta::fs_FromStringYamlFlow
						(
							"[1 # one\n"
							", 2]"
						)
					;
					DMibExpect(FlowSequenceValueComment[0].f_Yaml().f_LineComment(), ==, " # one");
					DMibExpect(FlowSequenceValueComment.f_ToStringYamlFlow(), ==, "[1 # one\n, 2]");
				};

				DMibTestCategory("Anchors")
				{
					auto Json = CJsonWithMeta::fs_FromStringYamlFlow("{defaults: &d {x: 1}, service: *d}");
					DMibExpect(Json["defaults"].f_Yaml().f_Anchor(), ==, "d");
					DMibExpect(Json["service"].f_Yaml().f_Alias(), ==, "d");
					DMibExpect(Json["service"]["x"].f_Integer(), ==, 1);
					DMibExpect(Json.f_ToStringYamlFlow(), ==, "{defaults: &d {x: 1}, service: *d}");

					Json["service"]["x"] = 2;
					DMibExpect(Json.f_ToStringYamlFlow(), ==, "{defaults: &d {x: 1}, service: {x: 2}}");

					CJsonWithMeta MissingAnchor(EJsonType_Object);
					MissingAnchor["service"]["x"] = 1;
					MissingAnchor["service"].f_Yaml().f_SetAlias("d");
					DMibExpect(MissingAnchor.f_ToStringYamlFlow(), ==, "{service: {x: 1}}");

					DMibExpect(CJsonWithMeta::fs_FromStringYamlFlow("[&d {x: 1}, &d {x: 2}, *d]").f_ToStringYamlFlow(), ==, "[&d {x: 1}, &d {x: 2}, {x: 2}]");
					DMibExpect(CJsonSortedYaml::fs_FromStringYamlFlow("{z: &d {x: 1}, a: *d}").f_ToStringYamlFlow(), ==, "{a: {x: 1}, z: &d {x: 1}}");

					DMibExpectException
						(
							CJsonWithMeta::fs_FromStringYamlFlow("{value: &v 123, copy: !!str *v}"), fs_MakeParseException("YAML alias node must not specify properties", 1, 27, 26)
						)
					;
					DMibExpectException
						(
							CJsonWithMeta::fs_FromStringYamlFlow("{value: &v \"123\", copy: !!int *v}"), fs_MakeParseException("YAML alias node must not specify properties", 1, 31, 30)
						)
					;
					DMibExpectException
						(
							CJsonWithMeta::fs_FromStringYamlFlow("{value: &v \"true\", copy: !!bool *v}"), fs_MakeParseException("YAML alias node must not specify properties", 1, 33, 32)
						)
					;
					DMibExpectException
						(
							CJsonWithMeta::fs_FromStringYamlFlow("{value: &v 123, copy: &a *v}"), fs_MakeParseException("YAML alias node must not specify properties", 1, 27, 26)
						)
					;
					DMibExpectException
						(
							CJsonWithMeta::fs_FromStringYamlBlock
							(
								"value: &v 123\n"
								"copy: !!str *v\n"
							)
							, fs_MakeParseException("YAML alias node must not specify properties", 2, 13, 26)
						)
					;
					DMibExpectException
						(
							CJsonWithMeta::fs_FromStringYamlBlock
							(
								"value: &v 123\n"
								"copy: &a *v\n"
							)
							, fs_MakeParseException("YAML alias node must not specify properties", 2, 10, 23)
						)
					;

					DMibExpect(CEJsonWithMeta::fs_FromStringYamlFlow("!Outer {a: &x 1, b: *x}").f_ToStringYamlFlow(), ==, "!Outer {a: &x 1, b: *x}");
					DMibExpect(CEJsonWithMeta::fs_FromStringYamlFlow("!Outer [ &x 1, *x ]").f_ToStringYamlFlow(), ==, "!Outer [&x 1, *x]");
					DMibExpect(CEJsonWithMeta::fs_FromStringYamlFlow("!Outer {child: !Inner {a: &x 1, b: *x}}").f_ToStringYamlFlow(), ==, "!Outer {child: !Inner {a: &x 1, b: *x}}");

					auto UserTypeBlockAlias = CEJsonWithMeta::fs_FromStringYamlBlock
						(
							"!Outer\n"
							"  a: &x 1\n"
							"  b: *x\n"
						)
					;
					DMibExpect(UserTypeBlockAlias.f_ToStringYaml(), ==, "!Outer\n  a: &x 1\n  b: *x\n");

					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("[*foo, &foo 1]"), fs_MakeParseException("Unknown YAML alias", 1, 7, 6));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("{self: &a {self: *a}}"), fs_MakeParseException("cyclic alias not supported", 1, 20, 19));
				};

				DMibTestCategory("PlainSafety")
				{
					CJsonWithMeta Json(EJsonType_Object);
					Json["true"] = "true";
					Json["int"] = "42";
					Json["negative"] = "-1";
					Json["positive"] = "+1";
					Json["leadingDot"] = ".5";
					Json["colon"] = "foo: bar";
					auto Text = Json.f_ToStringYamlFlow();
					DMibExpect(Text.f_Find("\"true\""), >=, 0);
					DMibExpect(Text.f_Find("\"42\""), >=, 0);
					DMibExpect(Text.f_Find("\"-1\""), >=, 0);
					DMibExpect(Text.f_Find("\"+1\""), >=, 0);
					DMibExpect(Text.f_Find("\".5\""), >=, 0);
					DMibExpect(Text.f_Find("\"foo: bar\""), >=, 0);
					DMibExpect(CJsonWithMeta::fs_FromStringYamlFlow(Text), ==, Json);

					CJsonWithMeta Keys(EJsonType_Object);
					Keys["-1"] = "negative";
					Keys["+1"] = "positive";
					Keys[".5"] = "leadingDot";
					Text = Keys.f_ToStringYamlFlow();
					DMibExpect(Text.f_Find("\"-1\":"), >=, 0);
					DMibExpect(Text.f_Find("\"+1\":"), >=, 0);
					DMibExpect(Text.f_Find("\".5\":"), >=, 0);
					DMibExpect(CJsonWithMeta::fs_FromStringYamlFlow(Text), ==, Keys);
				};

				DMibTestCategory("DocumentMarkers")
				{
					auto Json = CJsonWithoutMeta::fs_FromStringYaml("--- {a: 1} ...");
					DMibExpect(Json["a"].f_Integer(), ==, 1);
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYaml("--- {a: 1}\n--- {b: 2}"), fs_MakeParseException("multi-document streams not supported", 2, 1, 11));
				};

				DMibTestCategory("Block")
				{
					NStr::CStr Text =
						"name: test\n"
						"enabled: true\n"
						"items:\n"
						"  - 1\n"
						"  - 2\n"
						"nested:\n"
						"  value: ok\n"
					;
					auto Json = CJsonWithoutMeta::fs_FromStringYamlBlock(Text);
					DMibExpect(Json["name"].f_String(), ==, "test");
					DMibExpect(Json["enabled"].f_Boolean(), ==, true);
					DMibExpect(Json["items"][0].f_Integer(), ==, 1);
					DMibExpect(Json["items"][1].f_Integer(), ==, 2);
					DMibExpect(Json["nested"]["value"].f_String(), ==, "ok");

					if constexpr (tf_bOrdered)
						DMibExpect(Json.f_ToStringYaml(), ==, Text);
					else
						DMibExpect
							(
								Json.f_ToStringYaml()
								, ==
								, "enabled: true\n"
								"items:\n"
								"  - 1\n"
								"  - 2\n"
								"name: test\n"
								"nested:\n"
								"  value: ok\n"
							)
						;
					DMibExpect(CJsonWithMeta::fs_FromStringYamlBlock(Text).f_Yaml().f_NodeStyle(), ==, EYamlNodeStyle_Block);

					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlBlock("'42': ok\n")["42"].f_String(), ==, "ok");
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlBlock("a: 1\na: 2\n"), fs_MakeParseException("Duplicate YAML mapping key", 2, 1, 6));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlBlock("42: value\n"), fs_MakeParseException("YAML mapping key must be a string", 1, 1, 0));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("{a: 1, a: 2}"), fs_MakeParseException("Duplicate YAML mapping key", 1, 8, 7));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("{true: value}"), fs_MakeParseException("YAML mapping key must be a string", 1, 2, 1));
				};

				DMibTestCategory("BlockScalars")
				{
					auto Literal = CJsonWithoutMeta::fs_FromStringYamlBlock
						(
							"text: |\n"
							"  hello\n"
							"  world\n"
						)
					;
					DMibExpect(Literal["text"].f_String(), ==, "hello\nworld\n");

					auto Folded = CJsonWithoutMeta::fs_FromStringYamlBlock
						(
							"text: >\n"
							"  hello\n"
							"  world\n"
						)
					;
					DMibExpect(Folded["text"].f_String(), ==, "hello world\n");

					auto FoldedYaml = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"text: >\n"
							"  hello\n"
							"  world\n"
						)
					;
					DMibExpect(FoldedYaml["text"].f_Yaml().f_ScalarStyle(), ==, EYamlScalarStyle_Folded);
					DMibExpect(FoldedYaml.f_ToStringYaml(), ==, "text: >\n  hello world\n");
				};

				DMibTestCategory("ScalarStyles")
				{
					auto SingleQuoted = CJsonWithMeta::fs_FromStringYamlFlow("'it''s'");
					DMibExpect(SingleQuoted.f_Yaml().f_ScalarStyle(), ==, EYamlScalarStyle_SingleQuoted);
					DMibExpect(SingleQuoted.f_ToStringYamlFlow(), ==, "'it''s'");
					auto DoubleQuoted = CJsonWithMeta::fs_FromStringYamlFlow("\"hello\"");
					DMibExpect(DoubleQuoted.f_Yaml().f_ScalarStyle(), ==, EYamlScalarStyle_DoubleQuoted);
					DMibExpect(DoubleQuoted.f_ToStringYamlFlow(), ==, "\"hello\"");
				};

				DMibTestCategory("BlockComments")
				{
					auto Json = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"scalar: 1 # value\n"
							"nested: # key\n"
							"  x: 2\n"
						)
					;
					DMibExpect(Json["scalar"].f_Yaml().f_LineComment(), ==, " # value");
					auto iNested = Json.f_Object().f_OrderedIterator();
					if constexpr (tf_bOrdered)
						++iNested;
					DMibExpect(iNested->f_KeyYaml().f_LineComment(), ==, " # key");
					if constexpr (tf_bOrdered)
						DMibExpect(Json.f_ToStringYaml(), ==, "scalar: 1 # value\nnested: # key\n  x: 2\n");
					else
						DMibExpect(Json.f_ToStringYaml(), ==, "nested: # key\n  x: 2\nscalar: 1 # value\n");

					auto Leading = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"# scalar key\n"
							"scalar: 1\n"
							"items:\n"
							"  # first item\n"
							"  - a\n"
						)
					;
					DMibExpect(Leading.f_Yaml().f_LeadingComment(), ==, "# scalar key\n");
					DMibExpect(Leading["items"].f_Array()[0].f_Yaml().f_LeadingComment(), ==, "  # first item\n");
					if constexpr (tf_bOrdered)
						DMibExpect(Leading.f_ToStringYaml(), ==, "# scalar key\nscalar: 1\nitems:\n  # first item\n  - a\n");
					else
						DMibExpect(Leading.f_ToStringYaml(), ==, "# scalar key\nitems:\n  # first item\n  - a\nscalar: 1\n");
				};

				DMibTestCategory("Tags")
				{
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("!!str true").f_String(), ==, "true");
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("!!int 0xff").f_Integer(), ==, 255);
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("!!bool false").f_Boolean(), ==, false);

					auto Tagged = CJsonWithMeta::fs_FromStringYamlFlow("!!str true");
					DMibExpect(Tagged.f_Yaml().f_TagHandle(), ==, "!!");
					DMibExpect(Tagged.f_Yaml().f_TagSuffix(), ==, "str");
					DMibExpect(Tagged.f_ToStringYamlFlow(), ==, "!!str true");
				};

				DMibTestCategory("EJsonTags")
				{
					auto Binary = CEJsonWithMeta::fs_FromStringYamlFlow("!!binary AAECAw==");
					DMibExpect(Binary.f_IsBinary(), ==, true);
					DMibExpect(Binary.f_Binary().f_GetLen(), ==, 4);
					DMibExpect(Binary.f_Binary()[0], ==, 0);
					DMibExpect(Binary.f_Binary()[3], ==, 3);
					DMibExpect(Binary.f_Yaml().f_TagSuffix(), ==, "binary");
					DMibExpect(Binary.f_ToStringYamlFlow(), ==, "!!binary AAECAw==");
					auto BlockBinary = CEJsonWithMeta::fs_FromStringYamlBlock
						(
							"data: !!binary |\n"
							"  AAEC\n"
							"  Aw==\n"
						)
					;
					DMibExpect(BlockBinary["data"].f_IsBinary(), ==, true);
					DMibExpect(BlockBinary["data"].f_Binary().f_GetLen(), ==, 4);

					auto Timestamp = CEJsonWithMeta::fs_FromStringYamlFlow("!!timestamp 2024-01-15T12:00:00Z");
					DMibExpect(Timestamp.f_IsDate(), ==, true);
					DMibExpect(fg_FormatYamlTimestamp(Timestamp.f_Date()), ==, "2024-01-15T12:00:00Z");
					DMibExpect(Timestamp.f_Yaml().f_TagSuffix(), ==, "timestamp");
					DMibExpect(Timestamp.f_ToStringYamlFlow(), ==, "!!timestamp 2024-01-15T12:00:00Z");

					auto TimestampOffset = CEJsonWithMeta::fs_FromStringYamlFlow("!!timestamp 2024-01-15 14:30:00 +02:30");
					DMibExpect(fg_FormatYamlTimestamp(TimestampOffset.f_Date()), ==, "2024-01-15T12:00:00Z");

					CEJsonWithMeta GeneratedDate;
					GeneratedDate.f_Date() = NTime::CTimeConvert::fs_CreateTime(2024, 1, 15, 12, 0, 0);
					DMibExpect(GeneratedDate.f_ToStringYamlFlow(), ==, "!!timestamp 2024-01-15T12:00:00Z");
					CEJsonWithMeta InvalidDate(EEJsonType_Date);
					DMibExpect(InvalidDate.f_ToStringYamlFlow(), ==, "!!timestamp null");

					auto UserType = CEJsonWithMeta::fs_FromStringYamlFlow("!Thing {x: 1}");
					DMibExpect(UserType.f_IsUserType(), ==, true);
					DMibExpect(UserType.f_UserType().m_Type, ==, "Thing");
					DMibExpect(UserType.f_UserType().m_Value["x"].f_Integer(), ==, 1);
					DMibExpect(UserType.f_ToStringYamlFlow(), ==, "!Thing {x: 1}");
					auto UserTypePayloadMetadata = CEJsonWithMeta::fs_FromStringYamlFlow("!Thing {x: 'a'}");
					DMibExpect(UserTypePayloadMetadata.f_UserType().m_Value["x"].f_Yaml().f_ScalarStyle(), ==, EYamlScalarStyle_SingleQuoted);

					auto NamedUserType = CEJsonWithMeta::fs_FromStringYamlFlow
						(
							"%TAG !e! tag:example.com,2026:\n"
							"--- !e!Thing {x: 1}"
						)
					;
					DMibExpect(NamedUserType.f_IsUserType(), ==, true);
					DMibExpect(NamedUserType.f_UserType().m_Type, ==, "tag:example.com,2026:Thing");
					DMibExpect(NamedUserType.f_Yaml().f_TagHandle(), ==, "!e!");
					DMibExpect(NamedUserType.f_Yaml().f_TagSuffix(), ==, "Thing");
					DMibExpect(NamedUserType.f_Yaml().f_DocumentTagHandles()["!e!"], ==, "tag:example.com,2026:");
					DMibExpect(NamedUserType.f_ToStringYamlFlow(), ==, "%TAG !e! tag:example.com,2026:\n---\n!e!Thing {x: 1}");

					auto WrappedDate = CEJsonWithMeta::fs_FromStringYamlFlow("{$date: 477139811000}");
					DMibExpect(WrappedDate.f_IsObject(), ==, true);
					DMibExpect(WrappedDate["$date"].f_Integer(), ==, 477139811000);
					auto WrappedBinary = CEJsonWithMeta::fs_FromStringYamlFlow("{$binary: \"AAECAw==\"}");
					DMibExpect(WrappedBinary.f_IsObject(), ==, true);
					DMibExpect(WrappedBinary["$binary"].f_String(), ==, "AAECAw==");
					auto WrappedUserType = CEJsonWithMeta::fs_FromStringYamlFlow("{$type: \"Thing\", $value: {x: 1}}");
					DMibExpect(WrappedUserType.f_IsObject(), ==, true);
					DMibExpect(WrappedUserType["$type"].f_String(), ==, "Thing");
					DMibExpect(WrappedUserType["$value"]["x"].f_Integer(), ==, 1);

					CEJsonWithMeta ProgrammaticUserType;
					auto &ProgrammaticUserTypeValue = ProgrammaticUserType.f_UserType();
					ProgrammaticUserTypeValue.m_Type = "Thing";
					CEJsonWithMeta ProgrammaticPayload;
					ProgrammaticPayload["literal"]["$date"] = 477139811000;
					fg_SetYamlUserTypeValue(ProgrammaticUserTypeValue, ProgrammaticPayload);
					DMibExpect(ProgrammaticUserTypeValue.m_Value["literal"]["$escape"]["$date"].f_Integer(), ==, 477139811000);
					DMibExpect(fg_GetYamlUserTypeValue(ProgrammaticUserTypeValue), ==, ProgrammaticPayload);
					DMibExpect(ProgrammaticUserType.f_ToStringYamlFlow(), ==, "!Thing {literal: {$date: 477139811000}}");
				};

				DMibTestCategory("YamlFlowTagsProjectToJsonAndEJson")
				{
					auto JsonTimestamp = CJsonWithoutMeta::fs_FromStringYamlFlow("!!timestamp 2024-01-15T12:00:00Z");
					DMibExpect(JsonTimestamp.f_IsString(), ==, true);
					DMibExpect(JsonTimestamp.f_String(), ==, "2024-01-15T12:00:00Z");
					DMibExpect(JsonTimestamp.f_ToStringYamlFlow(), ==, "2024-01-15T12:00:00Z");

					auto JsonTimestampMeta = CJsonWithMeta::fs_FromStringYamlFlow("!!timestamp 2024-01-15T12:00:00Z");
					DMibExpect(JsonTimestampMeta.f_IsString(), ==, true);
					DMibExpect(JsonTimestampMeta.f_String(), ==, "2024-01-15T12:00:00Z");
					DMibExpect(JsonTimestampMeta.f_Yaml().f_TagSuffix(), ==, "timestamp");
					DMibExpect(JsonTimestampMeta.f_ToStringYamlFlow(), ==, "!!timestamp 2024-01-15T12:00:00Z");

					auto EJsonTimestamp = CEJsonWithoutMeta::fs_FromStringYamlFlow("!!timestamp 2024-01-15T12:00:00Z");
					DMibExpect(EJsonTimestamp.f_IsDate(), ==, true);
					DMibExpect(fg_FormatYamlTimestamp(EJsonTimestamp.f_Date()), ==, "2024-01-15T12:00:00Z");
					DMibExpect(EJsonTimestamp.f_ToStringYamlFlow(), ==, "!!timestamp 2024-01-15T12:00:00Z");

					auto EJsonTimestampMeta = CEJsonWithMeta::fs_FromStringYamlFlow("!!timestamp 2024-01-15T12:00:00Z");
					DMibExpect(EJsonTimestampMeta.f_IsDate(), ==, true);
					DMibExpect(EJsonTimestampMeta.f_Yaml().f_TagSuffix(), ==, "timestamp");
					DMibExpect(EJsonTimestampMeta.f_ToStringYamlFlow(), ==, "!!timestamp 2024-01-15T12:00:00Z");

					auto JsonInvalidTimestamp = CJsonWithoutMeta::fs_FromStringYamlFlow("!!timestamp null");
					DMibExpect(JsonInvalidTimestamp.f_String(), ==, "null");
					auto JsonInvalidTimestampMeta = CJsonWithMeta::fs_FromStringYamlFlow("!!timestamp null");
					DMibExpect(JsonInvalidTimestampMeta.f_String(), ==, "null");
					DMibExpect(JsonInvalidTimestampMeta.f_Yaml().f_TagSuffix(), ==, "timestamp");
					auto EJsonInvalidTimestamp = CEJsonWithoutMeta::fs_FromStringYamlFlow("!!timestamp null");
					DMibExpect(EJsonInvalidTimestamp.f_IsDate(), ==, true);
					DMibExpect(EJsonInvalidTimestamp.f_Date().f_IsValid(), ==, false);
					auto EJsonInvalidTimestampMeta = CEJsonWithMeta::fs_FromStringYamlFlow("!!timestamp null");
					DMibExpect(EJsonInvalidTimestampMeta.f_IsDate(), ==, true);
					DMibExpect(EJsonInvalidTimestampMeta.f_Date().f_IsValid(), ==, false);
					DMibExpect(EJsonInvalidTimestampMeta.f_Yaml().f_TagSuffix(), ==, "timestamp");

					auto JsonBinary = CJsonWithoutMeta::fs_FromStringYamlFlow("!!binary AAECAw==");
					DMibExpect(JsonBinary.f_IsString(), ==, true);
					DMibExpect(JsonBinary.f_String(), ==, "AAECAw==");
					DMibExpect(JsonBinary.f_ToStringYamlFlow(), ==, "AAECAw==");

					auto JsonBinaryMeta = CJsonWithMeta::fs_FromStringYamlFlow("!!binary AAECAw==");
					DMibExpect(JsonBinaryMeta.f_IsString(), ==, true);
					DMibExpect(JsonBinaryMeta.f_String(), ==, "AAECAw==");
					DMibExpect(JsonBinaryMeta.f_Yaml().f_TagSuffix(), ==, "binary");
					DMibExpect(JsonBinaryMeta.f_ToStringYamlFlow(), ==, "!!binary AAECAw==");

					auto EJsonBinary = CEJsonWithoutMeta::fs_FromStringYamlFlow("!!binary AAECAw==");
					DMibExpect(EJsonBinary.f_IsBinary(), ==, true);
					DMibExpect(EJsonBinary.f_Binary().f_GetLen(), ==, 4);
					DMibExpect(EJsonBinary.f_ToStringYamlFlow(), ==, "!!binary AAECAw==");

					auto EJsonBinaryMeta = CEJsonWithMeta::fs_FromStringYamlFlow("!!binary AAECAw==");
					DMibExpect(EJsonBinaryMeta.f_IsBinary(), ==, true);
					DMibExpect(EJsonBinaryMeta.f_Binary().f_GetLen(), ==, 4);
					DMibExpect(EJsonBinaryMeta.f_Yaml().f_TagSuffix(), ==, "binary");
					DMibExpect(EJsonBinaryMeta.f_ToStringYamlFlow(), ==, "!!binary AAECAw==");

					auto FlowUserText = "!Outer {x: !Inner {y: !!timestamp 2024-01-15T12:00:00Z}, bin: !!binary AAECAw==, literal: {$date: 5}}";
					auto JsonUser = CJsonWithoutMeta::fs_FromStringYamlFlow(FlowUserText);
					DMibExpect(JsonUser.f_IsObject(), ==, true);
					DMibExpect(JsonUser["x"].f_IsObject(), ==, true);
					DMibExpect(JsonUser["x"]["y"].f_String(), ==, "2024-01-15T12:00:00Z");
					DMibExpect(JsonUser["bin"].f_String(), ==, "AAECAw==");
					DMibExpect(JsonUser["literal"]["$date"].f_Integer(), ==, 5);
					if constexpr (tf_bOrdered)
						DMibExpect(JsonUser.f_ToStringYamlFlow(), ==, "{x: {y: 2024-01-15T12:00:00Z}, bin: AAECAw==, literal: {$date: 5}}");
					else
						DMibExpect(JsonUser.f_ToStringYamlFlow(), ==, "{bin: AAECAw==, literal: {$date: 5}, x: {y: 2024-01-15T12:00:00Z}}");

					auto JsonUserMeta = CJsonWithMeta::fs_FromStringYamlFlow(FlowUserText);
					DMibExpect(JsonUserMeta.f_IsObject(), ==, true);
					DMibExpect(JsonUserMeta.f_Yaml().f_TagSuffix(), ==, "Outer");
					DMibExpect(JsonUserMeta["x"].f_Yaml().f_TagSuffix(), ==, "Inner");
					DMibExpect(JsonUserMeta["x"]["y"].f_String(), ==, "2024-01-15T12:00:00Z");
					DMibExpect(JsonUserMeta["x"]["y"].f_Yaml().f_TagSuffix(), ==, "timestamp");
					DMibExpect(JsonUserMeta["bin"].f_String(), ==, "AAECAw==");
					DMibExpect(JsonUserMeta["bin"].f_Yaml().f_TagSuffix(), ==, "binary");
					DMibExpect(JsonUserMeta["literal"]["$date"].f_Integer(), ==, 5);
					if constexpr (tf_bOrdered)
						DMibExpect(JsonUserMeta.f_ToStringYamlFlow(), ==, "!Outer {x: !Inner {y: !!timestamp 2024-01-15T12:00:00Z}, bin: !!binary AAECAw==, literal: {$date: 5}}");
					else
						DMibExpect(JsonUserMeta.f_ToStringYamlFlow(), ==, "!Outer {bin: !!binary AAECAw==, literal: {$date: 5}, x: !Inner {y: !!timestamp 2024-01-15T12:00:00Z}}");
					if constexpr (tf_bOrdered)
						DMibExpect(JsonUserMeta.f_ToStringYamlFlow(), ==, FlowUserText);

					auto EJsonUser = CEJsonWithoutMeta::fs_FromStringYamlFlow(FlowUserText);
					DMibExpect(EJsonUser.f_IsUserType(), ==, true);
					DMibExpect(EJsonUser.f_UserType().m_Type, ==, "Outer");
					DMibExpect(EJsonUser.f_UserType().m_Value["x"]["$type"].f_String(), ==, "Inner");
					DMibExpect(EJsonUser.f_UserType().m_Value["x"]["$value"]["y"]["$date"].f_IsInteger(), ==, true);
					DMibExpect(EJsonUser.f_UserType().m_Value["bin"]["$binary"].f_String(), ==, "AAECAw==");
					DMibExpect(EJsonUser.f_UserType().m_Value["literal"]["$escape"]["$date"].f_Integer(), ==, 5);
					if constexpr (tf_bOrdered)
						DMibExpect(EJsonUser.f_ToStringYamlFlow(), ==, "!Outer {x: !Inner {y: !!timestamp 2024-01-15T12:00:00Z}, bin: !!binary AAECAw==, literal: {$date: 5}}");
					else
						DMibExpect(EJsonUser.f_ToStringYamlFlow(), ==, "!Outer {bin: !!binary AAECAw==, literal: {$date: 5}, x: !Inner {y: !!timestamp 2024-01-15T12:00:00Z}}");

					auto EJsonUserMeta = CEJsonWithMeta::fs_FromStringYamlFlow(FlowUserText);
					DMibExpect(EJsonUserMeta.f_IsUserType(), ==, true);
					DMibExpect(EJsonUserMeta.f_UserType().m_Type, ==, "Outer");
					DMibExpect(EJsonUserMeta.f_Yaml().f_TagSuffix(), ==, "Outer");
					DMibExpect(EJsonUserMeta.f_UserType().m_Value["x"]["$type"].f_String(), ==, "Inner");
					DMibExpect(EJsonUserMeta.f_UserType().m_Value["x"]["$value"]["y"]["$date"].f_IsInteger(), ==, true);
					DMibExpect(EJsonUserMeta.f_UserType().m_Value["bin"]["$binary"].f_String(), ==, "AAECAw==");
					DMibExpect(EJsonUserMeta.f_UserType().m_Value["literal"]["$escape"]["$date"].f_Integer(), ==, 5);
					if constexpr (tf_bOrdered)
						DMibExpect(EJsonUserMeta.f_ToStringYamlFlow(), ==, "!Outer {x: !Inner {y: !!timestamp 2024-01-15T12:00:00Z}, bin: !!binary AAECAw==, literal: {$date: 5}}");
					else
						DMibExpect(EJsonUserMeta.f_ToStringYamlFlow(), ==, "!Outer {bin: !!binary AAECAw==, literal: {$date: 5}, x: !Inner {y: !!timestamp 2024-01-15T12:00:00Z}}");
					if constexpr (tf_bOrdered)
						DMibExpect(EJsonUserMeta.f_ToStringYamlFlow(), ==, FlowUserText);
				};

				DMibTestCategory("YamlBlockTagsProjectToJsonAndEJson")
				{
					auto JsonTimestampBlock = CJsonWithoutMeta::fs_FromStringYamlBlock("!!timestamp 2024-01-15T12:00:00Z\n");
					DMibExpect(JsonTimestampBlock.f_IsString(), ==, true);
					DMibExpect(JsonTimestampBlock.f_String(), ==, "2024-01-15T12:00:00Z");
					auto JsonTimestampBlockMeta = CJsonWithMeta::fs_FromStringYamlBlock("!!timestamp 2024-01-15T12:00:00Z\n");
					DMibExpect(JsonTimestampBlockMeta.f_IsString(), ==, true);
					DMibExpect(JsonTimestampBlockMeta.f_String(), ==, "2024-01-15T12:00:00Z");
					DMibExpect(JsonTimestampBlockMeta.f_Yaml().f_TagSuffix(), ==, "timestamp");
					auto EJsonTimestampBlock = CEJsonWithoutMeta::fs_FromStringYamlBlock("!!timestamp 2024-01-15T12:00:00Z\n");
					DMibExpect(EJsonTimestampBlock.f_IsDate(), ==, true);
					DMibExpect(fg_FormatYamlTimestamp(EJsonTimestampBlock.f_Date()), ==, "2024-01-15T12:00:00Z");
					auto EJsonTimestampBlockMeta = CEJsonWithMeta::fs_FromStringYamlBlock("!!timestamp 2024-01-15T12:00:00Z\n");
					DMibExpect(EJsonTimestampBlockMeta.f_IsDate(), ==, true);
					DMibExpect(EJsonTimestampBlockMeta.f_Yaml().f_TagSuffix(), ==, "timestamp");

					auto JsonInvalidTimestampBlock = CJsonWithoutMeta::fs_FromStringYamlBlock("!!timestamp null\n");
					DMibExpect(JsonInvalidTimestampBlock.f_String(), ==, "null");
					auto JsonInvalidTimestampBlockMeta = CJsonWithMeta::fs_FromStringYamlBlock("!!timestamp null\n");
					DMibExpect(JsonInvalidTimestampBlockMeta.f_String(), ==, "null");
					DMibExpect(JsonInvalidTimestampBlockMeta.f_Yaml().f_TagSuffix(), ==, "timestamp");
					auto EJsonInvalidTimestampBlock = CEJsonWithoutMeta::fs_FromStringYamlBlock("!!timestamp null\n");
					DMibExpect(EJsonInvalidTimestampBlock.f_IsDate(), ==, true);
					DMibExpect(EJsonInvalidTimestampBlock.f_Date().f_IsValid(), ==, false);
					auto EJsonInvalidTimestampBlockMeta = CEJsonWithMeta::fs_FromStringYamlBlock("!!timestamp null\n");
					DMibExpect(EJsonInvalidTimestampBlockMeta.f_IsDate(), ==, true);
					DMibExpect(EJsonInvalidTimestampBlockMeta.f_Date().f_IsValid(), ==, false);
					DMibExpect(EJsonInvalidTimestampBlockMeta.f_Yaml().f_TagSuffix(), ==, "timestamp");

					auto JsonBinaryBlock = CJsonWithoutMeta::fs_FromStringYamlBlock("!!binary |\n  AAEC\n  Aw==\n");
					DMibExpect(JsonBinaryBlock.f_IsString(), ==, true);
					DMibExpect(JsonBinaryBlock.f_String(), ==, "AAEC\nAw==\n");
					auto JsonBinaryBlockMeta = CJsonWithMeta::fs_FromStringYamlBlock("!!binary |\n  AAEC\n  Aw==\n");
					DMibExpect(JsonBinaryBlockMeta.f_IsString(), ==, true);
					DMibExpect(JsonBinaryBlockMeta.f_String(), ==, "AAEC\nAw==\n");
					DMibExpect(JsonBinaryBlockMeta.f_Yaml().f_TagSuffix(), ==, "binary");
					auto EJsonBinaryBlock = CEJsonWithoutMeta::fs_FromStringYamlBlock("!!binary |\n  AAEC\n  Aw==\n");
					DMibExpect(EJsonBinaryBlock.f_IsBinary(), ==, true);
					DMibExpect(EJsonBinaryBlock.f_Binary().f_GetLen(), ==, 4);
					auto EJsonBinaryBlockMeta = CEJsonWithMeta::fs_FromStringYamlBlock("!!binary |\n  AAEC\n  Aw==\n");
					DMibExpect(EJsonBinaryBlockMeta.f_IsBinary(), ==, true);
					DMibExpect(EJsonBinaryBlockMeta.f_Binary().f_GetLen(), ==, 4);
					DMibExpect(EJsonBinaryBlockMeta.f_Yaml().f_TagSuffix(), ==, "binary");

					auto BlockUserText =
						"!Outer\n"
						"  bin: !!binary AAECAw==\n"
						"  literal:\n"
						"    $date: 5\n"
						"  x: !Inner\n"
						"    y: !!timestamp 2024-01-15T12:00:00Z\n"
					;

					auto JsonUserBlock = CJsonWithoutMeta::fs_FromStringYamlBlock(BlockUserText);
					DMibExpect(JsonUserBlock.f_IsObject(), ==, true);
					DMibExpect(JsonUserBlock["x"].f_IsObject(), ==, true);
					DMibExpect(JsonUserBlock["x"]["y"].f_String(), ==, "2024-01-15T12:00:00Z");
					DMibExpect(JsonUserBlock["bin"].f_String(), ==, "AAECAw==");
					DMibExpect(JsonUserBlock["literal"]["$date"].f_Integer(), ==, 5);

					auto JsonUserBlockMeta = CJsonWithMeta::fs_FromStringYamlBlock(BlockUserText);
					DMibExpect(JsonUserBlockMeta.f_IsObject(), ==, true);
					DMibExpect(JsonUserBlockMeta.f_Yaml().f_TagSuffix(), ==, "Outer");
					DMibExpect(JsonUserBlockMeta["x"].f_Yaml().f_TagSuffix(), ==, "Inner");
					DMibExpect(JsonUserBlockMeta["x"]["y"].f_String(), ==, "2024-01-15T12:00:00Z");
					DMibExpect(JsonUserBlockMeta["x"]["y"].f_Yaml().f_TagSuffix(), ==, "timestamp");
					DMibExpect(JsonUserBlockMeta["bin"].f_String(), ==, "AAECAw==");
					DMibExpect(JsonUserBlockMeta["bin"].f_Yaml().f_TagSuffix(), ==, "binary");
					DMibExpect(JsonUserBlockMeta["literal"]["$date"].f_Integer(), ==, 5);
					DMibExpect(JsonUserBlockMeta.f_ToStringYaml(), ==, BlockUserText);

					auto EJsonUserBlock = CEJsonWithoutMeta::fs_FromStringYamlBlock(BlockUserText);
					DMibExpect(EJsonUserBlock.f_IsUserType(), ==, true);
					DMibExpect(EJsonUserBlock.f_UserType().m_Type, ==, "Outer");
					DMibExpect(EJsonUserBlock.f_UserType().m_Value["x"]["$type"].f_String(), ==, "Inner");
					DMibExpect(EJsonUserBlock.f_UserType().m_Value["x"]["$value"]["y"]["$date"].f_IsInteger(), ==, true);
					DMibExpect(EJsonUserBlock.f_UserType().m_Value["bin"]["$binary"].f_String(), ==, "AAECAw==");
					DMibExpect(EJsonUserBlock.f_UserType().m_Value["literal"]["$escape"]["$date"].f_Integer(), ==, 5);

					auto EJsonUserBlockMeta = CEJsonWithMeta::fs_FromStringYamlBlock(BlockUserText);
					DMibExpect(EJsonUserBlockMeta.f_IsUserType(), ==, true);
					DMibExpect(EJsonUserBlockMeta.f_UserType().m_Type, ==, "Outer");
					DMibExpect(EJsonUserBlockMeta.f_Yaml().f_TagSuffix(), ==, "Outer");
					DMibExpect(EJsonUserBlockMeta.f_UserType().m_Value["x"]["$type"].f_String(), ==, "Inner");
					DMibExpect(EJsonUserBlockMeta.f_UserType().m_Value["x"]["$value"]["y"]["$date"].f_IsInteger(), ==, true);
					DMibExpect(EJsonUserBlockMeta.f_UserType().m_Value["bin"]["$binary"].f_String(), ==, "AAECAw==");
					DMibExpect(EJsonUserBlockMeta.f_UserType().m_Value["literal"]["$escape"]["$date"].f_Integer(), ==, 5);
					DMibExpect(EJsonUserBlockMeta.f_ToStringYaml(), ==, BlockUserText);
					DMibExpect(CEJsonWithMeta::fs_FromJson(EJsonUserBlockMeta.f_ToJson()).f_ToStringYaml(), ==, BlockUserText);

					auto BlockUserSeparateTagText =
						"!Outer\n"
						"  bin: !!binary AAECAw==\n"
						"  literal:\n"
						"    $date: 5\n"
						"  x:\n"
						"    !Inner\n"
						"      y: !!timestamp 2024-01-15T12:00:00Z\n"
					;

					auto JsonUserBlockSeparateTagMeta = CJsonWithMeta::fs_FromStringYamlBlock(BlockUserSeparateTagText);
					DMibExpect(JsonUserBlockSeparateTagMeta.f_IsObject(), ==, true);
					DMibExpect(JsonUserBlockSeparateTagMeta.f_Yaml().f_TagSuffix(), ==, "Outer");
					DMibExpect(JsonUserBlockSeparateTagMeta["x"].f_IsObject(), ==, true);
					DMibExpect(JsonUserBlockSeparateTagMeta["x"].f_Yaml().f_TagSuffix(), ==, "Inner");
					DMibExpect(JsonUserBlockSeparateTagMeta["x"]["y"].f_String(), ==, "2024-01-15T12:00:00Z");
					DMibExpect(JsonUserBlockSeparateTagMeta["x"]["y"].f_Yaml().f_TagSuffix(), ==, "timestamp");
					DMibExpect(JsonUserBlockSeparateTagMeta.f_ToStringYaml(), ==, BlockUserSeparateTagText);
					CJsonWithMeta JsonUserBlockSeparateTagMetaCopy = JsonUserBlockSeparateTagMeta;
					DMibExpect(JsonUserBlockSeparateTagMetaCopy.f_ToStringYaml(), ==, BlockUserSeparateTagText);

					auto EJsonUserBlockSeparateTagMeta = CEJsonWithMeta::fs_FromStringYamlBlock(BlockUserSeparateTagText);
					DMibExpect(EJsonUserBlockSeparateTagMeta.f_IsUserType(), ==, true);
					DMibExpect(EJsonUserBlockSeparateTagMeta.f_UserType().m_Type, ==, "Outer");
					DMibExpect(EJsonUserBlockSeparateTagMeta.f_UserType().m_Value["x"]["$type"].f_String(), ==, "Inner");
					DMibExpect(EJsonUserBlockSeparateTagMeta.f_UserType().m_Value["x"]["$value"]["y"]["$date"].f_IsInteger(), ==, true);
					DMibExpect(EJsonUserBlockSeparateTagMeta.f_ToStringYaml(), ==, BlockUserSeparateTagText);
					DMibExpect(CEJsonWithMeta::fs_FromJson(EJsonUserBlockSeparateTagMeta.f_ToJson()).f_ToStringYaml(), ==, BlockUserSeparateTagText);

					auto BlockUserCommentText =
						"# outer leading\n"
						"!Outer\n"
						"  # bin leading\n"
						"  bin: !!binary AAECAw== # bin line\n"
						"  # literal leading\n"
						"  literal: # literal key\n"
						"    # date leading\n"
						"    $date: 5 # date line\n"
						"  # x leading\n"
						"  x: !Inner # x line\n"
						"    # y leading\n"
						"    y: !!timestamp 2024-01-15T12:00:00Z # y line\n"
						"# outer trailing\n"
					;

					auto JsonUserBlockCommentMeta = CJsonWithMeta::fs_FromStringYamlBlock(BlockUserCommentText);
					DMibExpect(JsonUserBlockCommentMeta.f_Yaml().f_LeadingComment(), ==, "# outer leading\n");
					DMibExpect(JsonUserBlockCommentMeta["bin"].f_Yaml().f_LeadingComment(), ==, "  # bin leading\n");
					DMibExpect(JsonUserBlockCommentMeta["bin"].f_Yaml().f_LineComment(), ==, " # bin line");
					DMibExpect(JsonUserBlockCommentMeta["literal"].f_Yaml().f_LeadingComment(), ==, "  # literal leading\n");
					DMibExpect(JsonUserBlockCommentMeta["literal"]["$date"].f_Yaml().f_LeadingComment(), ==, "    # date leading\n");
					DMibExpect(JsonUserBlockCommentMeta["literal"]["$date"].f_Yaml().f_LineComment(), ==, " # date line");
					DMibExpect(JsonUserBlockCommentMeta["x"].f_Yaml().f_LeadingComment(), ==, "  # x leading\n");
					DMibExpect(JsonUserBlockCommentMeta["x"].f_Yaml().f_LineComment(), ==, " # x line");
					DMibExpect(JsonUserBlockCommentMeta["x"]["y"].f_Yaml().f_LeadingComment(), ==, "    # y leading\n");
					DMibExpect(JsonUserBlockCommentMeta["x"]["y"].f_Yaml().f_LineComment(), ==, " # y line");
					DMibExpect(JsonUserBlockCommentMeta.f_ToStringYaml(), ==, BlockUserCommentText);
					CJsonWithMeta JsonUserBlockCommentMetaCopy = JsonUserBlockCommentMeta;
					DMibExpect(JsonUserBlockCommentMetaCopy.f_ToStringYaml(), ==, BlockUserCommentText);

					auto EJsonUserBlockCommentMeta = CEJsonWithMeta::fs_FromStringYamlBlock(BlockUserCommentText);
					DMibExpect(EJsonUserBlockCommentMeta.f_IsUserType(), ==, true);
					DMibExpect(EJsonUserBlockCommentMeta.f_UserType().m_Type, ==, "Outer");
					DMibExpect(EJsonUserBlockCommentMeta.f_ToStringYaml(), ==, BlockUserCommentText);
					DMibExpect(CEJsonWithMeta::fs_FromJson(EJsonUserBlockCommentMeta.f_ToJson()).f_ToStringYaml(), ==, BlockUserCommentText);

					auto BlockUserSeparateTagCommentText =
						"# outer leading\n"
						"!Outer\n"
						"  # bin leading\n"
						"  bin: !!binary AAECAw== # bin line\n"
						"  # literal leading\n"
						"  literal: # literal key\n"
						"    # date leading\n"
						"    $date: 5 # date line\n"
						"  # x leading\n"
						"  x: # x key\n"
						"    !Inner # x line\n"
						"      # y leading\n"
						"      y: !!timestamp 2024-01-15T12:00:00Z # y line\n"
						"# outer trailing\n"
					;

					auto JsonUserBlockSeparateTagCommentMeta = CJsonWithMeta::fs_FromStringYamlBlock(BlockUserSeparateTagCommentText);
					DMibExpect(JsonUserBlockSeparateTagCommentMeta.f_Yaml().f_LeadingComment(), ==, "# outer leading\n");
					DMibExpect(JsonUserBlockSeparateTagCommentMeta["x"].f_Yaml().f_LeadingComment(), ==, "  # x leading\n");
					DMibExpect(JsonUserBlockSeparateTagCommentMeta["x"].f_Yaml().f_LineComment(), ==, " # x line");
					DMibExpect(JsonUserBlockSeparateTagCommentMeta["x"]["y"].f_Yaml().f_LeadingComment(), ==, "      # y leading\n");
					DMibExpect(JsonUserBlockSeparateTagCommentMeta["x"]["y"].f_Yaml().f_LineComment(), ==, " # y line");
					DMibExpect(JsonUserBlockSeparateTagCommentMeta.f_ToStringYaml(), ==, BlockUserSeparateTagCommentText);
					CJsonWithMeta JsonUserBlockSeparateTagCommentMetaCopy = JsonUserBlockSeparateTagCommentMeta;
					DMibExpect(JsonUserBlockSeparateTagCommentMetaCopy.f_ToStringYaml(), ==, BlockUserSeparateTagCommentText);

					auto EJsonUserBlockSeparateTagCommentMeta = CEJsonWithMeta::fs_FromStringYamlBlock(BlockUserSeparateTagCommentText);
					DMibExpect(EJsonUserBlockSeparateTagCommentMeta.f_IsUserType(), ==, true);
					DMibExpect(EJsonUserBlockSeparateTagCommentMeta.f_UserType().m_Type, ==, "Outer");
					DMibExpect(EJsonUserBlockSeparateTagCommentMeta.f_ToStringYaml(), ==, BlockUserSeparateTagCommentText);
					DMibExpect(CEJsonWithMeta::fs_FromJson(EJsonUserBlockSeparateTagCommentMeta.f_ToJson()).f_ToStringYaml(), ==, BlockUserSeparateTagCommentText);

					auto BlockUserCommentWhitespaceText =
						"                                            # outer leading\n"
						"!Outer\n"
						"                                            # bin leading\n"
						"  bin: !!binary AAECAw==                    # bin line\n"
						"                                            # literal leading\n"
						"\n"
						"  literal:                                  # literal key\n"
						"                                            # date leading\n"
						"    $date: 5                                # date line\n"
						"                                            # x leading\n"
						"  x: !Inner                                 # x line\n"
						"                                            # y leading\n"
						"    y: !!timestamp 2024-01-15T12:00:00Z     # y line\n"
						"\n"
						"\n"
						"                                            # outer trailing\n"
					;
					auto BlockUserCommentWhitespaceCommentMeta = CJsonWithMeta::fs_FromStringYamlBlock(BlockUserCommentWhitespaceText);
					DMibExpect(BlockUserCommentWhitespaceCommentMeta.f_ToStringYaml(), ==, BlockUserCommentWhitespaceText);
					auto BlockUserCommentWhitespaceCommentMetaEJson = CEJsonWithMeta::fs_FromStringYamlBlock(BlockUserCommentWhitespaceText);
					DMibExpect(BlockUserCommentWhitespaceCommentMetaEJson.f_ToStringYaml(), ==, BlockUserCommentWhitespaceText);
					auto BlockUserCommentWhitespaceCommentNoMeta = CJsonWithoutMeta::fs_FromStringYamlBlock(BlockUserCommentWhitespaceText);
					DMibExpect(BlockUserCommentWhitespaceCommentNoMeta.f_ToStringYaml(), !=, BlockUserCommentWhitespaceText);
					auto BlockUserCommentWhitespaceCommentNoMetaEJson = CEJsonWithoutMeta::fs_FromStringYamlBlock(BlockUserCommentWhitespaceText);
					DMibExpect(BlockUserCommentWhitespaceCommentNoMetaEJson.f_ToStringYaml(), !=, BlockUserCommentWhitespaceText);
				};

				DMibTestCategory("YamlMixedTagsProjectToJsonAndEJson")
				{
					auto MixedText =
						"!Outer\n"
						"  list: [!!binary AAECAw==, {$date: 5}]\n"
						"  x: !Inner {literal: {$binary: keep}, y: !!timestamp 2024-01-15T12:00:00Z}\n"
					;

					auto JsonMixed = CJsonWithoutMeta::fs_FromStringYaml(MixedText);
					DMibExpect(JsonMixed.f_IsObject(), ==, true);
					DMibExpect(JsonMixed["x"]["y"].f_String(), ==, "2024-01-15T12:00:00Z");
					DMibExpect(JsonMixed["x"]["literal"]["$binary"].f_String(), ==, "keep");
					DMibExpect(JsonMixed["list"].f_IsArray(), ==, true);
					DMibExpect(JsonMixed["list"][0].f_String(), ==, "AAECAw==");
					DMibExpect(JsonMixed["list"][1]["$date"].f_Integer(), ==, 5);

					auto JsonMixedMeta = CJsonWithMeta::fs_FromStringYaml(MixedText);
					DMibExpect(JsonMixedMeta.f_IsObject(), ==, true);
					DMibExpect(JsonMixedMeta.f_Yaml().f_TagSuffix(), ==, "Outer");
					DMibExpect(JsonMixedMeta["x"].f_Yaml().f_TagSuffix(), ==, "Inner");
					DMibExpect(JsonMixedMeta["x"]["y"].f_String(), ==, "2024-01-15T12:00:00Z");
					DMibExpect(JsonMixedMeta["x"]["y"].f_Yaml().f_TagSuffix(), ==, "timestamp");
					DMibExpect(JsonMixedMeta["x"]["literal"]["$binary"].f_String(), ==, "keep");
					DMibExpect(JsonMixedMeta["list"].f_IsArray(), ==, true);
					DMibExpect(JsonMixedMeta["list"][0].f_String(), ==, "AAECAw==");
					DMibExpect(JsonMixedMeta["list"][0].f_Yaml().f_TagSuffix(), ==, "binary");
					DMibExpect(JsonMixedMeta["list"][1]["$date"].f_Integer(), ==, 5);
					DMibExpect(JsonMixedMeta.f_ToStringYaml(), ==, MixedText);

					auto EJsonMixed = CEJsonWithoutMeta::fs_FromStringYaml(MixedText);
					DMibExpect(EJsonMixed.f_IsUserType(), ==, true);
					DMibExpect(EJsonMixed.f_UserType().m_Type, ==, "Outer");
					DMibExpect(EJsonMixed.f_UserType().m_Value["x"]["$type"].f_String(), ==, "Inner");
					DMibExpect(EJsonMixed.f_UserType().m_Value["x"]["$value"]["y"]["$date"].f_IsInteger(), ==, true);
					DMibExpect(EJsonMixed.f_UserType().m_Value["x"]["$value"]["literal"]["$escape"]["$binary"].f_String(), ==, "keep");
					DMibExpect(EJsonMixed.f_UserType().m_Value["list"].f_IsArray(), ==, true);
					DMibExpect(EJsonMixed.f_UserType().m_Value["list"][0]["$binary"].f_String(), ==, "AAECAw==");
					DMibExpect(EJsonMixed.f_UserType().m_Value["list"][1]["$escape"]["$date"].f_Integer(), ==, 5);

					auto EJsonMixedMeta = CEJsonWithMeta::fs_FromStringYaml(MixedText);
					DMibExpect(EJsonMixedMeta.f_IsUserType(), ==, true);
					DMibExpect(EJsonMixedMeta.f_UserType().m_Type, ==, "Outer");
					DMibExpect(EJsonMixedMeta.f_Yaml().f_TagSuffix(), ==, "Outer");
					DMibExpect(EJsonMixedMeta.f_UserType().m_Value["x"]["$type"].f_String(), ==, "Inner");
					DMibExpect(EJsonMixedMeta.f_UserType().m_Value["x"]["$value"]["y"]["$date"].f_IsInteger(), ==, true);
					DMibExpect(EJsonMixedMeta.f_UserType().m_Value["x"]["$value"]["literal"]["$escape"]["$binary"].f_String(), ==, "keep");
					DMibExpect(EJsonMixedMeta.f_UserType().m_Value["list"].f_IsArray(), ==, true);
					DMibExpect(EJsonMixedMeta.f_UserType().m_Value["list"][0]["$binary"].f_String(), ==, "AAECAw==");
					DMibExpect(EJsonMixedMeta.f_UserType().m_Value["list"][1]["$escape"]["$date"].f_Integer(), ==, 5);
					DMibExpect(EJsonMixedMeta.f_ToStringYaml(), ==, MixedText);
					DMibExpect(CEJsonWithMeta::fs_FromJson(EJsonMixedMeta.f_ToJson()).f_ToStringYaml(), ==, MixedText);
				};

				DMibTestCategory("RegressionScalarEdges")
				{
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow(".5").f_Float(), ==, 0.5);
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("-.5").f_Float(), ==, -0.5);
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("1e+2").f_Float(), ==, 100.0);
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("-1e2").f_Float(), ==, -100.0);

					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("'---'").f_String(), ==, "---");
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("'...'").f_String(), ==, "...");
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYaml("--- {a: 1}\n--- {b: 2}"), fs_MakeParseException("multi-document streams not supported", 2, 1, 11));

					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("\"a\\\n  b\"").f_String(), ==, "ab");
				};

				DMibTestCategory("RegressionTags")
				{
					auto LocalTaggedScalar = CEJsonWithMeta::fs_FromStringYamlFlow("!Thing 42");
					DMibExpect(LocalTaggedScalar.f_IsUserType(), ==, true);
					DMibExpect(LocalTaggedScalar.f_UserType().m_Type, ==, "Thing");
					DMibExpect(LocalTaggedScalar.f_UserType().m_Value.f_IsString(), ==, true);
					DMibExpect(LocalTaggedScalar.f_UserType().m_Value.f_String(), ==, "42");

					auto UnknownCoreTaggedScalar = CEJsonWithMeta::fs_FromStringYamlFlow("!!Foo 42");
					DMibExpect(UnknownCoreTaggedScalar.f_IsUserType(), ==, true);
					DMibExpect(UnknownCoreTaggedScalar.f_UserType().m_Value.f_IsString(), ==, true);
					DMibExpect(UnknownCoreTaggedScalar.f_UserType().m_Value.f_String(), ==, "42");

					auto TaggedMap = CEJsonWithMeta::fs_FromStringYamlBlock("!Thing\n  x: 1\n");
					DMibExpect(TaggedMap.f_IsUserType(), ==, true);
					DMibExpect(TaggedMap.f_UserType().m_Value["x"].f_Integer(), ==, 1);

					auto ExplicitString = CJsonWithMeta::fs_FromStringYamlFlow("!!str \"true\"");
					ExplicitString = "false";
					DMibExpect(ExplicitString.f_Yaml().f_TagSuffix(), ==, "str");
					DMibExpect(ExplicitString.f_Yaml().f_ScalarStyle(), ==, EYamlScalarStyle_DoubleQuoted);

					auto ExplicitBool = CJsonWithMeta::fs_FromStringYamlFlow("!!bool \"true\"");
					ExplicitBool = false;
					DMibExpect(ExplicitBool.f_Yaml().f_TagSuffix(), ==, "bool");
					DMibExpect(ExplicitBool.f_Yaml().f_ScalarStyle(), ==, EYamlScalarStyle_DoubleQuoted);
				};

				DMibTestCategory("RegressionAnchors")
				{
					DMibExpectException
						(
							CJsonWithMeta::fs_FromStringYamlBlock
								(
									"value: &v\n"
									"  x: 1\n"
									"copy: !!map *v\n"
								)
							, fs_MakeParseException("YAML alias node must not specify properties", 3, 13, 26)
						)
					;

					auto DuplicateAnchors = CJsonWithMeta::fs_FromStringYamlFlow("[&d {x: 1}, &d {x: 2}, *d]");
					DMibExpect(DuplicateAnchors[2]["x"].f_Integer(), ==, 2);
					DMibExpect(DuplicateAnchors.f_ToStringYamlFlow(), ==, "[&d {x: 1}, &d {x: 2}, {x: 2}]");

					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("{self: &a {self: *a}}"), fs_MakeParseException("cyclic alias not supported", 1, 20, 19));
				};

				DMibTestCategory("RegressionCommentsAndBlocks")
				{
					auto CommentedKey = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"parent: # c\n"
							"\n"
							"  child: 1\n"
						)
					;
					DMibExpect(CommentedKey["parent"]["child"].f_Integer(), ==, 1);

					auto DedentedComment = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"items:\n"
							"  - a\n"
							"# after\n"
							"next: b\n"
						)
					;
					DMibExpect(DedentedComment["items"].f_Array()[0].f_String(), ==, "a");
					DMibExpect(DedentedComment["next"].f_String(), ==, "b");

					auto BlockScalar = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"text: |+2 # header\n"
							"  hi\n"
							"\n"
						)
					;
					DMibExpect(BlockScalar["text"].f_Yaml().f_ChompIndicator(), ==, '+');
					DMibExpect(BlockScalar["text"].f_Yaml().f_BlockIndentHint(), ==, 2);
					DMibExpect(BlockScalar["text"].f_Yaml().f_LineComment(), ==, " # header");

					auto TaggedBlockScalar = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"text: !Thing |-\n"
							"  hi\n"
						)
					;
					DMibExpect(TaggedBlockScalar.f_ToStringYaml(), ==, "text: !Thing |-\n  hi\n");
				};

				DMibTestCategory("RegressionCompactAndWrappers")
				{
					auto Compact = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"root: a: 1\n"
							"  b: 2\n"
						)
					;
					DMibExpect(Compact["root"].f_IsObject(), ==, true);
					if (Compact["root"].f_IsObject())
					{
						DMibExpect(Compact["root"]["a"].f_IsInteger(), ==, true);
						if (Compact["root"]["a"].f_IsInteger())
							DMibExpect(Compact["root"]["a"].f_Integer(), ==, 1);

						DMibExpect(Compact["root"]["b"].f_IsInteger(), ==, true);
						if (Compact["root"]["b"].f_IsInteger())
							DMibExpect(Compact["root"]["b"].f_Integer(), ==, 2);
					}

					auto CompactSequence = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"items: - a\n"
							"  - b\n"
						)
					;
					DMibExpect(CompactSequence["items"].f_IsArray(), ==, true);
					if (CompactSequence["items"].f_IsArray())
					{
						DMibExpect(CompactSequence["items"][0].f_String(), ==, "a");
						DMibExpect(CompactSequence["items"][1].f_String(), ==, "b");
					}

					auto CommentedCompactSequence = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"items: - a\n"
							"  # keep\n"
							"  - b\n"
						)
					;
					DMibExpect(CommentedCompactSequence["items"].f_Array()[1].f_Yaml().f_LeadingComment(), ==, "  # keep\n");
					DMibExpect(CommentedCompactSequence.f_ToStringYaml(), ==, "items:\n  - a\n  # keep\n  - b\n");

					auto EscapedWrapper = CEJsonWithMeta::fs_FromStringYamlFlow("{$escape: {$date: 5}}");
					DMibExpect(EscapedWrapper.f_IsObject(), ==, true);
					DMibExpect(EscapedWrapper["$escape"]["$date"].f_Integer(), ==, 5);
					DMibExpect(CEJsonWithMeta::fs_FromStringYamlFlow("{$date: \"bad\"}")["$date"].f_String(), ==, "bad");
				};

				DMibTestCategory("RegressionPayloadValidation")
				{
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("!!int abc"), DMibErrorInstance("Invalid YAML !!int scalar"));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("!!int 9223372036854775808"), DMibErrorInstance("Invalid YAML !!int scalar"));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("!!int -9223372036854775809"), DMibErrorInstance("Invalid YAML !!int scalar"));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("9223372036854775808"), DMibErrorInstance("Number out of range"));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("-9223372036854775809"), DMibErrorInstance("Number out of range"));
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("9223372036854775807").f_Integer(), ==, TCLimitsInt<int64>::mc_Max);
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("-9223372036854775808").f_Integer(), ==, TCLimitsInt<int64>::mc_Min);
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("!!int 0x8000000000000000"), DMibErrorInstance("Invalid YAML !!int scalar"));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("!!int -0x8000000000000001"), DMibErrorInstance("Invalid YAML !!int scalar"));
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("!!int 0x7fffffffffffffff").f_Integer(), ==, TCLimitsInt<int64>::mc_Max);
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("!!int -0x8000000000000000").f_Integer(), ==, TCLimitsInt<int64>::mc_Min);
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("!!int 0o1000000000000000000000"), DMibErrorInstance("Invalid YAML !!int scalar"));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("!!int -0o1000000000000000000001"), DMibErrorInstance("Invalid YAML !!int scalar"));
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("!!int 0o777777777777777777777").f_Integer(), ==, TCLimitsInt<int64>::mc_Max);
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("!!int -0o1000000000000000000000").f_Integer(), ==, TCLimitsInt<int64>::mc_Min);
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("!!float xyz"), DMibErrorInstance("Invalid YAML !!float scalar"));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("!!bool maybe"), DMibErrorInstance("Invalid YAML !!bool scalar"));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("!!null oops"), DMibErrorInstance("Invalid YAML !!null scalar"));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("!!str {a: 1}"), DMibErrorInstance("YAML scalar tag requires a scalar value"));
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("!!float .nan").f_Float().f_IsNan(), ==, true);
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("!!null ").f_IsNull(), ==, true);
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("!!null null").f_IsNull(), ==, true);
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("!!bool FALSE").f_Boolean(), ==, false);
				};

				DMibTestCategory("RegressionDirectives")
				{
					auto WithComment = CJsonWithoutMeta::fs_FromStringYaml("%YAML 1.2 # ok\n--- 1");
					DMibExpect(WithComment.f_Integer(), ==, 1);

					DMibExpectException(CJsonWithoutMeta::fs_FromStringYaml("%YAML 1.3\n--- 1"), fs_MakeParseException("Unsupported YAML directive", 1, 1, 0));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYaml("%TAG !e! tag:example, junk\n--- 1"), fs_MakeParseException("Invalid YAML %TAG directive", 1, 1, 0));
				};

				DMibTestCategory("RegressionVerbatimTag")
				{
					auto Verbatim = CEJsonWithMeta::fs_FromStringYamlFlow("!<tag:foo,2024:Bar> 42");
					DMibExpect(Verbatim.f_IsUserType(), ==, true);
					DMibExpect(Verbatim.f_UserType().m_Type, ==, "tag:foo,2024:Bar");
					DMibExpect(Verbatim.f_Yaml().f_TagResolved(), ==, "tag:foo,2024:Bar");
					DMibExpect(Verbatim.f_ToStringYamlFlow().f_Find("!<tag:foo,2024:Bar>"), >=, 0);
				};

				DMibTestCategory("RegressionDocumentMarkerSeparation")
				{
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("'---'").f_String(), ==, "---");
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("'...'").f_String(), ==, "...");
					auto Plain = CJsonWithoutMeta::fs_FromStringYamlFlow("---hello");
					DMibExpect(Plain.f_String(), ==, "---hello");
					auto PlainDots = CJsonWithoutMeta::fs_FromStringYamlFlow("...world");
					DMibExpect(PlainDots.f_String(), ==, "...world");
				};

				DMibTestCategory("RegressionPlainScalarFold")
				{
					auto Folded = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"key: value\n"
							"  continued\n"
						)
					;
					DMibExpect(Folded["key"].f_String(), ==, "value continued");
				};

				DMibTestCategory("RegressionQuotedScalarFold")
				{
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("\"hello\n  world\"").f_String(), ==, "hello world");
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("'hello\n  world'").f_String(), ==, "hello world");
				};

				DMibTestCategory("RegressionQuotedKeyColon")
				{
					auto Mapping = CJsonWithMeta::fs_FromStringYamlBlock("\"a: b\": value\n");
					DMibExpect(Mapping.f_IsObject(), ==, true);
					DMibExpect(Mapping["a: b"].f_String(), ==, "value");

					auto SingleQuoted = CJsonWithMeta::fs_FromStringYamlBlock("'a: b': value\n");
					DMibExpect(SingleQuoted.f_IsObject(), ==, true);
					DMibExpect(SingleQuoted["a: b"].f_String(), ==, "value");
				};

				DMibTestCategory("RegressionDashPrefixedScalar")
				{
					auto Json = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"name: -value\n"
						)
					;
					DMibExpect(Json["name"].f_IsString(), ==, true);
					DMibExpect(Json["name"].f_String(), ==, "-value");
				};

				DMibTestCategory("RegressionFloatExponents")
				{
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("1.5e-3").f_Float(), ==, 0.0015);
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("1.5E+10").f_Float(), ==, 1.5e10);
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("-1.5e+2").f_Float(), ==, -150.0);
				};

				DMibTestCategory("RegressionIntegerStrictness")
				{
					auto Json = CJsonWithMeta::fs_FromStringYamlBlock("a: 12abc\n");
					DMibExpect(Json["a"].f_IsString(), ==, true);
					DMibExpect(Json["a"].f_String(), ==, "12abc");
				};

				DMibTestCategory("RegressionSurrogateEscapes")
				{
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("\"\\uD83D\\uDE00\"").f_String(), ==, "😀");
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("\"\\uD83D\""), fs_MakeParseException("Missing YAML low surrogate escape", 1, 8, 7));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("\"\\uDC00\""), fs_MakeParseException("Unexpected YAML low surrogate escape", 1, 8, 7));
				};

				DMibTestCategory("RegressionTimestampValidation")
				{
					DMibExpectException(CEJsonWithMeta::fs_FromStringYamlFlow("!!timestamp 2024-01-15 14:30:00 +25:00"), DMibErrorInstance("YAML timestamp timezone hour out of range"));
					DMibExpectException(CEJsonWithMeta::fs_FromStringYamlFlow("!!timestamp 2024-01-15 14:30:00 +02:75"), DMibErrorInstance("YAML timestamp timezone minute out of range"));

					auto RoundsToNextSecond = NTime::CTimeConvert::fs_CreateTimeIntFrac
						(
							2024
							, 1
							, 15
							, 12
							, 0
							, 59
							, NTime::NPrivate::CConst::mc_FractionDividend - 1
						)
					;
					DMibExpect(fg_FormatYamlTimestamp(RoundsToNextSecond), ==, "2024-01-15T12:01:00Z");

					auto NineDigitFraction = CEJsonWithMeta::fs_FromStringYamlFlow("!!timestamp 2024-01-15T12:00:00.999999999Z");
					DMibExpect(fg_FormatYamlTimestamp(NineDigitFraction.f_Date()), ==, "2024-01-15T12:00:00.999999999Z");

					auto TooManyFractionDigits = CEJsonWithMeta::fs_FromStringYamlFlow("!!timestamp 2024-01-15T12:00:00.9999999999Z");
					DMibExpect(fg_FormatYamlTimestamp(TooManyFractionDigits.f_Date()), ==, "2024-01-15T12:00:00.999999999Z");
				};

				DMibTestCategory("RegressionFoldedMoreIndented")
				{
					auto Folded = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"text: >\n"
							"  hello\n"
							"    world\n"
							"  end\n"
						)
					;
					DMibExpect(Folded["text"].f_String().f_Find("world"), >=, 0);
					DMibExpect(Folded["text"].f_String().f_Find("\n  world"), >=, 0);
					DMibExpect(Folded["text"].f_String()[Folded["text"].f_String().f_GetLen() - 1], ==, '\n');
				};

				DMibTestCategory("RegressionBlockScalarChomp")
				{
					auto Strip = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"text: |-\n"
							"  hi\n"
							"  there\n"
						)
					;
					DMibExpect(Strip["text"].f_String(), ==, "hi\nthere");
					DMibExpect(Strip["text"].f_Yaml().f_ChompIndicator(), ==, '-');

					auto Clip = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"text: |\n"
							"  hi\n"
							"\n"
							"\n"
						)
					;
					DMibExpect(Clip["text"].f_String(), ==, "hi\n");

					auto Keep = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"text: |+\n"
							"  hi\n"
							"\n"
							"\n"
						)
					;
					DMibExpect(Keep["text"].f_String(), ==, "hi\n\n\n");
					DMibExpect(Keep["text"].f_Yaml().f_ChompIndicator(), ==, '+');
				};

				DMibTestCategory("RegressionComplexKeyDetection")
				{
					auto Json = CJsonWithMeta::fs_FromStringYamlBlock("?abc: 1\n");
					DMibExpect(Json.f_IsObject(), ==, true);
					DMibExpect(Json["?abc"].f_Integer(), ==, 1);
				};

				DMibTestCategory("RegressionTaggedDoesNotCollapseWrapper")
				{
					auto OriginalText = "!Thing {$date: 5}";
					auto Tagged = CEJsonWithMeta::fs_FromStringYamlFlow(OriginalText);
					DMibExpect(Tagged.f_IsUserType(), ==, true);
					DMibExpect(Tagged.f_UserType().m_Type, ==, "Thing");
					DMibExpect(Tagged.f_IsDate(), ==, false);

					auto Round = Tagged.f_ToStringYamlFlow();
					DMibExpect(Round, ==, OriginalText);

					auto Reparsed = CEJsonWithMeta::fs_FromStringYamlFlow(Round);
					DMibExpect(Tagged, ==, Reparsed);
					DMibExpect(Reparsed.f_IsUserType(), ==, true);
					DMibExpect(Reparsed.f_UserType().m_Type, ==, "Thing");
					DMibExpect(Reparsed.f_ToStringYamlFlow(), ==, Round);

					auto FlowSequenceText = "!Thing [{$date: 5}]";
					auto FlowSequence = CEJsonWithMeta::fs_FromStringYamlFlow(FlowSequenceText);
					DMibExpect(FlowSequence.f_IsUserType(), ==, true);
					DMibExpect(FlowSequence.f_UserType().m_Value.f_IsArray(), ==, true);
					DMibExpect(FlowSequence.f_UserType().m_Value[0].f_IsObject(), ==, true);

					auto FlowSequenceRound = FlowSequence.f_ToStringYamlFlow();
					DMibExpect(FlowSequenceRound, ==, FlowSequenceText);

					if (FlowSequenceRound == FlowSequenceText)
					{
						auto FlowSequenceReparsed = CEJsonWithMeta::fs_FromStringYaml(FlowSequenceRound);
						DMibExpect(FlowSequence, ==, FlowSequenceReparsed);
						DMibExpect(FlowSequenceReparsed.f_ToStringYamlFlow(), ==, FlowSequenceRound);
					}

					auto BlockSequenceText =
						"!Thing\n"
						"- {$date: 5}\n"
					;

					auto BlockSequence = CEJsonWithMeta::fs_FromStringYaml(BlockSequenceText);
					DMibExpect(BlockSequence.f_IsUserType(), ==, true);
					DMibExpect(BlockSequence.f_UserType().m_Value.f_IsArray(), ==, true);
					DMibExpect(BlockSequence.f_UserType().m_Value[0].f_IsObject(), ==, true);

					auto BlockSequenceRound = BlockSequence.f_ToStringYaml();
					DMibExpect(BlockSequenceRound, ==, BlockSequenceText);

					auto BlockSequenceReparsed = CEJsonWithMeta::fs_FromStringYaml(BlockSequenceRound);
					DMibExpect(BlockSequence, ==, BlockSequenceReparsed);
					DMibExpect(BlockSequenceReparsed.f_ToStringYamlFlow(), ==, "!Thing [{$date: 5}]");
				};

				DMibTestCategory("EscapeRoundtrips")
				{
					auto OriginalText = "!Thing {$escape: 5}";
					auto Tagged = CEJsonWithMeta::fs_FromStringYamlFlow(OriginalText);
					auto Round = Tagged.f_ToStringYamlFlow();
					DMibExpect(Round, ==, OriginalText);
					auto Reparsed = CEJsonWithMeta::fs_FromStringYamlFlow(Round);
					DMibExpect(Tagged, ==, Reparsed);
				};

				DMibTestCategory("RegressionTaggedDoesNotCollapseWrapperNoMeta")
				{
					auto OriginalText = "!Thing {$date: 5}";
					auto Tagged = CEJsonWithoutMeta::fs_FromStringYamlFlow(OriginalText);
					DMibExpect(Tagged.f_IsUserType(), ==, true);
					DMibExpect(Tagged.f_UserType().m_Type, ==, "Thing");
					DMibExpect(Tagged.f_IsDate(), ==, false);

					auto Round = Tagged.f_ToStringYamlFlow();
					DMibExpect(Round, ==, OriginalText);

					auto Reparsed = CEJsonWithoutMeta::fs_FromStringYamlFlow(Round);
					DMibExpect(Tagged, ==, Reparsed);
					DMibExpect(Reparsed.f_IsUserType(), ==, true);
					DMibExpect(Reparsed.f_UserType().m_Type, ==, "Thing");
					DMibExpect(Reparsed.f_ToStringYamlFlow(), ==, Round);

					auto FlowSequenceText = "!Thing [{$date: 5}]";
					auto FlowSequence = CEJsonWithoutMeta::fs_FromStringYamlFlow(FlowSequenceText);
					DMibExpect(FlowSequence.f_IsUserType(), ==, true);
					DMibExpect(FlowSequence.f_UserType().m_Value.f_IsArray(), ==, true);
					DMibExpect(FlowSequence.f_UserType().m_Value[0].f_IsObject(), ==, true);

					auto FlowSequenceRound = FlowSequence.f_ToStringYamlFlow();
					DMibExpect(FlowSequenceRound, ==, FlowSequenceText);

					if (FlowSequenceRound == FlowSequenceText)
					{
						auto FlowSequenceReparsed = CEJsonWithoutMeta::fs_FromStringYaml(FlowSequenceRound);
						DMibExpect(FlowSequence, ==, FlowSequenceReparsed);
						DMibExpect(FlowSequenceReparsed.f_ToStringYamlFlow(), ==, FlowSequenceRound);
					}

					auto BlockSequenceText =
						"!Thing\n"
						"- {$date: 5}\n"
					;

					auto BlockSequence = CEJsonWithoutMeta::fs_FromStringYaml(BlockSequenceText);
					DMibExpect(BlockSequence.f_IsUserType(), ==, true);
					DMibExpect(BlockSequence.f_UserType().m_Value.f_IsArray(), ==, true);
					DMibExpect(BlockSequence.f_UserType().m_Value[0].f_IsObject(), ==, true);

					auto BlockSequenceRound = BlockSequence.f_ToStringYaml();
					DMibExpect(BlockSequenceRound, ==, "!Thing [{$date: 5}]\n");

					auto BlockSequenceReparsed = CEJsonWithoutMeta::fs_FromStringYaml(BlockSequenceRound);
					DMibExpect(BlockSequence, ==, BlockSequenceReparsed);
					DMibExpect(BlockSequenceReparsed.f_ToStringYaml(), ==, BlockSequenceRound);

					auto LiteralTypeText = "!Thing {x: {$escape: {$type: Literal, $value: 5}}}";
					auto LiteralType = CEJsonWithoutMeta::fs_FromStringYamlFlow(LiteralTypeText);
					auto LiteralTypeRound = LiteralType.f_ToStringYamlFlow();
					DMibExpect(LiteralTypeRound, ==, LiteralTypeText);
					DMibExpect(LiteralType, ==, CEJsonWithoutMeta::fs_FromStringYamlFlow(LiteralTypeRound));
				};

				DMibTestCategory("EscapeRoundwripsNoMeta")
				{
					auto OriginalText = "!Thing {$escape: 5}";
					auto Tagged = CEJsonWithoutMeta::fs_FromStringYamlFlow(OriginalText);
					auto Round = Tagged.f_ToStringYamlFlow();
					DMibExpect(Round, ==, OriginalText);
					auto Reparsed = CEJsonWithoutMeta::fs_FromStringYamlFlow(Round);
					DMibExpect(Tagged, ==, Reparsed);
				};

				DMibTestCategory("RegressionTrailingComment")
				{
					auto Json = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"a: 1\n"
							"b: 2\n"
							"# trailing\n"
						)
					;
					DMibExpect
						(
							Json.f_ToStringYaml()
							, ==
							, "a: 1\n"
							"b: 2\n"
							"# trailing\n"
						)
					;

					auto TrailingBeforeBlank = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"a: 1\n"
							"# trailing a\n"
							"\n"
							"b: 2\n"
						)
					;
					DMibExpect(TrailingBeforeBlank["a"].f_Yaml().f_TrailingComment(), ==, "# trailing a\n\n");
					DMibExpect(TrailingBeforeBlank["b"].f_Yaml().f_LeadingComment(), ==, "");
					DMibExpect
						(
							TrailingBeforeBlank.f_ToStringYaml()
							, ==
							, "a: 1\n"
							"# trailing a\n"
							"\n"
							"b: 2\n"
						)
					;

					auto RootScalarWithComments = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"# c\n"
							"1 # x\n"
						)
					;
					DMibExpect
						(
							RootScalarWithComments.f_ToStringYaml()
							, ==
							, "# c\n"
							"1 # x\n"
						)
					;

					auto TrailingBeforeBlankAndLeading = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"a: 1\n"
							"# trailing a\n"
							"\n"
							"# leading b\n"
							"b: 2\n"
						)
					;
					DMibExpect(TrailingBeforeBlankAndLeading["a"].f_Yaml().f_TrailingComment(), ==, "# trailing a\n\n");
					DMibExpect(TrailingBeforeBlankAndLeading["b"].f_Yaml().f_LeadingComment(), ==, "# leading b\n");
					DMibExpect
						(
							TrailingBeforeBlankAndLeading.f_ToStringYaml()
							, ==
							, "a: 1\n"
							"# trailing a\n"
							"\n"
							"# leading b\n"
							"b: 2\n"
						)
					;

					auto TrailingMiddleAndLeading = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"a: 1\n"
							"# trailing a\n"
							"\n"
							"# middle belongs to a\n"
							"\n"
							"# leading b\n"
							"b: 2\n"
						)
					;
					DMibExpect(TrailingMiddleAndLeading["a"].f_Yaml().f_TrailingComment(), ==, "# trailing a\n\n# middle belongs to a\n\n");
					DMibExpect(TrailingMiddleAndLeading["b"].f_Yaml().f_LeadingComment(), ==, "# leading b\n");
					DMibExpect
						(
							TrailingMiddleAndLeading.f_ToStringYaml()
							, ==
							, "a: 1\n"
							"# trailing a\n"
							"\n"
							"# middle belongs to a\n"
							"\n"
							"# leading b\n"
							"b: 2\n"
						)
					;
				};

				DMibTestCategory("RegressionHexEscapes")
				{
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("\"\\x41\"").f_String(), ==, "A");
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("\"\\U0001F600\"").f_String(), ==, "😀");
					DMibExpect(CJsonWithoutMeta::fs_FromStringYamlFlow("\"\\a\\b\\v\\f\"").f_String(), ==, "\a\b\v\f");
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("\"\\xZZ\""), fs_MakeParseException("Invalid YAML hex escape", 1, 4, 3));
				};

				DMibTestCategory("RegressionControlEmission")
				{
					CJsonWithMeta Value;
					NStr::CStr Raw;
					Raw += '\x01';
					Raw += "hello";
					Value = Raw;
					auto Emitted = Value.f_ToStringYamlFlow();
					DMibExpect(Emitted.f_Find("\\x01"), >=, 0);

					auto RoundTripped = CJsonWithMeta::fs_FromStringYamlFlow(Emitted);
					DMibExpect(RoundTripped.f_String(), ==, Raw);

					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("\"\\0\""), fs_MakeParseException("Null characters not supported in this implementation", 1, 3, 2));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("\"\\x00\""), fs_MakeParseException("Null characters not supported in this implementation", 1, 6, 5));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("\"\\u0000\""), fs_MakeParseException("Null characters not supported in this implementation", 1, 8, 7));
					DMibExpectException(CJsonWithoutMeta::fs_FromStringYamlFlow("\"\\U00000000\""), fs_MakeParseException("Null characters not supported in this implementation", 1, 12, 11));

					DMibExpect(CJsonWithoutMeta::template fs_FromStringYaml<CYamlFlowConvertNullToSpace>("\"\\0\"").f_String(), ==, " ");
					DMibExpect(CJsonWithoutMeta::template fs_FromStringYaml<CYamlFlowConvertNullToSpace>("\"\\x00\"").f_String(), ==, " ");
					DMibExpect(CJsonWithoutMeta::template fs_FromStringYaml<CYamlFlowConvertNullToSpace>("\"\\u0000\"").f_String(), ==, " ");
					DMibExpect(CJsonWithoutMeta::template fs_FromStringYaml<CYamlFlowConvertNullToSpace>("\"\\U00000000\"").f_String(), ==, " ");
				};

				DMibTestCategory("RegressionKeyScalarStyle")
				{
					auto Json = CJsonWithMeta::fs_FromStringYamlBlock("'42': ok\n");
					auto iEntry = Json.f_Object().f_OrderedIterator();
					DMibAssertTrue(iEntry);
					if (iEntry)
					{
						DMibExpect(iEntry->f_KeyYaml().f_ScalarStyle(), ==, EYamlScalarStyle_SingleQuoted);
						DMibExpect(Json.f_ToStringYaml(), ==, "'42': ok\n");
					}

					auto DoubleKey = CJsonWithMeta::fs_FromStringYamlBlock("\"x\": 1\n");
					auto iDouble = DoubleKey.f_Object().f_OrderedIterator();
					DMibAssertTrue(iDouble);
					if (iDouble)
						DMibExpect(iDouble->f_KeyYaml().f_ScalarStyle(), ==, EYamlScalarStyle_DoubleQuoted);
				};

				DMibTestCategory("RegressionEmptyValueIsNull")
				{
					auto Json = CJsonWithoutMeta::fs_FromStringYamlBlock("key:\n");
					DMibExpect(Json.f_IsObject(), ==, true);
					DMibExpect(Json["key"].f_IsNull(), ==, true);

					auto Tilde = CJsonWithoutMeta::fs_FromStringYamlFlow("~");
					DMibExpect(Tilde.f_IsNull(), ==, true);
				};

				DMibTestCategory("RegressionScalarStyleRoundTrip")
				{
					auto Single = CJsonWithMeta::fs_FromStringYamlFlow("'plain'");
					DMibExpect(Single.f_Yaml().f_ScalarStyle(), ==, EYamlScalarStyle_SingleQuoted);
					DMibExpect(Single.f_ToStringYamlFlow(), ==, "'plain'");

					auto Double = CJsonWithMeta::fs_FromStringYamlFlow("\"plain\"");
					DMibExpect(Double.f_Yaml().f_ScalarStyle(), ==, EYamlScalarStyle_DoubleQuoted);
					DMibExpect(Double.f_ToStringYamlFlow(), ==, "\"plain\"");

					auto Literal = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"text: |\n"
							"  hi\n"
						)
					;
					DMibExpect(Literal["text"].f_Yaml().f_ScalarStyle(), ==, EYamlScalarStyle_Literal);
					DMibExpect(Literal.f_ToStringYaml().f_Find("|"), >=, 0);
				};

				DMibTestCategory("RegressionAnchorTagOnAlias")
				{
					DMibExpectException
						(
							CJsonWithMeta::fs_FromStringYamlBlock
								(
									"value: &v\n"
									"  x: 1\n"
									"copy: !!map *v\n"
								)
							, fs_MakeParseException("YAML alias node must not specify properties", 3, 13, 26)
						)
					;
				};

				DMibTestCategory("RegressionAnchorOnSeparateLine")
				{
					auto AnchorOnLine = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"defaults: &d\n"
							"  x: 1\n"
							"copy: *d\n"
						)
					;
					DMibExpect(AnchorOnLine["copy"]["x"].f_Integer(), ==, 1);
					DMibExpect(AnchorOnLine["copy"].f_Yaml().f_Alias(), ==, "d");
				};

				DMibTestCategory("MixedBlockMappingWithFlowValue")
				{
					auto FlowMap = CJsonWithMeta::fs_FromStringYaml
						(
							"name: test\n"
							"point: {x: 1, y: 2}\n"
							"enabled: true\n"
						)
					;
					DMibExpect(FlowMap["name"].f_String(), ==, "test");
					DMibExpect(FlowMap["point"].f_IsObject(), ==, true);
					DMibExpect(FlowMap["point"]["x"].f_Integer(), ==, 1);
					DMibExpect(FlowMap["point"]["y"].f_Integer(), ==, 2);
					DMibExpect(FlowMap["point"].f_Yaml().f_NodeStyle(), ==, EYamlNodeStyle_Flow);
					DMibExpect(FlowMap["enabled"].f_Boolean(), ==, true);
					DMibExpect(FlowMap.f_Yaml().f_NodeStyle(), ==, EYamlNodeStyle_Block);
					if constexpr (tf_bOrdered)
						DMibExpect(FlowMap.f_ToStringYaml(), ==, "name: test\npoint: {x: 1, y: 2}\nenabled: true\n");
					else
						DMibExpect(FlowMap.f_ToStringYaml(), ==, "enabled: true\nname: test\npoint: {x: 1, y: 2}\n");

					auto FlowArr = CJsonWithMeta::fs_FromStringYaml
						(
							"name: test\n"
							"items: [1, 2, 3]\n"
						)
					;
					DMibExpect(FlowArr["items"].f_IsArray(), ==, true);
					DMibExpect(FlowArr["items"][0].f_Integer(), ==, 1);
					DMibExpect(FlowArr["items"][2].f_Integer(), ==, 3);
					DMibExpect(FlowArr["items"].f_Yaml().f_NodeStyle(), ==, EYamlNodeStyle_Flow);
					if constexpr (tf_bOrdered)
						DMibExpect(FlowArr.f_ToStringYaml(), ==, "name: test\nitems: [1, 2, 3]\n");
					else
						DMibExpect(FlowArr.f_ToStringYaml(), ==, "items: [1, 2, 3]\nname: test\n");
				};

				DMibTestCategory("MixedBlockSequenceWithFlowElements")
				{
					auto Json = CJsonWithMeta::fs_FromStringYaml
						(
							"- {x: 1, y: 2}\n"
							"- {x: 3, y: 4}\n"
						)
					;
					DMibExpect(Json.f_IsArray(), ==, true);
					DMibExpect(Json[0].f_IsObject(), ==, true);
					DMibExpect(Json[0]["x"].f_Integer(), ==, 1);
					DMibExpect(Json[1]["y"].f_Integer(), ==, 4);
					DMibExpect(Json.f_Yaml().f_NodeStyle(), ==, EYamlNodeStyle_Block);
					DMibExpect(Json[0].f_Yaml().f_NodeStyle(), ==, EYamlNodeStyle_Flow);
					DMibExpect(Json.f_ToStringYaml(), ==, "- {x: 1, y: 2}\n- {x: 3, y: 4}\n");

					auto NestedFlowArr = CJsonWithMeta::fs_FromStringYaml
						(
							"- [1, 2]\n"
							"- [3, 4]\n"
						)
					;
					DMibExpect(NestedFlowArr[0].f_IsArray(), ==, true);
					DMibExpect(NestedFlowArr[0][1].f_Integer(), ==, 2);
					DMibExpect(NestedFlowArr[1][0].f_Integer(), ==, 3);
					DMibExpect(NestedFlowArr[0].f_Yaml().f_NodeStyle(), ==, EYamlNodeStyle_Flow);
					DMibExpect(NestedFlowArr.f_ToStringYaml(), ==, "- [1, 2]\n- [3, 4]\n");
				};

				DMibTestCategory("MixedFlowContainingBlockComments")
				{
					auto Json = CJsonWithMeta::fs_FromStringYaml
						(
							"# header\n"
							"point: {x: 1, y: 2} # inline\n"
							"items: [1, 2]\n"
						)
					;
					DMibExpect(Json.f_Yaml().f_LeadingComment(), ==, "# header\n");
					DMibExpect(Json["point"].f_Yaml().f_LineComment(), ==, " # inline");
					if constexpr (tf_bOrdered)
						DMibExpect(Json.f_ToStringYaml(), ==, "# header\npoint: {x: 1, y: 2} # inline\nitems: [1, 2]\n");
					else
						DMibExpect(Json.f_ToStringYaml(), ==, "# header\nitems: [1, 2]\npoint: {x: 1, y: 2} # inline\n");
				};

				DMibTestCategory("FlowRoundTripWithComment")
				{
					auto Object = CJsonWithMeta::fs_FromStringYamlFlow("{a: 1, b: 2}");
					DMibExpect(Object.f_ToStringYamlFlow(), ==, "{a: 1, b: 2}");

					auto Array = CJsonWithMeta::fs_FromStringYamlFlow("[1, 2, 3]");
					DMibExpect(Array.f_ToStringYamlFlow(), ==, "[1, 2, 3]");

					auto Nested = CJsonWithMeta::fs_FromStringYamlFlow("{a: [1, 2], b: {c: 3}}");
					DMibExpect(Nested.f_ToStringYamlFlow(), ==, "{a: [1, 2], b: {c: 3}}");
				};

				DMibTestCategory("DocumentTrailingCommentByteExact")
				{
					auto Mapping = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"a: 1\n"
							"b: 2\n"
							"# trailing\n"
						)
					;
					DMibExpect
						(
							Mapping.f_ToStringYaml()
							, ==
							, "a: 1\n"
							  "b: 2\n"
							  "# trailing\n"
						)
					;

					auto AfterSequence = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"items:\n"
							"  - one\n"
							"  - two\n"
							"# trailing\n"
						)
					;
					DMibExpect
						(
							AfterSequence.f_ToStringYaml()
							, ==
							, "items:\n"
							  "  - one\n"
							  "  - two\n"
							  "# trailing\n"
						)
					;
				};

				DMibTestCategory("FlowValueOnSeparateLineUnderBlockKey")
				{
					auto Json = CJsonWithMeta::fs_FromStringYaml
						(
							"key:\n"
							"  {a: 1, b: 2}\n"
						)
					;
					DMibExpect(Json["key"]["a"].f_Integer(), ==, 1);
					DMibExpect(Json["key"]["b"].f_Integer(), ==, 2);
				};

				DMibTestCategory("RegressionNestedTagsPlainJson")
				{
					auto NestedSeq = CJsonWithMeta::fs_FromStringYamlFlow("!Outer {x: !!seq [1, 2]}");
					DMibExpect(NestedSeq.f_IsObject(), ==, true);
					DMibExpect(NestedSeq.f_Yaml().f_TagSuffix(), ==, "Outer");
					DMibExpect(NestedSeq["x"].f_IsArray(), ==, true);
					DMibExpect(NestedSeq["x"].f_Yaml().f_TagSuffix(), ==, "seq");

					auto NestedMap = CJsonWithMeta::fs_FromStringYamlFlow("!Outer {x: !!map {y: 1}}");
					DMibExpect(NestedMap["x"].f_Yaml().f_TagSuffix(), ==, "map");
					DMibExpect(NestedMap["x"]["y"].f_Integer(), ==, 1);

					auto NestedUser = CJsonWithMeta::fs_FromStringYamlFlow("!Outer {x: !Inner {y: 1}}");
					DMibExpect(NestedUser.f_Yaml().f_TagSuffix(), ==, "Outer");
					DMibExpect(NestedUser["x"].f_Yaml().f_TagSuffix(), ==, "Inner");
					DMibExpect(NestedUser["x"]["y"].f_Integer(), ==, 1);
				};

				DMibTestCategory("RegressionNestedTagsEJson")
				{
					auto NestedUser = CEJsonWithMeta::fs_FromStringYamlFlow("!Outer {x: !Inner {y: 1}}");
					DMibExpect(NestedUser.f_IsUserType(), ==, true);
					DMibExpect(NestedUser.f_UserType().m_Type, ==, "Outer");
					auto Round = NestedUser.f_ToStringYamlFlow();
					DMibExpect(Round, ==, "!Outer {x: !Inner {y: 1}}");

					auto Reparsed = CEJsonWithMeta::fs_FromStringYamlFlow(Round);
					DMibExpect(Reparsed.f_ToStringYamlFlow(), ==, "!Outer {x: !Inner {y: 1}}");

					auto NestedTimestamp = CEJsonWithMeta::fs_FromStringYamlFlow("!Outer {x: !!timestamp 2024-01-15T12:00:00Z}");
					DMibExpect(NestedTimestamp.f_IsUserType(), ==, true);
					auto TsRound = NestedTimestamp.f_ToStringYamlFlow();
					DMibExpect(TsRound, ==, "!Outer {x: !!timestamp 2024-01-15T12:00:00Z}");

					auto NestedBinary = CEJsonWithMeta::fs_FromStringYamlFlow("!Outer {x: !!binary AAECAw==}");
					DMibExpect(NestedBinary.f_IsUserType(), ==, true);
					auto BinRound = NestedBinary.f_ToStringYamlFlow();
					DMibExpect(BinRound.f_Find("!!binary"), >=, 0);

					DMibExpect(CEJsonWithMeta::fs_FromStringYamlFlow("!Outer {x: !Inner {$escape: 1}}").f_ToStringYamlFlow(), ==, "!Outer {x: !Inner {$escape: 1}}");
					DMibExpect
						(
							CEJsonWithMeta::fs_FromStringYamlFlow("!Outer {x: !Inner {$escape: !Inner {$escape: 1}}}").f_ToStringYamlFlow()
							, ==
							, "!Outer {x: !Inner {$escape: !Inner {$escape: 1}}}"
						)
					;
				};

				DMibTestCategory("RegressionNestedTagsEJsonNoMeta")
				{
					auto NestedUser = CEJsonWithoutMeta::fs_FromStringYamlFlow("!Outer {x: !Inner {y: 1}}");
					DMibExpect(NestedUser.f_IsUserType(), ==, true);
					DMibExpect(NestedUser.f_UserType().m_Type, ==, "Outer");
					auto Round = NestedUser.f_ToStringYamlFlow();
					DMibExpect(Round, ==, "!Outer {x: !Inner {y: 1}}");

					auto Reparsed = CEJsonWithoutMeta::fs_FromStringYamlFlow(Round);
					DMibExpect(Reparsed.f_ToStringYamlFlow(), ==, "!Outer {x: !Inner {y: 1}}");

					auto NestedTimestamp = CEJsonWithoutMeta::fs_FromStringYamlFlow("!Outer {x: !!timestamp 2024-01-15T12:00:00Z}");
					DMibExpect(NestedTimestamp.f_IsUserType(), ==, true);
					auto TsRound = NestedTimestamp.f_ToStringYamlFlow();
					DMibExpect(TsRound, ==, "!Outer {x: !!timestamp 2024-01-15T12:00:00Z}");

					auto NestedBinary = CEJsonWithoutMeta::fs_FromStringYamlFlow("!Outer {x: !!binary AAECAw==}");
					DMibExpect(NestedBinary.f_IsUserType(), ==, true);
					auto BinRound = NestedBinary.f_ToStringYamlFlow();
					DMibExpect(BinRound, ==, "!Outer {x: !!binary AAECAw==}");

					DMibExpect(CEJsonWithoutMeta::fs_FromStringYamlFlow("!Outer {x: !Inner {$escape: 1}}").f_ToStringYamlFlow(), ==, "!Outer {x: !Inner {$escape: 1}}");
					DMibExpect
						(
							CEJsonWithoutMeta::fs_FromStringYamlFlow("!Outer {x: !Inner {$escape: !Inner {$escape: 1}}}").f_ToStringYamlFlow()
							, ==
							, "!Outer {x: !Inner {$escape: !Inner {$escape: 1}}}"
						)
					;
				};

				DMibTestCategory("RegressionTypeValueDoesNotCollapse")
				{
					auto Object = CEJsonWithMeta::fs_FromStringYamlFlow("{$type: \"Thing\", $value: {x: 1, y: 2}}");
					DMibExpect(Object.f_IsObject(), ==, true);
					DMibExpect(Object["$type"].f_String(), ==, "Thing");
					DMibExpect(Object["$value"]["x"].f_Integer(), ==, 1);
					DMibExpect(Object["$value"]["y"].f_Integer(), ==, 2);

					auto Array = CEJsonWithMeta::fs_FromStringYamlFlow("{$type: \"Thing\", $value: [1, 2, 3]}");
					DMibExpect(Array.f_IsObject(), ==, true);
					DMibExpect(Array["$type"].f_String(), ==, "Thing");
					DMibExpect(Array["$value"].f_IsArray(), ==, true);
					DMibExpect(Array["$value"][0].f_Integer(), ==, 1);
					DMibExpect(Array["$value"][2].f_Integer(), ==, 3);

					auto Scalar = CEJsonWithMeta::fs_FromStringYamlFlow("{$type: \"Thing\", $value: 42}");
					DMibExpect(Scalar.f_IsObject(), ==, true);
					DMibExpect(Scalar["$type"].f_String(), ==, "Thing");
					DMibExpect(Scalar["$value"].f_Integer(), ==, 42);

					auto Reversed = CEJsonWithMeta::fs_FromStringYamlFlow("{$value: \"hi\", $type: \"Thing\"}");
					DMibExpect(Reversed.f_IsObject(), ==, true);
					DMibExpect(Reversed["$type"].f_String(), ==, "Thing");
					DMibExpect(Reversed["$value"].f_String(), ==, "hi");

					auto Reparsed = CEJsonWithMeta::fs_FromStringYamlFlow(Object.f_ToStringYamlFlow());
					DMibExpect(Reparsed.f_IsObject(), ==, true);
					DMibExpect(Reparsed["$type"].f_String(), ==, "Thing");
					DMibExpect(Reparsed["$value"]["x"].f_Integer(), ==, 1);
					DMibExpect(Reparsed["$value"]["y"].f_Integer(), ==, 2);
				};

				DMibTestCategory("ComplexKeyRejected")
				{
					DMibExpectException
						(
							CJsonWithoutMeta::fs_FromStringYamlBlock
								(
									"key: 1\n"
									"? - one\n"
									": value\n"
								)
							, fs_MakeParseException("complex YAML keys not supported", 2, 3, 9)
						)
					;
					DMibExpectException
						(
							CJsonWithoutMeta::fs_FromStringYamlBlock
								(
									"key: 1\n"
									"? [1, 2]\n"
									": value\n"
								)
							, fs_MakeParseException("complex YAML keys not supported", 2, 3, 9)
						)
					;
					DMibExpectException
						(
							CJsonWithoutMeta::fs_FromStringYamlBlock
								(
									"key: 1\n"
									"? - one\n"
									"  - two\n"
									": value\n"
								)
							, fs_MakeParseException("complex YAML keys not supported", 2, 3, 9)
						)
					;
					DMibExpectException
						(
							CJsonWithoutMeta::fs_FromStringYamlBlock
								(
									"key: 1\n"
									"? {a: 1, b: 2}\n"
									": value\n"
								)
							, fs_MakeParseException("complex YAML keys not supported", 2, 3, 9)
						)
					;
				};

				DMibTestCategory("BlockRoundTripWithComments")
				{
					auto Json = CJsonWithMeta::fs_FromStringYamlBlock
						(
							"# top leading\n"
							"a: 1 # a-line\n"
							"b: # b-key\n"
							"  c: 2 # c-line\n"
							"items:\n"
							"  # item leading\n"
							"  - one\n"
							"  - two # two-line\n"
							"# trailing\n"
						)
					;
					DMibExpect(Json.f_Yaml().f_LeadingComment(), ==, "# top leading\n");
					DMibExpect(Json["a"].f_Yaml().f_LineComment(), ==, " # a-line");
					DMibExpect(Json["b"]["c"].f_Yaml().f_LineComment(), ==, " # c-line");
					DMibExpect(Json["items"][0].f_Yaml().f_LeadingComment(), ==, "  # item leading\n");
					DMibExpect(Json["items"][1].f_Yaml().f_LineComment(), ==, " # two-line");
					DMibExpect
						(
							Json.f_ToStringYaml()
							, ==
							, "# top leading\n"
							"a: 1 # a-line\n"
							"b: # b-key\n"
							"  c: 2 # c-line\n"
							"items:\n"
							"  # item leading\n"
							"  - one\n"
							"  - two # two-line\n"
							"# trailing\n"
						)
					;
				};

				DMibTestCategory("MixedRoundTripWithComments")
				{
					auto Json = CJsonWithMeta::fs_FromStringYaml
						(
							"# header\n"
							"point: {x: 1, y: 2} # flow-line\n"
							"items: [10, 20] # arr-line\n"
							"# leading-shape\n"
							"shape:\n"
							"  edges:\n"
							"    - {a: 1, b: 2} # edge1\n"
							"    - {a: 3, b: 4}\n"
						)
					;

					DMibExpect(Json.f_Yaml().f_LeadingComment(), ==, "# header\n");
					DMibExpect(Json["point"].f_Yaml().f_LineComment(), ==, " # flow-line");
					DMibExpect(Json["items"].f_Yaml().f_LineComment(), ==, " # arr-line");
					DMibExpect(Json["shape"]["edges"][0].f_Yaml().f_LineComment(), ==, " # edge1");

					if constexpr (tf_bOrdered)
					{
						DMibExpect
							(
								Json.f_ToStringYaml()
								, ==
								, "# header\n"
								"point: {x: 1, y: 2} # flow-line\n"
								"items: [10, 20] # arr-line\n"
								"# leading-shape\n"
								"shape:\n"
								"  edges:\n"
								"    - {a: 1, b: 2} # edge1\n"
								"    - {a: 3, b: 4}\n"
							)
						;
					}
					else
					{
						DMibExpect
							(
								Json.f_ToStringYaml()
								, ==
								, "# header\n"
								"items: [10, 20] # arr-line\n"
								"point: {x: 1, y: 2} # flow-line\n"
								"# leading-shape\n"
								"shape:\n"
								"  edges:\n"
								"    - {a: 1, b: 2} # edge1\n"
								"    - {a: 3, b: 4}\n"
							)
						;
					}
				};
			};
		}

		void f_DoTests()
		{
			f_DoTestsImpl<true>("Ordered");
			f_DoTestsImpl<false>("Sorted");
		}
	};

	DMibTestRegister(CYaml_Tests, Malterlib::Encoding);
}
