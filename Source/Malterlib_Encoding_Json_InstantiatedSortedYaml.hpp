// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	extern template struct NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_PreserveYamlMetadata>;
	extern template struct TCJsonValue<NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_PreserveYamlMetadata>>;
	extern template struct TCJsonObject<CJsonSortedYaml, EJsonContainerFlag::mc_PreserveYamlMetadata>;
	extern template struct NPrivate::TCObjectEntry<CJsonSortedYaml, EJsonContainerFlag::mc_PreserveYamlMetadata>;

	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseSorted const &);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseSorted const &&);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseSorted &&);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrdered const &);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrdered const &&);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrdered &&);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrderedYaml const &);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrderedYaml const &&);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrderedYaml &&);

	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &);
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> &&);
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &&);
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &);
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> &&);
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &&);
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> const &
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> const &&
		)
	;

	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> &&);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &&);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> &&);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &&);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> const &);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> &&);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> const &&);

	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseSorted const &);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseSorted &);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseSorted &&);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrdered const &);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrdered &);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrdered &&);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrderedYaml const &);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrderedYaml &);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrderedYaml &&);

	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrderedWithComments const &);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrderedWithComments const &&);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseOrderedWithComments &&);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseSortedWithComments const &);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseSortedWithComments const &&);
	extern template CJsonValueJsonSortedYaml::TCJsonValue(CJsonValueBaseSortedWithComments &&);

	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrderedWithComments>
		(
			TCJsonValue<CJsonValueBaseOrderedWithComments> const &
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrderedWithComments>
		(
			TCJsonValue<CJsonValueBaseOrderedWithComments> &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseOrderedWithComments>
		(
			TCJsonValue<CJsonValueBaseOrderedWithComments> const &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseSortedWithComments>
		(
			TCJsonValue<CJsonValueBaseSortedWithComments> const &
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseSortedWithComments>
		(
			TCJsonValue<CJsonValueBaseSortedWithComments> &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseSortedYaml> CJsonSortedYaml::fs_FromCompatible<CJsonValueBaseSortedWithComments>
		(
			TCJsonValue<CJsonValueBaseSortedWithComments> const &&
		)
	;

	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedWithComments> const &);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedWithComments> &&);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedWithComments> const &&);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSortedWithComments> const &);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSortedWithComments> &&);
	extern template CJsonSortedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSortedWithComments> const &&);

	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrderedWithComments const &);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrderedWithComments &);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseOrderedWithComments &&);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseSortedWithComments const &);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseSortedWithComments &);
	extern template CJsonValueBaseSortedYaml::TCJsonValueBase(CJsonValueBaseSortedWithComments &&);

	extern template CJsonSortedYaml::TCJsonValue(CNullPtr &&);
	extern template CJsonSortedYaml::TCJsonValue(CNullPtr &);
	extern template CJsonSortedYaml::TCJsonValue(CNullPtr const &);

	extern template CJsonSortedYaml::TCJsonValue(NStr::CStr &&);
	extern template CJsonSortedYaml::TCJsonValue(NStr::CStr &);
	extern template CJsonSortedYaml::TCJsonValue(NStr::CStr const &);

	extern template CJsonSortedYaml::TCJsonValue(int64 &&);
	extern template CJsonSortedYaml::TCJsonValue(int64 &);
	extern template CJsonSortedYaml::TCJsonValue(int64 const &);

	extern template CJsonSortedYaml::TCJsonValue(int32 &&);
	extern template CJsonSortedYaml::TCJsonValue(int32 &);
	extern template CJsonSortedYaml::TCJsonValue(int32 const &);

	extern template CJsonSortedYaml::TCJsonValue(uint64 &&);
	extern template CJsonSortedYaml::TCJsonValue(uint64 &);
	extern template CJsonSortedYaml::TCJsonValue(uint64 const &);

	extern template CJsonSortedYaml::TCJsonValue(uint32 &&);
	extern template CJsonSortedYaml::TCJsonValue(uint32 &);
	extern template CJsonSortedYaml::TCJsonValue(uint32 const &);

	extern template CJsonSortedYaml::TCJsonValue(pfp64 &&);
	extern template CJsonSortedYaml::TCJsonValue(pfp64 &);
	extern template CJsonSortedYaml::TCJsonValue(pfp64 const &);

	extern template CJsonSortedYaml::TCJsonValue(pfp32 &&);
	extern template CJsonSortedYaml::TCJsonValue(pfp32 &);
	extern template CJsonSortedYaml::TCJsonValue(pfp32 const &);

	extern template CJsonSortedYaml::TCJsonValue(fp32 &&);
	extern template CJsonSortedYaml::TCJsonValue(fp32 &);
	extern template CJsonSortedYaml::TCJsonValue(fp32 const &);

	extern template CJsonSortedYaml::TCJsonValue(fp64 &&);
	extern template CJsonSortedYaml::TCJsonValue(fp64 &);
	extern template CJsonSortedYaml::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonSortedYaml::TCJsonValue(int &&);
	extern template CJsonSortedYaml::TCJsonValue(int &);
	extern template CJsonSortedYaml::TCJsonValue(int const &);
#endif
	extern template CJsonSortedYaml::TCJsonValue(bool &&);
	extern template CJsonSortedYaml::TCJsonValue(bool &);
	extern template CJsonSortedYaml::TCJsonValue(bool const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int64>(int64 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int64 &>(int64 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int64 const &>(int64 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int32>(int32 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int32 &>(int32 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int32 const &>(int32 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<uint64>(uint64 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<uint64 &>(uint64 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<uint64 const &>(uint64 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<uint32>(uint32 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<uint32 &>(uint32 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<uint32 const &>(uint32 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<pfp64>(pfp64 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<pfp64 &>(pfp64 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<pfp32>(pfp32 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<pfp32 &>(pfp32 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<fp32>(fp32 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<fp32 &>(fp32 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<fp32 const &>(fp32 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<fp64>(fp64 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<fp64 &>(fp64 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int>(int &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int &>(int &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<int const &>(int const &);
#endif
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<bool>(bool &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<bool &>(bool &);
	extern template CJsonSortedYaml &CJsonSortedYaml::f_Insert<bool const &>(bool const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <CNullPtr>(CNullPtr &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <CNullPtr &>(CNullPtr &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <int64>(int64 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <int64 &>(int64 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <int64 const &>(int64 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <int32>(int32 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <int32 &>(int32 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <int32 const &>(int32 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <uint64>(uint64 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <uint64 &>(uint64 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <uint64 const &>(uint64 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <uint32>(uint32 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <uint32 &>(uint32 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <uint32 const &>(uint32 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <pfp64>(pfp64 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <pfp64 &>(pfp64 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <pfp64 const &>(pfp64 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <pfp32>(pfp32 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <pfp32 &>(pfp32 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <pfp32 const &>(pfp32 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <fp32>(fp32 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <fp32 &>(fp32 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <fp32 const &>(fp32 const &);

	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <fp64>(fp64 &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <fp64 &>(fp64 &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <int>(int &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <int &>(int &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <int const &>(int const &);
#endif
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <bool>(bool &&);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <bool &>(bool &);
	extern template CJsonSortedYaml &CJsonSortedYaml::operator = <bool const &>(bool const &);

	extern template void CJsonSortedYaml::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSortedYaml, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSortedYaml, false>::CLocalOptions const &) const
	;
#endif
}
