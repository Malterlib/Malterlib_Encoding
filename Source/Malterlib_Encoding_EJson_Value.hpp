// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_EJson.h"
#include <Mib/Encoding/Base64>

namespace NMib::NEncoding
{
	template <typename t_CParent>
	TCEJsonValue<t_CParent>::TCEJsonValue()
	{
	}

	template <typename t_CParent>
	TCEJsonValue<t_CParent>::TCEJsonValue(EEJsonType _Type)
	{
		f_SetEType(_Type);
	}

	template <typename t_CParent>
	TCEJsonValue<t_CParent>::TCEJsonValue(TCEJsonValue const &_Other)
		: TCJsonValue<t_CParent>(static_cast<TCJsonValue<t_CParent> const &>(_Other))
	{
	}

	template <typename t_CParent>
	TCEJsonValue<t_CParent>::TCEJsonValue(TCEJsonValue &_Other)
		: TCJsonValue<t_CParent>(static_cast<TCJsonValue<t_CParent> &>(_Other))
	{
	}

	template <typename t_CParent>
	TCEJsonValue<t_CParent>::TCEJsonValue(TCEJsonValue &&_Other)
		: TCJsonValue<t_CParent>(fg_Move(static_cast<TCJsonValue<t_CParent> &>(_Other)))
	{
	}

