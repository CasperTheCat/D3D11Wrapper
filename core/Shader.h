#pragma once

#include <vector>
#include <cstdint>

#include "Interfaces/Serialisable.h"

// NOTE: The CShader class doesn't contain resources
// This is because it is entirely concievable to see
// a shader invoked again with a different set of
// resources when rendering a second object

// POD for Shaders
class CShader final : public ISerialisable
{
	// What needs to be here?

	// 1. Shader Bytecode
	// 2. Shader Disassembly (Can be a proxy :P)
public:
	std::vector<uint8_t> m_vBytecode;
	void* m_pEnginePointer;

public:
	//CShader(void* pEnginePointer, void* pBytecode, uint64_t uBytecodeLength);
	CShader(void* pShader, std::vector<uint8_t> &&vBytecode);
	~CShader();

	virtual void Serialise(std::string strFilename);
	virtual void Load();
};