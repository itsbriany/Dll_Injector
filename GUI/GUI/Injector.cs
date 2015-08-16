using System.Runtime.InteropServices;

namespace GUI
{
    static class Injector
    {
        // Make sure the the build configuration matches!
        private const string NativeDependency = "bin\\NativeInjector.dll";

        [DllImport(NativeDependency, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool traditionalInject(bool unloadLibrary, uint dwProcessId, string fullDllPath);

        /// <summary>
        /// Injects a DLL into a target process
        /// </summary>
        /// <param name="unloadLibrary">Determines if the injected dll should be unloaded as soon as DllMain terminates</param>
        /// <param name="processId">The process ID of the victim</param>
        /// <param name="fullDllPath">The full path to the dll being loaded into the victim process</param>
        /// <returns>True on success</returns>
        public static bool InjectDll(bool unloadLibrary, uint processId, string fullDllPath)
        {
            return traditionalInject(unloadLibrary, processId, fullDllPath);
        }
    }
}
