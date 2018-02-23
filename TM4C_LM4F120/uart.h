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

void uart2_init(uint32_t baudrate);
char uart2_busy(void);								//returns 1=tx is busy
char uart2_available(void);							//1=rx data available
void uart2_put(char ch);							//send a char. need to check if uart is busy first
void uart2_puts(char *str);							//send a string
char uart2_get(void);								//receive a char. need to check if data is available

void uart3_init(uint32_t baudrate);
char uart3_busy(void);								//returns 1=tx is busy
char uart3_available(void);							//1=rx data available
void uart3_put(char ch);							//send a char. need to check if uart is busy first
void uart3_puts(char *str);							//send a string
char uart3_get(void);								//receive a char. need to check if data is available

void uart4_init(uint32_t baudrate);
char uart4_busy(void);								//returns 1=tx is busy
char uart4_available(void);							//1=rx data available
void uart4_put(char ch);							//send a char. need to check if uart is busy first
void uart4_puts(char *str);							//send a string
char uart4_get(void);								//receive a char. need to check if data is available

void uart5_init(uint32_t baudrate);
char uart5_busy(void);								//returns 1=tx is busy
char uart5_available(void);							//1=rx data available
void uart5_put(char ch);							//send a char. need to check if uart is busy first
void uart5_puts(char *str);							//send a string
char uart5_get(void);								//receive a char. need to check if data is available

void uart6_init(uint32_t baudrate);
char uart6_busy(void);								//returns 1=tx is busy
char uart6_available(void);							//1=rx data available
void uart6_put(char ch);							//send a char. need to check if uart is busy first
void uart6_puts(char *str);							//send a string
char uart6_get(void);								//receive a char. need to check if data is available

void uart7_init(uint32_t baudrate);
char uart7_busy(void);								//returns 1=tx is busy
char uart7_available(void);							//1=rx data available
void uart7_put(char ch);							//send a char. need to check if uart is busy first
void uart7_puts(char *str);							//send a string
char uart7_get(void);								//receive a char. need to check if data is available

#endif /* UART_C_ */
