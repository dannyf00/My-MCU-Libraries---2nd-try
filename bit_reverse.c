//#include "gpio.h"
//#include "delay.h"							//we use software delays
#include "bit_reverse.h"				//we use bit reversal routines

//hardware configuration
//end hardware configuration

//global defines

//global variables
//look-up table for 4 bit reversal, in place
static unsigned char r4_lut[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };

//return the lowest 4 bits, via look-up table
uint8_t reverse4_lut(uint8_t b) {
	return r4_lut[b&0x0f];
}

//inverse 8bit orders - 4 bits at a time
//Index 1==0b0001 => 0b1000
//Index 7==0b0111 => 0b1110
//etc
uint8_t reverse8_lut(uint8_t b) {
   // Reverse the top and bottom nibble then swap them.
   return (r4_lut[b&0b1111] << 4) | r4_lut[b>>4];
}

//inverse 16bit orders - 4 bits at a time
//Index 1==0b0001 => 0b1000
//Index 7==0b0111 => 0b1110
//etc
uint16_t reverse16_lut(uint16_t b) {
   // Reverse the top and bottom nibble then swap them.
   return (reverse8_lut(b&0x00ff) << 4) | reverse8_lut(b >> 8);
}

//inverse 16bit orders - 4 bits at a time
//Index 1==0b0001 => 0b1000
//Index 7==0b0111 => 0b1110
//etc
uint32_t reverse32_lut(uint32_t b) {
   // Reverse the top and bottom nibble then swap them.
   return (reverse16_lut(b & 0xffff) << 4) | reverse16_lut(b >> 16);
}

//reverse 32 bits - lowest 4 bits effective
uint8_t reverse4(uint8_t b) {
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;	//swap negibhoring 1 bit
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;	//swap neghboring 2 bits
   //b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;	//swap neghboring 4 bits
   return b;
}

//inverse bit orders
uint8_t reverse8(uint8_t b) {
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   return b;
}

//reverse bit order - 16 bits
uint16_t reverse16(uint16_t x) {
    x = (((x & 0xaaaa) >> 1) | ((x & 0x5555) << 1));
    x = (((x & 0xcccc) >> 2) | ((x & 0x3333) << 2));
    x = (((x & 0xf0f0) >> 4) | ((x & 0x0f0f) << 4));
    x = (((x & 0xff00) >> 8) | ((x & 0x00ff) << 8));
    return x;
	//return (reverse8(b) << 8) | reverse8(b>>8);
}
//reverse bit order - 32 bits
uint32_t reverse32(uint32_t x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    return((x >> 16) | (x << 16));
}
