#pragma once

#include <vector>
#include <cstdint>

#include "Interfaces/Serialisable.h"

#if defined(CORE_D3D11)
#include <d3d11.h>
#endif

struct FInputLayout
{
	std::vector<char> strSemantic;
	uint16_t uIndex;
	uint16_t uSlot;
	uint32_t uFormat;

	FInputLayout(std::vector<char> &&strSemantic, uint16_t uIndex, uint16_t uSlot, uint32_t uFormat);
};

class CInputLayout final : public ISerialisable
{
public:
	std::vector<FInputLayout> m_vData;
	void* m_pEnginePointer;

public:
#if defined(CORE_D3D11)
	CInputLayout(void* pEngine, const D3D11_INPUT_ELEMENT_DESC* pElements, uint32_t uNumElements);
#elif defined(CORE_D3D9)
	CInputLayout(void* pEngine);
//CBuffer(void* pEngine, const void* pData, uint64_t uDataSize, uint32_t uBindFlags, class D3D9CustomDevice* pOwningDevice);
#else
#error Wrong Core
#endif
	
	~CInputLayout();

	virtual void Serialise(std::string strFilename);
	virtual void Load();
};