#include "TraditionalInjection.h"

HANDLE RtlCreateUserThread(
	HANDLE hProcess,
	LPVOID lpBaseAddress,
	LPVOID lpSpace
	)
{
	//The prototype of RtlCreateUserThread from undocumented.ntinternals.com	
	typedef DWORD(WINAPI * functypeRtlCreateUserThread)(
		HANDLE 					ProcessHandle,
		PSECURITY_DESCRIPTOR 	SecurityDescriptor,
		BOOL 					CreateSuspended,
		ULONG					StackZeroBits,
		PULONG					StackReserved,
		PULONG					StackCommit,
		LPVOID					StartAddress,
		LPVOID					StartParameter,
		HANDLE 					ThreadHandle,
		LPVOID					ClientID

		);

	//Get handle for ntdll which contains RtlCreateUserThread
	HANDLE hRemoteThread = NULL;
	HMODULE hNtDllModule = GetModuleHandleA("ntdll.dll");

	if (hNtDllModule == NULL)
	{
		return NULL;
	}

	functypeRtlCreateUserThread funcRtlCreateUserThread = (functypeRtlCreateUserThread)GetProcAddress(hNtDllModule, "RtlCreateUserThread");

	if (!funcRtlCreateUserThread)
	{
		return NULL;
	}

	funcRtlCreateUserThread(hProcess, NULL, 0, 0, 0, 0, lpBaseAddress, lpSpace, &hRemoteThread, NULL);
	DWORD lastError = GetLastError();
	return hRemoteThread;
}

HANDLE NtCreateThreadEx(
	HANDLE hProcess,
	LPVOID lpBaseAddress,
	LPVOID lpSpace
	)
{
	//The prototype of NtCreateThreadEx from undocumented.ntinternals.com
	typedef DWORD(WINAPI * functypeNtCreateThreadEx)(
		PHANDLE                 ThreadHandle,
		ACCESS_MASK             DesiredAccess,
		LPVOID                  ObjectAttributes,
		HANDLE                  ProcessHandle,
		LPTHREAD_START_ROUTINE  lpStartAddress,
		LPVOID                  lpParameter,
		BOOL                    CreateSuspended,
		DWORD                   dwStackSize,
		DWORD                   Unknown1,
		DWORD                   Unknown2,
		LPVOID                  Unknown3
		);

	HANDLE                      hRemoteThread = NULL;
	HMODULE                     hNtDllModule = NULL;
	functypeNtCreateThreadEx    funcNtCreateThreadEx = NULL;


	//Get handle for ntdll which contains NtCreateThreadEx
	hNtDllModule = GetModuleHandleA("ntdll.dll");
	if (hNtDllModule == NULL)
	{
		return NULL;
	}

	funcNtCreateThreadEx = (functypeNtCreateThreadEx)GetProcAddress(hNtDllModule, "NtCreateThreadEx");
	if (!funcNtCreateThreadEx)
	{
		return NULL;
	}

	funcNtCreateThreadEx(&hRemoteThread, GENERIC_ALL, NULL, hProcess, (LPTHREAD_START_ROUTINE)lpBaseAddress, lpSpace, FALSE, NULL, NULL, NULL, NULL);

	return hRemoteThread;
}