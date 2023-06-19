// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_EJSON.h"

namespace NMib::NEncoding
{
	extern template struct NPrivate::TCJSONValueBase<TCEJSONValue, NPrivate::CEJSONExtraTypesOrdered, true>;
	extern template struct TCJSONValue<CEJSONValueBaseOrdered>;
	extern template struct TCEJSONValue<CEJSONValueBaseOrdered>;
	extern template struct TCJSONObject<CEJSONOrdered, true>;
	extern template struct NPrivate::TCObjectEntry<CEJSONOrdered, true>;

#ifdef DMibEncodingJSONExternTemplate

	extern template CJSONValueEJSONOrdered::TCJSONValue(CEJSONValueBaseSorted const &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(CEJSONValueBaseSorted const &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(CEJSONValueBaseSorted &&);

	extern template TCEJSONValue<CEJSONValueBaseOrdered> CEJSONOrdered::fs_FromCompatible<CEJSONValueBaseSorted>(TCEJSONValue<CEJSONValueBaseSorted> const &);
	extern template TCEJSONValue<CEJSONValueBaseOrdered> CEJSONOrdered::fs_FromCompatible<CEJSONValueBaseSorted>(TCEJSONValue<CEJSONValueBaseSorted> &&);
	extern template TCEJSONValue<CEJSONValueBaseOrdered> CEJSONOrdered::fs_FromCompatible<CEJSONValueBaseSorted>(TCEJSONValue<CEJSONValueBaseSorted> const &&);

	extern template CEJSONOrdered::TCEJSONValue(TCEJSONValue<CEJSONValueBaseSorted> const &);
	extern template CEJSONOrdered::TCEJSONValue(TCEJSONValue<CEJSONValueBaseSorted> &&);
	extern template CEJSONOrdered::TCEJSONValue(TCEJSONValue<CEJSONValueBaseSorted> const &&);

	extern template CEJSONValueBaseOrdered::TCJSONValueBase(CEJSONValueBaseSorted const &);
	extern template CEJSONValueBaseOrdered::TCJSONValueBase(CEJSONValueBaseSorted &);
	extern template CEJSONValueBaseOrdered::TCJSONValueBase(CEJSONValueBaseSorted &&);

	extern template CJSONValueEJSONOrdered::TCJSONValue(CNullPtr &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(CNullPtr &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(CNullPtr const &);

	extern template CJSONValueEJSONOrdered::TCJSONValue(NStr::CStr &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(NStr::CStr &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(NStr::CStr const &);

	extern template CJSONValueEJSONOrdered::TCJSONValue(int64 &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(int64 &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(int64 const &);

	extern template CJSONValueEJSONOrdered::TCJSONValue(int32 &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(int32 &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(int32 const &);

	extern template CJSONValueEJSONOrdered::TCJSONValue(uint64 &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(uint64 &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(uint64 const &);

	extern template CJSONValueEJSONOrdered::TCJSONValue(uint32 &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(uint32 &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(uint32 const &);

	extern template CJSONValueEJSONOrdered::TCJSONValue(pfp64 &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(pfp64 &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(pfp64 const &);

	extern template CJSONValueEJSONOrdered::TCJSONValue(pfp32 &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(pfp32 &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(pfp32 const &);

	extern template CJSONValueEJSONOrdered::TCJSONValue(fp32 &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(fp32 &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(fp32 const &);

	extern template CJSONValueEJSONOrdered::TCJSONValue(fp64 &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(fp64 &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJSONValueEJSONOrdered::TCJSONValue(int &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(int &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(int const &);
#endif
	extern template CJSONValueEJSONOrdered::TCJSONValue(bool &&);
	extern template CJSONValueEJSONOrdered::TCJSONValue(bool &);
	extern template CJSONValueEJSONOrdered::TCJSONValue(bool const &);

	//

	extern template CEJSONOrdered::TCEJSONValue(EJSONType &&);
	extern template CEJSONOrdered::TCEJSONValue(EJSONType &);
	extern template CEJSONOrdered::TCEJSONValue(EJSONType const &);

	extern template CEJSONOrdered::TCEJSONValue(ch8 const *&&);
	extern template CEJSONOrdered::TCEJSONValue(ch8 const *&);
	extern template CEJSONOrdered::TCEJSONValue(ch8 const *const &);

	extern template CEJSONOrdered::TCEJSONValue(CNullPtr &&);
	extern template CEJSONOrdered::TCEJSONValue(CNullPtr &);
	extern template CEJSONOrdered::TCEJSONValue(CNullPtr const &);

	extern template CEJSONOrdered::TCEJSONValue(NStr::CStr &&);
	extern template CEJSONOrdered::TCEJSONValue(NStr::CStr &);
	extern template CEJSONOrdered::TCEJSONValue(NStr::CStr const &);

	extern template CEJSONOrdered::TCEJSONValue(int64 &&);
	extern template CEJSONOrdered::TCEJSONValue(int64 &);
	extern template CEJSONOrdered::TCEJSONValue(int64 const &);

	extern template CEJSONOrdered::TCEJSONValue(int32 &&);
	extern template CEJSONOrdered::TCEJSONValue(int32 &);
	extern template CEJSONOrdered::TCEJSONValue(int32 const &);

	extern template CEJSONOrdered::TCEJSONValue(uint64 &&);
	extern template CEJSONOrdered::TCEJSONValue(uint64 &);
	extern template CEJSONOrdered::TCEJSONValue(uint64 const &);

	extern template CEJSONOrdered::TCEJSONValue(uint32 &&);
	extern template CEJSONOrdered::TCEJSONValue(uint32 &);
	extern template CEJSONOrdered::TCEJSONValue(uint32 const &);

	extern template CEJSONOrdered::TCEJSONValue(pfp64 &&);
	extern template CEJSONOrdered::TCEJSONValue(pfp64 &);
	extern template CEJSONOrdered::TCEJSONValue(pfp64 const &);

	extern template CEJSONOrdered::TCEJSONValue(pfp32 &&);
	extern template CEJSONOrdered::TCEJSONValue(pfp32 &);
	extern template CEJSONOrdered::TCEJSONValue(pfp32 const &);

	extern template CEJSONOrdered::TCEJSONValue(fp32 &&);
	extern template CEJSONOrdered::TCEJSONValue(fp32 &);
	extern template CEJSONOrdered::TCEJSONValue(fp32 const &);

	extern template CEJSONOrdered::TCEJSONValue(fp64 &&);
	extern template CEJSONOrdered::TCEJSONValue(fp64 &);
	extern template CEJSONOrdered::TCEJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJSONOrdered::TCEJSONValue(int &&);
	extern template CEJSONOrdered::TCEJSONValue(int &);
	extern template CEJSONOrdered::TCEJSONValue(int const &);
#endif
	extern template CEJSONOrdered::TCEJSONValue(bool &&);
	extern template CEJSONOrdered::TCEJSONValue(bool &);
	extern template CEJSONOrdered::TCEJSONValue(bool const &);

	//
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int64>(int64 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int64 &>(int64 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int64 const &>(int64 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int32>(int32 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int32 &>(int32 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int32 const &>(int32 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<uint64>(uint64 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<uint64 &>(uint64 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<uint64 const &>(uint64 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<uint32>(uint32 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<uint32 &>(uint32 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<uint32 const &>(uint32 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<pfp64>(pfp64 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<pfp64 &>(pfp64 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<pfp32>(pfp32 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<pfp32 &>(pfp32 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<fp32>(fp32 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<fp32 &>(fp32 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<fp32 const &>(fp32 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<fp64>(fp64 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<fp64 &>(fp64 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int>(int &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int &>(int &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int const &>(int const &);
#endif
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<bool>(bool &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<bool &>(bool &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<bool const &>(bool const &);
#endif

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <CNullPtr>(CNullPtr &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <CNullPtr &>(CNullPtr &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int64>(int64 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int64 &>(int64 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int64 const &>(int64 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int32>(int32 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int32 &>(int32 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int32 const &>(int32 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <uint64>(uint64 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <uint64 &>(uint64 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <uint64 const &>(uint64 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <uint32>(uint32 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <uint32 &>(uint32 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <uint32 const &>(uint32 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <pfp64>(pfp64 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <pfp64 &>(pfp64 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <pfp64 const &>(pfp64 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <pfp32>(pfp32 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <pfp32 &>(pfp32 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <pfp32 const &>(pfp32 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <fp32>(fp32 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <fp32 &>(fp32 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <fp32 const &>(fp32 const &);

	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <fp64>(fp64 &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <fp64 &>(fp64 &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int>(int &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int &>(int &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int const &>(int const &);
#endif
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <bool>(bool &&);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <bool &>(bool &);
	extern template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <bool const &>(bool const &);

	extern template void CJSONValueEJSONOrdered::f_Format
		<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONOrdered, true>::CLocalOptions>
		(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONOrdered, true>::CLocalOptions const &) const
	;

	extern template void CJSONValueEJSONOrdered::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONOrdered, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONOrdered, true>::CLocalOptions const&) const
	;
}

#include "Malterlib_Encoding_EJSON_Value.hpp"
