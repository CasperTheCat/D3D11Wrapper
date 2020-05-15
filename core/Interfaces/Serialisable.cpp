#include "Serialisable.h"

ISerialisable::ISerialisable()
{
	// Sha256
	m_vHash.resize(32);
}

ISerialisable::~ISerialisable()
{
}



NTSTATUS ISerialisable::GenerateHash(std::vector<uint8_t>& vHash, void* pData, uint32_t uDatasize)
{
	BCRYPT_ALG_HANDLE algHandle{};

	auto nt = BCryptOpenAlgorithmProvider(
		&algHandle,
		BCRYPT_SHA256_ALGORITHM,
		nullptr, // Try all
		0
	);
	if (nt != S_OK) { return nt; }

	vHash.resize(32);

	nt = BCryptHash(
		algHandle,
		nullptr,
		0,
		reinterpret_cast<uint8_t*>(pData),
		uDatasize,
		vHash.data(),
		vHash.size()
	);

	auto second = BCryptCloseAlgorithmProvider(
		algHandle,
		0
	);

	return (nt != S_OK) ? nt : second;
}

// This is not a secure function :P
bool ISerialisable::HashCompare(std::vector<uint8_t>& vHash1, std::vector<uint8_t>& vHash2)
{
	if (vHash1.size() == 32 && vHash1.size() == vHash2.size()) { return false; }
	for (uint32_t i = 0; i < 32; ++i)
	{
		if (vHash1[i] != vHash2[i]) { return false; }
	}

	return true;
}
