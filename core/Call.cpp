#include "Call.h"
#include "../D3D11Wrapper/Globals.h"
#include <iostream>

#include "../D3D11Wrapper/d3d11ObjectManager.h"

CCall::CCall(uint32_t frameNumber) :
	m_eTopology(0xff),
	m_iComputeShader(-2),
	m_iDomainShader(-2),
	m_iGeometryShader(-2),
	m_iHullShader(-2),
	m_iIndexBuffer(-2),
	m_iPixelShader(-2),
	m_iVertexShader(-2)
{
	m_uFrameNumber = frameNumber;
}

CCall::~CCall()
{

}

//void CCall::SerialiseSRV(std::filesystem::path writePath, D3DObjectManager* pGLOM, CResourceBacking* srvPtr, uint32_t uSRVIndex, EShaderTypes eShaderType)
//{
//	if (srvPtr->m_eResourceType == EBackingType::Buffer)
//	{
//		DEBUG_LINE(pGLOM->Event, LOGWRT("SRV BUFFER"));
//		auto t = pGLOM->QueryBuffer(const_cast<void*>(srvPtr->m_pResPtr));
//		if (t >= 0)
//		{
//			DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Buffer: " << uSRVIndex));
//			pGLOM->GetBuffer(t)->Serialise((writePath / ("srv." + std::to_string(uSRVIndex) + ".buffer")).string());
//		}
//	}
//
//
//}

