using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace ManagedPluginContracts
{
    public class OllydbgMenuBuilder
    {
        private OllydbgMenu m_OllydbgMenu;
        private List<OllydbgMenu> m_OllydbgSubmenu;

        public OllydbgMenuBuilder(string name, string help, int shortcutid, MENUFUNC menufunc, uint index)
        {
            m_OllydbgMenu = new OllydbgMenu();
            m_OllydbgMenu.name = name;
            m_OllydbgMenu.help = help;
            m_OllydbgMenu.shortcutid = shortcutid;
            m_OllydbgMenu.menufunc = menufunc;
            m_OllydbgMenu.index = index;

            m_OllydbgSubmenu = new List<OllydbgMenu>();
        }

        public OllydbgMenuBuilder(string name, string help, int shortcutid, MENUFUNC menufunc, IntPtr hsubmenu)
        {
            m_OllydbgMenu = new OllydbgMenu();
            m_OllydbgMenu.name = name;
            m_OllydbgMenu.help = help;
            m_OllydbgMenu.shortcutid = shortcutid;
            m_OllydbgMenu.menufunc = menufunc;
            m_OllydbgMenu.hsubmenu = hsubmenu.ToInt32();

            m_OllydbgSubmenu = new List<OllydbgMenu>();
        }

        public void AddSubmenu(string name, string help, int shortcutid, MENUFUNC menufunc, uint index)
        {
            OllydbgMenu submenu = new OllydbgMenu();
            submenu.name = name;
            submenu.help = help;
            submenu.shortcutid = shortcutid;
            submenu.menufunc = menufunc;
            submenu.index = index;

            m_OllydbgSubmenu.Add(submenu);
        }

        public void AddSubmenu(string name, string help, int shortcutid, MENUFUNC menufunc, uint index, IList<OllydbgMenu> subsubmenus)
        {
            OllydbgMenu submenu = new OllydbgMenu();
            submenu.name = name;
            submenu.help = help;
            submenu.shortcutid = shortcutid;
            submenu.menufunc = menufunc;
            submenu.index = index;

            IntPtr subsubmenuPtr = Marshal.AllocCoTaskMem(Marshal.SizeOf(typeof(OllydbgMenu)) * (subsubmenus.Count + 1));
            for (int i = 0; i < subsubmenus.Count; i++)
            {
                Marshal.StructureToPtr(subsubmenus[i], new IntPtr(subsubmenuPtr.ToInt32() + Marshal.SizeOf(typeof(OllydbgMenu)) * i), false);
            }

            submenu.submenu = subsubmenuPtr.ToInt32();

            m_OllydbgSubmenu.Add(submenu);
        }

        public void AddSubmenu(string name, string help, int shortcutid, MENUFUNC menufunc, IntPtr hsubmenu)
        {
            OllydbgMenu submenu = new OllydbgMenu();
            submenu.name = name;
            submenu.help = help;
            submenu.shortcutid = shortcutid;
            submenu.menufunc = menufunc;
            submenu.hsubmenu = hsubmenu.ToInt32();

            m_OllydbgSubmenu.Add(submenu);
        }

        public OllydbgMenu Build()
        {
            if (m_OllydbgSubmenu.Count > 0)
            {
                m_OllydbgSubmenu.Add(new OllydbgMenu()); //Last item must be null/zero values.

                IntPtr pluginMenuPtr = Marshal.AllocCoTaskMem(Marshal.SizeOf(typeof(OllydbgMenu)) * m_OllydbgSubmenu.Count);
                for (int i = 0; i < m_OllydbgSubmenu.Count; i++)
                {
                    IntPtr itemPtr = new IntPtr(pluginMenuPtr.ToInt32() + Marshal.SizeOf(typeof(OllydbgMenu)) * i);
                    Marshal.StructureToPtr(m_OllydbgSubmenu[i], itemPtr, false);
                }
                m_OllydbgMenu.submenu = pluginMenuPtr.ToInt32();
            }
            return m_OllydbgMenu;
        }
    }
}
