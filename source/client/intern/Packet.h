#ifndef PACKET_H
#define PACKET_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	HEADER_GC_TARGET_UPDATE = 123,
	HEADER_GC_TARGET_DELETE = 124,
	HEADER_GC_TARGET_CREATE_NEW = 125,
};

#ifdef __cplusplus
}
#endif

#endif // PACKET_H
