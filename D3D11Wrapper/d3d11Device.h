#pragma once
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_2.h>
#include <d3d11_3.h>
#include <d3d11_4.h>
#include <d3d11on12.h>
#include <fstream>

class D3D11CustomDevice : public ID3D11Device
{
protected:
	ID3D11Device *m_d3dDevice;


public:
	D3D11CustomDevice(ID3D11Device *dev, ID3D11Device ***ret);

	//virtual HRESULT STDMETHODCALLTYPE CreateBuffer(
	//	/* [annotation] */
	//	_In_  const D3D11_BUFFER_DESC *pDesc,
	//	/* [annotation] */
	//	_In_opt_  const D3D11_SUBRESOURCE_DATA *pInitialData,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11Buffer **ppBuffer) override;

	//virtual HRESULT STDMETHODCALLTYPE CreateTexture1D(
	//	/* [annotation] */
	//	_In_  const D3D11_TEXTURE1D_DESC *pDesc,
	//	/* [annotation] */
	//	_In_reads_opt_(_Inexpressible_(pDesc->MipLevels * pDesc->ArraySize))  const D3D11_SUBRESOURCE_DATA *pInitialData,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11Texture1D **ppTexture1D);

	//virtual HRESULT STDMETHODCALLTYPE CreateTexture2D(
	//	/* [annotation] */
	//	_In_  const D3D11_TEXTURE2D_DESC *pDesc,
	//	/* [annotation] */
	//	_In_reads_opt_(_Inexpressible_(pDesc->MipLevels * pDesc->ArraySize))  const D3D11_SUBRESOURCE_DATA *pInitialData,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11Texture2D **ppTexture2D) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateTexture3D(
	//	/* [annotation] */
	//	_In_  const D3D11_TEXTURE3D_DESC *pDesc,
	//	/* [annotation] */
	//	_In_reads_opt_(_Inexpressible_(pDesc->MipLevels))  const D3D11_SUBRESOURCE_DATA *pInitialData,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11Texture3D **ppTexture3D) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateShaderResourceView(
	//	/* [annotation] */
	//	_In_  ID3D11Resource *pResource,
	//	/* [annotation] */
	//	_In_opt_  const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11ShaderResourceView **ppSRView) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateUnorderedAccessView(
	//	/* [annotation] */
	//	_In_  ID3D11Resource *pResource,
	//	/* [annotation] */
	//	_In_opt_  const D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11UnorderedAccessView **ppUAView) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateRenderTargetView(
	//	/* [annotation] */
	//	_In_  ID3D11Resource *pResource,
	//	/* [annotation] */
	//	_In_opt_  const D3D11_RENDER_TARGET_VIEW_DESC *pDesc,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11RenderTargetView **ppRTView) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilView(
	//	/* [annotation] */
	//	_In_  ID3D11Resource *pResource,
	//	/* [annotation] */
	//	_In_opt_  const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11DepthStencilView **ppDepthStencilView) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateInputLayout(
	//	/* [annotation] */
	//	_In_reads_(NumElements)  const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
	//	/* [annotation] */
	//	_In_range_(0, D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT)  UINT NumElements,
	//	/* [annotation] */
	//	_In_reads_(BytecodeLength)  const void *pShaderBytecodeWithInputSignature,
	//	/* [annotation] */
	//	_In_  SIZE_T BytecodeLength,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11InputLayout **ppInputLayout) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateVertexShader(
	//	/* [annotation] */
	//	_In_reads_(BytecodeLength)  const void *pShaderBytecode,
	//	/* [annotation] */
	//	_In_  SIZE_T BytecodeLength,
	//	/* [annotation] */
	//	_In_opt_  ID3D11ClassLinkage *pClassLinkage,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11VertexShader **ppVertexShader) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateGeometryShader(
	//	/* [annotation] */
	//	_In_reads_(BytecodeLength)  const void *pShaderBytecode,
	//	/* [annotation] */
	//	_In_  SIZE_T BytecodeLength,
	//	/* [annotation] */
	//	_In_opt_  ID3D11ClassLinkage *pClassLinkage,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11GeometryShader **ppGeometryShader) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateGeometryShaderWithStreamOutput(
	//	/* [annotation] */
	//	_In_reads_(BytecodeLength)  const void *pShaderBytecode,
	//	/* [annotation] */
	//	_In_  SIZE_T BytecodeLength,
	//	/* [annotation] */
	//	_In_reads_opt_(NumEntries)  const D3D11_SO_DECLARATION_ENTRY *pSODeclaration,
	//	/* [annotation] */
	//	_In_range_(0, D3D11_SO_STREAM_COUNT * D3D11_SO_OUTPUT_COMPONENT_COUNT)  UINT NumEntries,
	//	/* [annotation] */
	//	_In_reads_opt_(NumStrides)  const UINT *pBufferStrides,
	//	/* [annotation] */
	//	_In_range_(0, D3D11_SO_BUFFER_SLOT_COUNT)  UINT NumStrides,
	//	/* [annotation] */
	//	_In_  UINT RasterizedStream,
	//	/* [annotation] */
	//	_In_opt_  ID3D11ClassLinkage *pClassLinkage,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11GeometryShader **ppGeometryShader) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreatePixelShader(
	//	/* [annotation] */
	//	_In_reads_(BytecodeLength)  const void *pShaderBytecode,
	//	/* [annotation] */
	//	_In_  SIZE_T BytecodeLength,
	//	/* [annotation] */
	//	_In_opt_  ID3D11ClassLinkage *pClassLinkage,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11PixelShader **ppPixelShader) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateHullShader(
	//	/* [annotation] */
	//	_In_reads_(BytecodeLength)  const void *pShaderBytecode,
	//	/* [annotation] */
	//	_In_  SIZE_T BytecodeLength,
	//	/* [annotation] */
	//	_In_opt_  ID3D11ClassLinkage *pClassLinkage,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11HullShader **ppHullShader) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateDomainShader(
	//	/* [annotation] */
	//	_In_reads_(BytecodeLength)  const void *pShaderBytecode,
	//	/* [annotation] */
	//	_In_  SIZE_T BytecodeLength,
	//	/* [annotation] */
	//	_In_opt_  ID3D11ClassLinkage *pClassLinkage,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11DomainShader **ppDomainShader) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateComputeShader(
	//	/* [annotation] */
	//	_In_reads_(BytecodeLength)  const void *pShaderBytecode,
	//	/* [annotation] */
	//	_In_  SIZE_T BytecodeLength,
	//	/* [annotation] */
	//	_In_opt_  ID3D11ClassLinkage *pClassLinkage,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11ComputeShader **ppComputeShader) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateClassLinkage(
	//	/* [annotation] */
	//	_COM_Outptr_  ID3D11ClassLinkage **ppLinkage) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateBlendState(
	//	/* [annotation] */
	//	_In_  const D3D11_BLEND_DESC *pBlendStateDesc,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11BlendState **ppBlendState) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilState(
	//	/* [annotation] */
	//	_In_  const D3D11_DEPTH_STENCIL_DESC *pDepthStencilDesc,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11DepthStencilState **ppDepthStencilState) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState(
	//	/* [annotation] */
	//	_In_  const D3D11_RASTERIZER_DESC *pRasterizerDesc,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11RasterizerState **ppRasterizerState) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateSamplerState(
	//	/* [annotation] */
	//	_In_  const D3D11_SAMPLER_DESC *pSamplerDesc,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11SamplerState **ppSamplerState) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateQuery(
	//	/* [annotation] */
	//	_In_  const D3D11_QUERY_DESC *pQueryDesc,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11Query **ppQuery) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreatePredicate(
	//	/* [annotation] */
	//	_In_  const D3D11_QUERY_DESC *pPredicateDesc,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11Predicate **ppPredicate) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateCounter(
	//	/* [annotation] */
	//	_In_  const D3D11_COUNTER_DESC *pCounterDesc,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11Counter **ppCounter) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext(
	//	UINT ContextFlags,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  ID3D11DeviceContext **ppDeferredContext) = 0;

