// Copyright © 2022 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_EJSON_Parse.h"

namespace NMib::NEncoding
{
	template <typename t_CParent>
	NStr::CStr TCEJSONValue<t_CParent>::f_ToString(ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags) const
	{
		using namespace NStr;

		CStr Return;
		{
			CStr::CAppender StringAppender(Return);

			NJSON::fg_GenerateJSONValue<NPrivate::CEJSONParseContext>(StringAppender, *this, 0, _pPrettySeparator, _Flags);

			if (_pPrettySeparator && !(_Flags & EJSONDialectFlag_TrimWhitespace))
				StringAppender += "\n";
		}
		return Return;
	}
}

