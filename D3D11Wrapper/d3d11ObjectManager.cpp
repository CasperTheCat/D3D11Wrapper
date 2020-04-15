#include "stdafx.h"
#include "d3d11ObjectManager.h"
#include "utils.h"
#include <sstream>
#include <iostream>
#include <d3dcompiler.h>
#include "Globals.h"

D3DObjectManager::D3DObjectManager(HMODULE _hD3D)
	: 
	hD3D(_hD3D), 
	bIsDllValid(true),
	m_eCaptureState(ECaptureState::Await),
	m_eWriteState(EWritebackState::Complete),
	m_uFramenumber(0)
{
	//Event = std::ofstream("d3d.txt");
}

D3DObjectManager::D3DObjectManager()
	: hD3D(nullptr),
	bIsDllValid(false),
	m_eCaptureState(ECaptureState::Await),
	m_eWriteState(EWritebackState::Complete),
	m_uFramenumber(0)
{
	//m_vFrames = std::make_shared<std::vector<CFrame>>();

	LoadDLL();

	m_fspRoot = std::filesystem::path(std::filesystem::current_path() / std::filesystem::path("Vermilion/"));

	// Create if not
	std::filesystem::create_directories(m_fspRoot);

#ifndef NDEBUG
	Event.open("D3D11.log");
	DEBUG_LOGLINE(Event, LOG("Initialising"));

	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	std::cout << "DLL initialised" << std::endl;

	LPSTR lls = GetCommandLineA();
	DEBUG_LOGLINE(Event, "[ARGS] " << lls);
#endif

	//m_vFrames.emplace_back();
}

D3DObjectManager::~D3DObjectManager()
{
	Event.close();
}

void D3DObjectManager::WriteFrame()
{
	DEBUG_LOGLINE(Event, "[WRTE] Writing");

	// GetFrame
	for (uint32_t cf = 0; cf < m_vFrames.size(); ++cf)
	{
		auto fPtr = &m_vFrames[cf];
		std::ostringstream ssFolderPath;
		ssFolderPath << std::setfill('0') << std::setw(5) << cf;
		std::filesystem::path fspRelFolderPath(ssFolderPath.str());

		for (uint32_t cc = 0; cc < fPtr->m_calls.size(); ++cc)
		{
			DEBUG_LINE(Event, "[WRTE] Writing call " << cc);
			auto fCall = &(fPtr->m_calls[cc]);
			
			std::ostringstream ssCallPath;
			ssCallPath << std::setfill('0') << std::setw(5) << cc;
			std::filesystem::path fspRelCallPath(ssCallPath.str());

			auto fullPath = m_fspRoot / fspRelFolderPath / fspRelCallPath;

			std::filesystem::create_directories(fullPath);

			// Full Path
			fCall->Serialise(fullPath, this);
		}
	}

	m_vFrames.clear();
	//m_vFrames.emplace_back();
}

CFrame* D3DObjectManager::GetCurrentFrame()
{
	return &m_vFrames[m_vFrames.size() - 1];
}

bool D3DObjectManager::LoadDLL()
{
	// Initialise wrapper
	DEBUG_LOGLINE(Event, LOG("Loading DLL"));

	HMODULE hD3D = nullptr;
	if (IsWow64())
	{
		Event << LOG("Running on SysWOW64") << std::endl;
		hD3D = LoadLibrary(L"C:\\Windows\\SysWOW64\\d3d11.dll");
	}
	else
	{
		hD3D = LoadLibrary(L"C:\\Windows\\System32\\d3d11.dll");
	}

	if (hD3D == NULL)
	{
		DEBUG_LOGLINE(Event, LOGERR("Unable to load DLL"));
		return false;
	}

	this->hD3D = hD3D;
	this->bIsDllValid = true;
	DEBUG_LOGLINE(Event, LOG("Loaded DLL"));
	return true;
}

HMODULE D3DObjectManager::getDLL()
{
	if (!bIsDllValid) this->LoadDLL();
	return hD3D;
}

