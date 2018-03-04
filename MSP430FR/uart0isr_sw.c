//#include <msp430.h> 					//we use ccs/msp430
//msp430g2 launchpad
//msp430g2553 or msp430g2452
//msp430f2418 - proteus
//msp430fr5969
#include "uart0isr_sw.h"				//we use software uart on TA0 CC channels

//hardware configuration
//end hardware configuration

//global defines
#define RBIT(ch)		((r4_lut[(ch) & 0x0f] << 4) | r4_lut[(ch) >> 4])	//consider the use of RBIT() for Cortex-M4 chips

//for easy portability
#define TAxCTL				TA0CTL			//timera control
#define TAxR				TA0R			//timer / counter
#define TAxIV				TA0IV			//interrupt flag
#define TAxEX0				TA0EX0			//expansion register

#define TAxCCTL0			TA0CCTL0		//timer0 compare control
#define TAxCCTL1			TA0CCTL1		//timer1 cmpare control
#define TAxCCTL2			TA0CCTL2		//timer2 compare control
#define TAxCCTL3			TA0CCTL3		//timer0 compare control
#define TAxCCTL4			TA0CCTL4		//timer1 cmpare control
#define TAxCCTL5			TA0CCTL5		//timer2 compare control
#define TAxCCTL6			TA0CCTL6		//timer0 compare control
#define TAxCCR0				TA0CCR0			//timer0 compare register
#define TAxCCR1				TA0CCR1			//timer1 compare register
#define TAxCCR2				TA0CCR2			//timer2 compare register
#define TAxCCR3				TA0CCR3			//timer0 compare register
#define TAxCCR4				TA0CCR4			//timer1 compare register
#define TAxCCR5				TA0CCR5			//timer2 compare register
#define TAxCCR6				TA0CCR6			//timer0 compare register
#define TAx_PS8x			(3<<6)			//prescaler mask
#define TAx_EX8x			(7<<0)			//extensio prescaler/divider

//global variables
//look-up table for 4 bit reversal, in place
static unsigned char r4_lut[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };
//for uart0
static volatile char    _U0TX_BUSY;					//uart status, 1->busy, 0->not busy
static volatile char    _U0TXDR;						//transmission buffer -> data
static volatile char    _U0TXSR;						//transmission shift register -> data
static volatile char    _U0TXphase;					//send the first char: 1->start bit sent, 2->data byte sent, 0->stop bit(s) sent / not busy
static volatile char   *_U0TX_ptr;					//pointer to UxTX strings
static volatile uint8_t _U0TXmask;					//must be of unsigned type or right shift is undefined
static volatile char    _U0TX_PR;						//period

//for uart1
static volatile char    _U1TX_BUSY;					//uart status, 1->busy, 0->not busy
static volatile char    _U1TXDR;						//transmission buffer -> data
static volatile char    _U1TXSR;						//transmission shift register -> data
static volatile char    _U1TXphase;					//send the first char: 1->start bit sent, 2->data byte sent, 0->stop bit(s) sent / not busy
static volatile char   *_U1TX_ptr;					//pointer to UxTX strings
static volatile uint8_t _U1TXmask;					//must be of unsigned type or right shift is undefined
static volatile char    _U1TX_PR;						//period

//for uart2
static volatile char    _U2TX_BUSY;					//uart status, 1->busy, 0->not busy
static volatile char    _U2TXDR;						//transmission buffer -> data
static volatile char    _U2TXSR;						//transmission shift register -> data
static volatile char    _U2TXphase;					//send the first char: 1->start bit sent, 2->data byte sent, 0->stop bit(s) sent / not busy
static volatile char   *_U2TX_ptr;					//pointer to UxTX strings
static volatile uint8_t _U2TXmask;					//must be of unsigned type or right shift is undefined
static volatile char    _U2TX_PR;						//period

//for uart3....
//add your own code

//prototypes for UARTx_ISR
void uart0_isr(void);
void uart1_isr(void);
void uart2_isr(void);
//add your own code

//timer isr
// Timer A0 interrupt service routine, ccr0
#pragma vector=TIMER0_A0_VECTOR
__interrupt void _ISRTimer0_A0 (void) {
	TAxCCR0 += _U0TX_PR;						//update TxCCR0 -> continuous mode
	TAxCCTL0&=~CCIFG;							//clear the flag
	uart0_isr();								//execute user tmr1 isr
}

