#ifndef __RTC2_H
#define __RTC2_H

#include "gpio.h"								//we use gpio

//for calling programs
//extern void (*_tmr1_isr_ptr)(void);			//tmr1 isr handler pointer
//extern unsigned long _rtc1_count;			//tmr1 isr counter
//extern unsigned long _rtc1_trigger;			//tmr1's period


#ifndef _RTC_H
#define _RTC_H
//tmr1 prescaler
#define TMR_PS_1x			0x00
#define TMR_PS_8x			0x01
#define TMR_PS_64x			0x02
#define TMR_PS_256x			0x03
#define TMR_PS_MASK			TMR_PS_256x				//mask for tmr_ps

//rtc timing constant
#define RTC_10000ms			(RTC_ms * 10000)	//1ms * 10000
#define RTC_5000ms			(RTC_ms * 5000)		//1ms * 5000
#define RTC_2000ms			(RTC_ms * 2000)		//1ms * 2000
#define RTC_1000ms			(RTC_ms * 1000)		//1ms * 1000
#define RTC_500ms			(RTC_ms * 500)		//1ms * 1000
#define RTC_200ms			(RTC_ms * 200)		//1ms * 200
#define RTC_100ms			(RTC_ms * 100)		//1ms * 100
#define RTC_50ms			(RTC_ms * 50)		//1ms * 50
#define RTC_20ms			(RTC_ms * 20)		//1ms * 20
#define RTC_10ms			(RTC_ms * 10)		//1ms * 10
#define RTC_5ms				(RTC_ms * 5)		//1ms * 5
#define RTC_2ms				(RTC_ms * 2)		//1ms * 2
#define RTC_1ms				(RTC_ms * 1)		//1ms * 1
#define RTC_ms				(F_CPU / 1000)		//ms definition


typedef struct {
	unsigned char half_sec;
	unsigned char sec;
	unsigned char min;
	unsigned char hour;
	unsigned char day;
} RTC_TIME;
#endif

extern volatile RTC_TIME _rtc2;				//rtc1's timekeep

//for compatibility reasons

#define _T2ON				T2CONbits.TON
#define _T2CS				T2CONbits.TCS
#define _T2GE				T2CONbits.TGATE
#define _T2CKPS				T2CONbits.TCKPS
#define _T2_32				T2CONbits.T32
#define _T2IE				IEC0bits.T2IE
#define _T2IF				IFS0bits.T2IF			//tmr1 overflow flag

//tmr1 error term
//use a positive number if tmr0 is too fast
//use a negative number if tmr0 is too slow
#define RTC1_ERROR			0


//initialize the timer
void rtc2_init(unsigned long period);

//activate the isr handler
void rtc2_act(void (*isr_ptr)(void));

//update rtc2
void rtc2_update(void);

#endif //rtc2_h_
