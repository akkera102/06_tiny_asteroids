#ifndef CHR_H
#define CHR_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

typedef struct {
	s16  fx;
	s16  fy;
	s16  fmx;
	s16  fmy;
	u8   dir;
	bool isWarp;
	bool isEnd;
} ST_CHR;



//---------------------------------------------------------------------------
void ChrInit(void);

void ChrExec(void);
void ChrExecKey(void);
void ChrExecMove(void);
void ChrExecAccel(void);
void ChrExecFire(void);
void ChrExecHit(void);

void ChrDraw(void);

void ChrWarpOut(void);
bool ChrIsWarp(void);
bool ChrIsEnd(void);


#ifdef __cplusplus
}
#endif
#endif
