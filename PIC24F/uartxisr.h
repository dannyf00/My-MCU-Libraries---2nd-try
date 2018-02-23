#ifndef USARTXISR_H_INCLUDED
#define USARTXISR_H_INCLUDED

//software uart
//hardware configuration
#define UART_PORT       LATB
#define UART_DDR        TRISB
#define UART_TX         (1<<8)

//output routines - potentially to allow OD output
#define UART_SET(tx)    IO_SET(UART_PORT, tx)   //set tx pin
#define UART_CLR(tx)    IO_CLR(UART_PORT, tx)   //clear tx pin

//timer used to generate the baud rate
#include "tmr3.h"                       //we use timer
#define tmrx_init       tmr3_init
#define tmrx_act        tmr3_act
#define TxIF            _T3IF       //clear timer flag
#define TxIE            _T3IE       //set tmr interrupt
//end hardware configuration

//global defines
//uartx protocol
//1 start bit
//8 data bits
//1 stop bit
//lsb first
#define UART_SR(dat)		(0x0200 | ((dat) << 1) | 0x0000)	//form the uart shift register. 1 start bit (low), 8 data bits, 1 stop bit (high), lsb first

//global defines
//define baud rates
#define UART_BR_300			300ul		//baudrate=300 - it overflows under 24Mhz F_CPU
#define UART_BR_600			600ul		//baudrate=600
#define UART_BR_1200		1200ul		//baudrate=1200
#define UART_BR_2400		2400ul		//baudrate=2400
#define UART_BR_4800		4800ul		//baudrate=4800
#define UART_BR_9600		9600ul		//baudrate=9600
#define UART_BR_19200		19200ul		//baudrate=19200
#define UART_BR_38400		38400ul		//baudrate=38400
#define UART_BR_57600		57600ul		//baudrate=57600 - upper limit for 24Mhz F_CPU
#define UART_BR_115200		115200ul	//baudrate=115200


//global variables

//uartx handler
void uartx_isr(void);

//reset the module
void uartx_init(unsigned long baud);

//set a string
void uartx_puts(unsigned char * str);

//return status
unsigned char uartx_busy(void);

#endif // USARTXISR_H_INCLUDED
