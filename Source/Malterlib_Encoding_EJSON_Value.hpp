#pragma once

#include "Malterlib_Encoding_EJSON.h"
#include <Mib/Encoding/Base64>

namespace NMib::NEncoding
{
	template <typename t_CParent>
	TCEJSONValue<t_CParent>::TCEJSONValue()
	{
	}

	template <typename t_CParent>
	TCEJSONValue<t_CParent>::TCEJSONValue(EEJSONType _Type)
	{
		f_SetEType(_Type);
	}

	template <typename t_CParent>
	TCEJSONValue<t_CParent>::TCEJSONValue(TCEJSONValue const &_Other)
		: TCJSONValue<t_CParent>(static_cast<TCJSONValue<t_CParent> const &>(_Other))
	{
	}

	template <typename t_CParent>
	TCEJSONValue<t_CParent>::TCEJSONValue(TCEJSONValue &_Other)
		: TCJSONValue<t_CParent>(static_cast<TCJSONValue<t_CParent> &>(_Other))
	{
	}

	template <typename t_CParent>
	TCEJSONValue<t_CParent>::TCEJSONValue(TCEJSONValue &&_Other)
		: TCJSONValue<t_CParent>(fg_Move(static_cast<TCJSONValue<t_CParent> &>(_Other)))
	{
	}

	template <typename t_CParent>
	TCEJSONValue<t_CParent>::TCEJSONValue(TCInitializerList<CValue> const &_Init)
		: TCJSONValue<t_CParent>(_Init)
	{
	}

	template <typename t_CParent>
	TCEJSONValue<t_CParent>::TCEJSONValue(TCInitializerList<CKeyValue> const &_Init)
		: TCJSONValue<t_CParent>(_Init)
	{
	}


	template <typename t_CParent>
	TCEJSONValue<t_CParent>::TCEJSONValue(TCEJSONValue const &&_Other)
		: TCJSONValue<t_CParent>(static_cast<TCJSONValue<t_CParent> const &>(_Other))
	{
	}

	template <typename t_CParent>
	auto TCEJSONValue<t_CParent>::operator = (TCEJSONValue const &_Other) -> TCEJSONValue &
	{
		TCJSONValue<t_CParent>::operator = (static_cast<TCJSONValue<t_CParent> const &>(_Other));
		return *this;
	}

	template <typename t_CParent>
	auto TCEJSONValue<t_CParent>::operator = (TCEJSONValue &_Other) -> TCEJSONValue &
	{
		TCJSONValue<t_CParent>::operator = (static_cast<TCJSONValue<t_CParent> &>(_Other));
		return *this;
	}

	template <typename t_CParent>
	auto TCEJSONValue<t_CParent>::operator = (TCEJSONValue &&_Other) -> TCEJSONValue &
	{
		TCJSONValue<t_CParent>::operator = (fg_Move(static_cast<TCJSONValue<t_CParent> &>(_Other)));
		return *this;
	}

	template <typename t_CParent>
	auto TCEJSONValue<t_CParent>::operator = (EEJSONType _Type) -> TCEJSONValue &
	{
		f_SetEType(_Type);
		return *this;
	}

	template <typename t_CParent>
	EEJSONType TCEJSONValue<t_CParent>::f_EType() const
	{
		return (EEJSONType)this->f_Type();
	}

	template <typename t_CParent>
	void TCEJSONValue<t_CParent>::f_SetType(EJSONType _Type)
	{
		switch (EEJSONType(_Type))
		{
		case EEJSONType_Date:
			this->mp_Value.template f_Set<(EJSONType)EEJSONType_Date>();
			break;
		case EEJSONType_Binary:
			this->mp_Value.template f_Set<(EJSONType)EEJSONType_Binary>();
			break;
		case EEJSONType_UserType:
			this->mp_Value.template f_Set<(EJSONType)EEJSONType_UserType>();
			break;
		default:
			TCJSONValue<t_CParent>::f_SetType((EJSONType)_Type);
		}
	}

