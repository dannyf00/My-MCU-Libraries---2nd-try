//header file to drive 8 7segment led with two hc164
//segments on msb and digits on lsb

#ifndef __7SEGx8SPI_LED_H
#define __7SEGx8SPI_LED_H

//_7seg led display driver

//hardware configuration
//#define _7SEG_COMM_CATHODE										//common cathod. comment out for common anode

#define _7SEG_PORT			PORTB								//7seg connection, active low
#define _7SEG_DDR			TRISB
#define _7SEG_SCK			(1<<0)								//serial clock pin
#define _7SEG_MOSI			(1<<1)								//serial data pin
//#define _7SEG_RST			(1<<2)								//reset pin, active high. if not used, set to high

#define DIG0				(1<<0)
#define DIG1				(1<<1)
#define DIG2				(1<<2)
#define DIG3				(1<<3)
#define DIG4				(1<<4)
#define DIG5				(1<<5)
#define DIG6				(1<<6)
#define DIG7				(1<<7)
#define DIGs				(DIG0 | DIG1 | DIG2 | DIG3 | DIG4 | DIG5 | DIG6 | DIG7)

//do not change
#define _7SEG_NUMBER		8									//number of digits in the 7segment display - less than 8
//end hardware configuration

//for common cathode display - active high
#if defined(_7SEG_COMM_CATHODE)									//common cathod
#define _7SEG_ON(segs)		_7seg_write(segs)					//turn on segments, active high
#define _7SEG_OFF(segs)		_7seg_write(~(segs))				//turn off segments
#define DIG_ON(digs)		_7seg_write(~(digs))				//turn on digs, active low
#define DIG_OFF(digs)		_7seg_write(digs)					//turn off digs
#else															//common anode
#define _7SEG_ON(segs)		_7seg_write(~(segs))				//turn on segments, active low
#define _7SEG_OFF(segs)		_7seg_write(segs)					//turn off segments, active low
#define DIG_ON(digs)		_7seg_write(digs)					//turn on digs, active low
#define DIG_OFF(digs)		_7seg_write(~(digs))				//turn off digs, active low
#endif

extern unsigned char vRAM[_7SEG_NUMBER];						//for a max of 8 digits - revise if otherwise

//initialize the display
void _7seg_init(void);

//display the content of vRAM[_7SEG_NUMBER]
void _7seg_display(void);

#endif
