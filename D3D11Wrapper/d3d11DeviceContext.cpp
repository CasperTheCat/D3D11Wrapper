#include "d3d11DeviceContext.h"
#include <vector>
#include "Globals.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "d3d11ObjectManager.h"
#include "d3d11Device.h"
#include "utils.h"
#include <mutex>
#include <memory>

std::string DirectoryPrefix = "VMRDATA\\";

//extern D3DObjectManager *m_pGLOM;



void D3D11CustomContext::Notify_Present()
{
	////std::cout << "Present Notify" << std::endl;
	//if (CurrentState == ECaptureState::Capture)
	//{
	//	CurrentState = ECaptureState::Await;
	//	std::cout << "Captured Frame was presented. Switching to Await" << std::endl;
	//	infoOutput.close();
	//}

	//if (CurrentState == ECaptureState::WaitingForPresent)
	//{
	//	CurrentState = ECaptureState::Capture;
	//	resetPointerTable();
	//	std::cout << "Switching to Capture State" << std::endl;
	//	// Preemptively open a output stream
	//	infoOutput = std::ofstream(DirectoryPrefix + std::to_string(drawCallNumber) + ".vmrinfo");
	//	infoOutput << "BufferType, BufferSize, BufferStride, BindFlags, Usage, BufferOffset, VertexInfoStride, Redirect" << std::endl;
	//	vertexOutput = std::ofstream(DirectoryPrefix + std::to_string(vertexBufferNumber) + ".rinfo", std::ios::app);
	//}
}

