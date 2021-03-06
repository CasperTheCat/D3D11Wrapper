HRESULT __stdcall D3D9CustomDevice::QueryInterface(REFIID riid, void** ppvObj)
{
	return m_realDevice->QueryInterface(riid, ppvObj);
}

ULONG __stdcall D3D9CustomDevice::AddRef(void)
{
	return m_realDevice->AddRef();
}

ULONG __stdcall D3D9CustomDevice::Release(void)
{
	return m_realDevice->Release();
}

HRESULT __stdcall D3D9CustomDevice::TestCooperativeLevel(void)
{
	return m_realDevice->TestCooperativeLevel();
}

UINT __stdcall D3D9CustomDevice::GetAvailableTextureMem(void)
{
	return m_realDevice->GetAvailableTextureMem();
}

HRESULT __stdcall D3D9CustomDevice::EvictManagedResources(void)
{
	return m_realDevice->EvictManagedResources();
}

HRESULT __stdcall D3D9CustomDevice::GetDirect3D(IDirect3D9** ppD3D9)
{
	return m_realDevice->GetDirect3D(ppD3D9);
}

HRESULT __stdcall D3D9CustomDevice::GetDeviceCaps(D3DCAPS9* pCaps)
{
	return m_realDevice->GetDeviceCaps(pCaps);
}

HRESULT __stdcall D3D9CustomDevice::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
	return m_realDevice->GetDisplayMode(iSwapChain, pMode);
}

HRESULT __stdcall D3D9CustomDevice::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters)
{
	return m_realDevice->GetCreationParameters(pParameters);
}

HRESULT __stdcall D3D9CustomDevice::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
{
	return m_realDevice->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void __stdcall D3D9CustomDevice::SetCursorPosition(int X, int Y, DWORD Flags)
{
	return m_realDevice->SetCursorPosition(X, Y, Flags);
}

BOOL __stdcall D3D9CustomDevice::ShowCursor(BOOL bShow)
{
	return m_realDevice->ShowCursor(bShow);
}

HRESULT __stdcall D3D9CustomDevice::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
	return m_realDevice->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT __stdcall D3D9CustomDevice::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
	return m_realDevice->GetSwapChain(iSwapChain, pSwapChain);
}

UINT __stdcall D3D9CustomDevice::GetNumberOfSwapChains(void)
{
	return m_realDevice->GetNumberOfSwapChains();
}

HRESULT __stdcall D3D9CustomDevice::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	return m_realDevice->Reset(pPresentationParameters);
}

HRESULT __stdcall D3D9CustomDevice::Present(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	return m_realDevice->Present(RECT*, RECT*, hDestWindowOverride, RGNDATA*);
}

HRESULT __stdcall D3D9CustomDevice::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
	return m_realDevice->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT __stdcall D3D9CustomDevice::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
	return m_realDevice->GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT __stdcall D3D9CustomDevice::SetDialogBoxMode(BOOL bEnableDialogs)
{
	return m_realDevice->SetDialogBoxMode(bEnableDialogs);
}

void __stdcall D3D9CustomDevice::SetGammaRamp(UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP* pRamp)
{
	return m_realDevice->SetGammaRamp(iSwapChain, Flags, D3DGAMMARAMP*);
}

void __stdcall D3D9CustomDevice::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
	return m_realDevice->GetGammaRamp(iSwapChain, pRamp);
}

HRESULT __stdcall D3D9CustomDevice::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	return m_realDevice->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
	return m_realDevice->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
	return m_realDevice->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	return m_realDevice->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	return m_realDevice->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_realDevice->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_realDevice->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::UpdateSurface(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, const POINT* pDestPoint)
{
	return m_realDevice->UpdateSurface(pSourceSurface, RECT*, pDestinationSurface, POINT*);
}

HRESULT __stdcall D3D9CustomDevice::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
{
	return m_realDevice->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT __stdcall D3D9CustomDevice::GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
	return m_realDevice->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT __stdcall D3D9CustomDevice::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
	return m_realDevice->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT __stdcall D3D9CustomDevice::StretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	return m_realDevice->StretchRect(pSourceSurface, RECT*, pDestSurface, RECT*, Filter);
}

HRESULT __stdcall D3D9CustomDevice::ColorFill(IDirect3DSurface9* pSurface, const RECT* pRect, D3DCOLOR color)
{
	return m_realDevice->ColorFill(pSurface, RECT*, color);
}

