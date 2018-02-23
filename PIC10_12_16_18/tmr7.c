//#include <htc.h>						//we use htc compiler
#include "tmr7.h"						//we use tmr7

#ifndef T7SOSCEN
#define T7SOSCEN		T7CONbits.SOSCEN	//Microchip oddities
#endif

static void empty_handler(void) {		//empty handler
	//do nothing
}

void (*_tmr7_isr_ptr)(void)=empty_handler;			//tmr0 isr handler pointer
unsigned short tmr7_offset=0x0000;

//initialize the timer7 (16bit)
void tmr7_init(unsigned char prescaler, unsigned short period) {
	TMR7ON = 0;							//turn off tmr1
	_tmr7_isr_ptr=empty_handler;		//point to default handler
	T7SOSCEN = 0;						//t1 osc is disabled - count external pulse or internal pulse
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
	//TMR7CS1 = 0, TMR7CS0 = 0;			//count internal clock = Fosc / 4. 0b00
	TMR7CS1 = 0, TMR7CS0 = 1;			//count internal clock = Fosc. 0b01
	//TMR7CS1 = 1, TMR7CS0 = 0;			//count external pulse on T1CKI (RC0). 0b10
#else
	TMR7CS = 1;							//1 = count T1CKI; 0=count Fosc/4
#endif
	T7CON = (T7CON & 0xcf) | ((prescaler & 0x03) << 4);	//set the prescaler
	//T1GE = 0;							//tmr1 gate disabled
	nT7SYNC = 1;						//tmr1 asynchronuous
	TMR7IF = 0;							//clear the flag
	TMR7IE = 0;							//tmr1 interrupt on
	//PEIE = 1;							//peripheral interrupt on
	tmr7_offset=-period;				//update tmr1_period
	TMR7H = tmr7_offset >> 8;			//set the period
	TMR7L = tmr7_offset & 0x00ff;
	TMR7ON = 1;							//turn on tmr1
}

//activate the isr handler
void tmr7_act(void (*isr_ptr)(void)) {
	_tmr7_isr_ptr=isr_ptr;				//activate the isr handler
	TMR7IF = 0;							//clear the flag
	TMR7IE = 1;							//tmr1 interrupt on
	PEIE = 1;							//peripheral interrupt on
}
