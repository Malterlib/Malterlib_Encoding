// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Encoding_Json.h"
#include "Malterlib_Encoding_Json_Parse.h"
#include "Malterlib_Encoding_Json_Generate.h"
#include "Malterlib_Encoding_Yaml.h"
#include "Malterlib_Encoding_Json.hpp"
#include "Malterlib_Encoding_Json_GenerateColored.hpp"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	template struct NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;
	template struct TCJsonValue<NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;
	template struct TCJsonObject<CJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;
	template struct NPrivate::TCObjectEntry<CJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;

	template struct TCJsonObjectEntryHandle<TCJsonObject<CJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;
	template struct TCJsonOrderedDestructiveIterator<TCJsonObject<CJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;
	template struct TCJsonSortedDestructiveIterator<TCJsonObject<CJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;

	template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseOrdered const &);
	template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseOrdered const &&);
	template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseOrdered &&);
	template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSorted const &);
	template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSorted const &&);
	template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSorted &&);
	template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSortedWithComments const &);
	template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSortedWithComments const &&);
	template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSortedWithComments &&);

	template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &);
	template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> &&);
	template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &&);
	template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &);
	template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> &&);
	template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &&);
	template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSortedWithComments>
		(
			TCJsonValue<CJsonValueBaseSortedWithComments> const &
		)
	;
	template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSortedWithComments>
		(
			TCJsonValue<CJsonValueBaseSortedWithComments> &&
		)
	;
	template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSortedWithComments>
		(
			TCJsonValue<CJsonValueBaseSortedWithComments> const &&
		)
	;

	template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &);
	template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> &&);
	template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &&);
	template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &);
	template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> &&);
	template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &&);
	template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedWithComments> const &);
	template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedWithComments> &&);
	template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedWithComments> const &&);

	template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseOrdered const &);
	template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseOrdered &);
	template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseOrdered &&);
	template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSorted const &);
	template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSorted &);
	template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSorted &&);
	template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSortedWithComments const &);
	template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSortedWithComments &);
	template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSortedWithComments &&);

	template CJsonOrderedWithComments::TCJsonValue(CNullPtr &&);
	template CJsonOrderedWithComments::TCJsonValue(CNullPtr &);
	template CJsonOrderedWithComments::TCJsonValue(CNullPtr const &);

	template CJsonOrderedWithComments::TCJsonValue(NStr::CStr &&);
	template CJsonOrderedWithComments::TCJsonValue(NStr::CStr &);
	template CJsonOrderedWithComments::TCJsonValue(NStr::CStr const &);

	template CJsonOrderedWithComments::TCJsonValue(int64 &&);
	template CJsonOrderedWithComments::TCJsonValue(int64 &);
	template CJsonOrderedWithComments::TCJsonValue(int64 const &);

	template CJsonOrderedWithComments::TCJsonValue(int32 &&);
	template CJsonOrderedWithComments::TCJsonValue(int32 &);
	template CJsonOrderedWithComments::TCJsonValue(int32 const &);

	template CJsonOrderedWithComments::TCJsonValue(uint64 &&);
	template CJsonOrderedWithComments::TCJsonValue(uint64 &);
	template CJsonOrderedWithComments::TCJsonValue(uint64 const &);

	template CJsonOrderedWithComments::TCJsonValue(uint32 &&);
	template CJsonOrderedWithComments::TCJsonValue(uint32 &);
	template CJsonOrderedWithComments::TCJsonValue(uint32 const &);

	template CJsonOrderedWithComments::TCJsonValue(pfp64 &&);
	template CJsonOrderedWithComments::TCJsonValue(pfp64 &);
	template CJsonOrderedWithComments::TCJsonValue(pfp64 const &);

	template CJsonOrderedWithComments::TCJsonValue(pfp32 &&);
	template CJsonOrderedWithComments::TCJsonValue(pfp32 &);
	template CJsonOrderedWithComments::TCJsonValue(pfp32 const &);

	template CJsonOrderedWithComments::TCJsonValue(fp32 &&);
	template CJsonOrderedWithComments::TCJsonValue(fp32 &);
	template CJsonOrderedWithComments::TCJsonValue(fp32 const &);

	template CJsonOrderedWithComments::TCJsonValue(fp64 &&);
	template CJsonOrderedWithComments::TCJsonValue(fp64 &);
	template CJsonOrderedWithComments::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonOrderedWithComments::TCJsonValue(int &&);
	template CJsonOrderedWithComments::TCJsonValue(int &);
	template CJsonOrderedWithComments::TCJsonValue(int const &);
#endif
	template CJsonOrderedWithComments::TCJsonValue(bool &&);
	template CJsonOrderedWithComments::TCJsonValue(bool &);
	template CJsonOrderedWithComments::TCJsonValue(bool const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<CNullPtr>(CNullPtr &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<CNullPtr &>(CNullPtr &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int64>(int64 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int64 &>(int64 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int64 const &>(int64 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int32>(int32 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int32 &>(int32 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int32 const &>(int32 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<uint64>(uint64 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<uint64 &>(uint64 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<uint64 const &>(uint64 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<uint32>(uint32 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<uint32 &>(uint32 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<uint32 const &>(uint32 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<pfp64>(pfp64 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<pfp64 &>(pfp64 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<pfp64 const &>(pfp64 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<pfp32>(pfp32 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<pfp32 &>(pfp32 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<pfp32 const &>(pfp32 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<fp32>(fp32 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<fp32 &>(fp32 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<fp32 const &>(fp32 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<fp64>(fp64 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<fp64 &>(fp64 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int>(int &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int &>(int &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int const &>(int const &);
#endif
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<bool>(bool &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<bool &>(bool &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<bool const &>(bool const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <CNullPtr>(CNullPtr &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <CNullPtr &>(CNullPtr &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <CNullPtr const &>(CNullPtr const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <NStr::CStr>(NStr::CStr &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <NStr::CStr &>(NStr::CStr &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int64>(int64 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int64 &>(int64 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int64 const &>(int64 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int32>(int32 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int32 &>(int32 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int32 const &>(int32 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <uint64>(uint64 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <uint64 &>(uint64 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <uint64 const &>(uint64 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <uint32>(uint32 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <uint32 &>(uint32 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <uint32 const &>(uint32 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <pfp64>(pfp64 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <pfp64 &>(pfp64 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <pfp64 const &>(pfp64 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <pfp32>(pfp32 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <pfp32 &>(pfp32 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <pfp32 const &>(pfp32 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <fp32>(fp32 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <fp32 &>(fp32 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <fp32 const &>(fp32 const &);

	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <fp64>(fp64 &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <fp64 &>(fp64 &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int>(int &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int &>(int &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int const &>(int const &);
#endif
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <bool>(bool &&);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <bool &>(bool &);
	template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <bool const &>(bool const &);

	template void CJsonOrderedWithComments::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonOrderedWithComments, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonOrderedWithComments, true>::CLocalOptions const &) const
	;
#endif
}
