#pragma once

#include "Malterlib_Encoding_EJSON.h"

namespace NMib
{
	namespace NEncoding
	{
		extern template class NPrivate::TCJSONValueBase<TCEJSONValue, NTime::CTime, NContainer::TCVector<uint8>, CEJSONUserType>;
		extern template class TCJSONValue<NPrivate::TCJSONValueBase<TCEJSONValue, NTime::CTime, NContainer::TCVector<uint8>, CEJSONUserType>>;
		extern template class TCEJSONValue<NPrivate::TCJSONValueBase<TCEJSONValue, NTime::CTime, NContainer::TCVector<uint8>, CEJSONUserType>>;
		extern template class TCJSONObject<CEJSON>;
		extern template struct NPrivate::TCObjectEntry<CEJSON>;

		typedef TCJSONValue<NPrivate::TCJSONValueBase<TCEJSONValue, NTime::CTime, NContainer::TCVector<uint8>, CEJSONUserType>> CJSONValueEJSON;

#ifndef DCompiler_MSVC
		extern template CJSONValueEJSON::TCJSONValue(CNullPtr &&);
		extern template CJSONValueEJSON::TCJSONValue(CNullPtr &);
		extern template CJSONValueEJSON::TCJSONValue(CNullPtr const &);

		extern template CJSONValueEJSON::TCJSONValue(NStr::CStr &&);
		extern template CJSONValueEJSON::TCJSONValue(NStr::CStr &);
		extern template CJSONValueEJSON::TCJSONValue(NStr::CStr const &);

		extern template CJSONValueEJSON::TCJSONValue(int64 &&);
		extern template CJSONValueEJSON::TCJSONValue(int64 &);
		extern template CJSONValueEJSON::TCJSONValue(int64 const &);

		extern template CJSONValueEJSON::TCJSONValue(int32 &&);
		extern template CJSONValueEJSON::TCJSONValue(int32 &);
		extern template CJSONValueEJSON::TCJSONValue(int32 const &);

		extern template CJSONValueEJSON::TCJSONValue(uint64 &&);
		extern template CJSONValueEJSON::TCJSONValue(uint64 &);
		extern template CJSONValueEJSON::TCJSONValue(uint64 const &);

		extern template CJSONValueEJSON::TCJSONValue(uint32 &&);
		extern template CJSONValueEJSON::TCJSONValue(uint32 &);
		extern template CJSONValueEJSON::TCJSONValue(uint32 const &);
		
		extern template CJSONValueEJSON::TCJSONValue(pfp64 &&);
		extern template CJSONValueEJSON::TCJSONValue(pfp64 &);
		extern template CJSONValueEJSON::TCJSONValue(pfp64 const &);

		extern template CJSONValueEJSON::TCJSONValue(pfp32 &&);
		extern template CJSONValueEJSON::TCJSONValue(pfp32 &);
		extern template CJSONValueEJSON::TCJSONValue(pfp32 const &);
		
		extern template CJSONValueEJSON::TCJSONValue(fp32 &&);
		extern template CJSONValueEJSON::TCJSONValue(fp32 &);
		extern template CJSONValueEJSON::TCJSONValue(fp32 const &);
		
		extern template CJSONValueEJSON::TCJSONValue(fp64 &&);
		extern template CJSONValueEJSON::TCJSONValue(fp64 &);
		extern template CJSONValueEJSON::TCJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
		extern template CJSONValueEJSON::TCJSONValue(int &&);
		extern template CJSONValueEJSON::TCJSONValue(int &);
		extern template CJSONValueEJSON::TCJSONValue(int const &);
#endif
		extern template CJSONValueEJSON::TCJSONValue(bool &&);
		extern template CJSONValueEJSON::TCJSONValue(bool &);
		extern template CJSONValueEJSON::TCJSONValue(bool const &);

		//

		extern template CEJSON::TCEJSONValue(EJSONType &&);
		extern template CEJSON::TCEJSONValue(EJSONType &);
		extern template CEJSON::TCEJSONValue(EJSONType const &);

		extern template CEJSON::TCEJSONValue(ch8 const *&&);
		extern template CEJSON::TCEJSONValue(ch8 const *&);
		extern template CEJSON::TCEJSONValue(ch8 const *const &);

		extern template CEJSON::TCEJSONValue(CNullPtr &&);
		extern template CEJSON::TCEJSONValue(CNullPtr &);
		extern template CEJSON::TCEJSONValue(CNullPtr const &);

