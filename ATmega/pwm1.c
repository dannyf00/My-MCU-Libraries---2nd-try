#include "pwm1.h"						//we use pwm on tmr1

//hardware configuration
//end hardware configuration

//phase correct pwm
//top = 0x3ff
#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__ATtiny25__) || defined(__ATtiny45__) || defined(__ATtiny85__)
//#define PWM1_PERIOD		255
//reset pwm on tmr1, 10-bit, channel a
void pwm1a_init(void) {
	IO_OUT(PWM1A_DDR, PWM1A_PIN);			//pwm as output
#if defined(PWM1nA_PIN)
	IO_OUT(PWM1A_DDR, PWM1nA_PIN);			//pwm as output
#endif

	TIMSK = 0;								//no interrupt
	//set up timr1
	TCCR1 = TCCR1 & 0xf0;					//stop the module
	OCR1C = (OCR1C)?OCR1C:0xff;				//set ocr1c if it is not reset
	OCR1A = (OCR1C)/2;						//default to 50% dc
	TCCR1 =		(1<<CTC1) |					//1=reset counter on output match -> needed for the pwm mode
				(1<<PWM1A) |				//enable pwm1a, and reset TCNT1
#if defined(PWM1nA_PIN)
				(1<<COM1A1) | (0<<COM1A0) |	//0b10->OC1A and nOC1A both connected. 1-> set on match on upcounting and clear on match on downcounting
#else
				(0<<COM1A1) | (1<<COM1A0) |	//0b01->only OC1A connected. nOC1A disconnected
#endif
				//(1<<CS13) | (0<<CS12) | (0<<CS11) | (1<<CS10)	//0b0001 -> 1:1 prescaler. 0b1000 -> 128:1
				0x00;
	TCNT1 = 0;
	TCCR1 |=	(0<<CS13) | (0<<CS12) | (0<<CS11) | (1<<CS10)	//0b0001 -> 1:1 prescaler. 0b1000 -> 128:1
				;
	//OCR1A = pwm_dc;							//initialize output match
	//OCR1B = 0x3ff/2;

	//pll_enable();							//enable pll
}

//reset pwm on tmr1, 10-bit, channel b
void pwm1b_init(void) {
	IO_OUT(PWM1B_DDR, PWM1B_PIN);			//pwm as output
#if defined(PWM1nB_PIN)
	IO_OUT(PWM1B_DDR, PWM1nB_PIN);			//pwm as output
#endif

	TCCR1 =		(TCCR1 & 0xf0);				//turn off the clock

	TIMSK = 0;								//no interrupt
	//set up timr1
	//GTCCR &= (1<<TSM);						//stop the module
	OCR1C = (OCR1C)?OCR1C:0xff;				//set ocr1c if it is not reset
	OCR1B = (OCR1C)/2;						//default to 50% DC
	GTCCR =		(GTCCR & ~0x7e) |			//reset bit 6..1
				(1<<PWM1B) |				//enable pwm1a, and reset TCNT1
#if defined(PWM1nB_PIN)
				(0<<COM1B1) | (1<<COM1B0) |	//0b11-> set on match on upcounting and clear on match on downcounting. 0b00->pins disconnected. 0b01->activate OC1x and nOC1x
#else
				(1<<COM1B1) | (0<<COM1B0) |	//0b10-> only clear OC1x (nOC1x unconnected)
#endif
				(1<<FOC1B) |				//set foc1b -> force a change
				(1<<FOC1A) |				//set foc1a -> forece a change
				0x00;
	TCNT1 = 0;
	TCCR1 |=	(1<<CTC1) |					//reset counter on compare match -> needed for pwm mode
				(0<<CS13) | (0<<CS12) | (1<<CS11) | (0<<CS10)	//0b0001 -> 1:1 prescaler. 0b1000 -> 128:1
				;
	//OCR1A = pwm_dc;							//initialize output match
	//OCR1B = 0x3ff/2;

	//pll_enable();							//enable pll
}


//set pwm on tmr1, channel a
void pwm1a_setdc(unsigned short dc) {
	OCR1A = dc;
}

