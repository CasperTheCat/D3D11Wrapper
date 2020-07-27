#include "d3d9Device.h"

#include <d3dcompiler.h>
#include <atomic>
#include <string>
#include <iostream>
#include <fstream>
std::atomic<uint32_t> m_refCount = 0;

D3D9CustomDevice::D3D9CustomDevice(IDirect3DDevice9* pReal, D3DObjectManager* pGlOM)
{
	m_pRealDevice = pReal;
	m_pGLOM = pGlOM;
}

HRESULT __stdcall D3D9CustomDevice::QueryInterface(REFIID riid, void** ppvObj)
{
	return m_pRealDevice->QueryInterface(riid, ppvObj);
}

ULONG __stdcall D3D9CustomDevice::AddRef(void)
{
	return m_pRealDevice->AddRef();
}

ULONG __stdcall D3D9CustomDevice::Release(void)
{
	return m_pRealDevice->Release();
}

HRESULT __stdcall D3D9CustomDevice::TestCooperativeLevel(void)
{
	return m_pRealDevice->TestCooperativeLevel();
}

UINT __stdcall D3D9CustomDevice::GetAvailableTextureMem(void)
{
	return m_pRealDevice->GetAvailableTextureMem();
}

HRESULT __stdcall D3D9CustomDevice::EvictManagedResources(void)
{
	return m_pRealDevice->EvictManagedResources();
}

HRESULT __stdcall D3D9CustomDevice::GetDirect3D(IDirect3D9** ppD3D9)
{
	return m_pRealDevice->GetDirect3D(ppD3D9);
}

HRESULT __stdcall D3D9CustomDevice::GetDeviceCaps(D3DCAPS9* pCaps)
{
	return m_pRealDevice->GetDeviceCaps(pCaps);
}

HRESULT __stdcall D3D9CustomDevice::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
	return m_pRealDevice->GetDisplayMode(iSwapChain, pMode);
}

HRESULT __stdcall D3D9CustomDevice::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters)
{
	return m_pRealDevice->GetCreationParameters(pParameters);
}

HRESULT __stdcall D3D9CustomDevice::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
{
	return m_pRealDevice->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void __stdcall D3D9CustomDevice::SetCursorPosition(int X, int Y, DWORD Flags)
{
	return m_pRealDevice->SetCursorPosition(X, Y, Flags);
}

BOOL __stdcall D3D9CustomDevice::ShowCursor(BOOL bShow)
{
	return m_pRealDevice->ShowCursor(bShow);
}

HRESULT __stdcall D3D9CustomDevice::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
	return m_pRealDevice->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT __stdcall D3D9CustomDevice::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
	return m_pRealDevice->GetSwapChain(iSwapChain, pSwapChain);
}

UINT __stdcall D3D9CustomDevice::GetNumberOfSwapChains(void)
{
	return m_pRealDevice->GetNumberOfSwapChains();
}

HRESULT __stdcall D3D9CustomDevice::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	return m_pRealDevice->Reset(pPresentationParameters);
}

HRESULT __stdcall D3D9CustomDevice::Present(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	m_pGLOM->Notify_Present();
	return m_pRealDevice->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT __stdcall D3D9CustomDevice::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
	return m_pRealDevice->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT __stdcall D3D9CustomDevice::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
	return m_pRealDevice->GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT __stdcall D3D9CustomDevice::SetDialogBoxMode(BOOL bEnableDialogs)
{
	return m_pRealDevice->SetDialogBoxMode(bEnableDialogs);
}

void __stdcall D3D9CustomDevice::SetGammaRamp(UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP* pRamp)
{
	return m_pRealDevice->SetGammaRamp(iSwapChain, Flags, pRamp);
}

void __stdcall D3D9CustomDevice::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
	return m_pRealDevice->GetGammaRamp(iSwapChain, pRamp);
}

HRESULT __stdcall D3D9CustomDevice::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	auto ret = m_pRealDevice->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);

	if (ret == S_OK)
	{
		FTextureInfo fTexInfo{};

		bool CanCaptureImmediate = false;

		fTexInfo.uWidth = Width;
		fTexInfo.uHeight = Height;
		fTexInfo.uFormat = Format;

		//m_pGLOM->AddTexture(*ppTexture, nullptr, fTexInfo, this, CanCaptureImmediate);
	}

	return ret;
}

