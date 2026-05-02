// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json.h"

#include <Mib/String/Appender>
#include <Mib/Storage/Optional>

namespace NMib::NEncoding
{
	enum EJsonStringType
	{
		EJsonStringType_DoubleQuote = 0
		, EJsonStringType_SingleQuote
		, EJsonStringType_NoQuote
		, EJsonStringType_Custom
	};
}

namespace NMib::NEncoding::NJson
{
	enum EParseJsonStringFlag
	{
		EParseJsonStringFlag_None = 0
		, EParseJsonStringFlag_AllowMultiLine = DMibBit(0)
		, EParseJsonStringFlag_NoQuotes = DMibBit(1)
	};

	struct CParseContext
	{
		template <typename tf_CParseContext>
		NStr::CParseLocation f_GetLocation(uch8 const *_pParse) const;
		template <typename tf_CParseContext>
		static NStr::CParseLocation fs_GetLocation
			(
				NStr::CStr const &_FileName
				, uint32 _StartLine
				, uint32 _StartColumn
				, uint32 _StartCharacter
				, uch8 const *_pStartParse
				, uch8 const *_pParse
			)
		;

		template <typename tf_CParseContext>
		void f_ParseKey(NStr::CStr &o_Key, uch8 const *&o_pParse);
		template <typename tf_CParseContext, typename tf_CStr, typename tf_CSourceStr>
		static void fs_GenerateString(tf_CStr &o_String, tf_CSourceStr const &_Value);
		template <typename tf_CParseContext, typename tf_CStr, typename tf_CSourceStr>
		static void fs_GenerateKeyString(tf_CStr &o_String, tf_CSourceStr const &_Key);

		void f_ThrowErrors(NContainer::TCVector<NStr::CParseError> const &_Errors) const;

		NStr::CStr m_FileName;
		uint32 m_StartLine = 0;
		uint32 m_StartColumn = 0;
		uint32 m_StartCharacter = 0;
		umint m_ObjectArrayParseDepth = 0;
		uch8 const *m_pStartParse;
		EJsonDialectFlag m_Flags = EJsonDialectFlag_None;

		static constexpr bool mc_bCustomParse = false;
		static constexpr bool mc_bCustomGenerate = false;
		static constexpr bool mc_bAllowSingleQuote = false;
		static constexpr bool mc_bAllowKeyWithoutQuote = false;
		static constexpr bool mc_bAllowComments = false;
		static constexpr bool mc_bAllowTrailingCommas = true;
		static constexpr bool mc_bAllowHexNumbers = false;
		static constexpr bool mc_bAllowLeadingDecimal = false;
		static constexpr bool mc_bAllowSignAndSpecial = false;
		static constexpr bool mc_bAllowExtendedEscapes = false;
		static constexpr bool mc_bAllowExtendedWhitespace = false;
		static constexpr bool mc_bRecordComments = false;
		static constexpr NEncoding::NJson::EParseJsonStringFlag mc_ParseJsonStringFlags = NEncoding::NJson::EParseJsonStringFlag_None;
		static constexpr bool mc_bAllowDuplicateKeys = true;
		static constexpr bool mc_bRecordStringMap = false;
		static constexpr bool mc_bConvertNullToSpace = false;
		static inline constexpr ch8 mc_AllowedControlCharacters[] = "";
		static inline constexpr ch8 mc_AllowedKeyWithoutQuoteCharacters[] = "$_";
		static inline constexpr ch8 mc_ConstantEndCharacters[] = ",}]";
	};

	struct CStrictParseContext : public CParseContext
	{
		static constexpr bool mc_bAllowTrailingCommas = false;
	};

	struct CJsonCParseContext : public CParseContext
	{
		static constexpr bool mc_bAllowComments = true;
		static inline constexpr ch8 mc_ConstantEndCharacters[] = ",}]/";
	};

	struct CJson5ParseContext : public CParseContext
	{
		static constexpr bool mc_bAllowComments = true;
		static constexpr bool mc_bAllowTrailingCommas = true;
		static constexpr bool mc_bAllowSingleQuote = true;
		static constexpr bool mc_bAllowKeyWithoutQuote = true;
		static constexpr bool mc_bAllowHexNumbers = true;
		static constexpr bool mc_bAllowLeadingDecimal = true;
		static constexpr bool mc_bAllowSignAndSpecial = true;
		static constexpr bool mc_bAllowExtendedEscapes = true;
		static constexpr bool mc_bAllowExtendedWhitespace = true;
		static inline constexpr ch8 mc_ConstantEndCharacters[] = ",}]/";
	};

	struct CJson5RecordingParseContext : public CJson5ParseContext
	{
		static constexpr bool mc_bRecordComments = true;
	};

