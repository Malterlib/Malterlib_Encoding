// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib::NEncoding::NPrivate
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
		template <typename t_CValue, bool t_bOrdered, typename t_CTypes>
		struct TCGetJSONValueVariant
		{
		};

		template <typename t_CValue, bool t_bOrdered, typename ...tp_CTypes>
		struct TCGetJSONValueVariant<t_CValue, t_bOrdered, NMeta::TCTypeList<tp_CTypes...>>
		{
			using CType =
				NStorage::TCStreamableVariant
				<
					EJSONType
					, NStorage::TCMember<void, EJSONType_Invalid>
					, NStorage::TCMember<CJSONNull, EJSONType_Null>
					, NStorage::TCMember<NStr::CStr, EJSONType_String>
					, NStorage::TCMember<int64, EJSONType_Integer>
					, NStorage::TCMember<fp64, EJSONType_Float>
					, NStorage::TCMember<CJSONBoolean, EJSONType_Boolean>
					, NStorage::TCMember<TCJSONObject<t_CValue, t_bOrdered>, EJSONType_Object>
					, NStorage::TCMember<NContainer::TCVector<t_CValue>, EJSONType_Array>
					, tp_CTypes...
				>
			;
		} ;


	};

	template <typename t_CParent>
	struct TCJSONValue;

	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
	struct TCJSONValueBase;

	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
	struct TCJSONValueBase
	{
		static constexpr bool mc_bOrdered = t_bOrdered;
		static constexpr bool mc_bHasDefaultTypes = NMeta::TCTypeList_Len<typename t_CTypes::CTypes>::mc_Value == 0;

		using CValue = t_TCValue<TCJSONValueBase>;
		using CVariantType = typename NPrivate::TCGetJSONValueVariant<CValue, t_bOrdered, typename t_CTypes::CTypes>::CType;

		template <typename tf_CType>
		TCJSONValueBase(tf_CType &&_Value)
			requires (NTraits::cConstructibleWith<CVariantType, tf_CType &&>)
#ifdef DCompiler_MSVC_Workaround
			: mp_Value(fg_Forward<tf_CType>(_Value))
		{
		}
#else
		;
#endif
		TCJSONValueBase(TCJSONValueBase const &_Value);
		TCJSONValueBase(TCJSONValueBase &_Value);
		TCJSONValueBase(TCJSONValueBase &&_Value);

		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, bool tf_bOrdered>
		explicit TCJSONValueBase(TCJSONValueBase<tf_TCValue, tf_CTypes, tf_bOrdered> const &_Value);
		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, bool tf_bOrdered>
		explicit TCJSONValueBase(TCJSONValueBase<tf_TCValue, tf_CTypes, tf_bOrdered> &_Value);
		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, bool tf_bOrdered>
		explicit TCJSONValueBase(TCJSONValueBase<tf_TCValue, tf_CTypes, tf_bOrdered> &&_Value);

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
		template <typename t_CParent2>
		friend struct TCJSONValue;

		template <template <typename t_CParent2> class t_TCValue2, typename t_CTypes2, bool t_bOrdered2>
		friend struct TCJSONValueBase;
		
		// Members
		CVariantType mp_Value;
	};

	struct CJSONExtraTypes
	{
		using CTypes = NMeta::TCTypeList<>;
	};
}

namespace NMib::NEncoding
{
	template <typename t_CJSONObject>
	bool fg_ValidateType(t_CJSONObject const *_pObject, EJSONType _Type)
	{
		return _pObject && _pObject->f_Type() == _Type;
	}
}