void CCall::Serialise(std::filesystem::path writePath, D3DObjectManager* pGLOM)
{
	DEBUG_ONLY_PRINT("[WRTE] Serialising Call to path: " << writePath.string());

	std::ofstream serial(writePath / "call.info", std::ios::out | std::ios::binary);
	serial.write(
		reinterpret_cast<char*>(&m_uIndexCount),
		sizeof(uint32_t)
	);
	serial.write(
		reinterpret_cast<char*>(&m_uStartIndexLocation),
		sizeof(uint32_t)
	);
	serial.write(
		reinterpret_cast<char*>(&m_iBaseVertexLocation),
		sizeof(int32_t)
	);
	serial.close();

	///// ///// ////////// ///// /////
	// Draw Buffers
	//
	if (m_iIndexBuffer >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Index Buffer"));
		pGLOM->GetBuffer(m_iIndexBuffer)->Serialise((writePath / "index.buffer").string());
	}

	for (uint32_t i = 0; i < m_viVertexBuffers.size(); ++i)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Attempting Vertex Buffer: " << i));
		auto t = m_viVertexBuffers[i];
		if (t >= 0)
		{
			DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Vertex Buffer: " << i));
			pGLOM->GetBuffer(t)->Serialise((writePath / ("vertex." + std::to_string(i) + ".buffer")).string());
		}
	}

	///// ///// ////////// ///// /////
	// Shaders
	//

	if (m_iVertexShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Vertex Shader"));
		pGLOM->GetShader(m_iVertexShader)->Serialise((writePath / ("vertex.shader")).string());
		pGLOM->SerialiseShader(m_iVertexShader, (writePath / ("vertex.shader")).string());
	}

	if (m_iHullShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Hull Shader"));
		pGLOM->GetShader(m_iHullShader)->Serialise((writePath / ("hull.shader")).string());
	}

	if (m_iDomainShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Domain Shader"));
		pGLOM->GetShader(m_iDomainShader)->Serialise((writePath / ("domain.shader")).string());
	}

	if (m_iGeometryShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Geometry Shader"));
		pGLOM->GetShader(m_iGeometryShader)->Serialise((writePath / ("geometry.shader")).string());
		pGLOM->SerialiseShader(m_iGeometryShader, (writePath / ("geometry.shader")).string());
	}

	if (m_iPixelShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Pixel Shader"));
		pGLOM->GetShader(m_iPixelShader)->Serialise((writePath / ("pixel.shader")).string());
		pGLOM->SerialiseShader(m_iPixelShader, (writePath / ("pixel.shader")).string());
	}

	if (m_iComputeShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Compute Shader"));
		pGLOM->GetShader(m_iComputeShader)->Serialise((writePath / ("compute.shader")).string());
	}

	///// ///// ////////// ///// /////
	// Resources - Constants
	//

	for (uint32_t i = 0; i < m_stVertexResources.viConstantBuffers.size(); ++i)
	{
		auto t = m_stVertexResources.viConstantBuffers[i];
		if (t >= 0)
		{
			DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Vertex Constant Buffer: " << i));
			pGLOM->GetBuffer(t)->Serialise((writePath / ("vertex." + std::to_string(i) + ".constbuffer")).string());
		}
	}

	for (uint32_t i = 0; i < m_stHullResources.viConstantBuffers.size(); ++i)
	{
		auto t = m_stHullResources.viConstantBuffers[i];
		if (t >= 0)
		{
			DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Hull Constant Buffer: " << i));
			pGLOM->GetBuffer(t)->Serialise((writePath / ("hull." + std::to_string(i) + ".constbuffer")).string());
		}
	}

	for (uint32_t i = 0; i < m_stDomainResources.viConstantBuffers.size(); ++i)
	{
		auto t = m_stDomainResources.viConstantBuffers[i];
		if (t >= 0)
		{
			DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Domain Constant Buffer: " << i));
			pGLOM->GetBuffer(t)->Serialise((writePath / ("domain." + std::to_string(i) + ".constbuffer")).string());
		}
	}

	for (uint32_t i = 0; i < m_stGeometryResources.viConstantBuffers.size(); ++i)
	{
		auto t = m_stGeometryResources.viConstantBuffers[i];
		if (t >= 0)
		{
			DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Geometry Constant Buffer: " << i));
			pGLOM->GetBuffer(t)->Serialise((writePath / ("geometry." + std::to_string(i) + ".constbuffer")).string());
		}
	}

	for (uint32_t i = 0; i < m_stPixelResources.viConstantBuffers.size(); ++i)
	{
		auto t = m_stPixelResources.viConstantBuffers[i];
		if (t >= 0)
		{
			DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Pixel Constant Buffer: " << i));
			pGLOM->GetBuffer(t)->Serialise((writePath / ("pixel." + std::to_string(i) + ".constbuffer")).string());
		}
	}

	for (uint32_t i = 0; i < m_stComputeResources.viConstantBuffers.size(); ++i)
	{
		auto t = m_stComputeResources.viConstantBuffers[i];
		if (t >= 0)
		{
			DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Compute Constant Buffer: " << i));
			pGLOM->GetBuffer(t)->Serialise((writePath / ("compute." + std::to_string(i) + ".constbuffer")).string());
		}
	}

	///// ///// ////////// ///// /////
	// Resources - SRVs
	//

	for (uint32_t i = 0; i < m_stVertexResources.viShaderResources.size(); ++i)
	{
		auto sr = m_stVertexResources.viShaderResources[i];
		if (sr >= 0)
		{
			auto srvPtr = pGLOM->GetResourceView(sr);

			if (srvPtr->m_eResourceType == EBackingType::Buffer)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("VS SRV BUFFER"));
				auto t = pGLOM->QueryBuffer(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Buffer: " << i));
					pGLOM->GetBuffer(t)->Serialise((writePath / ("vertex." + std::to_string(i) + ".srvbuffer")).string());
				}
			}
			else if (srvPtr->m_eResourceType == EBackingType::Texture)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("VS SRV TEX"));
				auto t = pGLOM->QueryTexture(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Tex: " << i));
					pGLOM->GetTexture(t)->Serialise((writePath / ("vertex." + std::to_string(i) + ".tex")).string());
				}
			}
		}
	}

	for (uint32_t i = 0; i < m_stHullResources.viShaderResources.size(); ++i)
	{
		auto sr = m_stHullResources.viShaderResources[i];
		if (sr >= 0)
		{
			auto srvPtr = pGLOM->GetResourceView(sr);

			if (srvPtr->m_eResourceType == EBackingType::Buffer)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("SRV BUFFER"));
				auto t = pGLOM->QueryBuffer(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Buffer: " << i));
					pGLOM->GetBuffer(t)->Serialise((writePath / ("hull." + std::to_string(i) + ".srvbuffer")).string());
				}
			}
			else if (srvPtr->m_eResourceType == EBackingType::Texture)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("SRV TEX"));
				auto t = pGLOM->QueryTexture(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Buffer: " << i));
					pGLOM->GetTexture(t)->Serialise((writePath / ("hull." + std::to_string(i) + ".tex")).string());
				}
			}
		}
	}

	for (uint32_t i = 0; i < m_stDomainResources.viShaderResources.size(); ++i)
	{
		auto sr = m_stDomainResources.viShaderResources[i];
		if (sr >= 0)
		{
			auto srvPtr = pGLOM->GetResourceView(sr);

			if (srvPtr->m_eResourceType == EBackingType::Buffer)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("SRV BUFFER"));
				auto t = pGLOM->QueryBuffer(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Buffer: " << i));
					pGLOM->GetBuffer(t)->Serialise((writePath / ("domain." + std::to_string(i) + ".srvbuffer")).string());
				}
			}
			else if (srvPtr->m_eResourceType == EBackingType::Texture)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("SRV TEX"));
				auto t = pGLOM->QueryTexture(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Buffer: " << i));
					pGLOM->GetTexture(t)->Serialise((writePath / ("domain." + std::to_string(i) + ".tex")).string());
				}
			}
		}
	}

	for (uint32_t i = 0; i < m_stGeometryResources.viShaderResources.size(); ++i)
	{
		auto sr = m_stGeometryResources.viShaderResources[i];
		if (sr >= 0)
		{
			auto srvPtr = pGLOM->GetResourceView(sr);

			if (srvPtr->m_eResourceType == EBackingType::Buffer)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("SRV BUFFER"));
				auto t = pGLOM->QueryBuffer(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Buffer: " << i));
					pGLOM->GetBuffer(t)->Serialise((writePath / ("geometry." + std::to_string(i) + ".srvbuffer")).string());
				}
			}
			else if (srvPtr->m_eResourceType == EBackingType::Texture)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("SRV TEX"));
				auto t = pGLOM->QueryTexture(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Buffer: " << i));
					pGLOM->GetTexture(t)->Serialise((writePath / ("geometry." + std::to_string(i) + ".tex")).string());
				}
			}
		}
	}

	for (uint32_t i = 0; i < m_stPixelResources.viShaderResources.size(); ++i)
	{
		auto sr = m_stPixelResources.viShaderResources[i];
		if (sr >= 0)
		{
			auto srvPtr = pGLOM->GetResourceView(sr);

			if (srvPtr->m_eResourceType == EBackingType::Buffer)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("SRV BUFFER"));
				auto t = pGLOM->QueryBuffer(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Buffer: " << i));
					pGLOM->GetBuffer(t)->Serialise((writePath / ("pixel." + std::to_string(i) + ".srvbuffer")).string());
				}
			}
			else if (srvPtr->m_eResourceType == EBackingType::Texture)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("SRV TEX"));
				auto t = pGLOM->QueryTexture(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Buffer: " << i));
					pGLOM->GetTexture(t)->Serialise((writePath / ("pixel." + std::to_string(i) + ".tex")).string());
				}
			}
		}
	}

	for (uint32_t i = 0; i < m_stComputeResources.viShaderResources.size(); ++i)
	{
		auto sr = m_stComputeResources.viShaderResources[i];
		if (sr >= 0)
		{
			auto srvPtr = pGLOM->GetResourceView(sr);

			if (srvPtr->m_eResourceType == EBackingType::Buffer)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("SRV BUFFER"));
				auto t = pGLOM->QueryBuffer(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Buffer: " << i));
					pGLOM->GetBuffer(t)->Serialise((writePath / ("compute." + std::to_string(i) + ".srvbuffer")).string());
				}
			}
			else if (srvPtr->m_eResourceType == EBackingType::Texture)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("SRV TEX"));
				auto t = pGLOM->QueryTexture(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Writing SRV Buffer: " << i));
					pGLOM->GetTexture(t)->Serialise((writePath / ("compute." + std::to_string(i) + ".tex")).string());
				}
			}
		}
	}
}

