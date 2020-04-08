#pragma once

#include <vector>
#include <cstdint>

// NOTE: The CShader class doesn't contain resources
// This is because it is entirely concievable to see
// a shader invoked again with a different set of
// resources when rendering a second object

// POD for Shaders
class CShader final
{
	// What needs to be here?

	// 1. Shader Bytecode
	// 2. Shader Disassembly (Can be a proxy :P)
public:
	std::vector<uint8_t> m_vBytecode;
	void* m_pDXPointer;

public:
	CShader(void *pDevShader);
	~CShader();

	/**
	 * Sets Bytecode
	 */
	void SetBytecode(void* pShader, uint64_t uBytecodeLength);
};