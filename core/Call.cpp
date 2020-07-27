#include "Call.h"
#include <iostream>

#if defined(CORE_D3D11)
#include "../D3D11Wrapper/Globals.h"
#include "../D3D11Wrapper/d3d11ObjectManager.h"
#elif defined(CORE_D3D9)
#include "../D3D9Wrapper/Globals.h"
#include "../D3D9Wrapper/d3d9ObjectManager.h"
#else
#error Something Went Wrong
#endif

void CCall::Helper_AddBufferAtVectorLocation(std::vector<int32_t>& vec, int32_t iBufferIndex, uint32_t uSlotIndex)
{
	//DEBUG_ONLY_PRINT("[DEBG] v: " << vec.size() << " sl: " << uSlotIndex);
	// Check if the vector *has* the index
	if (uSlotIndex >= vec.size())
	{
		vec.resize(uSlotIndex + 1, -2);
		//DEBUG_ONLY_PRINT("[DEBG] Expanding Size to " << vec.size() << " sl: " << uSlotIndex + 1);
	}

	//DEBUG_ONLY_PRINT("[DEBG] v: " << vec.size() << " sl: " << uSlotIndex);
	vec[uSlotIndex] = iBufferIndex;
}

CCall::CCall(uint32_t frameNumber) :
	m_eTopology(0xff),
	m_iComputeShader(-2),
	m_iDomainShader(-2),
	m_iGeometryShader(-2),
	m_iHullShader(-2),
	m_iIndexBuffer(-2),
	m_iPixelShader(-2),
	m_iVertexShader(-2),
	m_uStartIndexLocation(0),
	m_uIndexCount(0),
	m_iBaseVertexLocation(0),
	m_iInputLayout(1),
	m_uDrawCallType(-1),
	m_uFrameNumber(frameNumber),
	m_uPrimitiveType(-1)
{

	// VertexBuffers
}

#define InitFromCopy(x) x(copy.x)
#define CopyStructVector(x) x = copy.x