//int D3D11CustomContext::SaveVBandIBFromDevice(ID3D11Device* Device, ID3D11DeviceContext* DevC, uint64_t * ibInUse)
//{
//	// Write out all of the info for the buffers and CSV header
//	D3D11_BUFFER_DESC ciBuf;
//	ID3D11Buffer *cpuIB;
//	ID3D11Buffer *vBufs;
//	UINT Stride;
//	UINT Offset;
//	ID3D11Buffer *indexBuffer = nullptr;
//	DXGI_FORMAT indBufFormat;
//	UINT offset1;
//
//
//	DevC->IAGetIndexBuffer(&indexBuffer, &indBufFormat, &offset1);
//	if (!indexBuffer) return 1;
//
//	// Check if the indexBufferTable, if things exist exist
//	{
//		const auto location = indexBufferTable.find(indexBuffer);
//		if (location == indexBufferTable.end())
//		{
//			// Emplace new buffer into map table
//			indexBufferTable.emplace(std::make_pair(indexBuffer, indexBufferNumber));
//			if(ibInUse)
//				*ibInUse = indexBufferNumber;
//			// Dump Buffer
//			indexBuffer->GetDesc(&ciBuf);
//
//			// CPU side buffer
//			D3D11_BUFFER_DESC i_buffer_desc;
//			i_buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
//			i_buffer_desc.BindFlags = 0;
//			i_buffer_desc.ByteWidth = ciBuf.ByteWidth;
//			i_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
//			i_buffer_desc.MiscFlags = 0;
//			i_buffer_desc.StructureByteStride = ciBuf.StructureByteStride;
//
//			// Output index buffer infomation
//			infoOutput << "Index," << ciBuf.ByteWidth << "," << ciBuf.StructureByteStride << "," << ciBuf.BindFlags << "," << ciBuf.Usage << "," << offset1 << ",0," << indexBufferNumber << std::endl;
//
//			// CPU Array
//			char* cpuibarr = new char[ciBuf.ByteWidth];
//			ZeroMemory(cpuibarr, ciBuf.ByteWidth);
//
//			// Create D3D11 Subresource
//			D3D11_SUBRESOURCE_DATA ini_data;
//			ini_data.pSysMem = cpuibarr;
//			ini_data.SysMemPitch = 0;
//			ini_data.SysMemSlicePitch = 0;
//
//			// Create the buffer and copy from the actual buffer to the new one
//			Device->CreateBuffer(&i_buffer_desc, &ini_data, &cpuIB);
//			DevC->CopyResource(cpuIB, indexBuffer);
//
//			// Use a mapped subresource to map the data to the CPU
//			D3D11_MAPPED_SUBRESOURCE ms;
//			HRESULT h = DevC->Map(cpuIB, 0, D3D11_MAP::D3D11_MAP_READ, NULL, &ms);
//
//			// Do this update BEFORE we can exit early. If the buffer is invalid, let it be invalid
//			std::ofstream ibOut(DirectoryPrefix + std::to_string(indexBufferNumber) + ".vmrib", std::ofstream::binary);
//			++indexBufferNumber;
//
//			if (ms.pData)
//			{
//				// Data is valid. Save it
//				ibOut.write(reinterpret_cast<char *>(ms.pData), ciBuf.ByteWidth);
//			}
//			else return 1;
//
//			/// Unlock and release buffers
//			DevC->Unmap(cpuIB, NULL);
//			indexBuffer->Release();
//			cpuIB->Release();
//			delete[] cpuibarr;
//		}
//		else
//		{
//			infoOutput << "Index," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << ",0," << location->second << std::endl;
//			if (ibInUse)
//				*ibInUse = location->second;
//		}
//	}
//
//
//	DevC->IAGetVertexBuffers(0, 1, &vBufs, &Stride, &Offset);
//	if (!vBufs) return 1;
//
//	{
//		const auto location = vertexBufferTable.find(vBufs);
//		if (location == vertexBufferTable.end())
//		{
//			// Add vertex structure to map
//			vertexBufferTable.emplace(std::make_pair(vBufs, vertexBufferNumber));
//
//			/// CREATE CPUSIDE BUFFER
//			vBufs->GetDesc(&ciBuf);
//			D3D11_BUFFER_DESC i_buffer_desc;
//			i_buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
//			i_buffer_desc.BindFlags = 0;
//			i_buffer_desc.ByteWidth = ciBuf.ByteWidth;
//			i_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
//			i_buffer_desc.MiscFlags = 0;
//			i_buffer_desc.StructureByteStride = ciBuf.StructureByteStride;
//
//			infoOutput << "Vertex," << ciBuf.ByteWidth << "," << ciBuf.StructureByteStride << "," << ciBuf.BindFlags << "," << ciBuf.Usage << "," << Offset << "," << Stride << "," << vertexBufferNumber << std::endl;
//			vertexOutput.close();
//			vertexOutput = std::ofstream(DirectoryPrefix + std::to_string(vertexBufferNumber) + ".rinfo", std::ios::app);
//			vertexOutput << "VertexInfo," << ciBuf.ByteWidth << "," << ciBuf.StructureByteStride << "," << ciBuf.BindFlags << "," << ciBuf.Usage << "," << Offset << "," << Stride << "," << vertexBufferNumber << std::endl;
//
//			char* ciarr = new char[ciBuf.ByteWidth];
//			ZeroMemory(ciarr, ciBuf.ByteWidth);
//
//			D3D11_SUBRESOURCE_DATA ini_data;
//			ini_data.pSysMem = ciarr;
//			ini_data.SysMemPitch = 0;
//			ini_data.SysMemSlicePitch = 0;
//
//
//			D3D11_MAPPED_SUBRESOURCE ms;
//			Device->CreateBuffer(&i_buffer_desc, &ini_data, &cpuIB);
//			DevC->CopyResource(cpuIB, vBufs);
//			DevC->Map(cpuIB, NULL, D3D11_MAP_READ, NULL, &ms);
//
//			std::ofstream vbOut(DirectoryPrefix + std::to_string(vertexBufferNumber) + ".vmrvb", std::ofstream::binary);
//			++vertexBufferNumber;
//
//			if (ms.pData)
//			{
//				vbOut.write(reinterpret_cast<char *>(ms.pData), ciBuf.ByteWidth);
//			}
//			else return 1;
//
//
//			DevC->Unmap(cpuIB, NULL);
//			vBufs->Release();
//			cpuIB->Release();
//			delete[] ciarr;
//		}
//		else
//		{
//			vBufs->GetDesc(&ciBuf);
//			infoOutput << "Vertex," << ciBuf.ByteWidth << "," << ciBuf.StructureByteStride << "," << ciBuf.BindFlags << "," << ciBuf.Usage << Offset << "," << Stride << "," << location->second << std::endl;
//			vertexOutput.close();
//			vertexOutput = std::ofstream(DirectoryPrefix + std::to_string(location->second) + ".rinfo", std::ios::app);
//		}
//	}
//
//	return 0;
//}

