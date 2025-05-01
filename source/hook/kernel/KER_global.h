#ifndef KER_GLOBAL_H
#define KER_GLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Global {
	char m2_folder[1024];
	char m2_client[1024];
} Global;

/** Global options regarding the application, the only global variable allowed. */
extern Global G;

void KER_globals_init();
void KER_globals_exit();

void KER_globals_launch_opt_init();

#ifdef __cplusplus
}
#endif

#endif // KER_GLOBAL_H
