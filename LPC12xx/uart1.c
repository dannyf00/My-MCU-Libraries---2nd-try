//uar1 driver for LPC17xx

#include "uart1.h"									//we use uart1

//global defines
#define UARTx					LPC_UART1			//specify uart modules used

//global variables
static uint32_t F_UART;

//initialize uart
void uart1_init(uint32_t bps) {
	uint32_t DLL, DIV, MUL, baudrate; int32_t error;			//uart parameters + error rate, x 100, for integer dividers
	uint32_t DLL_f, DIV_f, MUL_f, baudrate_f; int32_t error_f;			//uart parameters + error rate, x 100, for fractional dividers
	uint32_t DLL_f1, DIV_f1, MUL_f1, baudrate_f1; int32_t error_f1;			//uart parameters + error rate, x 100, for fractional dividers

	//configure the pins
    // Change P0.9/TXD1 and P0.8/RXD1 mode '0b010'
	LPC_IOCON->PIO0_9 = (LPC_IOCON->PIO0_9 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P0.9 to txd1
	LPC_IOCON->PIO0_8 = (LPC_IOCON->PIO0_8 &~(0b111 <<  0)) | (0b010 <<  0);	//'0b010'->P0.8 to rxd1

	//enable power to uart
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);	//12->uart0, 13=uart1, 14=adc
	LPC_SYSCON->UART1CLKDIV = 4;			//set uart clock divider. 0->disable uart
	//LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 &~(0b11<<6)) | (0b00 << 6);	//PCLKSEL0: 6=uart0, 8=uart1. 0b00=4:1,0b01=1:1, 0b10=2:1, 0b11=8:1
	//LPC_SC->PCLKSEL1 = (LPC_SC->PCLKSEL1 &~(0b11<<16)) | (0b00 << 16);	//PCLKSEL1: 16=uart2, 18=uart3. 0b00=4:1,0b01=1:1, 0b10=2:1, 0b11=8:1

	//find out F_UART
	//switch ((LPC_SYSCON->UART0CLKDIV) & 0b11) {
	//case 0b00: F_UART = F_CPU / 4; break;
	//case 0b01: F_UART = F_CPU / 1; break;
	//case 0b10: F_UART = F_CPU / 2; break;
	//case 0b11: F_UART = F_CPU / 8; break;
	//}
	F_UART = F_CPU / LPC_SYSCON->UART1CLKDIV;

    //calculate error rate for integer dividers
	DLL = F_UART / 16 / bps;						//divider, 16-bits
	DIV = 0; MUL = 1;								//set div/mul
	baudrate = F_UART / 16 * 100 / DLL / (MUL +  DIV) * MUL;	//baud rate, x100
	error = bps * 100 - baudrate;					//error, x100
	if (error < 0) error = - error;					//only compare positive numbers

	//calculate error rate for fractional dividers
	DLL_f = F_UART / 16 / bps * 10 / 15;			//estimate divider to 1.5x
	DIV_f = 0; MUL_f = 1;							//set div/mul
	baudrate_f = F_UART / 16 * 100 / DLL_f / (MUL_f + DIV_f) * MUL_f;	//baud rate, x100
	error_f = bps * 100 - baudrate_f;				//error, x100
	if (error_f < 0) error_f = -error_f;			//only compare positive numbers

	for (MUL_f1 = 2; MUL_f1 < 16; MUL_f1 ++ ) {		//MUL_f = [1..15]
		for (DIV_f1 = 0; DIV_f1 < MUL_f1; DIV_f1++) {		//DIV_f = [0..MUL_f-1]
			baudrate_f1 = F_UART / 16 * 100 / DLL_f / (MUL_f1 + DIV_f1) * MUL_f1;	//baud rate, x100
			error_f1 = bps * 100 - baudrate_f1;		//error, x100
			if (error_f1 < 0) error_f1 = -error_f1;	//only compare positive numbers
			//save the optimal dividers for fractional dividers
			if (error_f1 < error_f) {DIV_f = DIV_f1; MUL_f = MUL_f1; error_f = error_f1;}
		}
	}

	//now compare integer dividers vs. the optimal fractional dividers and find the best settings
	if (error_f < error) {DLL = DLL_f; DIV = DIV_f; MUL = MUL_f;}

	//now, DLL, DIV and MUL contain the best settings

	//now set up the uart: 8 data bits, 1 stop bit, no parity
	UARTx->IER = 0;									//disable all interrupts
	UARTx->TER = 0;									//0->disable transmission
	UARTx->ACR = 0;									//disable auto baud rate
	UARTx->LCR = 	(0b11<<0) |						//'0b11'->8-bit data
					(0<<2) |						//'0'->1stop bit, '1'->2 stop bits
					(0<<3) |						//'0'->disable parity
					(0b00<<4) |						//'0b00'->odd parity
					(0<<6) |						//'0'->disable break transmission
					(1<<7) |						//'1'->enable access to divisor latch
					0x00;
	UARTx->FDR = 	(DIV & 0b1111) |				//divider
					((MUL & 0b1111) << 4) |			//multiplier
					0x00;
	UARTx->DLL = 	(DLL & 0xff);					//DLL's lsb
	UARTx->DLM = 	(DLL >> 8) & 0xff;				//DLL's msb
	UARTx->LCR&=~(1<<7);							//disable divisor latch by clearing bit 7
	UARTx->FCR = 	(1<<0) |						//'1'->enable fifo
					(1<<1) |						//'1'->reset rx fifo - self-clearing
					(1<<2) |						//'1'->reset tx fifo - self-clearing
					(0<<3) |						//'0'->disable DMA
					(0b00<<6) |						//'0b00'->dma trigger level 0
					0x00;
	UARTx->TER = (1<<7);							//enable transmission

}


//send a char
void uart1_put(char ch) {
	while (uart1_busy()) continue;					//wait for transmission to free up
	UARTx->THR = ch;								//start transmission
}

//send a string - \null to terminate
void uart1_puts(char *str) {
	while (*str) uart1_put(*str++);					//keep sending until the end
}

//read a char
//before calling this routine, needs to test if data is available, via uart_available()
char uart1_get(void) {
	return UARTx->RBR;								//retrun a char
}

//is there data in the receiver?
uint8_t uart1_available(void) {
	return UARTx->LSR & (1<<0);						//'1'->the receiver has an unread char
}

//is the transmitter busy
uint8_t uart1_busy(void) {
	return ~UARTx->LSR & (1<<5);					//'1'@5 -> transmission buffer empty. '1'@6->transmission complete
}
