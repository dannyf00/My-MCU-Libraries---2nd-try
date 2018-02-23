#include "pwm0.h"						//we use pwm functions of timer1

//empty handler

//reset the tmr
//phase correct 8-bit (wgm13..0=0b0001, 8-bit period (top=0x00ff)
//phase correct 9-bit (wgm13..0=0b0010, 9-bit period (top=0x01ff)
//phase correct 10-bit (wgm13..0=0b0011, 10-bit period (top=0x03ff)
//fast 8-bit (wgm13..0=0b0101, 8-bit period (top=0x00ff)
//fast 9-bit (wgm13..0=0b0110, 9-bit period (top=0x01ff)
//fast 10-bit (wgm13..0=0b0111, 10-bit period (top=0x03ff)

//default: phase correct pwm (0b001)
void pwm0_init(uint8_t ps) {
	//TCCR1 =	TCCR1 & (~TMR1_PS_MASK);			//turn off tmr1
	///*_tmr1*/_isr_ptr=/*_tmr1_*/empty_handler;			//reset isr ptr
	//initialize the timer
	TCCR0B =	TCCR0B & ~(TMR0_PSMASK);				//turn off tmr0
	TCCR0A = 	(TCCR0A & ~((1<<WGM01) | (1<<WGM00))) |
				(0<<WGM01) | (1<<WGM00);				//wgm02..0 = 0b001
	TCCR0B  =	(TCCR0B & ~(1<<WGM02)) |
				(0<<WGM02);								//wgm02..0 = 0b001
	TCNT0 = 0;								//reset the counter
	TIFR |= (1<<TOV0) | (1<<OCF0A) | (1<<OCF0B);						//clear by writing 1 to it
	TIMSK = (TIMSK & ~((1<<TOIE0) | (1<<OCIE0A) | (1<<OCIE0B))) |		//tmr overflow interrupt: disabled
			(0<<TOIE0) | (0<<OCIE0A) | (0<<OCIE0B);
				;
	TCCR0B |=	(ps & TMR0_PSMASK)			//prescaler = 1:1, per the header file
				;
	//now timer 0 is running
}

//set dc for channel a
//0b10->clear on compare match
//need to pay attention to the mode bits (wgm13..0) and dc value
void pwm0a_setdc(uint8_t dc) {
	///*_tmr1*/_isr_ptr=isr_ptr;					//reassign tmr1 isr ptr
	//TIFR |= (1<<OCF1A);						//clear the flag by writing '1' to it
	//TIMSK |=	(1<<OCIE1A)					//tmr overflow interrupt: enabled
	//			;

	IO_OUT(PWM0A_DDR, PWM0A_PIN);				//oc1a as output

	TCCR0A = 	(TCCR0A & ~((1<<COM0A1) | (1<<COM0A0))) |
				(1<<COM0A1) | (0<<COM0A0) |
				//(1<<PWM1A) |				//pwm1a enabled
				//(1<<COM1A1) | (0<<COM1A0);	//0b10->clear on compare match
				0x00;
	OCR0A = dc;							//set dc
}

//set dc for channel b
//0b10->clear on compare match
//need to pay attention to the mode bits (wgm13..0) and dc value
void pwm0b_setdc(uint8_t dc) {
	///*_tmr1*/_isr_ptr=isr_ptr;					//reassign tmr1 isr ptr
	//TIFR |= (1<<OCF1A);						//clear the flag by writing '1' to it
	//TIMSK |=	(1<<OCIE1A)					//tmr overflow interrupt: enabled
	//			;

	IO_OUT(PWM0B_DDR, PWM0B_PIN);				//oc1b as output

	TCCR0A = 	(TCCR0A & ~((1<<COM0B1) | (1<<COM0B0))) |
				//(1<<PWM1B) |				//enable pwm1b
				(1<<COM0B1) | (0<<COM0B0);	//0b10->clear on compare match
	OCR0B = dc;							//set dc
}
