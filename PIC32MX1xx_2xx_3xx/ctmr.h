#ifndef CCTMR_H_							//we use core timer
#define CCTMR_H_

//#include <p32xxxx.h>					//we use htc compiler
#include "gpio.h"

//for calling programs
//extern void (*_tmr1_isr_ptr)(void);			//tmr1 isr handler pointer
//extern unsigned long _rtc1_count;			//tmr1 isr counter
//extern unsigned long _rtc1_trigger;			//tmr1's period


//tmr1 prescaler
#define CTMR_PS_1x			0x00
#define CTMR_PS_8x			0x01
#define CTMR_PS_64x			0x02
#define CTMR_PS_256x			0x03
#define CTMR_PS_MASK			CTMR_PS_256x

//rtc timing constant
#define CTMR_10000ms			(CTMR_ms * 10000)	//1ms * 10000
#define CTMR_5000ms			(CTMR_ms * 5000)		//1ms * 5000
#define CTMR_2000ms			(CTMR_ms * 2000)		//1ms * 2000
#define CTMR_1000ms			(CTMR_ms * 1000)		//1ms * 1000
#define CTMR_500ms			(CTMR_ms * 500)		//1ms * 1000
#define CTMR_200ms			(CTMR_ms * 200)		//1ms * 200
#define CTMR_100ms			(CTMR_ms * 100)		//1ms * 100
#define CTMR_50ms			(CTMR_ms * 50)		//1ms * 50
#define CTMR_20ms			(CTMR_ms * 20)		//1ms * 20
#define CTMR_10ms			(CTMR_ms * 10)		//1ms * 10
#define CTMR_5ms				(CTMR_ms * 5)		//1ms * 5
#define CTMR_2ms				(CTMR_ms * 2)		//1ms * 2
#define CTMR_1ms				(CTMR_ms * 1)		//1ms * 1
#define CTMR_ms				(F_CPU / 2 / 1000)	//ms definition. core timer runs at 1/2 of F_CPU



//tmr1 error term
//use a positive number if tmr0 is too fast
//use a negative number if tmr0 is too slow
#define RTC1_ERROR			0


//initialize the timer
void ctmr_init(unsigned short period);

//activate the isr handler
void ctmr_act(void (*isr_ptr)(void));

#endif //tmr1_h_
