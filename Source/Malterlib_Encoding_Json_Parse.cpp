// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_Json.h"
#include "Malterlib_Encoding_Json_Parse.h"

namespace NMib::NEncoding::NJson
{
	void CParseContext::f_ThrowErrors(NContainer::TCVector<NStr::CParseError> const &_Errors) const
	{
		NStr::CStr Description = NStr::CParseError::fs_ToString(_Errors);
		
		if (Description.f_IsEmpty())
			Description = "JSON Parse error";

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
