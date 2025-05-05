#ifndef C_ACTOR_INSTANCE_H
#define C_ACTOR_INSTANCE_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CActorInstance CActorInstance;

void CActorInstance_Hook();
void CActorInstance_Restore();

/* -------------------------------------------------------------------- */
/** \name Offset Resolve
 * \{ */

enum {
	ACTOR_ENEMY,
	ACTOR_NPC,
	ACTOR_STONE,
	ACTOR_WARP,
	ACTOR_DOOR,
	ACTOR_BUILDING,
	ACTOR_PC,
	ACTOR_POLY,
	ACTOR_HORSE,
	ACTOR_GOTO,
};

unsigned int *CActorInstance_mEActorType(CActorInstance *me);
unsigned long *CActorInstance_mDwSelfVID(CActorInstance *me);

/** \} */

#ifdef __cplusplus
}
#endif

#endif // C_ACTOR_INSTANCE_H
