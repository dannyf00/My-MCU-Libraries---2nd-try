//uart0..3 on eUSCI_A0..3 for MSP430

#ifndef UART0_H_
#define UART0_H_

#include "gpio.h"								//we use gpio
#include "delay.h"								//we use software delay - to deal with a bug

//hardware configuration
//initialize uart pins
//comment out if not used
//TX/P3.4, RX/P3.5
#define UART0_TX()			do {IO_OUT(P3DIR, 1<<4); P3SEL |= (1<<4); /*P3SEL2 &=~(1<<4);*/} while (0)
#define UART0_RX()			do {IO_IN (P3DIR, 1<<5); P3SEL |= (1<<5); /*P3SEL2 &=~(1<<5);*/} while (0)

#define F_UART				(F_CPU)				//F_UART(F_BRCLK = F_CPU)
//end hardware configuration

//EUSCI_A configuration


//uart0/eUSCI_A0: TX/p2.0 and RX/p2.1
void uart0_init(uint32_t bps);
char uart0_get(void);
void uart0_put(char ch);
void uart0_puts(char *str);
char uart0_busy(void);
char uart0_available(void);

#endif /* UART_H_ */
