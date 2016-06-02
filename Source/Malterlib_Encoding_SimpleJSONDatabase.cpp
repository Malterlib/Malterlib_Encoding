// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Encoding_SimpleJSONDatabase.h"
#include <Mib/Concurrency/ConcurrencyManager>

namespace NMib
{
	namespace NEncoding
	{
		CSimpleJSONDatabase::CSimpleJSONDatabase(NStr::CStr const &_FileName)
			: mp_FileActor(NConcurrency::fg_ConstructActor<NConcurrency::CSeparateThreadActor>(fg_Construct("JSONDatabase")))
			, mp_FileName(_FileName)
		{
		}
			
		NConcurrency::TCDispatchedActorCall<void> CSimpleJSONDatabase::f_Load()
		{
			return NConcurrency::fg_Dispatch
				(
					[this, FileName = mp_FileName, FileActor = mp_FileActor]
					{
						NConcurrency::TCContinuation<void> Continuation;
						fg_Dispatch
							(
								FileActor
								, [FileName]
								{
									if (!NFile::CFile::fs_FileExists(FileName))
										return CEJSON();
									return CEJSON::fs_FromString(NFile::CFile::fs_ReadStringFromFile(FileName), FileName);
								}
							)
							> Continuation / [this, Continuation](CEJSON &&_Data)
							{
								m_Data = fg_Move(_Data);
								Continuation.f_SetResult();
							}
						;
						return Continuation;
					}
				)
			;
		}
		
		NConcurrency::TCDispatchedActorCall<void> CSimpleJSONDatabase::f_Save()
		{
			using namespace NFile;
			return fg_Dispatch
				(
					mp_FileActor
					, [this, FileName = mp_FileName, Data = m_Data]
					{
						CFile::fs_CreateDirectory(CFile::fs_GetPath(FileName));
						EFileAttrib FileAttributes = EFileAttrib_UnixAttributesValid | EFileAttrib_UserRead | EFileAttrib_UserWrite;
						CFile::fs_WriteStringToFile(FileName, Data.f_ToString(), true, FileAttributes);
					}
				)
			;
		}
	}
}
