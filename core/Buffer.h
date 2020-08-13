#pragma once

#include <vector>
#include <cstdint>
//#include "../D3D11Wrapper/d3d11Device.h"


#if defined(CORE_D3D11)
#define PD3DCustomDevice D3D11CustomDevice*
#elif defined(CORE_D3D9)
#include "Helpers/Helpers.h"
#define PD3DCustomDevice D3D9CustomDevice*
//CBuffer(void* pEngine, const void* pData, uint64_t uDataSize, uint32_t uBindFlags, class D3D9CustomDevice* pOwningDevice);
#else
#error Wrong Core
#endif

#include "Interfaces/Serialisable.h"

class CBuffer final : public ISerialisable
{
public:
	std::vector<uint8_t> m_vData;
	void* m_pEnginePointer;
	class PD3DCustomDevice m_pOwner;
	bool m_bTransientCapture;
    uint32_t m_uFlags;
	uint32_t m_uStructure;
	uint32_t m_uMisc;

#ifdef CORE_D3D9
	EBufferTypes m_eBufferType;
#endif // CORE_D3D9


public:
#if defined(CORE_D3D11)
	CBuffer(void* pEngine, const void* pData, uint64_t uDataSize, uint32_t uBindFlags, class PD3DCustomDevice pOwningDevice);
#else defined(CORE_D3D9)
	CBuffer(void* pEngine, EBufferTypes eType, uint64_t uDataSize, uint32_t uBindFlags, class PD3DCustomDevice pOwningDevice);

	template <typename T, typename B>
	void LoadBuffer()
	{
		T* asBuffer = reinterpret_cast<T*>(m_pEnginePointer);
		B lDesc{};
		auto ret = asBuffer->GetDesc(&lDesc);
		if (ret != S_OK) { return; }

		// Get the buffer data
		uint8_t* mappedData;
		ret = asBuffer->Lock(0, 0, reinterpret_cast<void**>(&mappedData), 0x10L); // D3DLOCK_READONLY

		// If it is okay, hash and compare before copy
		if (ret == S_OK)
		{
			std::vector<uint8_t> mapHash;
			auto nt = GenerateHash(mapHash, mappedData, lDesc.Size);

			if (!HashCompare(m_vHash, mapHash))
			{
				bHasBeenSerialised = false;


				m_vHash = std::move(mapHash);
				m_vData.resize(lDesc.Size);
				memcpy(m_vData.data(), mappedData, m_vData.size());
			}
		}

		ret = asBuffer->Unlock();
	}
#endif
	~CBuffer();

	virtual void Serialise(std::string strFilename);
	virtual void Load();
};