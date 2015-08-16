#include "MessageBox.h"
#include <Windows.h>
#include <string>

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

extern "C" MESSAGEBOX_API void hello()
{
	MessageBox(nullptr, L"Hello!", L"Simple", 0);
}

extern "C" MESSAGEBOX_API BOOL helloArg(DWORD dwNumber, LPSTR lpMessage)
{
	std::string message(lpMessage);
	CHAR *numberBuffer = static_cast<char*>(malloc(300));
	_itoa_s(dwNumber, numberBuffer, 300, 10);
	message.append(numberBuffer);
	//strcat_s(lpMessage, strlen(lpMessage), numberBuffer);
	MessageBoxA(nullptr, message.c_str(), "HelloArg", 0);
	return true;
}


