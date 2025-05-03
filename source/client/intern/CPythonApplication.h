#ifndef CPYTHON_APPLICATION_H
#define CPYTHON_APPLICATION_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CPythonApplication CPythonApplication;

typedef CPythonApplication *(__fastcall *fnCPythonApplication_Constructor)(CPythonApplication *me);
typedef void (__fastcall *fnCPythonApplication_UpdateGame)(void *ECX, void *EDX);
typedef void (__fastcall *fnCPythonApplication_RenderGame)(void *ECX, void *EDX);
typedef bool(__fastcall *fnCPythonApplication_Process)(void *ECX, void *EDX);

void CPythonApplication_Hook();
void CPythonApplication_Restore();

#ifdef __cplusplus
}
#endif

#endif
