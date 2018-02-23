#include "pwm4.h"						//we use pwm on tmr1

//hardware configuration
//end hardware configuration


void pwm4_setpr(unsigned char ps, unsigned short period) {
	TCCR4B = TCCR4B & ~0x07;					//reset cs2..0, stop the timer
	//phase correct 10-bit pwm, wgmn3..0=0b0011
	TCCR4B &= ~((1<<WGM43) | (1<<WGM42));		//clear wgm13 and wgm12
	TCCR4A |= ((1<<WGM41) | (1<<WGM40));		//set wgm11 and wgm10
	//set up com1A/B/C1..0 = 0b10
	TCCR4A = (TCCR4A & 0x03) |					//clear com1a1..0
				(0<<COM4A1) | (0<<COM4A0) |		//clear com1a1, clear com1a0
				(0<<COM4B1) | (0<<COM4B0) |
#if defined(COM4C1)
				(0<<COM4C1) | (0<<COM4C0) |
#endif
				0x00;
	TCNT4 = 0;									//reset the counter
	TIMSK3 = 0;									//no interrupt
	TCCR4B |= ps & 0x07;						//set the prescaler
}

void pwm4a_init(void) {
	TCCR4A = (TCCR4A & ~((1<<COM4A1) | (1<<COM4A0))) |	//clear com1a1..0
				(1<<COM4A1) | (0<<COM4A0);		//set com1a1, clear com1a0
	IO_OUT(PWM4A_DDR, PWM4A_PIN);				//pwm1A_pin as output
}

void pwm4b_init(void) {
	TCCR4A = (TCCR4A & ~((1<<COM4B1) | (1<<COM4B0))) |	//clear com1b1..0
				(1<<COM4B1) | (0<<COM4B0);		//set com1b1, clear com1b0
	IO_OUT(PWM4B_DDR, PWM4B_PIN);				//pwm1b_pin as output
}

void pwm4c_init(void) {
#if defined(COM4C1)
	TCCR4A = (TCCR4A & ~((1<<COM4C1) | (1<<COM4C0))) |	//clear com1C1..0
				(1<<COM4C1) | (0<<COM4C0);		//set com1C1, clear com1C0
#endif
	IO_OUT(PWM4C_DDR, PWM4C_PIN);				//pwm1C_pin as output
}

void pwm4a_setdc(unsigned short dc) {
	OCR4A = dc;
}

void pwm4b_setdc(unsigned short dc) {
	OCR4B = dc;
}

void pwm4c_setdc(unsigned short dc) {
#if defined(COM4C1)
	OCR4C = dc;
#endif
}
