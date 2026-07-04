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
	template struct NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_PreserveComments>;
	template struct TCJsonValue<NPrivate::TCJsonValueBase<TCJsonValue, NPrivate::CJsonExtraTypes, EJsonContainerFlag::mc_PreserveComments>>;
	template struct TCJsonObject<CJsonSortedWithComments, EJsonContainerFlag::mc_PreserveComments>;
	template struct NPrivate::TCObjectEntry<CJsonSortedWithComments, EJsonContainerFlag::mc_PreserveComments>;

	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseSorted const &);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseSorted const &&);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseSorted &&);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrdered const &);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrdered const &&);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrdered &&);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrderedWithComments const &);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrderedWithComments const &&);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrderedWithComments &&);

	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &);
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> &&);
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseSorted>(TCJsonValue<CJsonValueBaseSorted> const &&);
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &);
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> &&);
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrdered>(TCJsonValue<CJsonValueBaseOrdered> const &&);
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrderedWithComments>
		(
			TCJsonValue<CJsonValueBaseOrderedWithComments> const &
		)
	;
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrderedWithComments>
		(
			TCJsonValue<CJsonValueBaseOrderedWithComments> &&
		)
	;
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrderedWithComments>
		(
			TCJsonValue<CJsonValueBaseOrderedWithComments> const &&
		)
	;

	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> &&);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSorted> const &&);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> &&);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrdered> const &&);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedWithComments> const &);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedWithComments> &&);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedWithComments> const &&);

	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseSorted const &);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseSorted &);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseSorted &&);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrdered const &);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrdered &);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrdered &&);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrderedWithComments const &);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrderedWithComments &);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrderedWithComments &&);

	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrderedYaml const &);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrderedYaml const &&);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseOrderedYaml &&);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseSortedYaml const &);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseSortedYaml const &&);
	template CJsonValueJsonSortedWithComments::TCJsonValue(CJsonValueBaseSortedYaml &&);

	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> const &
		)
	;
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> &&
		)
	;
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseOrderedYaml>
		(
			TCJsonValue<CJsonValueBaseOrderedYaml> const &&
		)
	;
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> const &
		)
	;
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> &&
		)
	;
	template TCJsonValue<CJsonValueBaseSortedWithComments> CJsonSortedWithComments::fs_FromCompatible<CJsonValueBaseSortedYaml>
		(
			TCJsonValue<CJsonValueBaseSortedYaml> const &&
		)
	;

	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> const &);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> &&);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseOrderedYaml> const &&);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> const &);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> &&);
	template CJsonSortedWithComments::TCJsonValue(TCJsonValue<CJsonValueBaseSortedYaml> const &&);

	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrderedYaml const &);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrderedYaml &);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseOrderedYaml &&);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseSortedYaml const &);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseSortedYaml &);
	template CJsonValueBaseSortedWithComments::TCJsonValueBase(CJsonValueBaseSortedYaml &&);

	template CJsonSortedWithComments::TCJsonValue(CNullPtr &&);
	template CJsonSortedWithComments::TCJsonValue(CNullPtr &);
	template CJsonSortedWithComments::TCJsonValue(CNullPtr const &);

	template CJsonSortedWithComments::TCJsonValue(NStr::CStr &&);
	template CJsonSortedWithComments::TCJsonValue(NStr::CStr &);
	template CJsonSortedWithComments::TCJsonValue(NStr::CStr const &);

	template CJsonSortedWithComments::TCJsonValue(int64 &&);
	template CJsonSortedWithComments::TCJsonValue(int64 &);
	template CJsonSortedWithComments::TCJsonValue(int64 const &);

	template CJsonSortedWithComments::TCJsonValue(int32 &&);
	template CJsonSortedWithComments::TCJsonValue(int32 &);
	template CJsonSortedWithComments::TCJsonValue(int32 const &);

	template CJsonSortedWithComments::TCJsonValue(uint64 &&);
	template CJsonSortedWithComments::TCJsonValue(uint64 &);
	template CJsonSortedWithComments::TCJsonValue(uint64 const &);

	template CJsonSortedWithComments::TCJsonValue(uint32 &&);
	template CJsonSortedWithComments::TCJsonValue(uint32 &);
	template CJsonSortedWithComments::TCJsonValue(uint32 const &);

	template CJsonSortedWithComments::TCJsonValue(pfp64 &&);
	template CJsonSortedWithComments::TCJsonValue(pfp64 &);
	template CJsonSortedWithComments::TCJsonValue(pfp64 const &);

	template CJsonSortedWithComments::TCJsonValue(pfp32 &&);
	template CJsonSortedWithComments::TCJsonValue(pfp32 &);
	template CJsonSortedWithComments::TCJsonValue(pfp32 const &);

	template CJsonSortedWithComments::TCJsonValue(fp32 &&);
	template CJsonSortedWithComments::TCJsonValue(fp32 &);
	template CJsonSortedWithComments::TCJsonValue(fp32 const &);

	template CJsonSortedWithComments::TCJsonValue(fp64 &&);
	template CJsonSortedWithComments::TCJsonValue(fp64 &);
	template CJsonSortedWithComments::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonSortedWithComments::TCJsonValue(int &&);
	template CJsonSortedWithComments::TCJsonValue(int &);
	template CJsonSortedWithComments::TCJsonValue(int const &);
