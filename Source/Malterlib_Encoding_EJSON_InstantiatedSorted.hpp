// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_EJSON.h"

namespace NMib::NEncoding
{
	extern template struct NPrivate::TCJSONValueBase<TCEJSONValue, NPrivate::CEJSONExtraTypesSorted, false>;
	extern template struct TCJSONValue<CEJSONValueBaseSorted>;
	extern template struct TCEJSONValue<CEJSONValueBaseSorted>;
	extern template struct TCJSONObject<CEJSONSorted, false>;
	extern template struct NPrivate::TCObjectEntry<CEJSONSorted, false>;

#ifdef DMibEncodingJSONExternTemplate
	extern template CJSONValueEJSONSorted::TCJSONValue(CEJSONValueBaseOrdered const &);
	extern template CJSONValueEJSONSorted::TCJSONValue(CEJSONValueBaseOrdered const &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(CEJSONValueBaseOrdered &&);

	extern template TCEJSONValue<CEJSONValueBaseSorted> CEJSONSorted::fs_FromCompatible<CEJSONValueBaseOrdered>(TCEJSONValue<CEJSONValueBaseOrdered> const &);
	extern template TCEJSONValue<CEJSONValueBaseSorted> CEJSONSorted::fs_FromCompatible<CEJSONValueBaseOrdered>(TCEJSONValue<CEJSONValueBaseOrdered> &&);
	extern template TCEJSONValue<CEJSONValueBaseSorted> CEJSONSorted::fs_FromCompatible<CEJSONValueBaseOrdered>(TCEJSONValue<CEJSONValueBaseOrdered> const &&);

	extern template CEJSONSorted::TCEJSONValue(TCEJSONValue<CEJSONValueBaseOrdered> const &);
	extern template CEJSONSorted::TCEJSONValue(TCEJSONValue<CEJSONValueBaseOrdered> &&);
	extern template CEJSONSorted::TCEJSONValue(TCEJSONValue<CEJSONValueBaseOrdered> const &&);

	extern template CEJSONValueBaseSorted::TCJSONValueBase(CEJSONValueBaseOrdered const &);
	extern template CEJSONValueBaseSorted::TCJSONValueBase(CEJSONValueBaseOrdered &);
	extern template CEJSONValueBaseSorted::TCJSONValueBase(CEJSONValueBaseOrdered &&);

	extern template CJSONValueEJSONSorted::TCJSONValue(CNullPtr &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(CNullPtr &);
	extern template CJSONValueEJSONSorted::TCJSONValue(CNullPtr const &);

	extern template CJSONValueEJSONSorted::TCJSONValue(NStr::CStr &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(NStr::CStr &);
	extern template CJSONValueEJSONSorted::TCJSONValue(NStr::CStr const &);

	extern template CJSONValueEJSONSorted::TCJSONValue(int64 &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(int64 &);
	extern template CJSONValueEJSONSorted::TCJSONValue(int64 const &);

	extern template CJSONValueEJSONSorted::TCJSONValue(int32 &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(int32 &);
	extern template CJSONValueEJSONSorted::TCJSONValue(int32 const &);

	extern template CJSONValueEJSONSorted::TCJSONValue(uint64 &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(uint64 &);
	extern template CJSONValueEJSONSorted::TCJSONValue(uint64 const &);

	extern template CJSONValueEJSONSorted::TCJSONValue(uint32 &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(uint32 &);
	extern template CJSONValueEJSONSorted::TCJSONValue(uint32 const &);

	extern template CJSONValueEJSONSorted::TCJSONValue(pfp64 &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(pfp64 &);
	extern template CJSONValueEJSONSorted::TCJSONValue(pfp64 const &);

	extern template CJSONValueEJSONSorted::TCJSONValue(pfp32 &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(pfp32 &);
	extern template CJSONValueEJSONSorted::TCJSONValue(pfp32 const &);

	extern template CJSONValueEJSONSorted::TCJSONValue(fp32 &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(fp32 &);
	extern template CJSONValueEJSONSorted::TCJSONValue(fp32 const &);

	extern template CJSONValueEJSONSorted::TCJSONValue(fp64 &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(fp64 &);
	extern template CJSONValueEJSONSorted::TCJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJSONValueEJSONSorted::TCJSONValue(int &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(int &);
	extern template CJSONValueEJSONSorted::TCJSONValue(int const &);
#endif
	extern template CJSONValueEJSONSorted::TCJSONValue(bool &&);
	extern template CJSONValueEJSONSorted::TCJSONValue(bool &);
	extern template CJSONValueEJSONSorted::TCJSONValue(bool const &);

	extern template CEJSONSorted::TCEJSONValue(EJSONType &&);
	extern template CEJSONSorted::TCEJSONValue(EJSONType &);
	extern template CEJSONSorted::TCEJSONValue(EJSONType const &);

	extern template CEJSONSorted::TCEJSONValue(ch8 const *&&);
	extern template CEJSONSorted::TCEJSONValue(ch8 const *&);
	extern template CEJSONSorted::TCEJSONValue(ch8 const *const &);

	extern template CEJSONSorted::TCEJSONValue(CNullPtr &&);
	extern template CEJSONSorted::TCEJSONValue(CNullPtr &);
	extern template CEJSONSorted::TCEJSONValue(CNullPtr const &);

	extern template CEJSONSorted::TCEJSONValue(NStr::CStr &&);
	extern template CEJSONSorted::TCEJSONValue(NStr::CStr &);
	extern template CEJSONSorted::TCEJSONValue(NStr::CStr const &);

	extern template CEJSONSorted::TCEJSONValue(int64 &&);
	extern template CEJSONSorted::TCEJSONValue(int64 &);
	extern template CEJSONSorted::TCEJSONValue(int64 const &);

	extern template CEJSONSorted::TCEJSONValue(int32 &&);
	extern template CEJSONSorted::TCEJSONValue(int32 &);
	extern template CEJSONSorted::TCEJSONValue(int32 const &);

	extern template CEJSONSorted::TCEJSONValue(uint64 &&);
	extern template CEJSONSorted::TCEJSONValue(uint64 &);
	extern template CEJSONSorted::TCEJSONValue(uint64 const &);

	extern template CEJSONSorted::TCEJSONValue(uint32 &&);
	extern template CEJSONSorted::TCEJSONValue(uint32 &);
	extern template CEJSONSorted::TCEJSONValue(uint32 const &);

	extern template CEJSONSorted::TCEJSONValue(pfp64 &&);
	extern template CEJSONSorted::TCEJSONValue(pfp64 &);
	extern template CEJSONSorted::TCEJSONValue(pfp64 const &);

	extern template CEJSONSorted::TCEJSONValue(pfp32 &&);
	extern template CEJSONSorted::TCEJSONValue(pfp32 &);
	extern template CEJSONSorted::TCEJSONValue(pfp32 const &);

	extern template CEJSONSorted::TCEJSONValue(fp32 &&);
	extern template CEJSONSorted::TCEJSONValue(fp32 &);
	extern template CEJSONSorted::TCEJSONValue(fp32 const &);

	extern template CEJSONSorted::TCEJSONValue(fp64 &&);
	extern template CEJSONSorted::TCEJSONValue(fp64 &);
	extern template CEJSONSorted::TCEJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJSONSorted::TCEJSONValue(int &&);
	extern template CEJSONSorted::TCEJSONValue(int &);
	extern template CEJSONSorted::TCEJSONValue(int const &);
#endif
	extern template CEJSONSorted::TCEJSONValue(bool &&);
	extern template CEJSONSorted::TCEJSONValue(bool &);
	extern template CEJSONSorted::TCEJSONValue(bool const &);

	//
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int64>(int64 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int64 &>(int64 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int64 const &>(int64 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int32>(int32 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int32 &>(int32 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int32 const &>(int32 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<uint64>(uint64 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<uint64 &>(uint64 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<uint64 const &>(uint64 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<uint32>(uint32 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<uint32 &>(uint32 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<uint32 const &>(uint32 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<pfp64>(pfp64 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<pfp64 &>(pfp64 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<pfp32>(pfp32 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<pfp32 &>(pfp32 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<fp32>(fp32 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<fp32 &>(fp32 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<fp32 const &>(fp32 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<fp64>(fp64 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<fp64 &>(fp64 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int>(int &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int &>(int &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int const &>(int const &);
#endif
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<bool>(bool &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<bool &>(bool &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<bool const &>(bool const &);
#endif

	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <CNullPtr>(CNullPtr &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <CNullPtr &>(CNullPtr &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <int64>(int64 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <int64 &>(int64 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <int64 const &>(int64 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <int32>(int32 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <int32 &>(int32 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <int32 const &>(int32 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <uint64>(uint64 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <uint64 &>(uint64 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <uint64 const &>(uint64 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <uint32>(uint32 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <uint32 &>(uint32 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <uint32 const &>(uint32 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <pfp64>(pfp64 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <pfp64 &>(pfp64 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <pfp64 const &>(pfp64 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <pfp32>(pfp32 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <pfp32 &>(pfp32 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <pfp32 const &>(pfp32 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <fp32>(fp32 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <fp32 &>(fp32 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <fp32 const &>(fp32 const &);

	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <fp64>(fp64 &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <fp64 &>(fp64 &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <int>(int &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <int &>(int &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <int const &>(int const &);
#endif
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <bool>(bool &&);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <bool &>(bool &);
	extern template CEJSONSorted &CJSONValueEJSONSorted::operator = <bool const &>(bool const &);

	extern template void CJSONValueEJSONSorted::f_Format
		<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONSorted, false>::CLocalOptions>
		(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONSorted, false>::CLocalOptions const &) const
	;

	extern template void CJSONValueEJSONSorted::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONSorted, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONSorted, false>::CLocalOptions const&) const
	;
}

#include "Malterlib_Encoding_EJSON_Value.hpp"
