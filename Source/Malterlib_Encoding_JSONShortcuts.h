// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON.h"
#include "Malterlib_Encoding_EJSON.h"

namespace NMib::NEncoding
{
	template <typename tf_CJson>
	struct TCJSONConstants
	{
		constexpr static auto mc_Null = EJSONType_Null;
		constexpr static auto mc_EmptyString = EJSONType_String;
		constexpr static auto mc_EmptyObject = EJSONType_Object;
		constexpr static auto mc_EmptyArray = EJSONType_Array;
		constexpr static auto mc_InvalidDate = EEJSONType_Date;
		constexpr static auto mc_EmptyBinary = EEJSONType_Binary;

		typename tf_CJson::CKey operator () (NStr::CStr const &_Key) const;

		tf_CJson operator = (tf_CJson _Convert) const
		{
			return _Convert;
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

	extern template CEJSONOrdered::CKey TCJSONConstants<CEJSONOrdered>::operator () (NStr::CStr const &_Key) const;
	extern template CEJSONSorted::CKey TCJSONConstants<CEJSONSorted>::operator () (NStr::CStr const &_Key) const;
	extern template CJSONOrdered::CKey TCJSONConstants<CJSONOrdered>::operator () (NStr::CStr const &_Key) const;
	extern template CJSONSorted::CKey TCJSONConstants<CJSONSorted>::operator () (NStr::CStr const &_Key) const;
}

NMib::NEncoding::CEJSONOrdered::CKey operator ""_o (const char *_pStr, std::size_t _Len);
NMib::NEncoding::CJSONOrdered::CKey operator ""_jo (const char *_pStr, std::size_t _Len);

NMib::NEncoding::CEJSONSorted::CKey operator ""_ (const char *_pStr, std::size_t _Len);
NMib::NEncoding::CJSONSorted::CKey operator ""_j (const char *_pStr, std::size_t _Len);

extern NMib::NEncoding::TCJSONConstants<NMib::NEncoding::CEJSONOrdered> const _o;
extern NMib::NEncoding::TCJSONConstants<NMib::NEncoding::CEJSONSorted> const _;

extern NMib::NEncoding::TCJSONConstants<NMib::NEncoding::CJSONOrdered> const _jo;
extern NMib::NEncoding::TCJSONConstants<NMib::NEncoding::CJSONSorted> const _j;

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
