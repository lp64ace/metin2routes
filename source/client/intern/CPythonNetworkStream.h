#ifndef CPYTHON_NETWORK_STREAM_H
#define CPYTHON_NETWORK_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CPythonNetworkStream CPythonNetworkStream;

typedef CPythonNetworkStream *(__fastcall *fnCPythonNetworkStream_Constructor)(CPythonNetworkStream *me);

void CPythonNetworkStream_Hook();
void CPythonNetworkStream_Restore();

#ifdef __cplusplus
}
#endif

#endif
