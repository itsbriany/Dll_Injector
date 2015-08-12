#include "MessageBox.h"
#include <Windows.h>

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpReserved)   // reserved
{
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		MessageBox(nullptr, L"DLLMain!", L"Simple", 0);
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

//extern "C" MESSAGEBOX_API void hello()
MESSAGEBOX_API void hello()
{
	// Call this export to use DLL
	MessageBox(nullptr, L"Hello!", L"Simple", 0);
}


