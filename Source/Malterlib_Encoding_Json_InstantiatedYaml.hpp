// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	extern template struct NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;
	extern template struct TCJsonValue<NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;
	extern template struct TCJsonObject<CJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;
	extern template struct NPrivate::TCObjectEntry<CJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;

	extern template struct TCJsonObjectEntryHandle<TCJsonObject<CJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;
	extern template struct TCJsonOrderedDestructiveIterator<TCJsonObject<CJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;
	extern template struct TCJsonSortedDestructiveIterator<TCJsonObject<CJsonOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>>;

	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseOrdered const &);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseOrdered const &&);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseOrdered &&);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSorted const &);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSorted const &&);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSorted &&);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSortedYaml const &);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSortedYaml const &&);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSortedYaml &&);

	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &);
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> &&);
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &&);
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &);
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> &&);
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &&);
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> const &
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> const &&
		)
	;

	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> &&);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &&);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> &&);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &&);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> const &);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> &&);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> const &&);

	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseOrdered const &);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseOrdered &);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseOrdered &&);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSorted const &);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSorted &);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSorted &&);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSortedYaml const &);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSortedYaml &);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSortedYaml &&);

	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseOrderedWithComments const &);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseOrderedWithComments const &&);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseOrderedWithComments &&);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSortedWithComments const &);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSortedWithComments const &&);
	extern template CJsonValueJsonOrderedYaml::TCJsonValue(CJsonValueBaseSortedWithComments &&);

	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseOrderedWithComments>
		(
			TCJsonValue<CJsonValueBaseOrderedWithComments> const &
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseOrderedWithComments>
		(
			TCJsonValue<CJsonValueBaseOrderedWithComments> &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseOrderedWithComments>
		(
			TCJsonValue<CJsonValueBaseOrderedWithComments> const &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSortedWithComments>
		(
			TCJsonValue<CJsonValueBaseSortedWithComments> const &
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSortedWithComments>
		(
			TCJsonValue<CJsonValueBaseSortedWithComments> &&
		)
	;
	extern template TCJsonValue<CJsonValueBaseOrderedYaml> CJsonOrderedYaml::fs_FromCompatible<CJsonValueBaseSortedWithComments>
		(
			TCJsonValue<CJsonValueBaseSortedWithComments> const &&
		)
	;

	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedWithComments> const &);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedWithComments> &&);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedWithComments> const &&);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSortedWithComments> const &);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSortedWithComments> &&);
	extern template CJsonOrderedYaml::TCJsonValue(TCJsonValue<CJsonValueBaseSortedWithComments> const &&);

	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseOrderedWithComments const &);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseOrderedWithComments &);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseOrderedWithComments &&);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSortedWithComments const &);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSortedWithComments &);
	extern template CJsonValueBaseOrderedYaml::TCJsonValueBase(CJsonValueBaseSortedWithComments &&);

	extern template CJsonOrderedYaml::TCJsonValue(CNullPtr &&);
	extern template CJsonOrderedYaml::TCJsonValue(CNullPtr &);
	extern template CJsonOrderedYaml::TCJsonValue(CNullPtr const &);

	extern template CJsonOrderedYaml::TCJsonValue(NStr::CStr &&);
	extern template CJsonOrderedYaml::TCJsonValue(NStr::CStr &);
	extern template CJsonOrderedYaml::TCJsonValue(NStr::CStr const &);

	extern template CJsonOrderedYaml::TCJsonValue(int64 &&);
	extern template CJsonOrderedYaml::TCJsonValue(int64 &);
	extern template CJsonOrderedYaml::TCJsonValue(int64 const &);

	extern template CJsonOrderedYaml::TCJsonValue(int32 &&);
	extern template CJsonOrderedYaml::TCJsonValue(int32 &);
	extern template CJsonOrderedYaml::TCJsonValue(int32 const &);

	extern template CJsonOrderedYaml::TCJsonValue(uint64 &&);
	extern template CJsonOrderedYaml::TCJsonValue(uint64 &);
	extern template CJsonOrderedYaml::TCJsonValue(uint64 const &);

	extern template CJsonOrderedYaml::TCJsonValue(uint32 &&);
	extern template CJsonOrderedYaml::TCJsonValue(uint32 &);
	extern template CJsonOrderedYaml::TCJsonValue(uint32 const &);

	extern template CJsonOrderedYaml::TCJsonValue(pfp64 &&);
	extern template CJsonOrderedYaml::TCJsonValue(pfp64 &);
	extern template CJsonOrderedYaml::TCJsonValue(pfp64 const &);

	extern template CJsonOrderedYaml::TCJsonValue(pfp32 &&);
	extern template CJsonOrderedYaml::TCJsonValue(pfp32 &);
	extern template CJsonOrderedYaml::TCJsonValue(pfp32 const &);

	extern template CJsonOrderedYaml::TCJsonValue(fp32 &&);
	extern template CJsonOrderedYaml::TCJsonValue(fp32 &);
	extern template CJsonOrderedYaml::TCJsonValue(fp32 const &);

	extern template CJsonOrderedYaml::TCJsonValue(fp64 &&);
	extern template CJsonOrderedYaml::TCJsonValue(fp64 &);
	extern template CJsonOrderedYaml::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonOrderedYaml::TCJsonValue(int &&);
	extern template CJsonOrderedYaml::TCJsonValue(int &);
	extern template CJsonOrderedYaml::TCJsonValue(int const &);
