#include "res.h"
#include "res/img.h"
#include "lib/oled.h"


//---------------------------------------------------------------------------
const unsigned char* ResChrList[] = {
	bmpChr00,
	bmpChr01,
	bmpChr02,
	bmpChr03,
	bmpChr04,
	bmpChr05,
	bmpChr06,
	bmpChr07,
	bmpChr08,
	bmpChr09,
	bmpChr10,
	bmpChr11,
	bmpChr12,
	bmpChr13,
	bmpChr14,
	bmpChr15,
};

const unsigned char* ResAstList[] = {
	bmpAst0a,
	bmpAst0b,
	bmpAst0c,
	bmpAst1a,
	bmpAst1b,
	bmpAst1c,
	bmpAst2a,
	bmpAst2b,
	bmpAst2c,
	bmpAst3a,
	bmpAst3b,
	bmpAst3c,
};

//---------------------------------------------------------------------------
void ResInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
void ResDrawChr(s8 x, s8 y, u8 num)
{
	ASSERT(num < 16);

	OledDrawBmp(x, y, (u8*)ResChrList[num]);
}
//---------------------------------------------------------------------------
void ResDrawAst(s8 x, s8 y, u8 type, u8 size)
{
	ASSERT(type < 4 && size < 3);

	OledDrawBmp(x, y, (u8*)ResAstList[type * 3 + size]);
}
//---------------------------------------------------------------------------
void ResDrawUfo(s8 x, s8 y)
{
	OledDrawBmp(x, y, (u8*)bmpUfo);
}
//---------------------------------------------------------------------------
void ResDrawBullet(s8 x, s8 y)
{
	OledDrawDot(x, y);
}
