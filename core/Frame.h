#pragma once
#include <vector>
#include "Call.h"
#include "Helpers/Helpers.h"

// Contains the frame abstraction
// [Frame]	-> [Call] -> [Shader]	-> [Resource]
//									-> [Resource]
//			-> [Call] -> [Shader]	-> [Resource]
//			-> [Call] -> [Shader]	-> [Resource]

class CFrame
{
	std::vector<CCall> m_calls;
};