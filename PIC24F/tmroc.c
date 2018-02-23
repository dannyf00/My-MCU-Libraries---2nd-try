#include "tmroc.h"					//output compare using tmr2 as time base

//global defines

//for compatibility reasons

#define _OC1IF				IFS0bits.OC1IF
#define _OC1IE				IEC0bits.OC1IE
#define _OC2IF				IFS0bits.OC2IF
#define _OC2IE				IEC0bits.OC2IE
#define _OC3IF				IFS1bits.OC3IF
#define _OC3IE				IEC1bits.OC3IE
#define _OC4IF				IFS1bits.OC4IF
#define _OC4IE				IEC1bits.OC4IE
#define _OC5IF				IFS2bits.OC5IF
#define _OC5IE				IEC2bits.OC5IE

//empty handler
static void empty_handler(void) {
	//do nothing here
}

//isr pointers
void (*tmroc1_isrptr)(void) = empty_handler;
void (*tmroc2_isrptr)(void) = empty_handler;
void (*tmroc3_isrptr)(void) = empty_handler;
void (*tmroc4_isrptr)(void) = empty_handler;
void (*tmroc5_isrptr)(void) = empty_handler;
	
//tmr output compare period
volatile uint16_t tmroc1_pr = 0xffff;
volatile uint16_t tmroc2_pr = 0xffff;
volatile uint16_t tmroc3_pr = 0xffff;
volatile uint16_t tmroc4_pr = 0xffff;
volatile uint16_t tmroc5_pr = 0xffff;

//output compare isr
void _ISR _OC1Interrupt(void) {
	_OC1IF=0;							//clear tmr1 interrupt flag
	OC1R += tmroc1_pr;					//go to the next match point
	tmroc1_isrptr();					//run user handler
}

//output compare isr
void _ISR _OC2Interrupt(void) {
	_OC2IF=0;							//clear tmr1 interrupt flag
	OC2R += tmroc2_pr;					//go to the next match point
	tmroc2_isrptr();					//run user handler
}

//output compare isr
void _ISR _OC3Interrupt(void) {
	_OC3IF=0;							//clear tmr1 interrupt flag
	OC3R += tmroc3_pr;					//go to the next match point
	tmroc3_isrptr();					//run user handler
}

//output compare isr
void _ISR _OC4Interrupt(void) {
	_OC4IF=0;							//clear tmr1 interrupt flag
	OC4R += tmroc4_pr;					//go to the next match point
	tmroc4_isrptr();					//run user handler
}

//output compare isr
void _ISR _OC5Interrupt(void) {
	_OC5IF=0;							//clear tmr1 interrupt flag
	OC5R += tmroc5_pr;					//go to the next match point
	tmroc5_isrptr();					//run user handler
}

//rest tmr output compare
void tmroc_init1(uint16_t ps) {
	tmroc1_isrptr = empty_handler;
	tmroc1_pr = 0xffff;
	
	_OC1MD = 0;
	OC1CON1 = 	(0 << 13) |				//'0'->OC operates in idle
				(0b111 << 10) |			//0b111->time base is system clock
				(0b000 << 7) |			//'0'->OC fault lines are disabled
				(0b000 << 4) |			//'0'->PWM fault lines are disabled
				(0<<3) |				//'0'->trigger mode disabled
				(0b011 << 0) |			//0b011->single compare continuous mode
				0x00;
	OC1CON2 = 	(0 << 15) |				//'0'->fault mode is maintained until it is cleared
				(0 << 14) |				//'0'->pwm driven low at fault
				(0 << 13) |				//'0'->pin io not affected by fault conditions
				(0 << 12) |				//'0'->OCx not inverted
				(0b00 << 9) |			//least significant two bits of duty cycle
				(0 << 8) |				//'0'->16-bit mode, '1'->32 bit mode
				(0 << 7) |				//'0'->synchronize oct
				(0 << 5) |				//'0'->OCx connected to gpio pin, '1'->OCx tristated
				(0b11111 << 0) |		//0b11111 -> synchronize to itself
				0x00;
	_OC1IF = 0;
	_OC1IE = 0;

}

