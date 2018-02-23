#ifndef _7SEG_LCD_H
#define _7SEG_LCD_H

//header file for 7seg lcd (upto 4 digits)

//hardware configuration
#define COM_PORT			PORTA
#define COM_DDR				TRISA
#define COM0				(1<<0)			//com0

#define DIG1_PORT			PORTB
#define DIG1_DDR			TRISB
#define DIG1s				0xff			//segments for digi1

#define DIG2_PORT			PORTC
#define DIG2_DDR			TRISC
#define DIG2s				0xff			//segments for digi2

//#define DIG3_PORT			P1
#define DIG3_DDR			P1
#define DIG3s				0xff			//segments for digi3

//#define DIG4_PORT			P0
#define DIG4_DDR			P0
#define DIG4s				0xff			//segments for digi4

#define _7SEG_NUMBER		3				//number of 7segment display
//end hardware configuration

//global variable
extern volatile unsigned char vRAM[8];						//display buffer

//reset the 7segment display
void _7seg_init(void);

//display vram[_7SEG_NUMBER]
void _7seg_display(void);

#endif
