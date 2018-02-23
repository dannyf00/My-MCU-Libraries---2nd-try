#ifndef _UARTISR_H
#define _UARTISR_H


#include "gpio.h"						//we use gpio

//hardware configuration
//#define UxPORT				PORTB
#define UxDDR				DDRB
#define UxTX				(1<<0)		//comment out if not used
#define UxRX				(1<<1)		//comment out if not used
//end hardware configuration


//baud rate definitions
#define F_UART				(F_CPU)		//8Mhz		//crystal frequency
#define UART_BR_300			300ul		//buadrate=300
#define UART_BR_600			600ul		//buadrate=600
#define UART_BR_1200		1200ul		//buadrate=1200
#define UART_BR_2400		2400ul		//buadrate=2400
#define UART_BR_4800		4800ul		//buadrate=4800
#define UART_BR_9600		9600ul		//buadrate=9600
#define UART_BR_19200		19200ul		//buadrate=19200
#define UART_BR_38400		38400ul		//buadrate=38400
#define UART_BR_57600		57600ul		//buadrate=57600
#define UART_BR_115200		115200ul	//buadrate=115200

#define uart_put(n)			uart_putch(n)
#define uart_get()			uart_getch()

void uart_init(unsigned long baud);

void uart_putch(char data_t);			//send data

void uart_puts(char * str);			//put a string

void uart_putline(char * str);			//put a string, with line return

char uart_getch(void);					//get a char from uart

//test if uart receiver has data
uint8_t uart_available(void);
//#define uart_available()	(UCSR0A & (1<<RXC0))

//test if transmitter is busy
uint8_t uart_busy(void);
//#define uart_busy()			(!(UCSR0A & (1<<UDRE0)))

#endif