	template <typename t_CParent>
	void TCEJSONValue<t_CParent>::f_SetEType(EEJSONType _Type)
	{
		f_SetType((EJSONType)_Type);
	}

	template <typename t_CParent>
	bool TCEJSONValue<t_CParent>::f_IsDate() const
	{
		return this->f_EType() == EEJSONType_Date;
	}

	template <typename t_CParent>
	bool TCEJSONValue<t_CParent>::f_IsBinary() const
	{
		return this->f_EType() == EEJSONType_Binary;
	}

	template <typename t_CParent>
	bool TCEJSONValue<t_CParent>::f_IsUserType() const
	{
		return this->f_EType() == EEJSONType_UserType;
	}

	template <typename t_CParent>
	NTime::CTime const &TCEJSONValue<t_CParent>::f_Date() const
	{
		this->fp_CheckType(static_cast<EJSONType>(EEJSONType_Date));
		return this->mp_Value.template f_Get<(EJSONType)EEJSONType_Date>();
	}

	template <typename t_CParent>
	NTime::CTime &TCEJSONValue<t_CParent>::f_Date()
	{
		this->fp_PromoteEType(EEJSONType_Date);
		return this->mp_Value.template f_Get<(EJSONType)EEJSONType_Date>();
	}

	template <typename t_CParent>
	NContainer::CByteVector const &TCEJSONValue<t_CParent>::f_Binary() const
	{
		this->fp_CheckType(static_cast<EJSONType>(EEJSONType_Binary));
		return this->mp_Value.template f_Get<(EJSONType)EEJSONType_Binary>();
	}

	template <typename t_CParent>
	NContainer::CByteVector &TCEJSONValue<t_CParent>::f_Binary()
	{
		this->fp_PromoteEType(EEJSONType_Binary);
		return this->mp_Value.template f_Get<(EJSONType)EEJSONType_Binary>();
	}

	template <typename t_CParent>
	CEJSONUserType const &TCEJSONValue<t_CParent>::f_UserType() const
	{
		this->fp_CheckType(static_cast<EJSONType>(EEJSONType_UserType));
		return this->mp_Value.template f_Get<(EJSONType)EEJSONType_UserType>();
	}

	template <typename t_CParent>
	CEJSONUserType &TCEJSONValue<t_CParent>::f_UserType()
	{
		this->fp_PromoteEType(EEJSONType_UserType);
		return this->mp_Value.template f_Get<(EJSONType)EEJSONType_UserType>();
	}

	template <typename t_CParent>
	auto TCEJSONValue<t_CParent>::f_GetMember(NStr::CStr const &_Name, EEJSONType _Type) const -> typename TCJSONValue<t_CParent>::CValue const *
	{
		return this->f_GetMember(_Name, static_cast<EJSONType>(_Type));
	}

	template <typename t_CParent>
	auto TCEJSONValue<t_CParent>::f_GetMember(NStr::CStr const &_Name, EEJSONType _Type) -> typename TCJSONValue<t_CParent>::CValue *
	{
		return this->f_GetMember(_Name, static_cast<EJSONType>(_Type));
	}

	template <typename t_CParent>
	void TCEJSONValue<t_CParent>::fsp_EscapeObject(CJSON &_Ret, typename TCJSONValue<t_CParent>::CObject const &_Value)
	{
		auto &Escaped = _Ret["$escape"].f_Object();
		for (auto iMember = _Value.f_OrderedIterator(); iMember; ++iMember)
		{
			auto &Member = *iMember;
			Member.f_Value().fp_ToJSON(Escaped.f_CreateMember(Member.f_Name()));
		}
	}

