#pragma once
#include <vector>
#include <memory>
#include "Shader.h"
#include "ShaderResources.h"
#include "Interfaces/Serialisable.h"

// Contains the frame abstraction
// [Frame]	-> [Call] -> [Shader]	-> [Resource]
//									-> [Resource]
//			-> [Call] -> [Shader]	-> [Resource]
//			-> [Call] -> [Shader]	-> [Resource]

class CCall : public Serialisable
{
	private:
		uint32_t m_uFrameNumber;

		// Vertex Shader
		std::shared_ptr<CShader> m_pVertexShader;
		FShaderResources m_stVertexResources;

		// Hull Shader
		std::shared_ptr<CShader> m_pHullShader;
		FShaderResources m_stHullResources;

		// Domain Shader
		std::shared_ptr<CShader> m_pDomainShader;
		FShaderResources m_stDomainResources;

		// Geometry Shader
		std::shared_ptr<CShader> m_pGeometryShader;
		FShaderResources m_stGeometryResources;

		// Pixel Shader
		std::shared_ptr<CShader> m_pPixelShader;
		FShaderResources m_stPixelResources;

	//
	public:
		explicit CCall(uint32_t frameNumber);
		~CCall();

		///// ///// ////////// ///// /////
		// Mimic DX Functions
		//

		/**
		 *
		 */
		void SetVertexShader(std::shared_ptr<CShader> pShader);

		/**
		 *
		 */
		void SetHullShader(std::shared_ptr<CShader> pShader);

		/**
		 * 
		 */
		void SetDomainShader(std::shared_ptr<CShader> pShader);

		/**
		 * 
		 */
		void SetGeometryShader(std::shared_ptr<CShader> pShader);

		/**
		 * 
		 */
		void SetPixelShader(std::shared_ptr<CShader> pShader);




		/**
		 * 
		 */
		void AddVertexConstantBuffer(std::shared_ptr<std::vector<uint8_t>> pvBuffer);
		/**
		 * 
		 */
		void AddVertexSamplers(std::shared_ptr<std::vector<uint8_t>> pvBuffer);
		/**
		 * 
		 */
		void AddVertexShaderResources(std::shared_ptr<std::vector<uint8_t>> pvBuffer);


		/**
		 * 
		 */
		void AddHullConstantBuffer(std::shared_ptr<std::vector<uint8_t>> pvBuffer);
		/**
		 * 
		 */
		void AddHullSamplers(std::shared_ptr<std::vector<uint8_t>> pvBuffer);
		/**
		 * 
		 */
		void AddHullShaderResources(std::shared_ptr<std::vector<uint8_t>> pvBuffer);


		/**
		 * 
		 */
		void AddDomainConstantBuffer(std::shared_ptr<std::vector<uint8_t>> pvBuffer);
		/**
		 * 
		 */
		void AddDomainSamplers(std::shared_ptr<std::vector<uint8_t>> pvBuffer);
		/**
		 * 
		 */
		void AddDomainShaderResources(std::shared_ptr<std::vector<uint8_t>> pvBuffer);


		/**
		 * 
		 */
		void AddGeometryConstantBuffer(std::shared_ptr<std::vector<uint8_t>> pvBuffer);
		/**
		 * 
		 */
		void AddGeometrySamplers(std::shared_ptr<std::vector<uint8_t>> pvBuffer);
		/**
		 * 
		 */
		void AddGeometryShaderResources(std::shared_ptr<std::vector<uint8_t>> pvBuffer);


		/**
		 * 
		 */
		void AddPixelConstantBuffer(std::shared_ptr<std::vector<uint8_t>> pvBuffer);
		/**
		 * 
		 */
		void AddPixelSamplers(std::shared_ptr<std::vector<uint8_t>> pvBuffer);
		/**
		 * 
		 */
		void AddPixelShaderResources(std::shared_ptr<std::vector<uint8_t>> pvBuffer);

};