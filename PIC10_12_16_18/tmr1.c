//#include <htc.h>						//we use htc compiler
#include "tmr1.h"						//we use tmr1

#ifndef T1SOSCEN
#if defined(_16F1933) || defined(_16LF1933) || \
 	defined(_16F1934) || defined(_16LF1934) || \
 	defined(_16F1936) || defined(_16LF1936) || \
 	defined(_16F1937) || defined(_16LF1937) || \
 	defined(_16F1938) || defined(_16LF1938) || \
 	defined(_16F1939) || defined(_16LF1939)
#define T1SOSCEN		T1CONbits.T1OSCEN		//Microchip oddities
#else
#define T1SOSCEN		T1CONbits.SOSCEN	//Microchip oddities
#endif
#endif

static void empty_handler(void) {		//empty handler
	//do nothing
}

void (*_tmr1_isr_ptr)(void)=empty_handler;			//tmr0 isr handler pointer
unsigned short tmr1_offset=0x0000;

//tmr1 isr
void tmr1_isr(void) {
	TMR1IF = 0;							//clear the flag
	TMR1 = tmr1_offset;					//load the offset
	_tmr1_isr_ptr();					//run user interrupts
}
	
//initialize the timer1 (16bit)
void tmr1_init(unsigned char prescaler, unsigned short period) {
	TMR1ON = 0;							//turn off tmr1
	_tmr1_isr_ptr=empty_handler;		//point to default handler
	T1OSCEN = 0;						//t1 osc is disabled - count external pulse or internal pulse
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
	//TMR1CS1 = 0, TMR1CS0 = 0;			//count internal clock = Fosc / 4. 0b00
	//TMR1CS1 = 0, TMR1CS0 = 1;			//count internal clock = Fosc. 0b01
	TMR1CS1 = 1, TMR1CS0 = 0;			//count external pulse on T1CKI (RC0). 0b10
#else
	TMR1CS = 0;							//1 = count T1CKI; 0=count Fosc/4
#endif
	TMR1GE = 0;
	//T1GE = 0;							//tmr1 gate disabled
	T1CON = (T1CON & 0xcf) | ((prescaler & 0x03) << 4);	//set the prescaler
	nT1SYNC = 1;						//tmr1 asynchronuous
	TMR1IF = 0;							//clera the flag
	TMR1IE = 0;							//tmr1 interrupt on
	//PEIE=1;								//peripheral interrupt on
	tmr1_offset=-period;				//update tmr1_period
	TMR1H = tmr1_offset >> 8;			//set the period
	TMR1L = tmr1_offset & 0x00ff;
	
	//TMR1 gate control
	//T1GPOL = 1;							//count when t1g is set/1
	//T1GSS0 = 0, T1GSS1=0;				//0b00->use T1G as the gate source
	//TMR1GE = 1;							//enable t1g
	
	TMR1ON = 1;							//turn on tmr1
}

//activate the isr handler
void tmr1_act(void (*isr_ptr)(void)) {
	_tmr1_isr_ptr=isr_ptr;				//activate the isr handler
	TMR1IF = 0;							//clera the flag
	TMR1IE = 1;							//tmr1 interrupt on
	PEIE = 1;								//peripheral interrupt on
}
