// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_EJson.h"
#include "Malterlib_Encoding_EJson.hpp"
#include "Malterlib_Encoding_EJson_Generate.h"
#include "Malterlib_Encoding_EJson_Parse.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	template struct NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesSorted, false>;
	template struct TCJsonValue<CEJsonValueBaseSorted>;
	template struct TCEJsonValue<CEJsonValueBaseSorted>;
	template struct TCJsonObject<CEJsonSorted, false>;
	template struct NPrivate::TCObjectEntry<CEJsonSorted, false>;

	template CJsonValueEJsonSorted::TCJsonValue(CEJsonValueBaseOrdered const &);
	template CJsonValueEJsonSorted::TCJsonValue(CEJsonValueBaseOrdered const &&);
	template CJsonValueEJsonSorted::TCJsonValue(CEJsonValueBaseOrdered &&);

	template TCEJsonValue<CEJsonValueBaseSorted> CEJsonSorted::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	template TCEJsonValue<CEJsonValueBaseSorted> CEJsonSorted::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	template TCEJsonValue<CEJsonValueBaseSorted> CEJsonSorted::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &&);

	template CEJsonSorted::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	template CEJsonSorted::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	template CEJsonSorted::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &&);

	template CEJsonValueBaseSorted::TCJsonValueBase(CEJsonValueBaseOrdered const &);
	template CEJsonValueBaseSorted::TCJsonValueBase(CEJsonValueBaseOrdered &);
	template CEJsonValueBaseSorted::TCJsonValueBase(CEJsonValueBaseOrdered &&);

	template CJsonValueEJsonSorted::TCJsonValue(CNullPtr &&);
	template CJsonValueEJsonSorted::TCJsonValue(CNullPtr &);
	template CJsonValueEJsonSorted::TCJsonValue(CNullPtr const &);

	template CJsonValueEJsonSorted::TCJsonValue(NStr::CStr &&);
	template CJsonValueEJsonSorted::TCJsonValue(NStr::CStr &);
	template CJsonValueEJsonSorted::TCJsonValue(NStr::CStr const &);

	template CJsonValueEJsonSorted::TCJsonValue(int64 &&);
	template CJsonValueEJsonSorted::TCJsonValue(int64 &);
	template CJsonValueEJsonSorted::TCJsonValue(int64 const &);

	template CJsonValueEJsonSorted::TCJsonValue(int32 &&);
	template CJsonValueEJsonSorted::TCJsonValue(int32 &);
	template CJsonValueEJsonSorted::TCJsonValue(int32 const &);

	template CJsonValueEJsonSorted::TCJsonValue(uint64 &&);
	template CJsonValueEJsonSorted::TCJsonValue(uint64 &);
	template CJsonValueEJsonSorted::TCJsonValue(uint64 const &);

	template CJsonValueEJsonSorted::TCJsonValue(uint32 &&);
	template CJsonValueEJsonSorted::TCJsonValue(uint32 &);
	template CJsonValueEJsonSorted::TCJsonValue(uint32 const &);

	template CJsonValueEJsonSorted::TCJsonValue(pfp64 &&);
	template CJsonValueEJsonSorted::TCJsonValue(pfp64 &);
	template CJsonValueEJsonSorted::TCJsonValue(pfp64 const &);

	template CJsonValueEJsonSorted::TCJsonValue(pfp32 &&);
	template CJsonValueEJsonSorted::TCJsonValue(pfp32 &);
	template CJsonValueEJsonSorted::TCJsonValue(pfp32 const &);

	template CJsonValueEJsonSorted::TCJsonValue(fp32 &&);
	template CJsonValueEJsonSorted::TCJsonValue(fp32 &);
	template CJsonValueEJsonSorted::TCJsonValue(fp32 const &);

	template CJsonValueEJsonSorted::TCJsonValue(fp64 &&);
	template CJsonValueEJsonSorted::TCJsonValue(fp64 &);
	template CJsonValueEJsonSorted::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonValueEJsonSorted::TCJsonValue(int &&);
	template CJsonValueEJsonSorted::TCJsonValue(int &);
	template CJsonValueEJsonSorted::TCJsonValue(int const &);
