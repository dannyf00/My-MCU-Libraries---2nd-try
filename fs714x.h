#ifndef FS714X_H_INCLUDED
#define FS714X_H_INCLUDED

#include "gpio.h"
#include "i2c_sw.h"						//we use software i2c

//hardware configuration
#define FS714x_ADDR			0xb0		//default FS714x address, 0b1011 0xx0.
//modify if A1..0 is set
//end hardware configuration

//global defines


//global variables

//select the device i2c address (to write to registers or eeprom)
void fs714x_select(unsigned char i2c_addr);

//read fs714x a register
unsigned char fs714x_read(unsigned char fs714x_reg);

//write fs714x register
unsigned char fs714x_write(unsigned char fs714x_reg, unsigned char dat);

//initialize fs714x
void fs714x_init(void);

//Fout = Fref * Nf / Fr / (Np1 * Np2 * Np3)
//set Nf - feedback divider (FBKDIV), 14 bits
void fs714x_setNf(unsigned short Nf);

//get Nf
unsigned short fs714x_getNf(unsigned short *Nf);

//set Nr - reference divider (REFDIV), 13 bits
void fs714x_setNr(unsigned short Nr);

//get Nr
unsigned short fs714x_getNr(unsigned short *Nr);

//set Np1..2
void fs714x_setNp(unsigned char Np1, unsigned char Np2, unsigned char Np3);

//get Np1..2
void fs714x_getNp(unsigned char *Np1, unsigned char *Np2, unsigned char *Np3);

//turn off fs714x(set SHUT1 | SETUT2)
void fs714x_off(void);

//turn on fs714x(clear SHUT1 | SETUT2)
void fs714x_on(void);

#endif // FS714X_H_INCLUDED
