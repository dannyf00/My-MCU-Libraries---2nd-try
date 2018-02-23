#include "dac.h"							//we use dac

//initialize dac
void dac_init(void) {
	//initialize the DAC
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;		//enable clock to DAC
	DAC->CR = 	(0<<29) |					//0=DAC2 under-run interrupt disabled
				(0<<28) |					//0->DAC2 DMA disabled
				(0<<24) |					//0->unmask = 1
				(0<<22) |					//0->wave generation disabled
				(7<<19) |					//7->triggered by software
				(1<<18) |					//1->trigge enabled for DACn
				(0<<17) |					//0->output buffered ***enabled***
				(1<<16) |					//0->disable DACn, 1->enable DACn
				(0<<14) |					//0=DAC2 under-run interrupt disabled
				(0<<13) |					//0->DAC2 DMA disabled
				(0<< 8) |					//0->unmask = 1
				(0<< 6) |					//0->wave generation disabled
				(7<< 3) |					//7->triggered by software
				(1<< 2) |					//1->trigge enabled for DACn
				(0<< 1) |					//0->output buffered ***enabled***
				(1<< 0) |					//0->disable DACn, 1->enable DACn
				0x00;
}

//extended function
//output a 12-bit value on DACn ch 1
//DAC1 = PA4 = Pin 4
void DAC1Write(uint16_t val) {
	IO_AFPP(GPIOA, 1<<4);					//GIO_AFPP(GPIO_PinDef[4].gpio, GPIO_PinDef[4].mask);	//configure pin 4 as afio output
	DAC->DHR12R1 = val & 0x0ffful;			//bound the value to [0..4095]
	DAC->SWTRIGR|= (1<<0);					//output on DAC1 - cleared by hardware
}

//output a 12-bit value on DACn ch 2
//DAC2 = PA5 = Pin 5
void DAC2Write(uint16_t val) {
	IO_AFPP(GPIOA, 1<<5);					//GIO_AFPP(GPIO_PinDef[5].gpio, GPIO_PinDef[5].mask);	//configure pin 5 as afio output
	DAC->DHR12R2 = val & 0x0ffful;			//bound the value to [0..4095]
	DAC->SWTRIGR|= (1<<1);					//output on DAC2 - cleared by hardware
}

