#ifndef UFO_H
#define UFO_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/common.h"

//---------------------------------------------------------------------------
enum {
	UFO_ACT_WAIT,
	UFO_ACT_MOVE,
	UFO_ACT_END,
};


//---------------------------------------------------------------------------

typedef struct {
	u8   act;

	s16  wait;
	s16  fx;
	s16  fy;
	s16  fmx;

} ST_UFO;


//---------------------------------------------------------------------------
void UfoInit(void);
void UfoExec(void);
void UfoDraw(void);
bool UfoHit(s16 x, s16 y);

void UfoSetWait(void);
bool UfoIsEnd(void);


#ifdef __cplusplus
}
#endif
#endif
