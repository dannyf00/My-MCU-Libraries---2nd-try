#include "ptmr0_mr.h"				//timer from pwm match channels

//hardware configuration
//end hardware configuration

//global defines
#define PWMx			PWM0
#define PWMx_IRQn		(1<<8)		//4=TIMER0, 5=TIMER1, 6=UART0, 7=UART1, 8=PWM0
#define PWMx_VICx		8			//vic channel. needs to be unique
#define VICVectAddrx	VICVectAddr8	  	//determined by CTx_VICx
#define VICVectCntlx	VICVectCntl8		//deterlimined by CTx_VICx

#define PWMx_EINT		0x01		//interrupt on match
#define PWMx_RESET		0x02		//reset on match
#define PWMx_STOP		0x04		//stop on match

//global variables
//empty handler
static void empty_handler(void) {
	//do nothing here
}

//global variable
//pointer to user handler
static void (* _tmr_isrptr0)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler
static void (* _tmr_isrptr1)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler
static void (* _tmr_isrptr2)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler
static void (* _tmr_isrptr3)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler
static void (* _tmr_isrptr4)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler
static void (* _tmr_isrptr5)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler
static void (* _tmr_isrptr6)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler

static uint32_t _tmr_pr0 = 0xffff;	//period register
static uint32_t _tmr_pr1 = 0xffff;	//period register
static uint32_t _tmr_pr2 = 0xffff;	//period register
static uint32_t _tmr_pr3 = 0xffff;	//period register
static uint32_t _tmr_pr4 = 0xffff;	//period register
static uint32_t _tmr_pr5 = 0xffff;	//period register
static uint32_t _tmr_pr6 = 0xffff;	//period register

//pwm isr
void __irq PWM0ISR(void) {
	if (PWMx->IR & (1<<0)) {		//mr0 interrupt
		PWMx->IR |= (1<<0);			//'1' to clear flag
		PWMx->MR0+= _tmr_pr0;		//update match register
		_tmr_isrptr0();				//run user interrupt
	}

	if (PWMx->IR & (1<<1)) {		//mr0 interrupt
		PWMx->IR |= (1<<1);			//'1' to clear flag
		PWMx->MR1+= _tmr_pr1;		//update match register
		_tmr_isrptr1();				//run user interrupt
	}

	if (PWMx->IR & (1<<2)) {		//mr0 interrupt
		PWMx->IR |= (1<<2);			//'1' to clear flag
		PWMx->MR2+= _tmr_pr2;		//update match register
		_tmr_isrptr2();				//run user interrupt
	}

	if (PWMx->IR & (1<<3)) {		//mr0 interrupt
		PWMx->IR |= (1<<3);			//'1' to clear flag
		PWMx->MR3+= _tmr_pr3;		//update match register
		_tmr_isrptr3();				//run user interrupt
	}

	if (PWMx->IR & (1<<8)) {		//mr0 interrupt
		PWMx->IR |= (1<<8);			//'1' to clear flag
		PWMx->MR4+= _tmr_pr4;		//update match register
		_tmr_isrptr4();				//run user interrupt
	}

	if (PWMx->IR & (1<<9)) {		//mr0 interrupt
		PWMx->IR |= (1<<9);			//'1' to clear flag
		PWMx->MR5+= _tmr_pr5;		//update match register
		_tmr_isrptr5();				//run user interrupt
	}

	if (PWMx->IR & (1<<10)) {		//mr0 interrupt
		PWMx->IR |= (1<<10);			//'1' to clear flag
		PWMx->MR6+= _tmr_pr6;		//update match register
		_tmr_isrptr6();				//run user interrupt
	}

	VICVectAddr = 0x00000000; 					//Dummy write to signal end of interrupt

}

//reset the pwm with a prescaler
void ptmr0_init(uint32_t ps) {
	//stop the pwm
	PWMx->TCR |= (1<<1);			//1=reset the counter 
	PWMx->TCR &=~(1<<0);			//0=disable the counter; 1=enable the counter
	PWMx->TCR &=~(1<<3);			//0=disable pwm (=standard timer), 1=enable pwm

	//set up the pwm
	PWMx->PR = ps - 1;				//load the prescaler
	
	//set pwm as up counter
	PWMx->PCR &=~(1<<0);			//0=upcounter, 1=up/down counter
	PWMx->TC = 0;					//reset the counter for upcounter

	//start the pwm
	//do not enable pwm mode - we are using the pwm module as a timer
	PWMx->TCR |= (1<<0);			//1=enable the counter, 0=disable the counter
	PWMx->TCR &=~(1<<1);			//1=reset the counter, 0=start the counter
}

