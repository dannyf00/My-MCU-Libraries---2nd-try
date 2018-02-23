//#define TARGET_IS_BLIZZARD_RA1					//indicate parts, for rom functions
//#define PART_TM4C1233H6PM						//indicate parts, for pin / memory definitions


#include "gpio.h"					//we use own gpio macros
#include "delay.h"					//we use delay -  to prevent the debug pins being locked up

//get pins
//uint16_t IO_GET(GPIO_TypeDef* port, uint16_t pins) {
//	return port->IDR & pins;
//}


//reset the mcu
void mcu_init(void) {
	volatile int i;

	SystemInit();								//CMSIS reset - optional

	//for debugging purposes
	//delay_ms(1000);							//short delay - in case the jtag / swd pins are locked up
	//MAP_SysCtlDelay(F_CPU / 3);				//instead
	i = 1000000ul; while (i--) continue;						//waste sometime, per Luminary app note

	//
    // Set the clocking to run directly from the crystal.
    //
	//SystemCoreClockHSI_10Mhz();
	//SystemCoreClockHSE_50Mhz();
	
	//enable the output
	//SYSCTL->RCGCGPIO |= (1<<0);					//0->GPIOA	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	//SYSCTL->RCGCGPIO |= (1<<1);					//1->GPIOB	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	//SYSCTL->RCGCGPIO |= (1<<2);					//2->GPIOC	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	//SYSCTL->RCGCGPIO |= (1<<3);					//3->GPIOD	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	//SYSCTL->RCGCGPIO |= (1<<4);					//4->GPIOE	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SYSCTL->RCGCGPIO |= (1<<5);						//5->GPIOF	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//SYSCTL->RCGCGPIO |= (1<<6);					//6->GPIOG	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOI);
	//SYSCTL->RCGCGPIO |= (1<<7);					//7->GPIOH	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
	//check for status - not available on all chips
	//only test for gpioa..gpiof
	//while ((SYSCTL->PRGPIO & 0x3f) != 0x3f) continue;	//1->peripheral ready, 0->peripheral not ready

	//IO_IN(LED_PORT, LEDR | LEDG | LEDB);	//turn all leds off

	//ei();							//enable interrupt

	//update systemcoreclock
	SystemCoreClockUpdate();
}

