
#include "dxgiFactory2.h"
#include "dxgiSwapchain2.h"
#include "utils.h"

#define AsV6 (reinterpret_cast<IDXGIFactory6*>(DxgiFactory))
#define AsV5 (reinterpret_cast<IDXGIFactory5*>(DxgiFactory))
#define AsV4 (reinterpret_cast<IDXGIFactory4*>(DxgiFactory))

DXGICustomFactory2::DXGICustomFactory2(void* factory, DXGIWrapper* log)
{
	// Don't error for speed
	DxgiFactory = reinterpret_cast<IDXGIFactory3*>(factory);
	m_pLog = log;
	m_pLog->Event << "[CF02] CTOR" << std::endl;
}

DXGICustomFactory2::~DXGICustomFactory2()
= default;

HRESULT __stdcall DXGICustomFactory2::EnumAdapterByGpuPreference(UINT Adapter, DXGI_GPU_PREFERENCE GpuPreference, REFIID riid, void** ppvAdapter)
{
	return AsV6->EnumAdapterByGpuPreference(Adapter, GpuPreference, riid, ppvAdapter);
}

BOOL DXGICustomFactory2::IsWindowedStereoEnabled()
{
	return DxgiFactory->IsWindowedStereoEnabled();
}

HRESULT DXGICustomFactory2::CreateSwapChainForHwnd(IUnknown* pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc,
	const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain)
{
	m_pLog->Event << "CREATE" << std::endl;
	// HOOK THIS
	const auto temp = DxgiFactory->CreateSwapChainForHwnd(pDevice, hWnd, pDesc, pFullscreenDesc, pRestrictToOutput, ppSwapChain);
	const auto tempSwapChain = new DXGICustomSwapChain(*ppSwapChain, pDevice, m_pLog);
	*ppSwapChain = tempSwapChain;
	return temp;
}

HRESULT DXGICustomFactory2::CreateSwapChainForCoreWindow(IUnknown* pDevice, IUnknown* pWindow,
	const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain)
{
	m_pLog->Event << "CREATE1" << std::endl;
	const auto temp = DxgiFactory->CreateSwapChainForCoreWindow(pDevice, pWindow, pDesc, pRestrictToOutput, ppSwapChain);
	const auto tempSwapChain = new DXGICustomSwapChain(*ppSwapChain, pDevice, m_pLog);
	*ppSwapChain = tempSwapChain;
	return temp;
}

HRESULT DXGICustomFactory2::GetSharedResourceAdapterLuid(HANDLE hResource, LUID* pLuid)
{
	return DxgiFactory->GetSharedResourceAdapterLuid(hResource, pLuid);
}

HRESULT DXGICustomFactory2::RegisterStereoStatusWindow(HWND WindowHandle, UINT wMsg, DWORD* pdwCookie)
{
	return DxgiFactory->RegisterStereoStatusWindow(WindowHandle, wMsg, pdwCookie);
}

HRESULT DXGICustomFactory2::RegisterStereoStatusEvent(HANDLE hEvent, DWORD* pdwCookie)
{
	return DxgiFactory->RegisterStereoStatusEvent(hEvent, pdwCookie);
}

void DXGICustomFactory2::UnregisterStereoStatus(DWORD dwCookie)
{
	DxgiFactory->UnregisterStereoStatus(dwCookie);
}

HRESULT DXGICustomFactory2::RegisterOcclusionStatusWindow(HWND WindowHandle, UINT wMsg, DWORD* pdwCookie)
{
	return DxgiFactory->RegisterOcclusionStatusWindow(WindowHandle, wMsg, pdwCookie);
}

HRESULT DXGICustomFactory2::RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD* pdwCookie)
{
	return DxgiFactory->RegisterOcclusionStatusEvent(hEvent, pdwCookie);
}

void DXGICustomFactory2::UnregisterOcclusionStatus(DWORD dwCookie)
{
	DxgiFactory->UnregisterOcclusionStatus(dwCookie);
}

