// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Encoding_Json.h"
#include "Malterlib_Encoding_Json_Parse.h"
#include "Malterlib_Encoding_Json_Generate.h"
#include "Malterlib_Encoding_Json.hpp"
#include "Malterlib_Encoding_Json_GenerateColored.hpp"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	template struct NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, true>;
	template struct TCJsonValue<NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, true>>;
	template struct TCJsonObject<CJsonOrdered, true>;
	template struct NPrivate::TCObjectEntry<CJsonOrdered, true>;

	// Destructive iterator types for ordered mode
	template struct TCJsonObjectEntryHandle<TCJsonObject<CJsonOrdered, true>>;
	template struct TCJsonOrderedDestructiveIterator<TCJsonObject<CJsonOrdered, true>>;
	template struct TCJsonSortedDestructiveIterator<TCJsonObject<CJsonOrdered, true>>;

	template CJsonValueJsonOrdered::TCJsonValue(CJsonValueBaseSorted const &);
	template CJsonValueJsonOrdered::TCJsonValue(CJsonValueBaseSorted const &&);
	template CJsonValueJsonOrdered::TCJsonValue(CJsonValueBaseSorted &&);

	template TCJsonValue<CJsonValueBaseOrdered> CJsonOrdered::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &);
	template TCJsonValue<CJsonValueBaseOrdered> CJsonOrdered::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> &&);
	template TCJsonValue<CJsonValueBaseOrdered> CJsonOrdered::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &&);

	template CJsonOrdered::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &);
	template CJsonOrdered::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> &&);
	template CJsonOrdered::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &&);

	template CJsonValueBaseOrdered::TCJsonValueBase(CJsonValueBaseSorted const &);
	template CJsonValueBaseOrdered::TCJsonValueBase(CJsonValueBaseSorted &);
	template CJsonValueBaseOrdered::TCJsonValueBase(CJsonValueBaseSorted &&);

	template CJsonOrdered::TCJsonValue(CNullPtr &&);
	template CJsonOrdered::TCJsonValue(CNullPtr &);
	template CJsonOrdered::TCJsonValue(CNullPtr const &);

	template CJsonOrdered::TCJsonValue(NStr::CStr &&);
	template CJsonOrdered::TCJsonValue(NStr::CStr &);
	template CJsonOrdered::TCJsonValue(NStr::CStr const &);

	template CJsonOrdered::TCJsonValue(int64 &&);
	template CJsonOrdered::TCJsonValue(int64 &);
	template CJsonOrdered::TCJsonValue(int64 const &);

	template CJsonOrdered::TCJsonValue(int32 &&);
	template CJsonOrdered::TCJsonValue(int32 &);
	template CJsonOrdered::TCJsonValue(int32 const &);

	template CJsonOrdered::TCJsonValue(uint64 &&);
	template CJsonOrdered::TCJsonValue(uint64 &);
	template CJsonOrdered::TCJsonValue(uint64 const &);

	template CJsonOrdered::TCJsonValue(uint32 &&);
	template CJsonOrdered::TCJsonValue(uint32 &);
	template CJsonOrdered::TCJsonValue(uint32 const &);

	template CJsonOrdered::TCJsonValue(pfp64 &&);
	template CJsonOrdered::TCJsonValue(pfp64 &);
	template CJsonOrdered::TCJsonValue(pfp64 const &);

	template CJsonOrdered::TCJsonValue(pfp32 &&);
	template CJsonOrdered::TCJsonValue(pfp32 &);
	template CJsonOrdered::TCJsonValue(pfp32 const &);

	template CJsonOrdered::TCJsonValue(fp32 &&);
	template CJsonOrdered::TCJsonValue(fp32 &);
	template CJsonOrdered::TCJsonValue(fp32 const &);

	template CJsonOrdered::TCJsonValue(fp64 &&);
	template CJsonOrdered::TCJsonValue(fp64 &);
	template CJsonOrdered::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonOrdered::TCJsonValue(int &&);
	template CJsonOrdered::TCJsonValue(int &);
	template CJsonOrdered::TCJsonValue(int const &);