void CCall::FinaliseResource(D3DObjectManager* pGLOM, FShaderResources* pSrv)
{
	for (uint32_t i = 0; i < pSrv->viConstantBuffers.size(); ++i)
	{
		auto t = pSrv->viConstantBuffers[i];
		if (t >= 0)
		{
			DEBUG_LINE(pGLOM->Event, LOGWRT("Finalising Constant Buffer: " << i));
			pGLOM->GetBuffer(t)->Load();
		}
	}

	for (uint32_t i = 0; i < pSrv->viShaderResources.size(); ++i)
	{
		auto sr = pSrv->viShaderResources[i];
		if (sr >= 0)
		{
			auto srvPtr = pGLOM->GetResourceView(sr);

			if (srvPtr->m_eResourceType == EBackingType::Buffer)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("SRV BUFFER"));
				auto t = pGLOM->QueryBuffer(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Loading SRV Buffer: " << i));
					pGLOM->GetBuffer(t)->Load();
				}
			}
			else if (srvPtr->m_eResourceType == EBackingType::Texture)
			{
				DEBUG_LINE(pGLOM->Event, LOGWRT("SRV TEX"));
				auto t = pGLOM->QueryTexture(const_cast<void*>(srvPtr->m_pResPtr));
				if (t >= 0)
				{
					DEBUG_LINE(pGLOM->Event, LOGWRT("Loading SRV Texture: " << i));
					pGLOM->GetTexture(t)->Load();
				}
			}
		}
	}
}