		extern template CEJSON::TCEJSONValue(NStr::CStr &&);
		extern template CEJSON::TCEJSONValue(NStr::CStr &);
		extern template CEJSON::TCEJSONValue(NStr::CStr const &);

		extern template CEJSON::TCEJSONValue(int64 &&);
		extern template CEJSON::TCEJSONValue(int64 &);
		extern template CEJSON::TCEJSONValue(int64 const &);

		extern template CEJSON::TCEJSONValue(int32 &&);
		extern template CEJSON::TCEJSONValue(int32 &);
		extern template CEJSON::TCEJSONValue(int32 const &);

		extern template CEJSON::TCEJSONValue(uint64 &&);
		extern template CEJSON::TCEJSONValue(uint64 &);
		extern template CEJSON::TCEJSONValue(uint64 const &);

		extern template CEJSON::TCEJSONValue(uint32 &&);
		extern template CEJSON::TCEJSONValue(uint32 &);
		extern template CEJSON::TCEJSONValue(uint32 const &);
		
		extern template CEJSON::TCEJSONValue(pfp64 &&);
		extern template CEJSON::TCEJSONValue(pfp64 &);
		extern template CEJSON::TCEJSONValue(pfp64 const &);

		extern template CEJSON::TCEJSONValue(pfp32 &&);
		extern template CEJSON::TCEJSONValue(pfp32 &);
		extern template CEJSON::TCEJSONValue(pfp32 const &);
		
		extern template CEJSON::TCEJSONValue(fp32 &&);
		extern template CEJSON::TCEJSONValue(fp32 &);
		extern template CEJSON::TCEJSONValue(fp32 const &);
		
		extern template CEJSON::TCEJSONValue(fp64 &&);
		extern template CEJSON::TCEJSONValue(fp64 &);
		extern template CEJSON::TCEJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
		extern template CEJSON::TCEJSONValue(int &&);
		extern template CEJSON::TCEJSONValue(int &);
		extern template CEJSON::TCEJSONValue(int const &);
#endif
		extern template CEJSON::TCEJSONValue(bool &&);
		extern template CEJSON::TCEJSONValue(bool &);
		extern template CEJSON::TCEJSONValue(bool const &);
#endif

		//
#ifndef DCompiler_MSVC
		extern template CEJSON &CJSONValueEJSON::f_Insert<NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

