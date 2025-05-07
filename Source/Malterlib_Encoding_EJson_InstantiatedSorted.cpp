// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_EJSON.h"
#include "Malterlib_Encoding_EJSON.hpp"
#include "Malterlib_Encoding_EJSON_Generate.h"
#include "Malterlib_Encoding_EJSON_Parse.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJSONExternTemplate
	template struct NPrivate::TCJSONValueBase<TCEJSONValue, NPrivate::CEJSONExtraTypesSorted, false>;
	template struct TCJSONValue<CEJSONValueBaseSorted>;
	template struct TCEJSONValue<CEJSONValueBaseSorted>;
	template struct TCJSONObject<CEJSONSorted, false>;
	template struct NPrivate::TCObjectEntry<CEJSONSorted, false>;

	template CJSONValueEJSONSorted::TCJSONValue(CEJSONValueBaseOrdered const &);
	template CJSONValueEJSONSorted::TCJSONValue(CEJSONValueBaseOrdered const &&);
	template CJSONValueEJSONSorted::TCJSONValue(CEJSONValueBaseOrdered &&);

	template TCEJSONValue<CEJSONValueBaseSorted> CEJSONSorted::fs_FromCompatible<CEJSONValueBaseOrdered>(TCEJSONValue<CEJSONValueBaseOrdered> const &);
	template TCEJSONValue<CEJSONValueBaseSorted> CEJSONSorted::fs_FromCompatible<CEJSONValueBaseOrdered>(TCEJSONValue<CEJSONValueBaseOrdered> &&);
	template TCEJSONValue<CEJSONValueBaseSorted> CEJSONSorted::fs_FromCompatible<CEJSONValueBaseOrdered>(TCEJSONValue<CEJSONValueBaseOrdered> const &&);

	template CEJSONSorted::TCEJSONValue(TCEJSONValue<CEJSONValueBaseOrdered> const &);
	template CEJSONSorted::TCEJSONValue(TCEJSONValue<CEJSONValueBaseOrdered> &&);
	template CEJSONSorted::TCEJSONValue(TCEJSONValue<CEJSONValueBaseOrdered> const &&);

	template CEJSONValueBaseSorted::TCJSONValueBase(CEJSONValueBaseOrdered const &);
	template CEJSONValueBaseSorted::TCJSONValueBase(CEJSONValueBaseOrdered &);
	template CEJSONValueBaseSorted::TCJSONValueBase(CEJSONValueBaseOrdered &&);

	template CJSONValueEJSONSorted::TCJSONValue(CNullPtr &&);
	template CJSONValueEJSONSorted::TCJSONValue(CNullPtr &);
	template CJSONValueEJSONSorted::TCJSONValue(CNullPtr const &);

	template CJSONValueEJSONSorted::TCJSONValue(NStr::CStr &&);
	template CJSONValueEJSONSorted::TCJSONValue(NStr::CStr &);
	template CJSONValueEJSONSorted::TCJSONValue(NStr::CStr const &);

	template CJSONValueEJSONSorted::TCJSONValue(int64 &&);
	template CJSONValueEJSONSorted::TCJSONValue(int64 &);
	template CJSONValueEJSONSorted::TCJSONValue(int64 const &);

	template CJSONValueEJSONSorted::TCJSONValue(int32 &&);
	template CJSONValueEJSONSorted::TCJSONValue(int32 &);
	template CJSONValueEJSONSorted::TCJSONValue(int32 const &);

	template CJSONValueEJSONSorted::TCJSONValue(uint64 &&);
	template CJSONValueEJSONSorted::TCJSONValue(uint64 &);
	template CJSONValueEJSONSorted::TCJSONValue(uint64 const &);

	template CJSONValueEJSONSorted::TCJSONValue(uint32 &&);
	template CJSONValueEJSONSorted::TCJSONValue(uint32 &);
	template CJSONValueEJSONSorted::TCJSONValue(uint32 const &);

	template CJSONValueEJSONSorted::TCJSONValue(pfp64 &&);
	template CJSONValueEJSONSorted::TCJSONValue(pfp64 &);
	template CJSONValueEJSONSorted::TCJSONValue(pfp64 const &);

	template CJSONValueEJSONSorted::TCJSONValue(pfp32 &&);
	template CJSONValueEJSONSorted::TCJSONValue(pfp32 &);
	template CJSONValueEJSONSorted::TCJSONValue(pfp32 const &);

	template CJSONValueEJSONSorted::TCJSONValue(fp32 &&);
	template CJSONValueEJSONSorted::TCJSONValue(fp32 &);
	template CJSONValueEJSONSorted::TCJSONValue(fp32 const &);

	template CJSONValueEJSONSorted::TCJSONValue(fp64 &&);
	template CJSONValueEJSONSorted::TCJSONValue(fp64 &);
	template CJSONValueEJSONSorted::TCJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJSONValueEJSONSorted::TCJSONValue(int &&);
	template CJSONValueEJSONSorted::TCJSONValue(int &);
	template CJSONValueEJSONSorted::TCJSONValue(int const &);
