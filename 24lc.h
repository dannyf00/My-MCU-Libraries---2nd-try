#ifndef __24LC_H
#define __24LC_H

//interfacing with 24lc with hardware i2c
//the code can handle 8-bit and 16bit addresses: 16bit enabled if I2C_24LC_16BIT is defined.
//it also offers the option to use ack polling on the write operation
//if I2C_24LC_ACK_POLLING is defined, it uses ack polling. Otherwise, it delays I2C_24LC_WRITE_DELAY
//unsigned long used for addresses: its lower 16 bits are addresses, and bit 20.19.18 are A2.1.0, respectively

//#include <htc.h>
//#include <ioavr.h>								//we use iar avr
//#include <regx51.h>									//we use keil c51
//#include <avr/io.h>									//we use avr gcc
//#include "delay.h"
#include "gpio.h"									//we use gpio
#include "i2c_sw.h"									//we use software i2c

#define I2C_24LC_ACK_POLLING						//use ack polling for writing to the eeprom. Otherwise, comment it out

#define I2C_24LC_16BIT								//define i2c for 16 bit address chips. comment out if 8-bit address chips are used

#define I2C_24LC_ID				0xa0				//0b10100000			//address of 24LC. High 4 bits only.
#define I2C_24LC_WRITE			0x00				//write to the device. logic low
#define I2C_24LC_READ			0x01				//read from the device
#define I2C_24LC_WRITE_DELAY	10					//delay, in ms
//extern unsigned char _24LC_CS;						//24lc chip select registers A2..0

void _24lc_init(void);								//initialize 24lc

void _24lc_select(unsigned char a210x);				//update a210

void _24lc_deselect(unsigned char a210x);			//deselect a chip

unsigned char _24lc_cs_get(void);					//read back 210x

unsigned char _24lc_write(unsigned short address, unsigned char dat);	//write to 24lc

unsigned char _24lc_read(unsigned short address); 	//random read from 24lc

#endif
