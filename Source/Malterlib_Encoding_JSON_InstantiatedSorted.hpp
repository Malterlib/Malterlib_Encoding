// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJSONExternTemplate
	extern template struct NPrivate::TCJSONValueBase<TCJSONValue, NPrivate::CJSONExtraTypes, false>;
	extern template struct TCJSONValue<NPrivate::TCJSONValueBase<TCJSONValue, NPrivate::CJSONExtraTypes, false>>;
	extern template struct TCJSONObject<CJSONSorted, false>;
	extern template struct NPrivate::TCObjectEntry<CJSONSorted, false>;

	extern template CJSONValueJSONSorted::TCJSONValue(CJSONValueBaseOrdered const &);
	extern template CJSONValueJSONSorted::TCJSONValue(CJSONValueBaseOrdered const &&);
	extern template CJSONValueJSONSorted::TCJSONValue(CJSONValueBaseOrdered &&);

	extern template TCJSONValue<CJSONValueBaseSorted> CJSONSorted::fs_FromCompatible<CJSONValueBaseOrdered>(TCJSONValue<CJSONValueBaseOrdered> const &);
	extern template TCJSONValue<CJSONValueBaseSorted> CJSONSorted::fs_FromCompatible<CJSONValueBaseOrdered>(TCJSONValue<CJSONValueBaseOrdered> &&);
	extern template TCJSONValue<CJSONValueBaseSorted> CJSONSorted::fs_FromCompatible<CJSONValueBaseOrdered>(TCJSONValue<CJSONValueBaseOrdered> const &&);

	extern template CJSONSorted::TCJSONValue(TCJSONValue<CJSONValueBaseOrdered> const &);
	extern template CJSONSorted::TCJSONValue(TCJSONValue<CJSONValueBaseOrdered> &&);
	extern template CJSONSorted::TCJSONValue(TCJSONValue<CJSONValueBaseOrdered> const &&);

	extern template CJSONValueBaseSorted::TCJSONValueBase(CJSONValueBaseOrdered const &);
	extern template CJSONValueBaseSorted::TCJSONValueBase(CJSONValueBaseOrdered &);
	extern template CJSONValueBaseSorted::TCJSONValueBase(CJSONValueBaseOrdered &&);

	extern template CJSONSorted::TCJSONValue(CNullPtr &&);
	extern template CJSONSorted::TCJSONValue(CNullPtr &);
	extern template CJSONSorted::TCJSONValue(CNullPtr const &);

	extern template CJSONSorted::TCJSONValue(NStr::CStr &&);
	extern template CJSONSorted::TCJSONValue(NStr::CStr &);
	extern template CJSONSorted::TCJSONValue(NStr::CStr const &);

	extern template CJSONSorted::TCJSONValue(int64 &&);
	extern template CJSONSorted::TCJSONValue(int64 &);
	extern template CJSONSorted::TCJSONValue(int64 const &);

	extern template CJSONSorted::TCJSONValue(int32 &&);
	extern template CJSONSorted::TCJSONValue(int32 &);
	extern template CJSONSorted::TCJSONValue(int32 const &);

	extern template CJSONSorted::TCJSONValue(uint64 &&);
	extern template CJSONSorted::TCJSONValue(uint64 &);
	extern template CJSONSorted::TCJSONValue(uint64 const &);

	extern template CJSONSorted::TCJSONValue(uint32 &&);
	extern template CJSONSorted::TCJSONValue(uint32 &);
	extern template CJSONSorted::TCJSONValue(uint32 const &);

	extern template CJSONSorted::TCJSONValue(pfp64 &&);
	extern template CJSONSorted::TCJSONValue(pfp64 &);
	extern template CJSONSorted::TCJSONValue(pfp64 const &);

	extern template CJSONSorted::TCJSONValue(pfp32 &&);
	extern template CJSONSorted::TCJSONValue(pfp32 &);
	extern template CJSONSorted::TCJSONValue(pfp32 const &);

	extern template CJSONSorted::TCJSONValue(fp32 &&);
	extern template CJSONSorted::TCJSONValue(fp32 &);
	extern template CJSONSorted::TCJSONValue(fp32 const &);

	extern template CJSONSorted::TCJSONValue(fp64 &&);
	extern template CJSONSorted::TCJSONValue(fp64 &);
	extern template CJSONSorted::TCJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJSONSorted::TCJSONValue(int &&);
	extern template CJSONSorted::TCJSONValue(int &);
	extern template CJSONSorted::TCJSONValue(int const &);
