#include "MEM_guardedalloc.h"

#include "LIB_assert.h"
#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include <windows.h>
#include <detours.h>

#include "CPythonMinimap.h"

/* -------------------------------------------------------------------- */
/** \name Original Functions
 * \{ */

fnCPythonMiniMap_RegisterAtlasMark CPythonMiniMap_RegisterAtlasMark = NULL;

/** \} */

/* -------------------------------------------------------------------- */
/** \name Overriden Functions
 * \{ */

void __fastcall mCPythonMiniMap_RegisterAtlasMark(CPythonMinimap *me, void *EDX, BYTE bType, const char *c_szName, long lx, long ly) {
	return CPythonMiniMap_RegisterAtlasMark(me, EDX, bType, c_szName, lx, ly);
}

/** \} */
 
/* -------------------------------------------------------------------- */
/** \name Hooking
 * \{ */

/** We keep these casts so that we ensure that the type of the functions are consistent with the header. */
fnCPythonMiniMap_RegisterAtlasMark m_CPythonMiniMap_RegisterAtlasMark = mCPythonMiniMap_RegisterAtlasMark;

void CPythonMinimap_Hook() {
	CPythonMiniMap_RegisterAtlasMark = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 6a ff 68 ?? ?? ?? ?? 64 a1 ?? ?? ?? ?? 50 83 ec 44 a1 ?? ?? ?? ?? 33 c5 89 45 f0 56 57 50 8d 45 f4 64 a3 ?? ?? ?? ?? 8b f9 8b 55 0c", 0x0, 0x0);

	HOOK_assert(CPythonMiniMap_RegisterAtlasMark);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID *)&CPythonMiniMap_RegisterAtlasMark, m_CPythonMiniMap_RegisterAtlasMark);
	DetourTransactionCommit();
}

void CPythonMinimap_Restore() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID *)&CPythonMiniMap_RegisterAtlasMark, m_CPythonMiniMap_RegisterAtlasMark);
	DetourTransactionCommit();
}

/** \} */
