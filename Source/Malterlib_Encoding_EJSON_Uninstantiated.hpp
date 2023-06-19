// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_EJSON.h"

namespace NMib::NEncoding
{
#ifndef DCompiler_MSVC_Workaround
	template <typename t_CParent>
	template
	<
		typename tf_CType
		, TCEnableIfType
		<
			NTraits::TCIsConstructorCallableWith<TCJSONValue<t_CParent>, void (tf_CType &&)>::mc_Value
			&& !NPrivate::TCIsTCJSONValue<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CType>::CType>::mc_Value
			&& !NPrivate::TCIsTCEJSONValue<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CType>::CType>::mc_Value
		> *
	>
	TCEJSONValue<t_CParent>::TCEJSONValue(tf_CType &&_Type)
		: TCJSONValue<t_CParent>(fg_Forward<tf_CType>(_Type))
	{
	}
#endif

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
