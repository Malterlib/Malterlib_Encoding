// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_JSON.h"
#include "Malterlib_Encoding_JSON_Parse.h"

namespace NMib::NEncoding::NPrivate
{
	CJSON fg_JSONParse(NStr::CStr const &_String, NStr::CStr const &_FileName, bool _bConvertNullToSpace)
	{
		using namespace NStr;
		CJSON Output;
		CStr ToParse = _String;

		uch8 const *pParse = reinterpret_cast<uch8 const *>(ToParse.f_GetStr());

		NJSON::CParseContext Context;
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

namespace NMib::NEncoding::NJSON
{
	void CParseContext::f_ThrowErrors(NContainer::TCVector<NStr::CParseError> const &_Errors) const
	{
		NStr::CStr Description = NStr::CStr::CFormat("JSON parse error:{\n}");
		for (auto &Error : _Errors)
		{
			Description
				+= NStr::CStr::CFormat(DMibPFileLineColumnFormat " {}{\n}")
				<< Error.m_Location.m_File
				<< Error.m_Location.m_Line
				<< Error.m_Location.m_Column
				<< Error.m_Error
			;
		}
		DMibErrorParse(Description, _Errors);
	}

	void CParseContext::f_ThrowError(NStr::CStr const &_Error, uch8 const *_pLocation) const
	{
		NContainer::TCVector<NStr::CParseError> Errors;
		auto &Error = Errors.f_Insert();
		Error.m_Location = f_GetLocation(_pLocation);
		Error.m_Error = _Error;
		f_ThrowErrors(Errors);
	}
}