#endif
	template CJsonSortedWithComments::TCJsonValue(bool &&);
	template CJsonSortedWithComments::TCJsonValue(bool &);
	template CJsonSortedWithComments::TCJsonValue(bool const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<CNullPtr>(CNullPtr &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<CNullPtr &>(CNullPtr &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int64>(int64 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int64 &>(int64 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int64 const &>(int64 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int32>(int32 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int32 &>(int32 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int32 const &>(int32 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<uint64>(uint64 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<uint64 &>(uint64 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<uint64 const &>(uint64 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<uint32>(uint32 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<uint32 &>(uint32 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<uint32 const &>(uint32 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<pfp64>(pfp64 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<pfp64 &>(pfp64 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<pfp64 const &>(pfp64 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<pfp32>(pfp32 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<pfp32 &>(pfp32 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<pfp32 const &>(pfp32 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<fp32>(fp32 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<fp32 &>(fp32 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<fp32 const &>(fp32 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<fp64>(fp64 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<fp64 &>(fp64 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int>(int &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int &>(int &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<int const &>(int const &);
#endif
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<bool>(bool &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<bool &>(bool &);
	template CJsonSortedWithComments &CJsonSortedWithComments::f_Insert<bool const &>(bool const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <CNullPtr>(CNullPtr &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <CNullPtr &>(CNullPtr &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <CNullPtr const &>(CNullPtr const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <NStr::CStr>(NStr::CStr &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <NStr::CStr &>(NStr::CStr &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int64>(int64 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int64 &>(int64 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int64 const &>(int64 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int32>(int32 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int32 &>(int32 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int32 const &>(int32 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <uint64>(uint64 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <uint64 &>(uint64 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <uint64 const &>(uint64 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <uint32>(uint32 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <uint32 &>(uint32 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <uint32 const &>(uint32 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <pfp64>(pfp64 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <pfp64 &>(pfp64 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <pfp64 const &>(pfp64 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <pfp32>(pfp32 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <pfp32 &>(pfp32 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <pfp32 const &>(pfp32 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <fp32>(fp32 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <fp32 &>(fp32 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <fp32 const &>(fp32 const &);

	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <fp64>(fp64 &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <fp64 &>(fp64 &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int>(int &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int &>(int &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <int const &>(int const &);
#endif
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <bool>(bool &&);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <bool &>(bool &);
	template CJsonSortedWithComments &CJsonSortedWithComments::operator = <bool const &>(bool const &);

	template void CJsonSortedWithComments::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSortedWithComments, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CJsonSortedWithComments, false>::CLocalOptions const &) const
	;
#endif
}
