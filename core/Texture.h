#pragma once

#include <vector>
#include <cstdint>
#include <d3d11.h>
#include "Interfaces/Serialisable.h"

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
	class D3D11CustomDevice* m_pOwner;
	D3D11_SUBRESOURCE_DATA m_stResourceInfo;
	FTextureInfo m_stTexInfo;


public:
	CTexture(void* pEngine, const D3D11_SUBRESOURCE_DATA* pData, FTextureInfo *texInfo, class D3D11CustomDevice* pOwningDevice, bool bIsImmediate);
	~CTexture();

	virtual void Serialise(std::string strFilename);
	virtual void Load();

	virtual uint32_t GetPixelSizeFromTypeBits(uint32_t dxgiFormat);

	virtual void Load1D();
	virtual void Load2D();
	virtual void Load3D();
};