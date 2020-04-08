#pragma once
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_2.h>
#include <d3d11_3.h>
#include <d3d11_4.h>
#include <d3d11on12.h>
#include <fstream>
#include <atomic>
#include <vector>
#include <cstdint>

// Include from our mgmt classes
// Not needed yet

// Global Object Manager

//std::unordered_map<ID3D11InputLayout*,uint64_t> InputLayoutMap;
//std::unordered_map<ID3D11VertexShader*, uint64_t> VertexShaderMap;

class D3DObjectManager
{
protected:
	HMODULE hD3D;
	bool bIsDllValid;
	std::atomic<uint64_t> m_uShaderCount;
	std::atomic<uint64_t> m_uShaderResourceCount;
	std::atomic<uint64_t> m_uConstantBufferCount;
	std::atomic<uint64_t> m_uSamplerCount;

public:
	std::ofstream Event;

public:
	D3DObjectManager(HMODULE _hD3D);
	D3DObjectManager();
	~D3DObjectManager();
	
	/// Public functions
	bool LoadDLL();

	// Getters
	HMODULE getDLL();

	///// ///// ////////// ///// /////
	// Present Notify
	//
	void Notify_Present();


	///// ///// ////////// ///// /////
	// Object Management
	//
	
	/**
	 * Shaders
	 */
	void AddShader(std::vector<uint8_t>& vBytes);
};
