#include "tmr3.h"						//we use tmr

//#define RTC_PERIOD			RTC_1ms		//rtc resolutoin

//empty handler
static void /*_tmr3_*/empty_handler(void) {
	//default tmr handler
}

static void (* /*_tmr3*/_isr_ptr)(void)=empty_handler;			//tmr_ptr pointing to empty_handler by default

void _ISR _T3Interrupt(void) {
	_T3IF=0;							//clear tmr3 interrupt flag
	/*_tmr3*/_isr_ptr();				//execute user tmr3 isr
}

//initialize the timer1 (16bit)
void tmr3_init(unsigned char ps) {
	_T3MD = 0;					//enable power to tmr
	_T3ON = 0;							//turn off rtc1
	/*_tmr3*/_isr_ptr=/*_tmr3_*/empty_handler;	//point to default handler
	PR3=/*period*/-1;						//minimum rtc resolution is 1ms
	_T3CS = 0;							//use internal clock = Fosc / 4
	//_T3_32 = 0;							//clock as two 16-bit timer/counter
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	_T3CKPS=ps & TMR_PS_MASK;					//set prescaler to 1:1
	_T3GE = 0;							//rtc1 gate disabled
	//_T3IF = 0;							//reset the flag
	//_T3IE=1;							//rtc1 interrupt on
	//PEIE=1;							//peripheral interrupt on. no PEIE for PIC24 mcus
	TMR3 = 0;							//reset the timer/counter
	//TMR1L = 0;
	_T3ON = 1;							//turn on rtc
}

//activate the isr handler
void tmr3_act(void (*isr_ptr)(void)) {
	/*_tmr3*/_isr_ptr=isr_ptr;			//activate the isr handler
	_T3IF = 0;							//reset the flag
	_T3IE=1;							//rtc1 interrupt on
}