//int D3D11CustomContext::CheckVB(ID3D11Device* Device, ID3D11DeviceContext* DevC, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
//{
//	D3D11_BUFFER_DESC ciBuf;
//	ID3D11Buffer *vBufs;
//	ID3D11Buffer *cpuIB;
//	UINT Stride;
//	UINT Offset;
//
//	DevC->IAGetVertexBuffers(0, 1, &vBufs, &Stride, &Offset);
//	if (!vBufs) return 1;
//
//	{
//		const auto location = vertexBufferTable.find(vBufs);
//		if (location == vertexBufferTable.end())
//		{
//			// Add vertex structure to map
//			vertexBufferTable.emplace(std::make_pair(vBufs, vertexBufferNumber));
//
//			/// CREATE CPUSIDE BUFFER
//			vBufs->GetDesc(&ciBuf);
//			D3D11_BUFFER_DESC i_buffer_desc;
//			i_buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
//			i_buffer_desc.BindFlags = 0;
//			i_buffer_desc.ByteWidth = ciBuf.ByteWidth;
//			i_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
//			i_buffer_desc.MiscFlags = 0;
//			i_buffer_desc.StructureByteStride = ciBuf.StructureByteStride;
//
//			std::ofstream fileOut(DirectoryPrefix + std::to_string(vertexBufferNumber) + ".vmrvb.info", std::ios::app);
//			fileOut << "VertexInfo," << ciBuf.ByteWidth << "," << ciBuf.StructureByteStride << "," << ciBuf.BindFlags << "," << ciBuf.Usage << "," << Offset << std::endl;
//			// Log the draw too
//			fileOut << "DrawIndexed," << IndexCount << "," << StartIndexLocation << "," << BaseVertexLocation << std::endl;
//
//
//			char* ciarr = new char[ciBuf.ByteWidth];
//			ZeroMemory(ciarr, ciBuf.ByteWidth);
//
//			D3D11_SUBRESOURCE_DATA ini_data;
//			ini_data.pSysMem = ciarr;
//			ini_data.SysMemPitch = 0;
//			ini_data.SysMemSlicePitch = 0;
//
//
//			D3D11_MAPPED_SUBRESOURCE ms;
//			Device->CreateBuffer(&i_buffer_desc, &ini_data, &cpuIB);
//			DevC->CopyResource(cpuIB, vBufs);
//			DevC->Map(cpuIB, NULL, D3D11_MAP_READ, NULL, &ms);
//
//			if (ms.pData)
//			{
//				std::ofstream vbOut(DirectoryPrefix + std::to_string(vertexBufferNumber) + ".vmrvb", std::ofstream::binary);
//
//				vbOut.write(reinterpret_cast<char *>(ms.pData), ciBuf.ByteWidth);
//				++vertexBufferNumber;
//			}
//			else return 1;
//
//
//			DevC->Unmap(cpuIB, NULL);
//			vBufs->Release();
//			cpuIB->Release();
//			delete[] ciarr;
//		}
//		else
//		{
//			std::ofstream fileOut(DirectoryPrefix + std::to_string(vertexBufferNumber) + ".vmrvb.info", std::ios::app);
//			fileOut << "DrawIndexed," << IndexCount << "," << StartIndexLocation << "," << BaseVertexLocation << std::endl;
//			return 1;
//		}
//	}
//}
//
//int D3D11CustomContext::DumpVSConstBuffer(ID3D11Device* Device, ID3D11DeviceContext* DevC,
//	ID3D11Buffer* const * ppConstBuffer)
//{
//	return DumpVSConstBufferWithName(Device, DevC, ppConstBuffer, std::to_string(drawCallNumber) + "." + std::to_string(vsBufferNumber));
//}
//
//int D3D11CustomContext::DumpVSConstBufferWithName(ID3D11Device* Device, ID3D11DeviceContext* DevC,
//	ID3D11Buffer* const * ppConstBuffer, std::string name)
//{
//	if (!ppConstBuffer) return 1;
//
//	DEBUG_ONLY_PRINT("ppBuffer is Valid");
//
//	ID3D11Buffer* pBuffer = *ppConstBuffer;
//	if (!pBuffer) return 1;
//
//	DEBUG_ONLY_PRINT("pBuffer is Valid");
//
//	/// CREATE CPUSIDE BUFFER
//	D3D11_BUFFER_DESC ciBuf;
//	ID3D11Buffer *cpuIB;
//
//	pBuffer->GetDesc(&ciBuf);
//
//	DEBUG_ONLY_PRINT("Got Buffer Description");
//
//	D3D11_BUFFER_DESC i_buffer_desc;
//	i_buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
//	i_buffer_desc.BindFlags = 0;
//	i_buffer_desc.ByteWidth = ciBuf.ByteWidth;
//	i_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
//	i_buffer_desc.MiscFlags = 0;
//	i_buffer_desc.StructureByteStride = ciBuf.StructureByteStride;
//
//	DEBUG_ONLY_PRINT("Created CPU side buffer");
//
//	infoOutput << "Const," << ciBuf.ByteWidth << "," << ciBuf.StructureByteStride << "," << ciBuf.BindFlags << "," << ciBuf.Usage << ",0,0" << std::endl;
//
//	// CPU Array
//	char* cpuibarr = new char[ciBuf.ByteWidth];
//	ZeroMemory(cpuibarr, ciBuf.ByteWidth);
//
//	DEBUG_ONLY_PRINT("Allocated Arrays for data transfer");
//
//	// Create D3D11 Subresource
//	D3D11_SUBRESOURCE_DATA ini_data;
//	ini_data.pSysMem = cpuibarr;
//	ini_data.SysMemPitch = 0;
//	ini_data.SysMemSlicePitch = 0;
//
//	// Create the buffer and copy from the actual buffer to the new one
//	Device->CreateBuffer(&i_buffer_desc, &ini_data, &cpuIB);
//	DevC->CopyResource(cpuIB, pBuffer);
//
//	// Use a mapped subresource to map the data to the CPU
//	D3D11_MAPPED_SUBRESOURCE ms;
//	HRESULT h = DevC->Map(cpuIB, 0, D3D11_MAP::D3D11_MAP_READ, NULL, &ms);
//
//	if (ms.pData)
//	{
//		// Data is valid. Save it
//		std::ofstream ibOut(DirectoryPrefix + name + ".vmrcb", std::ofstream::binary);
//
//		ibOut.write(reinterpret_cast<char *>(ms.pData), ciBuf.ByteWidth);
//	}
//	else return 1;
//
//	/// Unlock and release buffers
//	DevC->Unmap(cpuIB, NULL);
//	pBuffer->Release();
//	delete[] cpuibarr;
//	cpuIB->Release();
//	return 0;
//}
//
//void D3D11CustomContext::CaptureDraw()
//{
//	if (CurrentState == ECaptureState::Capture)
//	{
//		ID3D11Device *dev;
//		GetDevice(&dev);
//
//		if (SaveVBandIBFromDevice(dev, m_devContext) == 1)
//		{
//			std::cout << "Error capturing buffers for Draw Call " << drawCallNumber << std::endl;
//		}
//
//		
//		infoOutput.close();
//		infoOutput = std::ofstream(DirectoryPrefix + std::to_string(drawCallNumber+1) + ".vmrinfo");
//		infoOutput << "BufferType, BufferSize, BufferStride, BindFlags, Usage, BufferOffset, VertexInfoStride, Redirect" << std::endl;
//	}
//}