	template <typename t_CParent>
	void TCEJSONValue<t_CParent>::fsp_ToJSON_Object(CJSON &_Ret, typename TCJSONValue<t_CParent>::CObject const &_Value)
	{
		auto &DestObject = _Ret.f_Object();
		bool bFirst = true;
		for (auto iMember = _Value.f_OrderedIterator(); iMember; )
		{
			auto &Member = *iMember;
			++iMember;
			auto &Name = Member.f_Name();

			if (bFirst && Name.f_StartsWith("$"))
			{
				if (!iMember)
				{
					if (Name == "$escape" || Name == "$date" || Name == "$binary")
					{
						fsp_EscapeObject(_Ret, _Value);
						return;
					}
				}
				else
				{
					if
						(
							(Name == "$type" && iMember->f_Name() == "$value")
							|| (Name == "$value" && iMember->f_Name() == "$type")
						)
					{
						auto iNext = iMember;
						++iNext;
						if (!iNext)
						{
							fsp_EscapeObject(_Ret, _Value);
							return;
						}
					}
				}
			}
			bFirst = false;
			Member.f_Value().fp_ToJSON(DestObject.f_CreateMember(Member.f_Name()));
		}
	}

	template <typename t_CParent>
	void TCEJSONValue<t_CParent>::fp_ToJSON(CJSON &_Ret) const
	{
		switch (this->f_EType())
		{
		case EEJSONType_Null:
			_Ret = nullptr;
			break;
		case EEJSONType_String:
			_Ret = this->f_String();
			break;
		case EEJSONType_Integer:
			_Ret = this->f_Integer();
			break;
		case EEJSONType_Float:
			_Ret = this->f_Float();
			break;
		case EEJSONType_Boolean:
			_Ret = this->f_Boolean();
			break;
		case EEJSONType_Object:
			fsp_ToJSON_Object(_Ret, this->f_Object());
			break;
		case EEJSONType_Array:
			{
				_Ret = EJSONType_Array;
				auto &Array = _Ret.f_Array();
				for (auto &Member : this->f_Array())
					Member.fp_ToJSON(Array.f_Insert());
			}
			break;
		case EEJSONType_Date:
			{

				if (!f_Date().f_IsValid())
				{
					_Ret["$date"] = nullptr;
					break;
				}
				_Ret["$date"] = NTime::CTimeConvert(f_Date()).f_UnixMilliseconds();
			}
			break;
		case EEJSONType_Binary:
			{
				_Ret["$binary"] = NEncoding::fg_Base64Encode(f_Binary());
			}
			break;
		case EEJSONType_UserType:
			{
				auto &UserType = f_UserType();
				_Ret["$type"] = UserType.m_Type;
				_Ret["$value"] = UserType.m_Value;
			}
			break;
		}
	}

	template <typename t_CParent>
	CJSON TCEJSONValue<t_CParent>::f_ToJSON() const
	{
		CJSON Return;
		fp_ToJSON(Return);
		return fg_Move(Return);
	}

