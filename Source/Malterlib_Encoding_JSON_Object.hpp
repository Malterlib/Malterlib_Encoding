#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib::NEncoding
{
	template <typename t_CJSONValue>
	TCJSONObject<t_CJSONValue>::TCJSONObject()
	{
	}

	template <typename t_CJSONValue>
	TCJSONObject<t_CJSONValue>::~TCJSONObject()
	{
	}

	template <typename t_CJSONValue>
	TCJSONObject<t_CJSONValue>::TCJSONObject(TCJSONObject const &_Other)
		: mp_Objects(_Other.mp_Objects)
	{
		for (auto &Object : mp_Objects)
			mp_ObjectTree.f_Insert(Object);
	}

	template <typename t_CJSONValue>
	TCJSONObject<t_CJSONValue>::TCJSONObject(TCJSONObject &&_Other)
		: mp_Objects(fg_Move(_Other.mp_Objects))
		, mp_ObjectTree(fg_Move(_Other.mp_ObjectTree))
	{
	}

	template <typename t_CJSONValue>
	t_CJSONValue const *TCJSONObject<t_CJSONValue>::f_GetMember(NStr::CStr const &_Name) const
	{
		auto pFound = mp_ObjectTree.f_FindEqual(_Name);
		if (pFound)
			return &pFound->f_Value();
		return nullptr;
	}

	template <typename t_CJSONValue>
	t_CJSONValue *TCJSONObject<t_CJSONValue>::f_GetMember(NStr::CStr const &_Name)
	{
		auto pFound = mp_ObjectTree.f_FindEqual(_Name);
		if (pFound)
			return &pFound->f_Value();
		return nullptr;
	}

	template <typename t_CJSONValue>
	t_CJSONValue const *TCJSONObject<t_CJSONValue>::f_GetMember(NStr::CStr const &_Name, EJSONType _Type) const
	{
		auto pFound = mp_ObjectTree.f_FindEqual(_Name);
		if (pFound && pFound->f_Value().f_Type() == _Type)
			return &pFound->f_Value();
		return nullptr;
	}

	template <typename t_CJSONValue>
	t_CJSONValue *TCJSONObject<t_CJSONValue>::f_GetMember(NStr::CStr const &_Name, EJSONType _Type)
	{
		auto pFound = mp_ObjectTree.f_FindEqual(_Name);
		if (pFound && pFound->f_Value().f_Type() == _Type)
			return &pFound->f_Value();
		return nullptr;
	}

	template <typename t_CJSONValue>
	t_CJSONValue TCJSONObject<t_CJSONValue>::f_GetMemberValue(NStr::CStr const &_Name, t_CJSONValue const &_Default) const
	{
		auto pFound = mp_ObjectTree.f_FindEqual(_Name);
		if (pFound && pFound->f_Value().f_Type() == _Default.f_Type())
			return pFound->f_Value();
		return _Default;
	}

	template <typename t_CJSONValue>
	t_CJSONValue &TCJSONObject<t_CJSONValue>::f_CreateMember(NStr::CStr const &_Name)
	{
		auto pFound = mp_ObjectTree.f_FindEqual(_Name);
		if (pFound)
			return pFound->f_Value();
		auto &NewMember = mp_Objects.f_Insert();
		NewMember.mp_Name = _Name;
		mp_ObjectTree.f_Insert(NewMember);
		return NewMember.f_Value();
	}

	template <typename t_CJSONValue>
	t_CJSONValue const &TCJSONObject<t_CJSONValue>::operator [] (NStr::CStr const &_Name) const
	{
		auto pMember = f_GetMember(_Name);
		if (!pMember)
			DMibError(fg_Format("Member '{}' not found", _Name));

		return *pMember;
	}

	template <typename t_CJSONValue>
	t_CJSONValue &TCJSONObject<t_CJSONValue>::operator [](NStr::CStr const &_Name)
	{
		return f_CreateMember(_Name);
	}

	template <typename t_CJSONValue>
	bool TCJSONObject<t_CJSONValue>::f_RemoveMember(NStr::CStr const &_Name)
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

	template <typename t_CJSONValue>
	void TCJSONObject<t_CJSONValue>::f_SortObjectsLexicographically()
	{
		mp_Objects.f_Sort();
		for (auto &ObjectEntry : mp_Objects)
			ObjectEntry.mp_Value.f_SortObjectsLexicographically();
	}

	template <typename t_CJSONValue>
	void TCJSONObject<t_CJSONValue>::f_RemoveMember(typename NContainer::TCLinkedList<CObjectEntry>::CIteratorConst &_Iterator)
	{
		auto pObject = const_cast<CObjectEntry *>(&*_Iterator);
		++_Iterator;
		mp_ObjectTree.f_Remove(pObject);
		mp_Objects.f_Remove(*pObject);
	}

	template <typename t_CJSONValue>
	void TCJSONObject<t_CJSONValue>::f_RemoveMember(typename NContainer::TCLinkedList<CObjectEntry>::CIterator &_Iterator)
	{
		auto pObject = &*_Iterator;
		mp_ObjectTree.f_Remove(pObject);
		_Iterator.f_Remove();
	}

	template <typename t_CJSONValue>
	void TCJSONObject<t_CJSONValue>::f_RemoveMember
		(
		 	typename NIntrusive::TCAVLTree<&NPrivate::CObjectEntryBase::mp_Link, CCompare, NMemory::CDefaultAllocator, CObjectEntry>::CIterator &_Iterator
		)
	{
		auto pObject = &*_Iterator;
		_Iterator.f_Remove(mp_ObjectTree);
		mp_Objects.f_Remove(*pObject);
	}

	template <typename t_CJSONValue>
	auto TCJSONObject<t_CJSONValue>::f_OrderedIterator() const -> typename NContainer::TCLinkedList<CObjectEntry>::CIteratorConst
	{
		return mp_Objects.f_GetIterator();
	}

	template <typename t_CJSONValue>
	auto TCJSONObject<t_CJSONValue>::f_OrderedIterator() -> typename NContainer::TCLinkedList<CObjectEntry>::CIterator
	{
		return mp_Objects.f_GetIterator();
	}

	template <typename t_CJSONValue>
	auto TCJSONObject<t_CJSONValue>::f_SortedIterator() const
		-> typename NIntrusive::TCAVLTree<&NPrivate::CObjectEntryBase::mp_Link, CCompare, NMemory::CDefaultAllocator, CObjectEntry>::CIterator
	{
		return mp_ObjectTree.f_GetIterator();
	}

	template <typename t_CJSONValue>
	bool TCJSONObject<t_CJSONValue>::f_IsEmpty() const
	{
		return mp_Objects.f_IsEmpty();
	}

	template <typename t_CJSONValue>
	bool TCJSONObject<t_CJSONValue>::operator == (TCJSONObject const &_Right) const
	{
		return mp_Objects == _Right.mp_Objects;
	}

	template <typename t_CJSONValue>
	bool TCJSONObject<t_CJSONValue>::operator < (TCJSONObject const &_Right) const
	{
		return mp_Objects < _Right.mp_Objects;
	}
}
