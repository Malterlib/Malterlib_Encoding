// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_EJSON.h"
#include "Malterlib_Encoding_EJSON.hpp"
#include "Malterlib_Encoding_EJSON_Generate.h"
#include "Malterlib_Encoding_EJSON_Parse.h"

namespace NMib::NEncoding
{
	constinit NStr::CStr const CEJSONConstStrings::mc_Date = NStr::gc_Str<"$date">;
	constinit NStr::CStr const CEJSONConstStrings::mc_Binary = NStr::gc_Str<"$binary">;
	constinit NStr::CStr const CEJSONConstStrings::mc_Type = NStr::gc_Str<"$type">;
	constinit NStr::CStr const CEJSONConstStrings::mc_Value = NStr::gc_Str<"$value">;
	constinit NStr::CStr const CEJSONConstStrings::mc_Escape = NStr::gc_Str<"$escape">;

	CEJSONUserTypeOrdered::CEJSONUserTypeOrdered() = default;

	CEJSONUserTypeOrdered::CEJSONUserTypeOrdered(NStr::CStr const &_Type, CJSONOrdered const &_Value)
		: m_Type(_Type)
		, m_Value(_Value)
	{
	}

	CEJSONUserTypeOrdered::CEJSONUserTypeOrdered(NStr::CStr const &_Type, CJSONOrdered &&_Value)
		: m_Type(_Type)
		, m_Value(fg_Move(_Value))
	{
	}

	bool CEJSONUserTypeOrdered::operator == (CEJSONUserTypeOrdered const &_Right) const
	{
		if (m_Type != _Right.m_Type)
			return false;
		return m_Value == _Right.m_Value;
	}

	COrdering_Partial CEJSONUserTypeOrdered::operator <=> (CEJSONUserTypeOrdered const &_Right) const
	{
		if (auto Result = m_Type <=> _Right.m_Type; Result != 0)
			return Result;

		return m_Value <=> _Right.m_Value;
	}

	CEJSONUserTypeOrdered fg_UserTypeOrdered(NStr::CStr const &_Type, CJSONOrdered const &_Value)
	{
		return CEJSONUserTypeOrdered{_Type, _Value};
	}

	CEJSONUserTypeOrdered fg_UserTypeOrdered(NStr::CStr const &_Type, CJSONOrdered &&_Value)
	{
		return CEJSONUserTypeOrdered{_Type, fg_Move(_Value)};
	}

	CEJSONUserTypeSorted::CEJSONUserTypeSorted() = default;

	CEJSONUserTypeSorted::CEJSONUserTypeSorted(NStr::CStr const &_Type, CJSONSorted const &_Value)
		: m_Type(_Type)
		, m_Value(_Value)
	{
	}

	CEJSONUserTypeSorted::CEJSONUserTypeSorted(NStr::CStr const &_Type, CJSONSorted &&_Value)
		: m_Type(_Type)
		, m_Value(fg_Move(_Value))
	{
	}

	CEJSONUserTypeOrdered::CEJSONUserTypeOrdered(CEJSONUserTypeSorted const &_Other)
		: m_Type(_Other.m_Type)
		, m_Value(CJSONOrdered::fs_FromCompatible(_Other.m_Value))
	{
	}

	CEJSONUserTypeOrdered::CEJSONUserTypeOrdered(CEJSONUserTypeSorted &&_Other)
		: m_Type(fg_Move(_Other.m_Type))
		, m_Value(CJSONOrdered::fs_FromCompatible(fg_Move(_Other.m_Value) ))
	{
	}

	CEJSONUserTypeSorted::CEJSONUserTypeSorted(CEJSONUserTypeOrdered const &_Other)
		: m_Type(_Other.m_Type)
		, m_Value(CJSONSorted::fs_FromCompatible(_Other.m_Value))
	{
	}

	CEJSONUserTypeSorted::CEJSONUserTypeSorted(CEJSONUserTypeOrdered &&_Other)
		: m_Type(fg_Move(_Other.m_Type))
		, m_Value(CJSONSorted::fs_FromCompatible(fg_Move(_Other.m_Value)))
	{
	}

	bool CEJSONUserTypeSorted::operator == (CEJSONUserTypeSorted const &_Right) const
	{
		if (m_Type != _Right.m_Type)
			return false;
		return m_Value == _Right.m_Value;
	}

	COrdering_Partial CEJSONUserTypeSorted::operator <=> (CEJSONUserTypeSorted const &_Right) const
	{
		if (auto Result = m_Type <=> _Right.m_Type; Result != 0)
			return Result;

		return m_Value <=> _Right.m_Value;
	}

	CEJSONUserTypeSorted fg_UserTypeSorted(NStr::CStr const &_Type, CJSONSorted const &_Value)
	{
		return CEJSONUserTypeSorted{_Type, _Value};
	}

	CEJSONUserTypeSorted fg_UserTypeSorted(NStr::CStr const &_Type, CJSONSorted &&_Value)
	{
		return CEJSONUserTypeSorted{_Type, fg_Move(_Value)};
	}

	NStr::CStr fg_EJSONTypeToString(EEJSONType _Type)
	{
		using namespace NEncoding;
		switch (_Type)
		{
		case EEJSONType_Null: return "null";
		case EEJSONType_String: return "string";
		case EEJSONType_Integer: return "integer";
		case EEJSONType_Float: return "float";
		case EEJSONType_Boolean: return "boolean";
		case EEJSONType_Object: return "object";
		case EEJSONType_Array: return "array";
		case EEJSONType_Date: return "date";
		case EEJSONType_Binary: return "binary";
		case EEJSONType_UserType: return "user type";
		default: DMibNeverGetHere; return "unknown";
		}
	}
}
