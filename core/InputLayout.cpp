#include "InputLayout.h"

CInputLayout::CInputLayout(void* pEngine, const D3D11_INPUT_ELEMENT_DESC* pElements, uint32_t uNumElements)
{
	m_pEnginePointer = pEngine;

	for (uint32_t i = 0; i < uNumElements; ++i)
	{
		auto cElement = pElements[i];

		auto strLen = strlen(cElement.SemanticName);
		std::vector<char> str;
		str.resize(strLen);
		memcpy(str.data(), cElement.SemanticName, str.size());

		m_vData.emplace_back(std::move(str), cElement.SemanticIndex, cElement.InputSlot, cElement.Format);
	}
}

CInputLayout::~CInputLayout()
{
}

void CInputLayout::Serialise(std::string strFilename)
{
    std::ofstream serial(strFilename, std::ios::out | std::ios::binary);

	// Think about the serialise, it needs a bit of work
	for (auto item : m_vData)
	{
		// Write Semantic
		serial.write(
			reinterpret_cast<char*>(item.strSemantic.size()),
			sizeof(size_t)
		);

		// Write Semantic
		serial.write(
			reinterpret_cast<char*>(item.strSemantic.data()),
			item.strSemantic.size()
		);

		serial.write(
			reinterpret_cast<char*>(&item.uIndex),
			sizeof(uint16_t)
		);

		serial.write(
			reinterpret_cast<char*>(&item.uSlot),
			sizeof(uint16_t)
		);

		serial.write(
			reinterpret_cast<char*>(&item.uFormat),
			sizeof(uint32_t)
		);
	}

    serial.close();

//    bHasBeenSerialised = true;
}

void CInputLayout::Load()
{
}

FInputLayout::FInputLayout(std::vector<char>&& strSemantic, uint16_t uIndex, uint16_t uSlot, uint32_t uFormat)
{
	this->strSemantic = std::move(strSemantic);
	this->uIndex = uIndex;
	this->uSlot = uSlot;
	this->uFormat = uFormat;
}
