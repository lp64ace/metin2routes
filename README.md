# hook
Sample function hooking for windows

## Target program

We have a very simple C program that will always output zeros on the screen.
Each time calling a function `add_v4_v4`, the function we want to hook.

```c
#include "LIB_utildefines.h"

#include <stdbool.h>
#include <stdio.h>

HOOK_NOINLINE void add_v4_v4(float r[4], const float a[4]);

int main(void) {
	float v[4] = { -4, -8, -2, -1 };
	while (true) {
		add_v4_v4(v, (const float [4]){  4,  8,  2,  1 });
		fprintf(stdout, "%.1f %.1f %.1f %.1f\n", v[0], v[1], v[2], v[3]);
		add_v4_v4(v, (const float [4]){ -4, -8, -2, -1 });
	}
	return 0;
}

HOOK_NOINLINE void add_v4_v4(float r[4], const float a[4]) {
	r[0] += a[0];
	r[1] += a[1];
	r[2] += a[2];
	r[3] += a[3];
}

```
## Predator program

We want to override the function on the target program with a new function.

```c
HOOK_NOINLINE void hook_v4_v4(float r[4], const float a[4]) {
	fprintf(stdout, "[Hook] Hello from hook\n");

	r[0] = 6;
	r[1] = 9;
	r[2] = 6;
	r[3] = 9;
}
```

After opening the compiled .exe (from Release) we find this function in ASM

```c
0xf3 0x0f 0x10 0x01				// MOVSS	XMM0,dword ptr [param_1]
0xf3 0x0f 0x58 0x02				// ADDSS	XMM0,dword ptr [param_2]
0xf3 0x0f 0x11 0x01				// MOVSS	dword ptr [param_1],XMM0
0xf3 0x0f 0x10 0x4a 0x04		// MOVSS	XMM1,dword ptr [param_2 + 0x4]
0xf3 0x0f 0x58 0x49 0x04		// ADDSS	XMM1,dword ptr [param_1 + 0x4]
0xf3 0x0f 0x11 0x49 0x04		// MOVSS	dword ptr [param_1 + 0x4],XMM1
0xf3 0x0f 0x10 0x42 0x08		// MOVSS	XMM0,dword ptr [param_2 + 0x8]
0xf3 0x0f 0x58 0x41 0x08		// ADDSS	XMM0,dword ptr [param_1 + 0x8]
0xf3 0x0f 0x11 0x41 0x08		// MOVSS	dword ptr [param_1 + 0x8],XMM0
0xf3 0x0f 0x10 0x4a 0x0c		// MOVSS	XMM1,dword ptr [param_2 + 0xc]
0xf3 0x0f 0x58 0x49 0x0c		// ADDSS	XMM1,dword ptr [param_1 + 0xc]
0xf3 0x0f 0x11 0x49 0x0c		// MOVSS	dword ptr [param_1 + 0xc],XMM1
```

We hook the function and override it using Detours.
