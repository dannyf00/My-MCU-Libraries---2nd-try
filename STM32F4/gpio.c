#include "gpio.h"					//we use aruidno port for stm8s

//global definitions

//global variables

//configure gpio DDR mode (cnf1..0 + mod1..0 bits)
void GPIO_DDR(GPIO_TypeDef * GPIOx, uint32_t mask, uint32_t mode) {
	uint8_t pos;
	//uint32_t pin_mask;

	for (pos=0; pos < 16; pos++) {
		//looking for pin position / mask
		//pin_mask = 1ul << pos;
		if (mask & (1ul << pos)) {
			//we have found the pos / pin_mask
			if ((mode & GPIOMODE_OUTPUT) || (mode & GPIOMODE_AF)) {
				GPIOx->OSPEEDR &=~(0x03ul << (2 * pos));	//clear ospeeder
				GPIOx->OSPEEDR |= (0x01ul << (2 * pos));	//set to medium speed (0x01)

				GPIOx->OTYPER &=~(1ul << pos);				//clear otyper
				GPIOx->OTYPER |= ((mode & GPIOMODE_PP)?0ul:1ul) << pos;	//0->pp, 1->od
			}

			GPIOx->MODER &=~(0x03 << (2 * pos));			//clear moder
			GPIOx->MODER |= (mode & 0x03) << (2 * pos);		//set moder

			GPIOx->PUPDR &=~(0x03 << (2 * pos));			//clear pupdr
			GPIOx->PUPDR |= ((mode >> 4) & 0x03) << (2 * pos);	//set pupdr
		}
	}
}

//reset the chip
void mcu_init(void) {
	//select the clock source
	//or use default clock

	//enable clock to GPIO
	RCC->AHB1ENR |=
			RCC_AHB1ENR_GPIOAEN |
			RCC_AHB1ENR_GPIOBEN |
			RCC_AHB1ENR_GPIOCEN |
			RCC_AHB1ENR_GPIODEN |
			RCC_AHB1ENR_GPIOEEN |
#if defined(RCC_AHB1ENR_GPIOFEN)
			RCC_AHB1ENR_GPIOFEN |
#endif
#if defined(RCC_AHB1ENR_GPIOGEN)
			RCC_AHB1ENR_GPIOGEN |
#endif
#if defined(RCC_AHB1ENR_GPIOHEN)
			RCC_AHB1ENR_GPIOHEN |
#endif
#if defined(RCC_AHB1ENR_GPIOIEN)
			RCC_AHB1ENR_GPIOIEN |
#endif
			0x00;

	//update SystemCoreClock - it must be the last step before exiting mcu_init
	SystemCoreClockUpdate();
}
