#include "uart_sw.h"					//we use software uart

//hardware configuration
//end hardware configuration

//global defines
#define F_UART			F_CPU
//not used: system clock as timebase
#if UART_TMR == 2								//TIM2/3/4: decide on time base
#define TIMx				TIM2
#elif UART_TMR == 3
#define TIMx				TIM3
#elif UART_TMR == 4
#define TIMx				TIM4
#else
#define TIMx				TIM5
#endif

//global variables
//look-up table for 4 bit reversal, in place
//for OC1
static volatile char _U1TX_BUSY = 0;				//uart status, 1->busy, 0->not busy
static volatile char _U1TXDR;						//transmission buffer -> data
static volatile char _U1TXSR;						//transmission shift register -> data
static volatile char _U1TXphase;					//send the first char: 1->start bit sent, 2->data byte sent, 0->stop bit(s) sent / not busy
static volatile uint8_t _U1TXmask;					//needs to be unsigned or right shift is undefined
static uint16_t _U1TXPR=0xffff;						//uart0 period
//for OC2
static volatile char _U2TX_BUSY = 0;				//uart status, 1->busy, 0->not busy
static volatile char _U2TXDR;						//transmission buffer -> data
static volatile char _U2TXSR;						//transmission shift register -> data
static volatile char _U2TXphase;					//send the first char: 1->start bit sent, 2->data byte sent, 0->stop bit(s) sent / not busy
static volatile uint8_t _U2TXmask;					//needs to be unsigned or right shift is undefined
static uint16_t _U2TXPR=0xffff;						//uart0 period
//for OC3
static volatile char _U3TX_BUSY = 0;				//uart status, 1->busy, 0->not busy
static volatile char _U3TXDR;						//transmission buffer -> data
static volatile char _U3TXSR;						//transmission shift register -> data
static volatile char _U3TXphase;					//send the first char: 1->start bit sent, 2->data byte sent, 0->stop bit(s) sent / not busy
static volatile uint8_t _U3TXmask;					//needs to be unsigned or right shift is undefined
static uint16_t _U3TXPR=0xffff;						//uart0 period
//for OC4
static volatile char _U4TX_BUSY = 0;				//uart status, 1->busy, 0->not busy
static volatile char _U4TXDR;						//transmission buffer -> data
static volatile char _U4TXSR;						//transmission shift register -> data
static volatile char _U4TXphase;					//send the first char: 1->start bit sent, 2->data byte sent, 0->stop bit(s) sent / not busy
static volatile uint8_t _U4TXmask;					//needs to be unsigned or right shift is undefined
static uint16_t _U4TXPR=0xffff;						//uart0 period

void uartoc1_isr(void);
void uartoc2_isr(void);
void uartoc3_isr(void);
void uartoc4_isr(void);

