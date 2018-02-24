#include "systick.h"							//we use tmra3_ccr0 as systick generator

//hardware configuration
//end hardware configuration

//global defines
//for easy portability
#define TAxCTL				TA0CTL			//timera control
#define TAxR				TA0R			//timer / counter
#define TAxIV				TA0IV			//interrupt flag
#define TAxEX0				TA0EX0			//expansion register

#define TAxCCTL0			TA0CCTL0		//timer0 compare control
#define TAxCCTL1			TA0CCTL1		//timer1 cmpare control
#define TAxCCTL2			TA0CCTL2		//timer2 compare control
#define TAxCCTL3			TA0CCTL3		//timer0 compare control
#define TAxCCTL4			TA0CCTL4		//timer1 cmpare control
#define TAxCCTL5			TA0CCTL5		//timer2 compare control
#define TAxCCTL6			TA0CCTL6		//timer0 compare control
#define TAxCCR0				TA0CCR0			//timer0 compare register
#define TAxCCR1				TA0CCR1			//timer1 compare register
#define TAxCCR2				TA0CCR2			//timer2 compare register
#define TAxCCR3				TA0CCR3			//timer0 compare register
#define TAxCCR4				TA0CCR4			//timer1 compare register
#define TAxCCR5				TA0CCR5			//timer2 compare register
#define TAxCCR6				TA0CCR6			//timer0 compare register

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

volatile uint32_t systickovf_counter=0x00;			//systick counter

// Timer A0 interrupt service routine, ccr0
#pragma vector=TIMER0_A0_VECTOR
__interrupt void _ISRTimer0_A0 (void) {
	TAxCCR0+=_ccr0_pr; TAxCCTL0 &=~CCIFG; _isrptr_ccr0(); 
}

// Timer A0 interrupt service routine, ccr1..6, ia
#pragma vector=TIMER0_A1_VECTOR
__interrupt void _ISRTimer0_A1 (void) {
	switch (TAxIV) {
		case 0x02: 	TAxCCR1+=_ccr1_pr; TAxCCTL1 &=~CCIFG; _isrptr_ccr1(); break;		//0x02 -> ccr1
		case 0x04: 	TAxCCR2+=_ccr2_pr; TAxCCTL2 &=~CCIFG; _isrptr_ccr2(); break;		//0x04 -> ccr2
#if defined(TA0CCR3)
		case 0x06: 	TAxCCR3+=_ccr3_pr; TAxCCTL3 &=~CCIFG; _isrptr_ccr3(); break;		//0x04 -> ccr2
#endif
#if defined(TA0CCR4)
		case 0x08: 	TAxCCR4+=_ccr4_pr; TAxCCTL4 &=~CCIFG; _isrptr_ccr4(); break;		//0x04 -> ccr2
#endif
#if defined(TA0CCR5)
		case 0x0a: 	TAxCCR5+=_ccr5_pr; TAxCCTL5 &=~CCIFG; _isrptr_ccr5(); break;		//0x04 -> ccr2
#endif
#if defined(TA0CCR6)
		case 0x0c: 	TAxCCR6+=_ccr6_pr; TAxCCTL6 &=~CCIFG; _isrptr_ccr6(); break;		//0x04 -> ccr2
#endif
		//ta0 overflow - TAxIV positions may change - dumb design decision by TI!
		case 0x0a: 	TAxCTL &=~TAIFG; systickovf_counter+= 0x10000ul; break;				//16 bit counter, 1:1 prescaler
		default: break;
	}
}


