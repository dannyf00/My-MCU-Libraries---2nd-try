

//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

//#include "msp.h"
#include "ta3oc.h"							//we use tmra3

//hardware configuration
//end hardware configuration

//global defines
#define TAxCTL			TIMER_A3->CTL		//timer a0 control register
#define TAxR			TIMER_A3->R			//timer counter
#define TAxEX0			TIMER_A3->EX0		//expansion divider
#define TAxIV			TIMER_A3->IV		//status register

//compare control registers
#define TAxCCTL0		TIMER_A3->CCTL[0]	//timer a0 ccr0 control register
#define TAxCCTL1		TIMER_A3->CCTL[1]	//timer a0 ccr1 control register
#define TAxCCTL2		TIMER_A3->CCTL[2]	//timer a0 ccr1 control register
#define TAxCCTL3		TIMER_A3->CCTL[3]	//timer a0 ccr1 control register
#define TAxCCTL4		TIMER_A3->CCTL[4]	//timer a0 ccr1 control register
#define TAxCCTL5		TIMER_A3->CCTL[5]	//timer a0 ccr1 control register
#define TAxCCTL6		TIMER_A3->CCTL[6]	//timer a0 ccr1 control register
//compare period registers
#define TAxCCR0			TIMER_A3->CCR[0]	//timer a0 ccr0 period register
#define TAxCCR1			TIMER_A3->CCR[1]	//timer a0 ccr1 period register
#define TAxCCR2			TIMER_A3->CCR[2]	//timer a0 ccr1 period register
#define TAxCCR3			TIMER_A3->CCR[3]	//timer a0 ccr0 period register
#define TAxCCR4			TIMER_A3->CCR[4]	//timer a0 ccr1 period register
#define TAxCCR5			TIMER_A3->CCR[5]	//timer a0 ccr1 period register
#define TAxCCR6			TIMER_A3->CCR[6]	//timer a0 ccr0 period register

//global variables
//empty handler
static void empty_handler(void) {
	//do nothing here
}

//user isr ptr
//those two ISRs (T32_INT1_ISR and T32_INT2_ISR) will need to be inserted in the start-up file
static void (* _tmrx_ccr0isrptr)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default
static void (* _tmrx_ccr1isrptr)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default
static void (* _tmrx_ccr2isrptr)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default
static void (* _tmrx_ccr3isrptr)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default
static void (* _tmrx_ccr4isrptr)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default
static void (* _tmrx_ccr5isrptr)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default
static void (* _tmrx_ccr6isrptr)(void)=empty_handler;				//tmr_ptr pointing to empty_handler by default

//period register user handlers
static uint16_t _tmrx_ccr0pr = 0xffff;									//ccr period register
static uint16_t _tmrx_ccr1pr = 0xffff;									//ccr period register
static uint16_t _tmrx_ccr2pr = 0xffff;									//ccr period register
static uint16_t _tmrx_ccr3pr = 0xffff;									//ccr period register
static uint16_t _tmrx_ccr4pr = 0xffff;									//ccr period register
static uint16_t _tmrx_ccr5pr = 0xffff;									//ccr period register
static uint16_t _tmrx_ccr6pr = 0xffff;									//ccr period register

//tmra0 ccr0 isr
void TA3_0_IRQHandler(void) {
	TAxCCR0+=_tmrx_ccr0pr;			//update the compare register
	//clear the flag
	TAxCCTL0 &=~(1<<0);				//clear the interupt flag (ccifg) by writing '0' to it

	_tmrx_ccr0isrptr();				//run user handler
}


//tmra0 ccr1..6 isr
void TA3_N_IRQHandler(void) {
	switch (TAxIV & 0x0f) {
		case 0x02:	TAxCCR1+=_tmrx_ccr1pr; TAxCCTL1 &=~(1<<0); _tmrx_ccr1isrptr(); break;
		case 0x04:	TAxCCR2+=_tmrx_ccr2pr; TAxCCTL2 &=~(1<<0); _tmrx_ccr2isrptr(); break;
		case 0x06:	TAxCCR3+=_tmrx_ccr3pr; TAxCCTL3 &=~(1<<0); _tmrx_ccr3isrptr(); break;
		case 0x08:	TAxCCR4+=_tmrx_ccr4pr; TAxCCTL4 &=~(1<<0); _tmrx_ccr4isrptr(); break;
		case 0x0a:	TAxCCR5+=_tmrx_ccr5pr; TAxCCTL5 &=~(1<<0); _tmrx_ccr5isrptr(); break;
		case 0x0c:	TAxCCR6+=_tmrx_ccr6pr; TAxCCTL6 &=~(1<<0); _tmrx_ccr6isrptr(); break;
		default: 	break;
	}
	/*	if (TAxIV & 0x02) {					//ccr1 triggered the flag
		TAxCCR1+=_tmrx_ccr1pr;			//update the compare register
		//clear the flag
		TAxCCTL1 &=~(1<<0);				//clear the interupt flag (ccifg) by writing '0' to it

		_tmrx_ccr1isrptr();				//run user handler
	};

	if (TAxIV & 0x04) {					//ccr2 triggered
		TAxCCR2+=_tmrx_ccr2pr;			//update the compare register
		//clear the flag
		TAxCCTL2 &=~(1<<0);				//clear the interupt flag (ccifg) by writing '0' to it

		_tmrx_ccr2isrptr();				//run user handler
	}
*/
}


