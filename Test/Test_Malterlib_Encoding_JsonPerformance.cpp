// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifdef DMalterlibEnableThirdPartyComparisonTests
#define RAPIDJSON_USE_MEMBERSMAP 1

#include <Mib/Encoding/Json>
#include <Mib/Encoding/JsonImpl>
#include <Mib/Encoding/EJson>
#include <Mib/Encoding/EJsonImpl>
#include <Mib/Encoding/EJsonParse>
#include <Mib/Encoding/EJsonGenerate>
#include <Mib/Encoding/JsonParse>
#include <Mib/Encoding/JsonParse>
#include <Mib/Encoding/JsonGenerate>
#include <Mib/Encoding/Yaml>
#include <Mib/Test/Exception>
#include <Mib/Stream/ByteVector>
#include <Mib/Test/Performance>
#include <Mib/Cryptography/RandomID>

#ifdef DCompiler_MSVC
#pragma warning(disable:4996)
#endif

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <string>
#include <daw/json/daw_json_iterator.h>
#include <daw/json/daw_json_link.h>

#include <nlohmann/json.hpp>

struct CCoordinate
{
	double m_CoordinateX;
	double m_CoordinateY;
	double m_CoordinateZ;

	template <typename tf_CStr>
	void f_Format(tf_CStr &o_String) const
	{
		o_String += typename tf_CStr::CFormat("\n   x: {ffs,fdb} Mantissa {nfh}\n   y: {ffs,fdb} Mantissa {nfh}\n   z: {ffs,fdb} Mantissa {nfh}\n")
			<< m_CoordinateX
			<< fp64(m_CoordinateX).f_GetMantissa()
			<< m_CoordinateY
			<< fp64(m_CoordinateY).f_GetMantissa()
			<< m_CoordinateZ
			<< fp64(m_CoordinateZ).f_GetMantissa()
		;
	}

	CCoordinate operator / (smint _Length) const
	{
		return {m_CoordinateX / double(_Length), m_CoordinateY / double(_Length), m_CoordinateZ / double(_Length)};
	}

	auto operator == (const CCoordinate &_Right) const noexcept
	{
		return fp64(m_CoordinateX).f_AlmostEqual(fp64(_Right.m_CoordinateX), 2)
			&& fp64(m_CoordinateY).f_AlmostEqual(fp64(_Right.m_CoordinateY), 2)
			&& fp64(m_CoordinateZ).f_AlmostEqual(fp64(_Right.m_CoordinateZ), 2)
		;
	}
};

struct CCoordinates
{
	std::vector<CCoordinate> m_Coordinates;
};

namespace daw::json
{
	template<>
	struct json_data_contract<CCoordinate>
	{
		using type = json_member_list<json_number<"x">, json_number<"y">, json_number<"z">>;
	};

	template<>
	struct json_data_contract<CCoordinates>
	{
		using type = json_member_list<json_array<"coordinates", CCoordinate>>;
	};
}

namespace
{
	using namespace NMib;
	using namespace NMib::NEncoding;
	using namespace NMib::NStr;

	class CJsonPerformance_Tests : public NTest::CTest
	{
	public:

#if defined(DMibDebug) || defined(DMibSanitizerEnabled)
		static constexpr umint mc_TestDataLength = 16 * 1024;
		static constexpr umint mc_ArrayLength = 16 * 1024;
#else
		static constexpr umint mc_TestDataLength = 512 * 1024;
		static constexpr umint mc_ArrayLength = 512 * 1024;
#endif
		CStr fp_GenerateTestData(bool _bFloat, CCoordinate &o_Average)
		{
			CJsonSorted Data;
			auto &OutArray = Data["coordinates"].f_Array();
			for (umint i = 0; i < mc_TestDataLength; ++i)
			{
				auto &Entry = OutArray.f_Insert();
				Entry["name"] = "{} {}"_f << NCryptography::fg_RandomID(6) << (NMisc::fg_Random().f_GetValue<uint32>() % 10000);
				Entry["opts"]["1"].f_Array() = {1, true};
				if (_bFloat)
				{
					Entry["x"] = NMisc::fg_GetRandomFloatFullPrecision() * -10e-30;
					Entry["y"] = NMisc::fg_GetRandomFloatFullPrecision() * 10e30;
					Entry["z"] = NMisc::fg_GetRandomFloatFullPrecision();
				}
				else
				{
					Entry["x"] = NMisc::fg_GetRandomUnsigned();
					Entry["y"] = NMisc::fg_GetRandomUnsigned();
					Entry["z"] = NMisc::fg_GetRandomUnsigned();
				}
			}

			if (_bFloat)
			{
				CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

				for (auto &Coordinate : OutArray)
				{
					SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
					SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
					SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
				}

				o_Average = SumCoordinate / OutArray.f_GetLen();
			}

			return Data.f_ToString("\t", EJsonDialectFlag_HighPrecisionFloat);
		}

