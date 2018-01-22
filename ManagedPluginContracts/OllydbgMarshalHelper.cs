using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace ManagedPluginContracts
{
    public static class OllydbgMarshalHelper
    {
        public static IntPtr StructureToPtr<T>(T structure)
        {
            IntPtr ptr = Marshal.AllocCoTaskMem(Marshal.SizeOf(typeof(T)));
            Marshal.StructureToPtr(structure, ptr, false);
            return ptr;
        }

        public static T PtrToStructure<T>(IntPtr ptr)
        {
            T ret = (T) Marshal.PtrToStructure(ptr, typeof(T));
            Marshal.FreeCoTaskMem(ptr);
            return ret;
        }

        public static IntPtr StructureArrayToPtr<T>(IList<T> structureArray)
        {
            IntPtr ptr = Marshal.AllocCoTaskMem(Marshal.SizeOf(typeof(T)) * structureArray.Count);
            for (int i = 0; i < structureArray.Count; i++)
            {
                IntPtr nextPtr = new IntPtr(ptr.ToInt32() + Marshal.SizeOf(typeof(T)) * i);
                Marshal.StructureToPtr(structureArray[i], nextPtr, false);
            }
            return ptr;
        }

        public static IList<T> PtrToStructureArray<T>(IntPtr ptr)
        {
            throw new NotImplementedException();
        }
    }
}
