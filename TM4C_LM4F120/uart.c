#include "uart.h"

//hardware configuration
//end hardware configuration

//global defines

//global variables

//initialize uart
//high speed (HSE set)
//default: tx enabled(CTL bit 8 set), rx disabled -> CTL bit 9 cleared
void uart0_init(uint32_t baudrate) {
	//uart0: tx on PA1, rx on PA0
	//route clock to GPIO
	SYSCTL->RCGCGPIO |= (1<<0);				//0->GPIOA, 1->GPIOB, 2->GPIOC, ...
	while ((SYSCTL->PRGPIO & (1<<0)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PA0 for alternate function / mux group 1
	//GPIOA->DEN |= (1<<0); GPIOA->AFSEL |= (1<<0); GPIOA->PCTL = (GPIOA->PCTL &~(0x0f << (0*4))) | (0x01 << (0*4));
	//configure PA1 for alternate function / mux group 1
	GPIOA->DEN |= (1<<1); GPIOA->AFSEL |= (1<<1); GPIOA->PCTL = (GPIOA->PCTL &~(0x0f << (1*4))) | (0x01 << (1*4));

	//route clock to UART
	SYSCTL->RCGCUART |= (1<<0);				//0->UART0, 1->UART1, ...
	while ((SYSCTL->PRUART & (1<<0)) == 0) continue;	//1->peripheral ready, 0-> not ready

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

	if (UART0->CTL & (1<<5)) {				//HSE bit set -> divide by 8
		//calculate the integer baud rate
		UART0->IBRD = F_UART / baudrate / 8;
		//calculate the fractional baud rate = 64*fraction
		UART0->FBRD = (8 * F_UART / baudrate - UART0->IBRD * 64);
	} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART0->IBRD = F_UART / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART0->FBRD = (4 * F_UART / baudrate - UART0->IBRD * 64);
	}

	//configure serial parameters in LCRH
	UART0->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source
	UART0->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

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
void uart1_init(uint32_t baudrate) {
	//uart1: tx on PB1, rx on PB0
	//route clock to GPIO
	SYSCTL->RCGCGPIO |= (1<<1);				//0->GPIOA, 1->GPIOB, 2->GPIOC, ...
	while ((SYSCTL->PRGPIO & (1<<1)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PB0 for alternate function / mux group 1
	//GPIOB->DEN |= (1<<0); GPIOB->AFSEL |= (1<<0); GPIOB->PCTL = (GPIOB->PCTL &~(0x0f << (0*4))) | (0x01 << (0*4));
	//configure PB1 for alternate function / mux group 1
	GPIOB->DEN |= (1<<1); GPIOB->AFSEL |= (1<<1); GPIOB->PCTL = (GPIOB->PCTL &~(0x0f << (1*4))) | (0x01 << (1*4));

	//route clock to UART
	SYSCTL->RCGCUART |= (1<<1);				//0->UART0, 1->UART1, ...
	while ((SYSCTL->PRUART & (1<<1)) == 0) continue;	//1->peripheral ready, 0-> not ready

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

	if (UART1->CTL & (1<<5)) {				//HSE bit set -> divide by 8
		//calculate the integer baud rate
		UART1->IBRD = F_UART / baudrate / 8;
		//calculate the fractional baud rate = 64*fraction
		UART1->FBRD = (8 * F_UART / baudrate - UART1->IBRD * 64);
	} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART1->IBRD = F_UART / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART1->FBRD = (4 * F_UART / baudrate - UART1->IBRD * 64);
	}

	//configure serial parameters in LCRH
	UART1->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source
	UART1->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

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

//initialize uart
//high speed (HSE set)
//default: tx enabled(CTL bit 8 set), rx disabled -> CTL bit 9 cleared
void uart2_init(uint32_t baudrate) {
	//uart2: tx on PD7, rx on PD6
	//route clock to GPIO
	SYSCTL->RCGCGPIO |= (1<<3);				//0->GPIOA, 1->GPIOB, 2->GPIOC, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PD6 for alternate function / mux group 1
	//GPIOD->DEN |= (1<<6); GPIOD->AFSEL |= (1<<6); GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (6*4))) | (0x01 << (6*4));
	//configure PD7 for alternate function / mux group 1
	GPIOD->DEN |= (1<<7); GPIOD->AFSEL |= (1<<7); GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (7*4))) | (0x01 << (7*4));

	//route clock to UART
	SYSCTL->RCGCUART |= (1<<2);				//0->UART0, 1->UART1, ...
	while ((SYSCTL->PRUART & (1<<2)) == 0) continue;	//1->peripheral ready, 0-> not ready

	//stop the uart
	UART2->CTL &=~(1<<0);					//1->enable uart, 0->disable uart

	//set HSE for high speed
	UART2->CTL =	(0<<15) |				//0->clear to send disabled, 1->clear to send enabled
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
	if (GPIOD->AFSEL & (1<<6)) UART2->CTL |= (1<<9); else UART2->CTL &=~(1<<9);	//enable receiving if PD6 is configured for alternate function
	if (GPIOD->AFSEL & (1<<7)) UART2->CTL |= (1<<8); else UART2->CTL &=~(1<<8);	//enable transmission if PD7 is configured for alternate function

	if (UART2->CTL & (1<<5)) {				//HSE bit set -> divide by 8
		//calculate the integer baud rate
		UART2->IBRD = F_UART / baudrate / 8;
		//calculate the fractional baud rate = 64*fraction
		UART2->FBRD = (8 * F_UART / baudrate - UART2->IBRD * 64);
	} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART2->IBRD = F_UART / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART2->FBRD = (4 * F_UART / baudrate - UART2->IBRD * 64);
	}

	//configure serial parameters in LCRH
	UART2->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source
	UART2->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

	//clear the flags
	UART2->IM = 0x00;						//all interrupt disabled
	UART2->ICR = 0xffff;						//1->clear flags

	//start the uart
	UART2->CTL |= (1<<0);					//1->enable uart, 0->disable uart
}


//1=tx is busy
char uart2_busy(void) {
	// (UART2->FR & (1<<3)) continue;	//1->uart is busy, 0->uart is not busy
	//((UART2->FR & (1<<7)) == 0) c ontinue;	//0->transmitter has data to transmit, 1->fifo is empty
	// (UART2->FR & (1<<5)) continue;	//0->transmitter is not full, 1->fifo is full
	return (UART2->FR & (1<<3))?1:0;
}

//1=rx data available
char uart2_available(void) {
	return (UART2->FR & (1<<4))?1:0;
}

//send a char
//need to check if uart is busy first
void uart2_put(char ch) {
	UART2->DR = ch;
}

//send a string
void uart2_puts(char *str) {
	while (*str) {
		while (uart2_busy()) continue;
		uart2_put(*str++);
	}
}

//receive a char
//needs to make sure that there is data
char uart2_get(void) {
	return UART2->DR;
}

//initialize uart
//high speed (HSE set)
//default: tx enabled(CTL bit 8 set), rx disabled -> CTL bit 9 cleared
void uart3_init(uint32_t baudrate) {
	//uart3: tx on PC7, rx on PC6
	//route clock to GPIO
	SYSCTL->RCGCGPIO |= (1<<2);				//0->GPIOA, 1->GPIOB, 2->GPIOC, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PC6 for alternate function / mux group 1
	//GPIOC->DEN |= (1<<6); GPIOC->AFSEL |= (1<<6); GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (6*4))) | (0x01 << (6*4));
	//configure PC7 for alternate function / mux group 1
	GPIOC->DEN |= (1<<7); GPIOC->AFSEL |= (1<<7); GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (7*4))) | (0x01 << (7*4));

	//route clock to UART
	SYSCTL->RCGCUART |= (1<<3);				//0->UART0, 1->UART1, ...
	while ((SYSCTL->PRUART & (1<<3)) == 0) continue;	//1->peripheral ready, 0-> not ready

	//stop the uart
	UART3->CTL &=~(1<<0);					//1->enable uart, 0->disable uart

	//set HSE for high speed
	UART3->CTL =	(0<<15) |				//0->clear to send disabled, 1->clear to send enabled
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
	if (GPIOC->AFSEL & (1<<6)) UART3->CTL |= (1<<9); else UART3->CTL &=~(1<<9);	//enable receiving if PC6 is configured for alternate function
	if (GPIOC->AFSEL & (1<<7)) UART3->CTL |= (1<<8); else UART3->CTL &=~(1<<8);	//enable transmission if PC7 is configured for alternate function

	if (UART3->CTL & (1<<5)) {				//HSE bit set -> divide by 8
		//calculate the integer baud rate
		UART3->IBRD = F_UART / baudrate / 8;
		//calculate the fractional baud rate = 64*fraction
		UART3->FBRD = (8 * F_UART / baudrate - UART3->IBRD * 64);
	} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART3->IBRD = F_UART / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART3->FBRD = (4 * F_UART / baudrate - UART3->IBRD * 64);
	}

	//configure serial parameters in LCRH
	UART3->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source
	UART3->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

	//clear the flags
	UART3->IM = 0x00;						//all interrupt disabled
	UART3->ICR = 0xffff;						//1->clear flags

	//start the uart
	UART3->CTL |= (1<<0);					//1->enable uart, 0->disable uart
}


