#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib
{
	namespace NEncoding
	{
		namespace NPrivate
		{
			struct CJSONBoolean
			{
				CJSONBoolean() = default;
				inline_always CJSONBoolean(bool _bValue);
				inline_always operator bool const &() const;
				inline_always operator bool &();
				
				template <typename tf_CStream>
				void f_Feed(tf_CStream &_Stream) const;
				template <typename tf_CStream>
				void f_Consume(tf_CStream &_Stream);

				bool m_bValue;
			};
			
			struct CJSONNull
			{
				CJSONNull() = default;
				inline_always CJSONNull(CNullPtr _Value);
				inline_always operator CNullPtr () const;
				
				template <typename tf_CStream>
				void f_Feed(tf_CStream &_Stream) const;
				template <typename tf_CStream>
				void f_Consume(tf_CStream &_Stream);
			};
			
			namespace NPrivate
			{
				template <typename t_CValue, typename t_CTypes>
				struct TCGetJSONValueVariant
				{
				};

				template <typename t_CValue, typename ...tp_CTypes>
				struct TCGetJSONValueVariant<t_CValue, NMeta::TCTypeList<tp_CTypes...>>
				{
					using CType =
						NContainer::TCVariantMembers
						<
							EJSONType
							, NContainer::TCVariantMember<void, DMibVariantMember(EJSONType, Invalid)>
							, NContainer::TCVariantMember<CJSONNull, DMibVariantMember(EJSONType, Null)> 
							, NContainer::TCVariantMember<NStr::CStr, DMibVariantMember(EJSONType, String)>
							, NContainer::TCVariantMember<int64, DMibVariantMember(EJSONType, Integer)>
							, NContainer::TCVariantMember<fp64, DMibVariantMember(EJSONType, Float)>
							, NContainer::TCVariantMember<CJSONBoolean, DMibVariantMember(EJSONType, Boolean)>
							, NContainer::TCVariantMember<TCJSONObject<t_CValue>, DMibVariantMember(EJSONType, Object)>
							, NContainer::TCVariantMember<NContainer::TCVector<t_CValue>, DMibVariantMember(EJSONType, Array)>
							, tp_CTypes...
						>
					;
				} ;
				
				
			};
			
			template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
			class TCJSONValueBase
			{
			public:
				using CValue = t_TCValue<TCJSONValueBase>;
				using CVariantType = typename NPrivate::TCGetJSONValueVariant<CValue, typename t_CTypes::CTypes>::CType;

				template <typename tf_CType, TCEnableIfType<NTraits::TCIsConstructorCallableWith<CVariantType, void (tf_CType &&)>::mc_Value> * = nullptr>
				TCJSONValueBase(tf_CType &&_Value)
#ifdef DCompiler_MSVC
					: mp_Value(fg_Forward<tf_CType>(_Value))
				{
				}
#else
				;
#endif
				TCJSONValueBase(TCJSONValueBase const &_Value);
				TCJSONValueBase(TCJSONValueBase &_Value);
				TCJSONValueBase(TCJSONValueBase &&_Value);

				TCJSONValueBase(pfp64 _Value);
				TCJSONValueBase(pfp32 _Value);
				TCJSONValueBase(fp32 _Value);
				TCJSONValueBase(bool _Value);
				TCJSONValueBase();
				~TCJSONValueBase();

				template <typename tf_CStream>
				void f_Feed(tf_CStream &_Stream) const;
				template <typename tf_CStream>
				void f_Consume(tf_CStream &_Stream);
				
			protected:
				// Members
				CVariantType mp_Value;
			};

			struct CJSONExtraTypes
			{
				using CTypes = NMeta::TCTypeList<>;
			};
		}
		
		template <typename t_CJSONObject>
		bool fg_ValidateType(t_CJSONObject const *_pObject, EJSONType _Type)
		{
			return _pObject && _pObject->f_Type() == _Type;
		}
	}
}

