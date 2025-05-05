#ifndef C_ACCOUNT_CONNECTOR_H
#define C_ACCOUNT_CONNECTOR_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CAccountConnector CAccountConnector;

typedef CAccountConnector *(__fastcall *fnCAccountConnector_Constructor)(void *ECX, void *EDX);
typedef void(__fastcall *fnCAccountConnector_SetLoginInfo)(void *ECX, void *EDX, const char *c_szName, const char *c_szPwd);
typedef bool(__fastcall *fnCAccountConnector_Process)(void *ECX, void *EDX);
typedef bool(__fastcall *fnCAccountConnector_Connect)(void *ECX, void *EDX, const char *c_szAddr, int iPort, const char *c_szAccountAddr, int iAccountPort);

typedef bool(__fastcall *fnCAccountConnector___AuthState_RecvPhase)(void *ECX, void *EDX);
typedef bool(__fastcall *fnCAccountConnector___AuthState_RecvAuthSuccess)(void *ECX, void *EDX);

void CAccountConnector_Hook();
void CAccountConnector_Restore();

/* -------------------------------------------------------------------- */
/** \name Offset Resolve
 * \{ */

unsigned int *CAccountConnector_mEState(CAccountConnector *me);
int *CAccountConnector_mIsWaitKey(CAccountConnector *me);
const char *CAccountConnector_mStrId(CAccountConnector *me);
const char *CAccountConnector_mStrPassword(CAccountConnector *me);

/** \} */

#ifdef __cplusplus
}
#endif

#endif	// C_ACCOUNT_CONNECTOR_H