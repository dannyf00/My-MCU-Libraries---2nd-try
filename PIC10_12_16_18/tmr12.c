//#include <htc.h>							//we use htc compiler
#include "tmr12.h"							//we use tmr6

static void empty_handler(void);

void (*_tmr12_isr_ptr)(void)=empty_handler;			//tmr2 isr handler pointer
//unsigned char tmr2_offset=0xff;

static void empty_handler(void) {			//empty handler
	//do nothing here
}

//initialize the timer1 (16bit)
void tmr12_init(unsigned char scaler, unsigned char period) {
	TMR12ON = 0;								//turn off tmr2
	_tmr12_isr_ptr=empty_handler;			//point to default handler
	//TMR2CS = 0;							//use internal clock = Fosc / 4
	TMR12 = 0;								//reset tmr2
	//TMR2ON = 1;							//turn on tmr2
	//T2CON = (T2CON & ~0x02) | (prescaler & 0x02);	//set the prescaler
	//T2CON = (T2CON & ~0xf8) | ((postscaler & 0xf0)>>1);	//set the postscaler
	T12CON = (scaler & 0x03) |				//set the prescaler
			((scaler & 0xf0) >> 1) |		//set the postscaler
			//(1<<2);						//turn on the timer
			0x00;
	PR12=period-1;							//update tmr2_period: PR2 is auto reloaded
	TMR12IF = 0;									 //clear tmr2 interrupt
	TMR12IE = 0;							//tmr2 interrupt on
	//PEIE=1;									//peripheral interrupt on
	TMR12ON = 1;									 //turn on tmr2
}

//activate the isr handler
void tmr12_act(void (*isr_ptr)(void)) {
	_tmr12_isr_ptr=isr_ptr;					//activate the isr handler
	TMR12IF = 0;									 //clear tmr2 interrupt
	TMR12IE=1;							//tmr2 interrupt on
	PEIE=1;									//peripheral interrupt on
}


