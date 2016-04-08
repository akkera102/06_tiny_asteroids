#ifndef BEEP_H
#define BEEP_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void BeepInit(void);

void BeepPlayFire(void);
void BeepPlayHitChr(void);
void BeepPlayHitAst(void);
void BeepPlayHitUfo(void);


#ifdef __cplusplus
}
#endif
#endif