	template <typename t_CParent>
	void TCEJSONValue<t_CParent>::fsp_FromJSON_Object(TCEJSONValue &_Ret, CJSON::CObject const &_Value)
	{
		{
			auto iMember = _Value.f_OrderedIterator();
			if (!iMember)
			{
				_Ret = EJSONType_Object;
				return;
			}
			{
				auto &Member = *iMember;
				++iMember;
				auto &Name = Member.f_Name();
				auto &Value = Member.f_Value();

				if (!iMember)
				{
					if (Name == "$escape")
					{
						if (Value.f_Type() != EJSONType_Object)
							DMibError("Invalid EJSON: $escape value must be an object");
						for (auto iMember = Value.f_Object().f_OrderedIterator(); iMember; ++iMember)
							CEJSON::fsp_FromJSON(_Ret[iMember->f_Name()], iMember->f_Value());
						return;
					}
					else if (Name == "$date")
					{
						if (Value.f_IsNull())
						{
							_Ret = NTime::CTime();
							return;
						}
						if (Value.f_Type() != EJSONType_Integer)
							DMibError("Invalid EJSON: $date value must be an integer");

						_Ret = NTime::CTimeConvert::fs_FromCreateFromUnixMilliseconds(Value.f_Integer());
						return;
					}
					else if (Name == "$binary")
					{
						if (Value.f_Type() != EJSONType_String)
							DMibError("Invalid EJSON: $binary value must be a string");

						NEncoding::fg_Base64Decode(Value.f_String(), _Ret.f_Binary());
						return;
					}
				}
				else
				{
					if
						(
							(Name == "$type" && iMember->f_Name() == "$value")
							|| (Name == "$value" && iMember->f_Name() == "$type")
						)
					{
						++iMember;
						if (!iMember)
						{
							auto &UserType = _Ret.f_UserType();
							auto *pType = _Value.f_GetMember("$type");
							auto *pValue = _Value.f_GetMember("$value");
							DMibCheck(pType);
							DMibCheck(pValue);
							if (pType->f_Type() != EJSONType_String)
								DMibError("Invalid EJSON: $type value must be a string");

							UserType.m_Type = pType->f_String();
							UserType.m_Value = *pValue;
							return;
						}
					}
				}
			}
		}

		for (auto iMember = _Value.f_OrderedIterator(); iMember; ++iMember)
			CEJSON::fsp_FromJSON(_Ret[iMember->f_Name()], iMember->f_Value());
	}

	template <typename t_CParent>
	void TCEJSONValue<t_CParent>::fsp_FromJSON(TCEJSONValue &_Ret, CJSON const &_From)
	{
		switch (_From.f_Type())
		{
		case EJSONType_Null:
			_Ret = nullptr;
			break;
		case EJSONType_String:
			_Ret = _From.f_String();
			break;
		case EJSONType_Integer:
			_Ret = _From.f_Integer();
			break;
		case EJSONType_Float:
			_Ret = _From.f_Float();
			break;
		case EJSONType_Boolean:
			_Ret = _From.f_Boolean();
			break;
		case EJSONType_Object:
			fsp_FromJSON_Object(_Ret, _From.f_Object());
			break;
		case EJSONType_Array:
			{
				_Ret = EJSONType_Array;
				for (auto &Member : _From.f_Array())
					CEJSON::fsp_FromJSON(_Ret.f_Insert(), Member);
			}
			break;
		}
	}

	template <typename t_CParent>
	auto TCEJSONValue<t_CParent>::fs_FromJSON(CJSON const &_JSON) -> TCEJSONValue
	{
		TCEJSONValue Return;
		fsp_FromJSON(Return, _JSON);
		return Return;
	}

	template <typename t_CParent>
	void TCEJSONValue<t_CParent>::fp_PromoteEType(EEJSONType _Type)
	{
		DMibRequire(this->f_Type() == EJSONType_Invalid || this->f_EType() == _Type);
		if (this->f_EType() == _Type)
			return;
		f_SetEType(_Type);
	}

	template <typename t_CParent>
	TCEJSONValue<t_CParent> TCEJSONValue<t_CParent>::fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName, bool _bConvertNullToSpace)
	{
		CJSON JSON = CJSON::fs_FromString(_String, _FileName, _bConvertNullToSpace);
		return CEJSON::fs_FromJSON(JSON);
	}

	template <typename t_CParent>
	NStr::CStr TCEJSONValue<t_CParent>::f_ToString(ch8 const *_pPrettySeparator, bool _bAllowUndefined) const
	{
		return f_ToJSON().f_ToString(_pPrettySeparator, _bAllowUndefined);
	}

	template <typename t_CParent>
	NStr::CStr TCEJSONValue<t_CParent>::f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, bool _bAllowUndefined) const
	{
		return f_ToJSON().f_ToStringColored(_AnsiFlags, _pPrettySeparator, _bAllowUndefined);
	}
}
