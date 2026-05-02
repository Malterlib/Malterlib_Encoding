// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NEncoding
{
	template <typename t_CValueBase>
	struct TCJsonTriviaConstView
	{
		explicit TCJsonTriviaConstView(t_CValueBase const &_Value);

		NStr::CStr const &f_Leading() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		bool f_IsLeadingSet() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		bool f_HasLeadingComma() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		NStr::CStr const &f_Trailing() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		bool f_HasTrailingComma() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		bool f_IsTrailingSet() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		NStr::CStr const &f_Interior() const
			requires (t_CValueBase::mc_bPreserveComments)
		;

	private:
		t_CValueBase const &mp_Value;
	};

	template <typename t_CValueBase>
	struct TCJsonTriviaView
	{
		explicit TCJsonTriviaView(t_CValueBase &_Value);

		operator TCJsonTriviaConstView<t_CValueBase>() const;

		NStr::CStr const &f_Leading() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		NStr::CStr &&f_MoveLeading()
			requires (t_CValueBase::mc_bPreserveComments)
		;
		bool f_IsLeadingSet() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		bool f_HasLeadingComma() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		void f_SetLeading(NStr::CStr &&_Trivia, bool _bHasComma)
			requires (t_CValueBase::mc_bPreserveComments)
		;
		void f_UnsetLeading()
			requires (t_CValueBase::mc_bPreserveComments)
		;
		NStr::CStr const &f_Trailing() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		NStr::CStr &&f_MoveTrailing()
			requires (t_CValueBase::mc_bPreserveComments)
		;
		bool f_HasTrailingComma() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		bool f_IsTrailingSet() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		void f_SetTrailing(NStr::CStr &&_Trivia, bool _bHasComma)
			requires (t_CValueBase::mc_bPreserveComments)
		;
		void f_UnsetTrailing()
			requires (t_CValueBase::mc_bPreserveComments)
		;
		NStr::CStr const &f_Interior() const
			requires (t_CValueBase::mc_bPreserveComments)
		;
		NStr::CStr &&f_MoveInterior()
			requires (t_CValueBase::mc_bPreserveComments)
		;
		void f_SetInterior(NStr::CStr &&_Trivia)
			requires (t_CValueBase::mc_bPreserveComments)
		;
		void f_UnsetInterior()
			requires (t_CValueBase::mc_bPreserveComments)
		;

	private:
		t_CValueBase &mp_Value;
	};

	template <typename t_CObjectEntry>
	struct TCJsonKeyTriviaConstView
	{
		explicit TCJsonKeyTriviaConstView(t_CObjectEntry const &_Entry);

		NStr::CStr const &f_Leading() const
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		bool f_IsLeadingSet() const
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		bool f_HasLeadingComma() const
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		NStr::CStr const &f_Trailing() const
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		bool f_IsTrailingSet() const
			requires (t_CObjectEntry::mc_bPreserveComments)
		;

	private:
		t_CObjectEntry const &mp_Entry;
	};

	template <typename t_CObjectEntry>
	struct TCJsonKeyTriviaView
	{
		explicit TCJsonKeyTriviaView(t_CObjectEntry &_Entry);

		operator TCJsonKeyTriviaConstView<t_CObjectEntry>() const;

		NStr::CStr const &f_Leading() const
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		NStr::CStr &&f_MoveLeading()
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		bool f_IsLeadingSet() const
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		bool f_HasLeadingComma() const
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		void f_SetLeading(NStr::CStr &&_Trivia, bool _bHasComma)
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		void f_UnsetLeading()
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		NStr::CStr const &f_Trailing() const
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		NStr::CStr &&f_MoveTrailing()
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		bool f_IsTrailingSet() const
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		void f_SetTrailing(NStr::CStr &&_Trivia)
			requires (t_CObjectEntry::mc_bPreserveComments)
		;
		void f_UnsetTrailing()
			requires (t_CObjectEntry::mc_bPreserveComments)
		;

	private:
		t_CObjectEntry &mp_Entry;
	};
}
