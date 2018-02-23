#ifndef BIT_REVERSE_H_INCLUDED
#define BIT_REVERSE_H_INCLUDED

//#include <avr/io.h>							//we use gcc-avr
#include "gpio.h"
#include "delay.h"							//we use software delays

//hardware configuration
//end hardware configuration

//global defines

//global variables

//inverse bit orders - 4 bits at a time
//Index 1==0b0001 => 0b1000
//Index 7==0b0111 => 0b1110
//etc
//51us@1mips attiny85
uint8_t reverse4_lut(uint8_t b);

//inverse bit orders - 72us@1mips attiny85
uint8_t reverse8_lut(uint8_t b);

//inverse bit orders - 186us@1MIPS attiny85
uint16_t reverse16_lut(uint16_t b);

//reverse bit order - 32 bits - 434u@1MIPS attiny85
uint32_t reverse32_lut(uint32_t x);
//return the lowest 4 bits, via look-up table
//86us@1mips attiny85
uint8_t reverse4(uint8_t b);

//inverse bit orders - 100us@1MIPS attiny85
uint8_t reverse8(uint8_t b);

//inverse bit orders - 127us@1MIPS attiny85
uint16_t reverse16(uint16_t b);

//reverse bit order - 32 bits - 300u@1MIPS attiny85
uint32_t reverse32(uint32_t x);

#endif // BIT_REVERSE_H_INCLUDED
