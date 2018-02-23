#include "systick.h"						//we use tmr1

volatile uint32_t systickovf_counter=0;	//systick overflow counter

void _ISR _T1Interrupt(void) {
	_T1IF=0;							//clear tmr1 interrupt flag
	systickovf_counter+=0x10000ul;		//increment the counter - 16-bit counter
}

//global defines
//tmr1 prescaler
#define TMR_PS_1x			0x00
#define TMR_PS_8x			0x01
#define TMR_PS_64x			0x02
#define TMR_PS_256x			0x03
#define TMR_PS_MASK			TMR_PS_256x


//for compatibility reasons

#define _T1ON				T1CONbits.TON
#define _T1CS				T1CONbits.TCS
#define _T1GE				T1CONbits.TGATE
#define _T1CKPS				T1CONbits.TCKPS
#define _T1IE				IEC0bits.T1IE
#define _T1IF				IFS0bits.T1IF			//tmr1 overflow flag

//initialize the timer1 (16bit)
void systick_init(void) {
	_T1MD = 0;							//enable power to tmr
	_T1ON = 0;							//turn off rtc1
	PR1=0xffff;							//period-1;						//minimum rtc resolution is 1ms
	_T1CS = 0;							//use internal clock = Fosc / 4
	_T1CKPS=(0) & TMR_PS_MASK;			//set prescaler to 1:1
	_T1GE = 0;							//rtc1 gate disabled
	TMR1 = 0;							//reset the timer/counter

	_T1IF = 0;							//reset the flag
	_T1IE=1;							//rtc1 interrupt on

	_T1ON = 1;							//turn on rtc1
}

//return timer clicks
//execution time = 30 ticks, no optimization
uint32_t systicks(void) {
	uint32_t m;
	uint16_t f;

	//do a double read
	do {
		m = systickovf_counter;			//read the overflow counter
		f = TMR1;						//read the least significant 16-bits
	} while (m != systickovf_counter);	//gaurd against overflow

	return (m | f) << 0;
}

//return micros()

//return millis

//delay ms using SysTick ticks()
void systick_delayms(uint32_t ms) {
	uint32_t start_time = systicks();

	ms *= cyclesPerMillisecond();				//convert ms to ticks
	while (systicks() - start_time < ms) continue;	//wait for timer to expire
}

//delay using SysTick ticks()
void systick_delayus(uint32_t us) {
	uint32_t start_time = systicks();

	us *= cyclesPerMicrosecond();				//convert ms to ticks
	while (systicks() - start_time < us) continue;	//wait for timer to expire
}
