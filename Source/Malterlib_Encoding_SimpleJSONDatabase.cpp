// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_SimpleJSONDatabase.h"
#include <Mib/Concurrency/ConcurrencyManager>

namespace NMib::NEncoding
{
	namespace
	{
		constexpr EJSONDialectFlag gc_JsonDialectFlags = EJSONDialectFlag_AllowUndefined | EJSONDialectFlag_AllowInvalidFloat;
	}

	CSimpleJSONDatabase::CSimpleJSONDatabase(NStr::CStr const &_FileName)
		: mp_FileActor(NConcurrency::fg_ConstructActor<NConcurrency::CSeparateThreadActor>(fg_Construct("JSONDatabase")))
		, mp_FileName(_FileName)
	{
	}

	CSimpleJSONDatabase::~CSimpleJSONDatabase()
	{
		*mp_pWasDeleted = true;
	}

	NStr::CStr const &CSimpleJSONDatabase::f_GetFileName() const
	{
		return mp_FileName;
	}

	NConcurrency::TCFuture<void> CSimpleJSONDatabase::f_Load()
	{
		co_await NConcurrency::ECoroutineFlag_AllowReferences;
		auto pWasDeleted = mp_pWasDeleted;
		auto Data = co_await
			(
				NConcurrency::g_Dispatch(mp_FileActor) / [FileName = mp_FileName]() -> CEJSONSorted
				{
					if (!NFile::CFile::fs_FileExists(FileName))
						return CEJSONSorted();
					return CEJSONSorted::fs_FromString(NFile::CFile::fs_ReadStringFromFile(FileName), FileName, false, gc_JsonDialectFlags);
				}
			)
		;

		if (*pWasDeleted)
			co_return {};

		m_Data = fg_Move(Data);

		co_return {};
	}

	NConcurrency::TCFuture<void> CSimpleJSONDatabase::f_Save()
	{
		co_await NConcurrency::ECoroutineFlag_AllowReferences;
		using namespace NFile;

		co_await
			(
				NConcurrency::g_Dispatch(mp_FileActor) / [FileName = mp_FileName, Data = m_Data]
				{
					CFile::fs_CreateDirectory(CFile::fs_GetPath(FileName));
					EFileAttrib FileAttributes = EFileAttrib_UnixAttributesValid | EFileAttrib_UserRead | EFileAttrib_UserWrite;
					CFile::fs_WriteStringToFile(FileName, Data.f_ToString("\t", gc_JsonDialectFlags), true, FileAttributes);
				}
			)
		;

		co_return {};
	}
}