void D3DObjectManager::Notify_Present()
{
	DEBUG_LOGLINE(Event, LOG("HitPresent"));

	switch (m_eCaptureState)
	{
	case ECaptureState::Await:
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) { 
			m_eCaptureState = ECaptureState::Capturing; 
			m_vFrames.emplace_back(); // Prep new frame
		}
		break;
	case ECaptureState::WaitingForPresent:
		break;
	case ECaptureState::Capturing:
		m_eCaptureState = ECaptureState::Cooldown;
		//[[FALLTHROUGH]]
	case ECaptureState::Cooldown:
		if (m_uCooldownFrames < 1)
		{
			if (!(GetAsyncKeyState(VK_DOWN) & 0x8000))
			{
				m_eCaptureState = ECaptureState::Await;
				m_eWriteState = EWritebackState::Queued;
				m_uCooldownFrames = D3DObjectManager::m_uCooldownFrames;
			}
		}
		else { --m_uCooldownFrames; }

		DEBUG_LOGLINE(Event, LOG("Cooling: " << m_uCooldownFrames));

		break;
	case ECaptureState::TOTAL_CAPTURE_STATES:
		break;
	default:
		break;
	}

	// Check if we can write things out
	switch (m_eWriteState)
	{
	case EWritebackState::Idle:
		// Data is waiting
		break;
	case EWritebackState::Queued:
		// Data should be written
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			WriteFrame();
		} // I think we can skip
		break;
	case EWritebackState::Complete:
		// Done
		break;
	case EWritebackState::TOTAL_WRITEBACK_STATES:
		break;
	default:
		break;
	}
}

void D3DObjectManager::Notify_Draw(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	// We don't touch the arrays if no capture is occuring
	if (m_eCaptureState == ECaptureState::Capturing)
	{
		GetCurrentFrame()->GetCurrentCall()->SetInfo(IndexCount, StartIndexLocation, BaseVertexLocation);
		GetCurrentFrame()->GetCurrentCall()->Finalise(this);
		
		DEBUG_LINE(Event, LOG("Finalised draw call: " << GetCurrentFrame()->m_calls.size()));
		

		// Emplace a new call
		// raw
		CFrame* curFrame = &m_vFrames[m_vFrames.size() - 1];
		//m_vFrames.back();
		//curFrame.m_calls.emplace_back(m_vFrames->size());
		curFrame->m_calls.push_back(CCall(m_vFrames.size()));


	}
}

void D3DObjectManager::SetTopology(uint32_t eTopology)
{
	if (m_eCaptureState == ECaptureState::Capturing)
	{

		// Current Call
		auto curCall = GetCurrentFrame()->GetCurrentCall();

		curCall->SetTopology(eTopology);
	}
}


void D3DObjectManager::AddShader(void *pReturnPtr, const void *pBytecode, uint64_t uBytecodeLength)
{
	// Sanity
	if (!pBytecode)
	{
		DEBUG_LOGLINE(Event, LOGERR("AddShader called with nullptr"));
		return;
	}

	if (!pReturnPtr)
	{
		DEBUG_LOGLINE(Event, LOGERR("AddShader called with bad return pointer"));
		return;
	}

	SCOPED_LOCK(m_mtxShaders);

	auto loc = m_mShaders.find(pReturnPtr);
	if (loc == m_mShaders.end())
	{
		// Something seems to be VERY wrong
		if (m_vShaders.size() > INT32_MAX)	{ return; }

		// This shader does not exist, so create it
		int32_t shaderIndex = static_cast<int32_t>(m_vShaders.size());
		m_mShaders.emplace(pReturnPtr, shaderIndex);

		// Now we convert.
		std::vector<uint8_t> localVec;
		localVec.resize(uBytecodeLength);
		memcpy(localVec.data(), pBytecode, uBytecodeLength);

		m_vShaders.emplace_back(pReturnPtr, std::move(localVec));
		//m_vShaders.emplace_back(pReturnPtr, pBytecode, uBytecodeLength);
		DEBUG_LOGLINE(Event, LOG("Shader registered to ID: " << shaderIndex));

		//// Just Serialise now...
		//DEBUG_LINE(Event, "[WRTE] Serialising Shader");

		//std::ostringstream ssShaderName;
		//ssShaderName << std::setfill('0') << std::setw(5) << shaderIndex << ".html";
		//std::filesystem::path fspShaders("shaders");
		//std::filesystem::path fspRelCallPath(ssShaderName.str());

		//auto fullPath = m_fspRoot / fspShaders;
		//std::filesystem::create_directories(fullPath);
		//SerialiseShader(shaderIndex, (fullPath / fspRelCallPath).string());
	}
	else
	{
		// Object exists... Do a comparison on the data?
		//DEBUG_LOGLINE(Event, LOGWARN("Shader seen before. ID: " << loc->second << ". Next Index: " << m_vShaders.size()));
	}
}

