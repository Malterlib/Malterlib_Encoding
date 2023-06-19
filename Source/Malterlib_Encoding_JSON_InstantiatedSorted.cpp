// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_JSON.h"
#include "Malterlib_Encoding_JSON_Parse.h"
#include "Malterlib_Encoding_JSON_Generate.h"
#include "Malterlib_Encoding_JSON.hpp"
#include "Malterlib_Encoding_JSON_GenerateColored.hpp"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJSONExternTemplate
	template struct NPrivate::TCJSONValueBase<TCJSONValue, NPrivate::CJSONExtraTypes, false>;
	template struct TCJSONValue<NPrivate::TCJSONValueBase<TCJSONValue, NPrivate::CJSONExtraTypes, false>>;
	template struct TCJSONObject<CJSONSorted, false>;
	template struct NPrivate::TCObjectEntry<CJSONSorted, false>;

	template CJSONValueJSONSorted::TCJSONValue(CJSONValueBaseOrdered const &);
	template CJSONValueJSONSorted::TCJSONValue(CJSONValueBaseOrdered const &&);
	template CJSONValueJSONSorted::TCJSONValue(CJSONValueBaseOrdered &&);

	template TCJSONValue<CJSONValueBaseSorted> CJSONSorted::fs_FromCompatible<CJSONValueBaseOrdered>(TCJSONValue<CJSONValueBaseOrdered> const &);
	template TCJSONValue<CJSONValueBaseSorted> CJSONSorted::fs_FromCompatible<CJSONValueBaseOrdered>(TCJSONValue<CJSONValueBaseOrdered> &&);
	template TCJSONValue<CJSONValueBaseSorted> CJSONSorted::fs_FromCompatible<CJSONValueBaseOrdered>(TCJSONValue<CJSONValueBaseOrdered> const &&);

	template CJSONSorted::TCJSONValue(TCJSONValue<CJSONValueBaseOrdered> const &);
	template CJSONSorted::TCJSONValue(TCJSONValue<CJSONValueBaseOrdered> &&);
	template CJSONSorted::TCJSONValue(TCJSONValue<CJSONValueBaseOrdered> const &&);

	template CJSONValueBaseSorted::TCJSONValueBase(CJSONValueBaseOrdered const &);
	template CJSONValueBaseSorted::TCJSONValueBase(CJSONValueBaseOrdered &);
	template CJSONValueBaseSorted::TCJSONValueBase(CJSONValueBaseOrdered &&);

	template CJSONSorted::TCJSONValue(CNullPtr &&);
	template CJSONSorted::TCJSONValue(CNullPtr &);
	template CJSONSorted::TCJSONValue(CNullPtr const &);

	template CJSONSorted::TCJSONValue(NStr::CStr &&);
	template CJSONSorted::TCJSONValue(NStr::CStr &);
	template CJSONSorted::TCJSONValue(NStr::CStr const &);

	template CJSONSorted::TCJSONValue(int64 &&);
	template CJSONSorted::TCJSONValue(int64 &);
	template CJSONSorted::TCJSONValue(int64 const &);

	template CJSONSorted::TCJSONValue(int32 &&);
	template CJSONSorted::TCJSONValue(int32 &);
	template CJSONSorted::TCJSONValue(int32 const &);

	template CJSONSorted::TCJSONValue(uint64 &&);
	template CJSONSorted::TCJSONValue(uint64 &);
	template CJSONSorted::TCJSONValue(uint64 const &);

	template CJSONSorted::TCJSONValue(uint32 &&);
	template CJSONSorted::TCJSONValue(uint32 &);
	template CJSONSorted::TCJSONValue(uint32 const &);

	template CJSONSorted::TCJSONValue(pfp64 &&);
	template CJSONSorted::TCJSONValue(pfp64 &);
	template CJSONSorted::TCJSONValue(pfp64 const &);

	template CJSONSorted::TCJSONValue(pfp32 &&);
	template CJSONSorted::TCJSONValue(pfp32 &);
	template CJSONSorted::TCJSONValue(pfp32 const &);

	template CJSONSorted::TCJSONValue(fp32 &&);
	template CJSONSorted::TCJSONValue(fp32 &);
	template CJSONSorted::TCJSONValue(fp32 const &);

	template CJSONSorted::TCJSONValue(fp64 &&);
	template CJSONSorted::TCJSONValue(fp64 &);
	template CJSONSorted::TCJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJSONSorted::TCJSONValue(int &&);
	template CJSONSorted::TCJSONValue(int &);
	template CJSONSorted::TCJSONValue(int const &);
