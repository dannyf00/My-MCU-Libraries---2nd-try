#include "tmr5.h"						//we use tmr

//empty handler
static void /*_tmr5_*/empty_handler(void) {
	//default tmr handler
}

static void (* /*_tmr5*/_isr_ptr)(void)=empty_handler;			//tmr_ptr pointing to empty_handler by default

void _ISR _T5Interrupt(void) {
	_T5IF=0;							//clear tmr3 interrupt flag
	/*_tmr5*/_isr_ptr();				//execute user tmr3 isr
}

//initialize the timer1 (16bit)
void tmr5_init(unsigned char ps) {
	_T5MD = 0;					//enable power to tmr
	_T5ON = 0;							//turn off rtc1
	/*_tmr5*/_isr_ptr=/*_tmr5_*/empty_handler;	//point to default handler
	PR5=/*period*/-1;						//minimum rtc resolution is 1ms
	_T5CS = 0;							//use internal clock = Fosc / 4
	//_T32 = 0;							//clock as two 16-bit timer/counter
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	_T5CKPS=ps & TMR_PS_MASK;					//set prescaler to 1:1
	_T5GE = 0;							//rtc1 gate disabled
	//_T5IF = 0;							//reset the flag
	//_T5IE=1;							//rtc1 interrupt on
	//PEIE=1;							//peripheral interrupt on. no PEIE for PIC24 mcus
	TMR5 = 0;							//reset the timer/counter
	//TMR1L = 0;
	_T5ON = 1;							//turn on rtc
}

//activate the isr handler
void tmr5_act(void (*isr_ptr)(void)) {
	/*_tmr5*/_isr_ptr=isr_ptr;			//activate the isr handler
	_T5IF = 0;							//reset the flag
	_T5IE=1;							//rtc1 interrupt on
}