#endif
	template CJsonValueEJsonSorted::TCJsonValue(bool &&);
	template CJsonValueEJsonSorted::TCJsonValue(bool &);
	template CJsonValueEJsonSorted::TCJsonValue(bool const &);

	//

	template CEJsonSorted::TCEJsonValue(EJsonType &&);
	template CEJsonSorted::TCEJsonValue(EJsonType &);
	template CEJsonSorted::TCEJsonValue(EJsonType const &);

	template CEJsonSorted::TCEJsonValue(ch8 const *&&);
	template CEJsonSorted::TCEJsonValue(ch8 const *&);
	template CEJsonSorted::TCEJsonValue(ch8 const *const &);

	template CEJsonSorted::TCEJsonValue(CNullPtr &&);
	template CEJsonSorted::TCEJsonValue(CNullPtr &);
	template CEJsonSorted::TCEJsonValue(CNullPtr const &);

	template CEJsonSorted::TCEJsonValue(NStr::CStr &&);
	template CEJsonSorted::TCEJsonValue(NStr::CStr &);
	template CEJsonSorted::TCEJsonValue(NStr::CStr const &);

	template CEJsonSorted::TCEJsonValue(int64 &&);
	template CEJsonSorted::TCEJsonValue(int64 &);
	template CEJsonSorted::TCEJsonValue(int64 const &);

	template CEJsonSorted::TCEJsonValue(int32 &&);
	template CEJsonSorted::TCEJsonValue(int32 &);
	template CEJsonSorted::TCEJsonValue(int32 const &);

	template CEJsonSorted::TCEJsonValue(uint64 &&);
	template CEJsonSorted::TCEJsonValue(uint64 &);
	template CEJsonSorted::TCEJsonValue(uint64 const &);

	template CEJsonSorted::TCEJsonValue(uint32 &&);
	template CEJsonSorted::TCEJsonValue(uint32 &);
	template CEJsonSorted::TCEJsonValue(uint32 const &);

	template CEJsonSorted::TCEJsonValue(pfp64 &&);
	template CEJsonSorted::TCEJsonValue(pfp64 &);
	template CEJsonSorted::TCEJsonValue(pfp64 const &);

	template CEJsonSorted::TCEJsonValue(pfp32 &&);
	template CEJsonSorted::TCEJsonValue(pfp32 &);
	template CEJsonSorted::TCEJsonValue(pfp32 const &);

	template CEJsonSorted::TCEJsonValue(fp32 &&);
	template CEJsonSorted::TCEJsonValue(fp32 &);
	template CEJsonSorted::TCEJsonValue(fp32 const &);

	template CEJsonSorted::TCEJsonValue(fp64 &&);
	template CEJsonSorted::TCEJsonValue(fp64 &);
	template CEJsonSorted::TCEJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonSorted::TCEJsonValue(int &&);
	template CEJsonSorted::TCEJsonValue(int &);
	template CEJsonSorted::TCEJsonValue(int const &);
#endif
	template CEJsonSorted::TCEJsonValue(bool &&);
	template CEJsonSorted::TCEJsonValue(bool &);
	template CEJsonSorted::TCEJsonValue(bool const &);

	//
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<CNullPtr>(CNullPtr &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<CNullPtr &>(CNullPtr &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int64>(int64 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int64 &>(int64 &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int64 const &>(int64 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int32>(int32 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int32 &>(int32 &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int32 const &>(int32 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<uint64>(uint64 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<uint64 &>(uint64 &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<uint64 const &>(uint64 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<uint32>(uint32 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<uint32 &>(uint32 &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<uint32 const &>(uint32 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<pfp64>(pfp64 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<pfp64 &>(pfp64 &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<pfp64 const &>(pfp64 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<pfp32>(pfp32 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<pfp32 &>(pfp32 &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<pfp32 const &>(pfp32 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<fp32>(fp32 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<fp32 &>(fp32 &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<fp32 const &>(fp32 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<fp64>(fp64 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<fp64 &>(fp64 &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int>(int &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int &>(int &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<int const &>(int const &);
#endif
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<bool>(bool &&);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<bool &>(bool &);
	template CEJsonSorted &CJsonValueEJsonSorted::f_Insert<bool const &>(bool const &);

	template CEJsonSorted &CJsonValueEJsonSorted::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CEJsonSorted &CJsonValueEJsonSorted::operator = <CNullPtr>(CNullPtr &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <CNullPtr &>(CNullPtr &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <CNullPtr const &>(CNullPtr const &);

	template CEJsonSorted &CJsonValueEJsonSorted::operator = <NStr::CStr>(NStr::CStr &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <NStr::CStr &>(NStr::CStr &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CEJsonSorted &CJsonValueEJsonSorted::operator = <int64>(int64 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <int64 &>(int64 &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <int64 const &>(int64 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::operator = <int32>(int32 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <int32 &>(int32 &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <int32 const &>(int32 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::operator = <uint64>(uint64 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <uint64 &>(uint64 &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <uint64 const &>(uint64 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::operator = <uint32>(uint32 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <uint32 &>(uint32 &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <uint32 const &>(uint32 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::operator = <pfp64>(pfp64 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <pfp64 &>(pfp64 &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <pfp64 const &>(pfp64 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::operator = <pfp32>(pfp32 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <pfp32 &>(pfp32 &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <pfp32 const &>(pfp32 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::operator = <fp32>(fp32 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <fp32 &>(fp32 &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <fp32 const &>(fp32 const &);

	template CEJsonSorted &CJsonValueEJsonSorted::operator = <fp64>(fp64 &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <fp64 &>(fp64 &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <int>(int &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <int &>(int &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <int const &>(int const &);
#endif
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <bool>(bool &&);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <bool &>(bool &);
	template CEJsonSorted &CJsonValueEJsonSorted::operator = <bool const &>(bool const &);

	template void CJsonValueEJsonSorted::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonSorted, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonSorted, false>::CLocalOptions const &) const
	;
#endif
}
