#include "d3d11DeviceContext.h"
#include <vector>
#include "Globals.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "d3d11Wrapper.h"
#include "d3d11Device.h"
#include "utils.h"

int primsCapd = 0;
int lastBufferByteWidth = 300;
bool bLookingForCapture = false;
extern D3D11Wrapper *d3dw;
extern bool doingBufferCap;
extern std::vector<IVBuffer*> bufList;

std::string direct;

enum FCAPSTATE
{
	FCAP_READY,
	FCAP_WAITING,
	FCAP_CAPTURING,
	FCAP_FINISHED,
	FCAP_TOTAL_STATES
};

FCAPSTATE fcCaptureState = FCAP_READY;

void D3D11CustomContext::Notify_Present()
{
	if (CurrentState == ECaptureState::Capture)
	{
		CurrentState = ECaptureState::Await;
	}

	if(CurrentState == ECaptureState::WaitingForPresent)
	{
		CurrentState = ECaptureState::Capture;
	}
}

D3D11CustomContext::D3D11CustomContext(ID3D11DeviceContext* devCon, ID3D11DeviceContext*** ret)
{
	m_devContext = devCon;
	*ret = &m_devContext;
}

D3D11CustomContext::D3D11CustomContext(ID3D11DeviceContext* devCon)
{
	m_devContext = devCon;
}

D3D11CustomContext::D3D11CustomContext(ID3D11DeviceContext* dev, D3D11CustomDevice* cdev, D3D11Wrapper * Parent)
{
	m_devContext = dev;
	CustomDevice = cdev;
	CustomDevice->Link(this);
	ParentWrapper = Parent;
}

void D3D11CustomContext::VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	// This sets the constant buffers. Dump them to disk.
	// Do we need a serialisation object?

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

void D3D11CustomContext::PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::VSSetShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	m_devContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

////////
std::string ResolveDirectory()
{
	HMODULE ModuleHandle = GetModuleHandle(nullptr);
	if (!ModuleHandle) return "";
	char fileName[1024];
	GetModuleFileNameA(ModuleHandle, fileName, _MAX_PATH);

	char driveName[_MAX_DRIVE + 1];
	char directoryName[_MAX_DIR + 1];
	::_splitpath_s(fileName,
		driveName, _MAX_DRIVE,
		directoryName, _MAX_DIR,
		NULL, 0,
		NULL, 0);
	return (std::string(driveName) + std::string(directoryName));
}

//void FCAPWriteMesh
//(
//	std::vector<FCAPVertex> &verts,
//	std::vector<FCAPFace> &faces
//)
//{
//	// Write using OBJ export
//	// Create output file stream
//	ofstream objStream(g_Context->MeshDirectory + "dcall" + std::to_string(g_Context->PrimitivesCaptured) + ".obj");
//	//objStream.setf(std::ios_base::fixed, std::ios_base::floatfield);
//	objStream << fixed << showpoint;
//	objStream << setprecision(8);
//	uint32_t i;
//
//	// Write all vert positions in VB order
//	for (i = 0; i < verts.size(); i++)
//	{
//		objStream << "v " << verts[i].position.x << " " << verts[i].position.y << " " << verts[i].position.z << " 1" << std::endl;
//	}
//
//	//// Write all texcoords in VB order
//	//for(i = 0; i < verts.size(); i++)
//	//{
//	//	objStream << "vt " << verts[i].texcoord.x << " " << verts[i].texcoord.y << std::endl;
//	//}
//
//	// Write all face normals (three verts will use each value here) in IB order
//	for (i = 0; i < faces.size(); i++)
//	{
//		objStream << "vn " << faces[i].normal.x << " " << faces[i].normal.y << " " << faces[i].normal.z << std::endl;
//	}
//
//	// Write all face data, using full desc
//	for (i = 0; i < faces.size(); i++)
//	{
//		// f v/vt/vn v/vt/vn v/vt/vn
//		objStream << "f "
//			// Vertex				Texcoord				Normal
//			<< 1 + faces[i].v0 << "/" << /*faces[i].v0 <<*/ "/" << i << " "
//			<< 1 + faces[i].v1 << "/" << /*faces[i].v1 <<*/ "/" << i << " "
//			<< 1 + faces[i].v2 << "/" << /*faces[i].v2 <<*/ "/" << i << std::endl;
//	}
//
//
//
//	objStream.close();
//	//g_Context->PrimitivesCaptured
//
//



