// Copyright © 2023 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_Json.h"

#include <Mib/Storage/Indirection>

#include <Mib/CommandLine/AnsiEncoding>

namespace NMib::NEncoding
{
	enum EEJsonType : uint8
	{
		EEJsonType_Invalid = EJsonType_Invalid
		, EEJsonType_Null = EJsonType_Null
		, EEJsonType_String = EJsonType_String
		, EEJsonType_Integer = EJsonType_Integer
		, EEJsonType_Float = EJsonType_Float
		, EEJsonType_Boolean = EJsonType_Boolean
		, EEJsonType_Object = EJsonType_Object
		, EEJsonType_Array = EJsonType_Array
		, EEJsonType_Date = EJsonType_Max
		, EEJsonType_Binary
		, EEJsonType_UserType
	};

	struct CEJsonUserTypeSorted;

	struct CEJsonUserTypeOrdered final
	{
		CEJsonUserTypeOrdered();
		CEJsonUserTypeOrdered(CEJsonUserTypeOrdered const &_Other) = default;
		CEJsonUserTypeOrdered(CEJsonUserTypeOrdered &&_Other) = default;
		CEJsonUserTypeOrdered(CEJsonUserTypeSorted const &_Other);
		CEJsonUserTypeOrdered(CEJsonUserTypeSorted &&_Other);

		CEJsonUserTypeOrdered(NStr::CStr const &_Type, CJsonOrdered const &_Value);
		CEJsonUserTypeOrdered(NStr::CStr const &_Type, CJsonOrdered &&_Value);

		bool operator == (CEJsonUserTypeOrdered const &_Right) const noexcept;
		COrdering_Partial operator <=> (CEJsonUserTypeOrdered const &_Right) const noexcept;

