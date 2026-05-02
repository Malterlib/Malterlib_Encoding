// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Encoding_EJson.h"
#include "Malterlib_Encoding_EJson.hpp"
#include "Malterlib_Encoding_EJson_Generate.h"
#include "Malterlib_Encoding_EJson_Parse.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	template struct NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;
	template struct TCJsonValue<CEJsonValueBaseOrderedWithComments>;
	template struct TCEJsonValue<CEJsonValueBaseOrderedWithComments>;
	template struct TCJsonObject<CEJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;
	template struct NPrivate::TCObjectEntry<CEJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;

	template struct TCJsonObjectEntryHandle<TCJsonObject<CEJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;
	template struct TCJsonOrderedDestructiveIterator<TCJsonObject<CEJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;
	template struct TCJsonSortedDestructiveIterator<TCJsonObject<CEJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;

	template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseOrdered const &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseOrdered const &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseOrdered &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseSorted const &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseSorted const &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseSorted &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseSortedWithComments const &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseSortedWithComments const &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(CEJsonValueBaseSortedWithComments &&);

	template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &);
	template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> &&);
	template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &&);
	template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseSortedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseSortedWithComments> const &
		)
	;
	template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseSortedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseSortedWithComments> &&
		)
	;
	template TCEJsonValue<CEJsonValueBaseOrderedWithComments> CEJsonOrderedWithComments::fs_FromCompatible<CEJsonValueBaseSortedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseSortedWithComments> const &&
		)
	;

	template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &);
	template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> &&);
	template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &&);
	template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedWithComments> const &);
	template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedWithComments> &&);
	template CEJsonOrderedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedWithComments> const &&);

	template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseOrdered const &);
	template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseOrdered &);
	template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseOrdered &&);
	template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseSorted const &);
	template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseSorted &);
	template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseSorted &&);
	template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseSortedWithComments const &);
	template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseSortedWithComments &);
	template CEJsonValueBaseOrderedWithComments::TCJsonValueBase(CEJsonValueBaseSortedWithComments &&);

	template CJsonValueEJsonOrderedWithComments::TCJsonValue(CNullPtr &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(CNullPtr &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(CNullPtr const &);

	template CJsonValueEJsonOrderedWithComments::TCJsonValue(NStr::CStr &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(NStr::CStr &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(NStr::CStr const &);

	template CJsonValueEJsonOrderedWithComments::TCJsonValue(int64 &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(int64 &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(int64 const &);

	template CJsonValueEJsonOrderedWithComments::TCJsonValue(int32 &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(int32 &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(int32 const &);

	template CJsonValueEJsonOrderedWithComments::TCJsonValue(uint64 &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(uint64 &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(uint64 const &);

	template CJsonValueEJsonOrderedWithComments::TCJsonValue(uint32 &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(uint32 &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(uint32 const &);

	template CJsonValueEJsonOrderedWithComments::TCJsonValue(pfp64 &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(pfp64 &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(pfp64 const &);

	template CJsonValueEJsonOrderedWithComments::TCJsonValue(pfp32 &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(pfp32 &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(pfp32 const &);

	template CJsonValueEJsonOrderedWithComments::TCJsonValue(fp32 &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(fp32 &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(fp32 const &);

	template CJsonValueEJsonOrderedWithComments::TCJsonValue(fp64 &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(fp64 &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(int &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(int &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(int const &);
#endif
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(bool &&);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(bool &);
	template CJsonValueEJsonOrderedWithComments::TCJsonValue(bool const &);

	template CEJsonOrderedWithComments::TCEJsonValue(EJsonType &&);
	template CEJsonOrderedWithComments::TCEJsonValue(EJsonType &);
	template CEJsonOrderedWithComments::TCEJsonValue(EJsonType const &);

	template CEJsonOrderedWithComments::TCEJsonValue(ch8 const *&&);
	template CEJsonOrderedWithComments::TCEJsonValue(ch8 const *&);
	template CEJsonOrderedWithComments::TCEJsonValue(ch8 const *const &);

	template CEJsonOrderedWithComments::TCEJsonValue(CNullPtr &&);
	template CEJsonOrderedWithComments::TCEJsonValue(CNullPtr &);
	template CEJsonOrderedWithComments::TCEJsonValue(CNullPtr const &);

	template CEJsonOrderedWithComments::TCEJsonValue(NStr::CStr &&);
	template CEJsonOrderedWithComments::TCEJsonValue(NStr::CStr &);
	template CEJsonOrderedWithComments::TCEJsonValue(NStr::CStr const &);

	template CEJsonOrderedWithComments::TCEJsonValue(int64 &&);
	template CEJsonOrderedWithComments::TCEJsonValue(int64 &);
	template CEJsonOrderedWithComments::TCEJsonValue(int64 const &);

	template CEJsonOrderedWithComments::TCEJsonValue(int32 &&);
	template CEJsonOrderedWithComments::TCEJsonValue(int32 &);
	template CEJsonOrderedWithComments::TCEJsonValue(int32 const &);

	template CEJsonOrderedWithComments::TCEJsonValue(uint64 &&);
	template CEJsonOrderedWithComments::TCEJsonValue(uint64 &);
	template CEJsonOrderedWithComments::TCEJsonValue(uint64 const &);

	template CEJsonOrderedWithComments::TCEJsonValue(uint32 &&);
	template CEJsonOrderedWithComments::TCEJsonValue(uint32 &);
	template CEJsonOrderedWithComments::TCEJsonValue(uint32 const &);

	template CEJsonOrderedWithComments::TCEJsonValue(pfp64 &&);
	template CEJsonOrderedWithComments::TCEJsonValue(pfp64 &);
	template CEJsonOrderedWithComments::TCEJsonValue(pfp64 const &);

	template CEJsonOrderedWithComments::TCEJsonValue(pfp32 &&);
	template CEJsonOrderedWithComments::TCEJsonValue(pfp32 &);
	template CEJsonOrderedWithComments::TCEJsonValue(pfp32 const &);

	template CEJsonOrderedWithComments::TCEJsonValue(fp32 &&);
	template CEJsonOrderedWithComments::TCEJsonValue(fp32 &);
	template CEJsonOrderedWithComments::TCEJsonValue(fp32 const &);

	template CEJsonOrderedWithComments::TCEJsonValue(fp64 &&);
	template CEJsonOrderedWithComments::TCEJsonValue(fp64 &);
	template CEJsonOrderedWithComments::TCEJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonOrderedWithComments::TCEJsonValue(int &&);
	template CEJsonOrderedWithComments::TCEJsonValue(int &);
	template CEJsonOrderedWithComments::TCEJsonValue(int const &);
#endif
	template CEJsonOrderedWithComments::TCEJsonValue(bool &&);
	template CEJsonOrderedWithComments::TCEJsonValue(bool &);
	template CEJsonOrderedWithComments::TCEJsonValue(bool const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<CNullPtr>(CNullPtr &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<CNullPtr &>(CNullPtr &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int64>(int64 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int64 &>(int64 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int64 const &>(int64 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int32>(int32 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int32 &>(int32 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int32 const &>(int32 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<uint64>(uint64 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<uint64 &>(uint64 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<uint64 const &>(uint64 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<uint32>(uint32 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<uint32 &>(uint32 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<uint32 const &>(uint32 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<pfp64>(pfp64 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<pfp64 &>(pfp64 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<pfp64 const &>(pfp64 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<pfp32>(pfp32 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<pfp32 &>(pfp32 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<pfp32 const &>(pfp32 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<fp32>(fp32 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<fp32 &>(fp32 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<fp32 const &>(fp32 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<fp64>(fp64 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<fp64 &>(fp64 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int>(int &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int &>(int &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<int const &>(int const &);
#endif
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<bool>(bool &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<bool &>(bool &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::f_Insert<bool const &>(bool const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <CNullPtr>(CNullPtr &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <CNullPtr &>(CNullPtr &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <CNullPtr const &>(CNullPtr const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <NStr::CStr>(NStr::CStr &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <NStr::CStr &>(NStr::CStr &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int64>(int64 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int64 &>(int64 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int64 const &>(int64 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int32>(int32 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int32 &>(int32 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int32 const &>(int32 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <uint64>(uint64 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <uint64 &>(uint64 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <uint64 const &>(uint64 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <uint32>(uint32 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <uint32 &>(uint32 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <uint32 const &>(uint32 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <pfp64>(pfp64 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <pfp64 &>(pfp64 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <pfp64 const &>(pfp64 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <pfp32>(pfp32 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <pfp32 &>(pfp32 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <pfp32 const &>(pfp32 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <fp32>(fp32 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <fp32 &>(fp32 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <fp32 const &>(fp32 const &);

	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <fp64>(fp64 &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <fp64 &>(fp64 &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int>(int &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int &>(int &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <int const &>(int const &);
#endif
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <bool>(bool &&);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <bool &>(bool &);
	template CEJsonOrderedWithComments &CJsonValueEJsonOrderedWithComments::operator = <bool const &>(bool const &);

	template void CJsonValueEJsonOrderedWithComments::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonOrderedWithComments, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonOrderedWithComments, true>::CLocalOptions const &) const
	;
#endif
}