void FCAPWriteMesh
(
	std::vector<FCAPVertex> &verts,
	std::vector<UINT> &indices
)
{
	// Write using OBJ export
	std::ofstream objStream(direct + "dcall" + std::to_string(primsCapd++) + ".obj");

	//objStream.setf(std::ios_base::fixed, std::ios_base::floatfield);
	objStream << std::fixed << std::showpoint;
	objStream << std::setprecision(8);
	uint32_t i;


	// Write all vert positions in VB order
	for (i = 0; i < verts.size(); i++)
	{
		objStream << "v " << verts[i].position.x * 0.1 << " " << verts[i].position.y * 0.1 << " " << verts[i].position.z * 0.1 << " 1" << std::endl;
	}

	// Write all face data, using full desc
	for (i = 0; i < indices.size() / 3; i++)
	{
		// f v/vt/vn v/vt/vn v/vt/vn
		objStream << "f " << 1 + indices[i * 3] << " " << 1 + indices[i * 3 + 1] << " " << 1 + indices[i * 3 + 2] << std::endl;
	}

	// Write all vert positions in VB order
	//for (i = 0; i < verts.size(); i++)
	//{
	//	objStream << "v " << verts[i].position.x << " " << verts[i].position.y << " " << verts[i].position.z << " 1" << std::endl;
	//}

	//// Write all face data, using full desc
	//for (i = 0; i < faces.size(); i++)
	//{
	//	// f v/vt/vn v/vt/vn v/vt/vn
	//	objStream << "f "
	//		// Vertex				Texcoord				Normal
	//		<< faces[i].v0 << " "
	//		<< faces[i].v1 << " "
	//		<< faces[i].v2 << std::endl;
	//}

	objStream.close();
	//g_Context->PrimitivesCaptured


}

