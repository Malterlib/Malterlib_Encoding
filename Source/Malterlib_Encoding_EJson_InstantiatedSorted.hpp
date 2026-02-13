// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_EJson.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	extern template struct NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesSorted, false>;
	extern template struct TCJsonValue<CEJsonValueBaseSorted>;
	extern template struct TCEJsonValue<CEJsonValueBaseSorted>;
	extern template struct TCJsonObject<CEJsonSorted, false>;
	extern template struct NPrivate::TCObjectEntry<CEJsonSorted, false>;

	extern template CJsonValueEJsonSorted::TCJsonValue(CEJsonValueBaseOrdered const &);
	extern template CJsonValueEJsonSorted::TCJsonValue(CEJsonValueBaseOrdered const &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(CEJsonValueBaseOrdered &&);

	extern template TCEJsonValue<CEJsonValueBaseSorted> CEJsonSorted::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	extern template TCEJsonValue<CEJsonValueBaseSorted> CEJsonSorted::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	extern template TCEJsonValue<CEJsonValueBaseSorted> CEJsonSorted::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &&);

	extern template CEJsonSorted::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	extern template CEJsonSorted::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	extern template CEJsonSorted::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &&);

	extern template CEJsonValueBaseSorted::TCJsonValueBase(CEJsonValueBaseOrdered const &);
	extern template CEJsonValueBaseSorted::TCJsonValueBase(CEJsonValueBaseOrdered &);
	extern template CEJsonValueBaseSorted::TCJsonValueBase(CEJsonValueBaseOrdered &&);

	extern template CJsonValueEJsonSorted::TCJsonValue(CNullPtr &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(CNullPtr &);
	extern template CJsonValueEJsonSorted::TCJsonValue(CNullPtr const &);

	extern template CJsonValueEJsonSorted::TCJsonValue(NStr::CStr &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(NStr::CStr &);
	extern template CJsonValueEJsonSorted::TCJsonValue(NStr::CStr const &);

	extern template CJsonValueEJsonSorted::TCJsonValue(int64 &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(int64 &);
	extern template CJsonValueEJsonSorted::TCJsonValue(int64 const &);

	extern template CJsonValueEJsonSorted::TCJsonValue(int32 &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(int32 &);
	extern template CJsonValueEJsonSorted::TCJsonValue(int32 const &);

	extern template CJsonValueEJsonSorted::TCJsonValue(uint64 &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(uint64 &);
	extern template CJsonValueEJsonSorted::TCJsonValue(uint64 const &);

	extern template CJsonValueEJsonSorted::TCJsonValue(uint32 &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(uint32 &);
	extern template CJsonValueEJsonSorted::TCJsonValue(uint32 const &);

	extern template CJsonValueEJsonSorted::TCJsonValue(pfp64 &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(pfp64 &);
	extern template CJsonValueEJsonSorted::TCJsonValue(pfp64 const &);

	extern template CJsonValueEJsonSorted::TCJsonValue(pfp32 &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(pfp32 &);
	extern template CJsonValueEJsonSorted::TCJsonValue(pfp32 const &);

	extern template CJsonValueEJsonSorted::TCJsonValue(fp32 &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(fp32 &);
	extern template CJsonValueEJsonSorted::TCJsonValue(fp32 const &);

	extern template CJsonValueEJsonSorted::TCJsonValue(fp64 &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(fp64 &);
	extern template CJsonValueEJsonSorted::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonValueEJsonSorted::TCJsonValue(int &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(int &);
	extern template CJsonValueEJsonSorted::TCJsonValue(int const &);
#endif
	extern template CJsonValueEJsonSorted::TCJsonValue(bool &&);
	extern template CJsonValueEJsonSorted::TCJsonValue(bool &);
	extern template CJsonValueEJsonSorted::TCJsonValue(bool const &);

	extern template CEJsonSorted::TCEJsonValue(EJsonType &&);
	extern template CEJsonSorted::TCEJsonValue(EJsonType &);
	extern template CEJsonSorted::TCEJsonValue(EJsonType const &);

	extern template CEJsonSorted::TCEJsonValue(ch8 const *&&);
	extern template CEJsonSorted::TCEJsonValue(ch8 const *&);
	extern template CEJsonSorted::TCEJsonValue(ch8 const *const &);

	extern template CEJsonSorted::TCEJsonValue(CNullPtr &&);
	extern template CEJsonSorted::TCEJsonValue(CNullPtr &);
	extern template CEJsonSorted::TCEJsonValue(CNullPtr const &);

	extern template CEJsonSorted::TCEJsonValue(NStr::CStr &&);
	extern template CEJsonSorted::TCEJsonValue(NStr::CStr &);
	extern template CEJsonSorted::TCEJsonValue(NStr::CStr const &);

	extern template CEJsonSorted::TCEJsonValue(int64 &&);
	extern template CEJsonSorted::TCEJsonValue(int64 &);
	extern template CEJsonSorted::TCEJsonValue(int64 const &);

	extern template CEJsonSorted::TCEJsonValue(int32 &&);
	extern template CEJsonSorted::TCEJsonValue(int32 &);
	extern template CEJsonSorted::TCEJsonValue(int32 const &);

	extern template CEJsonSorted::TCEJsonValue(uint64 &&);
	extern template CEJsonSorted::TCEJsonValue(uint64 &);
	extern template CEJsonSorted::TCEJsonValue(uint64 const &);

	extern template CEJsonSorted::TCEJsonValue(uint32 &&);
	extern template CEJsonSorted::TCEJsonValue(uint32 &);
	extern template CEJsonSorted::TCEJsonValue(uint32 const &);

	extern template CEJsonSorted::TCEJsonValue(pfp64 &&);
	extern template CEJsonSorted::TCEJsonValue(pfp64 &);
	extern template CEJsonSorted::TCEJsonValue(pfp64 const &);

	extern template CEJsonSorted::TCEJsonValue(pfp32 &&);
	extern template CEJsonSorted::TCEJsonValue(pfp32 &);
	extern template CEJsonSorted::TCEJsonValue(pfp32 const &);

	extern template CEJsonSorted::TCEJsonValue(fp32 &&);
	extern template CEJsonSorted::TCEJsonValue(fp32 &);
	extern template CEJsonSorted::TCEJsonValue(fp32 const &);

	extern template CEJsonSorted::TCEJsonValue(fp64 &&);
	extern template CEJsonSorted::TCEJsonValue(fp64 &);
	extern template CEJsonSorted::TCEJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonSorted::TCEJsonValue(int &&);
	extern template CEJsonSorted::TCEJsonValue(int &);
	extern template CEJsonSorted::TCEJsonValue(int const &);
#endif
	extern template CEJsonSorted::TCEJsonValue(bool &&);
	extern template CEJsonSorted::TCEJsonValue(bool &);
	extern template CEJsonSorted::TCEJsonValue(bool const &);

	//
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int64>(int64 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int64 &>(int64 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int64 const &>(int64 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int32>(int32 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int32 &>(int32 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int32 const &>(int32 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<uint64>(uint64 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<uint64 &>(uint64 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<uint64 const &>(uint64 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<uint32>(uint32 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<uint32 &>(uint32 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<uint32 const &>(uint32 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<pfp64>(pfp64 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<pfp64 &>(pfp64 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<pfp32>(pfp32 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<pfp32 &>(pfp32 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<fp32>(fp32 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<fp32 &>(fp32 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<fp32 const &>(fp32 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<fp64>(fp64 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<fp64 &>(fp64 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int>(int &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int &>(int &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int const &>(int const &);
#endif
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<bool>(bool &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<bool &>(bool &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<bool const &>(bool const &);
#endif

	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <CNullPtr>(CNullPtr &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <CNullPtr &>(CNullPtr &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <int64>(int64 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <int64 &>(int64 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <int64 const &>(int64 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <int32>(int32 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <int32 &>(int32 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <int32 const &>(int32 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <uint64>(uint64 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <uint64 &>(uint64 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <uint64 const &>(uint64 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <uint32>(uint32 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <uint32 &>(uint32 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <uint32 const &>(uint32 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <pfp64>(pfp64 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <pfp64 &>(pfp64 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <pfp64 const &>(pfp64 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <pfp32>(pfp32 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <pfp32 &>(pfp32 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <pfp32 const &>(pfp32 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <fp32>(fp32 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <fp32 &>(fp32 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <fp32 const &>(fp32 const &);

	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <fp64>(fp64 &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <fp64 &>(fp64 &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <int>(int &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <int &>(int &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <int const &>(int const &);
#endif
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <bool>(bool &&);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <bool &>(bool &);
	extern template CEJsonSorted &CJsonValueEJsonSorted::operator = <bool const &>(bool const &);

	extern template void CJsonValueEJsonSorted::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonSorted, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonSorted, false>::CLocalOptions const &) const
	;
}

#include "Malterlib_Encoding_EJson_Value.hpp"
