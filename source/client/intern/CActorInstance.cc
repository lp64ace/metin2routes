#include "MEM_guardedalloc.h"

#include "LIB_assert.h"
#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include <windows.h>
#include <detours.h>

#include "CActorInstance.h"

/* -------------------------------------------------------------------- */
/** \name Offset Resolve
 * \{ */

unsigned int *CActorInstance_mEActorType(CActorInstance *me) {
	return NULL;
}
unsigned long *CActorInstance_mDwSelfVID(CActorInstance *me) {
	return NULL;
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Original Functions
 * \{ */

/** \} */

/* -------------------------------------------------------------------- */
/** \name Overriden Functions
 * \{ */

/** \} */

/* -------------------------------------------------------------------- */
/** \name Hooking
 * \{ */

/** We keep these casts so that we ensure that the type of the functions are consistent with the header. */

void CActorInstance_Hook() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourTransactionCommit();
}

void CActorInstance_Restore() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourTransactionCommit();
}

/** \} */
