#include "MEM_guardedalloc.h"

#include "LIB_assert.h"
#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include <windows.h>
#include <detours.h>

#include "CNetworkStream.h"
#include "CPythonApplication.h"
#include "CAccountConnector.h"

#include "KER_global.h"

/* -------------------------------------------------------------------- */
/** \name Offset Resolve
 * \{ */

unsigned int *CAccountConnector_mEState(CAccountConnector *me) {
	return POINTER_OFFSET(me, 0x80);
}
int *CAccountConnector_mIsWaitKey(CAccountConnector *me) {
	return POINTER_OFFSET(me, 0xd0);
}
const char *CAccountConnector_mStrId(CAccountConnector *me) {
	return POINTER_OFFSET(me, 0x84);
}
const char *CAccountConnector_mStrPassword(CAccountConnector *me) {
	return POINTER_OFFSET(me, 0x9c);
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Original Functions
 * \{ */

fnCAccountConnector_Constructor CAccountConnector_Constructor = NULL;
fnCAccountConnector_SetLoginInfo CAccountConnector_SetLoginInfo = NULL;
fnCAccountConnector_Process CAccountConnector_Process = NULL;
fnCAccountConnector_Connect CAccountConnector_Connect = NULL;
fnCAccountConnector___AuthState_RecvPhase CAccountConnector___AuthState_RecvPhase = NULL;
fnCAccountConnector___AuthState_RecvAuthSuccess CAccountConnector___AuthState_RecvAuthSuccess = NULL;

/** \} */

/* -------------------------------------------------------------------- */
/** \name Overriden Functions
 * \{ */

CAccountConnector *__fastcall mCAccountConnector_Constructor(CAccountConnector *me, void *EDX) {
	if ((me = CAccountConnector_Constructor(me, EDX))) {
	}
	return  me;
}

void __fastcall mCAccountConnector_SetLoginInfo(CAccountConnector *me, void *EDX, const char *c_szName, const char *c_szPwd) {
	return CAccountConnector_SetLoginInfo(me, EDX, c_szName, c_szPwd);
}

bool __fastcall mCAccountConnector_Process(CAccountConnector *me, void *EDX) {
	return CAccountConnector_Process(me, EDX);
}

bool __fastcall mCAccountConnector_Connect(CAccountConnector *me, void *EDX, const char *c_szAddr, int iPort, const char *c_szAccountAddr, int iAccountPort) {
	return CAccountConnector_Connect(me, EDX, c_szAddr, iPort, c_szAccountAddr, iAccountPort);
}

bool __fastcall mCAccountConnector___AuthState_RecvPhase(CAccountConnector *me, void *EDX) {
	return CAccountConnector___AuthState_RecvPhase(me, EDX);
}
bool __fastcall mCAccountConnector___AuthState_RecvAuthSuccess(CAccountConnector *me, void *EDX) {
	return CAccountConnector___AuthState_RecvAuthSuccess(me, EDX);
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Hooking
 * \{ */

/** We keep these casts so that we ensure that the type of the functions are consistent with the header. */
fnCAccountConnector_Constructor m_CAccountConnector_Constructor = mCAccountConnector_Constructor;
fnCAccountConnector_SetLoginInfo m_CAccountConnector_SetLoginInfo = mCAccountConnector_SetLoginInfo;
fnCAccountConnector_Process m_CAccountConnector_Process = mCAccountConnector_Process;
fnCAccountConnector_Connect m_CAccountConnector_Connect = mCAccountConnector_Connect;
fnCAccountConnector___AuthState_RecvPhase m_CAccountConnector___AuthState_RecvPhase = mCAccountConnector___AuthState_RecvPhase;
fnCAccountConnector___AuthState_RecvAuthSuccess m_CAccountConnector___AuthState_RecvAuthSuccess = mCAccountConnector___AuthState_RecvAuthSuccess;

void CAccountConnector_Hook() {
	CAccountConnector_Constructor = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 6a ff 68 ?? ?? ?? ?? 64 a1 ?? ?? ?? ?? 50 51 56 a1 ?? ?? ?? ?? 33 c5 50 8d 45 f4 64 a3 ?? ?? ?? ?? 8b f1 89 75 f0 e8 92 22 07 00", 0x0, 0x0);
	CAccountConnector_SetLoginInfo = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 56 8b 75 08 8b d6 57 8b f9 8d 4a 01 90 8a 02 42 84 c0 75 f9 2b d1 8d 8f 84", 0x0, 0x0);
	CAccountConnector_Process = LIB_pattern_find(GetModuleHandle(NULL), "56 8b f1 e8 88 23 07 00 8b ce", 0x0, 0x0);
	CAccountConnector_Connect = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 8b 55 08 8b c2 56 57 8b f1 8d 78 01 90 8a 08 40 84 c9 75 f9 2b c7 8d 8e b4", 0x0, 0x0);
	CAccountConnector___AuthState_RecvPhase = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 81 ec 58 01 00 00 a1 ?? ?? ?? ?? 33 c5 89 45 fc 57 8d 85 a8 fe ff ff", 0x0, 0x0);
	CAccountConnector___AuthState_RecvAuthSuccess = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 08 8d 45 f8 56 50 6a 06 8b f1 e8 3c 20 07 00", 0x0, 0x0);

	HOOK_assert(CAccountConnector_Constructor);
	HOOK_assert(CAccountConnector_SetLoginInfo);
	HOOK_assert(CAccountConnector_Process);
	HOOK_assert(CAccountConnector_Connect);
	HOOK_assert(CAccountConnector___AuthState_RecvPhase);
	HOOK_assert(CAccountConnector___AuthState_RecvAuthSuccess);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID *)&CAccountConnector_Constructor, m_CAccountConnector_Constructor);
	DetourAttach((PVOID *)&CAccountConnector_SetLoginInfo, m_CAccountConnector_SetLoginInfo);
	DetourAttach((PVOID *)&CAccountConnector_Process, m_CAccountConnector_Process);
	DetourAttach((PVOID *)&CAccountConnector_Connect, m_CAccountConnector_Connect);
	DetourAttach((PVOID *)&CAccountConnector___AuthState_RecvPhase, m_CAccountConnector___AuthState_RecvPhase);
	DetourAttach((PVOID *)&CAccountConnector___AuthState_RecvAuthSuccess, m_CAccountConnector___AuthState_RecvAuthSuccess);
	DetourTransactionCommit();
}

void CAccountConnector_Restore() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID *)&CAccountConnector_Constructor, m_CAccountConnector_Constructor);
	DetourDetach((PVOID *)&CAccountConnector_SetLoginInfo, m_CAccountConnector_SetLoginInfo);
	DetourDetach((PVOID *)&CAccountConnector_Process, m_CAccountConnector_Process);
	DetourDetach((PVOID *)&CAccountConnector_Connect, m_CAccountConnector_Connect);
	DetourDetach((PVOID *)&CAccountConnector___AuthState_RecvPhase, m_CAccountConnector___AuthState_RecvPhase);
	DetourDetach((PVOID *)&CAccountConnector___AuthState_RecvAuthSuccess, m_CAccountConnector___AuthState_RecvAuthSuccess);
	DetourTransactionCommit();
}

/** \} */
