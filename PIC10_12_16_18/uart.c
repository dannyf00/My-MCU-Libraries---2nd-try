/*****************************************************************


*****************************************************************/

//#include <htc.h>
//#include "gpio.h"				//we use F_CPU
#include "uart.h"				//we use usart

#define USART_WAIT(flag)		while (!flag) continue; flag=0		//wait for a usart tranmission to end

//initialize usart: high baudrate (brgh=1), 16-bit baudrate (brg16=1)
//baudrate=Fxtal/(4*(spbrg+1))
//spbrg=(Fxtal/4/baudrate)-1
//tx/rx pins to be assumed in gpio mode
//data bits: 	8
//parity: 		none
//stop bits: 	1
//Xon/Xoff:		none
void uart_init(unsigned long baud_rate) 
{
	//SYNC=0, BRG16=1, BRGH=1 -> divisor = 4
	unsigned int brg=F_UART / 4 / baud_rate -1;	//good for 300 - 115.2k

	SPBRG=brg;				//set lower byte of brg
	SPBRGH=(brg>>8);		//set higher byte of brg

	SYNC=0;					//asynchronous
	//TXSTA REG
	BRG16 = 1; BRGH=1;		//16-bit baud rate generator
	
	//RCSTA
	SREN=0;					//0->disable single receiver
	CREN=1;					//1->Enable continuous Receiver (RX)
	
	//BAUDCON
	//BRG16=1;				//use 16-bit brg
	
	//clear interrupt flags and disable all interrupts
	RCIF = 0;
	RCIE = 0;
	
	TXIF = 0;
	TXIE = 0;
	
	TXEN=1;							//transmit enable bit

	//just waste some time
	//baud_rate=10;
	//while(baud_rate--);

	SPEN = 1;				//1->enable serial port
}

void uart_putch(char ch)
{

	while(TRMT == 0) continue;		//wait for the transmission to finish (when TRMT = 1)

	//Write data
	TXREG=ch;						//load up the tx register

	//Wait for TXREG Buffer to become available
	//while(!TXIF) continue;			//wait for prior transmission to finish - this is the faster approach
	//while(TRMT == 0) continue;		//wait for the transmission to finish (when TRMT = 1)
}

void uart_puts(char *str) {
	while(*str) {
		//Wait for TXREG Buffer to become available
		//while(!TXIF);

		//Write data
		//TXREG=(*str);

		//Next goto char
		uart_putch(*str++);	//send the ch and advance the pointer

	}
}

/*

Writes a line of text to USART and goes to new line
The new line is Windows style CR/LF pair.

This will work on Hyper Terminal Only NOT on Linux

*/

void uart_putline(char *ln)
{
	//USARTWriteString(ln);
	uart_puts(ln);
	//USARTWriteString("\r\n");
	uart_puts((char *)"\r\n");
}

unsigned char uart_getch(void)
{
	//while(!RCIF); RCIF=0;		//Wait for a byte
	//USART_WAIT(RCIF);
	//while (RCIF == 0) continue;	//wait for a byte to come in
	
	//clear rcif
	//RCIF = 0;
	
	return RCREG;		//return the data and clear RCIF
}

