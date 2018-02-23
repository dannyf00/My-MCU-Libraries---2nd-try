//#include <lpc122x.h>				//we use lpc122x
#include "tmr16b1_pwm.h"			//we use tmr16b0

//hardware configuration
//end hardware configuration

//global defines
#define CTx				LPC_CT16B1	//16bix timer0
//#define CTx_IRQn		TIMER_32_1_IRQn

#define CTxMR_EINT		0b001		//enable interrupt on match
#define CTxMR_RESET		0b010		//reset tc on match
#define CTxMR_STOP		0b100		//stop on match


//set up tmr into pwm mode
//MR0 sets PWM periods
//MR1 generates PWm outputs
void tmr16b1_pwminit(uint32_t ps, uint32_t pr) {
	//route clock to timer
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<8);		//7=ct16b0, 8=ct16b1, 9=ct16b1, 10=ct32b1

	//configure as counter
	CTx->CTCR = (CTx->CTCR & ~0b11) | 0b00;		//00->as counter

	//set up the timer
	CTx->TCR&=~(1<<0);							//disable the timer
	//CTx->PC = (prescaler-1) & 0xffff;			//set up the prescaler
	CTx->PR = (ps-1)/* & 0xffff*/;				//set up the 32-bit prescaler register
	CTx->IR|=	(1<<0) |						//clear the interrupt flag on match channel 0..3, by writing 1s to it
				(1<<1) |
				(1<<2) |
				(1<<3);
	CTx->MR0 = (pr - 1);						//set pwm period
	CTx->MCR =	(CTx->MCR & ~(0b111<<(3*0))) |	//clear MCR
				((CTxMR_RESET & 0b111) << (3*0));		//0b00x: trigger an interrupt; 0b0x0: reset on match; 0bx00: stop on match
	CTx->TC = 0;								//reset the counter
	CTx->TCR|= (1<<0);							//start the timer
}

//set up match register - ch1
void tmr16b1_setdc1(uint32_t match/*, uint32_t config*/) {
	//enable timer interrupt on match
	CTx->MCR =	(CTx->MCR & ~(0b111<<(3*1))) |	//clear MCR
				((0b000 & 0b111) << (3*1));		//0b00x: trigger an interrupt; 0b0x0: reset on match; 0bx00: stop on match
	CTx->MR1 = (CTx->MR0 - match + 1)/* & 0xffff*/;			//set the match register
	CTx->PWMC|= 1<<1;							//pin controlled by pwm1
	//MAT1 on P0.16
	//output can be mapped to multiple pins, with differing masks (0x03 / 0x04)
	LPC_IOCON->PIO0_16 = (LPC_IOCON->PIO0_16 & ~(0x07)) | 0x04;     //4 -> set up pin for PWM use (sec 7.4.23)
}


