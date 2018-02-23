#ifndef _UART0_H
#define _UART0_H

//using tmr0 as a software uart generator
//transmission is interrupt driven
//only TX is implemented

#include "gpio.h"                           //we use gpio functions

//hardware configuration
#define UART0_PORT		PORTB
#define UART0_DDR		DDRB
#define UART0_TX		(1<<0)
//end hardware configuration

//global defines
#define UARTBPS_600		600					//uart bps
#define UARTBPS_1200	1200				//uart bps
#define UARTBPS_2400	2400				//uart bps
#define UARTBPS_4800	4800				//uart bps
#define UARTBPS_9600	9600				//uart bps -> max at 1MIPS
#define UARTBPS_19200	19200				//uart bps -> max at 2MIPS
#define UARTBPS_38400	38400				//uart bps -> max at 4MIPS/16MHz crystal

//global variables

//global isr

//uart0 isr
void uart0_isr(void);

//initialize the uart/tmr0
void uart0_init(uint32_t bps);

//send a uart char
//8 data bit, 1 start bit, 1 stop bit, lsb first
void uart0_put(char ch);

//send a string - non blocking
void uart0_puts(char *str);

//return 1 if uart is busy
char uart0_busy(void);

#endif
