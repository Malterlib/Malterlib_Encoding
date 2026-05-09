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
	template struct NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;
	template struct TCJsonValue<NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;
	template struct TCJsonObject<CJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;
	template struct NPrivate::TCObjectEntry<CJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;

	template struct TCJsonObjectEntryHandle<TCJsonObject<CJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;
	template struct TCJsonOrderedDestructiveIterator<TCJsonObject<CJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;
	template struct TCJsonSortedDestructiveIterator<TCJsonObject<CJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;

	template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseOrdered const &);
	template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseOrdered const &&);
	template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseOrdered &&);
	template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSorted const &);
	template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSorted const &&);
	template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSorted &&);
	template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSortedYaml const &);
	template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSortedYaml const &&);
	template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSortedYaml &&);

	template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &);
	template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> &&);
	template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &&);
	template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &);
	template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> &&);
	template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &&);
	template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> const &
		)
	;
	template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> &&
		)
	;
	template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> const &&
		)
	;

	template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &);
	template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> &&);
	template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &&);
	template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &);
	template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> &&);
	template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &&);
	template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> const &);
	template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> &&);
	template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> const &&);

	template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseOrdered const &);
	template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseOrdered &);
	template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseOrdered &&);
	template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSorted const &);
	template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSorted &);
	template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSorted &&);
	template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSortedYaml const &);
	template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSortedYaml &);
	template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSortedYaml &&);

	template CJsonOrderedYaml::TCJsonValue(CNullPtr &&);
	template CJsonOrderedYaml::TCJsonValue(CNullPtr &);
	template CJsonOrderedYaml::TCJsonValue(CNullPtr const &);

	template CJsonOrderedYaml::TCJsonValue(NStr::CStr &&);
	template CJsonOrderedYaml::TCJsonValue(NStr::CStr &);
	template CJsonOrderedYaml::TCJsonValue(NStr::CStr const &);

	template CJsonOrderedYaml::TCJsonValue(int64 &&);
	template CJsonOrderedYaml::TCJsonValue(int64 &);
	template CJsonOrderedYaml::TCJsonValue(int64 const &);

	template CJsonOrderedYaml::TCJsonValue(int32 &&);
	template CJsonOrderedYaml::TCJsonValue(int32 &);
	template CJsonOrderedYaml::TCJsonValue(int32 const &);

	template CJsonOrderedYaml::TCJsonValue(uint64 &&);
	template CJsonOrderedYaml::TCJsonValue(uint64 &);
	template CJsonOrderedYaml::TCJsonValue(uint64 const &);

	template CJsonOrderedYaml::TCJsonValue(uint32 &&);
	template CJsonOrderedYaml::TCJsonValue(uint32 &);
	template CJsonOrderedYaml::TCJsonValue(uint32 const &);

	template CJsonOrderedYaml::TCJsonValue(pfp64 &&);
	template CJsonOrderedYaml::TCJsonValue(pfp64 &);
	template CJsonOrderedYaml::TCJsonValue(pfp64 const &);

	template CJsonOrderedYaml::TCJsonValue(pfp32 &&);
	template CJsonOrderedYaml::TCJsonValue(pfp32 &);
	template CJsonOrderedYaml::TCJsonValue(pfp32 const &);

	template CJsonOrderedYaml::TCJsonValue(fp32 &&);
	template CJsonOrderedYaml::TCJsonValue(fp32 &);
	template CJsonOrderedYaml::TCJsonValue(fp32 const &);

	template CJsonOrderedYaml::TCJsonValue(fp64 &&);
	template CJsonOrderedYaml::TCJsonValue(fp64 &);
	template CJsonOrderedYaml::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonOrderedYaml::TCJsonValue(int &&);
	template CJsonOrderedYaml::TCJsonValue(int &);
	template CJsonOrderedYaml::TCJsonValue(int const &);
#endif
	template CJsonOrderedYaml::TCJsonValue(bool &&);
	template CJsonOrderedYaml::TCJsonValue(bool &);
	template CJsonOrderedYaml::TCJsonValue(bool const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<CNullPtr>(CNullPtr &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<CNullPtr &>(CNullPtr &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int64>(int64 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int64 &>(int64 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int64 const &>(int64 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int32>(int32 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int32 &>(int32 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int32 const &>(int32 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<uint64>(uint64 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<uint64 &>(uint64 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<uint64 const &>(uint64 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<uint32>(uint32 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<uint32 &>(uint32 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<uint32 const &>(uint32 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<pfp64>(pfp64 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<pfp64 &>(pfp64 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<pfp64 const &>(pfp64 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<pfp32>(pfp32 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<pfp32 &>(pfp32 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<pfp32 const &>(pfp32 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<fp32>(fp32 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<fp32 &>(fp32 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<fp32 const &>(fp32 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<fp64>(fp64 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<fp64 &>(fp64 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int>(int &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int &>(int &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int const &>(int const &);
#endif
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<bool>(bool &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<bool &>(bool &);
	template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<bool const &>(bool const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <CNullPtr>(CNullPtr &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <CNullPtr &>(CNullPtr &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <CNullPtr const &>(CNullPtr const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <NStr::CStr>(NStr::CStr &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <NStr::CStr &>(NStr::CStr &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int64>(int64 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int64 &>(int64 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int64 const &>(int64 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int32>(int32 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int32 &>(int32 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int32 const &>(int32 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <uint64>(uint64 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <uint64 &>(uint64 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <uint64 const &>(uint64 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <uint32>(uint32 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <uint32 &>(uint32 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <uint32 const &>(uint32 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <pfp64>(pfp64 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <pfp64 &>(pfp64 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <pfp64 const &>(pfp64 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <pfp32>(pfp32 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <pfp32 &>(pfp32 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <pfp32 const &>(pfp32 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <fp32>(fp32 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <fp32 &>(fp32 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <fp32 const &>(fp32 const &);

	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <fp64>(fp64 &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <fp64 &>(fp64 &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int>(int &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int &>(int &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int const &>(int const &);
#endif
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <bool>(bool &&);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <bool &>(bool &);
	template CJsonOrderedYaml &CJsonOrderedYaml::operator = <bool const &>(bool const &);

	template void CJsonOrderedYaml::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonOrderedYaml, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonOrderedYaml, true>::CLocalOptions const &) const
	;
#endif
}