// Timer A1 interrupt service routine, ccr1..4, ia
#pragma vector=TIMER0_A1_VECTOR
__interrupt void _ISRTimer0_A1 (void) {
	//TxCTL_bit.TAIFG=0;						//clear tmr1 interrupt flag
	///*_tmr1*/_isr_ptr1();					//execute user tmr1 isr
	switch (TAxIV) {
		case 0x02: 	TAxCCR1 += _U1TX_PR; TAxCCTL1 &=~CCIFG; uart1_isr(); break;		//0x02 -> ccr1
#if defined(TA0CCR2_)
		case 0x04: 	TAxCCR2 += _U2TX_PR; TAxCCTL2 &=~CCIFG; uart2_isr(); break;		//0x04 -> ccr2
#endif
#if defined(TA0CCR3_)
		case 0x06: 	TAxCCR3+=_ccr3_pr; TAxCCTL3 &=~CCIFG; _isrptr_ccr3(); break;		//0x04 -> ccr2
#endif
#if defined(TA0CCR4_)
		case 0x08: 	TAxCCR4+=_ccr4_pr; TAxCCTL4 &=~CCIFG; _isrptr_ccr4(); break;		//0x04 -> ccr2
#endif
#if defined(TA0CCR5_)
		case 0x0a: 	TAxCCR5+=_ccr5_pr; TAxCCTL5 &=~CCIFG; _isrptr_ccr5(); break;		//0x04 -> ccr2
#endif
#if defined(TA0CCR6_)
		case 0x0c: 	TAxCCR6+=_ccr6_pr; TAxCCTL6 &=~CCIFG; _isrptr_ccr6(); break;		//0x04 -> ccr2
#endif
		//ta0 overflow
		case 0x0e: 	                   TAxCTL &=~TAIFG; /*_isrptr_ta();*/ break;		//0x04 -> ccr2
		default: break;
	}
}

//uart0 isr
void uart0_isr(void) {
	char ch;									//transmission char
	//clear the flag - done automatically
	//USISR |= (1<<USIOIF);						//1->clera the flag
	switch (_U0TXphase) {
		case 1: 								//first half of the char has been sent, now send the 2nd transmission/data byte
			//OCR2A = TCNT2 + _UxTX_PR;			//reset the counter / prescaler
			//USIDR = _UxTXDR;					//load the data byte
			if (_U0TXDR & _U0TXmask) IO_SET(UART0_PORT, UART0_TX); else IO_CLR(UART0_PORT, UART0_TX);
			_U0TXmask = _U0TXmask >> 1;			//advance to the next bit
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-8);		//reload usisr: 1 data bit + 1 stop bit, 8->8 data bites to send
			if (_U0TXmask == 0) {				//current bit has been transmitted
				_U0TXphase = 2;					//2nd byte to be sent
				_U0TXDR = 0xff;					//stop bits
				_U0TXmask = 1<<(1-1);			//1 stop bit. 1<<(2-1) for 2 stop bits
			}
			break;
		case 2:									//send the stop bit(s)
			//OCR2A = TCNT2 + _UxTX_PR;			//reset the counter / prescaler
			if (_U0TXDR & _U0TXmask) IO_SET(UART0_PORT, UART0_TX); else IO_CLR(UART0_PORT, UART0_TX);
			_U0TXmask = _U0TXmask >> 1;			//advance to the next bit
			//USIDR = 0xff;						//load the stop bits - bits of 1
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-1);		//reload usisr: 1->1 stop bit, 2->2 stop bits, ..., 8->8 stop bits
			if (_U0TXmask == 0) {
				_U0TXphase = 0;					//2nd byte to be sent
			}
			break;
		case 0:									//end the transmission
			if (*_U0TX_ptr == 0) {				//end of the string has been reached
				//USICR = 0;						//disable usi
				//USISR = (1<<USIOIF);
				//TIMSK2&=~(1<<OCIE2A);				//1->enable the interrupt, 0->disable the interrupt
				TAxCCTL0 &=~(1<<4);					//1->enable the compare / capture interrupt
				_U0TX_BUSY = 0;						//no long buy
				//IO_SET(UART_PORT, UART_TX);		//set the TX pin - optional
			} else {
				//more char to sent
				//_UxTX_BUSY = 1;							//uart is busy
				//IO_SET(UART_PORT, UART_TX);			//TX high
				//reverse the input byte's order: LSB..MSB
				_U0TXphase = 1;							//to send the 1st byte
				//inverse the order of data byte
				//_UxTX_ptr = str;						//save the string
				ch = *_U0TX_ptr++;						//save the char and advance the string pointer
				_U0TXDR = RBIT(ch);						//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
				//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
				_U0TXmask = 1<<7;						//transmission mask
				//OCR2A = TCNT2 + _UxTX_PR;				//reset the timer/prescaler
				TAxCCR0 = TAxR + _U0TX_PR;				//reset the timer/prescaler
				//clear TIFR/TIMSK
				//TIFR |= (1<<OCF0A);					//1->clera the flag
				//TIMSK|= (1<<OCIE0A);					//1->enable the interrupt, 0->disable the interrupt
				IO_CLR(UART0_PORT, UART0_TX);				//send the start bit -> low
			}
			break;
	}
}

