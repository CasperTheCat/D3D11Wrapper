#include "stdafx.h"
#include "utils.h"
#include "dxgiWrapper.h"
#include "dxgiFactory.h"
#include "dxgiFactory1.h"
#include "dxgiFactory2.h"

DXGIWrapper *dxgw = new DXGIWrapper();

typedef HRESULT(WINAPI *DXGIFAC)(REFIID, _COM_Outptr_ void **);
typedef HRESULT(WINAPI *DXGIFAC2)(UINT, REFIID, _COM_Outptr_ void **);

enum class EFactoryType : uint8_t
{
	DXGIFactory,
	DXGIFactory1,
	DXGIFactory2,
	TOTAL_FACTORY_TYPES
};

// Helper Function reuse the code
HRESULT WINAPI CreateDXGIFactory_Generic(REFIID riid, _COM_Outptr_ void **ppFactory, EFactoryType factory)
{
	// I assume most calls are made to DXGI Factory Create here and not the other functions.
	dxgw->Event << LOG("Caught DXGI Factory Call") << 
		static_cast<uint32_t>(static_cast<std::underlying_type<EFactoryType>::type>(factory))
		<< std::endl;

	// Get the real function address
	DXGIFAC pCreateFactory = nullptr;
	switch(factory)
	{
	case EFactoryType::DXGIFactory:
		pCreateFactory = (DXGIFAC)GetProcAddress(dxgw->getDLL(), "CreateDXGIFactory");
		break;
	case EFactoryType::DXGIFactory1:
		pCreateFactory = (DXGIFAC)GetProcAddress(dxgw->getDLL(), "CreateDXGIFactory1");
		break;
	case EFactoryType::DXGIFactory2:
		pCreateFactory = (DXGIFAC)GetProcAddress(dxgw->getDLL(), "CreateDXGIFactory2");
		break;
	default:
		//dxgw->Event << LOGERR("Invalid Factory Type Requested") << std::endl;
		return NULL;
	}

	// Check Validity
	if (pCreateFactory == nullptr)
	{
		dxgw->Event << LOGERR("Unable to find CreateDXGIFactory in DLL") << std::endl;
		return NULL;
	}


	HRESULT hRes = 0;
	switch (factory)
	{
	case EFactoryType::DXGIFactory:
		dxgw->Event << LOG("Creating DXGI Factory: ");
		hRes = pCreateFactory(riid, ppFactory);
		break;
	case EFactoryType::DXGIFactory1:
		dxgw->Event << LOG("Creating DXGI Factory1: ");
		hRes = pCreateFactory(riid, ppFactory);
		break;
	case EFactoryType::DXGIFactory2:
		//dxgw->Event << LOG("Creating DXGI Factory1: ");
		hRes = pCreateFactory(riid, ppFactory);
		break;
	default:;
	}

	

	if (ppFactory != nullptr)
	{
		dxgw->Event << "Success" << std::endl << std::endl;

		// Wrap the factory
		IDXGIFactory * pTempDXGIFactory = nullptr;
		switch (factory)
		{
		case EFactoryType::DXGIFactory:
			dxgw->Event << LOG("Caught CF00") << std::endl;
			pTempDXGIFactory = new DXGICustomFactory(*ppFactory, dxgw);
			*ppFactory = pTempDXGIFactory;
			break;
		case EFactoryType::DXGIFactory1:
			dxgw->Event << LOG("Caught CF01") << std::endl;
			pTempDXGIFactory = new DXGICustomFactory1(*ppFactory, dxgw);
			*ppFactory = pTempDXGIFactory;
			break;
		case EFactoryType::DXGIFactory2:
			pTempDXGIFactory = new DXGICustomFactory1(*ppFactory, dxgw);
			*ppFactory = pTempDXGIFactory;
			break;
		default:;
		}
	}
	else
	{
		dxgw->Event << "Failure" << std::endl;
	}

	return hRes;
}


HRESULT WINAPI CreateDXGIFactory(REFIID riid, _COM_Outptr_ void **ppFactory)
{
	return CreateDXGIFactory_Generic(riid, ppFactory, EFactoryType::DXGIFactory);
}

HRESULT WINAPI CreateDXGIFactory1(REFIID riid, _COM_Outptr_  void **ppFactory)
{
	return CreateDXGIFactory_Generic(riid, ppFactory, EFactoryType::DXGIFactory1);
}

HRESULT WINAPI CreateDXGIFactory2(UINT Flags, REFIID riid, _COM_Outptr_  void **ppFactory)
{
	// I assume most calls are made to DXGI Factory Create here and not the other functions.
	dxgw->Event << LOG("Caught DXGI Factory2 Call") << std::endl;

	// Get the real function address
	DXGIFAC2 pCreateFactory = (DXGIFAC2)GetProcAddress(dxgw->getDLL(), "CreateDXGIFactory2");


	// Check Validity
	if (pCreateFactory == nullptr)
	{
		//dxgw->Event << LOGERR("Unable to find CreateDXGIFactory2 in DLL") << std::endl;
		return NULL;
	}


	//dxgw->Event << LOG("Creating DXGI Factory2: ");
	HRESULT hRes = pCreateFactory(Flags, riid, ppFactory);

	dxgw->Event << LOG("Caught DXGI 2 Call") << std::endl;



	if (ppFactory != nullptr)
	{
		dxgw->Event << "Success" << std::endl;

		// Wrap the factory
		IDXGIFactory *pTempDXGIFactory = new DXGICustomFactory2(*ppFactory, dxgw);
		*ppFactory = pTempDXGIFactory;
	}
	else
	{
		dxgw->Event << "Failure" << std::endl;
	}

	return hRes;
}