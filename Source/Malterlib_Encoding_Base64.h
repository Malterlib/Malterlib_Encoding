// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NEncoding
{
	extern ch8 g_Base64EncodingTable[65];
	extern int8 g_Base64EncodingTableReverse[256];

	template <typename t_CStreamType = NStream::CBinaryStreamDefault>
	class TCBinaryStream_Base64 : public t_CStreamType
	{
	private:
		void fp_WriteDirty();
		mint fp_PrepareBlock(NStream::CFilePos _Pos, bool _bWrite);

		NStream::CBinaryStream *mp_pStream;
		NFile::EFileOpen mp_OpenFlags;

		enum
		{
			EChunkSizeBase64 = 4,
			EChunkSizeData = 3
		};

		NStream::CFilePos mp_FilePos;
		NStream::CFilePos mp_CurrentLoaded;
		NStream::CFilePos mp_FileLen;
		uint8 mp_DecryptedData[EChunkSizeData];
		bool mp_bCurrentDirty;

	protected:
		DMibStreamImplementProtected(TCBinaryStream_Base64);
	public:
		DMibStreamImplementOperators(TCBinaryStream_Base64);

	//private:

	public:

		TCBinaryStream_Base64();
		~TCBinaryStream_Base64();
		void f_Close();
		void f_Open(NStream::CBinaryStream *_pStream, NFile::EFileOpen _OpenFlags);
		void f_FeedBytes(const void *_pMem, mint _nBytes);
		void f_ConsumeBytes(void *_pMem, mint _nBytes);
		bool f_IsValid() const;
		bool f_IsAtEndOfStream() const;
		NStream::CFilePos f_GetPosition() const;
		void f_SetPosition(NStream::CFilePos _Pos);
		void f_SetPositionFromEnd(NStream::CFilePos _Pos);
		void f_AddPosition(NStream::CFilePos _Pos);
		bool f_IsValidReadPosition(NStream::CFilePos _Pos) const;
		void f_Flush(bool _bLocalCacheOnly);
		void f_SetCacheSize(mint _CacheSize);
		NStream::CFilePos f_GetLength() const;
		mint f_ContainerLengthLimit() const;
		void f_SetLength(NStream::CFilePos _Length) { DMibError("Not supported"); }

	};

	NStr::CStr fg_Base64Encode(NStr::CStr const &_String);
	NStr::CStr fg_Base64Decode(NStr::CStr const &_String);

	NStr::CStr fg_Base64Encode(const NContainer::CByteVector &_Data);
	NStr::CStrSecure fg_Base64Encode(const NContainer::CSecureByteVector &_Data);
	void fg_Base64Decode(NStr::CStr const &_String, NContainer::CByteVector &_Data);
	void fg_Base64Decode(NStr::CStrSecure const &_String, NContainer::CSecureByteVector &_Data);
}

#include "Malterlib_Encoding_Base64.hpp"

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
