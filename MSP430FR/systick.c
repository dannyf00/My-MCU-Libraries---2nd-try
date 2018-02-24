#include "systick.h"							//we use tmra3_ccr0 as systick generator

//hardware configuration
//end hardware configuration

//global defines
//for easy portability
#define TAx					TIMERA3				//specify which timer is used for systick
/*
#define TAxCTL				TA3CTL			//timera control
#define TAxR				TA3R			//timer / counter
#define TAxIV				TA3IV			//interrupt flag
#define TAxEX0				TA3EX0			//expansion register

#define TAxCCTL0			TA3CCTL0		//timer0 compare control
#define TAxCCTL1			TA3CCTL1		//timer1 cmpare control
#define TAxCCTL2			TA3CCTL2		//timer2 compare control
#define TAxCCTL3			TA3CCTL3		//timer0 compare control
#define TAxCCTL4			TA3CCTL4		//timer1 cmpare control
#define TAxCCTL5			TA3CCTL5		//timer2 compare control
#define TAxCCTL6			TA3CCTL6		//timer0 compare control
#define TAxCCR0				TA3CCR0			//timer0 compare register
#define TAxCCR1				TA3CCR1			//timer1 compare register
#define TAxCCR2				TA3CCR2			//timer2 compare register
#define TAxCCR3				TA3CCR3			//timer0 compare register
#define TAxCCR4				TA3CCR4			//timer1 compare register
#define TAxCCR5				TA3CCR5			//timer2 compare register
#define TAxCCR6				TA3CCR6			//timer0 compare register
*/
//empty handler
static void /*_tmr1_*/empty_handler(void) {
	//default tmr handler - do nothing here
}

//global variables
static void (* /*_tmr1*/_isrptr_ccr0)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ccr1)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ccr2)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ccr3)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ccr4)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ccr5)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ccr6)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
//static void (* /*_tmr1*/_isrptr_ta)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

//period registers
static unsigned short _ccr0_pr=0xffff;			//ccr0 saved
static unsigned short _ccr1_pr=0xffff;			//ccr1 saved
static unsigned short _ccr2_pr=0xffff;			//ccr2 saved
static unsigned short _ccr3_pr=0xffff;			//ccr3 saved
static unsigned short _ccr4_pr=0xffff;			//ccr4 saved
static unsigned short _ccr5_pr=0xffff;			//ccr5 saved
static unsigned short _ccr6_pr=0xffff;			//ccr6 saved

//global variables
volatile uint32_t systickovf_counter=0x00;		//systick counter

// Timer A0 interrupt service routine, ccr0
#pragma vector=TIMER3_A0_VECTOR
__interrupt void _ISRTimer3_A0 (void) {
	TAx->CCR0 += _ccr0_pr;						//update TxCCR0 -> continuous mode
	TAx->CCTL0&=~CCIFG;							//clear the flag
	/*_tmr1*/_isrptr_ccr0();					//execute user tmr1 isr
}

// Timer A1 interrupt service routine, ccr1..6, ia
#pragma vector=TIMER3_A1_VECTOR
__interrupt void _ISRTimer3_A1 (void) {
	switch (TAx->IV) {
		case 0x02: 	TAx->CCR1+=_ccr1_pr; TAx->CCTL1 &=~CCIFG; _isrptr_ccr1(); break;		//0x02 -> ccr1
		case 0x04: 	TAx->CCR2+=_ccr2_pr; TAx->CCTL2 &=~CCIFG; _isrptr_ccr2(); break;		//0x04 -> ccr2
		case 0x06: 	TAx->CCR3+=_ccr3_pr; TAx->CCTL3 &=~CCIFG; _isrptr_ccr3(); break;		//0x04 -> ccr2
		case 0x08: 	TAx->CCR4+=_ccr4_pr; TAx->CCTL4 &=~CCIFG; _isrptr_ccr4(); break;		//0x04 -> ccr2
		case 0x0a: 	TAx->CCR5+=_ccr5_pr; TAx->CCTL5 &=~CCIFG; _isrptr_ccr5(); break;		//0x04 -> ccr2
		case 0x0c: 	TAx->CCR6+=_ccr6_pr; TAx->CCTL6 &=~CCIFG; _isrptr_ccr6(); break;		//0x04 -> ccr2
		//ta0 overflow
		case 0x0e: 	TAx->CTL &=~TAIFG; systickovf_counter+= 0x10000ul; break;				//16 bit counter, 1:1 prescaler
		default: break;
	}
}

