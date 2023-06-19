// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_JSON.h"
#include "Malterlib_Encoding_JSON_Parse.h"
#include "Malterlib_Encoding_JSON_Generate.h"
#include "Malterlib_Encoding_JSON.hpp"

namespace NMib::NEncoding
{
	namespace NPrivate
	{
		CObjectEntryBase::CObjectEntryBase()
		{
		}

		CObjectEntryBase::CObjectEntryBase(CObjectEntryBase const &_Other)
			: mp_Name(_Other.mp_Name)
		{
		}

		CObjectEntryBase::CObjectEntryBase(CObjectEntryBase &&_Other)
			: mp_Name(fg_Move(_Other.mp_Name))
		{
		}
	}
}
