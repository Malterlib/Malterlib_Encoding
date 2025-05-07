// Copyright © 2022 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_EJSON.h"
#include "Malterlib_Encoding_JSON_Parse.h"
#include "Malterlib_Encoding_JSON_Generate.h"

namespace NMib::NEncoding::NPrivate
{
	struct CEJSONParseContext : public NJSON::CParseContext
	{
		static constexpr bool mc_bCustomParse = true;
		static constexpr bool mc_bCustomGenerate = true;

		NContainer::TCVector<mint> m_InEscapeParseDepth;

		template <typename tf_CParseContext, typename tf_CJSON, typename tf_CStr>
		static bool fs_GenerateValue(tf_CStr &o_String, tf_CJSON const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags)
		{
			switch (_Value.f_EType())
			{
			case EEJSONType_Date:
				{
					typename tf_CJSON::CJSONType TempObject;
					auto &Date = _Value.f_Date();
					if (!Date.f_IsValid())
						TempObject[CEJSONConstStrings::mc_Date] = nullptr;
					else
						TempObject[CEJSONConstStrings::mc_Date] = NTime::CTimeConvert(Date).f_UnixMilliseconds();

					NJSON::fg_GenerateJSONObject<NJSON::CParseContext>(o_String, TempObject.f_Object(), _Depth, _pPrettySeparator, _Flags);
					return true;
				}
			case EEJSONType_Binary:
				{
					typename tf_CJSON::CJSONType TempObject;
					TempObject[CEJSONConstStrings::mc_Binary] = NEncoding::fg_Base64Encode(_Value.f_Binary());

					NJSON::fg_GenerateJSONObject<NJSON::CParseContext>(o_String, TempObject.f_Object(), _Depth, _pPrettySeparator, _Flags);
					return true;
				}
			case EEJSONType_UserType:
				{
					typename tf_CJSON::CJSONType TempObject;

					auto &UserType = _Value.f_UserType();
					TempObject[CEJSONConstStrings::mc_Type] = UserType.m_Type;
					TempObject[CEJSONConstStrings::mc_Value] = UserType.m_Value;

					NJSON::fg_GenerateJSONObject<NJSON::CParseContext>(o_String, TempObject.f_Object(), _Depth, _pPrettySeparator, _Flags);
					return true;
				}
			case EEJSONType_Object:
				{
					if (_Flags & EJSONDialectFlag(DMibBit(20)))
						return false;

					auto iMember = _Value.f_Object().f_OrderedIterator();
					if (!iMember)
						return false;

					auto &Member = *iMember;
					++iMember;
					auto &Name = Member.f_Name();

					if (!Name.f_StartsWith("$"))
						return false;

					if (!iMember)
					{
						if (!(Name == CEJSONConstStrings::mc_Escape || Name == CEJSONConstStrings::mc_Date || Name == CEJSONConstStrings::mc_Binary))
							return false;
					}
					else
					{
						if
							(
								(Name == CEJSONConstStrings::mc_Type && iMember->f_Name() == CEJSONConstStrings::mc_Value)
								|| (Name == CEJSONConstStrings::mc_Value && iMember->f_Name() == CEJSONConstStrings::mc_Type)
							)
						{
							auto iNext = iMember;
							++iNext;
							if (iNext)
								return false;
						}
						else
							return false;
					}

					if (_pPrettySeparator)
					{
						o_String += "{\n";
						NJSON::fg_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);
					}
					else
						o_String += "{";

					tf_CParseContext::template fs_GenerateKeyString<tf_CParseContext>(o_String, CEJSONConstStrings::mc_Escape);

					if (_pPrettySeparator)
						o_String += ": ";
					else
						o_String += ":";

					NJSON::fg_GenerateJSONValue<tf_CParseContext>(o_String, _Value, _Depth + 1, _pPrettySeparator, _Flags | EJSONDialectFlag(DMibBit(20)));

					if (_pPrettySeparator)
					{
						o_String += "\n";
						NJSON::fg_AddPrefix(o_String, _Depth, _pPrettySeparator);
					}
					o_String += "}";

					return true;
				}
			default:
				break;
			}
			return false;
		}

		template <typename tf_CJSON>
		bool f_ParseValue(tf_CJSON &o_Value, uch8 const *&o_pParse)
		{
			return false;
		}

		template <typename tf_CParseContext>
		void f_ParseKey(NStr::CStr &o_Key, uch8 const *&o_pParse)
		{
			NJSON::CParseContext::f_ParseKey<tf_CParseContext>(o_Key, o_pParse);

			if (o_Key != CEJSONConstStrings::mc_Escape)
				return;

			if (!m_InEscapeParseDepth.f_IsEmpty() && m_InEscapeParseDepth.f_GetLast() == (m_ObjectArrayParseDepth - 1))
				return;

			m_InEscapeParseDepth.f_Insert(m_ObjectArrayParseDepth);
		}

