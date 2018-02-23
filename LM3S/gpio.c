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

	delay_ms(1000ul/8);								//short delay - in case the jtag / swd pins are locked up
	//MAP_SysCtlDelay(F_CPU / 3);					//instead

	//
    // Set the clocking to run directly from the crystal.
    //
	//SystemCoreClockHSI_10Mhz();
	//SystemCoreClockHSE_50Mhz();
	
	//enable the GPIO (on RCGC2)
	SYSCTL->RCGC2 |= (1<<0);						//0->GPIOA	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SYSCTL->RCGC2 |= (1<<1);						//0->GPIOA	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SYSCTL->RCGC2 |= (1<<2);						//0->GPIOA	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SYSCTL->RCGC2 |= (1<<3);						//0->GPIOA	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SYSCTL->RCGC2 |= (1<<4);						//0->GPIOA	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SYSCTL->RCGC2 |= (1<<5);						//0->GPIOA	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SYSCTL->RCGC2 |= (1<<6);						//0->GPIOA	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	//IO_IN(LED_PORT, LEDR | LEDG | LEDB);	//turn all leds off

	//ei();							//enable interrupt

	//update systemcoreclock
	SystemCoreClockUpdate();
}