HRESULT __stdcall D3D9CustomDevice::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_realDevice->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT __stdcall D3D9CustomDevice::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
	return m_realDevice->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT __stdcall D3D9CustomDevice::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
	return m_realDevice->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT __stdcall D3D9CustomDevice::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
	return m_realDevice->SetDepthStencilSurface(pNewZStencil);
}

HRESULT __stdcall D3D9CustomDevice::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
	return m_realDevice->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT __stdcall D3D9CustomDevice::BeginScene(void)
{
	return m_realDevice->BeginScene();
}

HRESULT __stdcall D3D9CustomDevice::EndScene(void)
{
	return m_realDevice->EndScene();
}

HRESULT __stdcall D3D9CustomDevice::Clear(DWORD Count, const D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return m_realDevice->Clear(Count, D3DRECT*, Flags, Color, Z, Stencil);
}

HRESULT __stdcall D3D9CustomDevice::SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix)
{
	return m_realDevice->SetTransform(State, D3DMATRIX*);
}

HRESULT __stdcall D3D9CustomDevice::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
	return m_realDevice->GetTransform(State, pMatrix);
}

HRESULT __stdcall D3D9CustomDevice::MultiplyTransform(D3DTRANSFORMSTATETYPE, const D3DMATRIX*)
{
	return m_realDevice->MultiplyTransform(D3DMATRIX*);
}

HRESULT __stdcall D3D9CustomDevice::SetViewport(const D3DVIEWPORT9* pViewport)
{
	return m_realDevice->SetViewport(D3DVIEWPORT9*);
}

HRESULT __stdcall D3D9CustomDevice::GetViewport(D3DVIEWPORT9* pViewport)
{
	return m_realDevice->GetViewport(pViewport);
}

HRESULT __stdcall D3D9CustomDevice::SetMaterial(const D3DMATERIAL9* pMaterial)
{
	return m_realDevice->SetMaterial(D3DMATERIAL9*);
}

HRESULT __stdcall D3D9CustomDevice::GetMaterial(D3DMATERIAL9* pMaterial)
{
	return m_realDevice->GetMaterial(pMaterial);
}

HRESULT __stdcall D3D9CustomDevice::SetLight(DWORD Index, const D3DLIGHT9*)
{
	return m_realDevice->SetLight(Index, D3DLIGHT9*);
}

HRESULT __stdcall D3D9CustomDevice::GetLight(DWORD Index, D3DLIGHT9*)
{
	return m_realDevice->GetLight(Index);
}

HRESULT __stdcall D3D9CustomDevice::LightEnable(DWORD Index, BOOL Enable)
{
	return m_realDevice->LightEnable(Index, Enable);
}

HRESULT __stdcall D3D9CustomDevice::GetLightEnable(DWORD Index, BOOL* pEnable)
{
	return m_realDevice->GetLightEnable(Index, pEnable);
}

HRESULT __stdcall D3D9CustomDevice::SetClipPlane(DWORD Index, const float* pPlane)
{
	return m_realDevice->SetClipPlane(Index, float*);
}

HRESULT __stdcall D3D9CustomDevice::GetClipPlane(DWORD Index, float* pPlane)
{
	return m_realDevice->GetClipPlane(Index, pPlane);
}

HRESULT __stdcall D3D9CustomDevice::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return m_realDevice->SetRenderState(State, Value);
}

HRESULT __stdcall D3D9CustomDevice::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return m_realDevice->GetRenderState(State, pValue);
}

HRESULT __stdcall D3D9CustomDevice::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
	return m_realDevice->CreateStateBlock(Type, ppSB);
}

HRESULT __stdcall D3D9CustomDevice::BeginStateBlock(void)
{
	return m_realDevice->BeginStateBlock();
}

HRESULT __stdcall D3D9CustomDevice::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
	return m_realDevice->EndStateBlock(ppSB);
}

HRESULT __stdcall D3D9CustomDevice::SetClipStatus(const D3DCLIPSTATUS9* pClipStatus)
{
	return m_realDevice->SetClipStatus(D3DCLIPSTATUS9*);
}

HRESULT __stdcall D3D9CustomDevice::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
	return m_realDevice->GetClipStatus(pClipStatus);
}

