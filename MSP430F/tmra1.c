#include "tmra1.h"							//we use tmra0

//hardware configuration
//end hardware configuration

//global defines
//for easy portability
#define TAxCTL				TA1CTL			//timera control
#define TAxR				TA1R			//timer / counter
#define TAxIV				TA1IV			//interrupt flag
#define TAxEX0				TA1EX0			//expansion register

#define TAxCCTL0			TA1CCTL0		//timer0 compare control
#define TAxCCTL1			TA1CCTL1		//timer1 cmpare control
#define TAxCCTL2			TA1CCTL2		//timer2 compare control
#define TAxCCTL3			TA1CCTL3		//timer0 compare control
#define TAxCCTL4			TA1CCTL4		//timer1 cmpare control
//#define TAxCCTL5			TA1CCTL5		//timer2 compare control
//#define TAxCCTL6			TA1CCTL6		//timer0 compare control
#define TAxCCR0				TA1CCR0			//timer0 compare register
#define TAxCCR1				TA1CCR1			//timer1 compare register
#define TAxCCR2				TA1CCR2			//timer2 compare register
#define TAxCCR3				TA1CCR3			//timer0 compare register
#define TAxCCR4				TA1CCR4			//timer1 compare register
//#define TAxCCR5				TA1CCR5			//timer2 compare register
//#define TAxCCR6				TA1CCR6			//timer0 compare register

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

//period registers
static uint16_t _ccr0_pr=0xffff;			//ccr0 saved
static uint16_t _ccr1_pr=0xffff;			//ccr1 saved
static uint16_t _ccr2_pr=0xffff;			//ccr2 saved
static uint16_t _ccr3_pr=0xffff;			//ccr0 saved
static uint16_t _ccr4_pr=0xffff;			//ccr1 saved
static uint16_t _ccr5_pr=0xffff;			//ccr2 saved
static uint16_t _ccr6_pr=0xffff;			//ccr0 saved

// Timer A0 interrupt service routine, ccr0
#pragma vector=TIMER1_A0_VECTOR
__interrupt void _ISRTimer1_A0 (void) {
	TAxCCR0 += _ccr0_pr;						//update TxCCR0 -> continuous mode
	//TxCTL_bit.TAIFG=0;						//clear tmr1 interrupt flag
	TAxCCTL0&=~CCIFG;							//clear the flag
	/*_tmr1*/_isrptr_ccr0();					//execute user tmr1 isr
}

// Timer A1 interrupt service routine, ccr1..4, ia
#pragma vector=TIMER1_A1_VECTOR
__interrupt void _ISRTimer1_A1 (void) {
	//TxCTL_bit.TAIFG=0;						//clear tmr1 interrupt flag
	///*_tmr1*/_isr_ptr1();					//execute user tmr1 isr
	switch (TAxIV) {
		case 0x02: 	TAxCCR1+=_ccr1_pr; TAxCCTL1 &=~CCIFG; _isrptr_ccr1(); break;		//0x02 -> ccr1
		case 0x04: 	TAxCCR2+=_ccr2_pr; TAxCCTL2 &=~CCIFG; _isrptr_ccr2(); break;		//0x04 -> ccr2
		//case 0x06: 	TAxCCR3+=_ccr3_pr; TAxCCTL3 &=~CCIFG; _isrptr_ccr3(); break;		//0x04 -> ccr2
		//case 0x08: 	TAxCCR4+=_ccr4_pr; TAxCCTL4 &=~CCIFG; _isrptr_ccr4(); break;		//0x04 -> ccr2
		//case 0x0a: 	TAxCCR5+=_ccr5_pr; TAxCCTL5 &=~CCIFG; _isrptr_ccr5(); break;		//0x04 -> ccr2
		//case 0x0c: 	TAxCCR6+=_ccr6_pr; TAxCCTL6 &=~CCIFG; _isrptr_ccr6(); break;		//0x04 -> ccr2
		default: break;
	}
}

//initialize timer_a, ccr0
//continous mode
void tmra1_init(uint16_t ps) {
	//clear the timer control register
	TAxCTL |= TACLR;							//TxCTL_bit.TACLR;						//set to reset timer a

	//stop timer
	//TxCTL &=~MC_0;							//TxCTL_bit.TAMC = 0x00;				//timer mode - 0x00: halted, 0x01: up mode, 0x02: continuous mode (to 0xffff), 0x03: up/down
	//TxCTL |= TASSEL_2;						//TxCTL_bit.TASSEL = 0x02;				//timer source - 0x00: TACLK, 0x01: ACLK, 0x02: SMCLK, 0x03: INCLK
	//TxCTL |= (ps & ID_3);						//TxCTL_bit.TAID = ps & 0x03;			//input divider - 0x00: /1, 0x01: /2, 0x02: /4, 0x03: /8
	//TxCTL &=~TAIE;							//TxCTL_bit.TAIE = 0;					//timer a interrupt enable: 0: interrupt disabled; 1: interrupt enabled;
	//TxCTL &=~TAIFG;							//TxCTL_bit.TAIFG = 0;					//interrupt flag: 0= no interrupt pending; 1=interrupt pending
	//TxCTL |= OUTMOD0;							//set output mode to zero
	TAxCTL = 	TASSEL_2 |						//0=TACLK, 1=ACLK, 2=SMCLK, and 3=INCLK
				(ps & TMRA_PS8x) |				//prescaler
				MC_2 |							//0=stop, 1=up to ccr0, 2=continous mode, 3=up and down
				0x00;							//TCIE disabled
	TAxEX0 = (ps & TMRA_EX8x);	//set expansion divider
	//timer is running now
}

