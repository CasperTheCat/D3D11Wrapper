#include "stdafx.h"
#include "utils.h"
typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
bool IsWow64()
{
	BOOL Result = FALSE;

	LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(), &Result))
		{
			//g_Globals.ErrorFile() << "fnIsWow64Process failed\n";
		}
	}
	return (Result != FALSE);
}