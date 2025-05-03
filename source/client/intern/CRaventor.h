#ifndef CRAVENTOR_H
#define CRAVENTOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (__stdcall *fnInitServerInfo)(void);

void CRaventor_Hook();
void CRaventor_Restore();

#ifdef __cplusplus
}
#endif

#endif // CRAVENTOR_H