//Output compare ISR
#if UART_TMR == 2
void TIM2_IRQHandler(void) {
#elif UART_TMR == 3
void TIM3_IRQHandler(void) {
#elif UART_TMR == 4
void TIM4_IRQHandler(void) {
#else
void TIM5_IRQHandler(void) {
#endif
	//oc1 portion
	if ((TIMx->DIER & TIM_DIER_CC1IE) && (TIMx->SR & TIM_SR_CC1IF)) {		//output compare 1 flag is set
		TIMx->SR &=~TIM_SR_CC1IF;		//clear the flag
		TIMx->CCR1 += _U1TXPR;			//update the output compare register
		uartoc1_isr();					//execute user handler
	}

	//oc2 portion
	if ((TIMx->DIER & TIM_DIER_CC2IE) && (TIMx->SR & TIM_SR_CC2IF)) {		//output compare 2 flag is set
		TIMx->SR &=~TIM_SR_CC2IF;		//clear the flag
		TIMx->CCR2 += _U2TXPR;			//update the output compare register
		uartoc2_isr();					//execute user handler
	}

	//oc3 portion
	if ((TIMx->DIER & TIM_DIER_CC3IE) && (TIMx->SR & TIM_SR_CC3IF)) {		//output compare 2 flag is set
		TIMx->SR &=~TIM_SR_CC3IF;		//clear the flag
		TIMx->CCR3 += _U3TXPR;			//update the output compare register
		uartoc3_isr();					//execute user handler
	}

	//oc4 portion
	if ((TIMx->DIER & TIM_DIER_CC4IE) && (TIMx->SR & TIM_SR_CC4IF)) {		//output compare 2 flag is set
		TIMx->SR &=~TIM_SR_CC4IF;		//clear the flag
		TIMx->CCR4 += _U4TXPR;			//update the output compare register
		uartoc4_isr();					//execute user handler
	}

}

//oc1 isr
void uartoc1_isr(void) {
	//TIMx->SR &=~TIM_SR_CC1IF;					//clear tmr1 interrupt flag
	//TIMx->CCR1 += _U1TXPR;						//increment to the next match point
	switch (_U1TXphase) {
		case 1: 								//first half of the char has been sent, now send the 2nd transmission/data byte
			//TCNT0 = 0;							//reset the counter / prescaler
			//USIDR = _UxTXDR;					//load the data byte
			if (_U1TXDR & _U1TXmask) IO_SET(UARTSW1_PORT, UARTSW1_TX); else IO_CLR(UARTSW1_PORT, UARTSW1_TX);
			_U1TXmask = _U1TXmask << 1;			//advance to the next bit
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-8);		//reload usisr: 1 data bit + 1 stop bit, 8->8 data bites to send
			if (_U1TXmask == 0) {				//current bit has been transmitted
				_U1TXphase = 2;					//2nd byte to be sent
				_U1TXDR = 0xff;					//stop bits
				_U1TXmask = 1<<(8-1);			//1 stop bit. 1<<(2-1) for 2 stop bits
			}
			break;
		case 2:									//send the stop bit(s)
			//TCNT0 = 0;						//reset the counter / prescaler
			if (_U1TXDR & _U1TXmask) IO_SET(UARTSW1_PORT, UARTSW1_TX); else IO_CLR(UARTSW1_PORT, UARTSW1_TX);
			_U1TXmask = _U1TXmask << 1;			//advance to the next bit
			//USIDR = 0xff;						//load the stop bits - bits of 1
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-1);		//reload usisr: 1->1 stop bit, 2->2 stop bits, ..., 8->8 stop bits
			if (_U1TXmask == 0) {
				_U1TXphase = 0;					//2nd byte to be sent
			}
			break;
		case 0:									//end the transmission
			//USICR = 0;						//disable usi
			//USISR = (1<<USIOIF);
			TIMx->DIER &=~TIM_DIER_CC1IE;			//1->enable the interrupt, 0->disable the interrupt
			_U1TX_BUSY = 0;						//no long buy
			//IO_SET(UART_PORT, UART_TX);		//set the TX pin - optional
			break;
	}
}

//oc2 isr
void uartoc2_isr(void) {
	//TIMx->SR &=~TIM_SR_CC2IF;					//clear tmr1 interrupt flag
	//TIMx->CCR2 += _U2TXPR;						//increment to the next match point
	switch (_U2TXphase) {
		case 1: 								//first half of the char has been sent, now send the 2nd transmission/data byte
			//TCNT0 = 0;							//reset the counter / prescaler
			//USIDR = _UxTXDR;					//load the data byte
			if (_U2TXDR & _U2TXmask) IO_SET(UARTSW2_PORT, UARTSW2_TX); else IO_CLR(UARTSW2_PORT, UARTSW2_TX);
			_U2TXmask = _U2TXmask << 1;			//advance to the next bit
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-8);		//reload usisr: 1 data bit + 1 stop bit, 8->8 data bites to send
			if (_U2TXmask == 0) {				//current bit has been transmitted
				_U2TXphase = 2;					//2nd byte to be sent
				_U2TXDR = 0xff;					//stop bits
				_U2TXmask = 1<<(8-1);			//1 stop bit. 1<<(2-1) for 2 stop bits
			}
			break;
		case 2:									//send the stop bit(s)
			//TCNT0 = 0;						//reset the counter / prescaler
			if (_U2TXDR & _U2TXmask) IO_SET(UARTSW2_PORT, UARTSW2_TX); else IO_CLR(UARTSW2_PORT, UARTSW2_TX);
			_U2TXmask = _U2TXmask << 1;			//advance to the next bit
			//USIDR = 0xff;						//load the stop bits - bits of 1
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-1);		//reload usisr: 1->1 stop bit, 2->2 stop bits, ..., 8->8 stop bits
			if (_U2TXmask == 0) {
				_U2TXphase = 0;					//2nd byte to be sent
			}
			break;
		case 0:									//end the transmission
			//USICR = 0;						//disable usi
			//USISR = (1<<USIOIF);
			TIMx->DIER &=~TIM_DIER_CC2IE;			//1->enable the interrupt, 0->disable the interrupt
			_U2TX_BUSY = 0;						//no long buy
			//IO_SET(UART_PORT, UART_TX);		//set the TX pin - optional
			break;
	}
}