//1=tx is busy
char uart3_busy(void) {
	// (UART3->FR & (1<<3)) continue;	//1->uart is busy, 0->uart is not busy
	//((UART3->FR & (1<<7)) == 0) c ontinue;	//0->transmitter has data to transmit, 1->fifo is empty
	// (UART3->FR & (1<<5)) continue;	//0->transmitter is not full, 1->fifo is full
	return (UART3->FR & (1<<3))?1:0;
}

//1=rx data available
char uart3_available(void) {
	return (UART3->FR & (1<<4))?1:0;
}

//send a char
//need to check if uart is busy first
void uart3_put(char ch) {
	UART3->DR = ch;
}

//send a string
void uart3_puts(char *str) {
	while (*str) {
		while (uart3_busy()) continue;
		uart3_put(*str++);
	}
}

//receive a char
//needs to make sure that there is data
char uart3_get(void) {
	return UART3->DR;
}

//initialize uart
//high speed (HSE set)
//default: tx enabled(CTL bit 8 set), rx disabled -> CTL bit 9 cleared
void uart4_init(uint32_t baudrate) {
	//uart4: tx on PC5, rx on PC4
	//route clock to GPIO
	SYSCTL->RCGCGPIO |= (1<<2);				//0->GPIOA, 1->GPIOB, 2->GPIOC, ...
	while ((SYSCTL->PRGPIO & (1<<2)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PC4 for alternate function / mux group 1
	//GPIOC->DEN |= (1<<4); GPIOC->AFSEL |= (1<<4); GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (4*4))) | (0x01 << (4*4));
	//configure PC5 for alternate function / mux group 1
	GPIOC->DEN |= (1<<5); GPIOC->AFSEL |= (1<<5); GPIOC->PCTL = (GPIOC->PCTL &~(0x0f << (5*4))) | (0x01 << (5*4));

	//route clock to UART
	SYSCTL->RCGCUART |= (1<<4);				//0->UART0, 1->UART1, ...
	while ((SYSCTL->PRUART & (1<<4)) == 0) continue;	//1->peripheral ready, 0-> not ready

	//stop the uart
	UART4->CTL &=~(1<<0);					//1->enable uart, 0->disable uart

	//set HSE for high speed
	UART4->CTL =	(0<<15) |				//0->clear to send disabled, 1->clear to send enabled
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
	if (GPIOC->AFSEL & (1<<4)) UART4->CTL |= (1<<9); else UART4->CTL &=~(1<<9);	//enable receiving if PC4 is configured for alternate function
	if (GPIOC->AFSEL & (1<<5)) UART4->CTL |= (1<<8); else UART4->CTL &=~(1<<8);	//enable transmission if PC5 is configured for alternate function

	if (UART4->CTL & (1<<5)) {				//HSE bit set -> divide by 8
		//calculate the integer baud rate
		UART4->IBRD = F_UART / baudrate / 8;
		//calculate the fractional baud rate = 64*fraction
		UART4->FBRD = (8 * F_UART / baudrate - UART4->IBRD * 64);
	} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART4->IBRD = F_UART / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART4->FBRD = (4 * F_UART / baudrate - UART4->IBRD * 64);
	}

	//configure serial parameters in LCRH
	UART4->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source
	UART4->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

	//clear the flags
	UART4->IM = 0x00;						//all interrupt disabled
	UART4->ICR = 0xffff;						//1->clear flags

	//start the uart
	UART4->CTL |= (1<<0);					//1->enable uart, 0->disable uart
}


//1=tx is busy
char uart4_busy(void) {
	// (UART4->FR & (1<<3)) continue;	//1->uart is busy, 0->uart is not busy
	//((UART4->FR & (1<<7)) == 0) c ontinue;	//0->transmitter has data to transmit, 1->fifo is empty
	// (UART4->FR & (1<<5)) continue;	//0->transmitter is not full, 1->fifo is full
	return (UART4->FR & (1<<3))?1:0;
}

//1=rx data available
char uart4_available(void) {
	return (UART4->FR & (1<<4))?1:0;
}

//send a char
//need to check if uart is busy first
void uart4_put(char ch) {
	UART4->DR = ch;
}

//send a string
void uart4_puts(char *str) {
	while (*str) {
		while (uart4_busy()) continue;
		uart4_put(*str++);
	}
}

//receive a char
//needs to make sure that there is data
char uart4_get(void) {
	return UART4->DR;
}

//initialize uart
//high speed (HSE set)
//default: tx enabled(CTL bit 8 set), rx disabled -> CTL bit 9 cleared
void uart5_init(uint32_t baudrate) {
	//uart5: tx on PE5, rx on PE4
	//route clock to GPIO
	SYSCTL->RCGCGPIO |= (1<<4);				//0->GPIOA, 1->GPIOB, 2->GPIOC, ...
	while ((SYSCTL->PRGPIO & (1<<4)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PE4 for alternate function / mux group 1
	//GPIOE->DEN |= (1<<4); GPIOE->AFSEL |= (1<<4); GPIOE->PCTL = (GPIOE->PCTL &~(0x0f << (4*4))) | (0x01 << (4*4));
	//configure PE5 for alternate function / mux group 1
	GPIOE->DEN |= (1<<5); GPIOE->AFSEL |= (1<<5); GPIOE->PCTL = (GPIOE->PCTL &~(0x0f << (5*4))) | (0x01 << (5*4));

	//route clock to UART
	SYSCTL->RCGCUART |= (1<<5);				//0->UART0, 1->UART1, ...
	while ((SYSCTL->PRUART & (1<<5)) == 0) continue;	//1->peripheral ready, 0-> not ready

	//stop the uart
	UART5->CTL &=~(1<<0);					//1->enable uart, 0->disable uart

	//set HSE for high speed
	UART5->CTL =	(0<<15) |				//0->clear to send disabled, 1->clear to send enabled
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
	if (GPIOE->AFSEL & (1<<4)) UART5->CTL |= (1<<9); else UART5->CTL &=~(1<<9);	//enable receiving if PE4 is configured for alternate function
	if (GPIOE->AFSEL & (1<<5)) UART5->CTL |= (1<<8); else UART5->CTL &=~(1<<8);	//enable transmission if PE5 is configured for alternate function

	if (UART5->CTL & (1<<5)) {				//HSE bit set -> divide by 8
		//calculate the integer baud rate
		UART5->IBRD = F_UART / baudrate / 8;
		//calculate the fractional baud rate = 64*fraction
		UART5->FBRD = (8 * F_UART / baudrate - UART5->IBRD * 64);
	} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART5->IBRD = F_UART / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART5->FBRD = (4 * F_UART / baudrate - UART5->IBRD * 64);
	}

	//configure serial parameters in LCRH
	UART5->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source
	UART5->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

	//clear the flags
	UART5->IM = 0x00;						//all interrupt disabled
	UART5->ICR = 0xffff;						//1->clear flags

	//start the uart
	UART5->CTL |= (1<<0);					//1->enable uart, 0->disable uart
}


//1=tx is busy
char uart5_busy(void) {
	// (UART5->FR & (1<<3)) continue;	//1->uart is busy, 0->uart is not busy
	//((UART5->FR & (1<<7)) == 0) c ontinue;	//0->transmitter has data to transmit, 1->fifo is empty
	// (UART5->FR & (1<<5)) continue;	//0->transmitter is not full, 1->fifo is full
	return (UART5->FR & (1<<3))?1:0;
}

//1=rx data available
char uart5_available(void) {
	return (UART5->FR & (1<<4))?1:0;
}

//send a char
//need to check if uart is busy first
void uart5_put(char ch) {
	UART5->DR = ch;
}

//send a string
void uart5_puts(char *str) {
	while (*str) {
		while (uart5_busy()) continue;
		uart5_put(*str++);
	}
}

//receive a char
//needs to make sure that there is data
char uart5_get(void) {
	return UART5->DR;
}

//initialize uart
//high speed (HSE set)
//default: tx enabled(CTL bit 8 set), rx disabled -> CTL bit 9 cleared
void uart6_init(uint32_t baudrate) {
	//uart6: tx on PD5, rx on PD4
	//route clock to GPIO
	SYSCTL->RCGCGPIO |= (1<<3);				//0->GPIOA, 1->GPIOB, 2->GPIOC, ...
	while ((SYSCTL->PRGPIO & (1<<3)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PD4 for alternate function / mux group 1
	//GPIOD->DEN |= (1<<4); GPIOD->AFSEL |= (1<<4); GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (4*4))) | (0x01 << (4*4));
	//configure PD5 for alternate function / mux group 1
	GPIOD->DEN |= (1<<5); GPIOD->AFSEL |= (1<<5); GPIOD->PCTL = (GPIOD->PCTL &~(0x0f << (5*4))) | (0x01 << (5*4));

	//route clock to UART
	SYSCTL->RCGCUART |= (1<<6);				//0->UART0, 1->UART1, ...
	while ((SYSCTL->PRUART & (1<<6)) == 0) continue;	//1->peripheral ready, 0-> not ready

	//stop the uart
	UART6->CTL &=~(1<<0);					//1->enable uart, 0->disable uart

	//set HSE for high speed
	UART6->CTL =	(0<<15) |				//0->clear to send disabled, 1->clear to send enabled
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
	if (GPIOD->AFSEL & (1<<4)) UART6->CTL |= (1<<9); else UART6->CTL &=~(1<<9);	//enable receiving if PD4 is configured for alternate function
	if (GPIOD->AFSEL & (1<<5)) UART6->CTL |= (1<<8); else UART6->CTL &=~(1<<8);	//enable transmission if PD5 is configured for alternate function

	if (UART6->CTL & (1<<5)) {				//HSE bit set -> divide by 8
		//calculate the integer baud rate
		UART6->IBRD = F_UART / baudrate / 8;
		//calculate the fractional baud rate = 64*fraction
		UART6->FBRD = (8 * F_UART / baudrate - UART6->IBRD * 64);
	} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART6->IBRD = F_UART / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART6->FBRD = (4 * F_UART / baudrate - UART6->IBRD * 64);
	}

	//configure serial parameters in LCRH
	UART6->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source
	UART6->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

	//clear the flags
	UART6->IM = 0x00;						//all interrupt disabled
	UART6->ICR = 0xffff;						//1->clear flags

	//start the uart
	UART6->CTL |= (1<<0);					//1->enable uart, 0->disable uart
}


//1=tx is busy
char uart6_busy(void) {
	// (UART6->FR & (1<<3)) continue;	//1->uart is busy, 0->uart is not busy
	//((UART6->FR & (1<<7)) == 0) c ontinue;	//0->transmitter has data to transmit, 1->fifo is empty
	// (UART6->FR & (1<<5)) continue;	//0->transmitter is not full, 1->fifo is full
	return (UART6->FR & (1<<3))?1:0;
}

//1=rx data available
char uart6_available(void) {
	return (UART6->FR & (1<<4))?1:0;
}

//send a char
//need to check if uart is busy first
void uart6_put(char ch) {
	UART6->DR = ch;
}

//send a string
void uart6_puts(char *str) {
	while (*str) {
		while (uart6_busy()) continue;
		uart6_put(*str++);
	}
}

//receive a char
//needs to make sure that there is data
char uart6_get(void) {
	return UART6->DR;
}


//initialize uart
//high speed (HSE set)
//default: tx enabled(CTL bit 8 set), rx disabled -> CTL bit 9 cleared
void uart7_init(uint32_t baudrate) {
	//uart7: tx on PE1, rx on PE0
	//route clock to GPIO
	SYSCTL->RCGCGPIO |= (1<<4);				//0->GPIOA, 1->GPIOB, 2->GPIOC, ...
	while ((SYSCTL->PRGPIO & (1<<4)) == 0) continue;	//1->peripheral ready, 0-> not ready
	//configure PE0 for alternate function / mux group 1
	//GPIOE->DEN |= (1<<0); GPIOE->AFSEL |= (1<<0); GPIOE->PCTL = (GPIOE->PCTL &~(0x0f << (0*4))) | (0x01 << (0*4));
	//configure PE1 for alternate function / mux group 1
	GPIOE->DEN |= (1<<1); GPIOE->AFSEL |= (1<<1); GPIOE->PCTL = (GPIOE->PCTL &~(0x0f << (1*4))) | (0x01 << (1*4));

	//route clock to UART
	SYSCTL->RCGCUART |= (1<<7);				//0->UART0, 1->UART1, ...
	while ((SYSCTL->PRUART & (1<<7)) == 0) continue;	//1->peripheral ready, 0-> not ready

	//stop the uart
	UART7->CTL &=~(1<<0);					//1->enable uart, 0->disable uart

	//set HSE for high speed
	UART7->CTL =	(0<<15) |				//0->clear to send disabled, 1->clear to send enabled
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
	if (GPIOE->AFSEL & (1<<0)) UART7->CTL |= (1<<9); else UART7->CTL &=~(1<<9);	//enable receiving if PE0 is configured for alternate function
	if (GPIOE->AFSEL & (1<<1)) UART7->CTL |= (1<<8); else UART7->CTL &=~(1<<8);	//enable transmission if PE1 is configured for alternate function

	if (UART7->CTL & (1<<5)) {				//HSE bit set -> divide by 8
		//calculate the integer baud rate
		UART7->IBRD = F_UART / baudrate / 8;
		//calculate the fractional baud rate = 64*fraction
		UART7->FBRD = (8 * F_UART / baudrate - UART7->IBRD * 64);
	} else {								//HSE bit cleared -> divide by 16
		//calculate the integer baud rate
		UART7->IBRD = F_UART / baudrate / 16;
		//calculate the fractional baud rate = 64*fraction
		UART7->FBRD = (4 * F_UART / baudrate - UART7->IBRD * 64);
	}

	//configure serial parameters in LCRH
	UART7->LCRH = 	(0<<7) |				//0->stick parity disabled, 1->stick parity enabled
					(3<<5) |				//word length. 0->5bit, 1->6bit, 2->7bit, 3->8bit
					(1<<4) |				//0->fifo disabled, 1->fifo enabled
					(0<<3) |				//0->1 stop bit, 1->two stop bits
					(0<<2) |				//0->odd parity, 1->even parity. no effect if parity is disabled (bit 1 cleared)
					(0<<1) |				//0->parity disabled, 1->parity enabled
					(0<<0) | 				//0->normal use, 1->send break
					0x00;

	//configure the uart clock source
	UART7->CC = 0x00;						//0x00->system clock used, 0x05->PIOSC used

	//clear the flags
	UART7->IM = 0x00;						//all interrupt disabled
	UART7->ICR = 0xffff;						//1->clear flags

	//start the uart
	UART7->CTL |= (1<<0);					//1->enable uart, 0->disable uart
}


//1=tx is busy
char uart7_busy(void) {
	// (UART7->FR & (1<<3)) continue;	//1->uart is busy, 0->uart is not busy
	//((UART7->FR & (1<<7)) == 0) c ontinue;	//0->transmitter has data to transmit, 1->fifo is empty
	// (UART7->FR & (1<<5)) continue;	//0->transmitter is not full, 1->fifo is full
	return (UART7->FR & (1<<3))?1:0;
}

//1=rx data available
char uart7_available(void) {
	return (UART7->FR & (1<<4))?1:0;
}

//send a char
//need to check if uart is busy first
void uart7_put(char ch) {
	UART7->DR = ch;
}

//send a string
void uart7_puts(char *str) {
	while (*str) {
		while (uart7_busy()) continue;
		uart7_put(*str++);
	}
}

//receive a char
//needs to make sure that there is data
char uart7_get(void) {
	return UART7->DR;
}

