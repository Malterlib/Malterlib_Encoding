// Copyright © 2022 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

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

	auto operator == (const CCoordinate &_Right) const
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
		static constexpr mint mc_TestDataLength = 16 * 1024;
		static constexpr mint mc_ArrayLength = 16 * 1024;
#else
		static constexpr mint mc_TestDataLength = 512 * 1024;
		static constexpr mint mc_ArrayLength = 512 * 1024;
#endif

		CStr fp_GenerateTestData(bool _bFloat, CCoordinate &o_Average)
		{
			CJsonSorted Data;
			auto &OutArray = Data["coordinates"].f_Array();
			for (mint i = 0; i < mc_TestDataLength; ++i)
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

				mint nIterations = 11;

				mint RapidJsonLen = 0;
				{
					rapidjson::Document Document;
					Document.Parse<rapidjson::kParseFullPrecisionFlag>(JsonString.f_GetStr());

					CTestPerformanceMeasure Measure("RapidJson");
					for (mint i = 0; i < nIterations; ++i)
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
				mint NlohmannJsonLen = 0;
				{
					auto const JsonStringView = std::string_view(JsonString.f_GetStr(), JsonString.f_GetLen());
					auto Document = nlohmann::json::parse(JsonStringView);

					CTestPerformanceMeasure Measure("NlohmannJson");
					for (mint i = 0; i < nIterations; ++i)
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
				mint MalterlibLen = 0;
				{
					auto const Document = NEncoding::CJsonSorted::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("Malterlib");
					for (mint i = 0; i < nIterations; ++i)
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
				mint MalterlibEJsonLen = 0;
				{
					auto const Document = NEncoding::CEJsonSorted::fs_FromString(JsonString);

					CTestPerformanceMeasure Measure("MalterlibEJson");
					for (mint i = 0; i < nIterations; ++i)
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

				auto fDiff = [&](fp64 _Value0, fp64 _Value1)
					{
						return (_Value0 - _Value1).f_Abs() / _Value1;
					}
				;

				DMibExpectTrue(PerfTotal);
				DMibExpect(fDiff(RapidJsonLen, NlohmannJsonLen), <, 0.04);
				DMibExpect(fDiff(MalterlibLen, NlohmannJsonLen), <, 0.04);
				DMibExpect(fDiff(MalterlibEJsonLen, NlohmannJsonLen), <, 0.04);
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

				mint nIterations = 11;

				CCoordinate RapidJsonResult;
				{
					CTestPerformanceMeasure Measure("RapidJson");
					for (mint i = 0; i < nIterations; ++i)
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
					for (mint i = 0; i < nIterations; ++i)
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
					for (mint i = 0; i < nIterations; ++i)
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
					for (mint i = 0; i < nIterations; ++i)
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
					CTestPerformanceMeasure Measure("Malterlib");
					for (mint i = 0; i < nIterations; ++i)
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
				CCoordinate MalterlibEJsonResult;
				{
					CTestPerformanceMeasure Measure("MalterlibEJson");
					for (mint i = 0; i < nIterations; ++i)
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

				DMibExpectTrue(PerfTotal);
				if constexpr (tf_bDoCalculation)
				{
					DMibExpect(NlohmannJsonResult, ==, ExpectedAverage);
					DMibExpect(RapidJsonResult, ==, ExpectedAverage);
					DMibExpect(RapidJsonInaccurateResult, ==, ExpectedAverage);
					DMibExpect(DawJsonLinkResult, ==, ExpectedAverage);
					DMibExpect(MalterlibResult, ==, ExpectedAverage);
					DMibExpect(MalterlibEJsonResult, ==, ExpectedAverage);
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