//oc3 isr
void uartoc3_isr(void) {
	//TIMx->SR &=~TIM_SR_CC3IF;					//clear tmr1 interrupt flag
	//TIMx->CCR3 += _U3TXPR;						//increment to the next match point
	switch (_U3TXphase) {
		case 1: 								//first half of the char has been sent, now send the 2nd transmission/data byte
			//TCNT0 = 0;							//reset the counter / prescaler
			//USIDR = _UxTXDR;					//load the data byte
			if (_U3TXDR & _U3TXmask) IO_SET(UARTSW3_PORT, UARTSW3_TX); else IO_CLR(UARTSW3_PORT, UARTSW3_TX);
			_U3TXmask = _U3TXmask << 1;			//advance to the next bit
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-8);		//reload usisr: 1 data bit + 1 stop bit, 8->8 data bites to send
			if (_U3TXmask == 0) {				//current bit has been transmitted
				_U3TXphase = 2;					//2nd byte to be sent
				_U3TXDR = 0xff;					//stop bits
				_U3TXmask = 1<<(8-1);			//1 stop bit. 1<<(2-1) for 2 stop bits
			}
			break;
		case 2:									//send the stop bit(s)
			//TCNT0 = 0;						//reset the counter / prescaler
			if (_U3TXDR & _U3TXmask) IO_SET(UARTSW3_PORT, UARTSW3_TX); else IO_CLR(UARTSW3_PORT, UARTSW3_TX);
			_U3TXmask = _U3TXmask << 1;			//advance to the next bit
			//USIDR = 0xff;						//load the stop bits - bits of 1
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-1);		//reload usisr: 1->1 stop bit, 2->2 stop bits, ..., 8->8 stop bits
			if (_U3TXmask == 0) {
				_U3TXphase = 0;					//2nd byte to be sent
			}
			break;
		case 0:									//end the transmission
			//USICR = 0;						//disable usi
			//USISR = (1<<USIOIF);
			TIMx->DIER &=~TIM_DIER_CC3IE;			//1->enable the interrupt, 0->disable the interrupt
			_U3TX_BUSY = 0;						//no long buy
			//IO_SET(UART_PORT, UART_TX);		//set the TX pin - optional
			break;
	}
}

