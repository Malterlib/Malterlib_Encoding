// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NEncoding::NYaml
{
	template <typename tf_CStr, typename tf_CUInt>
	inline void fg_AppendYamlUnsigned(tf_CStr &o_String, tf_CUInt _Value)
	{
		ch8 Buffer[32];
		auto pWrite = Buffer + sizeof(Buffer) - 1;
		*pWrite = 0;

		do
		{
			*--pWrite = ch8('0' + (_Value % 10));
			_Value /= 10;
		}
		while (_Value);

		o_String.f_AddString(pWrite, Buffer + sizeof(Buffer) - 1 - pWrite);
	}

	template <typename tf_CStr, typename tf_CUInt>
	inline void fg_AppendYamlZeroPaddedUnsigned(tf_CStr &o_String, tf_CUInt _Value, umint _Width)
	{
		ch8 Buffer[32];
		auto pWrite = Buffer + _Width;
		*pWrite = 0;

		for (umint i = 0; i < _Width; ++i)
		{
			*--pWrite = ch8('0' + (_Value % 10));
			_Value /= 10;
		}

		if (_Value)
			fg_AppendYamlUnsigned(o_String, _Value);

		o_String.f_AddString(pWrite, Buffer + _Width - pWrite);
	}

	template <typename tf_CStr>
	inline void fg_FormatYamlTimestamp(tf_CStr &o_String, NTime::CTime const &_Time)
	{
		NTime::CTime RoundedTime = _Time;
		constexpr uint64 Billion = 1'000'000'000;
		constexpr uint64 Divisor = NTime::NPrivate::CConst::mc_FractionDividend / Billion;
		uint64 Fraction = (_Time.f_GetFractionInt() + Divisor / 2) / Divisor;
		if (Fraction == 1'000'000'000)
		{
			RoundedTime.f_SetSeconds(_Time.f_GetSeconds() + 1);
			Fraction = 0;
		}

		auto DateTime = NTime::CTimeConvert(RoundedTime).f_ExtractDateTime();

		fg_AppendYamlUnsigned(o_String, DateTime.m_Year);
		o_String += '-';
		fg_AppendYamlZeroPaddedUnsigned(o_String, DateTime.m_Month, 2);
		o_String += '-';
		fg_AppendYamlZeroPaddedUnsigned(o_String, DateTime.m_DayOfMonth, 2);
		o_String += 'T';
		fg_AppendYamlZeroPaddedUnsigned(o_String, DateTime.m_Hour, 2);
		o_String += ':';
		fg_AppendYamlZeroPaddedUnsigned(o_String, DateTime.m_Minute, 2);
		o_String += ':';
		fg_AppendYamlZeroPaddedUnsigned(o_String, DateTime.m_Second, 2);

		if (Fraction)
		{
			ch8 FractionString[10];
			FractionString[9] = 0;
			for (umint i = 9; i > 0; --i)
			{
				FractionString[i - 1] = ch8('0' + (Fraction % 10));
				Fraction /= 10;
			}

			auto pEnd = FractionString + 9;
			while (pEnd > FractionString && pEnd[-1] == '0')
				--pEnd;
			*pEnd = 0;

			o_String += '.';
			o_String += FractionString;
		}

		o_String += 'Z';
	}
}

namespace NMib::NEncoding
{
	inline NTime::CTime fg_ParseYamlTimestamp(NStr::CStr const &_String)
	{
		using namespace NYaml;

		auto Text = _String.f_Trim();
		auto pParse = Text.f_GetStr();
		int64 Year = 0;
		int64 Month = 0;
		int64 Day = 0;
		int64 Hour = 0;
		int64 Minute = 0;
		int64 Second = 0;
		uint64 Fraction = 0;
		int64 OffsetSign = 1;
		int64 OffsetHour = 0;
		int64 OffsetMinute = 0;

		if (!fg_YamlParseNDigits(pParse, 4, Year) || *pParse++ != '-' || !fg_YamlParseNDigits(pParse, 2, Month) || *pParse++ != '-' || !fg_YamlParseNDigits(pParse, 2, Day))
			DMibError("Invalid YAML timestamp date");

		if (!*pParse)
			return NTime::CTimeConvert::fs_CreateTime(Year, Month, Day, 0, 0, 0, 0.0);

		if (*pParse == 'T' || *pParse == 't')
			++pParse;
		else if (*pParse == ' ')
		{
			while (*pParse == ' ')
				++pParse;
		}
		else
			DMibError("Invalid YAML timestamp date/time separator");

		if (!fg_YamlParseVariableDigits(pParse, 1, 2, Hour) || *pParse++ != ':' || !fg_YamlParseNDigits(pParse, 2, Minute) || *pParse++ != ':' || !fg_YamlParseNDigits(pParse, 2, Second))
			DMibError("Invalid YAML timestamp time");

		if (*pParse == '.')
		{
			++pParse;
			uint64 FractionDecimal = 0;
			uint64 Divisor = 1;
			if (*pParse < '0' || *pParse > '9')
				DMibError("Invalid YAML timestamp fraction");
			while (*pParse >= '0' && *pParse <= '9')
			{
				if (Divisor < constant_uint64(1'000'000'000))
				{
					FractionDecimal = FractionDecimal * 10 + uint64(*pParse - '0');
					Divisor *= 10;
				}
				++pParse;
			}

			uint64 const FractionDivisor = NTime::NPrivate::CConst::mc_FractionDividend / Divisor;
			uint64 const FractionRemainder = NTime::NPrivate::CConst::mc_FractionDividend % Divisor;
			Fraction = FractionDecimal * FractionDivisor + FractionDecimal * FractionRemainder / Divisor;
		}

		while (*pParse == ' ')
			++pParse;

		if (*pParse == 'Z' || *pParse == 'z')
			++pParse;
		else if (*pParse == '+' || *pParse == '-')
		{
			OffsetSign = *pParse == '+' ? 1 : -1;
			++pParse;

			if (!fg_YamlParseVariableDigits(pParse, 1, 2, OffsetHour))
				DMibError("Invalid YAML timestamp timezone hour");

			if (OffsetHour > 23)
				DMibError("YAML timestamp timezone hour out of range");

			if (*pParse == ':')
			{
				++pParse;

				if (!fg_YamlParseNDigits(pParse, 2, OffsetMinute))
					DMibError("Invalid YAML timestamp timezone minute");

				if (OffsetMinute > 59)
					DMibError("YAML timestamp timezone minute out of range");
			}
		}

		if (*pParse)
			DMibError("Unexpected trailing characters after YAML timestamp");

		auto Time = NTime::CTimeConvert::fs_CreateTimeIntFrac(Year, Month, Day, Hour, Minute, Second, Fraction);
		auto Offset = NTime::CTimeSpanConvert::fs_CreateMinuteSpan(OffsetSign * (OffsetHour * 60 + OffsetMinute));

		return Time - Offset;
	}

	inline NStr::CStr fg_FormatYamlTimestamp(NTime::CTime const &_Time)
	{
		NStr::CStr Return;
		NStr::CStr::CAppender Appender(Return);
		NYaml::fg_FormatYamlTimestamp(Appender, _Time);
		return Return;
	}
}