#endif
	template CJsonOrdered::TCJsonValue(bool &&);
	template CJsonOrdered::TCJsonValue(bool &);
	template CJsonOrdered::TCJsonValue(bool const &);

	template CJsonOrdered &CJsonOrdered::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CJsonOrdered &CJsonOrdered::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CJsonOrdered &CJsonOrdered::f_Insert<CNullPtr>(CNullPtr &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<CNullPtr &>(CNullPtr &);
	template CJsonOrdered &CJsonOrdered::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CJsonOrdered &CJsonOrdered::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CJsonOrdered &CJsonOrdered::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CJsonOrdered &CJsonOrdered::f_Insert<int64>(int64 &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<int64 &>(int64 &);
	template CJsonOrdered &CJsonOrdered::f_Insert<int64 const &>(int64 const &);

	template CJsonOrdered &CJsonOrdered::f_Insert<int32>(int32 &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<int32 &>(int32 &);
	template CJsonOrdered &CJsonOrdered::f_Insert<int32 const &>(int32 const &);

	template CJsonOrdered &CJsonOrdered::f_Insert<uint64>(uint64 &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<uint64 &>(uint64 &);
	template CJsonOrdered &CJsonOrdered::f_Insert<uint64 const &>(uint64 const &);

	template CJsonOrdered &CJsonOrdered::f_Insert<uint32>(uint32 &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<uint32 &>(uint32 &);
	template CJsonOrdered &CJsonOrdered::f_Insert<uint32 const &>(uint32 const &);

	template CJsonOrdered &CJsonOrdered::f_Insert<pfp64>(pfp64 &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<pfp64 &>(pfp64 &);
	template CJsonOrdered &CJsonOrdered::f_Insert<pfp64 const &>(pfp64 const &);

	template CJsonOrdered &CJsonOrdered::f_Insert<pfp32>(pfp32 &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<pfp32 &>(pfp32 &);
	template CJsonOrdered &CJsonOrdered::f_Insert<pfp32 const &>(pfp32 const &);

	template CJsonOrdered &CJsonOrdered::f_Insert<fp32>(fp32 &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<fp32 &>(fp32 &);
	template CJsonOrdered &CJsonOrdered::f_Insert<fp32 const &>(fp32 const &);

	template CJsonOrdered &CJsonOrdered::f_Insert<fp64>(fp64 &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<fp64 &>(fp64 &);
	template CJsonOrdered &CJsonOrdered::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonOrdered &CJsonOrdered::f_Insert<int>(int &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<int &>(int &);
	template CJsonOrdered &CJsonOrdered::f_Insert<int const &>(int const &);
#endif
	template CJsonOrdered &CJsonOrdered::f_Insert<bool>(bool &&);
	template CJsonOrdered &CJsonOrdered::f_Insert<bool &>(bool &);
	template CJsonOrdered &CJsonOrdered::f_Insert<bool const &>(bool const &);

	template CJsonOrdered &CJsonOrdered::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CJsonOrdered &CJsonOrdered::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CJsonOrdered &CJsonOrdered::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CJsonOrdered &CJsonOrdered::operator = <CNullPtr>(CNullPtr &&);
	template CJsonOrdered &CJsonOrdered::operator = <CNullPtr &>(CNullPtr &);
	template CJsonOrdered &CJsonOrdered::operator = <CNullPtr const &>(CNullPtr const &);

	template CJsonOrdered &CJsonOrdered::operator = <NStr::CStr>(NStr::CStr &&);
	template CJsonOrdered &CJsonOrdered::operator = <NStr::CStr &>(NStr::CStr &);
	template CJsonOrdered &CJsonOrdered::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CJsonOrdered &CJsonOrdered::operator = <int64>(int64 &&);
	template CJsonOrdered &CJsonOrdered::operator = <int64 &>(int64 &);
	template CJsonOrdered &CJsonOrdered::operator = <int64 const &>(int64 const &);

	template CJsonOrdered &CJsonOrdered::operator = <int32>(int32 &&);
	template CJsonOrdered &CJsonOrdered::operator = <int32 &>(int32 &);
	template CJsonOrdered &CJsonOrdered::operator = <int32 const &>(int32 const &);

	template CJsonOrdered &CJsonOrdered::operator = <uint64>(uint64 &&);
	template CJsonOrdered &CJsonOrdered::operator = <uint64 &>(uint64 &);
	template CJsonOrdered &CJsonOrdered::operator = <uint64 const &>(uint64 const &);

	template CJsonOrdered &CJsonOrdered::operator = <uint32>(uint32 &&);
	template CJsonOrdered &CJsonOrdered::operator = <uint32 &>(uint32 &);
	template CJsonOrdered &CJsonOrdered::operator = <uint32 const &>(uint32 const &);

	template CJsonOrdered &CJsonOrdered::operator = <pfp64>(pfp64 &&);
	template CJsonOrdered &CJsonOrdered::operator = <pfp64 &>(pfp64 &);
	template CJsonOrdered &CJsonOrdered::operator = <pfp64 const &>(pfp64 const &);

	template CJsonOrdered &CJsonOrdered::operator = <pfp32>(pfp32 &&);
	template CJsonOrdered &CJsonOrdered::operator = <pfp32 &>(pfp32 &);
	template CJsonOrdered &CJsonOrdered::operator = <pfp32 const &>(pfp32 const &);

	template CJsonOrdered &CJsonOrdered::operator = <fp32>(fp32 &&);
	template CJsonOrdered &CJsonOrdered::operator = <fp32 &>(fp32 &);
	template CJsonOrdered &CJsonOrdered::operator = <fp32 const &>(fp32 const &);

	template CJsonOrdered &CJsonOrdered::operator = <fp64>(fp64 &&);
	template CJsonOrdered &CJsonOrdered::operator = <fp64 &>(fp64 &);
	template CJsonOrdered &CJsonOrdered::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonOrdered &CJsonOrdered::operator = <int>(int &&);
	template CJsonOrdered &CJsonOrdered::operator = <int &>(int &);
	template CJsonOrdered &CJsonOrdered::operator = <int const &>(int const &);
#endif
	template CJsonOrdered &CJsonOrdered::operator = <bool>(bool &&);
	template CJsonOrdered &CJsonOrdered::operator = <bool &>(bool &);
	template CJsonOrdered &CJsonOrdered::operator = <bool const &>(bool const &);

	template void CJsonOrdered::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonOrdered, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonOrdered, true>::CLocalOptions const &) const
	;
#endif
}
