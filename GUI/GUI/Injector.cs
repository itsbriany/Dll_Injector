using System.Runtime.InteropServices;

namespace GUI
{
    class Injector
    {
        // TODO verify that this DLL is located in the same directory as the executable!
        [DllImport("Injector.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void inject(int dwProcessId);

        /// <summary>
        /// Injects a DLL into a target process
        /// </summary>
        /// <returns>True on success</returns>
        public static bool InjectDll(int processId)
        {
            inject(processId);
            return true;
        }
    }
}
