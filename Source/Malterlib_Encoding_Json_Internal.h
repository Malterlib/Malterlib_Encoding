// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding::NPrivate
{
	struct CJsonBoolean
	{
		CJsonBoolean() = default;
		inline_always CJsonBoolean(bool _bValue);
		inline_always operator bool const &() const;
		inline_always operator bool &();

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

		bool m_bValue;
	};

	struct CJsonNull
	{
		CJsonNull() = default;
		inline_always CJsonNull(CNullPtr _Value);
		inline_always operator CNullPtr () const;

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);
	};

	namespace NPrivate
	{
		template <typename t_CValue, bool t_bOrdered, typename t_CTypes>
		struct TCGetJsonValueVariant
		{
		};

		template <typename t_CValue, bool t_bOrdered, typename ...tp_CTypes>
		struct TCGetJsonValueVariant<t_CValue, t_bOrdered, NMeta::TCTypeList<tp_CTypes...>>
		{
			using CType =
				NStorage::TCStreamableVariant
				<
					EJsonType
					, NStorage::TCMember<void, EJsonType_Invalid>
					, NStorage::TCMember<CJsonNull, EJsonType_Null>
					, NStorage::TCMember<NStr::CStr, EJsonType_String>
					, NStorage::TCMember<int64, EJsonType_Integer>
					, NStorage::TCMember<fp64, EJsonType_Float>
					, NStorage::TCMember<CJsonBoolean, EJsonType_Boolean>
					, NStorage::TCMember<TCJsonObject<t_CValue, t_bOrdered>, EJsonType_Object>
					, NStorage::TCMember<NContainer::TCVector<t_CValue>, EJsonType_Array>
					, tp_CTypes...
				>
			;
		} ;


	};

	template <typename t_CParent>
	struct TCJsonValue;

	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
	struct TCJsonValueBase;

	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
	struct TCJsonValueBase
	{
		static constexpr bool mc_bOrdered = t_bOrdered;
		static constexpr bool mc_bHasDefaultTypes = NMeta::TCTypeList_Len<typename t_CTypes::CTypes>::mc_Value == 0;

		using CValue = t_TCValue<TCJsonValueBase>;
		using CVariantType = typename NPrivate::TCGetJsonValueVariant<CValue, t_bOrdered, typename t_CTypes::CTypes>::CType;

		template <typename tf_CType>
		TCJsonValueBase(tf_CType &&_Value)
			requires (NTraits::cConstructibleWith<CVariantType, tf_CType &&>)
#ifdef DCompiler_MSVC_Workaround
			: mp_Value(fg_Forward<tf_CType>(_Value))
		{
		}
#else
		;
#endif
		TCJsonValueBase(TCJsonValueBase const &_Value);
		TCJsonValueBase(TCJsonValueBase &_Value);
		TCJsonValueBase(TCJsonValueBase &&_Value);

		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, bool tf_bOrdered>
		explicit TCJsonValueBase(TCJsonValueBase<tf_TCValue, tf_CTypes, tf_bOrdered> const &_Value);
		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, bool tf_bOrdered>
		explicit TCJsonValueBase(TCJsonValueBase<tf_TCValue, tf_CTypes, tf_bOrdered> &_Value);
		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, bool tf_bOrdered>
		explicit TCJsonValueBase(TCJsonValueBase<tf_TCValue, tf_CTypes, tf_bOrdered> &&_Value);

		TCJsonValueBase(pfp64 _Value);
		TCJsonValueBase(pfp32 _Value);
		TCJsonValueBase(fp32 _Value);
		TCJsonValueBase(bool _Value);
		TCJsonValueBase();
		~TCJsonValueBase();

		template <typename tf_CStream>
		void f_Feed(tf_CStream &_Stream) const;
		template <typename tf_CStream>
		void f_Consume(tf_CStream &_Stream);

	protected:
		template <typename t_CParent2>
		friend struct TCJsonValue;

		template <template <typename t_CParent2> class t_TCValue2, typename t_CTypes2, bool t_bOrdered2>
		friend struct TCJsonValueBase;
		
		// Members
		CVariantType mp_Value;
	};

	struct CJsonExtraTypes
	{
		using CTypes = NMeta::TCTypeList<>;
	};
}

namespace NMib::NEncoding
{
	template <typename t_CJsonObject>
	bool fg_ValidateType(t_CJsonObject const *_pObject, EJsonType _Type)
	{
		return _pObject && _pObject->f_Type() == _Type;
	}
}
