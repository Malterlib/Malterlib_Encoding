// Copyright © 2022 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_EJSON_Parse.h"

namespace NMib::NEncoding::NPrivate
{
	NStr::CStr fg_EJSONGenerate(CEJSON const &_JSON, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags)
	{
		using namespace NStr;

		CStr Return;
		{
			CStr::CAppender StringAppender(Return);

			NJSON::fg_GenerateJSONValue<CEJSONParseContext>(StringAppender, _JSON, 0, _pPrettySeparator, _Flags);

			if (_pPrettySeparator)
				StringAppender += "\n";
		}
		return Return;
	}
}

namespace NMib::NEncoding
{
	template <>
	NStr::CStr CEJSON::f_ToString(ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags) const
	{
		return NPrivate::fg_EJSONGenerate(*this, _pPrettySeparator, _Flags);
	}
}
