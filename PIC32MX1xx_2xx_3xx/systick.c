#include "systick.h"							//we use tmr1 as systick / time base generator

//configuration
//no user configurable parameters
//end configuration

//for compatibility reasons and easy porting
#define _T1MD				PMD4bits.T1MD		//t1md
#define _TxON				T1CONbits.TON		//tmr on
#define _TxCS				T1CONbits.TCS		//tmr source
#define _TxGE				T1CONbits.TGATE		//timer gate enable
#define _TxCKPS				T1CONbits.TCKPS		//tmr prescaler
#define _Tx_32				T1CONbits.T32		//32-bit timer if set
#define _TxIE				IEC0bits.T1IE		//tmr interrupt enable
#define _TxIF				IFS0bits.T1IF		//tmr1 overflow flag
#define _TxIP				IPC1bits.T1IP		//t1 interrupt priority
#define _TxIS				IPC1bits.T1IS		//t1 interrupt sub-priority
#define _PRx				PR1					//period
#define _TMRx				TMR1				//counter
#define _TxIPL				IPL2				//default isr priority levels
#define TxIP_DEFAULT		2					//default interrupt priority - lowest
#define TxIS_DEFAULT		0					//default interrupt subpriority

//global defines

//global variables
volatile uint32_t systickovf_counter=0;			//systick overflow counter

void __ISR(_TIMER_1_VECTOR, _TxIPL) _T1Interrupt(void) {
//void __ISR(_TIMER_1_VECTOR, IPL2SOFT) Timer1Handler(void) {
	_TxIF=0;							//clear tmr1 interrupt flag
	systickovf_counter+=0x10000ul;		//advance systick overflow counter, 16-bit timer
}

//initialize the timer1 (16bit)
void systick_init(void) {
	_T1MD = 0;							//enable power to tmr
	_TxON = 0;							//turn off rtc1
	_TxCS = 0;							//use internal clock = Fosc
	_TxCKPS=0x00;						//ps & TMR1_PS_MASK;			//set prescaler to 1:1
	_TxGE = 0;							//'0'->timer not gated
	_TMRx = 0;							//reset the timer/counter
	_PRx=0xffff;						//16-bit prescaler

	_TxIP = TxIP_DEFAULT;
	_TxIS = TxIS_DEFAULT;
	_TxIF = 0;							//reset the flag
	_TxIE = 1;							//'1'->enable interrupt

	_TxON = 1;							//turn on rtc1
}

//return timer clicks
//execution time = 30 ticks, no optimization
uint32_t systicks(void) {
	uint32_t m;
	uint16_t f;							//16-bit counter

	//do a double read
	do {
		m = systickovf_counter;			//read the overflow counter
		f = _TMRx;						//read the least significant 16-bits
	} while (m != systickovf_counter);	//gaurd against overflow

	return (m | f) << 0;				//prescaler is 1:1
}

//return micros()

//return millis

//delay ms using SysTick ticks()
void systick_delayms(uint32_t ms) {
	uint32_t start_time = ticks();

	ms *= cyclesPerMillisecond();				//convert ms to ticks
	while (ticks() - start_time < ms) continue;	//wait for timer to expire
}

//delay using SysTick ticks()
void systick_delayus(uint32_t us) {
	uint32_t start_time = ticks();

	us *= cyclesPerMicrosecond();				//convert ms to ticks
	while (ticks() - start_time < us) continue;	//wait for timer to expire
}

//delay using SysTick ticks()
void systick_delay(uint32_t tk) {
	uint32_t start_time = ticks();

	//us *= cyclesPerMicrosecond();				//convert ms to ticks
	while (ticks() - start_time < tk) continue;	//wait for timer to expire
}
