#pragma once
#ifdef INJECTOR_EXPORTS
#define NATIVE_INJECTOR_DLL_API __declspec(dllexport)
#else
#define NATIVE_INJECTOR_DLL_API __declspec(dllimport)
#endif

#include <windows.h>

class NATIVE_INJECTOR_DLL_API NativeInjector
{
public:

	 NativeInjector(DWORD processId, LPCSTR dll);
	
	~NativeInjector();
	
	//************************************
	// Returns: true of the this native injector's dll was successfully 
	//	injected into a process
	//************************************
	bool inject();

	SIZE_T getBytesInjected() const { return _bytesInjected; }
	void setBytesInjected(SIZE_T val) { _bytesInjected = val; }

private:

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
	// Returns: true if The DLL path was copied into the process's memory and the
	// appropriate memory addresses were determine
	//************************************
	bool copyDllPath();

	//************************************
	// Returns:  true if the DLL was successfully executed
	//************************************
	bool runDll();


	HANDLE _stdOut;			// A handle to stdout
	LPDWORD _charsWritten;	// The number of chars written
	DWORD _processId;		// The victim process
	LPCSTR _dll;			// The DLL that will be injected
	SIZE_T _bytesInjected;  // The amount of bytes injected into the target process 
	
};

