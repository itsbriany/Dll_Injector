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
			const std::wstring WC_ENTRY_NAME(L"putty.exe");
			const DWORD BUFSIZE = 4096;
			char dllFullPath[BUFSIZE];
			char *fileExt[BUFSIZE];
			DWORD pathSize = GetFullPathNameA("MessageBox.dll", BUFSIZE, dllFullPath, fileExt);
			
			// Find the process ID
			DWORD procId;
			Assert::IsTrue(findProcessByName(SNAPSHOT, entry, WC_ENTRY_NAME, procId));

			// Inject the process with traditional dll injection
			NativeInjector ntInjector(procId, dllFullPath);

			// Do not release the injected dll from the process
			Assert::IsTrue(ntInjector.traditionalInject(false));

			// Call an export from the dll and then free it
			Assert::IsTrue(ntInjector.callRemoteExport(true, "hello", nullptr));
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