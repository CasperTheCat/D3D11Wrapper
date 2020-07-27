#include "Texture.h"

#include <iostream>

#if defined(CORE_D3D11)
#include "../D3D11Wrapper/d3d11Device.h"
CTexture::CTexture(void* pEngine, const D3D11_SUBRESOURCE_DATA* pData, FTextureInfo* texInfo, D3D11CustomDevice* pOwningDevice, bool bIsImmediate) :
	m_pEnginePointer(pEngine),
	m_bTransientCapture(!bIsImmediate),
	m_pOwner(pOwningDevice)
{
	m_stResourceInfo.pSysMem = nullptr;
	m_stResourceInfo.SysMemPitch = 0;
	m_stResourceInfo.SysMemSlicePitch = 0;

	m_stTexInfo.uCount = texInfo->uCount;
	m_stTexInfo.uDepth = texInfo->uDepth;
	m_stTexInfo.uFormat = texInfo->uFormat;
	m_stTexInfo.uHeight = texInfo->uHeight;
	m_stTexInfo.uWidth = texInfo->uWidth;

	// Do copy?
	if (bIsImmediate && pData)
	{
		m_stResourceInfo.pSysMem = pData->pSysMem;
		m_stResourceInfo.SysMemPitch = pData->SysMemPitch;
		m_stResourceInfo.SysMemSlicePitch = pData->SysMemSlicePitch;
	}
}

CTexture::~CTexture()
{
}

void CTexture::Serialise(std::string strFilename)
{
    std::ofstream serial(strFilename, std::ios::out | std::ios::binary);
    serial.write(
        reinterpret_cast<char*>(m_vHash.data()),
        m_vHash.size()
    );

    if (bHasBeenSerialised) { serial.close();  return; }

    serial.write(
        reinterpret_cast<char*>(&m_stTexInfo),
        sizeof(m_stTexInfo)
    );
    serial.write(
        reinterpret_cast<char*>(m_vData.data()),
        m_vData.size()
    );
    serial.close();

    bHasBeenSerialised = true;
}