//oc4 isr
void uartoc4_isr(void) {
	//TIMx->SR &=~TIM_SR_CC4IF;					//clear tmr1 interrupt flag
	//TIMx->CCR4 += _U4TXPR;						//increment to the next match point
	switch (_U4TXphase) {
		case 1: 								//first half of the char has been sent, now send the 2nd transmission/data byte
			//TCNT0 = 0;							//reset the counter / prescaler
			//USIDR = _UxTXDR;					//load the data byte
			if (_U4TXDR & _U4TXmask) IO_SET(UARTSW4_PORT, UARTSW4_TX); else IO_CLR(UARTSW4_PORT, UARTSW4_TX);
			_U4TXmask = _U4TXmask << 1;			//advance to the next bit
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-8);		//reload usisr: 1 data bit + 1 stop bit, 8->8 data bites to send
			if (_U4TXmask == 0) {				//current bit has been transmitted
				_U4TXphase = 2;					//2nd byte to be sent
				_U4TXDR = 0xff;					//stop bits
				_U4TXmask = 1<<(8-1);			//1 stop bit. 1<<(2-1) for 2 stop bits
			}
			break;
		case 2:									//send the stop bit(s)
			//TCNT0 = 0;						//reset the counter / prescaler
			if (_U4TXDR & _U4TXmask) IO_SET(UARTSW4_PORT, UARTSW4_TX); else IO_CLR(UARTSW4_PORT, UARTSW4_TX);
			_U4TXmask = _U4TXmask << 1;			//advance to the next bit
			//USIDR = 0xff;						//load the stop bits - bits of 1
			//USICR = (1<<USIOIE) | (1<<USIWM0) | (1<<2);	//enable the interrupt + start uart
			//USISR = (1<<USIOIF) | (16-1);		//reload usisr: 1->1 stop bit, 2->2 stop bits, ..., 8->8 stop bits
			if (_U4TXmask == 0) {
				_U4TXphase = 0;					//2nd byte to be sent
			}
			break;
		case 0:									//end the transmission
			//USICR = 0;						//disable usi
			//USISR = (1<<USIOIF);
			TIMx->DIER &=~TIM_DIER_CC4IE;			//1->enable the interrupt, 0->disable the interrupt
			_U4TX_BUSY = 0;						//no long buy
			//IO_SET(UART_PORT, UART_TX);		//set the TX pin - optional
			break;
	}
}

//initialize software uart / CCP
//only TX is implemented
//time base TMRx, use output compare ch 1
void uartoc1_init(uint32_t bps) {
	_U1TX_BUSY = 0;							//0->not busy, 1->busy
	_U1TXphase = 0;							//1->sending the first byte, 0->sending the 2nd byte

	//initialize the tx pins: idles high, as output
	IO_SET(UARTSW1_PORT, UARTSW1_TX); IO_OUT(UARTSW1_PORT, UARTSW1_TX);

	//enable the clock
#if UART_TMR == 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM2_IRQn);		//enable irq
	//priorities not set -> default values used.
#elif UART_TMR == 3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM3_IRQn);		//enable irq
	//priorities not set -> default values used.
#elif UART_TMR == 4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM4_IRQn);		//enable irq
	//priorities not set -> default values used.
#else
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM5_IRQn);		//enable irq
	//priorities not set -> default values used.
#endif
	//stop the timer
	//source from internal clock -> disable slave mode
	TIMx->SMCR &=~TIM_SMCR_SMS;			//clear sms->use internal clock

	//stop the timer to configure it
	//TIMx as free running 16-bit time base
	//TIMx->CR1 &=~TIM_CR1_CEN;			//clear cen. 0=disable the timer, 1=enable the timer
	//TIMx->CR1 &=~TIM_CR1_CKD;			//clear CKD0..1. 0b00->1x clock; 0b01->2:1 clock, 0b10->4:1 clk; 0b11->reserved
	//TIMx->CR1 &=~TIM_CR1_DIR;			//clear DIR bit. 0=upcounter, 1=downcounter
	//TIMx->CR1 &=~TIM_CR1_OPM;			//clear opm bit. 0=periodic timer, 1=one-shot timer
	//or to simply zero the register
	TIMx->CR1 = 0;						//much easier

	//set the prescaler
	//TIMx->PSC = ps - 1;					//set the prescaler
	TIMx->RCR = 0;						//repetition counter = 0 (=no repetition)
	TIMx->ARR = -1;						//auto reload register / period = 0; - need to change for downcounters
	TIMx->CNT = 0;						//reset the counter
	//set prescaler
	if (F_UART <= bps * 65536ul) {
		//prescaler to 1:1
		TIMx->PSC = 1 - 1;
		_U1TXPR = F_UART / bps / 1 - 1;		//period saved to _U1TXPR
	} else {
		//prescaler to 256:1
		TIMx->PSC = 256 - 1;
		_U1TXPR = F_UART / bps / 256 - 1;	//period saved to _U1TXPR
	}

	//configure output compare channel
	//clear interrupt flag, disable interrupt
	//clear the status register bits for capture / compare flags
	TIMx->SR &=~TIM_SR_CC1IF;
	//disable the interrupt by clearing the enable bits
	TIMx->DIER &=~TIM_DIER_CC1IE;

	//configure the output compare unit
	TIMx->CCMR1 = (TIMx->CCMR1 &~0x0f);	//clear the lowest four bits
	TIMx->CCER &=~TIM_CCER_CC1E;		//1->enable the output, 0->disable the output

	//start timer
	//enable the timer.
	TIMx->CR1 |= TIM_CR1_CEN;			//enable the timer
}

