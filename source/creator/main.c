#include "LIB_memory.h"
#include "LIB_utildefines.h"

#include <stdio.h>
#include <windows.h>
#include <psapi.h>
#include <detours.h>

HOOK_NOINLINE void hook_v2_v2(float r[2], const float a[2]);
HOOK_NOINLINE void hook_v3_v3(float r[3], const float a[3]);
HOOK_NOINLINE void hook_v4_v4(float r[4], const float a[4]);

/**
 * RELEASE
 *
 * This is the function we want to hook in C.
 *
 * void add_v4_v4(float *r,float *a) {
 *   r[0] = r[0] + a[0];
 *   r[1] = r[1] + a[1];
 *   r[2] = r[2] + a[2];
 *   r[3] = r[3] + a[3];
 *   return;
 * }
 *
 * This is the function we want to hook in ASM.
 * 
 * MOVSS      XMM0,dword ptr [r]
 * ADDSS      XMM0,dword ptr [a]
 * MOVSS      dword ptr [r],XMM0
 * MOVSS      XMM1,dword ptr [a + 0x4]
 * ADDSS      XMM1,dword ptr [r + 0x4]
 * MOVSS      dword ptr [r + 0x4],XMM1
 * MOVSS      XMM0,dword ptr [a + 0x8]
 * ADDSS      XMM0,dword ptr [r + 0x8]
 * MOVSS      dword ptr [r + 0x8],XMM0
 * MOVSS      XMM1,dword ptr [a + 0xc]
 * ADDSS      XMM1,dword ptr [r + 0xc]
 * MOVSS      dword ptr [r + 0xc],XMM1
 * 
 * RET
 * ??         CCh
 * ??         CCh
 * ??         CCh
 * ??         CCh
 * ??         CCh
 * ??         CCh
 *
 * This is the function we want to hook in BINARY.
 *
 * f3 0f 10 01 f3 0f 58 02 f3 0f 11 01 f3 0f 10 4a
 * 04 f3 0f 58 49 04 f3 0f 11 49 04 f3 0f 10 42 08
 * f3 0f 58 41 08 f3 0f 11 41 08 f3 0f 10 4a 0c f3
 * 0f 58 49 0c f3 0f 11 49 0c
 *
 */

