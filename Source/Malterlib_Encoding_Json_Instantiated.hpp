// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	extern template struct NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, true>;
	extern template struct TCJsonValue<NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, true>>;
	extern template struct TCJsonObject<CJsonOrdered, true>;
	extern template struct NPrivate::TCObjectEntry<CJsonOrdered, true>;

	// Destructive iterator types for ordered mode
	extern template struct TCJsonObjectEntryHandle<TCJsonObject<CJsonOrdered, true>>;
	extern template struct TCJsonOrderedDestructiveIterator<TCJsonObject<CJsonOrdered, true>>;
	extern template struct TCJsonSortedDestructiveIterator<TCJsonObject<CJsonOrdered, true>>;

	extern template CJsonValueJsonOrdered::TCJsonValue(CJsonValueBaseSorted const &);
	extern template CJsonValueJsonOrdered::TCJsonValue(CJsonValueBaseSorted const &&);
	extern template CJsonValueJsonOrdered::TCJsonValue(CJsonValueBaseSorted &&);

	extern template TCJsonValue<CJsonValueBaseOrdered> CJsonOrdered::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &);
	extern template TCJsonValue<CJsonValueBaseOrdered> CJsonOrdered::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> &&);
	extern template TCJsonValue<CJsonValueBaseOrdered> CJsonOrdered::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &&);

	extern template CJsonOrdered::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &);
	extern template CJsonOrdered::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> &&);
	extern template CJsonOrdered::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &&);

	extern template CJsonValueBaseOrdered::TCJsonValueBase(CJsonValueBaseSorted const &);
	extern template CJsonValueBaseOrdered::TCJsonValueBase(CJsonValueBaseSorted &);
	extern template CJsonValueBaseOrdered::TCJsonValueBase(CJsonValueBaseSorted &&);

	extern template CJsonOrdered::TCJsonValue(CNullPtr &&);
	extern template CJsonOrdered::TCJsonValue(CNullPtr &);
	extern template CJsonOrdered::TCJsonValue(CNullPtr const &);

	extern template CJsonOrdered::TCJsonValue(NStr::CStr &&);
	extern template CJsonOrdered::TCJsonValue(NStr::CStr &);
	extern template CJsonOrdered::TCJsonValue(NStr::CStr const &);

	extern template CJsonOrdered::TCJsonValue(int64 &&);
	extern template CJsonOrdered::TCJsonValue(int64 &);
	extern template CJsonOrdered::TCJsonValue(int64 const &);

	extern template CJsonOrdered::TCJsonValue(int32 &&);
	extern template CJsonOrdered::TCJsonValue(int32 &);
	extern template CJsonOrdered::TCJsonValue(int32 const &);

	extern template CJsonOrdered::TCJsonValue(uint64 &&);
	extern template CJsonOrdered::TCJsonValue(uint64 &);
	extern template CJsonOrdered::TCJsonValue(uint64 const &);

	extern template CJsonOrdered::TCJsonValue(uint32 &&);
	extern template CJsonOrdered::TCJsonValue(uint32 &);
	extern template CJsonOrdered::TCJsonValue(uint32 const &);

	extern template CJsonOrdered::TCJsonValue(pfp64 &&);
	extern template CJsonOrdered::TCJsonValue(pfp64 &);
	extern template CJsonOrdered::TCJsonValue(pfp64 const &);

	extern template CJsonOrdered::TCJsonValue(pfp32 &&);
	extern template CJsonOrdered::TCJsonValue(pfp32 &);
	extern template CJsonOrdered::TCJsonValue(pfp32 const &);

	extern template CJsonOrdered::TCJsonValue(fp32 &&);
	extern template CJsonOrdered::TCJsonValue(fp32 &);
	extern template CJsonOrdered::TCJsonValue(fp32 const &);

	extern template CJsonOrdered::TCJsonValue(fp64 &&);
	extern template CJsonOrdered::TCJsonValue(fp64 &);
	extern template CJsonOrdered::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonOrdered::TCJsonValue(int &&);
	extern template CJsonOrdered::TCJsonValue(int &);
	extern template CJsonOrdered::TCJsonValue(int const &);