	struct CJsonCRecordingParseContext : public CJsonCParseContext
	{
		static constexpr bool mc_bRecordComments = true;
	};

	struct CDiscardCommentSink
	{
		void f_Reset();
		void f_AppendVerbatim(uch8 const *_pStart, uch8 const *_pEnd);
		void f_AppendComment(uch8 const *_pStart, uch8 const *_pEnd, bool _bIsBlock);
		void f_AppendChar(ch8 _Char);
	};

	struct CCommentSink
	{
		struct CCommentInfo
		{
			umint m_Start = 0;
			umint m_End = 0;
			bool m_bIsBlock = false;
		};

		struct CPartition
		{
			struct CTrivia
			{
				NStr::CStr m_Text;
				bool m_bHasComma = false;
			};

			CTrivia m_Trailing;
			CTrivia m_Leading;
		};

		void f_Reset();
		void f_AppendVerbatim(uch8 const *_pStart, uch8 const *_pEnd);
		void f_AppendComment(uch8 const *_pStart, uch8 const *_pEnd, bool _bIsBlock);
		void f_AppendChar(ch8 _Char);
		CPartition::CTrivia f_TakeAndClear();
		void f_CapturePendingLeading();
		CPartition::CTrivia f_TakePendingLeading();
		void f_SetPendingLeading(CPartition::CTrivia &&_PendingLeading);
		CPartition f_PartitionAtFreestanding();

		NStr::CStr m_Buffer;
		CPartition::CTrivia m_PendingLeading;
		NContainer::TCVector<CCommentInfo> m_Comments;
		smint m_iSeparatorComma = -1;

	private:
		// Lazy-constructed CAppender that batches writes into m_Buffer. Lifetime
		// must end before any operation that mutates m_Buffer outside the
		// appender (clear, move) so the appender's cached pointers don't go stale.
		NStorage::TCOptional<NStr::CStr::CAppender> mp_Appender;

		NStr::CStr::CAppender &fp_GetAppender();
		void fp_CommitAppender();
	};

	bool fg_IsJson5WhiteSpace(uch8 const *_pParse);
	void fg_ParseJson5WhiteSpace(uch8 const *&o_pParse);
	bool fg_IsJson5LineTerminator(uch8 const *_pParse);
	bool fg_ParseJson5LineTerminator(uch8 const *&o_pParse);
	template <typename tf_CParseContext>
	bool fg_IsJsonLineTerminator(uch8 const *_pParse);
	template <typename tf_CParseContext>
	bool fg_ParseJsonLineTerminator(uch8 const *&o_pParse);
	template <typename tf_CParseContext>
	bool fg_IsJsonWhiteSpace(uch8 const *_pParse);
	template <typename tf_CParseContext>
	void fg_ParseJsonWhiteSpace(uch8 const *&o_pParse);
	template <typename tf_CParseContext>
	NStr::CParseLocation fg_GetJsonParseLocation(tf_CParseContext const &_Context, uch8 const *_pParse);
	template <typename tf_CParseContext>
	void fg_ThrowJsonParseError(tf_CParseContext const &_Context, NStr::CStr const &_Error, uch8 const *_pLocation);

	template <typename tf_CParseContext, typename tf_CCommentSink>
	inline_always void fg_ParseWhiteSpaceAndComments(uch8 const *&o_pParse, tf_CParseContext &_Context, tf_CCommentSink &_Sink);

	template <typename tf_CParseContext>
	inline_always bool fg_IsValueTerminator(uch8 const *_pParse) noexcept;

	template <typename tf_COutValue, typename tf_CParseContext>
	static void fg_ParseJsonArray(tf_COutValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context);
	template <typename tf_COutValue, typename tf_CParseContext>
	static void fg_ParseJsonObject(tf_COutValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context);
	template <uch8 t_QuoteCharacter, EParseJsonStringFlag t_Flags, typename tf_CParseContext, typename tf_FExtraParse = bool>
	static bool fg_ParseJsonString(NStr::CStr &o_String, uch8 const *&o_pParse, tf_CParseContext &_Context, tf_FExtraParse &&_fExtraParse = false);
	template <typename tf_COutValue, typename tf_CParseContext>
	static void fg_ParseJsonValue(tf_COutValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context);
}

namespace NMib::NEncoding
{
	using CJsonStrictParseContext = NJson::CStrictParseContext;
	using CJsonCParseContext = NJson::CJsonCParseContext;
	using CJsonCRecordingParseContext = NJson::CJsonCRecordingParseContext;
	using CJson5ParseContext = NJson::CJson5ParseContext;
	using CJson5RecordingParseContext = NJson::CJson5RecordingParseContext;
}

#include "Malterlib_Encoding_Json_Parse.hpp"
