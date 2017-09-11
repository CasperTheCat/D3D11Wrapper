#include "d3d11DeviceContext.h"

D3D11CustomContext::D3D11CustomContext(ID3D11DeviceContext* devCon, ID3D11DeviceContext*** ret)
{
	m_devContext = devCon;
	*ret = &m_devContext;
}

D3D11CustomContext::D3D11CustomContext(ID3D11DeviceContext* devCon)
{
	m_devContext = devCon;
}

void D3D11CustomContext::VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	m_devContext->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::PSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	m_devContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::PSSetShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	m_devContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::VSSetShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	m_devContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	m_devContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void D3D11CustomContext::Draw(UINT VertexCount, UINT StartVertexLocation)
{
	m_devContext->Draw(VertexCount, StartVertexLocation);
}

HRESULT D3D11CustomContext::Map(ID3D11Resource* pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE* pMappedResource)
{
	return m_devContext->Map(pResource, Subresource, MapType, MapFlags, pMappedResource);
}

void D3D11CustomContext::Unmap(ID3D11Resource* pResource, UINT Subresource)
{
	m_devContext->Unmap(pResource, Subresource);
}

void D3D11CustomContext::PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	m_devContext->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::IASetInputLayout(ID3D11InputLayout* pInputLayout)
{
	m_devContext->IASetInputLayout(pInputLayout);
}

