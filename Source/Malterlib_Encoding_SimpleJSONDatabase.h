// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Encoding/EJSON>
#include <Mib/Concurrency/ConcurrencyDefines>

namespace NMib::NEncoding
{
	struct CSimpleJSONDatabase
	{
	public:
		CSimpleJSONDatabase(NStr::CStr const &_FileName);

		NConcurrency::TCDispatchedActorCall<void> f_Load();
		NConcurrency::TCDispatchedActorCall<void> f_Save();

		NStr::CStr const &f_GetFileName() const;

		CEJSON m_Data;

	private:
		NConcurrency::TCActor<NConcurrency::CSeparateThreadActor> mp_FileActor;
		NStr::CStr mp_FileName;
	};
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NEncoding;
#endif
