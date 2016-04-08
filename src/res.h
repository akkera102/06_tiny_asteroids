#ifndef RES_H
#define RES_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void ResInit(void);

void ResDrawChr(s8 x, s8 y, u8 num);
void ResDrawAst(s8 x, s8 y, u8 type, u8 size);
void ResDrawUfo(s8 x, s8 y);
void ResDrawBullet(s8 x, s8 y);

#ifdef __cplusplus
}
#endif
#endif
