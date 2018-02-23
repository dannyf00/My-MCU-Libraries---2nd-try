//#include "lpc13xx.h"				//we use lpx1343
//#include <stm32f10x.h>
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_gpio.h"
#include "gpio.h"					//we use own gpio macros
#include "delay.h"

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

//clock management
//set systemcoreclock to IRC
void SystemCoreClockHSI(void) {
	int i;
	//power up HSI/IRC
	LPC_SYSCON->PDRUNCFG     &= ~(1 << 1);          /* 0->Power-up IRC, 1->power down      */
	LPC_SYSCON->IRCCTRL    = 0x00;					//reset irc trim value
	for (i = 0; i < 200; i++) __NOP();

	LPC_SYSCON->MAINCLKSEL    = 0x00;     			/* Select PLL Clock Output:0x00->HSI/IRC, 0x01->HSI/HSE, 0x02->WDT, 0x03->PLL  */
	//update unlock sequence
	LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
	LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
	LPC_SYSCON->MAINCLKUEN    = 0x01;
	while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */
}

//set systemcoreclock to IRCPLL
void SystemCoreClockHSIPLL(uint32_t Mul, uint32_t Div) {
	int i;
	//power up HSI/IRC
	LPC_SYSCON->PDRUNCFG     &= ~(1 << 1);          /* 0->Power-up IRC, 1->power down      */
	LPC_SYSCON->IRCCTRL    = 0x00;					//reset irc trim value
	for (i = 0; i < 200; i++) __NOP();

	//configure PLL
	LPC_SYSCON->SYSPLLCLKSEL  = 0x00;				//select pll input clock, 0x01->system osc/hse, 0x00->hsi/irc
	LPC_SYSCON->SYSPLLCTRL    = (Mul & 0x01f) | (Div & (0x03 << 5));
	LPC_SYSCON->PDRUNCFG     &= ~(1 << 7);          /* 0->Power-up SYSPLL          */
	while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	      /* Wait Until PLL Locked    */

	//switch clock
	LPC_SYSCON->MAINCLKSEL    = 0x03;     			/* Select PLL Clock Output:0x00->HSI/IRC, 0x01->HSI/HSE, 0x02->WDT, 0x03->PLL  */
	//update unlock sequence
	LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
	LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
	LPC_SYSCON->MAINCLKUEN    = 0x01;
	while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */

}

//set systemcoreclock to SystemClock/HSE
void SystemCoreClockHSE(void) {
	int i;
	//power up HSE/SystemOSC
	LPC_SYSCON->PDRUNCFG     &= ~(1 << 5);          /* 0->Power-up System Osc, 1->power down      */
	LPC_SYSCON->SYSOSCCTRL    = 0x00;
	for (i = 0; i < 200; i++) __NOP();

	//configure syspllclksel to hse/system osc
	LPC_SYSCON->SYSPLLCLKSEL  = 0x01;				//select pll input clock, 0x01->system osc/hse, 0x00->hsi/irc

	LPC_SYSCON->MAINCLKSEL    = 0x01;     			/* Select PLL Clock Output:0x00->HSI/IRC, 0x01->HSI/HSE, 0x02->WDT, 0x03->PLL  */
	//update unlock sequence
	LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
	LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
	LPC_SYSCON->MAINCLKUEN    = 0x01;
	while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */

}

//set systemcoreclock to system osc x PLL
void SystemCoreClockHSEPLL(uint32_t Mul, uint32_t Div) {
	int i;
	//power up HSE/SystemOSC
	LPC_SYSCON->PDRUNCFG     &= ~(1 << 5);          /* 0->Power-up System Osc, 1->power down      */
	LPC_SYSCON->SYSOSCCTRL    = 0x00;
	for (i = 0; i < 200; i++) __NOP();

	//configure PLL
	LPC_SYSCON->SYSPLLCLKSEL  = 0x01;				//select pll input clock, 0x01->system osc/hse, 0x00->hsi/irc
	LPC_SYSCON->SYSPLLCTRL    = (Mul & 0x01f) | (Div & (0x03 << 5));
	LPC_SYSCON->PDRUNCFG     &= ~(1 << 7);          /* 0->Power-up SYSPLL          */
	while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	      /* Wait Until PLL Locked    */

	//configure main clock source
	LPC_SYSCON->MAINCLKSEL    = 0x03;     			/* Select PLL Clock Output:0x00->HSI/IRC, 0x01->HSI/HSE, 0x02->WDT, 0x03->PLL  */
	//update unlock sequence
	LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
	LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
	LPC_SYSCON->MAINCLKUEN    = 0x01;
	while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */

}
//reset the mcu
void mcu_init(void) {
	//big delays to avoid clock set up errors
	delay_ms(1000);

	//set up the clock

	/* Enable AHB clock to the GPIO domain. */
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<31);		//31:enable gpio0
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<30);		//30:enable gpio1
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<29);		//29:enable gpio2

	//update systemcoreclock
	SystemCoreClockUpdate();
}