HRESULT __stdcall D3D9CustomDevice::GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)
{
	return m_realDevice->GetTexture(Stage, ppTexture);
}

HRESULT __stdcall D3D9CustomDevice::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
	return m_realDevice->SetTexture(Stage, pTexture);
}

HRESULT __stdcall D3D9CustomDevice::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return m_realDevice->GetTextureStageState(Stage, Type, pValue);
}

HRESULT __stdcall D3D9CustomDevice::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return m_realDevice->SetTextureStageState(Stage, Type, Value);
}

HRESULT __stdcall D3D9CustomDevice::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
	return m_realDevice->GetSamplerState(Sampler, Type, pValue);
}

HRESULT __stdcall D3D9CustomDevice::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return m_realDevice->SetSamplerState(Sampler, Type, Value);
}

HRESULT __stdcall D3D9CustomDevice::ValidateDevice(DWORD* pNumPasses)
{
	return m_realDevice->ValidateDevice(pNumPasses);
}

HRESULT __stdcall D3D9CustomDevice::SetPaletteEntries(UINT PaletteNumber, const PALETTEENTRY* pEntries)
{
	return m_realDevice->SetPaletteEntries(PaletteNumber, PALETTEENTRY*);
}

HRESULT __stdcall D3D9CustomDevice::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return m_realDevice->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall D3D9CustomDevice::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return m_realDevice->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT __stdcall D3D9CustomDevice::GetCurrentTexturePalette(UINT* PaletteNumber)
{
	return m_realDevice->GetCurrentTexturePalette(PaletteNumber);
}

HRESULT __stdcall D3D9CustomDevice::SetScissorRect(const RECT* pRect)
{
	return m_realDevice->SetScissorRect(RECT*);
}

HRESULT __stdcall D3D9CustomDevice::GetScissorRect(RECT* pRect)
{
	return m_realDevice->GetScissorRect(pRect);
}

HRESULT __stdcall D3D9CustomDevice::SetSoftwareVertexProcessing(BOOL bSoftware)
{
	return m_realDevice->SetSoftwareVertexProcessing(bSoftware);
}

BOOL __stdcall D3D9CustomDevice::GetSoftwareVertexProcessing(void)
{
	return m_realDevice->GetSoftwareVertexProcessing();
}

HRESULT __stdcall D3D9CustomDevice::SetNPatchMode(float nSegments)
{
	return m_realDevice->SetNPatchMode(nSegments);
}

float __stdcall D3D9CustomDevice::GetNPatchMode(void)
{
	return m_realDevice->GetNPatchMode();
}

HRESULT __stdcall D3D9CustomDevice::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return m_realDevice->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT __stdcall D3D9CustomDevice::DrawIndexedPrimitive(D3DPRIMITIVETYPE, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	return m_realDevice->DrawIndexedPrimitive(BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT __stdcall D3D9CustomDevice::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_realDevice->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, void*, VertexStreamZeroStride);
}

HRESULT __stdcall D3D9CustomDevice::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void* pIndexData, D3DFORMAT IndexDataFormat, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_realDevice->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, void*, IndexDataFormat, void*, VertexStreamZeroStride);
}

HRESULT __stdcall D3D9CustomDevice::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
	return m_realDevice->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT __stdcall D3D9CustomDevice::CreateVertexDeclaration(const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
	return m_realDevice->CreateVertexDeclaration(D3DVERTEXELEMENT9*, ppDecl);
}

HRESULT __stdcall D3D9CustomDevice::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
	return m_realDevice->SetVertexDeclaration(pDecl);
}

HRESULT __stdcall D3D9CustomDevice::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
	return m_realDevice->GetVertexDeclaration(ppDecl);
}

HRESULT __stdcall D3D9CustomDevice::SetFVF(DWORD FVF)
{
	return m_realDevice->SetFVF(FVF);
}

HRESULT __stdcall D3D9CustomDevice::GetFVF(DWORD* pFVF)
{
	return m_realDevice->GetFVF(pFVF);
}

HRESULT __stdcall D3D9CustomDevice::CreateVertexShader(const DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
	return m_realDevice->CreateVertexShader(DWORD*, ppShader);
}

HRESULT __stdcall D3D9CustomDevice::SetVertexShader(IDirect3DVertexShader9* pShader)
{
	return m_realDevice->SetVertexShader(pShader);
}

