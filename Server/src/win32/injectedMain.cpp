#include <stdio.h>
#include <Windows.h>
#include "../app.h"
#include "../log.h"

bool first = true;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{	
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		if (first)
		{
			first = false;
			LOGD("DLL_PROCESS_ATTACH");
			startServerThread();
		}
		break;

	case DLL_PROCESS_DETACH:
		LOGD("DLL_PROCESS_DETACH");
		stopServerThread();
		break;

	case DLL_THREAD_ATTACH:

		break;
	case DLL_THREAD_DETACH:

		break;
	}
	
	return true;
}
