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

	NStr::CStr fg_JSONTypeToString(EJSONType _Type)
	{
		using namespace NEncoding;
		switch (_Type)
		{
		case EJSONType_Null: return "null";
		case EJSONType_String: return "string";
		case EJSONType_Integer: return "integer";
		case EJSONType_Float: return "float";
		case EJSONType_Boolean: return "boolean";
		case EJSONType_Object: return "object";
		case EJSONType_Array: return "array";
		default: DMibNeverGetHere; return "unknown";
		}
	}
}
