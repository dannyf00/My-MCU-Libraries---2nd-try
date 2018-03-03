#include "uart2aisr_sw.h"						//we use software uart / interrupt driven, timer0 as timebase, tx only

//hardware configuration
#define UART_PORT			PORTB
#define UART_DDR			DDRB
#define UART_TX				(1<<1)			//TX/DO on PB.1
//end hardware configuration

//global defines
#define F_UART				(F_CPU)		//uart clock speed
#define RBIT(ch)			((r4_lut[(ch) & 0x0f] << 4) | r4_lut[(ch) >> 4])	//consider the use of RBIT() for Cortex-M4 chips

//global variables
//look-up table for 4 bit reversal, in place
static unsigned char r4_lut[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };
static volatile char _UxTX_BUSY = 0;				//uart status, 1->busy, 0->not busy
static volatile char _UxTXDR;						//transmission buffer -> data
static volatile char _UxTXSR;						//transmission shift register -> data
static volatile char _UxTXphase;					//send the first char: 1->start bit sent, 2->data byte sent, 0->stop bit(s) sent / not busy
static volatile char *_UxTX_ptr;					//pointer to UxTX strings
static volatile uint8_t _UxTXmask;					//must be of unsigned type or right shift is undefined
static volatile char _UxTX_PR;						//period

//timer2 compa isr
ISR(TIMER2_COMPA_vect) {
	char ch;									//transmission char
	//clear the flag - done automatically
	//USISR |= (1<<USIOIF);						//1->clera the flag
	switch (_UxTXphase) {
		case 1: 								//first half of the char has been sent, now send the 2nd transmission/data byte
			OCR2A = TCNT2 + _UxTX_PR;			//reset the counter / prescaler
			//USIDR = _UxTXDR;					//load the data byte
			if (_UxTXDR & _UxTXmask) IO_SET(UART_PORT, UART_TX); else IO_CLR(UART_PORT, UART_TX);
			_UxTXmask = _UxTXmask >> 1;			//advance to the next bit
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-8);		//reload usisr: 1 data bit + 1 stop bit, 8->8 data bites to send
			if (_UxTXmask == 0) {				//current bit has been transmitted
				_UxTXphase = 2;					//2nd byte to be sent
				_UxTXDR = 0xff;					//stop bits
				_UxTXmask = 1<<(1-1);			//1 stop bit. 1<<(2-1) for 2 stop bits
			}
			break;
		case 2:									//send the stop bit(s)
			OCR2A = TCNT2 + _UxTX_PR;			//reset the counter / prescaler
			if (_UxTXDR & _UxTXmask) IO_SET(UART_PORT, UART_TX); else IO_CLR(UART_PORT, UART_TX);
			_UxTXmask = _UxTXmask >> 1;			//advance to the next bit
			//USIDR = 0xff;						//load the stop bits - bits of 1
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-1);		//reload usisr: 1->1 stop bit, 2->2 stop bits, ..., 8->8 stop bits
			if (_UxTXmask == 0) {
				_UxTXphase = 0;					//2nd byte to be sent
			}
			break;
		case 0:									//end the transmission
			if (*_UxTX_ptr == 0) {				//end of the string has been reached
				//USICR = 0;						//disable usi
				//USISR = (1<<USIOIF);
				TIMSK2&=~(1<<OCIE2A);				//1->enable the interrupt, 0->disable the interrupt
				_UxTX_BUSY = 0;						//no long buy
				//IO_SET(UART_PORT, UART_TX);		//set the TX pin - optional
			} else {
				//more char to sent
				//_UxTX_BUSY = 1;							//uart is busy
				//IO_SET(UART_PORT, UART_TX);			//TX high
				//reverse the input byte's order: LSB..MSB
				_UxTXphase = 1;							//to send the 1st byte
				//inverse the order of data byte
				//_UxTX_ptr = str;						//save the string
				ch = *_UxTX_ptr++;						//save the char and advance the string pointer
				_UxTXDR = RBIT(ch);						//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
				//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
				_UxTXmask = 1<<7;						//transmission mask
				OCR2A = TCNT2 + _UxTX_PR;				//reset the timer/prescaler
				//clear TIFR/TIMSK
				//TIFR |= (1<<OCF0A);					//1->clera the flag
				//TIMSK|= (1<<OCIE0A);					//1->enable the interrupt, 0->disable the interrupt
				IO_CLR(UART_PORT, UART_TX);				//send the start bit -> low
			}
			break;
	}
}
//rest uart using usi + timer0 as clock
//WGM02..0=0b000
//1-start bit, 1-stop bit, 8-data
void uart2a_init(uint32_t bps) {
	_UxTX_BUSY = 0;							//0->not busy, 1->busy
	_UxTXphase = 0;							//1->sending the first byte, 0->sending the 2nd byte

	//configure uart pins
	IO_SET(UART_PORT, UART_TX);				//TX idles high
	IO_OUT(UART_DDR, UART_TX);				//as output

	//configure timer2: CTC mode, top in OCR0A
	//stop timer2
	TCCR2B = (TCCR2B &~0x07) | (0x00 & 0x07);	//0->stop the timer, !0->start the timer
	TCCR2B &=~(1<<WGM22);					//WGM22=0
	TCCR2A &=~(1<<WGM21);					//WGM21=0
	TCCR2A &=~(1<<WGM20);					//WGM20=0
	//OCR2A/OCR2B pins disconnected
	TCCR2A &=~((1<<COM2A1) | (1<<COM2A0));	//COM2A1..0=0b00 -> OCR2A pin as gpio
	TCCR2A &=~((1<<COM2B1) | (1<<COM2B0));	//COM2B1..0=0b00 -> OCR2B pin as gpio
	//TCNT0 = 0;								//reset the counter

	//clear TIFR/TIMSK
	TIFR2 |= (1<<OCF2A);					//1->clera the flag
	TIMSK2&=~(1<<OCIE2A);					//1->enable the interrupt, 0->disable the interrupt

	//configure prescaler and start time0
	if (F_UART <= bps * 256 * 1) {
		//run at 1:1 prescaler
		_UxTX_PR = F_UART / bps / 1 - 1;				//set the top
		TCCR2B = (TCCR2B &~0x07) | (0x01 & 0x07);	//0->stop the timer, !0->start the timer. prescaler = 1:1
	} else if (F_UART <= bps * 256 * 8) {
		//run at 8:1 prescaler
		_UxTX_PR = F_UART / bps / 8 - 1;				//set the top
		TCCR2B = (TCCR2B &~0x07) | (0x02 & 0x07);	//0->stop the timer, !0->start the timer. prescaler = 8:1
	} else if (F_UART <= bps * 256 * 32) {
		//run at 32:1 prescaler
		_UxTX_PR = F_UART / bps / 32 - 1;				//set the top
		TCCR2B = (TCCR2B &~0x07) | (0x03 & 0x07);	//0->stop the timer, !0->start the timer. prescaler = 32:1
	} else if (F_UART <= bps * 256 * 64) {
		//run at 64:1 prescaler
		_UxTX_PR = F_UART / bps / 64 - 1;				//set the top
		TCCR2B = (TCCR2B &~0x07) | (0x04 & 0x07);	//0->stop the timer, !0->start the timer. prescaler = 64:1
	} else if (F_UART <= bps * 256 * 128) {
		//run at 128:1 prescaler
		_UxTX_PR = F_UART / bps / 128 - 1;				//set the top
		TCCR2B = (TCCR2B &~0x07) | (0x05 & 0x07);	//0->stop the timer, !0->start the timer. prescaler = 128:1
	} else if (F_UART <= bps * 256 * 256) {
		//run at 256:1 prescaler
		_UxTX_PR = F_UART / bps / 256 - 1;				//set the top
		TCCR2B = (TCCR2B &~0x07) | (0x06 & 0x07);	//0->stop the timer, !0->start the timer. prescaler = 256:1
	} else {
		//run at 1024:1 prescaler
		_UxTX_PR = F_UART / bps / 1024 - 1;				//set the top
		TCCR2B = (TCCR2B &~0x07) | (0x07 & 0x07);	//0->stop the timer, !0->start the timer. prescaler = 1024:1
	}
	//timer0 running now
	//compa interrupt remains disabled
}