//////////////////////////////////////////////////////////////////////////
// PERFORMANCE CRITICAL
// Capture Logic Mapping Segment
//
void FCapMeshLogicMapSegment(ID3D11Device* Device, ID3D11DeviceContext *DevC, UINT VertexIndexOffset, INT BaseVertexIndex, void *IndexBuffer, void *VertexBuffer, UINT Stride, UINT Offset, UINT IndexCount)
{
	// Maybe not the fastest this function could be, but good to get a ground truth first

	// For OBJ export, we need vertex indices, vertex positions and vertex normals
	// For this we need to work in faces not vertices

	/*std::ofstream dumpVB("dump" + std::to_string(primsCapd) + ".vb");
	std::ofstream dumpIB("dump" + std::to_string(primsCapd) + ".ib");
	std::ofstream dumpInfoB("dump" + std::to_string(primsCapd) + ".info", std::ios_base::app);*/

	// Predefinied Variables
	std::vector<FCAPVertex> vertices;
	//vertices.reserve(PrimitiveCount * 3);
	//std::vector<FCAPFace> faces;
	//faces.reserve(PrimitiveCount);
	std::vector<UINT> indices;
	//indices.reserve(PrimitiveCount * 3);
	//faces.reserve(PrimitiveCount);

	std::cout << "\rRipping object " << primsCapd << ", 0%\t\t\t\t";
	//// Scoped Variables
	////{
	////	UINT vt0,vt1,vt2;
	////	Vec3f normal, du, dv;
	////	void *vert;
	////	void *uv;
	////	float x, y, z, u, v;
	////	//FCAPVertex fcv0, fcv1, fcv2;
	////	Vec3f vt0_vc3, vt1_vc3, vt2_vc3;
	////	UINT vt0_idx, vt1_idx, vt2_idx;
	////	// Buffer for index
	////	std::vector<UINT>::iterator rmIter;
	////	std::vector<UINT> indexMap;
	////	//std::vector<UINT> indices;
	////	/// Iterate over the index buffer creating face information and vertex normal for the face
	////	for (UINT i = 0; i < PrimitiveCount; i++) // For all faces
	////	{
	////		/// Faces
	////		// Get 3 vertices that make the face from Index Buffer
	////		// These are locations in the vertices structure
	////		vt0 = IndexBuffer[VertexIndexOffset + i * 3] + BaseVertexIndex + MinIndex;
	////		rmIter = std::find(indexMap.begin(), indexMap.end(), vt0);
	////		if(rmIter == indexMap.end())
	////		{
	////			// Add the element
	////			indexMap.push_back(vt0);
	////			vert = reinterpret_cast<void *>(reinterpret_cast<uint8_t *>(VertexBuffer) + Stride * vt0);
	////			// Vert0 Data
	////			x = static_cast<float *>(vert)[0];
	////			y = static_cast<float *>(vert)[1];
	////			z = static_cast<float *>(vert)[2];
	////			uv = static_cast<void *>(static_cast<uint8_t *>(vert) + Stride - 2 * sizeof(float));
	////			u = static_cast<float *>(uv)[0];
	////			v = static_cast<float *>(uv)[1];
	////			vt0_vc3 = Vec3f(x, y, z);
	////			vertices.push_back(FCAPVertex(vt0_vc3, Vec2f(u, v)));
	////			//indices.push_back(static_cast<UINT>(indexMap.size() - 1));
	////			vt0_idx = static_cast<UINT>(indexMap.size() - 1);
	////		}
	////		else
	////		{
	////			vt0_idx = static_cast<UINT>(std::distance(indexMap.begin(), rmIter));
	////			//indices.push_back(indexer);
	////			vt0_vc3 = vertices[vt0_idx].position;
	////		}
	////		vt1 = IndexBuffer[VertexIndexOffset + 1 + i * 3] + BaseVertexIndex + MinIndex;
	////		rmIter = std::find(indexMap.begin(), indexMap.end(), vt1);
	////		if (rmIter == indexMap.end())
	////		{
	////			// Add the element
	////			indexMap.push_back(vt1);
	////			vert = reinterpret_cast<void *>(reinterpret_cast<uint8_t *>(VertexBuffer) + Stride * vt0);
	////			// Vert0 Data
	////			x = static_cast<float *>(vert)[0];
	////			y = static_cast<float *>(vert)[1];
	////			z = static_cast<float *>(vert)[2];
	////			uv = static_cast<void *>(static_cast<uint8_t *>(vert) + Stride - 2 * sizeof(float));
	////			u = static_cast<float *>(uv)[0];
	////			v = static_cast<float *>(uv)[1];
	////			vt1_vc3 = Vec3f(x, y, z);
	////			vertices.push_back(FCAPVertex(vt1_vc3, Vec2f(u, v)));
	////			//indices.push_back(static_cast<UINT>(indexMap.size() - 1));
	////			vt1_idx = static_cast<UINT>(indexMap.size() - 1);
	////		}
	////		else
	////		{
	////			vt1_idx = static_cast<UINT>(std::distance(indexMap.begin(), rmIter));
	////			vt1_vc3 = vertices[vt1_idx].position;
	////		
	////		vt2 = IndexBuffer[VertexIndexOffset + 2 + i * 3] + BaseVertexIndex + MinIndex;
	////		rmIter = std::find(indexMap.begin(), indexMap.end(), vt2);
	////		if (rmIter == indexMap.end())
	////		{
	////			// Add the element
	////			indexMap.push_back(vt2);
	////			vert = reinterpret_cast<void *>(reinterpret_cast<uint8_t *>(VertexBuffer) + Stride * vt0);
	////			// Vert0 Data
	////			x = static_cast<float *>(vert)[0];
	////			y = static_cast<float *>(vert)[1];
	////			z = static_cast<float *>(vert)[2];
	////			uv = static_cast<void *>(static_cast<uint8_t *>(vert) + Stride - 2 * sizeof(float));
	////			u = static_cast<float *>(uv)[0];
	////			v = static_cast<float *>(uv)[1];
	////			vt2_vc3 = Vec3f(x, y, z);
	////			vertices.push_back(FCAPVertex(vt2_vc3, Vec2f(u, v)));
	////			//indices.push_back(static_cast<UINT>(indexMap.size() - 1));
	////			vt2_idx = static_cast<UINT>(indexMap.size() - 1);
	////		}
	////		else
	////		{
	////			vt2_idx = static_cast<UINT>(std::distance(indexMap.begin(), rmIter));
	////			vt2_vc3 = vertices[vt2_idx].position;
	////		
	////		// Vertex Normal Calculation
	////		// Normals //
	////		// du = p1 - p0; //
	////		// dv - p2 - p0; //
	////		// n = du X dv // 
	////		// where n is normalised //
	////		du = vertices[vt1_idx].position - vertices[vt0_idx].position;
	////		dv = vertices[vt2_idx].position - vertices[vt0_idx].position;
	////		normal = Vec3f::Normalize(Vec3f::Cross(du, dv))
	////		faces.push_back(FCAPFace(vt0_idx,vt1_idx,vt2_idx,normal));
	////		dumpInfoB << vt0_idx << " " << vt1_idx << " " << vt2_idx << endl;
	////	}
	////}

	//std::cout << "\rStride of " << Stride << std::endl;
	//d3dw->Event << "Using Stride of " << Stride << std::endl;
	//d3dw->Event << "Using BaseVertexIndex of " << BaseVertexIndex << std::endl;
	//d3dw->Event << "VertexIndexOffset: " << VertexIndexOffset << std::endl;
	//d3dw->Event << "Using Offset of " << Offset << std::endl;

	if (Stride < (sizeof(float) * 3)) return;

	std::vector<uint16_t> indexMap;
	for (uint16_t i = 0; i < IndexCount; ++i) {
		if((i % 10000) == 0) std::cout << "\r" << "Ripping object " << primsCapd << ", " << i / static_cast<float>(IndexCount + 1) << "%\t\t\t\t";
		//d3dw->Event << "Adding to Map " << i << std::endl;
		//d3dw->Event << std::hex << IndexBuffer << std::endl;
		uint16_t a = reinterpret_cast<uint16_t*>(IndexBuffer)[VertexIndexOffset + i] + BaseVertexIndex;// +Offset;
		//dumpIB << i << ": " << a << std::endl;
		if (a == UINT32_MAX) continue; // Skip this invalid index
		std::vector<uint16_t>::iterator it = std::find(indexMap.begin(), indexMap.end(), a);
		if (it == indexMap.end()) {
			indexMap.push_back(a);

			void *vertexInfo = reinterpret_cast<void *>(reinterpret_cast<uint8_t *>(VertexBuffer) + Stride * a);
			float x = ((float *)vertexInfo)[0];
			float y = ((float *)vertexInfo)[1];
			float z = ((float *)vertexInfo)[2];
			//void *uv = (void *)((uint8_t *)vertexInfo + Stride - 2 * sizeof(float));
			//float u = ((float *)uv)[0];
			//float v = ((float *)uv)[1];
			//dumpVB << x << " " << y << " " << z << std::endl;
			vertices.push_back(FCAPVertex(Vec3f(x, y, z), Vec2f(0, 0)));
			//textureCoordList.push_back(Vec2f(u, v));
			indices.push_back((uint16_t)(indexMap.size() - 1));
			//dumpInfoB << "Addr " << a << " is now indexed as " << indexMap.size() - 1 << endl;
		}
		else {
			//dumpInfoB << "Addr " << a << " already in index at location " << std::distance(indexMap.begin(), it) << std::endl;
			indices.push_back((uint16_t)std::distance(indexMap.begin(), it));
		}
	}

	// Write to file, pass of as
	//FCAPWriteMesh(vertices, faces);
	FCAPWriteMesh(vertices, indices);

	//g_Context->Graphics.Device().get
}