int32_t D3DObjectManager::QueryShader(void* pReturnPtr)
{
	// Is this a shader call?
	if (!pReturnPtr)
	{
		return -1;
	}

	SCOPED_LOCK(m_mtxShaders);

	auto loc = m_mShaders.find(pReturnPtr);
	if (loc == m_mShaders.end())
	{
		DEBUG_LOGLINE(Event, LOGWARN("Engine appears to have temporal Shader pointers!"));
		return INT32_MIN;
	}
	else
	{
		// Object exists... Do a comparison on the data?
		//DEBUG_LOGLINE(Event, LOG("Shader known as ID: " << loc->second));

		return loc->second;
	}
}

void D3DObjectManager::SetShader(void* pReturnPtr, EShaderTypes eShaderType)
{
	if (m_eCaptureState == ECaptureState::Capturing)
	{
		// Current Call
		auto curCall = GetCurrentFrame()->GetCurrentCall();
		auto shaderIndex = QueryShader(pReturnPtr);

		switch (eShaderType)
		{
		case EShaderTypes::Vertex:
			curCall->SetVertexShader(shaderIndex);
			break;
		case EShaderTypes::Hull:
			curCall->SetHullShader(shaderIndex);
			break;
		case EShaderTypes::Domain:
			curCall->SetDomainShader(shaderIndex);
			break;
		case EShaderTypes::Geometry:
			curCall->SetGeometryShader(shaderIndex);
			break;
		case EShaderTypes::Pixel:
			curCall->SetPixelShader(shaderIndex);
			break;
		case EShaderTypes::Compute:
			curCall->SetComputeShader(shaderIndex);
			break;
		case EShaderTypes::TOTAL_SHADER_TYPES:
			break;
		default:
			break;
		}
	}
}

CShader* D3DObjectManager::GetShader(uint32_t iShaderIndex)
{
	return &m_vShaders[iShaderIndex];
}

CBuffer* D3DObjectManager::GetBuffer(uint32_t iBufferIndex)
{
	return &m_vBuffers[iBufferIndex];
}

void D3DObjectManager::SerialiseShader(uint32_t uShaderIndex, std::string& strShaderName)
{
	// Check Validity
	if (uShaderIndex >= m_vShaders.size())
	{
		return;
	}

	// Go for write
	std::ofstream VSDWrite(strShaderName, std::ofstream::binary);


	auto shader = m_vShaders[uShaderIndex].m_vBytecode;

	ID3DBlob *disShader;
	D3DDisassemble(shader.data(), shader.size(),
		D3D_DISASM_ENABLE_COLOR_CODE |
		D3D_DISASM_ENABLE_INSTRUCTION_OFFSET | 
		D3D_DISASM_ENABLE_DEFAULT_VALUE_PRINTS,
		nullptr,
		&disShader
	);

	VSDWrite.write(reinterpret_cast<char*>(disShader->GetBufferPointer()), disShader->GetBufferSize());
}

void D3DObjectManager::SerialiseShaderBytecode(uint32_t uShaderIndex, std::string& strShaderName)
{
	// Check Validity
	if (uShaderIndex >= m_vShaders.size())
	{
		return;
	}

	// Go for write
	std::ofstream VSDWrite(strShaderName, std::ofstream::binary);

	auto shader = m_vShaders[uShaderIndex].m_vBytecode;

	VSDWrite.write(reinterpret_cast<char *>(shader.data()), shader.size());
}

