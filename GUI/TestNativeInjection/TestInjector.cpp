#include "stdafx.h"
#include "CppUnitTest.h"
#include <windows.h>
#include <TlHelp32.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestNativeInjection
{		
	TEST_CLASS(DllInjectionUnitTest)
	{
	public:
		
		TEST_METHOD(TestDllInjection)
		{
		
			PROCESSENTRY32 entry;
			entry.dwSize = sizeof(PROCESSENTRY32);
			const HANDLE SNAPSHOT = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
			const std::wstring WC_ENTRY_NAME(L"notepad.exe");
			const std::string DLL("MessageBox.dll");
			DWORD procId;
			
			Assert::IsTrue(findProcessByName(SNAPSHOT, entry, WC_ENTRY_NAME, procId));
			NativeInjector ntInjector(procId, DLL.c_str());
			Assert::IsTrue(ntInjector.inject());
			Assert::IsTrue(ntInjector.getBytesInjected() > 0);
		}

		/**
			Finds the first occurrence of a process by name and fetches its PID

			@param snapshot a handle to the snapshot of the processes
			@param entry the process that we are interested in
			@param WC_ENTRY_NAME the name of the process that we are interested in
			@param procId the id of the process we are interested in
			@return true if an occurrence of the process name was found
		*/
		
		bool findProcessByName(HANDLE snapshot, PROCESSENTRY32 entry,
			const std::wstring WC_ENTRY_NAME, DWORD& procId)
		{
			bool foundEntries = false;
			if (Process32First(snapshot, &entry))
			{
				while (Process32Next(snapshot, &entry))
				{
					if (_wcsicmp(entry.szExeFile, WC_ENTRY_NAME.c_str()) == 0)
					{
						HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 
							FALSE, entry.th32ProcessID);
						procId = entry.th32ProcessID;
						std::wstring message = L"Found instance of " + WC_ENTRY_NAME +
							L" (" + std::to_wstring(procId) + L")";
						Logger::WriteMessage(message.c_str());
						CloseHandle(hProcess);
						foundEntries = true;
						break;
					}
				}
			}
			CloseHandle(snapshot);
			return foundEntries;
		}

	};
}