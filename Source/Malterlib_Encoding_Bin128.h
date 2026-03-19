// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NEncoding
{
	template <typename t_CStreamType = NStream::CBinaryStreamDefault>
	class TCBinaryStream_Bin128 : public t_CStreamType
	{
	private:
		void fp_WriteDirty();
		umint fp_PrepareBlock(NStream::CFilePos _Pos, bool _bWrite);

		NStream::CBinaryStream *mp_pStream;
		NFile::EFileOpen mp_OpenFlags;

		enum
		{
			EChunkSizeBin128 = 8
			, EChunkSizeData = 7
		};

		NStream::CFilePos mp_ParentFilePos;
		NStream::CFilePos mp_FilePos;
		NStream::CFilePos mp_ParentLength;
		NStream::CFilePos mp_CurrentLoaded;
		NStream::CFilePos mp_WriteFileLen;
		uint8 mp_DecryptedData[EChunkSizeData] = {0};
		uint8 mp_Offset;
		bool mp_bCurrentDirty;

	protected:
		DMibStreamImplementProtected(TCBinaryStream_Bin128);
	public:
		DMibStreamImplementOperators(TCBinaryStream_Bin128);

	public:

		TCBinaryStream_Bin128(bool _bUseUpper = false);
		~TCBinaryStream_Bin128();
		void f_Close();
		void f_Open(NStream::CBinaryStream *_pStream, NFile::EFileOpen _OpenFlags, NStream::CFilePos _ParentLength = -1);
		void f_FeedBytes(const void *_pMem, umint _nBytes);
		void f_ConsumeBytes(void *_pMem, umint _nBytes);
		bool f_IsValid() const;
		bool f_IsAtEndOfStream() const;
		NStream::CFilePos f_GetPosition() const;
		void f_SetPosition(NStream::CFilePos _Pos);
		void f_SetPositionFromEnd(NStream::CFilePos _Pos);
		void f_AddPosition(NStream::CFilePos _Pos);
		bool f_IsValidReadPosition(NStream::CFilePos _Pos) const;
		void f_Flush(bool _bLocalCacheOnly);
		void f_SetCacheSize(umint _CacheSize);
		NStream::CFilePos f_GetLength() const;
		umint f_ContainerLengthLimit() const;
		void f_SetLength(NStream::CFilePos _Length) { DMibError("Not supported"); }

	};

	NContainer::CByteVector fg_Bin128Encode(NContainer::CByteVector const &_Data, bool _bUseUpper = false);
	NContainer::CSecureByteVector fg_Bin128Encode(NContainer::CSecureByteVector const &_Data, bool _bUseUpper = false);

	NContainer::CByteVector fg_Bin128Decode(NContainer::CByteVector const &_Data, bool _bUseUpper = false);
	NContainer::CSecureByteVector fg_Bin128Decode(NContainer::CSecureByteVector const &_Data, bool _bUseUpper = false);
}

#include "Malterlib_Encoding_Bin128.hpp"

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
