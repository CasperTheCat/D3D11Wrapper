#include "d3d11Device.h"
#include "Globals.h"
#include <iostream>
#include <string>
#include <vector>
//#include "lodepng.h"

#include <atomic>

//extern int lastBufferByteWidth;
//int iBufsCapd = 0;
//bool doingBufferCap = false;
//std::vector<IVBuffer*> bufList;
//uint64_t bufferNumber = 0;
//std::atomic<uint64_t> t2dNumber = 0;

//extern std::string DirectoryPrefix;

std::atomic<uint32_t> badAtomicBufferCounter;

D3D11CustomDevice::D3D11CustomDevice(ID3D11Device* dev, ID3D11Device*** ret)
{
	m_d3dDevice = dev;
	*ret = &m_d3dDevice;
	PostInitialise();
}

D3D11CustomDevice::D3D11CustomDevice(ID3D11Device* dev)
{
	m_d3dDevice = dev;
	PostInitialise();
}

D3D11CustomDevice::D3D11CustomDevice(ID3D11Device* dev, ID3D11Device*** ret, D3DObjectManager *pGlOM)
{
	m_d3dDevice = dev;
	m_pGLOM = pGlOM;
	*ret = &m_d3dDevice;
	PostInitialise();
}

D3D11CustomDevice::D3D11CustomDevice(ID3D11Device* dev, D3DObjectManager *pGlOM)
{
	m_d3dDevice = dev;
	m_pGLOM = pGlOM;
	PostInitialise();
}


void D3D11CustomDevice::PostInitialise()
{
	//m_pvpFrames = make_shared<vector<CFrame>>(vector<CFrame>());

	//nCapturedVSShaders = 0;
	//nCapturedFSShaders = 0;
	//nBuffersCaptured = 0;

	/////////
	//// 2018.03.09 - Write Layout to Disk
	//////
	//ILWrite = std::ofstream("InputLayouts.csv", std::ofstream::binary);
	//ILWrite << "SemanticName,SemanticIndex,Format,InputSlot,AlignedByteOffset,InputSlotClass,InstanceDataStepRate" << std::endl;

	//m_log = std::ofstream("Device" + std::to_string(uint64_t(this)) + ".log", std::ofstream::binary);
}

void D3D11CustomDevice::Notify_Present()
{
	m_pGLOM->Notify_Present();
	if(CustomContext) CustomContext->Notify_Present();
	else std::cout << "NotifyPresent Called on nullptr" << std::endl;
}

void D3D11CustomDevice::Link(D3D11CustomContext* devCon)
{
	CustomContext = devCon;
}

void D3D11CustomDevice::LocateSwapchain()
{
	IDXGIDevice2* pDXGIDevice;
	auto hr = m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice2), (void**)&pDXGIDevice);

	IDXGIAdapter* pDXGIAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pDXGIAdapter);

	IDXGIFactory2* pIDXGIFactory;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&pIDXGIFactory);
}

ID3D11Device* D3D11CustomDevice::RealDevice()
{
	return m_d3dDevice;
}

ID3D11DeviceContext* D3D11CustomDevice::RealContext()
{
	return CustomContext->m_devContext;
}

D3DObjectManager* D3D11CustomDevice::GetGLOM()
{
	return m_pGLOM;
}

