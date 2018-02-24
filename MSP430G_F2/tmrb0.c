#include "tmrb0.h"							//we use tmrb0

//hardware configuration
//end hardware configuration

//global defines
//for easy portability
#define TBxCTL				TB0CTL			//timera control
#define TBxR				TB0R			//timer / counter
#define TBxIV				TB0IV			//interrupt flag
#define TBxEX0				TB0EX0			//expansion register

#define TBxCCTL0			TB0CCTL0		//timer0 compare control
#define TBxCCTL1			TB0CCTL1		//timer1 cmpare control
#define TBxCCTL2			TB0CCTL2		//timer2 compare control
#define TBxCCTL3			TB0CCTL3		//timer0 compare control
#define TBxCCTL4			TB0CCTL4		//timer1 cmpare control
#define TBxCCTL5			TB0CCTL5		//timer2 compare control
#define TBxCCTL6			TB0CCTL6		//timer0 compare control
#define TBxCCR0				TB0CCR0			//timer0 compare register
#define TBxCCR1				TB0CCR1			//timer1 compare register
#define TBxCCR2				TB0CCR2			//timer2 compare register
#define TBxCCR3				TB0CCR3			//timer0 compare register
#define TBxCCR4				TB0CCR4			//timer1 compare register
#define TBxCCR5				TB0CCR5			//timer2 compare register
#define TBxCCR6				TB0CCR6			//timer0 compare register

//global variables
//empty handler
static void /*_tmr1_*/empty_handler(void) {
	//default tmr handler
}

//global variables
static void (* /*_tmr1*/_isrptr_ccr0)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ccr1)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ccr2)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ccr3)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ccr4)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ccr5)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ccr6)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default
static void (* /*_tmr1*/_isrptr_ta)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

//period registers
static unsigned short _ccr0_pr=0xffff;			//ccr0 saved
static unsigned short _ccr1_pr=0xffff;			//ccr1 saved
static unsigned short _ccr2_pr=0xffff;			//ccr2 saved
static unsigned short _ccr3_pr=0xffff;			//ccr0 saved
static unsigned short _ccr4_pr=0xffff;			//ccr1 saved
static unsigned short _ccr5_pr=0xffff;			//ccr2 saved
static unsigned short _ccr6_pr=0xffff;			//ccr0 saved

// Timer A0 interrupt service routine, ccr0
#pragma vector=TIMER0_B0_VECTOR
__interrupt void _ISRTimer0_B0 (void) {
	TBxCCR0 += _ccr0_pr;						//update TxCCR0 -> continuous mode
	//TxCTL_bit.TAIFG=0;						//clear tmr1 interrupt flag
	TBxCCTL0&=~CCIFG;							//clear the flag
	/*_tmr1*/_isrptr_ccr0();					//execute user tmr1 isr
}

// Timer A1 interrupt service routine, ccr1..6, ia
#pragma vector=TIMER0_B1_VECTOR
__interrupt void _ISRTimer0_B1 (void) {
	//TxCTL_bit.TAIFG=0;						//clear tmr1 interrupt flag
	///*_tmr1*/_isr_ptr1();					//execute user tmr1 isr
	switch (TBxIV) {
		case 0x02: 	TBxCCR1+=_ccr1_pr; TBxCCTL1 &=~CCIFG; _isrptr_ccr1(); break;		//0x02 -> ccr1
#if defined(TB0CCTL2_)
		case 0x04: 	TBxCCR2+=_ccr2_pr; TBxCCTL2 &=~CCIFG; _isrptr_ccr2(); break;		//0x04 -> ccr2
#endif
#if defined(TB0CCTL3_)
		case 0x06: 	TBxCCR3+=_ccr3_pr; TBxCCTL3 &=~CCIFG; _isrptr_ccr3(); break;		//0x04 -> ccr2
#endif
#if defined(TB0CCTL4_)
		case 0x08: 	TBxCCR4+=_ccr4_pr; TBxCCTL4 &=~CCIFG; _isrptr_ccr4(); break;		//0x04 -> ccr2
#endif
#if defined(TB0CCTL5_)
		case 0x0a: 	TBxCCR5+=_ccr5_pr; TBxCCTL5 &=~CCIFG; _isrptr_ccr5(); break;		//0x04 -> ccr2
#endif
#if defined(TB0CCTL6_)
		case 0x0c: 	TBxCCR6+=_ccr6_pr; TBxCCTL6 &=~CCIFG; _isrptr_ccr6(); break;		//0x04 -> ccr2
#endif
		//overflow interrupt
		case 0x0e: 	                   TBxCTL &=~TBIFG; _isrptr_ta(); break;		//0x04 -> ccr2
		default: break;
	}
}