HRESULT __stdcall D3D9CustomDevice::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
	return m_pRealDevice->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
	return m_pRealDevice->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	auto ret = m_pRealDevice->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);

	if (ret == S_OK)
	{
		m_pGLOM->AddBuffer(*ppVertexBuffer, EBufferTypes::Vertex, 0, 0, this);
	}

	return ret;
}

HRESULT __stdcall D3D9CustomDevice::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	auto ret = m_pRealDevice->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);

	if (ret == S_OK)
	{
		m_pGLOM->AddBuffer(*ppIndexBuffer, EBufferTypes::Index, 0, 0, this);
	}

	return ret;
}

HRESULT __stdcall D3D9CustomDevice::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pRealDevice->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pRealDevice->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::UpdateSurface(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, const POINT* pDestPoint)
{
	return m_pRealDevice->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT __stdcall D3D9CustomDevice::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
{
	return m_pRealDevice->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT __stdcall D3D9CustomDevice::GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
	return m_pRealDevice->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT __stdcall D3D9CustomDevice::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
	return m_pRealDevice->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT __stdcall D3D9CustomDevice::StretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	return m_pRealDevice->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT __stdcall D3D9CustomDevice::ColorFill(IDirect3DSurface9* pSurface, const RECT* pRect, D3DCOLOR color)
{
	return m_pRealDevice->ColorFill(pSurface, pRect, color);
}

HRESULT __stdcall D3D9CustomDevice::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pRealDevice->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
	return m_pRealDevice->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT __stdcall D3D9CustomDevice::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
	return m_pRealDevice->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT __stdcall D3D9CustomDevice::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
	return m_pRealDevice->SetDepthStencilSurface(pNewZStencil);
}

HRESULT __stdcall D3D9CustomDevice::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
	return m_pRealDevice->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT __stdcall D3D9CustomDevice::BeginScene(void)
{
	return m_pRealDevice->BeginScene();
}

HRESULT __stdcall D3D9CustomDevice::EndScene(void)
{
	return m_pRealDevice->EndScene();
}

HRESULT __stdcall D3D9CustomDevice::Clear(DWORD Count, const D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return m_pRealDevice->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT __stdcall D3D9CustomDevice::SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix)
{
	return m_pRealDevice->SetTransform(State, pMatrix);
}

HRESULT __stdcall D3D9CustomDevice::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
	return m_pRealDevice->GetTransform(State, pMatrix);
}

HRESULT __stdcall D3D9CustomDevice::MultiplyTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix)
{
	return m_pRealDevice->MultiplyTransform(State, pMatrix);
}

HRESULT __stdcall D3D9CustomDevice::SetViewport(const D3DVIEWPORT9* pViewport)
{
	return m_pRealDevice->SetViewport(pViewport);
}

HRESULT __stdcall D3D9CustomDevice::GetViewport(D3DVIEWPORT9* pViewport)
{
	return m_pRealDevice->GetViewport(pViewport);
}

HRESULT __stdcall D3D9CustomDevice::SetMaterial(const D3DMATERIAL9* pMaterial)
{
	return m_pRealDevice->SetMaterial(pMaterial);
}

HRESULT __stdcall D3D9CustomDevice::GetMaterial(D3DMATERIAL9* pMaterial)
{
	return m_pRealDevice->GetMaterial(pMaterial);
}

HRESULT __stdcall D3D9CustomDevice::SetLight(DWORD Index, const D3DLIGHT9* Light)
{
	return m_pRealDevice->SetLight(Index, Light);
}

HRESULT __stdcall D3D9CustomDevice::GetLight(DWORD Index, D3DLIGHT9 *Light)
{
	return m_pRealDevice->GetLight(Index, Light);
}

HRESULT __stdcall D3D9CustomDevice::LightEnable(DWORD Index, BOOL Enable)
{
	return m_pRealDevice->LightEnable(Index, Enable);
}

HRESULT __stdcall D3D9CustomDevice::GetLightEnable(DWORD Index, BOOL* pEnable)
{
	return m_pRealDevice->GetLightEnable(Index, pEnable);
}

HRESULT __stdcall D3D9CustomDevice::SetClipPlane(DWORD Index, const float* pPlane)
{
	return m_pRealDevice->SetClipPlane(Index, pPlane);
}

HRESULT __stdcall D3D9CustomDevice::GetClipPlane(DWORD Index, float* pPlane)
{
	return m_pRealDevice->GetClipPlane(Index, pPlane);
}

