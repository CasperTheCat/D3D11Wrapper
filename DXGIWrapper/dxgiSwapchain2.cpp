#include "dxgiSwapchain2.h"
#include "utils.h"

#pragma region DXGISwapChain2

DXGICustomSwapChain2::DXGICustomSwapChain2(void * swapchain, IUnknown * dev)
{
	// Check the device for hook
	CustomDevice = dynamic_cast<D3D11CustomDevice*>(dev);
	DxgiSwapchain = reinterpret_cast<IDXGISwapChain2*>(swapchain);
}

DXGICustomSwapChain2::DXGICustomSwapChain2(IDXGISwapChain* swapchain, ID3D11Device* dev, D3DObjectManager* glom) :
	CustomDevice(nullptr),
	DxgiSwapchain(reinterpret_cast<IDXGISwapChain2*>(swapchain)),
	m_pGLOM(glom)
{
	auto temp = dynamic_cast<D3D11CustomDevice*>(dev);
	if (temp) { CustomDevice = temp; }
}

HRESULT DXGICustomSwapChain2::SetSourceSize(UINT Width, UINT Height)
{
	return DxgiSwapchain->SetSourceSize(Width, Height);
}

HRESULT DXGICustomSwapChain2::GetSourceSize(UINT* pWidth, UINT* pHeight)
{
	return DxgiSwapchain->GetSourceSize(pWidth, pHeight);
}

HRESULT DXGICustomSwapChain2::SetMaximumFrameLatency(UINT MaxLatency)
{
	return DxgiSwapchain->SetMaximumFrameLatency(MaxLatency);
}

HRESULT DXGICustomSwapChain2::GetMaximumFrameLatency(UINT* pMaxLatency)
{
	return DxgiSwapchain->GetMaximumFrameLatency(pMaxLatency);
}

HANDLE DXGICustomSwapChain2::GetFrameLatencyWaitableObject()
{
	return DxgiSwapchain->GetFrameLatencyWaitableObject();
}

HRESULT DXGICustomSwapChain2::SetMatrixTransform(const DXGI_MATRIX_3X2_F* pMatrix)
{
	return DxgiSwapchain->SetMatrixTransform(pMatrix);
}

HRESULT DXGICustomSwapChain2::GetMatrixTransform(DXGI_MATRIX_3X2_F* pMatrix)
{
	return DxgiSwapchain->GetMatrixTransform(pMatrix);
}
#pragma endregion 

#pragma region DXGISwapChain1
HRESULT DXGICustomSwapChain2::GetDesc1(DXGI_SWAP_CHAIN_DESC1* pDesc)
{
	return DxgiSwapchain->GetDesc1(pDesc);
}

HRESULT DXGICustomSwapChain2::GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pDesc)
{
	return DxgiSwapchain->GetFullscreenDesc(pDesc);
}

HRESULT DXGICustomSwapChain2::GetHwnd(HWND* pHwnd)
{
	return DxgiSwapchain->GetHwnd(pHwnd);
}

HRESULT DXGICustomSwapChain2::GetCoreWindow(const IID& refiid, void** ppUnk)
{
	return DxgiSwapchain->GetCoreWindow(refiid, ppUnk);
}

HRESULT DXGICustomSwapChain2::Present1(UINT SyncInterval, UINT PresentFlags,
	const DXGI_PRESENT_PARAMETERS* pPresentParameters)
{
	if (CustomDevice) CustomDevice->Notify_Present();
	return DxgiSwapchain->Present1(SyncInterval, PresentFlags, pPresentParameters);
}

BOOL DXGICustomSwapChain2::IsTemporaryMonoSupported()
{
	return DxgiSwapchain->IsTemporaryMonoSupported();
}

HRESULT DXGICustomSwapChain2::GetRestrictToOutput(IDXGIOutput** ppRestrictToOutput)
{
	return DxgiSwapchain->GetRestrictToOutput(ppRestrictToOutput);
}

HRESULT DXGICustomSwapChain2::SetBackgroundColor(const DXGI_RGBA* pColor)
{
	return DxgiSwapchain->SetBackgroundColor(pColor);
}

