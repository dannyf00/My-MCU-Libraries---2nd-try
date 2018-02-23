//#include <htc.h>						//we use htc compiler
#include "tmr5.h"						//we use tmr5

#ifndef T5SOSCEN
#if		defined (_18F23K22) || defined (_18F24K22) || defined (_18F25K22) || defined (_18F26K22) || \
		defined (_18F43K22) || defined (_18F44K22) || defined (_18F45K22) || defined (_18F46K22) || \
		defined (_18LF23K22) || defined (_18LF24K22) || defined (_18LF25K22) || defined (_18LF26K22) || \
		defined (_18LF43K22) || defined (_18LF44K22) || defined (_18LF45K22) || defined (_18LF46K22)
#define T5SOSCEN		T5CONbits.T5SOSCEN	//Microchip oddities
#else
#define T5SOSCEN		T5CONbits.SOSCEN	//Microchip oddities
#endif
#endif

static void empty_handler(void) {		//empty handler
	//do nothing
}

void (*_tmr5_isr_ptr)(void)=empty_handler;			//tmr0 isr handler pointer
unsigned short tmr5_offset=0x0000;

//initialize the timer5 (16bit)
void tmr5_init(unsigned char prescaler, unsigned short period) {
	TMR5ON = 0;							//turn off tmr1
	_tmr5_isr_ptr=empty_handler;		//point to default handler
	T5SOSCEN = 0;						//t1 osc is disabled - count external pulse or internal pulse
#if defined(_16F1933) || defined(_16LF1933) || \
 	defined(_16F1934) || defined(_16LF1934) || \
 	defined(_16F1936) || defined(_16LF1936) || \
 	defined(_16F1937) || defined(_16LF1937) || \
 	defined(_16F1938) || defined(_16LF1938) || \
 	defined(_16F1939) || defined(_16LF1939) || \
    defined (_18F23K22) || defined (_18F24K22) || defined (_18F25K22) || defined (_18F26K22) || \
    defined (_18F43K22) || defined (_18F44K22) || defined (_18F45K22) || defined (_18F46K22) || \
    defined (_18LF23K22) || defined (_18LF24K22) || defined (_18LF25K22) || defined (_18LF26K22) || \
    defined (_18LF43K22) || defined (_18LF44K22) || defined (_18LF45K22) || defined (_18LF46K22) || \
    defined (_18F65K90) || defined (_18F66K90) || defined (_18F67K90) || \
    defined (_18F85K90) || defined (_18F86K90) || defined (_18F87K90)
	//TMR5CS1 = 0, TMR5CS0 = 0;			//count internal clock = Fosc / 4. 0b00
	TMR5CS1 = 0, TMR5CS0 = 1;			//count internal clock = Fosc. 0b01
	//TMR5CS1 = 1, TMR5CS0 = 0;			//count external pulse on T1CKI (RC0). 0b10
#else
	TMR5CS = 1;							//1 = count T1CKI; 0=count Fosc/4
#endif
	T5CON = (T5CON & 0xcf) | ((prescaler & 0x03) << 4);	//set the prescaler
	//T1GE = 0;							//tmr1 gate disabled
	nT5SYNC = 1;						//tmr1 asynchronuous
	TMR5IF = 0;							//clear the flag
	TMR5IE = 0;							//tmr1 interrupt on
	//PEIE = 1;							//peripheral interrupt on
	tmr5_offset=-period;				//update tmr1_period
	TMR5H = tmr5_offset >> 8;			//set the period
	TMR5L = tmr5_offset & 0x00ff;
	
	//TMR1 gate control
	//T1GPOL = 1;							//count when t1g is set/1
	//T1GSS0 = 0, T1GSS1=0;				//0b00->use T1G as the gate source
	//TMR1GE = 1;							//enable t1g
	
	TMR5ON = 1;							//turn on tmr1
}

//activate the isr handler
void tmr5_act(void (*isr_ptr)(void)) {
	_tmr5_isr_ptr=isr_ptr;				//activate the isr handler
	TMR5IF = 0;							//clear the flag
	TMR5IE = 1;							//tmr1 interrupt on
	PEIE = 1;							//peripheral interrupt on
}
