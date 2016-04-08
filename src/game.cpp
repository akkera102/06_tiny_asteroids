#include "game.h"
#include "lib/key.h"
#include "lib/oled.h"
#include "ast.h"
#include "chr.h"
#include "beep.h"
#include "res.h"
#include "score.h"
#include "bullet.h"
#include "ufo.h"

//---------------------------------------------------------------------------
ST_GAME Game;


//---------------------------------------------------------------------------
void GameInit(void)
{
	_Memset(&Game, 0x00, sizeof(ST_GAME));
}
//---------------------------------------------------------------------------
void GameLoop(void)
{
	switch(Game.act)
	{
	case GAME_ACT_RESET: GameExecReset(); break;
	case GAME_ACT_DISP:  GameExecDisp();  break;
	case GAME_ACT_PLAY:  GameExecPlay();  break;
	case GAME_ACT_WARP:  GameExecWarp();  break;
	case GAME_ACT_OVER:  GameExecOver();  break;

	default:
		ERROR(Game.act);
		break;
	}
}
//---------------------------------------------------------------------------
void GameExecReset(void)
{
	BeepInit();
	ScoreInit();
	ResInit();

	AstInit();
	ChrInit();
	UfoInit();
	BulletInit();

	GameSetAct(GAME_ACT_DISP);
}
//---------------------------------------------------------------------------
void GameExecDisp(void)
{
	ChrDraw();
	BulletDraw();
	ScoreDraw();

	ChrExec();
	BulletExec();

	OledDrawStr(0, 7, "WAVE %d/%d  ", AstGetWave() + 1, AstGetWaveMax());

	if(Game.cnt++ >= 200)
	{
		AstAddWave();
		AstSetWave();
		UfoSetWait();

		GameSetAct(GAME_ACT_PLAY);
	}
}
//---------------------------------------------------------------------------
void GameExecPlay(void)
{
	ScoreDraw();

	AstDraw();
	ChrDraw();
	UfoDraw();
	BulletDraw();

	AstExec();
	ChrExec();
	UfoExec();
	BulletExec();

	if(ChrIsEnd() == TRUE)
	{
		GameSetAct(GAME_ACT_OVER);
	}
	else if(ChrIsWarp() == TRUE)
	{
		GameSetAct(GAME_ACT_WARP);
	}
	else if(AstIsEndCnt() == TRUE && UfoIsEnd() == TRUE)
	{
		if(AstIsEndWave() == TRUE)
		{
			GameSetAct(GAME_ACT_OVER);
		}
		else
		{
			GameSetAct(GAME_ACT_DISP);
		}
	}
}
//---------------------------------------------------------------------------
void GameExecWarp(void)
{
	ScoreDraw();

	AstDraw();
	UfoDraw();
	BulletDraw();

	AstExec();
	UfoExec();
	BulletExec();


	if(Game.cnt++ > 60)
	{
		ChrWarpOut();

		GameSetAct(GAME_ACT_PLAY);
	}
}
//---------------------------------------------------------------------------
void GameExecOver(void)
{
	ScoreDraw();

	AstDraw();
	UfoDraw();
	BulletDraw();

	AstExec();
	UfoExec();
	BulletExec();


	if(AstIsEndWave() == TRUE && AstIsEndCnt() == TRUE)
	{
		OledDrawStr(0, 6, "GAME CLEAR");
	}
	else
	{
		OledDrawStr(0, 6, "GAME OVER");
	}
	OledDrawStr(0, 7, "BEST %d", ScoreGetBest());


	if(KeyGetTrg() & KEY_D)
	{
		ScoreSaveBest();

		GameSetAct(GAME_ACT_RESET);
	}
}
//---------------------------------------------------------------------------
void GameSetAct(u8 act)
{
	Game.act = act;
	Game.cnt = 0;
}