#endif
	extern template CJsonOrderedYaml::TCJsonValue(bool &&);
	extern template CJsonOrderedYaml::TCJsonValue(bool &);
	extern template CJsonOrderedYaml::TCJsonValue(bool const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<CNullPtr>(CNullPtr &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<CNullPtr &>(CNullPtr &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<CNullPtr const &>(CNullPtr const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<NStr::CStr>(NStr::CStr &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<NStr::CStr &>(NStr::CStr &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int64>(int64 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int64 &>(int64 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int64 const &>(int64 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int32>(int32 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int32 &>(int32 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int32 const &>(int32 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<uint64>(uint64 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<uint64 &>(uint64 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<uint64 const &>(uint64 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<uint32>(uint32 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<uint32 &>(uint32 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<uint32 const &>(uint32 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<pfp64>(pfp64 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<pfp64 &>(pfp64 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<pfp64 const &>(pfp64 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<pfp32>(pfp32 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<pfp32 &>(pfp32 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<pfp32 const &>(pfp32 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<fp32>(fp32 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<fp32 &>(fp32 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<fp32 const &>(fp32 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<fp64>(fp64 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<fp64 &>(fp64 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int>(int &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int &>(int &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<int const &>(int const &);
#endif
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<bool>(bool &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<bool &>(bool &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::f_Insert<bool const &>(bool const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <CNullPtr>(CNullPtr &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <CNullPtr &>(CNullPtr &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <CNullPtr const &>(CNullPtr const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <NStr::CStr>(NStr::CStr &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <NStr::CStr &>(NStr::CStr &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <NStr::CStr const &>(NStr::CStr const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int64>(int64 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int64 &>(int64 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int64 const &>(int64 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int32>(int32 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int32 &>(int32 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int32 const &>(int32 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <uint64>(uint64 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <uint64 &>(uint64 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <uint64 const &>(uint64 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <uint32>(uint32 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <uint32 &>(uint32 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <uint32 const &>(uint32 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <pfp64>(pfp64 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <pfp64 &>(pfp64 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <pfp64 const &>(pfp64 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <pfp32>(pfp32 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <pfp32 &>(pfp32 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <pfp32 const &>(pfp32 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <fp32>(fp32 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <fp32 &>(fp32 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <fp32 const &>(fp32 const &);

	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <fp64>(fp64 &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <fp64 &>(fp64 &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int>(int &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int &>(int &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <int const &>(int const &);
#endif
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <bool>(bool &&);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <bool &>(bool &);
	extern template CJsonOrderedYaml &CJsonOrderedYaml::operator = <bool const &>(bool const &);

	extern template void CJsonOrderedYaml::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonOrderedYaml, true>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonOrderedYaml, true>::CLocalOptions const &) const
	;
#endif
}
