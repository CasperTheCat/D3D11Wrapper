#include "Call.h"

CCall::CCall(uint32_t frameNumber)
{
	m_uFrameNumber = frameNumber;
}

CCall::~CCall()
{

}

void CCall::SetVertexShader(std::shared_ptr<CShader> pShader)
{
	m_pVertexShader = pShader;
}

void CCall::SetHullShader(std::shared_ptr<CShader> pShader)
{
	m_pHullShader = pShader;
}

void CCall::SetDomainShader(std::shared_ptr<CShader> pShader)
{
	m_pDomainShader = pShader;
}

void CCall::SetGeometryShader(std::shared_ptr<CShader> pShader)
{
	m_pGeometryShader = pShader;
}

void CCall::SetPixelShader(std::shared_ptr<CShader> pShader)
{
	m_pPixelShader = pShader;
}

void CCall::AddVertexConstantBuffer(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stVertexResources.m_vpvConstantBuffers.push_back(pvBuffer);
}

void CCall::AddVertexSamplers(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stVertexResources.m_vpvSamplers.push_back(pvBuffer);
}

void CCall::AddVertexShaderResources(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stVertexResources.m_vpvShaderResources.push_back(pvBuffer);
}

void CCall::AddHullConstantBuffer(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stHullResources.m_vpvConstantBuffers.push_back(pvBuffer);
}

void CCall::AddHullSamplers(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stHullResources.m_vpvSamplers.push_back(pvBuffer);
}

void CCall::AddHullShaderResources(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stHullResources.m_vpvShaderResources.push_back(pvBuffer);
}

void CCall::AddDomainConstantBuffer(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stDomainResources.m_vpvConstantBuffers.push_back(pvBuffer);
}

void CCall::AddDomainSamplers(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stDomainResources.m_vpvSamplers.push_back(pvBuffer);
}

void CCall::AddDomainShaderResources(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stDomainResources.m_vpvShaderResources.push_back(pvBuffer);
}

void CCall::AddGeometryConstantBuffer(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stGeometryResources.m_vpvConstantBuffers.push_back(pvBuffer);
}

void CCall::AddGeometrySamplers(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stGeometryResources.m_vpvSamplers.push_back(pvBuffer);
}

void CCall::AddGeometryShaderResources(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stGeometryResources.m_vpvShaderResources.push_back(pvBuffer);
}

void CCall::AddPixelConstantBuffer(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stPixelResources.m_vpvConstantBuffers.push_back(pvBuffer);
}

void CCall::AddPixelSamplers(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stPixelResources.m_vpvSamplers.push_back(pvBuffer);
}

void CCall::AddPixelShaderResources(std::shared_ptr<std::vector<uint8_t>> pvBuffer)
{
	m_stPixelResources.m_vpvShaderResources.push_back(pvBuffer);
}