//initialize timer_a3, ccr0
//continous mode
//prescaler + postscaler both at 1:1
//continuous mode
void systick_init(void) {
	systickovf_counter=0;						//reset systick overflow counter
	_ccr0_pr=_ccr1_pr=_ccr2_pr=_ccr3_pr=_ccr4_pr=_ccr5_pr=_ccr6_pr=0xffff;
	_isrptr_ccr0=_isrptr_ccr1=_isrptr_ccr2=_isrptr_ccr3=_isrptr_ccr4=_isrptr_ccr5=_isrptr_ccr6=empty_handler;
	
	//clear the timer control register
	TAxCTL |= TACLR;							//TxCTL_bit.TACLR;						//set to reset timer a

	//stop timer
	TAxCTL &=~MC_0;							//TxCTL_bit.TAMC = 0x00;				//timer mode - 0x00: halted, 0x01: up mode, 0x02: continuous mode (to 0xffff), 0x03: up/down
	//TxCTL |= TASSEL_2;						//TxCTL_bit.TASSEL = 0x02;				//timer source - 0x00: TACLK, 0x01: ACLK, 0x02: SMCLK, 0x03: INCLK
	//TxCTL |= (ps & ID_3);						//TxCTL_bit.TAID = ps & 0x03;			//input divider - 0x00: /1, 0x01: /2, 0x02: /4, 0x03: /8
	//TxCTL &=~TAIE;							//TxCTL_bit.TAIE = 0;					//timer a interrupt enable: 0: interrupt disabled; 1: interrupt enabled;
	//TxCTL &=~TAIFG;							//TxCTL_bit.TAIFG = 0;					//interrupt flag: 0= no interrupt pending; 1=interrupt pending
	//TxCTL |= OUTMOD0;							//set output mode to zero
	//TAxCTL = 	TASSEL_2 |						//0=TACLK, 1=ACLK, 2=SMCLK, and 3=INCLK
	//			(TMRA_PS1x & TMRA_PS8x) |		//prescaler
	//			MC_2 |							//0=stop, 1=up to ccr0, 2=continous mode, 3=up and down
	//			0x00;							//TCIE disabled
#if defined(TA3EX0_)
	TAxEX0 = (TMRA_EX1x & TMRA_EX8x);			//set expansion divider
#endif
	//timer is running now

	//set up match register
#if defined(TA0CCR0)
	TAxCCR0 = 0xffff;
#endif
#if defined(TA0CCR1)
	TAxCCR1 = 0xffff;
#endif
#if defined(TA0CCR2)
	TAxCCR2 = 0xffff;
#endif
#if defined(TA0CCR3)
	TAxCCR3 = 0xffff;
#endif
#if defined(TA0CCR4)
	TAxCCR4 = 0xffff;
#endif
#if defined(TA0CCR5)
	TAxCCR5 = 0xffff;
#endif
#if defined(TA0CCR6)
	TAxCCR6 = 0xffff;						//match point in the middle of counter
#endif	
	
	//clear ccifg flag and disable the compare interrupt
#if defined(TA0CCTL0)
	TAxCCTL0 &=~(CCIE | CCIFG);					//clear the flag
#endif
#if defined(TA0CCTL1)
	TAxCCTL1 &=~(CCIE | CCIFG);					//clear the flag
#endif
#if defined(TA0CCTL2)
	TAxCCTL2 &=~(CCIE | CCIFG);					//clear the flag
#endif
#if defined(TA0CCTL3)
	TAxCCTL3 &=~(CCIE | CCIFG);					//clear the flag
#endif
#if defined(TA0CCTL4)
	TAxCCTL4 &=~(CCIE | CCIFG);					//clear the flag
#endif
#if defined(TA0CCTL5)
	TAxCCTL5 &=~(CCIE | CCIFG);					//clear the flag
#endif
#if defined(TA0CCTL6)
	TAxCCTL6 &=~(CCIE | CCIFG);					//clear the flag
#endif
	
	//clear ccifg flag
	TAxCTL &=~TAIFG;							//clear the overflow flag

	//set up TAxCTL register
	TAxCTL = 	TASSEL_2 |					//0=TACLK, 1=ACLK, 2=SMCLK, and 3=INCLK
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
		f = TAxR;						//SysTick->VAL;				//read the least significant 16-bits
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
	TAxCCR0 = TAxR + _ccr0_pr;			//set the next match point
}

//install handler 
void systick_act0(void (*isr_ptr)(void)) {
	_isrptr_ccr0=isr_ptr;						//install the user handler
	TAxCCTL0 &=~CCIFG;						//clear the timer flag
	TAxCCTL0 |= CCIE;							//enable timer interrupt
}

//enable compare interrupt
void systick_setpr1(uint16_t pr) {
	_ccr1_pr = pr - 1;
	TAxCCR1 = TAxR + _ccr1_pr;			//set the next match point
}

//install handler
void systick_act1(void (*isr_ptr)(void)) {
	_isrptr_ccr1=isr_ptr;						//install the user handler
	TAxCCTL1 &=~CCIFG;						//clear the timer flag
	TAxCCTL1 |= CCIE;							//enable timer interrupt
}

//enable compare interrupt
void systick_setpr2(uint16_t pr) {
	_ccr2_pr = pr - 1;
	TAxCCR2 = TAxR + _ccr2_pr;			//set the next match point
}

//install handler
void systick_act2(void (*isr_ptr)(void)) {
	_isrptr_ccr2=isr_ptr;						//install the user handler
	TAxCCTL2 &=~CCIFG;						//clear the timer flag
	TAxCCTL2 |= CCIE;							//enable timer interrupt
}

//enable compare interrupt
#if defined(TA0CCR3)
void systick_setpr3(uint16_t pr) {
	_ccr3_pr = pr - 1;
	TAxCCR3 = TAxR + _ccr3_pr;			//set the next match point
}

//install handler
void systick_act3(void (*isr_ptr)(void)) {
	_isrptr_ccr3=isr_ptr;						//install the user handler
	TAxCCTL3 &=~CCIFG;						//clear the timer flag
	TAxCCTL3 |= CCIE;							//enable timer interrupt
}
#endif

//enable compare interrupt
#if defined(TA0CCR4)
void systick_setpr4(uint16_t pr) {
	_ccr4_pr = pr - 1;
	TAxCCR4 = TAxR + _ccr4_pr;			//set the next match point
}

//install handler
void systick_act4(void (*isr_ptr)(void)) {
	_isrptr_ccr4=isr_ptr;						//install the user handler
	TAxCCTL4 &=~CCIFG;						//clear the timer flag
	TAxCCTL4 |= CCIE;							//enable timer interrupt
}
#endif

//enable compare interrupt
#if defined(TA0CCR5)
void systick_setpr5(uint16_t pr) {
	_ccr5_pr = pr - 1;
	TAxCCR5 = TAxR + _ccr5_pr;			//set the next match point
}

//install handler
void systick_act5(void (*isr_ptr)(void)) {
	_isrptr_ccr5=isr_ptr;						//install the user handler
	TAxCCTL5 &=~CCIFG;						//clear the timer flag
	TAxCCTL5 |= CCIE;							//enable timer interrupt
}
#endif

//enable compare interrupt
#if defined(TA0CCR6)
void systick_setpr6(uint16_t pr) {
	_ccr6_pr = pr - 1;
	TAxCCR6 = TAxR + _ccr6_pr;			//set the next match point
}

//install handler
void systick_act6(void (*isr_ptr)(void)) {
	_isrptr_ccr6=isr_ptr;						//install the user handler
	TAxCCTL6 &=~CCIFG;						//clear the timer flag
	TAxCCTL6 |= CCIE;							//enable timer interrupt
}
#endif