//initialize the uart0
//1-start bit, 8-data bit, 1-stop bit, no parity
void uart0_init(uint32_t bps) {
	//initialize the pins - output, idles high
	IO_SET(UART0_PORT, UART0_TX);
	IO_OUT(UART0_DDR, UART0_TX);
	
	//initialize the timer
	//clear the timer control register
	TAxCTL |= TACLR;							//TxCTL_bit.TACLR;						//set to reset timer a

	//stop timer
	//TxCTL &=~MC_0;							//TxCTL_bit.TAMC = 0x00;				//timer mode - 0x00: halted, 0x01: up mode, 0x02: continuous mode (to 0xffff), 0x03: up/down
	//TxCTL |= TASSEL_2;						//TxCTL_bit.TASSEL = 0x02;				//timer source - 0x00: TACLK, 0x01: ACLK, 0x02: SMCLK, 0x03: INCLK
	//TxCTL |= (ps & ID_3);						//TxCTL_bit.TAID = ps & 0x03;			//input divider - 0x00: /1, 0x01: /2, 0x02: /4, 0x03: /8
	TAxCTL &=~TAIFG;							//TxCTL_bit.TAIFG = 0;					//interrupt flag: 0= no interrupt pending; 1=interrupt pending
	TAxCTL &=~TAIE;							//TxCTL_bit.TAIE = 0;					//timer a interrupt enable: 0: interrupt disabled; 1: interrupt enabled;
	//TxCTL |= OUTMOD0;							//set output mode to zero

	//set up the output compare
	//set up TAxCCTLx register
	TAxCCTL0 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
	//clear the flag
	TAxCCTL0 &=~CCIFG;						//0->clear the interrupt flag
	TAxCCTL0 &=~(1<<4);						//1->enable the compare / capture interrupt

	TAxCTL = 	TASSEL_2 |						//0=TACLK, 1=ACLK, 2=SMCLK, and 3=INCLK
				(0 & TAx_PS8x) |				//prescaler
				MC_2 |							//0=stop, 1=up to ccr0, 2=continous mode, 3=up and down
				0x00;							//TCIE disabled
#if defined(TA0EX0_)
	TAxEX0 = (0 & TAx_EX8x);	//set expansion divider
#endif
	
	//calculate the timing
	if (F_UART <= (bps << 16) * 1) {
		//running at 1:1 prescaler
		_U0TX_PR = F_UART / bps / 1 - 1;	//set the range
		TAxCTL = (TAxCTL &~TAx_PS8x) | ((0<<6) & TAx_PS8x);	//0->set the prescaler to 1:1
	} else if (F_UART <= (bps << 16) * 8) {
		//running at 8:1 prescaler
		_U0TX_PR = F_UART / bps / 8 - 1;	//set the range
		TAxCTL = (TAxCTL &~TAx_PS8x) | ((3<<6) & TAx_PS8x);	//1->set the prescaler to 8:1
	}
	//timer is running now
}

//send a char
void uart0_put(char ch) {
	static char _buffer[2]={0,0};			//serial transmission buffer
	_buffer[0]=ch; 							//first char
	uart0_puts(_buffer);						//send the buffer
}

