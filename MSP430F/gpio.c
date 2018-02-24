//msp430 gpio source file

#include "gpio.h"					//we use own gpio macros
#include "delay.h"					//we use delay -  to prevent the debug pins being locked up

//get pins
//uint16_t IO_GET(GPIO_TypeDef* port, uint16_t pins) {
//	return port->IDR & pins;
//}

//reset the mcu
void mcu_init(void) {

    //WDTCTL=WDTPW + WDTHOLD; 			// πÿ±’ø¥√≈π∑
   	WDTCTL = WDTPW | WDTHOLD;			// Stop watchdog timer

	//set up ports / pins
#if defined(P1SEL)
	P1SEL = 0x00;						//all pins digital
#endif

#if defined(P2SEL)
	P2SEL = 0x00;						//all pins digital
#endif

#if defined(P3SEL)
	P3SEL = 0x00;						//all pins digital
#endif

#if defined(P4SEL)
	P4SEL = 0x00;						//all pins digital
#endif

	//delay_ms(100);					//short delay - in case the jtag / swd pins are locked up

	//
    // Set the clocking to run directly from the crystal.
    //
	//MAP_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	//MAP_SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);	//works for adc

	//enable the output
    //MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOI);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

	//IO_IN(LED_DDR, LEDR | LEDG | LEDB);	//turn all leds off

	//ei();							//enable interrupt
}

