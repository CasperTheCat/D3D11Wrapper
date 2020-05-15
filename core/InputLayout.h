#pragma once

#include <vector>
#include <cstdint>
#include <d3d11.h>
#include "Interfaces/Serialisable.h"


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
	CInputLayout(void* pEngine, const D3D11_INPUT_ELEMENT_DESC *pElements, uint32_t uNumElements);
	~CInputLayout();

	virtual void Serialise(std::string strFilename);
	virtual void Load();
};