#pragma once
#include "dxgiFactory.h"
#include <fstream>

class DXGICustomFactory1 : public IDXGIFactory1
{
protected:
	IDXGIFactory1 *DxgiFactory;
	DXGIWrapper* m_pLog;
public:
	DXGICustomFactory1(void* factory, DXGIWrapper* log);
	virtual ~DXGICustomFactory1();

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
