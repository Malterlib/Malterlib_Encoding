// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Encoding_Json_Generate.h"

#include <Mib/String/Appender>

namespace NMib::NEncoding::NJson
{
	template <typename tf_CParseContext>
	inline NStr::CParseLocation CParseContext::f_GetLocation(uch8 const *_pParse) const
	{
		return fs_GetLocation<tf_CParseContext>(m_FileName, m_StartLine, m_StartColumn, m_StartCharacter, m_pStartParse, _pParse);
	}

	template <typename tf_CParseContext>
	inline NStr::CParseLocation CParseContext::fs_GetLocation
		(
			NStr::CStr const &_FileName
			, uint32 _StartLine
			, uint32 _StartColumn
			, uint32 _StartCharacter
			, uch8 const *_pStartParse
			, uch8 const *_pParse
		)
	{
		using namespace NStr;
		CParseLocation Location;
		Location.m_File = _FileName;
		Location.m_Character = (_pParse - _pStartParse) + _StartCharacter;

		uint32 StartColumn = _StartColumn;

		auto *pParse = _pStartParse;
		umint Line = 1;
		auto *pLastLine = pParse;
		while (*pParse)
		{
			while (*pParse && !fg_IsJsonLineTerminator<tf_CParseContext>(pParse))
				++pParse;

			if (pParse >= _pParse)
				break;

			if (fg_ParseJsonLineTerminator<tf_CParseContext>(pParse))
			{
				StartColumn = 0;
				++Line;
				pLastLine = pParse;
			}
		}

		Location.m_Line = Line + _StartLine;
		if (_pParse >= pLastLine)
			Location.m_Column = (_pParse - pLastLine) + StartColumn + 1;
		else
			Location.m_Column = StartColumn + 1;

		return Location;
	}

	inline void CDiscardCommentSink::f_Reset()
	{
	}

	inline void CDiscardCommentSink::f_AppendVerbatim(uch8 const *, uch8 const *)
	{
	}

	inline void CDiscardCommentSink::f_AppendComment(uch8 const *, uch8 const *, bool)
	{
	}

	inline void CDiscardCommentSink::f_AppendChar(ch8)
	{
	}

	inline NStr::CStr::CAppender &CCommentSink::fp_GetAppender()
	{
		if (!mp_Appender)
			mp_Appender = NMib::fg_Construct<NStr::CStr::CAppender>(m_Buffer);
		return *mp_Appender;
	}

	inline void CCommentSink::fp_CommitAppender()
	{
		mp_Appender.f_Clear();
	}

	inline void CCommentSink::f_Reset()
	{
		fp_CommitAppender();
		m_Buffer.f_Clear();
		m_Comments.f_Clear();
		m_iSeparatorComma = -1;
	}

	inline void CCommentSink::f_AppendVerbatim(uch8 const *_pStart, uch8 const *_pEnd)
	{
		if (_pEnd > _pStart)
			fp_GetAppender().f_AddString((NStr::CStr::CChar const *)_pStart, _pEnd - _pStart);
	}

	inline void CCommentSink::f_AppendComment(uch8 const *_pStart, uch8 const *_pEnd, bool _bIsBlock)
	{
		auto &Appender = fp_GetAppender();
		auto &Comment = m_Comments.f_Insert();
		Comment.m_Start = Appender.f_GetStrLen();
		Comment.m_End = Comment.m_Start + (_pEnd - _pStart);
		Comment.m_bIsBlock = _bIsBlock;
		f_AppendVerbatim(_pStart, _pEnd);
	}

	inline void CCommentSink::f_AppendChar(ch8 _Char)
	{
		auto &Appender = fp_GetAppender();
		if (_Char == ',')
			m_iSeparatorComma = smint(Appender.f_GetStrLen());
		Appender.f_AddChar((NStr::CStr::CUnsignedChar)_Char);
	}

	inline CCommentSink::CPartition::CTrivia CCommentSink::f_TakeAndClear()
	{
		fp_CommitAppender();
		CPartition::CTrivia Return;
		Return.m_Text = fg_Move(m_Buffer);
		Return.m_bHasComma = m_iSeparatorComma >= 0;
		f_Reset();
		return Return;
	}

	inline void CCommentSink::f_CapturePendingLeading()
	{
		m_PendingLeading = f_TakeAndClear();
	}

	inline CCommentSink::CPartition::CTrivia CCommentSink::f_TakePendingLeading()
	{
		return fg_Move(m_PendingLeading);
	}

	inline void CCommentSink::f_SetPendingLeading(CPartition::CTrivia &&_PendingLeading)
	{
		m_PendingLeading = fg_Move(_PendingLeading);
	}

	inline bool fg_IsJson5LineTerminator(uch8 const *_pParse)
	{
		return
			_pParse[0] == '\n'
			|| _pParse[0] == '\r'
			|| (_pParse[0] == 0xE2 && _pParse[1] == 0x80 && (_pParse[2] == 0xA8 || _pParse[2] == 0xA9))
		;
	}

	inline bool fg_ParseJson5LineTerminator(uch8 const *&o_pParse)
	{
		if (o_pParse[0] == '\r')
		{
			++o_pParse;
			if (o_pParse[0] == '\n')
				++o_pParse;
			return true;
		}
		if (o_pParse[0] == '\n')
		{
			++o_pParse;
			return true;
		}
		if (o_pParse[0] == 0xE2 && o_pParse[1] == 0x80 && (o_pParse[2] == 0xA8 || o_pParse[2] == 0xA9))
		{
			o_pParse += 3;
			return true;
		}
		return false;
	}

	inline bool fg_IsJson5WhiteSpace(uch8 const *_pParse)
	{
		switch (_pParse[0])
		{
		case '\t':
		case '\v':
		case '\f':
		case ' ':
		case '\n':
		case '\r':
			return true;
		case 0xC2:
			return _pParse[1] == 0xA0;
		case 0xE1:
			if (!_pParse[1])
				return false;
			return _pParse[1] == 0x9A && _pParse[2] == 0x80;
		case 0xE2:
			if (!_pParse[1])
				return false;
			if (_pParse[1] == 0x80)
				return (_pParse[2] >= 0x80 && _pParse[2] <= 0x8A) || _pParse[2] == 0xA8 || _pParse[2] == 0xA9 || _pParse[2] == 0xAF;
			return _pParse[1] == 0x81 && _pParse[2] == 0x9F;
		case 0xE3:
			if (!_pParse[1])
				return false;
			return _pParse[1] == 0x80 && _pParse[2] == 0x80;
		case 0xEF:
			if (!_pParse[1])
				return false;
			return _pParse[1] == 0xBB && _pParse[2] == 0xBF;
		default:
			return false;
		}
	}

	inline void fg_ParseJson5WhiteSpace(uch8 const *&o_pParse)
	{
		while (*o_pParse && fg_IsJson5WhiteSpace(o_pParse))
		{
			switch (o_pParse[0])
			{
			case 0xC2:
				o_pParse += 2;
				break;
			case 0xE1:
			case 0xE2:
			case 0xE3:
			case 0xEF:
				o_pParse += 3;
				break;
			default:
				++o_pParse;
				break;
			}
		}
	}

