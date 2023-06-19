// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib::NEncoding
{
	extern template struct NPrivate::TCJSONValueBase<TCJSONValue, NPrivate::CJSONExtraTypes, true>;
	extern template struct TCJSONValue<NPrivate::TCJSONValueBase<TCJSONValue, NPrivate::CJSONExtraTypes, true>>;
	extern template struct TCJSONObject<CJSONOrdered, true>;
	extern template struct NPrivate::TCObjectEntry<CJSONOrdered, true>;

#ifdef DMibEncodingJSONExternTemplate
	extern template CJSONValueJSONOrdered::TCJSONValue(CJSONValueBaseSorted const &);
	extern template CJSONValueJSONOrdered::TCJSONValue(CJSONValueBaseSorted const &&);
	extern template CJSONValueJSONOrdered::TCJSONValue(CJSONValueBaseSorted &&);

	extern template TCJSONValue<CJSONValueBaseOrdered> CJSONOrdered::fs_FromCompatible<CJSONValueBaseSorted>(TCJSONValue<CJSONValueBaseSorted> const &);
	extern template TCJSONValue<CJSONValueBaseOrdered> CJSONOrdered::fs_FromCompatible<CJSONValueBaseSorted>(TCJSONValue<CJSONValueBaseSorted> &&);
	extern template TCJSONValue<CJSONValueBaseOrdered> CJSONOrdered::fs_FromCompatible<CJSONValueBaseSorted>(TCJSONValue<CJSONValueBaseSorted> const &&);

	extern template CJSONOrdered::TCJSONValue(TCJSONValue<CJSONValueBaseSorted> const &);
	extern template CJSONOrdered::TCJSONValue(TCJSONValue<CJSONValueBaseSorted> &&);
	extern template CJSONOrdered::TCJSONValue(TCJSONValue<CJSONValueBaseSorted> const &&);

	extern template CJSONValueBaseOrdered::TCJSONValueBase(CJSONValueBaseSorted const &);
	extern template CJSONValueBaseOrdered::TCJSONValueBase(CJSONValueBaseSorted &);
	extern template CJSONValueBaseOrdered::TCJSONValueBase(CJSONValueBaseSorted &&);
	
	extern template CJSONOrdered::TCJSONValue(CNullPtr &&);
	extern template CJSONOrdered::TCJSONValue(CNullPtr &);
	extern template CJSONOrdered::TCJSONValue(CNullPtr const &);

	extern template CJSONOrdered::TCJSONValue(NStr::CStr &&);
	extern template CJSONOrdered::TCJSONValue(NStr::CStr &);
	extern template CJSONOrdered::TCJSONValue(NStr::CStr const &);

	extern template CJSONOrdered::TCJSONValue(int64 &&);
	extern template CJSONOrdered::TCJSONValue(int64 &);
	extern template CJSONOrdered::TCJSONValue(int64 const &);

	extern template CJSONOrdered::TCJSONValue(int32 &&);
	extern template CJSONOrdered::TCJSONValue(int32 &);
	extern template CJSONOrdered::TCJSONValue(int32 const &);

	extern template CJSONOrdered::TCJSONValue(uint64 &&);
	extern template CJSONOrdered::TCJSONValue(uint64 &);
	extern template CJSONOrdered::TCJSONValue(uint64 const &);

	extern template CJSONOrdered::TCJSONValue(uint32 &&);
	extern template CJSONOrdered::TCJSONValue(uint32 &);
	extern template CJSONOrdered::TCJSONValue(uint32 const &);

	extern template CJSONOrdered::TCJSONValue(pfp64 &&);
	extern template CJSONOrdered::TCJSONValue(pfp64 &);
	extern template CJSONOrdered::TCJSONValue(pfp64 const &);

	extern template CJSONOrdered::TCJSONValue(pfp32 &&);
	extern template CJSONOrdered::TCJSONValue(pfp32 &);
	extern template CJSONOrdered::TCJSONValue(pfp32 const &);

	extern template CJSONOrdered::TCJSONValue(fp32 &&);
	extern template CJSONOrdered::TCJSONValue(fp32 &);
	extern template CJSONOrdered::TCJSONValue(fp32 const &);

	extern template CJSONOrdered::TCJSONValue(fp64 &&);
	extern template CJSONOrdered::TCJSONValue(fp64 &);
	extern template CJSONOrdered::TCJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJSONOrdered::TCJSONValue(int &&);
	extern template CJSONOrdered::TCJSONValue(int &);
	extern template CJSONOrdered::TCJSONValue(int const &);
#endif
	extern template CJSONOrdered::TCJSONValue(bool &&);
	extern template CJSONOrdered::TCJSONValue(bool &);
	extern template CJSONOrdered::TCJSONValue(bool const &);


	extern template CJSONOrdered &CJSONOrdered::f_Insert<NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	extern template CJSONOrdered &CJSONOrdered::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CJSONOrdered &CJSONOrdered::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CJSONOrdered &CJSONOrdered::f_Insert<int64>(int64 &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<int64 &>(int64 &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<int64 const &>(int64 const &);

	extern template CJSONOrdered &CJSONOrdered::f_Insert<int32>(int32 &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<int32 &>(int32 &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<int32 const &>(int32 const &);

	extern template CJSONOrdered &CJSONOrdered::f_Insert<uint64>(uint64 &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<uint64 &>(uint64 &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<uint64 const &>(uint64 const &);

	extern template CJSONOrdered &CJSONOrdered::f_Insert<uint32>(uint32 &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<uint32 &>(uint32 &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<uint32 const &>(uint32 const &);

	extern template CJSONOrdered &CJSONOrdered::f_Insert<pfp64>(pfp64 &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<pfp64 &>(pfp64 &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CJSONOrdered &CJSONOrdered::f_Insert<pfp32>(pfp32 &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<pfp32 &>(pfp32 &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CJSONOrdered &CJSONOrdered::f_Insert<fp32>(fp32 &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<fp32 &>(fp32 &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<fp32 const &>(fp32 const &);

	extern template CJSONOrdered &CJSONOrdered::f_Insert<fp64>(fp64 &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<fp64 &>(fp64 &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJSONOrdered &CJSONOrdered::f_Insert<int>(int &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<int &>(int &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<int const &>(int const &);
#endif
	extern template CJSONOrdered &CJSONOrdered::f_Insert<bool>(bool &&);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<bool &>(bool &);
	extern template CJSONOrdered &CJSONOrdered::f_Insert<bool const &>(bool const &);

	extern template CJSONOrdered &CJSONOrdered::operator = <NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	extern template CJSONOrdered &CJSONOrdered::operator = <NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	extern template CJSONOrdered &CJSONOrdered::operator = <CNullPtr>(CNullPtr &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <CNullPtr &>(CNullPtr &);
	extern template CJSONOrdered &CJSONOrdered::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CJSONOrdered &CJSONOrdered::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CJSONOrdered &CJSONOrdered::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CJSONOrdered &CJSONOrdered::operator = <int64>(int64 &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <int64 &>(int64 &);
	extern template CJSONOrdered &CJSONOrdered::operator = <int64 const &>(int64 const &);

	extern template CJSONOrdered &CJSONOrdered::operator = <int32>(int32 &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <int32 &>(int32 &);
	extern template CJSONOrdered &CJSONOrdered::operator = <int32 const &>(int32 const &);

	extern template CJSONOrdered &CJSONOrdered::operator = <uint64>(uint64 &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <uint64 &>(uint64 &);
	extern template CJSONOrdered &CJSONOrdered::operator = <uint64 const &>(uint64 const &);

	extern template CJSONOrdered &CJSONOrdered::operator = <uint32>(uint32 &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <uint32 &>(uint32 &);
	extern template CJSONOrdered &CJSONOrdered::operator = <uint32 const &>(uint32 const &);

	extern template CJSONOrdered &CJSONOrdered::operator = <pfp64>(pfp64 &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <pfp64 &>(pfp64 &);
	extern template CJSONOrdered &CJSONOrdered::operator = <pfp64 const &>(pfp64 const &);

	extern template CJSONOrdered &CJSONOrdered::operator = <pfp32>(pfp32 &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <pfp32 &>(pfp32 &);
	extern template CJSONOrdered &CJSONOrdered::operator = <pfp32 const &>(pfp32 const &);

	extern template CJSONOrdered &CJSONOrdered::operator = <fp32>(fp32 &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <fp32 &>(fp32 &);
	extern template CJSONOrdered &CJSONOrdered::operator = <fp32 const &>(fp32 const &);

	extern template CJSONOrdered &CJSONOrdered::operator = <fp64>(fp64 &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <fp64 &>(fp64 &);
	extern template CJSONOrdered &CJSONOrdered::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJSONOrdered &CJSONOrdered::operator = <int>(int &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <int &>(int &);
	extern template CJSONOrdered &CJSONOrdered::operator = <int const &>(int const &);
#endif
	extern template CJSONOrdered &CJSONOrdered::operator = <bool>(bool &&);
	extern template CJSONOrdered &CJSONOrdered::operator = <bool &>(bool &);
	extern template CJSONOrdered &CJSONOrdered::operator = <bool const &>(bool const &);

	extern template void CJSONOrdered::f_Format
		<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONOrdered, true>::CLocalOptions>
		(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONOrdered, true>::CLocalOptions const &) const
	;

	extern template void CJSONOrdered::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONOrdered, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONOrdered, true>::CLocalOptions const&) const
	;
#endif
}
