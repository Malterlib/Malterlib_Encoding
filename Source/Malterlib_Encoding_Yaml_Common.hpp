// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NEncoding::NYaml
{
	// Semantic token classes the YAML generators mark while emitting. A sink that satisfies cYamlColorSink receives
	// f_YamlColorBegin/f_YamlColorEnd around each token; plain string sinks compile the marks away.
	enum EYamlColorToken
	{
		EYamlColorToken_Key
		, EYamlColorToken_String
		, EYamlColorToken_Number
		, EYamlColorToken_Constant
		, EYamlColorToken_Comment
		, EYamlColorToken_Metadata // Tags, anchors, aliases, and document directives
	};

	template <typename t_CStr>
	concept cYamlColorSink = requires (t_CStr &_String)
		{
			_String.f_YamlColorBegin(EYamlColorToken_Key);
			_String.f_YamlColorEnd();
		}
	;

	// The non-trivial destructor keeps -Wunused-variable quiet for plain string sinks.
	struct CYamlColorScopeNone
	{
		~CYamlColorScopeNone()
		{
		}
	};

	template <typename tf_CStr>
	inline_always auto fg_YamlColorScope(tf_CStr &o_String, EYamlColorToken _Token)
	{
		if constexpr (cYamlColorSink<tf_CStr>)
		{
			o_String.f_YamlColorBegin(_Token);
			return g_OnScopeExit / [&o_String]
				{
					o_String.f_YamlColorEnd();
				}
			;
		}
		else
			return CYamlColorScopeNone{};
	}

	inline bool fg_YamlParseNDigits(ch8 const *&o_pParse, aint _nDigits, int64 &o_Value)
	{
		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		o_Value = 0;
		for (aint i = 0; i < _nDigits; ++i)
		{
			if (pParse[i] < '0' || pParse[i] > '9')
				return false;
			o_Value = o_Value * 10 + (pParse[i] - '0');
		}
		pParse += _nDigits;

		return true;
	}

	inline bool fg_YamlParseVariableDigits(ch8 const *&o_pParse, aint _nMinDigits, aint _nMaxDigits, int64 &o_Value)
	{
		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		o_Value = 0;
		aint nDigits = 0;
		while (nDigits < _nMaxDigits && *pParse >= '0' && *pParse <= '9')
		{
			o_Value = o_Value * 10 + (*pParse - '0');
			++pParse;
			++nDigits;
		}

		return nDigits >= _nMinDigits;
	}

	template <typename tf_CParseContext>
	void fg_ThrowYamlParseError(tf_CParseContext const &_Context, NStr::CStr const &_Error, uch8 const *_pLocation)
	{
		NJson::fg_ThrowJsonParseError<tf_CParseContext>(_Context, _Error, _pLocation);
	}

	template <typename tf_CParseContext>
	inline_always void fg_AssertExclusiveRecording()
	{
		static_assert
			(
				!tf_CParseContext::mc_bRecordComments
				, "YAML parse contexts must not set mc_bRecordComments; YAML records comments into CYamlValueMetadataSlots via mc_bRecordYamlMetadata"
			)
		;
	}

	inline bool fg_IsFlowWhitespace(uch8 _Char)
	{
		return _Char == ' ' || _Char == '\t' || _Char == '\r' || _Char == '\n';
	}

	inline bool fg_IsYamlSeparation(uch8 _Char)
	{
		return _Char == 0 || _Char == ' ' || _Char == '\t' || _Char == '\r' || _Char == '\n' || _Char == '#';
	}

	inline bool fg_IsYamlTrimChar(uch8 _Char)
	{
		return _Char == ' ' || _Char == '\b' || _Char == '\t' || _Char == '\n' || _Char == '\r';
	}

	inline void fg_TrimYamlStringRange(uch8 const *&o_pStart, uch8 const *&o_pEnd)
	{
		while (o_pStart < o_pEnd && fg_IsYamlTrimChar(*o_pStart))
			++o_pStart;

		while (o_pEnd > o_pStart && fg_IsYamlTrimChar(o_pEnd[-1]))
			--o_pEnd;
	}

	inline NStr::CStr fg_MakeYamlTrimmedString(uch8 const *_pStart, uch8 const *_pEnd)
	{
		fg_TrimYamlStringRange(_pStart, _pEnd);

		return NStr::CStr(reinterpret_cast<ch8 const *>(_pStart), _pEnd - _pStart);
	}

	inline NStr::CStrPtr fg_MakeYamlTrimmedStringPtr(uch8 const *_pStart, uch8 const *_pEnd)
	{
		fg_TrimYamlStringRange(_pStart, _pEnd);

		NStr::CStrPtr Return;
		Return.f_SetConstPtr(reinterpret_cast<ch8 const *>(_pStart), _pEnd - _pStart);
		return Return;
	}

	template <typename tf_CParseContext, typename tf_CComments>
	void fg_ParseYamlWhiteSpaceAndComments(uch8 const *&o_pParse, tf_CParseContext &_Context, tf_CComments &o_Comments)
	{
		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		if constexpr (NTraits::cIsSame<tf_CComments, CEmpty>)
		{
			if (_Context.m_nFlowDepth > 0)
			{
				while (*pParse)
				{
					while (fg_IsFlowWhitespace(*pParse))
						++pParse;

					if (*pParse != '#')
						break;

					while (*pParse && *pParse != '\r' && *pParse != '\n')
						++pParse;
				}

				return;
			}
		}

		auto fIsIndentationTab = [&]
			{
				if (_Context.m_nFlowDepth > 0)
					return false;

				if (*pParse != '\t')
					return false;

				auto pLine = pParse;
				while (pLine > _Context.m_pStartParse && pLine[-1] != '\r' && pLine[-1] != '\n')
					--pLine;

				for (auto pIndentationScan = pLine; pIndentationScan != pParse; ++pIndentationScan)
				{
					if (*pIndentationScan != ' ')
						return false;
				}

				return true;
			}
		;

		while (*pParse)
		{
			auto pRawCommentStart =
				pParse > _Context.m_pStartParse && (*pParse == '#') && (pParse[-1] == ' ' || pParse[-1] == '\t')
				? pParse - 1
				: pParse
			;

			while (fg_IsFlowWhitespace(*pParse))
			{
				if (fIsIndentationTab())
					fg_ThrowYamlParseError(_Context, "Tabs are not allowed in YAML block indentation", pParse);

				if (*pParse == '\r')
				{
					++pParse;
					if (*pParse == '\n')
						++pParse;
					pRawCommentStart = pParse;
				}
				else if (*pParse == '\n')
				{
					++pParse;
					pRawCommentStart = pParse;
				}
				else
					++pParse;
			}

			if (*pParse != '#')
				break;

			while (*pParse && *pParse != '\r' && *pParse != '\n')
				++pParse;

			if constexpr (!NTraits::cIsSame<tf_CComments, CEmpty>)
			{
				NStr::CStr::CAppender Appender(o_Comments);
				Appender.f_AddString(reinterpret_cast<ch8 const *>(pRawCommentStart), pParse - pRawCommentStart);
				Appender += '\n';
			}
		}
	}

	template <typename tf_CParseContext>
	void fg_ParseYamlWhiteSpaceAndComments(uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		CEmpty Comments;
		fg_ParseYamlWhiteSpaceAndComments(o_pParse, _Context, Comments);
	}

	inline void fg_ParseYamlFlowWhiteSpaceAndCommentsNoMetadata(uch8 const *&o_pParse)
	{
		while (*o_pParse)
		{
			while (fg_IsFlowWhitespace(*o_pParse))
				++o_pParse;

			if (*o_pParse != '#')
				break;

			while (*o_pParse && *o_pParse != '\r' && *o_pParse != '\n')
				++o_pParse;
		}
	}

	template <typename tf_CParseContext>
	void fg_EnsureYamlTagHandles(tf_CParseContext &_Context);

	inline NStr::CStr fg_ParseYamlDirectiveToken(uch8 const *&o_pParse)
	{
		auto pStart = o_pParse;
		while (*o_pParse && *o_pParse != ' ' && *o_pParse != '\t' && *o_pParse != '\r' && *o_pParse != '\n')
			++o_pParse;

		return NStr::CStr(reinterpret_cast<ch8 const *>(pStart), o_pParse - pStart);
	}

	template <typename tf_CParseContext, typename tf_CComments>
	void fg_ParseYamlDirectives(uch8 const *&o_pParse, tf_CParseContext &_Context, tf_CComments &o_Comments)
	{
		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		fg_EnsureYamlTagHandles(_Context);
		while (*pParse == '%')
		{
			auto pDirectiveStart = pParse;
			++pParse;
			NStr::CStr Directive = fg_ParseYamlDirectiveToken(pParse);

			while (*pParse == ' ' || *pParse == '\t')
				++pParse;

			if (Directive == "TAG")
			{
				NStr::CStr Handle = fg_ParseYamlDirectiveToken(pParse);

				while (*pParse == ' ' || *pParse == '\t')
					++pParse;

				NStr::CStr Prefix = fg_ParseYamlDirectiveToken(pParse);

				if (Handle.f_IsEmpty() || Prefix.f_IsEmpty() || Handle[0] != '!' || (Handle != NStr::gc_Str<"!">.m_Str && Handle[Handle.f_GetLen() - 1] != '!'))
					fg_ThrowYamlParseError(_Context, "Invalid YAML %TAG directive", pDirectiveStart);

				while (*pParse == ' ' || *pParse == '\t')
					++pParse;

				if (*pParse && *pParse != '#' && *pParse != '\r' && *pParse != '\n')
					fg_ThrowYamlParseError(_Context, "Invalid YAML %TAG directive", pDirectiveStart);

				_Context.m_TagHandles[Handle] = Prefix;
				_Context.m_DocumentTagHandles[Handle] = Prefix;
			}
			else if (Directive == "YAML")
			{
				NStr::CStr Version = fg_ParseYamlDirectiveToken(pParse);

				while (*pParse == ' ' || *pParse == '\t')
					++pParse;

				if (Version != "1.2" || (*pParse && *pParse != '#' && *pParse != '\r' && *pParse != '\n'))
					fg_ThrowYamlParseError(_Context, "Unsupported YAML directive", pDirectiveStart);
			}
			else
			{
				// YAML 1.2 allows processors to ignore unknown directives in this v1 parser.
			}

			NStr::fg_ParseToEndOfLine(pParse);
			NStr::fg_ParseEndOfLine(pParse);

			fg_ParseYamlWhiteSpaceAndComments(pParse, _Context, o_Comments);
		}
	}

	template <typename tf_CParseContext>
	void fg_ParseYamlDirectives(uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		CEmpty Comments;
		fg_ParseYamlDirectives(o_pParse, _Context, Comments);
	}

	inline bool fg_IsNameChar(uch8 _Char)
	{
		return (_Char >= 'A' && _Char <= 'Z') || (_Char >= 'a' && _Char <= 'z') || (_Char >= '0' && _Char <= '9') || _Char == '_' || _Char == '-' || _Char == '.';
	}

	inline bool fg_IsTagChar(uch8 _Char)
	{
		return fg_IsNameChar(_Char) || _Char == ':' || _Char == '/' || _Char == ',' || _Char == '%';
	}

	template <typename tf_CParseContext>
	void fg_EnsureYamlTagHandles(tf_CParseContext &_Context)
	{
		if (!_Context.m_TagHandles.f_FindEqual(NStr::gc_Str<"!">.m_Str))
			_Context.m_TagHandles[NStr::gc_Str<"!">.m_Str] = NStr::gc_Str<"!">.m_Str;

		if (!_Context.m_TagHandles.f_FindEqual(NStr::gc_Str<"!!">.m_Str))
			_Context.m_TagHandles[NStr::gc_Str<"!!">.m_Str] = "tag:yaml.org,2002:";
	}

	template <typename tf_CParseContext>
	NStr::CStr fg_ParseYamlName(uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		auto pStart = pParse;
		while (fg_IsNameChar(*pParse))
			++pParse;

		NStr::CStr Name(reinterpret_cast<ch8 const *>(pStart), pParse - pStart);

		if (Name.f_IsEmpty())
			fg_ThrowYamlParseError(_Context, "Expected YAML name", pStart);

		return Name;
	}

	template <typename tf_CParseContext>
	void fg_ParseYamlTag(uch8 const *&o_pParse, tf_CParseContext &_Context, NStr::CStr &o_Handle, NStr::CStr &o_Suffix, NStr::CStr &o_Resolved)
	{
		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		auto pStart = pParse;
		DMibCheck(*pParse == '!');

		if (pParse[1] == '!')
		{
			o_Handle = NStr::gc_Str<"!!">.m_Str;
			pParse += 2;

			{
				auto pSuffixStart = pParse;
				while (fg_IsTagChar(*pParse))
					++pParse;

				NStr::CStr::CAppender Appender(o_Suffix);
				Appender.f_AddString(reinterpret_cast<ch8 const *>(pSuffixStart), pParse - pSuffixStart);
			}

			auto *pPrefix = _Context.m_TagHandles.f_FindEqual(o_Handle);
			if (!pPrefix)
				fg_ThrowYamlParseError(_Context, "Unknown YAML tag handle", pStart);

			o_Resolved = *pPrefix;
			o_Resolved += o_Suffix;
		}
		else if (pParse[1] == '<')
		{
			o_Handle = NStr::gc_Str<"!">.m_Str;

			pParse += 2;

			{
				auto pSuffixStart = pParse;
				while (*pParse && *pParse != '>')
					++pParse;

				NStr::CStr::CAppender Appender(o_Suffix);
				Appender.f_AddString(reinterpret_cast<ch8 const *>(pSuffixStart), pParse - pSuffixStart);
			}

			if (*pParse != '>')
				fg_ThrowYamlParseError(_Context, "Missing closing > for YAML verbatim tag", pStart);

			++pParse;
			o_Resolved = o_Suffix;
		}
		else
		{
			++pParse;
			auto pSuffixStart = pParse;

			while (fg_IsNameChar(*pParse))
				++pParse;

			if (*pParse == '!')
			{
				o_Handle = {};

				{
					NStr::CStr::CAppender Appender(o_Handle);
					Appender += '!';
					Appender.f_AddString(reinterpret_cast<ch8 const *>(pSuffixStart), pParse - pSuffixStart);
					Appender += '!';
				}

				++pParse;

				{
					auto pTagStart = pParse;
					while (fg_IsTagChar(*pParse))
						++pParse;

					NStr::CStr::CAppender Appender(o_Suffix);
					Appender.f_AddString(reinterpret_cast<ch8 const *>(pTagStart), pParse - pTagStart);
				}

				auto *pPrefix = _Context.m_TagHandles.f_FindEqual(o_Handle);
				if (!pPrefix)
					fg_ThrowYamlParseError(_Context, "Unknown YAML tag handle", pStart);

				o_Resolved = *pPrefix;
				o_Resolved += o_Suffix;
			}
			else
			{
				o_Handle = NStr::gc_Str<"!">.m_Str;

				while (fg_IsTagChar(*pParse))
					++pParse;

				{
					NStr::CStr::CAppender Appender(o_Suffix);
					Appender.f_AddString(reinterpret_cast<ch8 const *>(pSuffixStart), pParse - pSuffixStart);
				}

				auto *pPrefix = _Context.m_TagHandles.f_FindEqual(o_Handle);
				if (!pPrefix)
					fg_ThrowYamlParseError(_Context, "Unknown YAML tag handle", pStart);

				o_Resolved = *pPrefix;
				o_Resolved += o_Suffix;
			}
		}

		if (o_Suffix.f_IsEmpty())
			fg_ThrowYamlParseError(_Context, "Expected YAML tag suffix", pStart);
	}

	inline bool fg_TryParseYamlInteger(NStr::CStr const &_Token, int64 &o_Value)
	{
		auto pStart = _Token.f_GetStr();
		bool bNegative = false;
		if (*pStart == '+' || *pStart == '-')
		{
			bNegative = *pStart == '-';
			++pStart;
		}

		constexpr uint64 c_MaxPositive = uint64(TCLimitsInt<int64>::mc_Max);
		constexpr uint64 c_MaxNegative = c_MaxPositive + 1;
		uint64 MaxValue = bNegative ? c_MaxNegative : c_MaxPositive;

		if (pStart[0] == '0' && (pStart[1] == 'x' || pStart[1] == 'X'))
		{
			uint64 Value = 0;

			auto pParse = pStart + 2;
			if (!*pParse)
				return false;

			while (*pParse)
			{
				uint8 Digit;
				if (*pParse >= '0' && *pParse <= '9')
					Digit = *pParse - '0';
				else if (*pParse >= 'a' && *pParse <= 'f')
					Digit = 10 + *pParse - 'a';
				else if (*pParse >= 'A' && *pParse <= 'F')
					Digit = 10 + *pParse - 'A';
				else
					return false;

				if (Value > (MaxValue - Digit) / 16)
					return false;

				Value = Value * 16 + Digit;
				++pParse;
			}

			if (bNegative)
			{
				if (Value == c_MaxNegative)
					o_Value = TCLimitsInt<int64>::mc_Min;
				else
					o_Value = -int64(Value);
			}
			else
				o_Value = int64(Value);

			return true;
		}
		else if (pStart[0] == '0' && (pStart[1] == 'o' || pStart[1] == 'O'))
		{
			uint64 Value = 0;

			auto pParse = pStart + 2;
			if (!*pParse)
				return false;

			while (*pParse)
			{
				if (*pParse < '0' || *pParse > '7')
					return false;

				uint64 Digit = uint64(*pParse - '0');
				if (Value > (MaxValue - Digit) / 8)
					return false;

				Value = Value * 8 + Digit;
				++pParse;
			}

			if (bNegative)
			{
				if (Value == c_MaxNegative)
					o_Value = TCLimitsInt<int64>::mc_Min;
				else
					o_Value = -int64(Value);
			}
			else
				o_Value = int64(Value);

			return true;
		}

		auto pParse = _Token.f_GetStr();

		if (*pParse == '+' || *pParse == '-')
			++pParse;

		if (!*pParse)
			return false;

		uint64 Value = 0;

		while (*pParse)
		{
			if (*pParse < '0' || *pParse > '9')
				return false;

			uint64 Digit = uint64(*pParse - '0');
			if (Value > (MaxValue - Digit) / 10)
				return false;

			Value = Value * 10 + Digit;
			++pParse;
		}

		if (bNegative)
		{
			if (Value == c_MaxNegative)
				o_Value = TCLimitsInt<int64>::mc_Min;
			else
				o_Value = -int64(Value);
		}
		else
			o_Value = int64(Value);

		return true;
	}

	inline NTime::CTime fg_YamlTimeFromUnixMilliseconds(int64 _Milliseconds)
	{
		int64 Seconds = _Milliseconds / constant_int64(1000);
		int64 Milliseconds = _Milliseconds % constant_int64(1000);
		if (Milliseconds < 0)
		{
			--Seconds;
			Milliseconds += constant_int64(1000);
		}

		NTime::CTime Return;
		Return.f_SetSeconds(uint64(int64(NTime::NPrivate::CConst::mc_UnixEpochSeconds) + Seconds));
		Return.f_SetFraction(fp64(Milliseconds) / 1000.0);

		return Return;
	}

	inline bool fg_IsYamlLocalTagSafe(NStr::CStr const &_Type)
	{
		if (_Type.f_IsEmpty())
			return false;

		for (auto pTagScan = _Type.f_GetStr(); *pTagScan; ++pTagScan)
		{
			if (!fg_IsTagChar(uch8(*pTagScan)) || *pTagScan == ':')
				return false;
		}

		return true;
	}

	inline bool fg_IsYamlCoreTag(NStr::CStr const &_TagResolved)
	{
		return _TagResolved.f_StartsWith("tag:yaml.org,2002:");
	}

	template <typename tf_CStr>
	void fg_FormatYamlTimestamp(tf_CStr &o_String, NTime::CTime const &_Time);

	template <typename tf_CValue>
	void fg_ApplyYamlTag(tf_CValue &o_Value, NStr::CStr const &_TagResolved, NStr::CStr const &_RawScalar)
	{
		if (_TagResolved.f_IsEmpty())
			return;

		if
		(
			_RawScalar.f_IsEmpty()
			&& (o_Value.f_IsObject() || o_Value.f_IsArray())
			&&
			(
				_TagResolved == "tag:yaml.org,2002:str"
				|| _TagResolved == "tag:yaml.org,2002:int"
				|| _TagResolved == "tag:yaml.org,2002:float"
				|| _TagResolved == "tag:yaml.org,2002:bool"
				|| _TagResolved == "tag:yaml.org,2002:null"
				|| _TagResolved == "tag:yaml.org,2002:binary"
				|| _TagResolved == "tag:yaml.org,2002:timestamp"
			)
		)
		{
			DMibError("YAML scalar tag requires a scalar value");
		}

		if (_TagResolved == "tag:yaml.org,2002:str")
			o_Value = _RawScalar;
		else if (_TagResolved == "tag:yaml.org,2002:int")
		{
			int64 Value = 0;
			if (!fg_TryParseYamlInteger(_RawScalar, Value))
				DMibError("Invalid YAML !!int scalar");

			o_Value = Value;
		}
		else if (_TagResolved == "tag:yaml.org,2002:float")
		{
			auto Value = fp64::fs_SNan();

			if (_RawScalar == ".inf" || _RawScalar == ".Inf" || _RawScalar == ".INF" || _RawScalar == "+.inf" || _RawScalar == "+.Inf" || _RawScalar == "+.INF")
				Value = fp64::fs_Inf();
			else if (_RawScalar == "-.inf" || _RawScalar == "-.Inf" || _RawScalar == "-.INF")
				Value = -fp64::fs_Inf();
			else
				Value = _RawScalar.f_ToFloat(fp64::fs_SNan());

			if (Value.f_IsNan() && _RawScalar != ".nan" && _RawScalar != ".NaN" && _RawScalar != ".NAN")
				DMibError("Invalid YAML !!float scalar");

			o_Value = Value;
		}
		else if (_TagResolved == "tag:yaml.org,2002:bool")
		{
			if (_RawScalar == NStr::gc_Str<"true">.m_Str || _RawScalar == NStr::gc_Str<"True">.m_Str || _RawScalar == NStr::gc_Str<"TRUE">.m_Str)
				o_Value = true;
			else if (_RawScalar == NStr::gc_Str<"false">.m_Str || _RawScalar == NStr::gc_Str<"False">.m_Str || _RawScalar == NStr::gc_Str<"FALSE">.m_Str)
				o_Value = false;
			else
				DMibError("Invalid YAML !!bool scalar");
		}
		else if (_TagResolved == "tag:yaml.org,2002:null")
		{
			if
			(
				_RawScalar != NStr::gc_Str<"null">.m_Str
				&& _RawScalar != NStr::gc_Str<"Null">.m_Str
				&& _RawScalar != NStr::gc_Str<"NULL">.m_Str
				&& _RawScalar != NStr::gc_Str<"~">.m_Str
				&& !_RawScalar.f_IsEmpty()
			)
			{
				DMibError("Invalid YAML !!null scalar");
			}

			o_Value = nullptr;
		}
		else if (_TagResolved == "tag:yaml.org,2002:binary")
		{
			if constexpr (requires (tf_CValue &Value) { Value.f_Binary(); })
			{
				NStr::CStr Compact;
				{
					NStr::CStr::CAppender Appender(Compact);
					for (auto pRawScalarScan = _RawScalar.f_GetStr(); *pRawScalarScan; )
					{
						while (*pRawScalarScan == ' ' || *pRawScalarScan == '\t' || *pRawScalarScan == '\r' || *pRawScalarScan == '\n')
							++pRawScalarScan;

						auto pRangeStart = pRawScalarScan;
						while (*pRawScalarScan && *pRawScalarScan != ' ' && *pRawScalarScan != '\t' && *pRawScalarScan != '\r' && *pRawScalarScan != '\n')
							++pRawScalarScan;

						Appender.f_AddString(pRangeStart, pRawScalarScan - pRangeStart);
					}
				}

				NContainer::CByteVector Binary;
				fg_Base64Decode(Compact, Binary);

				o_Value.f_SetEType(EEJsonType_Binary);
				o_Value.f_Binary() = fg_Move(Binary);
			}
			else
				o_Value = _RawScalar;
		}
		else if (_TagResolved == "tag:yaml.org,2002:timestamp")
		{
			if constexpr (requires (tf_CValue &Value) { Value.f_Date(); })
			{
				o_Value.f_SetEType(EEJsonType_Date);

				if
				(
					_RawScalar == NStr::gc_Str<"null">.m_Str
					|| _RawScalar == NStr::gc_Str<"Null">.m_Str
					|| _RawScalar == NStr::gc_Str<"NULL">.m_Str
					|| _RawScalar == NStr::gc_Str<"~">.m_Str
					|| _RawScalar.f_IsEmpty()
				)
				{
					o_Value.f_Date() = NTime::CTime();
				}
				else
					o_Value.f_Date() = fg_ParseYamlTimestamp(_RawScalar);
			}
			else
				o_Value = _RawScalar;
		}
		else if (_TagResolved == "tag:yaml.org,2002:seq")
		{
			if (!o_Value.f_IsArray())
				DMibError("YAML !!seq tag requires a sequence");
		}
		else if (_TagResolved == "tag:yaml.org,2002:map")
		{
			if (!o_Value.f_IsObject())
				DMibError("YAML !!map tag requires a mapping");
		}
		else
		{
			if constexpr (requires (tf_CValue &Value) { Value.f_UserType(); })
			{
				auto CurrentValue = fg_Move(o_Value);
				auto Payload = fg_Move(CurrentValue).f_ToJson();

				auto Type = (_TagResolved.f_StartsWith(NStr::gc_Str<"!">.m_Str) && _TagResolved.f_FindChar(':') < 0) ? _TagResolved.f_Extract(1) : _TagResolved;

				auto &UserType = o_Value.f_UserType();
				UserType.m_Type = fg_Move(Type);
				UserType.m_Value = fg_Move(Payload);
			}
		}
	}
}
