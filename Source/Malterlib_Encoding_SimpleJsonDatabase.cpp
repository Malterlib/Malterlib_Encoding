// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Encoding_SimpleJsonDatabase.h"
#include <Mib/Concurrency/ConcurrencyManager>
#include <Mib/Concurrency/LogError>
#include <Mib/Cryptography/RandomID>

namespace NMib::NEncoding
{
	namespace
	{
		constexpr EJsonDialectFlag gc_JsonDialectFlags = EJsonDialectFlag_AllowUndefined | EJsonDialectFlag_AllowInvalidFloat;

		bool fg_IsYamlFile(NStr::CStr const &_FileName)
		{
			return _FileName.f_EndsWith(".yaml") || _FileName.f_EndsWith(".yml");
		}
	}

	CSimpleJsonDatabase::CSimpleJsonDatabase(NStr::CStr const &_FileName)
		: mp_FileName(_FileName)
	{
	}

	CSimpleJsonDatabase::~CSimpleJsonDatabase()
	{
		*mp_pWasDeleted = true;
	}

	NConcurrency::TCUnsafeFuture<void> CSimpleJsonDatabase::f_Destroy() &&
	{
		auto WriteSequencer = fg_Move(mp_WriteSequencer);

		co_await fg_Move(WriteSequencer).f_Destroy().f_Wrap() > NConcurrency::fg_LogError("SimpleJsonDatabase", "Failed to destroy sequencer");

		co_return {};
	}

	NStr::CStr const &CSimpleJsonDatabase::f_GetFileName() const
	{
		return mp_FileName;
	}

	NConcurrency::TCUnsafeFuture<void> CSimpleJsonDatabase::f_Load()
	{
		auto pWasDeleted = mp_pWasDeleted;
		auto BlockingActorCheckout = NConcurrency::fg_BlockingActor();
		auto Data = co_await
			(
				NConcurrency::g_Dispatch(BlockingActorCheckout) / [FileName = mp_FileName]() -> CEJsonSortedYaml
				{
					if (!NFile::CFile::fs_FileExists(FileName))
						return CEJsonSortedYaml();

					auto FileData = NFile::CFile::fs_ReadStringFromFile(FileName, true);
					if (fg_IsYamlFile(FileName))
						return CEJsonSortedYaml::fs_FromStringYaml(FileData, FileName, gc_JsonDialectFlags);

					return CEJsonSortedYaml::fs_FromCompatible(CEJsonSortedWithComments::fs_FromStringJsonC(FileData, FileName, gc_JsonDialectFlags));
				}
			)
		;

		if (*pWasDeleted)
			co_return {};

		m_Data = fg_Move(Data);

		co_return {};
	}

	NConcurrency::TCUnsafeFuture<void> CSimpleJsonDatabase::f_Save()
	{
		using namespace NFile;
		using namespace NStr;

		auto SequenceSubscription = co_await mp_WriteSequencer.f_Sequence();

		auto BlockingActorCheckout = NConcurrency::fg_BlockingActor();
		co_await
			(
				NConcurrency::g_Dispatch(BlockingActorCheckout) / [FileName = mp_FileName, Data = m_Data]
				{
					CFile::fs_CreateDirectory(CFile::fs_GetPath(FileName));
					EFileAttrib FileAttributes = EFileAttrib_UnixAttributesValid | EFileAttrib_UserRead | EFileAttrib_UserWrite;
					CStr TempFileName = "{}.{}"_f << FileName << NCryptography::fg_FastRandomID();

					CStr FileData;
					if (fg_IsYamlFile(FileName))
						FileData = Data.f_ToStringYaml("  ", gc_JsonDialectFlags);
					else
						FileData = CEJsonSortedWithComments::fs_FromCompatible(Data).f_ToStringJsonC("\t", gc_JsonDialectFlags);

					CFile::fs_WriteStringToFile(TempFileName, FileData, true, FileAttributes);
					CFile::fs_AtomicReplaceFile(TempFileName, FileName);
				}
			)
		;

		co_return {};
	}
}
