#include "NativeInjector.h"
#include <consoleapi.h>


NativeInjector::NativeInjector(DWORD processId) : _std_out(GetStdHandle(STD_OUTPUT_HANDLE)),
												 _chars_written(nullptr),
												 _process_id(processId)
								   
{
	// Allocate memory for a new console
	AllocConsole();
}


NativeInjector::~NativeInjector()
{
}

bool NativeInjector::inject()
{
	if (attach())
	{
		const char *attached_message = "Attached!\n";
		WriteConsoleA(_std_out, attached_message, strlen(attached_message), _chars_written, NULL);
		return true;
	}
	const char *failed_message = "Failed to attach to process\n";
	WriteConsoleA(_std_out, failed_message, strlen(failed_message), _chars_written, NULL);
	return false;
}

bool NativeInjector::attach()
{
	// TODO get the process ID that we want to attach to
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | 
		PROCESS_QUERY_INFORMATION |
		PROCESS_VM_OPERATION | 
		PROCESS_VM_READ |
		PROCESS_VM_WRITE,
		FALSE,
		_process_id);
	if (hProcess) return true;
	return false;
}

bool NativeInjector::allocateMemory()
{
	//GetFullPathNameA()
	return false;
}

bool NativeInjector::copyDllPath()
{
	return false;
}

bool NativeInjector::runDll()
{
	return false;
}

extern "C" __declspec(dllexport) void inject(DWORD processId)
{
	NativeInjector injector(processId);
	injector.inject();
	Sleep(3000);
}
