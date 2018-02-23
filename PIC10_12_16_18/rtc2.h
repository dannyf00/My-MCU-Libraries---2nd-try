#ifndef __RTC2_H
#define __RTC2_H

//for calling programs
extern void (*_tmr2_isr_ptr)(void);				//isr handler
extern unsigned long _rtc2_count;				//tmr2 isr counter
extern unsigned long _rtc2_trigger;				//tmr2's period

//extern unsigned char tmr2_offset;				//tmr2 offset

//tmr1 prescaler
#define TMR2_PS_1x			0x00				//tmr2 post scaler
#define TMR2_PS_2x			0x10
#define TMR2_PS_3x			0x20
#define TMR2_PS_4x			0x30
#define TMR2_PS_5x			0x40
#define TMR2_PS_6x			0x50
#define TMR2_PS_7x			0x60
#define TMR2_PS_8x			0x70
#define TMR2_PS_9x			0x80
#define TMR2_PS_10x			0x90
#define TMR2_PS_11x			0xa0
#define TMR2_PS_12x			0xb0
#define TMR2_PS_13x			0xc0
#define TMR2_PS_14x			0xd0
#define TMR2_PS_15x			0xe0
#define TMR2_PS_16x			0xf0

#define TMR2_MLT_1x			0x00				//tmr2 multiplier = prescaler
#define TMR2_MLT_4x			0x01
#define TMR2_MLT_16x		0x02

//rtc timing constant
#define RTC_10000ms			(RTC_ms * 10000)	//1ms * 10000
#define RTC_5000ms			(RTC_ms * 5000)	//1ms * 5000
#define RTC_2000ms			(RTC_ms * 2000)	//1ms * 2000
#define RTC_1000ms			(RTC_ms * 1000)	//1ms * 1000
#define RTC_500ms			(RTC_ms * 500)	//1ms * 1000
#define RTC_250ms			(RTC_ms * 250)	//1ms * 250
#define RTC_100ms			(RTC_ms * 100)	//1ms * 100
#define RTC_50ms			(RTC_ms * 50)		//1ms * 50
#define RTC_33ms			(RTC_ms * 33)		//1ms * 33
#define RTC_25ms			(RTC_ms * 25)		//1ms * 25
#define RTC_10ms			(RTC_ms * 10)		//1ms * 10
#define RTC_5ms				(RTC_ms * 5)		//1ms * 5
#define RTC_2ms				(RTC_ms * 2)		//1ms * 2
#define RTC_1ms				(RTC_ms * 1)		//1ms * 1
#define RTC_ms				(F_CPU / 1000)		//ms definition


//tmr2 error term
//use a positive number if tmr0 is too fast
//use a negative number if tmr0 is too slow
#define RTC2_ERROR			0					

typedef struct {
	unsigned char half_sec;
	unsigned char sec;
	unsigned char min;
	unsigned char hour;
	unsigned char day;
} RTC_TIME;

extern volatile RTC_TIME _rtc2;

//initialize the timer
void rtc2_init(unsigned long period);

//activate the isr handler
void rtc2_act(void (*isr_ptr)(void));

//update rtc2
void rtc2_update(void);

#endif