void D3DObjectManager::AddBuffer(void* pReturnPtr, const void* pData, uint64_t uDataSize, uint32_t uBindType, D3D11CustomDevice* pOwningDevice)
{
	// Sanity
	if (!pReturnPtr)
	{
		DEBUG_LOGLINE(Event, LOGERR("AddBuffer called with bad return pointer"));
		return;
	}

	SCOPED_LOCK(m_mtxBuffers);

	auto loc = m_mBuffers.find(pReturnPtr);
	if (loc == m_mBuffers.end())
	{
		if (m_vBuffers.size() > INT32_MAX) { return; }

		// This shader does not exist, so create it
		int32_t bufferIndex = static_cast<int32_t>(m_vBuffers.size());
		m_mBuffers.emplace(pReturnPtr, bufferIndex);

		m_vBuffers.emplace_back(pReturnPtr, pData, uDataSize, uBindType, pOwningDevice);
		//m_vShaders.emplace_back(pReturnPtr, pBytecode, uBytecodeLength);
		DEBUG_LOGLINE(Event, LOG("Buffer registered to ID: " << bufferIndex));
	}
	else
	{
		// Object exists... Do a comparison on the data?
		DEBUG_LOGLINE(Event, LOGWARN("Buffer seen before. ID: " << loc->second << ". Next Index: " << m_vBuffers.size()));
	}
}

int32_t D3DObjectManager::QueryBuffer(void* pReturnPtr)
{
	if (!pReturnPtr)
	{
		return -1;
	}

	SCOPED_LOCK(m_mtxBuffers);

	auto loc = m_mBuffers.find(pReturnPtr);
	if (loc == m_mBuffers.end())
	{
		//DEBUG_LOGLINE(Event, LOGWARN("Engine appears to have temporal Buffer pointers!"));
		return INT32_MIN;
	}
	else
	{
		// Object exists... Do a comparison on the data?
		//DEBUG_LOGLINE(Event, LOG("Buffer known as ID: " << loc->second));
		return loc->second;
	}
}

void D3DObjectManager::SetBuffer(void* pReturnPtr, EBufferTypes eBufferType)
{
	if (m_eCaptureState == ECaptureState::Capturing)
	{
		// Current Call
		auto curCall = GetCurrentFrame()->GetCurrentCall();
		auto bufferIndex = QueryBuffer(pReturnPtr);

		switch (eBufferType)
		{
		case EBufferTypes::Vertex:
			curCall->AddVertexBuffer(bufferIndex);
			break;
		case EBufferTypes::Index:
			curCall->SetIndexBuffer(bufferIndex);
			break;
		case EBufferTypes::VertexConstant:
			curCall->AddVertexConstantBuffer(bufferIndex);
			break;
		case EBufferTypes::HullConstant:
			curCall->AddHullConstantBuffer(bufferIndex);
			break;
		case EBufferTypes::DomainConstant:
			curCall->AddDomainConstantBuffer(bufferIndex);
			break;
		case EBufferTypes::GeometryConstant:
			curCall->AddGeometryConstantBuffer(bufferIndex);
			break;
		case EBufferTypes::PixelConstant:
			curCall->AddPixelConstantBuffer(bufferIndex);
			break;
		case EBufferTypes::ComputeConstant:
			curCall->AddComputeConstantBuffer(bufferIndex);
			break;
		case EBufferTypes::TOTAL_SHADER_TYPES:
			break;
		default:
			break;
		}
	}
}

void D3DObjectManager::AddTexture(void* pReturnPtr, const D3D11_SUBRESOURCE_DATA* pData, FTextureInfo& texInfo, D3D11CustomDevice* pOwningDevice, bool bIsImmediate)
{
	// Sanity
	if (!pReturnPtr)
	{
		DEBUG_LOGLINE(Event, LOGERR("AddTexture called with bad return pointer"));
		return;
	}

	SCOPED_LOCK(m_mtxTextures);

	auto loc = m_mTextures.find(pReturnPtr);
	if (loc == m_mTextures.end())
	{
		if (m_vTextures.size() > INT32_MAX) { return; }

		// This shader does not exist, so create it
		int32_t bufferIndex = static_cast<int32_t>(m_vTextures.size());
		m_mTextures.emplace(pReturnPtr, bufferIndex);

		m_vTextures.emplace_back(pReturnPtr, pData, &texInfo, pOwningDevice, pOwningDevice);
		//m_vShaders.emplace_back(pReturnPtr, pBytecode, uBytecodeLength);
		DEBUG_LOGLINE(Event, LOG("Texture registered to ID: " << bufferIndex));
	}
	else
	{
		// Object exists... Do a comparison on the data?
		//DEBUG_LOGLINE(Event, LOGWARN("Texture seen before. ID: " << loc->second << ". Next Index: " << m_vTextures.size()));
	}
}

