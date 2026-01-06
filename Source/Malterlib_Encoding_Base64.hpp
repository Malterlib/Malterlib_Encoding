// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NEncoding
{
	template <typename t_CStreamType>
	TCBinaryStream_Base64<t_CStreamType>::TCBinaryStream_Base64()
	{
		mp_pStream = nullptr;
		mp_OpenFlags = NFile::EFileOpen_None;
		mp_CurrentLoaded = -1;
		mp_FilePos = 0;
		mp_bCurrentDirty = false;
		mp_FileLen = 0;
	}

	template <typename t_CStreamType>
	TCBinaryStream_Base64<t_CStreamType>::~TCBinaryStream_Base64()
	{
		f_Close();
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Base64<t_CStreamType>::f_Close()
	{
		if (mp_bCurrentDirty)
			fp_WriteDirty();
		mp_OpenFlags = NFile::EFileOpen_None;
		NMemory::fg_SecureMemClear(mp_DecryptedData);
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Base64<t_CStreamType>::f_Open(NStream::CBinaryStream *_pStream, NFile::EFileOpen _OpenFlags)
	{
		mp_pStream = _pStream;
		mp_OpenFlags = _OpenFlags;
		mp_pStream->f_SetPosition(0);
		mp_bCurrentDirty = false;

		if (mp_OpenFlags == NFile::EFileOpen_Write)
		{
			mp_FilePos = 0;
		}
		else if (mp_OpenFlags == NFile::EFileOpen_Read)
		{
			mp_FilePos = 0;
			NStream::CFilePos FLen = mp_pStream->f_GetLength();
			mp_pStream->f_SetPositionFromEnd(-2);
			uint8 Bytes[2];
			mp_pStream->f_ConsumeBytes(Bytes, 2);
			if (g_Base64EncodingTableReverse[Bytes[0]] == 64)
				mp_FileLen = ((FLen / 4) * 3) - 2;
			else if (g_Base64EncodingTableReverse[Bytes[1]] == 64)
				mp_FileLen = ((FLen / 4) * 3) - 1;
			else
				mp_FileLen = ((FLen / 4) * 3);
			mp_pStream->f_SetPosition(0);
		}
		else
		{
			DMibErrorFile("You must open the file either with read or write access not both at the same time");
		}
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Base64<t_CStreamType>::fp_WriteDirty()
	{
		mp_pStream->f_SetPosition((mp_CurrentLoaded/3)*4);
		uint8 Temp[EChunkSizeBase64];

		// 111111110000000011111111
		// 111111000000111111000000
		Temp[0] = g_Base64EncodingTable[mp_DecryptedData[0]>>2];
		Temp[1] = g_Base64EncodingTable[((mp_DecryptedData[0]<<4) | (mp_DecryptedData[1]>>4)) & 0x3f];
		Temp[2] = g_Base64EncodingTable[((mp_DecryptedData[1]<<2) | (mp_DecryptedData[2]>>6)) & 0x3f];
		Temp[3] = g_Base64EncodingTable[mp_DecryptedData[2] & 0x3f];

		if ((mp_FileLen - mp_CurrentLoaded) <= 2)
			Temp[3] = g_Base64EncodingTable[64];
		if ((mp_FileLen - mp_CurrentLoaded) <= 1)
			Temp[2] = g_Base64EncodingTable[64];

		mp_pStream->f_FeedBytes(Temp, EChunkSizeBase64);
		mp_bCurrentDirty = false;
	}

	template <typename t_CStreamType>
	mint TCBinaryStream_Base64<t_CStreamType>::fp_PrepareBlock(NStream::CFilePos _Pos, bool _bWrite)
	{
		if (mp_CurrentLoaded >= 0 && _Pos >=  mp_CurrentLoaded && _Pos < mp_CurrentLoaded + EChunkSizeData)
		{
			return _Pos - mp_CurrentLoaded;
		}

		if (mp_bCurrentDirty)
		{
			fp_WriteDirty();
		}

		mp_CurrentLoaded = (_Pos / 3)*3;
		NStream::CFilePos BlockPos = (_Pos / 3) * 4;

		if ((BlockPos+4) > mp_pStream->f_GetLength())
		{
			if (_bWrite)
				NMemory::fg_SecureMemClear(mp_DecryptedData);
			else
				DMibErrorFile("Read past end of file");
		}
		else
		{
			mp_pStream->f_SetPosition(BlockPos);
			uint8 Temp[EChunkSizeBase64];
			mp_pStream->f_ConsumeBytes(Temp, EChunkSizeBase64);
			int Table0 = g_Base64EncodingTableReverse[Temp[0]];
			int Table1 = g_Base64EncodingTableReverse[Temp[1]];
			int Table2 = g_Base64EncodingTableReverse[Temp[2]];
			int Table3 = g_Base64EncodingTableReverse[Temp[3]];
			if (Table0 < 0 || Table1 < 0 || Table2 < 0 || Table3 < 0)
				DMibErrorFile("Invalid Base64 character");

			mp_DecryptedData[0] = Table0 << 2 | Table1 >> 4;
			if (Table2 != 64)
			{
				mp_DecryptedData[1] = (Table1 & 0xf) << 4 | (Table2 >> 2);
				if (Table3 != 64)
				{
					mp_DecryptedData[2] = (Table2 & 0x3) << 6 | Table3;
				}
			}
		}

		return _Pos - mp_CurrentLoaded;
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Base64<t_CStreamType>::f_FeedBytes(const void *_pMem, mint _nBytes)
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
			if (mp_FilePos > mp_FileLen)
				mp_FileLen = mp_FilePos;
		}
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Base64<t_CStreamType>::f_ConsumeBytes(void *_pMem, mint _nBytes)
	{
		if (!(mp_OpenFlags & NFile::EFileOpen_Read))
			DMibErrorFile("File was not opened for read.");

		uint8 *pMem = (uint8 *)_pMem;
		while (_nBytes)
		{
			mint Pos = fp_PrepareBlock(mp_FilePos, false);
			mint ThisTime = fg_Min(_nBytes, (mint)EChunkSizeData - Pos);
			NMemory::fg_MemCopy(pMem, mp_DecryptedData + Pos, ThisTime);

			mp_FilePos += ThisTime;
			pMem += ThisTime;
			_nBytes -= ThisTime;
		}
	}

	template <typename t_CStreamType>
	bool TCBinaryStream_Base64<t_CStreamType>::f_IsValid() const
	{
		return mp_pStream->f_IsValid();
	}

	template <typename t_CStreamType>
	bool TCBinaryStream_Base64<t_CStreamType>::f_IsAtEndOfStream() const
	{
		return mp_pStream->f_IsAtEndOfStream();
	}

	template <typename t_CStreamType>
	NStream::CFilePos TCBinaryStream_Base64<t_CStreamType>::f_GetPosition() const
	{
		return mp_FilePos;
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Base64<t_CStreamType>::f_SetPosition(NStream::CFilePos _Pos)
	{
		mp_FilePos = _Pos;
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Base64<t_CStreamType>::f_SetPositionFromEnd(NStream::CFilePos _Pos)
	{
		mp_FilePos = (mp_pStream->f_GetLength()/4)*3 - _Pos;
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Base64<t_CStreamType>::f_AddPosition(NStream::CFilePos _Pos)
	{
		mp_FilePos += _Pos;
	}

	template <typename t_CStreamType>
	bool TCBinaryStream_Base64<t_CStreamType>::f_IsValidReadPosition(NStream::CFilePos _Pos) const
	{
		return mp_pStream->f_IsValidReadPosition(_Pos);
	}

	template <typename t_CStreamType>
	void TCBinaryStream_Base64<t_CStreamType>::f_Flush(bool _bLocalCacheOnly)
	{
		return mp_pStream->f_Flush(_bLocalCacheOnly);
	}
	template <typename t_CStreamType>
	void TCBinaryStream_Base64<t_CStreamType>::f_SetCacheSize(mint _CacheSize)
	{
		return mp_pStream->f_SetCacheSize(_CacheSize);
	}


	template <typename t_CStreamType>
	NStream::CFilePos TCBinaryStream_Base64<t_CStreamType>::f_GetLength() const
	{
		if (mp_OpenFlags == NFile::EFileOpen_Write)
			return fg_Max((mp_pStream->f_GetLength()/4)*3, fg_Max(mp_CurrentLoaded, mp_FilePos));
		else
			return mp_FileLen;
	}

	template <typename t_CStreamType>
	mint TCBinaryStream_Base64<t_CStreamType>::f_ContainerLengthLimit() const
	{
		return NStream::fg_CapLengthLimit(f_GetLength() - f_GetPosition());
	}
}
