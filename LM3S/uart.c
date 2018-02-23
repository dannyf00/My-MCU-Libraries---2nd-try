#include "uart.h"

//hardware configuration
//end hardware configuration

//global defines

//global variables

//initialize uart
//high speed (HSE set)
//default: tx enabled(CTL bit 8 set), rx disabled -> CTL bit 9 cleared
//U0RX/PA0, U0TX/PA1
void uart0_init(uint32_t baudrate) {
	uint32_t tmp;
	//uart0: tx on PA1, rx on PA0
	//route clock to GPIO
	SYSCTL->RCGC2 |= (1<<0);				//0->GPIOA, 1->GPIOB, 2->GPIOC, 3->GPIOD, ...
	//while ((SYSCTL->PRGPIO & (1<<0)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PA0 for alternate function / mux group 1
	GPIOA->AFSEL |= (1<<0); 				//PA0/U0RX on alternate function
	//configure PA1 for alternate function / mux group 1
	GPIOA->AFSEL |= (1<<1); 				//PA1/U0TX on alternate function

	//route clock to UART
	SYSCTL->RCGC1 |= (1<<0);				//0->UART0, 1->UART1, ...
	//while ((SYSCTL->PRUART & (1<<0)) == 0) continue;	//1->peripheral ready, 0-> not ready

	//stop the uart
	UART0->CTL &=~(1<<0);					//1->enable uart, 0->disable uart

	//set HSE for high speed
	UART0->CTL =	(0<<15) |				//0->clear to send disabled, 1->clear to send enabled
					(0<<14) |				//0->request to send disabled, 1->request to send enabled
					(0<<11) |				//1->RTS signal received, 0->RTS not received
					(0<< 9) |				//1->enable uart receive, 0->disable uart receive
					(0<< 8) |				//1->enable uart transmit, 0->disable uart transmit
					(0<< 7) |				//0->normal operation, 1->TX/RX loop back enabled
					(1<< 5) |				//0->HSE disabled, divide by 16, 1->HSE enabled, divide by 8
					(0<< 4) |				//0->set TXRIS when UARTIFLS is met, 1->TXRIS set only after all transmitted data have been sent
					(0<< 3) | 				//0->normal operation, 1->UART in smart card mode
					(0<< 2) |				//0->low level bits transmitted as active high, 1->uart in SIR low-power mode
					(0<< 1) |				//0->normal operation, 1->IrDA SIR enabled
					(0<< 0) |				//0->uart is disabled, 1->uart is enabled
					0x00;
	if (GPIOA->AFSEL & (1<<0)) UART0->CTL |= (1<<9); else UART0->CTL &=~(1<<9);	//enable receiving if PA0 is configured for alternate function
	if (GPIOA->AFSEL & (1<<1)) UART0->CTL |= (1<<8); else UART0->CTL &=~(1<<8);	//enable transmission if PA1 is configured for alternate function

	//bit 1..6 not available on LM3S chips
	//if (UART0->CTL & (1<<5)) {				//HSE bit set -> divide by 8
	//	//calculate the integer baud rate
	//	UART0->IBRD = F_UART / baudrate / 8;
	//	//calculate the fractional baud rate = 64*fraction
	//	UART0->FBRD = (8 * F_UART / baudrate - UART0->IBRD * 64);
	//} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART0->IBRD = F_UART / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART0->FBRD = (4 * F_UART / baudrate - UART0->IBRD * 64);
	//}

	tmp = UART0->IBRD;
	tmp = UART0->FBRD;
	//configure serial parameters in LCRH
	UART0->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source - default system clock
	//UART0->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

	//clear the flags
	UART0->IM = 0x00;						//all interrupt disabled
	UART0->ICR = 0xffff;						//1->clear flags

	//start the uart
	UART0->CTL |= (1<<0);					//1->enable uart, 0->disable uart
}


//1=tx is busy
char uart0_busy(void) {
	// (UART0->FR & (1<<3)) continue;	//1->uart is busy, 0->uart is not busy
	//((UART0->FR & (1<<7)) == 0) c ontinue;	//0->transmitter has data to transmit, 1->fifo is empty
	// (UART0->FR & (1<<5)) continue;	//0->transmitter is not full, 1->fifo is full
	return (UART0->FR & (1<<3))?1:0;
}

//1=rx data available
char uart0_available(void) {
	return (UART0->FR & (1<<4))?1:0;
}

//send a char
//need to check if uart is busy first
void uart0_put(char ch) {
	UART0->DR = ch;
}

//send a string
void uart0_puts(char *str) {
	while (*str) {
		while (uart0_busy()) continue;
		uart0_put(*str++);
	}
}

