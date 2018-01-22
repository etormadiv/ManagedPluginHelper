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

    public delegate uint TABFUNC(OllydbgTable pt, IntPtr hwnd, uint argA, IntPtr wparam, IntPtr lparam);
    public delegate void TABSELFUNC(OllydbgTable pt, int arg1, int arg2);
    public delegate int UPDATEFUNC(OllydbgTable pt);
    public delegate int DRAWFUNC(string s, byte[] mask, IntPtr select, OllydbgTable pt, OllydbgSortHdr ps, int column, IntPtr cache);
    public delegate int SORTFUNC(IntPtr hdr1, IntPtr hdr2, int num);
    public delegate void DESTFUNC(IntPtr hdr);

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

    [StructLayout(LayoutKind.Sequential)]
    public struct OllydbgTable
    {
        [MarshalAs(UnmanagedType.LPWStr, SizeConst = 32)]
        public string name;
        public int mode;
        public OllydbgSorted sorted;
        public int subtype;
        public OllydbgBar bar;
        public int bottomspace;
        public int minwidth;
        public TABFUNC tabfunc;
        public UPDATEFUNC updatefunc;
        public DRAWFUNC drawfunc;
        public TABSELFUNC tableselfunc;
        public IntPtr menu;
        public uint custommode;
        public IntPtr customdata;
        public IntPtr hparent;
        public IntPtr hstatus;
        public IntPtr hw;
        public IntPtr htooltip;
        public int font;
        public int scheme;
        public int hilite;
        public int hscroll;
        public int xshift;
        public int offset;
        public int colsel;
        public uint version;
        public uint timerdraw;
        public RECT rcprev;
        public int rtback;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct OllydbgSorted
    {
        public int n;
        public int nmax;
        public uint itemsize;
        public int mode;
        public IntPtr data;
        public IntPtr block;
        public int nblock;
        public uint version;
        public IntPtr dataptr;
        public int selected;
        public uint seladdr;
        public uint selsubaddr;
        public SORTFUNC sortfunc;
        public DESTFUNC destfunc;
        public int sort;
        public int sorted;
        public IntPtr sortindex;
    }

    public struct OllydbgBar
    {

    }

    public struct OllydbgSortHdr
    {

    }

    [StructLayout(LayoutKind.Sequential)]
    public struct RECT
    {
        public int Left;
        public int Top;
        public int Right;
        public int Bottom;
    }

}