	template <typename t_CParent>
	TCEJsonValue<t_CParent>::TCEJsonValue(TCEJsonValue const &&_Other)
		: TCJsonValue<t_CParent>(static_cast<TCJsonValue<t_CParent> const &>(_Other))
	{
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::operator = (TCEJsonValue const &_Other) -> TCEJsonValue &
	{
		TCJsonValue<t_CParent>::operator = (static_cast<TCJsonValue<t_CParent> const &>(_Other));
		return *this;
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::operator = (TCEJsonValue &_Other) -> TCEJsonValue &
	{
		TCJsonValue<t_CParent>::operator = (static_cast<TCJsonValue<t_CParent> &>(_Other));
		return *this;
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::operator = (TCEJsonValue &&_Other) -> TCEJsonValue &
	{
		TCJsonValue<t_CParent>::operator = (fg_Move(static_cast<TCJsonValue<t_CParent> &>(_Other)));
		return *this;
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::operator = (EEJsonType _Type) -> TCEJsonValue &
	{
		f_SetEType(_Type);
		return *this;
	}

	template <typename t_CParent>
	EEJsonType TCEJsonValue<t_CParent>::f_EType() const
	{
		return (EEJsonType)this->f_Type();
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::f_SetType(EJsonType _Type)
	{
		switch (EEJsonType(_Type))
		{
		case EEJsonType_Date:
			this->mp_Value.template f_Set<(EJsonType)EEJsonType_Date>();
			break;
		case EEJsonType_Binary:
			this->mp_Value.template f_Set<(EJsonType)EEJsonType_Binary>();
			break;
		case EEJsonType_UserType:
			this->mp_Value.template f_Set<(EJsonType)EEJsonType_UserType>();
			break;
		default:
			TCJsonValue<t_CParent>::f_SetType((EJsonType)_Type);
		}
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::f_SetEType(EEJsonType _Type)
	{
		f_SetType((EJsonType)_Type);
	}

	template <typename t_CParent>
	bool TCEJsonValue<t_CParent>::f_IsDate() const
	{
		return this->f_EType() == EEJsonType_Date;
	}

	template <typename t_CParent>
	bool TCEJsonValue<t_CParent>::f_IsBinary() const
	{
		return this->f_EType() == EEJsonType_Binary;
	}

	template <typename t_CParent>
	bool TCEJsonValue<t_CParent>::f_IsUserType() const
	{
		return this->f_EType() == EEJsonType_UserType;
	}

	template <typename t_CParent>
	NTime::CTime const &TCEJsonValue<t_CParent>::f_Date() const
	{
		this->fp_CheckType(static_cast<EJsonType>(EEJsonType_Date));
		return this->mp_Value.template f_Get<(EJsonType)EEJsonType_Date>();
	}

	template <typename t_CParent>
	NTime::CTime &TCEJsonValue<t_CParent>::f_Date()
	{
		this->fp_PromoteEType(EEJsonType_Date);
		return this->mp_Value.template f_Get<(EJsonType)EEJsonType_Date>();
	}

	template <typename t_CParent>
	NContainer::CByteVector const &TCEJsonValue<t_CParent>::f_Binary() const
	{
		this->fp_CheckType(static_cast<EJsonType>(EEJsonType_Binary));
		return this->mp_Value.template f_Get<(EJsonType)EEJsonType_Binary>();
	}

	template <typename t_CParent>
	NContainer::CByteVector &TCEJsonValue<t_CParent>::f_Binary()
	{
		this->fp_PromoteEType(EEJsonType_Binary);
		return this->mp_Value.template f_Get<(EJsonType)EEJsonType_Binary>();
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::f_UserType() const -> CUserType const &
	{
		this->fp_CheckType(static_cast<EJsonType>(EEJsonType_UserType));
		return this->mp_Value.template f_Get<(EJsonType)EEJsonType_UserType>();
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::f_UserType() -> CUserType &
	{
		this->fp_PromoteEType(EEJsonType_UserType);
		return this->mp_Value.template f_Get<(EJsonType)EEJsonType_UserType>();
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::f_GetMember(NStr::CStr const &_Name, EEJsonType _Type) const -> typename TCJsonValue<t_CParent>::CValue const *
	{
		return this->f_GetMember(_Name, static_cast<EJsonType>(_Type));
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::f_GetMember(NStr::CStr const &_Name, EEJsonType _Type) -> typename TCJsonValue<t_CParent>::CValue *
	{
		return this->f_GetMember(_Name, static_cast<EJsonType>(_Type));
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_EscapeObject(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject const &_Value)
	{
		auto &Escaped = _Ret[CEJsonConstStrings::mc_Escape].f_Object();
		for (auto iMember = _Value.f_OrderedIterator(); iMember; ++iMember)
		{
			auto &Member = *iMember;
			Member.f_Value().fp_ToJson(Escaped.f_CreateMember(Member.f_Name()));
		}
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_EscapeObject(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject &&_Value)
	{
		auto &Escaped = _Ret[CEJsonConstStrings::mc_Escape].f_Object();
		for (auto iMember = _Value.f_OrderedIterator(); iMember; ++iMember)
		{
			auto &Member = *iMember;
			fg_Move(Member.f_Value()).fp_ToJson(Escaped.f_CreateMember(Member.f_Name()));
		}
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_ToJson_Object(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject const &_Value)
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
					if (Name == CEJsonConstStrings::mc_Escape || Name == CEJsonConstStrings::mc_Date || Name == CEJsonConstStrings::mc_Binary)
					{
						fsp_EscapeObject(_Ret, _Value);
						return;
					}
				}
				else
				{
					if
						(
							(Name == CEJsonConstStrings::mc_Type && iMember->f_Name() == CEJsonConstStrings::mc_Value)
							|| (Name == CEJsonConstStrings::mc_Value && iMember->f_Name() == CEJsonConstStrings::mc_Type)
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
			Member.f_Value().fp_ToJson(DestObject.f_CreateMember(Member.f_Name()));
		}
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_ToJson_Object(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject &&_Value)
	{
		auto &DestObject = _Ret.f_Object();
		bool bFirst = true;
		for (auto iMember = _Value.f_OrderedIterator(); iMember;)
		{
			auto &Member = *iMember;
			++iMember;
			auto &Name = Member.f_Name();

			if (bFirst && Name.f_StartsWith("$"))
			{
				if (!iMember)
				{
					if (Name == CEJsonConstStrings::mc_Escape || Name == CEJsonConstStrings::mc_Date || Name == CEJsonConstStrings::mc_Binary)
					{
						fsp_EscapeObject(_Ret, fg_Move(_Value));
						return;
					}
				}
				else
				{
					if
						(
							(Name == CEJsonConstStrings::mc_Type && iMember->f_Name() == CEJsonConstStrings::mc_Value)
							|| (Name == CEJsonConstStrings::mc_Value && iMember->f_Name() == CEJsonConstStrings::mc_Type)
						)
					{
						auto iNext = iMember;
						++iNext;
						if (!iNext)
						{
							fsp_EscapeObject(_Ret, fg_Move(_Value));
							return;
						}
					}
				}
			}
			bFirst = false;
			fg_Move(Member.f_Value()).fp_ToJson(DestObject.f_CreateMember(Member.f_Name()));
		}
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fp_ToJson(CJsonType &_Ret) const &
	{
		switch (this->f_EType())
		{
		case EEJsonType_Null:
			_Ret = nullptr;
			break;
		case EEJsonType_String:
			_Ret = this->f_String();
			break;
		case EEJsonType_Integer:
			_Ret = this->f_Integer();
			break;
		case EEJsonType_Float:
			_Ret = this->f_Float();
			break;
		case EEJsonType_Boolean:
			_Ret = this->f_Boolean();
			break;
		case EEJsonType_Object:
			fsp_ToJson_Object(_Ret, this->f_Object());
			break;
		case EEJsonType_Array:
			{
				_Ret = EJsonType_Array;
				auto &Array = _Ret.f_Array();
				for (auto &Member : this->f_Array())
					Member.fp_ToJson(Array.f_Insert());
			}
			break;
		case EEJsonType_Date:
			{
				auto &Object = _Ret.f_Object();
				if (!f_Date().f_IsValid())
				{
					Object[CEJsonConstStrings::mc_Date] = nullptr;
					break;
				}
				Object[CEJsonConstStrings::mc_Date] = NTime::CTimeConvert(f_Date()).f_UnixMilliseconds();
			}
			break;
		case EEJsonType_Binary:
			{
				_Ret[CEJsonConstStrings::mc_Binary] = NEncoding::fg_Base64Encode(f_Binary());
			}
			break;
		case EEJsonType_UserType:
			{
				auto &UserType = f_UserType();
				auto &Object = _Ret.f_Object();
				Object[CEJsonConstStrings::mc_Type] = UserType.m_Type;
				Object[CEJsonConstStrings::mc_Value] = UserType.m_Value;
			}
			break;
		case EEJsonType_Invalid:
			break; // Leave as default which is invalid
		}
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fp_ToJson(CJsonType &_Ret) &&
	{
		switch (this->f_EType())
		{
		case EEJsonType_Null:
			_Ret = nullptr;
			break;
		case EEJsonType_String:
			_Ret = fg_Move(this->f_String());
			break;
		case EEJsonType_Integer:
			_Ret = this->f_Integer();
			break;
		case EEJsonType_Float:
			_Ret = this->f_Float();
			break;
		case EEJsonType_Boolean:
			_Ret = this->f_Boolean();
			break;
		case EEJsonType_Object:
			fg_Move(*this).fsp_ToJson_Object(_Ret, fg_Move(this->f_Object()));
			break;
		case EEJsonType_Array:
			{
				_Ret = EJsonType_Array;
				auto &Array = _Ret.f_Array();
				for (auto &Member : this->f_Array())
					fg_Move(Member).fp_ToJson(Array.f_Insert());
			}
			break;
		case EEJsonType_Date:
			{
				auto &Object = _Ret.f_Object();
				if (!f_Date().f_IsValid())
				{
					Object[CEJsonConstStrings::mc_Date] = nullptr;
					break;
				}
				Object[CEJsonConstStrings::mc_Date] = NTime::CTimeConvert(f_Date()).f_UnixMilliseconds();
			}
			break;
		case EEJsonType_Binary:
			{
				_Ret[CEJsonConstStrings::mc_Binary] = NEncoding::fg_Base64Encode(f_Binary());
			}
			break;
		case EEJsonType_UserType:
			{
				auto &UserType = f_UserType();

				auto &Object = _Ret.f_Object();
				Object[CEJsonConstStrings::mc_Type] = fg_Move(UserType.m_Type);
				Object[CEJsonConstStrings::mc_Value] = fg_Move(UserType.m_Value);
			}
			break;
		case EEJsonType_Invalid:
			break; // Leave as default which is invalid
		}
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::f_ToJson() const & -> CJsonType
	{
		CJsonType Return;
		fp_ToJson(Return);
		return Return;
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::f_ToJson() && -> CJsonType
	{
		CJsonType Return;
		fg_Move(*this).fp_ToJson(Return);
		return Return;
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_FromJson_Object(TCEJsonValue &_Ret, typename CJsonType::CObject const &_Value)
	{
		{
			auto iMember = _Value.f_OrderedIterator();
			if (!iMember)
			{
				_Ret = EJsonType_Object;
				return;
			}
			{
				auto &Member = *iMember;
				++iMember;
				auto &Name = Member.f_Name();
				auto &Value = Member.f_Value();

				if (!iMember)
				{
					if (Name == CEJsonConstStrings::mc_Escape)
					{
						if (Value.f_Type() != EJsonType_Object)
							DMibError("Invalid EJSON: $escape value must be an object");
						for (auto iMember = Value.f_Object().f_OrderedIterator(); iMember; ++iMember)
							CValue::fsp_FromJson(_Ret[iMember->f_Name()], iMember->f_Value());
						return;
					}
					else if (Name == CEJsonConstStrings::mc_Date)
					{
						if (Value.f_IsNull())
						{
							_Ret = NTime::CTime();
							return;
						}
						if (Value.f_Type() != EJsonType_Integer)
							DMibError("Invalid EJSON: $date value must be an integer");

						_Ret = NTime::CTimeConvert::fs_FromUnixMilliseconds(Value.f_Integer());
						return;
					}
					else if (Name == CEJsonConstStrings::mc_Binary)
					{
						if (Value.f_Type() != EJsonType_String)
							DMibError("Invalid EJSON: $binary value must be a string");

						NEncoding::fg_Base64Decode(Value.f_String(), _Ret.f_Binary());
						return;
					}
				}
				else
				{
					if
						(
							(Name == CEJsonConstStrings::mc_Type && iMember->f_Name() == CEJsonConstStrings::mc_Value)
							|| (Name == CEJsonConstStrings::mc_Value && iMember->f_Name() == CEJsonConstStrings::mc_Type)
						)
					{
						++iMember;
						if (!iMember)
						{
							auto &UserType = _Ret.f_UserType();
							auto *pType = _Value.f_GetMember(CEJsonConstStrings::mc_Type);
							auto *pValue = _Value.f_GetMember(CEJsonConstStrings::mc_Value);
							DMibCheck(pType);
							DMibCheck(pValue);
							if (pType->f_Type() != EJsonType_String)
								DMibError("Invalid EJSON: $type value must be a string");

							UserType.m_Type = pType->f_String();
							UserType.m_Value = *pValue;
							return;
						}
					}
				}
			}
		}

		auto &RetObject = _Ret.f_Object();
		for (auto iMember = _Value.f_OrderedIterator(); iMember; ++iMember)
			CValue::fsp_FromJson(RetObject[iMember->f_Name()], iMember->f_Value());
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_FromJson_Object(TCEJsonValue &_Ret, typename CJsonType::CObject &&_Value)
	{
		{
			auto iMember = _Value.f_OrderedIterator();
			if (!iMember)
			{
				_Ret = EJsonType_Object;
				return;
			}
			{
				auto &Member = *iMember;
				++iMember;
				auto &Name = Member.f_Name();
				auto &Value = Member.f_Value();

				if (!iMember)
				{
					if (Name == CEJsonConstStrings::mc_Escape)
					{
						if (Value.f_Type() != EJsonType_Object)
							DMibError("Invalid EJSON: $escape value must be an object");
						for (auto iMember = Value.f_Object().f_OrderedIterator(); iMember; ++iMember)
							CValue::fsp_FromJson(_Ret[iMember->f_Name()], fg_Move(iMember->f_Value()));
						return;
					}
					else if (Name == CEJsonConstStrings::mc_Date)
					{
						if (Value.f_IsNull())
						{
							_Ret = NTime::CTime();
							return;
						}
						if (Value.f_Type() != EJsonType_Integer)
							DMibError("Invalid EJSON: $date value must be an integer");

						_Ret = NTime::CTimeConvert::fs_FromUnixMilliseconds(Value.f_Integer());
						return;
					}
					else if (Name == CEJsonConstStrings::mc_Binary)
					{
						if (Value.f_Type() != EJsonType_String)
							DMibError("Invalid EJSON: $binary value must be a string");

						NEncoding::fg_Base64Decode(Value.f_String(), _Ret.f_Binary());
						return;
					}
				}
				else
				{
					if
						(
							(Name == CEJsonConstStrings::mc_Type && iMember->f_Name() == CEJsonConstStrings::mc_Value)
							|| (Name == CEJsonConstStrings::mc_Value && iMember->f_Name() == CEJsonConstStrings::mc_Type)
						)
					{
						++iMember;
						if (!iMember)
						{
							auto &UserType = _Ret.f_UserType();
							auto *pType = _Value.f_GetMember(CEJsonConstStrings::mc_Type);
							auto *pValue = _Value.f_GetMember(CEJsonConstStrings::mc_Value);
							DMibCheck(pType);
							DMibCheck(pValue);
							if (pType->f_Type() != EJsonType_String)
								DMibError("Invalid EJSON: $type value must be a string");

							UserType.m_Type = fg_Move(pType->f_String());
							UserType.m_Value = fg_Move(*pValue);
							return;
						}
					}
				}
			}
		}

		auto &RetObject = _Ret.f_Object();
		for (auto iMember = _Value.f_OrderedIterator(); iMember; ++iMember)
			CValue::fsp_FromJson(RetObject[iMember->f_Name()], fg_Move(iMember->f_Value()));
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_FromJson(TCEJsonValue &_Ret, CJsonType const &_From)
	{
		switch (_From.f_Type())
		{
		case EJsonType_Null:
			_Ret = nullptr;
			break;
		case EJsonType_String:
			_Ret = _From.f_String();
			break;
		case EJsonType_Integer:
			_Ret = _From.f_Integer();
			break;
		case EJsonType_Float:
			_Ret = _From.f_Float();
			break;
		case EJsonType_Boolean:
			_Ret = _From.f_Boolean();
			break;
		case EJsonType_Object:
			fsp_FromJson_Object(_Ret, _From.f_Object());
			break;
		case EJsonType_Array:
			{
				_Ret = EJsonType_Array;
				for (auto &Member : _From.f_Array())
					CValue::fsp_FromJson(_Ret.f_Insert(), Member);
			}
			break;
		case EJsonType_Invalid:
			break; // Default is invalid
		case EJsonType_Max:
			DMibNeverGetHere;
			break;
		}
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_FromJson(TCEJsonValue &_Ret, CJsonType &&_From)
	{
		switch (_From.f_Type())
		{
		case EJsonType_Null:
			_Ret = nullptr;
			break;
		case EJsonType_String:
			_Ret = fg_Move(_From.f_String());
			break;
		case EJsonType_Integer:
			_Ret = _From.f_Integer();
			break;
		case EJsonType_Float:
			_Ret = _From.f_Float();
			break;
		case EJsonType_Boolean:
			_Ret = _From.f_Boolean();
			break;
		case EJsonType_Object:
			fsp_FromJson_Object(_Ret, fg_Move(_From.f_Object()));
			break;
		case EJsonType_Array:
			{
				_Ret = EJsonType_Array;
				for (auto &Member : _From.f_Array())
					CValue::fsp_FromJson(_Ret.f_Insert(), fg_Move(Member));
			}
			break;
		case EJsonType_Invalid:
			break; // Default is invalid
		case EJsonType_Max:
			DMibNeverGetHere;
			break;
		}
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::fs_FromJson(CJsonType const &_Json) -> TCEJsonValue
	{
		TCEJsonValue Return;
		fsp_FromJson(Return, _Json);
		return Return;
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::fs_FromJson(CJsonType &&_Json) -> TCEJsonValue
	{
		TCEJsonValue Return;
		fsp_FromJson(Return, fg_Move(_Json));
		return Return;
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fp_PromoteEType(EEJsonType _Type)
	{
		DMibRequire(this->f_Type() == EJsonType_Invalid || this->f_EType() == _Type);
		if (this->f_EType() == _Type)
			return;
		f_SetEType(_Type);
	}

	template <typename t_CParent>
	NStr::CStr TCEJsonValue<t_CParent>::f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		return f_ToJson().f_ToStringColored(_AnsiFlags, _pPrettySeparator, _Flags);
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::fs_FromJsonNoConvert(CJsonType const &_Json) -> TCEJsonValue
	{
		TCEJsonValue Return;
		fsp_FromJsonNoConvert(Return, _Json);
		return Return;
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::fs_FromJsonNoConvert(CJsonType &&_Json) -> TCEJsonValue
	{
		TCEJsonValue Return;
		fsp_FromJsonNoConvert(Return, fg_Move(_Json));
		return Return;
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::f_ToJsonNoConvert() const & -> CJsonType
	{
		CJsonType Return;
		fp_ToJsonNoConvert(Return);
		return Return;
	}

	template <typename t_CParent>
	auto TCEJsonValue<t_CParent>::f_ToJsonNoConvert() && -> CJsonType
	{
		CJsonType Return;
		fg_Move(*this).fp_ToJsonNoConvert(Return);
		return Return;
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_FromJsonNoConvert_Object(TCEJsonValue &_Ret, typename CJsonType::CObject const &_Value)
	{
		auto &RetObject = _Ret.f_Object();
		for (auto iMember = _Value.f_OrderedIterator(); iMember; ++iMember)
			CValue::fsp_FromJsonNoConvert(RetObject[iMember->f_Name()], iMember->f_Value());
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_FromJsonNoConvert_Object(TCEJsonValue &_Ret, typename CJsonType::CObject &&_Value)
	{
		auto &RetObject = _Ret.f_Object();
		for (auto iMember = _Value.f_OrderedIterator(); iMember; ++iMember)
			CValue::fsp_FromJsonNoConvert(RetObject[iMember->f_Name()], fg_Move(iMember->f_Value()));
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_FromJsonNoConvert(TCEJsonValue &_Ret, CJsonType const &_From)
	{
		switch (_From.f_Type())
		{
		case EJsonType_Null:
			_Ret = nullptr;
			break;
		case EJsonType_String:
			_Ret = _From.f_String();
			break;
		case EJsonType_Integer:
			_Ret = _From.f_Integer();
			break;
		case EJsonType_Float:
			_Ret = _From.f_Float();
			break;
		case EJsonType_Boolean:
			_Ret = _From.f_Boolean();
			break;
		case EJsonType_Object:
			fsp_FromJsonNoConvert_Object(_Ret, _From.f_Object());
			break;
		case EJsonType_Array:
			{
				_Ret = EJsonType_Array;
				for (auto &Member : _From.f_Array())
					CValue::fsp_FromJsonNoConvert(_Ret.f_Insert(), Member);
			}
			break;
		case EJsonType_Invalid:
			break; // Default is invalid
		case EJsonType_Max:
			DMibNeverGetHere;
			break;
		}
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_FromJsonNoConvert(TCEJsonValue &_Ret, CJsonType &&_From)
	{
		switch (_From.f_Type())
		{
		case EJsonType_Null:
			_Ret = nullptr;
			break;
		case EJsonType_String:
			_Ret = fg_Move(_From.f_String());
			break;
		case EJsonType_Integer:
			_Ret = _From.f_Integer();
			break;
		case EJsonType_Float:
			_Ret = _From.f_Float();
			break;
		case EJsonType_Boolean:
			_Ret = _From.f_Boolean();
			break;
		case EJsonType_Object:
			fsp_FromJsonNoConvert_Object(_Ret, fg_Move(_From.f_Object()));
			break;
		case EJsonType_Array:
			{
				_Ret = EJsonType_Array;
				for (auto &Member : _From.f_Array())
					CValue::fsp_FromJsonNoConvert(_Ret.f_Insert(), fg_Move(Member));
			}
			break;
		case EJsonType_Invalid:
			break; // Default is invalid
		case EJsonType_Max:
			DMibNeverGetHere;
			break;
		}
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_ToJsonNoConvert_Object(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject const &_Value)
	{
		auto &DestObject = _Ret.f_Object();
		for (auto iMember = _Value.f_OrderedIterator(); iMember; )
		{
			auto &Member = *iMember;
			++iMember;
			Member.f_Value().fp_ToJsonNoConvert(DestObject.f_CreateMember(Member.f_Name()));
		}
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fsp_ToJsonNoConvert_Object(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject &&_Value)
	{
		auto &DestObject = _Ret.f_Object();
		for (auto iMember = _Value.f_OrderedIterator(); iMember;)
		{
			auto &Member = *iMember;
			++iMember;
			fg_Move(Member.f_Value()).fp_ToJsonNoConvert(DestObject.f_CreateMember(Member.f_Name()));
		}
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fp_ToJsonNoConvert(CJsonType &_Ret) const &
	{
		switch (this->f_EType())
		{
		case EEJsonType_Null:
			_Ret = nullptr;
			break;
		case EEJsonType_String:
			_Ret = this->f_String();
			break;
		case EEJsonType_Integer:
			_Ret = this->f_Integer();
			break;
		case EEJsonType_Float:
			_Ret = this->f_Float();
			break;
		case EEJsonType_Boolean:
			_Ret = this->f_Boolean();
			break;
		case EEJsonType_Object:
			fsp_ToJsonNoConvert_Object(_Ret, this->f_Object());
			break;
		case EEJsonType_Array:
			{
				_Ret = EJsonType_Array;
				auto &Array = _Ret.f_Array();
				for (auto &Member : this->f_Array())
					Member.fp_ToJsonNoConvert(Array.f_Insert());
			}
			break;
		case EEJsonType_Date:
		case EEJsonType_Binary:
		case EEJsonType_UserType:
			DMibError("EJSON contains data that cannot be represented as JSON without conversion");
			break;
		case EEJsonType_Invalid:
			break; // Leave as default which is invalid
		}
	}

	template <typename t_CParent>
	void TCEJsonValue<t_CParent>::fp_ToJsonNoConvert(CJsonType &_Ret) &&
	{
		switch (this->f_EType())
		{
		case EEJsonType_Null:
			_Ret = nullptr;
			break;
		case EEJsonType_String:
			_Ret = fg_Move(this->f_String());
			break;
		case EEJsonType_Integer:
			_Ret = this->f_Integer();
			break;
		case EEJsonType_Float:
			_Ret = this->f_Float();
			break;
		case EEJsonType_Boolean:
			_Ret = this->f_Boolean();
			break;
		case EEJsonType_Object:
			fg_Move(*this).fsp_ToJsonNoConvert_Object(_Ret, fg_Move(this->f_Object()));
			break;
		case EEJsonType_Array:
			{
				_Ret = EJsonType_Array;
				auto &Array = _Ret.f_Array();
				for (auto &Member : this->f_Array())
					fg_Move(Member).fp_ToJsonNoConvert(Array.f_Insert());
			}
			break;
		case EEJsonType_Date:
		case EEJsonType_Binary:
		case EEJsonType_UserType:
			DMibError("EJSON contains data that cannot be represented as JSON without conversion");
			break;
		case EEJsonType_Invalid:
			break; // Leave as default which is invalid
		}
	}

	template <typename t_CParent>
	template <typename tf_CParent>
	auto TCEJsonValue<t_CParent>::fs_FromCompatible(TCEJsonValue<tf_CParent> const &_Other) -> TCEJsonValue
	{
		return TCEJsonValue(_Other);
	}

	template <typename t_CParent>
	template <typename tf_CParent>
	auto TCEJsonValue<t_CParent>::fs_FromCompatible(TCEJsonValue<tf_CParent> &&_Other) -> TCEJsonValue
	{
		return TCEJsonValue(_Other);
	}

	template <typename t_CParent>
	template <typename tf_CParent>
	auto TCEJsonValue<t_CParent>::fs_FromCompatible(TCEJsonValue<tf_CParent> const &&_Other) -> TCEJsonValue
	{
		return TCEJsonValue(_Other);
	}

	template <typename t_CParent>
	template <typename tf_CParent>
	TCEJsonValue<t_CParent>::TCEJsonValue(TCEJsonValue<tf_CParent> const &_Other)
		: TCJsonValue<t_CParent>(static_cast<TCJsonValue<tf_CParent> const &>(_Other))
	{
	}

	template <typename t_CParent>
	template <typename tf_CParent>
	TCEJsonValue<t_CParent>::TCEJsonValue(TCEJsonValue<tf_CParent> &&_Other)
		: TCJsonValue<t_CParent>(static_cast<TCJsonValue<tf_CParent> &&>(_Other))
	{
	}

	template <typename t_CParent>
	template <typename tf_CParent>
	TCEJsonValue<t_CParent>::TCEJsonValue(TCEJsonValue<tf_CParent> const &&_Other)
		: TCJsonValue<t_CParent>(static_cast<TCJsonValue<tf_CParent> const &>(_Other))
	{
	}

}
