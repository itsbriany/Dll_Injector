#pragma once
#ifdef MESSAGEBOX_EXPORTS
#define MESSAGEBOX_API __declspec(dllexport)
#else
#define MESSAGEBOX_API __declspec(dllimport)
#endif

MESSAGEBOX_API void hello();