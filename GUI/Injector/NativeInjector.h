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
	// Returns:  true if the DLL was successfully executed
	//************************************
	bool __cdecl runDll();

	HANDLE _stdOut;			// A handle to stdout
	LPDWORD _charsWritten;	// The number of chars written
	DWORD _processId;		// The victim process
	LPCSTR _dll;			// The dll that will be injected
	SIZE_T _bytesInjected;  // The amount of bytes injected into the target process
	LPCSTR _fullDllPath;    // The full path to the dll that will be injected
	HANDLE _hProcess;       // A handle to the victim process
	LPVOID _lpBuffer;       // A buffer allocated in the heap that will contain the offset to the
							// address of the function called from the injected dll
};

