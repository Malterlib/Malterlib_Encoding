// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_JSON.h"
#include "Malterlib_Encoding_JSON.hpp"

namespace NMib
{
	namespace NEncoding
	{
		namespace NPrivate
		{
			CObjectEntryBase::CObjectEntryBase()
			{
			}
			
			CObjectEntryBase::CObjectEntryBase(CObjectEntryBase const &_Other)
				: mp_Name(_Other.mp_Name)
			{
			}

			CObjectEntryBase::CObjectEntryBase(CObjectEntryBase &&_Other)
				: mp_Name(fg_Move(_Other.mp_Name))
			{
			}
		}

		namespace NPrivate
		{
			CJSON fg_JSONParse(NStr::CStr const &_String, NStr::CStr const &_FileName, bool _bConvertNullToSpace);
			NStr::CStr fg_JSONGenerate(CJSON const &_JSON, ch8 const *_pPrettySeparator);
			NStr::CStr fg_JSONGenerateColored(CJSON const &_JSON, ch8 const *_pPrettySeparator);
		}

#ifndef DDocumentation_Doxygen
		template <>
		CJSON CJSON::fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName, bool _bConvertNullToSpace)
		{
			return NPrivate::fg_JSONParse(_String, _FileName, _bConvertNullToSpace);
		}

		template <>
		NStr::CStr CJSON::f_ToString(ch8 const *_pPrettySeparator) const
		{
			return NPrivate::fg_JSONGenerate(*this, _pPrettySeparator);
		}

		template <>
		NStr::CStr CJSON::f_ToStringColored(ch8 const *_pPrettySeparator, bool _bUseColor) const
		{
			if (_bUseColor)
				return NPrivate::fg_JSONGenerateColored(*this, _pPrettySeparator);
			else
				return NPrivate::fg_JSONGenerate(*this, _pPrettySeparator);
		}
#endif
		
#ifdef DMibEncodingJSONExternTemplate
		template class NPrivate::TCJSONValueBase<TCJSONValue, NPrivate::CJSONExtraTypes>;
		template class TCJSONValue<NPrivate::TCJSONValueBase<TCJSONValue, NPrivate::CJSONExtraTypes>>;
		template class TCJSONObject<CJSON>;
		template struct NPrivate::TCObjectEntry<CJSON>;

		template CJSON::TCJSONValue(CNullPtr &&);
		template CJSON::TCJSONValue(CNullPtr &);
		template CJSON::TCJSONValue(CNullPtr const &);

		template CJSON::TCJSONValue(NStr::CStr &&);
		template CJSON::TCJSONValue(NStr::CStr &);
		template CJSON::TCJSONValue(NStr::CStr const &);

		template CJSON::TCJSONValue(int64 &&);
		template CJSON::TCJSONValue(int64 &);
		template CJSON::TCJSONValue(int64 const &);

		template CJSON::TCJSONValue(int32 &&);
		template CJSON::TCJSONValue(int32 &);
		template CJSON::TCJSONValue(int32 const &);

		template CJSON::TCJSONValue(uint64 &&);
		template CJSON::TCJSONValue(uint64 &);
		template CJSON::TCJSONValue(uint64 const &);

		template CJSON::TCJSONValue(uint32 &&);
		template CJSON::TCJSONValue(uint32 &);
		template CJSON::TCJSONValue(uint32 const &);
		
		template CJSON::TCJSONValue(pfp64 &&);
		template CJSON::TCJSONValue(pfp64 &);
		template CJSON::TCJSONValue(pfp64 const &);

		template CJSON::TCJSONValue(pfp32 &&);
		template CJSON::TCJSONValue(pfp32 &);
		template CJSON::TCJSONValue(pfp32 const &);
		
		template CJSON::TCJSONValue(fp32 &&);
		template CJSON::TCJSONValue(fp32 &);
		template CJSON::TCJSONValue(fp32 const &);
		
		template CJSON::TCJSONValue(fp64 &&);
		template CJSON::TCJSONValue(fp64 &);
		template CJSON::TCJSONValue(fp64 const &);

#ifdef DMibPUniqueType_int
		template CJSON::TCJSONValue(int &&);
		template CJSON::TCJSONValue(int &);
		template CJSON::TCJSONValue(int const &);
#endif
		template CJSON::TCJSONValue(bool &&);
		template CJSON::TCJSONValue(bool &);
		template CJSON::TCJSONValue(bool const &);
		
		template CJSON &CJSON::f_Insert<NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
		template CJSON &CJSON::f_Insert<NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
		template CJSON &CJSON::f_Insert<NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

		template CJSON &CJSON::f_Insert<CNullPtr>(CNullPtr &&);
		template CJSON &CJSON::f_Insert<CNullPtr &>(CNullPtr &);
		template CJSON &CJSON::f_Insert<CNullPtr const &>(CNullPtr const &);

		template CJSON &CJSON::f_Insert<NStr::CStr>(NStr::CStr &&);
		template CJSON &CJSON::f_Insert<NStr::CStr &>(NStr::CStr &);
		template CJSON &CJSON::f_Insert<NStr::CStr const &>(NStr::CStr const &);

		template CJSON &CJSON::f_Insert<int64>(int64 &&);
		template CJSON &CJSON::f_Insert<int64 &>(int64 &);
		template CJSON &CJSON::f_Insert<int64 const &>(int64 const &);

