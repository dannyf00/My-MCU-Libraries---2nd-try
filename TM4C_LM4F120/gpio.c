//#define TARGET_IS_BLIZZARD_RA1					//indicate parts, for rom functions
//#define PART_TM4C1233H6PM						//indicate parts, for pin / memory definitions


#include "gpio.h"					//we use own gpio macros
//#include "delay.h"					//we use delay -  to prevent the debug pins being locked up

//get pins
//uint16_t IO_GET(GPIO_TypeDef* port, uint16_t pins) {
//	return port->IDR & pins;
//}

//set SystemCoreClock to HSI
//use RCC only
//sysdiv lowest 4 bits effective
void SystemCoreClock2HSI(uint32_t sysdiv) {
	//not use RCC2
	SYSCTL->RCC2 &=~(1<<31);					//1->use RCC2, 0->not used RCC2(=use RCC)
	//enable PIOSC: where is POSCDIS bit?

	//set OSCSRC to PIOSC
	SYSCTL->RCC = (SYSCTL->RCC &~(0x03<<4)) | (0x01 << 4);	//0x00->MainOSC/XTAL, 0x01->PIOSC, 0x02->PIOSC/4, 0x03->LSI

	//bypass PLL
	SYSCTL->RCC|= (1<<11);						//1->use osc and divide by sysdiv; 0->use pll and divide by sysdiv

	//set SYSDIV
	SYSCTL->RCC = (SYSCTL->RCC &~(0x0f << 23)) | ((0x0f & sysdiv) << 23);

}

//set SystemCoreClock to HSI/4
//use RCC only
//sysdiv lowest 4 bits effective
void SystemCoreClock2HSI4(uint32_t sysdiv) {
	//not use RCC2
	SYSCTL->RCC2 &=~(1<<31);					//1->use RCC2, 0->not used RCC2(=use RCC)
	//enable PIOSC: where is POSCDIS bit?

	//set OSCSRC to PIOSC
	SYSCTL->RCC = (SYSCTL->RCC &~(0x03<<4)) | (0x02 << 4);	//0x00->MainOSC/XTAL, 0x01->PIOSC, 0x02->PIOSC/4, 0x03->LSI

	//bypass PLL
	SYSCTL->RCC|= (1<<11);						//1->use osc and divide by sysdiv; 0->use pll and divide by sysdiv

	//set SYSDIV
	SYSCTL->RCC = (SYSCTL->RCC &~(0x0f << 23)) | ((0x0f & sysdiv) << 23);

}

//set SystemCoreClock to hsipll
void SystemCoreClock2HSIPLL(uint32_t mul, uint32_t div) {

}

//set SystemCoreClock to HSE
//sysdiv lowest 4 bits effective
void SystemCoreClock2HSE(uint32_t sysdiv) {
	//not use RCC2
	SYSCTL->RCC2 &=~(1<<31);					//1->use RCC2, 0->not used RCC2(=use RCC)
	//enable PIOSC: where is POSCDIS bit?

	//set OSCSRC to PIOSC
	SYSCTL->RCC = (SYSCTL->RCC &~(0x03<<4)) | (0x00 << 4);	//0x00->MainOSC/XTAL, 0x01->PIOSC, 0x02->PIOSC/4, 0x03->LSI

	//bypass PLL
	SYSCTL->RCC|= (1<<11);						//1->use osc and divide by sysdiv; 0->use pll and divide by sysdiv

	//set SYSDIV
	SYSCTL->RCC = (SYSCTL->RCC &~(0x0f << 23)) | ((0x0f & sysdiv) << 23);


}

//set SystemCoreClock to HSEPLL
void SystemCoreClock2HSEPLL(uint32_t mul, uint32_t div) {

}
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
	SystemCoreClock2HSI(RCC_SYSDIV2);			//16Mhz piosc/2
	//SystemCoreClock2HSI_0M50hz();
	//SystemCoreClockHSE_50Mhz();
	SystemCoreClock2HSE(RCC_SYSDIV2);			//use mainosc
	
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

