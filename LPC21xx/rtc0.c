#include <lpc210x.h>				//we use keil lpc210x
//#include "delay.h"
#include "gpio.h"
#include "rtc0.h"					//we use tmr0

#define RTC_PERIOD			TMR_1ms	//rtc periods

unsigned int _rtc0_period=TMR_10ms;	//default rtc period
unsigned int _rtc0_counter=0;		//rtc counter

void (*_tmr0_func) (void);			//tmr0_function ptr

void _rtc0_func_empty(void) {
}

void rtc0_isr(void) __irq {
  	T0IR        = 1;				// Clear interrupt flag
  	VICVectAddr = 0;				// Acknowledge Interrupt by writting to it
	_rtc0_counter+=RTC_PERIOD;		//increment rtc_counter
	if (_rtc0_counter>=_rtc0_period) {
		_rtc0_counter-=_rtc0_period;	//update rtc_counter
		_tmr0_func();					//execute my isr
	}
}

void rtc0_init(unsigned long period) {
  	T0TCR = 0;						//stop the timer
	
	//set up the tmr parameters
	T0PR=TMR_PS_1x;					//prescaler set to 1:1
  	_rtc0_period=period;			//update rtc_period
	T0MR0 = RTC_PERIOD;					//tmr0 channel 0, interrupt on match
  	T0MCR = (T0MCR & (~TxMCR_MaskMR0)) |	//clear t0mcr_mr0 bits
			TxMCR_ISRonMR0 |				//interrupt on mr0
			TxMCR_ResetonMR0;				//Reset on MR0
 	T0TC=0;							//reset tmr0 timer/counter
  	
	VICVectAddr0 = (unsigned long)rtc0_isr;       // set interrupt vector in 0
 	VICVectCntl0 = (1<<5) | TMR0_ISR_CH;		// use it for Timer 0 Interrupt. irq4 + enable bits (0x20, bit 5)
  	VICIntEnable = (1<<TMR0_ISR_CH);			// Enable Timer0 Interrupt. turn on irq4

  	T0TCR = 1;						// Timer0 Enable

	_tmr0_func = _rtc0_func_empty;	//point to an empty ptr
}

void rtc0_act(void (*func_ptr)(void)) {
	_tmr0_func=func_ptr;
}

