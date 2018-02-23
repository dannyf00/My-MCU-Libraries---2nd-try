#include "pwm_sw.h"							//we use software pwm

//hardware configuration
//end hardware configuration

//global defines

//global variables
volatile uint8_t _pwm_cnt;
PWM_T pwm[PWM_CNT];

//tmr0 isr
ISR(TIMER0_OVF_vect) {
	uint8_t ch;
	_pwm_cnt+=1;							//increment counter
	if (_pwm_cnt==0) {						//_pwm_cnt overflown
		for (ch=0; ch<PWM_CNT; ch++) IO_SET(PWM_PORT, pwm[ch].pin);
	} else {
		for (ch=0; ch<PWM_CNT; ch++) if (_pwm_cnt==pwm[ch].dc) IO_CLR(PWM_PORT, pwm[ch].pin);
	}
}

//reset pwm
void pwm_init(uint8_t ps, uint8_t period) {
	TCCR0B =	TCCR0B & (~0x07);			//turn off tmr0
	///*_tmr0*/_isr_ptr=/*_tmr0_*/tmr0_isrr;	//reset isr ptr
	TCCR0A =	(0<<COM0A1) | (0<<COM0A0) |	//output compare a pins normal operation
				(0<<COM0B1) | (0<<COM0B0) |	//output compare b pins normal operation
				//(0<<COM1C1) | (0<<COM1C0) |	//output compare c pins normal operation
				(0<<WGM01) | (0<<WGM00)		//wgm02..0 = 0b000 -> normal, overflow at 0xff->0x00
				;
	/*TCCR0B =	(0<<ICNC1) |				//nput capture noise canceller disabled
				(0<<ICES1) |				//input capture edge selection on falling edge
				(0<<WGM13) | (1<<WGM12) |	//wgm13..0 = 0b0100 -> ctc, top at ocr1a
				(TMR_PS_1x & TMR_PS_MASK)		//prescaler, per the header file
				;*/
	TCCR0B =	(0<<FOC0A) |				//forced output on ch a disabled
				(0<<FOC0B) |				//forced output on ch b disabled
				//(0<<FOC1C)					//forced output on ch c disabled
				(0<<WGM02) |				//wgm02..0 = 0b000 -> normal, overflow at 0xff->0x00
				(ps & TMR_PS_MASK)			//prescaler = 1:1, per the header file
				;
	OCR1A = period;							//minimum time interval is 1ms
	TCNT0 = 0;								//reset the timer / counter
	TIMSK0 =	//(0<<ICIE1) |				//input capture isr: disabled
				//(0<<OCIE1C) |				//output compare isr for ch a: disabled
				(0<<OCIE0B) |				//output compare isr for ch b: disabled
				(0<<OCIE0A) |				//output compare isr for ch c: disabled
				(1<<TOIE0)					//tmr overflow interrupt: enabled
				;
	ei();									//enable interrupt
}

//set dc
void pwm_setdc(uint8_t ch, uint8_t pin, uint8_t dc) {
	pwm[ch].pin=pin;
	pwm[ch].dc = dc;

	IO_SET(PWM_PORT, pwm[ch].pin);
	IO_OUT(PWM_DDR, pwm[ch].pin);
}
