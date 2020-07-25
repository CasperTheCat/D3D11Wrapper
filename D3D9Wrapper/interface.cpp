#include "interface.h"

D3D9CustomInterface::D3D9CustomInterface(IDirect3D9* pReal, D3DObjectManager* pGLOM)
{
    m_pRealInterface = pReal;
    m_pGLOM = pGLOM;
}

HRESULT __stdcall D3D9CustomInterface::QueryInterface(REFIID riid, void** ppvObj)
{
    return m_pRealInterface->QueryInterface(riid, ppvObj);
}

ULONG __stdcall D3D9CustomInterface::AddRef(void)
{
    return m_pRealInterface->AddRef();
}

ULONG __stdcall D3D9CustomInterface::Release(void)
{
    return m_pRealInterface->Release();
}

HRESULT __stdcall D3D9CustomInterface::RegisterSoftwareDevice(void* pInitializeFunction)
{
    return m_pRealInterface->RegisterSoftwareDevice(pInitializeFunction);
}

UINT __stdcall D3D9CustomInterface::GetAdapterCount(void)
{
    return m_pRealInterface->GetAdapterCount();
}

HRESULT __stdcall D3D9CustomInterface::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier)
{
    return m_pRealInterface->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT __stdcall D3D9CustomInterface::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
    return m_pRealInterface->GetAdapterModeCount(Adapter, Format);
}

HRESULT __stdcall D3D9CustomInterface::EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode)
{
    return m_pRealInterface->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

HRESULT __stdcall D3D9CustomInterface::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
    return m_pRealInterface->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT __stdcall D3D9CustomInterface::CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
    return m_pRealInterface->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);
}

HRESULT __stdcall D3D9CustomInterface::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
    return m_pRealInterface->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT __stdcall D3D9CustomInterface::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels)
{
    return m_pRealInterface->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT __stdcall D3D9CustomInterface::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
    return m_pRealInterface->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT __stdcall D3D9CustomInterface::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)
{
    return m_pRealInterface->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT __stdcall D3D9CustomInterface::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps)
{
    return m_pRealInterface->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR __stdcall D3D9CustomInterface::GetAdapterMonitor(UINT Adapter)
{
    return m_pRealInterface->GetAdapterMonitor(Adapter);
}

HRESULT __stdcall D3D9CustomInterface::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface)
{
    auto retVal = m_pRealInterface->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

    if (retVal == S_OK)
    {
        auto falseDevice = new D3D9CustomDevice(*ppReturnedDeviceInterface, m_pGLOM);
        *ppReturnedDeviceInterface = falseDevice;
    }

    return retVal;
}
