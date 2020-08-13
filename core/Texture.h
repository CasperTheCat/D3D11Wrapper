#pragma once

#include <vector>
#include <cstdint>
#include <d3d11.h>
#include "Interfaces/Serialisable.h"

#if defined(CORE_D3D11)
#define PD3DCustomDevice D3D11CustomDevice*
#define PD3DSubResData D3D11_SUBRESOURCE_DATA*
#elif defined(CORE_D3D9)
#define PD3DCustomDevice D3D9CustomDevice*
#define PD3DSubResData void*
//CBuffer(void* pEngine, const void* pData, uint64_t uDataSize, uint32_t uBindFlags, class D3D9CustomDevice* pOwningDevice);
#else
#error Wrong Core
#endif

struct FImageChannelInfo
{
	uint32_t uComponents;
	uint32_t uBitness;
};

struct FTextureInfo
{
	uint32_t uWidth;
	uint32_t uHeight;
	uint32_t uDepth;
	uint32_t uFormat;
	uint32_t uCount;
};

class CTexture final : public ISerialisable
{
public:
	std::vector<uint8_t> m_vData;
	void* m_pEnginePointer;
	bool m_bTransientCapture;
	class PD3DCustomDevice m_pOwner;
#ifdef CORE_D3D11
	D3D11_SUBRESOURCE_DATA m_stResourceInfo;
#endif
	FTextureInfo m_stTexInfo;


public:
	CTexture(void* pEngine, const PD3DSubResData pData, FTextureInfo *texInfo, class PD3DCustomDevice pOwningDevice, bool bIsImmediate);
	~CTexture();

	virtual void Serialise(std::string strFilename);
	virtual void Load();

	virtual uint32_t GetPixelSizeFromTypeBits(uint32_t dxgiFormat);

	virtual void Load1D();
	virtual void Load2D();
	virtual void Load3D();
};