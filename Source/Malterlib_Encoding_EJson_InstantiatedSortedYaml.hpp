// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_EJson.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	extern template struct NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesSortedYaml, EJsonContainerFlag::mc_PreserveYamlMetadata>;
	extern template struct TCJsonValue<CEJsonValueBaseSortedYaml>;
	extern template struct TCEJsonValue<CEJsonValueBaseSortedYaml>;
	extern template struct TCJsonObject<CEJsonSortedYaml, EJsonContainerFlag::mc_PreserveYamlMetadata>;
	extern template struct NPrivate::TCObjectEntry<CEJsonSortedYaml, EJsonContainerFlag::mc_PreserveYamlMetadata>;

	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrdered const &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrdered const &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrdered &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrderedYaml const &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrderedYaml const &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrderedYaml &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseSorted const &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseSorted const &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseSorted &&);

	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrderedYaml>
		(
			TCEJsonValue<CEJsonValueBaseOrderedYaml> const &
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrderedYaml>
		(
			TCEJsonValue<CEJsonValueBaseOrderedYaml> &&
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrderedYaml>
		(
			TCEJsonValue<CEJsonValueBaseOrderedYaml> const &&
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &);
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> &&);
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &&);

	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedYaml> const &);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedYaml> &&);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedYaml> const &&);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> &&);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &&);

	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrdered const &);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrdered &);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrdered &&);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrderedYaml const &);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrderedYaml &);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrderedYaml &&);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseSorted const &);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseSorted &);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseSorted &&);

	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrderedWithComments const &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrderedWithComments const &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseOrderedWithComments &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseSortedWithComments const &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseSortedWithComments const &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CEJsonValueBaseSortedWithComments &&);

	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrderedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrderedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseOrderedWithComments> &&
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseOrderedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &&
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseSortedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseSortedWithComments> const &
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseSortedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseSortedWithComments> &&
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseSortedYaml> CEJsonSortedYaml::fs_FromCompatible<CEJsonValueBaseSortedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseSortedWithComments> const &&
		)
	;

	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedWithComments> &&);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &&);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedWithComments> const &);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedWithComments> &&);
	extern template CEJsonSortedYaml::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedWithComments> const &&);

	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrderedWithComments const &);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrderedWithComments &);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseOrderedWithComments &&);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseSortedWithComments const &);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseSortedWithComments &);
	extern template CEJsonValueBaseSortedYaml::TCJsonValueBase(CEJsonValueBaseSortedWithComments &&);

	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CNullPtr &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CNullPtr &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(CNullPtr const &);

	extern template CJsonValueEJsonSortedYaml::TCJsonValue(NStr::CStr &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(NStr::CStr &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(NStr::CStr const &);

	extern template CJsonValueEJsonSortedYaml::TCJsonValue(int64 &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(int64 &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(int64 const &);

	extern template CJsonValueEJsonSortedYaml::TCJsonValue(int32 &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(int32 &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(int32 const &);

	extern template CJsonValueEJsonSortedYaml::TCJsonValue(uint64 &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(uint64 &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(uint64 const &);

	extern template CJsonValueEJsonSortedYaml::TCJsonValue(uint32 &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(uint32 &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(uint32 const &);

	extern template CJsonValueEJsonSortedYaml::TCJsonValue(pfp64 &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(pfp64 &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(pfp64 const &);

	extern template CJsonValueEJsonSortedYaml::TCJsonValue(pfp32 &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(pfp32 &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(pfp32 const &);

	extern template CJsonValueEJsonSortedYaml::TCJsonValue(fp32 &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(fp32 &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(fp32 const &);

	extern template CJsonValueEJsonSortedYaml::TCJsonValue(fp64 &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(fp64 &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(int &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(int &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(int const &);
#endif
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(bool &&);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(bool &);
	extern template CJsonValueEJsonSortedYaml::TCJsonValue(bool const &);

	extern template CEJsonSortedYaml::TCEJsonValue(EJsonType &&);
	extern template CEJsonSortedYaml::TCEJsonValue(EJsonType &);
	extern template CEJsonSortedYaml::TCEJsonValue(EJsonType const &);

	extern template CEJsonSortedYaml::TCEJsonValue(ch8 const *&&);
	extern template CEJsonSortedYaml::TCEJsonValue(ch8 const *&);
	extern template CEJsonSortedYaml::TCEJsonValue(ch8 const *const &);

	extern template CEJsonSortedYaml::TCEJsonValue(CNullPtr &&);
	extern template CEJsonSortedYaml::TCEJsonValue(CNullPtr &);
	extern template CEJsonSortedYaml::TCEJsonValue(CNullPtr const &);

	extern template CEJsonSortedYaml::TCEJsonValue(NStr::CStr &&);
	extern template CEJsonSortedYaml::TCEJsonValue(NStr::CStr &);
	extern template CEJsonSortedYaml::TCEJsonValue(NStr::CStr const &);

	extern template CEJsonSortedYaml::TCEJsonValue(int64 &&);
	extern template CEJsonSortedYaml::TCEJsonValue(int64 &);
	extern template CEJsonSortedYaml::TCEJsonValue(int64 const &);

	extern template CEJsonSortedYaml::TCEJsonValue(int32 &&);
	extern template CEJsonSortedYaml::TCEJsonValue(int32 &);
	extern template CEJsonSortedYaml::TCEJsonValue(int32 const &);

	extern template CEJsonSortedYaml::TCEJsonValue(uint64 &&);
	extern template CEJsonSortedYaml::TCEJsonValue(uint64 &);
	extern template CEJsonSortedYaml::TCEJsonValue(uint64 const &);

	extern template CEJsonSortedYaml::TCEJsonValue(uint32 &&);
	extern template CEJsonSortedYaml::TCEJsonValue(uint32 &);
	extern template CEJsonSortedYaml::TCEJsonValue(uint32 const &);

	extern template CEJsonSortedYaml::TCEJsonValue(pfp64 &&);
	extern template CEJsonSortedYaml::TCEJsonValue(pfp64 &);
	extern template CEJsonSortedYaml::TCEJsonValue(pfp64 const &);

	extern template CEJsonSortedYaml::TCEJsonValue(pfp32 &&);
	extern template CEJsonSortedYaml::TCEJsonValue(pfp32 &);
	extern template CEJsonSortedYaml::TCEJsonValue(pfp32 const &);

	extern template CEJsonSortedYaml::TCEJsonValue(fp32 &&);
	extern template CEJsonSortedYaml::TCEJsonValue(fp32 &);
	extern template CEJsonSortedYaml::TCEJsonValue(fp32 const &);

	extern template CEJsonSortedYaml::TCEJsonValue(fp64 &&);
	extern template CEJsonSortedYaml::TCEJsonValue(fp64 &);
	extern template CEJsonSortedYaml::TCEJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonSortedYaml::TCEJsonValue(int &&);
	extern template CEJsonSortedYaml::TCEJsonValue(int &);
	extern template CEJsonSortedYaml::TCEJsonValue(int const &);
#endif
	extern template CEJsonSortedYaml::TCEJsonValue(bool &&);
	extern template CEJsonSortedYaml::TCEJsonValue(bool &);
	extern template CEJsonSortedYaml::TCEJsonValue(bool const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int64>(int64 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int64 &>(int64 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int64 const &>(int64 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int32>(int32 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int32 &>(int32 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int32 const &>(int32 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<uint64>(uint64 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<uint64 &>(uint64 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<uint64 const &>(uint64 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<uint32>(uint32 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<uint32 &>(uint32 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<uint32 const &>(uint32 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<pfp64>(pfp64 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<pfp64 &>(pfp64 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<pfp32>(pfp32 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<pfp32 &>(pfp32 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<fp32>(fp32 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<fp32 &>(fp32 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<fp32 const &>(fp32 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<fp64>(fp64 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<fp64 &>(fp64 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int>(int &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int &>(int &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<int const &>(int const &);
#endif
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<bool>(bool &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<bool &>(bool &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::f_Insert<bool const &>(bool const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <CNullPtr>(CNullPtr &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <CNullPtr &>(CNullPtr &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int64>(int64 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int64 &>(int64 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int64 const &>(int64 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int32>(int32 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int32 &>(int32 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int32 const &>(int32 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <uint64>(uint64 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <uint64 &>(uint64 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <uint64 const &>(uint64 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <uint32>(uint32 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <uint32 &>(uint32 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <uint32 const &>(uint32 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <pfp64>(pfp64 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <pfp64 &>(pfp64 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <pfp64 const &>(pfp64 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <pfp32>(pfp32 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <pfp32 &>(pfp32 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <pfp32 const &>(pfp32 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <fp32>(fp32 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <fp32 &>(fp32 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <fp32 const &>(fp32 const &);

	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <fp64>(fp64 &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <fp64 &>(fp64 &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int>(int &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int &>(int &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <int const &>(int const &);
#endif
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <bool>(bool &&);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <bool &>(bool &);
	extern template CEJsonSortedYaml &CJsonValueEJsonSortedYaml::operator = <bool const &>(bool const &);

	extern template void CJsonValueEJsonSortedYaml::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonSortedYaml, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonSortedYaml, false>::CLocalOptions const &) const
	;
#endif
}

#include "Malterlib_Encoding_EJson_Value.hpp"
