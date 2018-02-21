#pragma once

#include <dxgi1_3.h>
#include "../D3D11Wrapper/d3d11Device.h"

class DXGICustomSwapChain2 : public IDXGISwapChain2
{
protected:
	IDXGISwapChain2 * DxgiSwapchain;
	D3D11CustomDevice * CustomDevice;
public:
	DXGICustomSwapChain2(void * swapchain);
	virtual ~DXGICustomSwapChain2() = default;

	#pragma region DXGISwapChain2

	virtual HRESULT STDMETHODCALLTYPE SetSourceSize(
		UINT Width,
		UINT Height) override;

	virtual HRESULT STDMETHODCALLTYPE GetSourceSize(
		/* [annotation][out] */
		_Out_  UINT *pWidth,
		/* [annotation][out] */
		_Out_  UINT *pHeight) override;

	virtual HRESULT STDMETHODCALLTYPE SetMaximumFrameLatency(
		UINT MaxLatency) override;

	virtual HRESULT STDMETHODCALLTYPE GetMaximumFrameLatency(
		/* [annotation][out] */
		_Out_  UINT *pMaxLatency) override;

	virtual HANDLE STDMETHODCALLTYPE GetFrameLatencyWaitableObject(void) override;

	virtual HRESULT STDMETHODCALLTYPE SetMatrixTransform(
		const DXGI_MATRIX_3X2_F *pMatrix) override;

	virtual HRESULT STDMETHODCALLTYPE GetMatrixTransform(
		/* [annotation][out] */
		_Out_  DXGI_MATRIX_3X2_F *pMatrix) override;
#pragma endregion

	#pragma region DXGISwapChain1
	// DXGISwapChain1
	virtual HRESULT STDMETHODCALLTYPE GetDesc1(
		/* [annotation][out] */
		_Out_  DXGI_SWAP_CHAIN_DESC1 *pDesc) override;

	virtual HRESULT STDMETHODCALLTYPE GetFullscreenDesc(
		/* [annotation][out] */
		_Out_  DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pDesc) override;

	virtual HRESULT STDMETHODCALLTYPE GetHwnd(
		/* [annotation][out] */
		_Out_  HWND *pHwnd) override;

	virtual HRESULT STDMETHODCALLTYPE GetCoreWindow(
		/* [annotation][in] */
		_In_  REFIID refiid,
		/* [annotation][out] */
		_COM_Outptr_  void **ppUnk) override;

	virtual HRESULT STDMETHODCALLTYPE Present1(
		/* [in] */ UINT SyncInterval,
		/* [in] */ UINT PresentFlags,
		/* [annotation][in] */
		_In_  const DXGI_PRESENT_PARAMETERS *pPresentParameters) override;

	virtual BOOL STDMETHODCALLTYPE IsTemporaryMonoSupported(void) override;

	virtual HRESULT STDMETHODCALLTYPE GetRestrictToOutput(
		/* [annotation][out] */
		_Out_  IDXGIOutput **ppRestrictToOutput) override;

	virtual HRESULT STDMETHODCALLTYPE SetBackgroundColor(
		/* [annotation][in] */
		_In_  const DXGI_RGBA *pColor) override;

	virtual HRESULT STDMETHODCALLTYPE GetBackgroundColor(
		/* [annotation][out] */
		_Out_  DXGI_RGBA *pColor) override;

	virtual HRESULT STDMETHODCALLTYPE SetRotation(
		/* [annotation][in] */
		_In_  DXGI_MODE_ROTATION Rotation) override;

	virtual HRESULT STDMETHODCALLTYPE GetRotation(
		/* [annotation][out] */
		_Out_  DXGI_MODE_ROTATION *pRotation) override;
#pragma endregion 

	#pragma region DXGISwapChain
	// DXGISwapChain

	virtual HRESULT STDMETHODCALLTYPE Present(
		/* [in] */ UINT SyncInterval,
		/* [in] */ UINT Flags) override;

	virtual HRESULT STDMETHODCALLTYPE GetBuffer(
		/* [in] */ UINT Buffer,
		/* [annotation][in] */
		_In_  REFIID riid,
		/* [annotation][out][in] */
		_COM_Outptr_  void **ppSurface) override;

	virtual HRESULT STDMETHODCALLTYPE SetFullscreenState(
		/* [in] */ BOOL Fullscreen,
		/* [annotation][in] */
		_In_opt_  IDXGIOutput *pTarget) override;

	virtual HRESULT STDMETHODCALLTYPE GetFullscreenState(
		/* [annotation][out] */
		_Out_opt_  BOOL *pFullscreen,
		/* [annotation][out] */
		_COM_Outptr_opt_result_maybenull_  IDXGIOutput **ppTarget) override;

	virtual HRESULT STDMETHODCALLTYPE GetDesc(
		/* [annotation][out] */
		_Out_  DXGI_SWAP_CHAIN_DESC *pDesc) override;

	virtual HRESULT STDMETHODCALLTYPE ResizeBuffers(
		/* [in] */ UINT BufferCount,
		/* [in] */ UINT Width,
		/* [in] */ UINT Height,
		/* [in] */ DXGI_FORMAT NewFormat,
		/* [in] */ UINT SwapChainFlags) override;

	virtual HRESULT STDMETHODCALLTYPE ResizeTarget(
		/* [annotation][in] */
		_In_  const DXGI_MODE_DESC *pNewTargetParameters) override;

	virtual HRESULT STDMETHODCALLTYPE GetContainingOutput(
		/* [annotation][out] */
		_COM_Outptr_  IDXGIOutput **ppOutput) override;

	virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics(
		/* [annotation][out] */
		_Out_  DXGI_FRAME_STATISTICS *pStats) override;

	virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount(
		/* [annotation][out] */
		_Out_  UINT *pLastPresentCount) override;
#pragma endregion

	#pragma region DXGISubObject
	virtual HRESULT STDMETHODCALLTYPE GetDevice(
		/* [annotation][in] */
		_In_  REFIID riid,
		/* [annotation][retval][out] */
		_COM_Outptr_  void **ppDevice) override;
	#pragma endregion

	#pragma region DXGIObject
	// IDXGIObject
	virtual HRESULT STDMETHODCALLTYPE SetPrivateData(
		/* [annotation][in] */
		_In_  REFGUID Name,
		/* [in] */ UINT DataSize,
		/* [annotation][in] */
		_In_reads_bytes_(DataSize)  const void *pData) override;

	virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(
		/* [annotation][in] */
		_In_  REFGUID Name,
		/* [annotation][in] */
		_In_opt_  const IUnknown *pUnknown) override;

	virtual HRESULT STDMETHODCALLTYPE GetPrivateData(
		/* [annotation][in] */
		_In_  REFGUID Name,
		/* [annotation][out][in] */
		_Inout_  UINT *pDataSize,
		/* [annotation][out] */
		_Out_writes_bytes_(*pDataSize)  void *pData) override;

	virtual HRESULT STDMETHODCALLTYPE GetParent(
		/* [annotation][in] */
		_In_  REFIID riid,
		/* [annotation][retval][out] */
		_COM_Outptr_  void **ppParent) override;
	#pragma endregion

	#pragma region IUnknown
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject) override;

	virtual ULONG STDMETHODCALLTYPE AddRef(void) override;

	virtual ULONG STDMETHODCALLTYPE Release(void) override;
	#pragma endregion 
};