HRESULT DXGICustomSwapChain2::GetBackgroundColor(DXGI_RGBA* pColor)
{
	return DxgiSwapchain->GetBackgroundColor(pColor);
}

HRESULT DXGICustomSwapChain2::SetRotation(DXGI_MODE_ROTATION Rotation)
{
	return DxgiSwapchain->SetRotation(Rotation);
}

HRESULT DXGICustomSwapChain2::GetRotation(DXGI_MODE_ROTATION* pRotation)
{
	return DxgiSwapchain->GetRotation(pRotation);
}
#pragma endregion

#pragma region DXGISwapChain
HRESULT DXGICustomSwapChain2::Present(UINT SyncInterval, UINT Flags)
{
	if (CustomDevice) CustomDevice->Notify_Present();

	return DxgiSwapchain->Present(SyncInterval, Flags);
}

HRESULT DXGICustomSwapChain2::GetBuffer(UINT Buffer, const IID& riid, void** ppSurface)
{
	return DxgiSwapchain->GetBuffer(Buffer, riid, ppSurface);
}

HRESULT DXGICustomSwapChain2::SetFullscreenState(BOOL Fullscreen, IDXGIOutput* pTarget)
{
	return DxgiSwapchain->SetFullscreenState(Fullscreen, pTarget);
}

HRESULT DXGICustomSwapChain2::GetFullscreenState(BOOL* pFullscreen, IDXGIOutput** ppTarget)
{
	return DxgiSwapchain->GetFullscreenState(pFullscreen, ppTarget);
}

HRESULT DXGICustomSwapChain2::GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc)
{
	return DxgiSwapchain->GetDesc(pDesc);
}

HRESULT DXGICustomSwapChain2::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat,
	UINT SwapChainFlags)
{
	return DxgiSwapchain->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT DXGICustomSwapChain2::ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters)
{
	return DxgiSwapchain->ResizeTarget(pNewTargetParameters);
}

HRESULT DXGICustomSwapChain2::GetContainingOutput(IDXGIOutput** ppOutput)
{
	return DxgiSwapchain->GetContainingOutput(ppOutput);
}

HRESULT DXGICustomSwapChain2::GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats)
{
	return DxgiSwapchain->GetFrameStatistics(pStats);
}

HRESULT DXGICustomSwapChain2::GetLastPresentCount(UINT* pLastPresentCount)
{
	return DxgiSwapchain->GetLastPresentCount(pLastPresentCount);
}
#pragma endregion

#pragma region SubObject
HRESULT DXGICustomSwapChain2::GetDevice(const IID& riid, void** ppDevice)
{
	auto ret = DxgiSwapchain->GetDevice(riid, ppDevice);
	if (CustomDevice) { *ppDevice = CustomDevice; }
	return ret;
}
#pragma endregion

#pragma region Object	
HRESULT DXGICustomSwapChain2::SetPrivateData(const GUID& Name, UINT DataSize, const void* pData)
{
	return DxgiSwapchain->SetPrivateData(Name, DataSize, pData);
}

HRESULT DXGICustomSwapChain2::SetPrivateDataInterface(const GUID& Name, const IUnknown* pUnknown)
{
	return DxgiSwapchain->SetPrivateDataInterface(Name, pUnknown);
}

HRESULT DXGICustomSwapChain2::GetPrivateData(const GUID& Name, UINT* pDataSize, void* pData)
{
	return DxgiSwapchain->GetPrivateData(Name, pDataSize, pData);
}

HRESULT DXGICustomSwapChain2::GetParent(const IID& riid, void** ppParent)
{
	return DxgiSwapchain->GetParent(riid, ppParent);
}
#pragma endregion 

#pragma region IUnknown
HRESULT DXGICustomSwapChain2::QueryInterface(const IID& riid, void** ppvObject)
{
	return DxgiSwapchain->QueryInterface(riid, ppvObject);
}

ULONG DXGICustomSwapChain2::AddRef()
{
	return DxgiSwapchain->AddRef();
}

ULONG DXGICustomSwapChain2::Release()
{
	return DxgiSwapchain->Release();
}
#pragma endregion
