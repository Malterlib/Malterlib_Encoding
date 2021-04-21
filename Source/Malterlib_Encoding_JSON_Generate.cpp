// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_JSON.h"
#include "Malterlib_Encoding_JSON_Generate.h"
#include "Malterlib_Encoding_JSON_Parse.h"

namespace NMib::NEncoding::NPrivate
{
	NStr::CStr fg_JSONGenerate(CJSON const &_JSON, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags)
	{
		using namespace NStr;

		CStr Return;

		NJSON::fg_GenerateJSONValue<NJSON::CParseContext>(Return, _JSON, 0, _pPrettySeparator, _Flags);

		if (_pPrettySeparator)
			Return += "\n";

		return Return;
	}
}
