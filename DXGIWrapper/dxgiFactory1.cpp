#include "dxgiFactory1.h"
#include "dxgiSwapchain2.h"
#include "utils.h"

DXGICustomFactory1::DXGICustomFactory1(void* factory, DXGIWrapper* log)
{
	// Don't error for speed
	DxgiFactory = reinterpret_cast<IDXGIFactory1*>(factory);
	m_pLog = log;
	m_pLog->Event << "[CF01] CTOR" << std::endl;
}

DXGICustomFactory1::~DXGICustomFactory1()
= default;

HRESULT DXGICustomFactory1::EnumAdapters(UINT Adapter, IDXGIAdapter** ppAdapter)
{
	return DxgiFactory->EnumAdapters(Adapter, ppAdapter);
}

HRESULT DXGICustomFactory1::MakeWindowAssociation(HWND WindowHandle, UINT Flags)
{
	return DxgiFactory->MakeWindowAssociation(WindowHandle, Flags);
}

HRESULT DXGICustomFactory1::GetWindowAssociation(HWND* pWindowHandle)
{
	return DxgiFactory->GetWindowAssociation(pWindowHandle);
}

HRESULT DXGICustomFactory1::CreateSwapChain(IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain)
{
	m_pLog->Event << "[CF01] CREATE" << std::endl;
	const auto temp = DxgiFactory->CreateSwapChain(pDevice, pDesc, ppSwapChain);
	const auto tempSwapChain = new DXGICustomSwapChain(*ppSwapChain, pDevice, m_pLog);
	*ppSwapChain = tempSwapChain;
	return temp;
}

HRESULT DXGICustomFactory1::CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter** ppAdapter)
{
	m_pLog->Event << "[CF01] CREATE Adapter" << std::endl;
	return DxgiFactory->CreateSoftwareAdapter(Module, ppAdapter);
}

HRESULT DXGICustomFactory1::SetPrivateData(const GUID& Name, UINT DataSize, const void* pData)
{
	return DxgiFactory->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGICustomFactory1::SetPrivateDataInterface(const GUID& Name, const IUnknown* pUnknown)
{
	return DxgiFactory->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGICustomFactory1::GetPrivateData(const GUID& Name, UINT* pDataSize, void* pData)
{
	return DxgiFactory->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGICustomFactory1::GetParent(const IID& riid, void** ppParent)
{
	m_pLog->Event << "[CF01] GetParent" << std::endl;
	return DxgiFactory->GetParent(riid, ppParent);
}

HRESULT DXGICustomFactory1::QueryInterface(const IID& riid, void** ppvObject)
{
	m_pLog->Event << "[CF01] Upgrade" << std::endl;
	return DxgiFactory->QueryInterface(riid, ppvObject);
}

ULONG DXGICustomFactory1::AddRef()
{
	return DxgiFactory->AddRef();
}

ULONG DXGICustomFactory1::Release()
{
	return DxgiFactory->Release();
}

HRESULT DXGICustomFactory1::EnumAdapters1(UINT Adapter, IDXGIAdapter1** ppAdapter)
{
	return DxgiFactory->EnumAdapters1(Adapter, ppAdapter);
}

BOOL DXGICustomFactory1::IsCurrent()
{
	return DxgiFactory->IsCurrent();
}
