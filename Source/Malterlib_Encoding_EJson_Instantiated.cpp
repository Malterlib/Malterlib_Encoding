// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Encoding_EJson.h"
#include "Malterlib_Encoding_EJson.hpp"
#include "Malterlib_Encoding_EJson_Generate.h"
#include "Malterlib_Encoding_EJson_Parse.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	template struct NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesOrdered, true>;
	template struct TCJsonValue<CEJsonValueBaseOrdered>;
	template struct TCEJsonValue<CEJsonValueBaseOrdered>;
	template struct TCJsonObject<CEJsonOrdered, true>;
	template struct NPrivate::TCObjectEntry<CEJsonOrdered, true>;

	// Destructive iterator types for ordered mode
	template struct TCJsonObjectEntryHandle<TCJsonObject<CEJsonOrdered, true>>;
	template struct TCJsonOrderedDestructiveIterator<TCJsonObject<CEJsonOrdered, true>>;
	template struct TCJsonSortedDestructiveIterator<TCJsonObject<CEJsonOrdered, true>>;

	template CJsonValueEJsonOrdered::TCJsonValue(CEJsonValueBaseSorted const &);
	template CJsonValueEJsonOrdered::TCJsonValue(CEJsonValueBaseSorted const &&);
	template CJsonValueEJsonOrdered::TCJsonValue(CEJsonValueBaseSorted &&);

	template TCEJsonValue<CEJsonValueBaseOrdered> CEJsonOrdered::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &);
	template TCEJsonValue<CEJsonValueBaseOrdered> CEJsonOrdered::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> &&);
	template TCEJsonValue<CEJsonValueBaseOrdered> CEJsonOrdered::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &&);

	template CEJsonOrdered::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &);
	template CEJsonOrdered::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> &&);
	template CEJsonOrdered::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &&);

	template CEJsonValueBaseOrdered::TCJsonValueBase(CEJsonValueBaseSorted const &);
	template CEJsonValueBaseOrdered::TCJsonValueBase(CEJsonValueBaseSorted &);
	template CEJsonValueBaseOrdered::TCJsonValueBase(CEJsonValueBaseSorted &&);

	template CJsonValueEJsonOrdered::TCJsonValue(CNullPtr &&);
	template CJsonValueEJsonOrdered::TCJsonValue(CNullPtr &);
	template CJsonValueEJsonOrdered::TCJsonValue(CNullPtr const &);

	template CJsonValueEJsonOrdered::TCJsonValue(NStr::CStr &&);
	template CJsonValueEJsonOrdered::TCJsonValue(NStr::CStr &);
	template CJsonValueEJsonOrdered::TCJsonValue(NStr::CStr const &);

	template CJsonValueEJsonOrdered::TCJsonValue(int64 &&);
	template CJsonValueEJsonOrdered::TCJsonValue(int64 &);
	template CJsonValueEJsonOrdered::TCJsonValue(int64 const &);

	template CJsonValueEJsonOrdered::TCJsonValue(int32 &&);
	template CJsonValueEJsonOrdered::TCJsonValue(int32 &);
	template CJsonValueEJsonOrdered::TCJsonValue(int32 const &);

	template CJsonValueEJsonOrdered::TCJsonValue(uint64 &&);
	template CJsonValueEJsonOrdered::TCJsonValue(uint64 &);
	template CJsonValueEJsonOrdered::TCJsonValue(uint64 const &);

	template CJsonValueEJsonOrdered::TCJsonValue(uint32 &&);
	template CJsonValueEJsonOrdered::TCJsonValue(uint32 &);
	template CJsonValueEJsonOrdered::TCJsonValue(uint32 const &);

	template CJsonValueEJsonOrdered::TCJsonValue(pfp64 &&);
	template CJsonValueEJsonOrdered::TCJsonValue(pfp64 &);
	template CJsonValueEJsonOrdered::TCJsonValue(pfp64 const &);

	template CJsonValueEJsonOrdered::TCJsonValue(pfp32 &&);
	template CJsonValueEJsonOrdered::TCJsonValue(pfp32 &);
	template CJsonValueEJsonOrdered::TCJsonValue(pfp32 const &);

	template CJsonValueEJsonOrdered::TCJsonValue(fp32 &&);
	template CJsonValueEJsonOrdered::TCJsonValue(fp32 &);
	template CJsonValueEJsonOrdered::TCJsonValue(fp32 const &);

	template CJsonValueEJsonOrdered::TCJsonValue(fp64 &&);
	template CJsonValueEJsonOrdered::TCJsonValue(fp64 &);
	template CJsonValueEJsonOrdered::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonValueEJsonOrdered::TCJsonValue(int &&);
	template CJsonValueEJsonOrdered::TCJsonValue(int &);
	template CJsonValueEJsonOrdered::TCJsonValue(int const &);
