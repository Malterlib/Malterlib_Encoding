// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_EJson.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	extern template struct NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;
	extern template struct TCJsonValue<CEJsonValueBaseOrderedWithComments>;
	extern template struct TCEJsonValue<CEJsonValueBaseOrderedWithComments>;
	extern template struct TCJsonObject<CEJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;
	extern template struct NPrivate::TCObjectEntry<CEJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;

	extern template struct TCJsonObjectEntryHandle<TCJsonObject<CEJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;
	extern template struct TCJsonOrderedDestructiveIterator<TCJsonObject<CEJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;
	extern template struct TCJsonSortedDestructiveIterator<TCJsonObject<CEJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;

	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseOrdered const &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseOrdered const &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseOrdered &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseSorted const &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseSorted const &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseSorted &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseSortedWithComments const &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseSortedWithComments const &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseSortedWithComments &&);

	extern template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	extern template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	extern template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	extern template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &);
	extern template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> &&);
	extern template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &&);
	extern template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseSortedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseSortedWithComments> const &
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseSortedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseSortedWithComments> &&
		)
	;
	extern template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseSortedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseSortedWithComments> const &&
		)
	;

	extern template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedWithComments> const &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedWithComments> &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedWithComments> const &&);

	extern template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseOrdered const &);
	extern template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseOrdered &);
	extern template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseOrdered &&);
	extern template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseSorted const &);
	extern template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseSorted &);
	extern template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseSorted &&);
	extern template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseSortedWithComments const &);
	extern template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseSortedWithComments &);
	extern template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseSortedWithComments &&);

	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(CNullPtr &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(CNullPtr &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(CNullPtr const &);

	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(NStr::CStr &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(NStr::CStr &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(NStr::CStr const &);

	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(int64 &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(int64 &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(int64 const &);

	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(int32 &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(int32 &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(int32 const &);

	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(uint64 &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(uint64 &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(uint64 const &);

	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(uint32 &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(uint32 &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(uint32 const &);

	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(pfp64 &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(pfp64 &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(pfp64 const &);

	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(pfp32 &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(pfp32 &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(pfp32 const &);

	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(fp32 &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(fp32 &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(fp32 const &);

	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(fp64 &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(fp64 &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(int &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(int &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(int const &);
#endif
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(bool &&);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(bool &);
	extern template CJsonValueEJsonOrderedWithComments::TCJsonValue(bool const &);

	extern template CEJsonOrderedWithComments::TCEJsonValue(EJsonType &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(EJsonType &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(EJsonType const &);

	extern template CEJsonOrderedWithComments::TCEJsonValue(ch8 const *&&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(ch8 const *&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(ch8 const *const &);

	extern template CEJsonOrderedWithComments::TCEJsonValue(CNullPtr &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(CNullPtr &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(CNullPtr const &);

	extern template CEJsonOrderedWithComments::TCEJsonValue(NStr::CStr &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(NStr::CStr &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(NStr::CStr const &);

	extern template CEJsonOrderedWithComments::TCEJsonValue(int64 &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(int64 &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(int64 const &);

	extern template CEJsonOrderedWithComments::TCEJsonValue(int32 &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(int32 &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(int32 const &);

	extern template CEJsonOrderedWithComments::TCEJsonValue(uint64 &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(uint64 &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(uint64 const &);

	extern template CEJsonOrderedWithComments::TCEJsonValue(uint32 &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(uint32 &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(uint32 const &);

	extern template CEJsonOrderedWithComments::TCEJsonValue(pfp64 &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(pfp64 &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(pfp64 const &);

	extern template CEJsonOrderedWithComments::TCEJsonValue(pfp32 &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(pfp32 &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(pfp32 const &);

	extern template CEJsonOrderedWithComments::TCEJsonValue(fp32 &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(fp32 &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(fp32 const &);

	extern template CEJsonOrderedWithComments::TCEJsonValue(fp64 &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(fp64 &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonOrderedWithComments::TCEJsonValue(int &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(int &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(int const &);
#endif
	extern template CEJsonOrderedWithComments::TCEJsonValue(bool &&);
	extern template CEJsonOrderedWithComments::TCEJsonValue(bool &);
	extern template CEJsonOrderedWithComments::TCEJsonValue(bool const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int64>(int64 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int64 &>(int64 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int64 const &>(int64 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int32>(int32 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int32 &>(int32 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int32 const &>(int32 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<uint64>(uint64 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<uint64 &>(uint64 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<uint64 const &>(uint64 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<uint32>(uint32 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<uint32 &>(uint32 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<uint32 const &>(uint32 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<pfp64>(pfp64 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<pfp64 &>(pfp64 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<pfp32>(pfp32 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<pfp32 &>(pfp32 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<fp32>(fp32 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<fp32 &>(fp32 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<fp32 const &>(fp32 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<fp64>(fp64 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<fp64 &>(fp64 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int>(int &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int &>(int &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int const &>(int const &);
#endif
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<bool>(bool &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<bool &>(bool &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<bool const &>(bool const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <CNullPtr>(CNullPtr &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <CNullPtr &>(CNullPtr &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int64>(int64 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int64 &>(int64 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int64 const &>(int64 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int32>(int32 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int32 &>(int32 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int32 const &>(int32 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <uint64>(uint64 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <uint64 &>(uint64 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <uint64 const &>(uint64 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <uint32>(uint32 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <uint32 &>(uint32 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <uint32 const &>(uint32 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <pfp64>(pfp64 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <pfp64 &>(pfp64 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <pfp64 const &>(pfp64 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <pfp32>(pfp32 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <pfp32 &>(pfp32 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <pfp32 const &>(pfp32 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <fp32>(fp32 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <fp32 &>(fp32 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <fp32 const &>(fp32 const &);

	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <fp64>(fp64 &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <fp64 &>(fp64 &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int>(int &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int &>(int &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int const &>(int const &);
#endif
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <bool>(bool &&);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <bool &>(bool &);
	extern template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <bool const &>(bool const &);

	extern template void CJsonValueEJsonOrderedWithComments::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonOrderedWithComments, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonOrderedWithComments, true>::CLocalOptions const &) const
	;
#endif
}

#include "Malterlib_Encoding_EJson_Value.hpp"
