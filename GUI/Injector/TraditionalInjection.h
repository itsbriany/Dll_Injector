#pragma once
#include <windows.h>

// Code snippet for this technique borrowed from 
// https://warroom.securestate.com/index.php/dll-injection-part-2-createremotethread-and-more/

//************************************
// Description: Native call to creating a thread, acts as a wrapper for NtCreateThreadEx
// Parameter: HANDLE hProcess the handle to the process we are injecting our dll into
// Parameter: LPVOID lpBaseAddress a pointer to where the thread execution starts  
// Parameter: LPVOID lpSpace args for the function pointer of lpBaseAddress
// Returns:   A thread on success, NULL on failure
//************************************
HANDLE RtlCreateUserThread(HANDLE hProcess, LPVOID lpBaseAddress, LPVOID lpSpace);

//************************************
// Description: Native call to creating a thread
// Parameter: HANDLE hProcess the handle to the process we are injecting our dll into
// Parameter: LPVOID lpBaseAddress a pointer to where the thread execution starts 
// Parameter: LPVOID lpSpace args for the function pointer of lpBaseAddress
// Returns:   A thread on success, NULL on failure
//************************************
HANDLE NtCreateThreadEx(HANDLE hProcess, LPVOID lpBaseAddress, LPVOID lpSpace);