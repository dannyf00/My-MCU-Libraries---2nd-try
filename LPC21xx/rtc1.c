#include <lpc210x.h>				//we use keil lpc210x
//#include "delay.h"
#include "gpio.h"
#include "rtc1.h"					//we use tmr1

#define RTC_PERIOD			TMR_1ms	//rtc periods

unsigned int _rtc1_period=TMR_10ms;	//default rtc period
unsigned int _rtc1_counter=0;		//rtc counter

void (*_tmr1_func) (void);			//tmr0_function ptr

void _rtc1_func_empty(void) {
}

void rtc1_isr(void) __irq {
  	T1IR        = 1;				// Clear interrupt flag
  	VICVectAddr = 0;				// Acknowledge Interrupt by writting to it
	_rtc1_counter+=RTC_PERIOD;		//increment rtc_counter
	if (_rtc1_counter>=_rtc1_period) {
		_rtc1_counter-=_rtc1_period;	//update rtc_counter
		_tmr1_func();					//execute my isr
	}
}

void rtc1_init(unsigned int period) {
  	T1TCR = 0;						//stop the timer
	
	//set up the tmr parameters
	T1PR=TMR_PS_1x;					//prescaler set to 1:1
  	_rtc1_period=period;			//update rtc_period
	T1MR0 = RTC_PERIOD;					//tmr0 channel 0, interrupt on match
   	T1MCR = (T1MCR & (~TxMCR_MaskMR0)) |	//clear t0mcr_mr0 bits
			TxMCR_ISRonMR0 |				//interrupt on mr0
			TxMCR_ResetonMR0;				//Reset on MR0
  	T1TC=0;							//reset tmr0 timer/counter
  	
	VICVectAddr1 = (unsigned long)rtc1_isr;       // set interrupt vector in 0
 	VICVectCntl1 = (1<<5) | TMR1_ISR_CH;		// use it for Timer 0 Interrupt. irq4 + enable bits (0x20, bit 5)
  	VICIntEnable = (1<<TMR1_ISR_CH);			// Enable Timer0 Interrupt. turn on irq4
	
  	T1TCR = 1;						// Timer0 Enable

	_tmr1_func = _rtc1_func_empty;	//point to an empty ptr

}

void rtc1_act(void (*func_ptr)(void)) {
	_tmr1_func=func_ptr;
}