//set the period register
void tmra1_setpr0(uint16_t pr) {
	_isrptr_ccr0 = empty_handler;				//reset handler ptr
	_ccr0_pr = pr - 1;							//remember period register
	TAxCCR0 = _ccr0_pr;
	//clear ccifg flag
	TAxCCTL0 &=~CCIFG;							//clear the flag

	//set up TAxCCTLx register
	TAxCCTL0 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
}

//install user handler for timer_a, ccr0
void tmra1_act0(void (*isr_ptr)(void)) {
	_isrptr_ccr0=isr_ptr;					//install the user handler
	//TxCTL_bit.TAIFG = 0;					//clear the timer flag
	//TxCTL_bit.TAIE = 1;					//enable timer interrupt
	TAxCCTL0 &=~CCIFG;						//clear the interrupt flag
	TAxCCTL0 |= (1<<4);						//enable the compare / capture interrupt
}

//initialize timer_a, ccr1
void tmra1_setpr1(uint16_t pr) {
	_isrptr_ccr1 = empty_handler;			//reset handler ptr
	_ccr1_pr = pr - 1;						//remember period register
	TAxCCR1 = _ccr1_pr;
	//clear ccifg flag
	TAxCCTL1 &=~CCIFG;						//clear the flag

	//set up TAxCCTLx register
	TAxCCTL1 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
}

//install user handler for timer_a, ccr1
void tmra1_act1(void (*isr_ptr)(void)) {
	_isrptr_ccr1=isr_ptr;					//install the user handler
	//TxCTL_bit.TAIFG = 0;					//clear the timer flag
	//TxCTL_bit.TAIE = 1;					//enable timer interrupt
	TAxCCTL1 &=~CCIFG;						//clear the interrupt flag
	TAxCCTL1 |= (1<<4);						//enable the compare / capture interrupt
}


//initialize timer_a, ccr2
void tmra1_setpr2(uint16_t pr) {
	_isrptr_ccr2 = empty_handler;			//reset handler ptr
	_ccr2_pr = pr - 1;						//remember period register
	TAxCCR2 = _ccr2_pr;
	//clear ccifg flag
	TAxCCTL2 &=~CCIFG;						//clear the flag

	//set up TAxCCTLx register
	TAxCCTL2 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
}

//install user handler for timer_a, ccr1
void tmra1_act2(void (*isr_ptr)(void)) {
	_isrptr_ccr2=isr_ptr;					//install the user handler
	//TxCTL_bit.TAIFG = 0;					//clear the timer flag
	//TxCTL_bit.TAIE = 1;					//enable timer interrupt
	TAxCCTL2 &=~CCIFG;						//clear the interrupt flag
	TAxCCTL2 |= (1<<4);						//enable the compare / capture interrupt
}

#if defined(TA1CCR3)
//initialize timer_a, ccr3
void tmra1_setpr3(uint16_t pr) {
	_isrptr_ccr3 = empty_handler;			//reset handler ptr
	_ccr3_pr = pr - 1;						//remember period register
	TAxCCR3 = _ccr3_pr;
	//clear ccifg flag
	TAxCCTL3 &=~CCIFG;						//clear the flag

	//set up TAxCCTLx register
	TAxCCTL3 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
}

//install user handler for timer_a, ccr1
void tmra1_act3(void (*isr_ptr)(void)) {
	_isrptr_ccr3=isr_ptr;					//install the user handler
	//TxCTL_bit.TAIFG = 0;					//clear the timer flag
	//TxCTL_bit.TAIE = 1;					//enable timer interrupt
	TAxCCTL3 &=~CCIFG;						//clear the interrupt flag
	TAxCCTL3 |= (1<<4);						//enable the compare / capture interrupt
}

#endif

#if defined(TA1CCR4)
//initialize timer_a, ccr4
void tmra1_setpr4(uint16_t pr) {
	_isrptr_ccr4 = empty_handler;			//reset handler ptr
	_ccr4_pr = pr - 1;						//remember period register
	TAxCCR4 = _ccr1_pr;
	//clear ccifg flag
	TAxCCTL4 &=~CCIFG;						//clear the flag

	//set up TAxCCTLx register
	TAxCCTL4 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
}

//install user handler for timer_a, ccr1
void tmra1_act4(void (*isr_ptr)(void)) {
	_isrptr_ccr4=isr_ptr;					//install the user handler
	//TxCTL_bit.TAIFG = 0;					//clear the timer flag
	//TxCTL_bit.TAIE = 1;					//enable timer interrupt
	TAxCCTL4 &=~CCIFG;						//clear the interrupt flag
	TAxCCTL4 |= (1<<4);						//enable the compare / capture interrupt
}

#endif

