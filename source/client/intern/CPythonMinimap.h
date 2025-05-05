#ifndef C_PYTHON_MINIMAP_H
#define C_PYTHON_MINIMAP_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CPythonMinimap CPythonMinimap;

typedef void(__fastcall *fnCPythonMiniMap_RegisterAtlasMark)(void *ECX, void *EDX, unsigned char bType, const char *c_szName, long lx, long ly);

void CPythonMinimap_Hook();
void CPythonMinimap_Restore();

#ifdef __cplusplus
}
#endif

#endif