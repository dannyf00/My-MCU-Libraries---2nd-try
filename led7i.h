#ifndef _LED7i_H
#define _LED7i_H

#include "gpio.h"					//we use gpio

//hardware configuration
//#define SEG_PORT		PORTB	   //specify the port the segment pins are attached to
//#define SEG_DDR		PORTB
#define SEGA_PORT		PORTB	   //specify the port the segment pins are attached to
#define SEGA_DDR		DDRB
#define SEGA		   	(1<<1)	  //specify individual segment connections

#define SEGB_PORT		PORTB	   //specify the port the segment pins are attached to
#define SEGB_DDR		DDRB
#define SEGB		   	(1<<5)

#define SEGC_PORT		PORTD	   //specify the port the segment pins are attached to
#define SEGC_DDR		DDRD
#define SEGC		   	(1<<3)

#define SEGD_PORT		PORTA	   //specify the port the segment pins are attached to
#define SEGD_DDR		DDRA
#define SEGD		   	(1<<0)

#define SEGE_PORT		PORTA	   //specify the port the segment pins are attached to
#define SEGE_DDR		DDRA
#define SEGE		   	(1<<1)

#define SEGF_PORT		PORTB	   //specify the port the segment pins are attached to
#define SEGF_DDR		DDRB
#define SEGF		   	(1<<2)

#define SEGG_PORT		PORTD	   //specify the port the segment pins are attached to
#define SEGG_DDR		DDRD
#define SEGG		   	(1<<4)

#define SEGDP_PORT		PORTD	   //specify the port the segment pins are attached to
#define SEGDP_DDR		DDRD
#define SEGDP		  	(1<<2)	  //use 0 if not connected

#define DIG0_PORT		PORTB	   //specify the port the digit pins are attached to
#define DIG0_DDR		DDRB
#define DIG0		   	(1<<0)	  //specify individual segment connections

#define DIG1_PORT		PORTB	   //specify the port the digit pins are attached to
#define DIG1_DDR		DDRB
#define DIG1		   	(1<<3)

#define DIG2_PORT		PORTB	   //specify the port the digit pins are attached to
#define DIG2_DDR		DDRB
#define DIG2		   	(1<<4)	  //use 0 if not connected

#define DIG3_PORT		PORTD	   //specify the port the digit pins are attached to
#define DIG3_DDR		DDRD
#define DIG3		   	(1<<5)

#define DIG4_PORT		PORTB	   //specify the port the digit pins are attached to
#define DIG4_DDR		DDRB
#define DIG4		   	(0<<4)

#define DIG5_PORT		PORTB	   //specify the port the digit pins are attached to
#define DIG5_DDR		DDRB
#define DIG5		   	(0<<4)

#define DIG6_PORT		PORTB	   //specify the port the digit pins are attached to
#define DIG6_DDR		DDRB
#define DIG6		   	(0<<4)

#define DIG7_PORT		PORTB	   //specify the port the digit pins are attached to
#define DIG7_DDR		DDRB
#define DIG7		   	(0<<4)

#define DIG_CNT		 	4		   //number of digits supported
//end hardware configuration

//global defines


//global variables
extern uint8_t lRAM[DIG_CNT];			  //display buffer

//initialize the module
void led7_init(void);

//update the display
void led7_display(void);
#endif
