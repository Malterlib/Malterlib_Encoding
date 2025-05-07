// Copyright © 2022 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_EJson_Parse.h"

namespace NMib::NEncoding
{
	template <typename t_CParent>
	NStr::CStr TCEJsonValue<t_CParent>::f_ToString(ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		using namespace NStr;

		CStr Return;
		{
			CStr::CAppender StringAppender(Return);

			NJson::fg_GenerateJsonValue<NPrivate::CEJsonParseContext>(StringAppender, *this, 0, _pPrettySeparator, _Flags);

			if (_pPrettySeparator && !(_Flags & EJsonDialectFlag_TrimWhitespace))
				StringAppender += "\n";
		}
		return Return;
	}
}

