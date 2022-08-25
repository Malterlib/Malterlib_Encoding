// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_JSON.h"
#include "Malterlib_Encoding_JSON.hpp"
#include "Malterlib_Encoding_JSONShortcuts.h"
#include "Malterlib_Encoding_EJSON.hpp"

namespace NMib::NEncoding
{
	constexpr EJSONType CJSONConstants::mc_Null;
	constexpr EJSONType CJSONConstants::mc_EmptyString;
	constexpr EJSONType CJSONConstants::mc_EmptyObject;
	constexpr EJSONType CJSONConstants::mc_EmptyArray;
	constexpr EEJSONType CJSONConstants::mc_InvalidDate;
	constexpr EEJSONType CJSONConstants::mc_EmptyBinary;

	CEJSON::CKey CJSONConstants::operator [] (NStr::CStr const &_Key)
	{
		CEJSON::CKey Key;
		Key.m_Key = _Key;
		return Key;
	}
}

NMib::NEncoding::CEJSON::CKey operator ""_ (const char *_pStr, std::size_t _Len)
{
	NMib::NEncoding::CEJSON::CKey Ret;
	Ret.m_Key = NMib::NStr::CStr(_pStr, _Len);
	return Ret;
}


NMib::NEncoding::CJSON::CKey operator ""__ (const char *_pStr, std::size_t _Len)
{
	NMib::NEncoding::CJSON::CKey Ret;
	Ret.m_Key = NMib::NStr::CStr(_pStr, _Len);
	return Ret;
}

NMib::NEncoding::CEJSONSorted::CKey operator ""_s (const char *_pStr, std::size_t _Len)
{
	NMib::NEncoding::CEJSONSorted::CKey Ret;
	Ret.m_Key = NMib::NStr::CStr(_pStr, _Len);
	return Ret;
}


NMib::NEncoding::CJSONSorted::CKey operator ""__s (const char *_pStr, std::size_t _Len)
{
	NMib::NEncoding::CJSONSorted::CKey Ret;
	Ret.m_Key = NMib::NStr::CStr(_pStr, _Len);
	return Ret;
}

NMib::NEncoding::CJSONConstants _;
