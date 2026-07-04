// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Encoding_EJson.h"
#include "Malterlib_Encoding_Yaml.h"
#include "Malterlib_Encoding_EJson.hpp"
#include "Malterlib_Encoding_EJson_Generate.h"
#include "Malterlib_Encoding_EJson_Parse.h"

namespace NMib::NEncoding
{
#ifdef DMibEncodingJsonExternTemplate
	template struct NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesSortedWithComments, EJsonContainerFlag::mc_PreserveComments>;
	template struct TCJsonValue<CEJsonValueBaseSortedWithComments>;
	template struct TCEJsonValue<CEJsonValueBaseSortedWithComments>;
	template struct TCJsonObject<CEJsonSortedWithComments, EJsonContainerFlag::mc_PreserveComments>;
	template struct NPrivate::TCObjectEntry<CEJsonSortedWithComments, EJsonContainerFlag::mc_PreserveComments>;

	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrdered const &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrdered const &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrdered &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrderedWithComments const &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrderedWithComments const &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrderedWithComments &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseSorted const &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseSorted const &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseSorted &&);

	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrdered>(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrderedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &
		)
	;
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrderedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseOrderedWithComments> &&
		)
	;
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrderedWithComments>
		(
			TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &&
		)
	;
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &);
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> &&);
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseSorted>(TCEJsonValue<CEJsonValueBaseSorted> const &&);

	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> &&);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrdered> const &&);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedWithComments> &&);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedWithComments> const &&);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> &&);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSorted> const &&);

	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrdered const &);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrdered &);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrdered &&);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrderedWithComments const &);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrderedWithComments &);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrderedWithComments &&);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseSorted const &);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseSorted &);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseSorted &&);

	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrderedYaml const &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrderedYaml const &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseOrderedYaml &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseSortedYaml const &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseSortedYaml const &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CEJsonValueBaseSortedYaml &&);

	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrderedYaml>
		(
			TCEJsonValue<CEJsonValueBaseOrderedYaml> const &
		)
	;
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrderedYaml>
		(
			TCEJsonValue<CEJsonValueBaseOrderedYaml> &&
		)
	;
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseOrderedYaml>
		(
			TCEJsonValue<CEJsonValueBaseOrderedYaml> const &&
		)
	;
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseSortedYaml>
		(
			TCEJsonValue<CEJsonValueBaseSortedYaml> const &
		)
	;
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseSortedYaml>
		(
			TCEJsonValue<CEJsonValueBaseSortedYaml> &&
		)
	;
	template TCEJsonValue<CEJsonValueBaseSortedWithComments> CEJsonSortedWithComments::fs_FromCompatible<CEJsonValueBaseSortedYaml>
		(
			TCEJsonValue<CEJsonValueBaseSortedYaml> const &&
		)
	;

	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedYaml> const &);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedYaml> &&);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseOrderedYaml> const &&);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedYaml> const &);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedYaml> &&);
	template CEJsonSortedWithComments::TCEJsonValue(TCEJsonValue<CEJsonValueBaseSortedYaml> const &&);

	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrderedYaml const &);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrderedYaml &);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseOrderedYaml &&);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseSortedYaml const &);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseSortedYaml &);
	template CEJsonValueBaseSortedWithComments::TCJsonValueBase(CEJsonValueBaseSortedYaml &&);

	template CJsonValueEJsonSortedWithComments::TCJsonValue(CNullPtr &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CNullPtr &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(CNullPtr const &);

	template CJsonValueEJsonSortedWithComments::TCJsonValue(NStr::CStr &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(NStr::CStr &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(NStr::CStr const &);

	template CJsonValueEJsonSortedWithComments::TCJsonValue(int64 &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(int64 &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(int64 const &);

	template CJsonValueEJsonSortedWithComments::TCJsonValue(int32 &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(int32 &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(int32 const &);

	template CJsonValueEJsonSortedWithComments::TCJsonValue(uint64 &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(uint64 &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(uint64 const &);

	template CJsonValueEJsonSortedWithComments::TCJsonValue(uint32 &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(uint32 &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(uint32 const &);

	template CJsonValueEJsonSortedWithComments::TCJsonValue(pfp64 &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(pfp64 &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(pfp64 const &);

	template CJsonValueEJsonSortedWithComments::TCJsonValue(pfp32 &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(pfp32 &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(pfp32 const &);

	template CJsonValueEJsonSortedWithComments::TCJsonValue(fp32 &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(fp32 &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(fp32 const &);

	template CJsonValueEJsonSortedWithComments::TCJsonValue(fp64 &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(fp64 &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CJsonValueEJsonSortedWithComments::TCJsonValue(int &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(int &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(int const &);
#endif
	template CJsonValueEJsonSortedWithComments::TCJsonValue(bool &&);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(bool &);
	template CJsonValueEJsonSortedWithComments::TCJsonValue(bool const &);

	template CEJsonSortedWithComments::TCEJsonValue(EJsonType &&);
	template CEJsonSortedWithComments::TCEJsonValue(EJsonType &);
	template CEJsonSortedWithComments::TCEJsonValue(EJsonType const &);

	template CEJsonSortedWithComments::TCEJsonValue(ch8 const *&&);
	template CEJsonSortedWithComments::TCEJsonValue(ch8 const *&);
	template CEJsonSortedWithComments::TCEJsonValue(ch8 const *const &);

	template CEJsonSortedWithComments::TCEJsonValue(CNullPtr &&);
	template CEJsonSortedWithComments::TCEJsonValue(CNullPtr &);
	template CEJsonSortedWithComments::TCEJsonValue(CNullPtr const &);

	template CEJsonSortedWithComments::TCEJsonValue(NStr::CStr &&);
	template CEJsonSortedWithComments::TCEJsonValue(NStr::CStr &);
	template CEJsonSortedWithComments::TCEJsonValue(NStr::CStr const &);

	template CEJsonSortedWithComments::TCEJsonValue(int64 &&);
	template CEJsonSortedWithComments::TCEJsonValue(int64 &);
	template CEJsonSortedWithComments::TCEJsonValue(int64 const &);

	template CEJsonSortedWithComments::TCEJsonValue(int32 &&);
	template CEJsonSortedWithComments::TCEJsonValue(int32 &);
	template CEJsonSortedWithComments::TCEJsonValue(int32 const &);

	template CEJsonSortedWithComments::TCEJsonValue(uint64 &&);
	template CEJsonSortedWithComments::TCEJsonValue(uint64 &);
	template CEJsonSortedWithComments::TCEJsonValue(uint64 const &);

	template CEJsonSortedWithComments::TCEJsonValue(uint32 &&);
	template CEJsonSortedWithComments::TCEJsonValue(uint32 &);
	template CEJsonSortedWithComments::TCEJsonValue(uint32 const &);

	template CEJsonSortedWithComments::TCEJsonValue(pfp64 &&);
	template CEJsonSortedWithComments::TCEJsonValue(pfp64 &);
	template CEJsonSortedWithComments::TCEJsonValue(pfp64 const &);

	template CEJsonSortedWithComments::TCEJsonValue(pfp32 &&);
	template CEJsonSortedWithComments::TCEJsonValue(pfp32 &);
	template CEJsonSortedWithComments::TCEJsonValue(pfp32 const &);

	template CEJsonSortedWithComments::TCEJsonValue(fp32 &&);
	template CEJsonSortedWithComments::TCEJsonValue(fp32 &);
	template CEJsonSortedWithComments::TCEJsonValue(fp32 const &);

	template CEJsonSortedWithComments::TCEJsonValue(fp64 &&);
	template CEJsonSortedWithComments::TCEJsonValue(fp64 &);
	template CEJsonSortedWithComments::TCEJsonValue(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonSortedWithComments::TCEJsonValue(int &&);
	template CEJsonSortedWithComments::TCEJsonValue(int &);
	template CEJsonSortedWithComments::TCEJsonValue(int const &);
#endif
	template CEJsonSortedWithComments::TCEJsonValue(bool &&);
	template CEJsonSortedWithComments::TCEJsonValue(bool &);
	template CEJsonSortedWithComments::TCEJsonValue(bool const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<CNullPtr>(CNullPtr &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<CNullPtr &>(CNullPtr &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<CNullPtr const &>(CNullPtr const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<NStr::CStr>(NStr::CStr &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<NStr::CStr &>(NStr::CStr &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<NStr::CStr const &>(NStr::CStr const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int64>(int64 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int64 &>(int64 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int64 const &>(int64 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int32>(int32 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int32 &>(int32 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int32 const &>(int32 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<uint64>(uint64 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<uint64 &>(uint64 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<uint64 const &>(uint64 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<uint32>(uint32 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<uint32 &>(uint32 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<uint32 const &>(uint32 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<pfp64>(pfp64 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<pfp64 &>(pfp64 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<pfp64 const &>(pfp64 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<pfp32>(pfp32 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<pfp32 &>(pfp32 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<pfp32 const &>(pfp32 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<fp32>(fp32 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<fp32 &>(fp32 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<fp32 const &>(fp32 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<fp64>(fp64 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<fp64 &>(fp64 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int>(int &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int &>(int &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<int const &>(int const &);
#endif
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<bool>(bool &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<bool &>(bool &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::f_Insert<bool const &>(bool const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <NMib::NEncoding::EJsonType>(NMib::NEncoding::EJsonType &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <NMib::NEncoding::EJsonType &>(NMib::NEncoding::EJsonType &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <NMib::NEncoding::EJsonType const &>(NMib::NEncoding::EJsonType const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <CNullPtr>(CNullPtr &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <CNullPtr &>(CNullPtr &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <CNullPtr const &>(CNullPtr const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <NStr::CStr>(NStr::CStr &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <NStr::CStr &>(NStr::CStr &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <NStr::CStr const &>(NStr::CStr const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int64>(int64 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int64 &>(int64 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int64 const &>(int64 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int32>(int32 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int32 &>(int32 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int32 const &>(int32 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <uint64>(uint64 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <uint64 &>(uint64 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <uint64 const &>(uint64 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <uint32>(uint32 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <uint32 &>(uint32 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <uint32 const &>(uint32 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <pfp64>(pfp64 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <pfp64 &>(pfp64 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <pfp64 const &>(pfp64 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <pfp32>(pfp32 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <pfp32 &>(pfp32 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <pfp32 const &>(pfp32 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <fp32>(fp32 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <fp32 &>(fp32 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <fp32 const &>(fp32 const &);

	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <fp64>(fp64 &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <fp64 &>(fp64 &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <fp64 const &>(fp64 const &);

#ifdef DMibPUniqueType_int
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int>(int &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int &>(int &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <int const &>(int const &);
#endif
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <bool>(bool &&);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <bool &>(bool &);
	template CEJsonSortedWithComments &CJsonValueEJsonSortedWithComments::operator = <bool const &>(bool const &);

	template void CJsonValueEJsonSortedWithComments::f_Format
		<NStr::CStr, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonSortedWithComments, false>::CLocalOptions>
		(NStr::CStr &, NMib::NStr::TCStrFormatType_Inline<NMib::NStr::TCFormat<NMib::NStr::CStrTraits_CStr>, CEJsonSortedWithComments, false>::CLocalOptions const &) const
	;
#endif
}
