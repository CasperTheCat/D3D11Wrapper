#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include "Helpers/Helpers.h"

// This is a POD
struct FShaderResources
{
    std::vector<std::shared_ptr<std::vector<uint8_t>>> m_vpvConstantBuffers;
    std::vector<std::shared_ptr<std::vector<uint8_t>>> m_vpvSamplers;
    std::vector<std::shared_ptr<std::vector<uint8_t>>> m_vpvShaderResources;
};