//initialize timer_a3
//continous mode
//prescaler + postscaler both at 1:1
//enable overflow interrupt
//top at 0xffff
//disable other interrupts
void systick_init(void) {
	//reset the variables
	systickovf_counter=0;						//reset systick overflow counter
	_ccr0_pr=_ccr1_pr=_ccr2_pr=_ccr3_pr=_ccr4_pr=_ccr5_pr=_ccr6_pr=0xffff;
	_isrptr_ccr0=_isrptr_ccr1=_isrptr_ccr2=_isrptr_ccr3=_isrptr_ccr4=_isrptr_ccr5=_isrptr_ccr6=empty_handler;
	
	//clear the timer control register
	TAx->CTL |= TACLR;							//TxCTL_bit.TACLR;						//set to reset / stop the timer

	//stop timer
	TAx->CTL &=~MC_0;							//TxCTL_bit.TAMC = 0x00;				//timer mode - 0x00: halted, 0x01: up mode, 0x02: continuous mode (to 0xffff), 0x03: up/down
	//TxCTL |= TASSEL_2;						//TxCTL_bit.TASSEL = 0x02;				//timer source - 0x00: TACLK, 0x01: ACLK, 0x02: SMCLK, 0x03: INCLK
	//TxCTL |= (ps & ID_3);						//TxCTL_bit.TAID = ps & 0x03;			//input divider - 0x00: /1, 0x01: /2, 0x02: /4, 0x03: /8
	//TxCTL &=~TAIE;							//TxCTL_bit.TAIE = 0;					//timer a interrupt enable: 0: interrupt disabled; 1: interrupt enabled;
	TAx->CTL &=~TAIFG;							//TxCTL_bit.TAIFG = 0;					//interrupt flag: 0= no interrupt pending; 1=interrupt pending
	//TxCTL |= OUTMOD0;							//set output mode to zero
#if defined(TA3EX0_)
	TAx->EX0 = (TMRA_EX1x & TMRA_EX8x);		//set expansion divider at 1x
#endif

	//set up match register
	TAx->CCR0 = TAx->CCR2 = TAx->CCR3 = TAx->CCR4 = TAx->CCR5 = TAx->CCR6 = 0xffff/2;						//match point in the middle of counter
	
	//clear ccifg flag and disable the compare interrupt
	TAx->CCTL0 &=~(CCIE | CCIFG);					//clear the flag
	TAx->CCTL1 &=~(CCIE | CCIFG);					//clear the flag
	TAx->CCTL2 &=~(CCIE | CCIFG);					//clear the flag
	TAx->CCTL3 &=~(CCIE | CCIFG);					//clear the flag
	TAx->CCTL4 &=~(CCIE | CCIFG);					//clear the flag
	TAx->CCTL5 &=~(CCIE | CCIFG);					//clear the flag
	TAx->CCTL6 &=~(CCIE | CCIFG);					//clear the flag

	//set up TAxCCTLx register
	//TAx->CCTL0 = 	CM_0 |						//0=no capture
	//			CCIS_0 |					//0=input is CCIxA
	//			(0 << 11) |					//0=asynchronous, 1=synchronous
	//			(0 << 8) |					//0=compare, 1=capture
	//			OUTMOD_0 |					//0=OUTBIT
	//			(1 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
	//			(0 << 2) |					//0=OUT is low, 1=OUT is high
	//			(0x00);
	TAx->CTL = TASSEL_2 |					//0=TACLK, 1=ACLK, 2=SMCLK, and 3=INCLK
				(TMRA_PS1x & TMRA_PS8x) |	//prescaler = 1x
				MC_2 |						//0=stop, 1=up to ccr0, 2=continous mode, 3=up and down
				TAIE |						//1=overflow interrupt enabled, 0=TCIE disabled
				0x00;
	//timer is running now
}

//get systick count
uint32_t systicks(void) {
	uint32_t m;
	uint16_t f;							//TA3 is a 16-bit counter

	//do a double read
	do {
		m = systickovf_counter;			//read the overflow counter
		f = TAx->R;						//SysTick->VAL;				//read the least significant 16-bits
	} while (m != systickovf_counter);	//guard against overflow

	return (m | f) << 0;				//systick is a 16_bit counter
}

