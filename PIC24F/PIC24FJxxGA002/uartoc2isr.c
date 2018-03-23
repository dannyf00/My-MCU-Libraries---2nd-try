#include "uartoc2isr.h"							//we use softwar uart 1 on Output Compare

//hardware configuration
#define UART_PORT			LATB
#define UART_DDR			TRISB
#define UART_TX				(1<<1)				//uart_tx on pb.1

#define UART_TMR			3					//use TMR2 or TMR3 as time base
//use OC1..5
#define OCxMD				PMD2bits.OC2MD
#define OCxCON				OC2CON
#define OCxR				OC2R
#define OCxIF				IFS0bits.OC2IF		//interrupt flag
#define OCxIE				IEC0bits.OC2IE		//interrupt enable
//end hardware configuration

//global defines
#define F_UART				F_CPU				//UART clock sourced from system clock

#if UART_TMR == 2								//decide on time base
#define TxMD				PMD1bits.T2MD
#define TxCON				T2CON
#define TMRx				TMR2
#define PRx					PR2
#else
#define TxMD				PMD1bits.T3MD
#define TxCON				T3CON
#define TMRx				TMR3
#define PRx					PR3
#endif

//global variables
//look-up table for 4 bit reversal, in place
static volatile char _UxTX_BUSY = 0;				//uart status, 1->busy, 0->not busy
static volatile char _UxTXDR;						//transmission buffer -> data
static volatile char _UxTXSR;						//transmission shift register -> data
static volatile char _UxTXphase;					//send the first char: 1->start bit sent, 2->data byte sent, 0->stop bit(s) sent / not busy
static volatile uint8_t _UxTXmask;					//needs to be unsigned or right shift is undefined
static uint16_t _UxTXPR=0xffff;						//uart0 period
static volatile char *_UxTX_ptr;					//pointer to UxTX strings

//Output compare ISR
void _ISR _OC2Interrupt(void) {
	char ch;

	OCxIF=0;							//clear tmr1 interrupt flag
	OCxR += _UxTXPR;					//increment to the next match point
	switch (_UxTXphase) {
		case 1: 								//first half of the char has been sent, now send the 2nd transmission/data byte
			//TCNT0 = 0;							//reset the counter / prescaler
			//USIDR = _UxTXDR;					//load the data byte
			if (_UxTXDR & _UxTXmask) IO_SET(UART_PORT, UART_TX); else IO_CLR(UART_PORT, UART_TX);
			_UxTXmask = _UxTXmask << 1;			//advance to the next bit
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-8);		//reload usisr: 1 data bit + 1 stop bit, 8->8 data bites to send
			if (_UxTXmask == 0) {				//current bit has been transmitted
				_UxTXphase = 2;					//2nd byte to be sent
				_UxTXDR = 0xff;					//stop bits
				_UxTXmask = 1<<(8-1);			//1 stop bit. 1<<(2-1) for 2 stop bits
			}
			break;
		case 2:									//send the stop bit(s)
			//TCNT0 = 0;						//reset the counter / prescaler
			if (_UxTXDR & _UxTXmask) IO_SET(UART_PORT, UART_TX); else IO_CLR(UART_PORT, UART_TX);
			_UxTXmask = _UxTXmask << 1;			//advance to the next bit
			//USIDR = 0xff;						//load the stop bits - bits of 1
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-1);		//reload usisr: 1->1 stop bit, 2->2 stop bits, ..., 8->8 stop bits
			if (_UxTXmask == 0) {
				_UxTXphase = 0;					//2nd byte to be sent
			}
			break;
		case 0:									//end the transmission
			if (*_UxTX_ptr == 0) {				//end of the string has been reached
				//USICR = 0;					//disable usi
				//USISR = (1<<USIOIF);
				OCxIE = 0;						//1->enable the interrupt, 0->disable the interrupt
				_UxTX_BUSY = 0;					//no long buy
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
				_UxTXDR = ch;						//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
				//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
				_UxTXmask = 1<<0;						//transmission mask
				OCxR = TMRx + _UxTXPR;							//reset the timer/prescaler
				//clear TIFR/TIMSK
				//TIFR |= (1<<OCF0A);					//1->clera the flag
				//TIMSK|= (1<<OCIE0A);					//1->enable the interrupt, 0->disable the interrupt
				IO_CLR(UART_PORT, UART_TX);				//send the start bit -> low
			}
			break;
	}
}

