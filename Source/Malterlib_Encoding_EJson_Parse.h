// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_EJson.h"
#include "Malterlib_Encoding_Json_Parse.h"
#include "Malterlib_Encoding_Json_Generate.h"

namespace NMib::NEncoding::NPrivate
{
	struct CEJsonParseContext : public NJson::CParseContext
	{
		using CJsonContext = NJson::CParseContext;

		template <typename tf_CParseContext, typename tf_CJson, typename tf_CStr>
		static bool fs_GenerateValue(tf_CStr &o_String, tf_CJson const &_Value, umint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags);

		template <typename tf_CParseContext, typename tf_CJson, typename tf_CGenerator>
		static auto fs_GenerateColoredValue
			(
				tf_CGenerator &_Generator
				, NStr::CStr &o_String
				, tf_CJson const &_Value
				, umint _Depth
				, ch8 const *_pPrettySeparator
				, EJsonDialectFlag _Flags
				, tf_CParseContext &_Context
			)
			-> bool
		;

		template <typename tf_CParseContext, typename tf_CJson>
		bool f_ParseValue(tf_CJson &o_Value, uch8 const * &o_pParse);

		template <typename tf_CParseContext>
		void f_ParseKey(NStr::CStr &o_Key, uch8 const * &o_pParse);

		template <typename tf_CParseContext, typename tf_CJson>
		void f_PreParse(tf_CJson &o_Value, uch8 const * &o_pParse);

		template <typename tf_CParseContext, typename tf_CJson>
		void f_PostParse(tf_CJson &o_Value, uch8 const * &o_pParse);

		template <typename tf_CParseContext, typename tf_CJson>
		void f_ParseAfterValue(tf_CJson &o_Value, uch8 const * &o_pParse);

		static constexpr bool mc_bCustomParse = true;
		static constexpr bool mc_bCustomGenerate = true;

		NContainer::TCVector<umint> m_InEscapeParseDepth;

	private:
		static bool fsp_HasComment(NStr::CStr const &_Trivia);
		static bool fsp_HasLineTerminator(NStr::CStr const &_Trivia);
		static void fsp_AppendCommentTrivia(NStr::CStr &o_Trivia, NStr::CStr const &_Trivia);

		template <typename tf_CObjectEntry>
		static void fsp_AppendEntryCommentTrivia(NStr::CStr &o_Trivia, tf_CObjectEntry const &_Entry);

		template <typename tf_CJson>
		static void fsp_CopyValueLeadingTrivia(tf_CJson &o_Dest, tf_CJson const &_Source);

		template <typename tf_CJson>
		static void fsp_SetComposedTrivia(tf_CJson &o_Value, NStr::CStr &&_Trivia);

		template <typename tf_CJson>
		static void fsp_AppendComposedTriviaToLastObjectValue(tf_CJson &o_Value, NStr::CStr &&_Trivia);

		template <typename tf_CParseContext, typename tf_CJson, typename tf_CGeneratedValue>
		static void fsp_SetGeneratedSemanticValueTrivia(tf_CGeneratedValue &o_Value, tf_CJson const &_Source);
	};

	struct CEJson5ParseContext : public CEJsonParseContext
	{
		using CJsonContext = NJson::CJson5ParseContext;
		static constexpr bool mc_bAllowComments = true;
		static constexpr bool mc_bAllowTrailingCommas = true;
		static constexpr bool mc_bAllowSingleQuote = true;
		static constexpr bool mc_bAllowKeyWithoutQuote = true;
		static constexpr bool mc_bAllowHexNumbers = true;
		static constexpr bool mc_bAllowLeadingDecimal = true;
		static constexpr bool mc_bAllowSignAndSpecial = true;
		static constexpr bool mc_bAllowExtendedEscapes = true;
		static constexpr bool mc_bAllowExtendedWhitespace = true;
	};

	struct CEJsonStrictParseContext : public CEJsonParseContext
	{
		using CJsonContext = NJson::CStrictParseContext;
		static constexpr bool mc_bAllowTrailingCommas = false;
	};

	struct CEJsonCParseContext : public CEJsonParseContext
	{
		using CJsonContext = NJson::CJsonCParseContext;
		static constexpr bool mc_bAllowComments = true;
		static inline constexpr ch8 mc_ConstantEndCharacters[] = ",}]/";
	};

	struct CEJson5RecordingParseContext : public CEJson5ParseContext
	{
		using CJsonContext = NJson::CJson5RecordingParseContext;
		static constexpr bool mc_bRecordComments = true;
	};

	struct CEJsonCRecordingParseContext : public CEJsonCParseContext
	{
		using CJsonContext = NJson::CJsonCRecordingParseContext;
		static constexpr bool mc_bRecordComments = true;
	};
}

namespace NMib::NEncoding
{
	using CEJson5ParseContext = NPrivate::CEJson5ParseContext;
	using CEJsonStrictParseContext = NPrivate::CEJsonStrictParseContext;
	using CEJsonCParseContext = NPrivate::CEJsonCParseContext;
	using CEJsonCRecordingParseContext = NPrivate::CEJsonCRecordingParseContext;
	using CEJson5RecordingParseContext = NPrivate::CEJson5RecordingParseContext;
}

#include "Malterlib_Encoding_EJson_Parse.hpp"
