// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_Json.h"

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
		virtual NStr::CParseLocation f_GetLocation(uch8 const *_pParse) const;

		template <typename tf_CParseContext>
		void f_ParseKey(NStr::CStr &o_Key, uch8 const *&o_pParse);
		template <typename tf_CParseContext, typename tf_CStr, typename tf_CSourceStr>
		static void fs_GenerateString(tf_CStr &o_String, tf_CSourceStr const &_Value);
		template <typename tf_CParseContext, typename tf_CStr, typename tf_CSourceStr>
		static void fs_GenerateKeyString(tf_CStr &o_String, tf_CSourceStr const &_Key);

		void f_ThrowErrors(NContainer::TCVector<NStr::CParseError> const &_Errors) const;
		void f_ThrowError(NStr::CStr const &_Error, uch8 const *_pLocation) const;

		NStr::CStr m_FileName;
		uint32 m_StartLine = 0;
		uint32 m_StartColumn = 0;
		uint32 m_StartCharacter = 0;
		umint m_ObjectArrayParseDepth = 0;
		uch8 const *m_pStartParse;
		bool m_bConvertNullToSpace = false;
		EJsonDialectFlag m_Flags = EJsonDialectFlag_None;

		static constexpr bool mc_bCustomParse = false;
		static constexpr bool mc_bCustomGenerate = false;
		static constexpr bool mc_bAllowSingleQuote = false;
		static constexpr bool mc_bAllowKeyWithoutQuote = false;
		static constexpr NEncoding::NJson::EParseJsonStringFlag mc_ParseJsonStringFlags = NEncoding::NJson::EParseJsonStringFlag_None;
		static constexpr bool mc_bAllowDuplicateKeys = true;
		static constexpr bool mc_bRecordStringMap = false;
		static inline constexpr ch8 mc_AllowedControlCharacters[] = "";
		static inline constexpr ch8 mc_AllowedKeyWithoutQuoteCharacters[] = "$_";
		static inline constexpr ch8 mc_ConstantEndCharacters[] = ",}]";
	};

	template <typename tf_COutValue, typename tf_CParseContext>
	static void fg_ParseJsonArray(tf_COutValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context);
	template <typename tf_COutValue, typename tf_CParseContext>
	static void fg_ParseJsonObject(tf_COutValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context);
	template <uch8 t_QuoteCharacter, EParseJsonStringFlag t_Flags, typename tf_CParseContext, typename tf_FExtraParse = bool>
	static bool fg_ParseJsonString(NStr::CStr &o_String, uch8 const *&o_pParse, tf_CParseContext &_Context, tf_FExtraParse &&_fExtraParse = false);
	template <typename tf_COutValue, typename tf_CParseContext>
	static void fg_ParseJsonValue(tf_COutValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context);
}

#include "Malterlib_Encoding_Json_Parse.hpp"