//initialize tmr_a
//continuous mode
//ps. bit 7..6: input divider, bit 2..0: expansion divider
void tmra3_init(uint16_t ps) {
	TAxCTL |= (1<<2);			//clear timer
	TAxCTL	=	TASSEL_2 |			//0->TAxCLK, 1->ACLK, 2->SMCLK, 3->INCLK
					(ps & TMRA_PS8x) |	//prescaler. 0b00->1x, 0b01->2x, 0b10->4x, 0b11->8x
					MC_2 |				//0=stop, 1=up to ccr0, 2->continuous mode, to 0xffff, 3=up and down
					(0b10 << 4) |	//0b10->continuous mode, to 0xffff
					(0<<1) |		//0->TAIE disabled
					(0<<1);			//TAIFG flag
	TAxCCR0 = 0xffff;				//set the top
	TAxEX0 = (ps & TMRA_EX8x);	//set expansion divider
	//tmr running now
}

//initialize tmra_ccr0
void tmra3_setpr0(uint16_t pr) {
	_tmrx_ccr0isrptr = empty_handler;	//reset handler
	TAxCCTL0 =		(0b00<<14) |	//0b00->no capture; 0b01->on rising edge; 0b10->on falling edge; 0b11->on rising and falling edges
					(0b00<<12) |	//input select. 0b00-> on ccixa, ...
					(0<<11) |		//0->synchronous capture. 1->synchronous capture
					(0<<8) |		//0->compare. 1->capture
					(0b000<<5) |	//output mode. 0b000-> out bit
					(0<<4) |		//1->interrupt enabled. 0->interrupt disabled
					(0<<2) |		//0->output low, 1=output high
					(0x00);
	_tmrx_ccr0pr = pr - 1;
	TAxCCR0 = TAxR + _tmrx_ccr0pr;			//pr - 1;			//set ccr

}

//activate ccr0 interrupt handler
void tmra3_act0(void (*isrptr)(void)) {
	_tmrx_ccr0isrptr = isrptr;		//install user handler
	TAxCCTL0 |= (1<<4);				//enable interrupt
	NVIC_EnableIRQ(TA3_0_IRQn);		//enable interrupt for timer0_ccr0
}

//initialize tmra_ccr1
void tmra3_setpr1(uint16_t pr) {
	_tmrx_ccr1isrptr = empty_handler;	//reset handler
	TAxCCTL1 =		(0b00<<14) |	//0b00->no capture; 0b01->on rising edge; 0b10->on falling edge; 0b11->on rising and falling edges
					(0b00<<12) |	//input select. 0b00-> on ccixa, ...
					(0<<11) |		//0->synchronous capture. 1->synchronous capture
					(0<<8) |		//0->compare. 1->capture
					(0b000<<5) |	//output mode. 0b000-> out bit
					(0<<4) |		//1->interrupt enabled. 0->interrupt disabled
					(0<<2) |		//0->output low, 1=output high
					(0x00);
	_tmrx_ccr1pr = pr - 1;
	TAxCCR1 = TAxR + _tmrx_ccr1pr;			//pr - 1;			//set ccr

}

//activate ccr1 interrupt handler
void tmra3_act1(void (*isrptr)(void)) {
	_tmrx_ccr1isrptr = isrptr;		//install user handler
	TAxCCTL1 |= (1<<4);				//enable interrupt
	NVIC_EnableIRQ(TA3_N_IRQn);		//enable interrupt for timer0_ccr0
}

//initialize tmra_ccr2
void tmra3_setpr2(uint16_t pr) {
	_tmrx_ccr2isrptr = empty_handler;	//reset handler
	TAxCCTL2 =		(0b00<<14) |	//0b00->no capture; 0b01->on rising edge; 0b10->on falling edge; 0b11->on rising and falling edges
					(0b00<<12) |	//input select. 0b00-> on ccixa, ...
					(0<<11) |		//0->synchronous capture. 1->synchronous capture
					(0<<8) |		//0->compare. 1->capture
					(0b000<<5) |	//output mode. 0b000-> out bit
					(0<<4) |		//1->interrupt enabled. 0->interrupt disabled
					(0<<2) |		//0->output low, 1=output high
					(0x00);
	_tmrx_ccr2pr = pr - 1;
	TAxCCR2 = TAxR + _tmrx_ccr2pr;			//pr - 1;			//set ccr

}

//activate ccr2 interrupt handler
void tmra3_act2(void (*isrptr)(void)) {
	_tmrx_ccr2isrptr = isrptr;		//install user handler
	TAxCCTL2 |= (1<<4);				//enable interrupt
	NVIC_EnableIRQ(TA3_N_IRQn);		//enable interrupt for timer0_ccr0
}

