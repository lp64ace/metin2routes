#ifndef C_PYTHON_APPLICATION_H
#define C_PYTHON_APPLICATION_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CPythonApplication CPythonApplication;

typedef CPythonApplication *(__fastcall *fnCPythonApplication_Constructor)(void *ECX, void *EDX);
typedef void (__fastcall *fnCPythonApplication_UpdateGame)(void *ECX, void *EDX);
typedef void (__fastcall *fnCPythonApplication_RenderGame)(void *ECX, void *EDX);
typedef bool(__fastcall *fnCPythonApplication_Process)(void *ECX, void *EDX);

void CPythonApplication_Hook();
void CPythonApplication_Restore();

/* -------------------------------------------------------------------- */
/** \name Offset Resolve
 * \{ */

extern CPythonApplication *nkApplication;

struct CAccountConnector *CPythonApplication_mkAccountConnector(CPythonApplication *me);

/** \} */

#ifdef __cplusplus
}
#endif

#endif