CCall::CCall(const CCall& copy) :
	InitFromCopy(m_eTopology),
	InitFromCopy(m_iComputeShader),
	InitFromCopy(m_iDomainShader),
	InitFromCopy(m_iGeometryShader),
	InitFromCopy(m_iHullShader),
	InitFromCopy(m_iIndexBuffer),
	InitFromCopy(m_iPixelShader),
	InitFromCopy(m_iVertexShader),
	InitFromCopy(m_uStartIndexLocation),
	InitFromCopy(m_uIndexCount),
	InitFromCopy(m_iBaseVertexLocation),
	InitFromCopy(m_iInputLayout),
	InitFromCopy(m_uDrawCallType),
	m_uFrameNumber(copy.m_uFrameNumber + 1),
	InitFromCopy(m_uPrimitiveType)
{
	// Structs
	// IA
	CopyStructVector(m_viVertexBuffers);

	// CBs
	CopyStructVector(m_stVertexResources.viConstantBuffers);
	CopyStructVector(m_stHullResources.viConstantBuffers);
	CopyStructVector(m_stDomainResources.viConstantBuffers);
	CopyStructVector(m_stGeometryResources.viConstantBuffers);
	CopyStructVector(m_stPixelResources.viConstantBuffers);

	// SRVs
	CopyStructVector(m_stVertexResources.viShaderResources);
	CopyStructVector(m_stHullResources.viShaderResources);
	CopyStructVector(m_stDomainResources.viShaderResources);
	CopyStructVector(m_stGeometryResources.viShaderResources);
	CopyStructVector(m_stPixelResources.viShaderResources);

	CopyStructVector(m_vstVertexInvocationData);
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
	serial.write(
		reinterpret_cast<char*>(&m_uDrawCallType),
		sizeof(uint32_t)
	);

	serial.write(
		reinterpret_cast<char*>(&m_uPrimitiveType),
		sizeof(uint32_t)
	);

	for(uint32_t i = 0; i < m_vstVertexInvocationData.size(); ++i)
	{
		serial.write(
			reinterpret_cast<char*>(&(m_vstVertexInvocationData[i].Stride)),
			sizeof(uint32_t)
		);
		serial.write(
			reinterpret_cast<char*>(&(m_vstVertexInvocationData[i].Offset)),
			sizeof(uint32_t)
		);
	}

	//DEBUG_LOGLINE(pGLOM->Event, "[WRTE] Checking vst: " << m_vstVertexInvocationData[0].Offset);

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

	if (m_iInputLayout >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Input Layout"));
		pGLOM->GetInputLayout(m_iInputLayout)->Serialise((writePath / "input.layout").string());
	}

	///// ///// ////////// ///// /////
	// Shaders
	//

	if (m_iVertexShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Vertex Shader"));
		pGLOM->GetShader(m_iVertexShader)->Serialise((writePath / ("vertex.shader")).string());
		//pGLOM->SerialiseShader(m_iVertexShader, (writePath / ("vertex.shader")).string());
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
		//pGLOM->SerialiseShader(m_iGeometryShader, (writePath / ("geometry.shader")).string());
	}

	if (m_iPixelShader >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Writing Pixel Shader"));
		pGLOM->GetShader(m_iPixelShader)->Serialise((writePath / ("pixel.shader")).string());
		//pGLOM->SerialiseShader(m_iPixelShader, (writePath / ("pixel.shader")).string());
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

	if (m_iInputLayout >= 0)
	{
		DEBUG_LINE(pGLOM->Event, LOGWRT("Finalising Index Layout"));
		pGLOM->GetInputLayout(m_iInputLayout)->Load();
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
	DEBUG_LINE(pGLOM->Event, LOGWRT("Vertex on Final"));
	FinaliseResource(pGLOM, &m_stVertexResources);
	DEBUG_LINE(pGLOM->Event, LOGWRT("Hull on Final"));
	FinaliseResource(pGLOM, &m_stHullResources);
	DEBUG_LINE(pGLOM->Event, LOGWRT("Domain on Final"));
	FinaliseResource(pGLOM, &m_stDomainResources);
	DEBUG_LINE(pGLOM->Event, LOGWRT("Geo on Final"));
	FinaliseResource(pGLOM, &m_stGeometryResources);
	DEBUG_LINE(pGLOM->Event, LOGWRT("Pixel on Final"));
	FinaliseResource(pGLOM, &m_stPixelResources);
	//FinaliseResource(pGLOM, &m_stComputeResources);
}

void CCall::SetInfo(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation, uint32_t uDrawCallType, uint32_t uPrimitiveType)
{
	m_uIndexCount = IndexCount;
	m_uStartIndexLocation = StartIndexLocation;
	m_iBaseVertexLocation = BaseVertexLocation;
	m_uDrawCallType = uDrawCallType;
	m_uPrimitiveType = uPrimitiveType;
}

void CCall::SetTopology(uint32_t eTopology)
{
	m_eTopology = eTopology;
}

void CCall::SetVertexMeta(uint32_t SlotNumber, uint32_t Stride, uint32_t Offset)
{
	//DEBUG_ONLY_PRINT("[DEBG] v: " << vec.size() << " sl: " << uSlotIndex);
	// Check if the vector *has* the index
	if (SlotNumber >= m_vstVertexInvocationData.size())
	{
		m_vstVertexInvocationData.resize(SlotNumber + 1);
		//DEBUG_ONLY_PRINT("[DEBG] Expanding Size to " << vec.size() << " sl: " << uSlotIndex + 1);
	}

	//DEBUG_ONLY_PRINT("[DEBG] v: " << m_vstVertexInvocationData.size() << " sl: " << SlotNumber);
	FVertexInvocation temp{};

	m_vstVertexInvocationData[SlotNumber].Offset = Offset;
	m_vstVertexInvocationData[SlotNumber].Stride = Stride;
}

void CCall::SetLayout(int32_t iLayout)
{
	m_iInputLayout = iLayout;
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

void CCall::SetIndexBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	m_iIndexBuffer = iBufferIndex;
}

void CCall::AddVertexBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_viVertexBuffers, iBufferIndex, uSlotIndex);
}

void CCall::AddVertexConstantBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_stVertexResources.viConstantBuffers, iBufferIndex, uSlotIndex);
}

void CCall::AddVertexShaderResources(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_stVertexResources.viShaderResources, iBufferIndex, uSlotIndex);
}

void CCall::AddHullConstantBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_stHullResources.viConstantBuffers, iBufferIndex, uSlotIndex);
}

void CCall::AddHullShaderResources(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_stHullResources.viShaderResources, iBufferIndex, uSlotIndex);
}

void CCall::AddDomainConstantBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_stDomainResources.viConstantBuffers, iBufferIndex, uSlotIndex);
}

void CCall::AddDomainShaderResources(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_stDomainResources.viShaderResources, iBufferIndex, uSlotIndex);
}

void CCall::AddGeometryConstantBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_stGeometryResources.viConstantBuffers, iBufferIndex, uSlotIndex);
}

void CCall::AddGeometryShaderResources(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_stGeometryResources.viShaderResources, iBufferIndex, uSlotIndex);
}

void CCall::AddPixelConstantBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_stPixelResources.viConstantBuffers, iBufferIndex, uSlotIndex);
}

void CCall::AddPixelShaderResources(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_stPixelResources.viShaderResources, iBufferIndex, uSlotIndex);
}

void CCall::AddComputeConstantBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_stComputeResources.viConstantBuffers, iBufferIndex, uSlotIndex);
}

void CCall::AddComputeShaderResources(int32_t iBufferIndex,  uint32_t uSlotIndex)
{
	Helper_AddBufferAtVectorLocation(m_stComputeResources.viShaderResources, iBufferIndex, uSlotIndex);
}

