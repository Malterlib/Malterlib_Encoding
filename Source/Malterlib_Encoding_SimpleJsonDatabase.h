// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Encoding/EJson>
#include <Mib/Concurrency/ConcurrencyDefines>
#include <Mib/Concurrency/ActorSequencerActor>

namespace NMib::NEncoding
{
	struct CSimpleJsonDatabase
	{
	public:
		CSimpleJsonDatabase(NStr::CStr const &_FileName);
		~CSimpleJsonDatabase();

		NConcurrency::TCUnsafeFuture<void> f_Load();
		NConcurrency::TCUnsafeFuture<void> f_Save();

		NStr::CStr const &f_GetFileName() const;

		CEJsonSorted m_Data;

		NConcurrency::TCUnsafeFuture<void> f_Destroy() &&;

	private:
		NStr::CStr mp_FileName;
		NStorage::TCSharedPointer<bool> mp_pWasDeleted = fg_Construct(false);
		NConcurrency::CSequencer mp_WriteSequencer{"JsonDatabaseSequencer"};
	};
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