#endif
	extern template CJsonOrdered::TCJsonValue(bool &&);
	extern template CJsonOrdered::TCJsonValue(bool &);
	extern template CJsonOrdered::TCJsonValue(bool const &);


	extern template CJsonOrdered &CJsonOrdered::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CJsonOrdered &CJsonOrdered::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CJsonOrdered &CJsonOrdered::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CJsonOrdered &CJsonOrdered::f_Insert<int64>(int64 &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<int64 &>(int64 &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<int64 const &>(int64 const &);

	extern template CJsonOrdered &CJsonOrdered::f_Insert<int32>(int32 &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<int32 &>(int32 &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<int32 const &>(int32 const &);

	extern template CJsonOrdered &CJsonOrdered::f_Insert<uint64>(uint64 &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<uint64 &>(uint64 &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<uint64 const &>(uint64 const &);

	extern template CJsonOrdered &CJsonOrdered::f_Insert<uint32>(uint32 &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<uint32 &>(uint32 &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<uint32 const &>(uint32 const &);

	extern template CJsonOrdered &CJsonOrdered::f_Insert<pfp64>(pfp64 &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<pfp64 &>(pfp64 &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CJsonOrdered &CJsonOrdered::f_Insert<pfp32>(pfp32 &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<pfp32 &>(pfp32 &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CJsonOrdered &CJsonOrdered::f_Insert<fp32>(fp32 &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<fp32 &>(fp32 &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<fp32 const &>(fp32 const &);

	extern template CJsonOrdered &CJsonOrdered::f_Insert<fp64>(fp64 &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<fp64 &>(fp64 &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonOrdered &CJsonOrdered::f_Insert<int>(int &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<int &>(int &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<int const &>(int const &);
#endif
	extern template CJsonOrdered &CJsonOrdered::f_Insert<bool>(bool &&);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<bool &>(bool &);
	extern template CJsonOrdered &CJsonOrdered::f_Insert<bool const &>(bool const &);

	extern template CJsonOrdered &CJsonOrdered::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CJsonOrdered &CJsonOrdered::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CJsonOrdered &CJsonOrdered::operator = <CNullPtr>(CNullPtr &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <CNullPtr &>(CNullPtr &);
	extern template CJsonOrdered &CJsonOrdered::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CJsonOrdered &CJsonOrdered::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CJsonOrdered &CJsonOrdered::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CJsonOrdered &CJsonOrdered::operator = <int64>(int64 &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <int64 &>(int64 &);
	extern template CJsonOrdered &CJsonOrdered::operator = <int64 const &>(int64 const &);

	extern template CJsonOrdered &CJsonOrdered::operator = <int32>(int32 &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <int32 &>(int32 &);
	extern template CJsonOrdered &CJsonOrdered::operator = <int32 const &>(int32 const &);

	extern template CJsonOrdered &CJsonOrdered::operator = <uint64>(uint64 &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <uint64 &>(uint64 &);
	extern template CJsonOrdered &CJsonOrdered::operator = <uint64 const &>(uint64 const &);

	extern template CJsonOrdered &CJsonOrdered::operator = <uint32>(uint32 &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <uint32 &>(uint32 &);
	extern template CJsonOrdered &CJsonOrdered::operator = <uint32 const &>(uint32 const &);

	extern template CJsonOrdered &CJsonOrdered::operator = <pfp64>(pfp64 &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <pfp64 &>(pfp64 &);
	extern template CJsonOrdered &CJsonOrdered::operator = <pfp64 const &>(pfp64 const &);

	extern template CJsonOrdered &CJsonOrdered::operator = <pfp32>(pfp32 &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <pfp32 &>(pfp32 &);
	extern template CJsonOrdered &CJsonOrdered::operator = <pfp32 const &>(pfp32 const &);

	extern template CJsonOrdered &CJsonOrdered::operator = <fp32>(fp32 &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <fp32 &>(fp32 &);
	extern template CJsonOrdered &CJsonOrdered::operator = <fp32 const &>(fp32 const &);

	extern template CJsonOrdered &CJsonOrdered::operator = <fp64>(fp64 &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <fp64 &>(fp64 &);
	extern template CJsonOrdered &CJsonOrdered::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonOrdered &CJsonOrdered::operator = <int>(int &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <int &>(int &);
	extern template CJsonOrdered &CJsonOrdered::operator = <int const &>(int const &);
#endif
	extern template CJsonOrdered &CJsonOrdered::operator = <bool>(bool &&);
	extern template CJsonOrdered &CJsonOrdered::operator = <bool &>(bool &);
	extern template CJsonOrdered &CJsonOrdered::operator = <bool const &>(bool const &);

	extern template void CJsonOrdered::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonOrdered, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonOrdered, true>::CLocalOptions const &) const
	;
#endif
}
