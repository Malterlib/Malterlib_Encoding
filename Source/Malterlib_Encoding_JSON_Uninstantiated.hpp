#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib
{
	namespace NEncoding
	{
		template <>
		CJSON CJSON::fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName);

		template <>
		NStr::CStr CJSON::f_ToString(ch8 const *_pPrettySeparator) const;

		namespace NPrivate
		{
			template <template <typename t_CParent> class t_TCValue, typename ...tp_CTypes>
			template <typename tf_CType>
			TCJSONValueBase<t_TCValue, tp_CTypes...>::TCJSONValueBase(tf_CType &&_Value)
				: mp_Value(fg_Forward<tf_CType>(_Value))
			{
			}
		}

		template <typename t_CParent>
		template <typename tf_CType>
		TCJSONValue<t_CParent>::TCJSONValue(tf_CType &&_Type)
			: t_CParent(fg_Forward<tf_CType>(_Type))
		{
		}

		template <typename t_CParent>
		template <typename tf_CType>
		auto TCJSONValue<t_CParent>::operator = (tf_CType &&_Value) -> CValue &
		{
			this->mp_Value = fg_Forward<tf_CType>(_Value);
			return static_cast<CValue &>(*this);
		}
		
		template <typename t_CParent>
		template <typename tf_CType>
		auto TCJSONValue<t_CParent>::f_Insert(tf_CType &&_Value) -> CValue &
		{
			return f_Array().f_Insert(fg_Construct(fg_Forward<tf_CType>(_Value)));
		}
		
		template <typename t_CParent>
		template <typename tf_COption>
		bool TCJSONValue<t_CParent>::f_FormatParseOption(CFormatOptions &_Options, tf_COption &_Option) const
		{
			switch (_Option.m_FormatTypes.m_Format1)
			{
			case 'J':
				{
					switch (_Option.m_FormatTypes.m_Format2)
					{
					case 'P':
						_Option.f_GetData_Str(_Options.m_PrettySeparator, 16);
						return true;
					}
				}
				break;
			}
			return false;
		}

		template <typename t_CParent>
		template <typename tf_CFormatInto, typename tf_CFormatOptions>
		void TCJSONValue<t_CParent>::f_Format(tf_CFormatInto &o_FormatInto, tf_CFormatOptions const &_Options) const
		{
			try
			{
				if (!this->f_IsValid())
					o_FormatInto += "INVALID";
				else if (_Options.m_LocalOptions.m_PrettySeparator[0])
					o_FormatInto += static_cast<CValue const &>(*this).f_ToString(_Options.m_LocalOptions.m_PrettySeparator);
				else
					o_FormatInto += static_cast<CValue const &>(*this).f_ToString(nullptr);
			}
			catch (NException::CException const &_Exception)
			{
				o_FormatInto += _Exception.f_GetErrorStr();
			}
		}
	}
}
