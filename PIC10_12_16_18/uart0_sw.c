#include "uart0_sw.h"						//we use software uart, timer2 as timebase, tx only

//hardware configuration
#define UART_PORT			PORTA
#define UART_DDR			TRISA
#define UART_TX				(1<<0)			//TX/DO on PA.1
//end hardware configuration

//global defines
#define F_UART				(F_CPU)		//uart clock speed
#define RBIT(ch)			((r4_lut[(ch) & 0x0f] << 4) | r4_lut[ch >> 4])	//consider the use of RBIT() macro for Cortex-M4 chips

//global variables
//look-up table for 4 bit reversal, in place
static unsigned char r4_lut[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };
volatile char _UxTX_BUSY = 0;				//uart status, 1->busy, 0->not busy
volatile char _UxTXDR;						//transmission buffer -> data
volatile char _UxTXSR;						//transmission shift register -> data
volatile char _UxTXphase;					//send the first char: 1->start bit sent, 2->data byte sent, 0->stop bit(s) sent / not busy
volatile uint8_t _UxTXmask;					//needs to be unsigned or right shift is undefined
static uint8_t _UxTXPR=0xff;						//uart0 period

#ifndef TMR0IF
#define TMR0IF				T0IF
#endif
//software uart / timer2 overflow isr
void tmr0_isr(void) {
	//clear the flag - done automatically
	//clear TIFR/TIMSK
	TMR0IF = 0;									//1->clera the flag
	TMR0-=_UxTXPR;								//load the offset
	switch (_UxTXphase) {
		case 1: 								//first half of the char has been sent, now send the 2nd transmission/data byte
			//TCNT0 = 0;							//reset the counter / prescaler
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
			//TCNT0 = 0;						//reset the counter / prescaler
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
			//USICR = 0;						//disable usi
			//USISR = (1<<USIOIF);
			TMR0IE = 0;							//1->enable the interrupt, 0->disable the interrupt
			_UxTX_BUSY = 0;						//no long buy
			//IO_SET(UART_PORT, UART_TX);		//set the TX pin - optional
			break;
	}
}
//rest uart timer0 as clock
//1-start bit, 1-stop bit, 8-data
void uart0_init(uint32_t bps) {
	_UxTX_BUSY = 0;							//0->not busy, 1->busy
	_UxTXphase = 0;							//1->sending the first byte, 0->sending the 2nd byte

	//configure uart pins
	IO_SET(UART_PORT, UART_TX);				//TX idles high
	IO_OUT(UART_DDR, UART_TX);				//as output

	//configure timer2: top at PR2
	//stop timer2
	//TMR0ON = 0;								//0->stop the timer, !0->start the timer
	TMR0 = 0;								//reset the counter

	//clear TIFR/TIMSK
	TMR0IF = 0;								//1->clera the flag
	TMR0IE = 0;								//1->enable the interrupt, 0->disable the interrupt
	//PEIE = 1;								//enable peripehral interrupt
	T0CS = 0;								//0->count on internal clock, 1->external clock
	
	//configure prescaler and start time0
	//prescaler formed by prescaler (1..256)
	if (F_UART <= bps * 256 * 1) {
		//run at 1:1 prescaler
		_UxTXPR/*PR2*/ = F_UART / bps / 1 - 1;			//set the top
		PSA=1;									//T1CONbits.T1CKPS = 0;				//0b00->prescaler = 1:1
		//T2CONbits.TOUTPS = 1-1;				//postscaler = 1:1
	} else if (F_UART <= bps * 256 * 2) {
		//run at 2:1 prescaler
		_UxTXPR/*PR2*/ = F_UART / bps / 2 - 1;		//set the top
		PSA=0, PS2=0, PS1=0, PS0=0;			//PS2..0=0b000->2:1prescaler
		//T2CONbits.T2CKPS = 1;				//0b01->prescaler = 4:1
		//T2CONbits.TOUTPS = 2 - 1;			//postscaler = 2:1
	} else if (F_UART <= bps * 256 * 4) {
		//run timer0 at 4:1 prescaler
		_UxTXPR/*PR2*/ = F_UART / bps / 4 - 1;		//set the top
		PSA=0, PS2=0, PS1=0, PS0=1;			//PS2..0=0b001->4:1prescaler
		//T2CONbits.T2CKPS = 2;				//0b10->prescaler = 16:1
		//T2CONbits.TOUTPS = 4-1;				//postscaler = 4:1
	} else if (F_UART <= bps * 256 * 8) {
		//run timer0 at 8:1 prescaler
		_UxTXPR/*PR2*/ = F_UART / bps / 8 - 1;		//set the top
		PSA=0, PS2=0, PS1=1, PS0=0;			//PS2..0=0b010->8:1prescaler
		//T2CONbits.T2CKPS = 2;				//0b10->prescaler = 16:1
		//T2CONbits.TOUTPS = 4-1;				//postscaler = 4:1
	} else if (F_UART <= bps * 256 * 16) {
		//run timer0 at 16:1 prescaler
		_UxTXPR/*PR2*/ = F_UART / bps / 16 - 1;		//set the top
		PSA=0, PS2=0, PS1=1, PS0=1;			//PS2..0=0b011->16:1prescaler
		//T2CONbits.T2CKPS = 2;				//0b10->prescaler = 16:1
		//T2CONbits.TOUTPS = 4-1;				//postscaler = 4:1
	} else if (F_UART <= bps * 256 * 32) {
		//run timer0 at 32:1 prescaler
		_UxTXPR/*PR2*/ = F_UART / bps / 32 - 1;		//set the top
		PSA=0, PS2=1, PS1=0, PS0=0;			//PS2..0=0b100->32:1prescaler
		//T2CONbits.T2CKPS = 2;				//0b10->prescaler = 16:1
		//T2CONbits.TOUTPS = 4-1;				//postscaler = 4:1
	} else if (F_UART <= bps * 256 * 64) {
		//run timer0 at 64:1 prescaler
		_UxTXPR/*PR2*/ = F_UART / bps / 64 - 1;		//set the top
		PSA=0, PS2=1, PS1=0, PS0=1;			//PS2..0=0b101->64:1prescaler
		//T2CONbits.T2CKPS = 2;				//0b10->prescaler = 16:1
		//T2CONbits.TOUTPS = 4-1;				//postscaler = 4:1
	} else if (F_UART <= bps * 256 * 128) {
		//run timer0 at 4:1 prescaler
		_UxTXPR/*PR2*/ = F_UART / bps / 128 - 1;		//set the top
		PSA=0, PS2=1, PS1=1, PS0=0;			//PS2..0=0b110->128:1prescaler
		//T2CONbits.T2CKPS = 2;				//0b10->prescaler = 16:1
		//T2CONbits.TOUTPS = 4-1;				//postscaler = 4:1
	} else {		
		//run timer2 at 256:1 prescaler
		_UxTXPR/*PR2*/ = F_UART / bps / 256 - 1;		//set the top
		PSA=0, PS2=1, PS1=1, PS0=1;			//PS2..0=0b111->256:1prescaler
		//T2CONbits.T2CKPS = 2;				//0b10->prescaler = 16:1
		//T2CONbits.TOUTPS = 16-1;			//postscaler = 16:1
	}	
	//TMR0ON = 1;								//enable TMR2
	//timer2 running now
	//overflow interrupt remains disabled
}


//send a char
void uart0_put(char ch) {
	while (uart0_busy()) continue;			//wait for the uart to be ready
	_UxTX_BUSY = 1;							//uart is busy
	//IO_SET(UART_PORT, UART_TX);			//TX high
	//reverse the input byte's order: LSB..MSB
	_UxTXphase = 1;							//to send the 1st byte
	//inverse the order of data byte
	_UxTXDR = RBIT(ch);						//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
	//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
	_UxTXmask = 1<<7;						//transmission mask
	TMR0 = -_UxTXPR;							//reset the timer/prescaler
	//clear TIFR/TIMSK
	TMR0IF = 0;								//1->clera the flag
	TMR0IE = 1;								//1->enable the interrupt, 0->disable the interrupt
	IO_CLR(UART_PORT, UART_TX);				//send the start bit -> low
}

//send a string
void uart0_puts(char *str) {
	while (*str) uart0_put(*str++);
}

//test for busy SIGNAL
char uart0_busy(void) {
	return _UxTX_BUSY;
}
