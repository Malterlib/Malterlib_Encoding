// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json_Trivia.h"

namespace NMib::NEncoding
{
	template <typename t_CValueBase>
	TCJsonTriviaConstView<t_CValueBase>::TCJsonTriviaConstView(t_CValueBase const &_Value)
		: mp_Value(_Value)
	{
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCJsonTriviaConstView<t_CValueBase>::f_Leading() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_Leading;
	}

	template <typename t_CValueBase>
	bool TCJsonTriviaConstView<t_CValueBase>::f_IsLeadingSet() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_bLeadingSet;
	}

	template <typename t_CValueBase>
	bool TCJsonTriviaConstView<t_CValueBase>::f_HasLeadingComma() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_bLeadingHasComma;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCJsonTriviaConstView<t_CValueBase>::f_Trailing() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_Trailing;
	}

	template <typename t_CValueBase>
	bool TCJsonTriviaConstView<t_CValueBase>::f_HasTrailingComma() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_bTrailingHasComma;
	}

	template <typename t_CValueBase>
	bool TCJsonTriviaConstView<t_CValueBase>::f_IsTrailingSet() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_bTrailingSet;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCJsonTriviaConstView<t_CValueBase>::f_Interior() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_Interior;
	}

	template <typename t_CValueBase>
	TCJsonTriviaView<t_CValueBase>::TCJsonTriviaView(t_CValueBase &_Value)
		: mp_Value(_Value)
	{
	}

	template <typename t_CValueBase>
	TCJsonTriviaView<t_CValueBase>::operator TCJsonTriviaConstView<t_CValueBase>() const
	{
		return TCJsonTriviaConstView<t_CValueBase>(mp_Value);
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCJsonTriviaView<t_CValueBase>::f_Leading() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_Leading;
	}

	template <typename t_CValueBase>
	NStr::CStr &&TCJsonTriviaView<t_CValueBase>::f_MoveLeading()
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return fg_Move(mp_Value.mp_ValueTrivia.m_Leading);
	}

	template <typename t_CValueBase>
	bool TCJsonTriviaView<t_CValueBase>::f_IsLeadingSet() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_bLeadingSet;
	}

	template <typename t_CValueBase>
	bool TCJsonTriviaView<t_CValueBase>::f_HasLeadingComma() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_bLeadingHasComma;
	}

	template <typename t_CValueBase>
	void TCJsonTriviaView<t_CValueBase>::f_SetLeading(NStr::CStr &&_Trivia, bool _bHasComma)
		requires (t_CValueBase::mc_bPreserveComments)
	{
		mp_Value.mp_ValueTrivia.m_Leading = fg_Move(_Trivia);
		mp_Value.mp_ValueTrivia.m_bLeadingSet = true;
		mp_Value.mp_ValueTrivia.m_bLeadingHasComma = _bHasComma;
	}

	template <typename t_CValueBase>
	void TCJsonTriviaView<t_CValueBase>::f_UnsetLeading()
		requires (t_CValueBase::mc_bPreserveComments)
	{
		mp_Value.mp_ValueTrivia.m_Leading.f_Clear();
		mp_Value.mp_ValueTrivia.m_bLeadingSet = false;
		mp_Value.mp_ValueTrivia.m_bLeadingHasComma = false;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCJsonTriviaView<t_CValueBase>::f_Trailing() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_Trailing;
	}

	template <typename t_CValueBase>
	NStr::CStr &&TCJsonTriviaView<t_CValueBase>::f_MoveTrailing()
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return fg_Move(mp_Value.mp_ValueTrivia.m_Trailing);
	}

	template <typename t_CValueBase>
	bool TCJsonTriviaView<t_CValueBase>::f_HasTrailingComma() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_bTrailingHasComma;
	}

	template <typename t_CValueBase>
	bool TCJsonTriviaView<t_CValueBase>::f_IsTrailingSet() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_bTrailingSet;
	}

	template <typename t_CValueBase>
	void TCJsonTriviaView<t_CValueBase>::f_SetTrailing(NStr::CStr &&_Trivia, bool _bHasComma)
		requires (t_CValueBase::mc_bPreserveComments)
	{
		mp_Value.mp_ValueTrivia.m_Trailing = fg_Move(_Trivia);
		mp_Value.mp_ValueTrivia.m_bTrailingSet = true;
		mp_Value.mp_ValueTrivia.m_bTrailingHasComma = _bHasComma;
	}

	template <typename t_CValueBase>
	void TCJsonTriviaView<t_CValueBase>::f_UnsetTrailing()
		requires (t_CValueBase::mc_bPreserveComments)
	{
		mp_Value.mp_ValueTrivia.m_Trailing.f_Clear();
		mp_Value.mp_ValueTrivia.m_bTrailingSet = false;
		mp_Value.mp_ValueTrivia.m_bTrailingHasComma = false;
	}

	template <typename t_CValueBase>
	NStr::CStr const &TCJsonTriviaView<t_CValueBase>::f_Interior() const
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return mp_Value.mp_ValueTrivia.m_Interior;
	}

	template <typename t_CValueBase>
	NStr::CStr &&TCJsonTriviaView<t_CValueBase>::f_MoveInterior()
		requires (t_CValueBase::mc_bPreserveComments)
	{
		return fg_Move(mp_Value.mp_ValueTrivia.m_Interior);
	}

	template <typename t_CValueBase>
	void TCJsonTriviaView<t_CValueBase>::f_SetInterior(NStr::CStr &&_Trivia)
		requires (t_CValueBase::mc_bPreserveComments)
	{
		mp_Value.mp_ValueTrivia.m_Interior = fg_Move(_Trivia);
	}

	template <typename t_CValueBase>
	void TCJsonTriviaView<t_CValueBase>::f_UnsetInterior()
		requires (t_CValueBase::mc_bPreserveComments)
	{
		mp_Value.mp_ValueTrivia.m_Interior.f_Clear();
	}

	template <typename t_CObjectEntry>
	TCJsonKeyTriviaConstView<t_CObjectEntry>::TCJsonKeyTriviaConstView(t_CObjectEntry const &_Entry)
		: mp_Entry(_Entry)
	{
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCJsonKeyTriviaConstView<t_CObjectEntry>::f_Leading() const
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		return mp_Entry.mp_KeyTrivia.m_Leading;
	}

	template <typename t_CObjectEntry>
	bool TCJsonKeyTriviaConstView<t_CObjectEntry>::f_IsLeadingSet() const
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		return mp_Entry.mp_KeyTrivia.m_bLeadingSet;
	}

	template <typename t_CObjectEntry>
	bool TCJsonKeyTriviaConstView<t_CObjectEntry>::f_HasLeadingComma() const
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		return mp_Entry.mp_KeyTrivia.m_bLeadingHasComma;
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCJsonKeyTriviaConstView<t_CObjectEntry>::f_Trailing() const
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		return mp_Entry.mp_KeyTrivia.m_Trailing;
	}

	template <typename t_CObjectEntry>
	bool TCJsonKeyTriviaConstView<t_CObjectEntry>::f_IsTrailingSet() const
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		return mp_Entry.mp_KeyTrivia.m_bTrailingSet;
	}

	template <typename t_CObjectEntry>
	TCJsonKeyTriviaView<t_CObjectEntry>::TCJsonKeyTriviaView(t_CObjectEntry &_Entry)
		: mp_Entry(_Entry)
	{
	}

	template <typename t_CObjectEntry>
	TCJsonKeyTriviaView<t_CObjectEntry>::operator TCJsonKeyTriviaConstView<t_CObjectEntry>() const
	{
		return TCJsonKeyTriviaConstView<t_CObjectEntry>(mp_Entry);
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCJsonKeyTriviaView<t_CObjectEntry>::f_Leading() const
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		return mp_Entry.mp_KeyTrivia.m_Leading;
	}

	template <typename t_CObjectEntry>
	NStr::CStr &&TCJsonKeyTriviaView<t_CObjectEntry>::f_MoveLeading()
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		return fg_Move(mp_Entry.mp_KeyTrivia.m_Leading);
	}

	template <typename t_CObjectEntry>
	bool TCJsonKeyTriviaView<t_CObjectEntry>::f_IsLeadingSet() const
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		return mp_Entry.mp_KeyTrivia.m_bLeadingSet;
	}

	template <typename t_CObjectEntry>
	bool TCJsonKeyTriviaView<t_CObjectEntry>::f_HasLeadingComma() const
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		return mp_Entry.mp_KeyTrivia.m_bLeadingHasComma;
	}

	template <typename t_CObjectEntry>
	void TCJsonKeyTriviaView<t_CObjectEntry>::f_SetLeading(NStr::CStr &&_Trivia, bool _bHasComma)
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		mp_Entry.mp_KeyTrivia.m_Leading = fg_Move(_Trivia);
		mp_Entry.mp_KeyTrivia.m_bLeadingSet = true;
		mp_Entry.mp_KeyTrivia.m_bLeadingHasComma = _bHasComma;
	}

	template <typename t_CObjectEntry>
	void TCJsonKeyTriviaView<t_CObjectEntry>::f_UnsetLeading()
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		mp_Entry.mp_KeyTrivia.m_Leading.f_Clear();
		mp_Entry.mp_KeyTrivia.m_bLeadingSet = false;
		mp_Entry.mp_KeyTrivia.m_bLeadingHasComma = false;
	}

	template <typename t_CObjectEntry>
	NStr::CStr const &TCJsonKeyTriviaView<t_CObjectEntry>::f_Trailing() const
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		return mp_Entry.mp_KeyTrivia.m_Trailing;
	}

	template <typename t_CObjectEntry>
	NStr::CStr &&TCJsonKeyTriviaView<t_CObjectEntry>::f_MoveTrailing()
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		return fg_Move(mp_Entry.mp_KeyTrivia.m_Trailing);
	}

	template <typename t_CObjectEntry>
	bool TCJsonKeyTriviaView<t_CObjectEntry>::f_IsTrailingSet() const
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		return mp_Entry.mp_KeyTrivia.m_bTrailingSet;
	}

	template <typename t_CObjectEntry>
	void TCJsonKeyTriviaView<t_CObjectEntry>::f_SetTrailing(NStr::CStr &&_Trivia)
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		mp_Entry.mp_KeyTrivia.m_Trailing = fg_Move(_Trivia);
		mp_Entry.mp_KeyTrivia.m_bTrailingSet = true;
	}

	template <typename t_CObjectEntry>
	void TCJsonKeyTriviaView<t_CObjectEntry>::f_UnsetTrailing()
		requires (t_CObjectEntry::mc_bPreserveComments)
	{
		mp_Entry.mp_KeyTrivia.m_Trailing.f_Clear();
		mp_Entry.mp_KeyTrivia.m_bTrailingSet = false;
	}
}
