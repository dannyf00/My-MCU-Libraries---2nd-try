#ifndef TMROC3_H_INCLUDED
#define TMROC3_H_INCLUDED

//#include <p24fxxxx.h>					//we use pic24f
#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines
//define timing constants
#define TMROC_ms					(F_CPU / 1000)	//1ms
#define TMROC_1ms					(TMROC_ms * 1)
//#define TMROC_10ms					(TMROC_ms * 10)

#define TMROC_PS_1x					1			//not actually used by the code
#define TMROC_PS_10x				10			//not actually used by the code
#define TMROC_PS_100x				100			//not actually used by the code
#define TMROC_PS_1000x				1000		//not actually used by the code
#define TMROC_PS_10000x				10000		//not actually used by the code
#define TMROC_PS_2x					2			//not actually used by the code
#define TMROC_PS_4x					4			//not actually used by the code
#define TMROC_PS_8x					8			//not actually used by the code
#define TMROC_PS_16x				16			//not actually used by the code
#define TMROC_PS_32x				32			//not actually used by the code
#define TMROC_PS_64x				64			//not actually used by the code
#define TMROC_PS_128x				128			//not actually used by the code
#define TMROC_PS_256x				256			//not actually used by the code

//global variables

//initialize oc1 as timer
void tmroc3_init(unsigned short ps, unsigned short period);

//activate user isr
void tmroc3_act(void (*isr_ptr)(void));

#endif // TMROC2_H_INCLUDED