//send a string - no empty string, null-terminated
void uart0_puts(char *str) {
	char ch;
	while (uart0_busy()) continue;			//wait for the uart to be ready
	_U0TX_BUSY = 1;							//uart is busy
	//IO_SET(UART_PORT, UART_TX);			//TX high
	//reverse the input byte's order: LSB..MSB
	_U0TXphase = 1;							//to send the 1st byte
	//inverse the order of data byte
	_U0TX_ptr = str;						//save the string
	ch = *_U0TX_ptr++;						//save the char and advance the string pointer
	_U0TXDR = RBIT(ch);						//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
	//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
	_U0TXmask = 1<<7;						//transmission mask
	TAxCCR0 = TAxR + _U0TX_PR;				//reset the timer/prescaler
	//clear the flag
	TAxCCTL0 &=~CCIFG;						//0->clear the interrupt flag
	TAxCCTL0 |= (1<<4);						//1->enable the compare / capture interrupt
	IO_CLR(UART0_PORT, UART0_TX);				//send the start bit -> low
}

//test for busy SIGNAL
char uart0_busy(void) {
	return _U0TX_BUSY;
}

//uart1 isr
void uart1_isr(void) {
	char ch;									//transmission char
	//clear the flag - done automatically
	//USISR |= (1<<USIOIF);						//1->clera the flag
	switch (_U1TXphase) {
		case 1: 								//first half of the char has been sent, now send the 2nd transmission/data byte
			//OCR2A = TCNT2 + _UxTX_PR;			//reset the counter / prescaler
			//USIDR = _UxTXDR;					//load the data byte
			if (_U1TXDR & _U1TXmask) IO_SET(UART1_PORT, UART1_TX); else IO_CLR(UART1_PORT, UART1_TX);
			_U1TXmask = _U1TXmask >> 1;			//advance to the next bit
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-8);		//reload usisr: 1 data bit + 1 stop bit, 8->8 data bites to send
			if (_U1TXmask == 0) {				//current bit has been transmitted
				_U1TXphase = 2;					//2nd byte to be sent
				_U1TXDR = 0xff;					//stop bits
				_U1TXmask = 1<<(1-1);			//1 stop bit. 1<<(2-1) for 2 stop bits
			}
			break;
		case 2:									//send the stop bit(s)
			//OCR2A = TCNT2 + _UxTX_PR;			//reset the counter / prescaler
			if (_U1TXDR & _U1TXmask) IO_SET(UART1_PORT, UART1_TX); else IO_CLR(UART1_PORT, UART1_TX);
			_U1TXmask = _U1TXmask >> 1;			//advance to the next bit
			//USIDR = 0xff;						//load the stop bits - bits of 1
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-1);		//reload usisr: 1->1 stop bit, 2->2 stop bits, ..., 8->8 stop bits
			if (_U1TXmask == 0) {
				_U1TXphase = 0;					//2nd byte to be sent
			}
			break;
		case 0:									//end the transmission
			if (*_U1TX_ptr == 0) {				//end of the string has been reached
				//USICR = 0;						//disable usi
				//USISR = (1<<USIOIF);
				//TIMSK2&=~(1<<OCIE2A);				//1->enable the interrupt, 0->disable the interrupt
				TAxCCTL1 &=~(1<<4);					//1->enable the compare / capture interrupt
				_U1TX_BUSY = 0;						//no long buy
				//IO_SET(UART_PORT, UART_TX);		//set the TX pin - optional
			} else {
				//more char to sent
				//_UxTX_BUSY = 1;							//uart is busy
				//IO_SET(UART_PORT, UART_TX);			//TX high
				//reverse the input byte's order: LSB..MSB
				_U1TXphase = 1;							//to send the 1st byte
				//inverse the order of data byte
				//_UxTX_ptr = str;						//save the string
				ch = *_U1TX_ptr++;						//save the char and advance the string pointer
				_U1TXDR = RBIT(ch);						//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
				//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
				_U1TXmask = 1<<7;						//transmission mask
				//OCR2A = TCNT2 + _UxTX_PR;				//reset the timer/prescaler
				TAxCCR1 = TAxR + _U1TX_PR;				//reset the timer/prescaler
				//clear TIFR/TIMSK
				//TIFR |= (1<<OCF0A);					//1->clera the flag
				//TIMSK|= (1<<OCIE0A);					//1->enable the interrupt, 0->disable the interrupt
				IO_CLR(UART1_PORT, UART1_TX);				//send the start bit -> low
			}
			break;
	}
}
//initialize the uart1
//1-start bit, 8-data bit, 1-stop bit, no parity
void uart1_init(uint32_t bps) {
	//initialize the pins - output, idles high
	IO_SET(UART1_PORT, UART1_TX);
	IO_OUT(UART1_DDR, UART1_TX);
	
	//initialize the timer
	//clear the timer control register
	TAxCTL |= TACLR;							//TxCTL_bit.TACLR;						//set to reset timer a

	//stop timer
	//TxCTL &=~MC_0;							//TxCTL_bit.TAMC = 0x00;				//timer mode - 0x00: halted, 0x01: up mode, 0x02: continuous mode (to 0xffff), 0x03: up/down
	//TxCTL |= TASSEL_2;						//TxCTL_bit.TASSEL = 0x02;				//timer source - 0x00: TACLK, 0x01: ACLK, 0x02: SMCLK, 0x03: INCLK
	//TxCTL |= (ps & ID_3);						//TxCTL_bit.TAID = ps & 0x03;			//input divider - 0x00: /1, 0x01: /2, 0x02: /4, 0x03: /8
	TAxCTL &=~TAIFG;							//TxCTL_bit.TAIFG = 0;					//interrupt flag: 0= no interrupt pending; 1=interrupt pending
	TAxCTL &=~TAIE;							//TxCTL_bit.TAIE = 0;					//timer a interrupt enable: 0: interrupt disabled; 1: interrupt enabled;
	//TxCTL |= OUTMOD0;							//set output mode to zero

	//set up the output compare
	//set up TAxCCTLx register
	TAxCCTL1 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
	//clear the flag
	TAxCCTL1 &=~CCIFG;						//0->clear the interrupt flag
	TAxCCTL1 &=~(1<<4);						//1->enable the compare / capture interrupt

	TAxCTL = 	TASSEL_2 |						//0=TACLK, 1=ACLK, 2=SMCLK, and 3=INCLK
				(0 & TAx_PS8x) |				//prescaler
				MC_2 |							//0=stop, 1=up to ccr0, 2=continous mode, 3=up and down
				0x00;							//TCIE disabled
#if defined(TA0EX0_)
	TAxEX0 = (0 & TAx_EX8x);	//set expansion divider
#endif
	
	//calculate the timing
	if (F_UART <= (bps << 16) * 1) {
		//running at 1:1 prescaler
		_U1TX_PR = F_UART / bps / 1 - 1;	//set the range
		TAxCTL = (TAxCTL &~TAx_PS8x) | ((0<<6) & TAx_PS8x);	//0->set the prescaler to 1:1
	} else if (F_UART <= (bps << 16) * 8) {
		//running at 8:1 prescaler
		_U1TX_PR = F_UART / bps / 8 - 1;	//set the range
		TAxCTL = (TAxCTL &~TAx_PS8x) | ((3<<6) & TAx_PS8x);	//1->set the prescaler to 8:1
	}
	//timer is running now
}

