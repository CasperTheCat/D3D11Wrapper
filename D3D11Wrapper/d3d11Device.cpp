#include "d3d11Device.h"
#include <iostream>

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

HRESULT D3D11CustomDevice::CreateGeometryShaderWithStreamOutput(const void* pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY* pSODeclaration, UINT NumEntries, const UINT* pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader)
{
	return m_d3dDevice->CreateGeometryShaderWithStreamOutput(pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader);
}

HRESULT D3D11CustomDevice::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
{
	return m_d3dDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
}

HRESULT D3D11CustomDevice::CreateHullShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11HullShader** ppHullShader)
{
	return m_d3dDevice->CreateHullShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);
}

HRESULT D3D11CustomDevice::CreateDomainShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11DomainShader** ppDomainShader)
{
	return m_d3dDevice->CreateDomainShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);
}

HRESULT D3D11CustomDevice::CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11ComputeShader** ppComputeShader)
{
	return m_d3dDevice->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);
}

HRESULT D3D11CustomDevice::CreateClassLinkage(ID3D11ClassLinkage** ppLinkage)
{
	return m_d3dDevice->CreateClassLinkage(ppLinkage);
}

HRESULT D3D11CustomDevice::CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState)
{
	return m_d3dDevice->CreateBlendState(pBlendStateDesc, ppBlendState);
}

HRESULT D3D11CustomDevice::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState)
{
	return m_d3dDevice->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState);
}

HRESULT D3D11CustomDevice::CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState)
{
	return m_d3dDevice->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);
}

HRESULT D3D11CustomDevice::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
{
	return m_d3dDevice->CreateSamplerState(pSamplerDesc, ppSamplerState);
}

HRESULT D3D11CustomDevice::CreateQuery(const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery)
{
	return m_d3dDevice->CreateQuery(pQueryDesc, ppQuery);
}

HRESULT D3D11CustomDevice::CreatePredicate(const D3D11_QUERY_DESC* pPredicateDesc, ID3D11Predicate** ppPredicate)
{
	return m_d3dDevice->CreatePredicate(pPredicateDesc, ppPredicate);
}

HRESULT D3D11CustomDevice::CreateCounter(const D3D11_COUNTER_DESC* pCounterDesc, ID3D11Counter** ppCounter)
{
	return m_d3dDevice->CreateCounter(pCounterDesc, ppCounter);
}

HRESULT D3D11CustomDevice::CreateDeferredContext(UINT ContextFlags, ID3D11DeviceContext** ppDeferredContext)
{
	return m_d3dDevice->CreateDeferredContext(ContextFlags, ppDeferredContext);
}

HRESULT D3D11CustomDevice::OpenSharedResource(HANDLE hResource, const IID& ReturnedInterface, void** ppResource)
{
	return m_d3dDevice->OpenSharedResource(hResource, ReturnedInterface, ppResource);
}

HRESULT D3D11CustomDevice::CheckFormatSupport(DXGI_FORMAT Format, UINT* pFormatSupport)
{
	return m_d3dDevice->CheckFormatSupport(Format, pFormatSupport);
}

HRESULT D3D11CustomDevice::CheckMultisampleQualityLevels(DXGI_FORMAT Format, UINT SampleCount, UINT* pNumQualityLevels)
{
	return m_d3dDevice->CheckMultisampleQualityLevels(Format, SampleCount, pNumQualityLevels);
}

void D3D11CustomDevice::CheckCounterInfo(D3D11_COUNTER_INFO* pCounterInfo)
{
	return m_d3dDevice->CheckCounterInfo(pCounterInfo);
}

HRESULT D3D11CustomDevice::CheckCounter(const D3D11_COUNTER_DESC* pDesc, D3D11_COUNTER_TYPE* pType, UINT* pActiveCounters, LPSTR szName, UINT* pNameLength, LPSTR szUnits, UINT* pUnitsLength, LPSTR szDescription, UINT* pDescriptionLength)
{
	return m_d3dDevice->CheckCounter(pDesc, pType, pActiveCounters, szName, pNameLength, szUnits, pUnitsLength, szDescription, pDescriptionLength);
}

HRESULT D3D11CustomDevice::CheckFeatureSupport(D3D11_FEATURE Feature, void* pFeatureSupportData, UINT FeatureSupportDataSize)
{
	return m_d3dDevice->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
}

HRESULT D3D11CustomDevice::GetPrivateData(const GUID& guid, UINT* pDataSize, void* pData)
{
	return m_d3dDevice->GetPrivateData(guid, pDataSize, pData);
}

HRESULT D3D11CustomDevice::SetPrivateData(const GUID& guid, UINT DataSize, const void* pData)
{
	return m_d3dDevice->SetPrivateData(guid, DataSize, pData);
}

HRESULT D3D11CustomDevice::SetPrivateDataInterface(const GUID& guid, const IUnknown* pData)
{
	return m_d3dDevice->SetPrivateDataInterface(guid, pData);
}

D3D_FEATURE_LEVEL D3D11CustomDevice::GetFeatureLevel()
{
	return m_d3dDevice->GetFeatureLevel();
}

UINT D3D11CustomDevice::GetCreationFlags()
{
	return m_d3dDevice->GetCreationFlags();
}

HRESULT D3D11CustomDevice::GetDeviceRemovedReason()
{
	return m_d3dDevice->GetDeviceRemovedReason();
}

void D3D11CustomDevice::GetImmediateContext(ID3D11DeviceContext** ppImmediateContext)
{
	// This will return the TRUE, non wrapped version of the context...
	// TODO
	// Store a reference to the wrapped version and return it here
	return m_d3dDevice->GetImmediateContext(ppImmediateContext);
}

HRESULT D3D11CustomDevice::SetExceptionMode(UINT RaiseFlags)
{
	return m_d3dDevice->SetExceptionMode(RaiseFlags);
}

UINT D3D11CustomDevice::GetExceptionMode()
{
	return m_d3dDevice->GetExceptionMode();
}

HRESULT D3D11CustomDevice::QueryInterface(const IID& riid, void** ppvObject)
{
	return m_d3dDevice->QueryInterface(riid, ppvObject);
}

ULONG D3D11CustomDevice::AddRef()
{
	return m_d3dDevice->AddRef();
}

ULONG D3D11CustomDevice::Release()
{
	return m_d3dDevice->Release();
}