		template CJSON &CJSON::f_Insert<int32>(int32 &&);
		template CJSON &CJSON::f_Insert<int32 &>(int32 &);
		template CJSON &CJSON::f_Insert<int32 const &>(int32 const &);

		template CJSON &CJSON::f_Insert<uint64>(uint64 &&);
		template CJSON &CJSON::f_Insert<uint64 &>(uint64 &);
		template CJSON &CJSON::f_Insert<uint64 const &>(uint64 const &);

		template CJSON &CJSON::f_Insert<uint32>(uint32 &&);
		template CJSON &CJSON::f_Insert<uint32 &>(uint32 &);
		template CJSON &CJSON::f_Insert<uint32 const &>(uint32 const &);
		
		template CJSON &CJSON::f_Insert<pfp64>(pfp64 &&);
		template CJSON &CJSON::f_Insert<pfp64 &>(pfp64 &);
		template CJSON &CJSON::f_Insert<pfp64 const &>(pfp64 const &);

		template CJSON &CJSON::f_Insert<pfp32>(pfp32 &&);
		template CJSON &CJSON::f_Insert<pfp32 &>(pfp32 &);
		template CJSON &CJSON::f_Insert<pfp32 const &>(pfp32 const &);
		
		template CJSON &CJSON::f_Insert<fp32>(fp32 &&);
		template CJSON &CJSON::f_Insert<fp32 &>(fp32 &);
		template CJSON &CJSON::f_Insert<fp32 const &>(fp32 const &);
		
		template CJSON &CJSON::f_Insert<fp64>(fp64 &&);
		template CJSON &CJSON::f_Insert<fp64 &>(fp64 &);
		template CJSON &CJSON::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
		template CJSON &CJSON::f_Insert<int>(int &&);
		template CJSON &CJSON::f_Insert<int &>(int &);
		template CJSON &CJSON::f_Insert<int const &>(int const &);
#endif
		template CJSON &CJSON::f_Insert<bool>(bool &&);
		template CJSON &CJSON::f_Insert<bool &>(bool &);
		template CJSON &CJSON::f_Insert<bool const &>(bool const &);
		
		template CJSON &CJSON::operator = <NMib::NEncoding::EJSONType>(NMib::NEncoding::EJSONType &&);
		template CJSON &CJSON::operator = <NMib::NEncoding::EJSONType &>(NMib::NEncoding::EJSONType &);
		template CJSON &CJSON::operator = <NMib::NEncoding::EJSONType const &>(NMib::NEncoding::EJSONType const &);

		template CJSON &CJSON::operator = <CNullPtr>(CNullPtr &&);
		template CJSON &CJSON::operator = <CNullPtr &>(CNullPtr &);
		template CJSON &CJSON::operator = <CNullPtr const &>(CNullPtr const &);

		template CJSON &CJSON::operator = <NStr::CStr>(NStr::CStr &&);
		template CJSON &CJSON::operator = <NStr::CStr &>(NStr::CStr &);
		template CJSON &CJSON::operator = <NStr::CStr const &>(NStr::CStr const &);

		template CJSON &CJSON::operator = <int64>(int64 &&);
		template CJSON &CJSON::operator = <int64 &>(int64 &);
		template CJSON &CJSON::operator = <int64 const &>(int64 const &);

		template CJSON &CJSON::operator = <int32>(int32 &&);
		template CJSON &CJSON::operator = <int32 &>(int32 &);
		template CJSON &CJSON::operator = <int32 const &>(int32 const &);

		template CJSON &CJSON::operator = <uint64>(uint64 &&);
		template CJSON &CJSON::operator = <uint64 &>(uint64 &);
		template CJSON &CJSON::operator = <uint64 const &>(uint64 const &);

		template CJSON &CJSON::operator = <uint32>(uint32 &&);
		template CJSON &CJSON::operator = <uint32 &>(uint32 &);
		template CJSON &CJSON::operator = <uint32 const &>(uint32 const &);
		
		template CJSON &CJSON::operator = <pfp64>(pfp64 &&);
		template CJSON &CJSON::operator = <pfp64 &>(pfp64 &);
		template CJSON &CJSON::operator = <pfp64 const &>(pfp64 const &);

		template CJSON &CJSON::operator = <pfp32>(pfp32 &&);
		template CJSON &CJSON::operator = <pfp32 &>(pfp32 &);
		template CJSON &CJSON::operator = <pfp32 const &>(pfp32 const &);
		
		template CJSON &CJSON::operator = <fp32>(fp32 &&);
		template CJSON &CJSON::operator = <fp32 &>(fp32 &);
		template CJSON &CJSON::operator = <fp32 const &>(fp32 const &);
		
		template CJSON &CJSON::operator = <fp64>(fp64 &&);
		template CJSON &CJSON::operator = <fp64 &>(fp64 &);
		template CJSON &CJSON::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
		template CJSON &CJSON::operator = <int>(int &&);
		template CJSON &CJSON::operator = <int &>(int &);
		template CJSON &CJSON::operator = <int const &>(int const &);
#endif
		template CJSON &CJSON::operator = <bool>(bool &&);
		template CJSON &CJSON::operator = <bool &>(bool &);
		template CJSON &CJSON::operator = <bool const &>(bool const &);
		
		template void CJSON::f_Format
			<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSON, true>::CLocalOptions>
			(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSON, true>::CLocalOptions const &) const
		;

		template void CJSON::f_Format
			<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSON, true>::CLocalOptions>
			(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJSON, true>::CLocalOptions const&) const
		;
#endif
	}
}
