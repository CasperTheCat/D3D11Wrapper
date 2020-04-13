#pragma once

#include <cstdint>
#include <string>
#include <fstream>
//#include "../D3D11Wrapper/d3d11Device.h"
#include <Windows.h>
#include <bcrypt.h>
#include <vector>

class ISerialisable
{
public:
	ISerialisable();
	~ISerialisable();

	std::vector<uint8_t> m_vHash;
	bool bHasBeenSerialised = false;
	virtual void Serialise(std::string strFilename) = 0;
	virtual void Load() = 0;
	virtual NTSTATUS GenerateHash(std::vector<uint8_t>& vHash, void* pData, uint32_t uDatasize);


	/**
	 * Compare Hashes
	 *
	 * Returns true when the hashes match
	 */
	virtual bool HashCompare(std::vector<uint8_t> &vHash1, std::vector<uint8_t>& vHash2);
};