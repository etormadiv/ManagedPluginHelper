using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ManagedPluginContracts
{
    public class OllydbgApi
    {
        public delegate uint ReadmemoryDelegate(byte[] buf, uint addr, uint size, int mode);

        static ReadmemoryDelegate Readmemory;
    }
}
