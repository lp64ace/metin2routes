#include "MEM_guardedalloc.h"

#include "LIB_assert.h"
#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include <windows.h>
#include <detours.h>

#include "CNetworkStream.h"

/* -------------------------------------------------------------------- */
/** \name Offset Resolve
 * \{ */

unsigned int *CNetworkStream_mSock(CNetworkStream *me) {
	return POINTER_OFFSET(me, 0x17);
}

int *CNetworkStream_mSendBufInputPos(CNetworkStream *me) {
	return POINTER_OFFSET(me, 0x34);
}
int *CNetworkStream_mSendBufOutputPos(CNetworkStream *me) {
	return POINTER_OFFSET(me, 0x38);
}
int *CNetworkStream_mRecvBufInputPos(CNetworkStream *me) {
	return POINTER_OFFSET(me, 0x24);
}
int *CNetworkStream_mRecvBufOutputPos(CNetworkStream *me) {
	return POINTER_OFFSET(me, 0x28);
}

char **CNetworkStream_mRecvBuf(CNetworkStream *me) {
	return POINTER_OFFSET(me, 0x1c);
}
char **CNetworkStream_mSendBuf(CNetworkStream *me) {
	return POINTER_OFFSET(me, 0x2c);
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Original Functions
 * \{ */

fnCNetworkStream_Process CNetworkStream_Process = NULL;
fnCNetworkStream_Peek CNetworkStream_Peek = NULL;
fnCNetworkStream_RecvInternalBuffer CNetworkStream_RecvInternalBuffer = NULL;
fnCNetworkStream_SendInternalBuffer CNetworkStream_SendInternalBuffer = NULL;
fnCNetworkStream_Connect CNetworkStream_Connect = NULL;

/** \} */

/* -------------------------------------------------------------------- */
/** \name Overriden Functions
 * \{ */

bool __fastcall mCNetworkStream_Process(CNetworkStream *me, void *EDX) {
	return CNetworkStream_Process(me, EDX);
}

bool __fastcall mCNetworkStream_Peek(CNetworkStream *me, void *EDX, int size, void *pDestBuf) {
	return CNetworkStream_Peek(me, EDX, size, pDestBuf);
}

bool __fastcall mCNetworkStream_RecvInternalBuffer(CNetworkStream *me, void *EDX) {
	return CNetworkStream_RecvInternalBuffer(me, EDX);
}
bool __fastcall mCNetworkStream_SendInternalBuffer(CNetworkStream *me, void *EDX) {
	return CNetworkStream_SendInternalBuffer(me, EDX);
}

bool __fastcall mCNetworkStream_Connect(CNetworkStream *me, void *EDX, const char *c_szAddr, int port, int limitSec) {
	if (CNetworkStream_Connect(me, EDX, c_szAddr, port, limitSec)) {
		LOG("CONNECTION TO %s:%d SUCCESS", c_szAddr, port);
		return true;
	}
	LOG("CONNECTION TO %s:%d FAILED", c_szAddr, port);
	return false;
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Hooking
 * \{ */

/** We keep these casts so that we ensure that the type of the functions are consistent with the header. */
fnCNetworkStream_Process m_CNetworkStream_Process = mCNetworkStream_Process;
fnCNetworkStream_Peek m_CNetworkStream_Peek = mCNetworkStream_Peek;
fnCNetworkStream_RecvInternalBuffer m_CNetworkStream_RecvInternalBuffer = mCNetworkStream_RecvInternalBuffer;
fnCNetworkStream_SendInternalBuffer m_CNetworkStream_SendInternalBuffer = mCNetworkStream_SendInternalBuffer;
fnCNetworkStream_Connect m_CNetworkStream_Connect = mCNetworkStream_Connect;

void CNetworkStream_Hook() {
	CNetworkStream_Process = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 81 ec 14 02 00 00 a1 ?? ?? ?? ?? 33 c5 89 45 fc 56", 0x0, 0x0);
	CNetworkStream_Peek = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 56 8b f1 e8 55 ff ff ff 8b 4d 08", 0x0, 0x0);
	CNetworkStream_RecvInternalBuffer = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 08 53 56 57 8b f9 8b 57 28 8d 77 24 85 d2", 0x0, 0x0);
	CNetworkStream_SendInternalBuffer = LIB_pattern_find(GetModuleHandle(NULL), "56 57 8b f1 e8 d7 fe ff ff 8b f8 85 ff 7e 4a 8b ce e8 ba", 0x0, 0x0);
	CNetworkStream_Connect = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 6a ff 68 ?? ?? ?? ?? 64 a1 ?? ?? ?? ?? 50 83 ec 14 a1 ?? ?? ?? ?? 33 c5 89 45 f0", 0x0, 0x0);

	HOOK_assert(CNetworkStream_Process);
	HOOK_assert(CNetworkStream_Peek);
	HOOK_assert(CNetworkStream_RecvInternalBuffer);
	HOOK_assert(CNetworkStream_SendInternalBuffer);
	HOOK_assert(CNetworkStream_Connect);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID *)&CNetworkStream_Process, m_CNetworkStream_Process);
	DetourAttach((PVOID *)&CNetworkStream_Peek, m_CNetworkStream_Peek);
	DetourAttach((PVOID *)&CNetworkStream_RecvInternalBuffer, m_CNetworkStream_RecvInternalBuffer);
	DetourAttach((PVOID *)&CNetworkStream_SendInternalBuffer, m_CNetworkStream_SendInternalBuffer);
	DetourAttach((PVOID *)&CNetworkStream_Connect, m_CNetworkStream_Connect);
	DetourTransactionCommit();
}

void CNetworkStream_Restore() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID *)&CNetworkStream_Process, m_CNetworkStream_Process);
	DetourDetach((PVOID *)&CNetworkStream_Peek, m_CNetworkStream_Peek);
	DetourDetach((PVOID *)&CNetworkStream_RecvInternalBuffer, m_CNetworkStream_RecvInternalBuffer);
	DetourDetach((PVOID *)&CNetworkStream_SendInternalBuffer, m_CNetworkStream_SendInternalBuffer);
	DetourDetach((PVOID *)&CNetworkStream_Connect, m_CNetworkStream_Connect);
	DetourTransactionCommit();
}

/** \} */
