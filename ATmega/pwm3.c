#include "pwm3.h"						//we use pwm on tmr1

//hardware configuration
//end hardware configuration


void pwm3_setpr(unsigned char ps, unsigned short period) {
	TCCR3B = TCCR3B & ~0x07;					//reset cs2..0, stop the timer
	//phase correct 10-bit pwm, wgmn3..0=0b0011
	TCCR3B &= ~((1<<WGM33) | (1<<WGM32));		//clear wgm13 and wgm12
	TCCR3A |= ((1<<WGM31) | (1<<WGM30));		//set wgm11 and wgm10
	//set up com1A/B/C1..0 = 0b10
	TCCR3A = (TCCR3A & 0x03) |					//clear com1a1..0
				(0<<COM3A1) | (0<<COM3A0) |		//clear com1a1, clear com1a0
				(0<<COM3B1) | (0<<COM3B0) |
#if defined(COM3C1)
				(0<<COM3C1) | (0<<COM3C0) |
#endif
				0x00;
	TCNT3 = 0;									//reset the counter
	TIMSK3 = 0;									//no interrupt
	TCCR3B |= ps & 0x07;						//set the prescaler
}

void pwm3a_init(void) {
	TCCR3A = (TCCR3A & ~((1<<COM3A1) | (1<<COM3A0))) |	//clear com1a1..0
				(1<<COM3A1) | (0<<COM3A0);		//set com1a1, clear com1a0
	IO_OUT(PWM3A_DDR, PWM3A_PIN);				//pwm1A_pin as output
}

void pwm3b_init(void) {
	TCCR3A = (TCCR3A & ~((1<<COM3B1) | (1<<COM3B0))) |	//clear com1b1..0
				(1<<COM3B1) | (0<<COM3B0);		//set com1b1, clear com1b0
	IO_OUT(PWM3B_DDR, PWM3B_PIN);				//pwm1b_pin as output
}

void pwm3c_init(void) {
#if defined(COM3C1)
	TCCR3A = (TCCR3A & ~((1<<COM3C1) | (1<<COM3C0))) |	//clear com1C1..0
				(1<<COM3C1) | (0<<COM3C0);		//set com1C1, clear com1C0
#endif
	IO_OUT(PWM3C_DDR, PWM3C_PIN);				//pwm1C_pin as output
}

void pwm3a_setdc(unsigned short dc) {
	OCR3A = dc;
}

void pwm3b_setdc(unsigned short dc) {
	OCR3B = dc;
}

void pwm3c_setdc(unsigned short dc) {
#if defined(COM3C1)
	OCR3C = dc;
#endif
}