#endif
	extern template CJSONSorted::TCJSONValue(bool &&);
	extern template CJSONSorted::TCJSONValue(bool &);
	extern template CJSONSorted::TCJSONValue(bool const &);


	extern template CJSONSorted &CJSONSorted::f_Insert<NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	extern template CJSONSorted &CJSONSorted::f_Insert<NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	extern template CJSONSorted &CJSONSorted::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CJSONSorted &CJSONSorted::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CJSONSorted &CJSONSorted::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CJSONSorted &CJSONSorted::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CJSONSorted &CJSONSorted::f_Insert<int64>(int64 &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<int64 &>(int64 &);
	extern template CJSONSorted &CJSONSorted::f_Insert<int64 const &>(int64 const &);

	extern template CJSONSorted &CJSONSorted::f_Insert<int32>(int32 &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<int32 &>(int32 &);
	extern template CJSONSorted &CJSONSorted::f_Insert<int32 const &>(int32 const &);

	extern template CJSONSorted &CJSONSorted::f_Insert<uint64>(uint64 &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<uint64 &>(uint64 &);
	extern template CJSONSorted &CJSONSorted::f_Insert<uint64 const &>(uint64 const &);

	extern template CJSONSorted &CJSONSorted::f_Insert<uint32>(uint32 &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<uint32 &>(uint32 &);
	extern template CJSONSorted &CJSONSorted::f_Insert<uint32 const &>(uint32 const &);

	extern template CJSONSorted &CJSONSorted::f_Insert<pfp64>(pfp64 &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<pfp64 &>(pfp64 &);
	extern template CJSONSorted &CJSONSorted::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CJSONSorted &CJSONSorted::f_Insert<pfp32>(pfp32 &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<pfp32 &>(pfp32 &);
	extern template CJSONSorted &CJSONSorted::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CJSONSorted &CJSONSorted::f_Insert<fp32>(fp32 &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<fp32 &>(fp32 &);
	extern template CJSONSorted &CJSONSorted::f_Insert<fp32 const &>(fp32 const &);

	extern template CJSONSorted &CJSONSorted::f_Insert<fp64>(fp64 &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<fp64 &>(fp64 &);
	extern template CJSONSorted &CJSONSorted::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJSONSorted &CJSONSorted::f_Insert<int>(int &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<int &>(int &);
	extern template CJSONSorted &CJSONSorted::f_Insert<int const &>(int const &);
#endif
	extern template CJSONSorted &CJSONSorted::f_Insert<bool>(bool &&);
	extern template CJSONSorted &CJSONSorted::f_Insert<bool &>(bool &);
	extern template CJSONSorted &CJSONSorted::f_Insert<bool const &>(bool const &);

	extern template CJSONSorted &CJSONSorted::operator = <NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	extern template CJSONSorted &CJSONSorted::operator = <NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	extern template CJSONSorted &CJSONSorted::operator = <NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	extern template CJSONSorted &CJSONSorted::operator = <CNullPtr>(CNullPtr &&);
	extern template CJSONSorted &CJSONSorted::operator = <CNullPtr &>(CNullPtr &);
	extern template CJSONSorted &CJSONSorted::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CJSONSorted &CJSONSorted::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CJSONSorted &CJSONSorted::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CJSONSorted &CJSONSorted::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CJSONSorted &CJSONSorted::operator = <int64>(int64 &&);
	extern template CJSONSorted &CJSONSorted::operator = <int64 &>(int64 &);
	extern template CJSONSorted &CJSONSorted::operator = <int64 const &>(int64 const &);

	extern template CJSONSorted &CJSONSorted::operator = <int32>(int32 &&);
	extern template CJSONSorted &CJSONSorted::operator = <int32 &>(int32 &);
	extern template CJSONSorted &CJSONSorted::operator = <int32 const &>(int32 const &);

	extern template CJSONSorted &CJSONSorted::operator = <uint64>(uint64 &&);
	extern template CJSONSorted &CJSONSorted::operator = <uint64 &>(uint64 &);
	extern template CJSONSorted &CJSONSorted::operator = <uint64 const &>(uint64 const &);

	extern template CJSONSorted &CJSONSorted::operator = <uint32>(uint32 &&);
	extern template CJSONSorted &CJSONSorted::operator = <uint32 &>(uint32 &);
	extern template CJSONSorted &CJSONSorted::operator = <uint32 const &>(uint32 const &);

	extern template CJSONSorted &CJSONSorted::operator = <pfp64>(pfp64 &&);
	extern template CJSONSorted &CJSONSorted::operator = <pfp64 &>(pfp64 &);
	extern template CJSONSorted &CJSONSorted::operator = <pfp64 const &>(pfp64 const &);

	extern template CJSONSorted &CJSONSorted::operator = <pfp32>(pfp32 &&);
	extern template CJSONSorted &CJSONSorted::operator = <pfp32 &>(pfp32 &);
	extern template CJSONSorted &CJSONSorted::operator = <pfp32 const &>(pfp32 const &);

	extern template CJSONSorted &CJSONSorted::operator = <fp32>(fp32 &&);
	extern template CJSONSorted &CJSONSorted::operator = <fp32 &>(fp32 &);
	extern template CJSONSorted &CJSONSorted::operator = <fp32 const &>(fp32 const &);

	extern template CJSONSorted &CJSONSorted::operator = <fp64>(fp64 &&);
	extern template CJSONSorted &CJSONSorted::operator = <fp64 &>(fp64 &);
	extern template CJSONSorted &CJSONSorted::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJSONSorted &CJSONSorted::operator = <int>(int &&);
	extern template CJSONSorted &CJSONSorted::operator = <int &>(int &);
	extern template CJSONSorted &CJSONSorted::operator = <int const &>(int const &);
#endif
	extern template CJSONSorted &CJSONSorted::operator = <bool>(bool &&);
	extern template CJSONSorted &CJSONSorted::operator = <bool &>(bool &);
	extern template CJSONSorted &CJSONSorted::operator = <bool const &>(bool const &);

	extern template void CJSONSorted::f_Format
		<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONSorted, false>::CLocalOptions>
		(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONSorted, false>::CLocalOptions const &) const
	;

	extern template void CJSONSorted::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONSorted, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONSorted, false>::CLocalOptions const&) const
	;
#endif
}
