#ifndef UART_C_
#define UART_C_

#include "gpio.h"									//use gpio

//hardware configuration
//end hardware configuration

//global defines
#define F_UART				(SystemCoreClock)		//F_UART = F_CPU

//global variables

//initialize uart
//high speed (HSE set)
//default: tx enabled(CTL bit 8 set), rx disabled -> CTL bit 9 cleared
void uart0_init(uint32_t baudrate);
char uart0_busy(void);								//returns 1=tx is busy
char uart0_available(void);							//1=rx data available
void uart0_put(char ch);							//send a char. need to check if uart is busy first
void uart0_puts(char *str);							//send a string
char uart0_get(void);								//receive a char. need to check if data is available

void uart1_init(uint32_t baudrate);
char uart1_busy(void);								//returns 1=tx is busy
char uart1_available(void);							//1=rx data available
void uart1_put(char ch);							//send a char. need to check if uart is busy first
void uart1_puts(char *str);							//send a string
char uart1_get(void);								//receive a char. need to check if data is available


#endif /* UART_C_ */
