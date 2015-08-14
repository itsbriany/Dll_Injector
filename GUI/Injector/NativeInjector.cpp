#include "NativeInjector.h"
//#include "LoadLibraryR.h"
#include "TraditionalInjection.h"
#include <consoleapi.h>
#include <string>


NativeInjector::NativeInjector(DWORD processId, LPCSTR dll) :
	_stdOut(GetStdHandle(STD_OUTPUT_HANDLE)),
	_charsWritten(nullptr),
	_processId(processId),
	_dll(dll),
	_bytesInjected(0),
	_fullDllPath(dll),
	_hProcess(nullptr),
	_lpBuffer(nullptr),
	_hDll(nullptr)
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

//::----------------------------------------------------------------------------------------
bool NativeInjector::traditionalInject()
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
	HANDLE hThread = nullptr;
	hThread = RtlCreateUserThread(hProc, loadLibAddr, lpBaseAddr);

	if (hThread == nullptr) return false;

	DWORD threadId = GetThreadId(hThread);
	DWORD processId = GetProcessIdOfThread(hThread);

	

	// Wait for the thread to finish before proceeding
	WaitForSingleObject(hThread, INFINITE);

	// Save the address of where the dll is loaded
	DWORD dwLibModule;
	GetExitCodeThread(hThread, &dwLibModule);

	// Clean up
	if (!CloseHandle(hThread)) return false;

	// Release the memory we previously wrote to
	DWORD dwMemReleased = VirtualFreeEx(hProc, lpBaseAddr, 0, MEM_RELEASE);
	if (!dwMemReleased) return false;

	// Unload the dll that was previously loaded
	hThread = CreateRemoteThread(hProc,
		nullptr,
		0,
		reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(hKernel32, "FreeLibrary")),
		reinterpret_cast<void*>(dwLibModule),
		0,
		nullptr
	);
	if (!hThread) return false;

	// Wait for the thread to finish
	WaitForSingleObject(hThread, INFINITE);
	

	// Close the handle on the thread
	if (!CloseHandle(hThread)) return false;

	// Release the handle on the victim process
	if(!CloseHandle(hProc)) return false;

	return true;
}

//::----------------------------------------------------------------------------------------
bool NativeInjector::inject()
{
	OutputDebugStringA("Injecting...");
	if (injectDll() == false)
	{
		const char *FAILED_MESSAGE = "Failed to inject dll to process\n";
		WriteConsoleA(_stdOut, FAILED_MESSAGE, strlen(FAILED_MESSAGE), _charsWritten, nullptr);
		return false;
	}
	return true;
}

//::----------------------------------------------------------------------------------------
bool NativeInjector::injectDll()
{
	// Open the victim process
	_hProcess = OpenProcess(PROCESS_CREATE_THREAD | 
		PROCESS_QUERY_INFORMATION |
		PROCESS_VM_OPERATION | 
		PROCESS_VM_READ |
		PROCESS_VM_WRITE,
		FALSE,
		_processId);

	if (_hProcess == nullptr)
	{
		const char *ATTACHED_MESSAGE = "Error could not attach to process!\n";
		MessageBoxA(nullptr, ATTACHED_MESSAGE, "Error!", MB_OK + MB_ICONERROR);
		return false;
	}

	// Allocate memory for the DLL we are injecting
	if (writeMemory(_hProcess)) return true;

	return false;
}