//initialize software uart / CCP
//only TX is implemented
//time base TMRx, use output compare ch 1
void uartoc2_init(uint32_t bps) {
	_UxTX_BUSY = 0;							//0->not busy, 1->busy
	_UxTXphase = 0;							//1->sending the first byte, 0->sending the 2nd byte

	//initialize the tx pins: idles high, as output
	IO_SET(UART_PORT, UART_TX); IO_OUT(UART_DDR, UART_TX);

	TxMD = 0;							//0->enable power to timer
	//configure time base
	//TxCON &=~(1<<15);					//0->stop timer, 1->start timer
	TxCON = 	(0<<15) |				//0->stop timer, 1->start timer
				(0<<13) |				//0->continue operation in idle; 1->stop operation in idle
				(0<< 6) |				//0->not gated, 1->gated
				(0<< 4) |				//prescaler: 0->1x, 1->8x, 2->64x, 3->256x
				(0<< 3) |				//0->two 16-bit timer, 1->one 32-bit timer
				(0<< 1) |				//0->timer source = internal clock (FOSC/2), 1->external clock from TxCK pin (on rising edge)
				0x00;
	TMRx = 0;							//optional
	PRx = 0xffff;						//period at 0xffff

	//configure output compare channel
	OCxMD = 0;							//0->enable power, 1->disable power
	OCxCON = 	(0<<13) |				//0->output compare continue in idle; 1->output compare disabled in idle
				(0<< 4) |				//0->no pwm fault condition, 1->pwm fault condition occured
#if UART_TMR == 2
				(0<< 3) |				//0->use TIMER2 as time base, 1->use TIMER3 as time base
#else
				(1<<3) |				//0->use TIMER2 as time base, 1->use TIMER3 as time base
#endif
				(1<< 0) |				//0->OC disabled, 1..5: OC enabled, 6..7: PWM mode
				0x00;
	//set the prescaler / baud rate
	if (F_UART <= bps * 65536ul) {
		//running at 1x prescaler
		TxCON = (TxCON &~(3<<4)) | (0 << 4);	//set prescaler to 1:1
		_UxTXPR = F_UART / bps - 1;					//set period
	} else if (F_UART <= bps * 65536ul * 8) {
		//running at 8x prescaler
		TxCON = (TxCON &~(3<<4)) | (1 << 4);	//set prescaler to 1:1
		_UxTXPR = F_UART / bps / 8 - 1;				//set period
	} else if (F_UART <= bps * 65536ul * 64){
		//running at 64x prescaler
		TxCON = (TxCON &~(3<<4)) | (2 << 4);	//set prescaler to 1:1
		_UxTXPR = F_UART / bps / 64 - 1;				//set period
	} else {
		//running at 256x prescaler
		TxCON = (TxCON &~(3<<4)) | (3 << 4);	//set prescaler to 1:1
		_UxTXPR = F_UART / bps / 256 - 1;				//set period
	}

	//clear interrupt flag, disable interrupt
	OCxIF = 0;							//0->clear the flag
	OCxIE = 0;							//0->disable the interrupt, 1->enable the interrupt

	//start timer
	TxCON |= (1<<15);					//0->stop timer, 1->start timer
}

//send a char
void uartoc2_put(char ch) {
	static char _buffer[2]={0,0};			//serial transmission buffer
	_buffer[0]=ch; 							//first char
	uartoc2_puts(_buffer);						//send the buffer
}

//send a string
void uartoc2_puts(char *str) {
	char ch;
	while (uartoc2_busy()) continue;			//wait for the uart to be ready
	_UxTX_BUSY = 1;							//uart is busy
	//IO_SET(UART_PORT, UART_TX);			//TX high
	//reverse the input byte's order: LSB..MSB
	_UxTXphase = 1;							//to send the 1st byte
	//inverse the order of data byte
	_UxTX_ptr = str;						//save the string
	ch = *_UxTX_ptr++;						//save the char and advance the string pointer
	_UxTXDR = ch;						//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
	//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
	_UxTXmask = 1<<0;						//transmission mask
	OCxR = TMRx + _UxTXPR;							//reset the timer/prescaler
	//clear TIFR/TIMSK
	OCxIF = 0;								//1->clera the flag
	OCxIE = 1;								//1->enable the interrupt, 0->disable the interrupt
	IO_CLR(UART_PORT, UART_TX);				//send the start bit -> low
}

//test for busy SIGNAL
char uartoc2_busy(void) {
	return _UxTX_BUSY;
}
