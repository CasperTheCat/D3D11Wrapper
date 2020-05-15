#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include "Helpers/Helpers.h"

#include "Interfaces/Serialisable.h"

// This is a POD
struct FShaderResources
{
    std::vector<int32_t> viConstantBuffers;
    std::vector<int32_t> viSamplers;
    std::vector<int32_t> viShaderResources;
};

enum class EBackingType : uint8_t
{
    Buffer,
    Texture,
    Other,

    TOTAL_BACKING_TYPES
};

class CResourceBacking : public ISerialisable
{
public:
    void* m_pEnginePtr;
    const void* m_pResPtr;
    EBackingType m_eResourceType;

public:
    CResourceBacking(void *pEngPtr, const void *pResPtr, EBackingType eBackingType);
    ~CResourceBacking();

    virtual void Serialise(std::string strFilename);
    virtual void Load();
};