//set pwm on tmr1, channel b
void pwm1b_setdc(unsigned short dc) {
	OCR1B = dc;
}

//set pwm on tmr1, channel b
void pwm1c_setdc(unsigned short dc) {
	OCR1C = dc;
}

//enable pll clock
void pll_enable(void) {
	PLLCSR = 0x00;							//disable pll
	PLLCSR |= (1<<LSM);						//1=enable low speed (32Mhz). 0=enable high speed (64Mhz)
	PLLCSR |= 1<<PLLE;						//enable pll
	while ((PLLCSR & (1<<PLOCK)) == 0);		//wait for PLL to lock
	PLLCSR |= (1<<PCKE);					//route pll clock to timer1
}

#else					//other avr chips

void pwm1_setpr(unsigned char ps, unsigned short period) {
	TCCR1B = TCCR1B & ~0x07;					//reset cs2..0, stop the timer
	//phase correct 10-bit pwm, wgmn3..0=0b0011
	TCCR1B &= ~((1<<WGM13) | (1<<WGM12));		//clear wgm13 and wgm12
	TCCR1A |= ((1<<WGM11) | (1<<WGM10));		//set wgm11 and wgm10
	//set up com1A/B/C1..0 = 0b10
	TCCR1A = (TCCR1A & 0x03) |					//clear com1a1..0
				(0<<COM1A1) | (0<<COM1A0) |		//clear com1a1, clear com1a0
				(0<<COM1B1) | (0<<COM1B0) |
#if defined(PWM1nC_PIN)
				(1<<COM1C1) | (0<<COM1C0) |		//0b10->OC1C and nOC1C connected
#else
				(0<<COM1C1) | (1<<COM1C0) |		//0B01->OC1C connected and nOC1C not connected
#endif
				0x00;
	TCNT1 = 0;									//reset the counter
	TIMSK1 = 0;									//no interrupt
	TCCR1B |= ps & 0x07;						//set the prescaler
}

void pwm1a_init(void) {
	TCCR1A = (TCCR1A & ~((1<<COM1A1) | (1<<COM1A0))) |	//clear com1a1..0
#if defined(PWM1nA_PIN)
				(0<<COM1A1) | (1<<COM1A0) |	//0b11-> set on match on upcounting and clear on match on downcounting. 0b00->pins disconnected. 0b01->activate OC1x and nOC1x
#else
				(1<<COM1A1) | (0<<COM1A0) |	//0b10-> only clear OC1x (nOC1x unconnected)
#endif
				0x00;
	IO_OUT(PWM1A_DDR, PWM1A_PIN);				//pwm1A_pin as output
}

void pwm1b_init(void) {
	TCCR1A = (TCCR1A & ~((1<<COM1B1) | (1<<COM1B0))) |	//clear com1b1..0
#if defined(PWM1nB_PIN)
				(0<<COM1B1) | (1<<COM1B0) |	//0b11-> set on match on upcounting and clear on match on downcounting. 0b00->pins disconnected. 0b01->activate OC1x and nOC1x
#else
				(1<<COM1B1) | (0<<COM1B0) |	//0b10-> only clear OC1x (nOC1x unconnected)
#endif
	IO_OUT(PWM1B_DDR, PWM1B_PIN);				//pwm1b_pin as output
}

void pwm1c_init(void) {
	TCCR1A = (TCCR1A & ~((1<<COM1C1) | (1<<COM1C0))) |	//clear com1C1..0
#if defined(PWM1nC_PIN)
				(0<<COM1C1) | (1<<COM1C0) |	//0b11-> set on match on upcounting and clear on match on downcounting. 0b00->pins disconnected. 0b01->activate OC1x and nOC1x
#else
				(1<<COM1C1) | (0<<COM1C0) |	//0b10-> only clear OC1x (nOC1x unconnected)
#endif
	IO_OUT(PWM1C_DDR, PWM1C_PIN);				//pwm1C_pin as output
}

void pwm1a_setdc(unsigned short dc) {
	OCR1A = dc;
}

void pwm1b_setdc(unsigned short dc) {
	OCR1B = dc;
}

void pwm1c_setdc(unsigned short dc) {
	OCR1C = dc;
}
#endif