//send a char
void uart2a_put(char ch) {
	static char _buffer[2]={0,0};			//serial transmission buffer
	_buffer[0]=ch; 							//first char
	uart2a_puts(_buffer);						//send the buffer
}

//send a string - no empty string, null-terminated
void uart2a_puts(char *str) {
	char ch;
	while (uart2a_busy()) continue;			//wait for the uart to be ready
	_UxTX_BUSY = 1;							//uart is busy
	//IO_SET(UART_PORT, UART_TX);			//TX high
	//reverse the input byte's order: LSB..MSB
	_UxTXphase = 1;							//to send the 1st byte
	//inverse the order of data byte
	_UxTX_ptr = str;						//save the string
	ch = *_UxTX_ptr++;						//save the char and advance the string pointer
	_UxTXDR = RBIT(ch);						//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
	//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
	_UxTXmask = 1<<7;						//transmission mask
	OCR2A = TCNT2 + _UxTX_PR;				//reset the timer/prescaler
	//clear TIFR/TIMSK
	TIFR2 |= (1<<OCF2A);						//1->clera the flag
	TIMSK2|= (1<<OCIE2A);					//1->enable the interrupt, 0->disable the interrupt
	IO_CLR(UART_PORT, UART_TX);				//send the start bit -> low
}

//test for busy SIGNAL
char uart2a_busy(void) {
	return _UxTX_BUSY;
}