HRESULT D3D11CustomDevice::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer)
{
	//bool CPUHasAccess = true;
	bool CanCaptureImmediate = false;
	//D3D11_BUFFER_DESC falseDesc{};

	//falseDesc.ByteWidth = pDesc->ByteWidth;
	//
	///////
	//// Usage Handling
	////
	//auto bufferType = pDesc->Usage;
	//falseDesc.Usage = pDesc->Usage;

	switch(pDesc->Usage)
	{
	case D3D11_USAGE_DEFAULT:
		break;
	case D3D11_USAGE_IMMUTABLE:
		CanCaptureImmediate = true;
		break;
	case D3D11_USAGE_DYNAMIC:
		// We are going to lose this pointer if it gets passed
		// This one needs changed
		//falseDesc.Usage = D3D11_USAGE_STAGING;
		break;
	case D3D11_USAGE_STAGING:
		break;
	default:
		break;
	}


	///////
	//// BindFlags
	////
	//falseDesc.BindFlags = pDesc->BindFlags;


	///////
	//// CPU Access
	//falseDesc.CPUAccessFlags = pDesc->CPUAccessFlags;
	//falseDesc.MiscFlags = pDesc->MiscFlags;
	//falseDesc.StructureByteStride = pDesc->StructureByteStride;

	auto ret = m_d3dDevice->CreateBuffer(pDesc, pInitialData, ppBuffer);
	if (ret == S_OK)
	{
		if (CanCaptureImmediate)
		{
			// Do immediate copy
			m_pGLOM->AddBuffer(*ppBuffer, pInitialData->pSysMem, pDesc->ByteWidth, pDesc->BindFlags, this);
		}
		else
		{
			m_pGLOM->AddBuffer(*ppBuffer, nullptr, 0, pDesc->BindFlags, this);
		}

		//if (pInitialData && pInitialData->pSysMem && pDesc->BindFlags & D3D11_BIND_VERTEX_BUFFER)
		//{
		//	auto hi = const_cast<D3D11_BUFFER_DESC*>(pDesc);
		//	// Write
		//	std::ofstream serial(std::to_string(badAtomicBufferCounter++) + ".vbuf", std::ios::out | std::ios::binary);

		//	serial.write(
		//		reinterpret_cast<char*>(&hi->StructureByteStride),
		//		sizeof(uint32_t)
		//	);

		//	serial.write(
		//		reinterpret_cast<char*>(&hi->ByteWidth),
		//		sizeof(uint32_t)
		//	);

		//	serial.write(
		//		reinterpret_cast<char*>(const_cast<void *>(pInitialData->pSysMem)),
		//		pDesc->ByteWidth
		//	);
		//	serial.close();
		//}
	}

	
	return ret;

	//if(pDesc->BindFlags & D3D11_BIND_INDEX_BUFFER)
	//{
	//	std::cout << "Registering Index Buffer" << std::endl;
	//	bufList.push_back(new IVBuffer(const_cast<D3D11_SUBRESOURCE_DATA*>(pInitialData), pDesc->ByteWidth, true, false));
	//}

	//if(pDesc->BindFlags & D3D11_BIND_VERTEX_BUFFER)
	//{ 
	//	std::cout << "Registering Vertex Buffer" << std::endl;
	//	if(bufList[bufList.size() - 1]->bIsIndex)
	//	{
	//		std::cout << "\tadded as buffer pair" << std::endl;
	//		bufList[bufList.size() - 1]->bHasVertex = true;
	//	}
	//	bufList.push_back(new IVBuffer(const_cast<D3D11_SUBRESOURCE_DATA*>(pInitialData), pDesc->ByteWidth, false, false));
	//}
	//if ((pDesc->BindFlags & (D3D11_BIND_INDEX_BUFFER | D3D11_BIND_VERTEX_BUFFER)) && (pDesc->Usage == 0))
	//{
	//	std::cout << "Adding read to buffer" << std::endl;
	//	//std::cout << pDesc->Usage << std::endl;
	//	
	//	const_cast<D3D11_BUFFER_DESC*>(pDesc)->Usage = D3D11_USAGE_DYNAMIC;
	//	const_cast<D3D11_BUFFER_DESC*>(pDesc)->CPUAccessFlags |= D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	//}

	//if (pDesc->BindFlags & D3D11_BIND_INDEX_BUFFER)
	//{
	//	std::cout << "Dynamicing Index Buffer" << std::endl;
	//	////lastBufferByteWidth = pDesc->ByteWidth;
	//	////std::ofstream objStream("Call_" + std::to_string(iBufsCapd++) + ".bufferObject");
	//	//if (pDesc->Usage != D3D11_USAGE_DEFAULT && pDesc->CPUAccessFlags != D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE)
	//	//{
	//	//	const_cast<D3D11_BUFFER_DESC*>(pDesc)->Usage = D3D11_USAGE_DYNAMIC; 
	//	//	const_cast<D3D11_BUFFER_DESC*>(pDesc)->CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	//	//}
	//	//const void*const dank = pInitialData->pSysMem;
	//	//objStream.write(static_cast<char *>(pInitialData->pSysMem), pDesc->ByteWidth);
	//	//pInitialData->pSysMem;
	//	std::ofstream objStream("Call_" + std::to_string(iBufsCapd++) + ".bufferObject");
	//	if (!pInitialData) objStream << "What is this call?" << std::endl;
	//	else if (!pInitialData->pSysMem) objStream << "RIP" << std::endl;
	//	else objStream.write(static_cast<char *>(const_cast<void *>(pInitialData->pSysMem)), pDesc->ByteWidth);
	//	objStream.close();
	//}
	//if (pDesc->BindFlags & D3D11_BIND_VERTEX_BUFFER)
	//{
	//	std::cout << "Dynamicing Vert Buffer" << std::endl;
	//	////lastBufferByteWidth = pDesc->ByteWidth;
	//	////std::ofstream objStream("Call_" + std::to_string(iBufsCapd++) + ".bufferObject");
	//	if (pDesc->Usage != D3D11_USAGE_DEFAULT && pDesc->CPUAccessFlags != D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE)
	//	{
	//		const_cast<D3D11_BUFFER_DESC*>(pDesc)->Usage = D3D11_USAGE_DYNAMIC;
	//		const_cast<D3D11_BUFFER_DESC*>(pDesc)->CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	//	}
	//	//const void*const dank = pInitialData->pSysMem;
	//	//objStream.write(static_cast<char *>(pInitialData->pSysMem), pDesc->ByteWidth);
	//	//pInitialData->pSysMem;
	//	std::ofstream objStream("CallV_" + std::to_string(iBufsCapd++) + ".bufferObject");
	//	if (!pInitialData) objStream << "What is this call?" << std::endl;
	//	else if (!pInitialData->pSysMem) objStream << "RIP" << std::endl;
	//	else objStream.write(static_cast<char *>(const_cast<void *>(pInitialData->pSysMem)), pDesc->ByteWidth);
	//	objStream.close();
	//}
	//if ((GetAsyncKeyState(VK_UP) & 0x8000 || doingBufferCap) && iBufsCapd < 10)
	//{
	//	doingBufferCap = true;
	//	std::ofstream objStream("Call_" + std::to_string(iBufsCapd++) + ".bufferObject");
	//	objStream.write(static_cast<char *>(const_cast<void *>(pInitialData->pSysMem)), pDesc->ByteWidth);
	//	objStream.close();
	//}

	///////
	// 2018.03.05 - Capture buffers on creation
	// SIZE DEPENDANT
	///
	//++nBuffersSeen;
	//if(pDesc->ByteWidth > (1024 * 8) && pDesc->BindFlags & D3D11_BIND_CONSTANT_BUFFER)
	//{
	//	std::ofstream bcOut(std::to_string(nBuffersCaptured++) + "." + std::to_string(nBuffersSeen) + ".vmrbc", std::ofstream::binary);
	//	bcOut.write(reinterpret_cast<char *>(const_cast<D3D11_SUBRESOURCE_DATA *>(pInitialData)), pDesc->ByteWidth);
	//}

	// Register the buffer with GLOM?
}