HRESULT __stdcall D3D9CustomDevice::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
	return m_realDevice->GetVertexShader(ppShader);
}

HRESULT __stdcall D3D9CustomDevice::SetVertexShaderConstantF(UINT StartRegister, const float* pConstantData, UINT Vector4fCount)
{
	return m_realDevice->SetVertexShaderConstantF(StartRegister, float*, Vector4fCount);
}

HRESULT __stdcall D3D9CustomDevice::GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_realDevice->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall D3D9CustomDevice::SetVertexShaderConstantI(UINT StartRegister, const int* pConstantData, UINT Vector4iCount)
{
	return m_realDevice->SetVertexShaderConstantI(StartRegister, int*, Vector4iCount);
}

HRESULT __stdcall D3D9CustomDevice::GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_realDevice->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall D3D9CustomDevice::SetVertexShaderConstantB(UINT StartRegister, const BOOL* pConstantData, UINT BoolCount)
{
	return m_realDevice->SetVertexShaderConstantB(StartRegister, BOOL*, BoolCount);
}

HRESULT __stdcall D3D9CustomDevice::GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_realDevice->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall D3D9CustomDevice::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	return m_realDevice->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT __stdcall D3D9CustomDevice::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride)
{
	return m_realDevice->GetStreamSource(StreamNumber, ppStreamData, pOffsetInBytes, pStride);
}

HRESULT __stdcall D3D9CustomDevice::SetStreamSourceFreq(UINT StreamNumber, UINT Setting)
{
	return m_realDevice->SetStreamSourceFreq(StreamNumber, Setting);
}

HRESULT __stdcall D3D9CustomDevice::GetStreamSourceFreq(UINT StreamNumber, UINT* pSetting)
{
	return m_realDevice->GetStreamSourceFreq(StreamNumber, pSetting);
}

HRESULT __stdcall D3D9CustomDevice::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
	return m_realDevice->SetIndices(pIndexData);
}

HRESULT __stdcall D3D9CustomDevice::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
	return m_realDevice->GetIndices(ppIndexData);
}

HRESULT __stdcall D3D9CustomDevice::CreatePixelShader(const DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
	return m_realDevice->CreatePixelShader(DWORD*, ppShader);
}

HRESULT __stdcall D3D9CustomDevice::SetPixelShader(IDirect3DPixelShader9* pShader)
{
	return m_realDevice->SetPixelShader(pShader);
}

HRESULT __stdcall D3D9CustomDevice::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
	return m_realDevice->GetPixelShader(ppShader);
}

HRESULT __stdcall D3D9CustomDevice::SetPixelShaderConstantF(UINT StartRegister, const float* pConstantData, UINT Vector4fCount)
{
	return m_realDevice->SetPixelShaderConstantF(StartRegister, float*, Vector4fCount);
}

HRESULT __stdcall D3D9CustomDevice::GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_realDevice->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall D3D9CustomDevice::SetPixelShaderConstantI(UINT StartRegister, const int* pConstantData, UINT Vector4iCount)
{
	return m_realDevice->SetPixelShaderConstantI(StartRegister, int*, Vector4iCount);
}

HRESULT __stdcall D3D9CustomDevice::GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_realDevice->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall D3D9CustomDevice::SetPixelShaderConstantB(UINT StartRegister, const BOOL* pConstantData, UINT BoolCount)
{
	return m_realDevice->SetPixelShaderConstantB(StartRegister, BOOL*, BoolCount);
}

HRESULT __stdcall D3D9CustomDevice::GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_realDevice->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall D3D9CustomDevice::DrawRectPatch(UINT Handle, const float* pNumSegs, const D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return m_realDevice->DrawRectPatch(Handle, float*, D3DRECTPATCH_INFO*);
}

HRESULT __stdcall D3D9CustomDevice::DrawTriPatch(UINT Handle, const float* pNumSegs, const D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return m_realDevice->DrawTriPatch(Handle, float*, D3DTRIPATCH_INFO*);
}

HRESULT __stdcall D3D9CustomDevice::DeletePatch(UINT Handle)
{
	return m_realDevice->DeletePatch(Handle);
}

HRESULT __stdcall D3D9CustomDevice::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	return m_realDevice->CreateQuery(Type, ppQuery);
}