/**
 * DEBUG
 *
 * This is the function we want to hook in C.
 *
 * void add_v4_v4(float *r,float *a) {
 *   r[0] = r[0] + a[0];
 *   r[1] = r[1] + a[1];
 *   r[2] = r[2] + a[2];
 *   r[3] = r[3] + a[3];
 *   return;
 * }
 *
 * This is the function we want to hook in ASM.
 * 
 * MOV        EAX,0x4
 * IMUL       RAX,RAX,0x0
 * MOV        param_1,0x4
 * IMUL       param_1,param_1,0x0
 * MOV        param_2,qword ptr [RSP + local_res8]
 * MOV        R8,qword ptr [RSP + local_res10]
 * MOVSS      XMM0,dword ptr [param_2 + RAX*0x1]
 * ADDSS      XMM0,dword ptr [R8 + param_1*0x1]
 * MOV        EAX,0x4
 * IMUL       RAX,RAX,0x0
 * MOV        param_1,qword ptr [RSP + local_res8]
 * MOVSS      dword ptr [param_1 + RAX*0x1],XMM0
 * 
 * MOV        EAX,0x4
 * IMUL       RAX,RAX,0x1
 * MOV        param_1,0x4
 * IMUL       param_1,param_1,0x1
 * MOV        param_2,qword ptr [RSP + local_res8]
 * MOV        R8,qword ptr [RSP + local_res10]
 * MOVSS      XMM0,dword ptr [param_2 + RAX*0x1]
 * ADDSS      XMM0,dword ptr [R8 + param_1*0x1]
 * MOV        EAX,0x4
 * IMUL       RAX,RAX,0x1
 * MOV        param_1,qword ptr [RSP + local_res8]
 * MOVSS      dword ptr [param_1 + RAX*0x1],XMM0
 * 
 * MOV        EAX,0x4
 * IMUL       RAX,RAX,0x2
 * MOV        param_1,0x4
 * IMUL       param_1,param_1,0x2
 * MOV        param_2,qword ptr [RSP + local_res8]
 * MOV        R8,qword ptr [RSP + local_res10]
 * MOVSS      XMM0,dword ptr [param_2 + RAX*0x1]
 * ADDSS      XMM0,dword ptr [R8 + param_1*0x1]
 * MOV        EAX,0x4
 * IMUL       RAX,RAX,0x2
 * MOV        param_1,qword ptr [RSP + local_res8]
 * MOVSS      dword ptr [param_1 + RAX*0x1],XMM0
 * 
 * MOV        EAX,0x4
 * IMUL       RAX,RAX,0x3
 * MOV        param_1,0x4
 * IMUL       param_1,param_1,0x3
 * MOV        param_2,qword ptr [RSP + local_res8]
 * MOV        R8,qword ptr [RSP + local_res10]
 * MOVSS      XMM0,dword ptr [param_2 + RAX*0x1]
 * ADDSS      XMM0,dword ptr [R8 + param_1*0x1]
 * MOV        EAX,0x4
 * IMUL       RAX,RAX,0x3
 * MOV        param_1,qword ptr [RSP + local_res8]
 * MOVSS      dword ptr [param_1 + RAX*0x1],XMM0
 *
 * This is the function we want to hook in BINARY.
 *
 * b8 04 00 00 00 48 6b c0 00 b9 04 00 00 00 48 6b
 * c9 00 48 8b 54 24 10 4c 8b 44 24 18 f3 0f 10 04
 * 02 f3 41 0f 58 04 08 b8 04 00 00 00 48 6b c0 00 
 * 48 8b 4c 24 10 f3 0f 11 04 01
 * 
 * b8 04 00 00 00 48 6b c0 01 b9 04 00 00 00 48 6b
 * c9 01 48 8b 54 24 10 4c 8b 44 24 18 f3 0f 10 04
 * 02 f3 41 0f 58 04 08 b8 04 00 00 00 48 6b c0 01 
 * 48 8b 4c 24 10 f3 0f 11 04 01
 * 
 * b8 04 00 00 00 48 6b c0 02 b9 04 00 00 00 48 6b
 * c9 02 48 8b 54 24 10 4c 8b 44 24 18 f3 0f 10 04 
 * 02 f3 41 0f 58 04 08 b8 04 00 00 00 48 6b c0 02 
 * 48 8b 4c 24 10 f3 0f 11 04 01
 * 
 * b8 04 00 00 00 48 6b c0 03 b9 04 00 00 00 48 6b
 * c9 03 48 8b 54 24 10 4c 8b 44 24 18 f3 0f 10 04
 * 02 f3 41 0f 58 04 08 b8 04 00 00 00 48 6b c0 03 
 * 48 8b 4c 24 10 f3 0f 11 04 01
 *
 */

typedef void (*fn_v4_v4)(float r[4], const float a[4]);

fn_v4_v4 real_v4_v4 = NULL;

const unsigned char rls_sequence[] = {
	0xf3, 0x0f, 0x10, 0x01,				// MOVSS	XMM0,dword ptr [param_1]
	0xf3, 0x0f, 0x58, 0x02,				// ADDSS	XMM0,dword ptr [param_2]
	0xf3, 0x0f, 0x11, 0x01,				// MOVSS	dword ptr [param_1],XMM0
	0xf3, 0x0f, 0x10, 0x4a, 0x04,		// MOVSS	XMM1,dword ptr [param_2 + 0x4]
	0xf3, 0x0f, 0x58, 0x49, 0x04,		// ADDSS	XMM1,dword ptr [param_1 + 0x4]
	0xf3, 0x0f, 0x11, 0x49, 0x04,		// MOVSS	dword ptr [param_1 + 0x4],XMM1
	0xf3, 0x0f, 0x10, 0x42, 0x08,		// MOVSS	XMM0,dword ptr [param_2 + 0x8]
	0xf3, 0x0f, 0x58, 0x41, 0x08,		// ADDSS	XMM0,dword ptr [param_1 + 0x8]
	0xf3, 0x0f, 0x11, 0x41, 0x08,		// MOVSS	dword ptr [param_1 + 0x8],XMM0
	0xf3, 0x0f, 0x10, 0x4a, 0x0c,		// MOVSS	XMM1,dword ptr [param_2 + 0xc]
	0xf3, 0x0f, 0x58, 0x49, 0x0c,		// ADDSS	XMM1,dword ptr [param_1 + 0xc]
	0xf3, 0x0f, 0x11, 0x49, 0x0c,		// MOVSS	dword ptr [param_1 + 0xc],XMM1
};

