#ifndef _UART1_H
#define _UART1_H

#include "gpio.h"						//we use gpio

//hardware configuration
//comment out if not used
//U1TX=PD3, U1RX=PD2
#define UART1_TX()			GPIOD->AFSEL |= (1<<3) 				//PD3/U1TX on alternate function
#define UART1_RX()			GPIOD->AFSEL |= (1<<2) 				//PD2/U1RX on alternate function
//end hardware configuration

//global defines
#define F_UART				F_CPU

//define baud rates
#define UART_BR_300			300ul		//baud rate=300
#define UART_BR_600			600ul		//baud rate=600
#define UART_BR_1200		1200ul		//baud rate=1200
#define UART_BR_2400		2400ul		//baud rate=2400
#define UART_BR_4800		4800ul		//baud rate=4800
#define UART_BR_9600		9600ul		//baud rate=9600
#define UART_BR_19200		19200ul		//baud rate=19200
#define UART_BR_38400		38400ul		//baud rate=38400
#define UART_BR_57600		57600ul		//baud rate=57600
#define UART_BR_115200		115200ul	//baud rate=115200

//global variables

//reset the usart module
void uart1_init(uint32_t uart_bps);

//send a char
void uart1_put(char ch);

//send a string
void uart1_puts(char * str);

//read usartx status
//1 if usartx is busy
//0 if usartx is available for new transmission
char uart1_busy(void);

//check for rx availability
char uart1_available(void);

#endif /* UART0ISR_H_ */
