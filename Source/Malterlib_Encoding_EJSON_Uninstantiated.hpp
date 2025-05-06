// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_EJSON.h"

namespace NMib::NEncoding
{
#ifndef DCompiler_MSVC_Workaround
	template <typename t_CParent>
	template <typename tf_CType>
	TCEJSONValue<t_CParent>::TCEJSONValue(tf_CType &&_Type)
		requires
		(
			NTraits::cConstructibleWith<TCJSONValue<t_CParent>, tf_CType &&>
			&& !NPrivate::TCIsTCJSONValue<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CType>::CType>::mc_Value
			&& !NPrivate::TCIsTCEJSONValue<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CType>::CType>::mc_Value
		)
		: TCJSONValue<t_CParent>(fg_Forward<tf_CType>(_Type))
	{
	}
#endif

	template <typename t_CParent>
	template <typename ...tfp_CValues>
	TCEJSONValue<t_CParent>::TCEJSONValue(tfp_CValues && ...p_Values)
		requires ((NTraits::cIsSame<NTraits::TCRemoveReferenceAndQualifiersType<tfp_CValues>, CKeyValue> && (sizeof...(p_Values) > 0)) && ...)
		: TCJSONValue<t_CParent>(fg_Forward<tfp_CValues>(p_Values)...)
	{
	}

	template <typename tf_CStream>
	void CEJSONUserTypeOrdered::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << m_Type;
		_Stream << m_Value;
	}

	template <typename tf_CStream>
	void CEJSONUserTypeOrdered::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> m_Type;
		_Stream >> m_Value;
	}

	template <typename tf_CStream>
	void CEJSONUserTypeSorted::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << m_Type;
		_Stream << m_Value;
	}

	template <typename tf_CStream>
	void CEJSONUserTypeSorted::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> m_Type;
		_Stream >> m_Value;
	}
}