void CCall::Finalise(class D3DObjectManager* pGLOM)
{
	///// ///// ////////// ///// /////
	// Draw Buffers
	//
	if (m_iIndexBuffer >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Finalising Index Buffer"));
		pGLOM->GetBuffer(m_iIndexBuffer)->Load();
	}

	for (uint32_t i = 0; i < m_viVertexBuffers.size(); ++i)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Finalising Vertex Buffer: " << i));
		auto t = m_viVertexBuffers[i];
		if (t >= 0)
		{
			DEBUG_LINE(pGLOM->Event, LOGWRT("Finalised Vertex Buffer: " << i));
			pGLOM->GetBuffer(t)->Load();
		}
	}

	///// ///// ////////// ///// /////
	// Shaders
	//

	if (m_iVertexShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Vertex Shader"));
		pGLOM->GetShader(m_iVertexShader)->Load();
	}

	if (m_iHullShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Hull Shader"));
		pGLOM->GetShader(m_iHullShader)->Load();
	}

	if (m_iDomainShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Domain Shader"));
		pGLOM->GetShader(m_iDomainShader)->Load();
	}

	if (m_iGeometryShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Geometry Shader"));
		pGLOM->GetShader(m_iGeometryShader)->Load();
	}

	if (m_iPixelShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Pixel Shader"));
		pGLOM->GetShader(m_iPixelShader)->Load();
	}

	if (m_iComputeShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Compute Shader"));
		pGLOM->GetShader(m_iComputeShader)->Load();
	}

	///// ///// ////////// ///// /////
	// Resources
	//

	FinaliseResource(pGLOM, &m_stVertexResources);
	FinaliseResource(pGLOM, &m_stHullResources);
	FinaliseResource(pGLOM, &m_stDomainResources);
	FinaliseResource(pGLOM, &m_stGeometryResources);
	FinaliseResource(pGLOM, &m_stPixelResources);
	//FinaliseResource(pGLOM, &m_stComputeResources);
}

void CCall::SetInfo(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	m_uIndexCount = IndexCount;
	m_uStartIndexLocation = StartIndexLocation;
	m_iBaseVertexLocation = BaseVertexLocation;
}

void CCall::SetTopology(uint32_t eTopology)
{
	m_eTopology = eTopology;
}

void CCall::SetVertexShader(int32_t pShader)
{
	m_iVertexShader = pShader;
}

void CCall::SetHullShader(int32_t pShader)
{
	m_iHullShader = pShader;
}

void CCall::SetDomainShader(int32_t pShader)
{
	m_iDomainShader = pShader;
}

void CCall::SetGeometryShader(int32_t pShader)
{
	m_iGeometryShader = pShader;
}

void CCall::SetPixelShader(int32_t pShader)
{
	m_iPixelShader = pShader;
}

void CCall::SetComputeShader(int32_t pShader)
{
	m_iComputeShader = pShader;
}

void CCall::SetIndexBuffer(int32_t iBufferIndex)
{
	m_iIndexBuffer = iBufferIndex;
}

void CCall::AddVertexBuffer(int32_t iBufferIndex)
{
	m_viVertexBuffers.push_back(iBufferIndex);
}

void CCall::AddVertexConstantBuffer(int32_t iBufferIndex)
{
	m_stVertexResources.viConstantBuffers.push_back(iBufferIndex);
}

void CCall::AddVertexShaderResources(int32_t iBufferIndex)
{
	m_stVertexResources.viShaderResources.push_back(iBufferIndex);
}

void CCall::AddHullConstantBuffer(int32_t iBufferIndex)
{
	m_stHullResources.viConstantBuffers.push_back(iBufferIndex);
}

void CCall::AddHullShaderResources(int32_t iBufferIndex)
{
	m_stHullResources.viShaderResources.push_back(iBufferIndex);
}

void CCall::AddDomainConstantBuffer(int32_t iBufferIndex)
{
	m_stDomainResources.viConstantBuffers.push_back(iBufferIndex);
}

void CCall::AddDomainShaderResources(int32_t iBufferIndex)
{
	m_stHullResources.viShaderResources.push_back(iBufferIndex);
}

void CCall::AddGeometryConstantBuffer(int32_t iBufferIndex)
{
	m_stGeometryResources.viConstantBuffers.push_back(iBufferIndex);
}

void CCall::AddGeometryShaderResources(int32_t iBufferIndex)
{
	m_stGeometryResources.viShaderResources.push_back(iBufferIndex);
}

void CCall::AddPixelConstantBuffer(int32_t iBufferIndex)
{
	m_stPixelResources.viConstantBuffers.push_back(iBufferIndex);
}

void CCall::AddPixelShaderResources(int32_t iBufferIndex)
{
	m_stPixelResources.viShaderResources.push_back(iBufferIndex);
}

void CCall::AddComputeConstantBuffer(int32_t iBufferIndex)
{
	m_stComputeResources.viConstantBuffers.push_back(iBufferIndex);
}

void CCall::AddComputeShaderResources(int32_t iBufferIndex)
{
	m_stComputeResources.viShaderResources.push_back(iBufferIndex);
}

