// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_Json.h"
#include "Malterlib_Encoding_Json_Parse.h"
#include "Malterlib_Encoding_Json_Generate.h"
#include "Malterlib_Encoding_Json.hpp"
#include "Malterlib_Encoding_Json_GenerateColored.hpp"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	template struct NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, false>;
	template struct TCJsonValue<NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, false>>;
	template struct TCJsonObject<CJsonSorted, false>;
	template struct NPrivate::TCObjectEntry<CJsonSorted, false>;

	template CJsonValueJsonSorted::TCJsonValue(CJsonValueBaseOrdered const &);
	template CJsonValueJsonSorted::TCJsonValue(CJsonValueBaseOrdered const &&);
	template CJsonValueJsonSorted::TCJsonValue(CJsonValueBaseOrdered &&);

	template TCJsonValue<CJsonValueBaseSorted> CJsonSorted::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &);
	template TCJsonValue<CJsonValueBaseSorted> CJsonSorted::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> &&);
	template TCJsonValue<CJsonValueBaseSorted> CJsonSorted::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &&);

	template CJsonSorted::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &);
	template CJsonSorted::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> &&);
	template CJsonSorted::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &&);

	template CJsonValueBaseSorted::TCJsonValueBase(CJsonValueBaseOrdered const &);
	template CJsonValueBaseSorted::TCJsonValueBase(CJsonValueBaseOrdered &);
	template CJsonValueBaseSorted::TCJsonValueBase(CJsonValueBaseOrdered &&);

	template CJsonSorted::TCJsonValue(CNullPtr &&);
	template CJsonSorted::TCJsonValue(CNullPtr &);
	template CJsonSorted::TCJsonValue(CNullPtr const &);

	template CJsonSorted::TCJsonValue(NStr::CStr &&);
	template CJsonSorted::TCJsonValue(NStr::CStr &);
	template CJsonSorted::TCJsonValue(NStr::CStr const &);

	template CJsonSorted::TCJsonValue(int64 &&);
	template CJsonSorted::TCJsonValue(int64 &);
	template CJsonSorted::TCJsonValue(int64 const &);

	template CJsonSorted::TCJsonValue(int32 &&);
	template CJsonSorted::TCJsonValue(int32 &);
	template CJsonSorted::TCJsonValue(int32 const &);

	template CJsonSorted::TCJsonValue(uint64 &&);
	template CJsonSorted::TCJsonValue(uint64 &);
	template CJsonSorted::TCJsonValue(uint64 const &);

	template CJsonSorted::TCJsonValue(uint32 &&);
	template CJsonSorted::TCJsonValue(uint32 &);
	template CJsonSorted::TCJsonValue(uint32 const &);

	template CJsonSorted::TCJsonValue(pfp64 &&);
	template CJsonSorted::TCJsonValue(pfp64 &);
	template CJsonSorted::TCJsonValue(pfp64 const &);

	template CJsonSorted::TCJsonValue(pfp32 &&);
	template CJsonSorted::TCJsonValue(pfp32 &);
	template CJsonSorted::TCJsonValue(pfp32 const &);

	template CJsonSorted::TCJsonValue(fp32 &&);
	template CJsonSorted::TCJsonValue(fp32 &);
	template CJsonSorted::TCJsonValue(fp32 const &);

	template CJsonSorted::TCJsonValue(fp64 &&);
	template CJsonSorted::TCJsonValue(fp64 &);
	template CJsonSorted::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonSorted::TCJsonValue(int &&);
	template CJsonSorted::TCJsonValue(int &);
	template CJsonSorted::TCJsonValue(int const &);
#endif
	template CJsonSorted::TCJsonValue(bool &&);
	template CJsonSorted::TCJsonValue(bool &);
	template CJsonSorted::TCJsonValue(bool const &);

	template CJsonSorted &CJsonSorted::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CJsonSorted &CJsonSorted::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CJsonSorted &CJsonSorted::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CJsonSorted &CJsonSorted::f_Insert<CNullPtr>(CNullPtr &&);
	template CJsonSorted &CJsonSorted::f_Insert<CNullPtr &>(CNullPtr &);
	template CJsonSorted &CJsonSorted::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CJsonSorted &CJsonSorted::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CJsonSorted &CJsonSorted::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CJsonSorted &CJsonSorted::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CJsonSorted &CJsonSorted::f_Insert<int64>(int64 &&);
	template CJsonSorted &CJsonSorted::f_Insert<int64 &>(int64 &);
	template CJsonSorted &CJsonSorted::f_Insert<int64 const &>(int64 const &);

	template CJsonSorted &CJsonSorted::f_Insert<int32>(int32 &&);
	template CJsonSorted &CJsonSorted::f_Insert<int32 &>(int32 &);
	template CJsonSorted &CJsonSorted::f_Insert<int32 const &>(int32 const &);

	template CJsonSorted &CJsonSorted::f_Insert<uint64>(uint64 &&);
	template CJsonSorted &CJsonSorted::f_Insert<uint64 &>(uint64 &);
	template CJsonSorted &CJsonSorted::f_Insert<uint64 const &>(uint64 const &);

	template CJsonSorted &CJsonSorted::f_Insert<uint32>(uint32 &&);
	template CJsonSorted &CJsonSorted::f_Insert<uint32 &>(uint32 &);
	template CJsonSorted &CJsonSorted::f_Insert<uint32 const &>(uint32 const &);

	template CJsonSorted &CJsonSorted::f_Insert<pfp64>(pfp64 &&);
	template CJsonSorted &CJsonSorted::f_Insert<pfp64 &>(pfp64 &);
	template CJsonSorted &CJsonSorted::f_Insert<pfp64 const &>(pfp64 const &);

	template CJsonSorted &CJsonSorted::f_Insert<pfp32>(pfp32 &&);
	template CJsonSorted &CJsonSorted::f_Insert<pfp32 &>(pfp32 &);
	template CJsonSorted &CJsonSorted::f_Insert<pfp32 const &>(pfp32 const &);

	template CJsonSorted &CJsonSorted::f_Insert<fp32>(fp32 &&);
	template CJsonSorted &CJsonSorted::f_Insert<fp32 &>(fp32 &);
	template CJsonSorted &CJsonSorted::f_Insert<fp32 const &>(fp32 const &);

	template CJsonSorted &CJsonSorted::f_Insert<fp64>(fp64 &&);
	template CJsonSorted &CJsonSorted::f_Insert<fp64 &>(fp64 &);
	template CJsonSorted &CJsonSorted::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonSorted &CJsonSorted::f_Insert<int>(int &&);
	template CJsonSorted &CJsonSorted::f_Insert<int &>(int &);
	template CJsonSorted &CJsonSorted::f_Insert<int const &>(int const &);
