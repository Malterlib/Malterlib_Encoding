
#include "Malterlib_Encoding_EJSON.h"
#include "Malterlib_Encoding_EJSON.hpp"

namespace NMib
{
	namespace NEncoding
	{
		bool CEJSONUserType::operator == (CEJSONUserType const &_Right) const
		{
			if (m_Type != _Right.m_Type)
				return false;
			return m_Value == _Right.m_Value;
		}
		
		bool CEJSONUserType::operator < (CEJSONUserType const &_Right) const
		{
			if (m_Type < _Right.m_Type)
				return true;
			else if (m_Type > _Right.m_Type)
				return false;
			return m_Value < _Right.m_Value;
		}

		template class NPrivate::TCJSONValueBase<TCEJSONValue, NTime::CTime, NContainer::TCVector<uint8>, CEJSONUserType>;
		template class TCJSONValue<NPrivate::TCJSONValueBase<TCEJSONValue, NTime::CTime, NContainer::TCVector<uint8>, CEJSONUserType>>;
		template class TCEJSONValue<NPrivate::TCJSONValueBase<TCEJSONValue, NTime::CTime, NContainer::TCVector<uint8>, CEJSONUserType>>;
		template class TCJSONObject<CEJSON>;
		template struct NPrivate::TCObjectEntry<CEJSON>;

		template CJSONValueEJSON::TCJSONValue(CNullPtr &&);
#ifndef DCompiler_MSVC
		template CJSONValueEJSON::TCJSONValue(CNullPtr &);
		template CJSONValueEJSON::TCJSONValue(CNullPtr const &);
#endif

		template CJSONValueEJSON::TCJSONValue(NStr::CStr &&);
#ifndef DCompiler_MSVC
		template CJSONValueEJSON::TCJSONValue(NStr::CStr &);
		template CJSONValueEJSON::TCJSONValue(NStr::CStr const &);
#endif

		template CJSONValueEJSON::TCJSONValue(int64 &&);
#ifndef DCompiler_MSVC
		template CJSONValueEJSON::TCJSONValue(int64 &);
		template CJSONValueEJSON::TCJSONValue(int64 const &);
#endif

		template CJSONValueEJSON::TCJSONValue(int32 &&);
#ifndef DCompiler_MSVC
		template CJSONValueEJSON::TCJSONValue(int32 &);
		template CJSONValueEJSON::TCJSONValue(int32 const &);
#endif

		template CJSONValueEJSON::TCJSONValue(uint64 &&);
#ifndef DCompiler_MSVC
		template CJSONValueEJSON::TCJSONValue(uint64 &);
		template CJSONValueEJSON::TCJSONValue(uint64 const &);
#endif

		template CJSONValueEJSON::TCJSONValue(uint32 &&);
#ifndef DCompiler_MSVC
		template CJSONValueEJSON::TCJSONValue(uint32 &);
		template CJSONValueEJSON::TCJSONValue(uint32 const &);
#endif
		
		template CJSONValueEJSON::TCJSONValue(pfp64 &&);
#ifndef DCompiler_MSVC
		template CJSONValueEJSON::TCJSONValue(pfp64 &);
		template CJSONValueEJSON::TCJSONValue(pfp64 const &);
#endif

		template CJSONValueEJSON::TCJSONValue(pfp32 &&);
#ifndef DCompiler_MSVC
		template CJSONValueEJSON::TCJSONValue(pfp32 &);
		template CJSONValueEJSON::TCJSONValue(pfp32 const &);
#endif
		
		template CJSONValueEJSON::TCJSONValue(fp32 &&);
#ifndef DCompiler_MSVC
		template CJSONValueEJSON::TCJSONValue(fp32 &);
		template CJSONValueEJSON::TCJSONValue(fp32 const &);
#endif
		
		template CJSONValueEJSON::TCJSONValue(fp64 &&);
#ifndef DCompiler_MSVC
		template CJSONValueEJSON::TCJSONValue(fp64 &);
		template CJSONValueEJSON::TCJSONValue(fp64 const &);
#endif

#ifdef DMibPUniqueType_int
		template CJSONValueEJSON::TCJSONValue(int &&);
#ifndef DCompiler_MSVC
		template CJSONValueEJSON::TCJSONValue(int &);
		template CJSONValueEJSON::TCJSONValue(int const &);
#endif
#endif
		template CJSONValueEJSON::TCJSONValue(bool &&);
#ifndef DCompiler_MSVC
		template CJSONValueEJSON::TCJSONValue(bool &);
		template CJSONValueEJSON::TCJSONValue(bool const &);
#endif

		//

