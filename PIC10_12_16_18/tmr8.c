//#include <htc.h>							//we use htc compiler
#include "tmr8.h"							//we use tmr8

static void empty_handler(void);

void (*_tmr8_isr_ptr)(void)=empty_handler;			//tmr2 isr handler pointer
//unsigned short tmr8_offset=0x0000;

static void empty_handler(void) {			//empty handler
	//do nothing here
}

//initialize the timer1 (16bit)
void tmr8_init(unsigned char scaler, unsigned char period) {
	TMR8ON = 0;								//turn off tmr2
	_tmr8_isr_ptr=empty_handler;			//point to default handler
	//TMR2CS = 0;							//use internal clock = Fosc / 4
	TMR8 = 0;								//reset tmr2
	//TMR2ON = 1;							//turn on tmr2
	//T2CON = (T2CON & ~0x02) | (prescaler & 0x02);	//set the prescaler
	//T2CON = (T2CON & ~0xf8) | ((postscaler & 0xf0)>>1);	//set the postscaler
	T8CON = (scaler & 0x03) |				//set the prescaler
			((scaler & 0xf0) >> 1) |		//set the postscaler
			//(1<<2);						//turn on the timer
			0x00;
	PR8=period-1;							//update tmr2_period: PR2 is auto reloaded
	TMR8IF = 0;									 //clear tmr2 interrupt
	TMR8IE = 0;							//tmr2 interrupt on
	//PEIE=1;									//peripheral interrupt on
	TMR8ON = 1;									 //turn on tmr2
}

//activate the isr handler
void tmr8_act(void (*isr_ptr)(void)) {
	_tmr8_isr_ptr=isr_ptr;					//activate the isr handler
	TMR8IF = 0;									 //clear tmr2 interrupt
	TMR8IE = 1;							//tmr2 interrupt on
	PEIE=1;									//peripheral interrupt on
}