HRESULT __stdcall D3D9CustomDevice::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return m_pRealDevice->SetRenderState(State, Value);
}

HRESULT __stdcall D3D9CustomDevice::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return m_pRealDevice->GetRenderState(State, pValue);
}

HRESULT __stdcall D3D9CustomDevice::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
	return m_pRealDevice->CreateStateBlock(Type, ppSB);
}

HRESULT __stdcall D3D9CustomDevice::BeginStateBlock(void)
{
	return m_pRealDevice->BeginStateBlock();
}

HRESULT __stdcall D3D9CustomDevice::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
	return m_pRealDevice->EndStateBlock(ppSB);
}

HRESULT __stdcall D3D9CustomDevice::SetClipStatus(const D3DCLIPSTATUS9* pClipStatus)
{
	return m_pRealDevice->SetClipStatus(pClipStatus);
}

HRESULT __stdcall D3D9CustomDevice::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
	return m_pRealDevice->GetClipStatus(pClipStatus);
}

HRESULT __stdcall D3D9CustomDevice::GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)
{
	return m_pRealDevice->GetTexture(Stage, ppTexture);
}

HRESULT __stdcall D3D9CustomDevice::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
	return m_pRealDevice->SetTexture(Stage, pTexture);
}

HRESULT __stdcall D3D9CustomDevice::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return m_pRealDevice->GetTextureStageState(Stage, Type, pValue);
}

HRESULT __stdcall D3D9CustomDevice::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return m_pRealDevice->SetTextureStageState(Stage, Type, Value);
}

HRESULT __stdcall D3D9CustomDevice::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
	return m_pRealDevice->GetSamplerState(Sampler, Type, pValue);
}

HRESULT __stdcall D3D9CustomDevice::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return m_pRealDevice->SetSamplerState(Sampler, Type, Value);
}

HRESULT __stdcall D3D9CustomDevice::ValidateDevice(DWORD* pNumPasses)
{
	return m_pRealDevice->ValidateDevice(pNumPasses);
}

HRESULT __stdcall D3D9CustomDevice::SetPaletteEntries(UINT PaletteNumber, const PALETTEENTRY* pEntries)
{
	return m_pRealDevice->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall D3D9CustomDevice::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return m_pRealDevice->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall D3D9CustomDevice::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return m_pRealDevice->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT __stdcall D3D9CustomDevice::GetCurrentTexturePalette(UINT* PaletteNumber)
{
	return m_pRealDevice->GetCurrentTexturePalette(PaletteNumber);
}

HRESULT __stdcall D3D9CustomDevice::SetScissorRect(const RECT* pRect)
{
	return m_pRealDevice->SetScissorRect(pRect);
}

HRESULT __stdcall D3D9CustomDevice::GetScissorRect(RECT* pRect)
{
	return m_pRealDevice->GetScissorRect(pRect);
}

HRESULT __stdcall D3D9CustomDevice::SetSoftwareVertexProcessing(BOOL bSoftware)
{
	return m_pRealDevice->SetSoftwareVertexProcessing(bSoftware);
}

BOOL __stdcall D3D9CustomDevice::GetSoftwareVertexProcessing(void)
{
	return m_pRealDevice->GetSoftwareVertexProcessing();
}

HRESULT __stdcall D3D9CustomDevice::SetNPatchMode(float nSegments)
{
	return m_pRealDevice->SetNPatchMode(nSegments);
}

float __stdcall D3D9CustomDevice::GetNPatchMode(void)
{
	return m_pRealDevice->GetNPatchMode();
}

HRESULT __stdcall D3D9CustomDevice::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	m_pGLOM->Notify_Draw(PrimitiveType, 0, StartVertex, 0, 0, PrimitiveCount, ECallsTypes::DrawPrimitive);
	return m_pRealDevice->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT __stdcall D3D9CustomDevice::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	m_pGLOM->Notify_Draw(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount, ECallsTypes::DrawIndexedPrimitive);
	return m_pRealDevice->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT __stdcall D3D9CustomDevice::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pRealDevice->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT __stdcall D3D9CustomDevice::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void* pIndexData, D3DFORMAT IndexDataFormat, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pRealDevice->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT __stdcall D3D9CustomDevice::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
	return m_pRealDevice->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT __stdcall D3D9CustomDevice::CreateVertexDeclaration(const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
	auto ret = m_pRealDevice->CreateVertexDeclaration(pVertexElements, ppDecl);

	if (ret == S_OK)
	{
		m_pGLOM->AddInputLayout(*ppDecl);
	}

	return ret;
}

HRESULT __stdcall D3D9CustomDevice::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
	auto ret = m_pRealDevice->SetVertexDeclaration(pDecl);

	if (ret == S_OK)
	{
		m_pGLOM->SetInputLayout(pDecl);
	}

	return ret;
}

