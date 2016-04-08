#include "bullet.h"
#include "beep.h"
#include "res.h"
#include "ast.h"
#include "ufo.h"
#include "score.h"

//---------------------------------------------------------------------------
ST_BULLET Bullet;


//---------------------------------------------------------------------------
void BulletInit(void)
{
	_Memset(&Bullet, 0x00, sizeof(ST_BULLET));
}
//---------------------------------------------------------------------------
void BulletExec(void)
{
	BulletExecChr();
	BulletExecUfo();
}
//---------------------------------------------------------------------------
void BulletExecChr(void)
{
	u8 i;

	for(i=0; i<BULLET_MAX_CNT; i++)
	{
		ST_BULLET_DATA* p = &Bullet.d[i];

		if(p->isUse == FALSE)
		{
			continue;
		}

		if(p->life-- < 0)
		{
			p->isUse = FALSE;
			Bullet.cnt--;

			continue;
		}

		if(AstHit(FIX2NUM(p->fx), FIX2NUM(p->fy)) == TRUE)
		{
			p->isUse = FALSE;
			Bullet.cnt--;

			BeepPlayHitAst();
			ScoreAddNow(1);

			continue;
		}

		if(UfoHit(FIX2NUM(p->fx), FIX2NUM(p->fy)) == TRUE)
		{
			p->isUse = FALSE;
			Bullet.cnt--;

			BeepPlayHitUfo();
			ScoreAddNow(10);

			continue;
		}

		p->fx = _MoveFx(p->fx, p->fmx);
		p->fy = _MoveFy(p->fy, p->fmy);
	}
}
//---------------------------------------------------------------------------
void BulletExecUfo(void)
{
	ST_BULLET_DATA* p = &Bullet.u;

	if(p->isUse == FALSE)
	{
		return;
	}

	if(p->life-- < 0)
	{
		p->isUse = FALSE;

		return;
	}

	if(AstHit(FIX2NUM(p->fx), FIX2NUM(p->fy)) == TRUE)
	{
		p->isUse = FALSE;
		BeepPlayHitAst();

		return;
	}

	p->fx = _MoveFx(p->fx, p->fmx);
	p->fy = _MoveFy(p->fy, p->fmy);
}
//---------------------------------------------------------------------------
void BulletDraw(void)
{
	BulletDrawChr();
	BulletDrawUfo();
}
//---------------------------------------------------------------------------
void BulletDrawChr(void)
{
	u8 i;

	for(i=0; i<BULLET_MAX_CNT; i++)
	{
		if(Bullet.d[i].isUse == TRUE)
		{
			ResDrawBullet(FIX2NUM(Bullet.d[i].fx), FIX2NUM(Bullet.d[i].fy));
		}
	}
}
//---------------------------------------------------------------------------
void BulletDrawUfo(void)
{
	if(Bullet.u.isUse == TRUE)
	{
		ResDrawBullet(FIX2NUM(Bullet.u.fx), FIX2NUM(Bullet.u.fy));
	}
}
//---------------------------------------------------------------------------
void BulletFireChr(s16 fx, s16 fy, s16 fmx, s16 fmy)
{
	if(Bullet.cnt >= BULLET_MAX_CNT)
	{
		return;
	}


	u8 i;

	for(i=0; i<BULLET_MAX_CNT; i++)
	{
		ST_BULLET_DATA* p = &Bullet.d[i];

		if(p->isUse == TRUE)
		{
			continue;
		}

		p->life  = 40;
		p->fx    = fx;
		p->fy    = fy;
		p->fmx   = fmx;
		p->fmy   = fmy;
		p->isUse = TRUE;
		Bullet.cnt++;

		BeepPlayFire();

		return;
	}
}
//---------------------------------------------------------------------------
void BulletFireUfo(s16 fx, s16 fy, s16 fmx, s16 fmy)
{
	ST_BULLET_DATA* p = &Bullet.u;

	p->life  = 60;
	p->fx    = fx;
	p->fy    = fy;
	p->fmx   = fmx;
	p->fmy   = fmy;
	p->isUse = TRUE;
}
//---------------------------------------------------------------------------
bool BulletIsUseUfo(void)
{
	return Bullet.u.isUse;
}
