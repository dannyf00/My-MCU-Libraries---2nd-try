#include "tmr1.h"						//we use tmr1

//empty handler
static void /*_tmr1_*/empty_handler(void) {
	//default tmr handler
}

//global variables
static void (* /*_tmr1*/_isr_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

void _ISR _T1Interrupt(void) {
	_T1IF=0;							//clear tmr1 interrupt flag
	/*_tmr1*/_isr_ptr();				//execute user tmr1 isr
}

//initialize the timer1 (16bit)
void tmr1_init(unsigned char ps) {
	_T1MD = 0;					//enable power to tmr
	_T1ON = 0;							//turn off rtc1
	/*_tmr1*/_isr_ptr=/*_tmr1_*/empty_handler;	//point to default handler
	//_rtc1_count=0;						//reset tmr1 isr counter
	//_rtc1_period=period;				//reset _rtc1_trigger
	PR1=/*period*/-1;						//minimum rtc resolution is 1ms
	_T1CS = 0;							//use internal clock = Fosc / 4
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	_T1CKPS=ps & TMR_PS_MASK;			//set prescaler to 1:1
	_T1GE = 0;							//rtc1 gate disabled
	//_T1IF = 0;							//reset the flag
	//_T1IE=1;							//rtc1 interrupt on
	//PEIE=1;								//peripheral interrupt on. no PEIE for PIC24 mcus
	TMR1 = 0;							//reset the timer/counter
	//TMR1L = 0;
	_T1ON = 1;							//turn on rtc1
}

//activate the isr handler
void tmr1_act(void (*isr_ptr)(void)) {
	/*_tmr1*/_isr_ptr=isr_ptr;			//activate the isr handler
	_T1IF = 0;							//reset the flag
	_T1IE=1;							//rtc1 interrupt on
}

