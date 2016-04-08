#ifndef GAME_H
#define GAME_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------
enum {
	GAME_ACT_RESET,
	GAME_ACT_DISP,
	GAME_ACT_PLAY,
	GAME_ACT_WARP,
	GAME_ACT_OVER,
};

//---------------------------------------------------------------------------

typedef struct {
	u8 act;
	u8 cnt;

} ST_GAME;



//---------------------------------------------------------------------------
void GameInit(void);
void GameLoop(void);

void GameExecReset(void);
void GameExecDisp(void);
void GameExecPlay(void);
void GameExecWarp(void);
void GameExecOver(void);

void GameSetAct(u8 act);


#ifdef __cplusplus
}
#endif
#endif
