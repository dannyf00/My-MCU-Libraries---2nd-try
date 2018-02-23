#include <pic24.h>						//we use pic24f
#include "gpio.h"
#include "uartxisr.h"                  //we use software uart

//hardware configuration
//timer settings
//output routines - potentially to allow OD output
//end hardware configuration

//global defines
//uartx protocol
//1 start bit
//8 data bits
//1 stop bit
//lsb first
#define UART_SR(dat)		(0x0200 | ((dat) << 1) | 0x0000)	//form the uart shift register. 1 start bit (low), 8 data bits, 1 stop bit (high), lsb first

//global variables
static unsigned char *_UxTX_ptr;
static unsigned char _UxTX_BUSY=0;		//0=u1 transmission done, 1=u1 transmission in process
static unsigned short _UxTX_MASK=0;		//current bit being transmitted. 0=end of transmission for the current char
static unsigned short _UxTX_buffer;		//software shift register for the transmiter

//uartx handler
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
			TxIE = 0;           //_T3IE = 0;
		}
	}
}

//reset the module
void uartx_init(unsigned long baud) {
    IO_SET(UART_PORT, UART_TX);         //tx idles high
    IO_OUT(UART_DDR, UART_TX);          //tx as output
    //IO_IN(UART_DDR, UART_TX);         //allow pull-up / od output

    tmrx_init(TMR_PS_1x, F_CPU / baud);            //set the baud rate
    tmrx_act(uartx_isr);                 //install the isr
    TxIE = 0;                        //_T3IE = 0;                         //don't start the isr yet

    _UxTX_BUSY = 0;                     //uartx isn't busy
}

//set a string
void uartx_puts(unsigned char * str) {
   	_UxTX_BUSY = 1;					//uartx is busy
	_UxTX_ptr = str;
	_UxTX_MASK = 0x0001;			//1 start bit, 8 data bits, 1 stop bits = 10 bits
	_UxTX_buffer = UART_SR(*_UxTX_ptr);	//form the buffer to be transmitted

	//clear the bits
	//TIM_ClearITPendingBit(UART_TIM, TIM_IT_Update);
	TxIF = 0;                  //_T3IF = 0;
	/* TIM IT enable */
	//TIM_ITConfig(UART_TIM, TIM_IT_Update, ENABLE);	//enable the transmission
	TxIE = 1;                  //_T3IE = 1;

}

//return status
unsigned char uartx_busy(void) {
    return _UxTX_BUSY;
}

