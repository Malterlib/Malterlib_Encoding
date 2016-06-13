#pragma once

#include "Malterlib_Encoding_EJSON.h"

namespace NMib
{
	namespace NEncoding
	{
		template <typename t_CParent>
		template <typename tf_CType, TCDisableIfForbidden<tf_CType> *>
		TCEJSONValue<t_CParent>::TCEJSONValue(tf_CType &&_Type)
			: TCJSONValue<t_CParent>(fg_Forward<tf_CType>(_Type))
		{
		}
	
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
