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
		CEJSONSorted::CKey operator [] (NStr::CStr const &_Key);
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
		CEJSONOrdered::CKey operator [] (NStr::CStr const &_Key);
	};
}

NMib::NEncoding::CEJSONOrdered::CKey operator ""_o (const char *_pStr, std::size_t _Len);
NMib::NEncoding::CJSONOrdered::CKey operator ""__o (const char *_pStr, std::size_t _Len);

NMib::NEncoding::CEJSONSorted::CKey operator ""_ (const char *_pStr, std::size_t _Len);
NMib::NEncoding::CJSONSorted::CKey operator ""__ (const char *_pStr, std::size_t _Len);

extern NMib::NEncoding::CJSONConstantsOrdered _o;
extern NMib::NEncoding::CJSONConstantsSorted _;

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
