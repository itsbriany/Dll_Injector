using System.Runtime.InteropServices;

namespace GUI
{
    class Injector
    {
        // TODO verify that this DLL is located in the same directory as the executable!
        [DllImport("Injector.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool traditionalInject(int dwProcessId, string fullDllPath);

        /// <summary>
        /// Injects a DLL into a target process
        /// </summary>
        /// <param name="processId">The process ID of the victim</param>
        /// <param name="fullDllPath">The full path to the dll being loaded into the victim process</param>
        /// <returns>True on success</returns>
        public static bool InjectDll(int processId, string fullDllPath)
        {
            try
            {
                return traditionalInject(processId, fullDllPath);

            }
            catch (System.Exception)
            {
                return false;
            }           
        }
    }
}
