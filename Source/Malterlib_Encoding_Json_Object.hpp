// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
	template <typename t_CJsonValue, bool t_bOrdered>
	TCJsonObject<t_CJsonValue, t_bOrdered>::TCJsonObject()
	{
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	TCJsonObject<t_CJsonValue, t_bOrdered>::~TCJsonObject()
	{
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	TCJsonObject<t_CJsonValue, t_bOrdered>::TCJsonObject(TCJsonObject const &_Other)
		: mp_Objects(_Other.mp_Objects)
	{
		if constexpr (t_bOrdered)
		{
			for (auto &Object : mp_Objects)
				mp_ObjectTree.f_Insert(Object);
		}
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	TCJsonObject<t_CJsonValue, t_bOrdered>::TCJsonObject(TCJsonObject &&_Other)
		: mp_Objects(fg_Move(_Other.mp_Objects))
		, mp_ObjectTree(fg_Move(_Other.mp_ObjectTree))
	{
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	template <typename tf_CJsonValue, bool tf_bOrdered>
	TCJsonObject<t_CJsonValue, t_bOrdered>::TCJsonObject(TCJsonObject<tf_CJsonValue, tf_bOrdered> const &_Other)
	{
		static_assert(t_bOrdered != tf_bOrdered);

		for (auto &Object : _Other)
			f_CreateMember(Object.f_Name()) = t_CJsonValue(Object.f_Value());
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	template <typename tf_CJsonValue, bool tf_bOrdered>
	TCJsonObject<t_CJsonValue, t_bOrdered>::TCJsonObject(TCJsonObject<tf_CJsonValue, tf_bOrdered> &&_Other)
	{
		static_assert(t_bOrdered != tf_bOrdered);

		for (auto &Object : _Other)
			f_CreateMember(Object.f_Name()) = t_CJsonValue(fg_Move(Object.f_Value()));
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue const *TCJsonObject<t_CJsonValue, t_bOrdered>::f_GetMember(NStr::CStr const &_Name) const
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

	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue *TCJsonObject<t_CJsonValue, t_bOrdered>::f_GetMember(NStr::CStr const &_Name)
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

	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue const *TCJsonObject<t_CJsonValue, t_bOrdered>::f_GetMember(NStr::CStr const &_Name, EJsonType _Type) const
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

	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue *TCJsonObject<t_CJsonValue, t_bOrdered>::f_GetMember(NStr::CStr const &_Name, EJsonType _Type)
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

	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue TCJsonObject<t_CJsonValue, t_bOrdered>::f_GetMemberValue(NStr::CStr const &_Name, t_CJsonValue const &_Default) const
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

	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue TCJsonObject<t_CJsonValue, t_bOrdered>::f_GetMemberValue(NStr::CStr const &_Name, t_CJsonValue &&_Default) const
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

	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue &TCJsonObject<t_CJsonValue, t_bOrdered>::f_CreateMember(NStr::CStr const &_Name)
	{
		if constexpr (t_bOrdered)
		{
			return mp_ObjectTree.f_FindEqualOrInsert
				(
					_Name
					, [&]() -> CObjectEntry *
					{
						auto &NewMember = mp_Objects.f_Insert();
						NewMember.mp_Name = _Name;
						return &NewMember;
					}
				)->f_Value()
			;
		}
		else
			return mp_Objects[_Name].f_Value();
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue &TCJsonObject<t_CJsonValue, t_bOrdered>::f_CreateMember(NStr::CStr &&_Name)
	{
		if constexpr (t_bOrdered)
		{
			return mp_ObjectTree.f_FindEqualOrInsert
				(
					_Name
					, [&]() -> CObjectEntry *
					{
						auto &NewMember = mp_Objects.f_Insert();
						NewMember.mp_Name = fg_Move(_Name);
						return &NewMember;
					}
				)->f_Value()
			;
		}
		else
			return mp_Objects[fg_Move(_Name)].f_Value();
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue const &TCJsonObject<t_CJsonValue, t_bOrdered>::operator [] (NStr::CStr const &_Name) const
	{
		auto pMember = f_GetMember(_Name);
		if (!pMember)
			DMibError(fg_Format("Member '{}' not found", _Name));

		return *pMember;
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue &TCJsonObject<t_CJsonValue, t_bOrdered>::operator [] (NStr::CStr const &_Name)
	{
		return f_CreateMember(_Name);
	}


	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue &TCJsonObject<t_CJsonValue, t_bOrdered>::operator () (NStr::CStr const &_Name)
	{
		auto pMember = f_GetMember(_Name);
		if (!pMember)
			DMibError(fg_Format("Member '{}' not found", _Name));

		return *pMember;
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	bool TCJsonObject<t_CJsonValue, t_bOrdered>::f_RemoveMember(NStr::CStr const &_Name)
	{
		if constexpr (t_bOrdered)
		{
			auto pRemoved = mp_ObjectTree.f_FindEqualAndRemove(_Name);
			if (pRemoved)
			{
				mp_Objects.f_Remove(*pRemoved);
				return true;
			}
			return false;
		}
		else
			return mp_Objects.f_Remove(_Name);
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	void TCJsonObject<t_CJsonValue, t_bOrdered>::f_SortObjectsLexicographically()
	{
		if constexpr (t_bOrdered)
		{
			mp_Objects.f_Sort();
			for (auto &ObjectEntry : mp_Objects)
				ObjectEntry.mp_Value.f_SortObjectsLexicographically();
		}
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	void TCJsonObject<t_CJsonValue, t_bOrdered>::f_RemoveMember(typename CObjects::CIteratorConst &_Iterator)
		requires (t_bOrdered)
	{
		auto pObject = const_cast<CObjectEntry *>(&*_Iterator);
		++_Iterator;
		mp_ObjectTree.f_Remove(pObject);
		mp_Objects.f_Remove(*pObject);
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	void TCJsonObject<t_CJsonValue, t_bOrdered>::f_RemoveMember(typename CObjects::CIterator &_Iterator)
	{
		if constexpr (t_bOrdered)
		{
			auto pObject = &*_Iterator;
			mp_ObjectTree.f_Remove(pObject);
		}
		_Iterator.f_Remove();
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	void TCJsonObject<t_CJsonValue, t_bOrdered>::f_RemoveMember
		(
			typename NIntrusive::TCAVLTree<&NPrivate::CObjectEntryBase::mp_Link, CCompare, NMemory::CDefaultAllocator, CObjectEntry>::CIterator &_Iterator
		)
		requires (t_bOrdered)
	{
		auto pObject = &*_Iterator;
		_Iterator.f_Remove(mp_ObjectTree);
		mp_Objects.f_Remove(*pObject);
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	auto TCJsonObject<t_CJsonValue, t_bOrdered>::f_OrderedIterator() const -> typename CObjects::CIteratorConst
	{
		return mp_Objects.f_GetIterator();
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	auto TCJsonObject<t_CJsonValue, t_bOrdered>::f_OrderedIterator() -> typename CObjects::CIterator
	{
		return mp_Objects.f_GetIterator();
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	auto TCJsonObject<t_CJsonValue, t_bOrdered>::f_SortedIterator() const
		-> typename NIntrusive::TCAVLTree<&NPrivate::CObjectEntryBase::mp_Link, CCompare, NMemory::CDefaultAllocator, CObjectEntry>::CIterator
		requires (t_bOrdered)
	{
		return mp_ObjectTree.f_GetIterator();
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	bool TCJsonObject<t_CJsonValue, t_bOrdered>::f_IsEmpty() const
	{
		return mp_Objects.f_IsEmpty();
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	bool TCJsonObject<t_CJsonValue, t_bOrdered>::operator == (TCJsonObject const &_Right) const noexcept
	{
		return mp_Objects == _Right.mp_Objects;
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	COrdering_Partial TCJsonObject<t_CJsonValue, t_bOrdered>::operator <=> (TCJsonObject const &_Right) const noexcept
	{
		return mp_Objects <=> _Right.mp_Objects;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Destructive iteration and node extraction (ordered mode) - member function implementations
	///////////////////////////////////////////////////////////////////////////////////////////////

	// TCJsonObjectEntryHandle implementations
	template <typename t_CJsonObject>
	TCJsonObjectEntryHandle<t_CJsonObject>::TCJsonObjectEntryHandle(TCJsonObjectEntryHandle &&_Other) noexcept
		: mp_ListHandle(fg_Move(_Other.mp_ListHandle))
	{
	}

	template <typename t_CJsonObject>
	TCJsonObjectEntryHandle<t_CJsonObject> &TCJsonObjectEntryHandle<t_CJsonObject>::operator = (TCJsonObjectEntryHandle &&_Other) noexcept
	{
		mp_ListHandle = fg_Move(_Other.mp_ListHandle);
		return *this;
	}

	template <typename t_CJsonObject>
	bool TCJsonObjectEntryHandle<t_CJsonObject>::f_IsEmpty() const noexcept
	{
		return mp_ListHandle.f_IsEmpty();
	}

	template <typename t_CJsonObject>
	TCJsonObjectEntryHandle<t_CJsonObject>::operator bool() const noexcept
	{
		return !!mp_ListHandle;
	}

	template <typename t_CJsonObject>
	NStr::CStr &TCJsonObjectEntryHandle<t_CJsonObject>::f_Name() noexcept
	{
		return const_cast<NStr::CStr &>(mp_ListHandle->f_Name());
	}

	template <typename t_CJsonObject>
	NStr::CStr const &TCJsonObjectEntryHandle<t_CJsonObject>::f_Name() const noexcept
	{
		return mp_ListHandle->f_Name();
	}

	template <typename t_CJsonObject>
	NStr::CStr &TCJsonObjectEntryHandle<t_CJsonObject>::f_Key() noexcept
	{
		return const_cast<NStr::CStr &>(mp_ListHandle->f_Key());
	}

	template <typename t_CJsonObject>
	NStr::CStr const &TCJsonObjectEntryHandle<t_CJsonObject>::f_Key() const noexcept
	{
		return mp_ListHandle->f_Key();
	}

	template <typename t_CJsonObject>
	auto TCJsonObjectEntryHandle<t_CJsonObject>::f_Value() noexcept -> CJsonValue &
	{
		return mp_ListHandle->f_Value();
	}

	template <typename t_CJsonObject>
	auto TCJsonObjectEntryHandle<t_CJsonObject>::f_Value() const noexcept -> CJsonValue const &
	{
		return mp_ListHandle->f_Value();
	}

	template <typename t_CJsonObject>
	TCJsonObjectEntryHandle<t_CJsonObject>::TCJsonObjectEntryHandle(CListHandle &&_ListHandle)
		: mp_ListHandle(fg_Move(_ListHandle))
	{
	}

	// TCJsonOrderedDestructiveIterator implementations
	template <typename t_CJsonObject>
	TCJsonOrderedDestructiveIterator<t_CJsonObject>::TCJsonOrderedDestructiveIterator(TCJsonOrderedDestructiveIterator &&_Other) noexcept
		: mp_Iter(fg_Move(_Other.mp_Iter))
		, mp_pObject(fg_Exchange(_Other.mp_pObject, nullptr))
	{
	}

	template <typename t_CJsonObject>
	TCJsonOrderedDestructiveIterator<t_CJsonObject> &TCJsonOrderedDestructiveIterator<t_CJsonObject>::operator = (TCJsonOrderedDestructiveIterator &&_Other) noexcept
	{
		fp_Clear();
		mp_Iter = fg_Move(_Other.mp_Iter);
		mp_pObject = fg_Exchange(_Other.mp_pObject, nullptr);
		return *this;
	}

	template <typename t_CJsonObject>
	TCJsonOrderedDestructiveIterator<t_CJsonObject>::~TCJsonOrderedDestructiveIterator()
	{
		fp_Clear();
	}

	template <typename t_CJsonObject>
	TCJsonOrderedDestructiveIterator<t_CJsonObject>::operator bool() const
	{
		return !!mp_Iter;
	}

	template <typename t_CJsonObject>
	auto TCJsonOrderedDestructiveIterator<t_CJsonObject>::f_GetCurrent() const -> CObjectEntry *
	{
		return mp_Iter.f_GetCurrent();
	}

	template <typename t_CJsonObject>
	auto TCJsonOrderedDestructiveIterator<t_CJsonObject>::operator->() const -> CObjectEntry *
	{
		return f_GetCurrent();
	}

	template <typename t_CJsonObject>
	auto TCJsonOrderedDestructiveIterator<t_CJsonObject>::operator*() const -> CObjectEntry &
	{
		return *f_GetCurrent();
	}

	template <typename t_CJsonObject>
	void TCJsonOrderedDestructiveIterator<t_CJsonObject>::operator++()
	{
		++mp_Iter;
	}

	template <typename t_CJsonObject>
	auto TCJsonOrderedDestructiveIterator<t_CJsonObject>::f_ExtractNode() -> CObjectEntryHandle
	{
		DMibFastCheck(mp_Iter && mp_pObject);
		mp_pObject->mp_ObjectTree.f_Remove(&*mp_Iter);
		return CObjectEntryHandle(mp_Iter.f_ExtractNode());
	}

	template <typename t_CJsonObject>
	TCJsonOrderedDestructiveIterator<t_CJsonObject>::TCJsonOrderedDestructiveIterator(t_CJsonObject &_Object)
		: mp_Iter(_Object.mp_Objects.f_GetIterator())
		, mp_pObject(&_Object)
	{
	}

	template <typename t_CJsonObject>
	void TCJsonOrderedDestructiveIterator<t_CJsonObject>::fp_Clear()
	{
		if (mp_pObject)
		{
			mp_pObject->mp_ObjectTree.f_Clear();
			mp_pObject->mp_Objects.f_Clear();
			mp_pObject = nullptr;
		}
	}

	// TCJsonSortedDestructiveIterator implementations
	template <typename t_CJsonObject>
	TCJsonSortedDestructiveIterator<t_CJsonObject>::TCJsonSortedDestructiveIterator(TCJsonSortedDestructiveIterator &&_Other) noexcept
		: mp_Iter(fg_Move(_Other.mp_Iter))
		, mp_pObject(fg_Exchange(_Other.mp_pObject, nullptr))
	{
	}

	template <typename t_CJsonObject>
	TCJsonSortedDestructiveIterator<t_CJsonObject> &TCJsonSortedDestructiveIterator<t_CJsonObject>::operator = (TCJsonSortedDestructiveIterator &&_Other) noexcept
	{
		fp_Clear();
		mp_Iter = fg_Move(_Other.mp_Iter);
		mp_pObject = fg_Exchange(_Other.mp_pObject, nullptr);
		return *this;
	}

	template <typename t_CJsonObject>
	TCJsonSortedDestructiveIterator<t_CJsonObject>::~TCJsonSortedDestructiveIterator()
	{
		fp_Clear();
	}

	template <typename t_CJsonObject>
	TCJsonSortedDestructiveIterator<t_CJsonObject>::operator bool() const
	{
		return !!mp_Iter;
	}

	template <typename t_CJsonObject>
	auto TCJsonSortedDestructiveIterator<t_CJsonObject>::f_GetCurrent() const -> CObjectEntry *
	{
		return mp_Iter.f_GetCurrent();
	}

	template <typename t_CJsonObject>
	auto TCJsonSortedDestructiveIterator<t_CJsonObject>::operator->() const -> CObjectEntry *
	{
		return f_GetCurrent();
	}

	template <typename t_CJsonObject>
	auto TCJsonSortedDestructiveIterator<t_CJsonObject>::operator*() const -> CObjectEntry &
	{
		return *f_GetCurrent();
	}

	template <typename t_CJsonObject>
	void TCJsonSortedDestructiveIterator<t_CJsonObject>::operator++()
	{
		++mp_Iter;
	}

	template <typename t_CJsonObject>
	auto TCJsonSortedDestructiveIterator<t_CJsonObject>::f_ExtractNode() -> CObjectEntryHandle
	{
		DMibFastCheck(mp_Iter && mp_pObject);
		// Extract current node without rebalancing (efficient for destructive iteration)
		// This also advances the iterator to the next node
		CObjectEntry *pExtracted = mp_Iter.template f_ExtractCurrentNoRebalance<false>(mp_pObject->mp_ObjectTree);
		return CObjectEntryHandle(mp_pObject->mp_Objects.f_Extract(*pExtracted));
	}

	template <typename t_CJsonObject>
	TCJsonSortedDestructiveIterator<t_CJsonObject>::TCJsonSortedDestructiveIterator(t_CJsonObject &_Object)
		: mp_Iter(_Object.mp_ObjectTree.f_GetIterator())
		, mp_pObject(&_Object)
	{
	}

	template <typename t_CJsonObject>
	void TCJsonSortedDestructiveIterator<t_CJsonObject>::fp_Clear()
	{
		if (mp_pObject)
		{
			mp_pObject->mp_ObjectTree.f_Clear();
			mp_pObject->mp_Objects.f_Clear();
			mp_pObject = nullptr;
		}
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	auto TCJsonObject<t_CJsonValue, t_bOrdered>::f_OrderedDestructiveIterator() &&
		-> COrderedDestructiveIterator
	{
		if constexpr (t_bOrdered)
			return COrderedDestructiveIterator(*this);
		else
			return fg_Move(mp_Objects).f_Entries().f_GetIteratorBidirectionalDestructive();
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	auto TCJsonObject<t_CJsonValue, t_bOrdered>::f_SortedDestructiveIterator() &&
		-> CSortedDestructiveIterator
	{
		if constexpr (t_bOrdered)
			return CSortedDestructiveIterator(*this);
		else
			return fg_Move(mp_Objects).f_Entries().f_GetIteratorBidirectionalDestructive();
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue &TCJsonObject<t_CJsonValue, t_bOrdered>::f_Insert(CObjectEntryHandle &&_Handle)
	{
		if constexpr (t_bOrdered)
		{
			DMibFastCheck(!!_Handle);
			return mp_ObjectTree.f_FindEqualOrInsert
				(
					_Handle.f_Name()
					, [&]() -> CObjectEntry *
					{
						auto &Entry = mp_Objects.f_Insert(fg_Move(_Handle.mp_ListHandle));
						return &Entry;
					}
				)->f_Value()
			;
		}
		else
		{
			return mp_Objects.f_Insert(fg_Move(_Handle)).f_Value();
		}
	}

	template <typename t_CJsonValue, bool t_bOrdered>
	t_CJsonValue &TCJsonObject<t_CJsonValue, t_bOrdered>::f_InsertOrAssign(CObjectEntryHandle &&_Handle)
	{
		if constexpr (t_bOrdered)
		{
			DMibFastCheck(!!_Handle);
			bool bInserted = false;
			auto pResult = mp_ObjectTree.f_FindEqualOrInsert
				(
					_Handle.f_Name()
					, [&]() -> CObjectEntry *
					{
						bInserted = true;
						auto &Entry = mp_Objects.f_Insert(fg_Move(_Handle.mp_ListHandle));
						return &Entry;
					}
				)
			;
			if (!bInserted)
				pResult->f_Value() = fg_Move(_Handle.f_Value());
			return pResult->f_Value();
		}
		else
		{
			return mp_Objects.f_InsertOrAssign(fg_Move(_Handle)).f_Value();
		}
	}
}