uint32_t CTexture::GetPixelSizeFromTypeBits(uint32_t dxgiFormat)
{
	DXGI_FORMAT asT = static_cast<DXGI_FORMAT>(dxgiFormat);
	switch (asT)
	{
    case DXGI_FORMAT_UNKNOWN:
        return 0;
        break;
    case DXGI_FORMAT_R32G32B32A32_TYPELESS:
    case DXGI_FORMAT_R32G32B32A32_FLOAT:
    case DXGI_FORMAT_R32G32B32A32_UINT:
    case DXGI_FORMAT_R32G32B32A32_SINT:
        return 128;
        break;
    case DXGI_FORMAT_R32G32B32_TYPELESS:
    case DXGI_FORMAT_R32G32B32_FLOAT:
    case DXGI_FORMAT_R32G32B32_UINT:
    case DXGI_FORMAT_R32G32B32_SINT:
        return 96;
        break;
    case DXGI_FORMAT_R16G16B16A16_TYPELESS:
    case DXGI_FORMAT_R16G16B16A16_FLOAT:
    case DXGI_FORMAT_R16G16B16A16_UNORM:
    case DXGI_FORMAT_R16G16B16A16_UINT:
    case DXGI_FORMAT_R16G16B16A16_SNORM:
    case DXGI_FORMAT_R16G16B16A16_SINT:
    case DXGI_FORMAT_R32G32_TYPELESS:
    case DXGI_FORMAT_R32G32_FLOAT:
    case DXGI_FORMAT_R32G32_UINT:
    case DXGI_FORMAT_R32G32_SINT:
    case DXGI_FORMAT_R32G8X24_TYPELESS:
        return 64;
        break;
    case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
    case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
    case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
        return 64;
        break;
    case DXGI_FORMAT_R10G10B10A2_TYPELESS:
    case DXGI_FORMAT_R10G10B10A2_UNORM:
    case DXGI_FORMAT_R10G10B10A2_UINT:
    case DXGI_FORMAT_R11G11B10_FLOAT:
        return 32;
        break;
    case DXGI_FORMAT_R8G8B8A8_TYPELESS:
    case DXGI_FORMAT_R8G8B8A8_UNORM:
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
    case DXGI_FORMAT_R8G8B8A8_UINT:
    case DXGI_FORMAT_R8G8B8A8_SNORM:
    case DXGI_FORMAT_R8G8B8A8_SINT:
    case DXGI_FORMAT_R16G16_TYPELESS:
    case DXGI_FORMAT_R16G16_FLOAT:
    case DXGI_FORMAT_R16G16_UNORM:
    case DXGI_FORMAT_R16G16_UINT:
    case DXGI_FORMAT_R16G16_SNORM:
    case DXGI_FORMAT_R16G16_SINT:
    case DXGI_FORMAT_R32_TYPELESS:
    case DXGI_FORMAT_D32_FLOAT:
    case DXGI_FORMAT_R32_FLOAT:
    case DXGI_FORMAT_R32_UINT:
    case DXGI_FORMAT_R32_SINT:
    case DXGI_FORMAT_R24G8_TYPELESS:
    case DXGI_FORMAT_D24_UNORM_S8_UINT:
    case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
    case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
        return 32;
        break;
    case DXGI_FORMAT_R8G8_TYPELESS:
    case DXGI_FORMAT_R8G8_UNORM:
    case DXGI_FORMAT_R8G8_UINT:
    case DXGI_FORMAT_R8G8_SNORM:
    case DXGI_FORMAT_R8G8_SINT:
    case DXGI_FORMAT_R16_TYPELESS:
    case DXGI_FORMAT_R16_FLOAT:
    case DXGI_FORMAT_D16_UNORM:
    case DXGI_FORMAT_R16_UNORM:
    case DXGI_FORMAT_R16_UINT:
    case DXGI_FORMAT_R16_SNORM:
    case DXGI_FORMAT_R16_SINT:
        return 16;
        break;
    case DXGI_FORMAT_R8_TYPELESS:
    case DXGI_FORMAT_R8_UNORM:
    case DXGI_FORMAT_R8_UINT:
    case DXGI_FORMAT_R8_SNORM:
    case DXGI_FORMAT_R8_SINT:
    case DXGI_FORMAT_A8_UNORM:
        return 8;
        break;
    case DXGI_FORMAT_R1_UNORM:
        return 1;
        break;
    case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
        return 32;
        break;
    case DXGI_FORMAT_R8G8_B8G8_UNORM:
    case DXGI_FORMAT_G8R8_G8B8_UNORM:
        return 32;
        break;
    case DXGI_FORMAT_BC1_TYPELESS:
    case DXGI_FORMAT_BC1_UNORM:
    case DXGI_FORMAT_BC1_UNORM_SRGB:
        return 4;
        break;
    case DXGI_FORMAT_BC2_TYPELESS:
    case DXGI_FORMAT_BC2_UNORM:
    case DXGI_FORMAT_BC2_UNORM_SRGB:
        return 8;
        break;
    case DXGI_FORMAT_BC3_TYPELESS:
    case DXGI_FORMAT_BC3_UNORM:
    case DXGI_FORMAT_BC3_UNORM_SRGB:
        return 8;
        break;
    case DXGI_FORMAT_BC4_TYPELESS:
    case DXGI_FORMAT_BC4_UNORM:
    case DXGI_FORMAT_BC4_SNORM:
        return 4;
        break;
    case DXGI_FORMAT_BC5_TYPELESS:
    case DXGI_FORMAT_BC5_UNORM:
    case DXGI_FORMAT_BC5_SNORM:
        return 8;
        break;
    case DXGI_FORMAT_B5G6R5_UNORM:
        return 16;
        break;
    case DXGI_FORMAT_B5G5R5A1_UNORM:
        return 16;
        break;
    case DXGI_FORMAT_B8G8R8A8_UNORM:
    case DXGI_FORMAT_B8G8R8X8_UNORM:
    case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
    case DXGI_FORMAT_B8G8R8A8_TYPELESS:
    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
    case DXGI_FORMAT_B8G8R8X8_TYPELESS:
    case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
        return 32;
        break;
    case DXGI_FORMAT_BC6H_TYPELESS:
    case DXGI_FORMAT_BC6H_UF16:
    case DXGI_FORMAT_BC6H_SF16:
        return 8;
        break;
    case DXGI_FORMAT_BC7_TYPELESS:
    case DXGI_FORMAT_BC7_UNORM:
    case DXGI_FORMAT_BC7_UNORM_SRGB:
        return 8;
        break;
    case DXGI_FORMAT_AYUV:
        return 32;
        break;
    case DXGI_FORMAT_Y410:
        return 32;
        break;
    case DXGI_FORMAT_Y416:
        return 64;
        break;
    case DXGI_FORMAT_NV12:
        return 24;
        break;
    case DXGI_FORMAT_P010:
        break;
    case DXGI_FORMAT_P016:
        break;
    case DXGI_FORMAT_420_OPAQUE:
        break;
    case DXGI_FORMAT_YUY2:
        break;
    case DXGI_FORMAT_Y210:
        break;
    case DXGI_FORMAT_Y216:
        break;
    case DXGI_FORMAT_NV11:
        break;
    case DXGI_FORMAT_AI44:
        break;
    case DXGI_FORMAT_IA44:
        break;
    case DXGI_FORMAT_P8:
        return 1;
        break;
    case DXGI_FORMAT_A8P8:
        return 2;
        break;
    case DXGI_FORMAT_B4G4R4A4_UNORM:
        return 16;
        break;
    case DXGI_FORMAT_P208:
        break;
    case DXGI_FORMAT_V208:
        break;
    case DXGI_FORMAT_V408:
        break;
    case DXGI_FORMAT_FORCE_UINT:
        break;
    default:
        break;
	}
    
    return 0;
}

