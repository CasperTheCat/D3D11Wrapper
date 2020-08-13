#include "Buffer.h"

#if defined(CORE_D3D11)
#include "../D3D11Wrapper/d3d11Device.h"
CBuffer::CBuffer(void* pEngine, const void* pData, uint64_t uDataSize, uint32_t uBindFlags, D3D11CustomDevice* pOwningDevice) :
    m_pEnginePointer(pEngine),
    m_pOwner(pOwningDevice),
    m_uFlags(uBindFlags)
{
	if (pData && uDataSize > 0)
	{
		m_bTransientCapture = false;
        m_vData.resize(uDataSize);
		memcpy(m_vData.data(), pData, uDataSize);
        GenerateHash(m_vHash, m_vData.data(), m_vData.size());
	}
    else
    {
        m_bTransientCapture = true;
    }

    ID3D11Buffer* asBuffer = reinterpret_cast<ID3D11Buffer*>(m_pEnginePointer);

    D3D11_BUFFER_DESC ofalseDesc{};
    asBuffer->GetDesc(&ofalseDesc);

    m_uStructure = ofalseDesc.StructureByteStride;
    m_uMisc = ofalseDesc.MiscFlags;
}

CBuffer::~CBuffer()
{
}


void CBuffer::Load()
{
    //if (m_uFlags == D3D11_BIND_UNORDERED_ACCESS) { return; }
    //if (m_uMisc == D3D11_RESOURCE_MISC_BUFFER_STRUCTURED)

    if (m_bTransientCapture)
    {
        ID3D11Buffer* asBuffer = reinterpret_cast<ID3D11Buffer*>(m_pEnginePointer);

        D3D11_BUFFER_DESC falseDesc{};
        asBuffer->GetDesc(&falseDesc);
        
        m_uStructure = falseDesc.StructureByteStride;

        falseDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        falseDesc.Usage = D3D11_USAGE_STAGING;
        falseDesc.BindFlags = 0;
        falseDesc.MiscFlags = 0;

        ID3D11Buffer* pResBuffer;
        auto h = m_pOwner->RealDevice()->CreateBuffer(&falseDesc, nullptr, &pResBuffer);
        if (h != S_OK) { return; }

        m_pOwner->RealContext()->CopyResource(pResBuffer, asBuffer);

        // Copy Data
        // Maybe a function
        D3D11_MAPPED_SUBRESOURCE mapped{};
        h = m_pOwner->RealContext()->Map(pResBuffer, 0, D3D11_MAP_READ, 0, &mapped);

        if (h == S_OK && mapped.pData)
        {
            std::vector<uint8_t> mapHash;
            auto nt = GenerateHash(mapHash, mapped.pData, falseDesc.ByteWidth);

            if (!HashCompare(m_vHash, mapHash))
            {
                bHasBeenSerialised = false; // Not written the new one!

                m_vHash = std::move(mapHash);

                m_vData.resize(falseDesc.ByteWidth);
                memcpy(m_vData.data(), mapped.pData, m_vData.size());
            }
        }

        m_pOwner->RealContext()->Unmap(pResBuffer, 0);
        pResBuffer->Release();
    }
}

#elif defined(CORE_D3D9)
#include "../D3D9Wrapper/d3d9Device.h"
CBuffer::CBuffer(void* pEngine, EBufferTypes eType, uint64_t uDataSize, uint32_t uBindFlags, PD3DCustomDevice pOwningDevice) :
    m_pEnginePointer(pEngine),
    m_pOwner(pOwningDevice),
    m_uFlags(uBindFlags),
    m_bTransientCapture(true),
    m_eBufferType(eType)
{
    //auto* asBuffer = reinterpret_cast<IDirect3DResource9*>(m_pEnginePointer);

    //D3D11_BUFFER_DESC ofalseDesc{};
    //asBuffer->GetDesc(&ofalseDesc);

    //m_uStructure = ofalseDesc.StructureByteStride;
    //m_uMisc = ofalseDesc.MiscFlags;
}

CBuffer::~CBuffer()
{
}

void CBuffer::Load()
{
    if (m_bTransientCapture)
    {
        switch (m_eBufferType)
        {
        case EBufferTypes::Vertex:
            LoadBuffer<IDirect3DVertexBuffer9, D3DVERTEXBUFFER_DESC>();
            break;
        case EBufferTypes::Index:
            LoadBuffer<IDirect3DIndexBuffer9, D3DINDEXBUFFER_DESC>();
            break;
        case EBufferTypes::VertexConstant:
            break;
        case EBufferTypes::HullConstant:
            break;
        case EBufferTypes::DomainConstant:
            break;
        case EBufferTypes::GeometryConstant:
            break;
        case EBufferTypes::PixelConstant:
            break;
        case EBufferTypes::ComputeConstant:
            break;
        case EBufferTypes::TOTAL_SHADER_TYPES:
            break;
        default:
            break;
        }
    }
}
#endif

void CBuffer::Serialise(std::string strFilename)
{
    std::ofstream serial(strFilename, std::ios::out | std::ios::binary);
    serial.write(
        reinterpret_cast<char*>(m_vHash.data()),
        m_vHash.size()
    );

    if (bHasBeenSerialised) { serial.close();  return; }

    serial.write(
        reinterpret_cast<char*>(&m_uFlags),
        sizeof(uint32_t)
    );
    serial.write(
        reinterpret_cast<char*>(&m_uStructure),
        sizeof(uint32_t)
    );
    serial.write(
        reinterpret_cast<char*>(m_vData.data()),
        m_vData.size()
    );
    serial.close();

    bHasBeenSerialised = true;
}