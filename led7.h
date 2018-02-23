#ifndef _LED7_H
#define _LED7_H

#include "gpio.h"					//we use gpio

//hardware configuration
#define SEG_PORT        PORTB       //specify the port the segment pins are attached to
#define SEG_DDR         DDRB
#define SEG_A           (1<<1)      //specify individual segment connections
#define SEG_B           (1<<2)
#define SEG_C           (1<<3)
#define SEG_D           (1<<6)
#define SEG_E           (1<<7)
#define SEG_F           (1<<5)
#define SEG_G           (1<<4)
#define SEG_DP          (1<<0)      //use 0 if not connected

#define DIG_PORT        PORTD       //specify the port the digit pins are attached to
#define DIG_DDR         DDRD
#define DIG_0           (1<<6)      //specify individual segment connections
#define DIG_1           (1<<4)
#define DIG_2           (1<<3)      //use 0 if not connected
#define DIG_3           (1<<5)
#define DIG_4           (0<<4)
#define DIG_5           (0<<4)
#define DIG_6           (0<<4)
#define DIG_7           (0<<4)

#define DIG_CNT         4           //number of digits supported
//end hardware configuration

//global defines


//global variables
extern uint8_t lRAM[DIG_CNT];              //display buffer

//initialize the module
void led7_init(void);

//update the display
void led7_display(void);
#endif
