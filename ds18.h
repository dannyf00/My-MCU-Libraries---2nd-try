//code shamelessly stolen from Maxim-ic's application 126
//ds1822 picc code. 
//v0.1	only one slave attached to the master

//#include <lpc210x.h>								//we use lpc
//#include "delay.h"
//#include "one_wire.h"

#define OW_RESOLUTION_I2F	0.0625f					//12bit temperature conversion factor
#define OW_RESOLUTION_I2L	625l					//conversion from i to l
#define OW_Tconv			800						//12-bit conversion time, in ms. May need to be more than 750 for pro compilers

// ds1822 scratchpad registers 
#define DS1822_SP_TLSB  	0 
#define DS1822_SP_TMSB  	1 
#define DS1822_SP_HLIM  	2 
#define DS1822_SP_LLIM  	3 
#define DS1822_SP_CFG   	4 
#define DS1822_SP_RES0  	5 
#define DS1822_SP_RES1  	6 
#define DS1822_SP_RES2  	7 
#define DS1822_SP_CRC   	8 

// ds1822 rom registers 
#define DS1822_ROM_DEVTYPE  0 
#define DS1822_ROM_SERIAL1  1 
#define DS1822_ROM_SERIAL2  2 
#define DS1822_ROM_SERIAL3  3 
#define DS1822_ROM_SERIAL4  4 
#define DS1822_ROM_SERIAL5  5 
#define DS1822_ROM_SERIAL6  6 
#define DS1822_ROM_CRC      7 

#define ON					1
#define OFF					0

// ds1822 command set 
#define OW_CMD_SKIPROM		0xcc						//command to skip rom
//#define OW_Search			0xf0						//search rom
#define OW_CMD_READROM		0x33						//reach rom
#define OW_CMD_ALARMSEARCH	0xec						//search alarm
//function commands
#define OW_CMD_TEMPCON		0x44						//start temperature conversion
#define OW_CMD_READSPAD		0xbe						//read scratchpad
#define OW_CMD_WRITESPAD	0x4e						//write scratch pad
#define OW_CMD_COPYSPAD		0x48						//copy scratch pad

#define OW_RS_9BIT			0x1f						//=0b00011111 = 9bit
#define OW_RS_10BIT			0x3f						//=0b00111111 = 10bit
#define OW_RS_11BIT			0x5f						//=0b01011111 = 11bit
#define OW_RS_12BIT			0x7f						//=0b01111111 = 12bit

//ds1822 functions
void ds18_readspad(unsigned int ow_pin, unsigned char *gSPad);				//gSPad should point to an int array 9 deep.
signed short ds18_readtemp(unsigned int ow_pin);						//read temperature
#define ds18_readtemp_l(ow_pin)		(OW_RESOLUTION_I2L* (signed long) ds18_readtemp(ow_pin))	//return fixed temp rating. 4 decimal points. yyxxxx=yy.xxxxC
#define ds18_readtemp_f(ow_pin)		(OW_RESOLUTION_I2F* (float) ds18_readtemp(ow_pin))		//return temp, in float format
//float ds18_readtemp_f(unsigned char ow_pin);
void ds18_readrom(unsigned int ow_pin, unsigned char *gSPad);				//gSPad should point to an int array 8 deep.
void ds18_init(unsigned int ow_pin, unsigned char OW_RS);		//initialize ds18
void ds18_writespad(unsigned int ow_pin, unsigned char *gSPad);				//write to lsb, msb and conf byte of ds18
