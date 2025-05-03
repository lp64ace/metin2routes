#include "LIB_assert.h"
#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include <windows.h>
#include <detours.h>

#include "CPythonNetworkStream.h"

/* -------------------------------------------------------------------- */
/** \name Original Functions
 * \{ */

fnCPythonNetworkStream_Constructor CPythonNetworkStream_Constructor = NULL;

/** \} */

/* -------------------------------------------------------------------- */
/** \name Overriden Functions
 * \{ */

CPythonNetworkStream *__fastcall mCPythonNetworkStream_Constructor(CPythonNetworkStream *me) {
	return CPythonNetworkStream_Constructor(me);
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Hooking
 * \{ */

/** We keep these casts so that we ensure that the type of the functions are consistent with the header. */
fnCPythonNetworkStream_Constructor m_CPythonNetworkStream_Constructor = mCPythonNetworkStream_Constructor;

void CPythonNetworkStream_Hook() {
	CPythonNetworkStream_Constructor = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 6a ff 68 87 c3", 0x0, 0x0);

	HOOK_assert(CPythonNetworkStream_Constructor);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID *)&CPythonNetworkStream_Constructor, m_CPythonNetworkStream_Constructor);
	DetourTransactionCommit();
}

void CPythonNetworkStream_Restore() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID *)&CPythonNetworkStream_Constructor, m_CPythonNetworkStream_Constructor);
	DetourTransactionCommit();
}

/** \} */