	//virtual HRESULT STDMETHODCALLTYPE OpenSharedResource(
	//	/* [annotation] */
	//	_In_  HANDLE hResource,
	//	/* [annotation] */
	//	_In_  REFIID ReturnedInterface,
	//	/* [annotation] */
	//	_COM_Outptr_opt_  void **ppResource) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CheckFormatSupport(
	//	/* [annotation] */
	//	_In_  DXGI_FORMAT Format,
	//	/* [annotation] */
	//	_Out_  UINT *pFormatSupport) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CheckMultisampleQualityLevels(
	//	/* [annotation] */
	//	_In_  DXGI_FORMAT Format,
	//	/* [annotation] */
	//	_In_  UINT SampleCount,
	//	/* [annotation] */
	//	_Out_  UINT *pNumQualityLevels) = 0;

	//virtual void STDMETHODCALLTYPE CheckCounterInfo(
	//	/* [annotation] */
	//	_Out_  D3D11_COUNTER_INFO *pCounterInfo) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CheckCounter(
	//	/* [annotation] */
	//	_In_  const D3D11_COUNTER_DESC *pDesc,
	//	/* [annotation] */
	//	_Out_  D3D11_COUNTER_TYPE *pType,
	//	/* [annotation] */
	//	_Out_  UINT *pActiveCounters,
	//	/* [annotation] */
	//	_Out_writes_opt_(*pNameLength)  LPSTR szName,
	//	/* [annotation] */
	//	_Inout_opt_  UINT *pNameLength,
	//	/* [annotation] */
	//	_Out_writes_opt_(*pUnitsLength)  LPSTR szUnits,
	//	/* [annotation] */
	//	_Inout_opt_  UINT *pUnitsLength,
	//	/* [annotation] */
	//	_Out_writes_opt_(*pDescriptionLength)  LPSTR szDescription,
	//	/* [annotation] */
	//	_Inout_opt_  UINT *pDescriptionLength) = 0;

