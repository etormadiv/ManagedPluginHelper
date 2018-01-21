using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace ManagedPluginContracts
{
    public enum OllydbgMenuMode
    {
        Verify  = 0,
        Execute = 1
    }

    public enum OllydbgMenuStatus
    {
        Absent      = 0,
        Normal      = 1,
        Checked     = 2,
        CheckParent = 3,
        Grayed      = 4,
        Shortcut    = 5,

        NoRedraw    = 0,
        Redraw      = 1
    }

    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.I4)]
    public delegate OllydbgMenuStatus MENUFUNC(
        int ptable, 
        [MarshalAs(UnmanagedType.LPWStr)]string name, 
        uint index, 
        [MarshalAs(UnmanagedType.I4)]OllydbgMenuMode mode);

    [StructLayout(LayoutKind.Explicit, CharSet = CharSet.Unicode)]
    public struct OllydbgMenu
    {
        [MarshalAs(UnmanagedType.LPWStr)]
        [FieldOffset(0)]
        public string name;

        [MarshalAs(UnmanagedType.LPWStr)]
        [FieldOffset(4)]
        public string help;

        [FieldOffset(8)]
        public int shortcutid;

        [MarshalAs(UnmanagedType.FunctionPtr)]
        [FieldOffset(12)]
        public MENUFUNC menufunc;

        [FieldOffset(16)]
        public int submenu;

        [FieldOffset(20)]
        public uint index;

        [FieldOffset(20)]
        public int hsubmenu;
    }
    public interface IOllydbgPlugin
    {
        string GetPluginName();
        OllydbgMenu GetPluginMenu();
    }
}
