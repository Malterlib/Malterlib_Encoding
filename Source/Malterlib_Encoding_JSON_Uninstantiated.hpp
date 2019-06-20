#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib::NEncoding
{
#ifndef DDocumentation_Doxygen
	template <>
	CJSON CJSON::fs_FromString(NStr::CStr const &_String, NStr::CStr const &_FileName, bool _bConvertNullToSpace);

	template <>
	NStr::CStr CJSON::f_ToString(ch8 const *_pPrettySeparator, bool _bAllowUndefined) const;

	template <>
	NStr::CStr CJSON::f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, bool _bAllowUndefined) const;
#endif

#ifndef DCompiler_MSVC_Workaround
	template <typename t_CParent>
	template <typename tf_CType, TCEnableIfType<NTraits::TCIsConstructorCallableWith<t_CParent, void (tf_CType &&)>::mc_Value> *>
	TCJSONValue<t_CParent>::TCJSONValue(tf_CType &&_Type)
		: t_CParent(fg_Forward<tf_CType>(_Type))
	{
	}
#endif

	template <typename t_CParent>
	template <typename tf_CType>
	auto TCJSONValue<t_CParent>::operator = (tf_CType &&_Value) -> TCEnableIfType<!NTraits::TCIsSame<decltype(this->mp_Value = fg_Forward<tf_CType>(_Value)), CDummy>::mc_Value, CValue> &
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

#ifndef DDocumentation_Doxygen

	template <typename t_CParent>
	auto TCJSONValue<t_CParent>::CKey::operator = (CValue &&_Value) && -> CKeyValue
	{
		CKeyValue Return;
		Return.m_Key = fg_Move(m_Key);
		Return.m_Value = fg_Move(_Value);
		return Return;
	}

	template <typename t_CParent>
	auto TCJSONValue<t_CParent>::CKey::operator = (TCInitializerList<CVoidTag> const &_Initializer) && -> CKeyValue
	{
		DMibRequire(_Initializer.size() == 0);
		CKeyValue Return;
		Return.m_Key = m_Key;
		Return.m_Value = EJSONType_Object;
		return Return;
	}
#endif

	template <typename t_CJSONValue>
	template <typename tf_CStream>
	void TCJSONObject<t_CJSONValue>::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << mp_Objects;
	}

	template <typename t_CJSONValue>
	template <typename tf_CStream>
	void TCJSONObject<t_CJSONValue>::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> mp_Objects;
		for (auto &Object : mp_Objects)
		{
			if (mp_ObjectTree.f_FindEqual(Object.f_Name()))
				DMibError("Duplicate object in stream");
			mp_ObjectTree.f_Insert(Object);
		}
	}
}

namespace NMib::NEncoding::NPrivate
{
#ifndef DCompiler_MSVC_Workaround
	template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
	template <typename tf_CType, TCEnableIfType<NTraits::TCIsConstructorCallableWith<typename TCJSONValueBase<t_TCValue, t_CTypes>::CVariantType, void (tf_CType &&)>::mc_Value> *>
	TCJSONValueBase<t_TCValue, t_CTypes>::TCJSONValueBase(tf_CType &&_Value)
		: mp_Value(fg_Forward<tf_CType>(_Value))
	{
	}
#endif

	template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
	template <typename tf_CStream>
	void TCJSONValueBase<t_TCValue, t_CTypes>::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << mp_Value;
	}

	template <template <typename t_CParent> class t_TCValue, typename t_CTypes>
	template <typename tf_CStream>
	void TCJSONValueBase<t_TCValue, t_CTypes>::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> mp_Value;
	}

	template <typename t_CJSONValue>
	template <typename tf_CStream>
	void TCObjectEntry<t_CJSONValue>::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << mp_Name;
		_Stream << mp_Value;
	}

	template <typename t_CJSONValue>
	template <typename tf_CStream>
	void TCObjectEntry<t_CJSONValue>::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> mp_Name;
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
