#pragma once
#include "dxgiFactory.h"
#include <d3d11_1.h>
#include <fstream>
#include <d3d11_2.h>

class DXGICustomFactory2 : public IDXGIFactory6
{
protected:
	IDXGIFactory3 *DxgiFactory;
	DXGIWrapper* m_pLog;
public:
	DXGICustomFactory2(void* factory, DXGIWrapper* log);
	virtual ~DXGICustomFactory2();

	// Fac6
	virtual HRESULT STDMETHODCALLTYPE EnumAdapterByGpuPreference(
		/* [annotation] */
		_In_  UINT Adapter,
		/* [annotation] */
		_In_  DXGI_GPU_PREFERENCE GpuPreference,
		/* [annotation] */
		_In_  REFIID riid,
		/* [annotation] */
		_COM_Outptr_  void** ppvAdapter);

	// Fac5
	virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport(
		DXGI_FEATURE Feature,
		/* [annotation] */
		_Inout_updates_bytes_(FeatureSupportDataSize)  void* pFeatureSupportData,
		UINT FeatureSupportDataSize);

	// Fac4
	virtual HRESULT STDMETHODCALLTYPE EnumAdapterByLuid(
		/* [annotation] */
		_In_  LUID AdapterLuid,
		/* [annotation] */
		_In_  REFIID riid,
		/* [annotation] */
		_COM_Outptr_  void** ppvAdapter);

	virtual HRESULT STDMETHODCALLTYPE EnumWarpAdapter(
		/* [annotation] */
		_In_  REFIID riid,
		/* [annotation] */
		_COM_Outptr_  void** ppvAdapter);



	// IDXGIFactory3
	virtual UINT STDMETHODCALLTYPE GetCreationFlags(void) override;

	// IDXGIFactory2
	virtual BOOL STDMETHODCALLTYPE IsWindowedStereoEnabled(void) override;

	virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForHwnd(
		/* [annotation][in] */
		_In_  IUnknown *pDevice,
		/* [annotation][in] */
		_In_  HWND hWnd,
		/* [annotation][in] */
		_In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
		/* [annotation][in] */
		_In_opt_  const DXGI_SWAP_CHAIN_FULLSCREEN_DESC *pFullscreenDesc,
		/* [annotation][in] */
		_In_opt_  IDXGIOutput *pRestrictToOutput,
		/* [annotation][out] */
		_COM_Outptr_  IDXGISwapChain1 **ppSwapChain) override;

	virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForCoreWindow(
		/* [annotation][in] */
		_In_  IUnknown *pDevice,
		/* [annotation][in] */
		_In_  IUnknown *pWindow,
		/* [annotation][in] */
		_In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
		/* [annotation][in] */
		_In_opt_  IDXGIOutput *pRestrictToOutput,
		/* [annotation][out] */
		_COM_Outptr_  IDXGISwapChain1 **ppSwapChain) override;

	virtual HRESULT STDMETHODCALLTYPE GetSharedResourceAdapterLuid(
		/* [annotation] */
		_In_  HANDLE hResource,
		/* [annotation] */
		_Out_  LUID *pLuid) override;

	virtual HRESULT STDMETHODCALLTYPE RegisterStereoStatusWindow(
		/* [annotation][in] */
		_In_  HWND WindowHandle,
		/* [annotation][in] */
		_In_  UINT wMsg,
		/* [annotation][out] */
		_Out_  DWORD *pdwCookie) override;

	virtual HRESULT STDMETHODCALLTYPE RegisterStereoStatusEvent(
		/* [annotation][in] */
		_In_  HANDLE hEvent,
		/* [annotation][out] */
		_Out_  DWORD *pdwCookie) override;

	virtual void STDMETHODCALLTYPE UnregisterStereoStatus(
		/* [annotation][in] */
		_In_  DWORD dwCookie) override;

	virtual HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusWindow(
		/* [annotation][in] */
		_In_  HWND WindowHandle,
		/* [annotation][in] */
		_In_  UINT wMsg,
		/* [annotation][out] */
		_Out_  DWORD *pdwCookie) override;

	virtual HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusEvent(
		/* [annotation][in] */
		_In_  HANDLE hEvent,
		/* [annotation][out] */
		_Out_  DWORD *pdwCookie) override;

	virtual void STDMETHODCALLTYPE UnregisterOcclusionStatus(
		/* [annotation][in] */
		_In_  DWORD dwCookie) override;

	virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForComposition(
		/* [annotation][in] */
		_In_  IUnknown *pDevice,
		/* [annotation][in] */
		_In_  const DXGI_SWAP_CHAIN_DESC1 *pDesc,
		/* [annotation][in] */
		_In_opt_  IDXGIOutput *pRestrictToOutput,
		/* [annotation][out] */
		_COM_Outptr_  IDXGISwapChain1 **ppSwapChain) override;




	// IDXGIFactory1
	virtual HRESULT STDMETHODCALLTYPE EnumAdapters1(
		/* [in] */ UINT Adapter,
		/* [annotation][out] */
		_COM_Outptr_  IDXGIAdapter1 **ppAdapter) override;

	virtual BOOL STDMETHODCALLTYPE IsCurrent(void) override;

	// IDXGIFactory

	virtual HRESULT STDMETHODCALLTYPE EnumAdapters(
		/* [in] */ UINT Adapter,
		/* [annotation][out] */
		_COM_Outptr_  IDXGIAdapter **ppAdapter) override;

	virtual HRESULT STDMETHODCALLTYPE MakeWindowAssociation(
		HWND WindowHandle,
		UINT Flags) override;

	virtual HRESULT STDMETHODCALLTYPE GetWindowAssociation(
		/* [annotation][out] */
		_Out_  HWND *pWindowHandle) override;

	virtual HRESULT STDMETHODCALLTYPE CreateSwapChain(
		/* [annotation][in] */
		_In_  IUnknown *pDevice,
		/* [annotation][in] */
		_In_  DXGI_SWAP_CHAIN_DESC *pDesc,
		/* [annotation][out] */
		_COM_Outptr_  IDXGISwapChain **ppSwapChain) override;

	virtual HRESULT STDMETHODCALLTYPE CreateSoftwareAdapter(
		/* [in] */ HMODULE Module,
		/* [annotation][out] */
		_COM_Outptr_  IDXGIAdapter **ppAdapter) override;


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

	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR *__RPC_FAR *ppvObject) override;

	virtual ULONG STDMETHODCALLTYPE AddRef(void) override;

	virtual ULONG STDMETHODCALLTYPE Release(void) override;

};
