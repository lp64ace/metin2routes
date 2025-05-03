#include "MEM_guardedalloc.h"

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
fnCPythonNetworkStream_SetLoginPhase CPythonNetworkStream_SetLoginPhase = NULL;
fnCPythonNetworkStream_SendLoginPacketNew CPythonNetworkStream_SendLoginPacketNew = NULL;
fnCPythonNetworkStream_SendAttackPacket CPythonNetworkStream_SendAttackPacket = NULL;
fnCPythonNetworkStream_SendItemDropPacketNew CPythonNetworkStream_SendItemDropPacketNew = NULL;
fnCPythonNetworkStream_SendGiveItemPacket CPythonNetworkStream_SendGiveItemPacket = NULL;

/** \} */

/* -------------------------------------------------------------------- */
/** \name Overriden Functions
 * \{ */

CPythonNetworkStream *__fastcall mCPythonNetworkStream_Constructor(CPythonNetworkStream *me) {
	if ((me = CPythonNetworkStream_Constructor(me))) {
	}
	return me;
}

void __fastcall mCPythonNetworkStream_SetLoginPhase(CPythonNetworkStream *me, void *EDX) {
	CPythonNetworkStream_SetLoginPhase(me, EDX);
}

/** NOTE: The second parameter <c_szPassword> is ommited because it is not used! */
bool __fastcall mCPythonNetworkStream_SendLoginPacketNew(CPythonNetworkStream *me, void *EDX, const char *c_szName, const char *c_szPassword) {
	return CPythonNetworkStream_SendLoginPacketNew(me, EDX, c_szName, c_szPassword);
}

bool __fastcall mCPythonNetworkStream_SendAttackPacket(CPythonNetworkStream *me, void *EDX, UINT uMotAttack, UINT dwVIDVictim) {
	return CPythonNetworkStream_SendAttackPacket(me, EDX, uMotAttack, dwVIDVictim);
}
int __fastcall mCPythonNetworkStream_SendItemDropPacketNew(void *ECX, void *EDX, uint16_t ItemPos, uint32_t param_2, uint8_t Count, uint32_t param_4) {
	return CPythonNetworkStream_SendItemDropPacketNew(ECX, EDX, ItemPos, param_2, Count, param_4);
}
bool __fastcall mCPythonNetworkStream_SendGiveItemPacket(void *ECX, void *EDX, unsigned long dwTargetVID, uint16_t ItemPos, int iItemCount) {
	return CPythonNetworkStream_SendGiveItemPacket(ECX, EDX, dwTargetVID, ItemPos, iItemCount);
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Hooking
 * \{ */

/** We keep these casts so that we ensure that the type of the functions are consistent with the header. */
fnCPythonNetworkStream_Constructor m_CPythonNetworkStream_Constructor = mCPythonNetworkStream_Constructor;
fnCPythonNetworkStream_SetLoginPhase m_CPythonNetworkStream_SetLoginPhase = mCPythonNetworkStream_SetLoginPhase;
fnCPythonNetworkStream_SendLoginPacketNew m_CPythonNetworkStream_SendLoginPacketNew = mCPythonNetworkStream_SendLoginPacketNew;
fnCPythonNetworkStream_SendAttackPacket m_CPythonNetworkStream_SendAttackPacket = mCPythonNetworkStream_SendAttackPacket;
fnCPythonNetworkStream_SendItemDropPacketNew m_CPythonNetworkStream_SendItemDropPacketNew = mCPythonNetworkStream_SendItemDropPacketNew;
fnCPythonNetworkStream_SendItemDropPacketNew m_CPythonNetworkStream_SendGiveItemPacket = mCPythonNetworkStream_SendGiveItemPacket;

void CPythonNetworkStream_Hook() {
	CPythonNetworkStream_Constructor = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 6a ff 68 87 c3", 0x0, 0x0);
	CPythonNetworkStream_SetLoginPhase = LIB_pattern_find(GetModuleHandle(NULL), "56 57 8b f1 ?? ?? ?? ?? ?? 8d be 18 01 00 00 57", 0x0, 0x0);
	CPythonNetworkStream_SendLoginPacketNew = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 38 a1 ?? ?? ?? ?? 33 c5 89 45 fc 56 8b f1 c6", 0x0, 0x0);
	CPythonNetworkStream_SendAttackPacket = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 08 56 8b f1 e8 d2 3c 00 00 84 c0 75 09 b0 01 5e 8b e5 5d c2 08 00", 0x0, 0x0);
	CPythonNetworkStream_SendItemDropPacketNew = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 10 56 8b f1 e8 c2 ed ff ff", 0x0, 0x0);
	CPythonNetworkStream_SendGiveItemPacket = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 0c 8b 45 08 89 45 f5 66 8b", 0x0, 0x0);

	HOOK_assert(CPythonNetworkStream_Constructor);
	HOOK_assert(CPythonNetworkStream_SetLoginPhase);
	HOOK_assert(CPythonNetworkStream_SendLoginPacketNew);
	HOOK_assert(CPythonNetworkStream_SendAttackPacket);
	HOOK_assert(CPythonNetworkStream_SendItemDropPacketNew);
	HOOK_assert(CPythonNetworkStream_SendGiveItemPacket);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID *)&CPythonNetworkStream_Constructor, m_CPythonNetworkStream_Constructor);
	DetourAttach((PVOID *)&CPythonNetworkStream_SetLoginPhase, m_CPythonNetworkStream_SetLoginPhase);
	DetourAttach((PVOID *)&CPythonNetworkStream_SendLoginPacketNew, m_CPythonNetworkStream_SendLoginPacketNew);
	DetourAttach((PVOID *)&CPythonNetworkStream_SendAttackPacket, m_CPythonNetworkStream_SendAttackPacket);
	DetourAttach((PVOID *)&CPythonNetworkStream_SendItemDropPacketNew, m_CPythonNetworkStream_SendItemDropPacketNew);
	DetourAttach((PVOID *)&CPythonNetworkStream_SendGiveItemPacket, m_CPythonNetworkStream_SendGiveItemPacket);
	DetourTransactionCommit();
}

void CPythonNetworkStream_Restore() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID *)&CPythonNetworkStream_Constructor, m_CPythonNetworkStream_Constructor);
	DetourDetach((PVOID *)&CPythonNetworkStream_SetLoginPhase, m_CPythonNetworkStream_SetLoginPhase);
	DetourDetach((PVOID *)&CPythonNetworkStream_SendLoginPacketNew, m_CPythonNetworkStream_SendLoginPacketNew);
	DetourDetach((PVOID *)&CPythonNetworkStream_SendAttackPacket, m_CPythonNetworkStream_SendAttackPacket);
	DetourDetach((PVOID *)&CPythonNetworkStream_SendItemDropPacketNew, m_CPythonNetworkStream_SendItemDropPacketNew);
	DetourDetach((PVOID *)&CPythonNetworkStream_SendGiveItemPacket, m_CPythonNetworkStream_SendGiveItemPacket);
	DetourTransactionCommit();
}

/** \} */
