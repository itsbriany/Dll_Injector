using System.Runtime.InteropServices;
using GUI.Properties;

namespace GUI
{
    static class Injector
    {
        // Make sure the the build configuration matches!
        private const string NativeDependency = "bin\\NativeInjector.dll";

        [DllImport(NativeDependency,
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool traditionalInject(uint dwProcessId, string fullDllPath);

        /// <summary>
        /// Injects a DLL into a target process
        /// </summary>
        /// <param name="processId">The process ID of the victim</param>
        /// <param name="fullDllPath">The full path to the dll being loaded into the victim process</param>
        /// <returns>True on success</returns>
        public static bool InjectDll(uint processId, string fullDllPath)
        {
            return traditionalInject(processId, fullDllPath);
        }
    }
}
