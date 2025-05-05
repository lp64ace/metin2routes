#ifndef C_NETWORK_STREAM_H
#define C_NETWORK_STREAM_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CNetworkStream CNetworkStream;

typedef bool (__fastcall *fnCNetworkStream_Process)(void *ECX, void *EDX);
typedef bool (__fastcall *fnCNetworkStream_Peek)(void *ECX, void *EDX, int size, char *pDestBuf);
typedef bool (__fastcall *fnCNetworkStream_RecvInternalBuffer)(void *ECX, void *EDX);
typedef bool (__fastcall *fnCNetworkStream_SendInternalBuffer)(void *ECX, void *EDX);
typedef bool(__fastcall *fnCNetworkStream_Connect)(void *ECX, void *EDX, const char *c_szAddr, int port, int limitSec);

void CNetworkStream_Hook();
void CNetworkStream_Restore();

extern fnCNetworkStream_Process CNetworkStream_Process;
extern fnCNetworkStream_Peek CNetworkStream_Peek;
extern fnCNetworkStream_RecvInternalBuffer CNetworkStream_RecvInternalBuffer;
extern fnCNetworkStream_SendInternalBuffer CNetworkStream_SendInternalBuffer;
extern fnCNetworkStream_Connect CNetworkStream_Connect;

/* -------------------------------------------------------------------- */
/** \name Offset Resolve
 * \{ */

unsigned int *CNetworkStream_mSock(CNetworkStream *me);

/** \} */

#ifdef __cplusplus
}
#endif

#endif
