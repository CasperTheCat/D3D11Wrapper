#pragma once
#include <dxgi.h>
#include <dxgi1_6.h>
#include <fstream>

class DXGIWrapper
{
protected:
	HMODULE hD3D;
	IDXGISwapChain* m_swapchain;
	bool bIsDllValid;

public:
	std::ofstream Event;

public:
	DXGIWrapper();
	~DXGIWrapper();

	/// Public functions
	bool LoadDLL();

	// Getters
	HMODULE getDLL();

	// Setters
	void setSwapChain(IDXGISwapChain* swapchain);
};