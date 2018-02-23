#include "gpio.h"					//we use aruidno port for stm8s

//global definitions

//global variables
//configure gpio DDR mode (cnf1..0 + mod1..0 bits)
void GPIO_DDR(GPIO_TypeDef * gpio, uint32_t mask, uint32_t mode) {
	mode = mode & 0x0f;				//lowest 4 bits effective

	//for the lowest 8 bits
	if (mask & (1ul<< 0)) gpio->CRL = (gpio->CRL &~0x0000000ful) | (mode << (0 * 4));
	if (mask & (1ul<< 1)) gpio->CRL = (gpio->CRL &~0x000000f0ul) | (mode << (1 * 4));
	if (mask & (1ul<< 2)) gpio->CRL = (gpio->CRL &~0x00000f00ul) | (mode << (2 * 4));
	if (mask & (1ul<< 3)) gpio->CRL = (gpio->CRL &~0x0000f000ul) | (mode << (3 * 4));
	if (mask & (1ul<< 4)) gpio->CRL = (gpio->CRL &~0x000f0000ul) | (mode << (4 * 4));
	if (mask & (1ul<< 5)) gpio->CRL = (gpio->CRL &~0x00f00000ul) | (mode << (5 * 4));
	if (mask & (1ul<< 6)) gpio->CRL = (gpio->CRL &~0x0f000000ul) | (mode << (6 * 4));
	if (mask & (1ul<< 7)) gpio->CRL = (gpio->CRL &~0xf0000000ul) | (mode << (7 * 4));

	//for the highest 8 bits
	if (mask & (1ul<< 8)) gpio->CRH = (gpio->CRH &~0x0000000ful) | (mode << (0 * 4));
	if (mask & (1ul<< 9)) gpio->CRH = (gpio->CRH &~0x000000f0ul) | (mode << (1 * 4));
	if (mask & (1ul<<10)) gpio->CRH = (gpio->CRH &~0x00000f00ul) | (mode << (2 * 4));
	if (mask & (1ul<<11)) gpio->CRH = (gpio->CRH &~0x0000f000ul) | (mode << (3 * 4));
	if (mask & (1ul<<12)) gpio->CRH = (gpio->CRH &~0x000f0000ul) | (mode << (4 * 4));
	if (mask & (1ul<<13)) gpio->CRH = (gpio->CRH &~0x00f00000ul) | (mode << (5 * 4));
	if (mask & (1ul<<14)) gpio->CRH = (gpio->CRH &~0x0f000000ul) | (mode << (6 * 4));
	if (mask & (1ul<<15)) gpio->CRH = (gpio->CRH &~0xf0000000ul) | (mode << (7 * 4));

}

//reset clock to HSI
void SystemCoreClockHSI(void) {
	RCC->CR |= RCC_CR_HSION;				//turn on HSI
	//wait for HSI to be ready
	while ((RCC->CR & RCC_CR_HSIRDY) == 0) continue;	//1->HSI ready, 0->HSI not ready
	//switch the clock to HSI
	RCC->CFGR = (RCC->CFGR &~RCC_CFGR_SW) | (RCC_CFGR_SW & RCC_CFGR_SW_HSI);
}

//reset clock to HSI
void SystemCoreClockHSE(void) {
	RCC->CR |= RCC_CR_HSEON;				//turn on HSE
	//wait for HSI to be ready
	while ((RCC->CR & RCC_CR_HSERDY) == 0) continue;	//1->HSE ready, 0->HSE not ready
	//switch the clock to HSE
	RCC->CFGR = (RCC->CFGR &~RCC_CFGR_SW) | (RCC_CFGR_SW & RCC_CFGR_SW_HSE);
}

