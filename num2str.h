#ifndef _NUM2STR_H
#define _NUM2STR_H

//reference: http://www.eevblog.com/forum/microcontrollers/adcdac-conversion-to-'decimal'-best-practices/

#include <stdint.h>

//math benchmarking

//global defines

//global variables

//convert a 10-bit digit to decimal string
//str = dat * 1000 / 2^10(=1024)
void num10_str(uint8_t *str, uint16_t dat);

//convert a 12-bit digit to decimal string
//str = dat * 1000 / 2^12(=4096)
void num12_str(uint8_t *str, uint16_t dat);

//convert a 14-bit digit to decimal string
//str = dat * 1000 / 2^12(=16384)
void num14_str(uint8_t *str, uint16_t dat);

//convert a 16-bit digit to decimal string
//str = dat * 1000 / 2^16(=65536)
void num16_str(uint8_t *str, uint32_t dat);


//convert a 18-bit digit to decimal string
//str = dat * 1000 / 2^18(=262144)
void num18_str(uint8_t *str, uint32_t dat);

//convert a 20-bit digit to decimal string
//str = dat * 1000 / 2^20(=1,048,576)
void num20_str(uint8_t *str, uint32_t dat);

//convert a 22-bit digit to decimal string
//str = dat * 1000 / 2^22(=4,194,304)
void num22_str(uint8_t *str, uint32_t dat);

//convert a 24-bit digit to decimal string
//str = dat * 1000 / 2^24(=16,777,216)
void num24_str(uint8_t *str, uint32_t dat);

#endif
