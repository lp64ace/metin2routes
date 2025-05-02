#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include <stdio.h>
#include <windows.h>
#include <psapi.h>
#include <detours.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID unused) {
	switch (reason) {
		case DLL_PROCESS_ATTACH: {
			DisableThreadLibraryCalls(hModule);

			if (AttachConsole(ATTACH_PARENT_PROCESS)) {
				(void)freopen("CONOUT$", "w", stdout);
				(void)freopen("CONOUT$", "w", stderr);
			}

			fprintf(stdout, "Hello from client.dll\n");
			fflush(stdout);
		} break;
		case DLL_PROCESS_DETACH: {
		} break;
	}
	return TRUE;
}
