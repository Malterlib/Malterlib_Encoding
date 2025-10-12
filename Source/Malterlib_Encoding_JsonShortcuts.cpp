// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_Json.h"
#include "Malterlib_Encoding_Json.hpp"
#include "Malterlib_Encoding_JsonShortcuts.h"
#include "Malterlib_Encoding_EJson.hpp"

namespace NMib::NEncoding
{
	template <typename tf_CJson>
	typename tf_CJson::CKey TCJsonConstants<tf_CJson>::operator () (NStr::CStr const &_Key)
	{
		typename tf_CJson::CKey Key;
		Key.m_Key = _Key;
		return Key;
	}

	template CEJsonOrdered::CKey TCJsonConstants<CEJsonOrdered>::operator () (NStr::CStr const &_Key);
	template CEJsonSorted::CKey TCJsonConstants<CEJsonSorted>::operator () (NStr::CStr const &_Key);
	template CJsonOrdered::CKey TCJsonConstants<CJsonOrdered>::operator () (NStr::CStr const &_Key);
	template CJsonSorted::CKey TCJsonConstants<CJsonSorted>::operator () (NStr::CStr const &_Key);
}

NMib::NEncoding::CEJsonOrdered::CKey operator ""_o (const char *_pStr, std::size_t _Len)
{
	NMib::NEncoding::CEJsonOrdered::CKey Ret;
	Ret.m_Key = NMib::NStr::CStr(_pStr, _Len);
	return Ret;
}


NMib::NEncoding::CJsonOrdered::CKey operator ""_jo (const char *_pStr, std::size_t _Len)
{
	NMib::NEncoding::CJsonOrdered::CKey Ret;
	Ret.m_Key = NMib::NStr::CStr(_pStr, _Len);
	return Ret;
}

NMib::NEncoding::CEJsonSorted::CKey operator ""_ (const char *_pStr, std::size_t _Len)
{
	NMib::NEncoding::CEJsonSorted::CKey Ret;
	Ret.m_Key = NMib::NStr::CStr(_pStr, _Len);
	return Ret;
}


NMib::NEncoding::CJsonSorted::CKey operator ""_j (const char *_pStr, std::size_t _Len)
{
	NMib::NEncoding::CJsonSorted::CKey Ret;
	Ret.m_Key = NMib::NStr::CStr(_pStr, _Len);
	return Ret;
}