void D3D11CustomContext::CommonInitialise()
{

}

D3D11CustomContext::D3D11CustomContext(ID3D11DeviceContext* devCon, ID3D11DeviceContext*** ret)
{
	CommonInitialise();
	m_devContext = devCon;
	*ret = &m_devContext;
	//m_eCurrentState = ECaptureState::Await;
}

D3D11CustomContext::D3D11CustomContext(ID3D11DeviceContext* devCon, D3DObjectManager* Parent)
{
	CommonInitialise();
	m_devContext = devCon;
	m_pGLOM = Parent;
	//m_eCurrentState = ECaptureState::Await;
}

D3D11CustomContext::D3D11CustomContext(ID3D11DeviceContext* dev, D3D11CustomDevice* cdev, D3DObjectManager * Parent)
{
	CommonInitialise();
	m_devContext = dev;
	m_pFalseDevice = cdev;
	m_pFalseDevice->Link(this);
	m_pGLOM = Parent;
	//m_eCurrentState = ECaptureState::Await;
}

void D3D11CustomContext::VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	for (uint32_t i = 0; i < NumBuffers; ++i)
	{
		m_pGLOM->SetBuffer(ppConstantBuffers[i], EBufferTypes::VertexConstant, StartSlot + i);
	}
	
	//if (CurrentState == ECaptureState::Capture)
	//{
	//	//std::cout << "Capturing " << NumBuffers << " Buffers" << std::endl;
	//	ID3D11Device *dev;
	//	GetDevice(&dev);

	//	for (uint32_t i = 0; i < NumBuffers; ++i)
	//	{
	//		// SpecialCasing
	//		/*if (NumBuffers == 14 && i == 11 && ppConstantBuffers[11] != nullptr)
	//		{
	//			std::cout << "AnimBinding is " << vsBufferNumber + i << std::endl;
	//			DumpVSConstBufferWithName(dev, m_devContext, &ppConstantBuffers[i], "AnimationData." + std::to_string(vsBufferNumber + i));
	//		}*/
	//		//else if (ppConstantBuffers[i])
	//		//	DumpVSConstBuffer(dev, m_devContext, &ppConstantBuffers[i]); // Don't use the abstract layer here
	//	}
	//}
	//
	//vsBufferNumber += NumBuffers;
	m_devContext->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::PSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	//DEBUG_LINE(m_pGLOM->Event, LOG("\tPSSetShaderResources"));

	for (uint32_t i = 0; i < NumViews; ++i)
	{
		m_pGLOM->SetResourceView(ppShaderResourceViews[i], ESRVTypes::PixelSRV, StartSlot + i);
	}

	m_devContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::PSSetShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	//DEBUG_LINE(m_pGLOM->Event, LOG("\tPSSetShader"));
	//m_pGLOM->QueryShader(pPixelShader);
	m_pGLOM->SetShader(pPixelShader, EShaderTypes::Pixel);
	m_devContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	//DEBUG_LINE(m_pGLOM->Event, LOG("\tPSSetSamplers"));
	m_devContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::VSSetShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	//DEBUG_LINE(m_pGLOM->Event, LOG("\tVSSetShader"));

	//m_pGLOM->QueryShader(pVertexShader);
	m_pGLOM->SetShader(pVertexShader, EShaderTypes::Vertex);

	//if (CurrentState == ECaptureState::Capture)
	//{
	//	auto location = VertexShaderMap.find(pVertexShader);
	//	if(location != VertexShaderMap.end())
	//		infoOutput << "VSShader,0,0,0,0,0,0,"<< location->second << std::endl;
	//}
	m_devContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	//DEBUG_LINE(m_pGLOM->Event, LOG("DrawIndexed"));
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000 && CurrentState == ECaptureState::Await)
	//{
	//	CurrentState = ECaptureState::WaitingForPresent;
	//	std::cout << "Changing Process State from Await to AwaitPresent" << std::endl;
	//}

	//if (CurrentState == ECaptureState::Capture)
	//{
	//	ID3D11Device *dev;
	//	GetDevice(&dev);

	//	//CheckVB(IndexCount, StartIndexLocation, BaseVertexLocation);
	//	uint64_t indexBufferID = 0;
	//	if (SaveVBandIBFromDevice(dev, m_devContext, &indexBufferID) == 1)
	//	{
	//		std::cout << "Error capturing buffers for Draw Call " << drawCallNumber << std::endl;
	//	}

	//	vertexOutput << "DrawIndexed," << indexBufferID << "," << IndexCount << "," << StartIndexLocation << "," << BaseVertexLocation << std::endl;

	//	// Last line of VMR is call info
	//	infoOutput << "DrawInfo," << IndexCount << "," << StartIndexLocation << "," << BaseVertexLocation << std::endl;
	//	infoOutput.close();
	//	infoOutput = std::ofstream(DirectoryPrefix + std::to_string(drawCallNumber + 1) + ".vmrinfo");
	//	infoOutput << "BufferType, BufferSize, BufferStride, BindFlags, Usage, BufferOffset, VertexInfoStride, Redirect" << std::endl;
	//}

	//++drawCallNumber;

	m_pGLOM->Notify_Draw(IndexCount, StartIndexLocation, BaseVertexLocation, ECallsTypes::DrawIndexed);
	m_devContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void D3D11CustomContext::Draw(UINT VertexCount, UINT StartVertexLocation)
{
	//DEBUG_LINE(m_pGLOM->Event, LOG("Draw"));
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000 && CurrentState == ECaptureState::Await)
	//{
	//	CurrentState = ECaptureState::WaitingForPresent;
	//}

	//CaptureDraw();
	//++drawCallNumber;
	m_pGLOM->Notify_Draw(0, VertexCount, StartVertexLocation, ECallsTypes::Draw);
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
	for (uint32_t i = 0; i < NumBuffers; ++i)
	{
		m_pGLOM->SetBuffer(ppConstantBuffers[i], EBufferTypes::PixelConstant, StartSlot + i);
	}
	m_devContext->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::IASetInputLayout(ID3D11InputLayout* pInputLayout)
{
	//if (CurrentState == ECaptureState::Capture)
	//{
	//	//std::ofstream infoOutput(DirectoryPrefix + std::to_string(drawCallNumber) + ".vmril");
	//	auto location = InputLayoutMap.find(pInputLayout);
	//	if (location != InputLayoutMap.end()) // No Item
	//	{
	//		// location->second;
	//		std::ofstream infoOutput(DirectoryPrefix + std::to_string(drawCallNumber) + ".vmril", std::ios::binary | std::ios::app);
	//		infoOutput << location->second << std::endl;
	//	}
	//}

	m_pGLOM->SetInputLayout(pInputLayout);

	m_devContext->IASetInputLayout(pInputLayout);
}