	//virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport(
	//	D3D11_FEATURE Feature,
	//	/* [annotation] */
	//	_Out_writes_bytes_(FeatureSupportDataSize)  void *pFeatureSupportData,
	//	UINT FeatureSupportDataSize) = 0;

	//virtual HRESULT STDMETHODCALLTYPE GetPrivateData(
	//	/* [annotation] */
	//	_In_  REFGUID guid,
	//	/* [annotation] */
	//	_Inout_  UINT *pDataSize,
	//	/* [annotation] */
	//	_Out_writes_bytes_opt_(*pDataSize)  void *pData) = 0;

	//virtual HRESULT STDMETHODCALLTYPE SetPrivateData(
	//	/* [annotation] */
	//	_In_  REFGUID guid,
	//	/* [annotation] */
	//	_In_  UINT DataSize,
	//	/* [annotation] */
	//	_In_reads_bytes_opt_(DataSize)  const void *pData) = 0;

	//virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(
	//	/* [annotation] */
	//	_In_  REFGUID guid,
	//	/* [annotation] */
	//	_In_opt_  const IUnknown *pData) = 0;

	//virtual D3D_FEATURE_LEVEL STDMETHODCALLTYPE GetFeatureLevel(void) = 0;

	//virtual UINT STDMETHODCALLTYPE GetCreationFlags(void) = 0;

	//virtual HRESULT STDMETHODCALLTYPE GetDeviceRemovedReason(void) = 0;

	//virtual void STDMETHODCALLTYPE GetImmediateContext(
	//	/* [annotation] */
	//	_Outptr_  ID3D11DeviceContext **ppImmediateContext) = 0;

	//virtual HRESULT STDMETHODCALLTYPE SetExceptionMode(
	//	UINT RaiseFlags) = 0;

	//virtual UINT STDMETHODCALLTYPE GetExceptionMode(void) = 0;

};
