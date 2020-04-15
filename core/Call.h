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

class CCall
{
	public:
		uint32_t m_uFrameNumber;

		int32_t m_iIndexBuffer;
		std::vector<int32_t> m_viVertexBuffers;
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

		uint32_t m_uIndexCount;
		uint32_t m_uStartIndexLocation;
		int32_t  m_iBaseVertexLocation;

	//
	public:
		explicit CCall(uint32_t frameNumber);
		~CCall();

		//virtual void SerialiseSRV(std::filesystem::path writePath, D3DObjectManager* pGLOM, CResourceBacking* srvPtr, uint32_t uSRVIndex, enum class EShaderTypes eShaderType);
		virtual void Serialise(std::filesystem::path writePath, class D3DObjectManager* pGLOM);

		void FinaliseResource(class D3DObjectManager* pGLOM, FShaderResources* pSrv);
		void Finalise(class D3DObjectManager* pGLOM);
		void SetInfo(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);

		///// ///// ////////// ///// /////
		// Mimic DX Functions
		//

		void SetTopology(uint32_t eTopology);

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
		void SetIndexBuffer(int32_t iBufferIndex);
		/**
		 *
		 */
		void AddVertexBuffer(int32_t iBufferIndex);



		/**
		 * 
		 */
		void AddVertexConstantBuffer(int32_t iBufferIndex);
		/**
		 * 
		 */
		void AddVertexSamplers(int32_t iBufferIndex);
		/**
		 * 
		 */
		void AddVertexShaderResources(int32_t iBufferIndex);


		/**
		 * 
		 */
		void AddHullConstantBuffer(int32_t iBufferIndex);
		/**
		 * 
		 */
		void AddHullSamplers(int32_t iBufferIndex);
		/**
		 * 
		 */
		void AddHullShaderResources(int32_t iBufferIndex);


		/**
		 * 
		 */
		void AddDomainConstantBuffer(int32_t iBufferIndex);
		/**
		 * 
		 */
		void AddDomainSamplers(int32_t iBufferIndex);
		/**
		 * 
		 */
		void AddDomainShaderResources(int32_t iBufferIndex);


		/**
		 * 
		 */
		void AddGeometryConstantBuffer(int32_t iBufferIndex);
		/**
		 * 
		 */
		void AddGeometrySamplers(int32_t iBufferIndex);
		/**
		 * 
		 */
		void AddGeometryShaderResources(int32_t iBufferIndex);


		/**
		 * 
		 */
		void AddPixelConstantBuffer(int32_t iBufferIndex);
		/**
		 * 
		 */
		void AddPixelSamplers(int32_t iBufferIndex);
		/**
		 * 
		 */
		void AddPixelShaderResources(int32_t iBufferIndex);

		/**
		 *
		 */
		void AddComputeConstantBuffer(int32_t iBufferIndex);

		void AddComputeShaderResources(int32_t iBufferIndex);

};