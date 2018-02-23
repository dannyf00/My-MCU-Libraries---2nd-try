#ifndef __RTC0_H
#define __RTC0_H

//for calling programs
extern void (*_tmr0_isr_ptr)(void);				//isr handler
extern unsigned long _rtc0_count;			//reset isr count
extern unsigned long _rtc0_trigger;	//rtc defaults to 1 cal per 1000ms

//tmr0 prescaler
#define TMR0_PS_1x			0xff
#define TMR0_PS_2x			0x00
#define TMR0_PS_4x			0x01
#define TMR0_PS_8x			0x02
#define TMR0_PS_16x			0x03
#define TMR0_PS_32x			0x04
#define TMR0_PS_64x			0x05
#define TMR0_PS_128			0x06
#define TMR0_PS_256x		0x07

//for compatibility
#define TMR0IF				T0IF
#define TMR0IE				T0IE

//rtc timing constant
#define RTC_10000ms			(F_CPU / 1000 * 10000)	//1ms * 10000
#define RTC_5000ms			(F_CPU / 1000 * 5000)	//1ms * 5000
#define RTC_2000ms			(F_CPU / 1000 * 2000)	//1ms * 2000
#define RTC_1000ms			(F_CPU / 1000 * 1000)	//1ms * 1000
#define RTC_500ms			(F_CPU / 1000 * 500)	//1ms * 1000
#define RTC_250ms			(F_CPU / 1000 * 250)	//1ms * 250
#define RTC_100ms			(F_CPU / 1000 * 100)	//1ms * 100
#define RTC_50ms			(F_CPU / 1000 * 50)		//1ms * 50
#define RTC_33ms			(F_CPU / 1000 * 33)		//1ms * 33
#define RTC_25ms			(F_CPU / 1000 * 25)		//1ms * 25
#define RTC_10ms			(F_CPU / 1000 * 10)		//1ms * 10
#define RTC_5ms				(F_CPU / 1000 * 5)		//1ms * 5
#define RTC_2ms				(F_CPU / 1000 * 2)		//1ms * 2
#define RTC_1ms				(F_CPU / 1000 * 1)		//1ms * 1

//tmr0 error term
//use a positive number if tmr0 is too fast
//use a negative number if tmr0 is too slow
#define RTC0_ERROR			0					

typedef struct {
	unsigned char half_sec;
	unsigned char sec;
	unsigned char min;
	unsigned char hour;
	unsigned char day;
} RTC_TIME;

extern volatile RTC_TIME _rtc0;					//time keep for rtc0

//initialize the timer
void rtc0_init(unsigned long period);

//activate the isr handler
void rtc0_act(void (*isr_ptr)(void));

//update rtc0
void rtc0_update(void);

#endif
