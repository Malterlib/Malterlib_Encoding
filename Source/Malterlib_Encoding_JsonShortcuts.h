// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_Json.h"
#include "Malterlib_Encoding_EJson.h"

namespace NMib::NEncoding
{
	template <typename tf_CJson>
	struct TCJsonConstants
	{
		constexpr static auto mc_Null = EJsonType_Null;
		constexpr static auto mc_EmptyString = EJsonType_String;
		constexpr static auto mc_EmptyObject = EJsonType_Object;
		constexpr static auto mc_EmptyArray = EJsonType_Array;
		constexpr static auto mc_InvalidDate = EEJsonType_Date;
		constexpr static auto mc_EmptyBinary = EEJsonType_Binary;

		typename tf_CJson::CKey operator () (NStr::CStr const &_Key) const;

		tf_CJson const &operator = (tf_CJson const &_Convert) const
		{
			return _Convert;
		}

		tf_CJson &&operator = (tf_CJson &&_Convert) const
		{
			return fg_Move(_Convert);
		}

		tf_CJson operator = (std::initializer_list<CVoidTag> const &_Initializer) const
		{
			return EJsonType_Object;
		}

		template <typename ...tfp_CValue>
		tf_CJson operator [] (tfp_CValue && ... p_Values) const
		{
			tf_CJson Return;

			auto &ReturnArray = Return.f_Array();
			((void)ReturnArray.f_Insert(fg_Forward<tfp_CValue>(p_Values)), ...);

			return Return;
		}
	};

	extern template CEJsonOrdered::CKey TCJsonConstants<CEJsonOrdered>::operator () (NStr::CStr const &_Key) const;
	extern template CEJsonSorted::CKey TCJsonConstants<CEJsonSorted>::operator () (NStr::CStr const &_Key) const;
	extern template CJsonOrdered::CKey TCJsonConstants<CJsonOrdered>::operator () (NStr::CStr const &_Key) const;
	extern template CJsonSorted::CKey TCJsonConstants<CJsonSorted>::operator () (NStr::CStr const &_Key) const;
}

NMib::NEncoding::CEJsonOrdered::CKey operator ""_o (const char *_pStr, std::size_t _Len);
NMib::NEncoding::CJsonOrdered::CKey operator ""_jo (const char *_pStr, std::size_t _Len);

NMib::NEncoding::CEJsonSorted::CKey operator ""_ (const char *_pStr, std::size_t _Len);
NMib::NEncoding::CJsonSorted::CKey operator ""_j (const char *_pStr, std::size_t _Len);

extern NMib::NEncoding::TCJsonConstants<NMib::NEncoding::CEJsonOrdered> const _o;
extern NMib::NEncoding::TCJsonConstants<NMib::NEncoding::CEJsonSorted> const _;

extern NMib::NEncoding::TCJsonConstants<NMib::NEncoding::CJsonOrdered> const _jo;
extern NMib::NEncoding::TCJsonConstants<NMib::NEncoding::CJsonSorted> const _j;

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
