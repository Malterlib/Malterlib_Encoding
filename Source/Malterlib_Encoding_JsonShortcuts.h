// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"
#include "Malterlib_Encoding_EJson.h"

namespace NMib::NEncoding
{
	template <typename t_CJson>
	struct TCJsonConstants
	{
		static typename t_CJson::CKey operator () (NStr::CStr const &_Key);

		t_CJson const &operator = (t_CJson const &_Convert) const;
		t_CJson &&operator = (t_CJson &&_Convert) const;
		t_CJson operator = (std::initializer_list<CVoidTag> const &_Initializer) const;

		template <typename ...tfp_CValue>
		t_CJson operator [] (tfp_CValue && ...p_Values) const;

		static constexpr auto mc_Null = EJsonType_Null;
		static constexpr auto mc_EmptyString = EJsonType_String;
		static constexpr auto mc_EmptyObject = EJsonType_Object;
		static constexpr auto mc_EmptyArray = EJsonType_Array;
		static constexpr auto mc_InvalidDate = EEJsonType_Date;
		static constexpr auto mc_EmptyBinary = EEJsonType_Binary;
	};

	extern template CEJsonOrdered::CKey TCJsonConstants<CEJsonOrdered>::operator () (NStr::CStr const &_Key);
	extern template CEJsonSorted::CKey TCJsonConstants<CEJsonSorted>::operator () (NStr::CStr const &_Key);
	extern template CJsonOrdered::CKey TCJsonConstants<CJsonOrdered>::operator () (NStr::CStr const &_Key);
	extern template CJsonSorted::CKey TCJsonConstants<CJsonSorted>::operator () (NStr::CStr const &_Key);
}

NMib::NEncoding::CEJsonOrdered::CKey operator ""_o (char const *_pStr, std::size_t _Len);
NMib::NEncoding::CJsonOrdered::CKey operator ""_jo (char const *_pStr, std::size_t _Len);

NMib::NEncoding::CEJsonSorted::CKey operator ""_ (char const *_pStr, std::size_t _Len);
NMib::NEncoding::CJsonSorted::CKey operator ""_j (char const *_pStr, std::size_t _Len);

// NOLINTBEGIN(malterlib-variable-naming): JSON shorthand syntax, named like the ""_o, ""_, ""_jo and ""_j literal operators
constexpr NMib::NEncoding::TCJsonConstants<NMib::NEncoding::CEJsonOrdered> _o;
constexpr NMib::NEncoding::TCJsonConstants<NMib::NEncoding::CEJsonSorted> _;

constexpr NMib::NEncoding::TCJsonConstants<NMib::NEncoding::CJsonOrdered> _jo;
constexpr NMib::NEncoding::TCJsonConstants<NMib::NEncoding::CJsonSorted> _j;
// NOLINTEND(malterlib-variable-naming)

#ifndef DMibPNoShortCuts
using namespace NMib::NEncoding;
#endif

#include "Malterlib_Encoding_JsonShortcuts.hpp"