#endif
	template CJSONValueEJSONSorted::TCJSONValue(bool &&);
	template CJSONValueEJSONSorted::TCJSONValue(bool &);
	template CJSONValueEJSONSorted::TCJSONValue(bool const &);

	//

	template CEJSONSorted::TCEJSONValue(EJSONType &&);
	template CEJSONSorted::TCEJSONValue(EJSONType &);
	template CEJSONSorted::TCEJSONValue(EJSONType const &);

	template CEJSONSorted::TCEJSONValue(ch8 const *&&);
	template CEJSONSorted::TCEJSONValue(ch8 const *&);
	template CEJSONSorted::TCEJSONValue(ch8 const *const &);

	template CEJSONSorted::TCEJSONValue(CNullPtr &&);
	template CEJSONSorted::TCEJSONValue(CNullPtr &);
	template CEJSONSorted::TCEJSONValue(CNullPtr const &);

	template CEJSONSorted::TCEJSONValue(NStr::CStr &&);
	template CEJSONSorted::TCEJSONValue(NStr::CStr &);
	template CEJSONSorted::TCEJSONValue(NStr::CStr const &);

	template CEJSONSorted::TCEJSONValue(int64 &&);
	template CEJSONSorted::TCEJSONValue(int64 &);
	template CEJSONSorted::TCEJSONValue(int64 const &);

	template CEJSONSorted::TCEJSONValue(int32 &&);
	template CEJSONSorted::TCEJSONValue(int32 &);
	template CEJSONSorted::TCEJSONValue(int32 const &);

	template CEJSONSorted::TCEJSONValue(uint64 &&);
	template CEJSONSorted::TCEJSONValue(uint64 &);
	template CEJSONSorted::TCEJSONValue(uint64 const &);

	template CEJSONSorted::TCEJSONValue(uint32 &&);
	template CEJSONSorted::TCEJSONValue(uint32 &);
	template CEJSONSorted::TCEJSONValue(uint32 const &);

	template CEJSONSorted::TCEJSONValue(pfp64 &&);
	template CEJSONSorted::TCEJSONValue(pfp64 &);
	template CEJSONSorted::TCEJSONValue(pfp64 const &);

	template CEJSONSorted::TCEJSONValue(pfp32 &&);
	template CEJSONSorted::TCEJSONValue(pfp32 &);
	template CEJSONSorted::TCEJSONValue(pfp32 const &);

	template CEJSONSorted::TCEJSONValue(fp32 &&);
	template CEJSONSorted::TCEJSONValue(fp32 &);
	template CEJSONSorted::TCEJSONValue(fp32 const &);

	template CEJSONSorted::TCEJSONValue(fp64 &&);
	template CEJSONSorted::TCEJSONValue(fp64 &);
	template CEJSONSorted::TCEJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJSONSorted::TCEJSONValue(int &&);
	template CEJSONSorted::TCEJSONValue(int &);
	template CEJSONSorted::TCEJSONValue(int const &);
#endif
	template CEJSONSorted::TCEJSONValue(bool &&);
	template CEJSONSorted::TCEJSONValue(bool &);
	template CEJSONSorted::TCEJSONValue(bool const &);

	//
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<CNullPtr>(CNullPtr &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<CNullPtr &>(CNullPtr &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int64>(int64 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int64 &>(int64 &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int64 const &>(int64 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int32>(int32 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int32 &>(int32 &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int32 const &>(int32 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<uint64>(uint64 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<uint64 &>(uint64 &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<uint64 const &>(uint64 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<uint32>(uint32 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<uint32 &>(uint32 &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<uint32 const &>(uint32 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<pfp64>(pfp64 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<pfp64 &>(pfp64 &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<pfp64 const &>(pfp64 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<pfp32>(pfp32 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<pfp32 &>(pfp32 &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<pfp32 const &>(pfp32 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<fp32>(fp32 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<fp32 &>(fp32 &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<fp32 const &>(fp32 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<fp64>(fp64 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<fp64 &>(fp64 &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int>(int &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int &>(int &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<int const &>(int const &);
#endif
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<bool>(bool &&);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<bool &>(bool &);
	template CEJSONSorted &CJSONValueEJSONSorted::f_Insert<bool const &>(bool const &);

	template CEJSONSorted &CJSONValueEJSONSorted::operator = <NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

	template CEJSONSorted &CJSONValueEJSONSorted::operator = <CNullPtr>(CNullPtr &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <CNullPtr &>(CNullPtr &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <CNullPtr const &>(CNullPtr const &);

	template CEJSONSorted &CJSONValueEJSONSorted::operator = <NStr::CStr>(NStr::CStr &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <NStr::CStr &>(NStr::CStr &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CEJSONSorted &CJSONValueEJSONSorted::operator = <int64>(int64 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <int64 &>(int64 &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <int64 const &>(int64 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::operator = <int32>(int32 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <int32 &>(int32 &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <int32 const &>(int32 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::operator = <uint64>(uint64 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <uint64 &>(uint64 &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <uint64 const &>(uint64 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::operator = <uint32>(uint32 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <uint32 &>(uint32 &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <uint32 const &>(uint32 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::operator = <pfp64>(pfp64 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <pfp64 &>(pfp64 &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <pfp64 const &>(pfp64 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::operator = <pfp32>(pfp32 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <pfp32 &>(pfp32 &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <pfp32 const &>(pfp32 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::operator = <fp32>(fp32 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <fp32 &>(fp32 &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <fp32 const &>(fp32 const &);

	template CEJSONSorted &CJSONValueEJSONSorted::operator = <fp64>(fp64 &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <fp64 &>(fp64 &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <int>(int &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <int &>(int &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <int const &>(int const &);
#endif
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <bool>(bool &&);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <bool &>(bool &);
	template CEJSONSorted &CJSONValueEJSONSorted::operator = <bool const &>(bool const &);

	template void CJSONValueEJSONSorted::f_Format
		<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONSorted, false>::CLocalOptions>
		(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONSorted, false>::CLocalOptions const &) const
	;

	template void CJSONValueEJSONSorted::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONSorted, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSONSorted, false>::CLocalOptions const&) const
	;
#endif
}