#endif
	template CJSONSorted::TCJSONValue(bool &&);
	template CJSONSorted::TCJSONValue(bool &);
	template CJSONSorted::TCJSONValue(bool const &);

	template CJSONSorted &CJSONSorted::f_Insert<NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	template CJSONSorted &CJSONSorted::f_Insert<NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	template CJSONSorted &CJSONSorted::f_Insert<NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	template CJSONSorted &CJSONSorted::f_Insert<CNullPtr>(CNullPtr &&);
	template CJSONSorted &CJSONSorted::f_Insert<CNullPtr &>(CNullPtr &);
	template CJSONSorted &CJSONSorted::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CJSONSorted &CJSONSorted::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CJSONSorted &CJSONSorted::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CJSONSorted &CJSONSorted::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CJSONSorted &CJSONSorted::f_Insert<int64>(int64 &&);
	template CJSONSorted &CJSONSorted::f_Insert<int64 &>(int64 &);
	template CJSONSorted &CJSONSorted::f_Insert<int64 const &>(int64 const &);

	template CJSONSorted &CJSONSorted::f_Insert<int32>(int32 &&);
	template CJSONSorted &CJSONSorted::f_Insert<int32 &>(int32 &);
	template CJSONSorted &CJSONSorted::f_Insert<int32 const &>(int32 const &);

	template CJSONSorted &CJSONSorted::f_Insert<uint64>(uint64 &&);
	template CJSONSorted &CJSONSorted::f_Insert<uint64 &>(uint64 &);
	template CJSONSorted &CJSONSorted::f_Insert<uint64 const &>(uint64 const &);

	template CJSONSorted &CJSONSorted::f_Insert<uint32>(uint32 &&);
	template CJSONSorted &CJSONSorted::f_Insert<uint32 &>(uint32 &);
	template CJSONSorted &CJSONSorted::f_Insert<uint32 const &>(uint32 const &);

	template CJSONSorted &CJSONSorted::f_Insert<pfp64>(pfp64 &&);
	template CJSONSorted &CJSONSorted::f_Insert<pfp64 &>(pfp64 &);
	template CJSONSorted &CJSONSorted::f_Insert<pfp64 const &>(pfp64 const &);

	template CJSONSorted &CJSONSorted::f_Insert<pfp32>(pfp32 &&);
	template CJSONSorted &CJSONSorted::f_Insert<pfp32 &>(pfp32 &);
	template CJSONSorted &CJSONSorted::f_Insert<pfp32 const &>(pfp32 const &);

	template CJSONSorted &CJSONSorted::f_Insert<fp32>(fp32 &&);
	template CJSONSorted &CJSONSorted::f_Insert<fp32 &>(fp32 &);
	template CJSONSorted &CJSONSorted::f_Insert<fp32 const &>(fp32 const &);

	template CJSONSorted &CJSONSorted::f_Insert<fp64>(fp64 &&);
	template CJSONSorted &CJSONSorted::f_Insert<fp64 &>(fp64 &);
	template CJSONSorted &CJSONSorted::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJSONSorted &CJSONSorted::f_Insert<int>(int &&);
	template CJSONSorted &CJSONSorted::f_Insert<int &>(int &);
	template CJSONSorted &CJSONSorted::f_Insert<int const &>(int const &);
