#include "stdafx.h"
#include "d3d9ObjectManager.h"
#include "utils.h"
#include "d3d9Device.h"
#include "interface.h"
//#include <processenv.h>

D3DObjectManager* GlOM = new D3DObjectManager();

typedef IDirect3D9* (WINAPI* PFN_Direct3DCreate9)(UINT);
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	DEBUG_LOGLINE(GlOM->Event, LOG("Direct3DCreate9 intercepted"));
	PFN_Direct3DCreate9 call = (PFN_Direct3DCreate9)GetProcAddress(GlOM->getDLL(), "Direct3DCreate9");
	IDirect3D9* realInterface = call(SDKVersion);
	auto falseInterface = new D3D9CustomInterface(realInterface, GlOM);
	DEBUG_LOGLINE(GlOM->Event, LOG("Redirecting " << realInterface << " to " << falseInterface));
	return falseInterface;
}


typedef HRESULT(WINAPI* PFN_Direct3DCreate9Ex)(UINT, IDirect3D9Ex**);
HRESULT WINAPI Direct3DCreate9Ex(UINT SDKVersion, IDirect3D9Ex** Return)
{
	DEBUG_LOGLINE(GlOM->Event, LOG("Direct3DCreate9Ex intercepted"));
	PFN_Direct3DCreate9Ex call = (PFN_Direct3DCreate9Ex)GetProcAddress(GlOM->getDLL(), "Direct3DCreate9Ex");
	return call(SDKVersion, Return);
}

typedef HRESULT(WINAPI* PFN_Direct3DShaderValidatorCreate9)();
HRESULT WINAPI Direct3DShaderValidatorCreate9()
{
	DEBUG_LOGLINE(GlOM->Event, LOG("Direct3DShaderValidatorCreate9 intercepted"));
	PFN_Direct3DShaderValidatorCreate9 call = (PFN_Direct3DShaderValidatorCreate9)GetProcAddress(GlOM->getDLL(), "Direct3DShaderValidatorCreate9");
	return call();
}

typedef HRESULT(WINAPI* PFN_PSGPError)();
HRESULT WINAPI PSGPError()
{
	DEBUG_LOGLINE(GlOM->Event, LOG("PSGPError intercepted"));
	PFN_PSGPError call = (PFN_PSGPError)GetProcAddress(GlOM->getDLL(), "PSGPError");
	return call();
}

typedef HRESULT(WINAPI* PFN_PSGPSampleTexture)();
HRESULT WINAPI PSGPSampleTexture()
{
	DEBUG_LOGLINE(GlOM->Event, LOG("PSGPSampleTexture intercepted"));
	PFN_PSGPSampleTexture call = (PFN_PSGPSampleTexture)GetProcAddress(GlOM->getDLL(), "PSGPSampleTexture");
	return call();
}


void WINAPI Direct3D9EnableMaximizedWindowedModeShim()
{
	DEBUG_LOGLINE(GlOM->Event, LOG("Shim intercepted"));
}

void WINAPI DebugSetLevel(DWORD dw1)
{
	DEBUG_LOGLINE(GlOM->Event, LOG("SetLevelDBG intercepted"));
}

typedef void(WINAPI* PFN_DebugSetMute)();
void WINAPI DebugSetMute()
{
	PFN_DebugSetMute call = (PFN_DebugSetMute)GetProcAddress(GlOM->getDLL(), "DebugSetMute");
	call();
}



typedef int(WINAPI* PFN_PrefBeginEvent)(D3DCOLOR, LPCWSTR);
int WINAPI D3DPERF_BeginEvent(D3DCOLOR col, LPCWSTR wszName)
{
	DEBUG_LOGLINE(GlOM->Event, LOG("D3DPERF_BeginEvent intercepted"));
	PFN_PrefBeginEvent call = (PFN_PrefBeginEvent)GetProcAddress(GlOM->getDLL(), "D3DPERF_BeginEvent");
	return call(col, wszName);
}


typedef int(WINAPI* PFN_PrefEndEvent)(void);
int WINAPI D3DPERF_EndEvent(void)
{
	DEBUG_LOGLINE(GlOM->Event, LOG("D3DPERF_EndEvent intercepted"));
	PFN_PrefEndEvent call = (PFN_PrefEndEvent)GetProcAddress(GlOM->getDLL(), "D3DPERF_EndEvent");
	return call();
}

typedef void(WINAPI* PFN_PrefSetMarker)(D3DCOLOR, LPCWSTR);
void WINAPI D3DPERF_SetMarker(D3DCOLOR col, LPCWSTR wszName)
{
	DEBUG_LOGLINE(GlOM->Event, LOG("D3DPERF_EndEvent intercepted"));
	PFN_PrefSetMarker call = (PFN_PrefSetMarker)GetProcAddress(GlOM->getDLL(), "D3DPERF_SetMarker");
	return call(col, wszName);
}