//set output compare channel period
void tmroc_setpr1(uint16_t pr) {
	tmroc1_pr = pr - 1;
	OC1R = OC1TMR + tmroc1_pr;					//load the top
	OC1RS= 0xffff;
	_OC1IF = _OC1IE = 0;				//clear the flag. no interrupt
}

//install user handler
void tmroc_act1(void (*isrptr)(void)) {
	tmroc1_isrptr = isrptr;
	_OC1IF = 0;
	_OC1IE = 1;
}

//rest tmr output compare
void tmroc_init2(uint16_t ps) {
	tmroc2_isrptr = empty_handler;
	tmroc2_pr = 0xffff;
	
	_OC2MD = 0;							//enable power to ocx
	OC2CON1 = 	(0 << 13) |				//'0'->OC operates in idle
				(0b111 << 10) |			//0b111->time base is system clock
				(0b000 << 7) |			//'0'->OC fault lines are disabled
				(0b000 << 4) |			//'0'->PWM fault lines are disabled
				(0<<3) |				//'0'->trigger mode disabled
				(0b011 << 0) |			//0b011->single compare continuous mode
				0x00;
	OC2CON2 = 	(0 << 15) |				//'0'->fault mode is maintained until it is cleared
				(0 << 14) |				//'0'->pwm driven low at fault
				(0 << 13) |				//'0'->pin io not affected by fault conditions
				(0 << 12) |				//'0'->OCx not inverted
				(0b00 << 9) |			//least significant two bits of duty cycle
				(0 << 8) |				//'0'->16-bit mode, '1'->32 bit mode
				(0 << 7) |				//'0'->synchronize oct
				(0 << 5) |				//'0'->OCx connected to gpio pin, '1'->OCx tristated
				(0b11111 << 0) |		//0b11111 -> synchronize to itself
				0x00;
	_OC2IF = 0;
	_OC2IE = 0;

}

//set output compare channel period
void tmroc_setpr2(uint16_t pr) {
	tmroc2_pr = pr - 1;
	OC2R = OC2TMR + tmroc2_pr;					//load the top
	OC2RS= 0xffff;
	_OC2IF = _OC2IE = 0;				//clear the flag. no interrupt
}

//install user handler
void tmroc_act2(void (*isrptr)(void)) {
	tmroc2_isrptr = isrptr;
	_OC2IF = 0;
	_OC2IE = 1;
}

//rest tmr output compare
void tmroc_init3(uint16_t ps) {
	tmroc3_isrptr = empty_handler;
	tmroc3_pr = 0xffff;
	
	_OC3MD = 0;							//enable power to ocx
	OC3CON1 = 	(0 << 13) |				//'0'->OC operates in idle
				(0b111 << 10) |			//0b111->time base is system clock
				(0b000 << 7) |			//'0'->OC fault lines are disabled
				(0b000 << 4) |			//'0'->PWM fault lines are disabled
				(0<<3) |				//'0'->trigger mode disabled
				(0b011 << 0) |			//0b011->single compare continuous mode
				0x00;
	OC3CON2 = 	(0 << 15) |				//'0'->fault mode is maintained until it is cleared
				(0 << 14) |				//'0'->pwm driven low at fault
				(0 << 13) |				//'0'->pin io not affected by fault conditions
				(0 << 12) |				//'0'->OCx not inverted
				(0b00 << 9) |			//least significant two bits of duty cycle
				(0 << 8) |				//'0'->16-bit mode, '1'->32 bit mode
				(0 << 7) |				//'0'->synchronize oct
				(0 << 5) |				//'0'->OCx connected to gpio pin, '1'->OCx tristated
				(0b11111 << 0) |		//0b11111 -> synchronize to itself
				0x00;
	_OC3IF = 0;
	_OC3IE = 0;

}

//set output compare channel period
void tmroc_setpr3(uint16_t pr) {
	tmroc3_pr = pr - 1;
	OC3R = OC3TMR + tmroc3_pr;			//load the top
	OC3RS= 0xffff;
	_OC3IF = _OC3IE = 0;				//clear the flag. no interrupt
}

