#ifndef KER_MAIN_H
#define KER_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Main {
	struct Main *prev, *next;
} Main;

#ifdef __cplusplus
}
#endif

#endif // KER_MAIN_H
