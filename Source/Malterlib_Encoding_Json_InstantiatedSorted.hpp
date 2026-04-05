// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	extern template struct NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, false>;
	extern template struct TCJsonValue<NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, false>>;
	extern template struct TCJsonObject<CJsonSorted, false>;
	extern template struct NPrivate::TCObjectEntry<CJsonSorted, false>;

	extern template CJsonValueJsonSorted::TCJsonValue(CJsonValueBaseOrdered const &);
	extern template CJsonValueJsonSorted::TCJsonValue(CJsonValueBaseOrdered const &&);
	extern template CJsonValueJsonSorted::TCJsonValue(CJsonValueBaseOrdered &&);

	extern template TCJsonValue<CJsonValueBaseSorted> CJsonSorted::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &);
	extern template TCJsonValue<CJsonValueBaseSorted> CJsonSorted::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> &&);
	extern template TCJsonValue<CJsonValueBaseSorted> CJsonSorted::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &&);

	extern template CJsonSorted::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &);
	extern template CJsonSorted::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> &&);
	extern template CJsonSorted::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &&);

	extern template CJsonValueBaseSorted::TCJsonValueBase(CJsonValueBaseOrdered const &);
	extern template CJsonValueBaseSorted::TCJsonValueBase(CJsonValueBaseOrdered &);
	extern template CJsonValueBaseSorted::TCJsonValueBase(CJsonValueBaseOrdered &&);

	extern template CJsonSorted::TCJsonValue(CNullPtr &&);
	extern template CJsonSorted::TCJsonValue(CNullPtr &);
	extern template CJsonSorted::TCJsonValue(CNullPtr const &);

	extern template CJsonSorted::TCJsonValue(NStr::CStr &&);
	extern template CJsonSorted::TCJsonValue(NStr::CStr &);
	extern template CJsonSorted::TCJsonValue(NStr::CStr const &);

	extern template CJsonSorted::TCJsonValue(int64 &&);
	extern template CJsonSorted::TCJsonValue(int64 &);
	extern template CJsonSorted::TCJsonValue(int64 const &);

	extern template CJsonSorted::TCJsonValue(int32 &&);
	extern template CJsonSorted::TCJsonValue(int32 &);
	extern template CJsonSorted::TCJsonValue(int32 const &);

	extern template CJsonSorted::TCJsonValue(uint64 &&);
	extern template CJsonSorted::TCJsonValue(uint64 &);
	extern template CJsonSorted::TCJsonValue(uint64 const &);

	extern template CJsonSorted::TCJsonValue(uint32 &&);
	extern template CJsonSorted::TCJsonValue(uint32 &);
	extern template CJsonSorted::TCJsonValue(uint32 const &);

	extern template CJsonSorted::TCJsonValue(pfp64 &&);
	extern template CJsonSorted::TCJsonValue(pfp64 &);
	extern template CJsonSorted::TCJsonValue(pfp64 const &);

	extern template CJsonSorted::TCJsonValue(pfp32 &&);
	extern template CJsonSorted::TCJsonValue(pfp32 &);
	extern template CJsonSorted::TCJsonValue(pfp32 const &);

	extern template CJsonSorted::TCJsonValue(fp32 &&);
	extern template CJsonSorted::TCJsonValue(fp32 &);
	extern template CJsonSorted::TCJsonValue(fp32 const &);

	extern template CJsonSorted::TCJsonValue(fp64 &&);
	extern template CJsonSorted::TCJsonValue(fp64 &);
	extern template CJsonSorted::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonSorted::TCJsonValue(int &&);
	extern template CJsonSorted::TCJsonValue(int &);
	extern template CJsonSorted::TCJsonValue(int const &);