//install user handler
void tmroc_act3(void (*isrptr)(void)) {
	tmroc3_isrptr = isrptr;
	_OC3IF = 0;
	_OC3IE = 1;
}

//rest tmr output compare
void tmroc_init4(uint16_t ps) {
	tmroc4_isrptr = empty_handler;
	tmroc4_pr = 0xffff;
	
	_OC4MD = 0;							//enable power to ocx
	OC4CON1 = 	(0 << 13) |				//'0'->OC operates in idle
				(0b111 << 10) |			//0b111->time base is system clock
				(0b000 << 7) |			//'0'->OC fault lines are disabled
				(0b000 << 4) |			//'0'->PWM fault lines are disabled
				(0<<3) |				//'0'->trigger mode disabled
				(0b011 << 0) |			//0b011->single compare continuous mode
				0x00;
	OC4CON2 = 	(0 << 15) |				//'0'->fault mode is maintained until it is cleared
				(0 << 14) |				//'0'->pwm driven low at fault
				(0 << 13) |				//'0'->pin io not affected by fault conditions
				(0 << 12) |				//'0'->OCx not inverted
				(0b00 << 9) |			//least significant two bits of duty cycle
				(0 << 8) |				//'0'->16-bit mode, '1'->32 bit mode
				(0 << 7) |				//'0'->synchronize oct
				(0 << 5) |				//'0'->OCx connected to gpio pin, '1'->OCx tristated
				(0b11111 << 0) |		//0b11111 -> synchronize to itself
				0x00;
	_OC4IF = 0;
	_OC4IE = 0;

}

//set output compare channel period
void tmroc_setpr4(uint16_t pr) {
	tmroc4_pr = pr - 1;
	OC4R = OC4TMR + tmroc4_pr;			//load the top
	OC4RS= 0xffff;
	_OC4IF = _OC4IE = 0;				//clear the flag. no interrupt
}

//install user handler
void tmroc_act4(void (*isrptr)(void)) {
	tmroc4_isrptr = isrptr;
	_OC4IF = 0;
	_OC4IE = 1;
}

//rest tmr output compare
void tmroc_init5(uint16_t ps) {
	tmroc5_isrptr = empty_handler;
	tmroc5_pr = 0xffff;
	
	_OC5MD = 0;							//enable power to ocx
	OC5CON1 = 	(0 << 13) |				//'0'->OC operates in idle
				(0b111 << 10) |			//0b111->time base is system clock
				(0b000 << 7) |			//'0'->OC fault lines are disabled
				(0b000 << 4) |			//'0'->PWM fault lines are disabled
				(0<<3) |				//'0'->trigger mode disabled
				(0b011 << 0) |			//0b011->single compare continuous mode
				0x00;
	OC5CON2 = 	(0 << 15) |				//'0'->fault mode is maintained until it is cleared
				(0 << 14) |				//'0'->pwm driven low at fault
				(0 << 13) |				//'0'->pin io not affected by fault conditions
				(0 << 12) |				//'0'->OCx not inverted
				(0b00 << 9) |			//least significant two bits of duty cycle
				(0 << 8) |				//'0'->16-bit mode, '1'->32 bit mode
				(0 << 7) |				//'0'->synchronize oct
				(0 << 5) |				//'0'->OCx connected to gpio pin, '1'->OCx tristated
				(0b11111 << 0) |		//0b11111 -> synchronize to itself
				0x00;
	_OC5IF = 0;
	_OC5IE = 0;

}

//set output compare channel period
void tmroc_setpr5(uint16_t pr) {
	tmroc5_pr = pr - 1;
	OC5R = OC5TMR + tmroc5_pr;			//load the top
	OC5RS= 0xffff;
	_OC5IF = _OC5IE = 0;				//clear the flag. no interrupt
}

//install user handler
void tmroc_act5(void (*isrptr)(void)) {
	tmroc5_isrptr = isrptr;
	_OC5IF = 0;
	_OC5IE = 1;
}
