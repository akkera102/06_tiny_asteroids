#ifndef SCORE_H
#define SCORE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	u16  best;
	u16  now;

} ST_SCORE;


//---------------------------------------------------------------------------
void ScoreInit(void);
void ScoreInitRnd(void);
void ScoreDraw(void);

void ScoreSaveBest(void);
void ScoreLoadBest(void);
void ScoreAddNow(u8 num);
u16  ScoreGetBest(void);

void ScoreDebug(void);


#ifdef __cplusplus
}
#endif
#endif