typedef void(WINAPI* PFN_PrefSetRegion)(D3DCOLOR, LPCWSTR);
void WINAPI D3DPERF_SetRegion(D3DCOLOR col, LPCWSTR wszName)
{
	DEBUG_LOGLINE(GlOM->Event, LOG("D3DPERF_SetRegion intercepted"));
	PFN_PrefSetRegion call = (PFN_PrefSetRegion)GetProcAddress(GlOM->getDLL(), "D3DPERF_SetRegion");
	return call(col, wszName);
}

typedef BOOL(WINAPI* PFN_PrefQueryRepeatFrame)(void);
BOOL WINAPI D3DPERF_QueryRepeatFrame(void)
{
	DEBUG_LOGLINE(GlOM->Event, LOG("D3DPERF_QueryRepeatFrame intercepted"));
	PFN_PrefQueryRepeatFrame call = (PFN_PrefQueryRepeatFrame)GetProcAddress(GlOM->getDLL(), "D3DPERF_QueryRepeatFrame");
	return call();
}

typedef void(WINAPI* PFN_PrefSetOption)(DWORD);
void WINAPI D3DPERF_SetOptions(DWORD dwOptions)
{
	DEBUG_LOGLINE(GlOM->Event, LOG("D3DPERF_SetOptions intercepted"));
	PFN_PrefSetOption call = (PFN_PrefSetOption)GetProcAddress(GlOM->getDLL(), "D3DPERF_SetOptions");
	return call(dwOptions);
}

typedef DWORD(WINAPI* PFN_PrefGetStatus)(void);
DWORD WINAPI D3DPERF_GetStatus(void)
{
	DEBUG_LOGLINE(GlOM->Event, LOG("D3DPERF_GetStatus intercepted"));
	PFN_PrefGetStatus call = (PFN_PrefGetStatus)GetProcAddress(GlOM->getDLL(), "D3DPERF_GetStatus");
	return call();
}











// Global Class
//D3DObjectManager *GlOM = new D3DObjectManager();


// TODO: Handling


//typedef HRESULT(WINAPI* PFN_D3D11_CREATE_DEVICE)(__in_opt IDXGIAdapter*,
//	D3D_DRIVER_TYPE, HMODULE, UINT,
//	__in_ecount_opt(FeatureLevels) CONST D3D_FEATURE_LEVEL*,
//	UINT FeatureLevels, UINT, __out_opt ID3D11Device**,
//	__out_opt D3D_FEATURE_LEVEL*, __out_opt ID3D11DeviceContext**);
//
//
//HRESULT WINAPI D3D11CreateDevice(
//	__in_opt IDXGIAdapter* pAdapter,
//	D3D_DRIVER_TYPE DriverType,
//	HMODULE Software,
//	UINT Flags,
//	__in_ecount_opt(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
//	UINT FeatureLevels,
//	UINT SDKVersion,
//	__out_opt ID3D11Device** ppDevice,
//	__out_opt D3D_FEATURE_LEVEL* pFeatureLevel,
//	__out_opt ID3D11DeviceContext** ppImmediateContext)
//{
//	// Log
//	DEBUG_LOGLINE(GlOM->Event, LOG("D3D11CreateDevice intercepted"));
//	PFN_D3D11_CREATE_DEVICE createDev = (PFN_D3D11_CREATE_DEVICE)GetProcAddress(GlOM->getDLL(), "D3D11CreateDevice");
//	if (createDev == nullptr)
//	{
//		DEBUG_LOGLINE(GlOM->Event, LOGERR("Cannot find function D3D11CreateDevice in DLL"));
//		return NULL;
//	}
//
//	// Use the real DLL's function
//	HRESULT out = createDev(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
//	if (ppDevice)
//	{
//		DEBUG_LOGLINE(GlOM->Event, LOG("Device Created. Registering."));
//		//d3dw->setDevice(*ppDevice);
//
//		const auto temp = new D3D11CustomDevice(*ppDevice, GlOM);
//		*ppDevice = temp;
//
//		// Check if the optional immediate is being used
//		if (ppImmediateContext)
//		{
//			DEBUG_LOGLINE(GlOM->Event, LOG("Caught Immediate Context"));
//			ID3D11DeviceContext* tempCtx = new D3D11CustomContext(*ppImmediateContext, temp, GlOM);
//			*ppImmediateContext = tempCtx;
//		}
//	} 
//	else
//	{
//		DEBUG_LOGLINE(GlOM->Event, LOGWARN("Failed to get device from D3D11"));
//	}
//
//	return out;
//}
