#pragma once
#ifdef MESSAGEBOX_EXPORTS
#define MESSAGEBOX_API __declspec(dllexport)
#else
#define MESSAGEBOX_API __declspec(dllimport)
#endif

# include <windows.h>

extern "C" MESSAGEBOX_API void hello();
extern "C" MESSAGEBOX_API BOOL helloArg(DWORD dwNumber, LPSTR lpMessage);