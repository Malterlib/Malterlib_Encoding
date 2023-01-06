#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib::NEncoding
{
	template <typename t_CJSONValue, bool t_bOrdered>
	TCJSONObject<t_CJSONValue, t_bOrdered>::TCJSONObject()
	{
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	TCJSONObject<t_CJSONValue, t_bOrdered>::~TCJSONObject()
	{
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	TCJSONObject<t_CJSONValue, t_bOrdered>::TCJSONObject(TCJSONObject const &_Other)
		: mp_Objects(_Other.mp_Objects)
	{
		if constexpr (t_bOrdered)
		{
			for (auto &Object : mp_Objects)
				mp_ObjectTree.f_Insert(Object);
		}
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	TCJSONObject<t_CJSONValue, t_bOrdered>::TCJSONObject(TCJSONObject &&_Other)
		: mp_Objects(fg_Move(_Other.mp_Objects))
		, mp_ObjectTree(fg_Move(_Other.mp_ObjectTree))
	{
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	t_CJSONValue const *TCJSONObject<t_CJSONValue, t_bOrdered>::f_GetMember(NStr::CStr const &_Name) const
	{
		if constexpr (t_bOrdered)
		{
			auto pFound = mp_ObjectTree.f_FindEqual(_Name);
			if (pFound)
				return &pFound->f_Value();
			return nullptr;
		}
		else
		{
			auto pFound = mp_Objects.f_FindEqual(_Name);
			if (pFound)
				return &pFound->f_Value();
			return nullptr;
		}
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	t_CJSONValue *TCJSONObject<t_CJSONValue, t_bOrdered>::f_GetMember(NStr::CStr const &_Name)
	{
		if constexpr (t_bOrdered)
		{
			auto pFound = mp_ObjectTree.f_FindEqual(_Name);
			if (pFound)
				return &pFound->f_Value();
			return nullptr;
		}
		else
		{
			auto pFound = mp_Objects.f_FindEqual(_Name);
			if (pFound)
				return &pFound->f_Value();
			return nullptr;
		}
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	t_CJSONValue const *TCJSONObject<t_CJSONValue, t_bOrdered>::f_GetMember(NStr::CStr const &_Name, EJSONType _Type) const
	{
		if constexpr (t_bOrdered)
		{
			auto pFound = mp_ObjectTree.f_FindEqual(_Name);
			if (pFound && pFound->f_Value().f_Type() == _Type)
				return &pFound->f_Value();
			return nullptr;
		}
		else
		{
			auto pFound = mp_Objects.f_FindEqual(_Name);
			if (pFound && pFound->f_Value().f_Type() == _Type)
				return &pFound->f_Value();
			return nullptr;
		}
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	t_CJSONValue *TCJSONObject<t_CJSONValue, t_bOrdered>::f_GetMember(NStr::CStr const &_Name, EJSONType _Type)
	{
		if constexpr (t_bOrdered)
		{
			auto pFound = mp_ObjectTree.f_FindEqual(_Name);
			if (pFound && pFound->f_Value().f_Type() == _Type)
				return &pFound->f_Value();
			return nullptr;
		}
		else
		{
			auto pFound = mp_Objects.f_FindEqual(_Name);
			if (pFound && pFound->f_Value().f_Type() == _Type)
				return &pFound->f_Value();
			return nullptr;
		}
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	t_CJSONValue TCJSONObject<t_CJSONValue, t_bOrdered>::f_GetMemberValue(NStr::CStr const &_Name, t_CJSONValue const &_Default) const
	{
		if constexpr (t_bOrdered)
		{
			auto pFound = mp_ObjectTree.f_FindEqual(_Name);
			if (pFound && pFound->f_Value().f_Type() == _Default.f_Type())
				return pFound->f_Value();
			return _Default;
		}
		else
		{
			auto pFound = mp_Objects.f_FindEqual(_Name);
			if (pFound && pFound->f_Value().f_Type() == _Default.f_Type())
				return pFound->f_Value();
			return _Default;
		}
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	t_CJSONValue TCJSONObject<t_CJSONValue, t_bOrdered>::f_GetMemberValue(NStr::CStr const &_Name, t_CJSONValue &&_Default) const
	{
		if constexpr (t_bOrdered)
		{
			auto pFound = mp_ObjectTree.f_FindEqual(_Name);
			if (pFound && pFound->f_Value().f_Type() == _Default.f_Type())
				return pFound->f_Value();
			return fg_Move(_Default);
		}
		else
		{
			auto pFound = mp_Objects.f_FindEqual(_Name);
			if (pFound && pFound->f_Value().f_Type() == _Default.f_Type())
				return pFound->f_Value();
			return fg_Move(_Default);
		}
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	t_CJSONValue &TCJSONObject<t_CJSONValue, t_bOrdered>::f_CreateMember(NStr::CStr const &_Name)
	{
		if constexpr (t_bOrdered)
		{
			auto pFound = mp_ObjectTree.f_FindEqual(_Name);
			if (pFound)
				return pFound->f_Value();
			auto &NewMember = mp_Objects.f_Insert();
			NewMember.mp_Name = _Name;
			mp_ObjectTree.f_Insert(NewMember);
			return NewMember.f_Value();
		}
		else
			return mp_Objects[_Name].f_Value();
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	t_CJSONValue const &TCJSONObject<t_CJSONValue, t_bOrdered>::operator [] (NStr::CStr const &_Name) const
	{
		auto pMember = f_GetMember(_Name);
		if (!pMember)
			DMibError(fg_Format("Member '{}' not found", _Name));

		return *pMember;
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	t_CJSONValue &TCJSONObject<t_CJSONValue, t_bOrdered>::operator [](NStr::CStr const &_Name)
	{
		return f_CreateMember(_Name);
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	bool TCJSONObject<t_CJSONValue, t_bOrdered>::f_RemoveMember(NStr::CStr const &_Name)
	{
		if constexpr (t_bOrdered)
		{
			auto pFound = mp_ObjectTree.f_FindEqual(_Name);
			if (pFound)
			{
				mp_ObjectTree.f_Remove(pFound);
				mp_Objects.f_Remove(*pFound);
				return true;
			}
			return false;
		}
		else
			return mp_Objects.f_Remove(_Name);
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	void TCJSONObject<t_CJSONValue, t_bOrdered>::f_SortObjectsLexicographically()
	{
		if constexpr (t_bOrdered)
		{
			mp_Objects.f_Sort();
			for (auto &ObjectEntry : mp_Objects)
				ObjectEntry.mp_Value.f_SortObjectsLexicographically();
		}
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	void TCJSONObject<t_CJSONValue, t_bOrdered>::f_RemoveMember(typename CObjects::CIteratorConst &_Iterator)
		requires (t_bOrdered)
	{
		auto pObject = const_cast<CObjectEntry *>(&*_Iterator);
		++_Iterator;
		mp_ObjectTree.f_Remove(pObject);
		mp_Objects.f_Remove(*pObject);
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	template <typename tf_FOnObject>
	void TCJSONObject<t_CJSONValue, t_bOrdered>::f_ExtractAll(tf_FOnObject &&_fOnObject)
	{
		if constexpr (t_bOrdered)
		{
			for (auto &Object : mp_Objects)
			{
				mp_ObjectTree.f_Remove(Object);
				_fOnObject(fg_Move(Object.mp_Name), fg_Move(Object.f_Value()));
			}
			mp_Objects.f_Clear();
		}
		else
		{
			mp_Objects.f_ExtractAll
				(
					[&_fOnObject](auto &&_NodeHandle)
					{
						_fOnObject(fg_Move(_NodeHandle.f_Key()), fg_Move(_NodeHandle.f_Value().f_Value()));
					}
				)
			;
		}
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	void TCJSONObject<t_CJSONValue, t_bOrdered>::f_RemoveMember(typename CObjects::CIterator &_Iterator)
	{
		if constexpr (t_bOrdered)
		{
			auto pObject = &*_Iterator;
			mp_ObjectTree.f_Remove(pObject);
		}
		_Iterator.f_Remove();
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	void TCJSONObject<t_CJSONValue, t_bOrdered>::f_RemoveMember
		(
		 	typename NIntrusive::TCAVLTree<&NPrivate::CObjectEntryBase::mp_Link, CCompare, NMemory::CDefaultAllocator, CObjectEntry>::CIterator &_Iterator
		)
		requires (t_bOrdered)
	{
		auto pObject = &*_Iterator;
		_Iterator.f_Remove(mp_ObjectTree);
		mp_Objects.f_Remove(*pObject);
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	auto TCJSONObject<t_CJSONValue, t_bOrdered>::f_OrderedIterator() const -> typename CObjects::CIteratorConst
	{
		return mp_Objects.f_GetIterator();
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	auto TCJSONObject<t_CJSONValue, t_bOrdered>::f_OrderedIterator() -> typename CObjects::CIterator
	{
		return mp_Objects.f_GetIterator();
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	auto TCJSONObject<t_CJSONValue, t_bOrdered>::f_SortedIterator() const
		-> typename NIntrusive::TCAVLTree<&NPrivate::CObjectEntryBase::mp_Link, CCompare, NMemory::CDefaultAllocator, CObjectEntry>::CIterator
		requires (t_bOrdered)
	{
		return mp_ObjectTree.f_GetIterator();
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	bool TCJSONObject<t_CJSONValue, t_bOrdered>::f_IsEmpty() const
	{
		return mp_Objects.f_IsEmpty();
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	bool TCJSONObject<t_CJSONValue, t_bOrdered>::operator == (TCJSONObject const &_Right) const
	{
		return mp_Objects == _Right.mp_Objects;
	}

	template <typename t_CJSONValue, bool t_bOrdered>
	COrdering_Partial TCJSONObject<t_CJSONValue, t_bOrdered>::operator <=> (TCJSONObject const &_Right) const
	{
		return mp_Objects <=> _Right.mp_Objects;
	}
}
