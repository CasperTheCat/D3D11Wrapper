#pragma once
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_2.h>
#include <d3d11_3.h>
#include <d3d11_4.h>
#include <d3d11on12.h>
#include <fstream>

class D3D11CustomContext : public ID3D11DeviceContext
{
protected:
	ID3D11DeviceContext *m_devContext;

public:
	D3D11CustomContext(ID3D11DeviceContext *dev, ID3D11DeviceContext ***ret);


	void STDMETHODCALLTYPE VSSetConstantBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_In_reads_opt_(NumBuffers)  ID3D11Buffer *const *ppConstantBuffers) override;

	void STDMETHODCALLTYPE PSSetShaderResources(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumViews,
		/* [annotation] */
		_In_reads_opt_(NumViews)  ID3D11ShaderResourceView *const *ppShaderResourceViews) override;

	void STDMETHODCALLTYPE PSSetShader(
		/* [annotation] */
		_In_opt_  ID3D11PixelShader *pPixelShader,
		/* [annotation] */
		_In_reads_opt_(NumClassInstances)  ID3D11ClassInstance *const *ppClassInstances,
		UINT NumClassInstances) override;

	void STDMETHODCALLTYPE PSSetSamplers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot)  UINT NumSamplers,
		/* [annotation] */
		_In_reads_opt_(NumSamplers)  ID3D11SamplerState *const *ppSamplers) override = 0;

	void STDMETHODCALLTYPE VSSetShader(
		/* [annotation] */
		_In_opt_  ID3D11VertexShader *pVertexShader,
		/* [annotation] */
		_In_reads_opt_(NumClassInstances)  ID3D11ClassInstance *const *ppClassInstances,
		UINT NumClassInstances) override;

	void STDMETHODCALLTYPE DrawIndexed(
		/* [annotation] */
		_In_  UINT IndexCount,
		/* [annotation] */
		_In_  UINT StartIndexLocation,
		/* [annotation] */
		_In_  INT BaseVertexLocation) override;

	void STDMETHODCALLTYPE Draw(
		/* [annotation] */
		_In_  UINT VertexCount,
		/* [annotation] */
		_In_  UINT StartVertexLocation) override;

	HRESULT STDMETHODCALLTYPE Map(
		/* [annotation] */
		_In_  ID3D11Resource *pResource,
		/* [annotation] */
		_In_  UINT Subresource,
		/* [annotation] */
		_In_  D3D11_MAP MapType,
		/* [annotation] */
		_In_  UINT MapFlags,
		/* [annotation] */
		_Out_opt_  D3D11_MAPPED_SUBRESOURCE *pMappedResource) override;

	void STDMETHODCALLTYPE Unmap(
		/* [annotation] */
		_In_  ID3D11Resource *pResource,
		/* [annotation] */
		_In_  UINT Subresource) override;

	void STDMETHODCALLTYPE PSSetConstantBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_In_reads_opt_(NumBuffers)  ID3D11Buffer *const *ppConstantBuffers) override;

	void STDMETHODCALLTYPE IASetInputLayout(
		/* [annotation] */
		_In_opt_  ID3D11InputLayout *pInputLayout) override;

	void STDMETHODCALLTYPE IASetVertexBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_In_reads_opt_(NumBuffers)  ID3D11Buffer *const *ppVertexBuffers,
		/* [annotation] */
		_In_reads_opt_(NumBuffers)  const UINT *pStrides,
		/* [annotation] */
		_In_reads_opt_(NumBuffers)  const UINT *pOffsets) override;

	void STDMETHODCALLTYPE IASetIndexBuffer(
		/* [annotation] */
		_In_opt_  ID3D11Buffer *pIndexBuffer,
		/* [annotation] */
		_In_  DXGI_FORMAT Format,
		/* [annotation] */
		_In_  UINT Offset) override;

	void STDMETHODCALLTYPE DrawIndexedInstanced(
		/* [annotation] */
		_In_  UINT IndexCountPerInstance,
		/* [annotation] */
		_In_  UINT InstanceCount,
		/* [annotation] */
		_In_  UINT StartIndexLocation,
		/* [annotation] */
		_In_  INT BaseVertexLocation,
		/* [annotation] */
		_In_  UINT StartInstanceLocation) override;

	void STDMETHODCALLTYPE DrawInstanced(
		/* [annotation] */
		_In_  UINT VertexCountPerInstance,
		/* [annotation] */
		_In_  UINT InstanceCount,
		/* [annotation] */
		_In_  UINT StartVertexLocation,
		/* [annotation] */
		_In_  UINT StartInstanceLocation) override;

	void STDMETHODCALLTYPE GSSetConstantBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_In_reads_opt_(NumBuffers)  ID3D11Buffer *const *ppConstantBuffers) override;

	void STDMETHODCALLTYPE GSSetShader(
		/* [annotation] */
		_In_opt_  ID3D11GeometryShader *pShader,
		/* [annotation] */
		_In_reads_opt_(NumClassInstances)  ID3D11ClassInstance *const *ppClassInstances,
		UINT NumClassInstances) override;

	void STDMETHODCALLTYPE IASetPrimitiveTopology(
		/* [annotation] */
		_In_  D3D11_PRIMITIVE_TOPOLOGY Topology) override;

	void STDMETHODCALLTYPE VSSetShaderResources(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumViews,
		/* [annotation] */
		_In_reads_opt_(NumViews)  ID3D11ShaderResourceView *const *ppShaderResourceViews) override;

	void STDMETHODCALLTYPE VSSetSamplers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot)  UINT NumSamplers,
		/* [annotation] */
		_In_reads_opt_(NumSamplers)  ID3D11SamplerState *const *ppSamplers) override;

	void STDMETHODCALLTYPE Begin(
		/* [annotation] */
		_In_  ID3D11Asynchronous *pAsync) override;

	virtual void STDMETHODCALLTYPE End(
		/* [annotation] */
		_In_  ID3D11Asynchronous *pAsync) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetData(
		/* [annotation] */
		_In_  ID3D11Asynchronous *pAsync,
		/* [annotation] */
		_Out_writes_bytes_opt_(DataSize)  void *pData,
		/* [annotation] */
		_In_  UINT DataSize,
		/* [annotation] */
		_In_  UINT GetDataFlags) = 0;

	virtual void STDMETHODCALLTYPE SetPredication(
		/* [annotation] */
		_In_opt_  ID3D11Predicate *pPredicate,
		/* [annotation] */
		_In_  BOOL PredicateValue) = 0;

	virtual void STDMETHODCALLTYPE GSSetShaderResources(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumViews,
		/* [annotation] */
		_In_reads_opt_(NumViews)  ID3D11ShaderResourceView *const *ppShaderResourceViews) = 0;

	virtual void STDMETHODCALLTYPE GSSetSamplers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot)  UINT NumSamplers,
		/* [annotation] */
		_In_reads_opt_(NumSamplers)  ID3D11SamplerState *const *ppSamplers) = 0;

	virtual void STDMETHODCALLTYPE OMSetRenderTargets(
		/* [annotation] */
		_In_range_(0, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)  UINT NumViews,
		/* [annotation] */
		_In_reads_opt_(NumViews)  ID3D11RenderTargetView *const *ppRenderTargetViews,
		/* [annotation] */
		_In_opt_  ID3D11DepthStencilView *pDepthStencilView) = 0;

	virtual void STDMETHODCALLTYPE OMSetRenderTargetsAndUnorderedAccessViews(
		/* [annotation] */
		_In_  UINT NumRTVs,
		/* [annotation] */
		_In_reads_opt_(NumRTVs)  ID3D11RenderTargetView *const *ppRenderTargetViews,
		/* [annotation] */
		_In_opt_  ID3D11DepthStencilView *pDepthStencilView,
		/* [annotation] */
		_In_range_(0, D3D11_1_UAV_SLOT_COUNT - 1)  UINT UAVStartSlot,
		/* [annotation] */
		_In_  UINT NumUAVs,
		/* [annotation] */
		_In_reads_opt_(NumUAVs)  ID3D11UnorderedAccessView *const *ppUnorderedAccessViews,
		/* [annotation] */
		_In_reads_opt_(NumUAVs)  const UINT *pUAVInitialCounts) = 0;

	virtual void STDMETHODCALLTYPE OMSetBlendState(
		/* [annotation] */
		_In_opt_  ID3D11BlendState *pBlendState,
		/* [annotation] */
		_In_opt_  const FLOAT BlendFactor[4],
		/* [annotation] */
		_In_  UINT SampleMask) = 0;

	virtual void STDMETHODCALLTYPE OMSetDepthStencilState(
		/* [annotation] */
		_In_opt_  ID3D11DepthStencilState *pDepthStencilState,
		/* [annotation] */
		_In_  UINT StencilRef) = 0;

	virtual void STDMETHODCALLTYPE SOSetTargets(
		/* [annotation] */
		_In_range_(0, D3D11_SO_BUFFER_SLOT_COUNT)  UINT NumBuffers,
		/* [annotation] */
		_In_reads_opt_(NumBuffers)  ID3D11Buffer *const *ppSOTargets,
		/* [annotation] */
		_In_reads_opt_(NumBuffers)  const UINT *pOffsets) = 0;

	virtual void STDMETHODCALLTYPE DrawAuto(void) = 0;

	virtual void STDMETHODCALLTYPE DrawIndexedInstancedIndirect(
		/* [annotation] */
		_In_  ID3D11Buffer *pBufferForArgs,
		/* [annotation] */
		_In_  UINT AlignedByteOffsetForArgs) = 0;

	virtual void STDMETHODCALLTYPE DrawInstancedIndirect(
		/* [annotation] */
		_In_  ID3D11Buffer *pBufferForArgs,
		/* [annotation] */
		_In_  UINT AlignedByteOffsetForArgs) = 0;

	virtual void STDMETHODCALLTYPE Dispatch(
		/* [annotation] */
		_In_  UINT ThreadGroupCountX,
		/* [annotation] */
		_In_  UINT ThreadGroupCountY,
		/* [annotation] */
		_In_  UINT ThreadGroupCountZ) = 0;

	virtual void STDMETHODCALLTYPE DispatchIndirect(
		/* [annotation] */
		_In_  ID3D11Buffer *pBufferForArgs,
		/* [annotation] */
		_In_  UINT AlignedByteOffsetForArgs) = 0;

	virtual void STDMETHODCALLTYPE RSSetState(
		/* [annotation] */
		_In_opt_  ID3D11RasterizerState *pRasterizerState) = 0;

	virtual void STDMETHODCALLTYPE RSSetViewports(
		/* [annotation] */
		_In_range_(0, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)  UINT NumViewports,
		/* [annotation] */
		_In_reads_opt_(NumViewports)  const D3D11_VIEWPORT *pViewports) = 0;

	virtual void STDMETHODCALLTYPE RSSetScissorRects(
		/* [annotation] */
		_In_range_(0, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)  UINT NumRects,
		/* [annotation] */
		_In_reads_opt_(NumRects)  const D3D11_RECT *pRects) = 0;

	virtual void STDMETHODCALLTYPE CopySubresourceRegion(
		/* [annotation] */
		_In_  ID3D11Resource *pDstResource,
		/* [annotation] */
		_In_  UINT DstSubresource,
		/* [annotation] */
		_In_  UINT DstX,
		/* [annotation] */
		_In_  UINT DstY,
		/* [annotation] */
		_In_  UINT DstZ,
		/* [annotation] */
		_In_  ID3D11Resource *pSrcResource,
		/* [annotation] */
		_In_  UINT SrcSubresource,
		/* [annotation] */
		_In_opt_  const D3D11_BOX *pSrcBox) = 0;

	virtual void STDMETHODCALLTYPE CopyResource(
		/* [annotation] */
		_In_  ID3D11Resource *pDstResource,
		/* [annotation] */
		_In_  ID3D11Resource *pSrcResource) = 0;

	virtual void STDMETHODCALLTYPE UpdateSubresource(
		/* [annotation] */
		_In_  ID3D11Resource *pDstResource,
		/* [annotation] */
		_In_  UINT DstSubresource,
		/* [annotation] */
		_In_opt_  const D3D11_BOX *pDstBox,
		/* [annotation] */
		_In_  const void *pSrcData,
		/* [annotation] */
		_In_  UINT SrcRowPitch,
		/* [annotation] */
		_In_  UINT SrcDepthPitch) = 0;

	virtual void STDMETHODCALLTYPE CopyStructureCount(
		/* [annotation] */
		_In_  ID3D11Buffer *pDstBuffer,
		/* [annotation] */
		_In_  UINT DstAlignedByteOffset,
		/* [annotation] */
		_In_  ID3D11UnorderedAccessView *pSrcView) = 0;

	virtual void STDMETHODCALLTYPE ClearRenderTargetView(
		/* [annotation] */
		_In_  ID3D11RenderTargetView *pRenderTargetView,
		/* [annotation] */
		_In_  const FLOAT ColorRGBA[4]) = 0;

	virtual void STDMETHODCALLTYPE ClearUnorderedAccessViewUint(
		/* [annotation] */
		_In_  ID3D11UnorderedAccessView *pUnorderedAccessView,
		/* [annotation] */
		_In_  const UINT Values[4]) = 0;

	virtual void STDMETHODCALLTYPE ClearUnorderedAccessViewFloat(
		/* [annotation] */
		_In_  ID3D11UnorderedAccessView *pUnorderedAccessView,
		/* [annotation] */
		_In_  const FLOAT Values[4]) = 0;

	virtual void STDMETHODCALLTYPE ClearDepthStencilView(
		/* [annotation] */
		_In_  ID3D11DepthStencilView *pDepthStencilView,
		/* [annotation] */
		_In_  UINT ClearFlags,
		/* [annotation] */
		_In_  FLOAT Depth,
		/* [annotation] */
		_In_  UINT8 Stencil) = 0;

	virtual void STDMETHODCALLTYPE GenerateMips(
		/* [annotation] */
		_In_  ID3D11ShaderResourceView *pShaderResourceView) = 0;

	virtual void STDMETHODCALLTYPE SetResourceMinLOD(
		/* [annotation] */
		_In_  ID3D11Resource *pResource,
		FLOAT MinLOD) = 0;

	virtual FLOAT STDMETHODCALLTYPE GetResourceMinLOD(
		/* [annotation] */
		_In_  ID3D11Resource *pResource) = 0;

	virtual void STDMETHODCALLTYPE ResolveSubresource(
		/* [annotation] */
		_In_  ID3D11Resource *pDstResource,
		/* [annotation] */
		_In_  UINT DstSubresource,
		/* [annotation] */
		_In_  ID3D11Resource *pSrcResource,
		/* [annotation] */
		_In_  UINT SrcSubresource,
		/* [annotation] */
		_In_  DXGI_FORMAT Format) = 0;

	virtual void STDMETHODCALLTYPE ExecuteCommandList(
		/* [annotation] */
		_In_  ID3D11CommandList *pCommandList,
		BOOL RestoreContextState) = 0;

	virtual void STDMETHODCALLTYPE HSSetShaderResources(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumViews,
		/* [annotation] */
		_In_reads_opt_(NumViews)  ID3D11ShaderResourceView *const *ppShaderResourceViews) = 0;

	virtual void STDMETHODCALLTYPE HSSetShader(
		/* [annotation] */
		_In_opt_  ID3D11HullShader *pHullShader,
		/* [annotation] */
		_In_reads_opt_(NumClassInstances)  ID3D11ClassInstance *const *ppClassInstances,
		UINT NumClassInstances) = 0;

	virtual void STDMETHODCALLTYPE HSSetSamplers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot)  UINT NumSamplers,
		/* [annotation] */
		_In_reads_opt_(NumSamplers)  ID3D11SamplerState *const *ppSamplers) = 0;

	virtual void STDMETHODCALLTYPE HSSetConstantBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_In_reads_opt_(NumBuffers)  ID3D11Buffer *const *ppConstantBuffers) = 0;

	virtual void STDMETHODCALLTYPE DSSetShaderResources(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumViews,
		/* [annotation] */
		_In_reads_opt_(NumViews)  ID3D11ShaderResourceView *const *ppShaderResourceViews) = 0;

	virtual void STDMETHODCALLTYPE DSSetShader(
		/* [annotation] */
		_In_opt_  ID3D11DomainShader *pDomainShader,
		/* [annotation] */
		_In_reads_opt_(NumClassInstances)  ID3D11ClassInstance *const *ppClassInstances,
		UINT NumClassInstances) = 0;

	virtual void STDMETHODCALLTYPE DSSetSamplers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot)  UINT NumSamplers,
		/* [annotation] */
		_In_reads_opt_(NumSamplers)  ID3D11SamplerState *const *ppSamplers) = 0;

	virtual void STDMETHODCALLTYPE DSSetConstantBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_In_reads_opt_(NumBuffers)  ID3D11Buffer *const *ppConstantBuffers) = 0;

	virtual void STDMETHODCALLTYPE CSSetShaderResources(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumViews,
		/* [annotation] */
		_In_reads_opt_(NumViews)  ID3D11ShaderResourceView *const *ppShaderResourceViews) = 0;

	virtual void STDMETHODCALLTYPE CSSetUnorderedAccessViews(
		/* [annotation] */
		_In_range_(0, D3D11_1_UAV_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_1_UAV_SLOT_COUNT - StartSlot)  UINT NumUAVs,
		/* [annotation] */
		_In_reads_opt_(NumUAVs)  ID3D11UnorderedAccessView *const *ppUnorderedAccessViews,
		/* [annotation] */
		_In_reads_opt_(NumUAVs)  const UINT *pUAVInitialCounts) = 0;

	virtual void STDMETHODCALLTYPE CSSetShader(
		/* [annotation] */
		_In_opt_  ID3D11ComputeShader *pComputeShader,
		/* [annotation] */
		_In_reads_opt_(NumClassInstances)  ID3D11ClassInstance *const *ppClassInstances,
		UINT NumClassInstances) = 0;

	virtual void STDMETHODCALLTYPE CSSetSamplers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot)  UINT NumSamplers,
		/* [annotation] */
		_In_reads_opt_(NumSamplers)  ID3D11SamplerState *const *ppSamplers) = 0;

	virtual void STDMETHODCALLTYPE CSSetConstantBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_In_reads_opt_(NumBuffers)  ID3D11Buffer *const *ppConstantBuffers) = 0;

	virtual void STDMETHODCALLTYPE VSGetConstantBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_Out_writes_opt_(NumBuffers)  ID3D11Buffer **ppConstantBuffers) = 0;

	virtual void STDMETHODCALLTYPE PSGetShaderResources(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumViews,
		/* [annotation] */
		_Out_writes_opt_(NumViews)  ID3D11ShaderResourceView **ppShaderResourceViews) = 0;

	virtual void STDMETHODCALLTYPE PSGetShader(
		/* [annotation] */
		_Outptr_result_maybenull_  ID3D11PixelShader **ppPixelShader,
		/* [annotation] */
		_Out_writes_opt_(*pNumClassInstances)  ID3D11ClassInstance **ppClassInstances,
		/* [annotation] */
		_Inout_opt_  UINT *pNumClassInstances) = 0;

	virtual void STDMETHODCALLTYPE PSGetSamplers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot)  UINT NumSamplers,
		/* [annotation] */
		_Out_writes_opt_(NumSamplers)  ID3D11SamplerState **ppSamplers) = 0;

	virtual void STDMETHODCALLTYPE VSGetShader(
		/* [annotation] */
		_Outptr_result_maybenull_  ID3D11VertexShader **ppVertexShader,
		/* [annotation] */
		_Out_writes_opt_(*pNumClassInstances)  ID3D11ClassInstance **ppClassInstances,
		/* [annotation] */
		_Inout_opt_  UINT *pNumClassInstances) = 0;

	virtual void STDMETHODCALLTYPE PSGetConstantBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_Out_writes_opt_(NumBuffers)  ID3D11Buffer **ppConstantBuffers) = 0;

	virtual void STDMETHODCALLTYPE IAGetInputLayout(
		/* [annotation] */
		_Outptr_result_maybenull_  ID3D11InputLayout **ppInputLayout) = 0;

	virtual void STDMETHODCALLTYPE IAGetVertexBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_Out_writes_opt_(NumBuffers)  ID3D11Buffer **ppVertexBuffers,
		/* [annotation] */
		_Out_writes_opt_(NumBuffers)  UINT *pStrides,
		/* [annotation] */
		_Out_writes_opt_(NumBuffers)  UINT *pOffsets) = 0;

	virtual void STDMETHODCALLTYPE IAGetIndexBuffer(
		/* [annotation] */
		_Outptr_opt_result_maybenull_  ID3D11Buffer **pIndexBuffer,
		/* [annotation] */
		_Out_opt_  DXGI_FORMAT *Format,
		/* [annotation] */
		_Out_opt_  UINT *Offset) = 0;

	virtual void STDMETHODCALLTYPE GSGetConstantBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_Out_writes_opt_(NumBuffers)  ID3D11Buffer **ppConstantBuffers) = 0;

	virtual void STDMETHODCALLTYPE GSGetShader(
		/* [annotation] */
		_Outptr_result_maybenull_  ID3D11GeometryShader **ppGeometryShader,
		/* [annotation] */
		_Out_writes_opt_(*pNumClassInstances)  ID3D11ClassInstance **ppClassInstances,
		/* [annotation] */
		_Inout_opt_  UINT *pNumClassInstances) = 0;

	virtual void STDMETHODCALLTYPE IAGetPrimitiveTopology(
		/* [annotation] */
		_Out_  D3D11_PRIMITIVE_TOPOLOGY *pTopology) = 0;

	virtual void STDMETHODCALLTYPE VSGetShaderResources(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumViews,
		/* [annotation] */
		_Out_writes_opt_(NumViews)  ID3D11ShaderResourceView **ppShaderResourceViews) = 0;

	virtual void STDMETHODCALLTYPE VSGetSamplers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot)  UINT NumSamplers,
		/* [annotation] */
		_Out_writes_opt_(NumSamplers)  ID3D11SamplerState **ppSamplers) = 0;

	virtual void STDMETHODCALLTYPE GetPredication(
		/* [annotation] */
		_Outptr_opt_result_maybenull_  ID3D11Predicate **ppPredicate,
		/* [annotation] */
		_Out_opt_  BOOL *pPredicateValue) = 0;

	virtual void STDMETHODCALLTYPE GSGetShaderResources(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumViews,
		/* [annotation] */
		_Out_writes_opt_(NumViews)  ID3D11ShaderResourceView **ppShaderResourceViews) = 0;

	virtual void STDMETHODCALLTYPE GSGetSamplers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot)  UINT NumSamplers,
		/* [annotation] */
		_Out_writes_opt_(NumSamplers)  ID3D11SamplerState **ppSamplers) = 0;

	virtual void STDMETHODCALLTYPE OMGetRenderTargets(
		/* [annotation] */
		_In_range_(0, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)  UINT NumViews,
		/* [annotation] */
		_Out_writes_opt_(NumViews)  ID3D11RenderTargetView **ppRenderTargetViews,
		/* [annotation] */
		_Outptr_opt_result_maybenull_  ID3D11DepthStencilView **ppDepthStencilView) = 0;

	virtual void STDMETHODCALLTYPE OMGetRenderTargetsAndUnorderedAccessViews(
		/* [annotation] */
		_In_range_(0, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)  UINT NumRTVs,
		/* [annotation] */
		_Out_writes_opt_(NumRTVs)  ID3D11RenderTargetView **ppRenderTargetViews,
		/* [annotation] */
		_Outptr_opt_result_maybenull_  ID3D11DepthStencilView **ppDepthStencilView,
		/* [annotation] */
		_In_range_(0, D3D11_PS_CS_UAV_REGISTER_COUNT - 1)  UINT UAVStartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_PS_CS_UAV_REGISTER_COUNT - UAVStartSlot)  UINT NumUAVs,
		/* [annotation] */
		_Out_writes_opt_(NumUAVs)  ID3D11UnorderedAccessView **ppUnorderedAccessViews) = 0;

	virtual void STDMETHODCALLTYPE OMGetBlendState(
		/* [annotation] */
		_Outptr_opt_result_maybenull_  ID3D11BlendState **ppBlendState,
		/* [annotation] */
		_Out_opt_  FLOAT BlendFactor[4],
		/* [annotation] */
		_Out_opt_  UINT *pSampleMask) = 0;

	virtual void STDMETHODCALLTYPE OMGetDepthStencilState(
		/* [annotation] */
		_Outptr_opt_result_maybenull_  ID3D11DepthStencilState **ppDepthStencilState,
		/* [annotation] */
		_Out_opt_  UINT *pStencilRef) = 0;

	virtual void STDMETHODCALLTYPE SOGetTargets(
		/* [annotation] */
		_In_range_(0, D3D11_SO_BUFFER_SLOT_COUNT)  UINT NumBuffers,
		/* [annotation] */
		_Out_writes_opt_(NumBuffers)  ID3D11Buffer **ppSOTargets) = 0;

	virtual void STDMETHODCALLTYPE RSGetState(
		/* [annotation] */
		_Outptr_result_maybenull_  ID3D11RasterizerState **ppRasterizerState) = 0;

	virtual void STDMETHODCALLTYPE RSGetViewports(
		/* [annotation] */
		_Inout_ /*_range(0, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )*/   UINT *pNumViewports,
		/* [annotation] */
		_Out_writes_opt_(*pNumViewports)  D3D11_VIEWPORT *pViewports) = 0;

	virtual void STDMETHODCALLTYPE RSGetScissorRects(
		/* [annotation] */
		_Inout_ /*_range(0, D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )*/   UINT *pNumRects,
		/* [annotation] */
		_Out_writes_opt_(*pNumRects)  D3D11_RECT *pRects) = 0;

	virtual void STDMETHODCALLTYPE HSGetShaderResources(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumViews,
		/* [annotation] */
		_Out_writes_opt_(NumViews)  ID3D11ShaderResourceView **ppShaderResourceViews) = 0;

	virtual void STDMETHODCALLTYPE HSGetShader(
		/* [annotation] */
		_Outptr_result_maybenull_  ID3D11HullShader **ppHullShader,
		/* [annotation] */
		_Out_writes_opt_(*pNumClassInstances)  ID3D11ClassInstance **ppClassInstances,
		/* [annotation] */
		_Inout_opt_  UINT *pNumClassInstances) = 0;

	virtual void STDMETHODCALLTYPE HSGetSamplers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot)  UINT NumSamplers,
		/* [annotation] */
		_Out_writes_opt_(NumSamplers)  ID3D11SamplerState **ppSamplers) = 0;

	virtual void STDMETHODCALLTYPE HSGetConstantBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_Out_writes_opt_(NumBuffers)  ID3D11Buffer **ppConstantBuffers) = 0;

	virtual void STDMETHODCALLTYPE DSGetShaderResources(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumViews,
		/* [annotation] */
		_Out_writes_opt_(NumViews)  ID3D11ShaderResourceView **ppShaderResourceViews) = 0;

	virtual void STDMETHODCALLTYPE DSGetShader(
		/* [annotation] */
		_Outptr_result_maybenull_  ID3D11DomainShader **ppDomainShader,
		/* [annotation] */
		_Out_writes_opt_(*pNumClassInstances)  ID3D11ClassInstance **ppClassInstances,
		/* [annotation] */
		_Inout_opt_  UINT *pNumClassInstances) = 0;

	virtual void STDMETHODCALLTYPE DSGetSamplers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot)  UINT NumSamplers,
		/* [annotation] */
		_Out_writes_opt_(NumSamplers)  ID3D11SamplerState **ppSamplers) = 0;

	virtual void STDMETHODCALLTYPE DSGetConstantBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_Out_writes_opt_(NumBuffers)  ID3D11Buffer **ppConstantBuffers) = 0;

	virtual void STDMETHODCALLTYPE CSGetShaderResources(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot)  UINT NumViews,
		/* [annotation] */
		_Out_writes_opt_(NumViews)  ID3D11ShaderResourceView **ppShaderResourceViews) = 0;

	virtual void STDMETHODCALLTYPE CSGetUnorderedAccessViews(
		/* [annotation] */
		_In_range_(0, D3D11_1_UAV_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_1_UAV_SLOT_COUNT - StartSlot)  UINT NumUAVs,
		/* [annotation] */
		_Out_writes_opt_(NumUAVs)  ID3D11UnorderedAccessView **ppUnorderedAccessViews) = 0;

	virtual void STDMETHODCALLTYPE CSGetShader(
		/* [annotation] */
		_Outptr_result_maybenull_  ID3D11ComputeShader **ppComputeShader,
		/* [annotation] */
		_Out_writes_opt_(*pNumClassInstances)  ID3D11ClassInstance **ppClassInstances,
		/* [annotation] */
		_Inout_opt_  UINT *pNumClassInstances) = 0;

	virtual void STDMETHODCALLTYPE CSGetSamplers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot)  UINT NumSamplers,
		/* [annotation] */
		_Out_writes_opt_(NumSamplers)  ID3D11SamplerState **ppSamplers) = 0;

	virtual void STDMETHODCALLTYPE CSGetConstantBuffers(
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1)  UINT StartSlot,
		/* [annotation] */
		_In_range_(0, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot)  UINT NumBuffers,
		/* [annotation] */
		_Out_writes_opt_(NumBuffers)  ID3D11Buffer **ppConstantBuffers) = 0;

	virtual void STDMETHODCALLTYPE ClearState(void) = 0;

	virtual void STDMETHODCALLTYPE Flush(void) = 0;

	virtual D3D11_DEVICE_CONTEXT_TYPE STDMETHODCALLTYPE GetType(void) = 0;

	virtual UINT STDMETHODCALLTYPE GetContextFlags(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE FinishCommandList(
		BOOL RestoreDeferredContextState,
		/* [annotation] */
		_COM_Outptr_opt_  ID3D11CommandList **ppCommandList) = 0;

};
