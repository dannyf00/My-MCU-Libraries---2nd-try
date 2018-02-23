/*	a ccs controlled by avr
	input: adc, 20x gain
	otput: pwm, 10-bit
	loop control: ipid
 */

#include "pwm2.h"						//we use pwm on tmr1

//hardware configuration
//end hardware configuration

//set pwm1 period
//phase correct pwm, top = 0xff
void pwm2_setpr(unsigned char ps, unsigned char period) {
	//set up timr1
	TCCR2B = (TCCR2B & ~0x0f) |			//stop tmr1, clear CS2..0
				(0<<WGM22);				//clear wgm02
	TCCR2A = 	(0<<WGM21) |			//wgm02..0=0b001->mode 1
				(1<<WGM20) |
				0x00;					//clear wgm0/com0
	TCNT2 = 0;							//reset the clock counter
	TIMSK2 = 0;							//no interrupt
	TCCR2B = TCCR2B | (ps & 0x07);		//set up the clock prescaler
}

//activate pwm1a
void pwm2a_init(void) {
	TCCR2A = (TCCR2A & ~((1<<COM2A1) | (1<<COM2A0))) |
				(1<<COM2A1) | (0<<COM2A0);		//0b10->clear oc0a on math
	IO_OUT(PWM2A_DDR, PWM2A_PIN);				//pwm as output

}

//activate pwm1a
void pwm2b_init(void) {
	TCCR2A = (TCCR2A & ~((1<<COM2B1) | (1<<COM2B0))) |
				(1<<COM2B1) | (0<<COM2B0);		//0b10->clear oc0a on math
	IO_OUT(PWM2B_DDR, PWM2B_PIN);				//pwm as output

}

//set pwm on tmr1, channel a
void pwm2a_setdc(unsigned char dc) {
	OCR2A = dc;
}

//set pwm on tmr1, channel b
void pwm2b_setdc(unsigned char dc) {
	OCR2B = dc;
}