//////////////////////////////////////////////////////////////////////////
// PERFORMANCE CRITICAL
// Capture Logic Vertex Segment
//
void FCapMeshLogicVertexOnlySegment(ID3D11Device* Device, ID3D11DeviceContext *DevC, UINT VertexIndexOffset, UINT VertexCount)
{
	return;
	ID3D11Buffer *vBufs;
	DXGI_FORMAT temp;
	UINT Stride;
	UINT Offset;
	DevC->IAGetVertexBuffers(0, 1, &vBufs, &Stride, &Offset);

	std::cout << "vBufs Valid: " << ((vBufs) ? "Yes" : "No") << std::endl;
	if (!vBufs) return;

	d3dw->Event << "vBufs Valid : " << ((vBufs) ? "Yes" : "No") << std::endl << "Stride: " << Stride << std::endl;

	/// CREATE CPUSIDE BUFFER
	D3D11_BUFFER_DESC ciBuf;
	ID3D11Buffer *cpuIB;
	vBufs->GetDesc(&ciBuf);



	D3D11_BUFFER_DESC i_buffer_desc;
	i_buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
	i_buffer_desc.BindFlags = 0;
	i_buffer_desc.ByteWidth = ciBuf.ByteWidth;
	i_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	i_buffer_desc.MiscFlags = 0;
	i_buffer_desc.StructureByteStride = ciBuf.StructureByteStride;

	char* ciarr = new char[ciBuf.ByteWidth];
	ZeroMemory(ciarr, ciBuf.ByteWidth);

	D3D11_SUBRESOURCE_DATA ini_data;
	ini_data.pSysMem = ciarr;
	ini_data.SysMemPitch = 0;
	ini_data.SysMemSlicePitch = 0;

	Device->CreateBuffer(&i_buffer_desc, &ini_data, &cpuIB);

	DevC->CopyResource(cpuIB, vBufs);



	// foreach
	D3D11_MAPPED_SUBRESOURCE ms;
	DevC->Map(cpuIB, NULL, D3D11_MAP_READ, NULL, &ms);

	if (!ms.pData)
	{
		std::cout << "vData is null" << std::endl;
		return;
	}

	/// Continue down the rabbit hole
	std::ofstream objStream("dcall" + std::to_string(primsCapd++) + ".obj");
	std::ofstream testStream("format" + std::to_string(primsCapd) + ".fmt", std::ios::binary);
	//objStream.setf(std::ios_base::fixed, std::ios_base::floatfield);
	objStream << std::fixed << std::showpoint;
	objStream << std::setprecision(8);
	uint32_t i;

	testStream.write((char*)ms.pData + VertexIndexOffset, Stride);
	testStream.close();

	for (i = 0; i < VertexCount; ++i)
	{
		void *vertexInfo = reinterpret_cast<void *>(reinterpret_cast<uint8_t *>(ms.pData) + (Stride * i) + VertexIndexOffset);
		float x = ((float *)vertexInfo)[0];
		float y = ((float *)vertexInfo)[1];
		float z = ((float *)vertexInfo)[2];
		//void *uv = (void *)((uint8_t *)vertexInfo + Stride - 2 * sizeof(float));
		//float u = ((float *)uv)[0];
		//float v = ((float *)uv)[1];
		objStream << "v " << x << " " << y << " " << z << " 1" << std::endl;
	}


	for (i = 0; i < VertexCount; ++i)
	{
		objStream << "f " << i << " " << (i + 1) << " " << (i + 2) << std::endl;
	}

	objStream.close();

	/// Unlock and release buffers
	DevC->Unmap(cpuIB, NULL);
	vBufs->Release();
	cpuIB->Release();
	delete[] ciarr;
}