void CTexture::Load1D()
{
	auto as1D = reinterpret_cast<ID3D11Texture1D*>(m_pEnginePointer);

	D3D11_TEXTURE1D_DESC falseDesc{};
	as1D->GetDesc(&falseDesc);

	falseDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	falseDesc.Usage = D3D11_USAGE_STAGING;
    falseDesc.BindFlags = 0;
    falseDesc.MiscFlags = 0;

    m_pOwner->GetGLOM()->Event << "[CTex] Format is " << falseDesc.Format << std::endl;
    auto size = (GetPixelSizeFromTypeBits(falseDesc.Format) * falseDesc.Width * falseDesc.ArraySize) / 8;
    m_pOwner->GetGLOM()->Event << "[CTex] Size is " << size << std::endl;
    if (size == 0) { return; }

    /////
    // Create CPU Buffer
    //

    ID3D11Texture1D* pResBuffer;
    auto h = m_pOwner->RealDevice()->CreateTexture1D(&falseDesc, nullptr, &pResBuffer);
    if (h != S_OK) { return; }

    m_pOwner->RealContext()->CopyResource(pResBuffer, as1D);
    
    // Copy Data
    // Maybe a function
    D3D11_MAPPED_SUBRESOURCE mapped{};
    h = m_pOwner->RealContext()->Map(pResBuffer, 0, D3D11_MAP_READ, 0, &mapped);

    if (h == S_OK && mapped.pData)
    {
        std::vector<uint8_t> mapHash;
        auto nt = GenerateHash(mapHash, mapped.pData, size);

        if (!HashCompare(m_vHash, mapHash))
        {
            bHasBeenSerialised = false; // Not written the new one!

            m_vHash = std::move(mapHash);

            m_vData.resize(size);
            memcpy(m_vData.data(), mapped.pData, m_vData.size());
        }
    }

    m_pOwner->RealContext()->Unmap(pResBuffer, 0);
    pResBuffer->Release();
}

void CTexture::Load2D()
{
    auto as2D = reinterpret_cast<ID3D11Texture2D*>(m_pEnginePointer);

    D3D11_TEXTURE2D_DESC falseDesc{};
    as2D->GetDesc(&falseDesc);

    falseDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    falseDesc.Usage = D3D11_USAGE_STAGING;
    falseDesc.BindFlags = 0;
    falseDesc.MiscFlags = 0;

    m_pOwner->GetGLOM()->Event << "[CTex] Format is " << falseDesc.Format << std::endl;
    auto size = (GetPixelSizeFromTypeBits(falseDesc.Format) * falseDesc.Width * falseDesc.Height * falseDesc.ArraySize) / 8;
    m_pOwner->GetGLOM()->Event << "[CTex] Size is " << size << std::endl;
    if (size == 0) { return; }

    /////
    // Create CPU Buffer
    //

    ID3D11Texture2D* pResBuffer;
    auto h = m_pOwner->RealDevice()->CreateTexture2D(&falseDesc, nullptr, &pResBuffer);
    if (h != S_OK) { return; }

    m_pOwner->RealContext()->CopyResource(pResBuffer, as2D);

    // Copy Data
    // Maybe a function
    D3D11_MAPPED_SUBRESOURCE mapped{};
    h = m_pOwner->RealContext()->Map(pResBuffer, 0, D3D11_MAP_READ, 0, &mapped);

    if (h == S_OK && mapped.pData)
    {
        std::vector<uint8_t> mapHash;
        auto nt = GenerateHash(mapHash, mapped.pData, size);

        if (!HashCompare(m_vHash, mapHash))
        {
            bHasBeenSerialised = false; // Not written the new one!

            m_vHash = std::move(mapHash);

            m_vData.resize(size);
            memcpy(m_vData.data(), mapped.pData, m_vData.size());
        }
    }

    m_pOwner->RealContext()->Unmap(pResBuffer, 0);
    pResBuffer->Release();
}

