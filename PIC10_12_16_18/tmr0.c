//#include <htc.h>						//we use htc compiler
#include "tmr0.h"						//we use tmr0

static void empty_handler(void) {		//empty handler
	//do nothing
}

void (*_tmr0_isr_ptr)(void)=empty_handler;			//tmr0 isr handler pointer
unsigned char tmr0_offset=0xff;

//tmr0 isr
//to be included in the global isr
//void interrupt isr(void) {
//	tmr0_isr();							//process tmr0 isr
//	...
//}

//tmr0 isr
void tmr0_isr(void) {
	TMR0IF = 0;							//clear the flag
	_tmr0_isr_ptr();					//execute user isr
}
	
//initialize the timer
void tmr0_init(unsigned char prescaler) {
	_tmr0_isr_ptr=empty_handler;	//point to default handler
	T0CS = 0;							//use internal clock = Fosc / 4
	if (prescaler == TMR0_PS_1x) {
		PSA = 1;						//prescaler assigned to wdt
	} else {
		PSA = 0;						//prescaler assigned to tmr0
//		tmr0 prescaler bits in T0CON/T0PS2..0 - on newer chips
#if   	defined(_18F2455) || defined(_18F2550) || defined(_18F4455) || defined(_18F4550) || \
		defined(_18F2525) || defined(_18F2620) || defined(_18F4525) || defined(_18F4620) || \
		defined(_18F2585) || defined(_18F2680) || defined(_18F4585) || defined(_18F4680) || \
		defined(_18F6520) || defined(_18F8520) || defined(_18F6620) || defined(_18F8620) || defined(_18F6720) || defined(_18F8720) || \
		defined (_18F13K22) || defined (_18F14K22) || \
        defined (_18LF13K22) || defined (_18LF14K22) || \
	   	defined (_18F23K20) || defined (_18F24K20) || defined (_18F25K20) || defined (_18F26K20) || \
        defined (_18F43K20) || defined (_18F44K20) || defined (_18F45K20) || defined (_18F46K20) || \
        defined (_18LF23K20) || defined (_18LF24K20) || defined (_18LF25K20) || defined (_18LF26K20) || \
        defined (_18LF43K20) || defined (_18LF44K20) || defined (_18LF45K20) || defined (_18LF46K20) || \
	   	defined (_18F23K22) || defined (_18F24K22) || defined (_18F25K22) || defined (_18F26K22) || \
        defined (_18F43K22) || defined (_18F44K22) || defined (_18F45K22) || defined (_18F46K22) || \
        defined (_18LF23K22) || defined (_18LF24K22) || defined (_18LF25K22) || defined (_18LF26K22) || \
        defined (_18LF43K22) || defined (_18LF44K22) || defined (_18LF45K22) || defined (_18LF46K22)

		T0PS2 = (prescaler & 0x04)?1:0;
		T0PS1 = (prescaler & 0x02)?1:0;
		T0PS0 = (prescaler & 0x01)?1:0;

//		tmr0 prescaler bits in OPTION_REG - on most chips
#elif 	defined(_12F675) || \
		defined(_12F683) || \
 		defined(_16F83) || defined(_16F84) || defined(_16FCR83) || defined(_16FCR84) || \
 		defined(_16F87) || defined(_16F88) || \
 		defined(_16F1933) || defined(_16LF1933) || \
 		defined(_16F1934) || defined(_16LF1934) || \
 		defined(_16F1936) || defined(_16LF1936) || \
 		defined(_16F1937) || defined(_16LF1937) || \
 		defined(_16F1938) || defined(_16LF1938) || \
 		defined(_16F1939) || defined(_16LF1939) || \
 		defined(_16F631) || defined(_16F677) || defined(_16F685) || defined(_16F687) || defined(_16F688) || defined(_16F690) || \
 		defined(_16F684) || \
	 	defined(_16F882) || defined(_16F883) || defined(_16F884) || defined(_16F886) || defined(_16F887)
		OPTION_REG = (OPTION_REG & ~0x07) | (prescaler & 0x07);	//set prescaler - option's last three bits

#else
//		tmr0 prescaler bits in OPTION - on older chips
 		OPTION	 = (OPTION	 & ~0x07) | (prescaler & 0x07);	//set prescaler - option's last three bits
#endif
	}
	//tmr0_offset=-period;				//update tmr0_period
	TMR0 = 0;							//tmr0_offset;					//set the period
	T0IE = 0;							//don't turn on tmr0 interrupt yet
}

//activate the isr handler
void tmr0_act(void (*isr_ptr)(void)) {
	TMR0IF = 0;							//reset the flag
	T0IE = 1;							//enable interrupt
	_tmr0_isr_ptr=isr_ptr;				//activate the isr handler
}


