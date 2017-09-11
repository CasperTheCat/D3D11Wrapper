#include "stdafx.h"
#include "utils.h"
#include "dxgiWrapper.h"

DXGIWrapper *dxdw = new DXGIWrapper();


typedef HRESULT(WINAPI *DXGIFAC)(REFIID, _COM_Outptr_ void **);
HRESULT WINAPI CreateDXGIFactory(REFIID riid, _COM_Outptr_ void **ppFactory)
{
	dxdw->Event << LOG("CreateDXGIFactory intercepted") << std::endl;
	MessageBox(NULL, L"FactoryCreate", L"D3D9Wrapper", MB_OK);
	DXGIFAC pCreateFactory = (DXGIFAC)GetProcAddress(dxdw->getDLL(), "CreateDXGIFactory");
	if (!pCreateFactory)
	{
		//g_Globals.ErrorFile() << "coud not find Direct3DCreate9 in d3d9.dll\n";
		return NULL;
	}
	MessageBox(NULL, L"Calling", L"D3D9Wrapper", MB_OK);
	HRESULT pD3D = pCreateFactory(riid, ppFactory);
	if (ppFactory == NULL)
	{
		MessageBox(NULL, L"Call Failed!", L"D3D9Wrapper", MB_OK);
		return NULL;
	}

	return pD3D;
}

HRESULT WINAPI CreateDXGIFactory1(REFIID riid, _COM_Outptr_  void **ppFactory)
{
	dxdw->Event << LOG("CreateDXGIFactory1 intercepted") << std::endl;
	MessageBox(NULL, L"FactoryCreate1", L"D3D9Wrapper", MB_OK);
	DXGIFAC pCreateFactory = (DXGIFAC)GetProcAddress(dxdw->getDLL(), "CreateDXGIFactory1");
	if (!pCreateFactory)
	{
		//g_Globals.ErrorFile() << "coud not find Direct3DCreate9 in d3d9.dll\n";
		return NULL;
	}
	MessageBox(NULL, L"Calling", L"D3D9Wrapper", MB_OK);
	HRESULT pD3D = pCreateFactory(riid, ppFactory);
	if (ppFactory == NULL)
	{
		MessageBox(NULL, L"Call Failed!", L"D3D9Wrapper", MB_OK);
		return NULL;
	}

	return pD3D;
}

HRESULT WINAPI CreateDXGIFactory2(REFIID riid, _COM_Outptr_  void **ppFactory)
{
	
	dxdw->Event << LOG("CreateDXGIFactory2 intercepted") << std::endl;
	MessageBox(NULL, L"FactoryCreate2", L"D3D9Wrapper", MB_OK);
	DXGIFAC pCreateFactory = (DXGIFAC)GetProcAddress(dxdw->getDLL(), "CreateDXGIFactory2");
	if (!pCreateFactory)
	{
		//g_Globals.ErrorFile() << "coud not find Direct3DCreate9 in d3d9.dll\n";
		return NULL;
	}

	HRESULT pD3D = pCreateFactory(riid, ppFactory);
	if (ppFactory == NULL)
	{
		return NULL;
	}

	return pD3D;
}