	template <typename tf_CParseContext>
	inline bool fg_IsJsonLineTerminator(uch8 const *_pParse)
	{
		if constexpr (tf_CParseContext::mc_bAllowExtendedWhitespace)
			return fg_IsJson5LineTerminator(_pParse);
		else
			return _pParse[0] == '\n' || _pParse[0] == '\r';
	}

	template <typename tf_CParseContext>
	inline bool fg_ParseJsonLineTerminator(uch8 const *&o_pParse)
	{
		if constexpr (tf_CParseContext::mc_bAllowExtendedWhitespace)
			return fg_ParseJson5LineTerminator(o_pParse);
		else
			return NStr::fg_ParseEndOfLine(o_pParse);
	}

	template <typename tf_CParseContext>
	inline bool fg_IsJsonWhiteSpace(uch8 const *_pParse)
	{
		if constexpr (tf_CParseContext::mc_bAllowExtendedWhitespace)
			return fg_IsJson5WhiteSpace(_pParse);
		else
			return NStr::fg_CharIsWhiteSpace(*_pParse);
	}

	template <typename tf_CParseContext>
	inline void fg_ParseJsonWhiteSpace(uch8 const *&o_pParse)
	{
		if constexpr (tf_CParseContext::mc_bAllowExtendedWhitespace)
			fg_ParseJson5WhiteSpace(o_pParse);
		else
			NStr::fg_ParseWhiteSpace(o_pParse);
	}

	template <typename tf_CParseContext>
	inline NStr::CParseLocation fg_GetJsonParseLocation(tf_CParseContext const &_Context, uch8 const *_pParse)
	{
		return _Context.template f_GetLocation<tf_CParseContext>(_pParse);
	}

	template <typename tf_CParseContext>
	inline void fg_ThrowJsonParseError(tf_CParseContext const &_Context, NStr::CStr const &_Error, uch8 const *_pLocation)
	{
		NContainer::TCVector<NStr::CParseError> Errors;

		auto &Error = Errors.f_Insert();
		Error.m_Location = fg_GetJsonParseLocation<tf_CParseContext>(_Context, _pLocation);
		Error.m_Error = _Error;

		_Context.f_ThrowErrors(Errors);
	}

	inline CCommentSink::CPartition CCommentSink::f_PartitionAtFreestanding()
	{
		CPartition Return;
		if (m_iSeparatorComma < 0)
		{
			Return.m_Trailing = f_TakeAndClear();
			return Return;
		}

		fp_CommitAppender();
		auto const *pData = m_Buffer.f_GetStr();
		umint const Length = m_Buffer.f_GetLen();

		// Walk the buffer and the recorded block-comment ranges jointly. Comments are
		// stored in document order and do not overlap, so a single forward index
		// suffices. Skipping every block comment is equivalent to ignoring only
		// multi-line ones, since single-line block comments contain no newlines.
		umint iPartition = Length;
		umint iNextComment = 0;
		umint NumComments = m_Comments.f_GetLen();

		for (umint i = 0; i < Length; )
		{
			while (iNextComment < NumComments && (!m_Comments[iNextComment].m_bIsBlock || m_Comments[iNextComment].m_End <= i))
			{
				++iNextComment;
			}

			if (iNextComment < NumComments && i >= m_Comments[iNextComment].m_Start)
			{
				i = m_Comments[iNextComment].m_End;
				++iNextComment;
				continue;
			}

			if (pData[i] == '\n' || pData[i] == '\r')
			{
				iPartition = i;
				if (pData[i] == '\r' && i + 1 < Length && pData[i + 1] == '\n')
				{
					i += 2;
					continue;
				}
			}
			++i;
		}

		if (iPartition == Length)
		{
			Return.m_Trailing = f_TakeAndClear();
			return Return;
		}

		// Capture comma flags before f_TakeAndClear resets m_iSeparatorComma.
		bool const bTrailingHasComma = umint(m_iSeparatorComma) < iPartition;
		bool const bLeadingHasComma = umint(m_iSeparatorComma) >= iPartition;

		// Take ownership of m_Buffer into Trailing, then carve Leading out of
		// its suffix before truncating. This saves one allocation + copy
		// compared to materializing the prefix into a fresh CStr.
		Return.m_Trailing = f_TakeAndClear();
		Return.m_Trailing.m_bHasComma = bTrailingHasComma;

		auto const *pTrailingData = Return.m_Trailing.m_Text.f_GetStr();
		Return.m_Leading.m_Text = NStr::CStr(pTrailingData + iPartition, Length - iPartition);
		Return.m_Leading.m_bHasComma = bLeadingHasComma;

		auto *pWritable = Return.m_Trailing.m_Text.f_GetStrUniqueWritable();
		pWritable[iPartition] = 0;
		Return.m_Trailing.m_Text.f_SetStrLen(iPartition);

		return Return;
	}

	template <typename tf_CParseContext, typename tf_CCommentSink>
	inline_always void fg_ParseWhiteSpaceAndComments(uch8 const *&o_pParse, tf_CParseContext &_Context, tf_CCommentSink &_Sink)
	{
		using namespace NStr;

		auto pSegmentStart = o_pParse;
		while (true)
		{
			fg_ParseJsonWhiteSpace<tf_CParseContext>(o_pParse);

			if constexpr (tf_CParseContext::mc_bAllowComments)
			{
				if (o_pParse[0] == '/' && (o_pParse[1] == '/' || o_pParse[1] == '*'))
				{
					if constexpr (tf_CParseContext::mc_bRecordComments)
						_Sink.f_AppendVerbatim(pSegmentStart, o_pParse);

					auto pCommentStart = o_pParse;
					bool bIsBlock = o_pParse[1] == '*';
					if (bIsBlock)
					{
						o_pParse += 2;
						while (*o_pParse && !(o_pParse[0] == '*' && o_pParse[1] == '/'))
							++o_pParse;
						if (!*o_pParse)
							fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Unterminated block comment", pCommentStart);
						o_pParse += 2;
					}
					else
					{
						o_pParse += 2;
						while (*o_pParse && !fg_IsJsonLineTerminator<tf_CParseContext>(o_pParse))
							++o_pParse;
					}

					if constexpr (tf_CParseContext::mc_bRecordComments)
						_Sink.f_AppendComment(pCommentStart, o_pParse, bIsBlock);
					pSegmentStart = o_pParse;
					continue;
				}
			}
			break;
		}

		if constexpr (tf_CParseContext::mc_bRecordComments)
			_Sink.f_AppendVerbatim(pSegmentStart, o_pParse);
	}

	template <typename tf_CParseContext>
	inline_always bool fg_IsValueTerminator(uch8 const *_pParse) noexcept
	{
		using namespace NStr;

		if (!*_pParse)
			return true;
		if (fg_StrFindChar(tf_CParseContext::mc_ConstantEndCharacters, *_pParse) >= 0)
			return true;
		if (fg_IsJsonWhiteSpace<tf_CParseContext>(_pParse))
			return true;
		if constexpr (tf_CParseContext::mc_bAllowComments)
		{
			if (_pParse[0] == '/' && (_pParse[1] == '/' || _pParse[1] == '*'))
				return true;
		}
		return false;
	}

