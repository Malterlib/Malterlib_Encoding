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
	template struct NPrivate::TCJSONValueBase<TCJSONValue, NPrivate::CJSONExtraTypes, true>;
	template struct TCJSONValue<NPrivate::TCJSONValueBase<TCJSONValue, NPrivate::CJSONExtraTypes, true>>;
	template struct TCJSONObject<CJSONOrdered, true>;
	template struct NPrivate::TCObjectEntry<CJSONOrdered, true>;

	template CJSONValueJSONOrdered::TCJSONValue(CJSONValueBaseSorted const &);
	template CJSONValueJSONOrdered::TCJSONValue(CJSONValueBaseSorted const &&);
	template CJSONValueJSONOrdered::TCJSONValue(CJSONValueBaseSorted &&);

	template TCJSONValue<CJSONValueBaseOrdered> CJSONOrdered::fs_FromCompatible<CJSONValueBaseSorted>(TCJSONValue<CJSONValueBaseSorted> const &);
	template TCJSONValue<CJSONValueBaseOrdered> CJSONOrdered::fs_FromCompatible<CJSONValueBaseSorted>(TCJSONValue<CJSONValueBaseSorted> &&);
	template TCJSONValue<CJSONValueBaseOrdered> CJSONOrdered::fs_FromCompatible<CJSONValueBaseSorted>(TCJSONValue<CJSONValueBaseSorted> const &&);

	template CJSONOrdered::TCJSONValue(TCJSONValue<CJSONValueBaseSorted> const &);
	template CJSONOrdered::TCJSONValue(TCJSONValue<CJSONValueBaseSorted> &&);
	template CJSONOrdered::TCJSONValue(TCJSONValue<CJSONValueBaseSorted> const &&);

	template CJSONValueBaseOrdered::TCJSONValueBase(CJSONValueBaseSorted const &);
	template CJSONValueBaseOrdered::TCJSONValueBase(CJSONValueBaseSorted &);
	template CJSONValueBaseOrdered::TCJSONValueBase(CJSONValueBaseSorted &&);
	
	template CJSONOrdered::TCJSONValue(CNullPtr &&);
	template CJSONOrdered::TCJSONValue(CNullPtr &);
	template CJSONOrdered::TCJSONValue(CNullPtr const &);

	template CJSONOrdered::TCJSONValue(NStr::CStr &&);
	template CJSONOrdered::TCJSONValue(NStr::CStr &);
	template CJSONOrdered::TCJSONValue(NStr::CStr const &);

	template CJSONOrdered::TCJSONValue(int64 &&);
	template CJSONOrdered::TCJSONValue(int64 &);
	template CJSONOrdered::TCJSONValue(int64 const &);

	template CJSONOrdered::TCJSONValue(int32 &&);
	template CJSONOrdered::TCJSONValue(int32 &);
	template CJSONOrdered::TCJSONValue(int32 const &);

	template CJSONOrdered::TCJSONValue(uint64 &&);
	template CJSONOrdered::TCJSONValue(uint64 &);
	template CJSONOrdered::TCJSONValue(uint64 const &);

	template CJSONOrdered::TCJSONValue(uint32 &&);
	template CJSONOrdered::TCJSONValue(uint32 &);
	template CJSONOrdered::TCJSONValue(uint32 const &);

	template CJSONOrdered::TCJSONValue(pfp64 &&);
	template CJSONOrdered::TCJSONValue(pfp64 &);
	template CJSONOrdered::TCJSONValue(pfp64 const &);

	template CJSONOrdered::TCJSONValue(pfp32 &&);
	template CJSONOrdered::TCJSONValue(pfp32 &);
	template CJSONOrdered::TCJSONValue(pfp32 const &);

	template CJSONOrdered::TCJSONValue(fp32 &&);
	template CJSONOrdered::TCJSONValue(fp32 &);
	template CJSONOrdered::TCJSONValue(fp32 const &);

	template CJSONOrdered::TCJSONValue(fp64 &&);
	template CJSONOrdered::TCJSONValue(fp64 &);
	template CJSONOrdered::TCJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJSONOrdered::TCJSONValue(int &&);
	template CJSONOrdered::TCJSONValue(int &);
	template CJSONOrdered::TCJSONValue(int const &);
