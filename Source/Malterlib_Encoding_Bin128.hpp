// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NEncoding
{
	template <typename t_CStreamType>
	TCBinaryStream_Bin128<t_CStreamType>::TCBinaryStream_Bin128(bool _bUseUpper)
	{
		mp_pStream = nullptr;
		mp_OpenFlags = NFile::EFileOpen_None;
		mp_CurrentLoaded = -1;
		mp_FilePos = 0;
		mp_bCurrentDirty = false;
		if (_bUseUpper)
			mp_Offset = 0x80;
		else
			mp_Offset = 0;
	}

	template <typename t_CStreamType>
	TCBinaryStream_Bin128<t_CStreamType>::~TCBinaryStream_Bin128()
	{
		f_Close();
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Bin128<t_CStreamType>::f_Close()
	{
		if (mp_bCurrentDirty)
			fp_WriteDirty();
		mp_OpenFlags = NFile::EFileOpen_None;
		NMemory::fg_SecureMemClear(mp_DecryptedData);
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Bin128<t_CStreamType>::f_Open(NStream::CBinaryStream *_pStream, NFile::EFileOpen _OpenFlags, NStream::CFilePos _ParentLength)
	{
		mp_pStream = _pStream;
		mp_OpenFlags = _OpenFlags;
		mp_bCurrentDirty = false;
		mp_ParentFilePos = _pStream->f_GetPosition();
		mp_ParentLength = _ParentLength;
		mp_WriteFileLen = 0;
		mp_FilePos = 0;

		if (!(mp_OpenFlags == NFile::EFileOpen_Write || mp_OpenFlags == NFile::EFileOpen_Read))
			DMibErrorFile("You must open the file either with read or write access not both at the same time");
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Bin128<t_CStreamType>::fp_WriteDirty()
	{
		mp_pStream->f_SetPosition(mp_ParentFilePos + (mp_CurrentLoaded/7)*8);

		mint nBytes = (fg_Min(mp_WriteFileLen - mp_CurrentLoaded, NStream::CFilePos(EChunkSizeData)) * 8 + 6) / 7;

		uint64 ByteData = 0;
		NMemory::fg_MemCopy(&ByteData, mp_DecryptedData, EChunkSizeData);
		ByteData = fg_ByteSwapBE(ByteData);

		mint Shift = 7*7 + 8;
		uint8 Temp[EChunkSizeBin128];

		for (mint iByte = 0; iByte < nBytes; ++iByte)
		{
			auto Shifted = ByteData >> Shift;
			Temp[iByte] = ((Shifted) & 0x7f) + mp_Offset;
			Shift -= 7;
		}

		mp_pStream->f_FeedBytes(Temp, nBytes);
		mp_bCurrentDirty = false;
	}

	template <typename t_CStreamType>
	mint TCBinaryStream_Bin128<t_CStreamType>::fp_PrepareBlock(NStream::CFilePos _Pos, bool _bWrite)
	{
		if (mp_CurrentLoaded >= 0 && _Pos >=  mp_CurrentLoaded && _Pos < mp_CurrentLoaded + EChunkSizeData)
		{
			return _Pos - mp_CurrentLoaded;
		}

		if (mp_bCurrentDirty)
			fp_WriteDirty();

		mp_CurrentLoaded = (_Pos / 7) * 7;
		NStream::CFilePos BlockPos = (_Pos / 7) * 8;
		NStream::CFilePos ParentLength = mp_pStream->f_GetLength() - mp_ParentFilePos;
		if (mp_ParentLength >= 0)
			ParentLength = mp_ParentLength;

		if (BlockPos >= ParentLength)
		{
			if (_bWrite)
				NMemory::fg_SecureMemClear(mp_DecryptedData);
			else
				DMibErrorFile("Read past end of file");
		}
		else
		{
			mp_pStream->f_SetPosition(mp_ParentFilePos + BlockPos);
			mint nBytesIn = fg_Min(ParentLength - BlockPos, NStream::CFilePos(EChunkSizeBin128));
			mint nBytesOut = (nBytesIn * 7) / 8;

			uint8 InBytes[EChunkSizeBin128] = {0};
			mp_pStream->f_ConsumeBytes(InBytes, nBytesIn);
			mint Shift = 64;
			uint64 ByteDataOut = 0;
			for (mint iByte = 0; iByte < nBytesIn; ++iByte)
			{
				Shift -= 7;
				ByteDataOut |= uint64(InBytes[iByte] - mp_Offset) << Shift;
			}
			ByteDataOut = fg_ByteSwapBE(ByteDataOut);
			NMemory::fg_MemCopy(mp_DecryptedData, &ByteDataOut, nBytesOut);

			if ((mp_CurrentLoaded + NStream::CFilePos(nBytesOut)) > mp_WriteFileLen)
				mp_WriteFileLen = mp_CurrentLoaded + NStream::CFilePos(nBytesOut);
		}

		return _Pos - mp_CurrentLoaded;
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Bin128<t_CStreamType>::f_FeedBytes(const void *_pMem, mint _nBytes)
	{
		if (!(mp_OpenFlags & NFile::EFileOpen_Write))
			DMibErrorFile("File was not opened for write.");

		const uint8 *pMem = (const uint8 *)_pMem;
		while (_nBytes)
		{
			mint Pos = fp_PrepareBlock(mp_FilePos, true);
			mint ThisTime = fg_Min(_nBytes, (mint)EChunkSizeData - Pos);
			NMemory::fg_MemCopy(mp_DecryptedData + Pos, pMem, ThisTime);
			mp_bCurrentDirty = true;

			mp_FilePos += ThisTime;
			pMem += ThisTime;
			_nBytes -= ThisTime;
			if (mp_FilePos > mp_WriteFileLen)
				mp_WriteFileLen = mp_FilePos;
		}
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Bin128<t_CStreamType>::f_ConsumeBytes(void *_pMem, mint _nBytes)
	{
		if (!(mp_OpenFlags & NFile::EFileOpen_Read))
			DMibErrorFile("File was not opened for read.");

		uint8 *pMem = (uint8 *)_pMem;
		while (_nBytes)
		{
			mint Pos = fp_PrepareBlock(mp_FilePos, false);

			if (mp_FilePos >= mp_WriteFileLen)
				DMibErrorFile("Read past end of file");

			mint ThisTime = fg_Min(_nBytes, (mint)EChunkSizeData - Pos);
			NMemory::fg_MemCopy(pMem, mp_DecryptedData + Pos, ThisTime);

			mp_FilePos += ThisTime;
			pMem += ThisTime;
			_nBytes -= ThisTime;
		}
	}

	template <typename t_CStreamType>
	bool TCBinaryStream_Bin128<t_CStreamType>::f_IsValid() const
	{
		return mp_pStream->f_IsValid();
	}

	template <typename t_CStreamType>
	bool TCBinaryStream_Bin128<t_CStreamType>::f_IsAtEndOfStream() const
	{
		if (mp_ParentLength >= 0)
		{
			auto Length = (mp_ParentLength * 7) / 8;
			if (mp_FilePos >= Length)
				return true;
		}
		return mp_pStream->f_IsAtEndOfStream();
	}

	template <typename t_CStreamType>
	NStream::CFilePos TCBinaryStream_Bin128<t_CStreamType>::f_GetPosition() const
	{
		return mp_FilePos;
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Bin128<t_CStreamType>::f_SetPosition(NStream::CFilePos _Pos)
	{
		mp_FilePos = _Pos;
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Bin128<t_CStreamType>::f_SetPositionFromEnd(NStream::CFilePos _Pos)
	{
		mp_FilePos = ((mp_pStream->f_GetLength() - mp_ParentFilePos)/8)*7 - _Pos;
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Bin128<t_CStreamType>::f_AddPosition(NStream::CFilePos _Pos)
	{
		mp_FilePos += _Pos;
	}

	template <typename t_CStreamType>
	bool TCBinaryStream_Bin128<t_CStreamType>::f_IsValidReadPosition(NStream::CFilePos _Pos) const
	{
		if (mp_ParentLength >= 0)
		{
			return _Pos >= 0 && _Pos < f_GetLength();
		}

		return mp_pStream->f_IsValidReadPosition(mp_ParentFilePos + ((_Pos * 8) / 7));
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Bin128<t_CStreamType>::f_Flush(bool _bLocalCacheOnly)
	{
		return mp_pStream->f_Flush(_bLocalCacheOnly);
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Bin128<t_CStreamType>::f_SetCacheSize(mint _CacheSize)
	{
		return mp_pStream->f_SetCacheSize(_CacheSize);
	}

	template <typename t_CStreamType>
	NStream::CFilePos TCBinaryStream_Bin128<t_CStreamType>::f_GetLength() const
	{
		if (mp_ParentLength >= 0)
			return (mp_ParentLength * 7) / 8;

		return fg_Max((mp_pStream->f_GetLength() * 7) / 8, fg_Max(mp_CurrentLoaded, mp_FilePos));
	}

	template <typename t_CStreamType>
	mint TCBinaryStream_Bin128<t_CStreamType>::f_ContainerLengthLimit() const
	{
		return NStream::fg_CapLengthLimit(f_GetLength() - f_GetPosition());
	}
}
