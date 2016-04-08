#ifndef BULLET_H
#define BULLET_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------
#define BULLET_MAX_CNT					3


//---------------------------------------------------------------------------

typedef struct {
	bool isUse;
	s16  life;
	s16  fx;
	s16  fy;
	s16  fmx;
	s16  fmy;
} ST_BULLET_DATA;

typedef struct {

	// Chr—p
	u8 cnt;
	ST_BULLET_DATA d[BULLET_MAX_CNT];

	// Ufo—p
	ST_BULLET_DATA u;

} ST_BULLET;

//---------------------------------------------------------------------------
void BulletInit(void);

void BulletExec(void);
void BulletExecChr(void);
void BulletExecUfo(void);

void BulletDraw(void);
void BulletDrawChr(void);
void BulletDrawUfo(void);

void BulletFireChr(s16 fx, s16 fy, s16 fmx, s16 fmy);
void BulletFireUfo(s16 fx, s16 fy, s16 fmx, s16 fmy);

bool BulletIsUseUfo(void);

#ifdef __cplusplus
}
#endif
#endif
