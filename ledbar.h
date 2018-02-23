#ifndef _LEDBAR_H
#define _LEDBAR_H

#include <stdint.h>						//use uint_t types

//convert data into led bar (trailing 1s)

//hardware configuration
//end hardware configuration

//global defines
//#define BAR(dig)			((1<<(dig))-1)	//return full digits for "dig"

//global variables

//bar style routines
//log-linear for 8-bit data into 8-bit led
//log-linear
uint8_t dat8_bar8(uint8_t w);

//convert 8-digit dat to 16-led digits
//log-linear
uint16_t dat8_bar16(uint8_t w);

//log-linear for 10-bit data into 8-bit led
//log-linear
uint8_t dat10_bar8(uint16_t w);

//convert 10-digit dat to 12-led digits
//log-linear
uint16_t dat10_bar12(uint16_t w);

//convert 10-digit dat to 16-led digits
//log-linear
uint16_t dat10_bar16(uint16_t w);

//convert 10-digit dat to 20-led digits
//log-linear
uint32_t dat10_bar20(uint16_t w);

//convert 16-bit data to 16-led digits
//log-linear
uint16_t dat16_bar16(uint16_t w);

//dot style routines
//log-linear for 8-bit data into 8-bit led
//log-linear
uint8_t dat8_dot8(uint8_t w);

//convert 8-digit dat to 16-led digits
//log-linear
uint16_t dat8_dot16(uint8_t w);

//log-linear for 10-bit data into 8-bit led
//log-linear
uint8_t dat10_dot8(uint16_t w);

//convert 10-digit dat to 12-led digits
//log-linear
uint16_t dat10_dot12(uint16_t w);

//convert 10-digit dat to 16-led digits
//log-linear
uint16_t dat10_dot16(uint16_t w);

//convert 16-bit data to 16-led digits
//log-linear
uint16_t dat16_dot16(uint16_t w);

#endif
