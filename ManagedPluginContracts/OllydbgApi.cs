using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace ManagedPluginContracts
{
    public delegate void AbsolutizepathDelegate([MarshalAs(UnmanagedType.LPWStr)]string path);
    public delegate IntPtr ActivatetablewindowDelegate(IntPtr pt);

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void ErrorDelegate([MarshalAs(UnmanagedType.LPWStr)]string format, IntPtr args);
    public delegate void FlushmemorycacheDelegate();
    public delegate uint ReadmemoryDelegate(byte[] buf, uint addr, uint size, int mode);
    public delegate uint ReadmemoryexDelegate(byte[] buf, uint addr, uint size, int mode, uint threadid);

    public class OllydbgApi
    {
        public static AbsolutizepathDelegate Absolutizepath;
        public static ActivatetablewindowDelegate Activatetablewindow;

        public static ErrorDelegate Error;
        public static FlushmemorycacheDelegate Flushmemorycache;
        public static ReadmemoryDelegate Readmemory;
        public static ReadmemoryexDelegate Readmemoryex;
    }
}