void D3D11CustomContext::IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
{
	for (uint32_t i = 0; i < NumBuffers; ++i)
	{
		m_pGLOM->SetBuffer(ppVertexBuffers[i], EBufferTypes::Vertex, StartSlot + i);
		//DEBUG_LOGLINE(m_pGLOM->Event, LOG("VertexBuffer Set with stride: " << pStrides[i] <<", Offset: " << pOffsets[i]));
		m_pGLOM->SetVertexMeta(StartSlot + i, pStrides[i], pOffsets[i]);
	}

	m_devContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void D3D11CustomContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
{
	m_pGLOM->SetBuffer(pIndexBuffer, EBufferTypes::Index, 0);
	m_devContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

void D3D11CustomContext::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
{
	//DEBUG_LINE(m_pGLOM->Event, LOG("DrawIndexedInstanced"));
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000 && CurrentState == ECaptureState::Await)
	//{
	//	CurrentState = ECaptureState::WaitingForPresent;
	//}

	//if (CurrentState == ECaptureState::Capture)
	//{
	//	ID3D11Device *dev;
	//	GetDevice(&dev);

	//	//CheckVB(IndexCount, StartIndexLocation, BaseVertexLocation);
	//	uint64_t indexBufferID = 0;
	//	if (SaveVBandIBFromDevice(dev, m_devContext, &indexBufferID) == 1)
	//	{
	//		std::cout << "Error capturing buffers for Draw Call " << drawCallNumber << std::endl;
	//	}

	//	vertexOutput << "DrawIndexed," << indexBufferID << "," << IndexCountPerInstance << "," << StartIndexLocation << "," << BaseVertexLocation << std::endl;

	//	// Last line of VMR is call info
	//	infoOutput << "DrawInfo," << IndexCountPerInstance << "," << StartIndexLocation << "," << BaseVertexLocation << std::endl;
	//	infoOutput.close();
	//	infoOutput = std::ofstream(DirectoryPrefix + std::to_string(drawCallNumber + 1) + ".vmrinfo");
	//	infoOutput << "BufferType, BufferSize, BufferStride, BindFlags, Usage, BufferOffset, VertexInfoStride, Redirect" << std::endl;
	//}

	//++drawCallNumber;
	m_pGLOM->Notify_Draw(IndexCountPerInstance, StartIndexLocation, BaseVertexLocation, ECallsTypes::DrawIndexedInstanced);
	m_devContext->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

void D3D11CustomContext::DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation)
{
	//DEBUG_LINE(m_pGLOM->Event, LOG("DrawInstanced"));
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000 && CurrentState == ECaptureState::Await)
	//{
	//	CurrentState = ECaptureState::WaitingForPresent;
	//}

	//CaptureDraw();
	//++drawCallNumber;
	m_pGLOM->Notify_Draw(0, VertexCountPerInstance, StartVertexLocation, ECallsTypes::DrawInstanced);
	m_devContext->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

void D3D11CustomContext::GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	for (uint32_t i = 0; i < NumBuffers; ++i)
	{
		m_pGLOM->SetBuffer(ppConstantBuffers[i], EBufferTypes::GeometryConstant, StartSlot + i);
	}
	m_devContext->GSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::GSSetShader(ID3D11GeometryShader* pShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	m_pGLOM->SetShader(pShader, EShaderTypes::Geometry);
	m_devContext->GSSetShader(pShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
{
	m_pGLOM->SetTopology(Topology);
	m_devContext->IASetPrimitiveTopology(Topology);
}

void D3D11CustomContext::VSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	for (uint32_t i = 0; i < NumViews; ++i)
	{
		m_pGLOM->SetResourceView(ppShaderResourceViews[i], ESRVTypes::VertexSRV, StartSlot + i);
	}
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
	m_pGLOM->Notify_Draw(0, 0, 0, ECallsTypes::DrawAuto);
	m_devContext->DrawAuto();
}

void D3D11CustomContext::DrawIndexedInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	m_pGLOM->Notify_Draw(0, 0, 0, ECallsTypes::DrawIndexedInstancedIndirect);
	m_devContext->DrawIndexedInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void D3D11CustomContext::DrawInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	m_pGLOM->Notify_Draw(0, 0, 0, ECallsTypes::DrawInstancedIndirect);
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
	m_pGLOM->SetShader(pHullShader, EShaderTypes::Hull);
	m_devContext->HSSetShader(pHullShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::HSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->HSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	for (uint32_t i = 0; i < NumBuffers; ++i)
	{
		m_pGLOM->SetBuffer(ppConstantBuffers[i], EBufferTypes::HullConstant, StartSlot + i);
	}
	m_devContext->HSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::DSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	m_devContext->DSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::DSSetShader(ID3D11DomainShader* pDomainShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	m_pGLOM->SetShader(pDomainShader, EShaderTypes::Domain);
	m_devContext->DSSetShader(pDomainShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::DSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->DSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	for (uint32_t i = 0; i < NumBuffers; ++i)
	{
		m_pGLOM->SetBuffer(ppConstantBuffers[i], EBufferTypes::DomainConstant, StartSlot + i);
	}
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
	m_pGLOM->SetShader(pComputeShader, EShaderTypes::Compute);
	m_devContext->CSSetShader(pComputeShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::CSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->CSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	for (uint32_t i = 0; i < NumBuffers; ++i)
	{
		m_pGLOM->SetBuffer(ppConstantBuffers[i], EBufferTypes::ComputeConstant, StartSlot + i);
	}
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
	return m_devContext->GetType();
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
	if (m_pFalseDevice)
	{
		*ppDevice = m_pFalseDevice;
	}
	else
	{
		m_devContext->GetDevice(ppDevice);
	}
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





