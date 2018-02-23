#include "awu.h"					//we use awu

//hardware configuration
#define AWU_TBR			AWU_TB1024x	//define timebase for AWU
//end hardware configuration

//empty handler
static void empty_handler(void) {
	//do nothing
}

//global variables
static void (*/*_tim4*/_isrptr) (void)=empty_handler;					//tim isr handler ptr

#pragma vector = AWU_vector			//awu interrupt
__interrupt void awu_isr(void) {	//awu handler
//INTERRUPT_HANDLER(awu_isr, AWU_vector-2) {
	AWU->CSR;						//clear the flag by reading the CSR register
	_isrptr();						//execute user handler
}

//reset awu
//may need to adjust TBR register for desired duration
//ps = 1..63
void awu_init(uint8_t ps) {
	_isrptr = empty_handler;		//reset _isrptr
	CLK->PCKENR2 |= CLK_PCKENR2_AWU;//1->enable clock to awu, 0->disable awu
	AWU->CSR |= AWU_CSR_MSR;		//1->turn on measurement to tim1/tim3 -> also turn on LSI oscillator
	AWU->CSR &=~AWU_CSR_AWUEN;		//0->disable AWU, 1->enable AWU
	AWU->APR = ps & 0x3f - 1;		//lowest 6 bits effective - cannot be kept at its reset value of 0x3f
	AWU->TBR = AWU_TBR;				//0->no interrupts, 1->APR/fs, 11->2^10APR/fs
	//AWU->CSR |= AWU_CSR_AWUEN;	//0->disable AWU, 1->enable AWU
	//interrupt is not yet enabled
}

//install awu handler
void awu_act(void (*isr_ptr)(void)) {
	_isrptr = isr_ptr;				//point to user handler
	AWU->CSR |= AWU_CSR_AWUEN;		//0->disable AWU, 1->enable AWU
	//interrupt is enabled
}
