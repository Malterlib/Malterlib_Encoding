// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_Json.h"
#include "Malterlib_Encoding_Json_Parse.h"
#include "Malterlib_Encoding_Json_Generate.h"
#include "Malterlib_Encoding_Json.hpp"

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

	NStr::CStr fg_JsonTypeToString(EJsonType _Type)
	{
		using namespace NEncoding;
		switch (_Type)
		{
		case EJsonType_Null: return "null";
		case EJsonType_String: return "string";
		case EJsonType_Integer: return "integer";
		case EJsonType_Float: return "float";
		case EJsonType_Boolean: return "boolean";
		case EJsonType_Object: return "object";
		case EJsonType_Array: return "array";
		default: DMibNeverGetHere; return "unknown";
		}
	}
}