//initialize tmra_ccr3
void tmra3_setpr3(uint16_t pr) {
	_tmrx_ccr3isrptr = empty_handler;	//reset handler
	TAxCCTL3 =		(0b00<<14) |	//0b00->no capture; 0b01->on rising edge; 0b10->on falling edge; 0b11->on rising and falling edges
					(0b00<<12) |	//input select. 0b00-> on ccixa, ...
					(0<<11) |		//0->synchronous capture. 1->synchronous capture
					(0<<8) |		//0->compare. 1->capture
					(0b000<<5) |	//output mode. 0b000-> out bit
					(0<<4) |		//1->interrupt enabled. 0->interrupt disabled
					(0<<2) |		//0->output low, 1=output high
					(0x00);
	_tmrx_ccr3pr = pr - 1;
	TAxCCR3 = TAxR + _tmrx_ccr3pr;			//pr - 1;			//set ccr

}

//activate ccr3 interrupt handler
void tmra3_act3(void (*isrptr)(void)) {
	_tmrx_ccr3isrptr = isrptr;		//install user handler
	TAxCCTL3 |= (1<<4);				//enable interrupt
	NVIC_EnableIRQ(TA3_N_IRQn);		//enable interrupt for timer0_ccr0
}

//initialize tmra_ccr4
void tmra3_setpr4(uint16_t pr) {
	_tmrx_ccr4isrptr = empty_handler;	//reset handler
	TAxCCTL4 =		(0b00<<14) |	//0b00->no capture; 0b01->on rising edge; 0b10->on falling edge; 0b11->on rising and falling edges
					(0b00<<12) |	//input select. 0b00-> on ccixa, ...
					(0<<11) |		//0->synchronous capture. 1->synchronous capture
					(0<<8) |		//0->compare. 1->capture
					(0b000<<5) |	//output mode. 0b000-> out bit
					(0<<4) |		//1->interrupt enabled. 0->interrupt disabled
					(0<<2) |		//0->output low, 1=output high
					(0x00);
	_tmrx_ccr4pr = pr - 1;
	TAxCCR4 = TAxR + _tmrx_ccr4pr;			//pr - 1;			//set ccr

}

//activate ccr4 interrupt handler
void tmra3_act4(void (*isrptr)(void)) {
	_tmrx_ccr4isrptr = isrptr;		//install user handler
	TAxCCTL4 |= (1<<4);				//enable interrupt
	NVIC_EnableIRQ(TA3_N_IRQn);		//enable interrupt for timer0_ccr0
}

//initialize tmra_ccr5
void tmra3_setpr5(uint16_t pr) {
	_tmrx_ccr5isrptr = empty_handler;	//reset handler
	TAxCCTL5 =		(0b00<<14) |	//0b00->no capture; 0b01->on rising edge; 0b10->on falling edge; 0b11->on rising and falling edges
					(0b00<<12) |	//input select. 0b00-> on ccixa, ...
					(0<<11) |		//0->synchronous capture. 1->synchronous capture
					(0<<8) |		//0->compare. 1->capture
					(0b000<<5) |	//output mode. 0b000-> out bit
					(0<<4) |		//1->interrupt enabled. 0->interrupt disabled
					(0<<2) |		//0->output low, 1=output high
					(0x00);
	_tmrx_ccr5pr = pr - 1;
	TAxCCR5 = TAxR + _tmrx_ccr5pr;			//pr - 1;			//set ccr

}

//activate ccr5 interrupt handler
void tmra3_act5(void (*isrptr)(void)) {
	_tmrx_ccr5isrptr = isrptr;		//install user handler
	TAxCCTL5 |= (1<<4);				//enable interrupt
	NVIC_EnableIRQ(TA3_N_IRQn);		//enable interrupt for timer0_ccr0
}

//initialize tmra_ccr6
void tmra3_setpr6(uint16_t pr) {
	_tmrx_ccr6isrptr = empty_handler;	//reset handler
	TAxCCTL6 =		(0b00<<14) |	//0b00->no capture; 0b01->on rising edge; 0b10->on falling edge; 0b11->on rising and falling edges
					(0b00<<12) |	//input select. 0b00-> on ccixa, ...
					(0<<11) |		//0->synchronous capture. 1->synchronous capture
					(0<<8) |		//0->compare. 1->capture
					(0b000<<5) |	//output mode. 0b000-> out bit
					(0<<4) |		//1->interrupt enabled. 0->interrupt disabled
					(0<<2) |		//0->output low, 1=output high
					(0x00);
	_tmrx_ccr6pr = pr - 1;
	TAxCCR6 = TAxR + _tmrx_ccr6pr;			//pr - 1;			//set ccr

}

//activate ccr6 interrupt handler
void tmra3_act6(void (*isrptr)(void)) {
	_tmrx_ccr6isrptr = isrptr;		//install user handler
	TAxCCTL6 |= (1<<4);				//enable interrupt
	NVIC_EnableIRQ(TA3_N_IRQn);		//enable interrupt for timer0_ccr0
}

