//#include <p24fxxxx.h>					//we use C30 compiler
//#include "gpio.h"
#include "systick.h"					//we use systick / systick

//hardware configuration
#define SYSTICK_TIMER 		1		//use Timerx as timebase for systick. 1..5
//end hardware configuration

//for compatibility reasons
#if   SYSTICK_TIMER == 1
#define _TxON				T1CONbits.TON
#define _TxCS				T1CONbits.TCS
#define _TxGE				T1CONbits.TGATE
#define _TxCKPS				T1CONbits.TCKPS
#define _TxIE				IEC0bits.T1IE
#define _TxIF				IFS0bits.T1IF			//tmr1 overflow flag
#define TMRx				TMR1
#define PRx					PR1
#define _TxMD				_T1MD

#elif SYSTICK_TIMER == 2
#define _TxON				T2CONbits.TON
#define _TxCS				T2CONbits.TCS
#define _TxGE				T2CONbits.TGATE
#define _TxCKPS				T2CONbits.TCKPS
#define _TxIE				IEC0bits.T2IE
#define _TxIF				IFS0bits.T2IF			//tmr1 overflow flag
#define TMRx				TMR2
#define PRx					PR2
#define _TxMD				_T2MD

#elif SYSTICK_TIMER == 3
#define _TxON				T3CONbits.TON
#define _TxCS				T3CONbits.TCS
#define _TxGE				T3CONbits.TGATE
#define _TxCKPS				T3CONbits.TCKPS
#define _TxIE				IEC0bits.T3IE
#define _TxIF				IFS0bits.T3IF			//tmr1 overflow flag
#define TMRx				TMR3
#define PRx					PR3
#define _TxMD				_T3MD

#elif SYSTICK_TIMER == 4
#define _TxON				T4CONbits.TON
#define _TxCS				T4CONbits.TCS
#define _TxGE				T4CONbits.TGATE
#define _TxCKPS				T4CONbits.TCKPS
#define _TxIE				IEC1bits.T4IE
#define _TxIF				IFS1bits.T4IF			//tmr1 overflow flag
#define TMRx				TMR4
#define PRx					PR4
#define _TxMD				_T4MD

#elif SYSTICK_TIMER == 5
#define _TxON				T5CONbits.TON
#define _TxCS				T5CONbits.TCS
#define _TxGE				T5CONbits.TGATE
#define _TxCKPS				T5CONbits.TCKPS
#define _TxIE				IEC1bits.T5IE
#define _TxIF				IFS1bits.T5IF			//tmr1 overflow flag
#define TMRx				TMR5
#define PRx					PR5
#define _TxMD				_T5MD

#else
#warning "SYSTICK timer definition not valid"
#endif

//empty handler
static void /*_systick_*/empty_handler(void) {
	//default tmr handler
}

//global variables
static volatile unsigned long _systick_count=0;

static void (* /*_systick*/_isr_ptr)(void)=empty_handler;				//systick_ptr pointing to empty_handler by default

//default systick handler
#if   SYSTICK_TIMER == 1
void _ISR _T1Interrupt(void) {
#elif SYSTICK_TIMER == 2
void _ISR _T2Interrupt(void) {
#elif SYSTICK_TIMER == 3
void _ISR _T3Interrupt(void) {
#elif SYSTICK_TIMER == 4
void _ISR _T4Interrupt(void) {
#elif SYSTICK_TIMER == 5
void _ISR _T5Interrupt(void) {
#else
#warning "SYSTICK Timer definition not valid"
void _ISR _T1Interrupt(void) {			//default to timer1
#endif
	_TxIF=0;							//clear tmr1 interrupt flag
	_systick_count+=1;					//increment systick_count
	/*_tmr1*/_isr_ptr();				//execute user tmr1 isr
}

//initialize the timer1 (16bit)
void systick_init(unsigned short period) {
	/*_systick*/_isr_ptr=/*_systick_*/empty_handler;	//point to default handler
	_systick_count=0;					//reset systick
	//tmrx_init(TMR_PS_1x, period);
	_TxMD = 0;					//enable power to tmr
	_TxON = 0;							//turn off rtc1
	/*_tmr1*/_isr_ptr=/*_tmr1_*/empty_handler;	//point to default handler
	//_rtc1_count=0;						//reset tmr1 isr counter
	//_rtc1_period=period;				//reset _rtc1_trigger
	PRx=period-1;						//minimum rtc resolution is 1ms
	_TxCS = 0;							//use internal clock = Fosc / 4
	//T1CON = (T1CON & 0xcf) | ((TMR1_PS_1x & 0x03) << 4);	//set the prescaler
	_TxCKPS=/*ps*/TMR_PS_1x & TMR_PS_MASK;			//set prescaler to 1:1
	_TxGE = 0;							//rtc1 gate disabled

	//enable interrupts here so systick_act() doesn't have to be called
	//for systick_get() to work
	_TxIF = 0;							//reset the flag
	_TxIE=1;							//rtc1 interrupt on
	//PEIE=1;								//peripheral interrupt on. no PEIE for PIC24 mcus
	TMRx = 0;							//reset the timer/counter
	//TMR1L = 0;
	_TxON = 1;							//turn on rtc1
}

//activate the isr handler
void systick_act(void (*isr_ptr)(void)) {
	//tmrx_act(systick_handler);		//install default handler
	/*_systick*/_isr_ptr=isr_ptr;		//activate the isr handler
	//_T1IF = 0;							//reset the flag
	//_T1IE=1;							//rtc1 interrupt on
}

//SysTick is count-down and TMRx is count-up
unsigned long systick_get(void)  {
#if 0									//maintain atomicity
	unsigned long systick_val, systick_count;

	do {
		systick_count = _systick_count;
		systick_val = TMRx;				//SysTick->VAL;
	} while (systick_count ^ _systick_count);
	return (systick_count * (unsigned long) (PRx/*SysTick->LOAD*/ + 1) + ( systick_val/*SysTick->VAL*/)) / (SYSTICK_ms / 1000ul);

#else									//no atomicity but faster
	//return (_systick_count * (SysTick->LOAD + 1) + ((SysTick->LOAD + 1) - SysTick->VAL)) / (F_CPU / 1000);
	return (_systick_count * (unsigned long) (PRx/*SysTick->LOAD*/ + 1) + ( TMRx/*SysTick->VAL*/)) / (SYSTICK_ms / 1000ul);
	//return ((_systick_count + 1) * (unsigned long) (PRx/*SysTick->LOAD*/ + 1) - ( TMRx/*SysTick->VAL*/)) / (F_CPU / 1000000ul);
#endif

}
