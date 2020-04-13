#include "dxgiSwapchain2.h"
#include "utils.h"

#include <iostream>

#define AsV4 (reinterpret_cast<IDXGISwapChain4*>(DxgiSwapchain))
#define AsV3 (reinterpret_cast<IDXGISwapChain3*>(DxgiSwapchain))
#define AsV2 (reinterpret_cast<IDXGISwapChain2*>(DxgiSwapchain))
#define AsV1 (reinterpret_cast<IDXGISwapChain1*>(DxgiSwapchain))

#pragma region DXGISwapChain2

DXGICustomSwapChain::DXGICustomSwapChain(void * swapchain, IUnknown * dev, DXGIWrapper *log)
{
	// Check the device for hook
	CustomDevice = dynamic_cast<D3D11CustomDevice*>(dev);
	DxgiSwapchain = reinterpret_cast<IDXGISwapChain*>(swapchain);
	m_pWrap = log;
	m_pGLOM = nullptr;

	m_pWrap->Event << "Created Custom SC " << swapchain << std::endl;
}

DXGICustomSwapChain::DXGICustomSwapChain(IDXGISwapChain* swapchain, ID3D11Device* dev, D3DObjectManager* glom) :
	CustomDevice(nullptr),
	DxgiSwapchain(swapchain),
	m_pGLOM(glom),
	m_pWrap(nullptr)
{
	auto temp = dynamic_cast<D3D11CustomDevice*>(dev);
	if (temp) { CustomDevice = temp; }
}

#pragma region DXGISwapChain4
HRESULT __stdcall DXGICustomSwapChain::SetHDRMetaData(DXGI_HDR_METADATA_TYPE Type, UINT Size, void* pMetaData)
{
	return AsV4->SetHDRMetaData(Type, Size, pMetaData);
}
#pragma endregion 

#pragma region DXGISwapChain3

UINT __stdcall DXGICustomSwapChain::GetCurrentBackBufferIndex()
{
	return AsV3->GetCurrentBackBufferIndex();
}

HRESULT __stdcall DXGICustomSwapChain::CheckColorSpaceSupport(DXGI_COLOR_SPACE_TYPE ColorSpace, UINT* pColorSpaceSupport)
{
	return AsV3->CheckColorSpaceSupport(ColorSpace, pColorSpaceSupport);
}

HRESULT __stdcall DXGICustomSwapChain::SetColorSpace1(DXGI_COLOR_SPACE_TYPE ColorSpace)
{
	return AsV3->SetColorSpace1(ColorSpace);
}

HRESULT __stdcall DXGICustomSwapChain::ResizeBuffers1(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT Format, UINT SwapChainFlags, const UINT* pCreationNodeMask, IUnknown* const* ppPresentQueue)
{
	return AsV3->ResizeBuffers1(BufferCount, Width, Height, Format, SwapChainFlags, pCreationNodeMask, ppPresentQueue);
}

#pragma endregion 

#pragma region DXGISwapChain2

HRESULT DXGICustomSwapChain::SetSourceSize(UINT Width, UINT Height)
{
	return AsV2->SetSourceSize(Width, Height);
}

HRESULT DXGICustomSwapChain::GetSourceSize(UINT* pWidth, UINT* pHeight)
{
	return AsV2->GetSourceSize(pWidth, pHeight);
}

HRESULT DXGICustomSwapChain::SetMaximumFrameLatency(UINT MaxLatency)
{
	return AsV2->SetMaximumFrameLatency(MaxLatency);
}

HRESULT DXGICustomSwapChain::GetMaximumFrameLatency(UINT* pMaxLatency)
{
	return AsV2->GetMaximumFrameLatency(pMaxLatency);
}

HANDLE DXGICustomSwapChain::GetFrameLatencyWaitableObject()
{
	return AsV2->GetFrameLatencyWaitableObject();
}

HRESULT DXGICustomSwapChain::SetMatrixTransform(const DXGI_MATRIX_3X2_F* pMatrix)
{
	return AsV2->SetMatrixTransform(pMatrix);
}

HRESULT DXGICustomSwapChain::GetMatrixTransform(DXGI_MATRIX_3X2_F* pMatrix)
{
	return AsV2->GetMatrixTransform(pMatrix);
}
#pragma endregion 

#pragma region DXGISwapChain1
HRESULT DXGICustomSwapChain::GetDesc1(DXGI_SWAP_CHAIN_DESC1* pDesc)
{
	return AsV1->GetDesc1(pDesc);
}

HRESULT DXGICustomSwapChain::GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pDesc)
{
	return AsV1->GetFullscreenDesc(pDesc);
}

HRESULT DXGICustomSwapChain::GetHwnd(HWND* pHwnd)
{
	return AsV1->GetHwnd(pHwnd);
}

HRESULT DXGICustomSwapChain::GetCoreWindow(const IID& refiid, void** ppUnk)
{
	return AsV1->GetCoreWindow(refiid, ppUnk);
}