		NStr::CStr m_Type;
		CJsonOrdered m_Value;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);
	};

	struct CEJsonUserTypeSorted final
	{
		CEJsonUserTypeSorted();
		CEJsonUserTypeSorted(CEJsonUserTypeSorted const &_Other) = default;
		CEJsonUserTypeSorted(CEJsonUserTypeSorted &&_Other) = default;
		CEJsonUserTypeSorted(CEJsonUserTypeOrdered const &_Other);
		CEJsonUserTypeSorted(CEJsonUserTypeOrdered &&_Other);
		CEJsonUserTypeSorted(NStr::CStr const &_Type, CJsonSorted const &_Value);
		CEJsonUserTypeSorted(NStr::CStr const &_Type, CJsonSorted &&_Value);

		bool operator == (CEJsonUserTypeSorted const &_Right) const noexcept;
		COrdering_Partial operator <=> (CEJsonUserTypeSorted const &_Right) const noexcept;

		NStr::CStr m_Type;
		CJsonSorted m_Value;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);
	};

	CEJsonUserTypeOrdered fg_UserTypeOrdered(NStr::CStr const &_Type, CJsonOrdered const &_Value);
	CEJsonUserTypeOrdered fg_UserTypeOrdered(NStr::CStr const &_Type, CJsonOrdered &&_Value);

	CEJsonUserTypeSorted fg_UserTypeSorted(NStr::CStr const &_Type, CJsonSorted const &_Value);
	CEJsonUserTypeSorted fg_UserTypeSorted(NStr::CStr const &_Type, CJsonSorted &&_Value);

	NStr::CStr fg_EJsonTypeToString(EEJsonType _Type);
	NStr::CStr fg_JsonTypeToString(EEJsonType _Type);

	struct CEJsonConstStrings
	{
		static NStr::CStr const mc_Date;
		static NStr::CStr const mc_Binary;
		static NStr::CStr const mc_Type;
		static NStr::CStr const mc_Value;
		static NStr::CStr const mc_Escape;
	};

	template <typename t_CParent>
	struct TCEJsonValue : public TCJsonValue<t_CParent>
	{
		using CValue = typename TCJsonValue<t_CParent>::CValue;
		using CKeyValue = typename TCJsonValue<t_CParent>::CKeyValue;
		using CUserType = TCConditional<CValue::mc_bOrdered, CEJsonUserTypeOrdered, CEJsonUserTypeSorted>;
		using CJsonType = TCConditional<CValue::mc_bOrdered, CJsonOrdered, CJsonSorted>;

		template <typename tf_CType>
		TCEJsonValue(tf_CType &&_Type)
			requires
			(
				NTraits::cIsPlacementNewConstructibleWith<TCJsonValue<t_CParent>, tf_CType &&>
				&& !NPrivate::TCIsTCJsonValue<NTraits::TCRemoveReferenceAndQualifiers<tf_CType>>::mc_Value
				&& !NPrivate::TCIsTCEJsonValue<NTraits::TCRemoveReferenceAndQualifiers<tf_CType>>::mc_Value
			)
#ifdef DCompiler_MSVC_Workaround
			: TCJsonValue<t_CParent>(fg_Forward<tf_CType>(_Type))
		{
		}
#else
		;
#endif

		TCEJsonValue();
		TCEJsonValue(EEJsonType _Type);
		TCEJsonValue(TCEJsonValue const &_Other);
		TCEJsonValue(TCEJsonValue &_Other);
		TCEJsonValue(TCEJsonValue &&_Other);
		TCEJsonValue(TCEJsonValue const &&_Other);

		template <typename ...tfp_CValues>
		TCEJsonValue(tfp_CValues && ...p_Values)
			requires ((NTraits::cIsSame<NTraits::TCRemoveReferenceAndQualifiers<tfp_CValues>, CKeyValue> && (sizeof...(p_Values) > 0)) && ...)
		;

		TCEJsonValue(NContainer::CSecureByteVector const &_Value) = delete;
		TCEJsonValue(NContainer::CSecureByteVector &_Value) = delete;
		TCEJsonValue(NContainer::CSecureByteVector &&_Value) = delete;

		using TCJsonValue<t_CParent>::operator = ;

		TCEJsonValue &operator = (TCEJsonValue const &_Value);
		TCEJsonValue &operator = (TCEJsonValue &_Value);
		TCEJsonValue &operator = (TCEJsonValue &&_Value);
		TCEJsonValue &operator = (EEJsonType _Type);

		EEJsonType f_EType() const;
		void f_SetEType(EEJsonType _Type);
		void f_SetType(EJsonType _Type);

		bool f_IsDate() const;
		bool f_IsBinary() const;
		bool f_IsUserType() const;

		NTime::CTime const &f_Date() const;
		NTime::CTime &f_Date();
		NContainer::CByteVector const &f_Binary() const;
		NContainer::CByteVector &f_Binary();
		CUserType const &f_UserType() const;
		CUserType &f_UserType();

		CJsonType f_ToJson() const &;
		CJsonType f_ToJson() &&;
		static TCEJsonValue fs_FromJson(CJsonType const &_Json);
		static TCEJsonValue fs_FromJson(CJsonType &&_Json);

		CJsonType f_ToJsonNoConvert() const &;
		CJsonType f_ToJsonNoConvert() &&;
		static TCEJsonValue fs_FromJsonNoConvert(CJsonType const &_Json);
		static TCEJsonValue fs_FromJsonNoConvert(CJsonType &&_Json);

		static TCEJsonValue fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName = {}, bool _bConvertNullToSpace = false, EJsonDialectFlag _Flags = EJsonDialectFlag_None);
		NStr::CStr f_ToString(ch8 const *_pPrettySeparator = "\t", EJsonDialectFlag _Flags = EJsonDialectFlag_None) const;
		NStr::CStr f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator = "\t", EJsonDialectFlag _Flags = EJsonDialectFlag_None) const;

		using TCJsonValue<t_CParent>::f_GetMember;
		CValue const *f_GetMember(NStr::CStr const &_Name, EEJsonType _Type) const;
		CValue *f_GetMember(NStr::CStr const &_Name, EEJsonType _Type);

		template <typename tf_CParent>
		static TCEJsonValue fs_FromCompatible(TCEJsonValue<tf_CParent> const &_Other);
		template <typename tf_CParent>
		static TCEJsonValue fs_FromCompatible(TCEJsonValue<tf_CParent> &&_Other);
		template <typename tf_CParent>
		static TCEJsonValue fs_FromCompatible(TCEJsonValue<tf_CParent> const &&_Other);

	protected:
		template <typename t_CJsonValue2, bool t_bOrdered2>
		friend struct TCJsonObject;

		template <template <typename t_CParent2> class t_TCValue2, typename t_CTypes2, bool t_bOrdered2>
		friend struct NPrivate::TCJsonValueBase;

		template <typename tf_CParent>
		explicit TCEJsonValue(TCEJsonValue<tf_CParent> const &_Other);
		template <typename tf_CParent>
		explicit TCEJsonValue(TCEJsonValue<tf_CParent> &&_Other);
		template <typename tf_CParent>
		explicit TCEJsonValue(TCEJsonValue<tf_CParent> const &&_Other);

		void fp_PromoteEType(EEJsonType _Type);

		void fp_ToJson(CJsonType &_Ret) const &;
		static void fsp_EscapeObject(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject const &_Value);
		static void fsp_ToJson_Object(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject const &_Value);
		static void fsp_FromJson(TCEJsonValue &_Ret, CJsonType const &_From);
		static void fsp_FromJson_Object(TCEJsonValue &_Ret, typename CJsonType::CObject const &_From);

		void fp_ToJson(CJsonType &_Ret) &&;
		static void fsp_EscapeObject(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject &&_Value);
		static void fsp_ToJson_Object(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject &&_Value);
		static void fsp_FromJson(TCEJsonValue &_Ret, CJsonType &&_From);
		static void fsp_FromJson_Object(TCEJsonValue &_Ret, typename CJsonType::CObject &&_From);

		void fp_ToJsonNoConvert(CJsonType &_Ret) const &;
		static void fsp_ToJsonNoConvert_Object(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject const &_Value);
		static void fsp_FromJsonNoConvert(TCEJsonValue &_Ret, CJsonType const &_From);
		static void fsp_FromJsonNoConvert_Object(TCEJsonValue &_Ret, typename CJsonType::CObject const &_From);

		void fp_ToJsonNoConvert(CJsonType &_Ret) &&;
		static void fsp_ToJsonNoConvert_Object(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject &&_Value);
		static void fsp_FromJsonNoConvert(TCEJsonValue &_Ret, CJsonType &&_From);
		static void fsp_FromJsonNoConvert_Object(TCEJsonValue &_Ret, typename CJsonType::CObject &&_From);
	};

	namespace NPrivate
	{
		struct CEJsonExtraTypesOrdered
		{
			using CTypes = NMeta::TCTypeList
				<
					NStorage::TCMember<NTime::CTime, (EJsonType)EEJsonType_Date>
					, NStorage::TCMember<NContainer::CByteVector, (EJsonType)EEJsonType_Binary>
					, NStorage::TCMember<NStorage::TCIndirection<CEJsonUserTypeOrdered>, (EJsonType)EEJsonType_UserType>
				>
			;
		};

		struct CEJsonExtraTypesSorted
		{
			using CTypes = NMeta::TCTypeList
				<
					NStorage::TCMember<NStorage::TCIndirection<NTime::CTime>, (EJsonType)EEJsonType_Date>
					, NStorage::TCMember<NContainer::CByteVector, (EJsonType)EEJsonType_Binary>
					, NStorage::TCMember<NStorage::TCIndirection<CEJsonUserTypeSorted>, (EJsonType)EEJsonType_UserType>
				>
			;
		};
	}

	using CEJsonOrdered = TCJson<TCEJsonValue, NPrivate::CEJsonExtraTypesOrdered, true>;
	using CEJsonSorted = TCJson<TCEJsonValue, NPrivate::CEJsonExtraTypesSorted, false>;

#ifdef DMibEncodingJsonExternTemplate
	using CEJsonValueBaseOrdered = NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesOrdered, true>;
	using CJsonValueEJsonOrdered = TCJsonValue<CEJsonValueBaseOrdered>;

	using CEJsonValueBaseSorted = NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesSorted, false>;
	using CJsonValueEJsonSorted = TCJsonValue<CEJsonValueBaseSorted>;
#endif
}

#include "Malterlib_Encoding_EJson_Uninstantiated.hpp"

#ifdef DMibEncodingJsonExternTemplate
#	include "Malterlib_Encoding_EJson_Instantiated.hpp"
#	include "Malterlib_Encoding_EJson_InstantiatedSorted.hpp"
#else
#	include "Malterlib_Encoding_EJson.hpp"
#endif

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
