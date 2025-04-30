#include "LIB_utildefines.h"

#include <stdbool.h>
#include <stdio.h>

HOOK_NOINLINE void add_v2_v2(float r[2], const float a[2]);
HOOK_NOINLINE void add_v3_v3(float r[3], const float a[3]);
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

HOOK_NOINLINE void add_v2_v2(float r[2], const float a[2]) {
	r[0] += a[0];
	r[1] += a[1];
}
HOOK_NOINLINE void add_v3_v3(float r[3], const float a[3]) {
	r[0] += a[0];
	r[1] += a[1];
	r[2] += a[2];
}
HOOK_NOINLINE void add_v4_v4(float r[4], const float a[4]) {
	r[0] += a[0];
	r[1] += a[1];
	r[2] += a[2];
	r[3] += a[3];
}
