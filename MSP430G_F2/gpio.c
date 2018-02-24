//msp430 gpio source file

#include "gpio.h"					//we use own gpio macros
#include "delay.h"					//we use delay -  to prevent the debug pins being locked up

//get pins
//uint16_t IO_GET(GPIO_TypeDef* port, uint16_t pins) {
//	return port->IDR & pins;
//}

//clock management
uint32_t SystemCoreClock=1000000ul;	//default clock

//dco settting
void SystemCoreClock2DCO(uint16_t clk) {
/*	
	//to be implemented later
	// Clock System Setup
  	CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers
	
	//set/clear RSEL bit
	if (clk & DCO_RSEL2x) CSCTL1 |= DCO_RSEL2x; else CSCTL1 &=~DCO_RSEL2x;
	//set/clear FSEL bits
	CSCTL1 = (CSCTL1 &~DCO_FSEL7) | (clk & DCO_FSEL7);
	//return SystemCoreClock
	switch (clk & DCO_FSEL7) {
	case DCO_FSEL0: SystemCoreClock = (CSCTL1 & DCO_RSEL2x)? 1000000ul:1000000ul; break;
	case DCO_FSEL1: SystemCoreClock = (CSCTL1 & DCO_RSEL2x)? 5330000ul:2670000ul; break;
	case DCO_FSEL2: SystemCoreClock = (CSCTL1 & DCO_RSEL2x)? 7000000ul:3500000ul; break;
	case DCO_FSEL3: SystemCoreClock = (CSCTL1 & DCO_RSEL2x)? 8000000ul:4000000ul; break;
	case DCO_FSEL4: SystemCoreClock = (CSCTL1 & DCO_RSEL2x)?16000000ul:5330000ul; break;
	case DCO_FSEL5: SystemCoreClock = (CSCTL1 & DCO_RSEL2x)?21000000ul:7000000ul; break;
	case DCO_FSEL6: SystemCoreClock = (CSCTL1 & DCO_RSEL2x)?24000000ul:8000000ul; break;
	//case DCO_FSEL7: SystemCoreClock = (CSCTL1 & DCO_RSEL2x)?5330000ul:2670000ul; break;
	}
	CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;  // Set SMCLK = MCLK = DCO
                                            // ACLK = VLOCLK
  	CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers to 1
  	CSCTL0_H = 0;                             // Lock CS registers
*/
}

//reset the mcu
void mcu_init(void) {

  	// Stop watchdog timer to prevent time out reset
  	WDTCTL = WDTPW + WDTHOLD;
#if defined(PM5CTL0)
	PM5CTL0 &= ~LOCKLPM5;           	// Disable the GPIO power-on default high-impedance mode
    	                              	// to activate previously configured port settings
#endif
	
	//clock mgmt
	SystemCoreClock2DCO_1Mhz();
	
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

