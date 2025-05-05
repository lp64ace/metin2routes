#ifndef C_NETWORK_ACTOR_MANAGER_H
#define C_NETWORK_ACTOR_MANAGER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SNetworkActorData SNetworkActorData;
typedef struct CNetworkActorManager CNetworkActorManager;

typedef void *(__fastcall *fnSNetworkActorData_Constructor)(void *ECX, void *EDX);
typedef void (__fastcall *fnSNetworkActorData_CopyConstructor)(void *ECX, void *EDX, const struct SNetworkActorData *lpSource);

typedef void(__fastcall *fnCNetworkActorManager_AppendActor)(void *ECX, void *EDX, const struct SNetworkActorData *c_rkNetworkData);

void CNetworkActorManager_Hook();
void CNetworkActorManager_Restore();

/* -------------------------------------------------------------------- */
/** \name Offset Resolve
 * \{ */

const char *SNetworkActorData_mStName(const SNetworkActorData *me);
const unsigned char *SNetworkActorData_mbType(const SNetworkActorData *me);
const unsigned long *SNetworkActorData_mdwVID(const SNetworkActorData *me);

const long *SNetworkActorData_mlCurX(const SNetworkActorData *me);
const long *SNetworkActorData_mlCurY(const SNetworkActorData *me);
const long *SNetworkActorData_mlSrcX(const SNetworkActorData *me);
const long *SNetworkActorData_mlSrcY(const SNetworkActorData *me);
const long *SNetworkActorData_mlDstX(const SNetworkActorData *me);
const long *SNetworkActorData_mlDstY(const SNetworkActorData *me);

SNetworkActorData *CNetworkActorManager_NetActorFind(const CNetworkActorManager *me, void *EDX, unsigned long dwVID);
SNetworkActorData *CNetworkActorManager_NetActorClose(const CNetworkActorManager *me, void *EDX, unsigned char bType);

const unsigned long *CNetworkActorManager_mdwMainVID(const CNetworkActorManager *me);
const long *CNetworkActorManager_mlMainPosX(const CNetworkActorManager *me);
const long *CNetworkActorManager_mlMainPosY(const CNetworkActorManager *me);

/** \} */

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#	include <map>

const std::map<unsigned long, SNetworkActorData> *CNetworkActorManager_mkNetActorDict(const CNetworkActorManager *me);
std::map<unsigned long, SNetworkActorData> *CNetworkActorManager_mkNetActorDict(CNetworkActorManager *me);
#endif

#endif // C_NETWORK_ACTOR_MANAGER_H