//////////////////////////////////////////////////////////////////////////
// PERFORMANCE CRITICAL
// Capture Logic Vertex Segment
//
void FCapMeshLogicVertexSegment(ID3D11Device* Device, ID3D11DeviceContext *DevC, UINT VertexIndexOffset, INT BaseVertexIndex, void *IndexBuffer, UINT IndexCount)
{
	ID3D11Buffer *vBufs;
	DXGI_FORMAT temp;
	UINT Stride;
	UINT Offset;
	DevC->IAGetVertexBuffers(0, 1, &vBufs, &Stride, &Offset);

	//std::cout << "vBufs Valid: " << ((vBufs) ? "Yes" : "No") << std::endl;
	if (!vBufs) return;

	//d3dw->Event << "vBufs Valid : " << ((vBufs) ? "Yes" : "No") << std::endl << "Stride: " << Stride << std::endl;

	/// CREATE CPUSIDE BUFFER
	D3D11_BUFFER_DESC ciBuf;
	ID3D11Buffer *cpuIB;
	vBufs->GetDesc(&ciBuf);



	D3D11_BUFFER_DESC i_buffer_desc;
	i_buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
	i_buffer_desc.BindFlags = 0;
	i_buffer_desc.ByteWidth = ciBuf.ByteWidth;
	i_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	i_buffer_desc.MiscFlags = 0;
	i_buffer_desc.StructureByteStride = ciBuf.StructureByteStride;

	char* ciarr = new char[ciBuf.ByteWidth];
	ZeroMemory(ciarr, ciBuf.ByteWidth);

	D3D11_SUBRESOURCE_DATA ini_data;
	ini_data.pSysMem = ciarr;
	ini_data.SysMemPitch = 0;
	ini_data.SysMemSlicePitch = 0;

	Device->CreateBuffer(&i_buffer_desc, &ini_data, &cpuIB);

	DevC->CopyResource(cpuIB, vBufs);



	// foreach
	D3D11_MAPPED_SUBRESOURCE ms;
	DevC->Map(cpuIB, NULL, D3D11_MAP_READ, NULL, &ms);

	if (!ms.pData)
	{
		std::cout << "vData is null" << std::endl;
		return;
	}
	//std::ofstream testStream("format" + std::to_string(primsCapd) + ".fmt", std::ios::binary);
	//testStream.write((char*)ms.pData + Offset, Stride);
	//testStream.close();

	/// Continue down the rabbit hole
	FCapMeshLogicMapSegment(Device, DevC, VertexIndexOffset, BaseVertexIndex, IndexBuffer, ms.pData, Stride, Offset, IndexCount);

	/// Unlock and release buffers
	DevC->Unmap(cpuIB, NULL);
	vBufs->Release();
	cpuIB->Release();
	delete[] ciarr;
}


