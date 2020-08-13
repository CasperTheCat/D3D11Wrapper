#include "InputLayout.h"

#if defined(CORE_D3D11)
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
#elif defined(CORE_D3D9)
#include <d3d9.h>
CInputLayout::CInputLayout(void* pEngine)
{
	m_pEnginePointer = pEngine;
}

std::string GetNameFromUsage(BYTE Usage)
{
	switch (Usage)
	{
		case D3DDECLUSAGE_POSITION:
			return "D3DDECLUSAGE_POSITION";
		case D3DDECLUSAGE_BLENDWEIGHT:
			return "D3DDECLUSAGE_BLENDWEIGHT";
		case D3DDECLUSAGE_BLENDINDICES:
			return "D3DDECLUSAGE_BLENDINDICES";
		case D3DDECLUSAGE_NORMAL:
			return "D3DDECLUSAGE_NORMAL";
		case D3DDECLUSAGE_PSIZE:
			return "D3DDECLUSAGE_PSIZE";
		case D3DDECLUSAGE_TEXCOORD:
			return "D3DDECLUSAGE_TEXCOORD";
		case D3DDECLUSAGE_TANGENT:
			return "D3DDECLUSAGE_TANGENT";
		case D3DDECLUSAGE_BINORMAL:
			return "D3DDECLUSAGE_BINORMAL";
		case D3DDECLUSAGE_TESSFACTOR:
			return "D3DDECLUSAGE_TESSFACTOR";
		case D3DDECLUSAGE_POSITIONT:
			return "D3DDECLUSAGE_POSITIONT";
		case D3DDECLUSAGE_COLOR :
			return "D3DDECLUSAGE_COLOR";
		case D3DDECLUSAGE_FOG :
			return "D3DDECLUSAGE_FOG";
		case D3DDECLUSAGE_DEPTH :
			return "D3DDECLUSAGE_DEPTH";
		case D3DDECLUSAGE_SAMPLE:
			return "D3DDECLUSAGE_SAMPLE";
	default:
		break;
	}
	return "D3DDECLUSAGE_NONAME";
}

#endif

CInputLayout::~CInputLayout()
{
}

void CInputLayout::Serialise(std::string strFilename)
{
    std::ofstream serial(strFilename, std::ios::out | std::ios::binary);

	// Think about the serialise, it needs a bit of work
	for (auto item : m_vData)
	{
		auto tempSize = item.strSemantic.size();
		// Write Semantic
		serial.write(
			reinterpret_cast<char*>(&tempSize),
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
#if defined(CORE_D3D9)
	auto asPtr = reinterpret_cast<IDirect3DVertexDeclaration9*>(m_pEnginePointer);
	UINT numElements;
	//auto ret = asPtr->GetDeclaration(nullptr, &numElements);

	//if (ret != S_OK)
	//{
	//	return;
	//}

	std::vector<D3DVERTEXELEMENT9> map;
	map.resize(MAXD3DDECLLENGTH + 1);

	asPtr->GetDeclaration(map.data(), &numElements);

	for (uint32_t i = 0; i < numElements; ++i)
	{
		//std::vector<char> str;
		//str.resize(strLen);
		//memcpy(str.data(), cElement.SemanticName, str.size());

		if (map[i].Type == D3DDECLTYPE_UNUSED) { break; }

		auto nameStr = GetNameFromUsage(map[i].Usage);
		m_vData.emplace_back(std::vector<char>(nameStr.begin(), nameStr.end()), map[i].UsageIndex, map[i].Stream, map[i].Type);
	}
#endif
}

FInputLayout::FInputLayout(std::vector<char>&& strSemantic, uint16_t uIndex, uint16_t uSlot, uint32_t uFormat)
{
	this->strSemantic = std::move(strSemantic);
	this->uIndex = uIndex;
	this->uSlot = uSlot;
	this->uFormat = uFormat;
}
