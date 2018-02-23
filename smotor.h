#ifndef _SMOTOR_H
#define _SMOTOR_H

//driver for unipolar stepper motors

#include "gpio.h"                           //we use gpio functions

//hardware configuration
#define SMOTOR_PORT		PORTB
#define SMOTOR_DDR		TRISB
#define SMOTOR_A		(1<<1)				//phase a pin
#define SMOTOR_B		(1<<2)				//phase b pin
#define SMOTOR_C		(1<<3)				//phase c pin
#define SMOTOR_D		(1<<4)				//phase d pin
//end hardware configuration

//global defines

//global variables

//reset the pins
void smotor_init(void);

//rotate forward
void smotor_inc(void);

//rotate backward
void smotor_dec(void);

#endif
