#include "tmr2.h"						//we use tmr1

//empty handler
static void /*_tmr2_*/empty_handler(void) {
	//default tmr handler
}

static void (* /*_tmr2*/_isr_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

void _ISR _T2Interrupt(void) {
	_T2IF=0;							//clear tmr1 interrupt flag
	/*_tmr2*/_isr_ptr();				//execute user tmr1 isr
}

//initialize the timer1 (16bit)
void tmr2_init(unsigned char ps) {
	_T2MD = 0;					//enable power to tmr
	_T2ON = 0;							//turn off rtc1
	/*_tmr2*/_isr_ptr=/*_tmr2_*/empty_handler;	//point to default handler
	//_rtc2_count=0;						//reset tmr1 isr counter
	//_rtc2_period=period;				//reset _rtc1_trigger
	PR2=/*period*/-1;							//minimum rtc resolution is 1ms
	_T2CS = 0;							//use internal clock = Fosc / 4
	_T2_32 = 0;							//clock as two 16-bit timer/counter
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	_T2CKPS=ps & TMR_PS_MASK;			//set prescaler to 1:1
	_T2GE = 0;							//rtc1 gate disabled
	//_T2IF = 0;							//reset the flag
	//_T2IE=1;							//rtc1 interrupt on
	//PEIE=1;								//peripheral interrupt on. no PEIE for PIC24 mcus
	TMR2 = 0;							//reset the timer/counter
	//TMR1L = 0;
	_T2ON = 1;							//turn on rtc1
}

//activate the isr handler
void tmr2_act(void (*isr_ptr)(void)) {
	/*_tmr2*/_isr_ptr=isr_ptr;			//activate the isr handler
	_T2IF = 0;							//reset the flag
	_T2IE=1;							//rtc1 interrupt on
}
