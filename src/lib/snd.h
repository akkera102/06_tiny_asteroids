#ifndef SND_H
#define SND_H
#ifdef __cplusplus
extern "C" {
#endif


// ch0 timer3(16bit) pin:A2
// ch1 timer1(16bit) pin:A3

// ISR(TIMER3_COMPA_vect)
// ISR(TIMER1_COMPA_vect)


#include <pins_arduino.h>
#include "common.h"

//---------------------------------------------------------------------------
#define SND_MAX_CH				2
#define SND_PIN_CH1				A2		// pins_arduino.h
#define SND_PIN_CH2				A3


//---------------------------------------------------------------------------

typedef struct {
	vu8* pPort;
	u8   mask;
} ST_SND_PIN;

typedef struct {
	bool isPlay;
	u32  cnt;
} ST_SND_TONE;


typedef struct {

	ST_SND_TONE t[SND_MAX_CH];
	ST_SND_PIN  p[SND_MAX_CH];

} ST_SND;


//---------------------------------------------------------------------------
void SndInit(void);

void SndPlay(u8 ch, u16 freq, u16 duration);
void SndStartTimer(u8 ch, u32 freq);
void SndStopTimer(u8 ch);


#ifdef __cplusplus
}
#endif
#endif
