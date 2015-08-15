// 

#pragma once
#ifdef INJECTOR_EXPORTS
#define NATIVE_INJECTOR_DLL_API __declspec(dllexport)
#else
#define NATIVE_INJECTOR_DLL_API __declspec(dllimport)
#endif

#include <windows.h>

extern "C" class NATIVE_INJECTOR_DLL_API NativeInjector
{
public:

	 
	 //************************************
	 // Description: Use this to inject a dll into a victim process
	 // Parameter: DWORD processId the victim's process ID
	 // Parameter: LPCSTR dll the full path to the dll we are injecting
	 //************************************
	 NativeInjector(DWORD processId, LPCSTR dll);
	

	//************************************
	// Returns:	True if the dll was successfully injected into the target process
	//************************************
	bool traditionalInject(BOOL freeDll);

	//************************************
	// Parameter: BOOL freeDll do we wish to free the dll once the export finishes executing?
	// Parameter: LPCSTR lpExportName the name of the dll export from the injected dll
	// Parameter: LPVOID lpArgs args to the remote export
	// Returns:	True if the target export was called from the dll
	//************************************
	bool callRemoteExport(BOOL freeDll, LPCSTR lpExportName, LPVOID lpArgs);

	//************************************
	// Returns: true of the this native injector's dll was successfully 
	//	injected into a process
	//************************************
	bool inject();

	SIZE_T getBytesInjected() const { return _bytesInjected; }
	void setBytesInjected(SIZE_T val) { _bytesInjected = val; }

	
private:

	//************************************
	// Returns:   True if the current process's token privileges were elevated
	//************************************
	bool elevateTokenPrivileges();

	//************************************
	// Parameter: HANDLE hProc a handle to the process already injected with a dll
	// Returns:   true if the dll was successfully released from the process
	//************************************
	bool releaseInjectedDll(HANDLE hProc);

	//************************************
	// Returns:   true if we have successfully attached to the target process
	//************************************
	bool injectDll();

	//************************************
	// Parameter: HANDLE hProcess a handle to the process that is going to be injected
	// Returns:   true if we have successfully allocated and written memory within 
	//			  the target process
	//************************************
	bool writeMemory(HANDLE hProcess);

	//************************************
	// Returns:  true if the DLL was successfully executed
	//************************************
	bool runDll();

	HANDLE _stdOut;			           // A handle to stdout
	LPDWORD _charsWritten;	           // The number of chars written
	DWORD _processId;	               // The victim process
	LPCSTR _dll;			           // The dll that will be injected
	SIZE_T _bytesInjected;             // The amount of bytes injected into the target process
	LPCSTR _fullDllPath;               // The full path to the dll that will be injected
	HANDLE _hProcess;                  // A handle to the victim process
	LPVOID _lpBuffer;                  // A buffer allocated in the heap that will contain the offset to the
								       // address of the function called from the injected dll
	
	DWORD _dwLoadLibraryBaseAddr;      // The base address of where LoadLibrary is located at in the victim process
};


//************************************
// Description: A decorator for calling the traditional dll injection
// Parameter: DWORD processId the process ID of the victim process
// Parameter: LPCSTR lpFullPathDll the full path to the dll to be injected
// Returns:   True on success
//************************************
extern "C" NATIVE_INJECTOR_DLL_API bool traditionalInject(DWORD processId, LPCSTR lpFullPathDll);
