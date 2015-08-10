#pragma once
#include <windows.h>

#ifdef NATIVE_INJECTOR_DLL_EXPORTS
#define NATIVE_INJECTOR_DLL_API __declspec(dllexport)
#else
#define NATIVE_INJECTOR_DLL_API __declspec(dllimport)
#endif

class NATIVE_INJECTOR_DLL_API NativeInjector
{
public:
	NativeInjector(DWORD processId);
	~NativeInjector();

	// Inject a dll into a process
	bool inject();

private:
	// Returns true if we have successfully attached to the target process
	bool attach();

	// Returns true if we have successfully allocated memory within the target process
	bool allocateMemory();

	// Returns true if The DLL path was copied into the process's memory and the
	// appropriate memory addresses were determined
	bool copyDllPath();

	// Returns true if the DLL was successfully executed
	bool runDll();


	HANDLE _std_out;			// A handle to stdout
	LPDWORD _chars_written;		// The number of chars written
	DWORD _process_id;			// The victim process
};

