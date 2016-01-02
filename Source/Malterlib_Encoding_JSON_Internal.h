#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib
{
	namespace NEncoding
	{
		namespace NPrivate
		{
			template <template <typename t_CParent> class t_TCValue, typename ...tp_CTypes>
			class TCJSONValueBase
			{
			public:
				using CValue = t_TCValue<TCJSONValueBase>;

				template <typename tf_CType>
				TCJSONValueBase(tf_CType &&_Value);
				TCJSONValueBase(TCJSONValueBase const &_Value);
				TCJSONValueBase(TCJSONValueBase &_Value);
				TCJSONValueBase(TCJSONValueBase &&_Value);

				TCJSONValueBase(pfp64 _Value);
				TCJSONValueBase(pfp32 _Value);
				TCJSONValueBase(fp32 _Value);
				TCJSONValueBase();
				~TCJSONValueBase();

			protected:
				// Members
				NContainer::TCVariant<void, CNullPtr, NStr::CStr, int64, fp64, bool, TCJSONObject<CValue>, NContainer::TCVector<CValue>, tp_CTypes...> mp_Value;
			};
		}
		
		template <typename t_CJSONObject>
		bool fg_ValidateType(t_CJSONObject const *_pObject, EJSONType _Type)
		{
			return _pObject && _pObject->f_Type() == _Type;
		}
	}
}

