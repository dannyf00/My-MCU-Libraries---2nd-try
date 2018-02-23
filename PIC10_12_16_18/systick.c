#include "systick.h"						//we use tmr1

volatile uint32_t systickovf_counter=0;	//systick overflow counter

//global defines

//tmr0 isr
//user needs to insert tmr0_isr() into the pulled isr handler, with a test of T0IF
//  if (T0IF) tmr0_isr();
//
void tmr0_isr(void) {
	T0IF = 0;							//clear the flag
	systickovf_counter+=0x100ul;		//increment the counter - 8-bit counter
}
	
//initialize the timer1 (16bit)
void systick_init(void) {
	T0CS = 0;							//'0'->count F_OSC/4
	PS2=PS1=PS0=1;						//'111'->256x prescaler
	PSA = 0;							//'0'->prescaler assigned to TMR0
	TMR0 = 0;							//tmr0_offset;					//set the period
	T0IF = 0;							//clear the flag
	T0IE = 1;							//enable interrupt on timer0 overflow
	//timer0 is always on
}

//return timer clicks
//execution time = 30 ticks, no optimization
uint32_t ticks(void) {
	uint32_t m;
	uint8_t f;							//8-bit counter

	//do a double read
	do {
		m = systickovf_counter;			//read the overflow counter
		f = TMR0;						//read the least significant 16-bits
	} while (m != systickovf_counter);	//gaurd against overflow

	return (m | f) << 8;				//prescaler is 256:1
}

//return micros()

//return millis

//delay ms using SysTick ticks()
void systick_delayms(uint32_t ms) {
	uint32_t start_time = ticks();

	ms *= cyclesPerMillisecond();				//convert ms to ticks
	while (ticks() - start_time < ms) continue;	//wait for timer to expire
}

//delay using SysTick ticks()
void systick_delayus(uint32_t us) {
	uint32_t start_time = ticks();

	us *= cyclesPerMicrosecond();				//convert ms to ticks
	while (ticks() - start_time < us) continue;	//wait for timer to expire
}
