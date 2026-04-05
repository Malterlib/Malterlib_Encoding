// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_EJson.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	extern template struct NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesOrdered, true>;
	extern template struct TCJsonValue<CEJsonValueBaseOrdered>;
	extern template struct TCEJsonValue<CEJsonValueBaseOrdered>;
	extern template struct TCJsonObject<CEJsonOrdered, true>;
	extern template struct NPrivate::TCObjectEntry<CEJsonOrdered, true>;

	// Destructive iterator types for ordered mode
	extern template struct TCJsonObjectEntryHandle<TCJsonObject<CEJsonOrdered, true>>;
	extern template struct TCJsonOrderedDestructiveIterator<TCJsonObject<CEJsonOrdered, true>>;
	extern template struct TCJsonSortedDestructiveIterator<TCJsonObject<CEJsonOrdered, true>>;

	extern template CJsonValueEJsonOrdered::TCJsonValue(CEJsonValueBaseSorted const &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(CEJsonValueBaseSorted const &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(CEJsonValueBaseSorted &&);

	extern template TCEJsonValue<CEJsonValueBaseOrdered> CEJsonOrdered::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &);
	extern template TCEJsonValue<CEJsonValueBaseOrdered> CEJsonOrdered::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> &&);
	extern template TCEJsonValue<CEJsonValueBaseOrdered> CEJsonOrdered::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &&);

	extern template CEJsonOrdered::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &);
	extern template CEJsonOrdered::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> &&);
	extern template CEJsonOrdered::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &&);

	extern template CEJsonValueBaseOrdered::TCJsonValueBase(CEJsonValueBaseSorted const &);
	extern template CEJsonValueBaseOrdered::TCJsonValueBase(CEJsonValueBaseSorted &);
	extern template CEJsonValueBaseOrdered::TCJsonValueBase(CEJsonValueBaseSorted &&);

	extern template CJsonValueEJsonOrdered::TCJsonValue(CNullPtr &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(CNullPtr &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(CNullPtr const &);

	extern template CJsonValueEJsonOrdered::TCJsonValue(NStr::CStr &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(NStr::CStr &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(NStr::CStr const &);

	extern template CJsonValueEJsonOrdered::TCJsonValue(int64 &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(int64 &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(int64 const &);

	extern template CJsonValueEJsonOrdered::TCJsonValue(int32 &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(int32 &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(int32 const &);

	extern template CJsonValueEJsonOrdered::TCJsonValue(uint64 &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(uint64 &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(uint64 const &);

	extern template CJsonValueEJsonOrdered::TCJsonValue(uint32 &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(uint32 &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(uint32 const &);

	extern template CJsonValueEJsonOrdered::TCJsonValue(pfp64 &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(pfp64 &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(pfp64 const &);

	extern template CJsonValueEJsonOrdered::TCJsonValue(pfp32 &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(pfp32 &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(pfp32 const &);

	extern template CJsonValueEJsonOrdered::TCJsonValue(fp32 &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(fp32 &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(fp32 const &);

	extern template CJsonValueEJsonOrdered::TCJsonValue(fp64 &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(fp64 &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonValueEJsonOrdered::TCJsonValue(int &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(int &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(int const &);
#endif
	extern template CJsonValueEJsonOrdered::TCJsonValue(bool &&);
	extern template CJsonValueEJsonOrdered::TCJsonValue(bool &);
	extern template CJsonValueEJsonOrdered::TCJsonValue(bool const &);

	//

	extern template CEJsonOrdered::TCEJsonValue(EJsonType &&);
	extern template CEJsonOrdered::TCEJsonValue(EJsonType &);
	extern template CEJsonOrdered::TCEJsonValue(EJsonType const &);

	extern template CEJsonOrdered::TCEJsonValue(ch8 const *&&);
	extern template CEJsonOrdered::TCEJsonValue(ch8 const *&);
	extern template CEJsonOrdered::TCEJsonValue(ch8 const *const &);

	extern template CEJsonOrdered::TCEJsonValue(CNullPtr &&);
	extern template CEJsonOrdered::TCEJsonValue(CNullPtr &);
	extern template CEJsonOrdered::TCEJsonValue(CNullPtr const &);

	extern template CEJsonOrdered::TCEJsonValue(NStr::CStr &&);
	extern template CEJsonOrdered::TCEJsonValue(NStr::CStr &);
	extern template CEJsonOrdered::TCEJsonValue(NStr::CStr const &);

	extern template CEJsonOrdered::TCEJsonValue(int64 &&);
	extern template CEJsonOrdered::TCEJsonValue(int64 &);
	extern template CEJsonOrdered::TCEJsonValue(int64 const &);

	extern template CEJsonOrdered::TCEJsonValue(int32 &&);
	extern template CEJsonOrdered::TCEJsonValue(int32 &);
	extern template CEJsonOrdered::TCEJsonValue(int32 const &);

	extern template CEJsonOrdered::TCEJsonValue(uint64 &&);
	extern template CEJsonOrdered::TCEJsonValue(uint64 &);
	extern template CEJsonOrdered::TCEJsonValue(uint64 const &);

	extern template CEJsonOrdered::TCEJsonValue(uint32 &&);
	extern template CEJsonOrdered::TCEJsonValue(uint32 &);
	extern template CEJsonOrdered::TCEJsonValue(uint32 const &);

	extern template CEJsonOrdered::TCEJsonValue(pfp64 &&);
	extern template CEJsonOrdered::TCEJsonValue(pfp64 &);
	extern template CEJsonOrdered::TCEJsonValue(pfp64 const &);

	extern template CEJsonOrdered::TCEJsonValue(pfp32 &&);
	extern template CEJsonOrdered::TCEJsonValue(pfp32 &);
	extern template CEJsonOrdered::TCEJsonValue(pfp32 const &);

	extern template CEJsonOrdered::TCEJsonValue(fp32 &&);
	extern template CEJsonOrdered::TCEJsonValue(fp32 &);
	extern template CEJsonOrdered::TCEJsonValue(fp32 const &);

	extern template CEJsonOrdered::TCEJsonValue(fp64 &&);
	extern template CEJsonOrdered::TCEJsonValue(fp64 &);
	extern template CEJsonOrdered::TCEJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonOrdered::TCEJsonValue(int &&);
	extern template CEJsonOrdered::TCEJsonValue(int &);
	extern template CEJsonOrdered::TCEJsonValue(int const &);
#endif
	extern template CEJsonOrdered::TCEJsonValue(bool &&);
	extern template CEJsonOrdered::TCEJsonValue(bool &);
	extern template CEJsonOrdered::TCEJsonValue(bool const &);

	//
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int64>(int64 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int64 &>(int64 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int64 const &>(int64 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int32>(int32 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int32 &>(int32 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int32 const &>(int32 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<uint64>(uint64 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<uint64 &>(uint64 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<uint64 const &>(uint64 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<uint32>(uint32 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<uint32 &>(uint32 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<uint32 const &>(uint32 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<pfp64>(pfp64 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<pfp64 &>(pfp64 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<pfp32>(pfp32 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<pfp32 &>(pfp32 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<fp32>(fp32 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<fp32 &>(fp32 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<fp32 const &>(fp32 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<fp64>(fp64 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<fp64 &>(fp64 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int>(int &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int &>(int &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int const &>(int const &);
#endif
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<bool>(bool &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<bool &>(bool &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<bool const &>(bool const &);
#endif

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <CNullPtr>(CNullPtr &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <CNullPtr &>(CNullPtr &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int64>(int64 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int64 &>(int64 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int64 const &>(int64 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int32>(int32 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int32 &>(int32 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int32 const &>(int32 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <uint64>(uint64 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <uint64 &>(uint64 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <uint64 const &>(uint64 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <uint32>(uint32 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <uint32 &>(uint32 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <uint32 const &>(uint32 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <pfp64>(pfp64 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <pfp64 &>(pfp64 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <pfp64 const &>(pfp64 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <pfp32>(pfp32 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <pfp32 &>(pfp32 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <pfp32 const &>(pfp32 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <fp32>(fp32 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <fp32 &>(fp32 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <fp32 const &>(fp32 const &);

	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <fp64>(fp64 &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <fp64 &>(fp64 &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int>(int &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int &>(int &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int const &>(int const &);
#endif
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <bool>(bool &&);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <bool &>(bool &);
	extern template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <bool const &>(bool const &);

	extern template void CJsonValueEJsonOrdered::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonOrdered, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonOrdered, true>::CLocalOptions const &) const
	;
}

#include "Malterlib_Encoding_EJson_Value.hpp"