//::----------------------------------------------------------------------------------------
bool NativeInjector::writeMemory(HANDLE hProcess)
{
	const DWORD BUFSIZE = 4096;
	char fullPath[BUFSIZE];
	char *fileExt[BUFSIZE];
	DWORD pathSize = GetFullPathNameA(_dll, BUFSIZE, fullPath, fileExt);
	std::string message("Path to DLL: ");
	_fullDllPath = fullPath;
	

	// Get the full path for the DLL
	if (pathSize == 0)
	{
		const char *NO_DLL_PATH_MESSAGE = "No dll specified!\n";
		MessageBoxA(nullptr, NO_DLL_PATH_MESSAGE, "Error!", MB_OK + MB_ICONERROR);
		return false;
	}

	// Get a handle on the dll file we are injecting
	HANDLE dllFile = CreateFileA(
		fullPath,
		GENERIC_READ,
		0,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
		);

	if (dllFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(nullptr, "Error cannot open dll!", "Error!", MB_OK + MB_ICONERROR);
		return false;
	}

	SIZE_T dllSize = GetFileSize(dllFile, nullptr); 

	// Allocate the virtual memory
	LPVOID lpDllBaseAddr = VirtualAllocEx(hProcess,
		nullptr,
		dllSize,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE);

	// Write to the virtual memory we just allocated
	_lpBuffer = HeapAlloc(GetProcessHeap(),
		HEAP_GENERATE_EXCEPTIONS|HEAP_ZERO_MEMORY,
		dllSize);
	DWORD bytesRead;

	if (ReadFile(dllFile, _lpBuffer, dllSize, &bytesRead, nullptr) == false)
	{
		MessageBoxA(nullptr, "Error cannot read dll!", "Error!", MB_OK + MB_ICONERROR);
		return false;
	}
	if (WriteProcessMemory(hProcess, lpDllBaseAddr, _lpBuffer, dllSize, &_bytesInjected) == false)
	{
	  MessageBoxA(nullptr, "Error cannot WriteProcessMemory!", "Error!", MB_OK + MB_ICONERROR);
	  return false;
	}
	
	// Run the function from the dll
	if (runDll()) return true;

	return false;
}

//::----------------------------------------------------------------------------------------
bool NativeInjector::runDll()
{
	// TODO Integrate reflective dll injection

	//HANDLE hToken = nullptr;
	//TOKEN_PRIVILEGES priv = { 0 };

	//// TODO the export should not be hardcoded!
	//DWORD dwReflectiveLoaderOffset = GetReflectiveLoaderOffset(_lpBuffer);

	//if (dwReflectiveLoaderOffset == 0)
	//{
	//	MessageBoxA(nullptr, "Error could not find the address of the loaded dll!",
	//		"Error!", MB_OK + MB_ICONERROR);
	//	return false;
	//}

	///*LPTHREAD_START_ROUTINE LPTHlpLoadExportAddress =
	//	reinterpret_cast<LPTHREAD_START_ROUTINE>
	//	(reinterpret_cast<ULONG_PTR>(_lpBuffer) + dwReflectiveLoaderOffset);*/

	//LPTHREAD_START_ROUTINE LPTHlpLoadExportAddress = reinterpret_cast<LPTHREAD_START_ROUTINE>(_lpBuffer);

	//char message[300] = {};
	//char result[30] = {};
	//strcat_s(message, sizeof message, "The address of the dll is ");
	//sprintf_s(result, "%x", LPTHlpLoadExportAddress);
	//strcat_s(message, sizeof message, result);
	//OutputDebugStringA(message);

	//// Launch a thread calling LoadLibraryA to get the proper offset to the function from
	//// our dll we wish to call
	//HANDLE remoteThread = CreateRemoteThread(_hProcess,
	//	nullptr,
	//	1024 * 1024,
	//	LPTHlpLoadExportAddress,
	//	nullptr, // TODO this is a pointer to where the arguments go
	//	0,
	//	nullptr
	//	);
	//if (remoteThread == nullptr)
	//{
	//	MessageBoxA(nullptr, "Error could not initialize the remote thread!",
	//		"Error!", MB_OK + MB_ICONERROR);
	//	return false;
	//}
	return true;
}

//::----------------------------------------------------------------------------------------
extern "C" NATIVE_INJECTOR_DLL_API bool traditionalInject(DWORD processId, LPCSTR lpFullPathDll)
{
	NativeInjector injector(processId, lpFullPathDll);
	return injector.traditionalInject();
}