	inline bool fg_TryParseJsonDecimalInteger(uch8 const *_pStart, uch8 const *_pEnd, bool _bNegative, int64 &o_Value) noexcept
	{
		auto pParse = _pStart;
		if (*pParse == '+' || *pParse == '-')
			++pParse;

		uint64 Value = 0;
		constexpr uint64 c_MaxPositive = uint64(TCLimitsInt<int64>::mc_Max);
		constexpr uint64 c_MaxNegative = c_MaxPositive + 1;
		uint64 MaxValue = _bNegative ? c_MaxNegative : c_MaxPositive;

		while (pParse != _pEnd)
		{
			uint64 Digit = uint64(*pParse - '0');
			if (Value > (MaxValue - Digit) / 10)
				return false;

			Value = Value * 10 + Digit;
			++pParse;
		}

		if (_bNegative)
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

	template <typename tf_CParseContext>
	void CParseContext::f_ParseKey(NStr::CStr &o_Key, uch8 const *&o_pParse)
	{
		using namespace NStr;

		auto pParse = o_pParse;
		if (*pParse == '"')
		{
			auto pStartString = pParse;
			if (!fg_ParseJsonString<'\"', tf_CParseContext::mc_ParseJsonStringFlags>(o_Key, pParse, static_cast<tf_CParseContext &>(*this)))
				fg_ThrowJsonParseError<tf_CParseContext>(static_cast<tf_CParseContext const &>(*this), "End of string character \" not found for key name string", pStartString);
			o_pParse = pParse;
			return;
		}

		if constexpr (tf_CParseContext::mc_bAllowSingleQuote)
		{
			if (*pParse == '\'')
			{
				auto pStartString = pParse;
				if (!fg_ParseJsonString<'\'', tf_CParseContext::mc_ParseJsonStringFlags>(o_Key, pParse, static_cast<tf_CParseContext &>(*this)))
					fg_ThrowJsonParseError<tf_CParseContext>(static_cast<tf_CParseContext const &>(*this), "End of string character ' not found for key name string", pStartString);
				o_pParse = pParse;
				return;
			}
		}

		if constexpr (tf_CParseContext::mc_bAllowKeyWithoutQuote)
		{
			if (fg_CharIsAlphabetical(*pParse) || fg_StrFindChar(tf_CParseContext::mc_AllowedKeyWithoutQuoteCharacters, *pParse) >= 0)
			{
				auto pStartString = pParse;
				while (fg_CharIsAlphabetical(*pParse) || fg_CharIsNumber(*pParse) || fg_StrFindChar(tf_CParseContext::mc_AllowedKeyWithoutQuoteCharacters, *pParse) >= 0)
					++pParse;
				o_Key = CStr(pStartString, pParse - pStartString);
				o_Key.f_SetUserData(EJsonStringType_NoQuote);
				o_pParse = pParse;
				return;
			}
		}

		CStr StartCharacters = "\"";
		if constexpr (tf_CParseContext::mc_bAllowSingleQuote)
			StartCharacters += " or '";

		fg_ThrowJsonParseError<tf_CParseContext>(static_cast<tf_CParseContext const &>(*this), "Expected {} to start object key name"_f << StartCharacters, pParse);
	}

	template <typename tf_CParseContext, typename tf_CStr, typename tf_CSourceStr>
	void CParseContext::fs_GenerateString(tf_CStr &o_String, tf_CSourceStr const &_Value)
	{
		if constexpr (tf_CParseContext::mc_bAllowSingleQuote)
		{
			if (_Value.f_GetUserData() == EJsonStringType_SingleQuote)
			{
				fg_GenerateJsonString<'\'', tf_CParseContext>(o_String, _Value);
				return;
			}
		}
		fg_GenerateJsonString<'\"', tf_CParseContext>(o_String, _Value);
	}

	template <typename tf_CParseContext, typename tf_CStr, typename tf_CSourceStr>
	void CParseContext::fs_GenerateKeyString(tf_CStr &o_String, tf_CSourceStr const &_Key)
	{
		using namespace NStr;
		if constexpr (tf_CParseContext::mc_bAllowKeyWithoutQuote)
		{
			if (_Key.f_GetUserData() == EJsonStringType_NoQuote)
			{
				auto *pParse = _Key.f_GetStr();
				if (fg_CharIsAlphabetical(*pParse) || fg_StrFindChar(tf_CParseContext::mc_AllowedKeyWithoutQuoteCharacters, *pParse) >= 0)
				{
					while (fg_CharIsAlphabetical(*pParse) || fg_CharIsNumber(*pParse) || fg_StrFindChar(tf_CParseContext::mc_AllowedKeyWithoutQuoteCharacters, *pParse) >= 0)
						++pParse;

					if (!*pParse)
					{
						o_String += _Key;
						return;
					}
				}
			}
		}

		return tf_CParseContext::template fs_GenerateString<tf_CParseContext>(o_String, _Key);
	}

	template <typename tf_COutValue, typename tf_CParseContext>
	static void fg_ParseJsonArray(tf_COutValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		using namespace NStr;
		using CSink = TCConditional<tf_CParseContext::mc_bRecordComments, CCommentSink, CDiscardCommentSink>;
		DMibRequire(o_Value.f_Type() == EJsonType_Array);

		auto &Array = o_Value.f_Array();

		++_Context.m_ObjectArrayParseDepth;

		uch8 const *pParse = o_pParse;
		auto Cleanup = g_OnScopeExit / [&]
			{
				--_Context.m_ObjectArrayParseDepth;
				o_pParse = pParse;
			}
		;

		CSink Sink;
		Sink.f_Reset();
		fg_ParseWhiteSpaceAndComments(pParse, _Context, Sink);
		if constexpr (tf_CParseContext::mc_bRecordComments)
			Sink.f_CapturePendingLeading();

		if (*pParse == ']')
		{
			if constexpr (tf_CParseContext::mc_bRecordComments)
				o_Value.f_Trivia().f_SetInterior(Sink.f_TakePendingLeading().m_Text);
			return;
		}

		while (*pParse)
		{
			auto &Child = Array.f_Insert();
			if constexpr (tf_CParseContext::mc_bRecordComments)
			{
				auto Leading = Sink.f_TakePendingLeading();
				Child.f_Trivia().f_SetLeading(fg_Move(Leading.m_Text), Leading.m_bHasComma);
			}
			fg_ParseJsonValue(Child, pParse, _Context);

			DMibCheck(Child.f_Type() != EJsonType_Invalid || (_Context.m_Flags & EJsonDialectFlag_AllowUndefined));

			Sink.f_Reset();
			fg_ParseWhiteSpaceAndComments(pParse, _Context, Sink);

			bool bSawComma = false;
			if (*pParse == ',')
			{
				bSawComma = true;
				if constexpr (tf_CParseContext::mc_bRecordComments)
					Sink.f_AppendChar(',');
				++pParse;
				fg_ParseWhiteSpaceAndComments(pParse, _Context, Sink);
				if (*pParse == ']')
				{
					if constexpr (!tf_CParseContext::mc_bAllowTrailingCommas)
						fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Trailing comma not allowed", pParse);
					if constexpr (tf_CParseContext::mc_bRecordComments)
					{
						auto Trailing = Sink.f_TakeAndClear();
						Child.f_Trivia().f_SetTrailing(fg_Move(Trailing.m_Text), Trailing.m_bHasComma);
					}
					break;
				}
			}

			if (*pParse == ']')
			{
				if constexpr (tf_CParseContext::mc_bRecordComments)
				{
					auto Trailing = Sink.f_TakeAndClear();
					Child.f_Trivia().f_SetTrailing(fg_Move(Trailing.m_Text), Trailing.m_bHasComma);
				}
				break;
			}
			if (!*pParse)
				break;

			if (!bSawComma)
				fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Expected ',' or ']' after value", pParse);

			if constexpr (tf_CParseContext::mc_bRecordComments)
			{
				auto Partition = Sink.f_PartitionAtFreestanding();
				Child.f_Trivia().f_SetTrailing(fg_Move(Partition.m_Trailing.m_Text), Partition.m_Trailing.m_bHasComma);
				Sink.f_SetPendingLeading(fg_Move(Partition.m_Leading));
			}
		}
	}

	template <typename tf_COutValue, typename tf_CParseContext>
	static void fg_ParseJsonObject(tf_COutValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		using namespace NStr;
		using CSink = TCConditional<tf_CParseContext::mc_bRecordComments, CCommentSink, CDiscardCommentSink>;
		DMibRequire(o_Value.f_Type() == EJsonType_Object);

		auto &Object = o_Value.f_Object();

		++_Context.m_ObjectArrayParseDepth;

		uch8 const *pParse = o_pParse;
		auto Cleanup = g_OnScopeExit / [&]
			{
				--_Context.m_ObjectArrayParseDepth;
				o_pParse = pParse;
			}
		;

		CSink Sink;
		Sink.f_Reset();
		fg_ParseWhiteSpaceAndComments(pParse, _Context, Sink);
		if constexpr (tf_CParseContext::mc_bRecordComments)
			Sink.f_CapturePendingLeading();

		if (*pParse == '}')
		{
			if constexpr (tf_CParseContext::mc_bRecordComments)
				o_Value.f_Trivia().f_SetInterior(Sink.f_TakePendingLeading().m_Text);
			return;
		}

		while (*pParse)
		{
			CStr KeyName;

			auto pKeyStart = pParse;
			_Context.template f_ParseKey<tf_CParseContext>(KeyName, pParse);

			if constexpr (!tf_CParseContext::mc_bAllowDuplicateKeys)
			{
				if (Object.f_GetMember(KeyName))
					fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Duplicate keys not allowed", pKeyStart);
			}

			auto &Entry = Object.f_CreateMemberEntry(fg_Move(KeyName));
			if constexpr (tf_CParseContext::mc_bRecordComments)
			{
				auto Leading = Sink.f_TakePendingLeading();
				Entry.f_KeyTrivia().f_SetLeading(fg_Move(Leading.m_Text), Leading.m_bHasComma);
			}

			Sink.f_Reset();
			fg_ParseWhiteSpaceAndComments(pParse, _Context, Sink);
			if (*pParse != ':')
				fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Expected : to follow key name in object", pParse);
			if constexpr (tf_CParseContext::mc_bRecordComments)
				Entry.f_KeyTrivia().f_SetTrailing(Sink.f_TakeAndClear().m_Text);

			++pParse;
			Sink.f_Reset();
			fg_ParseWhiteSpaceAndComments(pParse, _Context, Sink);
			auto &Child = Entry.f_Value();
			if constexpr (tf_CParseContext::mc_bRecordComments)
			{
				auto Leading = Sink.f_TakeAndClear();
				Child.f_Trivia().f_SetLeading(fg_Move(Leading.m_Text), Leading.m_bHasComma);
			}

			fg_ParseJsonValue(Child, pParse, _Context);
			DMibCheck(Child.f_Type() != EJsonType_Invalid || (_Context.m_Flags & EJsonDialectFlag_AllowUndefined));

			Sink.f_Reset();
			fg_ParseWhiteSpaceAndComments(pParse, _Context, Sink);

			bool bSawComma = false;
			if (*pParse == ',')
			{
				bSawComma = true;
				if constexpr (tf_CParseContext::mc_bRecordComments)
					Sink.f_AppendChar(',');
				++pParse;
				fg_ParseWhiteSpaceAndComments(pParse, _Context, Sink);
				if (*pParse == '}')
				{
					if constexpr (!tf_CParseContext::mc_bAllowTrailingCommas)
						fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Trailing comma not allowed", pParse);
					if constexpr (tf_CParseContext::mc_bRecordComments)
					{
						auto Trailing = Sink.f_TakeAndClear();
						Child.f_Trivia().f_SetTrailing(fg_Move(Trailing.m_Text), Trailing.m_bHasComma);
					}
					break;
				}
			}

			if (*pParse == '}')
			{
				if constexpr (tf_CParseContext::mc_bRecordComments)
				{
					auto Trailing = Sink.f_TakeAndClear();
					Child.f_Trivia().f_SetTrailing(fg_Move(Trailing.m_Text), Trailing.m_bHasComma);
				}
				break;
			}
			if (!*pParse)
				break;

			if (!bSawComma)
				fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Expected ',' or '}' after value", pParse);

			if constexpr (tf_CParseContext::mc_bRecordComments)
			{
				auto Partition = Sink.f_PartitionAtFreestanding();
				Child.f_Trivia().f_SetTrailing(fg_Move(Partition.m_Trailing.m_Text), Partition.m_Trailing.m_bHasComma);
				Sink.f_SetPendingLeading(fg_Move(Partition.m_Leading));
			}
		}
	}

	template <uch8 t_QuoteCharacter, EParseJsonStringFlag t_Flags, typename tf_CParseContext, typename tf_FExtraParse>
	static bool fg_ParseJsonString(NStr::CStr &o_String, uch8 const *&o_pParse, tf_CParseContext &_Context, tf_FExtraParse &&_fExtraParse)
	{
		using namespace NStr;
		uch8 const *pParse = o_pParse;

		auto Cleanup = g_OnScopeExit / [&]
			{
				o_pParse = pParse;
				switch (t_QuoteCharacter)
				{
					case '\"': o_String.f_SetUserData(EJsonStringType_DoubleQuote); break;
					case '\'': o_String.f_SetUserData(EJsonStringType_SingleQuote); break;
					default: o_String.f_SetUserData(EJsonStringType_Custom); break;
				}
			}
		;

		if constexpr ((t_Flags & EParseJsonStringFlag_NoQuotes) == EParseJsonStringFlag_None)
		{
			DMibRequire(*pParse == t_QuoteCharacter);
			++pParse;
		}

		NStr::CStr::CAppender StringAppender(o_String);

		auto fAddChar = [&](uch8 _Character)
			{
				StringAppender += _Character;

				if constexpr (tf_CParseContext::mc_bRecordStringMap)
					_Context.f_MapCharacter(StringAppender.f_GetStrLen() - 1, pParse - _Context.m_pStartParse, 1);
			}
		;

		auto fAddUTF32Char = [&](ch32 _Character, uch8 const *_pErrorLocation)
			{
				if (_Character == 0)
				{
					if constexpr (tf_CParseContext::mc_bConvertNullToSpace)
						StringAppender.f_AddChar(' ');
					else
						fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Null characters not supported in this implementation", _pErrorLocation);
				}
				else
					StringAppender.f_AddUnicodeChar(_Character);
			}
		;

		while (*pParse)
		{
			if (*pParse == t_QuoteCharacter)
			{
				++pParse;
				if constexpr (t_Flags & EParseJsonStringFlag_AllowMultiLine)
				{
					if (*pParse == '\\')
					{
						++pParse;
						fg_ParseJsonWhiteSpace<tf_CParseContext>(pParse);
						if (*pParse != t_QuoteCharacter)
							fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Expected continuation of string", pParse);
						++pParse;
					}
					else
						return true;
				}
				else
					return true;
			}
			else if(*pParse == '\\')
			{
				++pParse;
				if constexpr (tf_CParseContext::mc_bAllowExtendedEscapes)
				{
					if (fg_ParseJsonLineTerminator<tf_CParseContext>(pParse))
						continue;
				}
				switch (*pParse)
				{
				case '\\':
				case '/':
				case t_QuoteCharacter:
					fAddChar(*pParse);
					++pParse;
					break;
				case 'b':
					fAddChar(0x08);
					++pParse;
					break;
				case 'f':
					fAddChar(0x0C);
					++pParse;
					break;
				case 'n':
					fAddChar(0x0A);
					++pParse;
					break;
				case 'r':
					fAddChar(0x0D);
					++pParse;
					break;
				case 't':
					fAddChar(0x09);
					++pParse;
					break;
				case 'v':
					if constexpr (tf_CParseContext::mc_bAllowExtendedEscapes)
					{
						fAddChar(0x0B);
						++pParse;
						break;
					}
					else
						fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Invalid escape value", pParse);
					break;
				case '0':
					if constexpr (tf_CParseContext::mc_bAllowExtendedEscapes)
					{
						auto pStart = pParse;
						++pParse;
						if (fg_CharIsNumber(*pParse))
							fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Decimal escape values are not supported", pStart);
						fAddUTF32Char(0, pStart);
						break;
					}
					else
						fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Invalid escape value", pParse);
					break;
				case 'x':
					if constexpr (tf_CParseContext::mc_bAllowExtendedEscapes)
					{
						auto pStart = pParse;
						++pParse;
						uch8 ToParse[3];
						for (umint i = 0; i < 2; ++i)
						{
							if (!pParse[i])
								fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Too short escaped hex value", pStart);
							ToParse[i] = pParse[i];
						}
						ToParse[2] = 0;
						uch8 const *pParseHex = ToParse;
						bool bFailed = false;
						auto HexDigit = fg_StrToIntParse
							(
								pParseHex
								, uint16(0)
								, (uch8 const *)nullptr
								, false
								, EStrToIntParseMode_Hex
								, &bFailed
							)
						;
						if (bFailed || *pParseHex)
							fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Invalid escaped hex value", pStart);
						pParse += 2;
						fAddUTF32Char(ch32(HexDigit), pStart);
						break;
					}
					else
						fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Invalid escape value", pParse);
					break;
				case 'u':
					{
						[[maybe_unused]] auto pStart = pParse;
						++pParse;
						CWStr EscapedUTF16String;

						while (true)
						{
							bool bFailed = false;
							uch8 ToParse[5];
							umint iToParse = 0;
							auto pParseStart = pParse;
							while (*pParse && iToParse < 4)
							{
								ToParse[iToParse] = *pParse;
								++pParse;
								++iToParse;
							}

							if (iToParse < 4)
								fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Too short escaped UTF16 value", pParseStart);

							ToParse[4] = 0;

							uch8 const *pParseHex = ToParse;

							ch16 HexDigit = fg_StrToIntParse
								(
									pParseHex
									, uint16(0)
									, (uch8 const *)nullptr
									, false
									, EStrToIntParseMode_Hex
									, &bFailed
								)
							;

							if (bFailed || *pParseHex)
								fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Invalid escaped UTF16 value", pParseStart);

							if (HexDigit == 0)
							{
								if constexpr (tf_CParseContext::mc_bConvertNullToSpace)
									EscapedUTF16String.f_AddChar(' ');
								else
									fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Null characters not supported in this implementation", pParseStart);
							}
							else
								EscapedUTF16String.f_AddChar(HexDigit);

							if (pParse[0] == '\\' && pParse[1] == 'u')
							{
								// Another escaped UTF16 character
								pParse += 2;
								continue;
							}
							break;
						}

						{
							auto Committed = StringAppender.f_Commit();

							if constexpr (tf_CParseContext::mc_bRecordStringMap)
							{
								auto StartLen = Committed.m_String.f_GetLen();
								Committed.m_String += EscapedUTF16String;
								_Context.f_MapCharacter(StartLen, pStart - o_pParse, Committed.m_String.f_GetLen());
							}
							else
								Committed.m_String += EscapedUTF16String;
						}
					}
					break;
				default:
				if constexpr (tf_CParseContext::mc_bAllowExtendedEscapes)
				{
					if (!*pParse || fg_CharIsNumber(*pParse) || *pParse == 'u' || *pParse == 'x' || fg_IsJsonLineTerminator<tf_CParseContext>(pParse))
						fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Invalid escape value", pParse);
					fAddChar(*pParse);
						++pParse;
					}
					else
						fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Invalid escape value", pParse);
					break;
				}
			}
			else
			{
				if constexpr (!NTraits::cIsSame<NTraits::TCRemoveReference<tf_FExtraParse>, bool>)
				{
					auto Committed = StringAppender.f_Commit();
					if (_fExtraParse(pParse))
						continue;
					else
						Committed.f_Abort();
				}

				if constexpr (tf_CParseContext::mc_bAllowExtendedEscapes)
				{
					if (fg_IsJsonLineTerminator<tf_CParseContext>(pParse))
						fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Raw line terminators are not allowed in strings. Use escaped line continuation.", pParse);
				}

				auto Character = *pParse;
				if (Character < 32)
				{
					bool bAllowCharacter = false;
					if constexpr (sizeof(tf_CParseContext::mc_AllowedControlCharacters) > 1)
					{
						for (auto AllowdCharacter : tf_CParseContext::mc_AllowedControlCharacters)
						{
							if (!AllowdCharacter)
								continue;

							if (Character == AllowdCharacter)
							{
								bAllowCharacter = true;
								break;
							}
						}
					}
					if (!bAllowCharacter)
						fg_ThrowJsonParseError<tf_CParseContext>(_Context, "Control characters or new lines not allowed in string. Use escaped characters.", pParse);
				}
				fAddChar(Character);
				++pParse;
			}
		}

		if constexpr ((t_Flags & EParseJsonStringFlag_NoQuotes) != EParseJsonStringFlag_None)
			return true;
		else
			return false;
	}

	template <typename tf_COutValue, typename tf_CParseContext>
	static inline_always bool fg_TryParseJson5SpecialNumber(tf_COutValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		using namespace NStr;

		if constexpr (!tf_CParseContext::mc_bAllowSignAndSpecial)
			return false;
		else
		{
			auto pParse = o_pParse;
			bool bNegative = false;
			if (*pParse == '+' || *pParse == '-')
			{
				bNegative = *pParse == '-';
				++pParse;
			}

			if (fg_StrStartsWith(pParse, "Infinity"))
			{
				auto pEnd = pParse + 8;
				if (!fg_IsValueTerminator<tf_CParseContext>(pEnd))
					return false;
				o_pParse = pEnd;
				o_Value = bNegative ? fp64::fs_NegInf() : fp64::fs_Inf();
				return true;
			}
			if (fg_StrStartsWith(pParse, "NaN"))
			{
				auto pEnd = pParse + 3;
				if (!fg_IsValueTerminator<tf_CParseContext>(pEnd))
					return false;
				o_pParse = pEnd;
				o_Value = bNegative ? fp64::fs_NegQNan() : fp64::fs_QNan();
				return true;
			}
			return false;
		}
	}

	inline bool fg_IsJsonHexDigit(uch8 _Char)
	{
		return (_Char >= '0' && _Char <= '9') || (_Char >= 'a' && _Char <= 'f') || (_Char >= 'A' && _Char <= 'F');
	}

	inline uint8 fg_JsonHexValue(uch8 _Char)
	{
		if (_Char >= '0' && _Char <= '9')
			return _Char - '0';
		if (_Char >= 'a' && _Char <= 'f')
			return _Char - 'a' + 10;
		return _Char - 'A' + 10;
	}

	template <typename tf_COutValue, typename tf_CParseContext>
	static inline_always bool fg_TryParseJsonNumber(tf_COutValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		using namespace NStr;
		auto pStart = o_pParse;

		if constexpr
			(
				!tf_CParseContext::mc_bAllowComments
				&& !tf_CParseContext::mc_bAllowExtendedWhitespace
				&& !tf_CParseContext::mc_bAllowHexNumbers
				&& !tf_CParseContext::mc_bAllowLeadingDecimal
				&& !tf_CParseContext::mc_bAllowSignAndSpecial
			)
		{
			auto pFastEnd = pStart;
			bool bFastFloat = false;
			auto fCanUseFastPath = [&]() -> bool
				{
					if (*pFastEnd == '-')
						++pFastEnd;

					if (*pFastEnd == '0')
					{
						++pFastEnd;
						if (fg_CharIsNumber(*pFastEnd))
							return false;
					}
					else if (*pFastEnd >= '1' && *pFastEnd <= '9')
					{
						do
						{
							++pFastEnd;
						}
						while (fg_CharIsNumber(*pFastEnd));
					}
					else
						return false;

					if (*pFastEnd == '.')
					{
						bFastFloat = true;
						++pFastEnd;
						if (!fg_CharIsNumber(*pFastEnd))
							return false;
						do
						{
							++pFastEnd;
						}
						while (fg_CharIsNumber(*pFastEnd));
					}

					if (*pFastEnd == 'e' || *pFastEnd == 'E')
					{
						bFastFloat = true;
						++pFastEnd;
						if (*pFastEnd == '+' || *pFastEnd == '-')
							++pFastEnd;
						if (!fg_CharIsNumber(*pFastEnd))
							return false;
						do
						{
							++pFastEnd;
						}
						while (fg_CharIsNumber(*pFastEnd));
					}

					return fg_IsValueTerminator<tf_CParseContext>(pFastEnd);
				}
			;

			if (fCanUseFastPath())
			{
				if (!bFastFloat)
				{
					int64 Number = 0;
					if (fg_TryParseJsonDecimalInteger(pStart, pFastEnd, *pStart == '-', Number))
					{
						o_pParse = pFastEnd;
						o_Value = Number;
						return true;
					}
				}
				else
				{
					uch8 const *pTryParse = pStart;
					fp64 FloatNumber = fg_StrToFloatParse
						(
							pTryParse
							, fp64::fs_Inf()
							, tf_CParseContext::mc_ConstantEndCharacters
							, false
							, "."
						)
					;

					if (FloatNumber != fp64::fs_Inf() && pTryParse == pFastEnd)
					{
						o_pParse = pTryParse;
						o_Value = FloatNumber;
						return true;
					}
				}
			}
		}

		auto pParse = pStart;

		auto fReject = [&](ch8 const *_pError) -> bool
			{
				if constexpr (tf_CParseContext::mc_bCustomParse)
					return false;
				else
				{
					fg_ThrowJsonParseError<tf_CParseContext>(_Context, _pError, pStart);
					return false;
				}
			}
		;

		bool bNegative = false;
		if (*pParse == '+')
		{
			if constexpr (!tf_CParseContext::mc_bAllowSignAndSpecial)
				return fReject("Leading '+' not allowed in strict JSON");
			++pParse;
		}
		else if (*pParse == '-')
		{
			bNegative = true;
			++pParse;
		}

		if (*pParse == '.')
		{
			if constexpr (!tf_CParseContext::mc_bAllowLeadingDecimal)
				return fReject("Leading '.' not allowed in strict JSON");
			if (!fg_CharIsNumber(pParse[1]))
				return fReject("'.' must be followed by a digit");
		}
		else if (pParse[0] == '0' && (pParse[1] == 'x' || pParse[1] == 'X'))
		{
			if constexpr (!tf_CParseContext::mc_bAllowHexNumbers)
				return fReject("Hex literals not allowed in strict JSON");

			pParse += 2;
			if (!fg_IsJsonHexDigit(*pParse))
				return fReject("Hex literal must contain at least one digit");

			uint64 Number = 0;
			while (fg_IsJsonHexDigit(*pParse))
			{
				auto Digit = uint64(fg_JsonHexValue(*pParse));

				if (Number > (TCLimitsInt<uint64>::mc_Max - Digit) / 16)
					return fReject("Number out of range");

				Number = Number * 16 + Digit;
				++pParse;
			}

			if (!fg_IsValueTerminator<tf_CParseContext>(pParse))
			{
				if (fg_CharIsAlphabetical(*pParse))
					return false;

				return fReject("Invalid character after number");
			}

			constexpr uint64 c_MaxPositive = uint64(TCLimitsInt<int64>::mc_Max);
			constexpr uint64 c_MaxNegative = c_MaxPositive + 1;
			if ((!bNegative && Number > c_MaxPositive) || (bNegative && Number > c_MaxNegative))
				return fReject("Number out of range");

			o_pParse = pParse;
			if (bNegative)
			{
				if (Number == c_MaxNegative)
					o_Value = TCLimitsInt<int64>::mc_Min;
				else
					o_Value = -int64(Number);
			}
			else
				o_Value = int64(Number);

			return true;
		}
		else if (pParse[0] == '0' && (pParse[1] == 'b' || pParse[1] == 'B' || pParse[1] == 'o' || pParse[1] == 'O'))
			return fReject("Binary/octal literals not allowed");
		else if (!fg_CharIsNumber(*pParse))
			return false;

		bool bHasIntegerDigits = false;
		bool bHasFraction = false;
		bool bHasExponent = false;

		if (fg_CharIsNumber(*pParse))
		{
			if (pParse[0] == '0' && fg_CharIsNumber(pParse[1]))
				return fReject("Leading zeros not allowed");
			while (fg_CharIsNumber(*pParse))
			{
				bHasIntegerDigits = true;
				++pParse;
			}
		}

		if (*pParse == '.')
		{
			bHasFraction = true;
			++pParse;
			if constexpr (!tf_CParseContext::mc_bAllowLeadingDecimal)
			{
				if (!fg_CharIsNumber(*pParse))
					return fReject("Decimal point must be followed by a digit");
			}
			if (!bHasIntegerDigits && !fg_CharIsNumber(*pParse))
				return fReject("'.' must be followed by a digit");
			while (fg_CharIsNumber(*pParse))
				++pParse;
		}

		if (*pParse == 'e' || *pParse == 'E')
		{
			bHasExponent = true;
			++pParse;
			if (*pParse == '+' || *pParse == '-')
				++pParse;
			if (!fg_CharIsNumber(*pParse))
				return fReject("Exponent must be followed by a digit");
			while (fg_CharIsNumber(*pParse))
				++pParse;
		}

		if (!fg_IsValueTerminator<tf_CParseContext>(pParse))
		{
			if (fg_CharIsAlphabetical(*pParse))
				return false;
			return fReject("Invalid character after number");
		}

		NStr::CStrPtr NumberString;
		NumberString.f_SetConstPtr((ch8 const *)pStart, pParse - pStart);
		o_pParse = pParse;
		if (!bHasFraction && !bHasExponent)
		{
			int64 IntegerValue = 0;
			if (!fg_TryParseJsonDecimalInteger(pStart, pParse, bNegative, IntegerValue))
				return fReject("Number out of range");

			o_Value = IntegerValue;
		}
		else
		{
			auto FloatValue = NumberString.f_ToFloat(fp64::fs_SNan());
			if constexpr (!tf_CParseContext::mc_bAllowSignAndSpecial)
			{
				if (FloatValue.f_IsInvalid() && !(_Context.m_Flags & EJsonDialectFlag_AllowInvalidFloat))
					return fReject("Invalid float value");
			}
			o_Value = FloatValue;
		}
		return true;
	}

	template <typename tf_COutValue, typename tf_CParseContext>
	static void fg_ParseJsonValue(tf_COutValue &o_Value, uch8 const *&o_pParse, tf_CParseContext &_Context)
	{
		using namespace NStr;
		using CSink = TCConditional<tf_CParseContext::mc_bRecordComments, CCommentSink, CDiscardCommentSink>;
		static_assert
			(
				!tf_CParseContext::mc_bRecordComments || tf_COutValue::mc_bPreserveComments
				, "recording JSON5 comments requires a comment-preserving alias (e.g. CJsonOrderedWithComments)"
			)
		;

		uch8 const *pParse = o_pParse;
		bool bSuccessful = false;
		if constexpr (tf_CParseContext::mc_bCustomParse)
			_Context.template f_PreParse<tf_CParseContext>(o_Value, pParse);

		auto Cleanup = g_OnScopeExitWithException / [&]
			{
				if constexpr (tf_CParseContext::mc_bCustomParse)
				{
					if (bSuccessful)
						_Context.template f_ParseAfterValue<tf_CParseContext>(o_Value, pParse);
				}
				if constexpr (tf_CParseContext::mc_bCustomParse)
					_Context.template f_PostParse<tf_CParseContext>(o_Value, pParse);
				o_pParse = pParse;
			}
		;

		CSink Sink;
		while (*pParse)
		{
			Sink.f_Reset();
			fg_ParseWhiteSpaceAndComments(pParse, _Context, Sink);

			auto Char = *pParse;

			switch (Char)
			{
			case '{':
				{
					// Object
					auto pParseStart = pParse;
					++pParse;
					o_Value.f_SetType(EJsonType_Object);
					fg_ParseJsonObject(o_Value, pParse, _Context);

					Sink.f_Reset();
					fg_ParseWhiteSpaceAndComments(pParse, _Context, Sink);

					if (*pParse != '}')
					{
						NContainer::TCVector<NStr::CParseError> Errors;
						{
							auto &Error = Errors.f_Insert();
							Error.m_Error = "Missing closing } for object";
							Error.m_Location = fg_GetJsonParseLocation<tf_CParseContext>(_Context, pParse);
						}
						{
							auto &Error = Errors.f_Insert();
							Error.m_Error = "See opening { for object";
							Error.m_Location = fg_GetJsonParseLocation<tf_CParseContext>(_Context, pParseStart);
						}
						_Context.f_ThrowErrors(Errors);
					}

					++pParse;
					bSuccessful = true;
					return;
				}
				break;
			case '[':
				{
					// Array
					auto pParseStart = pParse;
					++pParse;
					o_Value.f_SetType(EJsonType_Array);
					fg_ParseJsonArray(o_Value, pParse, _Context);

					Sink.f_Reset();
					fg_ParseWhiteSpaceAndComments(pParse, _Context, Sink);

					if (*pParse != ']')
					{
						NContainer::TCVector<NStr::CParseError> Errors;
						{
							auto &Error = Errors.f_Insert();
							Error.m_Error = "Missing closing ] for array";
							Error.m_Location = fg_GetJsonParseLocation<tf_CParseContext>(_Context, pParse);
						}
						{
							auto &Error = Errors.f_Insert();
							Error.m_Error = "See opening [ for array";
							Error.m_Location = fg_GetJsonParseLocation<tf_CParseContext>(_Context, pParseStart);
						}
						_Context.f_ThrowErrors(Errors);
					}

					++pParse;
					bSuccessful = true;
					return;
				}
				break;
			case '\"':
				{
					// String
					CStr ParsedString;
					auto pParseStart = pParse;
					if (!fg_ParseJsonString<'\"', tf_CParseContext::mc_ParseJsonStringFlags>(ParsedString, pParse, _Context))
						fg_ThrowJsonParseError<tf_CParseContext>(_Context, "End of string character \" not found for string", pParseStart);

					o_Value = ParsedString;
					bSuccessful = true;
					return;
				}
				break;
			default:
				{
					if constexpr (tf_CParseContext::mc_bAllowSingleQuote)
					{
						if (Char == '\'')
						{
							// String
							CStr ParsedString;
							auto pParseStart = pParse;
							if (!fg_ParseJsonString<'\'', tf_CParseContext::mc_ParseJsonStringFlags>(ParsedString, pParse, _Context))
								fg_ThrowJsonParseError<tf_CParseContext>(_Context, "End of string character ' not found for string", pParseStart);

							o_Value = ParsedString;
							bSuccessful = true;
							return;
						}
					}
					auto pParseStart = pParse;
					if (fg_StrStartsWith(pParse, "true"))
					{
						auto pParseTemp = pParse;
						pParseTemp += 4;
						if (fg_IsValueTerminator<tf_CParseContext>(pParseTemp))
						{
							pParse = pParseTemp;
							o_Value = true;
							bSuccessful = true;
							return;
						}
					}
					else if (fg_StrStartsWith(pParse, "false"))
					{
						auto pParseTemp = pParse;
						pParseTemp += 5;
						if (fg_IsValueTerminator<tf_CParseContext>(pParseTemp))
						{
							pParse = pParseTemp;
							o_Value = false;
							bSuccessful = true;
							return;
						}
					}
					else if (fg_StrStartsWith(pParse, "null"))
					{
						auto pParseTemp = pParse;
						pParseTemp += 4;
						if (fg_IsValueTerminator<tf_CParseContext>(pParseTemp))
						{
							pParse = pParseTemp;
							o_Value = nullptr;
							bSuccessful = true;
							return;
						}
					}
					else if ((_Context.m_Flags & EJsonDialectFlag_AllowUndefined) && fg_StrStartsWith(pParse, "undefined"))
					{
						auto pParseTemp = pParse;
						pParseTemp += 9;
						if (fg_IsValueTerminator<tf_CParseContext>(pParseTemp))
						{
							pParse = pParseTemp;
							o_Value = tf_COutValue();
							bSuccessful = true;
							return;
						}
					}

					if (_Context.m_Flags & EJsonDialectFlag_AllowInvalidFloat)
					{
						if (fg_StrStartsWith(pParse, "QNaN"))
						{
							auto pParseTemp = pParse;
							pParseTemp += 4;
							if (fg_IsValueTerminator<tf_CParseContext>(pParseTemp))
							{
								pParse = pParseTemp;
								o_Value = fp64::fs_QNan();
								bSuccessful = true;
								return;
							}
						}
						else if (fg_StrStartsWith(pParse, "-QNaN"))
						{
							auto pParseTemp = pParse;
							pParseTemp += 5;
							if (fg_IsValueTerminator<tf_CParseContext>(pParseTemp))
							{
								pParse = pParseTemp;
								o_Value = fp64::fs_NegQNan();
								bSuccessful = true;
								return;
							}
						}
						else if (fg_StrStartsWith(pParse, "SNaN"))
						{
							auto pParseTemp = pParse;
							pParseTemp += 4;
							if (fg_IsValueTerminator<tf_CParseContext>(pParseTemp))
							{
								pParse = pParseTemp;
								o_Value = fp64::fs_SNan();
								bSuccessful = true;
								return;
							}
						}
						else if (fg_StrStartsWith(pParse, "-SNaN"))
						{
							auto pParseTemp = pParse;
							pParseTemp += 5;
							if (fg_IsValueTerminator<tf_CParseContext>(pParseTemp))
							{
								pParse = pParseTemp;
								o_Value = fp64::fs_NegSNan();
								bSuccessful = true;
								return;
							}
						}
						else if (fg_StrStartsWith(pParse, "Inf"))
						{
							auto pParseTemp = pParse;
							pParseTemp += 3;
							if (fg_IsValueTerminator<tf_CParseContext>(pParseTemp))
							{
								pParse = pParseTemp;
								o_Value = fp64::fs_Inf();
								bSuccessful = true;
								return;
							}
						}
						else if (fg_StrStartsWith(pParse, "-Inf"))
						{
							auto pParseTemp = pParse;
							pParseTemp += 4;
							if (fg_IsValueTerminator<tf_CParseContext>(pParseTemp))
							{
								pParse = pParseTemp;
								o_Value = fp64::fs_NegInf();
								bSuccessful = true;
								return;
							}
						}
					}

					if (fg_TryParseJson5SpecialNumber(o_Value, pParse, _Context))
					{
						bSuccessful = true;
						return;
					}

					if (fg_TryParseJsonNumber(o_Value, pParse, _Context))
					{
						bSuccessful = true;
						return;
					}

					if constexpr (tf_CParseContext::mc_bCustomParse)
					{
						if (_Context.template f_ParseValue<tf_CParseContext>(o_Value, pParse))
						{
							bSuccessful = true;
							return;
						}
					}

					fg_ThrowJsonParseError<tf_CParseContext>(_Context, fg_Format("Invalid literal starting with: {}", CStr(pParse, 4)), pParseStart);
				}
				break;
			}
		}
	}
}

namespace NMib::NEncoding
{
	template <typename t_CParent>
	template <typename t_CParseContext>
	auto TCJsonValue<t_CParent>::fs_FromString(NStr::CStr const & _String, NStr::CStr const & _FileName, EJsonDialectFlag _Flags) -> CValue
	{
		using namespace NStr;
		static_assert
			(
				!t_CParseContext::mc_bRecordComments || CValue::mc_bPreserveComments
				, "recording JSON5 comments requires a comment-preserving alias (e.g. CJsonOrderedWithComments)"
			)
		;
		CValue Output;
		CStr ToParse = _String;

		uch8 const *pParse = reinterpret_cast<uch8 const *>(ToParse.f_GetStr());

		t_CParseContext Context;
		Context.m_pStartParse = pParse;
		Context.m_FileName = _FileName;
		Context.m_Flags = _Flags;

		using CSink = TCConditional<t_CParseContext::mc_bRecordComments, NJson::CCommentSink, NJson::CDiscardCommentSink>;
		CSink Sink;
		Sink.f_Reset();
		NJson::fg_ParseWhiteSpaceAndComments(pParse, Context, Sink);
		if constexpr (t_CParseContext::mc_bRecordComments)
		{
			auto Leading = Sink.f_TakeAndClear();
			Output.f_Trivia().f_SetLeading(fg_Move(Leading.m_Text), Leading.m_bHasComma);
		}

		// Any value is allowed at root
		NJson::fg_ParseJsonValue(Output, pParse, Context);

		Sink.f_Reset();
		NJson::fg_ParseWhiteSpaceAndComments(pParse, Context, Sink);
		if constexpr (t_CParseContext::mc_bRecordComments)
		{
			auto Trailing = Sink.f_TakeAndClear();
			Output.f_Trivia().f_SetTrailing(fg_Move(Trailing.m_Text), Trailing.m_bHasComma);
		}

		if (*pParse)
			NJson::fg_ThrowJsonParseError<t_CParseContext>(Context, "Unexpected character after root value", pParse);

		return fg_Move(Output);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::fs_FromString(NStr::CStr const & _String, NStr::CStr const & _FileName, EJsonDialectFlag _Flags) -> CValue
	{
		return fs_FromString<NJson::CParseContext>(_String, _FileName, _Flags);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::fs_FromStringStrict(NStr::CStr const & _String, NStr::CStr const & _FileName, EJsonDialectFlag _Flags) -> CValue
	{
		return fs_FromString<NJson::CStrictParseContext>(_String, _FileName, _Flags);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::fs_FromStringJsonC(NStr::CStr const & _String, NStr::CStr const & _FileName, EJsonDialectFlag _Flags) -> CValue
	{
		if constexpr (CValue::mc_bPreserveComments)
			return fs_FromString<NJson::CJsonCRecordingParseContext>(_String, _FileName, _Flags);
		else
			return fs_FromString<NJson::CJsonCParseContext>(_String, _FileName, _Flags);
	}

	template <typename t_CParent>
	auto TCJsonValue<t_CParent>::fs_FromStringJson5(NStr::CStr const & _String, NStr::CStr const & _FileName, EJsonDialectFlag _Flags) -> CValue
	{
		if constexpr (CValue::mc_bPreserveComments)
			return fs_FromString<NJson::CJson5RecordingParseContext>(_String, _FileName, _Flags);
		else
			return fs_FromString<NJson::CJson5ParseContext>(_String, _FileName, _Flags);
	}
}
