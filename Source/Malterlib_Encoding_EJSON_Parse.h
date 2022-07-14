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

		template <typename tf_CParseContext, typename tf_CStr>
		static bool fs_GenerateValue(tf_CStr &o_String, NEncoding::CEJSON const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags)
		{
			switch (_Value.f_EType())
			{
			case EEJSONType_Date:
				{
					CJSON TempObject;
					auto &Date = _Value.f_Date();
					if (!Date.f_IsValid())
						TempObject["$date"] = nullptr;
					else
						TempObject["$date"] = NTime::CTimeConvert(Date).f_UnixMilliseconds();

					NJSON::fg_GenerateJSONObject<NJSON::CParseContext>(o_String, TempObject, _Depth, _pPrettySeparator, _Flags);
					return true;
				}
			case EEJSONType_Binary:
				{
					CJSON TempObject;
					TempObject["$binary"] = NEncoding::fg_Base64Encode(_Value.f_Binary());

					NJSON::fg_GenerateJSONObject<NJSON::CParseContext>(o_String, TempObject, _Depth, _pPrettySeparator, _Flags);
					return true;
				}
			case EEJSONType_UserType:
				{
					CJSON TempObject;

					auto &UserType = _Value.f_UserType();
					TempObject["$type"] = UserType.m_Type;
					TempObject["$value"] = UserType.m_Value;

					NJSON::fg_GenerateJSONObject<NJSON::CParseContext>(o_String, TempObject, _Depth, _pPrettySeparator, _Flags);
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
						if (!(Name == "$escape" || Name == "$date" || Name == "$binary"))
							return false;
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

					tf_CParseContext::template fs_GenerateKeyString<tf_CParseContext>(o_String, "$escape");

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

		bool f_ParseValue(NEncoding::CEJSON &o_Value, uch8 const *&o_pParse)
		{
			return false;
		}

		template <typename tf_CParseContext>
		void f_ParseKey(NStr::CStr &o_Key, uch8 const *&o_pParse)
		{
			NJSON::CParseContext::f_ParseKey<tf_CParseContext>(o_Key, o_pParse);

			if (o_Key != "$escape")
				return;

			if (!m_InEscapeParseDepth.f_IsEmpty() && m_InEscapeParseDepth.f_GetLast() == (m_ObjectArrayParseDepth - 1))
				return;

			m_InEscapeParseDepth.f_Insert(m_ObjectArrayParseDepth);
		}

		void f_ParseAfterValue(NEncoding::CEJSON &o_Value, uch8 const *&o_pParse)
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
				if (Name == "$escape")
				{
					if (m_InEscapeParseDepth.f_IsEmpty())
						return;

					if (m_InEscapeParseDepth.f_GetLast() != (m_ObjectArrayParseDepth + 1))
						return;

					m_InEscapeParseDepth.f_Remove(m_InEscapeParseDepth.f_GetLen() - 1);

					if (Value.f_Type() != EJSONType_Object)
						DMibError("Invalid EJSON: $escape value must be an object");
					auto ValueTemp = fg_Move(Value);
					o_Value = NEncoding::CEJSON();
					o_Value = EJSONType_Object;
					for (auto iMember = ValueTemp.f_Object().f_OrderedIterator(); iMember; ++iMember)
						o_Value[iMember->f_Name()] = fg_Move(iMember->f_Value());

					return;
				}
				else if (Name == "$date")
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
				else if (Name == "$binary")
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
						(Name == "$type" && iMember->f_Name() == "$value")
						|| (Name == "$value" && iMember->f_Name() == "$type")
					)
				{
					++iMember;
					if (!iMember)
					{
						NEncoding::CEJSON Temp;
						auto &UserType = Temp.f_UserType();
						auto *pType = o_Value.f_GetMember("$type");
						auto *pValue = o_Value.f_GetMember("$value");
						DMibCheck(pType);
						DMibCheck(pValue);
						if (pType->f_Type() != EJSONType_String)
							DMibError("Invalid EJSON: $type value must be a string");

						UserType.m_Type = fg_Move(pType->f_String());
						UserType.m_Value = fg_Move(*pValue).f_ToJSONNoConvert();
						o_Value = fg_Move(Temp);
						return;
					}
				}
			}
		}
	};
}
