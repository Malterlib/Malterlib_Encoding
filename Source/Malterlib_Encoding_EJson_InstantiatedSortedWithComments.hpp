// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_EJson.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	extern template struct NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesSortedWithComments, EJsonContainerFlag::mc_PreserveComments>;
	extern template struct TCJsonValue<CEJsonValueBaseSortedWithComments>;
	extern template struct TCEJsonValue<CEJsonValueBaseSortedWithComments>;
	extern template struct TCJsonObject<CEJsonSortedWithComments, EJsonContainerFlag::mc_PreserveComments>;
	extern template struct NPrivate::TCObjectEntry<CEJsonSortedWithComments, EJsonContainerFlag::mc_PreserveComments>;

	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrdered const &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrdered const &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrdered &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrderedWithComments const &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrderedWithComments const &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrderedWithComments &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseSorted const &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseSorted const &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseSorted &&);

	extern template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	extern template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	extern template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	extern template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrderedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrderedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseOrderedWithComments> &&
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrderedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &&
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &);
	extern template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> &&);
	extern template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &&);

	extern template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	extern template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &);
	extern template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedWithComments> &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &);
	extern template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &&);

	extern template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrdered const &);
	extern template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrdered &);
	extern template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrdered &&);
	extern template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrderedWithComments const &);
	extern template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrderedWithComments &);
	extern template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrderedWithComments &&);
	extern template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseSorted const &);
	extern template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseSorted &);
	extern template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseSorted &&);

	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(CNullPtr &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(CNullPtr &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(CNullPtr const &);

	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(NStr::CStr &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(NStr::CStr &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(NStr::CStr const &);

	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(int64 &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(int64 &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(int64 const &);

	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(int32 &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(int32 &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(int32 const &);

	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(uint64 &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(uint64 &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(uint64 const &);

	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(uint32 &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(uint32 &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(uint32 const &);

	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(pfp64 &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(pfp64 &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(pfp64 const &);

	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(pfp32 &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(pfp32 &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(pfp32 const &);

	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(fp32 &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(fp32 &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(fp32 const &);

	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(fp64 &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(fp64 &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(int &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(int &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(int const &);
#endif
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(bool &&);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(bool &);
	extern template CJsonValueEJsonSortedWithComments::TCJsonValue(bool const &);

	extern template CEJsonSortedWithComments::TCEJsonValue(EJsonType &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(EJsonType &);
	extern template CEJsonSortedWithComments::TCEJsonValue(EJsonType const &);

	extern template CEJsonSortedWithComments::TCEJsonValue(ch8 const *&&);
	extern template CEJsonSortedWithComments::TCEJsonValue(ch8 const *&);
	extern template CEJsonSortedWithComments::TCEJsonValue(ch8 const *const &);

	extern template CEJsonSortedWithComments::TCEJsonValue(CNullPtr &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(CNullPtr &);
	extern template CEJsonSortedWithComments::TCEJsonValue(CNullPtr const &);

	extern template CEJsonSortedWithComments::TCEJsonValue(NStr::CStr &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(NStr::CStr &);
	extern template CEJsonSortedWithComments::TCEJsonValue(NStr::CStr const &);

	extern template CEJsonSortedWithComments::TCEJsonValue(int64 &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(int64 &);
	extern template CEJsonSortedWithComments::TCEJsonValue(int64 const &);

	extern template CEJsonSortedWithComments::TCEJsonValue(int32 &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(int32 &);
	extern template CEJsonSortedWithComments::TCEJsonValue(int32 const &);

	extern template CEJsonSortedWithComments::TCEJsonValue(uint64 &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(uint64 &);
	extern template CEJsonSortedWithComments::TCEJsonValue(uint64 const &);

	extern template CEJsonSortedWithComments::TCEJsonValue(uint32 &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(uint32 &);
	extern template CEJsonSortedWithComments::TCEJsonValue(uint32 const &);

	extern template CEJsonSortedWithComments::TCEJsonValue(pfp64 &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(pfp64 &);
	extern template CEJsonSortedWithComments::TCEJsonValue(pfp64 const &);

	extern template CEJsonSortedWithComments::TCEJsonValue(pfp32 &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(pfp32 &);
	extern template CEJsonSortedWithComments::TCEJsonValue(pfp32 const &);

	extern template CEJsonSortedWithComments::TCEJsonValue(fp32 &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(fp32 &);
	extern template CEJsonSortedWithComments::TCEJsonValue(fp32 const &);

	extern template CEJsonSortedWithComments::TCEJsonValue(fp64 &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(fp64 &);
	extern template CEJsonSortedWithComments::TCEJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonSortedWithComments::TCEJsonValue(int &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(int &);
	extern template CEJsonSortedWithComments::TCEJsonValue(int const &);
#endif
	extern template CEJsonSortedWithComments::TCEJsonValue(bool &&);
	extern template CEJsonSortedWithComments::TCEJsonValue(bool &);
	extern template CEJsonSortedWithComments::TCEJsonValue(bool const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int64>(int64 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int64 &>(int64 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int64 const &>(int64 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int32>(int32 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int32 &>(int32 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int32 const &>(int32 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<uint64>(uint64 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<uint64 &>(uint64 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<uint64 const &>(uint64 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<uint32>(uint32 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<uint32 &>(uint32 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<uint32 const &>(uint32 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<pfp64>(pfp64 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<pfp64 &>(pfp64 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<pfp32>(pfp32 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<pfp32 &>(pfp32 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<fp32>(fp32 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<fp32 &>(fp32 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<fp32 const &>(fp32 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<fp64>(fp64 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<fp64 &>(fp64 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int>(int &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int &>(int &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int const &>(int const &);
#endif
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<bool>(bool &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<bool &>(bool &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<bool const &>(bool const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <CNullPtr>(CNullPtr &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <CNullPtr &>(CNullPtr &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int64>(int64 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int64 &>(int64 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int64 const &>(int64 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int32>(int32 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int32 &>(int32 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int32 const &>(int32 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <uint64>(uint64 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <uint64 &>(uint64 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <uint64 const &>(uint64 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <uint32>(uint32 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <uint32 &>(uint32 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <uint32 const &>(uint32 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <pfp64>(pfp64 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <pfp64 &>(pfp64 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <pfp64 const &>(pfp64 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <pfp32>(pfp32 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <pfp32 &>(pfp32 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <pfp32 const &>(pfp32 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <fp32>(fp32 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <fp32 &>(fp32 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <fp32 const &>(fp32 const &);

	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <fp64>(fp64 &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <fp64 &>(fp64 &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int>(int &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int &>(int &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int const &>(int const &);
#endif
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <bool>(bool &&);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <bool &>(bool &);
	extern template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <bool const &>(bool const &);

	extern template void CJsonValueEJsonSortedWithComments::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonSortedWithComments, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonSortedWithComments, false>::CLocalOptions const &) const
	;
#endif
}

#include "Malterlib_Encoding_EJson_Value.hpp"
