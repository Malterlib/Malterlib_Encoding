// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

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
	struct CEJsonUserTypeOrderedWithComments;
	struct CEJsonUserTypeSortedWithComments;
	struct CEJsonUserTypeOrderedYaml;
	struct CEJsonUserTypeSortedYaml;

	struct CEJsonUserTypeOrdered final
	{
		CEJsonUserTypeOrdered();
		CEJsonUserTypeOrdered(CEJsonUserTypeOrdered const &_Other) = default;
		CEJsonUserTypeOrdered(CEJsonUserTypeOrdered &&_Other) = default;
		CEJsonUserTypeOrdered(CEJsonUserTypeSorted const &_Other);
		CEJsonUserTypeOrdered(CEJsonUserTypeSorted &&_Other);
		CEJsonUserTypeOrdered(CEJsonUserTypeOrderedWithComments const &_Other);
		CEJsonUserTypeOrdered(CEJsonUserTypeOrderedWithComments &&_Other);
		CEJsonUserTypeOrdered(CEJsonUserTypeSortedWithComments const &_Other);
		CEJsonUserTypeOrdered(CEJsonUserTypeSortedWithComments &&_Other);
		CEJsonUserTypeOrdered(CEJsonUserTypeOrderedYaml const &_Other);
		CEJsonUserTypeOrdered(CEJsonUserTypeOrderedYaml &&_Other);
		CEJsonUserTypeOrdered(CEJsonUserTypeSortedYaml const &_Other);
		CEJsonUserTypeOrdered(CEJsonUserTypeSortedYaml &&_Other);

		CEJsonUserTypeOrdered(NStr::CStr const &_Type, CJsonOrdered const &_Value);
		CEJsonUserTypeOrdered(NStr::CStr const &_Type, CJsonOrdered &&_Value);

		bool operator == (CEJsonUserTypeOrdered const &_Right) const noexcept;
		COrdering_Partial operator <=> (CEJsonUserTypeOrdered const &_Right) const noexcept;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

		NStr::CStr m_Type;
		CJsonOrdered m_Value;
	};

	struct CEJsonUserTypeSorted final
	{
		CEJsonUserTypeSorted();
		CEJsonUserTypeSorted(CEJsonUserTypeSorted const &_Other) = default;
		CEJsonUserTypeSorted(CEJsonUserTypeSorted &&_Other) = default;
		CEJsonUserTypeSorted(CEJsonUserTypeOrdered const &_Other);
		CEJsonUserTypeSorted(CEJsonUserTypeOrdered &&_Other);
		CEJsonUserTypeSorted(CEJsonUserTypeOrderedWithComments const &_Other);
		CEJsonUserTypeSorted(CEJsonUserTypeOrderedWithComments &&_Other);
		CEJsonUserTypeSorted(CEJsonUserTypeSortedWithComments const &_Other);
		CEJsonUserTypeSorted(CEJsonUserTypeSortedWithComments &&_Other);
		CEJsonUserTypeSorted(CEJsonUserTypeOrderedYaml const &_Other);
		CEJsonUserTypeSorted(CEJsonUserTypeOrderedYaml &&_Other);
		CEJsonUserTypeSorted(CEJsonUserTypeSortedYaml const &_Other);
		CEJsonUserTypeSorted(CEJsonUserTypeSortedYaml &&_Other);
		CEJsonUserTypeSorted(NStr::CStr const &_Type, CJsonSorted const &_Value);
		CEJsonUserTypeSorted(NStr::CStr const &_Type, CJsonSorted &&_Value);

		bool operator == (CEJsonUserTypeSorted const &_Right) const noexcept;
		COrdering_Partial operator <=> (CEJsonUserTypeSorted const &_Right) const noexcept;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

		NStr::CStr m_Type;
		CJsonSorted m_Value;
	};

	struct CEJsonUserTypeOrderedWithComments final
	{
		CEJsonUserTypeOrderedWithComments();
		CEJsonUserTypeOrderedWithComments(CEJsonUserTypeOrderedWithComments const &_Other) = default;
		CEJsonUserTypeOrderedWithComments(CEJsonUserTypeOrderedWithComments &&_Other) = default;
		CEJsonUserTypeOrderedWithComments(CEJsonUserTypeOrdered const &_Other);
		CEJsonUserTypeOrderedWithComments(CEJsonUserTypeOrdered &&_Other);
		CEJsonUserTypeOrderedWithComments(CEJsonUserTypeSorted const &_Other);
		CEJsonUserTypeOrderedWithComments(CEJsonUserTypeSorted &&_Other);
		CEJsonUserTypeOrderedWithComments(CEJsonUserTypeSortedWithComments const &_Other);
		CEJsonUserTypeOrderedWithComments(CEJsonUserTypeSortedWithComments &&_Other);
		CEJsonUserTypeOrderedWithComments(CEJsonUserTypeOrderedYaml const &_Other);
		CEJsonUserTypeOrderedWithComments(CEJsonUserTypeOrderedYaml &&_Other);
		CEJsonUserTypeOrderedWithComments(CEJsonUserTypeSortedYaml const &_Other);
		CEJsonUserTypeOrderedWithComments(CEJsonUserTypeSortedYaml &&_Other);
		CEJsonUserTypeOrderedWithComments(NStr::CStr const &_Type, CJsonOrderedWithComments const &_Value);
		CEJsonUserTypeOrderedWithComments(NStr::CStr const &_Type, CJsonOrderedWithComments &&_Value);

		bool operator == (CEJsonUserTypeOrderedWithComments const &_Right) const noexcept;
		COrdering_Partial operator <=> (CEJsonUserTypeOrderedWithComments const &_Right) const noexcept;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

		NStr::CStr m_Type;
		CJsonOrderedWithComments m_Value;
	};

	struct CEJsonUserTypeSortedWithComments final
	{
		CEJsonUserTypeSortedWithComments();
		CEJsonUserTypeSortedWithComments(CEJsonUserTypeSortedWithComments const &_Other) = default;
		CEJsonUserTypeSortedWithComments(CEJsonUserTypeSortedWithComments &&_Other) = default;
		CEJsonUserTypeSortedWithComments(CEJsonUserTypeOrdered const &_Other);
		CEJsonUserTypeSortedWithComments(CEJsonUserTypeOrdered &&_Other);
		CEJsonUserTypeSortedWithComments(CEJsonUserTypeSorted const &_Other);
		CEJsonUserTypeSortedWithComments(CEJsonUserTypeSorted &&_Other);
		CEJsonUserTypeSortedWithComments(CEJsonUserTypeOrderedWithComments const &_Other);
		CEJsonUserTypeSortedWithComments(CEJsonUserTypeOrderedWithComments &&_Other);
		CEJsonUserTypeSortedWithComments(CEJsonUserTypeOrderedYaml const &_Other);
		CEJsonUserTypeSortedWithComments(CEJsonUserTypeOrderedYaml &&_Other);
		CEJsonUserTypeSortedWithComments(CEJsonUserTypeSortedYaml const &_Other);
		CEJsonUserTypeSortedWithComments(CEJsonUserTypeSortedYaml &&_Other);
		CEJsonUserTypeSortedWithComments(NStr::CStr const &_Type, CJsonSortedWithComments const &_Value);
		CEJsonUserTypeSortedWithComments(NStr::CStr const &_Type, CJsonSortedWithComments &&_Value);

		bool operator == (CEJsonUserTypeSortedWithComments const &_Right) const noexcept;
		COrdering_Partial operator <=> (CEJsonUserTypeSortedWithComments const &_Right) const noexcept;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

		NStr::CStr m_Type;
		CJsonSortedWithComments m_Value;
	};

	struct CEJsonUserTypeOrderedYaml final
	{
		CEJsonUserTypeOrderedYaml();
		CEJsonUserTypeOrderedYaml(CEJsonUserTypeOrderedYaml const &_Other) = default;
		CEJsonUserTypeOrderedYaml(CEJsonUserTypeOrderedYaml &&_Other) = default;
		CEJsonUserTypeOrderedYaml(CEJsonUserTypeOrdered const &_Other);
		CEJsonUserTypeOrderedYaml(CEJsonUserTypeOrdered &&_Other);
		CEJsonUserTypeOrderedYaml(CEJsonUserTypeSorted const &_Other);
		CEJsonUserTypeOrderedYaml(CEJsonUserTypeSorted &&_Other);
		CEJsonUserTypeOrderedYaml(CEJsonUserTypeOrderedWithComments const &_Other);
		CEJsonUserTypeOrderedYaml(CEJsonUserTypeOrderedWithComments &&_Other);
		CEJsonUserTypeOrderedYaml(CEJsonUserTypeSortedWithComments const &_Other);
		CEJsonUserTypeOrderedYaml(CEJsonUserTypeSortedWithComments &&_Other);
		CEJsonUserTypeOrderedYaml(CEJsonUserTypeSortedYaml const &_Other);
		CEJsonUserTypeOrderedYaml(CEJsonUserTypeSortedYaml &&_Other);
		CEJsonUserTypeOrderedYaml(NStr::CStr const &_Type, CJsonOrderedYaml const &_Value);
		CEJsonUserTypeOrderedYaml(NStr::CStr const &_Type, CJsonOrderedYaml &&_Value);

		bool operator == (CEJsonUserTypeOrderedYaml const &_Right) const noexcept;
		COrdering_Partial operator <=> (CEJsonUserTypeOrderedYaml const &_Right) const noexcept;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

		NStr::CStr m_Type;
		CJsonOrderedYaml m_Value;
	};

	struct CEJsonUserTypeSortedYaml final
	{
		CEJsonUserTypeSortedYaml();
		CEJsonUserTypeSortedYaml(CEJsonUserTypeSortedYaml const &_Other) = default;
		CEJsonUserTypeSortedYaml(CEJsonUserTypeSortedYaml &&_Other) = default;
		CEJsonUserTypeSortedYaml(CEJsonUserTypeOrdered const &_Other);
		CEJsonUserTypeSortedYaml(CEJsonUserTypeOrdered &&_Other);
		CEJsonUserTypeSortedYaml(CEJsonUserTypeSorted const &_Other);
		CEJsonUserTypeSortedYaml(CEJsonUserTypeSorted &&_Other);
		CEJsonUserTypeSortedYaml(CEJsonUserTypeOrderedWithComments const &_Other);
		CEJsonUserTypeSortedYaml(CEJsonUserTypeOrderedWithComments &&_Other);
		CEJsonUserTypeSortedYaml(CEJsonUserTypeSortedWithComments const &_Other);
		CEJsonUserTypeSortedYaml(CEJsonUserTypeSortedWithComments &&_Other);
		CEJsonUserTypeSortedYaml(CEJsonUserTypeOrderedYaml const &_Other);
		CEJsonUserTypeSortedYaml(CEJsonUserTypeOrderedYaml &&_Other);
		CEJsonUserTypeSortedYaml(NStr::CStr const &_Type, CJsonSortedYaml const &_Value);
		CEJsonUserTypeSortedYaml(NStr::CStr const &_Type, CJsonSortedYaml &&_Value);

		bool operator == (CEJsonUserTypeSortedYaml const &_Right) const noexcept;
		COrdering_Partial operator <=> (CEJsonUserTypeSortedYaml const &_Right) const noexcept;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

		NStr::CStr m_Type;
		CJsonSortedYaml m_Value;
	};

	CEJsonUserTypeOrdered fg_UserTypeOrdered(NStr::CStr const &_Type, CJsonOrdered const &_Value);
	CEJsonUserTypeOrdered fg_UserTypeOrdered(NStr::CStr const &_Type, CJsonOrdered &&_Value);

	CEJsonUserTypeSorted fg_UserTypeSorted(NStr::CStr const &_Type, CJsonSorted const &_Value);
	CEJsonUserTypeSorted fg_UserTypeSorted(NStr::CStr const &_Type, CJsonSorted &&_Value);
	CEJsonUserTypeOrderedWithComments fg_UserTypeOrderedWithComments(NStr::CStr const &_Type, CJsonOrderedWithComments const &_Value);
	CEJsonUserTypeOrderedWithComments fg_UserTypeOrderedWithComments(NStr::CStr const &_Type, CJsonOrderedWithComments &&_Value);
	CEJsonUserTypeSortedWithComments fg_UserTypeSortedWithComments(NStr::CStr const &_Type, CJsonSortedWithComments const &_Value);
	CEJsonUserTypeSortedWithComments fg_UserTypeSortedWithComments(NStr::CStr const &_Type, CJsonSortedWithComments &&_Value);

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
		using CUserType = TCConditional
			<
				CValue::mc_bPreserveYamlMetadata
				, TCConditional<CValue::mc_bOrdered, CEJsonUserTypeOrderedYaml, CEJsonUserTypeSortedYaml>
				, TCConditional
				<
					CValue::mc_bPreserveComments
					, TCConditional<CValue::mc_bOrdered, CEJsonUserTypeOrderedWithComments, CEJsonUserTypeSortedWithComments>
					, TCConditional<CValue::mc_bOrdered, CEJsonUserTypeOrdered, CEJsonUserTypeSorted>
				>
			>
		;
		using CJsonType = TCConditional
			<
				CValue::mc_bPreserveYamlMetadata
				, TCConditional<CValue::mc_bOrdered, CJsonOrderedYaml, CJsonSortedYaml>
				, TCConditional
				<
					CValue::mc_bPreserveComments
					, TCConditional<CValue::mc_bOrdered, CJsonOrderedWithComments, CJsonSortedWithComments>
					, TCConditional<CValue::mc_bOrdered, CJsonOrdered, CJsonSorted>
				>
			>
		;

		template <typename tf_CType>
		TCEJsonValue(tf_CType &&_Type)
			requires
			(
				NTraits::cIsPlacementNewConstructibleWith<TCJsonValue<t_CParent>, tf_CType &&>
				&& !NPrivate::TCIsTCJsonValue<NTraits::TCRemoveReferenceAndQualifiers<tf_CType>>::mc_Value
				&& !NPrivate::TCIsTCEJsonValue<NTraits::TCRemoveReferenceAndQualifiers<tf_CType>>::mc_Value
			)
		;

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

		template <typename t_CParseContext>
		static TCEJsonValue fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName = {}, EJsonDialectFlag _Flags = EJsonDialectFlag_None);
		template <typename t_CParseContext>
		NStr::CStr f_ToString(ch8 const *_pPrettySeparator = "\t", EJsonDialectFlag _Flags = EJsonDialectFlag_None) const;
		template <typename t_CParseContext>
		NStr::CStr f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator = "\t", EJsonDialectFlag _Flags = EJsonDialectFlag_None) const;

		static TCEJsonValue fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName = {}, EJsonDialectFlag _Flags = EJsonDialectFlag_None);
		static TCEJsonValue fs_FromStringStrict(NStr::CStr const &_String, NStr::CStr const &_FileName = {}, EJsonDialectFlag _Flags = EJsonDialectFlag_None);
		static TCEJsonValue fs_FromStringJsonC(NStr::CStr const &_String, NStr::CStr const &_FileName = {}, EJsonDialectFlag _Flags = EJsonDialectFlag_None);
		static TCEJsonValue fs_FromStringJson5(NStr::CStr const &_String, NStr::CStr const &_FileName = {}, EJsonDialectFlag _Flags = EJsonDialectFlag_None);
		NStr::CStr f_ToString(ch8 const *_pPrettySeparator = "\t", EJsonDialectFlag _Flags = EJsonDialectFlag_None) const;
		NStr::CStr f_ToStringJsonC(ch8 const *_pPrettySeparator = "\t", EJsonDialectFlag _Flags = EJsonDialectFlag_None) const;
		NStr::CStr f_ToStringJson5(ch8 const *_pPrettySeparator = "\t", EJsonDialectFlag _Flags = EJsonDialectFlag_None) const;
		NStr::CStr f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator = "\t", EJsonDialectFlag _Flags = EJsonDialectFlag_None) const;
		NStr::CStr f_ToStringColoredJsonC(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator = "\t", EJsonDialectFlag _Flags = EJsonDialectFlag_None) const;
		NStr::CStr f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator = "\t", EJsonDialectFlag _Flags = EJsonDialectFlag_None) const;

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
		template <typename t_CJsonValue2, EJsonContainerFlag t_ContainerFlags2>
		friend struct TCJsonObject;

		template <template <typename t_CParent2> class t_TCValue2, typename t_CTypes2, EJsonContainerFlag t_ContainerFlags2>
		friend struct NPrivate::TCJsonValueBase;

		template <typename tf_CParent>
		explicit TCEJsonValue(TCEJsonValue<tf_CParent> const &_Other);
		template <typename tf_CParent>
		explicit TCEJsonValue(TCEJsonValue<tf_CParent> &&_Other);
		template <typename tf_CParent>
		explicit TCEJsonValue(TCEJsonValue<tf_CParent> const &&_Other);

		using CSemanticTrivia = TCConditional<CValue::mc_bPreserveComments, NStr::CStr, CEmpty>;

		void fp_PromoteEType(EEJsonType _Type);

		void fp_ToJson(CJsonType &_Ret) const &;
		static void fsp_EscapeObject(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject const &_Value);
		static void fsp_ToJson_Object(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject const &_Value);
		static void fsp_FromJson(TCEJsonValue &_Ret, CJsonType const &_From);
		static bool fsp_FromJson_Object(TCEJsonValue &_Ret, typename CJsonType::CObject const &_From, CSemanticTrivia *o_pSemanticTrivia = nullptr);

		void fp_ToJson(CJsonType &_Ret) &&;
		static void fsp_EscapeObject(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject &&_Value);
		static void fsp_ToJson_Object(CJsonType &_Ret, typename TCJsonValue<t_CParent>::CObject &&_Value);
		static void fsp_FromJson(TCEJsonValue &_Ret, CJsonType &&_From);
		static bool fsp_FromJson_Object(TCEJsonValue &_Ret, typename CJsonType::CObject &&_From, CSemanticTrivia *o_pSemanticTrivia = nullptr);

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

		struct CEJsonExtraTypesOrderedWithComments
		{
			using CTypes = NMeta::TCTypeList
				<
					NStorage::TCMember<NTime::CTime, (EJsonType)EEJsonType_Date>
					, NStorage::TCMember<NContainer::CByteVector, (EJsonType)EEJsonType_Binary>
					, NStorage::TCMember<NStorage::TCIndirection<CEJsonUserTypeOrderedWithComments>, (EJsonType)EEJsonType_UserType>
				>
			;
		};

		struct CEJsonExtraTypesSortedWithComments
		{
			using CTypes = NMeta::TCTypeList
				<
					NStorage::TCMember<NStorage::TCIndirection<NTime::CTime>, (EJsonType)EEJsonType_Date>
					, NStorage::TCMember<NContainer::CByteVector, (EJsonType)EEJsonType_Binary>
					, NStorage::TCMember<NStorage::TCIndirection<CEJsonUserTypeSortedWithComments>, (EJsonType)EEJsonType_UserType>
				>
			;
		};

		struct CEJsonExtraTypesOrderedYaml
		{
			using CTypes = NMeta::TCTypeList
				<
					NStorage::TCMember<NTime::CTime, (EJsonType)EEJsonType_Date>
					, NStorage::TCMember<NContainer::CByteVector, (EJsonType)EEJsonType_Binary>
					, NStorage::TCMember<NStorage::TCIndirection<CEJsonUserTypeOrderedYaml>, (EJsonType)EEJsonType_UserType>
				>
			;
		};

		struct CEJsonExtraTypesSortedYaml
		{
			using CTypes = NMeta::TCTypeList
				<
					NStorage::TCMember<NStorage::TCIndirection<NTime::CTime>, (EJsonType)EEJsonType_Date>
					, NStorage::TCMember<NContainer::CByteVector, (EJsonType)EEJsonType_Binary>
					, NStorage::TCMember<NStorage::TCIndirection<CEJsonUserTypeSortedYaml>, (EJsonType)EEJsonType_UserType>
				>
			;
		};
	}

	using CEJsonOrdered = TCJson<TCEJsonValue, NPrivate::CEJsonExtraTypesOrdered, EJsonContainerFlag::mc_Ordered>;
	using CEJsonSorted = TCJson<TCEJsonValue, NPrivate::CEJsonExtraTypesSorted, EJsonContainerFlag::mc_None>;
	using CEJsonOrderedWithComments = TCJson<TCEJsonValue, NPrivate::CEJsonExtraTypesOrderedWithComments, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments>;
	using CEJsonSortedWithComments = TCJson<TCEJsonValue, NPrivate::CEJsonExtraTypesSortedWithComments, EJsonContainerFlag::mc_PreserveComments>;
	using CEJsonOrderedYaml = TCJson<TCEJsonValue, NPrivate::CEJsonExtraTypesOrderedYaml, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata>;
	using CEJsonSortedYaml = TCJson<TCEJsonValue, NPrivate::CEJsonExtraTypesSortedYaml, EJsonContainerFlag::mc_PreserveYamlMetadata>;

	namespace NPrivate
	{
		template <typename tf_CUserType>
		struct TCEJsonForUserType;

		template <>
		struct TCEJsonForUserType<CEJsonUserTypeOrdered>
		{
			using CType = CEJsonOrdered;
		};

		template <>
		struct TCEJsonForUserType<CEJsonUserTypeSorted>
		{
			using CType = CEJsonSorted;
		};

		template <>
		struct TCEJsonForUserType<CEJsonUserTypeOrderedWithComments>
		{
			using CType = CEJsonOrderedWithComments;
		};

		template <>
		struct TCEJsonForUserType<CEJsonUserTypeSortedWithComments>
		{
			using CType = CEJsonSortedWithComments;
		};

		template <>
		struct TCEJsonForUserType<CEJsonUserTypeOrderedYaml>
		{
			using CType = CEJsonOrderedYaml;
		};

		template <>
		struct TCEJsonForUserType<CEJsonUserTypeSortedYaml>
		{
			using CType = CEJsonSortedYaml;
		};
	}

	template <typename tf_CUserType>
	using TCEJsonUserTypeValueYamlType = typename NPrivate::TCEJsonForUserType<NTraits::TCRemoveReferenceAndQualifiers<tf_CUserType>>::CType;

	template <typename tf_CUserType>
	auto fg_GetYamlUserTypeValue(tf_CUserType const &_UserType) -> TCEJsonUserTypeValueYamlType<tf_CUserType>;

	template <typename tf_CUserType>
	void fg_SetYamlUserTypeValue(tf_CUserType &o_UserType, TCEJsonUserTypeValueYamlType<tf_CUserType> const &_Value);
	template <typename tf_CUserType>
	void fg_SetYamlUserTypeValue(tf_CUserType &o_UserType, TCEJsonUserTypeValueYamlType<tf_CUserType> &&_Value);