//set the period
void ptmr0_setpr0(uint32_t pr) {
	//clear the flag
	PWMx->IR |= (1<<0);				//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*0))) |		//clear the bigs
				(0x00 << (3*0));
	PWMx->MR0 = _tmr_pr0 = pr - 1;	//save and load the period

}

//insert the user handler
void ptmr0_act0(void (*isr_ptr)(void)) {
	_tmr_isrptr0=isr_ptr;								//install user handler
	//clear the flag
	PWMx->IR |= (1<<0);									//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*0))) |		//clear the bigs
				(PWMx_EINT << (3*0));

	//enable vic
	//NVIC_EnableIRQ(PWMx_IRQn);
	VICIntEnClr = PWMx_IRQn;							//1=disable the irq
	VICIntSelect &=~PWMx_IRQn;							//0=interrupt is IRQ, 1=interrupt is FIQ
	VICVectAddrx = (uint32_t) PWM0ISR;					//slot to contain isr address
	VICVectCntlx = (1<<5) | PWMx_VICx;					//set the priority	
	VICIntEnable |= PWMx_IRQn;							//1=enable interrupt, 0=disable interrupt

}

//set the period
void ptmr0_setpr1(uint32_t pr) {
	//clear the flag
	PWMx->IR |= (1<<1);				//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*1))) |		//clear the bigs
				(0x00 << (3*1));
	PWMx->MR1 = _tmr_pr1 = pr - 1;	//save and load the period

}

//insert the user handler
void ptmr0_act1(void (*isr_ptr)(void)) {
	_tmr_isrptr1=isr_ptr;								//install user handler
	//clear the flag
	PWMx->IR |= (1<<1);									//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*1))) |		//clear the bigs
				(PWMx_EINT << (3*1));

	//enable vic
	//NVIC_EnableIRQ(PWMx_IRQn);
	VICIntEnClr = PWMx_IRQn;							//1=disable the irq
	VICIntSelect &=~PWMx_IRQn;							//0=interrupt is IRQ, 1=interrupt is FIQ
	VICVectAddrx = (uint32_t) PWM0ISR;					//slot to contain isr address
	VICVectCntlx = (1<<5) | PWMx_VICx;					//set the priority	
	VICIntEnable |= PWMx_IRQn;							//1=enable interrupt, 0=disable interrupt

}

//set the period
void ptmr0_setpr2(uint32_t pr) {
	//clear the flag
	PWMx->IR |= (1<<2);				//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*2))) |		//clear the bigs
				(0x00 << (3*2));
	PWMx->MR2 = _tmr_pr2 = pr - 1;	//save and load the period

}

//insert the user handler
void ptmr0_act2(void (*isr_ptr)(void)) {
	_tmr_isrptr2=isr_ptr;								//install user handler
	//clear the flag
	PWMx->IR |= (1<<2);									//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*2))) |		//clear the bigs
				(PWMx_EINT << (3*2));

	//enable vic
	//NVIC_EnableIRQ(PWMx_IRQn);
	VICIntEnClr = PWMx_IRQn;							//1=disable the irq
	VICIntSelect &=~PWMx_IRQn;							//0=interrupt is IRQ, 1=interrupt is FIQ
	VICVectAddrx = (uint32_t) PWM0ISR;					//slot to contain isr address
	VICVectCntlx = (1<<5) | PWMx_VICx;					//set the priority	
	VICIntEnable |= PWMx_IRQn;							//1=enable interrupt, 0=disable interrupt

}

//set the period
void ptmr0_setpr3(uint32_t pr) {
	//clear the flag
	PWMx->IR |= (1<<3);				//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*3))) |		//clear the bigs
				(0x00 << (3*3));
	PWMx->MR3 = _tmr_pr3 = pr - 1;	//save and load the period

}