//send a char
void uartoc1_put(char ch) {
	while (uartoc1_busy()) continue;			//wait for the uart to be ready
	_U1TX_BUSY = 1;							//uart is busy
	//IO_SET(UART_PORT, UART_TX);			//TX high
	//reverse the input byte's order: LSB..MSB
	_U1TXphase = 1;							//to send the 1st byte
	//inverse the order of data byte
	_U1TXDR = ch;							//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
	//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
	_U1TXmask = 1<<0;						//transmission mask -> LSB
	//TIMx->CNT = 0;							//reset the counter
	//TIMx->CCR1 = TIMx->CNT + _U1TXPR;		//reset the timer/prescaler
	TIMx->CCR1= _U1TXPR;
	//while (TIMx->CNT < TIMx->CCR1) continue;
	//clear TIFR/TIMSK
	TIMx->SR &=~TIM_SR_CC1IF;				//1->clera the flag
	TIMx->DIER |=TIM_DIER_CC1IE;				//1->enable the interrupt, 0->disable the interrupt
	TIMx->EGR |= TIM_EGR_UG;		//force an update
	IO_CLR(UARTSW1_PORT, UARTSW1_TX);		//send the start bit -> low
}

//send a string
void uartoc1_puts(char *str) {
	while (*str) uartoc1_put(*str++);
}

//test for busy SIGNAL
char uartoc1_busy(void) {
	return _U1TX_BUSY;
}

//initialize software uart / CCP
//only TX is implemented
//time base TMRx, use output compare ch 1
void uartoc2_init(uint32_t bps) {
	_U2TX_BUSY = 0;							//0->not busy, 1->busy
	_U2TXphase = 0;							//1->sending the first byte, 0->sending the 2nd byte

	//initialize the tx pins: idles high, as output
	IO_SET(UARTSW2_PORT, UARTSW2_TX); IO_OUT(UARTSW2_PORT, UARTSW2_TX);

	//enable the clock
#if UART_TMR == 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM2_IRQn);		//enable irq
	//priorities not set -> default values used.
#elif UART_TMR == 3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM3_IRQn);		//enable irq
	//priorities not set -> default values used.
#elif UART_TMR == 4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM4_IRQn);		//enable irq
	//priorities not set -> default values used.
#else
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM5_IRQn);		//enable irq
	//priorities not set -> default values used.
