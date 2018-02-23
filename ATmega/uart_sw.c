//#include <regx51.h>							//we use c51
#include <avr/io.h>								//we use gcc avr
#include "gpio.h"
#include "uart_sw.h"

//unsigned short _uart_bps=UART_9600BPS;				//uart_bps

void uart_init(unsigned short bps) {
	IO_SET(UART_PORT, UART_TX);					//set tx
	IO_OUT(UART_DDR, UART_TX);					//tx as output

	IO_IN(UART_DDR, UART_RX);					//rx as input

	//_uart_bps=bps;								//set _uart_bps

	//set up tmr1
	TCCR1B = 0;									//turn off tmr1
	TCCR1A =	(0<<COM1A1) | (0<<COM1A0) |		//ch a operation: normal
				(0<<COM1B1) | (0<<COM1B0) |		//ch b operation: normal
				(0<<COM1C1) | (0<<COM1C0) |		//ch c operation: normal
				(0<<WGM11) | (0<<WGM10)			//wgm13..0: 0b0100 -> CTC, top in OCR1A
				;
	TCCR1B =	(0<<ICNC1) |					//input capture noise cancelling: off
				(0<<ICES1) |					//input edge selection: rising edge (default)
				(0<<WGM13) | (1<<WGM12) |		//wgm13..0: 0b0100 -> CTC, top in OCR1A
				(0<<CS12) | (0<<CS11) | (0<<CS10)	//cs2..0=0b000 -> tmr1 remains off
				;
	TCCR1C =	(0<<FOC1A) |					//force output compare to ch a: disabled
				(0<<FOC1B) |					//force output compare to ch b: disabled
				(0<<FOC1C)						//force output compare to ch c: disabled
				;
	TIMSK1 =	(0<<ICIE1) |					//input capture interrupt: disabled
				(0<<OCIE1C) |					//output compare interrupt ch c: disabled
				(0<<OCIE1B) |					//output compare interrupt ch b: disabled
				(0<<OCIE1A) |					//output compare interrupt ch a: disabled
				(0<<TOIE1) 						//tmr1 overflow interrupt: disabled
				;
	//TCNT1 = 0;									//clear tmr1 counter
	OCR1A = bps;								//set up the top
}

//send a bit over tx
void uart_send_bit(unsigned char bit_t) {		//send a bit
	//set up tmr0 counters
	//TCCR1B &=~((1<<CS12) | (1<<CS11) | (1<<CS10));		//turn off tmr1
	//TCNT1 = 0;									//reset tmr1 counter
	TIFR1 |= (1<<OCF1A);						//write 1 to clear ocf1a
	//TCCR1B |= (0<<CS12) | (0<<CS11) | (1<<CS10);	//turn on tmr1
	if (bit_t) IO_SET(UART_PORT, UART_TX);		//clear tx to send the start bit
	else IO_CLR(UART_PORT, UART_TX);			//otherwise, send 0
	//TR0 = 1;									//start the timer
	while (!(TIFR1 & (1<<OCF1A))) continue;						//wait for the tmr to overflow
	//TR0 = 0;									//turn off tmr0
	//up date tmr0 counters - retain timing errors
}

//1 start bit (low)
//8 data bit
//1 stop bit (high)
void uart_putch(unsigned char ch) {
	unsigned char mask = 0x01;

	//turn on tmr1
	TCNT1 = 0;									//reset the tmr1 counter
	TCCR1B |= (0<<CS12) | (0<<CS11) | (1<<CS10);		//turn off tmr1

	//send the start bit (0)
	uart_send_bit(0);							//send the start bit

	//send the ch (8-bit)
	do {
		uart_send_bit(ch & mask);
		mask = mask << 1;
	} while (mask);

	//send one stop bit
	uart_send_bit(1);
	TCCR1B &=~((1<<CS12) | (1<<CS11) | (1<<CS10));		//turn off tmr1
}

void uart_putstr(unsigned char *str) {
	while (*str) uart_putch(*str++);			//send a ch until it is empty
}
