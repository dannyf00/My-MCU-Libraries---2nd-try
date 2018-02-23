#ifndef TMR4_H_
#define TMR4_H_

//#include <p32xxxx.h>					//we use htc compiler
#include "gpio.h"

//for calling programs
//extern void (*_tmr1_isr_ptr)(void);			//tmr1 isr handler pointer
//extern unsigned long _rtc1_count;			//tmr1 isr counter
//extern unsigned long _rtc1_trigger;			//tmr1's period


//tmr2/3/4/5 prescaler
#define TMR_PS_1x			0x00
#define TMR_PS_2x			0x01
#define TMR_PS_4x			0x02
#define TMR_PS_8x			0x03
#define TMR_PS_16x			0x04
#define TMR_PS_32x			0x05
#define TMR_PS_64x			0x06
#define TMR_PS_256x			0x07
#define TMR_PS_MASK			TMR_PS_256x


//rtc timing constant
#define TMR_10000ms			(TMR_ms * 10000)	//1ms * 10000
#define TMR_5000ms			(TMR_ms * 5000)		//1ms * 5000
#define TMR_2000ms			(TMR_ms * 2000)		//1ms * 2000
#define TMR_1000ms			(TMR_ms * 1000)		//1ms * 1000
#define TMR_500ms			(TMR_ms * 500)		//1ms * 1000
#define TMR_200ms			(TMR_ms * 200)		//1ms * 200
#define TMR_100ms			(TMR_ms * 100)		//1ms * 100
#define TMR_50ms			(TMR_ms * 50)		//1ms * 50
#define TMR_20ms			(TMR_ms * 20)		//1ms * 20
#define TMR_10ms			(TMR_ms * 10)		//1ms * 10
#define TMR_5ms				(TMR_ms * 5)		//1ms * 5
#define TMR_2ms				(TMR_ms * 2)		//1ms * 2
#define TMR_1ms				(TMR_ms * 1)		//1ms * 1
#define TMR_ms				(F_PB / 1000)		//ms definition



//tmr1 error term
//use a positive number if tmr0 is too fast
//use a negative number if tmr0 is too slow
#define RTC1_ERROR			0


//initialize the timer
void tmr4_init(unsigned char ps, unsigned short period);

//activate the isr handler
void tmr4_act(void (*isr_ptr)(void));

#endif //tmr1_h_
