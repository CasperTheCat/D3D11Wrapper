#pragma once
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_2.h>
#include <d3d11_3.h>
#include <d3d11_4.h>
#include <d3d11on12.h>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <mutex>

// Data
#include "../core/Frame.h"
#include "../core/Call.h"

// Shorthand
#include "../core/Helpers/Helpers.h"

#include "../core/Buffer.h"
#include "../core/Shader.h"
#include "../core/ShaderResources.h"
#include "../core/Texture.h"

#include <atomic>
#include <filesystem>
// Include from our mgmt classes
// Not needed yet

// Global Object Manager

//std::unordered_map<ID3D11InputLayout*,uint32_t> InputLayoutMap;
//std::unordered_map<ID3D11VertexShader*, uint32_t> VertexShaderMap;

//struct FObjectIndex
//{
//	bool bIsValid
//};


enum class EWritebackState : uint8_t
{
	Idle,
	Queued,
	Complete,

	TOTAL_WRITEBACK_STATES
};

enum class ECaptureState : uint8_t
{
	Await,
	WaitingForPresent,
	Capturing,
	Cooldown,

	TOTAL_CAPTURE_STATES
};

enum class EShaderTypes : uint8_t
{
	Vertex,
	Hull,
	Domain,
	Geometry,
	Pixel,
	Compute,

	TOTAL_SHADER_TYPES
};

enum class EBufferTypes : uint8_t
{
	Vertex,
	Index,

	VertexConstant,
	HullConstant,
	DomainConstant,
	GeometryConstant,
	PixelConstant,
	ComputeConstant,

	TOTAL_SHADER_TYPES
};

enum class ESRVTypes : uint8_t
{
	VertexSRV,
	HullSRV,
	DomainSRV,
	GeometrySRV,
	PixelSRV,
	ComputeSRV,

	TOTAL_SHADER_TYPES
};

class D3DObjectManager
{
private:
	std::vector<CFrame> m_vFrames;

	std::mutex m_mtxShaders;
	std::unordered_map<void*, int32_t> m_mShaders;
	std::vector<CShader> m_vShaders;

	std::mutex m_mtxShaderResources;
	std::unordered_map<void*, int32_t> m_mShaderResources;
	std::vector<CResourceBacking> m_vShaderResourceBackings;

	std::mutex m_mtxBuffers;
	std::unordered_map<void*, int32_t> m_mBuffers;
	std::vector<CBuffer> m_vBuffers;

	std::mutex m_mtxTextures;
	std::unordered_map<void*, int32_t> m_mTextures;
	std::vector<CTexture> m_vTextures;

	std::mutex m_mtxShaderSamples;
	std::unordered_map<void*, int32_t> m_mShaderSamplers;

	// States
	ECaptureState m_eCaptureState;
	EWritebackState m_eWriteState;
	uint32_t m_uCooldownFrames = 15;

	// atomics
	std::atomic<uint64_t> m_uFramenumber;

	std::filesystem::path m_fspRoot;

protected:
	HMODULE hD3D;
	bool bIsDllValid;

public:
	std::ofstream Event;

public:
	D3DObjectManager(HMODULE _hD3D);
	D3DObjectManager();
	~D3DObjectManager();

	void WriteFrame();
	CFrame *GetCurrentFrame();
	
	/// Public functions
	bool LoadDLL();

	// Getters
	HMODULE getDLL();

	///// ///// ////////// ///// /////
	// Present Notify
	//
	void Notify_Present();

	void Notify_Draw();

	///// ///// ////////// ///// /////
	// Accessor
	//

	void SetTopology(uint32_t eTopology);

	///// ///// ////////// ///// /////
	// Object Management
	//
	
	/**
	 * Shaders
	 */
	void AddShader(void* pReturnPtr, const void* pBytecode, uint64_t uBytecodeLength);
	int32_t QueryShader(void* pReturnPtr);
	void SetShader(void* pReturnPtr, EShaderTypes eShaderType);
	CShader* GetShader(uint32_t iShaderIndex);


	void SerialiseShader(uint32_t uShaderIndex, std::string &strShaderName);
	void SerialiseShaderBytecode(uint32_t uShaderIndex, std::string& strShaderName);

	/**
	 * Buffer
	 */
	void AddBuffer(void* pReturnPtr, const void* pData, uint64_t uDataSize, uint32_t uBindType, class D3D11CustomDevice* pOwningDevice);
	int32_t QueryBuffer(void* pReturnPtr);
	void SetBuffer(void* pReturnPtr, EBufferTypes eBufferType);
	CBuffer* GetBuffer(uint32_t iBufferIndex);

	/**
	 * Textures 
	 */
	void AddTexture(void* pReturnPtr, const D3D11_SUBRESOURCE_DATA* pData, FTextureInfo &texInfo, class D3D11CustomDevice* pOwningDevice, bool bIsImmediate);
	int32_t QueryTexture(void* pReturnPtr);
	CTexture* GetTexture(uint32_t iTexIndex);

	/**
	 * SRVs
	 */
	void AddResourceView(void* pReturnPtr, const void* pResPtr, EBackingType eBackingType);
	int32_t QueryResourceView(void* pReturnPtr);
	void SetResourceView(void* pReturnPtr, ESRVTypes eBufferType);
	CResourceBacking* GetResourceView(uint32_t iSRVIndex);

};
