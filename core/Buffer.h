#pragma once

#include <vector>
#include <cstdint>
//#include "../D3D11Wrapper/d3d11Device.h"

#include "Interfaces/Serialisable.h"

class CBuffer final : public ISerialisable
{
public:
	std::vector<uint8_t> m_vData;
	void* m_pEnginePointer;
	class D3D11CustomDevice* m_pOwner;
	bool m_bTransientCapture;
    uint32_t m_uFlags;
	uint32_t m_uStructure;
	uint32_t m_uMisc;

public:
	CBuffer(void* pEngine, const void *pData, uint64_t uDataSize, uint32_t uBindFlags, class D3D11CustomDevice* pOwningDevice);
	~CBuffer();

	virtual void Serialise(std::string strFilename);
	virtual void Load();
};