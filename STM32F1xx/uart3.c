#include "uart3.h"								//we use uart

//for easier porting
#define UARTx				USART3				//uart module in use here

//reset the uart
//initialize uart1
void uart3_init(uint32_t baudrate) {
    //configure uart1
    //route clock to uart1
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

    UARTx->CR1 &=~(1<<13);			//'0'->disable uart, '1'->enable uart
    UARTx->CR1 = 	(0<<15) |		//'0'->oversample by 16, '1'->oversample by 8
    				(0<<13) |		//'0'->disable uart, '1'->enable uart
    				(0<<12) |		//'0'->1 start bit, 8 data bit, n stop bit, '1'->1 start bit, 9 data bit, n stop bit
    				(0<<11) |		//'0'->idle line, '1'->wake by address
    				(0<<10) |		//'0'->disable parity, '1'->enable parity
    				(0<< 9) |		//'0'->even parity, '1'->odd parity
    				(0<< 8) |		//'0'->PE interrupt disabled, '1'->pe interrupt enabled
    				(0<< 7) |		//'0'->tx empty interrupt disabled, '1'-tx empty interrupt enabled
    				(0<< 6) |		//'0'->transmission completion interrupt disabled, '1'->transmission complete interrupt enabled
    				(0<< 5) |		//'0'->rx not empty interrupt disabled, '1'->rx not empty interrupt enabled
    				(0<< 4) |		//'0'->idle interrupt disabled, '1'->idle interrupt enabled
    				(1<< 3) |		//'0'->disable tx, '1'->enable tx
    				(1<< 2) |		//'0'->disable rx, '1'->enable rx
    				(0<< 1) |		//'0'->disable receiver wake-up, '1'->enable receiver wake-up
    				(0<< 0) |		//'0'->no break char is transmitted, '1'->break char will be transmitted
    				0x00;
    UARTx->CR2 = 	(0<<14) |		//'0'->LIN mode disabled, '1'->LIN mode enabled
    				(0<<12) |		//0->1 stop bit, 1->0.5 stop bit, 2->2 stop bit, 3 -> 1.5 stop bit
    				(0<<11) |		//'0'->SCLK pin disabled, '1'->SCLK pin enabled
    				(0<<10) |		//'0'->SCLK idles low, '1'->SCLK idles high
    				(0<< 9) |		//'0'->first clock transition is first data capture edge, '1'->second clock transition is the first data capture edge
    				(0<< 8) |		//'0'->clock pulse of the last data bit is not output to the sclk pin, '1'->clock pulse of the last data bit is output to the sclk pin
    				(0<< 6) |		//'0'->LIN break detection interrupt disabled, '1'->LIN break detection interrupt enabled
    				(0<< 5) |		//'0'->LIN break detection is 10-bit, '1'->LIN break detection is 11 bit
    				(0<< 0) |		//address of the uart node
    				0x00;
    UARTx->CR3 = 	(0<<11) |		//'0'->three sample bit, '1'->one sample bit
    				(0<<10) |		//'0'->CTS interrupt disabled, '1'->CTS interrupt enabled
    				(0<< 9) |		//'0'->CTS disabled, '1'->CTS enabled
    				(0<< 8) |		//'0'->RTS interrupt disabled, '1'->RTS interrupt enabled
    				(0<< 5) |		//'0'->smartcard mode disabled, '1'->smartcard mode enabled
    				(0<< 4) |		//'0'->smartcard nack disabled, '1'->smartcard nack enabled
    				(0<< 3) |		//'0'->half duplex mode not selected, '1'->half duplex mode selected
    				(0<< 2) |		//'0'->irda normal mode, '1'->irda low-power mode
    				(0<< 1) |		//'0'->irda disabled, '1'->irda enabled
    				(0<< 0) |		//'0'->error interrupt disabled, '1'->error interrupt enabled
    				0x00;
    //set the baudrate register
    UARTx->BRR = SystemCoreClock / baudrate / 2 / ((UARTx->CR1 & (1<<15))?1:2);		//per datasheet, for OVER8=0 or 1
    UARTx->DR = 0;					//reset the data register
    UARTx->SR = 0;					//reset the data register
    //enable uart1
    UARTx->CR1 |= (1<<13);			//'0'->disable uart, '1'->enable uart

    //configure the RX-PB11/TX-PB10 pins - GPIO clock assumed enabled here previously
    IO_INFL(GPIOB, 1<<11);			//RX as floating input/AF input
    IO_AFPP(GPIOB, 1<<10);			//TX as AFPP

}

//uart1 send a char
void uart3_put(char dat) {
    //while (!(UARTx->SR & USART_SR_TXE));    	//wait for the transmission buffer to be empty
    while (uart3_busy()) continue;    			//wait for the transmission buffer to be empty
    UARTx->DR = dat;                        	//load the data buffer
    //while (!(UARTx->SR & (1<<6)));    		//wait for the transmission to complete
}

//uart1 print a string
void uart3_puts(char *str) {
	while (*str) uart3_put(*str++);
}

//uart1 returns a char
char uart3_get(void) {
    //while (!(UARTx->SR & USART_SR_RXNE));  	//wait for the receipt buffer to be empty
    return UARTx->DR;                       	//save the transmission buffer
}

//test if uart1 receiver has data available
//return true if transmission on uart1 has completed
uint8_t uart3_available(void) {
	//return (UARTx->SR & USART_SR_TC)?true:false;
	return (UARTx->SR & USART_SR_RXNE);
}

//test if uart1 is busy
uint8_t uart3_busy(void) {
    return !(UARTx->SR & USART_SR_TXE);    	//return 1 if TX buffer is empty

}
