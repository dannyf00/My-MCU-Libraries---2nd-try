/*****************************************************************
*****************************************************************/

//#include <htc.h>
#include "usart_hw.h"			//we  use hardware uart

#define USART_BUSY(flag)		do {while (!flag) continue; flag=0;} while (0)		//wait for a usart tranmission to end

//initialize usart: high baudrate (brgh=1), 16-bit baudrate (brg16=1)
//baudrate=Fxtal/(4*(spbrg+1))
//spbrg=(Fxtal/4/baudrate)-1
//tx/rx pins to be assumed in gpio mode
//data bits: 	8
//parity: 		none
//stop bits: 	1
//Xon/Xoff:		none
void usart_init(unsigned long baud_rate) 
{
	unsigned int brg=F_UART / 4 / baud_rate -1;	//good for 300 - 115.2k

	//BAUDCON
	BRG16=1;				//use 16-bit brg
	
	SYNC=0;					//asynchronous
	SPBRG=brg;				//set lower byte of brg
	SPBRGH=(brg>>8);		//set higher byte of brg

	//TXSTA REG
	TXEN=1;					//transmit enable bit
	BRGH=1;					//high speed transmission

	//RCSTA
	CREN=1;					//Enable continuous Receiver (RX)
	SPEN=1;					//serial port enabled
	
	//just waste some time
	baud_rate=10;
	while(baud_rate--);

}

void usart_putch(unsigned char ch)
{
	//Wait for TXREG Buffer to become available
	//while(!TXIF);			//wait for prior transmission to finish
	USART_BUSY(TXIF);

	//Write data
	TXREG=ch;				//load up the tx register

	//while(!TRMT);			//wait for the transmission to finish
							//don't use txif as this is not back-to-back transmission
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

unsigned char usart_getch(void)
{
	//while(!RCIF); RCIF=0;		//Wait for a byte
	USART_BUSY(RCIF);
	
	return RCREG;		//return it
}

