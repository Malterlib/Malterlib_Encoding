// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NEncoding::NYaml
{
	template <typename tf_CParseContext>
	void fg_ParseYamlSingleQuotedScalar(NStr::CStr &o_String, uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		NStr::CStr::CAppender Appender(o_String);
		bool bHasOutput = Appender.f_GetStrLen() != 0;
		ch8 LastChar = bHasOutput ? o_String[o_String.f_GetLen() - 1] : 0;

		auto fAppendChar = [&] (uch8 _Character)
			{
				Appender += _Character;
				bHasOutput = true;
				LastChar = ch8(_Character);
			}
		;

		auto fAppendString = [&] (uch8 const *_pStart, uch8 const *_pEnd)
			{
				if (_pStart == _pEnd)
					return;

				Appender.f_AddString(reinterpret_cast<ch8 const *>(_pStart), _pEnd - _pStart);
				bHasOutput = true;
				LastChar = ch8(_pEnd[-1]);
			}
		;

		++pParse;
		while (*pParse)
		{
			auto pStart = pParse;
			while (*pParse && *pParse != '\'' && *pParse != '\r' && *pParse != '\n')
				++pParse;

			fAppendString(pStart, pParse);

			if (*pParse == '\'')
			{
				if (pParse[1] == '\'')
				{
					fAppendChar('\'');

					pParse += 2;

					continue;
				}

				++pParse;

				return;
			}

			if (*pParse == '\r' || *pParse == '\n')
			{
				fg_ConsumeYamlLineEnd(pParse, _Context);

				while (*pParse == ' ' || *pParse == '\t')
					++pParse;

				if (bHasOutput && LastChar != ' ')
					fAppendChar(' ');

				continue;
			}
		}

		fg_ThrowYamlParseError(_Context, "Missing closing quote for YAML scalar", pParse);
	}

	inline bool fg_YamlQuotedScalarStartsCompactMapping(uch8 const *_pParse, uch8 _Quote)
	{
		++_pParse;
		while (*_pParse && *_pParse != '\r' && *_pParse != '\n')
		{
			if (*_pParse == _Quote)
			{
				if (_Quote == '\'' && _pParse[1] == '\'')
				{
					_pParse += 2;
					continue;
				}

				++_pParse;

				while (*_pParse == ' ' || *_pParse == '\t')
					++_pParse;

				return *_pParse == ':' && fg_IsYamlSeparation(_pParse[1]);
			}

			if (_Quote == '"' && *_pParse == '\\' && _pParse[1])
				_pParse += 2;
			else
				++_pParse;
		}

		return false;
	}

	template <typename tf_CParseContext>
	void fg_ParseYamlDoubleQuotedScalar(NStr::CStr &o_String, uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		auto pParse = o_pParse;
		auto UpdateParse = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
			}
		;

		NStr::CStr::CAppender Appender(o_String);
		bool bHasOutput = Appender.f_GetStrLen() != 0;
		ch8 LastChar = bHasOutput ? o_String[o_String.f_GetLen() - 1] : 0;

		auto fAppendChar = [&] (uch8 _Character)
			{
				Appender += _Character;
				bHasOutput = true;
				LastChar = ch8(_Character);
			}
		;

		auto fAppendString = [&] (uch8 const *_pStart, uch8 const *_pEnd)
			{
				if (_pStart == _pEnd)
					return;

				Appender.f_AddString(reinterpret_cast<ch8 const *>(_pStart), _pEnd - _pStart);
				bHasOutput = true;
				LastChar = ch8(_pEnd[-1]);
			}
		;

		auto fAppendNull = [&] (uch8 const *_pLocation)
			{
				if constexpr (tf_CParseContext::mc_bConvertNullToSpace)
					fAppendChar(' ');
				else
					fg_ThrowYamlParseError(_Context, "Null characters not supported in this implementation", _pLocation);
			}
		;

		auto fParseHex = [&] (umint _Digits) -> uint32
			{
				uint32 Value = 0;
				for (umint i = 0; i < _Digits; ++i)
				{
					uint32 Digit = 0;

					if (*pParse >= '0' && *pParse <= '9')
						Digit = *pParse - '0';
					else if (*pParse >= 'a' && *pParse <= 'f')
						Digit = *pParse - 'a' + 10;
					else if (*pParse >= 'A' && *pParse <= 'F')
						Digit = *pParse - 'A' + 10;
					else
						fg_ThrowYamlParseError(_Context, "Invalid YAML hex escape", pParse);

					Value = Value * 16 + Digit;

					++pParse;
				}

				return Value;
			}
		;

		auto fAppendCodepoint = [&] (uint32 _Codepoint)
			{
				if (_Codepoint > 0x10ffff || (_Codepoint >= 0xd800 && _Codepoint <= 0xdfff))
					fg_ThrowYamlParseError(_Context, "Invalid YAML Unicode escape", pParse);

				if (!_Codepoint)
				{
					fAppendNull(pParse);
					return;
				}

				Appender.f_AddUnicodeChar(ch32(_Codepoint));
				bHasOutput = true;
				LastChar = _Codepoint == ' ' ? ' ' : ch8(1);
			}
		;

		++pParse;
		while (*pParse)
		{
			auto pStart = pParse;
			while (*pParse && *pParse != '"' && *pParse != '\\' && *pParse != '\r' && *pParse != '\n')
				++pParse;

			fAppendString(pStart, pParse);

			if (*pParse == '"')
			{
				++pParse;
				return;
			}

			if (*pParse == '\\')
			{
				++pParse;
				if (*pParse == '\r' || *pParse == '\n')
				{
					fg_ConsumeYamlLineEnd(pParse, _Context);
					while (*pParse == ' ' || *pParse == '\t')
						++pParse;
					continue;
				}

				switch (*pParse)
				{
				case '0': fAppendNull(pParse); break;
				case 'a': fAppendChar('\a'); break;
				case 'b': fAppendChar('\b'); break;
				case 'e': fAppendChar(0x1b); break;
				case ' ': fAppendChar(' '); break;
				case 't': fAppendChar('\t'); break;
				case '\t': fAppendChar('\t'); break;
				case 'n': fAppendChar('\n'); break;
				case 'v': fAppendChar('\v'); break;
				case 'f': fAppendChar('\f'); break;
				case 'r': fAppendChar('\r'); break;
				case '"': fAppendChar('"'); break;
				case '/': fAppendChar('/'); break;
				case '\\': fAppendChar('\\'); break;
				case 'N': fAppendCodepoint(0x85); break;
				case '_': fAppendCodepoint(0xa0); break;
				case 'L': fAppendCodepoint(0x2028); break;
				case 'P': fAppendCodepoint(0x2029); break;
				case 'x':
					++pParse;
					fAppendCodepoint(fParseHex(2));
					continue;
				case 'u':
					{
						++pParse;
						auto Codepoint = fParseHex(4);
						if (Codepoint >= 0xd800 && Codepoint <= 0xdbff)
						{
							if (pParse[0] != '\\' || pParse[1] != 'u')
								fg_ThrowYamlParseError(_Context, "Missing YAML low surrogate escape", pParse);
							pParse += 2;
							auto Low = fParseHex(4);
							if (Low < 0xdc00 || Low > 0xdfff)
								fg_ThrowYamlParseError(_Context, "Invalid YAML low surrogate escape", pParse);
							Codepoint = 0x10000 + ((Codepoint - 0xd800) << 10) + (Low - 0xdc00);
						}
						else if (Codepoint >= 0xdc00 && Codepoint <= 0xdfff)
							fg_ThrowYamlParseError(_Context, "Unexpected YAML low surrogate escape", pParse);
						fAppendCodepoint(Codepoint);
						continue;
					}
				case 'U':
					++pParse;
					fAppendCodepoint(fParseHex(8));
					continue;
				default:
					fg_ThrowYamlParseError(_Context, "Unsupported YAML escape", pParse);
				}

				++pParse;

				continue;
			}

			if (*pParse == '\r' || *pParse == '\n')
			{
				fg_ConsumeYamlLineEnd(pParse, _Context);

				while (*pParse == ' ' || *pParse == '\t')
					++pParse;

				if (bHasOutput && LastChar != ' ')
					fAppendChar(' ');

				continue;
			}
		}

		fg_ThrowYamlParseError(_Context, "Missing closing quote for YAML scalar", pParse);
	}

	template <typename tf_CValue, typename tf_CToken>
	void fg_SetYamlPlainScalar(tf_CValue &o_Value, tf_CToken const &_Token)
	{
		auto pToken = _Token.f_GetStr();
		auto nTokenLen = _Token.f_GetLen();
		auto pTokenEnd = pToken + nTokenLen;

		if (!nTokenLen || (nTokenLen == 1 && pToken[0] == '~'))
		{
			o_Value = nullptr;
			return;
		}

		// Fast path for ordinary digit-prefixed numbers; signed and leading-dot numbers still reach l_Number below.
		if (NStr::fg_CharIsNumber(*pToken))
			goto l_Number;

		if
		(
			nTokenLen == 4
			&&
			(
				(pToken[0] == 'n' && pToken[1] == 'u' && pToken[2] == 'l' && pToken[3] == 'l')
				|| (pToken[0] == 'N' && pToken[1] == 'u' && pToken[2] == 'l' && pToken[3] == 'l')
				|| (pToken[0] == 'N' && pToken[1] == 'U' && pToken[2] == 'L' && pToken[3] == 'L')
			)
		)
		{
			o_Value = nullptr;
			return;
		}

		if
		(
			nTokenLen == 4
			&&
			(
				(pToken[0] == 't' && pToken[1] == 'r' && pToken[2] == 'u' && pToken[3] == 'e')
				|| (pToken[0] == 'T' && pToken[1] == 'r' && pToken[2] == 'u' && pToken[3] == 'e')
				|| (pToken[0] == 'T' && pToken[1] == 'R' && pToken[2] == 'U' && pToken[3] == 'E')
			)
		)
		{
			o_Value = true;
			return;
		}

		if
		(
			nTokenLen == 5
			&&
			(
				(pToken[0] == 'f' && pToken[1] == 'a' && pToken[2] == 'l' && pToken[3] == 's' && pToken[4] == 'e')
				|| (pToken[0] == 'F' && pToken[1] == 'a' && pToken[2] == 'l' && pToken[3] == 's' && pToken[4] == 'e')
				|| (pToken[0] == 'F' && pToken[1] == 'A' && pToken[2] == 'L' && pToken[3] == 'S' && pToken[4] == 'E')
			)
		)
		{
			o_Value = false;
			return;
		}

		if
		(
			(nTokenLen == 4 && pToken[0] == '.')
			|| (nTokenLen == 5 && pToken[0] == '+' && pToken[1] == '.')
		)
		{
			auto pInf = pToken + nTokenLen - 3;
			if
			(
				(pInf[0] == 'i' && pInf[1] == 'n' && pInf[2] == 'f')
				|| (pInf[0] == 'I' && pInf[1] == 'n' && pInf[2] == 'f')
				|| (pInf[0] == 'I' && pInf[1] == 'N' && pInf[2] == 'F')
			)
			{
				o_Value = fp64::fs_Inf();
				return;
			}
		}

		if (nTokenLen == 5 && pToken[0] == '-' && pToken[1] == '.')
		{
			if
			(
				(pToken[2] == 'i' && pToken[3] == 'n' && pToken[4] == 'f')
				|| (pToken[2] == 'I' && pToken[3] == 'n' && pToken[4] == 'f')
				|| (pToken[2] == 'I' && pToken[3] == 'N' && pToken[4] == 'F')
			)
			{
				o_Value = -fp64::fs_Inf();
				return;
			}
		}

		if
		(
			nTokenLen == 4
			&& pToken[0] == '.'
			&&
			(
				(pToken[1] == 'n' && pToken[2] == 'a' && pToken[3] == 'n')
				|| (pToken[1] == 'N' && pToken[2] == 'a' && pToken[3] == 'N')
				|| (pToken[1] == 'N' && pToken[2] == 'A' && pToken[3] == 'N')
			)
		)
		{
			o_Value = fp64::fs_QNan();
			return;
		}

		{
		l_Number:
			bool bNumber = false;
			bool bFloat = false;
			bool bLeadingDotFloat = false;
			auto pTokenScan = pToken;
			if (pTokenScan != pTokenEnd && (*pTokenScan == '+' || *pTokenScan == '-'))
				++pTokenScan;

			umint nDigits = 0;
			while (pTokenScan != pTokenEnd && *pTokenScan >= '0' && *pTokenScan <= '9')
			{
				++nDigits;
				++pTokenScan;
			}

			if (pTokenScan != pTokenEnd && *pTokenScan == '.')
			{
				bLeadingDotFloat = nDigits == 0;
				bFloat = true;
				++pTokenScan;

				while (pTokenScan != pTokenEnd && *pTokenScan >= '0' && *pTokenScan <= '9')
				{
					++nDigits;
					++pTokenScan;
				}
			}

			if (pTokenScan != pTokenEnd && (*pTokenScan == 'e' || *pTokenScan == 'E') && nDigits)
			{
				bFloat = true;
				++pTokenScan;
				if (pTokenScan != pTokenEnd && (*pTokenScan == '+' || *pTokenScan == '-'))
					++pTokenScan;

				umint nExponentDigits = 0;
				while (pTokenScan != pTokenEnd && *pTokenScan >= '0' && *pTokenScan <= '9')
				{
					++nExponentDigits;
					++pTokenScan;
				}

				if (!nExponentDigits)
					nDigits = 0;
			}

			bNumber = nDigits && pTokenScan == pTokenEnd;

			if (bNumber && !bFloat)
			{
				int64 Value = 0;
				if (!fg_TryParseYamlInteger(_Token, Value))
					DMibError("Number out of range");

				o_Value = Value;
			}
			else if (bNumber && bFloat)
			{
				if (bLeadingDotFloat)
				{
					auto pToken = _Token.f_GetStr();
					bool bHasSign = *pToken == '+' || *pToken == '-';
					if (bHasSign)
						++pToken;

					if (nTokenLen <= 30)
					{
						NStr::CFStr32 Token;

						if (bHasSign)
							Token += *_Token.f_GetStr();

						Token += '0';
						Token.f_AddStr(pToken, nTokenLen - (pToken - _Token.f_GetStr()));

						o_Value = Token.f_ToFloat(fp64::fs_SNan());
					}
					else
					{
						NStr::CStr Token;
						{
							NStr::CStr::CAppender Appender(Token);

							if (bHasSign)
								Appender += *_Token.f_GetStr();

							Appender += '0';
							Appender.f_AddString(pToken, nTokenLen - (pToken - _Token.f_GetStr()));
						}

						o_Value = Token.f_ToFloat(fp64::fs_SNan());
					}
				}
				else
					o_Value = _Token.f_ToFloat(fp64::fs_SNan());
			}
			else
				o_Value = _Token;
		}
	}

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_ValidateYamlMappingKeyString(NStr::CStr const &_Key, bool _bQuoted, tf_CParseContext &_Context, uch8 const *_pLocation)
	{
		if (_bQuoted)
			return;

		tf_CValue KeyValue;
		fg_SetYamlPlainScalar(KeyValue, _Key);

		if (!KeyValue.f_IsString())
			fg_ThrowYamlParseError(_Context, "YAML mapping key must be a string", _pLocation);
	}

	template <typename tf_CValue>
	struct TCYamlAnchor
	{
		NStr::CStr m_Name;
		tf_CValue m_Value;
		bool m_bOpen = false;
	};

	template <typename tf_CValue>
	using TCYamlAnchors = NContainer::TCVector<TCYamlAnchor<tf_CValue>>;

	template <typename tf_CValue>
	TCYamlAnchor<tf_CValue> *fg_FindAnchor(TCYamlAnchors<tf_CValue> &_Anchors, NStr::CStr const &_Name)
	{
		TCYamlAnchor<tf_CValue> *pFound = nullptr;
		for (auto &Anchor : _Anchors)
		{
			if (Anchor.m_Name == _Name)
				pFound = &Anchor;
		}

		return pFound;
	}

	template <typename tf_CValue>
	TCYamlAnchor<tf_CValue> &fg_AddAnchor(TCYamlAnchors<tf_CValue> &_Anchors, NStr::CStr const &_Name)
	{
		auto &Anchor = _Anchors.f_Insert();
		Anchor.m_Name = _Name;
		Anchor.m_bOpen = true;
		return Anchor;
	}

	template <typename tf_CValue, typename tf_CParseContext>
	void fg_ParseYamlNode(tf_CValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context, TCYamlAnchors<tf_CValue> &_Anchors);
}
