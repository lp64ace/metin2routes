#include "MEM_guardedalloc.h"

#include "LIB_assert.h"
#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include <windows.h>
#include <detours.h>

#include "CNetworkActorManager.h"
#include "CActorInstance.h"

#include <map>
#include <string>

/* -------------------------------------------------------------------- */
/** \name Original Functions
 * \{ */

fnSNetworkActorData_Constructor SNetworkActorData_Constructor = NULL;
fnSNetworkActorData_CopyConstructor SNetworkActorData_CopyConstructor = NULL;

/** \} */

/* -------------------------------------------------------------------- */
/** \name Offset Resolve
 * \{ */

typedef void *(__thiscall *fnThisSNetworkActorData_Constructor)(SNetworkActorData *me);
typedef void(__thiscall *fnThisSNetworkActorData_CopyConstructor)(SNetworkActorData *me, const SNetworkActorData *other);

typedef struct SNetworkActorData {
	SNetworkActorData() {
		reinterpret_cast<fnThisSNetworkActorData_Constructor>(SNetworkActorData_Constructor)(this);
	}
	SNetworkActorData(const SNetworkActorData& other) {
		reinterpret_cast<fnThisSNetworkActorData_CopyConstructor>(SNetworkActorData_CopyConstructor)(this, &other);
	}

	MEM_PAD(0x169);
} SNetworkActorData;

const char *SNetworkActorData_mStName(const SNetworkActorData *me) {
	return reinterpret_cast<const std::string *>(POINTER_OFFSET(me, 0x0))->c_str();
}
const BYTE *SNetworkActorData_mbType(const SNetworkActorData *me) {
	return reinterpret_cast<BYTE *>(POINTER_OFFSET(me, 0x20));
}
const DWORD *SNetworkActorData_mdwVID(const SNetworkActorData *me) {
	return reinterpret_cast<DWORD *>(POINTER_OFFSET(me, 0x24));
}

const LONG *SNetworkActorData_mlCurX(const SNetworkActorData *me) {
	return reinterpret_cast<LONG *>(POINTER_OFFSET(me, 0x40));
}
const LONG *SNetworkActorData_mlCurY(const SNetworkActorData *me) {
	return reinterpret_cast<LONG *>(POINTER_OFFSET(me, 0x44));
}
const LONG *SNetworkActorData_mlSrcX(const SNetworkActorData *me) {
	return reinterpret_cast<LONG *>(POINTER_OFFSET(me, 0x48));
}
const LONG *SNetworkActorData_mlSrcY(const SNetworkActorData *me) {
	return reinterpret_cast<LONG *>(POINTER_OFFSET(me, 0x4c));
}
const LONG *SNetworkActorData_mlDstX(const SNetworkActorData *me) {
	return reinterpret_cast<LONG *>(POINTER_OFFSET(me, 0x50));
}
const LONG *SNetworkActorData_mlDstY(const SNetworkActorData *me) {
	return reinterpret_cast<LONG *>(POINTER_OFFSET(me, 0x54));
}

const std::map<DWORD, SNetworkActorData> *CNetworkActorManager_mkNetActorDict(const CNetworkActorManager *me) {
	return reinterpret_cast<const std::map<DWORD, SNetworkActorData> *>(POINTER_OFFSET(me, 0x14));
}
std::map<DWORD, SNetworkActorData> *CNetworkActorManager_mkNetActorDict(CNetworkActorManager *me) {
	return reinterpret_cast<std::map<DWORD, SNetworkActorData> *>(POINTER_OFFSET(me, 0x14));
}
const DWORD *CNetworkActorManager_mdwMainVID(const CNetworkActorManager *me) {
	return reinterpret_cast<DWORD *>(POINTER_OFFSET(me, 0x0c));
}
const LONG *CNetworkActorManager_mlMainPosX(const CNetworkActorManager *me) {
	return reinterpret_cast<LONG *>(POINTER_OFFSET(me, 0x10));
}
const LONG *CNetworkActorManager_mlMainPosY(const CNetworkActorManager *me) {
	return reinterpret_cast<LONG *>(POINTER_OFFSET(me, 0x14));
}

