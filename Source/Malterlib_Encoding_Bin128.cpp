// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_Bin128.h"

namespace NMib::NEncoding
{
	NContainer::CByteVector fg_Bin128Encode(NContainer::CByteVector const &_Data, bool _bUseUpper)
	{
		NStream::CBinaryStreamMemory<> Stream;
		{
			TCBinaryStream_Bin128<> Bin128(_bUseUpper);
			Bin128.f_Open(&Stream, NFile::EFileOpen_Write);
			Bin128.f_FeedBytes(_Data.f_GetArray(), _Data.f_GetLen());
		}
		return Stream.f_MoveVector();
	}

	NContainer::CSecureByteVector fg_Bin128Encode(NContainer::CSecureByteVector const &_Data, bool _bUseUpper)
	{
		NStream::CBinaryStreamMemory<NStream::CBinaryStreamDefault, NContainer::CSecureByteVector> Stream;
		{
			TCBinaryStream_Bin128<> Bin128(_bUseUpper);
			Bin128.f_Open(&Stream, NFile::EFileOpen_Write);
			Bin128.f_FeedBytes(_Data.f_GetArray(), _Data.f_GetLen());
		}
		return Stream.f_MoveVector();
	}

	NContainer::CByteVector fg_Bin128Decode(NContainer::CByteVector const &_Data, bool _bUseUpper)
	{
		NStream::CBinaryStreamMemoryPtr<> Stream;
		Stream.f_OpenRead(_Data);
		NContainer::CByteVector Ret;
		{
			TCBinaryStream_Bin128<> Bin128(_bUseUpper);
			Bin128.f_Open(&Stream, NFile::EFileOpen_Read);
			auto Length = Bin128.f_GetLength();
			Bin128.f_ConsumeBytes(Ret.f_GetArray(Length), Length);
		}
		return Ret;
	}

	NContainer::CSecureByteVector fg_Bin128Decode(NContainer::CSecureByteVector const &_Data, bool _bUseUpper)
	{
		NStream::CBinaryStreamMemoryPtr<> Stream;
		Stream.f_OpenRead(_Data);
		NContainer::CSecureByteVector Ret;
		{
			TCBinaryStream_Bin128<> Bin128(_bUseUpper);
			Bin128.f_Open(&Stream, NFile::EFileOpen_Read);
			auto Length = Bin128.f_GetLength();
			Bin128.f_ConsumeBytes(Ret.f_GetArray(Length), Length);
		}
		return Ret;
	}
}
