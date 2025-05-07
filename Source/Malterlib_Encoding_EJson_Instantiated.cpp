// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_EJSON.h"
#include "Malterlib_Encoding_EJSON.hpp"
#include "Malterlib_Encoding_EJSON_Generate.h"
#include "Malterlib_Encoding_EJSON_Parse.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJSONExternTemplate
	template struct NPrivate::TCJSONValueBase<TCEJSONValue, NPrivate::CEJSONExtraTypesOrdered, true>;
	template struct TCJSONValue<CEJSONValueBaseOrdered>;
	template struct TCEJSONValue<CEJSONValueBaseOrdered>;
	template struct TCJSONObject<CEJSONOrdered, true>;
	template struct NPrivate::TCObjectEntry<CEJSONOrdered, true>;

	template CJSONValueEJSONOrdered::TCJSONValue(CEJSONValueBaseSorted const &);
	template CJSONValueEJSONOrdered::TCJSONValue(CEJSONValueBaseSorted const &&);
	template CJSONValueEJSONOrdered::TCJSONValue(CEJSONValueBaseSorted &&);

	template TCEJSONValue<CEJSONValueBaseOrdered> CEJSONOrdered::fs_FromCompatible<CEJSONValueBaseSorted>(TCEJSONValue<CEJSONValueBaseSorted> const &);
	template TCEJSONValue<CEJSONValueBaseOrdered> CEJSONOrdered::fs_FromCompatible<CEJSONValueBaseSorted>(TCEJSONValue<CEJSONValueBaseSorted> &&);
	template TCEJSONValue<CEJSONValueBaseOrdered> CEJSONOrdered::fs_FromCompatible<CEJSONValueBaseSorted>(TCEJSONValue<CEJSONValueBaseSorted> const &&);

	template CEJSONOrdered::TCEJSONValue(TCEJSONValue<CEJSONValueBaseSorted> const &);
	template CEJSONOrdered::TCEJSONValue(TCEJSONValue<CEJSONValueBaseSorted> &&);
	template CEJSONOrdered::TCEJSONValue(TCEJSONValue<CEJSONValueBaseSorted> const &&);

	template CEJSONValueBaseOrdered::TCJSONValueBase(CEJSONValueBaseSorted const &);
	template CEJSONValueBaseOrdered::TCJSONValueBase(CEJSONValueBaseSorted &);
	template CEJSONValueBaseOrdered::TCJSONValueBase(CEJSONValueBaseSorted &&);
	
	template CJSONValueEJSONOrdered::TCJSONValue(CNullPtr &&);
	template CJSONValueEJSONOrdered::TCJSONValue(CNullPtr &);
	template CJSONValueEJSONOrdered::TCJSONValue(CNullPtr const &);

	template CJSONValueEJSONOrdered::TCJSONValue(NStr::CStr &&);
	template CJSONValueEJSONOrdered::TCJSONValue(NStr::CStr &);
	template CJSONValueEJSONOrdered::TCJSONValue(NStr::CStr const &);

	template CJSONValueEJSONOrdered::TCJSONValue(int64 &&);
	template CJSONValueEJSONOrdered::TCJSONValue(int64 &);
	template CJSONValueEJSONOrdered::TCJSONValue(int64 const &);

	template CJSONValueEJSONOrdered::TCJSONValue(int32 &&);
	template CJSONValueEJSONOrdered::TCJSONValue(int32 &);
	template CJSONValueEJSONOrdered::TCJSONValue(int32 const &);

	template CJSONValueEJSONOrdered::TCJSONValue(uint64 &&);
	template CJSONValueEJSONOrdered::TCJSONValue(uint64 &);
	template CJSONValueEJSONOrdered::TCJSONValue(uint64 const &);

	template CJSONValueEJSONOrdered::TCJSONValue(uint32 &&);
	template CJSONValueEJSONOrdered::TCJSONValue(uint32 &);
	template CJSONValueEJSONOrdered::TCJSONValue(uint32 const &);

	template CJSONValueEJSONOrdered::TCJSONValue(pfp64 &&);
	template CJSONValueEJSONOrdered::TCJSONValue(pfp64 &);
	template CJSONValueEJSONOrdered::TCJSONValue(pfp64 const &);

	template CJSONValueEJSONOrdered::TCJSONValue(pfp32 &&);
	template CJSONValueEJSONOrdered::TCJSONValue(pfp32 &);
	template CJSONValueEJSONOrdered::TCJSONValue(pfp32 const &);

	template CJSONValueEJSONOrdered::TCJSONValue(fp32 &&);
	template CJSONValueEJSONOrdered::TCJSONValue(fp32 &);
	template CJSONValueEJSONOrdered::TCJSONValue(fp32 const &);

	template CJSONValueEJSONOrdered::TCJSONValue(fp64 &&);
	template CJSONValueEJSONOrdered::TCJSONValue(fp64 &);
	template CJSONValueEJSONOrdered::TCJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJSONValueEJSONOrdered::TCJSONValue(int &&);
	template CJSONValueEJSONOrdered::TCJSONValue(int &);
	template CJSONValueEJSONOrdered::TCJSONValue(int const &);
