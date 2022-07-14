// Copyright © 2022 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_EJSON_Parse.h"

namespace NMib::NEncoding::NPrivate
{
	CEJSON fg_EJSONParse(NStr::CStr const &_String, NStr::CStr const &_FileName, bool _bConvertNullToSpace)
	{
		using namespace NStr;
		CEJSON Output;
		CStr ToParse = _String;

		uch8 const *pParse = reinterpret_cast<uch8 const *>(ToParse.f_GetStr());

		CEJSONParseContext Context;
		Context.m_pStartParse = pParse;
		Context.m_FileName = _FileName;
		Context.m_bConvertNullToSpace = _bConvertNullToSpace;

		fg_ParseWhiteSpace(pParse);

		// Any value is allowed at root
		NJSON::fg_ParseJSONValue(Output, pParse, Context);

		fg_ParseWhiteSpace(pParse);

		if (*pParse)
			Context.f_ThrowError("Unexpected character after root value", pParse);

		return fg_Move(Output);
	}
}

namespace NMib::NEncoding
{
	template <>
	CEJSON CEJSON::fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName, bool _bConvertNullToSpace)
	{
		return NPrivate::fg_EJSONParse(_String, _FileName, _bConvertNullToSpace);
	}
}
