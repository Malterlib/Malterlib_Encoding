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
	template struct NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;
	template struct TCJsonValue<CEJsonValueBaseOrderedYaml>;
	template struct TCEJsonValue<CEJsonValueBaseOrderedYaml>;
	template struct TCJsonObject<CEJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;
	template struct NPrivate::TCObjectEntry<CEJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;

	template struct TCJsonObjectEntryHandle<TCJsonObject<CEJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;
	template struct TCJsonOrderedDestructiveIterator<TCJsonObject<CEJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;
	template struct TCJsonSortedDestructiveIterator<TCJsonObject<CEJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;

	template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseOrdered const &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseOrdered const &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseOrdered &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSorted const &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSorted const &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSorted &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSortedYaml const &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSortedYaml const &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSortedYaml &&);

	template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &);
	template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> &&);
	template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &&);
	template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSortedYaml>
		(
			TCEJsonValue<CEJsonValueBaseSortedYaml> const &
		)
	;
	template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSortedYaml>
		(
			TCEJsonValue<CEJsonValueBaseSortedYaml> &&
		)
	;
	template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSortedYaml>
		(
			TCEJsonValue<CEJsonValueBaseSortedYaml> const &&
		)
	;

	template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &);
	template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> &&);
	template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &&);
	template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedYaml> const &);
	template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedYaml> &&);
	template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedYaml> const &&);

	template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseOrdered const &);
	template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseOrdered &);
	template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseOrdered &&);
	template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSorted const &);
	template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSorted &);
	template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSorted &&);
	template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSortedYaml const &);
	template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSortedYaml &);
	template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSortedYaml &&);

	template CJsonValueEJsonOrderedYaml::TCJsonValue(CNullPtr &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(CNullPtr &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(CNullPtr const &);

	template CJsonValueEJsonOrderedYaml::TCJsonValue(NStr::CStr &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(NStr::CStr &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(NStr::CStr const &);

	template CJsonValueEJsonOrderedYaml::TCJsonValue(int64 &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(int64 &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(int64 const &);

	template CJsonValueEJsonOrderedYaml::TCJsonValue(int32 &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(int32 &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(int32 const &);

	template CJsonValueEJsonOrderedYaml::TCJsonValue(uint64 &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(uint64 &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(uint64 const &);

	template CJsonValueEJsonOrderedYaml::TCJsonValue(uint32 &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(uint32 &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(uint32 const &);

	template CJsonValueEJsonOrderedYaml::TCJsonValue(pfp64 &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(pfp64 &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(pfp64 const &);

	template CJsonValueEJsonOrderedYaml::TCJsonValue(pfp32 &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(pfp32 &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(pfp32 const &);

	template CJsonValueEJsonOrderedYaml::TCJsonValue(fp32 &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(fp32 &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(fp32 const &);

	template CJsonValueEJsonOrderedYaml::TCJsonValue(fp64 &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(fp64 &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonValueEJsonOrderedYaml::TCJsonValue(int &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(int &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(int const &);
#endif
	template CJsonValueEJsonOrderedYaml::TCJsonValue(bool &&);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(bool &);
	template CJsonValueEJsonOrderedYaml::TCJsonValue(bool const &);

	template CEJsonOrderedYaml::TCEJsonValue(EJsonType &&);
	template CEJsonOrderedYaml::TCEJsonValue(EJsonType &);
	template CEJsonOrderedYaml::TCEJsonValue(EJsonType const &);

	template CEJsonOrderedYaml::TCEJsonValue(ch8 const *&&);
	template CEJsonOrderedYaml::TCEJsonValue(ch8 const *&);
	template CEJsonOrderedYaml::TCEJsonValue(ch8 const *const &);

	template CEJsonOrderedYaml::TCEJsonValue(CNullPtr &&);
	template CEJsonOrderedYaml::TCEJsonValue(CNullPtr &);
	template CEJsonOrderedYaml::TCEJsonValue(CNullPtr const &);

	template CEJsonOrderedYaml::TCEJsonValue(NStr::CStr &&);
	template CEJsonOrderedYaml::TCEJsonValue(NStr::CStr &);
	template CEJsonOrderedYaml::TCEJsonValue(NStr::CStr const &);

	template CEJsonOrderedYaml::TCEJsonValue(int64 &&);
	template CEJsonOrderedYaml::TCEJsonValue(int64 &);
	template CEJsonOrderedYaml::TCEJsonValue(int64 const &);

	template CEJsonOrderedYaml::TCEJsonValue(int32 &&);
	template CEJsonOrderedYaml::TCEJsonValue(int32 &);
	template CEJsonOrderedYaml::TCEJsonValue(int32 const &);

	template CEJsonOrderedYaml::TCEJsonValue(uint64 &&);
	template CEJsonOrderedYaml::TCEJsonValue(uint64 &);
	template CEJsonOrderedYaml::TCEJsonValue(uint64 const &);

	template CEJsonOrderedYaml::TCEJsonValue(uint32 &&);
	template CEJsonOrderedYaml::TCEJsonValue(uint32 &);
	template CEJsonOrderedYaml::TCEJsonValue(uint32 const &);

	template CEJsonOrderedYaml::TCEJsonValue(pfp64 &&);
	template CEJsonOrderedYaml::TCEJsonValue(pfp64 &);
	template CEJsonOrderedYaml::TCEJsonValue(pfp64 const &);

	template CEJsonOrderedYaml::TCEJsonValue(pfp32 &&);
	template CEJsonOrderedYaml::TCEJsonValue(pfp32 &);
	template CEJsonOrderedYaml::TCEJsonValue(pfp32 const &);

	template CEJsonOrderedYaml::TCEJsonValue(fp32 &&);
	template CEJsonOrderedYaml::TCEJsonValue(fp32 &);
	template CEJsonOrderedYaml::TCEJsonValue(fp32 const &);

	template CEJsonOrderedYaml::TCEJsonValue(fp64 &&);
	template CEJsonOrderedYaml::TCEJsonValue(fp64 &);
	template CEJsonOrderedYaml::TCEJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonOrderedYaml::TCEJsonValue(int &&);
	template CEJsonOrderedYaml::TCEJsonValue(int &);
	template CEJsonOrderedYaml::TCEJsonValue(int const &);
#endif
	template CEJsonOrderedYaml::TCEJsonValue(bool &&);
	template CEJsonOrderedYaml::TCEJsonValue(bool &);
	template CEJsonOrderedYaml::TCEJsonValue(bool const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<CNullPtr>(CNullPtr &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<CNullPtr &>(CNullPtr &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int64>(int64 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int64 &>(int64 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int64 const &>(int64 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int32>(int32 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int32 &>(int32 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int32 const &>(int32 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<uint64>(uint64 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<uint64 &>(uint64 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<uint64 const &>(uint64 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<uint32>(uint32 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<uint32 &>(uint32 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<uint32 const &>(uint32 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<pfp64>(pfp64 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<pfp64 &>(pfp64 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<pfp64 const &>(pfp64 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<pfp32>(pfp32 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<pfp32 &>(pfp32 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<pfp32 const &>(pfp32 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<fp32>(fp32 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<fp32 &>(fp32 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<fp32 const &>(fp32 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<fp64>(fp64 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<fp64 &>(fp64 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int>(int &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int &>(int &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int const &>(int const &);
#endif
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<bool>(bool &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<bool &>(bool &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<bool const &>(bool const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <CNullPtr>(CNullPtr &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <CNullPtr &>(CNullPtr &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <CNullPtr const &>(CNullPtr const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <NStr::CStr>(NStr::CStr &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <NStr::CStr &>(NStr::CStr &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int64>(int64 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int64 &>(int64 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int64 const &>(int64 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int32>(int32 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int32 &>(int32 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int32 const &>(int32 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <uint64>(uint64 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <uint64 &>(uint64 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <uint64 const &>(uint64 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <uint32>(uint32 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <uint32 &>(uint32 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <uint32 const &>(uint32 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <pfp64>(pfp64 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <pfp64 &>(pfp64 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <pfp64 const &>(pfp64 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <pfp32>(pfp32 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <pfp32 &>(pfp32 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <pfp32 const &>(pfp32 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <fp32>(fp32 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <fp32 &>(fp32 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <fp32 const &>(fp32 const &);

	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <fp64>(fp64 &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <fp64 &>(fp64 &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int>(int &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int &>(int &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int const &>(int const &);
#endif
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <bool>(bool &&);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <bool &>(bool &);
	template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <bool const &>(bool const &);

	template void CJsonValueEJsonOrderedYaml::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonOrderedYaml, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonOrderedYaml, true>::CLocalOptions const &) const
	;
#endif
}