//send a char
void uart1_put(char ch) {
	static char _buffer[2]={0,0};			//serial transmission buffer
	_buffer[0]=ch; 							//first char
	uart1_puts(_buffer);						//send the buffer
}

//send a string - no empty string, null-terminated
void uart1_puts(char *str) {
	char ch;
	while (uart1_busy()) continue;			//wait for the uart to be ready
	_U1TX_BUSY = 1;							//uart is busy
	//IO_SET(UART_PORT, UART_TX);			//TX high
	//reverse the input byte's order: LSB..MSB
	_U1TXphase = 1;							//to send the 1st byte
	//inverse the order of data byte
	_U1TX_ptr = str;						//save the string
	ch = *_U1TX_ptr++;						//save the char and advance the string pointer
	_U1TXDR = RBIT(ch);						//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
	//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
	_U1TXmask = 1<<7;						//transmission mask
	TAxCCR1 = TAxR + _U1TX_PR;				//reset the timer/prescaler
	//clear the flag
	TAxCCTL1 &=~CCIFG;						//0->clear the interrupt flag
	TAxCCTL1 |= (1<<4);						//1->enable the compare / capture interrupt
	IO_CLR(UART1_PORT, UART1_TX);			//send the start bit -> low
}

//test for busy SIGNAL
char uart1_busy(void) {
	return _U1TX_BUSY;
}


