/*****************************************************************
Most Basic USART (RS232 Serial) Communication Support File.
Simple reading and writing of data without using
Interrupts.

BAUD RATE:57600 Bits per Second
CRYSTAL Frequency: 20MHz

Target Chip: PIC18F4520
Target Compiler: HI-TECH C For PIC18 (http://www.htsoft.com/)
Project: MPLAP Project File

Copyright (c) 2008-2010
eXtreme Electronics, India
www.eXtremeElectronics.co.in

*****************************************************************/
//hardware configuration
#define USART_PORT			IOPIN		//usart pins on port
#define USART_DDR			IODIR		//output direction register for usart pins
#define USART_Tx			(1<<6)		//usart transmit pin
#define USART_Rx			(1<<7)		//usart receive pin

#define Mhz					000000ul	//suffix for Mhz
//#define USART_Fxtal			8Mhz		//crystal frequency
#define USART_BR_300		300ul		//buadrate=300
#define USART_BR_1200		1200ul		//buadrate=300
#define USART_BR_2400		2400ul		//buadrate=300
#define USART_BR_4800		4800ul		//buadrate=300
#define USART_BR_9600		9600ul		//buadrate=300
#define USART_BR_14400		14400ul		//buadrate=300
#define USART_BR_19200		19200ul		//buadrate=300
#define USART_BR_38400		38400ul		//buadrate=300
#define USART_BR_57600		57600ul		//buadrate=300
#define USART_BR_115200		115200ul		//buadrate=300

//delay parameters
#define USART_DLY_300		3300ul
#define USART_DLY_1200		780ul
#define USART_DLY_2400		394ul
#define USART_DLY_4800		196ul
#define USART_DLY_9600		99ul
#define USART_DLY_14400		66ul
#define USART_DLY_19200		49ul
#define USART_DLY_38400		24ul
#define USART_DLY_57600		15ul

//initiate the hardware usart
void usart_init(unsigned long baud_rate);

void usart_putch(unsigned char ch);

void usart_puts(const unsigned char *str);

/*

Writes a line of text to USART and goes to new line
The new line is Windows style CR/LF pair.

This will work on Hyper Terminal Only NOT on Linux

*/

void usart_putline(const unsigned char *ln);

//read a char from usart
unsigned char usart_getch(void);
