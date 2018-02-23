/*****************************************************************
Most Basic USART (RS232 Serial) Communication Support File.
Simple reading and writing of data without using
Interrupts.
*****************************************************************/

#include <lpc210x.h>
#include "gpio.h"
#include "delay.h"
#include "usart_sw.h"

unsigned long _USART_DLY=USART_DLY_4800;		//4800bps is the default rate

//data bits: 	8
//parity: 		none
//stop bits: 	1
//Xon/Xoff:		none
void usart_init(unsigned long baud_rate) 
{
	IO_SET(USART_PORT, USART_Tx), IO_OUT(USART_DDR, USART_Tx);		//usart tx pin in output mode. Tx idles high
	IO_IN(USART_DDR, USART_Rx);		//usart rx pin in input mode
	//_usart_baud_rate=baud_rate;		//update the baud rate	
	//delay_ms(1);					//delay a llittle
	switch (baud_rate) {
		case USART_BR_300:			_USART_DLY=USART_DLY_300; break;
		case USART_BR_1200:			_USART_DLY=USART_DLY_1200; break;
		case USART_BR_2400:			_USART_DLY=USART_DLY_2400; break;
		case USART_BR_4800:			_USART_DLY=USART_DLY_4800; break;
		case USART_BR_9600:			_USART_DLY=USART_DLY_9600; break;
		case USART_BR_14400:		_USART_DLY=USART_DLY_14400; break;
		case USART_BR_19200:		_USART_DLY=USART_DLY_19200; break;
		case USART_BR_38400:		_USART_DLY=USART_DLY_38400; break;
		case USART_BR_57600:		_USART_DLY=USART_DLY_57600; break;
		default:					_USART_DLY=USART_DLY_9600; break;
	}
}


/* **********************************************************************
*      Function Name:  WriteUART/usart_putch                           *
*      Return Value:   void                                            *
*      Parameters:     data: byte to send out the UART                 *
*      Description:    This routine sends a byte out the TXD pin.      *
*      Special Note:   The user must provide a routine:                * 
*                      DelayTXBit():                                   *
*                        DelayTXBit should have:                       *
*                              8 Tcy for overhead                      *
*                              2 Tcy call to DelayTXBit                *
*                              ? Tcy                                   *
*                              2 Tcy for return from DelayTXBit        *
*                      = (((2*OSC_FREQ)/(4*BAUDRATE))+1)/2  Tcy        *
*********************************************************************** */

void usart_putch(unsigned char ch)
{
	unsigned char bitcount=1+8+1;			//start bit, 8 data bits, 1 stop bit
	//each 
	//RB4=0;
	IO_CLR(USART_PORT, USART_Tx);		//drive tx pin low - usart start condition
	do {
		delay_us(_USART_DLY);				//delay some time
		if (ch & 0x01) IO_SET(USART_PORT, USART_Tx);	//send a 1
		else IO_CLR(USART_PORT, USART_Tx);		//otherwise, send a 0
		ch=(ch>>1) | 0x80;				//shift out the next bit
	} while (--bitcount);
	//NOP();
}

void usart_puts(const unsigned char *str)
{
	while(*str)
	{
		//Wait for TXREG Buffer to become available
		//while(!TXIF);

		//Write data
		//TXREG=(*str);

		//Next goto char
		//str++;
		usart_putch(*str++);	//send the ch and advance the pointer
	}
}

/*
Writes a line of text to USART and goes to new line
The new line is Windows style CR/LF pair.

This will work on Hyper Terminal Only NOT on Linux
*/

void usart_putline(const unsigned char *ln)
{
	//USARTWriteString(ln);
	usart_puts(ln);
	//USARTWriteString("\r\n");
	usart_puts("\r\n");
}

/* **********************************************************************
*      Function Name:  ReadUART/usart_getch                            *
*      Return Value:   char: received data                             *
*      Parameters:     void                                            *
*      Description:    This routine waits for a start bit, and then    *
*                      reads all 8-bits.                               *
*      Special Note:   The user must provide two routines:             *
*                      DelayRXHalfBit():                               *
*                        DelayRXHalfBit should have:                   *
*                              5 Tcy for overhead                      *
*                              2 Tcy call to DelayRXHalfBit            *
*                              ? Tcy                                   *
*                              2 Tcy for return from DelayRXHalfBit    *
*                              = (((2*OSC_FREQ)/(8*BAUDRATE))+1)/2 Tcy *
*                      DelayRXBit():                                   *
*                        DelayRXBit should have:                       *
*                              10 Tcy for overhead                     *
*                              2 Tcy call to DelayRXBit                *
*                              ? Tcy                                   *
*                              2 Tcy for return from DelayRXBit        *
*                              = (((2*OSC_FREQ)/(4*BAUDRATE))+1)/2 Tcy *
*********************************************************************** */
unsigned char usart_getch(void)
{
	unsigned char bitcount=8;		//1 start bit, 8 data bits, 1 stop bit
	unsigned char uartdata=0;
	
	while (IO_GET(USART_PORT, USART_Rx)) 
		continue;	//wait for the start bit
	delay_us(_USART_DLY/2);					//delay half a bit

	do{
		//DelayRxBitUART();
		delay_us(_USART_DLY);				//delay a period
		//CARRY = RB5 ? 1:0;
		uartdata>>=1;						//shift right uartdata by 1 - incoming bit to the highest bit
		if (IO_GET(USART_PORT, USART_Rx)) uartdata |=0x80;
	} while (--bitcount);
	delay_us(_USART_DLY);					//wait for the stop bit
	return uartdata;
}
