#ifndef CPYTHON_APPLICATION_H
#define CPYTHON_APPLICATION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CPythonApplication CPythonApplication;

typedef CPythonApplication *(__fastcall *fnCPythonApplication_Constructor)(CPythonApplication *me);
typedef void (__fastcall *fnCPythonApplication_UpdateGame)(CPythonApplication *me);
typedef void (__fastcall *fnCPythonApplication_RenderGame)(CPythonApplication *me);

void CPythonApplication_Hook();
void CPythonApplication_Restore();

#ifdef __cplusplus
}
#endif

#endif
