#include "chr.h"
#include <avr/pgmspace.h>
#include "lib/key.h"
#include "lib/frame.h"
#include "lib/rnd.h"
#include "res.h"
#include "bullet.h"
#include "beep.h"
#include "ast.h"

//---------------------------------------------------------------------------
// ‰Á‘¬
PROGMEM const s8 ChrAccelTable[32] = {
//   x   y
	 0, -8,
	 3, -7,
	 6, -6,
	 7, -3,
	 8,  0,
	 7,  3,
	 6,  6,
	 3,  7,
	 0,  8,
	-3,  7,
	-6,  6,
	-7,  3,
	-8,  0,
	-7, -3,
	-6, -6,
	-3, -7,
};

// ”­ŽËˆÊ’u
PROGMEM const s8 ChrFireTable[32] = {
//   x   y
	 0, -5,
	 2, -5,
	 3, -4,
	 4, -1,
	 4,  0,
	 4,  2,
	 3,  4,
	 2,  4,
	-1,  4,
	-3,  4,
	-4,  4,
	-5,  1,
	-5, -1,
	-5, -2,
	-4, -4,
	-3, -5,
};

//---------------------------------------------------------------------------
ST_CHR Chr;


//---------------------------------------------------------------------------
void ChrInit(void)
{
	_Memset(&Chr, 0x00, sizeof(ST_CHR));

	Chr.fx = NUM2FIX(64);
	Chr.fy = NUM2FIX(32);
}
//---------------------------------------------------------------------------
void ChrExec(void)
{
	ChrExecKey();
	ChrExecMove();
	ChrExecHit();
}
//---------------------------------------------------------------------------
void ChrExecKey(void)
{
	u8 rep = KeyGetRep();
	u8 trg = KeyGetTrg();

	if(rep & KEY_L)
	{
		Chr.dir = (Chr.dir - 1) & 0xf;
	}

	if(rep & KEY_R)
	{
		Chr.dir = (Chr.dir + 1) & 0xf;
	}

	if(rep & KEY_B)
	{
		ChrExecAccel();
	}

	if(trg & KEY_A)
	{
		ChrExecFire();
	}

	if(trg & KEY_U)
	{
		Chr.isWarp = TRUE;
	}
}
//---------------------------------------------------------------------------
void ChrExecMove(void)
{
	Chr.fx = _MoveFx(Chr.fx, Chr.fmx);
	Chr.fy = _MoveFy(Chr.fy, Chr.fmy);


	if(FrameIsMod(20) == FALSE)
	{
		return;
	}

	if(Chr.fmx != 0)
	{
		if(Chr.fmx > 0) Chr.fmx--;
		else            Chr.fmx++;
	}

	if(Chr.fmy != 0)
	{
		if(Chr.fmy > 0) Chr.fmy--;
		else            Chr.fmy++;
	}
}
//---------------------------------------------------------------------------
void ChrExecAccel(void)
{
	if(Chr.fmx >= 200 || Chr.fmx <= -200)
	{
		return;
	}

	if(Chr.fmy >= 200 || Chr.fmy <= -200)
	{
		return;
	}

	Chr.fmx += (s8)__LPM(ChrAccelTable + Chr.dir * 2 + 0);
	Chr.fmy += (s8)__LPM(ChrAccelTable + Chr.dir * 2 + 1);
}
//---------------------------------------------------------------------------
void ChrExecFire(void)
{
	s16 fx  = Chr.fx  + NUM2FIX((s8)__LPM(ChrFireTable + Chr.dir * 2 + 0));
	s16 fy  = Chr.fy  + NUM2FIX((s8)__LPM(ChrFireTable + Chr.dir * 2 + 1));
	s16 fmx = Chr.fmx + (s8)__LPM(ChrAccelTable + Chr.dir * 2 + 0) * 15;
	s16 fmy = Chr.fmy + (s8)__LPM(ChrAccelTable + Chr.dir * 2 + 1) * 15;

	BulletFireChr(fx, fy, fmx, fmy);
}
//---------------------------------------------------------------------------
void ChrExecHit(void)
{
	Chr.isEnd = AstHit(FIX2NUM(Chr.fx), FIX2NUM(Chr.fy));

	if(Chr.isEnd == TRUE)
	{
		BeepPlayHitChr();
	}
}
//---------------------------------------------------------------------------
void ChrDraw(void)
{
	ResDrawChr(FIX2NUM(Chr.fx) - 8, FIX2NUM(Chr.fy) - 8, Chr.dir);
}
//---------------------------------------------------------------------------
void ChrWarpOut(void)
{
	Chr.fx  = NUM2FIX(Rnd(128 - 16) + 8);
	Chr.fy  = NUM2FIX(Rnd( 64 - 16) + 8);
	Chr.fmx = 0;
	Chr.fmy = 0;

	Chr.isWarp = FALSE;
}
//---------------------------------------------------------------------------
bool ChrIsWarp(void)
{
	return Chr.isWarp;
}
//---------------------------------------------------------------------------
bool ChrIsEnd(void)
{
	return Chr.isEnd;
}
