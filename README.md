# Dll Injector
---

### Goals
The goal of this project is to use various dll injection methods to inject a dll into an existing process's memory. This project also comes with a GUI, making it simple to select the dll you wish to inject and the target process.

---
### Injection Methods
- Traditional dll injection
    - VirtualAllocEx()
	> Allocate memory for the path to the dll we wish to inject. Make sure to flag the allocated pages as readable, executable, and writeable!
    
    - WriteProcessMemory()
	> Write the path to the dll to the allocated memory pointed to via the base address returned from VirtualAllocEx(). 
	
    - RtlCreateUserThread()
	> A wrapper for NtCreateThreadEx which creates a new thread to execute the executable memory that we just wrote.
	This is from an undocumented API from ntdll.dll and is more likely to work than CreateRemoteThread() due to Microsoft making continuous tweaks to their documented APIs.
	The magic happens when the thread calls LoadLibraryA() and we pass our path (in the victim process's memory) as an argument to make the victim process load DllMain().
    
    - NtCreateThreadEx()
	> The lowest API level for creating a thread.
	
	- VirtualFreeEx()
	> Free the allocated memory from the dll path we wrote
	
	- FreeLibrary()
	> Free the dll once the thread exits so that we can inject our dll again and make it call DllMain()

----
### Compatibility
This project was built with MSVC 2015. It is notable that the GUI was written in C# .NET. The rest of the project is written in C/C++ with Win32Api.

---
### Resources
- [Process Hacker](http://processhacker.sourceforge.net/)
- [Dll Injection Methods](http://www.codeproject.com/Articles/4610/Three-Ways-to-Inject-Your-Code-into-Another-Proces)
- [RtlCreateUserThread](https://warroom.securestate.com/index.php/dll-injection-part-2-createremotethread-and-more/)
- [Reflective Dll Injection](https://github.com/stephenfewer)

----
### Contact
If you have any questions, send an email to itsbriany@gmail.com

### License
----
Licensed under an Apache V2.0 license. For more details, see [LICENSE.txt](https://github.com/itsbriany/DLL_Injector/blob/master/LICENSE)

----
### TODO

- Support reflective dll injection and properly integrate it into the project
- Provide an interface to call exports from the dll being injected
- Provide instructions on building the project
