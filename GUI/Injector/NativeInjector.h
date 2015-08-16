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
	// NOTE: This only takes zero or one argument! The problem is that every dll has a different interface
	// taking a different number of parameters. Because we need to create a new thread, threads
	// only provide a LPVOID argument. Also, this would not be very convenient to interface with
	// the GUI.
	// Parameter: BOOL freeDll do we wish to free the dll once the export finishes executing?
	// Parameter: LPCSTR lpExportName the name of the dll export from the injected dll
	// Parameter: LPVOID lpArgs args to the remote export
	// Returns:	True if the target export was called from the dll
	//************************************
	bool callRemoteExport(BOOL freeDll, LPCSTR lpExportName, LPVOID lpArgs);

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

	DWORD _processId;	               // The victim process
	LPCSTR _fullDllPath;               // The full path to the dll that will be injected
	DWORD _dwLoadLibraryBaseAddr;      // The base address of where LoadLibrary is located at in the victim process
};


//************************************
// Description: A decorator for calling the traditional dll injection
// Parameter: BOOL determines if the library should be unloaded as soon as the thread running
// DllMain terminates
// Parameter: DWORD processId the process ID of the victim process
// Parameter: LPCSTR lpFullPathDll the full path to the dll to be injected
// Returns:   True on success
//************************************
extern "C" NATIVE_INJECTOR_DLL_API bool traditionalInject(BOOL unloadLibrary, DWORD processId, LPCSTR lpFullPathDll);