//initialize timer_a, ccr0
//continous mode
void tmrb0_init(uint16_t ps) {
	//clear the timer control register
	TBxCTL |= TBCLR;							//TxCTL_bit.TACLR;						//set to reset timer a

	//stop timer
	//TxCTL &=~MC_0;							//TxCTL_bit.TAMC = 0x00;				//timer mode - 0x00: halted, 0x01: up mode, 0x02: continuous mode (to 0xffff), 0x03: up/down
	//TxCTL |= TASSEL_2;						//TxCTL_bit.TASSEL = 0x02;				//timer source - 0x00: TACLK, 0x01: ACLK, 0x02: SMCLK, 0x03: INCLK
	//TxCTL |= (ps & ID_3);						//TxCTL_bit.TAID = ps & 0x03;			//input divider - 0x00: /1, 0x01: /2, 0x02: /4, 0x03: /8
	//TxCTL &=~TAIE;							//TxCTL_bit.TAIE = 0;					//timer a interrupt enable: 0: interrupt disabled; 1: interrupt enabled;
	//TxCTL &=~TAIFG;							//TxCTL_bit.TAIFG = 0;					//interrupt flag: 0= no interrupt pending; 1=interrupt pending
	//TxCTL |= OUTMOD0;							//set output mode to zero
	TBxCTL = 	TBSSEL_2 |						//0=TACLK, 1=ACLK, 2=SMCLK, and 3=INCLK
				(ps & TMRB_PS8x) |				//prescaler
				MC_2 |							//0=stop, 1=up to ccr0, 2=continous mode, 3=up and down
				0x00;							//TCIE disabled
#if defined(TB0EX0_)
	TBxEX0 = (ps & TMRB_EX8x);	//set expansion divider
#endif
	//timer is running now
}

//install user handler for timer_a overflow
void tmrb0_act(void (*isr_ptr)(void)) {
	_isrptr_ta=isr_ptr;						//install the user handler
	TBxCTL &=~TBIFG;						//clear the timer flag
	TBxCTL |= TBIE;							//enable timer interrupt
}

//set the period register
void tmrb0_setpr0(uint16_t pr) {
	_isrptr_ccr0 = empty_handler;				//reset handler ptr
	_ccr0_pr = pr - 1;							//remember period register
	TBxCCR0 = _ccr0_pr;
	//clear ccifg flag
	TBxCCTL0 &=~CCIFG;							//clear the flag

	//set up TBxCCTLx register
	TBxCCTL0 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
}

//install user handler for timer_a, ccr0
void tmrb0_act0(void (*isr_ptr)(void)) {
	_isrptr_ccr0=isr_ptr;					//install the user handler
	//TxCTL_bit.TAIFG = 0;					//clear the timer flag
	//TxCTL_bit.TAIE = 1;					//enable timer interrupt
	TBxCCTL0 &=~CCIFG;						//clear the interrupt flag
	TBxCCTL0 |= (1<<4);						//enable the compare / capture interrupt
}

//initialize timer_a, ccr1
void tmrb0_setpr1(uint16_t pr) {
	_isrptr_ccr1 = empty_handler;			//reset handler ptr
	_ccr1_pr = pr - 1;						//remember period register
	TBxCCR1 = _ccr1_pr;
	//clear ccifg flag
	TBxCCTL1 &=~CCIFG;						//clear the flag

	//set up TBxCCTLx register
	TBxCCTL1 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
}

//install user handler for timer_a, ccr1
void tmrb0_act1(void (*isr_ptr)(void)) {
	_isrptr_ccr1=isr_ptr;					//install the user handler
	//TxCTL_bit.TAIFG = 0;					//clear the timer flag
	//TxCTL_bit.TAIE = 1;					//enable timer interrupt
	TBxCCTL1 &=~CCIFG;						//clear the interrupt flag
	TBxCCTL1 |= (1<<4);						//enable the compare / capture interrupt
}

#if defined(TB0CCTL2_)
//initialize timer_a, ccr2
void tmrb0_setpr2(uint16_t pr) {
	_isrptr_ccr2 = empty_handler;			//reset handler ptr
	_ccr2_pr = pr - 1;						//remember period register
	TBxCCR2 = _ccr2_pr;
	//clear ccifg flag
	TBxCCTL2 &=~CCIFG;						//clear the flag

	//set up TBxCCTLx register
	TBxCCTL2 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
}

