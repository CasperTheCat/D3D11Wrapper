#pragma once
#include <vector>
#include <memory>
#include "Shader.h"
#include "ShaderResources.h"
#include "Interfaces/Serialisable.h"
#include <filesystem>

// Contains the frame abstraction
// [Frame]	-> [Call] -> [Shader]	-> [Resource]
//									-> [Resource]
//			-> [Call] -> [Shader]	-> [Resource]
//			-> [Call] -> [Shader]	-> [Resource]

struct FVertexInvocation
{
	uint32_t Stride;
	uint32_t Offset;
};

class CCall
{
	public:
		uint32_t m_uFrameNumber;

		int32_t m_iIndexBuffer;
		std::vector<int32_t> m_viVertexBuffers;
		std::vector<FVertexInvocation> m_vstVertexInvocationData;
		uint32_t m_eTopology;

		// Vertex Shader
		int32_t m_iVertexShader;
		FShaderResources m_stVertexResources;

		// Hull Shader
		int32_t m_iHullShader;
		FShaderResources m_stHullResources;

		// Domain Shader
		int32_t m_iDomainShader;
		FShaderResources m_stDomainResources;

		// Geometry Shader
		int32_t m_iGeometryShader;
		FShaderResources m_stGeometryResources;

		// Pixel Shader
		int32_t m_iPixelShader;
		FShaderResources m_stPixelResources;

		// Computer Shader
		int32_t m_iComputeShader;
		FShaderResources m_stComputeResources;

		// IA
		int32_t m_iInputLayout;

		uint32_t m_uIndexCount;
		uint32_t m_uStartIndexLocation;
		int32_t  m_iBaseVertexLocation;
		uint32_t m_uDrawCallType;
		uint32_t m_uPrimitiveType;

		void Helper_AddBufferAtVectorLocation(std::vector<int32_t>& vec, int32_t iBufferIndex, uint32_t uSlotIndex);

	//
	public:
		explicit CCall(uint32_t frameNumber);
		CCall(const CCall& copy);
		~CCall();

		//virtual void SerialiseSRV(std::filesystem::path writePath, D3DObjectManager* pGLOM, CResourceBacking* srvPtr, uint32_t uSRVIndex, enum class EShaderTypes eShaderType);
		virtual void Serialise(std::filesystem::path writePath, class D3DObjectManager* pGLOM);

		void FinaliseResource(class D3DObjectManager* pGLOM, FShaderResources* pSrv);
		void Finalise(class D3DObjectManager* pGLOM);
		void SetInfo(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation, uint32_t uDrawCallType, uint32_t uPrimitiveType = -1);


		///// ///// ////////// ///// /////
		// Mimic DX Functions
		//

		void SetTopology(uint32_t eTopology);
		void SetVertexMeta(uint32_t SlotNumber, uint32_t Stride, uint32_t Offset);
		void SetLayout(int32_t iLayout);

		/**
		 *
		 */
		void SetVertexShader(int32_t pShader);

		/**
		 *
		 */
		void SetHullShader(int32_t pShader);

		/**
		 * 
		 */
		void SetDomainShader(int32_t pShader);

		/**
		 * 
		 */
		void SetGeometryShader(int32_t pShader);

		/**
		 * 
		 */
		void SetPixelShader(int32_t pShader);

		/**
		 *
		 */
		void SetComputeShader(int32_t pShader);

		/**
		 *
		 */
		void SetIndexBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex);
		/**
		 *
		 */
		void AddVertexBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex);



		/**
		 * 
		 */
		void AddVertexConstantBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex);
		/**
		 * 
		 */
		void AddVertexSamplers(int32_t iBufferIndex,  uint32_t uSlotIndex);
		/**
		 * 
		 */
		void AddVertexShaderResources(int32_t iBufferIndex,  uint32_t uSlotIndex);


		/**
		 * 
		 */
		void AddHullConstantBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex);
		/**
		 * 
		 */
		void AddHullSamplers(int32_t iBufferIndex,  uint32_t uSlotIndex);
		/**
		 * 
		 */
		void AddHullShaderResources(int32_t iBufferIndex,  uint32_t uSlotIndex);


		/**
		 * 
		 */
		void AddDomainConstantBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex);
		/**
		 * 
		 */
		void AddDomainSamplers(int32_t iBufferIndex,  uint32_t uSlotIndex);
		/**
		 * 
		 */
		void AddDomainShaderResources(int32_t iBufferIndex,  uint32_t uSlotIndex);


		/**
		 * 
		 */
		void AddGeometryConstantBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex);
		/**
		 * 
		 */
		void AddGeometrySamplers(int32_t iBufferIndex,  uint32_t uSlotIndex);
		/**
		 * 
		 */
		void AddGeometryShaderResources(int32_t iBufferIndex,  uint32_t uSlotIndex);


		/**
		 * 
		 */
		void AddPixelConstantBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex);
		/**
		 * 
		 */
		void AddPixelSamplers(int32_t iBufferIndex,  uint32_t uSlotIndex);
		/**
		 * 
		 */
		void AddPixelShaderResources(int32_t iBufferIndex,  uint32_t uSlotIndex);

		/**
		 *
		 */
		void AddComputeConstantBuffer(int32_t iBufferIndex,  uint32_t uSlotIndex);

		void AddComputeShaderResources(int32_t iBufferIndex,  uint32_t uSlotIndex);

};