#endif
	template CJSONValueEJSONOrdered::TCJSONValue(bool &&);
	template CJSONValueEJSONOrdered::TCJSONValue(bool &);
	template CJSONValueEJSONOrdered::TCJSONValue(bool const &);

	//

	template CEJSONOrdered::TCEJSONValue(EJSONType &&);
	template CEJSONOrdered::TCEJSONValue(EJSONType &);
	template CEJSONOrdered::TCEJSONValue(EJSONType const &);

	template CEJSONOrdered::TCEJSONValue(ch8 const *&&);
	template CEJSONOrdered::TCEJSONValue(ch8 const *&);
	template CEJSONOrdered::TCEJSONValue(ch8 const *const &);

	template CEJSONOrdered::TCEJSONValue(CNullPtr &&);
	template CEJSONOrdered::TCEJSONValue(CNullPtr &);
	template CEJSONOrdered::TCEJSONValue(CNullPtr const &);

	template CEJSONOrdered::TCEJSONValue(NStr::CStr &&);
	template CEJSONOrdered::TCEJSONValue(NStr::CStr &);
	template CEJSONOrdered::TCEJSONValue(NStr::CStr const &);

	template CEJSONOrdered::TCEJSONValue(int64 &&);
	template CEJSONOrdered::TCEJSONValue(int64 &);
	template CEJSONOrdered::TCEJSONValue(int64 const &);

	template CEJSONOrdered::TCEJSONValue(int32 &&);
	template CEJSONOrdered::TCEJSONValue(int32 &);
	template CEJSONOrdered::TCEJSONValue(int32 const &);

	template CEJSONOrdered::TCEJSONValue(uint64 &&);
	template CEJSONOrdered::TCEJSONValue(uint64 &);
	template CEJSONOrdered::TCEJSONValue(uint64 const &);

	template CEJSONOrdered::TCEJSONValue(uint32 &&);
	template CEJSONOrdered::TCEJSONValue(uint32 &);
	template CEJSONOrdered::TCEJSONValue(uint32 const &);

	template CEJSONOrdered::TCEJSONValue(pfp64 &&);
	template CEJSONOrdered::TCEJSONValue(pfp64 &);
	template CEJSONOrdered::TCEJSONValue(pfp64 const &);

	template CEJSONOrdered::TCEJSONValue(pfp32 &&);
	template CEJSONOrdered::TCEJSONValue(pfp32 &);
	template CEJSONOrdered::TCEJSONValue(pfp32 const &);

	template CEJSONOrdered::TCEJSONValue(fp32 &&);
	template CEJSONOrdered::TCEJSONValue(fp32 &);
	template CEJSONOrdered::TCEJSONValue(fp32 const &);

	template CEJSONOrdered::TCEJSONValue(fp64 &&);
	template CEJSONOrdered::TCEJSONValue(fp64 &);
	template CEJSONOrdered::TCEJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJSONOrdered::TCEJSONValue(int &&);
	template CEJSONOrdered::TCEJSONValue(int &);
	template CEJSONOrdered::TCEJSONValue(int const &);
#endif
	template CEJSONOrdered::TCEJSONValue(bool &&);
	template CEJSONOrdered::TCEJSONValue(bool &);
	template CEJSONOrdered::TCEJSONValue(bool const &);

	//
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<CNullPtr>(CNullPtr &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<CNullPtr &>(CNullPtr &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int64>(int64 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int64 &>(int64 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int64 const &>(int64 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int32>(int32 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int32 &>(int32 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int32 const &>(int32 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<uint64>(uint64 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<uint64 &>(uint64 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<uint64 const &>(uint64 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<uint32>(uint32 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<uint32 &>(uint32 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<uint32 const &>(uint32 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<pfp64>(pfp64 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<pfp64 &>(pfp64 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<pfp64 const &>(pfp64 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<pfp32>(pfp32 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<pfp32 &>(pfp32 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<pfp32 const &>(pfp32 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<fp32>(fp32 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<fp32 &>(fp32 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<fp32 const &>(fp32 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<fp64>(fp64 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<fp64 &>(fp64 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int>(int &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int &>(int &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<int const &>(int const &);
#endif
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<bool>(bool &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<bool &>(bool &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::f_Insert<bool const &>(bool const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <CNullPtr>(CNullPtr &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <CNullPtr &>(CNullPtr &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <CNullPtr const &>(CNullPtr const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <NStr::CStr>(NStr::CStr &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <NStr::CStr &>(NStr::CStr &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int64>(int64 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int64 &>(int64 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int64 const &>(int64 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int32>(int32 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int32 &>(int32 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int32 const &>(int32 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <uint64>(uint64 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <uint64 &>(uint64 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <uint64 const &>(uint64 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <uint32>(uint32 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <uint32 &>(uint32 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <uint32 const &>(uint32 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <pfp64>(pfp64 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <pfp64 &>(pfp64 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <pfp64 const &>(pfp64 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <pfp32>(pfp32 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <pfp32 &>(pfp32 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <pfp32 const &>(pfp32 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <fp32>(fp32 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <fp32 &>(fp32 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <fp32 const &>(fp32 const &);

	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <fp64>(fp64 &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <fp64 &>(fp64 &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int>(int &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int &>(int &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <int const &>(int const &);
#endif
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <bool>(bool &&);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <bool &>(bool &);
	template CEJSONOrdered &CJSONValueEJSONOrdered::operator = <bool const &>(bool const &);

	template void CJSONValueEJSONOrdered::f_Format
		<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONOrdered, true>::CLocalOptions>
		(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONOrdered, true>::CLocalOptions const &) const
	;

	template void CJSONValueEJSONOrdered::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONOrdered, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONOrdered, true>::CLocalOptions const&) const
	;
#endif
}
