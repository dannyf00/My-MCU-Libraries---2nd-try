#include "tmr3.h"						//we use tmr3

//for compatibility reasons and easy porting
#define _TxON				T3CONbits.TON		//tmr on
#define _TxCS				T3CONbits.TCS		//tmr source
#define _TxGE				T3CONbits.TGATE		//timer gate enable
#define _TxCKPS				T3CONbits.TCKPS		//tmr prescaler
#define _Tx_32				T3CONbits.T32		//32-bit timer if set
#define _TxIE				IEC0bits.T3IE		//tmr interrupt enable
#define _TxIF				IFS0bits.T3IF		//tmr1 overflow flag
#define _TxIP				IPC3bits.T3IP		//t1 interrupt priority
#define _TxIS				IPC3bits.T3IS		//t1 interrupt sub-priority
#define _PRx				PR3					//period
#define _TMRx				TMR3				//counter
#define _TxIPL				IPL2				//default isr priority levels
#define TxIP_DEFAULT		2					//default interrupt priority - lowest
#define TxIS_DEFAULT		0					//default interrupt subpriority

//empty handler
static void /*_tmr1_*/empty_handler(void) {
	//default tmr handler
}

//global variables
static void (* /*_tmr1*/_isr_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

void __ISR(_TIMER_3_VECTOR, _TxIPL) _T3Interrupt(void) {
//void __ISR(_TIMER_1_VECTOR, IPL2SOFT) Timer1Handler(void) {
	_TxIF=0;							//clear tmr1 interrupt flag
	//IFS0CLR = 0x0010;
	//LATB ^= 1<<0;
	/*_tmr1*/_isr_ptr();				//execute user tmr1 isr
}

//initialize the timer1 (16bit)
void tmr3_init(unsigned char ps, unsigned short period) {
	//_T1MD = 0;					//enable power to tmr
	_TxON = 0;							//turn off rtc1
	/*_tmr1*/_isr_ptr=/*_tmr1_*/empty_handler;	//point to default handler
	//_rtc1_count=0;						//reset tmr1 isr counter
	//_rtc1_period=period;				//reset _rtc1_trigger
	_PRx=period-1;						//minimum rtc resolution is 1ms
	_TxCS = 0;							//use internal clock = Fosc
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	_TxCKPS=ps & TMR_PS_MASK;			//set prescaler to 1:1
	_TxGE = 0;							//rtc1 gate disabled
	_TxIF = 0;							//reset the flag
	_TxIE = 0;							//rtc1 interrupt off
	//PEIE=1;								//peripheral interrupt on. no PEIE for PIC24 mcus
	_TMRx = 0;							//reset the timer/counter
	//TMR1L = 0;
	_TxON = 1;							//turn on rtc1
}

//activate the isr handler
void tmr3_act(void (*isr_ptr)(void)) {
	/*_tmr1*/_isr_ptr=isr_ptr;			//activate the isr handler
	_TxIP = TxIP_DEFAULT;
	_TxIS = TxIS_DEFAULT;
	_TxIF = 0;							//reset the flag
	_TxIE = 1;							//rtc1 interrupt on
}