int32_t D3DObjectManager::QueryTexture(void* pReturnPtr)
{
	if (!pReturnPtr)
	{
		return -1;
	}

	SCOPED_LOCK(m_mtxTextures);

	auto loc = m_mTextures.find(pReturnPtr);
	if (loc == m_mTextures.end())
	{
		DEBUG_LOGLINE(Event, LOGWARN("Engine appears to have temporal Texture pointers!"));
		return INT32_MIN;
	}
	else
	{
		// Object exists... Do a comparison on the data?
		//DEBUG_LOGLINE(Event, LOG("Texture known as ID: " << loc->second));
		return loc->second;
	}
}

CTexture* D3DObjectManager::GetTexture(uint32_t iTexIndex)
{
	return &m_vTextures[iTexIndex];
}

void D3DObjectManager::AddResourceView(void* pReturnPtr, const void* pResPtr, EBackingType eBackingType)
{
	// Sanity
	if (!pReturnPtr)
	{
		DEBUG_LOGLINE(Event, LOGERR("AddResourceView called with bad return pointer"));
		return;
	}

	SCOPED_LOCK(m_mtxShaderResources);

	auto loc = m_mShaderResources.find(pReturnPtr);
	if (loc == m_mShaderResources.end())
	{
		if (m_vShaderResourceBackings.size() > INT32_MAX) { return; }

		// This shader does not exist, so create it
		int32_t bufferIndex = static_cast<int32_t>(m_vShaderResourceBackings.size());
		m_mShaderResources.emplace(pReturnPtr, bufferIndex);

		m_vShaderResourceBackings.emplace_back(pReturnPtr, pResPtr, eBackingType);
		//m_vShaders.emplace_back(pReturnPtr, pBytecode, uBytecodeLength);
		DEBUG_LOGLINE(Event, LOG("SRV registered to ID: " << bufferIndex));
	}
	else
	{
		// Object exists... Do a comparison on the data?
		//DEBUG_LOGLINE(Event, LOGWARN("SRV seen before. ID: " << loc->second << ". Next Index: " << m_vShaderResourceBackings.size()));
	}
}

int32_t D3DObjectManager::QueryResourceView(void* pReturnPtr)
{
	if (!pReturnPtr)
	{
		return -1;
	}

	SCOPED_LOCK(m_mtxShaderResources);

	auto loc = m_mShaderResources.find(pReturnPtr);
	if (loc == m_mShaderResources.end())
	{
		DEBUG_LOGLINE(Event, LOGWARN("Engine appears to have temporal SRV pointers!"));
		return INT32_MIN;
	}
	else
	{
		// Object exists... Do a comparison on the data?
		//DEBUG_LOGLINE(Event, LOG("SRV known as ID: " << loc->second));
		return loc->second;
	}
}

void D3DObjectManager::SetResourceView(void* pReturnPtr, ESRVTypes eBufferType)
{
	if (m_eCaptureState == ECaptureState::Capturing)
	{
		// Current Call
		auto curCall = GetCurrentFrame()->GetCurrentCall();
		auto SRVIndex = QueryResourceView(pReturnPtr);

		switch (eBufferType)
		{
		case ESRVTypes::VertexSRV:
			curCall->AddVertexShaderResources(SRVIndex);
			break;
		case ESRVTypes::HullSRV:
			curCall->AddHullShaderResources(SRVIndex);
			break;
		case ESRVTypes::DomainSRV:
			curCall->AddDomainShaderResources(SRVIndex);
			break;
		case ESRVTypes::GeometrySRV:
			curCall->AddGeometryShaderResources(SRVIndex);
			break;
		case ESRVTypes::PixelSRV:
			curCall->AddPixelShaderResources(SRVIndex);
			break;
		case ESRVTypes::ComputeSRV:
			curCall->AddComputeShaderResources(SRVIndex);
			break;
		case ESRVTypes::TOTAL_SHADER_TYPES:
			break;
		default:
			break;
		}
	}
}

CResourceBacking* D3DObjectManager::GetResourceView(uint32_t iSRVIndex)
{
	return &m_vShaderResourceBackings[iSRVIndex];
}

//void D3DObjectManager::setDevice(ID3D11Device* dev)
//{
//	m_device = dev;
//	//Event << "Device is " << ((m_device != nullptr) ? "VALID" : "INVALID") << std::endl;
//}
//
//void D3DObjectManager::setSwapChain(IDXGISwapChain* swapchain)
//{
//	m_swapchain = swapchain;
//}