//install user handler for timer_a, ccr1
void tmrb0_act2(void (*isr_ptr)(void)) {
	_isrptr_ccr2=isr_ptr;					//install the user handler
	//TxCTL_bit.TAIFG = 0;					//clear the timer flag
	//TxCTL_bit.TAIE = 1;					//enable timer interrupt
	TBxCCTL2 &=~CCIFG;						//clear the interrupt flag
	TBxCCTL2 |= (1<<4);						//enable the compare / capture interrupt
}
#endif

#if defined(TB0CCTL3_)
//initialize timer_a, ccr3
void tmrb0_setpr3(uint16_t pr) {
	_isrptr_ccr3 = empty_handler;			//reset handler ptr
	_ccr3_pr = pr - 1;						//remember period register
	TBxCCR3 = _ccr3_pr;
	//clear ccifg flag
	TBxCCTL3 &=~CCIFG;						//clear the flag

	//set up TBxCCTLx register
	TBxCCTL3 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
}

//install user handler for timer_a, ccr1
void tmrb0_act3(void (*isr_ptr)(void)) {
	_isrptr_ccr3=isr_ptr;					//install the user handler
	//TxCTL_bit.TAIFG = 0;					//clear the timer flag
	//TxCTL_bit.TAIE = 1;					//enable timer interrupt
	TBxCCTL3 &=~CCIFG;						//clear the interrupt flag
	TBxCCTL3 |= (1<<4);						//enable the compare / capture interrupt
}
#endif

#if defined(TB0CCTL4_)
//initialize timer_a, ccr4
void tmrb0_setpr4(uint16_t pr) {
	_isrptr_ccr4 = empty_handler;			//reset handler ptr
	_ccr4_pr = pr - 1;						//remember period register
	TBxCCR4 = _ccr1_pr;
	//clear ccifg flag
	TBxCCTL4 &=~CCIFG;						//clear the flag

	//set up TBxCCTLx register
	TBxCCTL4 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
}

//install user handler for timer_a, ccr1
void tmrb0_act4(void (*isr_ptr)(void)) {
	_isrptr_ccr4=isr_ptr;					//install the user handler
	//TxCTL_bit.TAIFG = 0;					//clear the timer flag
	//TxCTL_bit.TAIE = 1;					//enable timer interrupt
	TBxCCTL4 &=~CCIFG;						//clear the interrupt flag
	TBxCCTL4 |= (1<<4);						//enable the compare / capture interrupt
}
#endif

#if defined(TB0CCTL5_)
//initialize timer_a, ccr5
void tmrb0_setpr5(uint16_t pr) {
	_isrptr_ccr5 = empty_handler;			//reset handler ptr
	_ccr5_pr = pr - 1;						//remember period register
	TBxCCR5 = _ccr1_pr;
	//clear ccifg flag
	TBxCCTL5 &=~CCIFG;						//clear the flag

	//set up TBxCCTLx register
	TBxCCTL5 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
}

//install user handler for timer_a, ccr5
void tmrb0_act5(void (*isr_ptr)(void)) {
	_isrptr_ccr5=isr_ptr;					//install the user handler
	//TxCTL_bit.TAIFG = 0;					//clear the timer flag
	//TxCTL_bit.TAIE = 1;					//enable timer interrupt
	TBxCCTL5 &=~CCIFG;						//clear the interrupt flag
	TBxCCTL5 |= (1<<4);						//enable the compare / capture interrupt
}
#endif

#if defined(TB0CCTL6_)
//initialize timer_a, ccr6
void tmrb0_setpr6(uint16_t pr) {
	_isrptr_ccr6 = empty_handler;			//reset handler ptr
	_ccr6_pr = pr - 1;						//remember period register
	TBxCCR6 = _ccr1_pr;
	//clear ccifg flag
	TBxCCTL6 &=~CCIFG;						//clear the flag

	//set up TBxCCTLx register
	TBxCCTL6 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
}

//install user handler for timer_a, ccr6
void tmrb0_act6(void (*isr_ptr)(void)) {
	_isrptr_ccr6=isr_ptr;					//install the user handler
	//TxCTL_bit.TAIFG = 0;					//clear the timer flag
	//TxCTL_bit.TAIE = 1;					//enable timer interrupt
	TBxCCTL6 &=~CCIFG;						//clear the interrupt flag
	TBxCCTL6 |= (1<<4);						//enable the compare / capture interrupt
}
#endif
