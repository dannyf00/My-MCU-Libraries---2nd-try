#include "pwm1.h"						//we use pwm functions of timer1

//empty handler

//reset the tmr
//phase correct 8-bit (wgm13..0=0b0001, 8-bit period (top=0x00ff)
//phase correct 9-bit (wgm13..0=0b0010, 9-bit period (top=0x01ff)
//phase correct 10-bit (wgm13..0=0b0011, 10-bit period (top=0x03ff)
//fast 8-bit (wgm13..0=0b0101, 8-bit period (top=0x00ff)
//fast 9-bit (wgm13..0=0b0110, 9-bit period (top=0x01ff)
//fast 10-bit (wgm13..0=0b0111, 10-bit period (top=0x03ff)

//default: pwm (0b10)
void pwm1_init(uint8_t prescaler) {
	//TCCR1 =	TCCR1 & (~TMR1_PS_MASK);			//turn off tmr1
	///*_tmr1*/_isr_ptr=/*_tmr1_*/empty_handler;			//reset isr ptr
	TCCR1 =		(0<<CTC1) |					//clear on compare match
				(0<<COM1A1) | (0<<COM1A0) |	//output compare a pins normal operation
				(0<<COM1B1) | (0<<COM1B0) |	//output compare b pins normal operation
				//(0<<COM1C1) | (0<<COM1C0) |	//output compare c pins normal operation
				//(1<<WGM11) | (1<<WGM10)		//wgm13..0 = 0b0000 -> default
				0x00;
	//TCCR1B =	(TCCR1B & ~((1<<WGM13) | (1<<WGM12))) |	//clear wgm13..2
	//			(0<<WGM13) | (0<<WGM12);	//wgm13.0=0b0000 - default
	//TCCR1C =	(0<<FOC1A) |				//forced output on ch a disabled
	//			(0<<FOC1B) |				//forced output on ch b disabled
	//			(0<<FOC1C)					//forced output on ch c disabled
	//			;
	//OCR1A = period-1;
	TCNT1 = 0;								//reset the timer / counter
	OCR1C = 0xff;							//top value for counter
	//TIFR |= (1<<OCF1A);						//clear the flag by writing '1' to it
	TIMSK =		//(0<<TICIE1) |				//input capture isr: disabled
				//(0<<OCIE1C) |				//output compare isr for ch a: disabled
				(0<<OCIE1B) |				//output compare isr for ch b: disabled
				(0<<OCIE1A) |				//output compare isr for ch c: disabled
				(0<<TOIE1)					//tmr overflow interrupt: disabled
				;
	TCCR1 |=	(prescaler & TMR1_PS_MASK)	//prescaler, per the header file
				;
	//now timer1 is running
}

//set dc for channel a
//0b10->clear on compare match
//need to pay attention to the mode bits (wgm13..0) and dc value
void pwm1a_setdc(uint8_t dc) {
	///*_tmr1*/_isr_ptr=isr_ptr;					//reassign tmr1 isr ptr
	//TIFR |= (1<<OCF1A);						//clear the flag by writing '1' to it
	//TIMSK |=	(1<<OCIE1A)					//tmr overflow interrupt: enabled
	//			;

#if defined(_PWM1A_PIN)
	IO_OUT(PWM1A_DDR, PWM1A_PIN | _PWM1A_PIN);				//oc1a as output
#else
	IO_OUT(PWM1A_DDR, PWM1A_PIN);				//oc1a as output
#endif

	TCCR1 = 	(TCCR1 & ~((1<<COM1A1) | (1<<COM1A0))) |
				(1<<PWM1A) |				//pwm1a enabled
#if defined(_PWM1A_PIN)
				(0<<COM1A1) | (1<<COM1A0);	//0b01->clear on compare match on both pins
#else
				(1<<COM1A1) | (0<<COM1A0);	//0b10->clear on compare match negative pins not connected
#endif
	OCR1A = dc;							//set dc
}

//set dc for channel b
//0b10->clear on compare match
//need to pay attention to the mode bits (wgm13..0) and dc value
void pwm1b_setdc(uint8_t dc) {
	///*_tmr1*/_isr_ptr=isr_ptr;					//reassign tmr1 isr ptr
	//TIFR |= (1<<OCF1A);						//clear the flag by writing '1' to it
	//TIMSK |=	(1<<OCIE1A)					//tmr overflow interrupt: enabled
	//			;

#if defined(_PWM1B_PIN)
	IO_OUT(PWM1B_DDR, PWM1B_PIN | _PWM1B_PIN);				//oc1b as output
#else
	IO_OUT(PWM1B_DDR, PWM1B_PIN);				//oc1b as output
#endif

	GTCCR = 	(GTCCR & ~((1<<COM1B1) | (1<<COM1B0))) |
				(1<<PWM1B) |				//enable pwm1b
#if defined(_PWM1B_PIN)
				(0<<COM1B1) | (1<<COM1B0);	//0b10->clear on compare match
#else
				(1<<COM1B1) | (0<<COM1B0);	//0b10->clear on compare match
#endif
	OCR1B = dc;							//set dc
}
