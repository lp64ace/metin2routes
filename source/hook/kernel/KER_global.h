#ifndef KER_GLOBAL_H
#define KER_GLOBAL_H

#include "KER_main.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Global {
	char m2_folder[1024];
	char m2_client[1024];

	char auth_channel[1024];
	char auth_username[1024];
	char auth_password[1024];

	struct {
		struct {
			char host[24];
			int port;
		} Server;

		struct {
			char host[24];
			int port;
		} Auth;
	} Raventor_V2;

	Main *main;
} Global;

/** Global options regarding the application, the only global variable allowed. */
extern Global G;
#define G_MAIN (G.main)

void KER_globals_init();
void KER_globals_exit();

void KER_globals_main_replace(Main *main);
void KER_globals_launch_opt_init();

#ifdef __cplusplus
}
#endif

#endif // KER_GLOBAL_H
