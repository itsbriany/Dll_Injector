#include "NativeInjector.h"
#include "TraditionalInjection.h"


NativeInjector::NativeInjector(DWORD processId, LPCSTR dll) :
	_processId(processId),
	_fullDllPath(dll),
	_dwLoadLibraryBaseAddr(0)
{
}

//::----------------------------------------------------------------------------------------
bool NativeInjector::elevateTokenPrivileges()
{
	HANDLE hToken = nullptr;
	TOKEN_PRIVILEGES priv = { 0 };

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		priv.PrivilegeCount = 1;
		priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		if (LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &priv.Privileges[0].Luid))
			AdjustTokenPrivileges(hToken, FALSE, &priv, 0, nullptr, nullptr);

		CloseHandle(hToken);
		return true;
	}
	return false;
}

//::--------------------------------------------------------------------------------------------------------
bool NativeInjector::releaseInjectedDll(HANDLE hProc)
{
	
	
	if (!_dwLoadLibraryBaseAddr) return false;

	HMODULE hKernel32 = GetModuleHandle(TEXT("kernel32.dll"));
	HANDLE hThread;

	hThread = CreateRemoteThread(hProc,
	                             nullptr,
	                             0,
	                             reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(hKernel32, "FreeLibrary")),
	                             reinterpret_cast<void*>(_dwLoadLibraryBaseAddr),
	                             0,
	                             nullptr
	);
	if (!hThread) return false;

	// Wait for the thread to finish
	WaitForSingleObject(hThread, INFINITE);


	// Close the handle on the thread
	if (!CloseHandle(hThread)) return false;
	
	return true;
}

//::----------------------------------------------------------------------------------------
bool NativeInjector::traditionalInject(BOOL freeDll)
{
	// Elevate permissions
	if(!elevateTokenPrivileges()) return false;

	// Open the target process
	HANDLE hProc = OpenProcess(PROCESS_CREATE_THREAD |
		PROCESS_QUERY_INFORMATION |
		PROCESS_VM_OPERATION |
		PROCESS_VM_READ |
		PROCESS_VM_WRITE,
		FALSE,
		_processId);

	if (!_fullDllPath) return false;

	// Find the absolute address of LoadLibraryA in kernel32.dll
	HMODULE hKernel32 = GetModuleHandle(TEXT("kernel32.dll"));
	FARPROC loadLibAddr = GetProcAddress(hKernel32, "LoadLibraryA");

	if (!loadLibAddr) return false;

	SIZE_T lpNumberOfBytesWritten = 0;

	// Allocate the memory in the victim process
	LPVOID lpBaseAddr = VirtualAllocEx(hProc,
		nullptr,
		strlen(_fullDllPath),
		MEM_RESERVE | MEM_COMMIT,
		PAGE_EXECUTE_READWRITE);

	if (!lpBaseAddr) return false;

	// Write the path to the dll we are injecting into the victim process
	if (!WriteProcessMemory(hProc,
		lpBaseAddr,
		_fullDllPath,
		strlen(_fullDllPath),
		&lpNumberOfBytesWritten
		)) return false;

	// Execute the remote thread from the target process
	HANDLE hThread;
	hThread = RtlCreateUserThread(hProc, loadLibAddr, lpBaseAddr);

	if (hThread == nullptr) return false;

	DWORD threadId = GetThreadId(hThread);
	DWORD processId = GetProcessIdOfThread(hThread);

	

	// Wait for the thread to finish before proceeding
	WaitForSingleObject(hThread, INFINITE);

	// Save the address of where the dll is loaded
	GetExitCodeThread(hThread, &_dwLoadLibraryBaseAddr);

	// Clean up
	if (!CloseHandle(hThread)) return false;

	// Release the memory we previously wrote to
	DWORD dwMemReleased = VirtualFreeEx(hProc, lpBaseAddr, 0, MEM_RELEASE);
	if (!dwMemReleased) return false;

	// Unload the dll that was previously loaded
	if (freeDll)
	{
		if (!releaseInjectedDll(hProc)) return false;
	}


	// Release the handle on the victim process
	if(!CloseHandle(hProc)) return false;

	return true;
}

//::----------------------------------------------------------------------------------------
bool NativeInjector::callRemoteExport(BOOL freeDll, LPCSTR lpExportName, LPVOID lpArgs)
{

	// Elevate permissions
	if (!elevateTokenPrivileges()) return false;
	
	// Open the target process
	HANDLE hProc = OpenProcess(PROCESS_CREATE_THREAD |
		PROCESS_QUERY_INFORMATION |
		PROCESS_VM_OPERATION |
		PROCESS_VM_READ |
		PROCESS_VM_WRITE,
		FALSE,
		_processId);

	// Load payload in our own virtual address space
	HMODULE hLoaded = LoadLibraryA(_fullDllPath);

	if (!hLoaded) return false;
	
	// Get the address of the export in our address space
	void* lpExport = GetProcAddress(hLoaded, lpExportName);
	DWORD dwOffset = static_cast<char*>(lpExport) - reinterpret_cast<char*>(hLoaded);
	FreeLibrary(hLoaded);

	// Use the relative offset to calculate the location of the export in the remote process
	DWORD dwExportAddress = static_cast<DWORD>(_dwLoadLibraryBaseAddr) + dwOffset;
	
	// Write the arguments provided to the victim's memory
	LPVOID lpArgsAddress = nullptr;
	SIZE_T lpBytesWritten;
	if (lpArgs)
	{
		lpArgsAddress = VirtualAllocEx(hProc, 
			nullptr,
			sizeof(lpArgs),
			MEM_RESERVE | MEM_COMMIT,
			PAGE_READWRITE);
		
		if (!lpArgsAddress) return false;

		WriteProcessMemory(hProc,
			lpArgsAddress,
			lpArgs,
			sizeof(lpArgs),
			&lpBytesWritten
			);

		if (!lpBytesWritten) return false;

		// TODO still need to free the memory allocated for lpArgs
	}
	
	// Call the export in the memory space of the victim process
	HANDLE hThread = RtlCreateUserThread(hProc,
		reinterpret_cast<LPVOID>(dwExportAddress),
		lpArgsAddress);

	if (!hThread) return false;

	// Free the dll
	if (freeDll)
	{
		// Wait for the thread to finish before proceeding
		WaitForSingleObject(hThread, INFINITE);
		
		// Clean up the thread
		if (!CloseHandle(hThread)) return false;

		releaseInjectedDll(hProc);
	}

	// Close the handle to the victim process
	if (!CloseHandle(hProc)) return false;

	return true;
}

//::----------------------------------------------------------------------------------------
extern "C" NATIVE_INJECTOR_DLL_API bool traditionalInject(BOOL unloadLibrary, DWORD processId, LPCSTR lpFullPathDll)
{
	NativeInjector injector(processId, lpFullPathDll);
	return injector.traditionalInject(true);
}
