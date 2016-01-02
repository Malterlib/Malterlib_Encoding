// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_Base64.h"

namespace NMib
{
	namespace NDataProcessing
	{

		ch8 g_Base64EncodingTable[65] = 
		{
			'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
			'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
			'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
			'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/',
			'=' // Padding
		};

		ch8 g_Base64EncodingTableReverse[256] = 
		{
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
			52,53,54,55,56,57,58,59,60,61,-1,-1,-1,64,-1,-1,
			-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,
			15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
			-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
			41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		};
		
		NStr::CStr fg_Base64Encode(NStr::CStr const &_String)
		{
			NStream::CBinaryStreamMemoryPtr<> Stream;
			int FLen = ((_String.f_GetLen()+2) / 3) * 4;
			NStr::CStr Ret;
			Stream.f_OpenReadWrite(Ret.f_GetStr(FLen+1), FLen);
			{
				TCBinaryStream_Base64<> Base64;
				Base64.f_Open(&Stream, NFile::EFileOpen_Write);
				Base64.f_FeedBytes(_String.f_GetStr(), _String.f_GetLen());
			}
			Ret.f_SetAt(FLen, 0);
			return Ret;
		}

		NStr::CStr fg_Base64Decode(NStr::CStr const &_String)
		{
			NStream::CBinaryStreamMemoryPtr<> Stream;
			Stream.f_OpenRead(_String.f_GetStr(), _String.f_GetLen());
			NStr::CStr Ret;
			{
				TCBinaryStream_Base64<> Base64;
				Base64.f_Open(&Stream, NFile::EFileOpen_Read);
				mint FLen = Base64.f_GetLength();
				Base64.f_ConsumeBytes(Ret.f_GetStr(FLen+1), FLen);
				Ret.f_SetAt(FLen, 0);
			}
			return Ret;
		}

		NStr::CStr fg_Base64Encode(const NContainer::TCVector<uint8> &_Data)
		{
			NStream::CBinaryStreamMemoryPtr<> Stream;
			int FLen = ((_Data.f_GetLen()+2) / 3) * 4;
			NStr::CStr Ret;
			Stream.f_OpenReadWrite(Ret.f_GetStr(FLen+1), FLen);
			{
				TCBinaryStream_Base64<> Base64;
				Base64.f_Open(&Stream, NFile::EFileOpen_Write);
				Base64.f_FeedBytes(_Data.f_GetArray(), _Data.f_GetLen());
			}
			Ret.f_SetAt(FLen, 0);
			return Ret;
		}

		void fg_Base64Decode(NStr::CStr const &_String, NContainer::TCVector<uint8> &_Data)
		{
			if (_String.f_IsEmpty())
				return;
			NStream::CBinaryStreamMemoryPtr<> Stream;
			Stream.f_OpenRead(_String.f_GetStr(), _String.f_GetLen());
			{
				TCBinaryStream_Base64<> Base64;
				Base64.f_Open(&Stream, NFile::EFileOpen_Read);
				mint FLen = Base64.f_GetLength();
				_Data.f_SetLen(FLen);
				Base64.f_ConsumeBytes(_Data.f_GetArray(), FLen);
			}
		}


	}
}