#endif
	template CJsonSorted &CJsonSorted::f_Insert<bool>(bool &&);
	template CJsonSorted &CJsonSorted::f_Insert<bool &>(bool &);
	template CJsonSorted &CJsonSorted::f_Insert<bool const &>(bool const &);

	template CJsonSorted &CJsonSorted::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CJsonSorted &CJsonSorted::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CJsonSorted &CJsonSorted::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CJsonSorted &CJsonSorted::operator = <CNullPtr>(CNullPtr &&);
	template CJsonSorted &CJsonSorted::operator = <CNullPtr &>(CNullPtr &);
	template CJsonSorted &CJsonSorted::operator = <CNullPtr const &>(CNullPtr const &);

	template CJsonSorted &CJsonSorted::operator = <NStr::CStr>(NStr::CStr &&);
	template CJsonSorted &CJsonSorted::operator = <NStr::CStr &>(NStr::CStr &);
	template CJsonSorted &CJsonSorted::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CJsonSorted &CJsonSorted::operator = <int64>(int64 &&);
	template CJsonSorted &CJsonSorted::operator = <int64 &>(int64 &);
	template CJsonSorted &CJsonSorted::operator = <int64 const &>(int64 const &);

	template CJsonSorted &CJsonSorted::operator = <int32>(int32 &&);
	template CJsonSorted &CJsonSorted::operator = <int32 &>(int32 &);
	template CJsonSorted &CJsonSorted::operator = <int32 const &>(int32 const &);

	template CJsonSorted &CJsonSorted::operator = <uint64>(uint64 &&);
	template CJsonSorted &CJsonSorted::operator = <uint64 &>(uint64 &);
	template CJsonSorted &CJsonSorted::operator = <uint64 const &>(uint64 const &);

	template CJsonSorted &CJsonSorted::operator = <uint32>(uint32 &&);
	template CJsonSorted &CJsonSorted::operator = <uint32 &>(uint32 &);
	template CJsonSorted &CJsonSorted::operator = <uint32 const &>(uint32 const &);

	template CJsonSorted &CJsonSorted::operator = <pfp64>(pfp64 &&);
	template CJsonSorted &CJsonSorted::operator = <pfp64 &>(pfp64 &);
	template CJsonSorted &CJsonSorted::operator = <pfp64 const &>(pfp64 const &);

	template CJsonSorted &CJsonSorted::operator = <pfp32>(pfp32 &&);
	template CJsonSorted &CJsonSorted::operator = <pfp32 &>(pfp32 &);
	template CJsonSorted &CJsonSorted::operator = <pfp32 const &>(pfp32 const &);

	template CJsonSorted &CJsonSorted::operator = <fp32>(fp32 &&);
	template CJsonSorted &CJsonSorted::operator = <fp32 &>(fp32 &);
	template CJsonSorted &CJsonSorted::operator = <fp32 const &>(fp32 const &);

	template CJsonSorted &CJsonSorted::operator = <fp64>(fp64 &&);
	template CJsonSorted &CJsonSorted::operator = <fp64 &>(fp64 &);
	template CJsonSorted &CJsonSorted::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonSorted &CJsonSorted::operator = <int>(int &&);
	template CJsonSorted &CJsonSorted::operator = <int &>(int &);
	template CJsonSorted &CJsonSorted::operator = <int const &>(int const &);
#endif
	template CJsonSorted &CJsonSorted::operator = <bool>(bool &&);
	template CJsonSorted &CJsonSorted::operator = <bool &>(bool &);
	template CJsonSorted &CJsonSorted::operator = <bool const &>(bool const &);

	template void CJsonSorted::f_Format
		<NStr::CStrAggregate, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSorted, false>::CLocalOptions>
		(NStr::CStrAggregate &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSorted, false>::CLocalOptions const &) const
	;

	template void CJsonSorted::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSorted, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSorted, false>::CLocalOptions const&) const
	;
#endif
}