SNetworkActorData *CNetworkActorManager_NetActorFind(const CNetworkActorManager *me, void *EDX, DWORD dwVID) {
	auto iterator = CNetworkActorManager_mkNetActorDict(me)->find(dwVID);
	if (iterator == CNetworkActorManager_mkNetActorDict(me)->end()) {
		return NULL;
	}

	SNetworkActorData *lpActor = reinterpret_cast<SNetworkActorData *>(MEM_mallocN(sizeof(SNetworkActorData), "SNetworkActorData"));
	SNetworkActorData_Constructor(lpActor, EDX);
	SNetworkActorData_CopyConstructor(lpActor, EDX, &iterator->second);
	return lpActor;
}
SNetworkActorData *CNetworkActorManager_NetActorClose(const CNetworkActorManager *me, void *EDX, unsigned char bType) {
	SNetworkActorData *lpActor = NULL;

	double dblMeX = *CNetworkActorManager_mlMainPosX(me);
	double dblMeY = *CNetworkActorManager_mlMainPosY(me);
	double dblBestDist = INT_MAX;
	for (const auto &pair : *CNetworkActorManager_mkNetActorDict(me)) {
		const SNetworkActorData *lpData = &pair.second;

		if (*SNetworkActorData_mbType(lpData) != bType) {
			continue;
		}

		double dblCurX = *SNetworkActorData_mlCurX(lpData);
		double dblCurY = *SNetworkActorData_mlCurY(lpData);
		double dblCurDist = (dblCurX - dblMeX) * (dblCurX - dblMeX) + (dblCurY - dblMeY) * (dblCurY - dblMeY);

		// LOG("ME (%ld, %ld) TARGET %s (%ld, %ld) DIST %lf BEST %lf", *CNetworkActorManager_mlMainPosX(me), *CNetworkActorManager_mlMainPosY(me), SNetworkActorData_mStName(lpData), *SNetworkActorData_mlCurX(lpData), *SNetworkActorData_mlCurY(lpData), dblCurDist, dblBestDist);

		if (dblBestDist > dblCurDist) {
			if (!lpActor) {
				lpActor = reinterpret_cast<SNetworkActorData *>(MEM_mallocN(sizeof(SNetworkActorData), "SNetworkActorData"));
				SNetworkActorData_Constructor(lpActor, EDX);
			}
			SNetworkActorData_CopyConstructor(lpActor, EDX, lpData);
			dblBestDist = dblCurDist;
		}
	}

	return lpActor;
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Original Functions
 * \{ */

fnCNetworkActorManager_AppendActor CNetworkActorManager_AppendActor = NULL;

/** \} */

/* -------------------------------------------------------------------- */
/** \name Overriden Functions
 * \{ */

void __fastcall mCNetworkActorManager_AppendActor(CNetworkActorManager *me, void *EDX, const struct SNetworkActorData *c_rkNetworkData) {
	LOG("CALL");
	CNetworkActorManager_AppendActor(me, EDX, c_rkNetworkData);
	for (const auto &pair : *CNetworkActorManager_mkNetActorDict(me)) {
		if (pair.first == *CNetworkActorManager_mdwMainVID(me)) {
			LOG("MAINT ACTOR AT (%ld/%ld, %ld/%ld)", *CNetworkActorManager_mlMainPosX(me), *SNetworkActorData_mlCurX(&pair.second), *CNetworkActorManager_mlMainPosY(me), *SNetworkActorData_mlCurY(&pair.second));
		}
	}
}

/** \} */

/* -------------------------------------------------------------------- */
/** \name Hooking
 * \{ */

/** We keep these casts so that we ensure that the type of the functions are consistent with the header. */
fnCNetworkActorManager_AppendActor m_CNetworkActorManager_AppendActor = reinterpret_cast<fnCNetworkActorManager_AppendActor>(mCNetworkActorManager_AppendActor);

void CNetworkActorManager_Hook() {
	SNetworkActorData_Constructor = reinterpret_cast<fnSNetworkActorData_Constructor>(LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 6a ff 68 ?? ?? ?? ?? 64 a1 00 00 00 00 50 51 56 57 a1 ?? ?? ?? ?? 33 c5 50 8d 45 f4 64 a3 ?? ?? ?? ?? 8b f1 89 75 f0 0f 57 c0 0f 11 06 c7 46 10 00 00 00 00 c7 46 14 00 00 00 00 c7 46 10 00 00 00 00 c7 46 14 0f 00 00 00 c6 06 00 8d 4e 18 c7 45 fc 00 00 00 00 e8 32 c8", 0x0, 0x0));
	SNetworkActorData_CopyConstructor = reinterpret_cast<fnSNetworkActorData_CopyConstructor>(LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 56 8b 75 08 57 8b f9 0f b6 46 20 88 47 20", 0x0, 0x0));
	
	CNetworkActorManager_AppendActor = reinterpret_cast<fnCNetworkActorManager_AppendActor>(LIB_pattern_find(GetModuleHandle(NULL), "55 8b ec 6a ff 68 ?? ?? ?? ?? 64 a1 ?? ?? ?? ?? 50 83 ec 18 53 56 57 a1 ?? ?? ?? ?? 33 c5 50 8d 45 f4 64 a3 ?? ?? ?? ?? 8b d9 8b 75 08", 0x0, 0x0));

	HOOK_assert(SNetworkActorData_Constructor);
	HOOK_assert(SNetworkActorData_CopyConstructor);

	HOOK_assert(CNetworkActorManager_AppendActor);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID *)&CNetworkActorManager_AppendActor, m_CNetworkActorManager_AppendActor);
	DetourTransactionCommit();
}

void CNetworkActorManager_Restore() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach((PVOID *)&CNetworkActorManager_AppendActor, m_CNetworkActorManager_AppendActor);
	DetourTransactionCommit();
}

/** \} */