#endif
	template CJsonValueEJsonOrdered::TCJsonValue(bool &&);
	template CJsonValueEJsonOrdered::TCJsonValue(bool &);
	template CJsonValueEJsonOrdered::TCJsonValue(bool const &);

	//

	template CEJsonOrdered::TCEJsonValue(EJsonType &&);
	template CEJsonOrdered::TCEJsonValue(EJsonType &);
	template CEJsonOrdered::TCEJsonValue(EJsonType const &);

	template CEJsonOrdered::TCEJsonValue(ch8 const *&&);
	template CEJsonOrdered::TCEJsonValue(ch8 const *&);
	template CEJsonOrdered::TCEJsonValue(ch8 const *const &);

	template CEJsonOrdered::TCEJsonValue(CNullPtr &&);
	template CEJsonOrdered::TCEJsonValue(CNullPtr &);
	template CEJsonOrdered::TCEJsonValue(CNullPtr const &);

	template CEJsonOrdered::TCEJsonValue(NStr::CStr &&);
	template CEJsonOrdered::TCEJsonValue(NStr::CStr &);
	template CEJsonOrdered::TCEJsonValue(NStr::CStr const &);

	template CEJsonOrdered::TCEJsonValue(int64 &&);
	template CEJsonOrdered::TCEJsonValue(int64 &);
	template CEJsonOrdered::TCEJsonValue(int64 const &);

	template CEJsonOrdered::TCEJsonValue(int32 &&);
	template CEJsonOrdered::TCEJsonValue(int32 &);
	template CEJsonOrdered::TCEJsonValue(int32 const &);

	template CEJsonOrdered::TCEJsonValue(uint64 &&);
	template CEJsonOrdered::TCEJsonValue(uint64 &);
	template CEJsonOrdered::TCEJsonValue(uint64 const &);

	template CEJsonOrdered::TCEJsonValue(uint32 &&);
	template CEJsonOrdered::TCEJsonValue(uint32 &);
	template CEJsonOrdered::TCEJsonValue(uint32 const &);

	template CEJsonOrdered::TCEJsonValue(pfp64 &&);
	template CEJsonOrdered::TCEJsonValue(pfp64 &);
	template CEJsonOrdered::TCEJsonValue(pfp64 const &);

	template CEJsonOrdered::TCEJsonValue(pfp32 &&);
	template CEJsonOrdered::TCEJsonValue(pfp32 &);
	template CEJsonOrdered::TCEJsonValue(pfp32 const &);

	template CEJsonOrdered::TCEJsonValue(fp32 &&);
	template CEJsonOrdered::TCEJsonValue(fp32 &);
	template CEJsonOrdered::TCEJsonValue(fp32 const &);

	template CEJsonOrdered::TCEJsonValue(fp64 &&);
	template CEJsonOrdered::TCEJsonValue(fp64 &);
	template CEJsonOrdered::TCEJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonOrdered::TCEJsonValue(int &&);
	template CEJsonOrdered::TCEJsonValue(int &);
	template CEJsonOrdered::TCEJsonValue(int const &);
#endif
	template CEJsonOrdered::TCEJsonValue(bool &&);
	template CEJsonOrdered::TCEJsonValue(bool &);
	template CEJsonOrdered::TCEJsonValue(bool const &);

	//
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<CNullPtr>(CNullPtr &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<CNullPtr &>(CNullPtr &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int64>(int64 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int64 &>(int64 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int64 const &>(int64 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int32>(int32 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int32 &>(int32 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int32 const &>(int32 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<uint64>(uint64 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<uint64 &>(uint64 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<uint64 const &>(uint64 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<uint32>(uint32 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<uint32 &>(uint32 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<uint32 const &>(uint32 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<pfp64>(pfp64 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<pfp64 &>(pfp64 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<pfp64 const &>(pfp64 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<pfp32>(pfp32 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<pfp32 &>(pfp32 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<pfp32 const &>(pfp32 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<fp32>(fp32 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<fp32 &>(fp32 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<fp32 const &>(fp32 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<fp64>(fp64 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<fp64 &>(fp64 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int>(int &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int &>(int &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<int const &>(int const &);
#endif
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<bool>(bool &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<bool &>(bool &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::f_Insert<bool const &>(bool const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <CNullPtr>(CNullPtr &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <CNullPtr &>(CNullPtr &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <CNullPtr const &>(CNullPtr const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <NStr::CStr>(NStr::CStr &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <NStr::CStr &>(NStr::CStr &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int64>(int64 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int64 &>(int64 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int64 const &>(int64 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int32>(int32 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int32 &>(int32 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int32 const &>(int32 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <uint64>(uint64 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <uint64 &>(uint64 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <uint64 const &>(uint64 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <uint32>(uint32 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <uint32 &>(uint32 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <uint32 const &>(uint32 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <pfp64>(pfp64 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <pfp64 &>(pfp64 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <pfp64 const &>(pfp64 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <pfp32>(pfp32 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <pfp32 &>(pfp32 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <pfp32 const &>(pfp32 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <fp32>(fp32 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <fp32 &>(fp32 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <fp32 const &>(fp32 const &);

	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <fp64>(fp64 &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <fp64 &>(fp64 &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int>(int &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int &>(int &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <int const &>(int const &);
#endif
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <bool>(bool &&);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <bool &>(bool &);
	template CEJsonOrdered &CJsonValueEJsonOrdered::operator = <bool const &>(bool const &);

	template void CJsonValueEJsonOrdered::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonOrdered, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonOrdered, true>::CLocalOptions const &) const
	;
#endif
}