void D3D11CustomContext::IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
{
	m_devContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void D3D11CustomContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
{
	m_devContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

void D3D11CustomContext::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
{
	m_devContext->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

void D3D11CustomContext::DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation)
{
	m_devContext->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

void D3D11CustomContext::GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	m_devContext->GSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::GSSetShader(ID3D11GeometryShader* pShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	m_devContext->GSSetShader(pShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
{
	m_devContext->IASetPrimitiveTopology(Topology);
}

void D3D11CustomContext::VSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	m_devContext->VSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::VSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->VSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::Begin(ID3D11Asynchronous* pAsync)
{
	m_devContext->Begin(pAsync);
}

void D3D11CustomContext::End(ID3D11Asynchronous* pAsync)
{
	m_devContext->End(pAsync);
}

HRESULT D3D11CustomContext::GetData(ID3D11Asynchronous* pAsync, void* pData, UINT DataSize, UINT GetDataFlags)
{
	return m_devContext->GetData(pAsync, pData, DataSize, GetDataFlags);
}

void D3D11CustomContext::SetPredication(ID3D11Predicate* pPredicate, BOOL PredicateValue)
{
	m_devContext->SetPredication(pPredicate, PredicateValue);
}

void D3D11CustomContext::GSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	m_devContext->GSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::GSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->GSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView)
{
	m_devContext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}

void D3D11CustomContext::OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView* const* ppUnorderedAccessViews, const UINT* pUAVInitialCounts)
{
	m_devContext->OMSetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, pDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
}

void D3D11CustomContext::OMSetBlendState(ID3D11BlendState* pBlendState, const FLOAT BlendFactor[4], UINT SampleMask)
{
	m_devContext->OMSetBlendState(pBlendState, BlendFactor, SampleMask);
}

void D3D11CustomContext::OMSetDepthStencilState(ID3D11DepthStencilState* pDepthStencilState, UINT StencilRef)
{
	m_devContext->OMSetDepthStencilState(pDepthStencilState, StencilRef);
}

void D3D11CustomContext::SOSetTargets(UINT NumBuffers, ID3D11Buffer* const* ppSOTargets, const UINT* pOffsets)
{
	m_devContext->SOSetTargets(NumBuffers, ppSOTargets, pOffsets);
}

void D3D11CustomContext::DrawAuto()
{
	m_devContext->DrawAuto();
}

void D3D11CustomContext::DrawIndexedInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	m_devContext->DrawIndexedInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void D3D11CustomContext::DrawInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	m_devContext->DrawInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void D3D11CustomContext::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
{
	m_devContext->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
}

void D3D11CustomContext::DispatchIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	m_devContext->DispatchIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void D3D11CustomContext::RSSetState(ID3D11RasterizerState* pRasterizerState)
{
	m_devContext->RSSetState(pRasterizerState);
}

void D3D11CustomContext::RSSetViewports(UINT NumViewports, const D3D11_VIEWPORT* pViewports)
{
	m_devContext->RSSetViewports(NumViewports, pViewports);
}

void D3D11CustomContext::RSSetScissorRects(UINT NumRects, const D3D11_RECT* pRects)
{
	m_devContext->RSSetScissorRects(NumRects, pRects);
}

void D3D11CustomContext::CopySubresourceRegion(ID3D11Resource* pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox)
{
	m_devContext->CopySubresourceRegion(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox);
}

void D3D11CustomContext::CopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource)
{
	m_devContext->CopyResource(pDstResource, pSrcResource);
}

void D3D11CustomContext::UpdateSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
	m_devContext->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void D3D11CustomContext::CopyStructureCount(ID3D11Buffer* pDstBuffer, UINT DstAlignedByteOffset, ID3D11UnorderedAccessView* pSrcView)
{
	m_devContext->CopyStructureCount(pDstBuffer, DstAlignedByteOffset, pSrcView);
}

void D3D11CustomContext::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[4])
{
	m_devContext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

void D3D11CustomContext::ClearUnorderedAccessViewUint(ID3D11UnorderedAccessView* pUnorderedAccessView, const UINT Values[4])
{
	m_devContext->ClearUnorderedAccessViewUint(pUnorderedAccessView, Values);
}

void D3D11CustomContext::ClearUnorderedAccessViewFloat(ID3D11UnorderedAccessView* pUnorderedAccessView, const FLOAT Values[4])
{
	m_devContext->ClearUnorderedAccessViewFloat(pUnorderedAccessView, Values);
}

void D3D11CustomContext::ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil)
{
	m_devContext->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

void D3D11CustomContext::GenerateMips(ID3D11ShaderResourceView* pShaderResourceView)
{
	m_devContext->GenerateMips(pShaderResourceView);
}

void D3D11CustomContext::SetResourceMinLOD(ID3D11Resource* pResource, FLOAT MinLOD)
{
	m_devContext->SetResourceMinLOD(pResource, MinLOD);
}

FLOAT D3D11CustomContext::GetResourceMinLOD(ID3D11Resource* pResource)
{
	return m_devContext->GetResourceMinLOD(pResource);
}

void D3D11CustomContext::ResolveSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, ID3D11Resource* pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format)
{
	m_devContext->ResolveSubresource(pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format);
}

void D3D11CustomContext::ExecuteCommandList(ID3D11CommandList* pCommandList, BOOL RestoreContextState)
{
	m_devContext->ExecuteCommandList(pCommandList, RestoreContextState);
}

void D3D11CustomContext::HSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	m_devContext->HSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::HSSetShader(ID3D11HullShader* pHullShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	m_devContext->HSSetShader(pHullShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::HSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->HSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	m_devContext->HSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::DSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	m_devContext->DSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::DSSetShader(ID3D11DomainShader* pDomainShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	m_devContext->DSSetShader(pDomainShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::DSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->DSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	m_devContext->DSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::CSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	m_devContext->CSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView* const* ppUnorderedAccessViews, const UINT* pUAVInitialCounts)
{
	m_devContext->CSSetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
}

void D3D11CustomContext::CSSetShader(ID3D11ComputeShader* pComputeShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	m_devContext->CSSetShader(pComputeShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::CSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->CSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	m_devContext->CSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
	m_devContext->VSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::PSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews)
{
	m_devContext->PSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::PSGetShader(ID3D11PixelShader** ppPixelShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
	m_devContext->PSGetShader(ppPixelShader, ppClassInstances, pNumClassInstances);
}

void D3D11CustomContext::PSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
	m_devContext->PSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::VSGetShader(ID3D11VertexShader** ppVertexShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
	m_devContext->VSGetShader(ppVertexShader, ppClassInstances, pNumClassInstances);
}

void D3D11CustomContext::PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
	m_devContext->PSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::IAGetInputLayout(ID3D11InputLayout** ppInputLayout)
{
	m_devContext->IAGetInputLayout(ppInputLayout);
}

void D3D11CustomContext::IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppVertexBuffers, UINT* pStrides, UINT* pOffsets)
{
	m_devContext->IAGetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void D3D11CustomContext::IAGetIndexBuffer(ID3D11Buffer** pIndexBuffer, DXGI_FORMAT* Format, UINT* Offset)
{
	m_devContext->IAGetIndexBuffer(pIndexBuffer, Format, Offset);
}

void D3D11CustomContext::GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
	m_devContext->GSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::GSGetShader(ID3D11GeometryShader** ppGeometryShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
	m_devContext->GSGetShader(ppGeometryShader, ppClassInstances, pNumClassInstances);
}

void D3D11CustomContext::IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY* pTopology)
{
	m_devContext->IAGetPrimitiveTopology(pTopology);
}

void D3D11CustomContext::VSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews)
{
	m_devContext->VSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::VSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
	m_devContext->VSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::GetPredication(ID3D11Predicate** ppPredicate, BOOL* pPredicateValue)
{
	m_devContext->GetPredication(ppPredicate, pPredicateValue);
}

void D3D11CustomContext::GSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews)
{
	m_devContext->GSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::GSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
	m_devContext->GSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::OMGetRenderTargets(UINT NumViews, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView** ppDepthStencilView)
{
	m_devContext->OMGetRenderTargets(NumViews, ppRenderTargetViews, ppDepthStencilView);
}

void D3D11CustomContext::OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView** ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView** ppUnorderedAccessViews)
{
	m_devContext->OMGetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, ppDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews);
}

void D3D11CustomContext::OMGetBlendState(ID3D11BlendState** ppBlendState, FLOAT BlendFactor[4], UINT* pSampleMask)
{
	m_devContext->OMGetBlendState(ppBlendState, BlendFactor, pSampleMask);
}

void D3D11CustomContext::OMGetDepthStencilState(ID3D11DepthStencilState** ppDepthStencilState, UINT* pStencilRef)
{
	m_devContext->OMGetDepthStencilState(ppDepthStencilState, pStencilRef);
}

void D3D11CustomContext::SOGetTargets(UINT NumBuffers, ID3D11Buffer** ppSOTargets)
{
	m_devContext->SOGetTargets(NumBuffers, ppSOTargets);
}

void D3D11CustomContext::RSGetState(ID3D11RasterizerState** ppRasterizerState)
{
	m_devContext->RSGetState(ppRasterizerState);
}

void D3D11CustomContext::RSGetViewports(UINT* pNumViewports, D3D11_VIEWPORT* pViewports)
{
	m_devContext->RSGetViewports(pNumViewports, pViewports);
}

void D3D11CustomContext::RSGetScissorRects(UINT* pNumRects, D3D11_RECT* pRects)
{
	m_devContext->RSGetScissorRects(pNumRects, pRects);
}

void D3D11CustomContext::HSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews)
{
	m_devContext->HSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::HSGetShader(ID3D11HullShader** ppHullShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
	m_devContext->HSGetShader(ppHullShader, ppClassInstances, pNumClassInstances);
}

void D3D11CustomContext::HSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
	m_devContext->HSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
	m_devContext->HSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::DSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews)
{
	m_devContext->DSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::DSGetShader(ID3D11DomainShader** ppDomainShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
	m_devContext->DSGetShader(ppDomainShader, ppClassInstances, pNumClassInstances);
}

void D3D11CustomContext::DSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
	m_devContext->DSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
	m_devContext->DSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::CSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews)
{
	m_devContext->CSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView** ppUnorderedAccessViews)
{
	m_devContext->CSGetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews);
}

void D3D11CustomContext::CSGetShader(ID3D11ComputeShader** ppComputeShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances)
{
	m_devContext->CSGetShader(ppComputeShader, ppClassInstances, pNumClassInstances);
}

void D3D11CustomContext::CSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers)
{
	m_devContext->CSGetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers)
{
	m_devContext->CSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::ClearState()
{
	m_devContext->ClearState();
}

void D3D11CustomContext::Flush()
{
	m_devContext->Flush();
}

D3D11_DEVICE_CONTEXT_TYPE D3D11CustomContext::GetType()
{
	return  m_devContext->GetType();
}

UINT D3D11CustomContext::GetContextFlags()
{
	return m_devContext->GetContextFlags();
}

HRESULT D3D11CustomContext::FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList** ppCommandList)
{
	return m_devContext->FinishCommandList(RestoreDeferredContextState, ppCommandList);
}

void D3D11CustomContext::GetDevice(ID3D11Device** ppDevice)
{
	m_devContext->GetDevice(ppDevice);
}

HRESULT D3D11CustomContext::GetPrivateData(const GUID& guid, UINT* pDataSize, void* pData)
{
	return m_devContext->GetPrivateData(guid, pDataSize, pData);
}

HRESULT D3D11CustomContext::SetPrivateData(const GUID& guid, UINT DataSize, const void* pData)
{
	return m_devContext->SetPrivateData(guid, DataSize, pData);
}

HRESULT D3D11CustomContext::SetPrivateDataInterface(const GUID& guid, const IUnknown* pData)
{
	return m_devContext->SetPrivateDataInterface(guid, pData);
}

HRESULT D3D11CustomContext::QueryInterface(const IID& riid, void** ppvObject)
{
	return m_devContext->QueryInterface(riid, ppvObject);
}

ULONG D3D11CustomContext::AddRef()
{
	return m_devContext->AddRef();
}

ULONG D3D11CustomContext::Release()
{
	return m_devContext->Release();
}