const unsigned char dbg_sequence[] = {
	0xb8, 0x04, 0x00, 0x00, 0x00,		// MOV        EAX,0x4
	0x48, 0x6b, 0xc0, 0x00,				// IMUL       RAX,RAX,0x0
	0xb9, 0x04, 0x00, 0x00, 0x00,		// MOV        param_1,0x4
	0x48, 0x6b, 0xc9, 0x00,				// IMUL       param_1,param_1,0x0
	0x48, 0x8b, 0x54, 0x24, 0x10,		// MOV        param_2,qword ptr [RSP + local_res8]
	0x4c, 0x8b, 0x44, 0x24, 0x18,		// MOV        R8,qword ptr [RSP + local_res10]
	0xf3, 0x0f, 0x10, 0x04, 0x02,		// MOVSS      XMM0,dword ptr [param_2 + RAX*0x1]
	0xf3, 0x41, 0x0f, 0x58, 0x04, 0x08,	// ADDSS      XMM0,dword ptr [R8 + param_1*0x1]
	0xb8, 0x04, 0x00, 0x00, 0x00,		// MOV        EAX,0x4
	0x48, 0x6b, 0xc0, 0x00,				// IMUL       RAX,RAX,0x0
	0x48, 0x8b, 0x4c, 0x24, 0x10,		// MOV        param_1,qword ptr [RSP + local_res8]
	0xf3, 0x0f, 0x11, 0x04, 0x01,		// MOVSS      dword ptr [param_1 + RAX*0x1],XMM0

	0xb8, 0x04, 0x00, 0x00, 0x00,		// MOV        EAX,0x4
	0x48, 0x6b, 0xc0, 0x01,				// IMUL       RAX,RAX,0x1
	0xb9, 0x04, 0x00, 0x00, 0x00,		// MOV        param_1,0x4
	0x48, 0x6b, 0xc9, 0x01,				// IMUL       param_1,param_1,0x1
	0x48, 0x8b, 0x54, 0x24, 0x10,		// MOV        param_2,qword ptr [RSP + local_res8]
	0x4c, 0x8b, 0x44, 0x24, 0x18,		// MOV        R8,qword ptr [RSP + local_res10]
	0xf3, 0x0f, 0x10, 0x04, 0x02,		// MOVSS      XMM0,dword ptr [param_2 + RAX*0x1]
	0xf3, 0x41, 0x0f, 0x58, 0x04, 0x08,	// ADDSS      XMM0,dword ptr [R8 + param_1*0x1]
	0xb8, 0x04, 0x00, 0x00, 0x00,		// MOV        EAX,0x4
	0x48, 0x6b, 0xc0, 0x01,				// IMUL       RAX,RAX,0x1
	0x48, 0x8b, 0x4c, 0x24, 0x10,		// MOV        param_1,qword ptr [RSP + local_res8]
	0xf3, 0x0f, 0x11, 0x04, 0x01,		// MOVSS      dword ptr [param_1 + RAX*0x1],XMM0

	0xb8, 0x04, 0x00, 0x00, 0x00,		// MOV        EAX,0x4
	0x48, 0x6b, 0xc0, 0x02,				// IMUL       RAX,RAX,0x2
	0xb9, 0x04, 0x00, 0x00, 0x00,		// MOV        param_1,0x4
	0x48, 0x6b, 0xc9, 0x02,				// IMUL       param_1,param_1,0x2
	0x48, 0x8b, 0x54, 0x24, 0x10,		// MOV        param_2,qword ptr [RSP + local_res8]
	0x4c, 0x8b, 0x44, 0x24, 0x18,		// MOV        R8,qword ptr [RSP + local_res10]
	0xf3, 0x0f, 0x10, 0x04, 0x02,		// MOVSS      XMM0,dword ptr [param_2 + RAX*0x1]
	0xf3, 0x41, 0x0f, 0x58, 0x04, 0x08,	// ADDSS      XMM0,dword ptr [R8 + param_1*0x1]
	0xb8, 0x04, 0x00, 0x00, 0x00,		// MOV        EAX,0x4
	0x48, 0x6b, 0xc0, 0x02,				// IMUL       RAX,RAX,0x2
	0x48, 0x8b, 0x4c, 0x24, 0x10,		// MOV        param_1,qword ptr [RSP + local_res8]
	0xf3, 0x0f, 0x11, 0x04, 0x01,		// MOVSS      dword ptr [param_1 + RAX*0x1],XMM0

	0xb8, 0x04, 0x00, 0x00, 0x00,		// MOV        EAX,0x4
	0x48, 0x6b, 0xc0, 0x03,				// IMUL       RAX,RAX,0x3
	0xb9, 0x04, 0x00, 0x00, 0x00,		// MOV        param_1,0x4
	0x48, 0x6b, 0xc9, 0x03,				// IMUL       param_1,param_1,0x3
	0x48, 0x8b, 0x54, 0x24, 0x10,		// MOV        param_2,qword ptr [RSP + local_res8]
	0x4c, 0x8b, 0x44, 0x24, 0x18,		// MOV        R8,qword ptr [RSP + local_res10]
	0xf3, 0x0f, 0x10, 0x04, 0x02,		// MOVSS      XMM0,dword ptr [param_2 + RAX*0x1]
	0xf3, 0x41, 0x0f, 0x58, 0x04, 0x08,	// ADDSS      XMM0,dword ptr [R8 + param_1*0x1]
	0xb8, 0x04, 0x00, 0x00, 0x00,		// MOV        EAX,0x4
	0x48, 0x6b, 0xc0, 0x03,				// IMUL       RAX,RAX,0x3
	0x48, 0x8b, 0x4c, 0x24, 0x10,		// MOV        param_1,qword ptr [RSP + local_res8]
	0xf3, 0x0f, 0x11, 0x04, 0x01,		// MOVSS      dword ptr [param_1 + RAX*0x1],XMM0
};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID unused) {
	switch (reason) {
		case DLL_PROCESS_ATTACH: {
			DisableThreadLibraryCalls(hModule);
			
			MODULEINFO mModInfo;
			HMODULE hMain = GetModuleHandle(NULL);
			GetModuleInformation(GetCurrentProcess(), hMain, &mModInfo, sizeof(mModInfo));
			
			uintptr_t offset;

			offset = LIB_pattern_offset(hMain, mModInfo.SizeOfImage, rls_sequence, NULL, ARRAY_SIZE(rls_sequence), 0x0);
			fprintf(stdout, "[RLS|0x%p] add_v4_v4\n", (void *)offset);
			if (offset != (uintptr_t)-1) {
				real_v4_v4 = POINTER_OFFSET(hMain, offset);
				
				DetourTransactionBegin();
				DetourUpdateThread(GetCurrentThread());
				DetourAttach((PVOID*)&real_v4_v4, hook_v4_v4);
				DetourTransactionCommit();
			}
			
			offset = LIB_pattern_offset(hMain, mModInfo.SizeOfImage, dbg_sequence, NULL, ARRAY_SIZE(dbg_sequence), 0xb);
			fprintf(stdout, "[DBG|0x%p] add_v4_v4\n", (void *)offset);
			if (offset != (uintptr_t)-1) {
				real_v4_v4 = POINTER_OFFSET(hMain, offset);
				
				DetourTransactionBegin();
				DetourUpdateThread(GetCurrentThread());
				DetourAttach((PVOID*)&real_v4_v4, hook_v4_v4);
				DetourTransactionCommit();
			}
		} break;
		case DLL_PROCESS_DETACH: {
			if (real_v4_v4 != NULL) {
				DetourTransactionBegin();
				DetourUpdateThread(GetCurrentThread());
				DetourDetach((PVOID*)&real_v4_v4, hook_v4_v4);
				DetourTransactionCommit();
			}
		} break;
	}
	return TRUE;
}

HOOK_NOINLINE void hook_v2_v2(float r[2], const float a[2]) {
	r[0] -= a[0];
	r[1] -= a[1];
}
HOOK_NOINLINE void hook_v3_v3(float r[3], const float a[3]) {
	r[0] -= a[0];
	r[1] -= a[1];
	r[2] -= a[2];
}
HOOK_NOINLINE void hook_v4_v4(float r[4], const float a[4]) {
	fprintf(stdout, "[Hook] Hello from hook\n");

	r[0] = 6;
	r[1] = 9;
	r[2] = 6;
	r[3] = 9;
}
