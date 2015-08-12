#include "NativeInjector.h"
#include "LoadLibraryR.h"
#include <consoleapi.h>
#include <string>


NativeInjector::NativeInjector(DWORD processId, LPCSTR dll) :
	_stdOut(GetStdHandle(STD_OUTPUT_HANDLE)),
	_charsWritten(nullptr),
	_processId(processId),
	_dll(dll),
	_bytesInjected(0),
	_fullDllPath(nullptr),
	_hProcess(nullptr),
	_lpBuffer(nullptr)
{
	// Allocate memory for a new console
	AllocConsole();
}


NativeInjector::~NativeInjector()
{
}

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
		WriteConsoleA(_stdOut, ATTACHED_MESSAGE, strlen(ATTACHED_MESSAGE), _charsWritten, nullptr);
		MessageBoxA(nullptr, ATTACHED_MESSAGE, "Error!", MB_OK + MB_ICONERROR);
		return false;
	}

	// Allocate memory for the DLL we are injecting
	if (writeMemory(_hProcess)) return true;

	return false;
}

bool NativeInjector::writeMemory(HANDLE hProcess)
{
	//LPSTR fullPath = static_cast<LPSTR>(LocalAlloc(LPTR, MAX_PATH * sizeof(LPSTR)));
	const DWORD BUFSIZE = 4096;
	char fullPath[BUFSIZE];
	char *fileExt[BUFSIZE];
	DWORD pathSize = GetFullPathNameA(_dll, BUFSIZE, fullPath, fileExt);
	std::string message("Path to DLL: ");
	_fullDllPath = fullPath;
	message.append(_fullDllPath);
	OutputDebugStringA(message.c_str());
	
	

	// Get the full path for the DLL
	if (pathSize == 0)
	{
		const char *NO_DLL_PATH_MESSAGE = "No dll specified!\n";
		WriteConsoleA(_stdOut, NO_DLL_PATH_MESSAGE, strlen(NO_DLL_PATH_MESSAGE),
			_charsWritten, nullptr);
		MessageBoxA(nullptr, "Error no dll specified!", "Error!", MB_OK + MB_ICONERROR);
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

	return true;
}

bool __cdecl NativeInjector::runDll()
{
	// Get the address for LoadLibraryA so that the injected process can load our dll
	/*FARPROC lpLoadLibraryAddress = GetProcAddress(LoadLibraryA("kernel32.dll"), "LoadLibraryA");
	if (lpLoadLibraryAddress == nullptr)
	{
		MessageBoxA(nullptr, "Error could not find address of LoadLibraryA in kernel32.dll",
			"Error!", MB_OK + MB_ICONERROR);
		return false;
	}*/

	DWORD lpLoadLibraryAddress = GetReflectiveLoaderOffset(_lpBuffer);

	if (lpLoadLibraryAddress == 0)
	{
		MessageBoxA(nullptr, "Error could not find the address of the loaded dll!",
			"Error!", MB_OK + MB_ICONERROR);
		return false;
	}

	// Launch a thread calling LoadLibraryA to get the proper offset to the function from
	// our dll we wish to call
	/*HANDLE remoteThread = CreateRemoteThread(_hProcess, 
		nullptr,
		0,
		);*/
	return true;
}

//void compileThis()
//{
//	LPVOID buffer = HeapAlloc(GetProcessHeap(),
//		HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY,
//		100);
//	DWORD lpLoadLibraryAddress = GetReflectiveLoaderOffset(buffer);
//
//	if (lpLoadLibraryAddress == 0)
//	{
//		MessageBoxA(nullptr, "Error could not find the address of the loaded dll!",
//			"Error!", MB_OK + MB_ICONERROR);
//	}
//}

extern "C" __declspec(dllexport) void inject(DWORD processId, LPCSTR dll)
{
	NativeInjector injector(processId, dll);
	injector.inject();
	Sleep(3000);
}
