#include "uart2.h"

//reset uart
void uart2_init(uint16_t BaudRate) {
	uint16_t tmp;
	//route clock to uart2
	CLK->PCKENR1 |= CLK_PCKENR1_UART2;		//'1'=clock enabled, '0'=clock disabled

  	//user to configure TXpin (PD5) as output through serialBegin()
	//user to configure RXpin (PD6) as input through serialBegin()
	//configure UART2 RX (on PD6)
	
	//configure UART2 TX: 8-bit, 1-stop bit, no parity, syncmode disable
	UART2->CR1 |= (1<<5);					//'1'->disable uart, '0'->enable uart transmitter

	/*uint16_t */tmp = SystemCoreClock / BaudRate;			//max of 16-bit
	//set BRR2 first, per the datasheet
	UART2->BRR2 = ((tmp >> 8) & 0xf0) | (tmp & 0x0f);	//BRR2 is the top 4 + bottom 4 digits
	UART2->BRR1 = tmp >> 4;								//BRR1 is the middle 4 digits
	
	UART2->CR1 = 	(0<<7) |				//9th bit for receiving in 9-bit mode (when M=1)
					(0<<6) |				//9th bit for transmission in 9-bit mode (when M=1)
					(0<<5) |				//'0'->uart enabled, '1'->uart disabled
					(0<<4) |				//'0'->1start bit, 8 data bits, n stop bits; '1'->1 start bit, 9 data bits, 1 stop bit
					(0<<3) |				//'0'->idle line, '1'->address line wakes up uart
					(0<<2) |				//'0'->parity disabled, '1'->parity enabled
					(0<<1) |				//'0'->even partity, '1'->odd parity
					(0<<0) |				//'0'->parity interrupt disabled, '1'->parity interrupt enabled
					0x00;
	UART2->CR2 =	(0<<7) |				//'0'->tx interrupt disabled, '1'->tx interrupt enabled
					(0<<6) |				//'0'->tx completion interrupt diabled, '1'->tx completion interrupt enabled
					(0<<5) |				//'0'->rx interrupt disabled, '1'->rx interrupt enabled
					(0<<4) |				//'0'->idle line interrupt disabled, '1'->idle line interrupt enabled
					(1<<3) |				//'0'->tx disabled, '1'->tx enabled
					(1<<2) |				//'0'->rx disabled, '1'->rx enabled
					(0<<1) |				//'0'->receiver in active mode, '1'->receiver in mute mode
					(0<<0) |				//'0'->don't send break; '1'->send break;
					0x00;
	UART2->CR3 = 	(0<<6) |				//'0'->disable LIN, '1'->enable LIN
					(0<<4) |				//0->1 stop bit, 1->reserved, 2->2 stop bit, 3->1.5 stop bit
					(0<<3) |				//'0'->disable SCK, '1'->enable SCK
					(0<<2) |				//'0'->SCK idles low, '1'->SCK idles high
					(0<<1) |				//'0'->capture data on first clock transition, '1'->capture data on 2nd clock transition
					(0<<0) |				//'0'->last clock pulse is not output, '1'->last clock pulse is on output
					0x00;
	UART2->CR4 = 	(0<<6) |				//'0'->LIN break detection interrupt disabled, '1'->enabled
					(0<<5) |				//'0'->10-bit line detection, '1'->11-bit line detection
					(0<<4) |				//'0'->line break not detected, '1'->line break detected
					(0<<0) |				//4-bit Address of the UART note
					0x00;
	UART2->CR5 = 0;							//default value
	//configure interrupt -> if uart2 to be interrupt-driven
	
	//enable UART2
	UART2->CR1 &=~(1<<5);					//'0'->enable uart, '1'->disable uart
}

//get a char - blocking
//test uart1_available() before calling this function
char uart2_get(void) {
    //while (!(UART2->SR & UART2_SR_RXNE));  	//wait fo the receipt to terminate
    return UART2->DR;                       //save the transmission buffer
}

//put a char - blocking
void uart2_put(char dat) {
    UART2->DR = dat;                        //load the data buffer
    while (!(UART2->SR & UART2_SR_TXE));    //wait for the transmission to complete (_TC) or transmission buffer becomes empty (_TXE)
}

//put a string
void uart2_puts(char *str) {
	while (*str) 
		uart2_put(*str++);
}

//test if there is data in uart1 receiver buffer
//return !0 if there is data in UART2->DR
char uart2_available(void) {
	return UART2->SR & UART2_SR_RXNE;
}

//test if uart tx is in progress
//returns 1 if transmission buffer is full / uart1 busy
char uart2_busy(void) {
	return !(UART2->SR & UART2_SR_TXE);
}

