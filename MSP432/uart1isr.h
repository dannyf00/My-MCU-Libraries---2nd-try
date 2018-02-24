//uart0..3 on eUSCI_A0..3 for MSP430

#ifndef UART1ISR_H_
#define UART1ISR_H_

#include "gpio.h"								//we use gpio

//hardware configuration
//initialize uart pins
//comment out if not used
//TX/P2.0, RX/P2.1
#define UART1_TX()			do {IO_OUT(PORT2, 1<<0); IO_AF2(PORT2, 1<<0);} while (0)
//#define UART1_RX()			do {IO_IN (PORT2, 1<<1); IO_AF2(PORT2, 1<<1);} while (0)

#define F_UART				(F_CPU)				//F_UART(F_BRCLK = F_CPU)
//end hardware configuration

//EUSCI_A configuration


//uart0/eUSCI_A0: TX/p2.0 and RX/p2.1
void uart1_init(uint32_t bps);
char uart1_get(void);
void uart1_put(char ch);
void uart1_puts(char *str);
char uart1_busy(void);
char uart1_available(void);

#endif /* UART_H_ */
