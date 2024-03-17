// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON.h"
#include "Malterlib_Encoding_EJSON.h"

namespace NMib::NEncoding
{
	struct CJSONConstantsSorted
	{
		constexpr static auto mc_Null = EJSONType_Null;
		constexpr static auto mc_EmptyString = EJSONType_String;
		constexpr static auto mc_EmptyObject = EJSONType_Object;
		constexpr static auto mc_EmptyArray = EJSONType_Array;
		constexpr static auto mc_InvalidDate = EEJSONType_Date;
		constexpr static auto mc_EmptyBinary = EEJSONType_Binary;
		EJSONType operator [] (CJSONConstantsSorted const &) const
		{
			return EJSONType_Array;
		}
		CEJSONSorted::CKey operator () (NStr::CStr const &_Key) const;
#if 0 // Not yet supported on MSVC
		template <typename ...tfp_CValue>
		NContainer::TCVector<CEJSONSorted> operator [] (tfp_CValue && ... p_Values) const
		{
			NContainer::TCVector<CEJSONSorted> Return;
			((void)Return.f_Insert(fg_Forward<tfp_CValue>(p_Values)), ...);
			return Return;
		}
#endif
	};

	struct CJSONConstantsOrdered
	{
		constexpr static auto mc_Null = EJSONType_Null;
		constexpr static auto mc_EmptyString = EJSONType_String;
		constexpr static auto mc_EmptyObject = EJSONType_Object;
		constexpr static auto mc_EmptyArray = EJSONType_Array;
		constexpr static auto mc_InvalidDate = EEJSONType_Date;
		constexpr static auto mc_EmptyBinary = EEJSONType_Binary;
		EJSONType operator [] (CJSONConstantsOrdered const &) const
		{
			return EJSONType_Array;
		}
#if 0 // Not yet supported on MSVC
		template <typename ...tfp_CValue>
		NContainer::TCVector<CEJSONOrdered> operator [] (tfp_CValue && ... p_Values) const
		{
			NContainer::TCVector<CEJSONOrdered> Return;
			((void)Return.f_Insert(fg_Forward<tfp_CValue>(p_Values)), ...);
			return Return;
		}
#endif
		CEJSONOrdered::CKey operator () (NStr::CStr const &_Key) const;
	};
}

NMib::NEncoding::CEJSONOrdered::CKey operator ""_o (const char *_pStr, std::size_t _Len);
NMib::NEncoding::CJSONOrdered::CKey operator ""_jo (const char *_pStr, std::size_t _Len);

NMib::NEncoding::CEJSONSorted::CKey operator ""_ (const char *_pStr, std::size_t _Len);
NMib::NEncoding::CJSONSorted::CKey operator ""_j (const char *_pStr, std::size_t _Len);

extern NMib::NEncoding::CJSONConstantsOrdered const _o;
extern NMib::NEncoding::CJSONConstantsSorted const _;

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