#endif
	template CJSONOrdered::TCJSONValue(bool &&);
	template CJSONOrdered::TCJSONValue(bool &);
	template CJSONOrdered::TCJSONValue(bool const &);

	template CJSONOrdered &CJSONOrdered::f_Insert<NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	template CJSONOrdered &CJSONOrdered::f_Insert<NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	template CJSONOrdered &CJSONOrdered::f_Insert<CNullPtr>(CNullPtr &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<CNullPtr &>(CNullPtr &);
	template CJSONOrdered &CJSONOrdered::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CJSONOrdered &CJSONOrdered::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CJSONOrdered &CJSONOrdered::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CJSONOrdered &CJSONOrdered::f_Insert<int64>(int64 &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<int64 &>(int64 &);
	template CJSONOrdered &CJSONOrdered::f_Insert<int64 const &>(int64 const &);

	template CJSONOrdered &CJSONOrdered::f_Insert<int32>(int32 &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<int32 &>(int32 &);
	template CJSONOrdered &CJSONOrdered::f_Insert<int32 const &>(int32 const &);

	template CJSONOrdered &CJSONOrdered::f_Insert<uint64>(uint64 &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<uint64 &>(uint64 &);
	template CJSONOrdered &CJSONOrdered::f_Insert<uint64 const &>(uint64 const &);

	template CJSONOrdered &CJSONOrdered::f_Insert<uint32>(uint32 &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<uint32 &>(uint32 &);
	template CJSONOrdered &CJSONOrdered::f_Insert<uint32 const &>(uint32 const &);

	template CJSONOrdered &CJSONOrdered::f_Insert<pfp64>(pfp64 &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<pfp64 &>(pfp64 &);
	template CJSONOrdered &CJSONOrdered::f_Insert<pfp64 const &>(pfp64 const &);

	template CJSONOrdered &CJSONOrdered::f_Insert<pfp32>(pfp32 &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<pfp32 &>(pfp32 &);
	template CJSONOrdered &CJSONOrdered::f_Insert<pfp32 const &>(pfp32 const &);

	template CJSONOrdered &CJSONOrdered::f_Insert<fp32>(fp32 &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<fp32 &>(fp32 &);
	template CJSONOrdered &CJSONOrdered::f_Insert<fp32 const &>(fp32 const &);

	template CJSONOrdered &CJSONOrdered::f_Insert<fp64>(fp64 &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<fp64 &>(fp64 &);
	template CJSONOrdered &CJSONOrdered::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJSONOrdered &CJSONOrdered::f_Insert<int>(int &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<int &>(int &);
	template CJSONOrdered &CJSONOrdered::f_Insert<int const &>(int const &);
#endif
	template CJSONOrdered &CJSONOrdered::f_Insert<bool>(bool &&);
	template CJSONOrdered &CJSONOrdered::f_Insert<bool &>(bool &);
	template CJSONOrdered &CJSONOrdered::f_Insert<bool const &>(bool const &);

	template CJSONOrdered &CJSONOrdered::operator = <NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	template CJSONOrdered &CJSONOrdered::operator = <NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	template CJSONOrdered &CJSONOrdered::operator = <NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	template CJSONOrdered &CJSONOrdered::operator = <CNullPtr>(CNullPtr &&);
	template CJSONOrdered &CJSONOrdered::operator = <CNullPtr &>(CNullPtr &);
	template CJSONOrdered &CJSONOrdered::operator = <CNullPtr const &>(CNullPtr const &);

	template CJSONOrdered &CJSONOrdered::operator = <NStr::CStr>(NStr::CStr &&);
	template CJSONOrdered &CJSONOrdered::operator = <NStr::CStr &>(NStr::CStr &);
	template CJSONOrdered &CJSONOrdered::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CJSONOrdered &CJSONOrdered::operator = <int64>(int64 &&);
	template CJSONOrdered &CJSONOrdered::operator = <int64 &>(int64 &);
	template CJSONOrdered &CJSONOrdered::operator = <int64 const &>(int64 const &);

	template CJSONOrdered &CJSONOrdered::operator = <int32>(int32 &&);
	template CJSONOrdered &CJSONOrdered::operator = <int32 &>(int32 &);
	template CJSONOrdered &CJSONOrdered::operator = <int32 const &>(int32 const &);

	template CJSONOrdered &CJSONOrdered::operator = <uint64>(uint64 &&);
	template CJSONOrdered &CJSONOrdered::operator = <uint64 &>(uint64 &);
	template CJSONOrdered &CJSONOrdered::operator = <uint64 const &>(uint64 const &);

	template CJSONOrdered &CJSONOrdered::operator = <uint32>(uint32 &&);
	template CJSONOrdered &CJSONOrdered::operator = <uint32 &>(uint32 &);
	template CJSONOrdered &CJSONOrdered::operator = <uint32 const &>(uint32 const &);

	template CJSONOrdered &CJSONOrdered::operator = <pfp64>(pfp64 &&);
	template CJSONOrdered &CJSONOrdered::operator = <pfp64 &>(pfp64 &);
	template CJSONOrdered &CJSONOrdered::operator = <pfp64 const &>(pfp64 const &);

	template CJSONOrdered &CJSONOrdered::operator = <pfp32>(pfp32 &&);
	template CJSONOrdered &CJSONOrdered::operator = <pfp32 &>(pfp32 &);
	template CJSONOrdered &CJSONOrdered::operator = <pfp32 const &>(pfp32 const &);

	template CJSONOrdered &CJSONOrdered::operator = <fp32>(fp32 &&);
	template CJSONOrdered &CJSONOrdered::operator = <fp32 &>(fp32 &);
	template CJSONOrdered &CJSONOrdered::operator = <fp32 const &>(fp32 const &);

	template CJSONOrdered &CJSONOrdered::operator = <fp64>(fp64 &&);
	template CJSONOrdered &CJSONOrdered::operator = <fp64 &>(fp64 &);
	template CJSONOrdered &CJSONOrdered::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJSONOrdered &CJSONOrdered::operator = <int>(int &&);
	template CJSONOrdered &CJSONOrdered::operator = <int &>(int &);
	template CJSONOrdered &CJSONOrdered::operator = <int const &>(int const &);
#endif
	template CJSONOrdered &CJSONOrdered::operator = <bool>(bool &&);
	template CJSONOrdered &CJSONOrdered::operator = <bool &>(bool &);
	template CJSONOrdered &CJSONOrdered::operator = <bool const &>(bool const &);

	template void CJSONOrdered::f_Format
		<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONOrdered, true>::CLocalOptions>
		(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONOrdered, true>::CLocalOptions const &) const
	;

	template void CJSONOrdered::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONOrdered, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSONOrdered, true>::CLocalOptions const&) const
	;
#endif
}