//uart2 isr
void uart2_isr(void) {
	char ch;									//transmission char
	//clear the flag - done automatically
	//USISR |= (1<<USIOIF);						//1->clera the flag
	switch (_U2TXphase) {
		case 1: 								//first half of the char has been sent, now send the 2nd transmission/data byte
			//OCR2A = TCNT2 + _UxTX_PR;			//reset the counter / prescaler
			//USIDR = _UxTXDR;					//load the data byte
			if (_U2TXDR & _U2TXmask) IO_SET(UART2_PORT, UART2_TX); else IO_CLR(UART2_PORT, UART2_TX);
			_U2TXmask = _U2TXmask >> 1;			//advance to the next bit
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-8);		//reload usisr: 1 data bit + 1 stop bit, 8->8 data bites to send
			if (_U2TXmask == 0) {				//current bit has been transmitted
				_U2TXphase = 2;					//2nd byte to be sent
				_U2TXDR = 0xff;					//stop bits
				_U2TXmask = 1<<(1-1);			//1 stop bit. 1<<(2-1) for 2 stop bits
			}
			break;
		case 2:									//send the stop bit(s)
			//OCR2A = TCNT2 + _UxTX_PR;			//reset the counter / prescaler
			if (_U2TXDR & _U2TXmask) IO_SET(UART0_PORT, UART0_TX); else IO_CLR(UART0_PORT, UART0_TX);
			_U2TXmask = _U2TXmask >> 1;			//advance to the next bit
			//USIDR = 0xff;						//load the stop bits - bits of 1
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-1);		//reload usisr: 1->1 stop bit, 2->2 stop bits, ..., 8->8 stop bits
			if (_U2TXmask == 0) {
				_U2TXphase = 0;					//2nd byte to be sent
			}
			break;
		case 0:									//end the transmission
			if (*_U2TX_ptr == 0) {				//end of the string has been reached
				//USICR = 0;						//disable usi
				//USISR = (1<<USIOIF);
				//TIMSK2&=~(1<<OCIE2A);				//1->enable the interrupt, 0->disable the interrupt
				TAxCCTL2 &=~(1<<4);					//1->enable the compare / capture interrupt
				_U2TX_BUSY = 0;						//no long buy
				//IO_SET(UART_PORT, UART_TX);		//set the TX pin - optional
			} else {
				//more char to sent
				//_UxTX_BUSY = 1;							//uart is busy
				//IO_SET(UART_PORT, UART_TX);			//TX high
				//reverse the input byte's order: LSB..MSB
				_U2TXphase = 1;							//to send the 1st byte
				//inverse the order of data byte
				//_UxTX_ptr = str;						//save the string
				ch = *_U2TX_ptr++;						//save the char and advance the string pointer
				_U2TXDR = RBIT(ch);						//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
				//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
				_U2TXmask = 1<<7;						//transmission mask
				//OCR2A = TCNT2 + _UxTX_PR;				//reset the timer/prescaler
				TAxCCR2 = TAxR + _U2TX_PR;				//reset the timer/prescaler
				//clear TIFR/TIMSK
				//TIFR |= (1<<OCF0A);					//1->clera the flag
				//TIMSK|= (1<<OCIE0A);					//1->enable the interrupt, 0->disable the interrupt
				IO_CLR(UART2_PORT, UART2_TX);				//send the start bit -> low
			}
			break;
	}
}

