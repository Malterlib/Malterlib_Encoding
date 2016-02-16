#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib
{
	namespace NEncoding
	{
		extern template class NPrivate::TCJSONValueBase<TCJSONValue>;
		extern template class TCJSONValue<NPrivate::TCJSONValueBase<TCJSONValue>>;
		extern template class TCJSONObject<CJSON>;
		extern template struct NPrivate::TCObjectEntry<CJSON>;

#ifndef DCompiler_MSVC
		extern template CJSON::TCJSONValue(CNullPtr &&);
		extern template CJSON::TCJSONValue(CNullPtr &);
		extern template CJSON::TCJSONValue(CNullPtr const &);

		extern template CJSON::TCJSONValue(NStr::CStr &&);
		extern template CJSON::TCJSONValue(NStr::CStr &);
		extern template CJSON::TCJSONValue(NStr::CStr const &);

		extern template CJSON::TCJSONValue(int64 &&);
		extern template CJSON::TCJSONValue(int64 &);
		extern template CJSON::TCJSONValue(int64 const &);

		extern template CJSON::TCJSONValue(int32 &&);
		extern template CJSON::TCJSONValue(int32 &);
		extern template CJSON::TCJSONValue(int32 const &);

		extern template CJSON::TCJSONValue(uint64 &&);
		extern template CJSON::TCJSONValue(uint64 &);
		extern template CJSON::TCJSONValue(uint64 const &);

		extern template CJSON::TCJSONValue(uint32 &&);
		extern template CJSON::TCJSONValue(uint32 &);
		extern template CJSON::TCJSONValue(uint32 const &);
		
		extern template CJSON::TCJSONValue(pfp64 &&);
		extern template CJSON::TCJSONValue(pfp64 &);
		extern template CJSON::TCJSONValue(pfp64 const &);

		extern template CJSON::TCJSONValue(pfp32 &&);
		extern template CJSON::TCJSONValue(pfp32 &);
		extern template CJSON::TCJSONValue(pfp32 const &);
		
		extern template CJSON::TCJSONValue(fp32 &&);
		extern template CJSON::TCJSONValue(fp32 &);
		extern template CJSON::TCJSONValue(fp32 const &);
		
		extern template CJSON::TCJSONValue(fp64 &&);
		extern template CJSON::TCJSONValue(fp64 &);
		extern template CJSON::TCJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
		extern template CJSON::TCJSONValue(int &&);
		extern template CJSON::TCJSONValue(int &);
		extern template CJSON::TCJSONValue(int const &);
#endif
		extern template CJSON::TCJSONValue(bool &&);
		extern template CJSON::TCJSONValue(bool &);
		extern template CJSON::TCJSONValue(bool const &);
#endif
		
		
		extern template CJSON &CJSON::f_Insert<NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
		extern template CJSON &CJSON::f_Insert<NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
		extern template CJSON &CJSON::f_Insert<NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

		extern template CJSON &CJSON::f_Insert<CNullPtr>(CNullPtr &&);
		extern template CJSON &CJSON::f_Insert<CNullPtr &>(CNullPtr &);
		extern template CJSON &CJSON::f_Insert<CNullPtr const &>(CNullPtr const &);

		extern template CJSON &CJSON::f_Insert<NStr::CStr>(NStr::CStr &&);
		extern template CJSON &CJSON::f_Insert<NStr::CStr &>(NStr::CStr &);
		extern template CJSON &CJSON::f_Insert<NStr::CStr const &>(NStr::CStr const &);

#ifndef DCompiler_MSVC
		extern template CJSON &CJSON::f_Insert<int64>(int64 &&);
		extern template CJSON &CJSON::f_Insert<int64 &>(int64 &);
		extern template CJSON &CJSON::f_Insert<int64 const &>(int64 const &);

		extern template CJSON &CJSON::f_Insert<int32>(int32 &&);
		extern template CJSON &CJSON::f_Insert<int32 &>(int32 &);
		extern template CJSON &CJSON::f_Insert<int32 const &>(int32 const &);

		extern template CJSON &CJSON::f_Insert<uint64>(uint64 &&);
		extern template CJSON &CJSON::f_Insert<uint64 &>(uint64 &);
		extern template CJSON &CJSON::f_Insert<uint64 const &>(uint64 const &);

		extern template CJSON &CJSON::f_Insert<uint32>(uint32 &&);
		extern template CJSON &CJSON::f_Insert<uint32 &>(uint32 &);
		extern template CJSON &CJSON::f_Insert<uint32 const &>(uint32 const &);
		
		extern template CJSON &CJSON::f_Insert<pfp64>(pfp64 &&);
		extern template CJSON &CJSON::f_Insert<pfp64 &>(pfp64 &);
		extern template CJSON &CJSON::f_Insert<pfp64 const &>(pfp64 const &);

		extern template CJSON &CJSON::f_Insert<pfp32>(pfp32 &&);
		extern template CJSON &CJSON::f_Insert<pfp32 &>(pfp32 &);
		extern template CJSON &CJSON::f_Insert<pfp32 const &>(pfp32 const &);
		
		extern template CJSON &CJSON::f_Insert<fp32>(fp32 &&);
		extern template CJSON &CJSON::f_Insert<fp32 &>(fp32 &);
		extern template CJSON &CJSON::f_Insert<fp32 const &>(fp32 const &);
		
		extern template CJSON &CJSON::f_Insert<fp64>(fp64 &&);
		extern template CJSON &CJSON::f_Insert<fp64 &>(fp64 &);
		extern template CJSON &CJSON::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
		extern template CJSON &CJSON::f_Insert<int>(int &&);
		extern template CJSON &CJSON::f_Insert<int &>(int &);
		extern template CJSON &CJSON::f_Insert<int const &>(int const &);
#endif
		extern template CJSON &CJSON::f_Insert<bool>(bool &&);
		extern template CJSON &CJSON::f_Insert<bool &>(bool &);
		extern template CJSON &CJSON::f_Insert<bool const &>(bool const &);
#endif
		
		extern template CJSON &CJSON::operator = <NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
		extern template CJSON &CJSON::operator = <NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
		extern template CJSON &CJSON::operator = <NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

		extern template CJSON &CJSON::operator = <CNullPtr>(CNullPtr &&);
		extern template CJSON &CJSON::operator = <CNullPtr &>(CNullPtr &);
		extern template CJSON &CJSON::operator = <CNullPtr const &>(CNullPtr const &);

		extern template CJSON &CJSON::operator = <NStr::CStr>(NStr::CStr &&);
		extern template CJSON &CJSON::operator = <NStr::CStr &>(NStr::CStr &);
		extern template CJSON &CJSON::operator = <NStr::CStr const &>(NStr::CStr const &);

		extern template CJSON &CJSON::operator = <int64>(int64 &&);
		extern template CJSON &CJSON::operator = <int64 &>(int64 &);
		extern template CJSON &CJSON::operator = <int64 const &>(int64 const &);

		extern template CJSON &CJSON::operator = <int32>(int32 &&);
		extern template CJSON &CJSON::operator = <int32 &>(int32 &);
		extern template CJSON &CJSON::operator = <int32 const &>(int32 const &);

		extern template CJSON &CJSON::operator = <uint64>(uint64 &&);
		extern template CJSON &CJSON::operator = <uint64 &>(uint64 &);
		extern template CJSON &CJSON::operator = <uint64 const &>(uint64 const &);

		extern template CJSON &CJSON::operator = <uint32>(uint32 &&);
		extern template CJSON &CJSON::operator = <uint32 &>(uint32 &);
		extern template CJSON &CJSON::operator = <uint32 const &>(uint32 const &);
		
		extern template CJSON &CJSON::operator = <pfp64>(pfp64 &&);
		extern template CJSON &CJSON::operator = <pfp64 &>(pfp64 &);
		extern template CJSON &CJSON::operator = <pfp64 const &>(pfp64 const &);

		extern template CJSON &CJSON::operator = <pfp32>(pfp32 &&);
		extern template CJSON &CJSON::operator = <pfp32 &>(pfp32 &);
		extern template CJSON &CJSON::operator = <pfp32 const &>(pfp32 const &);
		
		extern template CJSON &CJSON::operator = <fp32>(fp32 &&);
		extern template CJSON &CJSON::operator = <fp32 &>(fp32 &);
		extern template CJSON &CJSON::operator = <fp32 const &>(fp32 const &);
		
		extern template CJSON &CJSON::operator = <fp64>(fp64 &&);
		extern template CJSON &CJSON::operator = <fp64 &>(fp64 &);
		extern template CJSON &CJSON::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
		extern template CJSON &CJSON::operator = <int>(int &&);
		extern template CJSON &CJSON::operator = <int &>(int &);
		extern template CJSON &CJSON::operator = <int const &>(int const &);
#endif
		extern template CJSON &CJSON::operator = <bool>(bool &&);
		extern template CJSON &CJSON::operator = <bool &>(bool &);
		extern template CJSON &CJSON::operator = <bool const &>(bool const &);
		
		extern template void CJSON::f_Format
			<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSON, true>::CLocalOptions>
			(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSON, true>::CLocalOptions const &) const
		;

		extern template void CJSON::f_Format
			<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSON, true>::CLocalOptions>
			(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSON, true>::CLocalOptions const&) const
		;
	}
}