HRESULT DXGICustomSwapChain::Present1(UINT SyncInterval, UINT PresentFlags,
	const DXGI_PRESENT_PARAMETERS* pPresentParameters)
{
	//if (m_pGLOM)
	//{
	//	m_pGLOM->Event << LOG("Present1") << std::endl;
	//}
	//else
	//{
	//	m_pWrap->Event << LOG("Present1") << std::endl;
	//}

	if (CustomDevice) CustomDevice->Notify_Present();
	return AsV1->Present1(SyncInterval, PresentFlags, pPresentParameters);
}

BOOL DXGICustomSwapChain::IsTemporaryMonoSupported()
{
	return AsV1->IsTemporaryMonoSupported();
}

HRESULT DXGICustomSwapChain::GetRestrictToOutput(IDXGIOutput** ppRestrictToOutput)
{
	return AsV1->GetRestrictToOutput(ppRestrictToOutput);
}

HRESULT DXGICustomSwapChain::SetBackgroundColor(const DXGI_RGBA* pColor)
{
	return AsV1->SetBackgroundColor(pColor);
}

HRESULT DXGICustomSwapChain::GetBackgroundColor(DXGI_RGBA* pColor)
{
	return AsV1->GetBackgroundColor(pColor);
}

HRESULT DXGICustomSwapChain::SetRotation(DXGI_MODE_ROTATION Rotation)
{
	return AsV1->SetRotation(Rotation);
}

HRESULT DXGICustomSwapChain::GetRotation(DXGI_MODE_ROTATION* pRotation)
{
	return AsV1->GetRotation(pRotation);
}
#pragma endregion

#pragma region DXGISwapChain
HRESULT DXGICustomSwapChain::Present(UINT SyncInterval, UINT Flags)
{
	//if (m_pGLOM)
	//{
	//	m_pGLOM->Event << LOG("Present1") << std::endl;
	//}
	//else
	//{
	//	m_pWrap->Event << LOG("Present1") << std::endl;
	//}
	if (CustomDevice) CustomDevice->Notify_Present();

	return DxgiSwapchain->Present(SyncInterval, Flags);
}

HRESULT DXGICustomSwapChain::GetBuffer(UINT Buffer, const IID& riid, void** ppSurface)
{
	return DxgiSwapchain->GetBuffer(Buffer, riid, ppSurface);
}

HRESULT DXGICustomSwapChain::SetFullscreenState(BOOL Fullscreen, IDXGIOutput* pTarget)
{
	return DxgiSwapchain->SetFullscreenState(Fullscreen, pTarget);
}

HRESULT DXGICustomSwapChain::GetFullscreenState(BOOL* pFullscreen, IDXGIOutput** ppTarget)
{
	return DxgiSwapchain->GetFullscreenState(pFullscreen, ppTarget);
}

HRESULT DXGICustomSwapChain::GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc)
{
	return DxgiSwapchain->GetDesc(pDesc);
}

HRESULT DXGICustomSwapChain::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat,
	UINT SwapChainFlags)
{
	return DxgiSwapchain->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT DXGICustomSwapChain::ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters)
{
	return DxgiSwapchain->ResizeTarget(pNewTargetParameters);
}

HRESULT DXGICustomSwapChain::GetContainingOutput(IDXGIOutput** ppOutput)
{
	return DxgiSwapchain->GetContainingOutput(ppOutput);
}

HRESULT DXGICustomSwapChain::GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats)
{
	return DxgiSwapchain->GetFrameStatistics(pStats);
}

HRESULT DXGICustomSwapChain::GetLastPresentCount(UINT* pLastPresentCount)
{
	return DxgiSwapchain->GetLastPresentCount(pLastPresentCount);
}
#pragma endregion

#pragma region SubObject
HRESULT DXGICustomSwapChain::GetDevice(const IID& riid, void** ppDevice)
{
	auto ret = DxgiSwapchain->GetDevice(riid, ppDevice);
	if (CustomDevice) { *ppDevice = CustomDevice; }
	return ret;
}
#pragma endregion

#pragma region Object	
HRESULT DXGICustomSwapChain::SetPrivateData(const GUID& Name, UINT DataSize, const void* pData)
{
	return DxgiSwapchain->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGICustomSwapChain::SetPrivateDataInterface(const GUID& Name, const IUnknown* pUnknown)
{
	return DxgiSwapchain->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGICustomSwapChain::GetPrivateData(const GUID& Name, UINT* pDataSize, void* pData)
{
	return DxgiSwapchain->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGICustomSwapChain::GetParent(const IID& riid, void** ppParent)
{
	return DxgiSwapchain->GetParent(riid, ppParent);
}
#pragma endregion 

#pragma region IUnknown
HRESULT DXGICustomSwapChain::QueryInterface(const IID& riid, void** ppvObject)
{
	return DxgiSwapchain->QueryInterface(riid, ppvObject);
}

ULONG DXGICustomSwapChain::AddRef()
{
	return DxgiSwapchain->AddRef();
}

ULONG DXGICustomSwapChain::Release()
{
	return DxgiSwapchain->Release();
}
#pragma endregion
