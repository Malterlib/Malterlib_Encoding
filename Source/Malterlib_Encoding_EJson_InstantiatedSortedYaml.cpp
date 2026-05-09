// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Encoding_EJson.h"
#include "Malterlib_Encoding_Yaml.h"
#include "Malterlib_Encoding_EJson.hpp"
#include "Malterlib_Encoding_EJson_Generate.h"
#include "Malterlib_Encoding_EJson_Parse.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	template struct NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesSortedYaml, EJsonContainerFlag::mc_PreserveYamlMetadata>;
	template struct TCJsonValue<CEJsonValueBaseSortedYaml>;
	template struct TCEJsonValue<CEJsonValueBaseSortedYaml>;
	template struct TCJsonObject<CEJsonSortedYaml, EJsonContainerFlag::mc_PreserveYamlMetadata>;
	template struct NPrivate::TCObjectEntry<CEJsonSortedYaml, EJsonContainerFlag::mc_PreserveYamlMetadata>;

	template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrdered const &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrdered const &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrdered &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrderedYaml const &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrderedYaml const &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrderedYaml &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseSorted const &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseSorted const &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseSorted &&);

	template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrderedYaml>
		(
			TCEJsonValue<CEJsonValueBaseOrderedYaml> const &
		)
	;
	template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrderedYaml>
		(
			TCEJsonValue<CEJsonValueBaseOrderedYaml> &&
		)
	;
	template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrderedYaml>
		(
			TCEJsonValue<CEJsonValueBaseOrderedYaml> const &&
		)
	;
	template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &);
	template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> &&);
	template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &&);

	template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedYaml> const &);
	template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedYaml> &&);
	template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedYaml> const &&);
	template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &);
	template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> &&);
	template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &&);

	template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrdered const &);
	template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrdered &);
	template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrdered &&);
	template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrderedYaml const &);
	template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrderedYaml &);
	template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrderedYaml &&);
	template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseSorted const &);
	template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseSorted &);
	template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseSorted &&);

	template CJsonValueEJsonSortedYaml::TCJsonValue(CNullPtr &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(CNullPtr &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(CNullPtr const &);

	template CJsonValueEJsonSortedYaml::TCJsonValue(NStr::CStr &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(NStr::CStr &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(NStr::CStr const &);

	template CJsonValueEJsonSortedYaml::TCJsonValue(int64 &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(int64 &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(int64 const &);

	template CJsonValueEJsonSortedYaml::TCJsonValue(int32 &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(int32 &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(int32 const &);

	template CJsonValueEJsonSortedYaml::TCJsonValue(uint64 &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(uint64 &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(uint64 const &);

	template CJsonValueEJsonSortedYaml::TCJsonValue(uint32 &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(uint32 &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(uint32 const &);

	template CJsonValueEJsonSortedYaml::TCJsonValue(pfp64 &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(pfp64 &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(pfp64 const &);

	template CJsonValueEJsonSortedYaml::TCJsonValue(pfp32 &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(pfp32 &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(pfp32 const &);

	template CJsonValueEJsonSortedYaml::TCJsonValue(fp32 &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(fp32 &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(fp32 const &);

	template CJsonValueEJsonSortedYaml::TCJsonValue(fp64 &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(fp64 &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonValueEJsonSortedYaml::TCJsonValue(int &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(int &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(int const &);
#endif
	template CJsonValueEJsonSortedYaml::TCJsonValue(bool &&);
	template CJsonValueEJsonSortedYaml::TCJsonValue(bool &);
	template CJsonValueEJsonSortedYaml::TCJsonValue(bool const &);

	template CEJsonSortedYaml::TCEJsonValue(EJsonType &&);
	template CEJsonSortedYaml::TCEJsonValue(EJsonType &);
	template CEJsonSortedYaml::TCEJsonValue(EJsonType const &);

	template CEJsonSortedYaml::TCEJsonValue(ch8 const *&&);
	template CEJsonSortedYaml::TCEJsonValue(ch8 const *&);
	template CEJsonSortedYaml::TCEJsonValue(ch8 const *const &);

	template CEJsonSortedYaml::TCEJsonValue(CNullPtr &&);
	template CEJsonSortedYaml::TCEJsonValue(CNullPtr &);
	template CEJsonSortedYaml::TCEJsonValue(CNullPtr const &);

	template CEJsonSortedYaml::TCEJsonValue(NStr::CStr &&);
	template CEJsonSortedYaml::TCEJsonValue(NStr::CStr &);
	template CEJsonSortedYaml::TCEJsonValue(NStr::CStr const &);

	template CEJsonSortedYaml::TCEJsonValue(int64 &&);
	template CEJsonSortedYaml::TCEJsonValue(int64 &);
	template CEJsonSortedYaml::TCEJsonValue(int64 const &);

	template CEJsonSortedYaml::TCEJsonValue(int32 &&);
	template CEJsonSortedYaml::TCEJsonValue(int32 &);
	template CEJsonSortedYaml::TCEJsonValue(int32 const &);

	template CEJsonSortedYaml::TCEJsonValue(uint64 &&);
	template CEJsonSortedYaml::TCEJsonValue(uint64 &);
	template CEJsonSortedYaml::TCEJsonValue(uint64 const &);

	template CEJsonSortedYaml::TCEJsonValue(uint32 &&);
	template CEJsonSortedYaml::TCEJsonValue(uint32 &);
	template CEJsonSortedYaml::TCEJsonValue(uint32 const &);

	template CEJsonSortedYaml::TCEJsonValue(pfp64 &&);
	template CEJsonSortedYaml::TCEJsonValue(pfp64 &);
	template CEJsonSortedYaml::TCEJsonValue(pfp64 const &);

	template CEJsonSortedYaml::TCEJsonValue(pfp32 &&);
	template CEJsonSortedYaml::TCEJsonValue(pfp32 &);
	template CEJsonSortedYaml::TCEJsonValue(pfp32 const &);

	template CEJsonSortedYaml::TCEJsonValue(fp32 &&);
	template CEJsonSortedYaml::TCEJsonValue(fp32 &);
	template CEJsonSortedYaml::TCEJsonValue(fp32 const &);

	template CEJsonSortedYaml::TCEJsonValue(fp64 &&);
	template CEJsonSortedYaml::TCEJsonValue(fp64 &);
	template CEJsonSortedYaml::TCEJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonSortedYaml::TCEJsonValue(int &&);
	template CEJsonSortedYaml::TCEJsonValue(int &);
	template CEJsonSortedYaml::TCEJsonValue(int const &);
#endif
	template CEJsonSortedYaml::TCEJsonValue(bool &&);
	template CEJsonSortedYaml::TCEJsonValue(bool &);
	template CEJsonSortedYaml::TCEJsonValue(bool const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<CNullPtr>(CNullPtr &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<CNullPtr &>(CNullPtr &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int64>(int64 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int64 &>(int64 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int64 const &>(int64 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int32>(int32 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int32 &>(int32 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int32 const &>(int32 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<uint64>(uint64 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<uint64 &>(uint64 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<uint64 const &>(uint64 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<uint32>(uint32 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<uint32 &>(uint32 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<uint32 const &>(uint32 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<pfp64>(pfp64 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<pfp64 &>(pfp64 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<pfp64 const &>(pfp64 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<pfp32>(pfp32 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<pfp32 &>(pfp32 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<pfp32 const &>(pfp32 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<fp32>(fp32 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<fp32 &>(fp32 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<fp32 const &>(fp32 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<fp64>(fp64 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<fp64 &>(fp64 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int>(int &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int &>(int &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int const &>(int const &);
#endif
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<bool>(bool &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<bool &>(bool &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<bool const &>(bool const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <CNullPtr>(CNullPtr &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <CNullPtr &>(CNullPtr &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <CNullPtr const &>(CNullPtr const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <NStr::CStr>(NStr::CStr &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <NStr::CStr &>(NStr::CStr &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int64>(int64 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int64 &>(int64 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int64 const &>(int64 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int32>(int32 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int32 &>(int32 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int32 const &>(int32 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <uint64>(uint64 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <uint64 &>(uint64 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <uint64 const &>(uint64 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <uint32>(uint32 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <uint32 &>(uint32 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <uint32 const &>(uint32 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <pfp64>(pfp64 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <pfp64 &>(pfp64 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <pfp64 const &>(pfp64 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <pfp32>(pfp32 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <pfp32 &>(pfp32 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <pfp32 const &>(pfp32 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <fp32>(fp32 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <fp32 &>(fp32 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <fp32 const &>(fp32 const &);

	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <fp64>(fp64 &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <fp64 &>(fp64 &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int>(int &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int &>(int &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int const &>(int const &);
#endif
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <bool>(bool &&);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <bool &>(bool &);
	template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <bool const &>(bool const &);

	template void CJsonValueEJsonSortedYaml::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonSortedYaml, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonSortedYaml, false>::CLocalOptions const &) const
	;
#endif
}