#endif
	//stop the timer
	//source from internal clock -> disable slave mode
	TIMx->SMCR &=~TIM_SMCR_SMS;			//clear sms->use internal clock

	//stop the timer to configure it
	//TIMx as free running 16-bit time base
	//TIMx->CR1 &=~TIM_CR1_CEN;			//clear cen. 0=disable the timer, 1=enable the timer
	//TIMx->CR1 &=~TIM_CR1_CKD;			//clear CKD0..1. 0b00->1x clock; 0b01->2:1 clock, 0b10->4:1 clk; 0b11->reserved
	//TIMx->CR1 &=~TIM_CR1_DIR;			//clear DIR bit. 0=upcounter, 1=downcounter
	//TIMx->CR1 &=~TIM_CR1_OPM;			//clear opm bit. 0=periodic timer, 1=one-shot timer
	//or to simply zero the register
	TIMx->CR1 = 0;						//much easier

	//set the prescaler
	//TIMx->PSC = ps - 1;					//set the prescaler
	TIMx->RCR = 0;						//repetition counter = 0 (=no repetition)
	TIMx->ARR = -1;						//auto reload register / period = 0; - need to change for downcounters
	TIMx->CNT = 0;						//reset the counter
	//set prescaler
	if (F_UART <= bps * 65536ul) {
		//prescaler to 1:1
		TIMx->PSC = 1 - 1;
		_U2TXPR = F_UART / bps / 1 - 1;		//period saved to _U1TXPR
	} else {
		//prescaler to 256:1
		TIMx->PSC = 256 - 1;
		_U2TXPR = F_UART / bps / 256 - 1;	//period saved to _U1TXPR
	}

	//configure output compare channel
	//clear interrupt flag, disable interrupt
	//clear the status register bits for capture / compare flags
	TIMx->SR &=~TIM_SR_CC2IF;
	//disable the interrupt by clearing the enable bits
	TIMx->DIER &=~TIM_DIER_CC2IE;

	//configure the output compare unit
	TIMx->CCMR1 = (TIMx->CCMR1 &~0xf0);	//clear the lowest four bits
	TIMx->CCER &=~TIM_CCER_CC2E;		//1->enable the output, 0->disable the output

	//start timer
	//enable the timer.
	TIMx->CR1 |= TIM_CR1_CEN;			//enable the timer
}

//send a char
void uartoc2_put(char ch) {
	while (uartoc2_busy()) continue;			//wait for the uart to be ready
	_U2TX_BUSY = 1;							//uart is busy
	//IO_SET(UART_PORT, UART_TX);			//TX high
	//reverse the input byte's order: LSB..MSB
	_U2TXphase = 1;							//to send the 1st byte
	//inverse the order of data byte
	_U2TXDR = ch;							//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
	//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
	_U2TXmask = 1<<0;						//transmission mask -> LSB
	//TIMx->CNT = 0;							//reset the counter
	//TIMx->CCR2 = TIMx->CNT + _U2TXPR;		//reset the timer/prescaler
	TIMx->CCR2 = _U2TXPR;
	//clear TIFR/TIMSK
	TIMx->SR &=~TIM_SR_CC2IF;				//1->clera the flag
	TIMx->DIER |=TIM_DIER_CC2IE;				//1->enable the interrupt, 0->disable the interrupt
	TIMx->EGR |= TIM_EGR_UG;		//force an update
	IO_CLR(UARTSW2_PORT, UARTSW2_TX);		//send the start bit -> low
}

//send a string
void uartoc2_puts(char *str) {
	while (*str) uartoc2_put(*str++);
}

//test for busy SIGNAL
char uartoc2_busy(void) {
	return _U2TX_BUSY;
}

//initialize software uart / CCP
//only TX is implemented
//time base TMRx, use output compare ch 1
void uartoc3_init(uint32_t bps) {
	_U3TX_BUSY = 0;							//0->not busy, 1->busy
	_U3TXphase = 0;							//1->sending the first byte, 0->sending the 2nd byte

	//initialize the tx pins: idles high, as output
	IO_SET(UARTSW3_PORT, UARTSW3_TX); IO_OUT(UARTSW3_PORT, UARTSW3_TX);

	//enable the clock
#if UART_TMR == 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM2_IRQn);		//enable irq
	//priorities not set -> default values used.
#elif UART_TMR == 3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM3_IRQn);		//enable irq
	//priorities not set -> default values used.
#elif UART_TMR == 4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM4_IRQn);		//enable irq
	//priorities not set -> default values used.
#else
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM5_IRQn);		//enable irq
	//priorities not set -> default values used.
