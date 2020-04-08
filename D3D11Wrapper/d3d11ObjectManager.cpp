#include "stdafx.h"
#include "d3d11ObjectManager.h"
#include "utils.h"
#include <iostream>
#include "Globals.h"


D3DObjectManager::D3DObjectManager(HMODULE _hD3D)
	: hD3D(_hD3D), bIsDllValid(true)
{
	//Event = std::ofstream("d3d.txt");
}

D3DObjectManager::D3DObjectManager()
	: hD3D(nullptr), bIsDllValid(false)
{
#ifndef NDEBUG
	Event.open("D3D11.log");
	DEBUG_LOGLINE(Event, LOG("Initialising"));

	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	std::cout << "DLL initialised" << std::endl;
#endif
}

D3DObjectManager::~D3DObjectManager()
{
	Event.close();
}

bool D3DObjectManager::LoadDLL()
{
	// Initialise wrapper
	DEBUG_LOGLINE(Event, LOG("Loading DLL"));

	HMODULE hD3D = nullptr;
	if (IsWow64())
	{
		Event << LOG("Running on SysWOW64") << std::endl;
		hD3D = LoadLibrary(L"C:\\Windows\\SysWOW64\\d3d11.dll");
	}
	else
	{
		hD3D = LoadLibrary(L"C:\\Windows\\System32\\d3d11.dll");
	}

	if (hD3D == NULL)
	{
		DEBUG_LOGLINE(Event, LOGERR("Unable to load DLL"));
		return false;
	}

	this->hD3D = hD3D;
	this->bIsDllValid = true;
	DEBUG_LOGLINE(Event, LOG("Loaded DLL"));
	return true;
}

HMODULE D3DObjectManager::getDLL()
{
	if (!bIsDllValid) this->LoadDLL();
	return hD3D;
}

//void D3DObjectManager::setDevice(ID3D11Device* dev)
//{
//	m_device = dev;
//	//Event << "Device is " << ((m_device != nullptr) ? "VALID" : "INVALID") << std::endl;
//}
//
//void D3DObjectManager::setSwapChain(IDXGISwapChain* swapchain)
//{
//	m_swapchain = swapchain;
//}
