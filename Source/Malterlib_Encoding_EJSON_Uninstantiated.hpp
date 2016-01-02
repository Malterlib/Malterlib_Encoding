#pragma once

#include "Malterlib_Encoding_EJSON.h"

namespace NMib
{
	namespace NEncoding
	{
		template <typename t_CParent>
		template <typename tf_CType>
		TCEJSONValue<t_CParent>::TCEJSONValue(tf_CType &&_Type)
			: TCJSONValue<t_CParent>(fg_Forward<tf_CType>(_Type))
		{
		}
	}
}
