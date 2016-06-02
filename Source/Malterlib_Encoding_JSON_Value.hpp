#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib
{
	namespace NEncoding
	{

		template <typename t_CParent>
		TCJSONValue<t_CParent>::TCJSONValue()
		{
		}

		template <typename t_CParent>
		TCJSONValue<t_CParent>::TCJSONValue(TCJSONValue const &_Other)
			: t_CParent(static_cast<t_CParent const &>(_Other))
		{
		}

		template <typename t_CParent>
		TCJSONValue<t_CParent>::TCJSONValue(TCJSONValue &_Other)
			: t_CParent(static_cast<t_CParent &>(_Other))
		{
		}

		template <typename t_CParent>
		TCJSONValue<t_CParent>::TCJSONValue(TCJSONValue &&_Other)
			: t_CParent(fg_Move(static_cast<t_CParent &>(_Other)))
		{
		}

		template <typename t_CParent>
		TCJSONValue<t_CParent>::TCJSONValue(TCJSONValue const &&_Other)
			: t_CParent(static_cast<t_CParent const &>(_Other))
		{
		}
		
		template <typename t_CParent>
		TCJSONValue<t_CParent>::TCJSONValue(TCInitializerList<CValue> const &_Init)
		{
			auto &Array = f_Array();
			for (auto &Value : _Init)
				Array.f_Insert(Value);
		}
		
		template <typename t_CParent>
		TCJSONValue<t_CParent>::TCJSONValue(TCInitializerList<CKeyValue> const &_Init)
		{
			auto &Object = f_Object();
			for (auto &Value : _Init)
				Object.f_CreateMember(Value.m_Key) = Value.m_Value;
		}		

		template <typename t_CParent>
		TCJSONValue<t_CParent>::TCJSONValue(EJSONType _Type)
		{
			f_SetType(_Type);
		}

		template <typename t_CParent>
		TCJSONValue<t_CParent>::TCJSONValue(ch8 const *_pValue)
			: t_CParent(_pValue)
		{
		}
		
		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::operator = (ch8 const *_pValue) -> CValue &
		{
			this->mp_Value = _pValue;
			return static_cast<CValue &>(*this);
		}
		
		template <typename t_CParent>
		EJSONType TCJSONValue<t_CParent>::f_Type() const
		{
			return (EJSONType)this->mp_Value.f_GetTypeID();
		}

		template <typename t_CParent>
		void TCJSONValue<t_CParent>::f_SetType(EJSONType _Type)
		{
			if (f_Type() == _Type)
				return;
			switch (_Type)
			{
			case EJSONType_Invalid:
				this->mp_Value.template f_Set<EJSONType_Invalid>();
				break;
			case EJSONType_Null:
				this->mp_Value.template f_Set<EJSONType_Null>();
				break;
			case EJSONType_String:
				this->mp_Value.template f_Set<EJSONType_String>();
				break;
			case EJSONType_Integer:
				this->mp_Value.template f_Set<EJSONType_Integer>();
				break;
			case EJSONType_Float:
				this->mp_Value.template f_Set<EJSONType_Float>();
				break;
			case EJSONType_Boolean:
				this->mp_Value.template f_Set<EJSONType_Boolean>();
				break;
			case EJSONType_Object:
				this->mp_Value.template f_Set<EJSONType_Object>();
				break;
			case EJSONType_Array:
				this->mp_Value.template f_Set<EJSONType_Array>();
				break;
			default:
				DMibNeverGetHere;
				break;
			}
		}

		template <typename t_CParent>
		bool TCJSONValue<t_CParent>::f_IsValid() const
		{
			return this->f_Type() != EJSONType_Invalid;
		}
		
		template <typename t_CParent>
		bool TCJSONValue<t_CParent>::f_IsNull() const
		{
			return this->f_Type() == EJSONType_Null;
		}

		template <typename t_CParent>
		bool TCJSONValue<t_CParent>::f_IsString() const
		{
			return this->f_Type() == EJSONType_String;
		}

		template <typename t_CParent>
		bool TCJSONValue<t_CParent>::f_IsInteger() const
		{
			return this->f_Type() == EJSONType_Integer;
		}

		template <typename t_CParent>
		bool TCJSONValue<t_CParent>::f_IsFloat() const
		{
			return this->f_Type() == EJSONType_Float;
		}

		template <typename t_CParent>
		bool TCJSONValue<t_CParent>::f_IsBoolean() const
		{
			return this->f_Type() == EJSONType_Boolean;
		}

		template <typename t_CParent>
		bool TCJSONValue<t_CParent>::f_IsObject() const
		{
			return this->f_Type() == EJSONType_Object;
		}

		template <typename t_CParent>
		bool TCJSONValue<t_CParent>::f_IsArray() const
		{
			return this->f_Type() == EJSONType_Array;
		}
		
		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::fs_FromString(NStr::CStr const & _String, NStr::CStr const & _FileName) -> TCJSONValue
		{
			return TCJSONValue();
		}

		template <typename t_CParent>
		NStr::CStr TCJSONValue<t_CParent>::f_ToString(ch8 const * _pPrettySeparator) const
		{
			return NStr::CStr();
		}

		template <typename t_CParent>
		void TCJSONValue<t_CParent>::fp_PromoteType(EJSONType _Type)
		{
			DMibRequire(this->f_Type() == EJSONType_Invalid || this->f_Type() == _Type);
			if (this->f_Type() == _Type)
				return;
			f_SetType(_Type);
		}
		
		template <typename t_CParent>
		void TCJSONValue<t_CParent>::fp_CheckType(EJSONType _Type) const
		{
			if (this->f_Type() != _Type)
				DMibError("Trying to access by wrong type");
		}		
		
		template <typename t_CParent>
		NStr::CStr const &TCJSONValue<t_CParent>::f_String() const
		{
			fp_CheckType(EJSONType_String);
			return this->mp_Value.template f_Get<2>();
		}

		template <typename t_CParent>
		NStr::CStr &TCJSONValue<t_CParent>::f_String()
		{
			fp_PromoteType(EJSONType_String);
			return this->mp_Value.template f_Get<2>();
		}

		template <typename t_CParent>
		int64 const &TCJSONValue<t_CParent>::f_Integer() const
		{
			fp_CheckType(EJSONType_Integer);
			return this->mp_Value.template f_Get<3>();
		}

		template <typename t_CParent>
		int64 &TCJSONValue<t_CParent>::f_Integer()
		{
			fp_PromoteType(EJSONType_Integer);
			return this->mp_Value.template f_Get<3>();
		}

		template <typename t_CParent>
		fp64 const &TCJSONValue<t_CParent>::f_Float() const
		{
			fp_CheckType(EJSONType_Float);
			return this->mp_Value.template f_Get<4>();
		}

		template <typename t_CParent>
		fp64 &TCJSONValue<t_CParent>::f_Float()
		{
			fp_PromoteType(EJSONType_Float);
			return this->mp_Value.template f_Get<4>();
		}

		template <typename t_CParent>
		bool const &TCJSONValue<t_CParent>::f_Boolean() const
		{
			fp_CheckType(EJSONType_Boolean);
			return this->mp_Value.template f_Get<5>();
		}

		template <typename t_CParent>
		bool &TCJSONValue<t_CParent>::f_Boolean()
		{
			fp_PromoteType(EJSONType_Boolean);
			return this->mp_Value.template f_Get<5>();
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::f_Object() const -> TCJSONObject<CValue> const &
		{
			fp_CheckType(EJSONType_Object);
			return this->mp_Value.template f_Get<6>();
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::f_Object() -> TCJSONObject<CValue> &
		{
			fp_PromoteType(EJSONType_Object);
			return this->mp_Value.template f_Get<6>();
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::f_Array() const -> typename NContainer::TCVector<CValue> const &
		{
			fp_CheckType(EJSONType_Array);
			return this->mp_Value.template f_Get<7>();
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::f_Array() -> typename NContainer::TCVector<CValue> &
		{
			fp_PromoteType(EJSONType_Array);
			return this->mp_Value.template f_Get<7>();
		}

		template <typename t_CParent>
		NStr::CStr TCJSONValue<t_CParent>::f_AsString() const
		{
			switch (f_Type())
			{
			case EJSONType_Null:
				return "null";
			case EJSONType_String:
				return f_String();
			case EJSONType_Integer:
				return NStr::CStr::fs_ToStr(f_Integer());
			case EJSONType_Float:
				return NStr::CStr::fs_ToStr(f_Float());
			case EJSONType_Boolean:
				return f_Boolean() ? "true" : "false";
			case EJSONType_Object:
				return static_cast<CValue const &>(*this).f_ToString();
			case EJSONType_Array:
				return static_cast<CValue const &>(*this).f_ToString();
			default:
				DMibError("JSON type cannot be converted to string");
			}
		}
		
		template <typename t_CParent>
		int64 TCJSONValue<t_CParent>::f_AsInteger() const
		{
			switch (f_Type())
			{
			case EJSONType_String:
				return f_String().f_ToInt(int64(0));
			case EJSONType_Integer:
				return f_Integer();
			case EJSONType_Float:
				return f_Float().f_ToIntRound();
			case EJSONType_Boolean:
				return f_Boolean() ? 1 : 0;
			default:
				DMibError("JSON type cannot be converted to integer");
			}
		}
		
		template <typename t_CParent>
		fp64 TCJSONValue<t_CParent>::f_AsFloat() const
		{
			switch (f_Type())
			{
			case EJSONType_String:
				return f_String().f_ToFloat(fp64::fs_SNan());
			case EJSONType_Integer:
				return f_Integer();
			case EJSONType_Float:
				return f_Float();
			case EJSONType_Boolean:
				return f_Boolean() ? 1.0 : 0.0;
			default:
				DMibError("JSON type cannot be converted to float");
			}
		}
		
		template <typename t_CParent>
		bool TCJSONValue<t_CParent>::f_AsBoolean() const
		{
			switch (f_Type())
			{
			case EJSONType_String:
				{
					auto &String = f_String();
					return String.f_CmpNoCase("true") == 0 || String.f_ToInt(0) != 0;
				}
			case EJSONType_Integer:
				return f_Integer() != 0;
			case EJSONType_Float:
				return f_Float() != 0.0;
			case EJSONType_Boolean:
				return f_Boolean();
			default:
				DMibError("JSON type cannot be converted to boolean");
			}
		}		

		template <typename t_CParent>
		NStr::CStr TCJSONValue<t_CParent>::f_AsString(NStr::CStr const &_Default) const
		{
			switch (f_Type())
			{
			case EJSONType_Null:
				return "null";
			case EJSONType_String:
				return f_String();
			case EJSONType_Integer:
				return NStr::CStr::fs_ToStr(f_Integer());
			case EJSONType_Float:
				return NStr::CStr::fs_ToStr(f_Float());
			case EJSONType_Boolean:
				return f_Boolean() ? "true" : "false";
			case EJSONType_Object:
				return static_cast<CValue const &>(*this).f_ToString();
			case EJSONType_Array:
				return static_cast<CValue const &>(*this).f_ToString();
			default:
				return _Default;
			}
		}
		
		template <typename t_CParent>
		int64 TCJSONValue<t_CParent>::f_AsInteger(int64 _Default) const
		{
			switch (f_Type())
			{
			case EJSONType_String:
				return f_String().f_ToInt(_Default);
			case EJSONType_Integer:
				return f_Integer();
			case EJSONType_Float:
				return f_Float().f_ToIntRound();
			case EJSONType_Boolean:
				return f_Boolean() ? 1 : 0;
			default:
				return _Default;
			}
		}
		
		template <typename t_CParent>
		fp64 TCJSONValue<t_CParent>::f_AsFloat(fp64 _Default) const
		{
			switch (f_Type())
			{
			case EJSONType_String:
				return f_String().f_ToFloat(_Default);
			case EJSONType_Integer:
				return f_Integer();
			case EJSONType_Float:
				return f_Float();
			case EJSONType_Boolean:
				return f_Boolean() ? 1.0 : 0.0;
			default:
				return _Default;
			}
		}
		
		template <typename t_CParent>
		bool TCJSONValue<t_CParent>::f_AsBoolean(bool _Default) const
		{
			switch (f_Type())
			{
			case EJSONType_String:
				{
					auto &String = f_String();
					return String.f_CmpNoCase("true") == 0 || String.f_ToInt(0) != 0;
				}
			case EJSONType_Integer:
				return f_Integer() != 0;
			case EJSONType_Float:
				return f_Float() != 0.0;
			case EJSONType_Boolean:
				return f_Boolean();
			default:
				return _Default;
			}
		}
		
		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::operator = (TCJSONValue const &_Value) -> CValue &
		{
			this->mp_Value = _Value.mp_Value;
			return static_cast<CValue &>(*this);
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::operator = (TCJSONValue &_Value) -> CValue &
		{
			this->mp_Value = _Value.mp_Value;
			return static_cast<CValue &>(*this);
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::operator = (TCJSONValue &&_Value) -> CValue &
		{
			this->mp_Value = fg_Move(_Value.mp_Value);
			return static_cast<CValue &>(*this);
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::operator = (pfp64 _Value) -> CValue &
		{
			this->mp_Value = fp64(_Value);
			return static_cast<CValue &>(*this);
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::operator = (pfp32 _Value) -> CValue &
		{
			this->mp_Value = fp64(_Value);
			return static_cast<CValue &>(*this);
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::operator = (fp32 _Value) -> CValue &
		{
			this->mp_Value = fp64(_Value);
			return static_cast<CValue &>(*this);
		}
		
		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::operator = (EJSONType _Type) -> CValue &
		{
			this->f_SetType(_Type);
			return static_cast<CValue &>(*this);
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::f_GetMember(NStr::CStr const &_Name) const -> CValue const *
		{
			if (!f_IsObject())
				return nullptr;

			auto pMember = f_Object().f_GetMember(_Name);
			if (pMember)
				return pMember;
			return nullptr;
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::f_GetMember(NStr::CStr const &_Name) -> CValue *
		{
			if (!f_IsObject())
				return nullptr;

			auto pMember = f_Object().f_GetMember(_Name);
			if (pMember)
				return pMember;
			return nullptr;
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::f_GetMember(NStr::CStr const &_Name, EJSONType _Type) const -> CValue const *
		{
			if (!f_IsObject())
				return nullptr;

			auto pMember = f_Object().f_GetMember(_Name);
			if (pMember)
				return pMember;
			return nullptr;
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::f_GetMember(NStr::CStr const &_Name, EJSONType _Type) -> CValue *
		{
			if (!f_IsObject())
				return nullptr;

			auto pMember = f_Object().f_GetMember(_Name, _Type);
			if (pMember)
				return pMember;
			return nullptr;
		}
		
		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::operator [](NStr::CStr const &_Name) -> CValue &
		{
			return f_Object().f_CreateMember(_Name);
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::operator [] (NStr::CStr const &_Name) const -> CValue const &
		{
			if (!f_IsObject())
				DMibError("Not an object");

			auto pMember = f_Object().f_GetMember(_Name);
			if (!pMember)
				DMibError(fg_Format("Member '{}' not found", _Name));

			return *pMember;
		}	

		template <typename t_CParent>
		void TCJSONValue<t_CParent>::f_RemoveMember(NStr::CStr const &_Name)
		{
			return f_Object().f_RemoveMember(_Name);
		}
		
		namespace NPrivate
		{
			struct CJSONEqualsVisitor
			{
				template <typename tf_CTypeLeft, typename tf_CTypeRight>
				bool operator ()(tf_CTypeLeft const &, tf_CTypeRight const &)
				{
					return false;
				}

				bool operator ()(CVoidTag const &_Left, CVoidTag const &_Right)
				{
					return true;
				}

				bool operator ()(CNullPtr const &_Left, CNullPtr const &_Right)
				{
					return true;
				}

				template <typename tf_CType>
				bool operator ()(tf_CType const &_Left, tf_CType const &_Right)
				{
					return _Left == _Right;
				}
			};

			struct CJSONLessThanVisitor
			{
				template <typename tf_CTypeLeft, typename tf_CTypeRight>
				bool operator ()(tf_CTypeLeft const &, tf_CTypeRight const &)
				{
					return false;
				}

				bool operator ()(CVoidTag const &_Left, CVoidTag const &_Right)
				{
					return false;
				}

				bool operator ()(CNullPtr const &_Left, CNullPtr const &_Right)
				{
					return false;
				}

				template <typename tf_CType>
				bool operator ()(tf_CType const &_Left, tf_CType const &_Right)
				{
					return _Left < _Right;
				}
			};
		}

		template <typename t_CParent>
		bool TCJSONValue<t_CParent>::operator == (TCJSONValue const &_Right) const
		{
			if (this->f_Type() != _Right.f_Type())
				return false;
			return fg_VisitRet<bool>(NPrivate::CJSONEqualsVisitor(), this->mp_Value, _Right.mp_Value);
		}

		template <typename t_CParent>
		bool TCJSONValue<t_CParent>::operator < (TCJSONValue const &_Right) const
		{
			if (this->f_Type() < _Right.f_Type())
				return true;
			else if (this->f_Type() > _Right.f_Type())
				return false;
			return fg_VisitRet<bool>(NPrivate::CJSONLessThanVisitor(), this->mp_Value, _Right.mp_Value);
		}

		template <typename t_CParent>
		mint TCJSONValue<t_CParent>::f_GetLen() const
		{
			fp_CheckType(EJSONType_Array);
			return f_Array().f_GetLen();
		}

		template <typename t_CParent>
		void TCJSONValue<t_CParent>::f_SetLen(mint _Len)
		{
			f_Array().f_SetLen(_Len);
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::f_Insert() -> CValue &
		{
			return f_Array().f_Insert();
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::operator [](mint _Index) const -> CValue const &
		{
			fp_CheckType(EJSONType_Array);
			return f_Array()[_Index];
		}

		template <typename t_CParent>
		auto TCJSONValue<t_CParent>::operator [](mint _Index) -> CValue &
		{
			fp_CheckType(EJSONType_Array);
			return f_Array()[_Index];
		}
	}
}

