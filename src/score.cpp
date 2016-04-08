#include "score.h"
#include "lib/eep.h"
#include "lib/rnd.h"
#include "lib/oled.h"

//---------------------------------------------------------------------------
ST_SCORE Score;


//---------------------------------------------------------------------------
void ScoreInit(void)
{
	_Memset(&Score, 0x00, sizeof(ST_SCORE));

//	ScoreDebug();
	ScoreInitRnd();
	ScoreLoadBest();
}
//---------------------------------------------------------------------------
void ScoreInitRnd(void)
{
	EepSeek(0x10);
	u32 r = EepRead32();

	if(r != 0)
	{
		RndInitSeed(r);
	}

	EepSeek(0x10);
	EepWrite32(Rnd32());
}
//---------------------------------------------------------------------------
void ScoreDraw(void)
{
	OledDrawStr(18, 7, "%3d", Score.now);
}
//---------------------------------------------------------------------------
void ScoreSaveBest(void)
{
	if(Score.best > Score.now)
	{
		return;
	}
	Score.best = Score.now;


	EepSeek(0);

	EepWrite8('A');
	EepWrite8('S');
	EepWrite8('T');
	EepWrite8('E');

	EepWrite16(Score.best);
}
//---------------------------------------------------------------------------
void ScoreLoadBest(void)
{
	Score.best = 0;


	EepSeek(0);

	if(EepRead8() != 'A') return;
	if(EepRead8() != 'S') return;
	if(EepRead8() != 'T') return;
	if(EepRead8() != 'E') return;

	Score.best = EepRead16();
}
//---------------------------------------------------------------------------
void ScoreAddNow(u8 num)
{
	Score.now += num;
}
//---------------------------------------------------------------------------
u16 ScoreGetBest(void)
{
	return Score.best;
}
//---------------------------------------------------------------------------
void ScoreDebug(void)
{
	EepSeek(0);
	EepWrite32(0);
	EepWrite16(0);

	EepSeek(0x10);
	EepWrite32(0);
}