HRESULT __stdcall D3D9CustomDevice::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pRealDevice->GetVertexDeclaration(ppDecl);
}

HRESULT __stdcall D3D9CustomDevice::SetFVF(DWORD FVF)
{
	return m_pRealDevice->SetFVF(FVF);
}

HRESULT __stdcall D3D9CustomDevice::GetFVF(DWORD* pFVF)
{
	return m_pRealDevice->GetFVF(pFVF);
}

HRESULT __stdcall D3D9CustomDevice::CreateVertexShader(const DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
	auto ret = m_pRealDevice->CreateVertexShader(pFunction, ppShader);

	if (ret == S_OK)
	{
		// Unlike DX11, we need to get the bytecode ourselves
		std::vector<char> vBytecode;
		uint32_t RequestedSize = 0;

		auto returnValue = (*ppShader)->GetFunction(NULL, &RequestedSize);
		if (returnValue != S_OK)
		{
			DEBUG_LINE(m_pGLOM->Event, LOGERR("Bad Return for GetFunction"));
			return ret;
		}

		vBytecode.resize(RequestedSize);

		returnValue = (*ppShader)->GetFunction(vBytecode.data(), &RequestedSize);
		if (returnValue != S_OK)
		{
			DEBUG_LINE(m_pGLOM->Event, LOGERR("Bad Return for GetFunction with data"));
			return ret;
		}

		m_pGLOM->AddShader(*ppShader, vBytecode.data(), vBytecode.size());
	}

	return ret;
}

HRESULT __stdcall D3D9CustomDevice::SetVertexShader(IDirect3DVertexShader9* pShader)
{
	//if (m_refCount < 10 && pShader)
	//{
	//	std::ofstream html(std::to_string(m_refCount++) + ".html", std::ios::out | std::ios::binary);

	//	//DEBUG_LINE(m_pGLOM->Event, LOGERR("TEST"));

	//	std::vector<char> vBytecode;
	//	uint32_t RequestedSize = 0;

	//	auto returnValue = pShader->GetFunction(NULL, &RequestedSize);
	//	if (returnValue != S_OK)
	//	{
	//		DEBUG_LINE(m_pGLOM->Event, LOGERR("Bad Return for GetFunction"));
	//	}

	//	DEBUG_LINE(m_pGLOM->Event, LOG("Good Return for GetFunction"));
	//	vBytecode.resize(RequestedSize);

	//	returnValue = pShader->GetFunction(vBytecode.data(), &RequestedSize);
	//	if (returnValue != S_OK)
	//	{
	//		DEBUG_LINE(m_pGLOM->Event, LOGERR("Bad Return for GetFunction with data"));
	//	}
	//	DEBUG_LINE(m_pGLOM->Event, LOG("Good Return for GetFunction with Data"));

	//	ID3DBlob* disShader;
	//	D3DDisassemble(vBytecode.data(), vBytecode.size(),
	//		D3D_DISASM_ENABLE_COLOR_CODE |
	//		D3D_DISASM_ENABLE_INSTRUCTION_OFFSET |
	//		D3D_DISASM_ENABLE_DEFAULT_VALUE_PRINTS,
	//		nullptr,
	//		&disShader
	//	);

	//	html.write(reinterpret_cast<char*>(disShader->GetBufferPointer()), disShader->GetBufferSize());
	//	html.close();
	//}

	m_pGLOM->SetShader(pShader, EShaderTypes::Vertex);
	return m_pRealDevice->SetVertexShader(pShader);
}

HRESULT __stdcall D3D9CustomDevice::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
	return m_pRealDevice->GetVertexShader(ppShader);
}