//initialize the uart2
//1-start bit, 8-data bit, 1-stop bit, no parity
void uart2_init(uint32_t bps) {
	//initialize the pins - output, idles high
	IO_SET(UART2_PORT, UART2_TX);
	IO_OUT(UART2_DDR, UART2_TX);
	
	//initialize the timer
	//clear the timer control register
	TAxCTL |= TACLR;							//TxCTL_bit.TACLR;						//set to reset timer a

	//stop timer
	//TxCTL &=~MC_0;							//TxCTL_bit.TAMC = 0x00;				//timer mode - 0x00: halted, 0x01: up mode, 0x02: continuous mode (to 0xffff), 0x03: up/down
	//TxCTL |= TASSEL_2;						//TxCTL_bit.TASSEL = 0x02;				//timer source - 0x00: TACLK, 0x01: ACLK, 0x02: SMCLK, 0x03: INCLK
	//TxCTL |= (ps & ID_3);						//TxCTL_bit.TAID = ps & 0x03;			//input divider - 0x00: /1, 0x01: /2, 0x02: /4, 0x03: /8
	TAxCTL &=~TAIFG;							//TxCTL_bit.TAIFG = 0;					//interrupt flag: 0= no interrupt pending; 1=interrupt pending
	TAxCTL &=~TAIE;							//TxCTL_bit.TAIE = 0;					//timer a interrupt enable: 0: interrupt disabled; 1: interrupt enabled;
	//TxCTL |= OUTMOD0;						//set output mode to zero

	//set up the output compare
	//set up TAxCCTLx register
	TAxCCTL2 = 	CM_0 |						//0=no capture
				CCIS_0 |					//0=input is CCIxA
				(0 << 11) |					//0=asynchronous, 1=synchronous
				(0 << 8) |					//0=compare, 1=capture
				OUTMOD_0 |					//0=OUTBIT
				(0 << 4) |					//1=compare / capture interrupt enabled, 0=disabled
				(0 << 2) |					//0=OUT is low, 1=OUT is high
				(0x00);
	//clear the flag
	TAxCCTL2 &=~CCIFG;						//0->clear the interrupt flag
	TAxCCTL2 &=~(1<<4);						//1->enable the compare / capture interrupt

	TAxCTL = 	TASSEL_2 |						//0=TACLK, 1=ACLK, 2=SMCLK, and 3=INCLK
				(0 & TAx_PS8x) |				//prescaler
				MC_2 |							//0=stop, 1=up to ccr0, 2=continous mode, 3=up and down
				0x00;							//TCIE disabled
#if defined(TA0EX0_)
	TAxEX0 = (0 & TAx_EX8x);	//set expansion divider
#endif
	
	//calculate the timing
	if (F_UART <= (bps << 16) * 1) {
		//running at 1:1 prescaler
		_U2TX_PR = F_UART / bps / 1 - 1;	//set the range
		TAxCTL = (TAxCTL &~TAx_PS8x) | ((0<<6) & TAx_PS8x);	//0->set the prescaler to 1:1
	} else if (F_UART <= (bps << 16) * 8) {
		//running at 8:1 prescaler
		_U2TX_PR = F_UART / bps / 8 - 1;	//set the range
		TAxCTL = (TAxCTL &~TAx_PS8x) | ((3<<6) & TAx_PS8x);	//1->set the prescaler to 8:1
	}
	//timer is running now
}

//send a char
void uart2_put(char ch) {
	static char _buffer[2]={0,0};			//serial transmission buffer
	_buffer[0]=ch; 							//first char
	uart2_puts(_buffer);					//send the buffer
}

//send a string - no empty string, null-terminated
void uart2_puts(char *str) {
	char ch;
	while (uart2_busy()) continue;			//wait for the uart to be ready
	_U2TX_BUSY = 1;							//uart is busy
	//IO_SET(UART_PORT, UART_TX);			//TX high
	//reverse the input byte's order: LSB..MSB
	_U2TXphase = 1;							//to send the 1st byte
	//inverse the order of data byte
	_U2TX_ptr = str;						//save the string
	ch = *_U2TX_ptr++;						//save the char and advance the string pointer
	_U2TXDR = RBIT(ch);						//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
	//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
	_U2TXmask = 1<<7;						//transmission mask
	TAxCCR2 = TAxR + _U2TX_PR;				//reset the timer/prescaler
	//clear the flag
	TAxCCTL2 &=~CCIFG;						//0->clear the interrupt flag
	TAxCCTL2 |= (1<<4);						//1->enable the compare / capture interrupt
	IO_CLR(UART2_PORT, UART2_TX);			//send the start bit -> low
}

//test for busy SIGNAL
char uart2_busy(void) {
	return _U2TX_BUSY;
}