void CTexture::Load3D()
{
    auto as3D = reinterpret_cast<ID3D11Texture3D*>(m_pEnginePointer);

    D3D11_TEXTURE3D_DESC falseDesc{};
    as3D->GetDesc(&falseDesc);

    falseDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    falseDesc.Usage = D3D11_USAGE_STAGING;
    falseDesc.BindFlags = 0;
    falseDesc.MiscFlags = 0;

    m_pOwner->GetGLOM()->Event << "[CTex] Format is " << falseDesc.Format << std::endl;
    auto size = (GetPixelSizeFromTypeBits(falseDesc.Format) * falseDesc.Width * falseDesc.Height * falseDesc.Depth) / 8;
    m_pOwner->GetGLOM()->Event << "[CTex] Size is " << size << std::endl;
    if (size == 0) { return; }

    /////
    // Create CPU Buffer
    //

    ID3D11Texture3D* pResBuffer;
    auto h = m_pOwner->RealDevice()->CreateTexture3D(&falseDesc, nullptr, &pResBuffer);
    if (h != S_OK) { return; }

    m_pOwner->RealContext()->CopyResource(pResBuffer, as3D);

    // Copy Data
    // Maybe a function
    D3D11_MAPPED_SUBRESOURCE mapped{};
    h = m_pOwner->RealContext()->Map(pResBuffer, 0, D3D11_MAP_READ, 0, &mapped);

    if (h == S_OK && mapped.pData)
    {
        std::vector<uint8_t> mapHash;
        auto nt = GenerateHash(mapHash, mapped.pData, size);

        if (!HashCompare(m_vHash, mapHash))
        {
            bHasBeenSerialised = false; // Not written the new one!

            m_vHash = std::move(mapHash);

            m_vData.resize(size);
            memcpy(m_vData.data(), mapped.pData, m_vData.size());
        }
    }

    m_pOwner->RealContext()->Unmap(pResBuffer, 0);
    pResBuffer->Release();
}


#elif defined(CORE_D3D9)
#include "../D3D9Wrapper/d3d9Device.h"
CTexture::CTexture(void* pEngine, const void* pData, FTextureInfo* texInfo, D3D9CustomDevice* pOwningDevice, bool bIsImmediate) :
    m_pEnginePointer(pEngine),
    m_bTransientCapture(!bIsImmediate),
    m_pOwner(pOwningDevice)
{
    m_stTexInfo.uCount = texInfo->uCount;
    m_stTexInfo.uDepth = texInfo->uDepth;
    m_stTexInfo.uFormat = texInfo->uFormat;
    m_stTexInfo.uHeight = texInfo->uHeight;
    m_stTexInfo.uWidth = texInfo->uWidth;
}

CTexture::~CTexture()
{
}

void CTexture::Serialise(std::string strFilename)
{

}

uint32_t CTexture::GetPixelSizeFromTypeBits(uint32_t dxgiFormat)
{
    return 0;
}

void CTexture::Load1D()
{

}

void CTexture::Load2D()
{

}

void CTexture::Load3D()
{

}
#endif


void CTexture::Load()
{
    // Infer Type
    if (m_stTexInfo.uDepth == 0)
    {
        if (m_stTexInfo.uHeight == 0)
        {
            Load1D();
        }
        else
        {
            // 2D
            Load2D();
        }
    }
    else
    {
        // 3D
        Load3D();
    }
}