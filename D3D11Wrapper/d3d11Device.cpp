#include "d3d11Device.h"

D3D11CustomDevice::D3D11CustomDevice(ID3D11Device* dev, ID3D11Device*** ret)
{
	m_d3dDevice = dev;
	*ret = &m_d3dDevice;
}

//HRESULT D3D11CustomDevice::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer)
//{
//	return m_d3dDevice->CreateBuffer(pDesc, pInitialData, ppBuffer);
//}