HRESULT __stdcall D3D9CustomDevice::SetVertexShaderConstantF(UINT StartRegister, const float* pConstantData, UINT Vector4fCount)
{
	return m_pRealDevice->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall D3D9CustomDevice::GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pRealDevice->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall D3D9CustomDevice::SetVertexShaderConstantI(UINT StartRegister, const int* pConstantData, UINT Vector4iCount)
{
	return m_pRealDevice->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall D3D9CustomDevice::GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pRealDevice->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall D3D9CustomDevice::SetVertexShaderConstantB(UINT StartRegister, const BOOL* pConstantData, UINT BoolCount)
{
	return m_pRealDevice->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall D3D9CustomDevice::GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pRealDevice->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall D3D9CustomDevice::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	//DEBUG_LOGLINE(m_pGLOM->Event, LOG("CallSSS: " << StreamNumber << " with " << OffsetInBytes << " " << Stride));
	m_pGLOM->SetBuffer(pStreamData, EBufferTypes::Vertex, StreamNumber);
	return m_pRealDevice->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT __stdcall D3D9CustomDevice::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride)
{
	return m_pRealDevice->GetStreamSource(StreamNumber, ppStreamData, pOffsetInBytes, pStride);
}

HRESULT __stdcall D3D9CustomDevice::SetStreamSourceFreq(UINT StreamNumber, UINT Setting)
{
	return m_pRealDevice->SetStreamSourceFreq(StreamNumber, Setting);
}

HRESULT __stdcall D3D9CustomDevice::GetStreamSourceFreq(UINT StreamNumber, UINT* pSetting)
{
	return m_pRealDevice->GetStreamSourceFreq(StreamNumber, pSetting);
}

HRESULT __stdcall D3D9CustomDevice::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
	m_pGLOM->SetBuffer(pIndexData, EBufferTypes::Index, 0);
	return m_pRealDevice->SetIndices(pIndexData);
}

HRESULT __stdcall D3D9CustomDevice::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
	return m_pRealDevice->GetIndices(ppIndexData);
}

HRESULT __stdcall D3D9CustomDevice::CreatePixelShader(const DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
	auto ret = m_pRealDevice->CreatePixelShader(pFunction, ppShader);
	if (ret == S_OK)
	{
		// Unlike DX11, we need to get the bytecode ourselves
		std::vector<char> vBytecode;
		uint32_t RequestedSize = 0;

		auto returnValue = (*ppShader)->GetFunction(NULL, &RequestedSize);
		if (returnValue != S_OK)
		{
			DEBUG_LINE(m_pGLOM->Event, LOGERR("Bad Return for GetFunction"));
			return ret;
		}

		vBytecode.resize(RequestedSize);

		returnValue = (*ppShader)->GetFunction(vBytecode.data(), &RequestedSize);
		if (returnValue != S_OK)
		{
			DEBUG_LINE(m_pGLOM->Event, LOGERR("Bad Return for GetFunction with data"));
			return ret;
		}

		m_pGLOM->AddShader(*ppShader, vBytecode.data(), vBytecode.size());
	}

	return ret;
}

HRESULT __stdcall D3D9CustomDevice::SetPixelShader(IDirect3DPixelShader9* pShader)
{
	m_pGLOM->SetShader(pShader, EShaderTypes::Pixel);
	return m_pRealDevice->SetPixelShader(pShader);
}

HRESULT __stdcall D3D9CustomDevice::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
	return m_pRealDevice->GetPixelShader(ppShader);
}

HRESULT __stdcall D3D9CustomDevice::SetPixelShaderConstantF(UINT StartRegister, const float* pConstantData, UINT Vector4fCount)
{
	return m_pRealDevice->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall D3D9CustomDevice::GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pRealDevice->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall D3D9CustomDevice::SetPixelShaderConstantI(UINT StartRegister, const int* pConstantData, UINT Vector4iCount)
{
	return m_pRealDevice->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall D3D9CustomDevice::GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pRealDevice->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall D3D9CustomDevice::SetPixelShaderConstantB(UINT StartRegister, const BOOL* pConstantData, UINT BoolCount)
{
	return m_pRealDevice->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall D3D9CustomDevice::GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pRealDevice->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall D3D9CustomDevice::DrawRectPatch(UINT Handle, const float* pNumSegs, const D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return m_pRealDevice->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT __stdcall D3D9CustomDevice::DrawTriPatch(UINT Handle, const float* pNumSegs, const D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return m_pRealDevice->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT __stdcall D3D9CustomDevice::DeletePatch(UINT Handle)
{
	return m_pRealDevice->DeletePatch(Handle);
}

HRESULT __stdcall D3D9CustomDevice::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	return m_pRealDevice->CreateQuery(Type, ppQuery);
}

