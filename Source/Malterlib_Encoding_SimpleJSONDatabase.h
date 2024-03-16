// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Encoding/EJSON>
#include <Mib/Concurrency/ConcurrencyDefines>
#include <Mib/Concurrency/ActorSequencerActor>

namespace NMib::NEncoding
{
	struct CSimpleJSONDatabase
	{
	public:
		CSimpleJSONDatabase(NStr::CStr const &_FileName);
		~CSimpleJSONDatabase();

		NConcurrency::TCFuture<void> f_Load();
		NConcurrency::TCFuture<void> f_Save();

		NStr::CStr const &f_GetFileName() const;

		CEJSONSorted m_Data;

	private:
		NStr::CStr mp_FileName;
		NStorage::TCSharedPointer<bool> mp_pWasDeleted = fg_Construct(false);
		NConcurrency::CSequencer mp_WriteSequencer{"JSONDatabaseSequencer"};
	};
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