HRESULT DXGICustomFactory2::CreateSwapChainForComposition(IUnknown* pDevice, const DXGI_SWAP_CHAIN_DESC1* pDesc,
	IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain)
{
	m_pLog->Event << "CREATE2" << std::endl;
	const auto temp = DxgiFactory->CreateSwapChainForComposition(pDevice, pDesc, pRestrictToOutput, ppSwapChain);
	const auto tempSwapChain = new DXGICustomSwapChain(*ppSwapChain, pDevice, m_pLog);
	*ppSwapChain = tempSwapChain;
	return temp;
}

HRESULT DXGICustomFactory2::EnumAdapters(UINT Adapter, IDXGIAdapter** ppAdapter)
{
	return DxgiFactory->EnumAdapters(Adapter, ppAdapter);
}

HRESULT DXGICustomFactory2::MakeWindowAssociation(HWND WindowHandle, UINT Flags)
{
	return DxgiFactory->MakeWindowAssociation(WindowHandle, Flags);
}

HRESULT DXGICustomFactory2::GetWindowAssociation(HWND* pWindowHandle)
{
	return DxgiFactory->GetWindowAssociation(pWindowHandle);
}

HRESULT DXGICustomFactory2::CreateSwapChain(IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain)
{
	m_pLog->Event << "CREATE3" << std::endl;
	const auto temp = DxgiFactory->CreateSwapChain(pDevice, pDesc, ppSwapChain);
	const auto tempSwapChain = new DXGICustomSwapChain(*ppSwapChain, pDevice, m_pLog);
	*ppSwapChain = tempSwapChain;
	return temp;
}

HRESULT DXGICustomFactory2::CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter** ppAdapter)
{
	m_pLog->Event << "[CF02] SF Adapter" << std::endl;
	return DxgiFactory->CreateSoftwareAdapter(Module, ppAdapter);
}

HRESULT DXGICustomFactory2::SetPrivateData(const GUID& Name, UINT DataSize, const void* pData)
{
	return DxgiFactory->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGICustomFactory2::SetPrivateDataInterface(const GUID& Name, const IUnknown* pUnknown)
{
	return DxgiFactory->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGICustomFactory2::GetPrivateData(const GUID& Name, UINT* pDataSize, void* pData)
{
	return DxgiFactory->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGICustomFactory2::GetParent(const IID& riid, void** ppParent)
{
	m_pLog->Event << "Getting Parent :(" << std::endl;
	return DxgiFactory->GetParent(riid, ppParent);
}

HRESULT DXGICustomFactory2::QueryInterface(const IID& riid, void** ppvObject)
{
	m_pLog->Event << "[CF02] UPGRADE" << std::endl;
	return DxgiFactory->QueryInterface(riid, ppvObject);
}

ULONG DXGICustomFactory2::AddRef()
{
	return DxgiFactory->AddRef();
}

ULONG DXGICustomFactory2::Release()
{
	return DxgiFactory->Release();
}

HRESULT DXGICustomFactory2::EnumAdapters1(UINT Adapter, IDXGIAdapter1** ppAdapter)
{
	return DxgiFactory->EnumAdapters1(Adapter, ppAdapter);
}

BOOL DXGICustomFactory2::IsCurrent()
{
	return DxgiFactory->IsCurrent();
}

HRESULT __stdcall DXGICustomFactory2::CheckFeatureSupport(DXGI_FEATURE Feature, void* pFeatureSupportData, UINT FeatureSupportDataSize)
{
	return AsV5->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
}

HRESULT __stdcall DXGICustomFactory2::EnumAdapterByLuid(LUID AdapterLuid, REFIID riid, void** ppvAdapter)
{
	return AsV4->EnumAdapterByLuid(AdapterLuid, riid, ppvAdapter);
}

HRESULT __stdcall DXGICustomFactory2::EnumWarpAdapter(REFIID riid, void** ppvAdapter)
{
	return AsV4->EnumWarpAdapter(riid, ppvAdapter);
}

UINT DXGICustomFactory2::GetCreationFlags()
{
	return DxgiFactory->GetCreationFlags();
}
