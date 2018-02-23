/*	a ccs controlled by avr
	input: adc, 20x gain
	otput: pwm, 10-bit
	loop control: ipid
 */

#include "pwm0.h"						//we use pwm on tmr0

//hardware configuration
//end hardware configuration

//set pwm1 period
//pwm mode 1, top = 0xff
void pwm0_setpr(unsigned char ps, unsigned char period) {
	//set up timr1
	TCCR0B = (TCCR0B & ~0x0f) |			//stop tmr1, clear CS2..0
				(0<<WGM02);				//clear wgm02
	TCCR0A = 	(0<<WGM01) |			//wgm02..0=0b001->mode 1
				(1<<WGM00) |
				0x00;					//clear wgm0/com0
	TCNT0 = 0;							//reset the clock counter
#if defined(TIMSK0)
	TIMSK0 &=~(1<<TOIE0);				//no interrupt
#else
	TIMSK &=~(1<<TOIE0);				//clear toie0)
#endif
	TCCR0B = TCCR0B | (ps & 0x07);		//set up the clock prescaler
}

//activate pwm1a
void pwm0a_init(void) {
	TCCR0A = (TCCR0A & ~((1<<COM0A1) | (1<<COM0A0))) |
				(1<<COM0A1) | (0<<COM0A0);		//0b10->clear oc0a on math
	IO_OUT(PWM0A_DDR, PWM0A_PIN);				//pwm as output

}

//activate pwm1a
void pwm0b_init(void) {
	TCCR0A = (TCCR0A & ~((1<<COM0B1) | (1<<COM0B0))) |
				(1<<COM0B1) | (0<<COM0B0);		//0b10->clear oc0b on math
	IO_OUT(PWM0B_DDR, PWM0B_PIN);				//pwm as output

}

//set pwm on tmr1, channel a
void pwm0a_setdc(unsigned char dc) {
	OCR0A = dc;
}

//set pwm on tmr1, channel b
void pwm0b_setdc(unsigned char dc) {
	OCR0B = dc;
}
