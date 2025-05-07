// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
	template <typename t_CParent>
	TCJsonValue<t_CParent>::CKey::CKey() = default;

	template <typename t_CParent>
	TCJsonValue<t_CParent>::CKey::CKey(CKey &&_Other) = default;

	template <typename t_CParent>
	TCJsonValue<t_CParent>::TCJsonValue()
	{
	}

	template <typename t_CParent>
	TCJsonValue<t_CParent>::TCJsonValue(TCJsonValue const &_Other)
		: t_CParent(static_cast<t_CParent const &>(_Other))
	{
	}

	template <typename t_CParent>
	TCJsonValue<t_CParent>::TCJsonValue(TCJsonValue &&_Other)
		: t_CParent(fg_Move(static_cast<t_CParent &>(_Other)))
	{
	}

	template <typename t_CParent>
	TCJsonValue<t_CParent>::TCJsonValue(TCJsonValue const &&_Other)
		: t_CParent(static_cast<t_CParent const &>(_Other))
	{
	}

	template <typename t_CParent>
	template <typename tf_CParent>
	TCJsonValue<t_CParent>::TCJsonValue(TCJsonValue<tf_CParent> const &_Other)
		: t_CParent(static_cast<tf_CParent const &>(_Other))
	{
	}

	template <typename t_CParent>
	template <typename tf_CParent>
	TCJsonValue<t_CParent>::TCJsonValue(TCJsonValue<tf_CParent> &&_Other)
		: t_CParent(fg_Move(static_cast<tf_CParent &>(_Other)))
	{
	}

	template <typename t_CParent>
	template <typename tf_CParent>
	TCJsonValue<t_CParent>::TCJsonValue(TCJsonValue<tf_CParent> const &&_Other)
		: t_CParent(static_cast<tf_CParent const &>(_Other))
	{
	}

	template <typename t_CParent>
	template <typename tf_CParent>
	auto TCJsonValue<t_CParent>::fs_FromCompatible(TCJsonValue<tf_CParent> const &_Other) -> TCJsonValue
	{
		return TCJsonValue(_Other);
	}

	template <typename t_CParent>
	template <typename tf_CParent>
	auto TCJsonValue<t_CParent>::fs_FromCompatible(TCJsonValue<tf_CParent> &&_Other) -> TCJsonValue
	{
		return TCJsonValue(_Other);
	}

	template <typename t_CParent>
	template <typename tf_CParent>
	auto TCJsonValue<t_CParent>::fs_FromCompatible(TCJsonValue<tf_CParent> const &&_Other) -> TCJsonValue
	{
		return TCJsonValue(_Other);
	}

	template <typename t_CParent>
	TCJsonValue<t_CParent>::TCJsonValue(EJsonType _Type)
	{
		f_SetType(_Type);
	}

	template <typename t_CParent>
	TCJsonValue<t_CParent>::TCJsonValue(ch8 const *_pValue)
		: t_CParent(_pValue)
	{
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator = (ch8 const *_pValue) -> CValue &
	{
		this->mp_Value = _pValue;
		return static_cast<CValue &>(*this);
	}

	template <typename t_CParent>
	EJsonType TCJsonValue<t_CParent>::f_Type() const
	{
		return (EJsonType)this->mp_Value.f_GetTypeID();
	}

	template <typename t_CParent>
	void TCJsonValue<t_CParent>::f_SetType(EJsonType _Type)
	{
		if (f_Type() == _Type)
			return;
		switch (_Type)
		{
		case EJsonType_Invalid:
			this->mp_Value.template f_Set<EJsonType_Invalid>();
			break;
		case EJsonType_Null:
			this->mp_Value.template f_Set<EJsonType_Null>();
			break;
		case EJsonType_String:
			this->mp_Value.template f_Set<EJsonType_String>();
			break;
		case EJsonType_Integer:
			this->mp_Value.template f_Set<EJsonType_Integer>();
			break;
		case EJsonType_Float:
			this->mp_Value.template f_Set<EJsonType_Float>();
			break;
		case EJsonType_Boolean:
			this->mp_Value.template f_Set<EJsonType_Boolean>();
			break;
		case EJsonType_Object:
			this->mp_Value.template f_Set<EJsonType_Object>();
			break;
		case EJsonType_Array:
			this->mp_Value.template f_Set<EJsonType_Array>();
			break;
		default:
			DMibNeverGetHere;
			break;
		}
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::f_IsValid() const
	{
		return this->f_Type() != EJsonType_Invalid;
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::f_IsNull() const
	{
		return this->f_Type() == EJsonType_Null;
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::f_IsString() const
	{
		return this->f_Type() == EJsonType_String;
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::f_IsInteger() const
	{
		return this->f_Type() == EJsonType_Integer;
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::f_IsFloat() const
	{
		return this->f_Type() == EJsonType_Float;
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::f_IsBoolean() const
	{
		return this->f_Type() == EJsonType_Boolean;
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::f_IsObject() const
	{
		return this->f_Type() == EJsonType_Object;
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::f_IsArray() const
	{
		return this->f_Type() == EJsonType_Array;
	}

	template <typename t_CParent>
	void TCJsonValue<t_CParent>::fp_PromoteType(EJsonType _Type)
	{
		DMibRequire(this->f_Type() == EJsonType_Invalid || this->f_Type() == _Type);
		if (this->f_Type() == _Type)
			return;
		f_SetType(_Type);
	}

	template <typename t_CParent>
	void TCJsonValue<t_CParent>::fp_CheckType(EJsonType _Type) const
	{
		using namespace NStr;
		
		if (this->f_Type() != _Type)
			DMibError("Trying to access by wrong type. {} != {}"_f << fg_JsonTypeToString(this->f_Type()) << fg_JsonTypeToString(_Type));
	}

	template <typename t_CParent>
	NStr::CStr const &TCJsonValue<t_CParent>::f_String() const
	{
		fp_CheckType(EJsonType_String);
		return this->mp_Value.template f_Get<EJsonType_String>();
	}

	template <typename t_CParent>
	NStr::CStr &TCJsonValue<t_CParent>::f_String()
	{
		fp_PromoteType(EJsonType_String);
		return this->mp_Value.template f_Get<EJsonType_String>();
	}

	template <typename t_CParent>
	int64 const &TCJsonValue<t_CParent>::f_Integer() const
	{
		fp_CheckType(EJsonType_Integer);
		return this->mp_Value.template f_Get<EJsonType_Integer>();
	}

	template <typename t_CParent>
	int64 &TCJsonValue<t_CParent>::f_Integer()
	{
		fp_PromoteType(EJsonType_Integer);
		return this->mp_Value.template f_Get<EJsonType_Integer>();
	}

	template <typename t_CParent>
	fp64 const &TCJsonValue<t_CParent>::f_Float() const
	{
		fp_CheckType(EJsonType_Float);
		return this->mp_Value.template f_Get<EJsonType_Float>();
	}

	template <typename t_CParent>
	fp64 &TCJsonValue<t_CParent>::f_Float()
	{
		fp_PromoteType(EJsonType_Float);
		return this->mp_Value.template f_Get<EJsonType_Float>();
	}

	template <typename t_CParent>
	bool const &TCJsonValue<t_CParent>::f_Boolean() const
	{
		fp_CheckType(EJsonType_Boolean);
		return this->mp_Value.template f_Get<EJsonType_Boolean>();
	}

	template <typename t_CParent>
	bool &TCJsonValue<t_CParent>::f_Boolean()
	{
		fp_PromoteType(EJsonType_Boolean);
		return this->mp_Value.template f_Get<EJsonType_Boolean>();
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::f_Object() const -> CObject const &
	{
		fp_CheckType(EJsonType_Object);
		return this->mp_Value.template f_Get<EJsonType_Object>();
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::f_Object() -> CObject &
	{
		fp_PromoteType(EJsonType_Object);
		return this->mp_Value.template f_Get<EJsonType_Object>();
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::f_Array() const -> typename NContainer::TCVector<CValue> const &
	{
		fp_CheckType(EJsonType_Array);
		return this->mp_Value.template f_Get<EJsonType_Array>();
	}

	template <typename t_CParent>
	NContainer::TCVector<NStr::CStr> TCJsonValue<t_CParent>::f_StringArray() const &
	{
		auto &SourceArray = f_Array();

		NContainer::TCVector<NStr::CStr> Return;
		Return.f_Reserve(SourceArray.f_GetLen());

		for (auto &Value : SourceArray)
			Return.f_Insert(Value.f_String());

		return Return;
	}

	template <typename t_CParent>
	NContainer::TCVector<NStr::CStr> TCJsonValue<t_CParent>::f_StringArray() &&
	{
		auto &SourceArray = f_Array();

		if (SourceArray.f_IsEmpty())
			return {};

		NContainer::TCVector<NStr::CStr> Return;
		Return.f_Reserve(SourceArray.f_GetLen());

		for (auto &Value : SourceArray)
			Return.f_Insert(fg_Move(Value.f_String()));

		return Return;
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::f_IsStringArray() const
	{
		if (!f_IsArray())
			return false;

		for (auto &Value : f_Array())
		{
			if (!Value.f_IsString())
				return false;
		}

		return true;
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::f_Array() -> typename NContainer::TCVector<CValue> &
	{
		fp_PromoteType(EJsonType_Array);
		return this->mp_Value.template f_Get<EJsonType_Array>();
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_AsString() const
	{
		switch (f_Type())
		{
		case EJsonType_Null:
			return "null";
		case EJsonType_String:
			return f_String();
		case EJsonType_Integer:
			return NStr::CStr::fs_ToStr(f_Integer());
		case EJsonType_Float:
			return NStr::CStr::fs_ToStr(f_Float());
		case EJsonType_Boolean:
			return f_Boolean() ? "true" : "false";
		case EJsonType_Object:
			return static_cast<CValue const &>(*this).f_ToString();
		case EJsonType_Array:
			return static_cast<CValue const &>(*this).f_ToString();
		default:
			DMibError("JSON type cannot be converted to string");
		}
	}

	template <typename t_CParent>
	int64 TCJsonValue<t_CParent>::f_AsInteger() const
	{
		switch (f_Type())
		{
		case EJsonType_String:
			return f_String().f_ToInt(int64(0));
		case EJsonType_Integer:
			return f_Integer();
		case EJsonType_Float:
			return f_Float().f_ToIntRound();
		case EJsonType_Boolean:
			return f_Boolean() ? 1 : 0;
		default:
			DMibError("JSON type cannot be converted to integer");
		}
	}

	template <typename t_CParent>
	fp64 TCJsonValue<t_CParent>::f_AsFloat() const
	{
		switch (f_Type())
		{
		case EJsonType_String:
			{
				auto &String = f_String();
				if (String == "QNaN")
					return fp64::fs_QNan();
				else if (String == "-QNaN")
					return fp64::fs_NegQNan();
				else if (String == "SNaN")
					return fp64::fs_SNan();
				else if (String == "-SNaN")
					return fp64::fs_NegSNan();
				else if (String == "Inf")
					return fp64::fs_Inf();
				else if (String == "-Inf")
					return fp64::fs_NegInf();
				else
					return f_String().f_ToFloat(fp64::fs_SNan());
			}
		case EJsonType_Integer:
			return f_Integer();
		case EJsonType_Float:
			return f_Float();
		case EJsonType_Boolean:
			return f_Boolean() ? 1.0 : 0.0;
		default:
			DMibError("JSON type cannot be converted to float");
		}
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::f_AsBoolean() const
	{
		switch (f_Type())
		{
		case EJsonType_String:
			{
				auto &String = f_String();
				return String.f_CmpNoCase("true") == 0 || String.f_ToInt(0) != 0;
			}
		case EJsonType_Integer:
			return f_Integer() != 0;
		case EJsonType_Float:
			return f_Float() != 0.0;
		case EJsonType_Boolean:
			return f_Boolean();
		default:
			DMibError("JSON type cannot be converted to boolean");
		}
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_AsString(NStr::CStr const &_Default) const
	{
		switch (f_Type())
		{
		case EJsonType_Null:
			return "null";
		case EJsonType_String:
			return f_String();
		case EJsonType_Integer:
			return NStr::CStr::fs_ToStr(f_Integer());
		case EJsonType_Float:
			return NStr::CStr::fs_ToStr(f_Float());
		case EJsonType_Boolean:
			return f_Boolean() ? "true" : "false";
		case EJsonType_Object:
			return static_cast<CValue const &>(*this).f_ToString();
		case EJsonType_Array:
			return static_cast<CValue const &>(*this).f_ToString();
		default:
			return _Default;
		}
	}

	template <typename t_CParent>
	int64 TCJsonValue<t_CParent>::f_AsInteger(int64 _Default) const
	{
		switch (f_Type())
		{
		case EJsonType_String:
			return f_String().f_ToInt(_Default);
		case EJsonType_Integer:
			return f_Integer();
		case EJsonType_Float:
			return f_Float().f_ToIntRound();
		case EJsonType_Boolean:
			return f_Boolean() ? 1 : 0;
		default:
			return _Default;
		}
	}

	template <typename t_CParent>
	fp64 TCJsonValue<t_CParent>::f_AsFloat(fp64 _Default) const
	{
		switch (f_Type())
		{
		case EJsonType_String:
			return f_String().f_ToFloat(_Default);
		case EJsonType_Integer:
			return f_Integer();
		case EJsonType_Float:
			return f_Float();
		case EJsonType_Boolean:
			return f_Boolean() ? 1.0 : 0.0;
		default:
			return _Default;
		}
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::f_AsBoolean(bool _Default) const
	{
		switch (f_Type())
		{
		case EJsonType_String:
			{
				auto &String = f_String();
				return String.f_CmpNoCase("true") == 0 || String.f_ToInt(0) != 0;
			}
		case EJsonType_Integer:
			return f_Integer() != 0;
		case EJsonType_Float:
			return f_Float() != 0.0;
		case EJsonType_Boolean:
			return f_Boolean();
		default:
			return _Default;
		}
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator = (TCJsonValue const &_Value) -> CValue &
	{
		this->mp_Value = _Value.mp_Value;
		return static_cast<CValue &>(*this);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator = (TCJsonValue &&_Value) -> CValue &
	{
		auto Temp = fg_Move(_Value.mp_Value);
		_Value.mp_Value.template f_Set<EJsonType_Invalid>();
		this->mp_Value = fg_Move(Temp);
		return static_cast<CValue &>(*this);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator = (pfp64 _Value) -> CValue &
	{
		this->mp_Value = fp64(_Value);
		return static_cast<CValue &>(*this);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator = (pfp32 _Value) -> CValue &
	{
		this->mp_Value = fp64(_Value);
		return static_cast<CValue &>(*this);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator = (fp32 _Value) -> CValue &
	{
		this->mp_Value = fp64(_Value);
		return static_cast<CValue &>(*this);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator = (bool _Value) -> CValue &
	{
		this->mp_Value = NPrivate::CJsonBoolean(_Value);
		return static_cast<CValue &>(*this);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator = (EJsonType _Type) -> CValue &
	{
		this->f_SetType(_Type);
		return static_cast<CValue &>(*this);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::f_GetMember(NStr::CStr const &_Name) const -> CValue const *
	{
		if (!f_IsObject())
			return nullptr;

		auto pMember = f_Object().f_GetMember(_Name);
		if (pMember)
			return pMember;
		return nullptr;
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::f_GetMember(NStr::CStr const &_Name) -> CValue *
	{
		if (!f_IsObject())
			return nullptr;

		auto pMember = f_Object().f_GetMember(_Name);
		if (pMember)
			return pMember;
		return nullptr;
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::f_GetMember(NStr::CStr const &_Name, EJsonType _Type) const -> CValue const *
	{
		if (!f_IsObject())
			return nullptr;

		auto pMember = f_Object().f_GetMember(_Name, _Type);
		if (pMember)
			return pMember;
		return nullptr;
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::f_GetMember(NStr::CStr const &_Name, EJsonType _Type) -> CValue *
	{
		if (!f_IsObject())
			return nullptr;

		auto pMember = f_Object().f_GetMember(_Name, _Type);
		if (pMember)
			return pMember;
		return nullptr;
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::f_GetMemberValue(NStr::CStr const &_Name, CValue const &_Default) const -> CValue
	{
		if (!f_IsObject())
			return _Default;

		return f_Object().f_GetMemberValue(_Name, _Default);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::f_GetMemberValue(NStr::CStr const &_Name, CValue &&_Default) const -> CValue
	{
		if (!f_IsObject())
			return _Default;

		return f_Object().f_GetMemberValue(_Name, fg_Move(_Default));
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator [](NStr::CStr const &_Name) -> CValue &
	{
		return f_Object().f_CreateMember(_Name);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator [] (NStr::CStr const &_Name) const -> CValue const &
	{
		if (!f_IsObject())
			DMibError(fg_Format("Not an object when getting member '{}'", _Name));

		auto pMember = f_Object().f_GetMember(_Name);
		if (!pMember)
			DMibError(fg_Format("Member '{}' not found", _Name));

		return *pMember;
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator () (NStr::CStr const &_Name) -> CValue &
	{
		if (!f_IsObject())
			DMibError(fg_Format("Not an object when getting member '{}'", _Name));

		auto pMember = f_Object().f_GetMember(_Name);
		if (!pMember)
			DMibError(fg_Format("Member '{}' not found", _Name));

		return *pMember;
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::f_RemoveMember(NStr::CStr const &_Name)
	{
		return f_Object().f_RemoveMember(_Name);
	}

	template <typename t_CParent>
	void TCJsonValue<t_CParent>::f_SortObjectsLexicographically()
	{
		if (f_IsObject())
			f_Object().f_SortObjectsLexicographically();
		else if (f_IsArray())
		{
			for (auto &Value : f_Array())
				Value.f_SortObjectsLexicographically();
		}
	}

	namespace NPrivate
	{
		struct CJsonEqualsVisitor
		{
			template <typename tf_CTypeLeft, typename tf_CTypeRight>
			bool operator ()(tf_CTypeLeft const &, tf_CTypeRight const &)
			{
				return false;
			}

			template <typename tf_CType>
			bool operator ()(tf_CType const &_Left, tf_CType const &_Right)
			{
				return _Left == _Right;
			}

			bool operator ()(fp64 const &_Left, fp64 const &_Right)
			{
				return _Left.f_EqualIncludingNan(_Right);
			}

			bool operator ()(CVoidTag const &_Left, CVoidTag const &_Right)
			{
				return true;
			}

			bool operator ()(CJsonNull const &_Left, CJsonNull const &_Right)
			{
				return true;
			}
		};

		struct CJsonSpaceshipVisitor
		{
			template <typename tf_CTypeLeft, typename tf_CTypeRight>
			COrdering_Partial operator ()(tf_CTypeLeft const &, tf_CTypeRight const &)
			{
				return COrdering_Partial::unordered;
			}

			COrdering_Partial operator ()(CVoidTag const &_Left, CVoidTag const &_Right)
			{
				return COrdering_Partial::equivalent;
			}

			COrdering_Partial operator ()(CJsonNull const &_Left, CJsonNull const &_Right)
			{
				return COrdering_Partial::equivalent;
			}

			COrdering_Partial operator ()(fp64 const &_Left, fp64 const &_Right)
			{
				return _Left.f_SpaceshipIncludingNan(_Right);
			}

			template <typename tf_CType>
			COrdering_Partial operator ()(tf_CType const &_Left, tf_CType const &_Right)
			{
				return _Left <=> _Right;
			}
		};
	}

	template <typename t_CParent>
	bool TCJsonValue<t_CParent>::operator == (TCJsonValue const &_Right) const
	{
		if (this->f_Type() != _Right.f_Type())
			return false;
		return fg_VisitRet<bool>(NPrivate::CJsonEqualsVisitor(), this->mp_Value, _Right.mp_Value);
	}

	template <typename t_CParent>
	COrdering_Partial TCJsonValue<t_CParent>::operator <=> (TCJsonValue const &_Right) const
	{
		if (auto Result = this->f_Type() <=> _Right.f_Type(); Result != 0)
			return Result;

		return fg_VisitRet<COrdering_Partial>(NPrivate::CJsonSpaceshipVisitor(), this->mp_Value, _Right.mp_Value);
	}

	template <typename t_CParent>
	mint TCJsonValue<t_CParent>::f_GetLen() const
	{
		fp_CheckType(EJsonType_Array);
		return f_Array().f_GetLen();
	}

	template <typename t_CParent>
	void TCJsonValue<t_CParent>::f_SetLen(mint _Len)
	{
		f_Array().f_SetLen(_Len);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::f_Insert() -> CValue &
	{
		return f_Array().f_Insert();
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator [] (mint _Index) const -> CValue const &
	{
		fp_CheckType(EJsonType_Array);
		return f_Array()[_Index];
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::operator [] (mint _Index) -> CValue &
	{
		fp_CheckType(EJsonType_Array);
		return f_Array()[_Index];
	}

	namespace NPrivate
	{
		template <typename tf_CJson>
		NStr::CStr fg_JsonGenerateColored(tf_CJson const &_Json, ch8 const *_pPrettySeparator, NCommandLine::EAnsiEncodingFlag _AnsiFlags, EJsonDialectFlag _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		if constexpr (t_CParent::mc_bHasDefaultTypes)
		{
			if (_AnsiFlags & NCommandLine::EAnsiEncodingFlag_Color)
				return NPrivate::fg_JsonGenerateColored(*this, _pPrettySeparator, _AnsiFlags, _Flags);
		}

		return f_ToString(_pPrettySeparator, _Flags);
	}
}
