#include "LIB_assert.h"
#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include <windows.h>
#include <detours.h>

#include "CRaventor.h"

/* -------------------------------------------------------------------- */
/** \name Original Functions
 * \{ */

fnInitServerInfo InitServerInfo = NULL;

/** \} */

/* -------------------------------------------------------------------- */
/** \name Overriden Functions
 * \{ */

void __stdcall mInitServerInfo(void) {
	InitServerInfo();
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Hooking
 * \{ */

/** We keep these casts so that we ensure that the type of the functions are consistent with the header. */
fnInitServerInfo m_InitServerInfo = mInitServerInfo;

void CRaventor_Hook() {
	InitServerInfo = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 81 ec e8 00 00 00 a1", 0x0, 0x0);

	HOOK_assert(InitServerInfo);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID *)&InitServerInfo, m_InitServerInfo);
	DetourTransactionCommit();
}

void CRaventor_Restore() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID *)&InitServerInfo, m_InitServerInfo);
	DetourTransactionCommit();
}

/** \} */
