#include "Shader.h"
#include <memory>
#include <d3d11.h>
#include <d3dcompiler.h>

//void CShader::SetBytecode(void* pShader, uint64_t uBytecodeLength)
//{
//	// Resize
//	m_vBytecode.resize(uBytecodeLength);
//
//	// Blit the pointer: we don't know how long it'll be alive
//	memcpy(m_vBytecode.data(), pShader, uBytecodeLength);
//}

CShader::CShader(void* pShader, std::vector<uint8_t>&& vBytecode)
	:
	m_vBytecode(std::move(vBytecode)),
	m_pEnginePointer(pShader)
{
    GenerateHash(m_vHash, m_vBytecode.data(), m_vBytecode.size());
}

CShader::~CShader()
{
}

void CShader::Serialise(std::string strFilename)
{
    std::ofstream serial(strFilename, std::ios::out | std::ios::binary);
    serial.write(
        reinterpret_cast<char*>(m_vHash.data()),
        m_vHash.size()
    );

    if (bHasBeenSerialised) { serial.close();  return; }

    serial.write(
        reinterpret_cast<char*>(m_vBytecode.data()),
        m_vBytecode.size()
    );
    serial.close();

    std::ofstream html(strFilename + ".html", std::ios::out | std::ios::binary);

    ID3DBlob* disShader;
    D3DDisassemble(m_vBytecode.data(), m_vBytecode.size(),
        D3D_DISASM_ENABLE_COLOR_CODE |
        D3D_DISASM_ENABLE_INSTRUCTION_OFFSET |
        D3D_DISASM_ENABLE_DEFAULT_VALUE_PRINTS,
        nullptr,
        &disShader
    );

    html.write(reinterpret_cast<char*>(disShader->GetBufferPointer()), disShader->GetBufferSize());
    html.close();

    bHasBeenSerialised = true;
}

void CShader::Load()
{
	// Pointless on this type :)
}
