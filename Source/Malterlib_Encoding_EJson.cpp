// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_EJson.h"
#include "Malterlib_Encoding_EJson.hpp"
#include "Malterlib_Encoding_EJson_Generate.h"
#include "Malterlib_Encoding_EJson_Parse.h"

namespace NMib::NEncoding
{
	constinit NStr::CStr const CEJsonConstStrings::mc_Date = NStr::gc_Str<"$date">;
	constinit NStr::CStr const CEJsonConstStrings::mc_Binary = NStr::gc_Str<"$binary">;
	constinit NStr::CStr const CEJsonConstStrings::mc_Type = NStr::gc_Str<"$type">;
	constinit NStr::CStr const CEJsonConstStrings::mc_Value = NStr::gc_Str<"$value">;
	constinit NStr::CStr const CEJsonConstStrings::mc_Escape = NStr::gc_Str<"$escape">;

	CEJsonUserTypeOrdered::CEJsonUserTypeOrdered() = default;

	CEJsonUserTypeOrdered::CEJsonUserTypeOrdered(NStr::CStr const &_Type, CJsonOrdered const &_Value)
		: m_Type(_Type)
		, m_Value(_Value)
	{
	}

	CEJsonUserTypeOrdered::CEJsonUserTypeOrdered(NStr::CStr const &_Type, CJsonOrdered &&_Value)
		: m_Type(_Type)
		, m_Value(fg_Move(_Value))
	{
	}

	bool CEJsonUserTypeOrdered::operator == (CEJsonUserTypeOrdered const &_Right) const
	{
		if (m_Type != _Right.m_Type)
			return false;
		return m_Value == _Right.m_Value;
	}

	COrdering_Partial CEJsonUserTypeOrdered::operator <=> (CEJsonUserTypeOrdered const &_Right) const
	{
		if (auto Result = m_Type <=> _Right.m_Type; Result != 0)
			return Result;

		return m_Value <=> _Right.m_Value;
	}

	CEJsonUserTypeOrdered fg_UserTypeOrdered(NStr::CStr const &_Type, CJsonOrdered const &_Value)
	{
		return CEJsonUserTypeOrdered{_Type, _Value};
	}

	CEJsonUserTypeOrdered fg_UserTypeOrdered(NStr::CStr const &_Type, CJsonOrdered &&_Value)
	{
		return CEJsonUserTypeOrdered{_Type, fg_Move(_Value)};
	}

	CEJsonUserTypeSorted::CEJsonUserTypeSorted() = default;

	CEJsonUserTypeSorted::CEJsonUserTypeSorted(NStr::CStr const &_Type, CJsonSorted const &_Value)
		: m_Type(_Type)
		, m_Value(_Value)
	{
	}

	CEJsonUserTypeSorted::CEJsonUserTypeSorted(NStr::CStr const &_Type, CJsonSorted &&_Value)
		: m_Type(_Type)
		, m_Value(fg_Move(_Value))
	{
	}

	CEJsonUserTypeOrdered::CEJsonUserTypeOrdered(CEJsonUserTypeSorted const &_Other)
		: m_Type(_Other.m_Type)
		, m_Value(CJsonOrdered::fs_FromCompatible(_Other.m_Value))
	{
	}

	CEJsonUserTypeOrdered::CEJsonUserTypeOrdered(CEJsonUserTypeSorted &&_Other)
		: m_Type(fg_Move(_Other.m_Type))
		, m_Value(CJsonOrdered::fs_FromCompatible(fg_Move(_Other.m_Value) ))
	{
	}

	CEJsonUserTypeSorted::CEJsonUserTypeSorted(CEJsonUserTypeOrdered const &_Other)
		: m_Type(_Other.m_Type)
		, m_Value(CJsonSorted::fs_FromCompatible(_Other.m_Value))
	{
	}

	CEJsonUserTypeSorted::CEJsonUserTypeSorted(CEJsonUserTypeOrdered &&_Other)
		: m_Type(fg_Move(_Other.m_Type))
		, m_Value(CJsonSorted::fs_FromCompatible(fg_Move(_Other.m_Value)))
	{
	}

	bool CEJsonUserTypeSorted::operator == (CEJsonUserTypeSorted const &_Right) const
	{
		if (m_Type != _Right.m_Type)
			return false;
		return m_Value == _Right.m_Value;
	}

	COrdering_Partial CEJsonUserTypeSorted::operator <=> (CEJsonUserTypeSorted const &_Right) const
	{
		if (auto Result = m_Type <=> _Right.m_Type; Result != 0)
			return Result;

		return m_Value <=> _Right.m_Value;
	}

	CEJsonUserTypeSorted fg_UserTypeSorted(NStr::CStr const &_Type, CJsonSorted const &_Value)
	{
		return CEJsonUserTypeSorted{_Type, _Value};
	}

	CEJsonUserTypeSorted fg_UserTypeSorted(NStr::CStr const &_Type, CJsonSorted &&_Value)
	{
		return CEJsonUserTypeSorted{_Type, fg_Move(_Value)};
	}

	NStr::CStr fg_EJsonTypeToString(EEJsonType _Type)
	{
		using namespace NEncoding;
		switch (_Type)
		{
		case EEJsonType_Null: return "null";
		case EEJsonType_String: return "string";
		case EEJsonType_Integer: return "integer";
		case EEJsonType_Float: return "float";
		case EEJsonType_Boolean: return "boolean";
		case EEJsonType_Object: return "object";
		case EEJsonType_Array: return "array";
		case EEJsonType_Date: return "date";
		case EEJsonType_Binary: return "binary";
		case EEJsonType_UserType: return "user type";
		default: DMibNeverGetHere; return "unknown";
		}
	}

	NStr::CStr fg_JsonTypeToString(EEJsonType _Type)
	{
		return fg_EJsonTypeToString(_Type);
	}
}
