// ManagedPluginHelper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#define PLUGINNAME     L"Managed Plugin Helper"
#define VERSION        L"1.0.0.0"

static HINSTANCE hdllinst;
static std::vector<t_menu> mainmenu_dynamic;
int mainmenu_open_api_list(struct t_table* ptable, wchar_t* name, ulong index, int mode);
static t_menu* managed_plugins_menu;

BOOL WINAPI DllEntryPoint(HINSTANCE hi, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH)
		hdllinst = hi;
	return 1;
};

extc int __cdecl ODBG2_Pluginquery(
	int ollydbgversion, 
	ulong *features,
	wchar_t pluginname[SHORTNAME], 
	wchar_t pluginversion[SHORTNAME]) 
{

	if (ollydbgversion < 201)
		return 0;

	wcscpy(pluginname, PLUGINNAME);
	wcscpy(pluginversion, VERSION);
	return PLUGIN_VERSION;
};

extc int __cdecl ODBG2_Plugininit(void) {
	
	ICLRMetaHost* pMetaHost = NULL;
	HRESULT hr;
	/* Get ICLRMetaHost instance */
	hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (VOID**)&pMetaHost);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] CLRCreateInstance(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	ICLRRuntimeInfo* pRuntimeInfo = NULL;
	/* Get ICLRRuntimeInfo instance */
	hr = pMetaHost->GetRuntime(L"v4.0.30319", IID_ICLRRuntimeInfo, (VOID**)&pRuntimeInfo);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pMetaHost->GetRuntime(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	BOOL bLoadable;
	/* Check if the specified runtime can be loaded */
	hr = pRuntimeInfo->IsLoadable(&bLoadable);
	if (FAILED(hr) || !bLoadable)
	{
		MessageBox(NULL, L"[!] pRuntimeInfo->IsLoadable(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	ICorRuntimeHost* pRuntimeHost = NULL;
	/* Get ICorRuntimeHost instance */
	hr = pRuntimeInfo->GetInterface(CLSID_CorRuntimeHost, IID_ICorRuntimeHost, (VOID**)&pRuntimeHost);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pRuntimeInfo->GetInterface(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	/* Start the CLR */
	hr = pRuntimeHost->Start();
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pRuntimeHost->Start() failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	IUnknownPtr pAppDomainThunk = NULL;
	hr = pRuntimeHost->GetDefaultDomain(&pAppDomainThunk);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pRuntimeHost->GetDefaultDomain(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	_AppDomainPtr pDefaultAppDomain = NULL;
	/* Equivalent of System.AppDomain.CurrentDomain in C# */
	hr = pAppDomainThunk->QueryInterface(__uuidof(_AppDomain), (VOID**)&pDefaultAppDomain);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pAppDomainThunk->QueryInterface(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}
	_AssemblyPtr pAssembly = NULL;

	FILE * pFile;
	long lSize;
	void *buffer;
	size_t result;

	pFile = fopen("ManagedPluginLoader.dll", "rb");
	if (pFile == NULL)
	{
		MessageBox(NULL, L"[!] fopen(\"ManagedPluginLoader.dll\") failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory to contain the whole file:
	buffer = CoTaskMemAlloc(lSize);
	if (buffer == NULL)
	{
		MessageBox(NULL, L"[!] malloc(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	// copy the file into the buffer:
	result = fread(buffer, 1, lSize, pFile);
	SAFEARRAYBOUND bounds = { lSize, 0 };

	SAFEARRAY *psa = SafeArrayCreate(VT_UI1, 1, &bounds);
	void* data;
	SafeArrayAccessData(psa, &data);
	CopyMemory(data, buffer, lSize);
	CoTaskMemFree(buffer);
	buffer = nullptr;

	SafeArrayUnaccessData(psa);

	hr = pDefaultAppDomain->Load_3(psa, &pAssembly);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pDefaultAppDomain->Load_3(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	_TypePtr pManagedPluginLoaderType = NULL;
	hr = pAssembly->GetType_2(bstr_t("ManagedPluginLoader.ManagedPluginLoader"), &pManagedPluginLoaderType);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pAssembly->GetType_2(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	VARIANT managedPluginLoaderInstance;
	VariantClear(&managedPluginLoaderInstance);
	hr = pAssembly->CreateInstance(bstr_t("ManagedPluginLoader.ManagedPluginLoader"), &managedPluginLoaderInstance);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pAssembly->CreateInstance(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	_MethodInfoPtr pLoadManagedPluginsMethodInfo;
	hr = pManagedPluginLoaderType->GetMethod_6(bstr_t("LoadManagedPlugins"), &pLoadManagedPluginsMethodInfo);
	if (FAILED(hr) || !pLoadManagedPluginsMethodInfo)
	{
		MessageBox(NULL, L"[!] pManagedPluginLoaderType->GetMethod_6(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	SAFEARRAY *psaLoadManagedPlugins = SafeArrayCreateVector(VT_VARIANT, 0, 0);
	VARIANT retVal;
	VariantClear(&retVal);
	hr = pLoadManagedPluginsMethodInfo->Invoke_3(managedPluginLoaderInstance, psaLoadManagedPlugins, &retVal);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pLoadManagedPluginsMethodInfo->Invoke_3(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	_MethodInfoPtr pGetPluginsMenusMethodInfo;
	hr = pManagedPluginLoaderType->GetMethod_6(bstr_t("GetPluginsMenus"), &pGetPluginsMenusMethodInfo);
	if (FAILED(hr) || !pGetPluginsMenusMethodInfo)
	{
		MessageBox(NULL, L"[!] pManagedPluginLoaderType->GetMethod_6(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	SAFEARRAY *psaGetPluginsMenus = SafeArrayCreateVector(VT_VARIANT, 0, 0);
	VariantClear(&retVal);
	hr = pGetPluginsMenusMethodInfo->Invoke_3(managedPluginLoaderInstance, psaGetPluginsMenus, &retVal);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"[!] pLoadManagedPluginsMethodInfo->Invoke_3(...) failed\n", L"Managed Plugin Helper Error", MB_ICONERROR);
		return -1;
	}

	managed_plugins_menu = (t_menu*)retVal.intVal;
	return 0;
};

extc t_menu * __cdecl ODBG2_Pluginmenu(wchar_t *type) {
	if (wcscmp(type, PWM_MAIN) == 0)
		return managed_plugins_menu;
	return NULL;
};