HRESULT D3D11CustomDevice::CreateTexture1D(const D3D11_TEXTURE1D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture1D** ppTexture1D)
{
	auto ret = m_d3dDevice->CreateTexture1D(pDesc, pInitialData, ppTexture1D);

	// Only on success
	if (ret == S_OK && pDesc->BindFlags == D3D11_BIND_SHADER_RESOURCE)
	{
		// Our texture information
		FTextureInfo fTexInfo{};

		bool CanCaptureImmediate = false;
		if (pDesc->Usage == D3D11_USAGE_IMMUTABLE)
		{
			CanCaptureImmediate = true;
			if (!pInitialData) { DEBUG_LOGLINE(m_pGLOM->Event, LOGERR("NULLPTR in immut. Texture")); }
		}

		// Mip handling?
		// No, not yet, only 1 mip is assumed

		fTexInfo.uWidth = pDesc->Width;
		fTexInfo.uFormat = pDesc->Format;
		fTexInfo.uCount = pDesc->ArraySize;

		m_pGLOM->AddTexture(*ppTexture1D, pInitialData, fTexInfo, this, CanCaptureImmediate);
	}

	return ret;
}

HRESULT D3D11CustomDevice::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D)
{
	auto ret = m_d3dDevice->CreateTexture2D(pDesc, pInitialData, ppTexture2D);

	// Only on success
	if (ret == S_OK && pDesc->BindFlags == D3D11_BIND_SHADER_RESOURCE)
	{
		// Our texture information
		FTextureInfo fTexInfo{};

		bool CanCaptureImmediate = false;
		if (pDesc->Usage == D3D11_USAGE_IMMUTABLE)
		{
			CanCaptureImmediate = true;
			if (!pInitialData) { DEBUG_LOGLINE(m_pGLOM->Event, LOGERR("NULLPTR in immut. Texture")); }
		}

		// Mip handling?
		// No, not yet, only 1 mip is assumed

		fTexInfo.uWidth = pDesc->Width;
		fTexInfo.uHeight = pDesc->Height;
		fTexInfo.uFormat = pDesc->Format;
		fTexInfo.uCount = pDesc->ArraySize;

		m_pGLOM->AddTexture(*ppTexture2D, pInitialData, fTexInfo, this, CanCaptureImmediate);
	}

	//if ((pDesc->Format == DXGI_FORMAT_R8G8B8A8_UNORM
	//	|| pDesc->Format == DXGI_FORMAT_R8G8B8A8_UINT
	//	|| pDesc->Format == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB
	//	|| pDesc->Format == DXGI_FORMAT_R8G8B8A8_SNORM
	//	|| pDesc->Format == DXGI_FORMAT_R8G8B8A8_SINT
	//	|| pDesc->Format == DXGI_FORMAT_R8G8B8A8_TYPELESS

	//	|| pDesc->Format == DXGI_FORMAT_B8G8R8A8_TYPELESS
	//	|| pDesc->Format == DXGI_FORMAT_B8G8R8X8_TYPELESS
	//	|| pDesc->Format == DXGI_FORMAT_B8G8R8A8_UNORM
	//	|| pDesc->Format == DXGI_FORMAT_B8G8R8X8_UNORM
	//	|| pDesc->Format == DXGI_FORMAT_B8G8R8A8_UNORM_SRGB
	//	|| pDesc->Format == DXGI_FORMAT_B8G8R8X8_UNORM_SRGB


	//	) && pInitialData != nullptr
	//	)
	//{
	//	DEBUG_LINE(p_GLOM->Event, LOG"Attempting writeout: " << t2dNumber);

	//	std::ofstream ibOut(DirectoryPrefix + std::to_string(t2dNumber) + ".vmt2d", std::ofstream::binary);
	//	const auto nonConstSysMem = const_cast<void *>(pInitialData->pSysMem);
	//	const auto nonConstDesc = const_cast<D3D11_TEXTURE2D_DESC *>(pDesc);
	//	//writeBMP(nonConstSysMem, pDesc->Height, pDesc->Width);
	//	ibOut.write(reinterpret_cast<char *>(&(nonConstDesc->Width)), sizeof(uint32_t));
	//	ibOut.write(reinterpret_cast<char *>(&(nonConstDesc->Height)), sizeof(uint32_t));
	//	ibOut.write(reinterpret_cast<char *>(nonConstSysMem), pDesc->Width * pDesc->Height * 4);
	//	++t2dNumber;
	//}
	//
	//DEBUG_LINE(p_GLOM->Event, LOG"CreateTex2D Returning");

	return ret;
}