#ifdef DMibEncodingJsonExternTemplate
	using CEJsonValueBaseOrdered = NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesOrdered, EJsonContainerFlag::mc_Ordered>;
	using CJsonValueEJsonOrdered = TCJsonValue<CEJsonValueBaseOrdered>;

	using CEJsonValueBaseSorted = NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesSorted, EJsonContainerFlag::mc_None>;
	using CJsonValueEJsonSorted = TCJsonValue<CEJsonValueBaseSorted>;

	using CEJsonValueBaseOrderedWithComments = NPrivate::TCJsonValueBase
		<
			TCEJsonValue
			, NPrivate::CEJsonExtraTypesOrderedWithComments
			, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveComments
		>
	;
	using CJsonValueEJsonOrderedWithComments = TCJsonValue<CEJsonValueBaseOrderedWithComments>;

	using CEJsonValueBaseSortedWithComments = NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesSortedWithComments, EJsonContainerFlag::mc_PreserveComments>;
	using CJsonValueEJsonSortedWithComments = TCJsonValue<CEJsonValueBaseSortedWithComments>;

	using CEJsonValueBaseOrderedYaml = NPrivate::TCJsonValueBase
		<
			TCEJsonValue
			, NPrivate::CEJsonExtraTypesOrderedYaml
			, EJsonContainerFlag::mc_Ordered | EJsonContainerFlag::mc_PreserveYamlMetadata
		>
	;
	using CJsonValueEJsonOrderedYaml = TCJsonValue<CEJsonValueBaseOrderedYaml>;

	using CEJsonValueBaseSortedYaml = NPrivate::TCJsonValueBase<TCEJsonValue, NPrivate::CEJsonExtraTypesSortedYaml, EJsonContainerFlag::mc_PreserveYamlMetadata>;
	using CJsonValueEJsonSortedYaml = TCJsonValue<CEJsonValueBaseSortedYaml>;
#endif
}

#include "Malterlib_Encoding_EJson_Uninstantiated.hpp"

#ifdef DMibEncodingJsonExternTemplate
#	include "Malterlib_Encoding_EJson_Instantiated.hpp"
#	include "Malterlib_Encoding_EJson_InstantiatedWithComments.hpp"
#	include "Malterlib_Encoding_EJson_InstantiatedSorted.hpp"
#	include "Malterlib_Encoding_EJson_InstantiatedSortedWithComments.hpp"
#	include "Malterlib_Encoding_EJson_InstantiatedYaml.hpp"
#	include "Malterlib_Encoding_EJson_InstantiatedSortedYaml.hpp"
#else
#	include "Malterlib_Encoding_EJson.hpp"
#endif

#include "Malterlib_Encoding_EJson_Generate.h"

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
