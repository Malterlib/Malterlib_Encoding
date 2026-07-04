// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Encoding/SimpleJsonDatabase>
#include <Mib/Encoding/Yaml>
#include <Mib/Concurrency/ConcurrencyManager>
#include <Mib/File/File>
#include <Mib/Test/Exception>

namespace
{
	using namespace NMib;
	using namespace NMib::NConcurrency;
	using namespace NMib::NEncoding;

	struct CSimpleJsonDatabase_Tests : public NTest::CTest
	{
		void f_DoTests()
		{
			DMibTestSuite("JsonC") -> TCFuture<void>
			{
				NStr::CStr FilePath = NFile::CFile::fs_GetProgramDirectory() + "/TestSimpleJsonDatabase.json";
				fg_TestAddCleanupPath(FilePath);

				NFile::CFile::fs_WriteStringToFile
					(
						FilePath
						, "// header\n"
						"{\n"
						"\t// keep me\n"
						"\t\"Alpha\": 1, // inline\n"
						"\t\"Beta\": 2\n"
						"}\n"
					)
				;

				CSimpleJsonDatabase Database(FilePath);
				co_await Database.f_Load();

				DMibExpect(Database.m_Data["Alpha"].f_Integer(), ==, 1);
				DMibExpect(Database.m_Data["Beta"].f_Integer(), ==, 2);
				DMibExpect(Database.m_Data.f_Yaml().f_LeadingComment(), ==, "# header\n");
				DMibExpect(Database.m_Data["Alpha"].f_Yaml().f_LineComment(), ==, " # inline");

				Database.m_Data["Beta"] = 3;
				Database.m_Data["Gamma"] = true;
				co_await Database.f_Save();

				auto SavedText = NFile::CFile::fs_ReadStringFromFile(FilePath, true);
				DMibExpect(SavedText.f_Find("// header"), >=, 0);
				DMibExpect(SavedText.f_Find("// keep me"), >=, 0);
				DMibExpect(SavedText.f_Find("// inline"), >=, 0);
				DMibExpect(SavedText.f_Find("\"Beta\": 3"), >=, 0);
				DMibExpect(SavedText.f_Find("\"Gamma\": true"), >=, 0);

				CSimpleJsonDatabase Reloaded(FilePath);
				co_await Reloaded.f_Load();
				DMibExpect(Reloaded.m_Data["Beta"].f_Integer(), ==, 3);
				DMibExpect(Reloaded.m_Data["Gamma"].f_Boolean(), ==, true);
				DMibExpect(Reloaded.m_Data["Alpha"].f_Yaml().f_LineComment(), ==, " # inline");

				co_await fg_Move(Reloaded).f_Destroy();
				co_await fg_Move(Database).f_Destroy();

				co_return {};
			};

			DMibTestSuite("Yaml") -> TCFuture<void>
			{
				NStr::CStr FilePath = NFile::CFile::fs_GetProgramDirectory() + "/TestSimpleJsonDatabase.yaml";
				fg_TestAddCleanupPath(FilePath);

				NFile::CFile::fs_WriteStringToFile
					(
						FilePath
						, "# header\n"
						"Alpha: 1 # inline\n"
						"Beta: 2\n"
					)
				;

				CSimpleJsonDatabase Database(FilePath);
				co_await Database.f_Load();

				DMibExpect(Database.m_Data["Alpha"].f_Integer(), ==, 1);
				DMibExpect(Database.m_Data["Beta"].f_Integer(), ==, 2);
				DMibExpect(Database.m_Data["Alpha"].f_Yaml().f_LineComment(), ==, " # inline");

				Database.m_Data["Beta"] = 3;
				Database.m_Data["Gamma"] = true;
				co_await Database.f_Save();

				auto SavedText = NFile::CFile::fs_ReadStringFromFile(FilePath, true);
				DMibExpect(SavedText.f_Find("# header"), >=, 0);
				DMibExpect(SavedText.f_Find("Alpha: 1 # inline"), >=, 0);
				DMibExpect(SavedText.f_Find("Beta: 3"), >=, 0);
				DMibExpect(SavedText.f_Find("Gamma: true"), >=, 0);

				CSimpleJsonDatabase Reloaded(FilePath);
				co_await Reloaded.f_Load();
				DMibExpect(Reloaded.m_Data["Beta"].f_Integer(), ==, 3);
				DMibExpect(Reloaded.m_Data["Gamma"].f_Boolean(), ==, true);

				co_await fg_Move(Reloaded).f_Destroy();
				co_await fg_Move(Database).f_Destroy();

				co_return {};
			};
		}
	};

	DMibTestRegister(CSimpleJsonDatabase_Tests, Malterlib::Encoding);
}
