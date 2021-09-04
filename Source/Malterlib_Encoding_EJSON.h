#pragma once

#include "Malterlib_Encoding_JSON.h"

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

	struct CEJSONUserType
	{
		CEJSONUserType();
		CEJSONUserType(NStr::CStr const &_Type, CJSON const &_Value);
		CEJSONUserType(NStr::CStr const &_Type, CJSON &&_Value);

		bool operator == (CEJSONUserType const &_Right) const;
		COrdering_Partial operator <=> (CEJSONUserType const &_Right) const;

		NStr::CStr m_Type;
		CJSON m_Value;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);
	};

	CEJSONUserType fg_UserType(NStr::CStr const &_Type, CJSON const &_Value);
	CEJSONUserType fg_UserType(NStr::CStr const &_Type, CJSON &&_Value);

	NStr::CStr fg_EJSONTypeToString(EEJSONType _Type);

	template <typename t_CParent>
	class TCEJSONValue : public TCJSONValue<t_CParent>
	{
	public:
		using CValue = typename TCJSONValue<t_CParent>::CValue;
		using CKeyValue = typename TCJSONValue<t_CParent>::CKeyValue;

		template <typename tf_CType, TCEnableIfType<NTraits::TCIsConstructorCallableWith<TCJSONValue<t_CParent>, void (tf_CType &&)>::mc_Value> * = nullptr>
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
		TCEJSONValue(TCInitializerList<CValue> const &_Init);
		TCEJSONValue(TCInitializerList<CKeyValue> const &_Init);

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
		CEJSONUserType const &f_UserType() const;
		CEJSONUserType &f_UserType();

		CJSON f_ToJSON() const &;
		CJSON f_ToJSON() &&;
		static TCEJSONValue fs_FromJSON(CJSON const &_JSON);
		static TCEJSONValue fs_FromJSON(CJSON &&_JSON);

		CJSON f_ToJSONNoConvert() const &;
		CJSON f_ToJSONNoConvert() &&;
		static TCEJSONValue fs_FromJSONNoConvert(CJSON const &_JSON);
		static TCEJSONValue fs_FromJSONNoConvert(CJSON &&_JSON);

		static TCEJSONValue fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName = NStr::CStr(), bool _bConvertNullToSpace = false);
		NStr::CStr f_ToString(ch8 const *_pPrettySeparator = "\t", EJSONDialectFlag _Flags = EJSONDialectFlag_None) const;
		NStr::CStr f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator = "\t", EJSONDialectFlag _Flags = EJSONDialectFlag_None) const;

		using TCJSONValue<t_CParent>::f_GetMember;
		typename TCJSONValue<t_CParent>::CValue const *f_GetMember(NStr::CStr const &_Name, EEJSONType _Type) const;
		typename TCJSONValue<t_CParent>::CValue *f_GetMember(NStr::CStr const &_Name, EEJSONType _Type);

	protected:
		void fp_PromoteEType(EEJSONType _Type);

		void fp_ToJSON(CJSON &_Ret) const &;
		static void fsp_EscapeObject(CJSON &_Ret, typename TCJSONValue<t_CParent>::CObject const &_Value);
		static void fsp_ToJSON_Object(CJSON &_Ret, typename TCJSONValue<t_CParent>::CObject const &_Value);
		static void fsp_FromJSON(TCEJSONValue &_Ret, CJSON const &_From);
		static void fsp_FromJSON_Object(TCEJSONValue &_Ret, CJSON::CObject const &_From);

		void fp_ToJSON(CJSON &_Ret) &&;
		static void fsp_EscapeObject(CJSON &_Ret, typename TCJSONValue<t_CParent>::CObject &&_Value);
		static void fsp_ToJSON_Object(CJSON &_Ret, typename TCJSONValue<t_CParent>::CObject &&_Value);
		static void fsp_FromJSON(TCEJSONValue &_Ret, CJSON &&_From);
		static void fsp_FromJSON_Object(TCEJSONValue &_Ret, CJSON::CObject &&_From);

		void fp_ToJSONNoConvert(CJSON &_Ret) const &;
		static void fsp_ToJSONNoConvert_Object(CJSON &_Ret, typename TCJSONValue<t_CParent>::CObject const &_Value);
		static void fsp_FromJSONNoConvert(TCEJSONValue &_Ret, CJSON const &_From);
		static void fsp_FromJSONNoConvert_Object(TCEJSONValue &_Ret, CJSON::CObject const &_From);

		void fp_ToJSONNoConvert(CJSON &_Ret) &&;
		static void fsp_ToJSONNoConvert_Object(CJSON &_Ret, typename TCJSONValue<t_CParent>::CObject &&_Value);
		static void fsp_FromJSONNoConvert(TCEJSONValue &_Ret, CJSON &&_From);
		static void fsp_FromJSONNoConvert_Object(TCEJSONValue &_Ret, CJSON::CObject &&_From);
	};

	namespace NPrivate
	{
		struct CEJSONExtraTypes
		{
			using CTypes = NMeta::TCTypeList
				<
					NStorage::TCMember<NTime::CTime, (EJSONType)EEJSONType_Date>
					, NStorage::TCMember<NContainer::CByteVector, (EJSONType)EEJSONType_Binary>
					, NStorage::TCMember<CEJSONUserType, (EJSONType)EEJSONType_UserType>
				>
			;
		};
	}

	using CEJSON = TCJSON
		<
			TCEJSONValue
			, NPrivate::CEJSONExtraTypes
		>
	;
}

#include "Malterlib_Encoding_EJSON_Uninstantiated.hpp"

#ifdef DMibEncodingJSONExternTemplate
#	include "Malterlib_Encoding_EJSON_Instantiated.hpp"
#else
#	include "Malterlib_Encoding_EJSON.hpp"
#endif

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