		template CEJSON::TCEJSONValue(EJSONType &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(EJSONType &);
		template CEJSON::TCEJSONValue(EJSONType const &);
#endif

		template CEJSON::TCEJSONValue(ch8 const *&&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(ch8 const *&);
		template CEJSON::TCEJSONValue(ch8 const *const &);
#endif

		template CEJSON::TCEJSONValue(CNullPtr &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(CNullPtr &);
		template CEJSON::TCEJSONValue(CNullPtr const &);
#endif

		template CEJSON::TCEJSONValue(NStr::CStr &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(NStr::CStr &);
		template CEJSON::TCEJSONValue(NStr::CStr const &);
#endif

		template CEJSON::TCEJSONValue(int64 &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(int64 &);
		template CEJSON::TCEJSONValue(int64 const &);
#endif

		template CEJSON::TCEJSONValue(int32 &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(int32 &);
		template CEJSON::TCEJSONValue(int32 const &);
#endif

		template CEJSON::TCEJSONValue(uint64 &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(uint64 &);
		template CEJSON::TCEJSONValue(uint64 const &);
#endif

		template CEJSON::TCEJSONValue(uint32 &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(uint32 &);
		template CEJSON::TCEJSONValue(uint32 const &);
#endif
		
		template CEJSON::TCEJSONValue(pfp64 &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(pfp64 &);
		template CEJSON::TCEJSONValue(pfp64 const &);
#endif

		template CEJSON::TCEJSONValue(pfp32 &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(pfp32 &);
		template CEJSON::TCEJSONValue(pfp32 const &);
#endif
		
		template CEJSON::TCEJSONValue(fp32 &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(fp32 &);
		template CEJSON::TCEJSONValue(fp32 const &);
#endif
		
		template CEJSON::TCEJSONValue(fp64 &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(fp64 &);
		template CEJSON::TCEJSONValue(fp64 const &);
#endif

#ifdef DMibPUniqueType_int
		template CEJSON::TCEJSONValue(int &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(int &);
		template CEJSON::TCEJSONValue(int const &);
#endif
#endif
		template CEJSON::TCEJSONValue(bool &&);
#ifndef DCompiler_MSVC
		template CEJSON::TCEJSONValue(bool &);
		template CEJSON::TCEJSONValue(bool const &);
#endif

		//

		template CEJSON &CJSONValueEJSON::f_Insert<NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
		template CEJSON &CJSONValueEJSON::f_Insert<NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
		template CEJSON &CJSONValueEJSON::f_Insert<NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

		template CEJSON &CJSONValueEJSON::f_Insert<CNullPtr>(CNullPtr &&);
		template CEJSON &CJSONValueEJSON::f_Insert<CNullPtr &>(CNullPtr &);
		template CEJSON &CJSONValueEJSON::f_Insert<CNullPtr const &>(CNullPtr const &);

		template CEJSON &CJSONValueEJSON::f_Insert<NStr::CStr>(NStr::CStr &&);
		template CEJSON &CJSONValueEJSON::f_Insert<NStr::CStr &>(NStr::CStr &);
		template CEJSON &CJSONValueEJSON::f_Insert<NStr::CStr const &>(NStr::CStr const &);

		template CEJSON &CJSONValueEJSON::f_Insert<int64>(int64 &&);
		template CEJSON &CJSONValueEJSON::f_Insert<int64 &>(int64 &);
		template CEJSON &CJSONValueEJSON::f_Insert<int64 const &>(int64 const &);

		template CEJSON &CJSONValueEJSON::f_Insert<int32>(int32 &&);
		template CEJSON &CJSONValueEJSON::f_Insert<int32 &>(int32 &);
		template CEJSON &CJSONValueEJSON::f_Insert<int32 const &>(int32 const &);

		template CEJSON &CJSONValueEJSON::f_Insert<uint64>(uint64 &&);
		template CEJSON &CJSONValueEJSON::f_Insert<uint64 &>(uint64 &);
		template CEJSON &CJSONValueEJSON::f_Insert<uint64 const &>(uint64 const &);

		template CEJSON &CJSONValueEJSON::f_Insert<uint32>(uint32 &&);
		template CEJSON &CJSONValueEJSON::f_Insert<uint32 &>(uint32 &);
		template CEJSON &CJSONValueEJSON::f_Insert<uint32 const &>(uint32 const &);
		
		template CEJSON &CJSONValueEJSON::f_Insert<pfp64>(pfp64 &&);
		template CEJSON &CJSONValueEJSON::f_Insert<pfp64 &>(pfp64 &);
		template CEJSON &CJSONValueEJSON::f_Insert<pfp64 const &>(pfp64 const &);

		template CEJSON &CJSONValueEJSON::f_Insert<pfp32>(pfp32 &&);
		template CEJSON &CJSONValueEJSON::f_Insert<pfp32 &>(pfp32 &);
		template CEJSON &CJSONValueEJSON::f_Insert<pfp32 const &>(pfp32 const &);
		
		template CEJSON &CJSONValueEJSON::f_Insert<fp32>(fp32 &&);
		template CEJSON &CJSONValueEJSON::f_Insert<fp32 &>(fp32 &);
		template CEJSON &CJSONValueEJSON::f_Insert<fp32 const &>(fp32 const &);
		
		template CEJSON &CJSONValueEJSON::f_Insert<fp64>(fp64 &&);
		template CEJSON &CJSONValueEJSON::f_Insert<fp64 &>(fp64 &);
		template CEJSON &CJSONValueEJSON::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
		template CEJSON &CJSONValueEJSON::f_Insert<int>(int &&);
		template CEJSON &CJSONValueEJSON::f_Insert<int &>(int &);
		template CEJSON &CJSONValueEJSON::f_Insert<int const &>(int const &);
#endif
		template CEJSON &CJSONValueEJSON::f_Insert<bool>(bool &&);
		template CEJSON &CJSONValueEJSON::f_Insert<bool &>(bool &);
		template CEJSON &CJSONValueEJSON::f_Insert<bool const &>(bool const &);

		
		template CEJSON &CJSONValueEJSON::operator = <NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
		template CEJSON &CJSONValueEJSON::operator = <NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
		template CEJSON &CJSONValueEJSON::operator = <NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

		template CEJSON &CJSONValueEJSON::operator = <CNullPtr>(CNullPtr &&);
		template CEJSON &CJSONValueEJSON::operator = <CNullPtr &>(CNullPtr &);
		template CEJSON &CJSONValueEJSON::operator = <CNullPtr const &>(CNullPtr const &);

		template CEJSON &CJSONValueEJSON::operator = <NStr::CStr>(NStr::CStr &&);
		template CEJSON &CJSONValueEJSON::operator = <NStr::CStr &>(NStr::CStr &);
		template CEJSON &CJSONValueEJSON::operator = <NStr::CStr const &>(NStr::CStr const &);

		template CEJSON &CJSONValueEJSON::operator = <int64>(int64 &&);
		template CEJSON &CJSONValueEJSON::operator = <int64 &>(int64 &);
		template CEJSON &CJSONValueEJSON::operator = <int64 const &>(int64 const &);

		template CEJSON &CJSONValueEJSON::operator = <int32>(int32 &&);
		template CEJSON &CJSONValueEJSON::operator = <int32 &>(int32 &);
		template CEJSON &CJSONValueEJSON::operator = <int32 const &>(int32 const &);

		template CEJSON &CJSONValueEJSON::operator = <uint64>(uint64 &&);
		template CEJSON &CJSONValueEJSON::operator = <uint64 &>(uint64 &);
		template CEJSON &CJSONValueEJSON::operator = <uint64 const &>(uint64 const &);

		template CEJSON &CJSONValueEJSON::operator = <uint32>(uint32 &&);
		template CEJSON &CJSONValueEJSON::operator = <uint32 &>(uint32 &);
		template CEJSON &CJSONValueEJSON::operator = <uint32 const &>(uint32 const &);
		
		template CEJSON &CJSONValueEJSON::operator = <pfp64>(pfp64 &&);
		template CEJSON &CJSONValueEJSON::operator = <pfp64 &>(pfp64 &);
		template CEJSON &CJSONValueEJSON::operator = <pfp64 const &>(pfp64 const &);

		template CEJSON &CJSONValueEJSON::operator = <pfp32>(pfp32 &&);
		template CEJSON &CJSONValueEJSON::operator = <pfp32 &>(pfp32 &);
		template CEJSON &CJSONValueEJSON::operator = <pfp32 const &>(pfp32 const &);
		
		template CEJSON &CJSONValueEJSON::operator = <fp32>(fp32 &&);
		template CEJSON &CJSONValueEJSON::operator = <fp32 &>(fp32 &);
		template CEJSON &CJSONValueEJSON::operator = <fp32 const &>(fp32 const &);
		
		template CEJSON &CJSONValueEJSON::operator = <fp64>(fp64 &&);
		template CEJSON &CJSONValueEJSON::operator = <fp64 &>(fp64 &);
		template CEJSON &CJSONValueEJSON::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
		template CEJSON &CJSONValueEJSON::operator = <int>(int &&);
		template CEJSON &CJSONValueEJSON::operator = <int &>(int &);
		template CEJSON &CJSONValueEJSON::operator = <int const &>(int const &);
#endif
		template CEJSON &CJSONValueEJSON::operator = <bool>(bool &&);
		template CEJSON &CJSONValueEJSON::operator = <bool &>(bool &);
		template CEJSON &CJSONValueEJSON::operator = <bool const &>(bool const &);
		
		template void CJSONValueEJSON::f_Format
			<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSON, true>::CLocalOptions>
			(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSON, true>::CLocalOptions const &) const
		;

		template void CJSONValueEJSON::f_Format
			<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSON, true>::CLocalOptions>
			(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJSON, true>::CLocalOptions const&) const
		;
	}
}
