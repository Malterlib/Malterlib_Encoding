// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	extern template struct NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;
	extern template struct TCJsonValue<NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;
	extern template struct TCJsonObject<CJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;
	extern template struct NPrivate::TCObjectEntry<CJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;

	extern template struct TCJsonObjectEntryHandle<TCJsonObject<CJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;
	extern template struct TCJsonOrderedDestructiveIterator<TCJsonObject<CJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;
	extern template struct TCJsonSortedDestructiveIterator<TCJsonObject<CJsonOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>>;

	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseOrdered const &);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseOrdered const &&);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseOrdered &&);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSorted const &);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSorted const &&);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSorted &&);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSortedWithComments const &);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSortedWithComments const &&);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSortedWithComments &&);

	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &);
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> &&);
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &&);
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &);
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> &&);
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &&);
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSortedWithComments>
		(
			TCJsonValue<CJsonValueBaseSortedWithComments> const &
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSortedWithComments>
		(
			TCJsonValue<CJsonValueBaseSortedWithComments> &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSortedWithComments>
		(
			TCJsonValue<CJsonValueBaseSortedWithComments> const &&
		)
	;

	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> &&);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &&);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> &&);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &&);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedWithComments> const &);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedWithComments> &&);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedWithComments> const &&);

	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseOrdered const &);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseOrdered &);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseOrdered &&);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSorted const &);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSorted &);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSorted &&);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSortedWithComments const &);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSortedWithComments &);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSortedWithComments &&);

	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseOrderedYaml const &);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseOrderedYaml const &&);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseOrderedYaml &&);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSortedYaml const &);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSortedYaml const &&);
	extern template CJsonValueJsonOrderedWithComments::TCJsonValue(CJsonValueBaseSortedYaml &&);

	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> const &
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> const &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> const &
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedWithComments> CJsonOrderedWithComments::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> const &&
		)
	;

	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> const &);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> &&);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> const &&);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> const &);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> &&);
	extern template CJsonOrderedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> const &&);

	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseOrderedYaml const &);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseOrderedYaml &);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseOrderedYaml &&);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSortedYaml const &);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSortedYaml &);
	extern template CJsonValueBaseOrderedWithComments::TCJsonValueBase(CJsonValueBaseSortedYaml &&);

	extern template CJsonOrderedWithComments::TCJsonValue(CNullPtr &&);
	extern template CJsonOrderedWithComments::TCJsonValue(CNullPtr &);
	extern template CJsonOrderedWithComments::TCJsonValue(CNullPtr const &);

	extern template CJsonOrderedWithComments::TCJsonValue(NStr::CStr &&);
	extern template CJsonOrderedWithComments::TCJsonValue(NStr::CStr &);
	extern template CJsonOrderedWithComments::TCJsonValue(NStr::CStr const &);

	extern template CJsonOrderedWithComments::TCJsonValue(int64 &&);
	extern template CJsonOrderedWithComments::TCJsonValue(int64 &);
	extern template CJsonOrderedWithComments::TCJsonValue(int64 const &);

	extern template CJsonOrderedWithComments::TCJsonValue(int32 &&);
	extern template CJsonOrderedWithComments::TCJsonValue(int32 &);
	extern template CJsonOrderedWithComments::TCJsonValue(int32 const &);

	extern template CJsonOrderedWithComments::TCJsonValue(uint64 &&);
	extern template CJsonOrderedWithComments::TCJsonValue(uint64 &);
	extern template CJsonOrderedWithComments::TCJsonValue(uint64 const &);

	extern template CJsonOrderedWithComments::TCJsonValue(uint32 &&);
	extern template CJsonOrderedWithComments::TCJsonValue(uint32 &);
	extern template CJsonOrderedWithComments::TCJsonValue(uint32 const &);

	extern template CJsonOrderedWithComments::TCJsonValue(pfp64 &&);
	extern template CJsonOrderedWithComments::TCJsonValue(pfp64 &);
	extern template CJsonOrderedWithComments::TCJsonValue(pfp64 const &);

	extern template CJsonOrderedWithComments::TCJsonValue(pfp32 &&);
	extern template CJsonOrderedWithComments::TCJsonValue(pfp32 &);
	extern template CJsonOrderedWithComments::TCJsonValue(pfp32 const &);

	extern template CJsonOrderedWithComments::TCJsonValue(fp32 &&);
	extern template CJsonOrderedWithComments::TCJsonValue(fp32 &);
	extern template CJsonOrderedWithComments::TCJsonValue(fp32 const &);

	extern template CJsonOrderedWithComments::TCJsonValue(fp64 &&);
	extern template CJsonOrderedWithComments::TCJsonValue(fp64 &);
	extern template CJsonOrderedWithComments::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonOrderedWithComments::TCJsonValue(int &&);
	extern template CJsonOrderedWithComments::TCJsonValue(int &);
	extern template CJsonOrderedWithComments::TCJsonValue(int const &);
#endif
	extern template CJsonOrderedWithComments::TCJsonValue(bool &&);
	extern template CJsonOrderedWithComments::TCJsonValue(bool &);
	extern template CJsonOrderedWithComments::TCJsonValue(bool const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int64>(int64 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int64 &>(int64 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int64 const &>(int64 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int32>(int32 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int32 &>(int32 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int32 const &>(int32 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<uint64>(uint64 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<uint64 &>(uint64 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<uint64 const &>(uint64 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<uint32>(uint32 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<uint32 &>(uint32 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<uint32 const &>(uint32 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<pfp64>(pfp64 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<pfp64 &>(pfp64 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<pfp32>(pfp32 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<pfp32 &>(pfp32 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<fp32>(fp32 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<fp32 &>(fp32 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<fp32 const &>(fp32 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<fp64>(fp64 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<fp64 &>(fp64 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int>(int &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int &>(int &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<int const &>(int const &);
#endif
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<bool>(bool &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<bool &>(bool &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::f_Insert<bool const &>(bool const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <CNullPtr>(CNullPtr &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <CNullPtr &>(CNullPtr &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int64>(int64 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int64 &>(int64 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int64 const &>(int64 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int32>(int32 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int32 &>(int32 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int32 const &>(int32 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <uint64>(uint64 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <uint64 &>(uint64 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <uint64 const &>(uint64 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <uint32>(uint32 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <uint32 &>(uint32 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <uint32 const &>(uint32 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <pfp64>(pfp64 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <pfp64 &>(pfp64 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <pfp64 const &>(pfp64 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <pfp32>(pfp32 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <pfp32 &>(pfp32 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <pfp32 const &>(pfp32 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <fp32>(fp32 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <fp32 &>(fp32 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <fp32 const &>(fp32 const &);

	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <fp64>(fp64 &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <fp64 &>(fp64 &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int>(int &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int &>(int &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <int const &>(int const &);
#endif
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <bool>(bool &&);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <bool &>(bool &);
	extern template CJsonOrderedWithComments &CJsonOrderedWithComments::operator = <bool const &>(bool const &);

	extern template void CJsonOrderedWithComments::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonOrderedWithComments, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonOrderedWithComments, true>::CLocalOptions const &) const
	;
#endif
}