//////////////////////////////////////////////////////////////////////////
// PERFORMANCE CRITICAL
// Capture Logic Index Segment
//
void FCapMeshLogicIndexSegment(ID3D11Device* Device, ID3D11DeviceContext* DevC, UINT VertexIndexOffset, INT BaseVertexIndex, UINT IndexCount)
{
	/// Get Index Buffer
	ID3D11Buffer *indexBuffer = nullptr;
	DXGI_FORMAT indBufFormat;
	UINT offset;
	DevC->IAGetIndexBuffer(&indexBuffer, &indBufFormat, &offset);
	//d3dw->Event << "iBufs Valid : " << ((indexBuffer) ? "Yes" : "No") << std::endl << "Offset: " << offset << std::endl;
	//std::cout << "iBufs Valid : " << ((indexBuffer) ? "Yes" : "No") << std::endl << "Offset: " << offset << std::endl;

	// TEMPORARILY HERE
	//ID3D11InputLayout *inpLayout = nullptr;
	//DevC->IAGetInputLayout(&inpLayout);

//	inpLayout.
	//DevC->IAGetPrimitiveTopology()

	///// Get Index Buffer Descriptions
	//D3D9Base::D3DINDEXBUFFER_DESC indexBufferDesciption;
	//if (indexBuffer->GetDesc(&indexBufferDesciption) != D3D_OK)
	//{
	//	indexBuffer->Release();
	//	return;
	//}

	///// Get Index Buffer Desc Formats
	//if (D3DFMT_INDEX16 != indexBufferDesciption.Format) {
	//	indexBuffer->Release();
	//	return;
	//}


	/// Get Index Buffer Data and lock the buffer
	//uint16_t *indexBufferData = nullptr;
	//if (indexBuffer->Lock(0, 0, reinterpret_cast<void **>(&indexBufferData), D3DLOCK_READONLY) != D3D_OK) {
	//	indexBuffer->Release();
	//	return;
	//}


	/// CREATE CPUSIDE BUFFER
	D3D11_BUFFER_DESC ciBuf;
	ID3D11Buffer *cpuIB;
	indexBuffer->GetDesc(&ciBuf);

	//d3dw->Event << "BUFFER MADE" << std::endl;

	D3D11_BUFFER_DESC i_buffer_desc;
	i_buffer_desc.Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
	i_buffer_desc.BindFlags = 0;
	i_buffer_desc.ByteWidth = ciBuf.ByteWidth;
	i_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	i_buffer_desc.MiscFlags = 0;
	i_buffer_desc.StructureByteStride = ciBuf.StructureByteStride;

	char* ciarr = new char[ciBuf.ByteWidth];
	ZeroMemory(ciarr, ciBuf.ByteWidth);

	D3D11_SUBRESOURCE_DATA ini_data;
	ini_data.pSysMem = ciarr;
	ini_data.SysMemPitch = 0;
	ini_data.SysMemSlicePitch = 0;

	Device->CreateBuffer(&i_buffer_desc, &ini_data, &cpuIB);
	//d3dw->Event << "BUFFER MADE" << std::endl;

	DevC->CopyResource(cpuIB, indexBuffer);
	//d3dw->Event << "BUFFER COPIED" << std::endl;

	//std::cout << (int)ciarr[0] << (int)ciarr[1000 % ciBuf.ByteWidth] << std::endl;

	D3D11_MAPPED_SUBRESOURCE ms;
	HRESULT h = DevC->Map(cpuIB, 0, D3D11_MAP::D3D11_MAP_READ, NULL, &ms);
	//std::cout << "iBufs Mapped" << std::endl;
	//d3dw->Event << h << std::endl;

	if (!ms.pData)
	{
		std::cout << "pData is null" << std::endl;
		return;
	}

	//std::cout << reinterpret_cast<UINT*>(ms.pData)[3] << std::endl;

	/// Continue down the rabbit hole
	FCapMeshLogicVertexSegment(Device, DevC, VertexIndexOffset, BaseVertexIndex, ms.pData, IndexCount);

	/// Unlock and release buffers
	//indexBuffer->Release();
	DevC->Unmap(cpuIB, NULL);
	indexBuffer->Release();
	delete[] ciarr;
	cpuIB->Release();
}