HRESULT D3D11CustomDevice::CreateTexture3D(const D3D11_TEXTURE3D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture3D** ppTexture3D)
{
	auto ret = m_d3dDevice->CreateTexture3D(pDesc, pInitialData, ppTexture3D);

	// Only on success
	if (ret == S_OK && pDesc->BindFlags == D3D11_BIND_SHADER_RESOURCE)
	{
		// Our texture information
		FTextureInfo fTexInfo{};

		bool CanCaptureImmediate = false;
		if (pDesc->Usage == D3D11_USAGE_IMMUTABLE)
		{
			CanCaptureImmediate = true;
			if (!pInitialData) { DEBUG_LOGLINE(m_pGLOM->Event, LOGERR("NULLPTR in immut. Texture")); }
		}

		// Mip handling?
		// No, not yet, only 1 mip is assumed

		fTexInfo.uWidth = pDesc->Width;
		fTexInfo.uHeight = pDesc->Height;
		fTexInfo.uDepth = pDesc->Depth;
		fTexInfo.uFormat = pDesc->Format;

		m_pGLOM->AddTexture(*ppTexture3D, pInitialData, fTexInfo, this, CanCaptureImmediate);
	}

	return ret;
}

HRESULT D3D11CustomDevice::CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView)
{
	auto ret = m_d3dDevice->CreateShaderResourceView(pResource, pDesc, ppSRView);

	if (ret == S_OK)
	{
		// Try all
		int32_t val;
		val = m_pGLOM->QueryBuffer(pResource);
		if (val >= 0)
		{
			m_pGLOM->AddResourceView(*ppSRView, pResource, EBackingType::Buffer);
		}
		
		val = m_pGLOM->QueryTexture(pResource);
		if (val >= 0)
		{
			m_pGLOM->AddResourceView(*ppSRView, pResource, EBackingType::Texture);
		}		
	}

	return ret;
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

//// 2018.03.09 - Define for ease of use
//#define pIED pInputElementDescs[i]
//#define Glue << "," <<

HRESULT D3D11CustomDevice::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout)
{
	/////////
	//// 2018.03.09 - Write Layout to Disk
	//////
	//for(uint32_t i = 0; i < NumElements; ++i)
	//	ILWrite << pIED.SemanticName Glue pIED.SemanticIndex Glue pIED.Format Glue pIED.InputSlot Glue pIED.AlignedByteOffset Glue pIED.InputSlotClass Glue pIED.InstanceDataStepRate << std::endl;
	//
	//ILWrite << ",,,,,," << std::endl;

	const auto ret = m_d3dDevice->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);

	if (ret == S_OK) { m_pGLOM->AddInputLayout(*ppInputLayout, pInputElementDescs, NumElements); }

	//InputLayoutMap.emplace(std::make_pair(*ppInputLayout, bufferNumber));
	//++bufferNumber;
	return ret;
}

