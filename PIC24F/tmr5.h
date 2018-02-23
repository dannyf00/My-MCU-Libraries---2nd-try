#ifndef TMR5_H_
#define TMR5_H_

//#include <p24fxxxx.h>					//we use htc compiler
#include "gpio.h"

//for calling programs
//extern void (*_tmr1_isr_ptr)(void);			//tmr1 isr handler pointer
//extern unsigned long _rtc1_count;			//tmr1 isr counter
//extern unsigned long _rtc1_trigger;			//tmr1's period


//tmr1 prescaler
#define TMR_PS_1x			0x00
#define TMR_PS_8x			0x01
#define TMR_PS_64x			0x02
#define TMR_PS_256x			0x03
#define TMR_PS_MASK			TMR_PS_256x

//tmr timing constant
#define TMR_10000ms			(TMR_ms * 10000)//1ms * 10000
#define TMR_5000ms			(TMR_ms * 5000)	//1ms * 5000
#define TMR_2000ms			(TMR_ms * 2000)	//1ms * 2000
#define TMR_1000ms			(TMR_ms * 1000)	//1ms * 1000
#define TMR_500ms			(TMR_ms * 500)	//1ms * 1000
#define TMR_200ms			(TMR_ms * 200)	//1ms * 200
#define TMR_100ms			(TMR_ms * 100)	//1ms * 100
#define TMR_50ms			(TMR_ms * 50)	//1ms * 50
#define TMR_20ms			(TMR_ms * 20)	//1ms * 20
#define TMR_10ms			(TMR_ms * 10)	//1ms * 10
#define TMR_5ms				(TMR_ms * 5)	//1ms * 5
#define TMR_2ms				(TMR_ms * 2)	//1ms * 2
#define TMR_1ms				(TMR_ms * 1)	//1ms * 1
#define TMR_ms				(F_CPU / 1000)		//1ms

//for compatibility reasons

#define _T5ON				T5CONbits.TON
#define _T5CS				T5CONbits.TCS
#define _T5GE				T5CONbits.TGATE
#define _T5CKPS				T5CONbits.TCKPS
//#define _T5_32				T2CONbits.T32
#define _T5IE				IEC1bits.T5IE
#define _T5IF				IFS1bits.T5IF			//tmr1 overflow flag

//tmr1 error term
//use a positive number if tmr0 is too fast
//use a negative number if tmr0 is too slow
#define TMR5_ERROR			0


//initialize the timer
void tmr5_init(unsigned char ps);

#define tmr5_setpr(n)		PR5 = (n) - 1

//activate the isr handler
void tmr5_act(void (*isr_ptr)(void));

#endif //tmr5_h_
