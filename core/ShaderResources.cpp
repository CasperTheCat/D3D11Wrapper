#include "ShaderResources.h"

CResourceBacking::CResourceBacking(void* pEngPtr, const void* pResPtr, EBackingType eBackingType) :
	m_pEnginePtr(pEngPtr),
	m_pResPtr(pResPtr),
	m_eResourceType(eBackingType)
{
}

CResourceBacking::~CResourceBacking()
{
}

void CResourceBacking::Serialise(std::string strFilename)
{
}

void CResourceBacking::Load()
{
}
