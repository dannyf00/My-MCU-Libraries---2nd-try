#include "systick.h"						//we use tmr1

volatile uint32_t systickovf_counter=0;	//systick overflow counter

ISR(TIMER0_OVF_vect) {
	//clear the flag - done by hardware
	systickovf_counter+=0x100ul;		//increment the counter - 8-bit counter
}

//global defines
//tmr0 prescaler
#define TMR0_PS_1x			0x01
#define TMR0_PS_8x			0x02
#define TMR0_PS_64x			0x03
#define TMR0_PS_256x		0x04			//default
#define TMR0_PS_1024x		0x05
#define TMR0_PS_MASK		0x07

//initialize the timer1 (16bit)
void systick_init(void) {
	TCCR0B =	TCCR0B & (~0x07);			//turn off tmr0
	TCCR0A&=~((1<<WGM01) | (1<<WGM00));		//wgm02..0 = 0b000 -> normal, overflow at 0xff->0x00
	TCCR0B&=~((1<<WGM02));
	TCNT0 = 0;								//reset the timer / counter
	TIFR0|= (1<<TOV0);						//clear the overflow flag by writing '1' to it
	TIMSK0|=(1<<TOIE0);						//tmr overflow interrupt: enabled
	TCCR0B = (TCCR0B &~TMR0_PS_MASK) | (TMR0_PS_256x);	//prescaler at 256x, and timer starts
	//timer now starts
}

//return timer clicks
//execution time = 30 ticks, no optimization
uint32_t ticks(void) {
	uint32_t m;
	uint8_t f;							//8-bit counter

	//do a double read
	do {
		m = systickovf_counter;			//read the overflow counter
		f = TCNT0;						//read the least significant 16-bits
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
