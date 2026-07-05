// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Yaml.h"

#include <Mib/CommandLine/AnsiEncoding>
#include <Mib/String/Appender>

namespace NMib::NEncoding::NPrivate
{
	// String sink for the YAML generators that wraps the semantic tokens marked through fg_YamlColorScope (keys,
	// scalars, comments, and tag/anchor/alias metadata) in ANSI syntax colors.
	struct CYamlColorAppender
	{
		using CString = NStr::CStr;

		CYamlColorAppender(NStr::CStr &o_String, NCommandLine::EAnsiEncodingFlag _AnsiFlags)
			: mp_Appender(o_String)
			, mp_AnsiEncoding(_AnsiFlags)
			, mp_bColor((_AnsiFlags & NCommandLine::EAnsiEncodingFlag_Color) != 0)
		{
		}

		template <typename tf_CValue>
		void operator += (tf_CValue const &_Value)
		{
			mp_Appender += _Value;
		}

		void f_AddChar(uch8 _Character)
		{
			mp_Appender.f_AddChar(_Character);
		}

		void f_AddString(ch8 const *_pString, umint _Len)
		{
			mp_Appender.f_AddString(_pString, _Len);
		}

		void f_YamlColorBegin(NYaml::EYamlColorToken _Token)
		{
			if (!mp_bColor)
				return;

			mp_Appender += mp_AnsiEncoding.f_SyntaxColor(fsp_SyntaxColor(_Token));
		}

		void f_YamlColorEnd()
		{
			if (!mp_bColor)
				return;

			mp_Appender += mp_AnsiEncoding.f_Default();
		}

	private:
		static NCommandLine::CAnsiEncoding::ESyntaxColor fsp_SyntaxColor(NYaml::EYamlColorToken _Token)
		{
			using ESyntaxColor = NCommandLine::CAnsiEncoding::ESyntaxColor;

			switch (_Token)
			{
			case NYaml::EYamlColorToken_Key: return ESyntaxColor::ESyntaxColor_MemberVariable;
			case NYaml::EYamlColorToken_String: return ESyntaxColor::ESyntaxColor_String;
			case NYaml::EYamlColorToken_Number: return ESyntaxColor::ESyntaxColor_Number;
			case NYaml::EYamlColorToken_Constant: return ESyntaxColor::ESyntaxColor_Constant;
			case NYaml::EYamlColorToken_Comment: return ESyntaxColor::ESyntaxColor_Comment;
			// YAML tags are type annotations; anchors, aliases, and directives share the metadata token.
			case NYaml::EYamlColorToken_Metadata: return ESyntaxColor::ESyntaxColor_Type;
			}

			return ESyntaxColor::ESyntaxColor_String;
		}

		NStr::CStr::CAppender mp_Appender;
		NCommandLine::CAnsiEncoding mp_AnsiEncoding;
		bool mp_bColor;
	};
}

namespace NMib::NEncoding
{
	template <typename t_CParent>
	template <typename t_CParseContext>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringColoredYamlContext
		(
			NCommandLine::EAnsiEncodingFlag _AnsiFlags
			, ch8 const *_pPrettySeparator
			, EJsonDialectFlag _Flags
		) const
	{
		NStr::CStr Return;
		{
			NPrivate::CYamlColorAppender Appender(Return, _AnsiFlags);
			NYaml::fg_GenerateYamlDocument<t_CParseContext>(Appender, static_cast<CValue const &>(*this), _pPrettySeparator, _Flags);
		}
		return Return;
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringColoredYaml(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		return f_ToStringColoredYamlContext<NYaml::CParseContext>(_AnsiFlags, _pPrettySeparator, _Flags);
	}

	template <typename t_CParent>
	NStr::CStr TCJsonValue<t_CParent>::f_ToStringColoredYamlFlow(NCommandLine::EAnsiEncodingFlag _AnsiFlags, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags) const
	{
		return f_ToStringColoredYamlContext<NYaml::CFlowOnlyParseContext>(_AnsiFlags, _pPrettySeparator, _Flags);
	}
}
