#ifndef UART2_HW_H_
#define UART2_HW_H_

#include "gpio.h"				//we use gpio

//#define Mhz					000000ul	//suffix for Mhz
#define F_UART				(F_CPU)	//8Mhz		//crystal frequency
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

//for compatability
#define uart2_put(ch)		uart2_putch(ch)
#define uart2_get()		uart2_getch()


//initiate the hardware usart
void uart2_init(unsigned long baud_rate);

void uart2_putch(char ch);

void uart2_puts(char *str);

/*

Writes a line of text to USART and goes to new line
The new line is Windows style CR/LF pair.

This will work on Hyper Terminal Only NOT on Linux

*/

void uart2_putline(char *ln);

//read a char from usart
unsigned char uart2_getch(void);

//test if data rx is available
uint16_t uart2_available(void);
//test if uart tx is busy
uint16_t uart2_busy(void);


#endif //usart_hw_h_