#endif
	template CJSONSorted &CJSONSorted::f_Insert<bool>(bool &&);
	template CJSONSorted &CJSONSorted::f_Insert<bool &>(bool &);
	template CJSONSorted &CJSONSorted::f_Insert<bool const &>(bool const &);

	template CJSONSorted &CJSONSorted::operator = <NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	template CJSONSorted &CJSONSorted::operator = <NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	template CJSONSorted &CJSONSorted::operator = <NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	template CJSONSorted &CJSONSorted::operator = <CNullPtr>(CNullPtr &&);
	template CJSONSorted &CJSONSorted::operator = <CNullPtr &>(CNullPtr &);
	template CJSONSorted &CJSONSorted::operator = <CNullPtr const &>(CNullPtr const &);

	template CJSONSorted &CJSONSorted::operator = <NStr::CStr>(NStr::CStr &&);
	template CJSONSorted &CJSONSorted::operator = <NStr::CStr &>(NStr::CStr &);
	template CJSONSorted &CJSONSorted::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CJSONSorted &CJSONSorted::operator = <int64>(int64 &&);
	template CJSONSorted &CJSONSorted::operator = <int64 &>(int64 &);
	template CJSONSorted &CJSONSorted::operator = <int64 const &>(int64 const &);

	template CJSONSorted &CJSONSorted::operator = <int32>(int32 &&);
	template CJSONSorted &CJSONSorted::operator = <int32 &>(int32 &);
	template CJSONSorted &CJSONSorted::operator = <int32 const &>(int32 const &);

	template CJSONSorted &CJSONSorted::operator = <uint64>(uint64 &&);
	template CJSONSorted &CJSONSorted::operator = <uint64 &>(uint64 &);
	template CJSONSorted &CJSONSorted::operator = <uint64 const &>(uint64 const &);

	template CJSONSorted &CJSONSorted::operator = <uint32>(uint32 &&);
	template CJSONSorted &CJSONSorted::operator = <uint32 &>(uint32 &);
	template CJSONSorted &CJSONSorted::operator = <uint32 const &>(uint32 const &);

	template CJSONSorted &CJSONSorted::operator = <pfp64>(pfp64 &&);
	template CJSONSorted &CJSONSorted::operator = <pfp64 &>(pfp64 &);
	template CJSONSorted &CJSONSorted::operator = <pfp64 const &>(pfp64 const &);

	template CJSONSorted &CJSONSorted::operator = <pfp32>(pfp32 &&);
	template CJSONSorted &CJSONSorted::operator = <pfp32 &>(pfp32 &);
	template CJSONSorted &CJSONSorted::operator = <pfp32 const &>(pfp32 const &);

	template CJSONSorted &CJSONSorted::operator = <fp32>(fp32 &&);
	template CJSONSorted &CJSONSorted::operator = <fp32 &>(fp32 &);
	template CJSONSorted &CJSONSorted::operator = <fp32 const &>(fp32 const &);

	template CJSONSorted &CJSONSorted::operator = <fp64>(fp64 &&);
	template CJSONSorted &CJSONSorted::operator = <fp64 &>(fp64 &);
	template CJSONSorted &CJSONSorted::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJSONSorted &CJSONSorted::operator = <int>(int &&);
	template CJSONSorted &CJSONSorted::operator = <int &>(int &);
	template CJSONSorted &CJSONSorted::operator = <int const &>(int const &);
#endif
	template CJSONSorted &CJSONSorted::operator = <bool>(bool &&);
	template CJSONSorted &CJSONSorted::operator = <bool &>(bool &);
	template CJSONSorted &CJSONSorted::operator = <bool const &>(bool const &);

	template void CJSONSorted::f_Format
		<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONSorted, false>::CLocalOptions>
		(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONSorted, false>::CLocalOptions const &) const
	;

	template void CJSONSorted::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONSorted, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONSorted, false>::CLocalOptions const&) const
	;
#endif
}
