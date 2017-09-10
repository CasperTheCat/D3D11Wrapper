#include "d3d11DeviceContext.h"

D3D11CustomContext::D3D11CustomContext(ID3D11DeviceContext* devCon, ID3D11DeviceContext*** ret)
{
	m_devContext = devCon;
	*ret = &m_devContext;
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




