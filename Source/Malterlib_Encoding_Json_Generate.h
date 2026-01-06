// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Encoding_Json.h"

namespace NMib::NEncoding::NJson
{
	template <typename tf_CStr>
	static void fg_AddPrefix(tf_CStr &o_String, mint _Depth, ch8 const *_pPrettySeparator);
	template <ch8 t_QuoteCharacter, typename tf_CParseContext, bool tf_bAddQuotes = true, typename tf_CStr, typename tf_CSourceString>
	static void fg_GenerateJsonString(tf_CStr &o_String, tf_CSourceString const &_Value);
	template <typename tf_CParseContext, typename tf_CStr, typename tf_CJson>
	static void fg_GenerateJsonObject(tf_CStr &o_String, tf_CJson const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags);
	template <typename tf_CParseContext, typename tf_CStr, typename tf_CJson>
	static void fg_GenerateJsonArray(tf_CStr &o_String, tf_CJson const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags);
	template <typename tf_CParseContext, typename tf_CStr, typename tf_CJson>
	static void fg_GenerateJsonValue(tf_CStr &o_String, tf_CJson const &_Value, mint _Depth, ch8 const *_pPrettySeparator, EJsonDialectFlag _Flags);
}

#include "Malterlib_Encoding_Json_Generate.hpp"
