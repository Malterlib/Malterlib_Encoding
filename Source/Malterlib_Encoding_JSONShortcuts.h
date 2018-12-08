#pragma once

#include "Malterlib_Encoding_JSON.h"
#include "Malterlib_Encoding_EJSON.h"

namespace NMib::NEncoding
{
	struct CJSONConstants
	{
		constexpr static auto mc_Null = EJSONType_Null;
		constexpr static auto mc_EmptyString = EJSONType_String;
		constexpr static auto mc_EmptyObject = EJSONType_Object;
		constexpr static auto mc_EmptyArray = EJSONType_Array;
		constexpr static auto mc_InvalidDate = EEJSONType_Date;
		constexpr static auto mc_EmptyBinary = EEJSONType_Binary;
		EJSONType operator [] (CJSONConstants const &) const
		{
			return EJSONType_Array;
		}
		CEJSON::CKey operator [] (NStr::CStr const &_Key);
	};
}

NMib::NEncoding::CEJSON::CKey operator "" _ (const char *_pStr, std::size_t _Len);
NMib::NEncoding::CJSON::CKey operator "" __ (const char *_pStr, std::size_t _Len);
extern NMib::NEncoding::CJSONConstants _;

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