//switch to HSIxPLL
void SystemCoreClockHSIPLL(uint32_t PLLMul_x) {
	SystemCoreClockHSI();					//switch to HSI - so PLL can be disabled

	//RCC->CR |= RCC_CR_HSION;				//turn on HSI - so PLL can be disabled
	//wait for HSI to be ready
	//while ((RCC->CR & RCC_CR_HSIRDY) == 0) continue;	//1->HSI ready, 0->HSI not ready
	//HSI is ready now
	//switch the clock to HSI
	//RCC->CFGR = (RCC->CFGR &~RCC_CFGR_SW) | (RCC_CFGR_SW & RCC_CFGR_SW_HSI);

	//turn off PLL - doable only if PLL is NOT the system clock
	RCC->CR &=~RCC_CR_PLLON;				//1->pll on, 0->pll off
	//configure PLL multiplier
	RCC->CFGR = (RCC->CFGR &~RCC_CFGR_PLLMULL) | (RCC_CFGR_PLLMULL & PLLMul_x);	//set the pll multiplier
	RCC->CFGR = (RCC->CFGR &~RCC_CFGR_PLLSRC) | (RCC_CFGR_PLLSRC & RCC_CFGR_PLLSRC_HSI_Div2);		//0->HSI selected as pll source (pll input = HSI/2); 1->prediv1 as pll source
	RCC->CR |= RCC_CR_PLLON;				//1->pll on, 0->pll off
	while ((RCC->CR & RCC_CR_PLLRDY) == 0) continue;	//1->PLL ready, 0->pll not ready
	//switch the clock to PLL
	RCC->CFGR = (RCC->CFGR &~RCC_CFGR_SW) | (RCC_CFGR_SW & RCC_CFGR_SW_PLL);
	//now hsi/2pll is the clock source
}

//switch to HSExPLL
//Predivx makes sure that PLL output frequency is less than 24Mhz
void SystemCoreClockHSEPLL(uint32_t PLLMul_x, uint32_t PREDIV_x) {
	SystemCoreClockHSI();					//switch to HSI - so PLL can be disabled

	RCC->CR |= RCC_CR_HSEON;				//turn on HSE
	//wait for HSI to be ready
	while ((RCC->CR & RCC_CR_HSERDY) == 0) continue;	//1->HSI ready, 0->HSI not ready
	//HSE is ready now
	//switch the clock to HS
	//RCC->CFGR = (RCC->CFGR &~RCC_CFGR_SW) | (RCC_CFGR_SW & RCC_CFGR_SW_HSE);

	//turn off PLL - doable only if PLL is NOT the system clock
	RCC->CR &=~RCC_CR_PLLON;				//1->pll on, 0->pll off
	//configure predivider
	RCC->CFGR = (RCC->CFGR &~RCC_CFGR2_PREDIV1) | (RCC_CFGR2_PREDIV1 & PREDIV_x);
	//configure PLL multiplier
	RCC->CFGR = (RCC->CFGR &~RCC_CFGR_PLLMULL) | (RCC_CFGR_PLLMULL & PLLMul_x);	//set the pll multiplier
	RCC->CFGR = (RCC->CFGR &~RCC_CFGR_PLLSRC) | (RCC_CFGR_PLLSRC & (1<<16));		//0->HSI selected as pll source (pll input = HSI/2); 1->prediv1 as pll source
	RCC->CR |= RCC_CR_PLLON;				//1->pll on, 0->pll off
	while ((RCC->CR & RCC_CR_PLLRDY) == 0) continue;	//1->PLL ready, 0->pll not ready
	//switch the clock to PLL
	RCC->CFGR = (RCC->CFGR &~RCC_CFGR_SW) | (RCC_CFGR_SW & RCC_CFGR_SW_PLL);
	//now hsi/2pll is the clock source
}

//reset the chip
void mcu_init(void) {
	//select the clock source
	//or use default clock
	//SystemCoreClockHSI();					//use HSi as system coreclock
	//SystemCoreClockHSE();					//use hse as system core clock
	//SystemCoreClockHSIPLL_12Mhz();			//hsipll at 12Mhz
	//SystemCoreClockHSEPLL(RCC_PLLMul4, RCC_PREDIV2);	//HSEPLL, 8Mhz/2*4=16Mhz

	//enable clock to GPIO
	RCC->APB2ENR |=
			RCC_APB2ENR_IOPAEN |
			RCC_APB2ENR_IOPBEN |
			RCC_APB2ENR_IOPCEN |
			RCC_APB2ENR_IOPDEN |
			RCC_APB2ENR_IOPEEN |
#if defined(RCC_APB2ENR_IOPFEN)
			RCC_APB2ENR_IOPFEN |
#endif
#if defined(RCC_APB2ENR_IOPGEN)
			RCC_APB2ENR_IOPGEN |
#endif
			0x00;

	//update SystemCoreClock - it must be the last step before exiting mcu_init
	SystemCoreClockUpdate();
}
