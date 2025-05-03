#include "LIB_assert.h"
#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include <windows.h>
#include <detours.h>

#include "CPythonApplication.h"

/* -------------------------------------------------------------------- */
/** \name Original Functions
 * \{ */

fnCPythonApplication_Constructor CPythonApplication_Constructor = NULL;
fnCPythonApplication_UpdateGame CPythonApplication_UpdateGame = NULL;
fnCPythonApplication_RenderGame CPythonApplication_RenderGame = NULL;

/** \} */

/* -------------------------------------------------------------------- */
/** \name Overriden Functions
 * \{ */

CPythonApplication *__fastcall mCPythonApplication_Constructor(CPythonApplication *me) {
	if ((me = CPythonApplication_Constructor(me))) {
	}
	return me;
}

void __fastcall mCPythonApplication_UpdateGame(CPythonApplication *me) {
	CPythonApplication_UpdateGame(me);
}
void __fastcall mCPythonApplication_RenderGame(CPythonApplication *me) {
	CPythonApplication_RenderGame(me);
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Hooking
 * \{ */

/** We keep these casts so that we ensure that the type of the functions are consistent with the header. */
fnCPythonApplication_Constructor m_CPythonApplication_Constructor = mCPythonApplication_Constructor;
fnCPythonApplication_UpdateGame m_CPythonApplication_UpdateGame = mCPythonApplication_UpdateGame;
fnCPythonApplication_RenderGame m_CPythonApplication_RenderGame = mCPythonApplication_RenderGame;

void CPythonApplication_Hook() {
	CPythonApplication_Constructor = reinterpret_cast<fnCPythonApplication_Constructor>(LIB_pattern_find(GetModuleHandle(NULL), "53 8b dc 83 ec 08 83 e4 f0 83 c4 04 55 8b 6b 04 89 6c 24 04 8b ec 6a ff 68 ?? ?? ?? ?? 64 a1 ?? ?? ?? ?? 50 53 83 ec 38", 0x0, 0x0));
	CPythonApplication_UpdateGame = reinterpret_cast<fnCPythonApplication_UpdateGame>(LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 6a ff 68 ?? ?? ?? ?? 64 a1 ?? ?? ?? ?? 50 83 ec 4c a1 ?? ?? ?? ?? 33 c5 89 45 f0 53 56 57 50 8d 45 f4 64 a3 ?? ?? ?? ?? 8b f1 89 75 e0", 0x0, 0x0));
	CPythonApplication_RenderGame = reinterpret_cast<fnCPythonApplication_RenderGame>(LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 44 80 3d ?? ?? ?? ?? 00", 0x0, 0x0));

	HOOK_assert(CPythonApplication_Constructor);
	HOOK_assert(CPythonApplication_UpdateGame);
	HOOK_assert(CPythonApplication_RenderGame);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID *)&CPythonApplication_Constructor, m_CPythonApplication_Constructor);
	DetourAttach((PVOID *)&CPythonApplication_UpdateGame, m_CPythonApplication_UpdateGame);
	DetourAttach((PVOID *)&CPythonApplication_RenderGame, m_CPythonApplication_RenderGame);
	DetourTransactionCommit();
}

void CPythonApplication_Restore() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID *)&CPythonApplication_Constructor, m_CPythonApplication_Constructor);
	DetourDetach((PVOID *)&CPythonApplication_UpdateGame, m_CPythonApplication_UpdateGame);
	DetourDetach((PVOID *)&CPythonApplication_RenderGame, m_CPythonApplication_RenderGame);
	DetourTransactionCommit();
}

/** \} */
