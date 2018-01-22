// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <stdio.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here
#include "plugin.h"

#include <metahost.h>
#include <direct.h>
#include <Propvarutil.h>
#include <vector>

#pragma comment(lib, "MSCorEE.lib")
#pragma comment(lib, "Ollydbg.lib")

#import "C:\Windows\Microsoft.NET\Framework\v4.0.30319\mscorlib.tlb" raw_interfaces_only \
    high_property_prefixes("_get","_put","_putref")		\
    rename("ReportEvent", "InteropServices_ReportEvent")
using namespace mscorlib;
