#include "ast.h"
#include <avr/pgmspace.h>
#include "lib/rnd.h"
#include "res.h"

//---------------------------------------------------------------------------
PROGMEM const s8 AstRadiusTable[3] = {
	8,
	4,
	2,
};

//---------------------------------------------------------------------------
ST_AST Ast;


//---------------------------------------------------------------------------
void AstInit(void)
{
	_Memset(&Ast, 0x00, sizeof(ST_AST));
}
//---------------------------------------------------------------------------
void AstExec(void)
{
	u8 i;

	for(i=0; i<AST_MAX_CNT; i++)
	{
		if(Ast.d[i].isUse == TRUE)
		{
			Ast.d[i].fx = _MoveFx(Ast.d[i].fx, Ast.d[i].fmx);
			Ast.d[i].fy = _MoveFy(Ast.d[i].fy, Ast.d[i].fmy);
		}
	}
}
//---------------------------------------------------------------------------
void AstDraw(void)
{
	s8 x, y;
	u8 i;

	for(i=0; i<AST_MAX_CNT; i++)
	{
		if(Ast.d[i].isUse == TRUE)
		{
			x = FIX2NUM(Ast.d[i].fx) - Ast.d[i].r;
			y = FIX2NUM(Ast.d[i].fy) - Ast.d[i].r;

			ResDrawAst(x, y, Ast.d[i].type, Ast.d[i].step);
		}
	}
}
//---------------------------------------------------------------------------
bool AstHit(s16 x, s16 y)
{
	s16 ax, ay, ar, r;
	u8  i;

	for(i=0; i<AST_MAX_CNT; i++)
	{
		if(Ast.d[i].isUse == FALSE)
		{
			continue;
		}

		ax = FIX2NUM(Ast.d[i].fx);
		ay = FIX2NUM(Ast.d[i].fy);
		ar = Ast.d[i].r;
		r  = 1;

		// ‰~“¯Žm‚Ì“–‚½‚è”»’è
		if((x - ax) * (x - ax) + (y - ay) * (y - ay) > (r + ar) * (r + ar))
		{
			continue;
		}

		if(Ast.d[i].step < 2)
		{
			AstSetUnit2(ax, ay, Ast.d[i].type, Ast.d[i].step + 1);
			AstSetUnit2(ax, ay, Ast.d[i].type, Ast.d[i].step + 1);
		}

		Ast.d[i].isUse = FALSE;
		Ast.cnt--;

		return TRUE;
	}

	return FALSE;
}
//---------------------------------------------------------------------------
void AstSetWave(void)
{
	u8 i;

	for(i=0; i<Ast.wave; i++)
	{
		if(RndIsBool() == TRUE)
		{
			AstSetUnit(i, Rnd(128), ((RndIsBool() == TRUE) ? 0 : 63), Rnd(4), 0);
		}
		else
		{
			AstSetUnit(i, ((RndIsBool() == TRUE) ? 0 : 127), Rnd(64), Rnd(4), 0);
		}
	}
}
//---------------------------------------------------------------------------
void AstSetUnit(u8 num, s8 x, s8 y, u8 type, u8 step)
{
	ST_AST_DATA* p = &Ast.d[num];

	p->fx    = NUM2FIX(x);
	p->fy    = NUM2FIX(y);
	p->fmx   = (Rnd((1 + Ast.wave + step) * 4) + (1 + Ast.wave) * 2) * (RndIsBool() == TRUE ? 1 : -1);
	p->fmy   = (Rnd((1 + Ast.wave + step) * 4) + (1 + Ast.wave) * 2) * (RndIsBool() == TRUE ? 1 : -1);
	p->type  = type;
	p->step  = step;
	p->r     = (s8)__LPM(AstRadiusTable + step);
	p->isUse = TRUE;

	Ast.cnt++;
}
//---------------------------------------------------------------------------
void AstSetUnit2(s8 x, s8 y, u8 type, u8 step)
{
	u8 i;

	for(i=0; i<AST_MAX_CNT; i++)
	{
		if(Ast.d[i].isUse == FALSE)
		{
			goto End;
		}
	}

End:
	ASSERT(i < AST_MAX_CNT);

	AstSetUnit(i, x, y, type, step);
}
//---------------------------------------------------------------------------
void AstAddWave(void)
{
	Ast.wave++;
}
//---------------------------------------------------------------------------
u8 AstGetWave(void)
{
	return Ast.wave;
}
//---------------------------------------------------------------------------
u8 AstGetWaveMax(void)
{
	return AST_MAX_WAVE;
}
//---------------------------------------------------------------------------
bool AstIsEndCnt(void)
{
	return (Ast.cnt <= 0) ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
bool AstIsEndWave(void)
{
	return (Ast.wave >= AST_MAX_WAVE) ? TRUE : FALSE;
}
