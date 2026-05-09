// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Encoding_Json.h"
#include "Malterlib_Encoding_Json_Parse.h"
#include "Malterlib_Encoding_Json_Generate.h"
#include "Malterlib_Encoding_Yaml.h"
#include "Malterlib_Encoding_Json.hpp"
#include "Malterlib_Encoding_Json_GenerateColored.hpp"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	template struct NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_PreserveYamlMetadata>;
	template struct TCJsonValue<NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_PreserveYamlMetadata>>;
	template struct TCJsonObject<CJsonSortedYaml, EJsonContainerFlag::mc_PreserveYamlMetadata>;
	template struct NPrivate::TCObjectEntry<CJsonSortedYaml, EJsonContainerFlag::mc_PreserveYamlMetadata>;

	template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseSorted const &);
	template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseSorted const &&);
	template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseSorted &&);
	template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrdered const &);
	template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrdered const &&);
	template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrdered &&);
	template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrderedYaml const &);
	template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrderedYaml const &&);
	template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrderedYaml &&);

	template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &);
	template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> &&);
	template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &&);
	template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &);
	template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> &&);
	template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &&);
	template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> const &
		)
	;
	template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> &&
		)
	;
	template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> const &&
		)
	;

	template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &);
	template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> &&);
	template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &&);
	template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &);
	template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> &&);
	template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &&);
	template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> const &);
	template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> &&);
	template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> const &&);

	template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseSorted const &);
	template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseSorted &);
	template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseSorted &&);
	template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrdered const &);
	template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrdered &);
	template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrdered &&);
	template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrderedYaml const &);
	template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrderedYaml &);
	template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrderedYaml &&);

	template CJsonSortedYaml::TCJsonValue(CNullPtr &&);
	template CJsonSortedYaml::TCJsonValue(CNullPtr &);
	template CJsonSortedYaml::TCJsonValue(CNullPtr const &);

	template CJsonSortedYaml::TCJsonValue(NStr::CStr &&);
	template CJsonSortedYaml::TCJsonValue(NStr::CStr &);
	template CJsonSortedYaml::TCJsonValue(NStr::CStr const &);

	template CJsonSortedYaml::TCJsonValue(int64 &&);
	template CJsonSortedYaml::TCJsonValue(int64 &);
	template CJsonSortedYaml::TCJsonValue(int64 const &);

	template CJsonSortedYaml::TCJsonValue(int32 &&);
	template CJsonSortedYaml::TCJsonValue(int32 &);
	template CJsonSortedYaml::TCJsonValue(int32 const &);

	template CJsonSortedYaml::TCJsonValue(uint64 &&);
	template CJsonSortedYaml::TCJsonValue(uint64 &);
	template CJsonSortedYaml::TCJsonValue(uint64 const &);

	template CJsonSortedYaml::TCJsonValue(uint32 &&);
	template CJsonSortedYaml::TCJsonValue(uint32 &);
	template CJsonSortedYaml::TCJsonValue(uint32 const &);

	template CJsonSortedYaml::TCJsonValue(pfp64 &&);
	template CJsonSortedYaml::TCJsonValue(pfp64 &);
	template CJsonSortedYaml::TCJsonValue(pfp64 const &);

	template CJsonSortedYaml::TCJsonValue(pfp32 &&);
	template CJsonSortedYaml::TCJsonValue(pfp32 &);
	template CJsonSortedYaml::TCJsonValue(pfp32 const &);

	template CJsonSortedYaml::TCJsonValue(fp32 &&);
	template CJsonSortedYaml::TCJsonValue(fp32 &);
	template CJsonSortedYaml::TCJsonValue(fp32 const &);

	template CJsonSortedYaml::TCJsonValue(fp64 &&);
	template CJsonSortedYaml::TCJsonValue(fp64 &);
	template CJsonSortedYaml::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonSortedYaml::TCJsonValue(int &&);
	template CJsonSortedYaml::TCJsonValue(int &);
	template CJsonSortedYaml::TCJsonValue(int const &);
#endif
	template CJsonSortedYaml::TCJsonValue(bool &&);
	template CJsonSortedYaml::TCJsonValue(bool &);
	template CJsonSortedYaml::TCJsonValue(bool const &);

	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<CNullPtr>(CNullPtr &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<CNullPtr &>(CNullPtr &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int64>(int64 &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int64 &>(int64 &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int64 const &>(int64 const &);

	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int32>(int32 &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int32 &>(int32 &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int32 const &>(int32 const &);

	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<uint64>(uint64 &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<uint64 &>(uint64 &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<uint64 const &>(uint64 const &);

	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<uint32>(uint32 &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<uint32 &>(uint32 &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<uint32 const &>(uint32 const &);

	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<pfp64>(pfp64 &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<pfp64 &>(pfp64 &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<pfp64 const &>(pfp64 const &);

	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<pfp32>(pfp32 &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<pfp32 &>(pfp32 &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<pfp32 const &>(pfp32 const &);

	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<fp32>(fp32 &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<fp32 &>(fp32 &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<fp32 const &>(fp32 const &);

	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<fp64>(fp64 &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<fp64 &>(fp64 &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int>(int &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int &>(int &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int const &>(int const &);
#endif
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<bool>(bool &&);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<bool &>(bool &);
	template CJsonSortedYaml &CJsonSortedYaml::f_Insert<bool const &>(bool const &);

	template CJsonSortedYaml &CJsonSortedYaml::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CJsonSortedYaml &CJsonSortedYaml::operator = <CNullPtr>(CNullPtr &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <CNullPtr &>(CNullPtr &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <CNullPtr const &>(CNullPtr const &);

	template CJsonSortedYaml &CJsonSortedYaml::operator = <NStr::CStr>(NStr::CStr &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <NStr::CStr &>(NStr::CStr &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CJsonSortedYaml &CJsonSortedYaml::operator = <int64>(int64 &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <int64 &>(int64 &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <int64 const &>(int64 const &);

	template CJsonSortedYaml &CJsonSortedYaml::operator = <int32>(int32 &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <int32 &>(int32 &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <int32 const &>(int32 const &);

	template CJsonSortedYaml &CJsonSortedYaml::operator = <uint64>(uint64 &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <uint64 &>(uint64 &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <uint64 const &>(uint64 const &);

	template CJsonSortedYaml &CJsonSortedYaml::operator = <uint32>(uint32 &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <uint32 &>(uint32 &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <uint32 const &>(uint32 const &);

	template CJsonSortedYaml &CJsonSortedYaml::operator = <pfp64>(pfp64 &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <pfp64 &>(pfp64 &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <pfp64 const &>(pfp64 const &);

	template CJsonSortedYaml &CJsonSortedYaml::operator = <pfp32>(pfp32 &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <pfp32 &>(pfp32 &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <pfp32 const &>(pfp32 const &);

	template CJsonSortedYaml &CJsonSortedYaml::operator = <fp32>(fp32 &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <fp32 &>(fp32 &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <fp32 const &>(fp32 const &);

	template CJsonSortedYaml &CJsonSortedYaml::operator = <fp64>(fp64 &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <fp64 &>(fp64 &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonSortedYaml &CJsonSortedYaml::operator = <int>(int &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <int &>(int &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <int const &>(int const &);
#endif
	template CJsonSortedYaml &CJsonSortedYaml::operator = <bool>(bool &&);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <bool &>(bool &);
	template CJsonSortedYaml &CJsonSortedYaml::operator = <bool const &>(bool const &);

	template void CJsonSortedYaml::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSortedYaml, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSortedYaml, false>::CLocalOptions const &) const
	;
#endif
}
