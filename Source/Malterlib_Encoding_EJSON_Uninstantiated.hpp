#pragma once

#include "Malterlib_Encoding_EJSON.h"

namespace NMib
{
	namespace NEncoding
	{
#ifndef DCompiler_MSVC
		template <typename t_CParent>
		template <typename tf_CType, TCEnableIfType<NTraits::TCIsConstructorCallableWith<TCJSONValue<t_CParent>, void (tf_CType &&)>::mc_Value> *>
		TCEJSONValue<t_CParent>::TCEJSONValue(tf_CType &&_Type)
			: TCJSONValue<t_CParent>(fg_Forward<tf_CType>(_Type))
		{
		}
#endif
	
		template <typename tf_CStream>
		void CEJSONUserType::f_Feed(tf_CStream &_Stream) const
		{
			_Stream << m_Type;
			_Stream << m_Value;
		}
		
		template <typename tf_CStream>
		void CEJSONUserType::f_Consume(tf_CStream &_Stream)
		{
			_Stream >> m_Type;
			_Stream >> m_Value;
		}
	}
}
