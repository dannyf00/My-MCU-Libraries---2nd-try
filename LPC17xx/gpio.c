#include "gpio.h"					//we use own gpio macros

//set pins to output
//port = GPIOA..x, as the chip may support
//void IO_OUT(uint8_t port, uint32_t pins) {
	/* Set PIO2_9 as output. */
//	GPIO_SetDir(port, pins, 1);
//}

//set pins as floating input
//void IO_OUT(uint8_t port, uint32_t pins) {
	/* Set PIO2_9 as output. */
//	GPIO_SetDir(port, pins, 0);
//}

//get pins
//uint16_t IO_GET(GPIO_TypeDef* port, uint16_t pins) {
//	return port->IDR & pins;
//}

//reset the mcu
void mcu_init(void) {
	/* Enable AHB clock to the GPIO domain. */
	LPC_SC->PCONP |= 1<<15;			//15: enable clock to gpio

	//update SystemCoreClock - must be the last thing to do
	SystemCoreClockUpdate();		//update SystemCoreClock
}

