#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include "intern/CRaventor.h"
#include "intern/CPythonApplication.h"
#include "intern/CPythonNetworkStream.h"

#include <stdio.h>
#include <windows.h>

HOOK_EXPORT BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID unused) {
	switch (reason) {
		case DLL_PROCESS_ATTACH: {
			DisableThreadLibraryCalls(hModule);

			if (AttachConsole(ATTACH_PARENT_PROCESS)) {
				(void)freopen("CONOUT$", "w", stdout);
				(void)freopen("CONOUT$", "w", stderr);
			}

			CRaventor_Hook();
			CPythonApplication_Hook();
			CPythonNetworkStream_Hook();
		} break;
		case DLL_PROCESS_DETACH: {
			CRaventor_Restore();
			CPythonApplication_Restore();
			CPythonNetworkStream_Restore();
		} break;
	}
	return TRUE;
}
