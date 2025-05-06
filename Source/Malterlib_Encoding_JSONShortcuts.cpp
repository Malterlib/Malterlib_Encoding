// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_JSON.h"
#include "Malterlib_Encoding_JSON.hpp"
#include "Malterlib_Encoding_JSONShortcuts.h"
#include "Malterlib_Encoding_EJSON.hpp"

namespace NMib::NEncoding
{
	template <typename tf_CJson>
	typename tf_CJson::CKey TCJSONConstants<tf_CJson>::operator () (NStr::CStr const &_Key) const
	{
		typename tf_CJson::CKey Key;
		Key.m_Key = _Key;
		return Key;
	}

	template CEJSONOrdered::CKey TCJSONConstants<CEJSONOrdered>::operator () (NStr::CStr const &_Key) const;
	template CEJSONSorted::CKey TCJSONConstants<CEJSONSorted>::operator () (NStr::CStr const &_Key) const;
	template CJSONOrdered::CKey TCJSONConstants<CJSONOrdered>::operator () (NStr::CStr const &_Key) const;
	template CJSONSorted::CKey TCJSONConstants<CJSONSorted>::operator () (NStr::CStr const &_Key) const;
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

constinit NMib::NEncoding::TCJSONConstants<NMib::NEncoding::CEJSONOrdered> const _o;
constinit NMib::NEncoding::TCJSONConstants<NMib::NEncoding::CEJSONSorted> const _;

constinit NMib::NEncoding::TCJSONConstants<NMib::NEncoding::CJSONOrdered> const _jo;
constinit NMib::NEncoding::TCJSONConstants<NMib::NEncoding::CJSONSorted> const _j;

