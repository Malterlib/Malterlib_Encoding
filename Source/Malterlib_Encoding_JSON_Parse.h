// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib::NEncoding
{
	enum EJSONStringType
	{
		EJSONStringType_DoubleQuote = 0
		, EJSONStringType_SingleQuote
		, EJSONStringType_NoQuote
		, EJSONStringType_Custom
	};
}

namespace NMib::NEncoding::NJSON
{
	enum EParseJSONStringFlag
	{
		EParseJSONStringFlag_None = 0
		, EParseJSONStringFlag_AllowMultiLine = DMibBit(0)
		, EParseJSONStringFlag_NoQuotes = DMibBit(1)
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
		uch8 const *m_pStartParse;
		bool m_bConvertNullToSpace = false;
		EJSONDialectFlag m_Flags = EJSONDialectFlag_None;

		static constexpr bool mc_bCustomParse = false;
		static constexpr bool mc_bCustomGenerate = false;
		static constexpr bool mc_bAllowSingleQuote = false;
		static constexpr bool mc_bAllowKeyWithoutQuote = false;
		static constexpr NEncoding::NJSON::EParseJSONStringFlag mc_ParseJSONStringFlags = NEncoding::NJSON::EParseJSONStringFlag_None;
		static constexpr bool mc_bAllowDuplicateKeys = true;
		static constexpr bool mc_bRecordStringMap = false;
		static inline constexpr ch8 mc_AllowedControlCharacters[] = "";
		static inline constexpr ch8 mc_AllowedKeyWithoutQuoteCharacters[] = "$_";
		static inline constexpr ch8 mc_ConstantEndCharacters[] = ",}]";
		
		//bool f_ParseValue(CJSON &o_Value, uch8 const *&o_pParse);
	};

	template <typename tf_CParseContext>
	static void fg_ParseJSONArray(CJSON &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context);
	template <typename tf_CParseContext>
	static void fg_ParseJSONObject(CJSON &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context);
	template <uch8 t_QuoteCharacter, EParseJSONStringFlag t_Flags, typename tf_CParseContext, typename tf_FExtraParse = bool>
	static bool fg_ParseJSONString(NStr::CStr &o_String, uch8 const *&o_pParse, tf_CParseContext &_Context, tf_FExtraParse &&_fExtraParse = false);
	template <typename tf_CParseContext>
	static void fg_ParseJSONValue(CJSON &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context);
}

#include "Malterlib_Encoding_JSON_Parse.hpp"
