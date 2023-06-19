// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON.h"

#include <Mib/Storage/Indirection>

#include <Mib/CommandLine/AnsiEncoding>

namespace NMib::NEncoding
{
	enum EEJSONType : uint8
	{
		EEJSONType_Invalid = EJSONType_Invalid
		, EEJSONType_Null = EJSONType_Null
		, EEJSONType_String = EJSONType_String
		, EEJSONType_Integer = EJSONType_Integer
		, EEJSONType_Float = EJSONType_Float
		, EEJSONType_Boolean = EJSONType_Boolean
		, EEJSONType_Object = EJSONType_Object
		, EEJSONType_Array = EJSONType_Array
		, EEJSONType_Date = EJSONType_Max
		, EEJSONType_Binary
		, EEJSONType_UserType
	};

	struct CEJSONUserTypeSorted;

	struct CEJSONUserTypeOrdered final
	{
		CEJSONUserTypeOrdered();
		CEJSONUserTypeOrdered(CEJSONUserTypeOrdered const &_Other) = default;
		CEJSONUserTypeOrdered(CEJSONUserTypeOrdered &&_Other) = default;
		CEJSONUserTypeOrdered(CEJSONUserTypeSorted const &_Other);
		CEJSONUserTypeOrdered(CEJSONUserTypeSorted &&_Other);

		CEJSONUserTypeOrdered(NStr::CStr const &_Type, CJSONOrdered const &_Value);
		CEJSONUserTypeOrdered(NStr::CStr const &_Type, CJSONOrdered &&_Value);

		bool operator == (CEJSONUserTypeOrdered const &_Right) const;
		COrdering_Partial operator <=> (CEJSONUserTypeOrdered const &_Right) const;

