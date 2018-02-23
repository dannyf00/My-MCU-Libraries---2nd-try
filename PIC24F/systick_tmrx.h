#ifndef SYSTICK1_H_
#define SYSTICK1_H_

//#include <p24fxxxx.h>					//we use C30 compiler
#include "gpio.h"
//#include "tmr1.h"								//we use tmr1

//hardware configuration
//using tmr1 to simulate systick
//#define tmrx_init			tmr1_init
//#define tmrx_act			tmr1_act
//#define TMRx				TMR1
//#define PRx					PR1
//end hardware configuration

//for calling programs
//extern void (*_tmr1_isr_ptr)(void);			//tmr1 isr handler pointer
//extern unsigned long _rtc1_count;			//tmr1 isr counter
//extern unsigned long _rtc1_trigger;			//tmr1's period

//tmr1 prescaler
#define TMR_PS_1x				0x00
//#define TMR_PS_8x				0x01
//#define TMR_PS_64x			0x02
#define TMR_PS_256x				0x03
#define TMR_PS_MASK				TMR_PS_256x

//rtc timing constant
#define SYSTICK_ms				(F_CPU / 1000ul)		//ms definition
#define SYSTICK_1ms				(SYSTICK_ms * 1)		//1ms * 1
#define SYSTICK_2ms				(SYSTICK_ms * 2)		//1ms * 2
#define SYSTICK_5ms				(SYSTICK_ms * 5)		//1ms * 5
#define SYSTICK_10ms			(SYSTICK_ms * 10)		//1ms * 10
#define SYSTICK_20ms			(SYSTICK_ms * 20)		//1ms * 20
#define SYSTICK_50ms			(SYSTICK_ms * 50)		//1ms * 50
#define SYSTICK_100ms			(SYSTICK_ms * 100)		//1ms * 100
#define SYSTICK_200ms			(SYSTICK_ms * 200)		//1ms * 200
#define SYSTICK_500ms			(SYSTICK_ms * 500)		//1ms * 1000
#define SYSTICK_1000ms			(SYSTICK_ms * 1000)		//1ms * 1000
#define SYSTICK_2000ms			(SYSTICK_ms * 2000)		//1ms * 2000
#define SYSTICK_5000ms			(SYSTICK_ms * 5000)		//1ms * 5000
#define SYSTICK_10000ms			(SYSTICK_ms * 10000)	//1ms * 10000


//initialize the timer
void systick_init(unsigned short period);

//activate the isr handler
void systick_act(void (*isr_ptr)(void));

//read the timer
unsigned long systick_get(void);

#endif //tmr1_h_
