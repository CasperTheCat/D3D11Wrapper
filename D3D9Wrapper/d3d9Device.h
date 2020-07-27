#pragma once

#include <d3d9.h>
#include <fstream>
#include <vector>
#include "Globals.h"
#include "d3d9ObjectManager.h"

class D3D9CustomDevice : public IDirect3DDevice9
{
protected:
	IDirect3DDevice9* m_pRealDevice;
	class D3DObjectManager* m_pGLOM;

public:
	D3D9CustomDevice(IDirect3DDevice9* pReal, D3DObjectManager* pGlOM);
	virtual ~D3D9CustomDevice() = default;

	IDirect3DDevice9* RealDevice()
	{
		return m_pRealDevice;
	}

	D3DObjectManager* GetGLOM()
	{
		return m_pGLOM;
	}

	// Inherited via IDirect3DDevice9
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObj) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;
	virtual HRESULT __stdcall TestCooperativeLevel(void) override;
	virtual UINT __stdcall GetAvailableTextureMem(void) override;
	virtual HRESULT __stdcall EvictManagedResources(void) override;
	virtual HRESULT __stdcall GetDirect3D(IDirect3D9** ppD3D9) override;
	virtual HRESULT __stdcall GetDeviceCaps(D3DCAPS9* pCaps) override;
	virtual HRESULT __stdcall GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode) override;
	virtual HRESULT __stdcall GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters) override;
	virtual HRESULT __stdcall SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap) override;
	virtual void __stdcall SetCursorPosition(int X, int Y, DWORD Flags) override;
	virtual BOOL __stdcall ShowCursor(BOOL bShow) override;
	virtual HRESULT __stdcall CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain) override;
	virtual HRESULT __stdcall GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain) override;
	virtual UINT __stdcall GetNumberOfSwapChains(void) override;
	virtual HRESULT __stdcall Reset(D3DPRESENT_PARAMETERS* pPresentationParameters) override;
	virtual HRESULT __stdcall Present(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion) override;
	virtual HRESULT __stdcall GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer) override;
	virtual HRESULT __stdcall GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus) override;
	virtual HRESULT __stdcall SetDialogBoxMode(BOOL bEnableDialogs) override;
	virtual void __stdcall SetGammaRamp(UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP* pRamp) override;
	virtual void __stdcall GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp) override;
	virtual HRESULT __stdcall CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle) override;
	virtual HRESULT __stdcall CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle) override;
	virtual HRESULT __stdcall CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle) override;
	virtual HRESULT __stdcall CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle) override;
	virtual HRESULT __stdcall CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle) override;
	virtual HRESULT __stdcall CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) override;
	virtual HRESULT __stdcall CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) override;
	virtual HRESULT __stdcall UpdateSurface(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, const POINT* pDestPoint) override;
	virtual HRESULT __stdcall UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture) override;
	virtual HRESULT __stdcall GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface) override;
	virtual HRESULT __stdcall GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface) override;
	virtual HRESULT __stdcall StretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter) override;
	virtual HRESULT __stdcall ColorFill(IDirect3DSurface9* pSurface, const RECT* pRect, D3DCOLOR color) override;
	virtual HRESULT __stdcall CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) override;
	virtual HRESULT __stdcall SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget) override;
	virtual HRESULT __stdcall GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget) override;
	virtual HRESULT __stdcall SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil) override;
	virtual HRESULT __stdcall GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface) override;
	virtual HRESULT __stdcall BeginScene(void) override;
	virtual HRESULT __stdcall EndScene(void) override;
	virtual HRESULT __stdcall Clear(DWORD Count, const D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil) override;
	virtual HRESULT __stdcall SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix) override;
	virtual HRESULT __stdcall GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix) override;
	virtual HRESULT __stdcall MultiplyTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix) override;
	virtual HRESULT __stdcall SetViewport(const D3DVIEWPORT9* pViewport) override;
	virtual HRESULT __stdcall GetViewport(D3DVIEWPORT9* pViewport) override;
	virtual HRESULT __stdcall SetMaterial(const D3DMATERIAL9* pMaterial) override;
	virtual HRESULT __stdcall GetMaterial(D3DMATERIAL9* pMaterial) override;
	virtual HRESULT __stdcall SetLight(DWORD Index, const D3DLIGHT9* Light) override;
	virtual HRESULT __stdcall GetLight(DWORD Index, D3DLIGHT9* Light) override;
	virtual HRESULT __stdcall LightEnable(DWORD Index, BOOL Enable) override;
	virtual HRESULT __stdcall GetLightEnable(DWORD Index, BOOL* pEnable) override;
	virtual HRESULT __stdcall SetClipPlane(DWORD Index, const float* pPlane) override;
	virtual HRESULT __stdcall GetClipPlane(DWORD Index, float* pPlane) override;
	virtual HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE State, DWORD Value) override;
	virtual HRESULT __stdcall GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue) override;
	virtual HRESULT __stdcall CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB) override;
	virtual HRESULT __stdcall BeginStateBlock(void) override;
	virtual HRESULT __stdcall EndStateBlock(IDirect3DStateBlock9** ppSB) override;
	virtual HRESULT __stdcall SetClipStatus(const D3DCLIPSTATUS9* pClipStatus) override;
	virtual HRESULT __stdcall GetClipStatus(D3DCLIPSTATUS9* pClipStatus) override;
	virtual HRESULT __stdcall GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture) override;
	virtual HRESULT __stdcall SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture) override;
	virtual HRESULT __stdcall GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue) override;
	virtual HRESULT __stdcall SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) override;
	virtual HRESULT __stdcall GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue) override;
	virtual HRESULT __stdcall SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) override;
	virtual HRESULT __stdcall ValidateDevice(DWORD* pNumPasses) override;
	virtual HRESULT __stdcall SetPaletteEntries(UINT PaletteNumber, const PALETTEENTRY* pEntries) override;
	virtual HRESULT __stdcall GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries) override;
	virtual HRESULT __stdcall SetCurrentTexturePalette(UINT PaletteNumber) override;
	virtual HRESULT __stdcall GetCurrentTexturePalette(UINT* PaletteNumber) override;
	virtual HRESULT __stdcall SetScissorRect(const RECT* pRect) override;
	virtual HRESULT __stdcall GetScissorRect(RECT* pRect) override;
	virtual HRESULT __stdcall SetSoftwareVertexProcessing(BOOL bSoftware) override;
	virtual BOOL __stdcall GetSoftwareVertexProcessing(void) override;
	virtual HRESULT __stdcall SetNPatchMode(float nSegments) override;
	virtual float __stdcall GetNPatchMode(void) override;
	virtual HRESULT __stdcall DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) override;
	virtual HRESULT __stdcall DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount) override;
	virtual HRESULT __stdcall DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride) override;
	virtual HRESULT __stdcall DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void* pIndexData, D3DFORMAT IndexDataFormat, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride) override;
	virtual HRESULT __stdcall ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags) override;
	virtual HRESULT __stdcall CreateVertexDeclaration(const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl) override;
	virtual HRESULT __stdcall SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl) override;
	virtual HRESULT __stdcall GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl) override;
	virtual HRESULT __stdcall SetFVF(DWORD FVF) override;
	virtual HRESULT __stdcall GetFVF(DWORD* pFVF) override;
	virtual HRESULT __stdcall CreateVertexShader(const DWORD* pFunction, IDirect3DVertexShader9** ppShader) override;
	virtual HRESULT __stdcall SetVertexShader(IDirect3DVertexShader9* pShader) override;
	virtual HRESULT __stdcall GetVertexShader(IDirect3DVertexShader9** ppShader) override;
	virtual HRESULT __stdcall SetVertexShaderConstantF(UINT StartRegister, const float* pConstantData, UINT Vector4fCount) override;
	virtual HRESULT __stdcall GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount) override;
	virtual HRESULT __stdcall SetVertexShaderConstantI(UINT StartRegister, const int* pConstantData, UINT Vector4iCount) override;
	virtual HRESULT __stdcall GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount) override;
	virtual HRESULT __stdcall SetVertexShaderConstantB(UINT StartRegister, const BOOL* pConstantData, UINT BoolCount) override;
	virtual HRESULT __stdcall GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount) override;
	virtual HRESULT __stdcall SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride) override;
	virtual HRESULT __stdcall GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride) override;
	virtual HRESULT __stdcall SetStreamSourceFreq(UINT StreamNumber, UINT Setting) override;
	virtual HRESULT __stdcall GetStreamSourceFreq(UINT StreamNumber, UINT* pSetting) override;
	virtual HRESULT __stdcall SetIndices(IDirect3DIndexBuffer9* pIndexData) override;
	virtual HRESULT __stdcall GetIndices(IDirect3DIndexBuffer9** ppIndexData) override;
	virtual HRESULT __stdcall CreatePixelShader(const DWORD* pFunction, IDirect3DPixelShader9** ppShader) override;
	virtual HRESULT __stdcall SetPixelShader(IDirect3DPixelShader9* pShader) override;
	virtual HRESULT __stdcall GetPixelShader(IDirect3DPixelShader9** ppShader) override;
	virtual HRESULT __stdcall SetPixelShaderConstantF(UINT StartRegister, const float* pConstantData, UINT Vector4fCount) override;
	virtual HRESULT __stdcall GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount) override;
	virtual HRESULT __stdcall SetPixelShaderConstantI(UINT StartRegister, const int* pConstantData, UINT Vector4iCount) override;
	virtual HRESULT __stdcall GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount) override;
	virtual HRESULT __stdcall SetPixelShaderConstantB(UINT StartRegister, const BOOL* pConstantData, UINT BoolCount) override;
	virtual HRESULT __stdcall GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount) override;
	virtual HRESULT __stdcall DrawRectPatch(UINT Handle, const float* pNumSegs, const D3DRECTPATCH_INFO* pRectPatchInfo) override;
	virtual HRESULT __stdcall DrawTriPatch(UINT Handle, const float* pNumSegs, const D3DTRIPATCH_INFO* pTriPatchInfo) override;
	virtual HRESULT __stdcall DeletePatch(UINT Handle) override;
	virtual HRESULT __stdcall CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery) override;
};