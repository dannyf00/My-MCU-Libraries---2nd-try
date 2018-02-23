#include "uart1.h"								//we use uart

//for easier porting
#define UARTx				USART1				//uart module in use here

//global variables
//static uint8_t _UxTX_BUSY = 0;		//0->uart not busy, 1->uart busy
//static char *_UxTX_ptr;				//transmission string


//reset the uart
//initialize uart1
void uart1_init(uint32_t baudrate) {
	uint16_t uartdiv;

	//configure uart1
    //route clock to uart1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    UARTx->CR1 &=~(1<<0);			//'0'->disable uart, '1'->enable uart
    UARTx->CR1 =	(0<<28) | (0<<12) |	//0b00->1 start bit, 8 data bits, n stop bit; 0b01->1 start bit, 9 data bits, n stop bit, 0b10->1 start bit 7 data bits, n stop bit
    				(0<<27) |		//0->disable end of block interrupt
    				(0<<26) |		//0->receiver timeout interrupt disabled
    				(0x00<<21) |	//0b00000->driver enable assertion time
    				(0x00<<16) |	//0b00000->driver enable disassertion time
    				(0<<15) |		//0->oversampling by 16
    				(0<<14) |		//0->character match interrupt disabled
    				(0<<13) |		//0->receiver in active mode permanently
    				//bit 12 set earlier
    				(0<<11) |		//0->idle line to wake up uart
    				(0<<10) |		//0->no parity
    				(0<<9) |		//0->even parity
    				(0<<8) |		//0->disable PE interrupt
    				(0<<7) |		//0->disable txie)
    				(0<<6) |		//0->disable transmission complete interrupt
    				(0<<5) |		//0->disable receiver buffer not empty interrupt
    				(0<<4) |		//0->disable idle interrupt
    				(1<<3) |		//0->transmitter disabled, 1->transmitter enabled
    				(1<<2) |		//0->receiver disabled, 1->receiver enabled
    				//bit 1 reserved
    				(0<<0) |		//0->disable uart, 1->enable uart
    				0x00;
    UARTx->CR2 = 	(0x00<<28) |	//address of the uart
    				(0x00<<24) |	//address of the uart
    				(0<<23) |		//0->disable receiver time out
    				(0x00<<21) |	//00->measurement of the start bit used to detect baud rate
    				(0<<20) |		//auto baud rate disabled
    				(0<<19) |		//0->data bit 0 first
    				(0<<18) |		//0->data transmitted / received in positive logic
    				(0<<17) |		//0->tx in positive logic
    				(0<<16) |		//0->rx in positive logic
    				(0<<15) |		//0->tx/rx pins not swapped, 1->tx/rx pins swapped
    				(0x00<<12) |	//00->1 stop bit, 10->2 stop bit, 11->1.5 stop bit
    				(0<<11) |		//0->sclk disabled
    				(0<<10) |		//0->sclk idles low
    				(0<<9) |		//0->clock on first data capture
    				(0<<8) |		//0->clock on the last bit is not data pulse
    				(0<<4) |		//0->4 bit address detection
    				0x00;
    UARTx->CR3 =	(0<<15) |		//0->driver enable signal active high
    				(0<<14) |		//0->disable driver more
    				0x00;			//reset value
    //set the baudrate register
    uartdiv = F_UART / baudrate;
    if (UARTx->CR1 & (1<<15)) {		//oversample by 8
    	uartdiv = uartdiv * 2;
    	uartdiv = 	(uartdiv &~0x000f) |	//clear lowest 4 bits
    				(1<<3) |			//bit 3 is always set
    				((uartdiv >> 1) & 0x07);	//keep the lowest 3 bits
    }
    UARTx->BRR = uartdiv;
    //UARTx->BRR = F_UART / baudrate * ((UARTx->CR1 & (1<<15))?2:1);		//per datasheet, for OVER8=0 or 1

    //UARTx->DR = 0;					//reset the data register
    //UARTx->SR = 0;					//reset the data register

    //enable uart1
    UARTx->CR1 |= (1<<0);			//'0'->disable uart, '1'->enable uart

    //configure the TX-PA9/RX-PA10 pins - GPIO clock assumed enabled here previously
    //RX as floating input/AF input, AF1
    IO_INFL(GPIOA, 1<<10); GPIOA->AFR[1] = (GPIOA->AFR[1] &~(0x0f << (4 * (10-8)))) | (1<<(4 * (10-8)));
	//TX as AFPP, AF1
    IO_AFPP(GPIOA, 1<< 9); GPIOA->AFR[1] = (GPIOA->AFR[1] &~(0x0f << (4 * ( 9-8)))) | (1<<(4 * ( 9-8)));

}

//uart1 send a char
void uart1_put(char dat) {
    //while (!(UARTx->SR & USART_SR_TXE));    	//wait for the transmission buffer to be empty
    while (uart1_busy()) continue;    			//wait for the transmission buffer to be empty
    UARTx->TDR = dat;                        	//load the data buffer
    //while (!(UARTx->SR & (1<<6)));    		//wait for the transmission to complete
}

//uart1 print a string
void uart1_puts(char *str) {
	while (*str) uart1_put(*str++);
}

//uart1 returns a char
char uart1_get(void) {
    //while (!(UARTx->SR & USART_SR_RXNE));  	//wait for the receipt buffer to be empty
    return UARTx->RDR;                       	//save the transmission buffer
}

//test if uart1 receiver has data available
//return true if transmission on uart1 has completed
uint8_t uart1_available(void) {
	//return (UARTx->SR & USART_SR_TC)?true:false;
	return (UARTx->ISR & USART_ISR_RXNE);
}

//test if uart1 is busy
uint8_t uart1_busy(void) {
    return !(UARTx->ISR & USART_ISR_TXE);    	//return 1 if TX buffer is empty

}