//insert the user handler
void ptmr0_act3(void (*isr_ptr)(void)) {
	_tmr_isrptr3=isr_ptr;								//install user handler
	//clear the flag
	PWMx->IR |= (1<<3);									//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*3))) |		//clear the bigs
				(PWMx_EINT << (3*3));

	//enable vic
	//NVIC_EnableIRQ(PWMx_IRQn);
	VICIntEnClr = PWMx_IRQn;							//1=disable the irq
	VICIntSelect &=~PWMx_IRQn;							//0=interrupt is IRQ, 1=interrupt is FIQ
	VICVectAddrx = (uint32_t) PWM0ISR;					//slot to contain isr address
	VICVectCntlx = (1<<5) | PWMx_VICx;					//set the priority	
	VICIntEnable |= PWMx_IRQn;							//1=enable interrupt, 0=disable interrupt

}

//set the period
void ptmr0_setpr4(uint32_t pr) {
	//clear the flag
	PWMx->IR |= (1<<4);				//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*4))) |		//clear the bigs
				(0x00 << (3*4));
	PWMx->MR4 = _tmr_pr4 = pr - 1;	//save and load the period

}

//insert the user handler
void ptmr0_act4(void (*isr_ptr)(void)) {
	_tmr_isrptr4=isr_ptr;								//install user handler
	//clear the flag
	PWMx->IR |= (1<<4);									//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*4))) |		//clear the bigs
				(PWMx_EINT << (3*4));

	//enable vic
	//NVIC_EnableIRQ(PWMx_IRQn);
	VICIntEnClr = PWMx_IRQn;							//1=disable the irq
	VICIntSelect &=~PWMx_IRQn;							//0=interrupt is IRQ, 1=interrupt is FIQ
	VICVectAddrx = (uint32_t) PWM0ISR;					//slot to contain isr address
	VICVectCntlx = (1<<5) | PWMx_VICx;					//set the priority	
	VICIntEnable |= PWMx_IRQn;							//1=enable interrupt, 0=disable interrupt

}

//set the period
void ptmr0_setpr5(uint32_t pr) {
	//clear the flag
	PWMx->IR |= (1<<5);				//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*5))) |		//clear the bigs
				(0x00 << (3*5));
	PWMx->MR5 = _tmr_pr5 = pr - 1;	//save and load the period

}

//insert the user handler
void ptmr0_act5(void (*isr_ptr)(void)) {
	_tmr_isrptr5=isr_ptr;								//install user handler
	//clear the flag
	PWMx->IR |= (1<<5);									//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*5))) |		//clear the bigs
				(PWMx_EINT << (3*5));

	//enable vic
	//NVIC_EnableIRQ(PWMx_IRQn);
	VICIntEnClr = PWMx_IRQn;							//1=disable the irq
	VICIntSelect &=~PWMx_IRQn;							//0=interrupt is IRQ, 1=interrupt is FIQ
	VICVectAddrx = (uint32_t) PWM0ISR;					//slot to contain isr address
	VICVectCntlx = (1<<5) | PWMx_VICx;					//set the priority	
	VICIntEnable |= PWMx_IRQn;							//1=enable interrupt, 0=disable interrupt

}

//set the period
void ptmr0_setpr6(uint32_t pr) {
	//clear the flag
	PWMx->IR |= (1<<6);				//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*6))) |		//clear the bigs
				(0x00 << (3*6));
	PWMx->MR6 = _tmr_pr6 = pr - 1;	//save and load the period

}

//insert the user handler
void ptmr0_act6(void (*isr_ptr)(void)) {
	_tmr_isrptr6=isr_ptr;								//install user handler
	//clear the flag
	PWMx->IR |= (1<<6);									//1=clear the flag
	PWMx->MCR =	(PWMx->MCR & ~(0x07 << (3*6))) |		//clear the bigs
				(PWMx_EINT << (3*6));

	//enable vic
	//NVIC_EnableIRQ(PWMx_IRQn);
	VICIntEnClr = PWMx_IRQn;							//1=disable the irq
	VICIntSelect &=~PWMx_IRQn;							//0=interrupt is IRQ, 1=interrupt is FIQ
	VICVectAddrx = (uint32_t) PWM0ISR;					//slot to contain isr address
	VICVectCntlx = (1<<5) | PWMx_VICx;					//set the priority	
	VICIntEnable |= PWMx_IRQn;							//1=enable interrupt, 0=disable interrupt

}
