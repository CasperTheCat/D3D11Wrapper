#include "d3d11Device.h"

D3D11CustomDevice::D3D11CustomDevice(ID3D11Device* dev, ID3D11Device*** ret)
{
	m_d3dDevice = dev;
	*ret = &m_d3dDevice;
}

D3D11CustomDevice::D3D11CustomDevice(ID3D11Device* dev)
{
    m_d3dDevice = dev;
}

HRESULT D3D11CustomDevice::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer)
{
	return m_d3dDevice->CreateBuffer(pDesc, pInitialData, ppBuffer);
}

HRESULT D3D11CustomDevice::CreateTexture1D(const D3D11_TEXTURE1D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture1D** ppTexture1D)
{
	return m_d3dDevice->CreateTexture1D(pDesc, pInitialData, ppTexture1D);
}

HRESULT D3D11CustomDevice::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D)
{
	return m_d3dDevice->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
}

HRESULT D3D11CustomDevice::CreateTexture3D(const D3D11_TEXTURE3D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture3D** ppTexture3D)
{
	return m_d3dDevice->CreateTexture3D(pDesc, pInitialData, ppTexture3D);
}

HRESULT D3D11CustomDevice::CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView)
{
	return m_d3dDevice->CreateShaderResourceView(pResource, pDesc, ppSRView);
}

HRESULT D3D11CustomDevice::CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView)
{
	return m_d3dDevice->CreateUnorderedAccessView(pResource, pDesc, ppUAView);
}

HRESULT D3D11CustomDevice::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
{
	return m_d3dDevice->CreateRenderTargetView(pResource, pDesc, ppRTView);
}

HRESULT D3D11CustomDevice::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
{
	return m_d3dDevice->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
}

HRESULT D3D11CustomDevice::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout)
{
	return m_d3dDevice->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
}

HRESULT D3D11CustomDevice::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
{
	return m_d3dDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
}

HRESULT D3D11CustomDevice::CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader)
{
	return m_d3dDevice->CreateGeometryShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);
}