HRESULT D3D11CustomDevice::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
{
	/////////
	//// 2018.03.05 - Write out the buffer
	//////
	//std::ofstream VSSWrite(DirectoryPrefix + std::to_string(nCapturedVSShaders) + ".VSS", std::ofstream::binary);
	//VSSWrite.write(reinterpret_cast<char*>(const_cast<void*>(pShaderBytecode)), BytecodeLength);

	//std::ofstream VSDWrite(DirectoryPrefix + std::to_string(nCapturedVSShaders) + ".VSD", std::ofstream::binary);

	//ID3DBlob *disShader;
	//D3DDisassemble(pShaderBytecode, BytecodeLength,
	//	D3D_DISASM_ENABLE_COLOR_CODE |
	//	D3D_DISASM_ENABLE_INSTRUCTION_OFFSET | 
	//	D3D_DISASM_ENABLE_DEFAULT_VALUE_PRINTS,
	//	nullptr,
	//	&disShader
	//);
	//
	//VSDWrite.write(reinterpret_cast<char*>(const_cast<void*>(disShader->GetBufferPointer())), disShader->GetBufferSize());

	auto ret = m_d3dDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);

	if (ret == S_OK) { m_pGLOM->AddShader(*ppVertexShader, pShaderBytecode, BytecodeLength); }

	return ret;
}

HRESULT D3D11CustomDevice::CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader)
{
	auto ret = m_d3dDevice->CreateGeometryShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);

	if (ret == S_OK) { m_pGLOM->AddShader(*ppGeometryShader, pShaderBytecode, BytecodeLength); }

	return ret;
}

HRESULT D3D11CustomDevice::CreateGeometryShaderWithStreamOutput(const void* pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY* pSODeclaration, UINT NumEntries, const UINT* pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader)
{
	auto ret = m_d3dDevice->CreateGeometryShaderWithStreamOutput(pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader);

	DEBUG_LOGLINE(m_pGLOM->Event, LOG("This shader needs buffer binding: StreamOutput"));

	if (ret == S_OK) { m_pGLOM->AddShader(*ppGeometryShader, pShaderBytecode, BytecodeLength); }

	return ret;
}

HRESULT D3D11CustomDevice::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
{
	auto ret = m_d3dDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);

	if (ret == S_OK) { m_pGLOM->AddShader(*ppPixelShader, pShaderBytecode, BytecodeLength); }

	return ret;
}

HRESULT D3D11CustomDevice::CreateHullShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11HullShader** ppHullShader)
{
	auto ret = m_d3dDevice->CreateHullShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);

	if (ret == S_OK) { m_pGLOM->AddShader(*ppHullShader, pShaderBytecode, BytecodeLength); }

	return ret;
}

HRESULT D3D11CustomDevice::CreateDomainShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11DomainShader** ppDomainShader)
{
	auto ret = m_d3dDevice->CreateDomainShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);

	if (ret == S_OK) { m_pGLOM->AddShader(*ppDomainShader, pShaderBytecode, BytecodeLength); }

	return ret;
}

HRESULT D3D11CustomDevice::CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11ComputeShader** ppComputeShader)
{
	auto ret = m_d3dDevice->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);

	if (ret == S_OK) { m_pGLOM->AddShader(*ppComputeShader, pShaderBytecode, BytecodeLength); }

	return ret;
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
	//return m_d3dDevice->GetImmediateContext(ppImmediateContext);

	///////
	// 2018.03.05 - Returning wrapped context
	////
	if (CustomContext) *ppImmediateContext = CustomContext;
	else m_d3dDevice->GetImmediateContext(ppImmediateContext);
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
	DEBUG_LOGLINE(m_pGLOM->Event, "[CF99] QI");

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

