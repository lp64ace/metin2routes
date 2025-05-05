#ifndef KER_MAIN_H
#define KER_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Main {
	struct Main *prev, *next;

	bool is_global;

	struct CPythonNetworkStream *rkNetStream;
} Main;

Main *KER_main_init();
void KER_main_free(Main *main);

#ifdef __cplusplus
}
#endif

#endif // KER_MAIN_H
