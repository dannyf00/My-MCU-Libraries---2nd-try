//uart0..3 on eUSCI_A0..3 for MSP430

#ifndef UART_H_
#define UART_H_

#include "gpio.h"								//we use gpio

//hardware configuration
//initialize uart pins
//comment out if not used
//TX/P2.0, RX/P2.1
#define UART0_TX()			do {IO_OUT(PORT2, 1<<0); IO_AF2(PORT2, 1<<0);} while (0)
#define UART0_RX()			//do {IO_IN (PORT2, 1<<1); IO_AF2(PORT2, 1<<1);} while (0)

//TX/P2.5, RX/P2.6
#define UART1_TX()			do {IO_OUT(PORT2, 1<<5); IO_AF2(PORT2, 1<<5);} while (0)
#define UART1_RX()			//do {IO_IN (PORT2, 1<<6); IO_AF2(PORT2, 1<<6);} while (0)

#define F_UART				(F_CPU)				//F_UART(F_BRCLK = F_CPU)
//end hardware configuration

//EUSCI_A configuration


//uart0/eUSCI_A0: TX/p2.0 and RX/p2.1
#define uart0_init(bps)		do {UART0_TX(); UART0_RX(); uart_init(UART0, bps);} while (0)
#define uart0_get()			uart_get(UART0)
#define uart0_put(ch)		uart_put(UART0, ch)
#define uart0_puts(str)		uart_puts(UART0, str)
#define uart0_busy()		uart_busy(UART0)
#define uart0_available()	uart_available(UART0)

//uart1/eUSCI_A1
//TX/p2.3, RX/p2.2
#define uart1_init(bps)		do {UART1_TX(); UART1_RX(); uart_init(UART1, bps);} while (0)
#define uart1_get()			uart_get(UART1)
#define uart1_put(ch)		uart_put(UART1, ch)
#define uart1_puts(str)		uart_puts(UART1, str)
#define uart1_busy()		uart_busy(UART1)
#define uart1_available()	uart_available(UART1)

//uart2/eUSCI_A2
//TX/p3.3, RX/p3.2
#define uart2_init(bps)		do {UART2_TX(); UART2_RX(); uart_init(UART2, bps);} while (0)
#define uart2_get()			uart_get(UART2)
#define uart2_put(ch)		uart_put(UART2, ch)
#define uart2_puts(str)		uart_puts(UART2, str)
#define uart2_busy()		uart_busy(UART2)
#define uart2_available()	uart_available(UART2)

//uart3/eUSCI_A3
//TX/p9.7, RX/p9.6
#define uart3_init(bps)		do {UART3_TX(); UART3_RX(); uart_init(UART3, bps);} while (0)
#define uart3_get()			uart_get(UART3)
#define uart3_put(ch)		uart_put(UART3, ch)
#define uart3_puts(str)		uart_puts(UART3, str)
#define uart3_busy()		uart_busy(UART3)
#define uart3_available()	uart_available(UART3)

//generic calls
//reset uart0/eusci_a0
void uart_init(UART_TypeDef *uscix, uint32_t bps);

//send a char
void uart_put(UART_TypeDef *uscix, char ch);

//send a string
void uart_puts(UART_TypeDef *uscix, char *str);

//receive a char
char uart_get(UART_TypeDef *uscix);

//test if uart tx is busy
char uart_busy(UART_TypeDef *uscix);

//test if uart rx is available
char uart_available(UART_TypeDef *uscix);

#endif /* UART_H_ */