//delay cnt using SysTick ticks()
//watch out for overflow - max = 2^32/(F_CPU / 1000)
void systick_delay(uint32_t cnt) {
	uint32_t start_time = ticks();

	//ms *= cyclesPerMillisecond();				//convert ms to ticks
	while (ticks() - start_time < cnt) continue;	//wait for timer to expire
}

//delay ms using SysTick ticks()
//watch out for overflow - max = 2^32/(F_CPU / 1000)
void systick_delayms(uint32_t ms) {
	uint32_t start_time = ticks();

	ms *= cyclesPerMillisecond();				//convert ms to ticks
	while (ticks() - start_time < ms) continue;	//wait for timer to expire
}

//delay using SysTick ticks()
//watch out for overflow - max = 2^32/(F_CPU / 1000000)
void systick_delayus(uint32_t us) {
	uint32_t start_time = ticks();

	us *= cyclesPerMicrosecond();				//convert ms to ticks
	while (ticks() - start_time < us) continue;	//wait for timer to expire
}

//enable compare interrupt
void systick_setpr0(uint16_t pr) {
	_ccr0_pr = pr - 1;
	TAx->CCR0 = TAx->R + _ccr0_pr;			//set the next match point
}

//install handler 
void systick_act0(void (*isr_ptr)(void)) {
	_isrptr_ccr0=isr_ptr;						//install the user handler
	TAx->CCTL0 &=~CCIFG;						//clear the timer flag
	TAx->CCTL0 |= CCIE;							//enable timer interrupt
}

//enable compare interrupt
void systick_setpr1(uint16_t pr) {
	_ccr1_pr = pr - 1;
	TAx->CCR1 = TAx->R + _ccr1_pr;			//set the next match point
}

//install handler
void systick_act1(void (*isr_ptr)(void)) {
	_isrptr_ccr1=isr_ptr;						//install the user handler
	TAx->CCTL1 &=~CCIFG;						//clear the timer flag
	TAx->CCTL1 |= CCIE;							//enable timer interrupt
}

//enable compare interrupt
void systick_setpr2(uint16_t pr) {
	_ccr2_pr = pr - 1;
	TAx->CCR2 = TAx->R + _ccr2_pr;			//set the next match point
}

//install handler
void systick_act2(void (*isr_ptr)(void)) {
	_isrptr_ccr2=isr_ptr;						//install the user handler
	TAx->CCTL2 &=~CCIFG;						//clear the timer flag
	TAx->CCTL2 |= CCIE;							//enable timer interrupt
}

//enable compare interrupt
void systick_setpr3(uint16_t pr) {
	_ccr3_pr = pr - 1;
	TAx->CCR3 = TAx->R + _ccr3_pr;			//set the next match point
}

//install handler
void systick_act3(void (*isr_ptr)(void)) {
	_isrptr_ccr3=isr_ptr;						//install the user handler
	TAx->CCTL3 &=~CCIFG;						//clear the timer flag
	TAx->CCTL3 |= CCIE;							//enable timer interrupt
}

//enable compare interrupt
void systick_setpr4(uint16_t pr) {
	_ccr4_pr = pr - 1;
	TAx->CCR4 = TAx->R + _ccr4_pr;			//set the next match point
}

//install handler
void systick_act4(void (*isr_ptr)(void)) {
	_isrptr_ccr4=isr_ptr;						//install the user handler
	TAx->CCTL4 &=~CCIFG;						//clear the timer flag
	TAx->CCTL4 |= CCIE;							//enable timer interrupt
}

//enable compare interrupt
void systick_setpr5(uint16_t pr) {
	_ccr5_pr = pr - 1;
	TAx->CCR5 = TAx->R + _ccr5_pr;			//set the next match point
}

//install handler
void systick_act5(void (*isr_ptr)(void)) {
	_isrptr_ccr5=isr_ptr;						//install the user handler
	TAx->CCTL5 &=~CCIFG;						//clear the timer flag
	TAx->CCTL5 |= CCIE;							//enable timer interrupt
}

//enable compare interrupt
void systick_setpr6(uint16_t pr) {
	_ccr6_pr = pr - 1;
	TAx->CCR6 = TAx->R + _ccr6_pr;			//set the next match point
}

//install handler
void systick_act6(void (*isr_ptr)(void)) {
	_isrptr_ccr6=isr_ptr;						//install the user handler
	TAx->CCTL6 &=~CCIFG;						//clear the timer flag
	TAx->CCTL6 |= CCIE;							//enable timer interrupt
}