#endif
	//stop the timer
	//source from internal clock -> disable slave mode
	TIMx->SMCR &=~TIM_SMCR_SMS;			//clear sms->use internal clock

	//stop the timer to configure it
	//TIMx as free running 16-bit time base
	//TIMx->CR1 &=~TIM_CR1_CEN;			//clear cen. 0=disable the timer, 1=enable the timer
	//TIMx->CR1 &=~TIM_CR1_CKD;			//clear CKD0..1. 0b00->1x clock; 0b01->2:1 clock, 0b10->4:1 clk; 0b11->reserved
	//TIMx->CR1 &=~TIM_CR1_DIR;			//clear DIR bit. 0=upcounter, 1=downcounter
	//TIMx->CR1 &=~TIM_CR1_OPM;			//clear opm bit. 0=periodic timer, 1=one-shot timer
	//or to simply zero the register
	TIMx->CR1 = 0;						//much easier

	//set the prescaler
	//TIMx->PSC = ps - 1;					//set the prescaler
	TIMx->RCR = 0;						//repetition counter = 0 (=no repetition)
	TIMx->ARR = -1;						//auto reload register / period = 0; - need to change for downcounters
	TIMx->CNT = 0;						//reset the counter
	//set prescaler
	if (F_UART <= bps * 65536ul) {
		//prescaler to 1:1
		TIMx->PSC = 1 - 1;
		_U3TXPR = F_UART / bps / 1 - 1;		//period saved to _U1TXPR
	} else {
		//prescaler to 256:1
		TIMx->PSC = 256 - 1;
		_U3TXPR = F_UART / bps / 256 - 1;	//period saved to _U1TXPR
	}

	//configure output compare channel
	//clear interrupt flag, disable interrupt
	//clear the status register bits for capture / compare flags
	TIMx->SR &=~TIM_SR_CC3IF;
	//disable the interrupt by clearing the enable bits
	TIMx->DIER &=~TIM_DIER_CC3IE;

	//configure the output compare unit
	TIMx->CCMR2 = (TIMx->CCMR2 &~0x0f);	//clear the lowest four bits
	TIMx->CCER &=~TIM_CCER_CC3E;		//1->enable the output, 0->disable the output

	//start timer
	//enable the timer.
	TIMx->CR1 |= TIM_CR1_CEN;			//enable the timer
}

//send a char
void uartoc3_put(char ch) {
	while (uartoc3_busy()) continue;			//wait for the uart to be ready
	_U3TX_BUSY = 1;							//uart is busy
	//IO_SET(UART_PORT, UART_TX);			//TX high
	//reverse the input byte's order: LSB..MSB
	_U3TXphase = 1;							//to send the 1st byte
	//inverse the order of data byte
	_U3TXDR = ch;							//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
	//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
	_U3TXmask = 1<<0;						//transmission mask -> LSB
	//TIMx->CNT = 0;							//reset the counter
	//TIMx->CCR3 = TIMx->CNT + _U3TXPR;		//reset the timer/prescaler
	TIMx->CCR3 = _U3TXPR;
	//clear TIFR/TIMSK
	TIMx->SR &=~TIM_SR_CC3IF;				//1->clera the flag
	TIMx->DIER |=TIM_DIER_CC3IE;				//1->enable the interrupt, 0->disable the interrupt
	TIMx->EGR |= TIM_EGR_UG;		//force an update
	IO_CLR(UARTSW3_PORT, UARTSW3_TX);		//send the start bit -> low
}

//send a string
void uartoc3_puts(char *str) {
	while (*str) uartoc3_put(*str++);
}

//test for busy SIGNAL
char uartoc3_busy(void) {
	return _U3TX_BUSY;
}

