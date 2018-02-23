#include "tmr0_mr.h"				//we use tmr0 match compare

//hardware configuration
//end hardware configuration

//global defines
#define CTx				CT0			//timer in use
#define CTx_IRQn		(1<<4)		//4=TIMER0, 5=TIMER1, 6=UART0, 7=UART1
#define CTx_VICx		4			//vic channel. needs to be unique
#define VICVectAddrx	VICVectAddr4	  	//determined by CTx_VICx
#define VICVectCntlx	VICVectCntl4		//deterlimined by CTx_VICx

//empty handler
static void empty_handler(void) {
	//do nothing here
}

//global variable
//pointer to user handler
static void (* _tmrisr0_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler
static void (* _tmrisr1_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler
static void (* _tmrisr2_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler
static void (* _tmrisr3_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler

//shadow period registers
static uint16_t _tmr_pr0=0xffff;
static uint16_t _tmr_pr1=0xffff;
static uint16_t _tmr_pr2=0xffff;
static uint16_t _tmr_pr3=0xffff;

//isr
void __irq T0ISR(void) {
	//match channel 0
	if (CTx->IR & (1<<0)) {
		CTx->IR |= 1<<0;						//clear the flag by writing 1 to it
		CTx->MR0+= _tmr_pr0;					//update match register
		_tmrisr0_ptr();							//execute user handler
	}

	//match channel 1
	if (CTx->IR & (1<<1)) {
		CTx->IR |= 1<<1;						//clear the flag by writing 1 to it
		CTx->MR1+= _tmr_pr1;					//update match register
		_tmrisr1_ptr();							//execute user handler
	}

	//match channel 2
	if (CTx->IR & (1<<2)) {
		CTx->IR |= 1<<2;						//clear the flag by writing 1 to it
		CTx->MR2+= _tmr_pr2;					//update match register
		_tmrisr2_ptr();							//execute user handler
	}

	//match channel 3
	if (CTx->IR & (1<<3)) {
		CTx->IR |= 1<<3;						//clear the flag by writing 1 to it
		CTx->MR3+= _tmr_pr3;					//update match register
		_tmrisr3_ptr();							//execute user handler
	}
	VICVectAddr = 0x00000000; 					//Dummy write to signal end of interrupt
}

//initialize the timer
//upcounter
void tmr0_init(uint32_t ps) {
	//enable the timer

	//stop the timer
	CTx->TCR = 1<<1;				//1=reset and disable the timer

	CTx->CTCR&=~0x03;				//reset bit 1..0->count on rising edge of pclk
	CTx->TC = 0;					//reset counter - optional
	CTx->PC = 0;					//reset prescaler
	CTx->PR = ps-1;					//set prescaler
	CTx->MCR= 	(CTx->MCR & ~(0x07 << (3*0))) |
				(0x00 << (3*0));	//set up the match register. no interrupt yet
	CTx->TCR = 1;					//start the timer
}

//set up the match
void tmr0_setpr0(uint32_t pr) {
	//clear the flag
	CTx->IR = 1<<0;					//0=mr0, 1=mr1, 2=mr2, 3=mr3
	//don't enable interrupt
	CTx->MCR= 	(CTx->MCR & ~(0x07 << (3*0))) |
				(0x000 << (3*0));	//set up the match register. no interrupt yet
	CTx->MR0= _tmr_pr0 = pr - 1;

}

//install user handler
void tmr0_act0(void (*isr_ptr)(void)) {
	//install user handler
	_tmrisr0_ptr = isr_ptr;

	//clear the flag
	CTx->IR = 1<<0;					//0=MR0, 1=MR1, 2=MR2, 3=MR3
	//enable interrupt
	CTx->MCR= 	(CTx->MCR & ~(0x07 << (3*0))) |
				(CTMCR_EINT << (3*0));	//set up the match register. no interrupt yet

	//enable irq -> no priority etc.
	//NVIC_EnableIRQ(CTx_IRQn);
	VICIntEnClr = CTx_IRQn;			//1=disable the irq
	VICIntSelect &=~CTx_IRQn;		//0=interrupt is IRQ, 1=interrupt is FIQ
	VICVectAddrx = (uint32_t) T0ISR;	//slot to contain isr address
	VICVectCntlx = (1<<5) | CTx_VICx;				//set the priority	
	VICIntEnable |= CTx_IRQn;		//1=enable interrupt, 0=disable interrupt

}

//set up the match
void tmr0_setpr1(uint32_t pr) {
	//clear the flag
	CTx->IR = 1<<1;					//0=mr0, 1=mr1, 2=mr2, 3=mr3
	//don't enable interrupt
	CTx->MCR= 	(CTx->MCR & ~(0x07 << (3*1))) |
				(0x000 << (3*1));	//set up the match register. no interrupt yet
	CTx->MR1= _tmr_pr1 = pr - 1;

}

//install user handler
void tmr0_act1(void (*isr_ptr)(void)) {
	//install user handler
	_tmrisr1_ptr = isr_ptr;

	//clear the flag
	CTx->IR = 1<<1;					//0=MR0, 1=MR1, 2=MR2, 3=MR3
	//enable interrupt
	CTx->MCR= 	(CTx->MCR & ~(0x07 << (3*1))) |
				(CTMCR_EINT << (3*1));	//set up the match register. no interrupt yet

	//enable irq -> no priority etc.
	//NVIC_EnableIRQ(CTx_IRQn);
	VICIntEnClr = CTx_IRQn;			//1=disable the irq
	VICIntSelect &=~CTx_IRQn;		//0=interrupt is IRQ, 1=interrupt is FIQ
	VICVectAddrx = (uint32_t) T0ISR;	//slot to contain isr address
	VICVectCntlx = (1<<5) | CTx_VICx;				//set the priority	
	VICIntEnable |= CTx_IRQn;		//1=enable interrupt, 0=disable interrupt

}

//set up the match
void tmr0_setpr2(uint32_t pr) {
	//clear the flag
	CTx->IR = 1<<2;					//0=mr0, 1=mr1, 2=mr2, 3=mr3
	//don't enable interrupt
	CTx->MCR= 	(CTx->MCR & ~(0x07 << (3*2))) |
				(0x000 << (3*2));	//set up the match register. no interrupt yet
	CTx->MR2= _tmr_pr2 = pr - 1;

}

//install user handler
void tmr0_act2(void (*isr_ptr)(void)) {
	//install user handler
	_tmrisr2_ptr = isr_ptr;

	//clear the flag
	CTx->IR = 1<<2;					//0=MR0, 1=MR1, 2=MR2, 3=MR3
	//enable interrupt
	CTx->MCR= 	(CTx->MCR & ~(0x07 << (3*2))) |
				(CTMCR_EINT << (3*2));	//set up the match register. no interrupt yet

	//enable irq -> no priority etc.
	//NVIC_EnableIRQ(CTx_IRQn);
	VICIntEnClr = CTx_IRQn;			//1=disable the irq
	VICIntSelect &=~CTx_IRQn;		//0=interrupt is IRQ, 1=interrupt is FIQ
	VICVectAddrx = (uint32_t) T0ISR;	//slot to contain isr address
	VICVectCntlx = (1<<5) | CTx_VICx;				//set the priority	
	VICIntEnable |= CTx_IRQn;		//1=enable interrupt, 0=disable interrupt

}

//set up the match
void tmr0_setpr3(uint32_t pr) {
	//clear the flag
	CTx->IR = 1<<3;					//0=mr0, 1=mr1, 2=mr2, 3=mr3
	//don't enable interrupt
	CTx->MCR= 	(CTx->MCR & ~(0x07 << (3*3))) |
				(0x000 << (3*3));	//set up the match register. no interrupt yet
	CTx->MR3= _tmr_pr3 = pr - 1;

}

//install user handler
void tmr0_act3(void (*isr_ptr)(void)) {
	//install user handler
	_tmrisr3_ptr = isr_ptr;

	//clear the flag
	CTx->IR = 1<<3;					//0=MR0, 1=MR1, 2=MR2, 3=MR3
	//enable interrupt
	CTx->MCR= 	(CTx->MCR & ~(0x07 << (3*3))) |
				(CTMCR_EINT << (3*3));	//set up the match register. no interrupt yet

	//enable irq -> no priority etc.
	//NVIC_EnableIRQ(CTx_IRQn);
	VICIntEnClr = CTx_IRQn;			//1=disable the irq
	VICIntSelect &=~CTx_IRQn;		//0=interrupt is IRQ, 1=interrupt is FIQ
	VICVectAddrx = (uint32_t) T0ISR;	//slot to contain isr address
	VICVectCntlx = (1<<5) | CTx_VICx;				//set the priority	
	VICIntEnable |= CTx_IRQn;		//1=enable interrupt, 0=disable interrupt

}
