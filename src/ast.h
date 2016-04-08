#ifndef AST_H
#define AST_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------
#define AST_MAX_WAVE		5
#define AST_MAX_CNT			((AST_MAX_WAVE) * 4 + 4)

//---------------------------------------------------------------------------

typedef struct {
	bool isUse;
	u8   type;
	s8   step;
	s8   r;
	s16  fx;
	s16  fy;
	s16  fmx;
	s16  fmy;
} ST_AST_DATA;

typedef struct {

	s8 cnt;
	ST_AST_DATA d[AST_MAX_CNT];

	s8 wave;

} ST_AST;


//---------------------------------------------------------------------------
void AstInit(void);
void AstExec(void);
void AstDraw(void);
bool AstHit(s16 x, s16 y);

void AstSetWave(void);
void AstSetUnit(u8 num, s8 x, s8 y, u8 type, u8 step);
void AstSetUnit2(s8 x, s8 y, u8 type, u8 step);

void AstAddWave(void);
u8   AstGetWave(void);
u8   AstGetWaveMax(void);
bool AstIsEndCnt(void);
bool AstIsEndWave(void);

#ifdef __cplusplus
}
#endif
#endif
