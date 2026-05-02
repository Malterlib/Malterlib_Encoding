// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding
{
	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	TCJsonObject<t_CJsonValue, t_ContainerFlags>::TCJsonObject()
	{
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	TCJsonObject<t_CJsonValue, t_ContainerFlags>::~TCJsonObject()
	{
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	TCJsonObject<t_CJsonValue, t_ContainerFlags>::TCJsonObject(TCJsonObject const &_Other)
		: mp_Objects(_Other.mp_Objects)
	{
		if constexpr (mc_bOrdered)
		{
			for (auto &Object : mp_Objects)
				mp_ObjectTree.f_Insert(Object);
		}
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	TCJsonObject<t_CJsonValue, t_ContainerFlags>::TCJsonObject(TCJsonObject &&_Other)
		: mp_Objects(fg_Move(_Other.mp_Objects))
		, mp_ObjectTree(fg_Move(_Other.mp_ObjectTree))
	{
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	template <typename tf_CJsonValue, EJsonContainerFlag tf_ContainerFlags>
	TCJsonObject<t_CJsonValue, t_ContainerFlags>::TCJsonObject(TCJsonObject<tf_CJsonValue, tf_ContainerFlags> const &_Other)
	{
		static_assert(t_ContainerFlags != tf_ContainerFlags);

		for (auto &Object : _Other)
		{
			auto &Entry = f_CreateMemberEntry(Object.f_Name());
			auto &EntryValue = Entry.f_Value();
			auto &OtherValue = Object.f_Value();
			EntryValue = t_CJsonValue(OtherValue);

			if constexpr (mc_bPreserveComments && TCJsonContainerFlagTraits<tf_ContainerFlags>::mc_bPreserveComments)
			{
				auto EntryTrivia = Entry.f_KeyTrivia();
				auto ObjectTrivia = Object.f_KeyTrivia();
				auto EntryValueTrivia = EntryValue.f_Trivia();
				auto OtherValueTrivia = OtherValue.f_Trivia();

				if (ObjectTrivia.f_IsLeadingSet())
					EntryTrivia.f_SetLeading(fg_TempCopy(ObjectTrivia.f_Leading()), ObjectTrivia.f_HasLeadingComma());
				else
					EntryTrivia.f_UnsetLeading();

				if (ObjectTrivia.f_IsTrailingSet())
					EntryTrivia.f_SetTrailing(fg_TempCopy(ObjectTrivia.f_Trailing()));
				else
					EntryTrivia.f_UnsetTrailing();

				if (OtherValueTrivia.f_IsLeadingSet())
					EntryValueTrivia.f_SetLeading(fg_TempCopy(OtherValueTrivia.f_Leading()), OtherValueTrivia.f_HasLeadingComma());
				else
					EntryValueTrivia.f_UnsetLeading();

				if (OtherValueTrivia.f_IsTrailingSet())
					EntryValueTrivia.f_SetTrailing(fg_TempCopy(OtherValueTrivia.f_Trailing()), OtherValueTrivia.f_HasTrailingComma());
				else
					EntryValueTrivia.f_UnsetTrailing();

				EntryValueTrivia.f_SetInterior(fg_TempCopy(OtherValueTrivia.f_Interior()));
			}
		}
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	template <typename tf_CJsonValue, EJsonContainerFlag tf_ContainerFlags>
	TCJsonObject<t_CJsonValue, t_ContainerFlags>::TCJsonObject(TCJsonObject<tf_CJsonValue, tf_ContainerFlags> &&_Other)
	{
		static_assert(t_ContainerFlags != tf_ContainerFlags);

		for (auto &Object : _Other)
		{
			auto &Entry = f_CreateMemberEntry(Object.f_Name());
			auto &EntryValue = Entry.f_Value();
			auto &OtherValue = Object.f_Value();
			EntryValue = t_CJsonValue(fg_Move(OtherValue));

			if constexpr (mc_bPreserveComments && TCJsonContainerFlagTraits<tf_ContainerFlags>::mc_bPreserveComments)
			{
				auto EntryTrivia = Entry.f_KeyTrivia();
				auto ObjectTrivia = Object.f_KeyTrivia();

				if (ObjectTrivia.f_IsLeadingSet())
					EntryTrivia.f_SetLeading(ObjectTrivia.f_MoveLeading(), ObjectTrivia.f_HasLeadingComma());
				else
					EntryTrivia.f_UnsetLeading();

				if (ObjectTrivia.f_IsTrailingSet())
					EntryTrivia.f_SetTrailing(ObjectTrivia.f_MoveTrailing());
				else
					EntryTrivia.f_UnsetTrailing();
			}
		}
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue const *TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_GetMember(NStr::CStr const &_Name) const
	{
		if constexpr (mc_bOrdered)
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

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue *TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_GetMember(NStr::CStr const &_Name)
	{
		if constexpr (mc_bOrdered)
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

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue const *TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_GetMember(NStr::CStr const &_Name, EJsonType _Type) const
	{
		if constexpr (mc_bOrdered)
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

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue *TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_GetMember(NStr::CStr const &_Name, EJsonType _Type)
	{
		if constexpr (mc_bOrdered)
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

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_GetMemberValue(NStr::CStr const &_Name, t_CJsonValue const &_Default) const
	{
		if constexpr (mc_bOrdered)
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

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_GetMemberValue(NStr::CStr const &_Name, t_CJsonValue &&_Default) const
	{
		if constexpr (mc_bOrdered)
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

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	auto TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_CreateMemberEntry(NStr::CStr const &_Name) -> CObjectEntry &
	{
		if constexpr (mc_bOrdered)
		{
			return *mp_ObjectTree.f_FindEqualOrInsert
				(
					_Name
					, [&]() -> CObjectEntry *
					{
						auto &NewMember = mp_Objects.f_Insert();
						NewMember.mp_Name = _Name;
						return &NewMember;
					}
				)
			;
		}
		else
			return mp_Objects[_Name];
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	auto TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_CreateMemberEntry(NStr::CStr &&_Name) -> CObjectEntry &
	{
		if constexpr (mc_bOrdered)
		{
			return *mp_ObjectTree.f_FindEqualOrInsert
				(
					_Name
					, [&]() -> CObjectEntry *
					{
						auto &NewMember = mp_Objects.f_Insert();
						NewMember.mp_Name = fg_Move(_Name);
						return &NewMember;
					}
				)
			;
		}
		else
			return mp_Objects[fg_Move(_Name)];
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue &TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_CreateMember(NStr::CStr const &_Name)
	{
		return f_CreateMemberEntry(_Name).f_Value();
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue &TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_CreateMember(NStr::CStr &&_Name)
	{
		return f_CreateMemberEntry(fg_Move(_Name)).f_Value();
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue const &TCJsonObject<t_CJsonValue, t_ContainerFlags>::operator [] (NStr::CStr const &_Name) const
	{
		auto pMember = f_GetMember(_Name);
		if (!pMember)
			DMibError(fg_Format("Member '{}' not found", _Name));

		return *pMember;
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue &TCJsonObject<t_CJsonValue, t_ContainerFlags>::operator [] (NStr::CStr const &_Name)
	{
		return f_CreateMember(_Name);
	}


	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue &TCJsonObject<t_CJsonValue, t_ContainerFlags>::operator () (NStr::CStr const &_Name)
	{
		auto pMember = f_GetMember(_Name);
		if (!pMember)
			DMibError(fg_Format("Member '{}' not found", _Name));

		return *pMember;
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	bool TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_RemoveMember(NStr::CStr const &_Name)
	{
		if constexpr (mc_bOrdered)
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

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	void TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_SortObjectsLexicographically()
		requires (!mc_bPreserveComments)
	{
		if constexpr (mc_bOrdered)
		{
			mp_Objects.f_Sort();
			for (auto &ObjectEntry : mp_Objects)
				ObjectEntry.mp_Value.f_SortObjectsLexicographically();
		}
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	void TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_RemoveMember(typename CObjects::CIteratorConst &_Iterator)
		requires (mc_bOrdered)
	{
		auto pObject = const_cast<CObjectEntry *>(&*_Iterator);
		++_Iterator;
		mp_ObjectTree.f_Remove(pObject);
		mp_Objects.f_Remove(*pObject);
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	void TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_RemoveMember(typename CObjects::CIterator &_Iterator)
	{
		if constexpr (mc_bOrdered)
		{
			auto pObject = &*_Iterator;
			mp_ObjectTree.f_Remove(pObject);
		}
		_Iterator.f_Remove();
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	void TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_RemoveMember
		(
			typename NIntrusive::TCAVLTree<&NPrivate::CObjectEntryBase::mp_Link, CCompare, NMemory::CDefaultAllocator, CObjectEntry>::CIterator &_Iterator
		)
		requires (mc_bOrdered)
	{
		auto pObject = &*_Iterator;
		_Iterator.f_Remove(mp_ObjectTree);
		mp_Objects.f_Remove(*pObject);
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	auto TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_OrderedIterator() const -> typename CObjects::CIteratorConst
	{
		return mp_Objects.f_GetIterator();
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	auto TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_OrderedIterator() -> typename CObjects::CIterator
	{
		return mp_Objects.f_GetIterator();
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	auto TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_SortedIterator() const
		-> typename NIntrusive::TCAVLTree<&NPrivate::CObjectEntryBase::mp_Link, CCompare, NMemory::CDefaultAllocator, CObjectEntry>::CIterator
		requires (mc_bOrdered)
	{
		return mp_ObjectTree.f_GetIterator();
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	bool TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_IsEmpty() const
	{
		return mp_Objects.f_IsEmpty();
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	bool TCJsonObject<t_CJsonValue, t_ContainerFlags>::operator == (TCJsonObject const &_Right) const noexcept
	{
		return mp_Objects == _Right.mp_Objects;
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	COrdering_Partial TCJsonObject<t_CJsonValue, t_ContainerFlags>::operator <=> (TCJsonObject const &_Right) const noexcept
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

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	auto TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_OrderedDestructiveIterator() &&
		-> COrderedDestructiveIterator
	{
		if constexpr (mc_bOrdered)
			return COrderedDestructiveIterator(*this);
		else
			return fg_Move(mp_Objects).f_Entries().f_GetIteratorBidirectionalDestructive();
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	auto TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_SortedDestructiveIterator() &&
		-> CSortedDestructiveIterator
	{
		if constexpr (mc_bOrdered)
			return CSortedDestructiveIterator(*this);
		else
			return fg_Move(mp_Objects).f_Entries().f_GetIteratorBidirectionalDestructive();
	}

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue &TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_Insert(CObjectEntryHandle &&_Handle)
	{
		if constexpr (mc_bOrdered)
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

	template <typename t_CJsonValue, EJsonContainerFlag t_ContainerFlags>
	t_CJsonValue &TCJsonObject<t_CJsonValue, t_ContainerFlags>::f_InsertOrAssign(CObjectEntryHandle &&_Handle)
	{
		if constexpr (mc_bOrdered)
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
