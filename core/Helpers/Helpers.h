#pragma once

#include <vector>
#include <memory>

template<typename T>
using vector = std::vector<T>;

template<typename T>
using shared_ptr = std::shared_ptr<T>;

template<typename T>
using unique_ptr = std::unique_ptr<T>;

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

enum class ECallsTypes : uint8_t
{
	Draw,
	DrawInstanced,
	DrawIndexed,
	DrawIndexedInstanced,
	DrawIndexedInstancedIndirect,
	DrawInstancedIndirect,
	DrawAuto,

	// D3D9
	DrawPrimitive,
	DrawIndexedPrimitive,
	DrawPrimitiveUP,
	DrawIndexedPrimitiveUP,


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