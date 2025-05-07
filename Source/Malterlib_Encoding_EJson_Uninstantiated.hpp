// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_EJson.h"

namespace NMib::NEncoding
{
#ifndef DCompiler_MSVC_Workaround
	template <typename t_CParent>
	template <typename tf_CType>
	TCEJsonValue<t_CParent>::TCEJsonValue(tf_CType &&_Type)
		requires
		(
			NTraits::cConstructibleWith<TCJsonValue<t_CParent>, tf_CType &&>
			&& !NPrivate::TCIsTCJsonValue<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CType>::CType>::mc_Value
			&& !NPrivate::TCIsTCEJsonValue<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CType>::CType>::mc_Value
		)
		: TCJsonValue<t_CParent>(fg_Forward<tf_CType>(_Type))
	{
	}
#endif

	template <typename t_CParent>
	template <typename ...tfp_CValues>
	TCEJsonValue<t_CParent>::TCEJsonValue(tfp_CValues && ...p_Values)
		requires ((NTraits::cIsSame<NTraits::TCRemoveReferenceAndQualifiersType<tfp_CValues>, CKeyValue> && (sizeof...(p_Values) > 0)) && ...)
		: TCJsonValue<t_CParent>(fg_Forward<tfp_CValues>(p_Values)...)
	{
	}

	template <typename tf_CStream>
	void CEJsonUserTypeOrdered::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << m_Type;
		_Stream << m_Value;
	}

	template <typename tf_CStream>
	void CEJsonUserTypeOrdered::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> m_Type;
		_Stream >> m_Value;
	}

	template <typename tf_CStream>
	void CEJsonUserTypeSorted::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << m_Type;
		_Stream << m_Value;
	}

	template <typename tf_CStream>
	void CEJsonUserTypeSorted::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> m_Type;
		_Stream >> m_Value;
	}
}
