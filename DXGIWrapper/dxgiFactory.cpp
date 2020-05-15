#include "dxgiFactory.h"
#include "dxgiSwapchain2.h"
#include "utils.h"

DXGICustomFactory::DXGICustomFactory(void* factory, DXGIWrapper* log)
{
	// Don't error for speed
	DxgiFactory = reinterpret_cast<IDXGIFactory*>(factory);
	m_pLog = log;
	m_pLog->Event << "[CF00] CTOR" << std::endl;
}

DXGICustomFactory::~DXGICustomFactory()
= default;

HRESULT DXGICustomFactory::EnumAdapters(UINT Adapter, IDXGIAdapter** ppAdapter)
{
	return DxgiFactory->EnumAdapters(Adapter, ppAdapter);
}

HRESULT DXGICustomFactory::MakeWindowAssociation(HWND WindowHandle, UINT Flags)
{
	return DxgiFactory->MakeWindowAssociation(WindowHandle, Flags);
}

HRESULT DXGICustomFactory::GetWindowAssociation(HWND* pWindowHandle)
{
	return DxgiFactory->GetWindowAssociation(pWindowHandle);
}

HRESULT DXGICustomFactory::CreateSwapChain(IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain)
{
	const auto temp = DxgiFactory->CreateSwapChain(pDevice, pDesc, ppSwapChain);
	const auto tempSwapChain = new DXGICustomSwapChain(*ppSwapChain, pDevice, m_pLog);
	*ppSwapChain = tempSwapChain;
	return temp;
}

HRESULT DXGICustomFactory::CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter** ppAdapter)
{
	return DxgiFactory->CreateSoftwareAdapter(Module, ppAdapter);
}

HRESULT DXGICustomFactory::SetPrivateData(const GUID& Name, UINT DataSize, const void* pData)
{
	return DxgiFactory->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGICustomFactory::SetPrivateDataInterface(const GUID& Name, const IUnknown* pUnknown)
{
	return DxgiFactory->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGICustomFactory::GetPrivateData(const GUID& Name, UINT* pDataSize, void* pData)
{
	return DxgiFactory->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGICustomFactory::GetParent(const IID& riid, void** ppParent)
{
	return DxgiFactory->GetParent(riid, ppParent);
}

HRESULT DXGICustomFactory::QueryInterface(const IID& riid, void** ppvObject)
{
	return DxgiFactory->QueryInterface(riid, ppvObject);
}

ULONG DXGICustomFactory::AddRef()
{
	return DxgiFactory->AddRef();
}

ULONG DXGICustomFactory::Release()
{
	return DxgiFactory->Release();
}
