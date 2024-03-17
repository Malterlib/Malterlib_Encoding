// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_JSON.h"
#include "Malterlib_Encoding_JSON.hpp"
#include "Malterlib_Encoding_JSONShortcuts.h"
#include "Malterlib_Encoding_EJSON.hpp"

namespace NMib::NEncoding
{
	CEJSONOrdered::CKey CJSONConstantsOrdered::operator () (NStr::CStr const &_Key) const
	{
		CEJSONOrdered::CKey Key;
		Key.m_Key = _Key;
		return Key;
	}

	CEJSONSorted::CKey CJSONConstantsSorted::operator () (NStr::CStr const &_Key) const
	{
		CEJSONSorted::CKey Key;
		Key.m_Key = _Key;
		return Key;
	}
}

NMib::NEncoding::CEJSONOrdered::CKey operator ""_o (const char *_pStr, std::size_t _Len)
{
	NMib::NEncoding::CEJSONOrdered::CKey Ret;
	Ret.m_Key = NMib::NStr::CStr(_pStr, _Len);
	return Ret;
}


NMib::NEncoding::CJSONOrdered::CKey operator ""_jo (const char *_pStr, std::size_t _Len)
{
	NMib::NEncoding::CJSONOrdered::CKey Ret;
	Ret.m_Key = NMib::NStr::CStr(_pStr, _Len);
	return Ret;
}

NMib::NEncoding::CEJSONSorted::CKey operator ""_ (const char *_pStr, std::size_t _Len)
{
	NMib::NEncoding::CEJSONSorted::CKey Ret;
	Ret.m_Key = NMib::NStr::CStr(_pStr, _Len);
	return Ret;
}


NMib::NEncoding::CJSONSorted::CKey operator ""_j (const char *_pStr, std::size_t _Len)
{
	NMib::NEncoding::CJSONSorted::CKey Ret;
	Ret.m_Key = NMib::NStr::CStr(_pStr, _Len);
	return Ret;
}

constinit NMib::NEncoding::CJSONConstantsOrdered const _o;
constinit NMib::NEncoding::CJSONConstantsSorted const _;