		void fp_TestGenerate(CStr const &_Description, NFunction::TCFunction<CStr ()> const &_GenerateJson, bool _bFloat)
		{
			DMibTestSuite(CTestCategory(_Description) << CTestGroup("Performance"))
			{
				CTestPerformance PerfTotal(0.75, false);

				auto JsonString = _GenerateJson();

				umint nIterations = 11;

				umint MalterlibStreamLen = 0;
				{
					auto const Document = NEncoding::CJsonSorted::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MibStream");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto Output = NStream::fg_ToByteVector(Document);
								MalterlibStreamLen = Output.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_AddBaseline(Measure);
				}
				umint RapidJsonLen = 0;
				{
					rapidjson::Document Document;
					Document.Parse<rapidjson::kParseFullPrecisionFlag>(JsonString.f_GetStr());

					CTestPerformanceMeasure Measure("RapidJson");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								rapidjson::StringBuffer Buffer;

								rapidjson::Writer<rapidjson::StringBuffer> Writer(Buffer);
								Document.Accept(Writer);

								Buffer.GetString();
								RapidJsonLen = Buffer.GetLength();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_AddBaseline(Measure);
				}
				umint NlohmannJsonLen = 0;
				{
					auto const JsonStringView = std::string_view(JsonString.f_GetStr(), JsonString.f_GetLen());
					auto Document = nlohmann::json::parse(JsonStringView);

					CTestPerformanceMeasure Measure("NlohmannJson");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto Dump = Document.dump();
								NlohmannJsonLen = Dump.length();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_AddReference(Measure);
				}
				umint MalterlibLen = 0;
				{
					auto const Document = NEncoding::CJsonSorted::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("Mib");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToString(nullptr);
								MalterlibLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibPLen = 0;
				{
					auto const Document = NEncoding::CJsonSorted::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MibP");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToString();
								MalterlibPLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibJsonCLen = 0;
				{
					auto const Document = NEncoding::CJsonSorted::fs_FromStringJsonC(JsonString);

					CTestPerformanceMeasure Measure("MibJsonC");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringJsonC(nullptr);
								MalterlibJsonCLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibJsonCPLen = 0;
				{
					auto const Document = NEncoding::CJsonSorted::fs_FromStringJsonC(JsonString);

					CTestPerformanceMeasure Measure("MibJsonCP");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringJsonC();
								MalterlibJsonCPLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibJsonCWithCommentsLen = 0;
				{
					auto const Document = NEncoding::CJsonSortedWithComments::fs_FromStringJsonC(JsonString);

					CTestPerformanceMeasure Measure("MibJsonCPre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringJsonC();
								MalterlibJsonCWithCommentsLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibJson5Len = 0;
				{
					auto const Document = NEncoding::CJsonSorted::fs_FromStringJson5(JsonString);

					CTestPerformanceMeasure Measure("MibJson5");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringJson5(nullptr);
								MalterlibJson5Len = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibJson5PLen = 0;
				{
					auto const Document = NEncoding::CJsonSorted::fs_FromStringJson5(JsonString);

					CTestPerformanceMeasure Measure("MibJson5P");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringJson5();
								MalterlibJson5PLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibJson5WithCommentsLen = 0;
				{
					auto const Document = NEncoding::CJsonSortedWithComments::fs_FromStringJson5(JsonString);

					CTestPerformanceMeasure Measure("MibJson5Pre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringJson5();
								MalterlibJson5WithCommentsLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibEJsonLen = 0;
				{
					auto const Document = NEncoding::CEJsonSorted::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MibEJson");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToString(nullptr);
								MalterlibEJsonLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibEJsonPLen = 0;
				{
					auto const Document = NEncoding::CEJsonSorted::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MibEJsonP");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToString();
								MalterlibEJsonPLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibEJsonCLen = 0;
				{
					auto const Document = NEncoding::CEJsonSorted::fs_FromStringJsonC(JsonString);

					CTestPerformanceMeasure Measure("MibEJsonC");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringJsonC(nullptr);
								MalterlibEJsonCLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibEJsonCPLen = 0;
				{
					auto const Document = NEncoding::CEJsonSorted::fs_FromStringJsonC(JsonString);

					CTestPerformanceMeasure Measure("MibEJsonCP");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringJsonC();
								MalterlibEJsonCPLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibEJsonCWithCommentsLen = 0;
				{
					auto const Document = NEncoding::CEJsonSortedWithComments::fs_FromStringJsonC(JsonString);

					CTestPerformanceMeasure Measure("MibEJsonCPre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringJsonC();
								MalterlibEJsonCWithCommentsLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibEJson5Len = 0;
				{
					auto const Document = NEncoding::CEJsonSorted::fs_FromStringJson5(JsonString);

					CTestPerformanceMeasure Measure("MibEJson5");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringJson5(nullptr);
								MalterlibEJson5Len = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibEJson5PLen = 0;
				{
					auto const Document = NEncoding::CEJsonSorted::fs_FromStringJson5(JsonString);

					CTestPerformanceMeasure Measure("MibEJson5P");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringJson5();
								MalterlibEJson5PLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibEJson5WithCommentsLen = 0;
				{
					auto const Document = NEncoding::CEJsonSortedWithComments::fs_FromStringJson5(JsonString);

					CTestPerformanceMeasure Measure("MibEJson5Pre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringJson5();
								MalterlibEJson5WithCommentsLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibYamlLen = 0;
				{
					auto const Document = NEncoding::CJsonSorted::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MibYaml");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringYaml();
								MalterlibYamlLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibYamlFlowLen = 0;
				{
					auto const Document = NEncoding::CJsonSorted::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MibYamlFlow");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringYamlFlow();
								MalterlibYamlFlowLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibYamlPreLen = 0;
				{
					auto const Document = NEncoding::CJsonSortedYaml::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MibYamlPre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringYaml();
								MalterlibYamlPreLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibYamlFlowPreLen = 0;
				{
					auto const Document = NEncoding::CJsonSortedYaml::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MibYamlFlowPre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringYamlFlow();
								MalterlibYamlFlowPreLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibEYamlLen = 0;
				{
					auto const Document = NEncoding::CEJsonSorted::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MibEYaml");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringYaml();
								MalterlibEYamlLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibEYamlFlowLen = 0;
				{
					auto const Document = NEncoding::CEJsonSorted::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MibEYamlFlow");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringYamlFlow();
								MalterlibEYamlFlowLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				umint MalterlibEYamlPreLen = 0;
				{
					auto const Document = NEncoding::CEJsonSortedYaml::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MibEYamlPre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringYaml();
								MalterlibEYamlPreLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}

					PerfTotal.f_Add(Measure);
				}
				umint MalterlibEYamlFlowPreLen = 0;
				{
					auto const Document = NEncoding::CEJsonSortedYaml::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MibEYamlFlowPre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						[&]() inline_never
							{
								auto String = Document.f_ToStringYamlFlow();
								MalterlibEYamlFlowPreLen = String.f_GetLen();
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}

				auto fDiff = [&](fp64 _Value0, fp64 _Value1)
					{
						return (_Value0 - _Value1).f_Abs() / _Value1;
					}
				;

				DMibExpectTrue(PerfTotal);

				DMibExpect(fDiff(RapidJsonLen, NlohmannJsonLen), <, 0.04);
				DMibExpect(fDiff(MalterlibLen, NlohmannJsonLen), <, 0.04);
				DMibExpect(fDiff(MalterlibJsonCLen, NlohmannJsonLen), <, 0.04);
				DMibExpect(fDiff(MalterlibJson5Len, NlohmannJsonLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEJsonLen, NlohmannJsonLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEJsonCLen, NlohmannJsonLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEJson5Len, NlohmannJsonLen), <, 0.04);

				DMibExpect(fDiff(MalterlibJsonCPLen, MalterlibPLen), <, 0.04);
				DMibExpect(fDiff(MalterlibJson5PLen, MalterlibPLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEJsonPLen, MalterlibPLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEJsonCPLen, MalterlibPLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEJson5PLen, MalterlibPLen), <, 0.04);

				DMibExpect(fDiff(MalterlibJson5WithCommentsLen, MalterlibJsonCWithCommentsLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEJsonCWithCommentsLen, MalterlibJsonCWithCommentsLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEJson5WithCommentsLen, MalterlibJsonCWithCommentsLen), <, 0.04);

				DMibExpect(fDiff(MalterlibYamlFlowPreLen, MalterlibYamlFlowLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEYamlFlowLen, MalterlibYamlFlowLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEYamlFlowPreLen, MalterlibYamlFlowLen), <, 0.04);

				DMibExpect(fDiff(MalterlibYamlPreLen, MalterlibYamlLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEYamlLen, MalterlibYamlLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEYamlPreLen, MalterlibYamlLen), <, 0.04);
			};
		}

		template <bool tf_bDoCalculation>
		void fp_TestParse(CStr const &_Description)
		{
			DMibTestSuite(CTestCategory(_Description) << CTestGroup("Performance"))
			{
				CTestPerformance PerfTotal(0.75, false);

				CCoordinate ExpectedAverage;
				auto JsonString = fp_GenerateTestData(true, ExpectedAverage);
				auto JamlString = NEncoding::CJsonSorted::fs_FromStringYaml(JsonString).f_ToStringYaml();

				umint nIterations = 11;

				CCoordinate RapidJsonResult;
				{
					CTestPerformanceMeasure Measure("RapidJson");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						RapidJsonResult = [&]() inline_never -> CCoordinate
							{
								rapidjson::Document Document;
								Document.Parse<rapidjson::kParseFullPrecisionFlag>(JsonString.f_GetStr());

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};
									auto const &Coordinates = Document["coordinates"];
									auto Length = Coordinates.Size();

									for (rapidjson::SizeType i = 0; i < Length; i++)
									{
										auto const &Coordinate = Coordinates[i];
										SumCoordinate.m_CoordinateX += Coordinate["x"].GetDouble();
										SumCoordinate.m_CoordinateY += Coordinate["y"].GetDouble();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].GetDouble();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_AddBaseline(Measure);
				}
				CCoordinate RapidJsonInaccurateResult;
				{
					CTestPerformanceMeasure Measure("RapidJsonInaccurate");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						RapidJsonInaccurateResult = [&]() inline_never -> CCoordinate
							{
								rapidjson::Document Document;
								Document.Parse(JsonString.f_GetStr());

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};
									rapidjson::Value const &Coordinates = Document["coordinates"];
									auto Length = Coordinates.Size();

									for (rapidjson::SizeType i = 0; i < Length; i++)
									{
										auto const &Coordinate = Coordinates[i];
										SumCoordinate.m_CoordinateX += Coordinate["x"].GetDouble();
										SumCoordinate.m_CoordinateY += Coordinate["y"].GetDouble();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].GetDouble();
									}
									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_AddBaseline(Measure);
				}
				[[maybe_unused]] CCoordinate DawJsonLinkResult;
				if constexpr (tf_bDoCalculation)
				{
					CTestPerformanceMeasure Measure("DawJsonLink");
					for (umint i = 0; i < nIterations; ++i)
					{
						auto const JsonStringView = std::string_view(JsonString.f_GetStr(), JsonString.f_GetLen());

						using range_t = daw::json::json_array_range<CCoordinate>;

						Measure.f_Start();
						DawJsonLinkResult = [&]() inline_never -> CCoordinate
							{
								CCoordinate SumCoordinate = {0.0, 0.0, 0.0};
								auto Length = 0;

								auto Coordinates = range_t(JsonStringView, "coordinates");

								for (auto Coordinate : Coordinates)
								{
									++Length;
									SumCoordinate.m_CoordinateX += Coordinate.m_CoordinateX;
									SumCoordinate.m_CoordinateY += Coordinate.m_CoordinateY;
									SumCoordinate.m_CoordinateZ += Coordinate.m_CoordinateZ;
								}

								return SumCoordinate / Length;
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_AddBaseline(Measure);
				}
				CCoordinate NlohmannJsonResult;
				{
					CTestPerformanceMeasure Measure("NlohmannJson");
					for (umint i = 0; i < nIterations; ++i)
					{
						auto const JsonStringView = std::string_view(JsonString.f_GetStr(), JsonString.f_GetLen());

						Measure.f_Start();
						NlohmannJsonResult = [&]() inline_never -> CCoordinate
							{
								auto Document = nlohmann::json::parse(JsonStringView);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};
									auto Length = 0;

									auto &Coordinates = Document["coordinates"];
									for (auto &Coordinate : Coordinates)
									{
										++Length;
										SumCoordinate.m_CoordinateX += Coordinate["x"].get<double>();
										SumCoordinate.m_CoordinateY += Coordinate["y"].get<double>();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].get<double>();
									}
									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_AddReference(Measure);
				}
				CCoordinate MalterlibResult;
				{
					CTestPerformanceMeasure Measure("Mib");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CJsonSorted::fs_FromString(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}
									return SumCoordinate / Length;
								}
								else
									return {};

							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibStreamResult;
				{
					auto const DocumentStream = NStream::fg_ToByteVector(NEncoding::CJsonSorted::fs_FromString(JsonString));

					CTestPerformanceMeasure Measure("MibStream");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibStreamResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NStream::fg_FromByteVector<NEncoding::CJsonSorted>(DocumentStream);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}
									return SumCoordinate / Length;
								}
								else
									return {};

							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_AddBaseline(Measure);
				}

				CCoordinate MalterlibJsonCResult;
				{
					CTestPerformanceMeasure Measure("MibJsonC");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibJsonCResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CJsonSorted::fs_FromStringJsonC(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}
									return SumCoordinate / Length;
								}
								else
									return {};

							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibJsonCWithCommentsResult;
				{
					CTestPerformanceMeasure Measure("MibJsonCPre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibJsonCWithCommentsResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CJsonSortedWithComments::fs_FromStringJsonC(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}
									return SumCoordinate / Length;
								}
								else
									return {};

							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibJson5Result;
				{
					CTestPerformanceMeasure Measure("MibJson5");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibJson5Result = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CJsonSorted::fs_FromStringJson5(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}
									return SumCoordinate / Length;
								}
								else
									return {};

							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibJson5WithCommentsResult;
				{
					CTestPerformanceMeasure Measure("MibJson5Pre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibJson5WithCommentsResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CJsonSortedWithComments::fs_FromStringJson5(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}
									return SumCoordinate / Length;
								}
								else
									return {};

							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibEJsonResult;
				{
					CTestPerformanceMeasure Measure("MibEJson");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibEJsonResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CEJsonSorted::fs_FromString(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibEJsonCResult;
				{
					CTestPerformanceMeasure Measure("MibEJsonC");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibEJsonCResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CEJsonSorted::fs_FromStringJsonC(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibEJsonCWithCommentsResult;
				{
					CTestPerformanceMeasure Measure("MibEJsonCPre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibEJsonCWithCommentsResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CEJsonSortedWithComments::fs_FromStringJsonC(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibEJson5Result;
				{
					CTestPerformanceMeasure Measure("MibEJson5");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibEJson5Result = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CEJsonSorted::fs_FromStringJson5(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibEJson5WithCommentsResult;
				{
					CTestPerformanceMeasure Measure("MibEJson5Pre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibEJson5WithCommentsResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CEJsonSortedWithComments::fs_FromStringJson5(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibYamlResult;
				{
					CTestPerformanceMeasure Measure("MibYaml");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibYamlResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CJsonSorted::fs_FromStringYaml(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibYamlPreResult;
				{
					CTestPerformanceMeasure Measure("MibYamlPre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibYamlPreResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CJsonSortedYaml::fs_FromStringYaml(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibEYamlResult;
				{
					CTestPerformanceMeasure Measure("MibEYaml");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibEYamlResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CEJsonSorted::fs_FromStringYaml(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibEYamlPreResult;
				{
					CTestPerformanceMeasure Measure("MibEYamlPre");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibEYamlPreResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CEJsonSortedYaml::fs_FromStringYaml(JsonString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibYamlBlockResult;
				{
					CTestPerformanceMeasure Measure("MibYamlB");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibYamlBlockResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CJsonSorted::fs_FromStringYaml(JamlString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibYamlPreBlockResult;
				{
					CTestPerformanceMeasure Measure("MibYamlPreB");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibYamlPreBlockResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CJsonSortedYaml::fs_FromStringYaml(JamlString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibEYamlBlockResult;
				{
					CTestPerformanceMeasure Measure("MibEYamlB");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibEYamlBlockResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CEJsonSorted::fs_FromStringYaml(JamlString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}
				CCoordinate MalterlibEYamlPreBlockResult;
				{
					CTestPerformanceMeasure Measure("MibEYamlPreB");
					for (umint i = 0; i < nIterations; ++i)
					{
						Measure.f_Start();
						MalterlibEYamlPreBlockResult = [&]() inline_never -> CCoordinate
							{
								auto const Document = NEncoding::CEJsonSortedYaml::fs_FromStringYaml(JamlString);

								if constexpr (tf_bDoCalculation)
								{
									CCoordinate SumCoordinate = {0.0, 0.0, 0.0};

									auto &Array = Document["coordinates"].f_Array();
									auto Length = Array.f_GetLen();

									for (auto &Coordinate : Array)
									{
										SumCoordinate.m_CoordinateX += Coordinate["x"].f_Float().f_Get();
										SumCoordinate.m_CoordinateY += Coordinate["y"].f_Float().f_Get();
										SumCoordinate.m_CoordinateZ += Coordinate["z"].f_Float().f_Get();
									}

									return SumCoordinate / Length;
								}
								else
									return {};
							}
							()
						;
						Measure.f_Stop(mc_ArrayLength);
					}
					PerfTotal.f_Add(Measure);
				}

				DMibExpectTrue(PerfTotal);

				if constexpr (tf_bDoCalculation)
				{
					DMibExpect(NlohmannJsonResult, ==, ExpectedAverage);
					DMibExpect(RapidJsonResult, ==, ExpectedAverage);
					DMibExpect(RapidJsonInaccurateResult, ==, ExpectedAverage);
					DMibExpect(DawJsonLinkResult, ==, ExpectedAverage);
					DMibExpect(MalterlibStreamResult, ==, ExpectedAverage);
					DMibExpect(MalterlibJsonCResult, ==, ExpectedAverage);
					DMibExpect(MalterlibJsonCWithCommentsResult, ==, ExpectedAverage);
					DMibExpect(MalterlibJson5Result, ==, ExpectedAverage);
					DMibExpect(MalterlibJson5WithCommentsResult, ==, ExpectedAverage);
					DMibExpect(MalterlibEJsonResult, ==, ExpectedAverage);
					DMibExpect(MalterlibEJsonCResult, ==, ExpectedAverage);
					DMibExpect(MalterlibEJsonCWithCommentsResult, ==, ExpectedAverage);
					DMibExpect(MalterlibEJson5Result, ==, ExpectedAverage);
					DMibExpect(MalterlibEJson5WithCommentsResult, ==, ExpectedAverage);
					DMibExpect(MalterlibYamlResult, ==, ExpectedAverage);
					DMibExpect(MalterlibYamlPreResult, ==, ExpectedAverage);
					DMibExpect(MalterlibEYamlResult, ==, ExpectedAverage);
					DMibExpect(MalterlibEYamlPreResult, ==, ExpectedAverage);
					DMibExpect(MalterlibYamlBlockResult, ==, ExpectedAverage);
					DMibExpect(MalterlibYamlPreBlockResult, ==, ExpectedAverage);
					DMibExpect(MalterlibEYamlBlockResult, ==, ExpectedAverage);
					DMibExpect(MalterlibEYamlPreBlockResult, ==, ExpectedAverage);
				}
			};
		}

		void f_DoTests()
		{
			fp_TestParse<false>("Parse");
			fp_TestParse<true>("Parse Calculate");
			fp_TestGenerate
				(
					"Generate Float"
					, [&]
					{
						CCoordinate Dummy;
						return fp_GenerateTestData(true, Dummy);
					}
					, true
				)
			;
			fp_TestGenerate
				(
					"Generate Integer"
					, [&]
					{
						CCoordinate Dummy;
						return fp_GenerateTestData(false, Dummy);
					}
					, false
				)
			;
		}
	};

	DMibTestRegister(CJsonPerformance_Tests, Malterlib::Encoding);
}

#endif
