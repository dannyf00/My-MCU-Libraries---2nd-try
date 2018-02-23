#ifndef __RTC1_H
#define __RTC1_H

//for calling programs
extern void (*_tmr1_isr_ptr)(void);			//tmr1 isr handler pointer
extern unsigned long _rtc1_count;			//tmr1 isr counter
extern unsigned long _rtc1_trigger;			//tmr1's period


//tmr1 prescaler
#define TMR1_PS_1x			0x00
#define TMR1_PS_2x			0x01
#define TMR1_PS_4x			0x02
#define TMR1_PS_8x			0x03

//rtc timing constant
#define RTC_10000ms			(RTC_ms * 10000)	//1ms * 10000
#define RTC_5000ms			(RTC_ms * 5000)	//1ms * 5000
#define RTC_2000ms			(RTC_ms * 2000)	//1ms * 2000
#define RTC_1000ms			(RTC_ms * 1000)	//1ms * 1000
#define RTC_500ms			(RTC_ms * 500)	//1ms * 1000
#define RTC_250ms			(RTC_ms * 250)	//1ms * 250
#define RTC_100ms			(RTC_ms * 100)	//1ms * 100
#define RTC_ms				(F_CPU / 1000)		//ms definition


//tmr1 error term
//use a positive number if tmr0 is too fast
//use a negative number if tmr0 is too slow
#define RTC1_ERROR			0					

typedef struct {
	unsigned char half_sec;
	unsigned char sec;
	unsigned char min;
	unsigned char hour;
	unsigned char day;
} RTC_TIME;

extern volatile RTC_TIME _rtc1;

//initialize the timer
void rtc1_init(unsigned long period);

//activate the isr handler
void rtc1_act(void (*isr_ptr)(void));

//update rtc1
void rtc1_update(void);

#endif RTC1_H_