void FCAPALL()
{
	for (int i = 0; i < bufList.size(); ++i)
	{
		if (bufList[i]->bIsIndex && bufList[i]->bufferPointer)
		{
			std::ofstream objStream("Call_" + std::to_string(i) + ".indexObject");
			objStream.write(
				static_cast<char *>(
					const_cast<void *>(
						bufList[i]->bufferPointer
						)
					), bufList[i]->uSize);

			objStream.close();
		}
		else if (bufList[i]->bufferPointer)
		{
			std::ofstream vStream("CallV_" + std::to_string(i) + ".vertexObject");
			vStream.write(
				static_cast<char *>(
					const_cast<void *>(
						bufList[i]->bufferPointer
						)
					), bufList[i]->uSize);

			vStream.close();
		}
		else
		{
			std::cout << "Buffer " << primsCapd << " is null" << std::endl;
		}
	}
}

void D3D11CustomContext::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && CurrentState == ECaptureState::Await)
	{
		CurrentState = ECaptureState::WaitingForPresent;
	}

	if (CurrentState == ECaptureState::Capture)
	{
		direct = "INDEXED";
		bLookingForCapture = true;
		ID3D11Device* dev;
		this->GetDevice(&dev);

		FCapMeshLogicIndexSegment(dev, this, StartIndexLocation, BaseVertexLocation, IndexCount);
	}

	m_devContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void D3D11CustomContext::Draw(UINT VertexCount, UINT StartVertexLocation)
{
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && CurrentState == ECaptureState::Await)
	{
		CurrentState = ECaptureState::WaitingForPresent;
	}

	if (CurrentState == ECaptureState::Capture)
	{
		direct = "DF";
		bLookingForCapture = true;
		ID3D11Device* dev;
		this->GetDevice(&dev);

		FCapMeshLogicVertexOnlySegment(dev, this, StartVertexLocation, VertexCount);
	}
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
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && CurrentState == ECaptureState::Await)
	{
		CurrentState = ECaptureState::WaitingForPresent;
	}

	if (CurrentState == ECaptureState::Capture)
	{
		direct = "InstINDEXED";
		bLookingForCapture = true;
		ID3D11Device* dev;
		this->GetDevice(&dev);

		FCapMeshLogicIndexSegment(dev, this, StartIndexLocation, BaseVertexLocation, IndexCountPerInstance);
	}
	
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
	std::cout << "Auto draw call..." << std::endl;
	m_devContext->DrawAuto();
}

void D3D11CustomContext::DrawIndexedInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	m_devContext->DrawIndexedInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
}

void D3D11CustomContext::DrawInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
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
	m_devContext->HSSetShader(pHullShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::HSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->HSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	m_devContext->HSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void D3D11CustomContext::DSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	m_devContext->DSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void D3D11CustomContext::DSSetShader(ID3D11DomainShader* pDomainShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	m_devContext->DSSetShader(pDomainShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::DSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->DSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
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
	m_devContext->CSSetShader(pComputeShader, ppClassInstances, NumClassInstances);
}

void D3D11CustomContext::CSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	m_devContext->CSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void D3D11CustomContext::CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
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
	m_devContext->GetDevice(ppDevice);
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





