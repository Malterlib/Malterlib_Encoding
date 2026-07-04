// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	extern template struct NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_PreserveComments>;
	extern template struct TCJsonValue<NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_PreserveComments>>;
	extern template struct TCJsonObject<CJsonSortedWithComments, EJsonContainerFlag::mc_PreserveComments>;
	extern template struct NPrivate::TCObjectEntry<CJsonSortedWithComments, EJsonContainerFlag::mc_PreserveComments>;

	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseSorted const &);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseSorted const &&);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseSorted &&);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrdered const &);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrdered const &&);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrdered &&);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrderedWithComments const &);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrderedWithComments const &&);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrderedWithComments &&);

	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &);
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> &&);
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &&);
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &);
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> &&);
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &&);
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrderedWithComments>
		(
			TCJsonValue<CJsonValueBaseOrderedWithComments> const &
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrderedWithComments>
		(
			TCJsonValue<CJsonValueBaseOrderedWithComments> &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrderedWithComments>
		(
			TCJsonValue<CJsonValueBaseOrderedWithComments> const &&
		)
	;

	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> &&);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &&);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> &&);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &&);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedWithComments> const &);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedWithComments> &&);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedWithComments> const &&);

	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseSorted const &);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseSorted &);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseSorted &&);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrdered const &);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrdered &);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrdered &&);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrderedWithComments const &);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrderedWithComments &);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrderedWithComments &&);

	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrderedYaml const &);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrderedYaml const &&);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrderedYaml &&);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseSortedYaml const &);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseSortedYaml const &&);
	extern template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseSortedYaml &&);

	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> const &
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> const &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> const &
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> const &&
		)
	;

	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> const &);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> &&);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> const &&);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> const &);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> &&);
	extern template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> const &&);

	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrderedYaml const &);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrderedYaml &);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrderedYaml &&);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseSortedYaml const &);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseSortedYaml &);
	extern template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseSortedYaml &&);

	extern template CJsonSortedWithComments::TCJsonValue(CNullPtr &&);
	extern template CJsonSortedWithComments::TCJsonValue(CNullPtr &);
	extern template CJsonSortedWithComments::TCJsonValue(CNullPtr const &);

	extern template CJsonSortedWithComments::TCJsonValue(NStr::CStr &&);
	extern template CJsonSortedWithComments::TCJsonValue(NStr::CStr &);
	extern template CJsonSortedWithComments::TCJsonValue(NStr::CStr const &);

	extern template CJsonSortedWithComments::TCJsonValue(int64 &&);
	extern template CJsonSortedWithComments::TCJsonValue(int64 &);
	extern template CJsonSortedWithComments::TCJsonValue(int64 const &);

	extern template CJsonSortedWithComments::TCJsonValue(int32 &&);
	extern template CJsonSortedWithComments::TCJsonValue(int32 &);
	extern template CJsonSortedWithComments::TCJsonValue(int32 const &);

	extern template CJsonSortedWithComments::TCJsonValue(uint64 &&);
	extern template CJsonSortedWithComments::TCJsonValue(uint64 &);
	extern template CJsonSortedWithComments::TCJsonValue(uint64 const &);

	extern template CJsonSortedWithComments::TCJsonValue(uint32 &&);
	extern template CJsonSortedWithComments::TCJsonValue(uint32 &);
	extern template CJsonSortedWithComments::TCJsonValue(uint32 const &);

	extern template CJsonSortedWithComments::TCJsonValue(pfp64 &&);
	extern template CJsonSortedWithComments::TCJsonValue(pfp64 &);
	extern template CJsonSortedWithComments::TCJsonValue(pfp64 const &);

	extern template CJsonSortedWithComments::TCJsonValue(pfp32 &&);
	extern template CJsonSortedWithComments::TCJsonValue(pfp32 &);
	extern template CJsonSortedWithComments::TCJsonValue(pfp32 const &);

	extern template CJsonSortedWithComments::TCJsonValue(fp32 &&);
	extern template CJsonSortedWithComments::TCJsonValue(fp32 &);
	extern template CJsonSortedWithComments::TCJsonValue(fp32 const &);

	extern template CJsonSortedWithComments::TCJsonValue(fp64 &&);
	extern template CJsonSortedWithComments::TCJsonValue(fp64 &);
	extern template CJsonSortedWithComments::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonSortedWithComments::TCJsonValue(int &&);
	extern template CJsonSortedWithComments::TCJsonValue(int &);
	extern template CJsonSortedWithComments::TCJsonValue(int const &);
#endif
	extern template CJsonSortedWithComments::TCJsonValue(bool &&);
	extern template CJsonSortedWithComments::TCJsonValue(bool &);
	extern template CJsonSortedWithComments::TCJsonValue(bool const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int64>(int64 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int64 &>(int64 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int64 const &>(int64 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int32>(int32 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int32 &>(int32 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int32 const &>(int32 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<uint64>(uint64 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<uint64 &>(uint64 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<uint64 const &>(uint64 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<uint32>(uint32 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<uint32 &>(uint32 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<uint32 const &>(uint32 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<pfp64>(pfp64 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<pfp64 &>(pfp64 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<pfp32>(pfp32 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<pfp32 &>(pfp32 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<fp32>(fp32 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<fp32 &>(fp32 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<fp32 const &>(fp32 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<fp64>(fp64 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<fp64 &>(fp64 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int>(int &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int &>(int &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int const &>(int const &);
#endif
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<bool>(bool &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<bool &>(bool &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<bool const &>(bool const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <CNullPtr>(CNullPtr &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <CNullPtr &>(CNullPtr &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int64>(int64 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int64 &>(int64 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int64 const &>(int64 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int32>(int32 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int32 &>(int32 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int32 const &>(int32 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <uint64>(uint64 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <uint64 &>(uint64 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <uint64 const &>(uint64 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <uint32>(uint32 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <uint32 &>(uint32 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <uint32 const &>(uint32 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <pfp64>(pfp64 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <pfp64 &>(pfp64 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <pfp64 const &>(pfp64 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <pfp32>(pfp32 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <pfp32 &>(pfp32 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <pfp32 const &>(pfp32 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <fp32>(fp32 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <fp32 &>(fp32 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <fp32 const &>(fp32 const &);

	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <fp64>(fp64 &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <fp64 &>(fp64 &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int>(int &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int &>(int &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int const &>(int const &);
#endif
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <bool>(bool &&);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <bool &>(bool &);
	extern template CJsonSortedWithComments &CJsonSortedWithComments::operator = <bool const &>(bool const &);

	extern template void CJsonSortedWithComments::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSortedWithComments, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSortedWithComments, false>::CLocalOptions const &) const
	;
#endif
}
