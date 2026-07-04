// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_EJson.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	extern template struct NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;
	extern template struct TCJsonValue<CEJsonValueBaseOrderedYaml>;
	extern template struct TCEJsonValue<CEJsonValueBaseOrderedYaml>;
	extern template struct TCJsonObject<CEJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;
	extern template struct NPrivate::TCObjectEntry<CEJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;

	extern template struct TCJsonObjectEntryHandle<TCJsonObject<CEJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;
	extern template struct TCJsonOrderedDestructiveIterator<TCJsonObject<CEJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;
	extern template struct TCJsonSortedDestructiveIterator<TCJsonObject<CEJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;

	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseOrdered const &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseOrdered const &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseOrdered &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSorted const &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSorted const &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSorted &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSortedYaml const &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSortedYaml const &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSortedYaml &&);

	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &);
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> &&);
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &&);
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSortedYaml>
		(
			TCEJsonValue<CEJsonValueBaseSortedYaml> const &
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSortedYaml>
		(
			TCEJsonValue<CEJsonValueBaseSortedYaml> &&
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSortedYaml>
		(
			TCEJsonValue<CEJsonValueBaseSortedYaml> const &&
		)
	;

	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedYaml> const &);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedYaml> &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedYaml> const &&);

	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseOrdered const &);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseOrdered &);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseOrdered &&);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSorted const &);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSorted &);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSorted &&);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSortedYaml const &);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSortedYaml &);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSortedYaml &&);

	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseOrderedWithComments const &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseOrderedWithComments const &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseOrderedWithComments &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSortedWithComments const &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSortedWithComments const &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CEJsonValueBaseSortedWithComments &&);

	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseOrderedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseOrderedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseOrderedWithComments> &&
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseOrderedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &&
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSortedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseSortedWithComments> const &
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSortedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseSortedWithComments> &&
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseOrderedYaml> CEJsonOrderedYaml::fs_FromCompatible<CEJsonValueBaseSortedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseSortedWithComments> const &&
		)
	;

	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedWithComments> &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedWithComments> const &);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedWithComments> &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedWithComments> const &&);

	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseOrderedWithComments const &);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseOrderedWithComments &);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseOrderedWithComments &&);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSortedWithComments const &);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSortedWithComments &);
	extern template CEJsonValueBaseOrderedYaml::TCJsonValueBase(CEJsonValueBaseSortedWithComments &&);

	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CNullPtr &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CNullPtr &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(CNullPtr const &);

	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(NStr::CStr &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(NStr::CStr &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(NStr::CStr const &);

	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(int64 &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(int64 &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(int64 const &);

	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(int32 &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(int32 &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(int32 const &);

	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(uint64 &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(uint64 &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(uint64 const &);

	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(uint32 &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(uint32 &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(uint32 const &);

	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(pfp64 &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(pfp64 &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(pfp64 const &);

	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(pfp32 &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(pfp32 &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(pfp32 const &);

	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(fp32 &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(fp32 &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(fp32 const &);

	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(fp64 &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(fp64 &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(int &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(int &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(int const &);
#endif
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(bool &&);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(bool &);
	extern template CJsonValueEJsonOrderedYaml::TCJsonValue(bool const &);

	extern template CEJsonOrderedYaml::TCEJsonValue(EJsonType &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(EJsonType &);
	extern template CEJsonOrderedYaml::TCEJsonValue(EJsonType const &);

	extern template CEJsonOrderedYaml::TCEJsonValue(ch8 const *&&);
	extern template CEJsonOrderedYaml::TCEJsonValue(ch8 const *&);
	extern template CEJsonOrderedYaml::TCEJsonValue(ch8 const *const &);

	extern template CEJsonOrderedYaml::TCEJsonValue(CNullPtr &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(CNullPtr &);
	extern template CEJsonOrderedYaml::TCEJsonValue(CNullPtr const &);

	extern template CEJsonOrderedYaml::TCEJsonValue(NStr::CStr &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(NStr::CStr &);
	extern template CEJsonOrderedYaml::TCEJsonValue(NStr::CStr const &);

	extern template CEJsonOrderedYaml::TCEJsonValue(int64 &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(int64 &);
	extern template CEJsonOrderedYaml::TCEJsonValue(int64 const &);

	extern template CEJsonOrderedYaml::TCEJsonValue(int32 &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(int32 &);
	extern template CEJsonOrderedYaml::TCEJsonValue(int32 const &);

	extern template CEJsonOrderedYaml::TCEJsonValue(uint64 &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(uint64 &);
	extern template CEJsonOrderedYaml::TCEJsonValue(uint64 const &);

	extern template CEJsonOrderedYaml::TCEJsonValue(uint32 &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(uint32 &);
	extern template CEJsonOrderedYaml::TCEJsonValue(uint32 const &);

	extern template CEJsonOrderedYaml::TCEJsonValue(pfp64 &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(pfp64 &);
	extern template CEJsonOrderedYaml::TCEJsonValue(pfp64 const &);

	extern template CEJsonOrderedYaml::TCEJsonValue(pfp32 &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(pfp32 &);
	extern template CEJsonOrderedYaml::TCEJsonValue(pfp32 const &);

	extern template CEJsonOrderedYaml::TCEJsonValue(fp32 &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(fp32 &);
	extern template CEJsonOrderedYaml::TCEJsonValue(fp32 const &);

	extern template CEJsonOrderedYaml::TCEJsonValue(fp64 &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(fp64 &);
	extern template CEJsonOrderedYaml::TCEJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonOrderedYaml::TCEJsonValue(int &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(int &);
	extern template CEJsonOrderedYaml::TCEJsonValue(int const &);
#endif
	extern template CEJsonOrderedYaml::TCEJsonValue(bool &&);
	extern template CEJsonOrderedYaml::TCEJsonValue(bool &);
	extern template CEJsonOrderedYaml::TCEJsonValue(bool const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int64>(int64 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int64 &>(int64 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int64 const &>(int64 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int32>(int32 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int32 &>(int32 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int32 const &>(int32 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<uint64>(uint64 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<uint64 &>(uint64 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<uint64 const &>(uint64 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<uint32>(uint32 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<uint32 &>(uint32 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<uint32 const &>(uint32 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<pfp64>(pfp64 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<pfp64 &>(pfp64 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<pfp32>(pfp32 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<pfp32 &>(pfp32 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<fp32>(fp32 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<fp32 &>(fp32 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<fp32 const &>(fp32 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<fp64>(fp64 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<fp64 &>(fp64 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int>(int &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int &>(int &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<int const &>(int const &);
#endif
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<bool>(bool &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<bool &>(bool &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::f_Insert<bool const &>(bool const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <CNullPtr>(CNullPtr &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <CNullPtr &>(CNullPtr &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int64>(int64 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int64 &>(int64 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int64 const &>(int64 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int32>(int32 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int32 &>(int32 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int32 const &>(int32 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <uint64>(uint64 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <uint64 &>(uint64 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <uint64 const &>(uint64 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <uint32>(uint32 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <uint32 &>(uint32 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <uint32 const &>(uint32 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <pfp64>(pfp64 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <pfp64 &>(pfp64 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <pfp64 const &>(pfp64 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <pfp32>(pfp32 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <pfp32 &>(pfp32 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <pfp32 const &>(pfp32 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <fp32>(fp32 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <fp32 &>(fp32 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <fp32 const &>(fp32 const &);

	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <fp64>(fp64 &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <fp64 &>(fp64 &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int>(int &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int &>(int &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <int const &>(int const &);
#endif
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <bool>(bool &&);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <bool &>(bool &);
	extern template CEJsonOrderedYaml &CJsonValueEJsonOrderedYaml::operator = <bool const &>(bool const &);

	extern template void CJsonValueEJsonOrderedYaml::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonOrderedYaml, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonOrderedYaml, true>::CLocalOptions const &) const
	;
#endif
}

#include "Malterlib_Encoding_EJson_Value.hpp"
