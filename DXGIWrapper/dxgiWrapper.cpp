#include "dxgiWrapper.h"
#include "stdafx.h"
#include "utils.h"

DXGIWrapper::DXGIWrapper(): hD3D(nullptr), m_swapchain(nullptr), bIsDllValid(false)
{
	Event = std::ofstream("DXGI.log");
	Event << this << std::endl;
}

DXGIWrapper::~DXGIWrapper()
{
}

bool DXGIWrapper::LoadDLL()
{
	// Initialise wrapper
	//Event << LOG("Loading DLL") << std::endl;

	HMODULE hD3D = nullptr;
	if (IsWow64())
	{
		//Event << LOG("Running on SysWOW64") << std::endl;
		hD3D = LoadLibrary(L"C:\\Windows\\SysWOW64\\dxgi.dll");
	}
	else
	{
		hD3D = LoadLibrary(L"C:\\Windows\\System32\\dxgi.dll");
	}

	if (hD3D == NULL)
	{
		//Event << LOGERR("Unable to load DLL") << std::endl;
		return false;
	}

	this->hD3D = hD3D;
	this->bIsDllValid = true;
	//Event << LOG("Loaded DLL") << std::endl;
	return true;
}

HMODULE DXGIWrapper::getDLL()
{
	std::lock_guard<std::mutex> lock(MutLoader);
	if (!bIsDllValid) this->LoadDLL();
	return hD3D;
}

void DXGIWrapper::setSwapChain(IDXGISwapChain* swapchain)
{
	m_swapchain = swapchain;
}
