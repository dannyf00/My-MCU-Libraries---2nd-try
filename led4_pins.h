/* 
 * File:   led4_bits.h
 *
 * Created on April 15, 2014, 9:27 PM
 */

#ifndef LED4_PINS_H
#define	LED4_PINS_H

#include "gpio.h"

//hardware configuration
#define DISPLAY_MAX			9999						//maximum value to be displayed - modify for your application

#ifndef DISPLAY_MODE
#define DISPLAY_MODE		CC							//CC=common cathod, and CA=common anode
#endif
//end hardware configuration
 
//global defines

//global variables
extern unsigned char lRAM[];							//display buffer, to be provided by the user. 4 digit long
extern const unsigned char ledfont_num[];               //led font for numerical values, '0'..'f', including blanks
extern const unsigned char ledfont_alpha[];             //led font for alphabeta values, 'a'..'z', including blanks

//initialize the pins
void led_init(void);

//display the ledram
void led_display(void);

#endif	/* LED4_PINS_H */