		template <typename tf_CJSON>
		void f_PreParse(tf_CJSON &o_Value, uch8 const *&o_pParse)
		{
		}

		template <typename tf_CJSON>
		void f_PostParse(tf_CJSON &o_Value, uch8 const *&o_pParse)
		{
		}

		template <typename tf_CJSON>
		void f_ParseAfterValue(tf_CJSON &o_Value, uch8 const *&o_pParse)
		{
			if (!o_Value.f_IsObject())
				return;

			auto iMember = o_Value.f_Object().f_OrderedIterator();
			if (!iMember)
				return;

			auto &Member = *iMember;
			++iMember;
			auto &Name = Member.f_Name();
			auto &Value = Member.f_Value();

			if (!iMember)
			{
				if (Name == CEJSONConstStrings::mc_Escape)
				{
					if (m_InEscapeParseDepth.f_IsEmpty())
						return;

					if (m_InEscapeParseDepth.f_GetLast() != (m_ObjectArrayParseDepth + 1))
						return;

					m_InEscapeParseDepth.f_Remove(m_InEscapeParseDepth.f_GetLen() - 1);

					if (Value.f_Type() != EJSONType_Object)
						DMibError("Invalid EJSON: $escape value must be an object");
					auto ValueTemp = fg_Move(Value);
					o_Value = tf_CJSON();
					o_Value = EJSONType_Object;
					for (auto iMember = ValueTemp.f_Object().f_OrderedIterator(); iMember; ++iMember)
						o_Value[iMember->f_Name()] = fg_Move(iMember->f_Value());

					return;
				}
				else if (Name == CEJSONConstStrings::mc_Date)
				{
					if (!m_InEscapeParseDepth.f_IsEmpty() && m_InEscapeParseDepth.f_GetLast() == m_ObjectArrayParseDepth)
						return;

					if (Value.f_IsNull())
					{
						o_Value = NTime::CTime();
						return;
					}
					if (Value.f_Type() != EJSONType_Integer)
						DMibError("Invalid EJSON: $date value must be an integer");

					o_Value = NTime::CTimeConvert::fs_FromUnixMilliseconds(Value.f_Integer());
					return;
				}
				else if (Name == CEJSONConstStrings::mc_Binary)
				{
					if (!m_InEscapeParseDepth.f_IsEmpty() && m_InEscapeParseDepth.f_GetLast() == m_ObjectArrayParseDepth)
						return;

					if (Value.f_Type() != EJSONType_String)
						DMibError("Invalid EJSON: $binary value must be a string");

					NContainer::CByteVector Binary;
					NEncoding::fg_Base64Decode(Value.f_String(), Binary);
					o_Value = fg_Move(Binary);
					return;
				}
			}
			else
			{
				if (!m_InEscapeParseDepth.f_IsEmpty() && m_InEscapeParseDepth.f_GetLast() == m_ObjectArrayParseDepth)
					return;

				if
					(
						(Name == CEJSONConstStrings::mc_Type && iMember->f_Name() == CEJSONConstStrings::mc_Value)
						|| (Name == CEJSONConstStrings::mc_Value && iMember->f_Name() == CEJSONConstStrings::mc_Type)
					)
				{
					++iMember;
					if (!iMember)
					{
						tf_CJSON Temp;
						auto &UserType = Temp.f_UserType();
						auto *pType = o_Value.f_GetMember(CEJSONConstStrings::mc_Type);
						auto *pValue = o_Value.f_GetMember(CEJSONConstStrings::mc_Value);
						DMibCheck(pType);
						DMibCheck(pValue);
						if (pType->f_Type() != EJSONType_String)
							DMibError("Invalid EJSON: $type value must be a string");

						UserType.m_Type = fg_Move(pType->f_String());
						UserType.m_Value = fg_Move(*pValue).f_ToJsonNoConvert();
						o_Value = fg_Move(Temp);
						return;
					}
				}
			}
		}
	};
}

namespace NMib::NEncoding
{
	template <typename t_CParent>
	TCEJSONValue<t_CParent> TCEJSONValue<t_CParent>::fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName, bool _bConvertNullToSpace, EJSONDialectFlag _Flags)
	{
		using namespace NStr;
		TCEJSONValue<t_CParent> Output;
		CStr ToParse = _String;

		uch8 const *pParse = reinterpret_cast<uch8 const *>(ToParse.f_GetStr());

		NPrivate::CEJSONParseContext Context;
		Context.m_pStartParse = pParse;
		Context.m_FileName = _FileName;
		Context.m_bConvertNullToSpace = _bConvertNullToSpace;
		Context.m_Flags = _Flags;

		fg_ParseWhiteSpace(pParse);

		// Any value is allowed at root
		NJSON::fg_ParseJSONValue(Output, pParse, Context);

		fg_ParseWhiteSpace(pParse);

		if (*pParse)
			Context.f_ThrowError("Unexpected character after root value", pParse);

		return fg_Move(Output);
	}
}