//initialize software uart / CCP
//only TX is implemented
//time base TMRx, use output compare ch 1
void uartoc4_init(uint32_t bps) {
	_U4TX_BUSY = 0;							//0->not busy, 1->busy
	_U4TXphase = 0;							//1->sending the first byte, 0->sending the 2nd byte

	//initialize the tx pins: idles high, as output
	IO_SET(UARTSW4_PORT, UARTSW4_TX); IO_OUT(UARTSW4_PORT, UARTSW4_TX);

	//enable the clock
#if UART_TMR == 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM2_IRQn);		//enable irq
	//priorities not set -> default values used.
#elif UART_TMR == 3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM3_IRQn);		//enable irq
	//priorities not set -> default values used.
#elif UART_TMR == 4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM4_IRQn);		//enable irq
	//priorities not set -> default values used.
#else
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	//enable interrupt
	NVIC_EnableIRQ(TIM5_IRQn);		//enable irq
	//priorities not set -> default values used.
#endif
	//stop the timer
	//source from internal clock -> disable slave mode
	TIMx->SMCR &=~TIM_SMCR_SMS;			//clear sms->use internal clock

	//stop the timer to configure it
	//TIMx as free running 16-bit time base
	//TIMx->CR1 &=~TIM_CR1_CEN;			//clear cen. 0=disable the timer, 1=enable the timer
	//TIMx->CR1 &=~TIM_CR1_CKD;			//clear CKD0..1. 0b00->1x clock; 0b01->2:1 clock, 0b10->4:1 clk; 0b11->reserved
	//TIMx->CR1 &=~TIM_CR1_DIR;			//clear DIR bit. 0=upcounter, 1=downcounter
	//TIMx->CR1 &=~TIM_CR1_OPM;			//clear opm bit. 0=periodic timer, 1=one-shot timer
	//or to simply zero the register
	TIMx->CR1 = 0;						//much easier

	//set the prescaler
	//TIMx->PSC = ps - 1;					//set the prescaler
	TIMx->RCR = 0;						//repetition counter = 0 (=no repetition)
	TIMx->ARR = -1;						//auto reload register / period = 0; - need to change for downcounters
	TIMx->CNT = 0;						//reset the counter
	//set prescaler
	if (F_UART <= bps * 65536ul) {
		//prescaler to 1:1
		TIMx->PSC = 1 - 1;
		_U4TXPR = F_UART / bps / 1 - 1;		//period saved to _U1TXPR
	} else {
		//prescaler to 256:1
		TIMx->PSC = 256 - 1;
		_U4TXPR = F_UART / bps / 256 - 1;	//period saved to _U1TXPR
	}

	//configure output compare channel
	//clear interrupt flag, disable interrupt
	//clear the status register bits for capture / compare flags
	TIMx->SR &=~TIM_SR_CC4IF;
	//disable the interrupt by clearing the enable bits
	TIMx->DIER &=~TIM_DIER_CC4IE;

	//configure the output compare unit
	TIMx->CCMR2 = (TIMx->CCMR2 &~0xf0);	//clear the lowest four bits
	TIMx->CCER &=~TIM_CCER_CC4E;		//1->enable the output, 0->disable the output

	//start timer
	//enable the timer.
	TIMx->CR1 |= TIM_CR1_CEN;			//enable the timer
}

//send a char
void uartoc4_put(char ch) {
	while (uartoc4_busy()) continue;			//wait for the uart to be ready
	_U4TX_BUSY = 1;							//uart is busy
	//IO_SET(UART_PORT, UART_TX);			//TX high
	//reverse the input byte's order: LSB..MSB
	_U4TXphase = 1;							//to send the 1st byte
	//inverse the order of data byte
	_U4TXDR = ch;							//(r4_lut[ch & 0x0f] << 4) | r4_lut[ch >> 4];
	//_UxTXSR = (_UxTXDR << 7) | 0x7f;		//prepare for the next byte
	_U4TXmask = 1<<0;						//transmission mask -> LSB
	//TIMx->CNT = 0;							//reset the counter
	//TIMx->CCR4 = TIMx->CNT + _U4TXPR;		//reset the timer/prescaler
	TIMx->CCR4 = _U4TXPR;
	//clear TIFR/TIMSK
	TIMx->SR &=~TIM_SR_CC4IF;				//1->clera the flag
	TIMx->DIER |=TIM_DIER_CC4IE;				//1->enable the interrupt, 0->disable the interrupt
	TIMx->EGR |= TIM_EGR_UG;		//force an update
	IO_CLR(UARTSW4_PORT, UARTSW4_TX);		//send the start bit -> low
}

//send a string
void uartoc4_puts(char *str) {
	while (*str) uartoc4_put(*str++);
}

//test for busy SIGNAL
char uartoc4_busy(void) {
	return _U4TX_BUSY;
}