		NStr::CStr m_Type;
		CJSONOrdered m_Value;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);
	};

	struct CEJSONUserTypeSorted final
	{
		CEJSONUserTypeSorted();
		CEJSONUserTypeSorted(CEJSONUserTypeSorted const &_Other) = default;
		CEJSONUserTypeSorted(CEJSONUserTypeSorted &&_Other) = default;
		CEJSONUserTypeSorted(CEJSONUserTypeOrdered const &_Other);
		CEJSONUserTypeSorted(CEJSONUserTypeOrdered &&_Other);
		CEJSONUserTypeSorted(NStr::CStr const &_Type, CJSONSorted const &_Value);
		CEJSONUserTypeSorted(NStr::CStr const &_Type, CJSONSorted &&_Value);

		bool operator == (CEJSONUserTypeSorted const &_Right) const;
		COrdering_Partial operator <=> (CEJSONUserTypeSorted const &_Right) const;

		NStr::CStr m_Type;
		CJSONSorted m_Value;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);
	};

	CEJSONUserTypeOrdered fg_UserTypeOrdered(NStr::CStr const &_Type, CJSONOrdered const &_Value);
	CEJSONUserTypeOrdered fg_UserTypeOrdered(NStr::CStr const &_Type, CJSONOrdered &&_Value);

	CEJSONUserTypeSorted fg_UserTypeSorted(NStr::CStr const &_Type, CJSONSorted const &_Value);
	CEJSONUserTypeSorted fg_UserTypeSorted(NStr::CStr const &_Type, CJSONSorted &&_Value);

	NStr::CStr fg_EJSONTypeToString(EEJSONType _Type);

	struct CEJSONConstStrings
	{
		static NStr::CStr const mc_Date;
		static NStr::CStr const mc_Binary;
		static NStr::CStr const mc_Type;
		static NStr::CStr const mc_Value;
		static NStr::CStr const mc_Escape;
	};

	template <typename t_CParent>
	struct TCEJSONValue : public TCJSONValue<t_CParent>
	{
		using CValue = typename TCJSONValue<t_CParent>::CValue;
		using CKeyValue = typename TCJSONValue<t_CParent>::CKeyValue;
		using CUserType = typename TCChooseType<CValue::mc_bOrdered, CEJSONUserTypeOrdered, CEJSONUserTypeSorted>::CType;
		using CJSONType = typename TCChooseType<CValue::mc_bOrdered, CJSONOrdered, CJSONSorted>::CType;

		template
		<
			typename tf_CType
			, TCEnableIfType
			<
				NTraits::TCIsConstructorCallableWith<TCJSONValue<t_CParent>, void (tf_CType &&)>::mc_Value
				&& !NPrivate::TCIsTCJSONValue<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CType>::CType>::mc_Value
				&& !NPrivate::TCIsTCEJSONValue<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CType>::CType>::mc_Value
			> * = nullptr
		>
		TCEJSONValue(tf_CType &&_Type)
#ifdef DCompiler_MSVC_Workaround
			: TCJSONValue<t_CParent>(fg_Forward<tf_CType>(_Type))
		{
		}
#else
		;
#endif

		TCEJSONValue();
		TCEJSONValue(EEJSONType _Type);
		TCEJSONValue(TCEJSONValue const &_Other);
		TCEJSONValue(TCEJSONValue &_Other);
		TCEJSONValue(TCEJSONValue &&_Other);
		TCEJSONValue(TCEJSONValue const &&_Other);
		TCEJSONValue(std::initializer_list<CValue> const &_Init);
		TCEJSONValue(std::initializer_list<CKeyValue> const &_Init);

		TCEJSONValue(NContainer::CSecureByteVector const &_Value) = delete;
		TCEJSONValue(NContainer::CSecureByteVector &_Value) = delete;
		TCEJSONValue(NContainer::CSecureByteVector &&_Value) = delete;

		using TCJSONValue<t_CParent>::operator = ;

		TCEJSONValue &operator = (TCEJSONValue const &_Value);
		TCEJSONValue &operator = (TCEJSONValue &_Value);
		TCEJSONValue &operator = (TCEJSONValue &&_Value);
		TCEJSONValue &operator = (EEJSONType _Type);

		EEJSONType f_EType() const;
		void f_SetEType(EEJSONType _Type);
		void f_SetType(EJSONType _Type);

		bool f_IsDate() const;
		bool f_IsBinary() const;
		bool f_IsUserType() const;

		NTime::CTime const &f_Date() const;
		NTime::CTime &f_Date();
		NContainer::CByteVector const &f_Binary() const;
		NContainer::CByteVector &f_Binary();
		CUserType const &f_UserType() const;
		CUserType &f_UserType();

		CJSONType f_ToJson() const &;
		CJSONType f_ToJson() &&;
		static TCEJSONValue fs_FromJson(CJSONType const &_JSON);
		static TCEJSONValue fs_FromJson(CJSONType &&_JSON);

		CJSONType f_ToJsonNoConvert() const &;
		CJSONType f_ToJsonNoConvert() &&;
		static TCEJSONValue fs_FromJsonNoConvert(CJSONType const &_JSON);
		static TCEJSONValue fs_FromJsonNoConvert(CJSONType &&_JSON);

		static TCEJSONValue fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName = NStr::CStr(), bool _bConvertNullToSpace = false);
		NStr::CStr f_ToString(ch8 const *_pPrettySeparator = "\t", EJSONDialectFlag _Flags = EJSONDialectFlag_None) const;
		NStr::CStr f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator = "\t", EJSONDialectFlag _Flags = EJSONDialectFlag_None) const;

		using TCJSONValue<t_CParent>::f_GetMember;
		CValue const *f_GetMember(NStr::CStr const &_Name, EEJSONType _Type) const;
		CValue *f_GetMember(NStr::CStr const &_Name, EEJSONType _Type);

		template <typename tf_CParent>
		static TCEJSONValue fs_FromCompatible(TCEJSONValue<tf_CParent> const &_Other);
		template <typename tf_CParent>
		static TCEJSONValue fs_FromCompatible(TCEJSONValue<tf_CParent> &&_Other);
		template <typename tf_CParent>
		static TCEJSONValue fs_FromCompatible(TCEJSONValue<tf_CParent> const &&_Other);

	protected:
		template <typename t_CJSONValue2, bool t_bOrdered2>
		friend struct TCJSONObject;

		template <template <typename t_CParent2> class t_TCValue2, typename t_CTypes2, bool t_bOrdered2>
		friend struct NPrivate::TCJSONValueBase;

		template <typename tf_CParent>
		explicit TCEJSONValue(TCEJSONValue<tf_CParent> const &_Other);
		template <typename tf_CParent>
		explicit TCEJSONValue(TCEJSONValue<tf_CParent> &&_Other);
		template <typename tf_CParent>
		explicit TCEJSONValue(TCEJSONValue<tf_CParent> const &&_Other);

		void fp_PromoteEType(EEJSONType _Type);

		void fp_ToJson(CJSONType &_Ret) const &;
		static void fsp_EscapeObject(CJSONType &_Ret, typename TCJSONValue<t_CParent>::CObject const &_Value);
		static void fsp_ToJson_Object(CJSONType &_Ret, typename TCJSONValue<t_CParent>::CObject const &_Value);
		static void fsp_FromJson(TCEJSONValue &_Ret, CJSONType const &_From);
		static void fsp_FromJson_Object(TCEJSONValue &_Ret, typename CJSONType::CObject const &_From);

		void fp_ToJson(CJSONType &_Ret) &&;
		static void fsp_EscapeObject(CJSONType &_Ret, typename TCJSONValue<t_CParent>::CObject &&_Value);
		static void fsp_ToJson_Object(CJSONType &_Ret, typename TCJSONValue<t_CParent>::CObject &&_Value);
		static void fsp_FromJson(TCEJSONValue &_Ret, CJSONType &&_From);
		static void fsp_FromJson_Object(TCEJSONValue &_Ret, typename CJSONType::CObject &&_From);

		void fp_ToJsonNoConvert(CJSONType &_Ret) const &;
		static void fsp_ToJsonNoConvert_Object(CJSONType &_Ret, typename TCJSONValue<t_CParent>::CObject const &_Value);
		static void fsp_FromJsonNoConvert(TCEJSONValue &_Ret, CJSONType const &_From);
		static void fsp_FromJsonNoConvert_Object(TCEJSONValue &_Ret, typename CJSONType::CObject const &_From);

		void fp_ToJsonNoConvert(CJSONType &_Ret) &&;
		static void fsp_ToJsonNoConvert_Object(CJSONType &_Ret, typename TCJSONValue<t_CParent>::CObject &&_Value);
		static void fsp_FromJsonNoConvert(TCEJSONValue &_Ret, CJSONType &&_From);
		static void fsp_FromJsonNoConvert_Object(TCEJSONValue &_Ret, typename CJSONType::CObject &&_From);
	};

	namespace NPrivate
	{
		struct CEJSONExtraTypesOrdered
		{
			using CTypes = NMeta::TCTypeList
				<
					NStorage::TCMember<NTime::CTime, (EJSONType)EEJSONType_Date>
					, NStorage::TCMember<NContainer::CByteVector, (EJSONType)EEJSONType_Binary>
					, NStorage::TCMember<NStorage::TCIndirection<CEJSONUserTypeOrdered>, (EJSONType)EEJSONType_UserType>
				>
			;
		};

		struct CEJSONExtraTypesSorted
		{
			using CTypes = NMeta::TCTypeList
				<
					NStorage::TCMember<NStorage::TCIndirection<NTime::CTime>, (EJSONType)EEJSONType_Date>
					, NStorage::TCMember<NContainer::CByteVector, (EJSONType)EEJSONType_Binary>
					, NStorage::TCMember<NStorage::TCIndirection<CEJSONUserTypeSorted>, (EJSONType)EEJSONType_UserType>
				>
			;
		};
	}

	using CEJSONOrdered = TCJSON<TCEJSONValue, NPrivate::CEJSONExtraTypesOrdered, true>;
	using CEJSONSorted = TCJSON<TCEJSONValue, NPrivate::CEJSONExtraTypesSorted, false>;

#ifdef DMibEncodingJSONExternTemplate
	using CEJSONValueBaseOrdered = NPrivate::TCJSONValueBase<TCEJSONValue, NPrivate::CEJSONExtraTypesOrdered, true>;
	using CJSONValueEJSONOrdered = TCJSONValue<CEJSONValueBaseOrdered>;

	using CEJSONValueBaseSorted = NPrivate::TCJSONValueBase<TCEJSONValue, NPrivate::CEJSONExtraTypesSorted, false>;
	using CJSONValueEJSONSorted = TCJSONValue<CEJSONValueBaseSorted>;
#endif
}

#include "Malterlib_Encoding_EJSON_Uninstantiated.hpp"

#ifdef DMibEncodingJSONExternTemplate
#	include "Malterlib_Encoding_EJSON_Instantiated.hpp"
#	include "Malterlib_Encoding_EJSON_InstantiatedSorted.hpp"
#else
#	include "Malterlib_Encoding_EJSON.hpp"
#endif

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
