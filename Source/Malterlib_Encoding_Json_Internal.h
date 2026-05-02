// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

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
		template <typename t_CValue, EJsonContainerFlag t_ContainerFlags, typename t_CTypes>
		struct TCGetJsonValueVariant
		{
		};

		template <typename t_CValue, EJsonContainerFlag t_ContainerFlags, typename ...tp_CTypes>
		struct TCGetJsonValueVariant<t_CValue, t_ContainerFlags, NMeta::TCTypeList<tp_CTypes...>>
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
					, NStorage::TCMember<TCJsonObject<t_CValue, t_ContainerFlags>, EJsonType_Object>
					, NStorage::TCMember<NContainer::TCVector<t_CValue>, EJsonType_Array>
					, tp_CTypes...
				>
			;
		} ;
	};

	template <typename t_CParent>
	struct TCJsonValue;

	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
	struct TCJsonValueBase;

	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
	struct TCJsonValueBase
	{
		static constexpr EJsonContainerFlag mc_ContainerFlags = t_ContainerFlags;
		static constexpr bool mc_bOrdered = TCJsonContainerFlagTraits<t_ContainerFlags>::mc_bOrdered;
		static constexpr bool mc_bPreserveComments = TCJsonContainerFlagTraits<t_ContainerFlags>::mc_bPreserveComments;
		static constexpr bool mc_bHasDefaultTypes = NMeta::gc_TypeList_Len<typename t_CTypes::CTypes> == 0;

		using CValue = t_TCValue<TCJsonValueBase>;
		using CVariantType = typename NPrivate::TCGetJsonValueVariant<CValue, t_ContainerFlags, typename t_CTypes::CTypes>::CType;

		template <typename tf_CType>
		TCJsonValueBase(tf_CType &&_Value)
			requires (NTraits::cIsPlacementNewConstructibleWith<CVariantType, tf_CType &&>)
		;
		TCJsonValueBase(TCJsonValueBase const &_Value);
		TCJsonValueBase(TCJsonValueBase &_Value);
		TCJsonValueBase(TCJsonValueBase &&_Value);

		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, EJsonContainerFlag tf_ContainerFlags>
		explicit TCJsonValueBase(TCJsonValueBase<tf_TCValue, tf_CTypes, tf_ContainerFlags> const &_Value);
		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, EJsonContainerFlag tf_ContainerFlags>
		explicit TCJsonValueBase(TCJsonValueBase<tf_TCValue, tf_CTypes, tf_ContainerFlags> &_Value);
		template <template <typename t_CParent> class tf_TCValue, typename tf_CTypes, EJsonContainerFlag tf_ContainerFlags>
		explicit TCJsonValueBase(TCJsonValueBase<tf_TCValue, tf_CTypes, tf_ContainerFlags> &&_Value);

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

		TCJsonTriviaView<TCJsonValueBase> f_Trivia()
			requires (mc_bPreserveComments)
		;
		TCJsonTriviaConstView<TCJsonValueBase> f_Trivia() const
			requires (mc_bPreserveComments)
		;

	protected:
		template <typename t_CParent2>
		friend struct TCJsonValue;

		template <template <typename t_CParent2> class t_TCValue2, typename t_CTypes2, EJsonContainerFlag t_ContainerFlags2>
		friend struct TCJsonValueBase;
		template <typename t_CValueBase>
		friend struct NEncoding::TCJsonTriviaConstView;
		template <typename t_CValueBase>
		friend struct NEncoding::TCJsonTriviaView;

		// Members
		CVariantType mp_Value;
		DMibNoUniqueAddress TCConditional<mc_bPreserveComments, CJsonValueTriviaSlots, CEmpty> mp_ValueTrivia;
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
