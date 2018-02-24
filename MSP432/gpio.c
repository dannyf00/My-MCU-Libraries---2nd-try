//#define TARGET_IS_BLIZZARD_RA1					//indicate parts, for rom functions
//#define PART_TM4C1233H6PM						//indicate parts, for pin / memory definitions


#include "gpio.h"					//we use own gpio macros
//#include "delay.h"					//we use delay -  to prevent the debug pins being locked up

//get pins
//uint16_t IO_GET(GPIO_TypeDef* port, uint16_t pins) {
//	return port->IDR & pins;
//}

//clock management
void SystemCoreClockHSI(uint32_t F_DCO) {
	//change smclk divider
	CS->KEY = CS_KEY_VAL;                   // Unlock CS module for register access
    CS->CTL0 = F_DCO;           			//3:Set DCO to 12MHz (nominal, center of 8-16MHz range), 0=1.5Mhz, 1=3Mhz, 2=6Mhz, 3=12Mhz, 4=24Mhz, 5=48Mhz
    // Select ACLK = REFO, SMCLK = MCLK = DCO
    CS->CTL1 = CS_CTL1_SELA__REFOCLK | CS_CTL1_SELS__DCOCLK | CS_CTL1_SELM__DCOCLK;	//default value
    CS->KEY = 0;                            // Lock CS module from unintended accesses
}

//reset the mcu
void mcu_init(void) {
	//for debugging purposes
	//delay_ms(1000);					//short delay - in case the jtag / swd pins are locked up
	//MAP_SysCtlDelay(F_CPU / 3);				//instead

	WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

	//change clock
	SystemCoreClockHSI_3Mhz();			//run at 3Mhz, DCO/HSI


	//enable the output
    //MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOI);
	//MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

	//ei();							//enable interrupt

    //update SystemCoreClock
    SystemCoreClockUpdate();			//update system clock

}

