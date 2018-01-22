using ManagedPluginContracts;
using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace ManagedPluginLoader
{
    public class ManagedPluginLoader
    {
        private IntPtr pluginsMenuPtr = IntPtr.Zero;
        private List<OllydbgMenu> menuList = new List<OllydbgMenu>();

        public ManagedPluginLoader()
        {

        }

        public void LoadManagedPlugins()
        {
            DirectoryInfo di = Directory.CreateDirectory(".\\ManagedPlugins");
            menuList.Clear();
            foreach (FileInfo file in di.GetFiles())
            {
                if(file.Name.ToLower().EndsWith(".dll"))
                {
                    try
                    {
                        Assembly asm = AppDomain.CurrentDomain.Load(File.ReadAllBytes(file.FullName));
                        Type[] exportTypes = asm.GetExportedTypes();
                        foreach (var item in exportTypes)
                        {
                            if (typeof(IOllydbgPlugin).IsAssignableFrom(item))
                            {
                                IOllydbgPlugin plugin = (IOllydbgPlugin) Activator.CreateInstance(item);
                                OllydbgMenu menu = plugin.GetPluginMenu();
                                menuList.Add(menu);
                                break; //Get only one type from each assembly, to make things clear
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message);
                    }
                }
            }
            menuList.Add(new OllydbgMenu()); //Last item must be null/zero values
        }
        public void FillApiFunction(string functionName, int functionAddress)
        {
            try
            {
                typeof(OllydbgApi).GetField(functionName).SetValue(null,
                    Marshal.GetDelegateForFunctionPointer(new IntPtr(functionAddress),
                    Type.GetType("ManagedPluginContracts." + functionName + "Delegate, ManagedPluginContracts"))
                );
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        public int GetPluginsMenus()
        {
            if (pluginsMenuPtr == IntPtr.Zero)
            {
                pluginsMenuPtr = OllydbgMarshalHelper.StructureArrayToPtr(menuList);
            }
            return pluginsMenuPtr.ToInt32();
        }
    }
}
