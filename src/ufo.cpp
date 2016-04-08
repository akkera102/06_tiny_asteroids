#include "ufo.h"
#include "lib/rnd.h"
#include "res.h"
#include "bullet.h"
#include "score.h"
#include "beep.h"

//---------------------------------------------------------------------------
ST_UFO Ufo;


//---------------------------------------------------------------------------
void UfoInit(void)
{
	_Memset(&Ufo, 0x00, sizeof(ST_UFO));
}
//---------------------------------------------------------------------------
void UfoExec(void)
{
	switch(Ufo.act)
	{
	case UFO_ACT_END:
		// EMPTY
		break;

	case UFO_ACT_WAIT:
		if(Ufo.wait-- <= 0)
		{
			Ufo.act  = UFO_ACT_MOVE;
		}
		break;

	case UFO_ACT_MOVE:
		// ’e
		if(BulletIsUseUfo() == FALSE)
		{
			s16 fmx = (Rnd(50) + 20) * (RndIsBool() == TRUE ? 1 : -1);
			s16 fmy = (Rnd(50) + 20) * (RndIsBool() == TRUE ? 1 : -1);

			BulletFireUfo(Ufo.fx, Ufo.fy, fmx, fmy);
		}

		// ˆÚ“®
		Ufo.fx += Ufo.fmx;

		if(FIX2NUM(Ufo.fx) < -4 || FIX2NUM(Ufo.fx) > 128+4)
		{
			Ufo.act  = UFO_ACT_END;
		}
		break;

	default:
		ERROR(Ufo.act);
		break;
	}
}
//---------------------------------------------------------------------------
void UfoDraw(void)
{
	if(Ufo.act == UFO_ACT_MOVE)
	{
		ResDrawUfo(FIX2NUM(Ufo.fx) - 4, FIX2NUM(Ufo.fy) - 4);
	}
}
//---------------------------------------------------------------------------
bool UfoHit(s16 x, s16 y)
{
	if(Ufo.act != UFO_ACT_MOVE)
	{
		return FALSE;
	}

	s16 ux = FIX2NUM(Ufo.fx);
	s16 uy = FIX2NUM(Ufo.fy);

	if(y > uy-4 && y < uy+4 && x > ux-4 && x < ux+4)
	{
		Ufo.act = UFO_ACT_END;

		return TRUE;
	}

	return FALSE;
}
//---------------------------------------------------------------------------
void UfoSetWait(void)
{
	bool is = RndIsBool();

	Ufo.act  = UFO_ACT_WAIT;
	Ufo.wait = 60 + Rnd(60);
	Ufo.fx   = ((is == TRUE) ? NUM2FIX(-4) : NUM2FIX(128 + 4));
	Ufo.fmx  = ((is == TRUE) ? 40 : -40);
	Ufo.fy   = NUM2FIX(4 + Rnd(64 - 8));
}
//---------------------------------------------------------------------------
bool UfoIsEnd(void)
{
	return (Ufo.act == UFO_ACT_END) ? TRUE : FALSE;
}
