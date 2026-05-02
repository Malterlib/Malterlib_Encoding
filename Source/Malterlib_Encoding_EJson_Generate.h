// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_EJson_Parse.h"

namespace NMib::NEncoding
{
	template <typename t_CParent>
	template <typename t_CParseContext>
	NStr::CStr TCEJsonValue<t_CParent>::f_ToString(ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		using namespace NStr;

		CStr Return;
		{
			CStr::CAppender StringAppender(Return);

			if constexpr (CValue::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
				NJson::fg_AppendJsonTrivia<t_CParseContext>(StringAppender, this->f_Trivia().f_Leading(), false);

			NJson::fg_GenerateJsonValue<t_CParseContext>(StringAppender, *this, 0, _pPrettySeparator, _Flags);

			bool bWroteRootTrailing = false;
			if constexpr (CValue::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
			{
				if (this->f_Trivia().f_IsTrailingSet())
				{
					NJson::fg_AppendJsonTrivia<t_CParseContext>(StringAppender, this->f_Trivia().f_Trailing(), true);
					bWroteRootTrailing = true;
				}
			}

			if
			(
				_pPrettySeparator
				&& !(_Flags & EJsonDialectFlag_TrimWhitespace)
				&& !bWroteRootTrailing
				&& !(CValue::mc_bPreserveComments && t_CParseContext::mc_bAllowComments)
			)
			{
				StringAppender += "\n";
			}
		}
		return Return;
	}

	template <typename t_CParent>
	NStr::CStr TCEJsonValue<t_CParent>::f_ToString(ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		return f_ToString<NPrivate::CEJsonParseContext>(_pPrettySeparator, _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCEJsonValue<t_CParent>::f_ToStringJsonC(ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		if constexpr (CValue::mc_bPreserveComments)
			return f_ToString<NPrivate::CEJsonCRecordingParseContext>(_pPrettySeparator, _Flags);
		else
			return f_ToString<NPrivate::CEJsonCParseContext>(_pPrettySeparator, _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCEJsonValue<t_CParent>::f_ToStringJson5(ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		if constexpr (CValue::mc_bPreserveComments)
			return f_ToString<NPrivate::CEJson5RecordingParseContext>(_pPrettySeparator, _Flags);
		else
			return f_ToString<NPrivate::CEJson5ParseContext>(_pPrettySeparator, _Flags);
	}

	template <typename t_CParent>
	template <typename t_CParseContext>
	NStr::CStr TCEJsonValue<t_CParent>::f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		return NPrivate::fg_JsonGenerateColored<t_CParseContext>(*this, _pPrettySeparator, _AnsiFlags, _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCEJsonValue<t_CParent>::f_ToStringColored(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		return f_ToStringColored<NPrivate::CEJsonParseContext>(_AnsiFlags, _pPrettySeparator, _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCEJsonValue<t_CParent>::f_ToStringColoredJsonC(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		if constexpr (CValue::mc_bPreserveComments)
			return f_ToStringColored<NPrivate::CEJsonCRecordingParseContext>(_AnsiFlags, _pPrettySeparator, _Flags);
		else
			return f_ToStringColored<NPrivate::CEJsonCParseContext>(_AnsiFlags, _pPrettySeparator, _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCEJsonValue<t_CParent>::f_ToStringColoredJson5(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		if constexpr (CValue::mc_bPreserveComments)
			return f_ToStringColored<NPrivate::CEJson5RecordingParseContext>(_AnsiFlags, _pPrettySeparator, _Flags);
		else
			return f_ToStringColored<NPrivate::CEJson5ParseContext>(_AnsiFlags, _pPrettySeparator, _Flags);
	}
}
