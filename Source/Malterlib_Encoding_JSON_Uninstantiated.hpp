// Copyright © 2023 Favro Holding AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib::NEncoding
{
#ifndef DCompiler_MSVC_Workaround
	template <typename t_CParent>
	template <typename tf_CType>
	TCJSONValue<t_CParent>::TCJSONValue(tf_CType &&_Type)
		requires
		(
			NTraits::cConstructibleWith<t_CParent, tf_CType &&>
			&& !NPrivate::TCIsTCJSONValue<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CType>::CType>::mc_Value
			&& !NPrivate::TCIsTCEJSONValue<typename NTraits::TCRemoveReferenceAndQualifiers<tf_CType>::CType>::mc_Value
		)
		: t_CParent(fg_Forward<tf_CType>(_Type))
	{
	}
#endif

#ifndef DCompiler_MSVC_Workaround
	template <typename t_CParent>
	template <typename tf_CType>
	auto TCJSONValue<t_CParent>::operator = (tf_CType &&_Value) -> TCEnableIfType<!NTraits::TCIsSame<decltype(this->mp_Value = fg_Forward<tf_CType>(_Value)), CDummy>::mc_Value, CValue> &
	{
		this->mp_Value = fg_Forward<tf_CType>(_Value);
		return static_cast<CValue &>(*this);
	}
#endif

	template <typename t_CParent>
	template <typename ...tfp_CValues>
	TCJSONValue<t_CParent>::TCJSONValue(tfp_CValues && ...p_Values)
		requires ((NTraits::cIsSame<NTraits::TCRemoveReferenceAndQualifiersType<tfp_CValues>, CKeyValue> && (sizeof...(p_Values) > 0)) && ...)
	{
		auto &Object = f_Object();
		(

			[&]
			{
				DMibCheck(!Object.f_GetMember(p_Values.m_Key));
				if constexpr (NTraits::TCIsRValueReference<tfp_CValues &&>::mc_Value)
					Object.f_CreateMember(fg_Move(p_Values.m_Key)) = fg_Move(p_Values.m_Value);
				else
					Object.f_CreateMember(p_Values.m_Key) = p_Values.m_Value;
			}
			()
			, ...
		);
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
			constexpr static auto c_Flags = EJSONDialectFlag_AllowUndefined | EJSONDialectFlag_AllowInvalidFloat | EJSONDialectFlag_TrimWhitespace;

			if (!this->f_IsValid())
				o_FormatInto += "INVALID";
			else if (_Options.m_LocalOptions.m_PrettySeparator[0])
				o_FormatInto += static_cast<CValue const &>(*this).f_ToString(_Options.m_LocalOptions.m_PrettySeparator, c_Flags);
			else
				o_FormatInto += static_cast<CValue const &>(*this).f_ToString(nullptr, c_Flags);
		}
		catch (NException::CException const &_Exception)
		{
			o_FormatInto += _Exception.f_GetErrorStr();
		}
	}

	template <typename t_CParent>
	auto TCJSONValue<t_CParent>::CKey::operator = (CValue &&_Value) && -> CKeyValue
	{
		CKeyValue Return;
		Return.m_Key = fg_Move(m_Key);
		Return.m_Value = fg_Move(_Value);
		return Return;
	}

	template <typename t_CParent>
	auto TCJSONValue<t_CParent>::CKey::operator = (CValue const &_Value) && -> CKeyValue
	{
		CKeyValue Return;
		Return.m_Key = fg_Move(m_Key);
		Return.m_Value = _Value;
		return Return;
	}

	template <typename t_CParent>
	auto TCJSONValue<t_CParent>::CKey::operator = (std::initializer_list<CVoidTag> const &_Initializer) && -> CKeyValue
	{
		DMibRequire(_Initializer.size() == 0);
		CKeyValue Return;
		Return.m_Key = m_Key;
		Return.m_Value = EJSONType_Object;
		return Return;
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	template <typename tf_CStream>
	void TCJSONObject<t_CJSONValue, t_bOrdered>::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << mp_Objects;
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	template <typename tf_CStream>
	void TCJSONObject<t_CJSONValue, t_bOrdered>::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> mp_Objects;
		if constexpr (t_bOrdered)
		{
			for (auto &Object : mp_Objects)
			{
				if (mp_ObjectTree.f_FindEqual(Object.f_Name()))
					DMibError("Duplicate object in stream");
				mp_ObjectTree.f_Insert(Object);
			}
		}
	}
}

namespace NMib::NEncoding::NPrivate
{
#ifndef DCompiler_MSVC_Workaround
	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
	template <typename tf_CType>
	TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::TCJSONValueBase(tf_CType &&_Value)
		requires (NTraits::cConstructibleWith<typename TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::CVariantType, tf_CType &&>)
		: mp_Value(fg_Forward<tf_CType>(_Value))
	{
	}
#endif

	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
	template <typename tf_CStream>
	void TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << mp_Value;
	}

	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, bool t_bOrdered>
	template <typename tf_CStream>
	void TCJSONValueBase<t_TCValue, t_CTypes, t_bOrdered>::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> mp_Value;
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	template <typename tf_CStream>
	void TCObjectEntry<t_CJSONValue, t_bOrdered>::f_Feed(tf_CStream &_Stream) const
	{
		if constexpr (t_bOrdered)
			_Stream << this->mp_Name;
		_Stream << mp_Value;
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	template <typename tf_CStream>
	void TCObjectEntry<t_CJSONValue, t_bOrdered>::f_Consume(tf_CStream &_Stream)
	{
		if constexpr (t_bOrdered)
			_Stream >> this->mp_Name;
		_Stream >> mp_Value;
	}
	template <typename tf_CStream>
	void CJSONNull::f_Feed(tf_CStream &_Stream) const
	{
	}

	template <typename tf_CStream>
	void CJSONNull::f_Consume(tf_CStream &_Stream)
	{
	}

	template <typename tf_CStream>
	void CJSONBoolean::f_Feed(tf_CStream &_Stream) const
	{
		uint8 bValue = !!m_bValue;
		_Stream << bValue;
	}

	template <typename tf_CStream>
	void CJSONBoolean::f_Consume(tf_CStream &_Stream)
	{
		uint8 bValue;
		_Stream >> bValue;
		m_bValue = !!bValue;
	}

	inline_always CJSONBoolean::CJSONBoolean(bool _bValue)
		: m_bValue(_bValue)
	{
	}

	inline_always CJSONBoolean::operator bool const &() const
	{
		return m_bValue;
	}

	inline_always CJSONBoolean::operator bool &()
	{
		return m_bValue;
	}

	inline_always CJSONNull::CJSONNull(CNullPtr _Value)
	{
	}

	inline_always CJSONNull::operator CNullPtr () const
	{
		return nullptr;
	}
}
