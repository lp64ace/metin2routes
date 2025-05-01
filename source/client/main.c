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
		} break;
		case DLL_PROCESS_DETACH: {
		} break;
	}
}
