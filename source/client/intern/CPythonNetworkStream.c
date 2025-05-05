#include "MEM_guardedalloc.h"

#include "LIB_assert.h"
#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include <windows.h>
#include <detours.h>

#include "CNetworkStream.h"
#include "CPythonNetworkStream.h"
#include "CString.h"

#include "Packet.h"

CPythonNetworkStream *nkNetStream = NULL;

/* -------------------------------------------------------------------- */
/** \name Offset Resolve
 * \{ */

const char *CPythonNetworkStream_mStrPhase(CPythonNetworkStream *me) {
	return POINTER_OFFSET(me, 0x118);
}
const char *CPythonNetworkStream_mStrID(CPythonNetworkStream *me) {
	return POINTER_OFFSET(me, 0xd0);
}
const char *CPythonNetworkStream_mStrPassword(CPythonNetworkStream *me) {
	return POINTER_OFFSET(me, 0x10c);
}

struct CNetworkActorManager **CPythonNetworkStream_mNetActorMgr(CPythonNetworkStream *me) {
	return POINTER_OFFSET(me, 0x39c);
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Original Functions
 * \{ */

fnCPythonNetworkStream_Constructor CPythonNetworkStream_Constructor = NULL;
fnCPythonNetworkStream_SetOfflinePhase CPythonNetworkStream_SetOfflinePhase = NULL;
fnCPythonNetworkStream_SetHandshakePhase CPythonNetworkStream_SetHandshakePhase = NULL;
fnCPythonNetworkStream_SetLoginPhase CPythonNetworkStream_SetLoginPhase = NULL;
fnCPythonNetworkStream_SendLoginPacketNew CPythonNetworkStream_SendLoginPacketNew = NULL;
fnCPythonNetworkStream_SendAttackPacket CPythonNetworkStream_SendAttackPacket = NULL;
fnCPythonNetworkStream_SendItemDropPacketNew CPythonNetworkStream_SendItemDropPacketNew = NULL;
fnCPythonNetworkStream_SendGiveItemPacket CPythonNetworkStream_SendGiveItemPacket = NULL;

fnCPythonNetworkStream_RecvTargetCreatePacket CPythonNetworkStream_RecvTargetCreatePacket = NULL;
fnCPythonNetworkStream_RecvTargetCreatePacketNew CPythonNetworkStream_RecvTargetCreatePacketNew = NULL;
fnCPythonNetworkStream_RecvNPCList CPythonNetworkStream_RecvNPCList = NULL;

/** \} */

/* -------------------------------------------------------------------- */
/** \name Overriden Functions
 * \{ */

CPythonNetworkStream *__fastcall mCPythonNetworkStream_Constructor(CPythonNetworkStream *me, void *EDX) {
	if ((me = CPythonNetworkStream_Constructor(me, EDX))) {
		nkNetStream = me;
	}
	return me;
}

void __fastcall mCPythonNetworkStream_SetOfflinePhase(CPythonNetworkStream *me, void *EDX) {
	CPythonNetworkStream_SetOfflinePhase(me, EDX);
}
void __fastcall mCPythonNetworkStream_SetHandshakePhase(CPythonNetworkStream *me, void *EDX) {
	CPythonNetworkStream_SetHandshakePhase(me, EDX);
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
int __fastcall mCPythonNetworkStream_SendItemDropPacketNew(CPythonNetworkStream *me, void *EDX, uint16_t ItemPos, uint32_t param_2, uint8_t Count, uint32_t param_4) {
	return CPythonNetworkStream_SendItemDropPacketNew(me, EDX, ItemPos, param_2, Count, param_4);
}
bool __fastcall mCPythonNetworkStream_SendGiveItemPacket(CPythonNetworkStream *me, void *EDX, unsigned long dwTargetVID, uint16_t ItemPos, int iItemCount) {
	return CPythonNetworkStream_SendGiveItemPacket(me, EDX, dwTargetVID, ItemPos, iItemCount);
}

bool __fastcall mCPythonNetworkStream_RecvTargetCreatePacket(CPythonNetworkStream *me, void *EDX) {
	return CPythonNetworkStream_RecvTargetCreatePacket(me, EDX);
}
/** This receives 'Teacher of Strenght' etc... */
bool __fastcall mCPythonNetworkStream_RecvTargetCreatePacketNew(CPythonNetworkStream *me, void *EDX) {
	return CPythonNetworkStream_RecvTargetCreatePacketNew(me, EDX);
}

bool __fastcall mCPythonNetworkStream_RecvNPCList(CPythonNetworkStream *me, void *EDX) {
	return CPythonNetworkStream_RecvNPCList(me, EDX);
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Hooking
 * \{ */

/** We keep these casts so that we ensure that the type of the functions are consistent with the header. */
fnCPythonNetworkStream_Constructor m_CPythonNetworkStream_Constructor = mCPythonNetworkStream_Constructor;
fnCPythonNetworkStream_SetOfflinePhase m_CPythonNetworkStream_SetOfflinePhase = mCPythonNetworkStream_SetOfflinePhase;
fnCPythonNetworkStream_SetHandshakePhase m_CPythonNetworkStream_SetHandshakePhase = mCPythonNetworkStream_SetHandshakePhase;
fnCPythonNetworkStream_SetLoginPhase m_CPythonNetworkStream_SetLoginPhase = mCPythonNetworkStream_SetLoginPhase;
fnCPythonNetworkStream_SendLoginPacketNew m_CPythonNetworkStream_SendLoginPacketNew = mCPythonNetworkStream_SendLoginPacketNew;
fnCPythonNetworkStream_SendAttackPacket m_CPythonNetworkStream_SendAttackPacket = mCPythonNetworkStream_SendAttackPacket;
fnCPythonNetworkStream_SendItemDropPacketNew m_CPythonNetworkStream_SendItemDropPacketNew = mCPythonNetworkStream_SendItemDropPacketNew;
fnCPythonNetworkStream_SendItemDropPacketNew m_CPythonNetworkStream_SendGiveItemPacket = mCPythonNetworkStream_SendGiveItemPacket;

fnCPythonNetworkStream_RecvTargetCreatePacket m_CPythonNetworkStream_RecvTargetCreatePacket = mCPythonNetworkStream_RecvTargetCreatePacket;
fnCPythonNetworkStream_RecvTargetCreatePacketNew m_CPythonNetworkStream_RecvTargetCreatePacketNew = mCPythonNetworkStream_RecvTargetCreatePacketNew;
fnCPythonNetworkStream_RecvNPCList m_CPythonNetworkStream_RecvNPCList = mCPythonNetworkStream_RecvNPCList;

void CPythonNetworkStream_Hook() {
	CPythonNetworkStream_Constructor = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 6a ff 68 87 c3", 0x0, 0x0);
	CPythonNetworkStream_SetOfflinePhase = LIB_pattern_find(GetModuleHandle(NULL), "56 8b f1 57 8d be 18 01 00 00 57 68 ?? ?? ?? ?? e8 bb 61 f6 ff", 0x0, 0x0);
	CPythonNetworkStream_SetHandshakePhase = LIB_pattern_find(GetModuleHandle(NULL), "56 8b f1 57 8d be 18 01 00 00 57 68 ?? ?? ?? ?? e8 6b e9 f4 ff", 0x0, 0x0);
	CPythonNetworkStream_SetLoginPhase = LIB_pattern_find(GetModuleHandle(NULL), "56 57 8b f1 ?? ?? ?? ?? ?? 8d be 18 01 00 00 57", 0x0, 0x0);
	CPythonNetworkStream_SendLoginPacketNew = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 38 a1 ?? ?? ?? ?? 33 c5 89 45 fc 56 8b f1 c6", 0x0, 0x0);
	CPythonNetworkStream_SendAttackPacket = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 08 56 8b f1 e8 d2 3c 00 00 84 c0 75 09 b0 01 5e 8b e5 5d c2 08 00", 0x0, 0x0);
	CPythonNetworkStream_SendItemDropPacketNew = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 10 56 8b f1 e8 c2 ed ff ff", 0x0, 0x0);
	CPythonNetworkStream_SendGiveItemPacket = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 0c 8b 45 08 89 45 f5 66 8b", 0x0, 0x0);
	
	CPythonNetworkStream_RecvTargetCreatePacket = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 2c a1 ?? ?? ?? ?? 33 c5 89 45 fc 56 8d 45 d4", 0x0, 0x0);
	CPythonNetworkStream_RecvTargetCreatePacketNew = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 30 a1 ?? ?? ?? ?? 33 c5 89 45 fc 56 8d 45 d0", 0x0, 0x0);
	CPythonNetworkStream_RecvNPCList = LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 83 ec 30 a1 ?? ?? ?? ?? 33 c5 89 45 fc 56 57", 0x0, 0x0);

	HOOK_assert(CPythonNetworkStream_Constructor);
	HOOK_assert(CPythonNetworkStream_SetOfflinePhase);
	HOOK_assert(CPythonNetworkStream_SetHandshakePhase);
	HOOK_assert(CPythonNetworkStream_SetLoginPhase);
	HOOK_assert(CPythonNetworkStream_SendLoginPacketNew);
	HOOK_assert(CPythonNetworkStream_SendAttackPacket);
	HOOK_assert(CPythonNetworkStream_SendItemDropPacketNew);
	HOOK_assert(CPythonNetworkStream_SendGiveItemPacket);

	HOOK_assert(CPythonNetworkStream_RecvTargetCreatePacket);
	HOOK_assert(CPythonNetworkStream_RecvTargetCreatePacketNew);
	HOOK_assert(CPythonNetworkStream_RecvNPCList);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID *)&CPythonNetworkStream_Constructor, m_CPythonNetworkStream_Constructor);
	DetourAttach((PVOID *)&CPythonNetworkStream_SetOfflinePhase, m_CPythonNetworkStream_SetOfflinePhase);
	DetourAttach((PVOID *)&CPythonNetworkStream_SetHandshakePhase, m_CPythonNetworkStream_SetHandshakePhase);
	DetourAttach((PVOID *)&CPythonNetworkStream_SetLoginPhase, m_CPythonNetworkStream_SetLoginPhase);
	DetourAttach((PVOID *)&CPythonNetworkStream_SendLoginPacketNew, m_CPythonNetworkStream_SendLoginPacketNew);
	DetourAttach((PVOID *)&CPythonNetworkStream_SendAttackPacket, m_CPythonNetworkStream_SendAttackPacket);
	DetourAttach((PVOID *)&CPythonNetworkStream_SendItemDropPacketNew, m_CPythonNetworkStream_SendItemDropPacketNew);
	DetourAttach((PVOID *)&CPythonNetworkStream_SendGiveItemPacket, m_CPythonNetworkStream_SendGiveItemPacket);
	DetourAttach((PVOID *)&CPythonNetworkStream_RecvTargetCreatePacket, m_CPythonNetworkStream_RecvTargetCreatePacket);
	DetourAttach((PVOID *)&CPythonNetworkStream_RecvTargetCreatePacketNew, m_CPythonNetworkStream_RecvTargetCreatePacketNew);
	DetourAttach((PVOID *)&CPythonNetworkStream_RecvNPCList, m_CPythonNetworkStream_RecvNPCList);
	DetourTransactionCommit();
}

void CPythonNetworkStream_Restore() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID *)&CPythonNetworkStream_Constructor, m_CPythonNetworkStream_Constructor);
	DetourDetach((PVOID *)&CPythonNetworkStream_SetOfflinePhase, m_CPythonNetworkStream_SetOfflinePhase);
	DetourDetach((PVOID *)&CPythonNetworkStream_SetHandshakePhase, m_CPythonNetworkStream_SetHandshakePhase);
	DetourDetach((PVOID *)&CPythonNetworkStream_SetLoginPhase, m_CPythonNetworkStream_SetLoginPhase);
	DetourDetach((PVOID *)&CPythonNetworkStream_SendLoginPacketNew, m_CPythonNetworkStream_SendLoginPacketNew);
	DetourDetach((PVOID *)&CPythonNetworkStream_SendAttackPacket, m_CPythonNetworkStream_SendAttackPacket);
	DetourDetach((PVOID *)&CPythonNetworkStream_SendItemDropPacketNew, m_CPythonNetworkStream_SendItemDropPacketNew);
	DetourDetach((PVOID *)&CPythonNetworkStream_SendGiveItemPacket, m_CPythonNetworkStream_SendGiveItemPacket);
	DetourDetach((PVOID *)&CPythonNetworkStream_RecvTargetCreatePacket, m_CPythonNetworkStream_RecvTargetCreatePacket);
	DetourDetach((PVOID *)&CPythonNetworkStream_RecvTargetCreatePacketNew, m_CPythonNetworkStream_RecvTargetCreatePacketNew);
	DetourDetach((PVOID *)&CPythonNetworkStream_RecvNPCList, m_CPythonNetworkStream_RecvNPCList);
	DetourTransactionCommit();
}

/** \} */
