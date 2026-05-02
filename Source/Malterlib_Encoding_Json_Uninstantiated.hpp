// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
	template <typename t_CParent>
	template <typename tf_CType>
	TCJsonValue<t_CParent>::TCJsonValue(tf_CType &&_Type)
		requires
		(
			NTraits::cIsPlacementNewConstructibleWith<t_CParent, tf_CType &&>
			&& !NPrivate::TCIsTCJsonValue<NTraits::TCRemoveReferenceAndQualifiers<tf_CType>>::mc_Value
			&& !NPrivate::TCIsTCEJsonValue<NTraits::TCRemoveReferenceAndQualifiers<tf_CType>>::mc_Value
		)
		: t_CParent(fg_Forward<tf_CType>(_Type))
	{
	}

	template <typename t_CParent>
	template <typename tf_CType>
	auto TCJsonValue<t_CParent>::operator = (tf_CType &&_Value) -> TCEnableIf<!NTraits::cIsSame<decltype(this->mp_Value = fg_Forward<tf_CType>(_Value)), CDummy>, CValue> &
	{
		this->mp_Value = fg_Forward<tf_CType>(_Value);
		return static_cast<CValue &>(*this);
	}

	template <typename t_CParent>
	template <typename ...tfp_CValues>
	TCJsonValue<t_CParent>::TCJsonValue(tfp_CValues && ...p_Values)
		requires ((NTraits::cIsSame<NTraits::TCRemoveReferenceAndQualifiers<tfp_CValues>, CKeyValue> && (sizeof...(p_Values) > 0)) && ...)
	{
		auto &Object = f_Object();
		(

			[&]
			{
				DMibCheck(!Object.f_GetMember(p_Values.m_Key));
				if constexpr (NTraits::cIsRValueReference<tfp_CValues &&>)
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
	auto TCJsonValue<t_CParent>::f_Insert(tf_CType &&_Value) -> CValue &
	{
		return f_Array().f_Insert(fg_Construct(fg_Forward<tf_CType>(_Value)));
	}

	template <typename t_CParent>
	template <typename tf_COption>
	bool TCJsonValue<t_CParent>::f_FormatParseOption(CFormatOptions &_Options, tf_COption &_Option) const
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
	void TCJsonValue<t_CParent>::f_Format(tf_CFormatInto &o_FormatInto, tf_CFormatOptions const &_Options) const
	{
		try
		{
			constexpr static auto c_Flags = EJsonDialectFlag_AllowUndefined | EJsonDialectFlag_AllowInvalidFloat | EJsonDialectFlag_TrimWhitespace;

			if (_Options.m_LocalOptions.m_PrettySeparator[0])
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
	auto TCJsonValue<t_CParent>::CKey::operator = (CValue &&_Value) && -> CKeyValue
	{
		CKeyValue Return;
		Return.m_Key = fg_Move(m_Key);
		Return.m_Value = fg_Move(_Value);
		return Return;
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::CKey::operator = (CValue const &_Value) && -> CKeyValue
	{
		CKeyValue Return;
		Return.m_Key = fg_Move(m_Key);
		Return.m_Value = _Value;
		return Return;
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::CKey::operator = (std::initializer_list<CVoidTag> const &_Initializer) && -> CKeyValue
	{
		DMibRequire(_Initializer.size() == 0);
		CKeyValue Return;
		Return.m_Key = m_Key;
		Return.m_Value = EJsonType_Object;
		return Return;
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	template <typename tf_CStream>
	void TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << mp_Objects;
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	template <typename tf_CStream>
	void TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> mp_Objects;
		if constexpr (mc_bOrdered)
		{
			for (auto &Object : mp_Objects)
			{
				if (mp_ObjectTree.f_FindEqual(Object.f_Name()))
					DMibError("Duplicate object in stream");
				mp_ObjectTree.f_Insert(Object);
			}
		}
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	template <typename tf_FOnObject>
	void TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_ExtractAll(tf_FOnObject &&_fOnObject)
	{
		if constexpr (mc_bOrdered)
		{
			mp_ObjectTree.f_Clear();
			for (auto iIter = mp_Objects.f_GetIterator(); iIter; )
				_fOnObject(CObjectEntryHandle(iIter.f_ExtractNode()));
		}
		else
		{
			mp_Objects.f_ExtractAll
				(
					[&_fOnObject](auto &&_NodeHandle)
					{
						_fOnObject(CObjectEntryHandle(fg_Move(_NodeHandle)));
					}
				)
			;
		}
	}
}

namespace NMib::NEncoding::NPrivate
{
#ifndef DCompiler_MSVC_Workaround
	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
	template <typename tf_CType>
	TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::TCJsonValueBase(tf_CType &&_Value)
		requires (NTraits::cIsPlacementNewConstructibleWith<typename TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::CVariantType, tf_CType &&>)
		: mp_Value(fg_Forward<tf_CType>(_Value))
	{
	}
#endif

	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
	template <typename tf_CStream>
	void TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << mp_Value;

		if constexpr (mc_bPreserveComments)
		{
			if (mp_Value.f_GetTypeID() == EJsonType_String)
			{
				uint8 StringUserData = mp_Value.template f_Get<EJsonType_String>().f_GetUserData();
				_Stream << StringUserData;
			}
			_Stream << mp_ValueTrivia;
		}
	}

	template <template <typename t_CParent> class t_TCValue, typename t_CTypes, EJsonContainerFlag t_ContainerFlags>
	template <typename tf_CStream>
	void TCJsonValueBase<t_TCValue, t_CTypes, t_ContainerFlags>::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> mp_Value;

		if constexpr (mc_bPreserveComments)
		{
			if (mp_Value.f_GetTypeID() == EJsonType_String)
			{
				uint8 StringUserData;
				_Stream >> StringUserData;
				mp_Value.template f_Get<EJsonType_String>().f_SetUserData(StringUserData);
			}
			_Stream >> mp_ValueTrivia;
		}
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	template <typename tf_CStream>
	void TCObjectEntry<t_CJsonValue, t_ContainerFlags>::f_Feed(tf_CStream &_Stream) const
	{
		if constexpr (mc_bOrdered)
			_Stream << this->mp_Name;

		_Stream << mp_Value;

		if constexpr (mc_bPreserveComments)
		{
			uint8 KeyUserData = f_Name().f_GetUserData();
			_Stream << KeyUserData;
			_Stream << mp_KeyTrivia;
		}
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	template <typename tf_CStream>
	void TCObjectEntry<t_CJsonValue, t_ContainerFlags>::f_Consume(tf_CStream &_Stream)
	{
		if constexpr (mc_bOrdered)
			_Stream >> this->mp_Name;

		_Stream >> mp_Value;

		if constexpr (mc_bPreserveComments)
		{
			uint8 KeyUserData;
			_Stream >> KeyUserData;
			const_cast<NStr::CStr &>(f_Name()).f_SetUserData(KeyUserData);
			_Stream >> mp_KeyTrivia;
		}
	}

	template <typename tf_CStream>
	void CJsonValueTriviaSlots::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << m_Leading;
		_Stream << m_Trailing;
		_Stream << m_Interior;

		uint8 Flags = 0;
		if (m_bLeadingSet)
			Flags |= uint8(fg_Bit(0));
		if (m_bTrailingSet)
			Flags |= uint8(fg_Bit(1));
		if (m_bLeadingHasComma)
			Flags |= uint8(fg_Bit(2));
		if (m_bTrailingHasComma)
			Flags |= uint8(fg_Bit(3));
		_Stream << Flags;
	}

	template <typename tf_CStream>
	void CJsonValueTriviaSlots::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> m_Leading;
		_Stream >> m_Trailing;
		_Stream >> m_Interior;

		uint8 Flags;
		_Stream >> Flags;
		m_bLeadingSet = (Flags & uint8(fg_Bit(0))) != 0;
		m_bTrailingSet = (Flags & uint8(fg_Bit(1))) != 0;
		m_bLeadingHasComma = (Flags & uint8(fg_Bit(2))) != 0;
		m_bTrailingHasComma = (Flags & uint8(fg_Bit(3))) != 0;
	}

	template <typename tf_CStream>
	void CJsonKeyTriviaSlots::f_Feed(tf_CStream &_Stream) const
	{
		_Stream << m_Leading;
		_Stream << m_Trailing;

		uint8 Flags = 0;
		if (m_bLeadingSet)
			Flags |= uint8(fg_Bit(0));
		if (m_bTrailingSet)
			Flags |= uint8(fg_Bit(1));
		if (m_bLeadingHasComma)
			Flags |= uint8(fg_Bit(2));
		_Stream << Flags;
	}

	template <typename tf_CStream>
	void CJsonKeyTriviaSlots::f_Consume(tf_CStream &_Stream)
	{
		_Stream >> m_Leading;
		_Stream >> m_Trailing;

		uint8 Flags;
		_Stream >> Flags;
		m_bLeadingSet = (Flags & uint8(fg_Bit(0))) != 0;
		m_bTrailingSet = (Flags & uint8(fg_Bit(1))) != 0;
		m_bLeadingHasComma = (Flags & uint8(fg_Bit(2))) != 0;
	}
	template <typename tf_CStream>
	void CJsonNull::f_Feed(tf_CStream &_Stream) const
	{
	}

	template <typename tf_CStream>
	void CJsonNull::f_Consume(tf_CStream &_Stream)
	{
	}

	template <typename tf_CStream>
	void CJsonBoolean::f_Feed(tf_CStream &_Stream) const
	{
		uint8 bValue = !!m_bValue;
		_Stream << bValue;
	}

	template <typename tf_CStream>
	void CJsonBoolean::f_Consume(tf_CStream &_Stream)
	{
		uint8 bValue;
		_Stream >> bValue;
		m_bValue = !!bValue;
	}

	inline_always CJsonBoolean::CJsonBoolean(bool _bValue)
		: m_bValue(_bValue)
	{
	}

	inline_always CJsonBoolean::operator bool const &() const
	{
		return m_bValue;
	}

	inline_always CJsonBoolean::operator bool &()
	{
		return m_bValue;
	}

	inline_always CJsonNull::CJsonNull(CNullPtr _Value)
	{
	}

	inline_always CJsonNull::operator CNullPtr () const
	{
		return nullptr;
	}
}
