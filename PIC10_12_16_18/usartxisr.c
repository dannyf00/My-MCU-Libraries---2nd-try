#include <htc.h>					//we use picc
//#include <stm32f10x.h>
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_tim.h"			//we use timer
#include "gpio.h"					//we use own macros
#include "tmr1.h"					//we use tmr1 as baud rate generator
#include "uartxisr.h"				//we use software uart

//hardware configuration
//end hardware configuration

//global defines

//global variables
static unsigned char *_UxTX_ptr;
static unsigned char _UxTX_BUSY=0;		//0=u1 transmission done, 1=u1 transmission in process
static unsigned short _UxTX_MASK=0;		//current bit being transmitted. 0=end of transmission for the current char
static unsigned short _UxTX_buffer;		//software shift register for the transmiter
unsigned short _Ux_OFFSET;				//timer offset for uart baud rate


//softuart_isr handler
//install this in the timer
void uartx_isr(void) {
	//IO_FLP(UART_PORT, UART_TX);	//flip the pin - for debugging
	if (_UxTX_MASK!=0x0400) {				//current char isn't fully transmitted
		if (_UxTX_MASK & _UxTX_buffer) UART_SET(UART_TX);	//send '1'
		else UART_CLR(UART_TX);		//send '0'
		_UxTX_MASK = _UxTX_MASK << 1;	//shift to the next bit
	} else {						//current char has been fully transmitted
		if (*_UxTX_ptr)	{			//current char is not a null char
			_UxTX_ptr+=1;			//increment to the next character
			_UxTX_MASK = 0x0001;	//1 start bit, 8 data bits, 1 stop bits = 10 bits
			_UxTX_buffer = UART_SR(*_UxTX_ptr);	//form the buffer to be transmitted
		} else {					//current char is a null char -> end of transmission
			_UxTX_BUSY = 0;			//uartx no longer busy
			/* TIM IT enable */
			//TIM_ITConfig(UART_TIM, TIM_IT_Update, DISABLE);	//don't start the isr yet
			TMR1IE = 0;				//disable tmr1 interrupt
		}
	}
}

//reset softuart_isr
void uartx_init(unsigned long baud) {
	//set up the pin
	IO_SET(UART_PORT, UART_TX);		//tx idles high
	IO_OUT(UART_DDR, UART_TX);		//tx as output

	//set up the baud rate generator
	tmrx_init(0, F_CPU / baud);		//set up timer
	tmrx_act(uartx_isr);			//install the handler
	//clear the bits
	//TIM_ClearITPendingBit(UART_TIM, TIM_IT_Update);
	TMR1IF = 0;
	/* TIM IT enable */
	//TIM_ITConfig(UART_TIM, TIM_IT_Update, DISABLE);	//don't start the isr yet
	TMR1IE = 1;

	_UxTX_BUSY = 0;					//uartx not busy
}

//transmit a string
void uartx_puts(unsigned char * str) {
	_UxTX_BUSY = 1;					//uartx is busy
	_UxTX_ptr = str;
	_UxTX_MASK = 0x0001;			//1 start bit, 8 data bits, 1 stop bits = 10 bits
	_UxTX_buffer = UART_SR(*_UxTX_ptr);	//form the buffer to be transmitted

	//clear the bits
	//TIM_ClearITPendingBit(UART_TIM, TIM_IT_Update);
	TMR1IF = 0;			//force loading of offsets in the isr
	/* TIM IT enable */
	//TIM_ITConfig(UART_TIM, TIM_IT_Update, ENABLE);	//enable the transmission
	TMR1IE = 1;
}

//if uart is busy, return 1
unsigned char uartx_busy(void) {
	return _UxTX_BUSY;
}

