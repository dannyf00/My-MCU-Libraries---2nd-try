#include "tmr4.h"						//we use tmr1

//empty handler
static void /*_tmr4_*/empty_handler(void) {
	//default tmr handler
}

static void (* /*_tmr4*/_isr_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

void _ISR _T4Interrupt(void) {
	_T4IF=0;							//clear tmr1 interrupt flag
	/*_tmr4*/_isr_ptr();				//execute user tmr1 isr
}

//initialize the timer1 (16bit)
void tmr4_init(unsigned char ps) {
	_T4MD = 0;					//enable power to tmr
	_T4ON = 0;							//turn off rtc1
	/*_tmr4*/_isr_ptr=/*_tmr4_*/empty_handler;	//point to default handler
	PR4=/*period*/-1;						//minimum rtc resolution is 1ms
	_T4CS = 0;							//use internal clock = Fosc / 4
	_T4_32 = 0;							//clock as two 16-bit timer/counter
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	_T4CKPS=ps & TMR_PS_MASK;			//set prescaler to 1:1
	_T4GE = 0;							//rtc1 gate disabled
	//_T4IF = 0;							//reset the flag
	//_T4IE=1;							//rtc1 interrupt on
	//PEIE=1;								//peripheral interrupt on. no PEIE for PIC24 mcus
	TMR4 = 0;							//reset the timer/counter
	//TMR1L = 0;
	_T4ON = 1;							//turn on rtc1
}

//activate the isr handler
void tmr4_act(void (*isr_ptr)(void)) {
	/*_tmr4*/_isr_ptr=isr_ptr;			//activate the isr handler
	_T4IF = 0;							//reset the flag
	_T4IE=1;							//rtc1 interrupt on
}
