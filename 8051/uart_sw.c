#include <regx51.h>
#include "gpio.h"
#include "uart_sw.h"

unsigned short _uart_bps=UART_9600BPS;				//uart_bps

void uart_init(unsigned short bps) {
	IO_SET(UART_PORT, UART_TX);					//set tx
	IO_OUT(UART_PORT, UART_TX);					//tx as output

	IO_IN(UART_DDR, UART_RX);					//rx as input

	_uart_bps=bps;								//set _uart_bps

	//set up tmr0
	//TR0 = 0;									//turn off tmr0
	//TMOD = (TMOD & 0xf0) | 0x01;				//tmr0: 16-bit timer, mode 01
	//ET0 = 1;									//tmr0 interrupt on
}

//send a bit over tx
void uart_send_bit(unsigned char bit_t) {		//send a bit
	//set up tmr0 counters
	TF0 = 0;									//clear the flag
	TH0 += MSB(-_uart_bps);
	TL0 += LSB(-_uart_bps);
	TR0 = 1;									//turn on tmr0
	if (bit_t) IO_SET(UART_PORT, UART_TX);		//clear tx to send the start bit
	else IO_CLR(UART_PORT, UART_TX);			//otherwise, send 0
	//TR0 = 1;									//start the timer
	while (!TF0) continue;						//wait for the tmr to overflow
	//TR0 = 0;									//turn off tmr0
	//up date tmr0 counters - retain timing errors
}

//1 start bit (low)
//8 data bit
//1 stop bit (high)
void uart_putch(unsigned char ch) {
	unsigned char mask = 0x01;

	//set up tmr0 counters
	TR0=0;										//turn on tmr0
	TMOD = (TMOD & 0xf0) | 0x01;				//tmr0: 16-bit timer, mode 01
	TH0 = 0;									//set up tmr0 counters
	TL0 = 0;
	//ET0 = 1;									//tmr0 interrupt on
	//TR0 = 1;									//start tmr0

	//send the start bit (0)
	uart_send_bit(0);							//send the start bit

	//send the ch (8-bit)
	do {
		uart_send_bit(ch & mask);
		mask = mask << 1;
	} while (mask);

	//send one stop bit
	uart_send_bit(1);
	TR0=0;										//turn off tmr0
}

void uart_putstr(unsigned char *str) {
	while (*str) uart_putch(*str++);			//send a ch until it is empty
}
