
#include "dxgiFactory2.h"
#include "dxgiSwapchain2.h"
#include "utils.h"

DXGICustomFactory2::DXGICustomFactory2(void* factory)
{
	// Don't error for speed
	DxgiFactory = reinterpret_cast<IDXGIFactory3*>(factory);
	Event.open("DXGIFactory2.log");
	Event << LOG("Initialising") << std::endl;
	Event << DxgiFactory << std::endl;
	Event << DxgiFactory->IsWindowedStereoEnabled();
	Event << ": Success" << std::endl;
}

DXGICustomFactory2::~DXGICustomFactory2()
= default;

BOOL DXGICustomFactory2::IsWindowedStereoEnabled()
{
	return DxgiFactory->IsWindowedStereoEnabled();
}

HRESULT DXGICustomFactory2::CreateSwapChainForHwnd(IUnknown* pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc,
	const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain)
{
	Event << "CREATE" << std::endl;
	// HOOK THIS
	const auto temp = DxgiFactory->CreateSwapChainForHwnd(pDevice, hWnd, pDesc, pFullscreenDesc, pRestrictToOutput, ppSwapChain);
	//const auto tempSwapChain = new DXGICustomSwapChain2(*ppSwapChain, pDevice);
	//*ppSwapChain = tempSwapChain;
	return temp;
}

HRESULT DXGICustomFactory2::CreateSwapChainForCoreWindow(IUnknown* pDevice, IUnknown* pWindow,
	const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain)
{
	Event << "CREATE1" << std::endl;
	const auto temp = DxgiFactory->CreateSwapChainForCoreWindow(pDevice, pWindow, pDesc, pRestrictToOutput, ppSwapChain);
	//const auto tempSwapChain = new DXGICustomSwapChain2(*ppSwapChain, pDevice);
	//*ppSwapChain = tempSwapChain;
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
	Event << "CREATE2" << std::endl;
	const auto temp = DxgiFactory->CreateSwapChainForComposition(pDevice, pDesc, pRestrictToOutput, ppSwapChain);
	//const auto tempSwapChain = new DXGICustomSwapChain2(*ppSwapChain, pDevice);
	//*ppSwapChain = tempSwapChain;
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
	Event << "CREATE2" << std::endl;
	const auto temp = DxgiFactory->CreateSwapChain(pDevice, pDesc, ppSwapChain);
	//const auto tempSwapChain = new DXGICustomSwapChain2(*ppSwapChain, pDevice);
	//*ppSwapChain = tempSwapChain;
	return temp;
}

HRESULT DXGICustomFactory2::CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter** ppAdapter)
{
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
	return DxgiFactory->GetParent(riid, ppParent);
}

HRESULT DXGICustomFactory2::QueryInterface(const IID& riid, void** ppvObject)
{
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

UINT DXGICustomFactory2::GetCreationFlags()
{
	return DxgiFactory->GetCreationFlags();
}
