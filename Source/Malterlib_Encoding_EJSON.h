#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib
{
	namespace NEncoding
	{
		enum EEJSONType : uint8
		{
			EEJSONType_Date = EJSONType_Max
			, EEJSONType_Binary
			, EEJSONType_UserType
		};

		struct CEJSONUserType
		{
			CEJSONUserType();
			CEJSONUserType(NStr::CStr const &_Type, CJSON const &_Value);
			CEJSONUserType(NStr::CStr const &_Type, CJSON &&_Value);
			
			bool operator == (CEJSONUserType const &_Right) const;
			bool operator < (CEJSONUserType const &_Right) const;

			NStr::CStr m_Type;
			CJSON m_Value;
			
			template <typename tf_CStream>
			void f_Feed(tf_CStream &_Stream) const;
			template <typename tf_CStream>
			void f_Consume(tf_CStream &_Stream);
		};
		
		CEJSONUserType fg_UserType(NStr::CStr const &_Type, CJSON const &_Value);
		CEJSONUserType fg_UserType(NStr::CStr const &_Type, CJSON &&_Value);

		template <typename t_CParent>
		class TCEJSONValue : public TCJSONValue<t_CParent>
		{
			using CValue = typename TCJSONValue<t_CParent>::CValue;
			using CKeyValue = typename TCJSONValue<t_CParent>::CKeyValue;
		public:
			
			template <typename tf_CType, TCEnableIfType<NTraits::TCIsConstructorCallableWith<TCJSONValue<t_CParent>, void (tf_CType &&)>::mc_Value> * = nullptr>
			TCEJSONValue(tf_CType &&_Type)
#ifdef DCompiler_MSVC
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
			NContainer::TCVector<uint8> const &f_Binary() const;
			NContainer::TCVector<uint8> &f_Binary();
			CEJSONUserType const &f_UserType() const;
			CEJSONUserType &f_UserType();
			
			CJSON f_ToJSON() const;
			static TCEJSONValue fs_FromJSON(CJSON const &_JSON);

			static TCEJSONValue fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName = NStr::CStr());
			NStr::CStr f_ToString(ch8 const *_pPrettySeparator = "\t") const;
			
			using TCJSONValue<t_CParent>::f_GetMember;
			typename TCJSONValue<t_CParent>::CValue const *f_GetMember(NStr::CStr const &_Name, EEJSONType _Type) const;
			typename TCJSONValue<t_CParent>::CValue *f_GetMember(NStr::CStr const &_Name, EEJSONType _Type);

		protected:
			void fp_PromoteEType(EEJSONType _Type);
			void fp_ToJSON(CJSON &_Ret) const;
			static void fsp_EscapeObject(CJSON &_Ret, typename TCJSONValue<t_CParent>::CObject const &_Value);
			static void fsp_ToJSON_Object(CJSON &_Ret, typename TCJSONValue<t_CParent>::CObject const &_Value);
			static void fsp_FromJSON(TCEJSONValue &_Ret, CJSON const &_From);
			static void fsp_FromJSON_Object(TCEJSONValue &_Ret, CJSON::CObject const &_From);
		};
		
		namespace NPrivate
		{
			struct CEJSONExtraTypes
			{
				using CTypes = NMeta::TCTypeList
					<
						NContainer::TCVariantMember<NTime::CTime, EJSONType, (EJSONType)EEJSONType_Date>
						, NContainer::TCVariantMember<NContainer::TCVector<uint8>, EJSONType, (EJSONType)EEJSONType_Binary>
						, NContainer::TCVariantMember<CEJSONUserType, EJSONType, (EJSONType)EEJSONType_UserType>
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
}

#include "Malterlib_Encoding_EJSON_Uninstantiated.hpp"

#ifdef DMibEncodingJSONExternTemplate
#	include "Malterlib_Encoding_EJSON_Instantiated.hpp"
#else
#	include "Malterlib_Encoding_EJSON.hpp"
#endif
