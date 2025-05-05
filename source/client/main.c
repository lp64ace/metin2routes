#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include "intern/CRaventor.h"
#include "intern/CActorInstance.h"
#include "intern/CNetworkActorManager.h"
#include "intern/CPythonApplication.h"
#include "intern/CNetworkStream.h"
#include "intern/CPythonNetworkStream.h"
#include "intern/CAccountConnector.h"
#include "intern/CPythonMinimap.h"

#include <stdio.h>
#include <windows.h>

#include "KER_global.h"

HOOK_EXPORT BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID unused) {
	switch (reason) {
		case DLL_PROCESS_ATTACH: {
			DisableThreadLibraryCalls(hModule);

			if (AttachConsole(ATTACH_PARENT_PROCESS)) {
				(void)freopen("CONOUT$", "w", stdout);
				(void)freopen("CONOUT$", "w", stderr);
			}
			SetConsoleOutputCP(1253);

			KER_globals_init();

			CRaventor_Hook();
			CActorInstance_Hook();
			CNetworkActorManager_Hook();
			CPythonApplication_Hook();
			CNetworkStream_Hook();
			CPythonNetworkStream_Hook();
			CAccountConnector_Hook();
			CPythonMinimap_Hook();
		} break;
		case DLL_PROCESS_DETACH: {
			CRaventor_Restore();
			CActorInstance_Restore();
			CNetworkActorManager_Restore();
			CPythonApplication_Restore();
			CNetworkStream_Restore();
			CPythonNetworkStream_Restore();
			CAccountConnector_Restore();
			CPythonMinimap_Restore();

			KER_globals_exit();
		} break;
	}
	return TRUE;
}
