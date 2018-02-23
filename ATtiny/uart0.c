#include "uart0.h"							//we use uart0 software

//hardware configuration
//end hardware configuration

//global defines

//global variables
static volatile uint8_t _uart_busy=0;				//uart busy flag
volatile uint16_t _uart_txbuf;				//uart transmission buffer
volatile char *_uart_txstr;					//transmission string / pointer
volatile uint16_t _uart_mask;				//current bit being transmitted
volatile uint16_t _uart_pr;					//uart period, msb only
uint16_t _uart_pr0;

//global isr
//to be included in user code
//void interrupt isr(void) {
//	if (T0IF) uart0_isr();
//}

//uart0 isr
//void uart0_isr(void) {
ISR(TIMER0_OVF_vect) {
	//T0IF = 0;								//clear the flag
	if (_uart_pr) {							//current bit not yet done
		_uart_pr -= 0x100;					//decremeent uart_pr
	} else {								//current bit has been transmitted.
		_uart_mask = _uart_mask << 1;		//shift to the next bit
		if (_uart_mask != (1<<10)) {		//done with the stop bit / current char
			TCNT0 += -_uart_pr0;				//load the lsb
			_uart_pr = _uart_pr0 &~0x00ff;	//clear the lsb
			if (_uart_txbuf & _uart_mask) IO_SET(UART0_PORT, UART0_TX);
			else IO_CLR(UART0_PORT, UART0_TX);
		} else {							//transmitt the next bit
			//_uart_txbuf has been transmitted
			//check to see if we are at end of the string
			if (*_uart_txstr!=0) {			//more chars to transmit
				uart0_put(*_uart_txstr++);
			} else {						//end of the string has been reached
				TIMSK &=~(1<<TOIE0);		//T0IE = 0;					//turn off the isr
				_uart_busy=0;				//uart is no longer busy
			}
		}
	}
}


//initialize the uart/tmr0
void uart0_init(uint32_t bps) {
	//TX idles high
	IO_SET(UART0_PORT, UART0_TX);
	IO_OUT(UART0_DDR, UART0_TX);

	_uart_busy=0;							//0->uart is not busy

	//configure timer
	_uart_pr0 = F_CPU / bps;				//calculat the period
	TCCR0B = (TCCR0B &~0x07) | (0x01 & 0x07);	//0x01->1:1	//T0CS = 0;								//0->count internal clock
	//PSA = 1;								//1->prescaler assigned to wdt. tmr0 runs at 1:1
	//PS2=PS1=PS0=0;							//
	TIFR |= (1<<TOV0);						//set 1 to clear the flag	//T0IF = 0;								//clear the flag
	TIMSK&=~(1<<TOIE0);						//0->disable the interrupt	//T0IE = 0;								//disable the isr
	//TMR0 = -_uart_pr;						//load the lsb
	//_uart_pr &=~0xff;						//clear the lsb

}

//send a uart char
//8 data bit, 1 start bit, 1 stop bit, lsb first
void uart0_put(char ch) {
	//set / clear the tx pin
	if (_uart_txbuf & _uart_mask) IO_SET(UART0_PORT, UART0_TX);
	else IO_CLR(UART0_PORT, UART0_TX);

	//while (_uart_busy) continue;			//wait for uart to free up
	_uart_busy=1;							//uart is now busy
	_uart_txbuf = 	(0<<0) |				//start bit = 0
					(ch << 1) | 			//8 data bits, lsb first
					(1<<9);					//1 stop bit = 1
	_uart_mask = (1<<0);					//start transmission, lsb first

	//configure timer
	TCNT0 = -_uart_pr0;						//lowest the lsb
	_uart_pr =_uart_pr0 &~0x00ff;			//clear lsb
	TIFR |= (1<<TOV0);						//set 1 to clear the flag	//T0IF = 0;								//clear the flag
	TIMSK|= (1<<TOIE0);						//1->enable the interrupt	//T0IE = 0;								//disable the isr
	//the rest of the transmission done in the isr
}

//send a string - non blocking
void uart0_puts(char *str) {
	//while (*str) uart0_put(*str++);		//block transmission
	_uart_txstr=str;						//point to the string
	uart0_put(*_uart_txstr++);				//start the transmission
}

//return 1 if uart is busy
char uart0_busy(void) {
	return		(_uart_busy!=0);
}