#endif
	extern template CJsonSorted::TCJsonValue(bool &&);
	extern template CJsonSorted::TCJsonValue(bool &);
	extern template CJsonSorted::TCJsonValue(bool const &);


	extern template CJsonSorted &CJsonSorted::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CJsonSorted &CJsonSorted::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CJsonSorted &CJsonSorted::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CJsonSorted &CJsonSorted::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CJsonSorted &CJsonSorted::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CJsonSorted &CJsonSorted::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CJsonSorted &CJsonSorted::f_Insert<int64>(int64 &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<int64 &>(int64 &);
	extern template CJsonSorted &CJsonSorted::f_Insert<int64 const &>(int64 const &);

	extern template CJsonSorted &CJsonSorted::f_Insert<int32>(int32 &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<int32 &>(int32 &);
	extern template CJsonSorted &CJsonSorted::f_Insert<int32 const &>(int32 const &);

	extern template CJsonSorted &CJsonSorted::f_Insert<uint64>(uint64 &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<uint64 &>(uint64 &);
	extern template CJsonSorted &CJsonSorted::f_Insert<uint64 const &>(uint64 const &);

	extern template CJsonSorted &CJsonSorted::f_Insert<uint32>(uint32 &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<uint32 &>(uint32 &);
	extern template CJsonSorted &CJsonSorted::f_Insert<uint32 const &>(uint32 const &);

	extern template CJsonSorted &CJsonSorted::f_Insert<pfp64>(pfp64 &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<pfp64 &>(pfp64 &);
	extern template CJsonSorted &CJsonSorted::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CJsonSorted &CJsonSorted::f_Insert<pfp32>(pfp32 &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<pfp32 &>(pfp32 &);
	extern template CJsonSorted &CJsonSorted::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CJsonSorted &CJsonSorted::f_Insert<fp32>(fp32 &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<fp32 &>(fp32 &);
	extern template CJsonSorted &CJsonSorted::f_Insert<fp32 const &>(fp32 const &);

	extern template CJsonSorted &CJsonSorted::f_Insert<fp64>(fp64 &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<fp64 &>(fp64 &);
	extern template CJsonSorted &CJsonSorted::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonSorted &CJsonSorted::f_Insert<int>(int &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<int &>(int &);
	extern template CJsonSorted &CJsonSorted::f_Insert<int const &>(int const &);
#endif
	extern template CJsonSorted &CJsonSorted::f_Insert<bool>(bool &&);
	extern template CJsonSorted &CJsonSorted::f_Insert<bool &>(bool &);
	extern template CJsonSorted &CJsonSorted::f_Insert<bool const &>(bool const &);

	extern template CJsonSorted &CJsonSorted::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CJsonSorted &CJsonSorted::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CJsonSorted &CJsonSorted::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CJsonSorted &CJsonSorted::operator = <CNullPtr>(CNullPtr &&);
	extern template CJsonSorted &CJsonSorted::operator = <CNullPtr &>(CNullPtr &);
	extern template CJsonSorted &CJsonSorted::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CJsonSorted &CJsonSorted::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CJsonSorted &CJsonSorted::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CJsonSorted &CJsonSorted::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CJsonSorted &CJsonSorted::operator = <int64>(int64 &&);
	extern template CJsonSorted &CJsonSorted::operator = <int64 &>(int64 &);
	extern template CJsonSorted &CJsonSorted::operator = <int64 const &>(int64 const &);

	extern template CJsonSorted &CJsonSorted::operator = <int32>(int32 &&);
	extern template CJsonSorted &CJsonSorted::operator = <int32 &>(int32 &);
	extern template CJsonSorted &CJsonSorted::operator = <int32 const &>(int32 const &);

	extern template CJsonSorted &CJsonSorted::operator = <uint64>(uint64 &&);
	extern template CJsonSorted &CJsonSorted::operator = <uint64 &>(uint64 &);
	extern template CJsonSorted &CJsonSorted::operator = <uint64 const &>(uint64 const &);

	extern template CJsonSorted &CJsonSorted::operator = <uint32>(uint32 &&);
	extern template CJsonSorted &CJsonSorted::operator = <uint32 &>(uint32 &);
	extern template CJsonSorted &CJsonSorted::operator = <uint32 const &>(uint32 const &);

	extern template CJsonSorted &CJsonSorted::operator = <pfp64>(pfp64 &&);
	extern template CJsonSorted &CJsonSorted::operator = <pfp64 &>(pfp64 &);
	extern template CJsonSorted &CJsonSorted::operator = <pfp64 const &>(pfp64 const &);

	extern template CJsonSorted &CJsonSorted::operator = <pfp32>(pfp32 &&);
	extern template CJsonSorted &CJsonSorted::operator = <pfp32 &>(pfp32 &);
	extern template CJsonSorted &CJsonSorted::operator = <pfp32 const &>(pfp32 const &);

	extern template CJsonSorted &CJsonSorted::operator = <fp32>(fp32 &&);
	extern template CJsonSorted &CJsonSorted::operator = <fp32 &>(fp32 &);
	extern template CJsonSorted &CJsonSorted::operator = <fp32 const &>(fp32 const &);

	extern template CJsonSorted &CJsonSorted::operator = <fp64>(fp64 &&);
	extern template CJsonSorted &CJsonSorted::operator = <fp64 &>(fp64 &);
	extern template CJsonSorted &CJsonSorted::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonSorted &CJsonSorted::operator = <int>(int &&);
	extern template CJsonSorted &CJsonSorted::operator = <int &>(int &);
	extern template CJsonSorted &CJsonSorted::operator = <int const &>(int const &);
#endif
	extern template CJsonSorted &CJsonSorted::operator = <bool>(bool &&);
	extern template CJsonSorted &CJsonSorted::operator = <bool &>(bool &);
	extern template CJsonSorted &CJsonSorted::operator = <bool const &>(bool const &);

	extern template void CJsonSorted::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSorted, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSorted, false>::CLocalOptions const &) const
	;
#endif
}
