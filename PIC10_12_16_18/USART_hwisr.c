/*****************************************************************


*****************************************************************/

//#include <htc.h>
//#include "gpio.h"
#include "usart_hwisr.h"

//not used
#define USART_WAIT(flag)		while (!flag) continue; flag=0		//wait for a usart tranmission to end

//global variables
volatile unsigned char _UART_BUSY;			//uart busy flag. 0=uart not busy. 1=uart busy
volatile unsigned char *_UART_ptr;			//buffer pointer

//initialize usart: high baudrate (brgh=1), 16-bit baudrate (brg16=1)
//baudrate=Fxtal/(4*(spbrg+1))
//spbrg=(Fxtal/4/baudrate)-1
//tx/rx pins to be assumed in gpio mode
//data bits: 	8
//parity: 		none
//stop bits: 	1
//Xon/Xoff:		none
void uart_init(unsigned long baud_rate) {
	unsigned int brg=F_UART / 1 / baud_rate -1;	//good for 300 - 115.2k

	_UART_BUSY = 0;			//reset uart busy flag.
	
/*
	bit 7 CSRC: Clock Source Select bit
	Asynchronous mode:
	Don’t care
	Synchronous mode:
	1 = Master mode (clock generated internally from BRG)
	0 = Slave mode (clock from external source)
*/
	CSRC = 1;
	
/*
	bit 6 TX9: 9-bit Transmit Enable bit
	1 = Selects 9-bit transmission
	0 = Selects 8-bit transmission
*/
	TX9 = 0;					//8-bit transmission
	
/*
	bit 5 TXEN: Transmit Enable bit(1)
	1 = Transmit enabled
	0 = Transmit disabled
*/

/*
	bit 4 SYNC: EUSART Mode Select bit
	1 = Synchronous mode
	0 = Asynchronous mode
*/
	SYNC = 0;						//asynchronous mode
	
/*
	bit 3 SENDB: Send Break Character bit
	Asynchronous mode:
	1 = Send Sync Break on next transmission (cleared by hardware upon completion)
	0 = Sync Break transmission completed
	Synchronous mode:
	Don’t care
*/
	SENDB = 0;
	
/*
	bit 2 BRGH: High Baud Rate Select bit
	Asynchronous mode:
	1 = High speed
	0 = Low speed
	Synchronous mode:
	Unused in this mode
	bit 1 TRMT: Transmit Shift Register Status bit
	1 = TSR empty
	0 = TSR full
*/
	//BRGH = 1;					//high speed
	
/*
	bit 0 TX9D: Ninth bit of Transmit Data
	Can be address/data bit or a parity bit.
	Note 1: SREN/CREN overrides TXEN in Sync mode.
*/
	TX9D = 0;				//9th bit is parity
		
/*
	bit 7 SPEN: Serial Port Enable bit
	1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
	0 = Serial port disabled (held in Reset)
*/
	SPEN = 1;
	
/*
	bit 6 RX9: 9-bit Receive Enable bit
	1 = Selects 9-bit reception
	0 = Selects 8-bit reception
*/

/*
	bit 5 SREN: Single Receive Enable bit
	Asynchronous mode:
	Don’t care
	Synchronous mode ?Master:
	1 = Enables single receive
	0 = Disables single receive
	This bit is cleared after reception is complete.
	Synchronous mode ?Slave
	Don’t care
*/

/*
	bit 4 CREN: Continuous Receive Enable bit
	Asynchronous mode:
	1 = Enables receiver
	0 = Disables receiver
	Synchronous mode:
	1 = Enables continuous receive until enable bit CREN is cleared (CREN overrides SREN)
	0 = Disables continuous receive
*/

/*
	bit 3 ADDEN: Address Detect Enable bit
	Asynchronous mode 9-bit (RX9 = 1):
	1 = Enables address detection, enable interrupt and load the receive buffer when RSR<8> is set
	0 = Disables address detection, all bytes are received and ninth bit can be used as parity bit
	Asynchronous mode 8-bit (RX9 = 0):
	Don’t care
*/

/*
	bit 2 FERR: Framing Error bit
	1 = Framing error (can be updated by reading RCREG register and receive next valid byte)
	0 = No framing error
*/

/*
	bit 1 OERR: Overrun Error bit
	1 = Overrun error (can be cleared by clearing bit CREN)
	0 = No overrun error
*/

/*
	bit 0 RX9D: Ninth bit of Received Data
	This can be address/data bit or a parity bit and must be calculated by user firmware.
*/

	//BAUDCON
	BRGH=1;					//high speed transmission
	BRG16=1;				//use 16-bit brg
	SPBRG=brg;				//set lower byte of brg
	SPBRGH=(brg>>8);		//set higher byte of brg

	//RCSTA
	SPEN=1;					//serial port enabled
	SYNC=0;					//asynchronous

	//CREN=1;					//Enable continuous Receiver (RX)

	//just waste some time
	//baud_rate=10;
	//while(baud_rate--);

	//enable interrupt
	TXIF = 0;				//clear the flag
	TXIE = 0;				//not yet enable the interrupt

	//set up the receiver
	RX9 = 0;				//8 bit data
	RCIF =  0;				//clear the flag
	RCIE = 0;				//enable the reception
	CREN = 1;				//enable data reception
	
	PEIE = 1;				//enable peripheral interrupts

	//TXSTA REG
	TXEN=1;					//transmit enable bit
	
}

void uart_putch(unsigned char ch)
{
	//Wait for TXREG Buffer to become available
	//while(!TXIF);			//wait for prior transmission to finish
	USART_WAIT(TXIF);

	//Write data
	TXREG=ch;				//load up the tx register

	//while(!TRMT);			//wait for the transmission to finish
							//don't use txif as this is not back-to-back transmission
}

unsigned char uart_puts(unsigned char *str) {
	//if (_UART_BUSY) return _UART_BUSY;	//if uart is busy, bypass
	_UART_BUSY = 1;			//uart is busy
	_UART_ptr = str;		//take the string
	//TXIF = 0;				//clear the flag
	TXIE = 1;				//enable transmission interrupt
	//TXREG = *_UART_ptr;		//load up the first char. transmission starts
	return 0;				
}

/*

Writes a line of text to USART and goes to new line
The new line is Windows style CR/LF pair.

This will work on Hyper Terminal Only NOT on Linux

*/

void uart_putline(const unsigned char *ln)
{
	//USARTWriteString(ln);
	//uart_puts(ln);
	//USARTWriteString("\r\n");
	//uart_puts("\r\n");
}

unsigned char uart_getch(void)
{
	//while(!RCIF); RCIF=0;		//Wait for a byte
	USART_WAIT(RCIF);
	
	return RCREG;		//return it
}
