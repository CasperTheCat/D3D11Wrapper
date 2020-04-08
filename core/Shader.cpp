#include "Shader.h"
#include <memory>

void CShader::SetBytecode(void* pShader, uint64_t uBytecodeLength)
{
	// Resize
	m_vBytecode.resize(uBytecodeLength);

	// Blit the pointer: we don't know how long it'll be alive
	memcpy(m_vBytecode.data(), pShader, uBytecodeLength);
}