		extern template CEJSON &CJSONValueEJSON::f_Insert<CNullPtr>(CNullPtr &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<CNullPtr &>(CNullPtr &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<CNullPtr const &>(CNullPtr const &);

		extern template CEJSON &CJSONValueEJSON::f_Insert<NStr::CStr>(NStr::CStr &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<NStr::CStr &>(NStr::CStr &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<NStr::CStr const &>(NStr::CStr const &);

		extern template CEJSON &CJSONValueEJSON::f_Insert<int64>(int64 &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<int64 &>(int64 &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<int64 const &>(int64 const &);

		extern template CEJSON &CJSONValueEJSON::f_Insert<int32>(int32 &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<int32 &>(int32 &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<int32 const &>(int32 const &);

		extern template CEJSON &CJSONValueEJSON::f_Insert<uint64>(uint64 &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<uint64 &>(uint64 &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<uint64 const &>(uint64 const &);

		extern template CEJSON &CJSONValueEJSON::f_Insert<uint32>(uint32 &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<uint32 &>(uint32 &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<uint32 const &>(uint32 const &);
		
		extern template CEJSON &CJSONValueEJSON::f_Insert<pfp64>(pfp64 &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<pfp64 &>(pfp64 &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<pfp64 const &>(pfp64 const &);

		extern template CEJSON &CJSONValueEJSON::f_Insert<pfp32>(pfp32 &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<pfp32 &>(pfp32 &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<pfp32 const &>(pfp32 const &);
		
		extern template CEJSON &CJSONValueEJSON::f_Insert<fp32>(fp32 &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<fp32 &>(fp32 &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<fp32 const &>(fp32 const &);
		
		extern template CEJSON &CJSONValueEJSON::f_Insert<fp64>(fp64 &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<fp64 &>(fp64 &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
		extern template CEJSON &CJSONValueEJSON::f_Insert<int>(int &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<int &>(int &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<int const &>(int const &);
#endif
		extern template CEJSON &CJSONValueEJSON::f_Insert<bool>(bool &&);
		extern template CEJSON &CJSONValueEJSON::f_Insert<bool &>(bool &);
		extern template CEJSON &CJSONValueEJSON::f_Insert<bool const &>(bool const &);
#endif

		extern template CEJSON &CJSONValueEJSON::operator = <NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
		extern template CEJSON &CJSONValueEJSON::operator = <NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
		extern template CEJSON &CJSONValueEJSON::operator = <NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

		extern template CEJSON &CJSONValueEJSON::operator = <CNullPtr>(CNullPtr &&);
		extern template CEJSON &CJSONValueEJSON::operator = <CNullPtr &>(CNullPtr &);
		extern template CEJSON &CJSONValueEJSON::operator = <CNullPtr const &>(CNullPtr const &);

		extern template CEJSON &CJSONValueEJSON::operator = <NStr::CStr>(NStr::CStr &&);
		extern template CEJSON &CJSONValueEJSON::operator = <NStr::CStr &>(NStr::CStr &);
		extern template CEJSON &CJSONValueEJSON::operator = <NStr::CStr const &>(NStr::CStr const &);

		extern template CEJSON &CJSONValueEJSON::operator = <int64>(int64 &&);
		extern template CEJSON &CJSONValueEJSON::operator = <int64 &>(int64 &);
		extern template CEJSON &CJSONValueEJSON::operator = <int64 const &>(int64 const &);

		extern template CEJSON &CJSONValueEJSON::operator = <int32>(int32 &&);
		extern template CEJSON &CJSONValueEJSON::operator = <int32 &>(int32 &);
		extern template CEJSON &CJSONValueEJSON::operator = <int32 const &>(int32 const &);

		extern template CEJSON &CJSONValueEJSON::operator = <uint64>(uint64 &&);
		extern template CEJSON &CJSONValueEJSON::operator = <uint64 &>(uint64 &);
		extern template CEJSON &CJSONValueEJSON::operator = <uint64 const &>(uint64 const &);

		extern template CEJSON &CJSONValueEJSON::operator = <uint32>(uint32 &&);
		extern template CEJSON &CJSONValueEJSON::operator = <uint32 &>(uint32 &);
		extern template CEJSON &CJSONValueEJSON::operator = <uint32 const &>(uint32 const &);
		
		extern template CEJSON &CJSONValueEJSON::operator = <pfp64>(pfp64 &&);
		extern template CEJSON &CJSONValueEJSON::operator = <pfp64 &>(pfp64 &);
		extern template CEJSON &CJSONValueEJSON::operator = <pfp64 const &>(pfp64 const &);

		extern template CEJSON &CJSONValueEJSON::operator = <pfp32>(pfp32 &&);
		extern template CEJSON &CJSONValueEJSON::operator = <pfp32 &>(pfp32 &);
		extern template CEJSON &CJSONValueEJSON::operator = <pfp32 const &>(pfp32 const &);
		
		extern template CEJSON &CJSONValueEJSON::operator = <fp32>(fp32 &&);
		extern template CEJSON &CJSONValueEJSON::operator = <fp32 &>(fp32 &);
		extern template CEJSON &CJSONValueEJSON::operator = <fp32 const &>(fp32 const &);
		
		extern template CEJSON &CJSONValueEJSON::operator = <fp64>(fp64 &&);
		extern template CEJSON &CJSONValueEJSON::operator = <fp64 &>(fp64 &);
		extern template CEJSON &CJSONValueEJSON::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
		extern template CEJSON &CJSONValueEJSON::operator = <int>(int &&);
		extern template CEJSON &CJSONValueEJSON::operator = <int &>(int &);
		extern template CEJSON &CJSONValueEJSON::operator = <int const &>(int const &);
#endif
		extern template CEJSON &CJSONValueEJSON::operator = <bool>(bool &&);
		extern template CEJSON &CJSONValueEJSON::operator = <bool &>(bool &);
		extern template CEJSON &CJSONValueEJSON::operator = <bool const &>(bool const &);
		
		extern template void CJSONValueEJSON::f_Format
			<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSON, true>::CLocalOptions>
			(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSON, true>::CLocalOptions const &) const
		;

		extern template void CJSONValueEJSON::f_Format
			<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSON, true>::CLocalOptions>
			(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSON, true>::CLocalOptions const&) const
		;
	}
}

#include "Malterlib_Encoding_EJSON_Value.hpp"
