#pragma once
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_2.h>
#include <d3d11_3.h>
#include <d3d11_4.h>
#include <d3d11on12.h>
#include <fstream>


class D3D11Wrapper
{
protected:
	HMODULE hD3D;
	ID3D11Device *m_device;
	IDXGISwapChain* m_swapchain;
	bool bIsDllValid;

public:
	std::ofstream Event;

public:
	D3D11Wrapper(HMODULE _hD3D);
	D3D11Wrapper();
	~D3D11Wrapper();
	
	/// Public functions
	bool LoadDLL();

	// Getters
	HMODULE getDLL();

	// Setters
	void setDevice(ID3D11Device *dev);
	void setSwapChain(IDXGISwapChain* swapchain);
};
