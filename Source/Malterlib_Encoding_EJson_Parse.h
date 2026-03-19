// Copyright © 2022 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_EJson.h"
#include "Malterlib_Encoding_Json_Parse.h"
#include "Malterlib_Encoding_Json_Generate.h"

namespace NMib::NEncoding::NPrivate
{
	struct CEJsonParseContext : public NJson::CParseContext
	{
		static constexpr bool mc_bCustomParse = true;
		static constexpr bool mc_bCustomGenerate = true;

		NContainer::TCVector<umint> m_InEscapeParseDepth;

		template <typename tf_CParseContext, typename tf_CJson, typename tf_CStr>
		static bool fs_GenerateValue(tf_CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags)
		{
			switch (_Value.f_EType())
			{
			case EEJsonType_Date:
				{
					typename tf_CJson::CJsonType TempObject;
					auto &Date = _Value.f_Date();
					if (!Date.f_IsValid())
						TempObject[CEJsonConstStrings::mc_Date] = nullptr;
					else
						TempObject[CEJsonConstStrings::mc_Date] = NTime::CTimeConvert(Date).f_UnixMilliseconds();

					NJson::fg_GenerateJsonObject<NJson::CParseContext>(o_String, TempObject.f_Object(), _Depth, _pPrettySeparator, _Flags);
					return true;
				}
			case EEJsonType_Binary:
				{
					typename tf_CJson::CJsonType TempObject;
					TempObject[CEJsonConstStrings::mc_Binary] = NEncoding::fg_Base64Encode(_Value.f_Binary());

					NJson::fg_GenerateJsonObject<NJson::CParseContext>(o_String, TempObject.f_Object(), _Depth, _pPrettySeparator, _Flags);
					return true;
				}
			case EEJsonType_UserType:
				{
					typename tf_CJson::CJsonType TempObject;

					auto &UserType = _Value.f_UserType();
					TempObject[CEJsonConstStrings::mc_Type] = UserType.m_Type;
					TempObject[CEJsonConstStrings::mc_Value] = UserType.m_Value;

					NJson::fg_GenerateJsonObject<NJson::CParseContext>(o_String, TempObject.f_Object(), _Depth, _pPrettySeparator, _Flags);
					return true;
				}
			case EEJsonType_Object:
				{
					if (_Flags & EJsonDialectFlag(DMibBit(20)))
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
						if (!(Name == CEJsonConstStrings::mc_Escape || Name == CEJsonConstStrings::mc_Date || Name == CEJsonConstStrings::mc_Binary))
							return false;
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
							if (iNext)
								return false;
						}
						else
							return false;
					}

					if (_pPrettySeparator)
					{
						o_String += "{\n";
						NJson::fg_AddPrefix(o_String, _Depth + 1, _pPrettySeparator);
					}
					else
						o_String += "{";

					tf_CParseContext::template fs_GenerateKeyString<tf_CParseContext>(o_String, CEJsonConstStrings::mc_Escape);

					if (_pPrettySeparator)
						o_String += ": ";
					else
						o_String += ":";

					NJson::fg_GenerateJsonValue<tf_CParseContext>(o_String, _Value, _Depth + 1, _pPrettySeparator, _Flags | EJsonDialectFlag(DMibBit(20)));

					if (_pPrettySeparator)
					{
						o_String += "\n";
						NJson::fg_AddPrefix(o_String, _Depth, _pPrettySeparator);
					}
					o_String += "}";

					return true;
				}
			default:
				break;
			}
			return false;
		}

		template <typename tf_CJson>
		bool f_ParseValue(tf_CJson &o_Value, uch8 const *&o_pParse)
		{
			return false;
		}

		template <typename tf_CParseContext>
		void f_ParseKey(NStr::CStr &o_Key, uch8 const *&o_pParse)
		{
			NJson::CParseContext::f_ParseKey<tf_CParseContext>(o_Key, o_pParse);

			if (o_Key != CEJsonConstStrings::mc_Escape)
				return;

			if (!m_InEscapeParseDepth.f_IsEmpty() && m_InEscapeParseDepth.f_GetLast() == (m_ObjectArrayParseDepth - 1))
				return;

			m_InEscapeParseDepth.f_Insert(m_ObjectArrayParseDepth);
		}

		template <typename tf_CJson>
		void f_PreParse(tf_CJson &o_Value, uch8 const *&o_pParse)
		{
		}

		template <typename tf_CJson>
		void f_PostParse(tf_CJson &o_Value, uch8 const *&o_pParse)
		{
		}

		template <typename tf_CJson>
		void f_ParseAfterValue(tf_CJson &o_Value, uch8 const *&o_pParse)
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
				if (Name == CEJsonConstStrings::mc_Escape)
				{
					if (m_InEscapeParseDepth.f_IsEmpty())
						return;

					if (m_InEscapeParseDepth.f_GetLast() != (m_ObjectArrayParseDepth + 1))
						return;

					m_InEscapeParseDepth.f_Remove(m_InEscapeParseDepth.f_GetLen() - 1);

					if (Value.f_Type() != EJsonType_Object)
						DMibError("Invalid EJSON: $escape value must be an object");
					auto ValueTemp = fg_Move(Value);
					o_Value = tf_CJson();
					o_Value = EJsonType_Object;
					for (auto iMember = ValueTemp.f_Object().f_OrderedIterator(); iMember; ++iMember)
						o_Value[iMember->f_Name()] = fg_Move(iMember->f_Value());

					return;
				}
				else if (Name == CEJsonConstStrings::mc_Date)
				{
					if (!m_InEscapeParseDepth.f_IsEmpty() && m_InEscapeParseDepth.f_GetLast() == m_ObjectArrayParseDepth)
						return;

					if (Value.f_IsNull())
					{
						o_Value = NTime::CTime();
						return;
					}
					if (Value.f_Type() != EJsonType_Integer)
						DMibError("Invalid EJSON: $date value must be an integer");

					o_Value = NTime::CTimeConvert::fs_FromUnixMilliseconds(Value.f_Integer());
					return;
				}
				else if (Name == CEJsonConstStrings::mc_Binary)
				{
					if (!m_InEscapeParseDepth.f_IsEmpty() && m_InEscapeParseDepth.f_GetLast() == m_ObjectArrayParseDepth)
						return;

					if (Value.f_Type() != EJsonType_String)
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
						(Name == CEJsonConstStrings::mc_Type && iMember->f_Name() == CEJsonConstStrings::mc_Value)
						|| (Name == CEJsonConstStrings::mc_Value && iMember->f_Name() == CEJsonConstStrings::mc_Type)
					)
				{
					++iMember;
					if (!iMember)
					{
						tf_CJson Temp;
						auto &UserType = Temp.f_UserType();
						auto *pType = o_Value.f_GetMember(CEJsonConstStrings::mc_Type);
						auto *pValue = o_Value.f_GetMember(CEJsonConstStrings::mc_Value);
						DMibCheck(pType);
						DMibCheck(pValue);
						if (pType->f_Type() != EJsonType_String)
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
	TCEJsonValue<t_CParent> TCEJsonValue<t_CParent>::fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName, bool _bConvertNullToSpace, EJsonDialectFlag _Flags)
	{
		using namespace NStr;
		TCEJsonValue<t_CParent> Output;
		CStr ToParse = _String;

		uch8 const *pParse = reinterpret_cast<uch8 const *>(ToParse.f_GetStr());

		NPrivate::CEJsonParseContext Context;
		Context.m_pStartParse = pParse;
		Context.m_FileName = _FileName;
		Context.m_bConvertNullToSpace = _bConvertNullToSpace;
		Context.m_Flags = _Flags;

		fg_ParseWhiteSpace(pParse);

		// Any value is allowed at root
		NJson::fg_ParseJsonValue(Output, pParse, Context);

		fg_ParseWhiteSpace(pParse);

		if (*pParse)
			Context.f_ThrowError("Unexpected character after root value", pParse);

		return fg_Move(Output);
	}
}
