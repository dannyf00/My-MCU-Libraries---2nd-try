#include "pwm5.h"						//we use pwm on tmr1

//hardware configuration
//end hardware configuration


void pwm5_setpr(unsigned char ps, unsigned short period) {
	TCCR5B = TCCR5B & ~0x07;					//reset cs2..0, stop the timer
	//phase correct 10-bit pwm, wgmn3..0=0b0011
	TCCR5B &= ~((1<<WGM53) | (1<<WGM52));		//clear wgm13 and wgm12
	TCCR5A |= ((1<<WGM51) | (1<<WGM50));		//set wgm11 and wgm10
	//set up com1A/B/C1..0 = 0b10
	TCCR5A = (TCCR5A & 0x03) |					//clear com1a1..0
				(0<<COM5A1) | (0<<COM5A0) |		//clear com1a1, clear com1a0
				(0<<COM5B1) | (0<<COM5B0) |
#if defined(COM5C1)
				(0<<COM5C1) | (0<<COM5C0) |
#endif
				0x00;
	TCNT5 = 0;									//reset the counter
	TIMSK5 = 0;									//no interrupt
	TCCR5B |= ps & 0x07;						//set the prescaler
}

void pwm5a_init(void) {
	TCCR5A = (TCCR5A & ~((1<<COM5A1) | (1<<COM5A0))) |	//clear com1a1..0
				(1<<COM5A1) | (0<<COM5A0);		//set com1a1, clear com1a0
	IO_OUT(PWM5A_DDR, PWM5A_PIN);				//pwm1A_pin as output
}

void pwm5b_init(void) {
	TCCR5A = (TCCR5A & ~((1<<COM5B1) | (1<<COM5B0))) |	//clear com1b1..0
				(1<<COM5B1) | (0<<COM5B0);		//set com1b1, clear com1b0
	IO_OUT(PWM5B_DDR, PWM5B_PIN);				//pwm1b_pin as output
}

void pwm5c_init(void) {
#if defined(COM5C1)
	TCCR5A = (TCCR5A & ~((1<<COM5C1) | (1<<COM5C0))) |	//clear com1C1..0
				(1<<COM5C1) | (0<<COM5C0);		//set com1C1, clear com1C0
#endif
	IO_OUT(PWM5C_DDR, PWM5C_PIN);				//pwm1C_pin as output
}

void pwm5a_setdc(unsigned short dc) {
	OCR5A = dc;
}

void pwm5b_setdc(unsigned short dc) {
	OCR5B = dc;
}

void pwm5c_setdc(unsigned short dc) {
#if defined(COM5C1)
	OCR5C = dc;
#endif
}
