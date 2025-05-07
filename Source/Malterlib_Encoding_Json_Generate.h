// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_JSON.h"

namespace NMib::NEncoding::NJSON
{
	template <typename tf_CStr>
	static void fg_AddPrefix(tf_CStr &o_String, mint _Depth, ch8 const *_pPrettySeparator);
	template <ch8 t_QuoteCharacter, typename tf_CParseContext, bool tf_bAddQuotes = true, typename tf_CStr, typename tf_CSourceString>
	static void fg_GenerateJSONString(tf_CStr &o_String, tf_CSourceString const &_Value);
	template <typename tf_CParseContext, typename tf_CStr, typename tf_CJson>
	static void fg_GenerateJSONObject(tf_CStr &o_String, tf_CJson const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags);
	template <typename tf_CParseContext, typename tf_CStr, typename tf_CJson>
	static void fg_GenerateJSONArray(tf_CStr &o_String, tf_CJson const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags);
	template <typename tf_CParseContext, typename tf_CStr, typename tf_CJson>
	static void fg_GenerateJSONValue(tf_CStr &o_String, tf_CJson const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJSONDialectFlag _Flags);
}

#include "Malterlib_Encoding_JSON_Generate.hpp"
