/*	demo to use uart hardware
 */

//#include <iccioavr.h>
//#include <macros.h>
//#include "gpio.h"
//#include "delay.h"
#include "uart.h"

//baud rate definitions
#define USART_BR_300		300ul
#define USART_BR_1200		1200ul
#define USART_BR_2400		2400ul
#define USART_BR_4800		4800ul
#define USART_BR_9600		9600ul
#define USART_BR_14400		14400ul
#define USART_BR_19200		19200ul
#define USART_BR_38400		38400ul
#define USART_BR_57600		57600ul

//for compatability
#define UxBRR				UBRR0
#define UxCSRA				UCSR0A
#define UxCSRB				UCSR0B
#define UxCSRC				UCSR0C
#define UxDR				UDR0

//uart for 8-bit, 1stop bit, no parity transmission
void uart_init(unsigned long baud) {

	//check to see if if rx/tx pins are defined
#if defined(UxTX)								//TX as output
	//IO_OUT(UxDDR, UxTX);
#endif

#if defined(UxRX)								//RX as input
	//IO_IN(UxDDR, UxRX);
#endif

	/* enable receiver and transmitter */
	UxCSRA=		(1<<U2X0);						//double speed
	UxCSRB=		(0<<RXCIE0) |					//0->disable RX complete interrupt
				(0<<TXCIE0) |					//0->disable TX complete interrupt
				(0<<UDRIE0) |					//0->disable usart data register empty interrupt
#if defined(UxRX)
				(1<<RXEN0) |					//1->enable receiver
#else
				(0<<RXEN0) |					//1->enable receiver
#endif
#if defined(UxTX)
				(1<<TXEN0) |					//1->enable transmitter
#else
				(0<<TXEN0) |					//1->enable transmitter
#endif
				(0<<UCSZ02) |					//char size 0b011->8bit
				(0<<RXB80) |					//receive data bit 8 / 9th data bit received
				(0<<TXB80);						//transmitter data bit 8 / 9th data bit to be sent

	/* set frame format: 8 data, 1 stop bit */
	UxCSRC=		(0<<UMSEL01) | (0<<UMSEL00) |	//00-> asynchronous usart
												//01-> synchronous usart
												//10-> reserved
												//11-> master spi
				(0<<UPM01) | (0<<UPM00) |		//parity check 00-> disabled
												//01-> reserved
												//10-> enabled, even parity
												//11-> enabled, odd parity
				(0<<USBS0) |					//stop bit select. 0->1 bit, 1->2bit
				(1<<UCSZ01) | (1<<UCSZ00) |		//char size.
												//000-> 5-bit
												//001-> 6-bit
												//010-> 7-bit
												//011-> 8-bit
												//100-> reserved
												//101-> reserved
												//110-> reserved
												//111-> 9-bit
				(1<<UCPOL0);					//clock polarity. 0-> rising xck edge. 1-> falling xck edge
	/* baud rate generator */
	//UBRR0H=(unsigned char) (baud >> 8);
	//UBRR0L=(unsigned char) baud;
	UxBRR=F_UART / ((UxCSRA & (1<<U2X0))?8:16) / baud - 1;			//generate baud rate register

	//DDRD |= (1<<5);							//xck as output

}

void uart_putch(char data_t) {			//send data
	while (!(UxCSRA & (1<<UDRE0)));			//wait for transmission to end
	UxDR=data_t;									//load up the buffer
	//return 0;									//transmission complete
}

void uart_puts(char * str) {			//put a string
	while (*str)								//if the string isn't empty
		uart_putch(*str++);						//send the char and advance the pointer
}

void uart_putline(char * str) {
	uart_puts(str);
	uart_puts("\r\n");
}

char uart_getch(void) {
	//while (!(UxCSRA & (1<<RXC0))) continue;		//wait for the receive to finish
	return UxDR;									//return the context of uart register
}

//test if uart receiver has data
uint8_t uart_available(void) {
	return UxCSRA & (1<<RXC0);				//RXC0 set if data is available
}

//test if transmitter is busy
uint8_t uart_busy(void) {
	return !(UxCSRA & (1<<UDRE0));			//UDRE0 set if tx buffer is empty
}
