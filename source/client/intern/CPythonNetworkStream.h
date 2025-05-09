#ifndef C_PYTHON_NETWORK_STREAM_H
#define C_PYTHON_NETWORK_STREAM_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct CNetworkActorManager;

typedef struct CPythonNetworkStream CPythonNetworkStream;

typedef CPythonNetworkStream *(__fastcall *fnCPythonNetworkStream_Constructor)(void *ECX, void *EDX);
typedef void (__fastcall *fnCPythonNetworkStream_SetOfflinePhase)(void *ECX, void *EDX);
typedef void (__fastcall *fnCPythonNetworkStream_SetHandshakePhase)(void *ECX, void *EDX);
typedef void (__fastcall *fnCPythonNetworkStream_SetLoginPhase)(void *ECX, void *EDX);
typedef bool (__fastcall *fnCPythonNetworkStream_SendLoginPacketNew)(void *ECX, void *EDX, const char *c_szName, const char *c_szPassword);
typedef bool (__fastcall *fnCPythonNetworkStream_SendAttackPacket)(void *ECX, void *EDX, unsigned int uMotAttack, unsigned int dwVIDVictim);
typedef int (__fastcall *fnCPythonNetworkStream_SendItemDropPacketNew)(void *ECX, void *EDX, uint16_t ItemPos, uint32_t param_2, uint8_t param_3, uint32_t param_4);
typedef bool (__fastcall *fnCPythonNetworkStream_SendGiveItemPacket)(void *ECX, void *EDX, unsigned long dwTargetVID, uint16_t ItemPos, int iItemCount);

typedef bool(__fastcall *fnCPythonNetworkStream_RecvTargetCreatePacket)(void *ECX, void *EDX);
typedef bool(__fastcall *fnCPythonNetworkStream_RecvTargetCreatePacketNew)(void *ECX, void *EDX);
typedef bool(__fastcall *fnCPythonNetworkStream_RecvNPCList)(void *ECX, void *EDX);

void CPythonNetworkStream_Hook();
void CPythonNetworkStream_Restore();

/* -------------------------------------------------------------------- */
/** \name Offset Resolve
 * \{ */

extern CPythonNetworkStream *nkNetStream;

const char *CPythonNetworkStream_mStrPhase(CPythonNetworkStream *me);
struct CNetworkActorManager **CPythonNetworkStream_mNetActorMgr(CPythonNetworkStream *me);

/** \} */

#ifdef __cplusplus
}
#endif

#endif