//receive a char
//needs to make sure that there is data
char uart0_get(void) {
	return UART0->DR;
}

//initialize uart
//high speed (HSE set)
//default: tx enabled(CTL bit 8 set), rx disabled -> CTL bit 9 cleared
//U1RX/PD2, U1TX/PD3
void uart1_init(uint32_t baudrate) {
	//uart1: tx on PD3, rx on PD2
	//route clock to GPIO
	SYSCTL->RCGC2 |= (1<<3);				//0->GPIOA, 1->GPIOB, 2->GPIOC, 3->GPIOD, ...
	//while ((SYSCTL->PRGPIO & (1<<1)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PD2 for alternate function / mux group 1
	GPIOD->AFSEL |= (1<<2); 				//PD2/U1RX on alternate function
	//configure PD3 for alternate function / mux group 1
	GPIOD->AFSEL |= (1<<3); 				//PD3/U1TX on alternate function

	//route clock to UART
	SYSCTL->RCGC1 |= (1<<1);				//0->UART0, 1->UART1, ...
	//while ((SYSCTL->PRUART & (1<<1)) == 0) continue;	//1->peripheral ready, 0-> not ready

	//stop the uart
	UART1->CTL &=~(1<<0);					//1->enable uart, 0->disable uart

	//set HSE for high speed
	UART1->CTL =	(0<<15) |				//0->clear to send disabled, 1->clear to send enabled
					(0<<14) |				//0->request to send disabled, 1->request to send enabled
					(0<<11) |				//1->RTS signal received, 0->RTS not received
					(0<< 9) |				//1->enable uart receive, 0->disable uart receive
					(0<< 8) |				//1->enable uart transmit, 0->disable uart transmit
					(0<< 7) |				//0->normal operation, 1->TX/RX loop back enabled
					(1<< 5) |				//0->HSE disabled, divide by 16, 1->HSE enabled, divide by 8
					(0<< 4) |				//0->set TXRIS when UARTIFLS is met, 1->TXRIS set only after all transmitted data have been sent
					(0<< 3) | 				//0->normal operation, 1->UART in smart card mode
					(0<< 2) |				//0->low level bits transmitted as active high, 1->uart in SIR low-power mode
					(0<< 1) |				//0->normal operation, 1->IrDA SIR enabled
					(0<< 0) |				//0->uart is disabled, 1->uart is enabled
					0x00;
	if (GPIOB->AFSEL & (1<<0)) UART1->CTL |= (1<<9); else UART1->CTL &=~(1<<9);	//enable receiving if PB0 is configured for alternate function
	if (GPIOB->AFSEL & (1<<1)) UART1->CTL |= (1<<8); else UART1->CTL &=~(1<<8);	//enable transmission if PB1 is configured for alternate function

	//bit 1..6 not available on LM3S chips
	//if (UART1->CTL & (1<<5)) {				//HSE bit set -> divide by 8
	//	//calculate the integer baud rate
	//	UART1->IBRD = F_UART / baudrate / 8;
	//	//calculate the fractional baud rate = 64*fraction
	//	UART1->FBRD = (8 * F_UART / baudrate - UART1->IBRD * 64);
	//} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART1->IBRD = F_UART / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART1->FBRD = (4 * F_UART / baudrate - UART1->IBRD * 64);
	//}

	//configure serial parameters in LCRH
	UART1->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source - default system clock
	//UART1->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

	//clear the flags
	UART1->IM = 0x00;						//all interrupt disabled
	UART1->ICR = 0xffff;						//1->clear flags

	//start the uart
	UART1->CTL |= (1<<0);					//1->enable uart, 0->disable uart
}


//1=tx is busy
char uart1_busy(void) {
	// (UART1->FR & (1<<3)) continue;	//1->uart is busy, 0->uart is not busy
	//((UART1->FR & (1<<7)) == 0) c ontinue;	//0->transmitter has data to transmit, 1->fifo is empty
	// (UART1->FR & (1<<5)) continue;	//0->transmitter is not full, 1->fifo is full
	return (UART1->FR & (1<<3))?1:0;
}

//1=rx data available
char uart1_available(void) {
	return (UART1->FR & (1<<4))?1:0;
}

//send a char
//need to check if uart is busy first
void uart1_put(char ch) {
	UART1->DR = ch;
}

//send a string
void uart1_puts(char *str) {
	while (*str) {
		while (uart1_busy()) continue;
		uart1_put(*str++);
	}
}

//receive a char
//needs to make sure that there is data
char uart1_get(void) {
	return UART1->DR;
}

