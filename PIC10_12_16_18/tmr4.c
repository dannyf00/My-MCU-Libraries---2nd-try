//#include <htc.h>							//we use htc compiler
#include "tmr4.h"							//we use tmr4

static void empty_handler(void) {			//empty handler
	//do nothing here
}

void (*tmr4_isr)(void) = empty_handler;			//tmr2 isr handler pointer
//unsigned char tmr2_offset=0xff;

//initialize the timer1 (16bit)
void tmr4_init(unsigned char scaler, unsigned char period) {
	TMR4ON = 0;								//turn off tmr2
	tmr4_isr=empty_handler;			//point to default handler
	//TMR2CS = 0;							//use internal clock = Fosc / 4
	TMR4 = 0;								//reset tmr2
	//TMR2ON = 1;							//turn on tmr2
	//T2CON = (T2CON & ~0x02) | (prescaler & 0x02);	//set the prescaler
	//T2CON = (T2CON & ~0xf8) | ((postscaler & 0xf0)>>1);	//set the postscaler
	T4CON = (scaler & 0x03) |				//set the prescaler
			((scaler & 0xf0) >> 1) |		//set the postscaler
			//(1<<2);						//turn on the timer
			0x00;
	PR4=period-1;							//update tmr2_period: PR2 is auto reloaded
	TMR4IF = 0;									 //clear tmr2 interrupt
	TMR4IE = 0;							//tmr2 interrupt on
	//PEIE=1;									//peripheral interrupt on
	TMR4ON = 1;									 //turn on tmr2
}

//activate the isr handler
void tmr4_act(void (*isr_ptr)(void)) {
	tmr4_isr=isr_ptr;					//activate the isr handler
	TMR4IF = 0;									 //clear tmr2 interrupt
	TMR4IE = 1;							//tmr2 interrupt on
	PEIE=1;									//peripheral interrupt on
}


