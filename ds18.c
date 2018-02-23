//code shamelessly stolen from Maxim-ic's application 126
//not working
//#include <lpc210x.h>								//we use lpc
#include <regx51.h>									//we use keil c51
#include "delay.h"
#include "one_wire.h"
#include "ds18.h"

//not yet working
void ds18_init(unsigned int ow_pin, unsigned char OW_RS) {		//initialize ds18
	unsigned char spad[9];

	ds18_readspad(ow_pin, spad);					//read the scratchpad
	spad[4]=OW_RS;									//put in the configuration words
	ds18_writespad(ow_pin, spad);					//write lsb, msb and configuration
	//ow_init(ow_pin);								//reset the device to effect the transmission
}


void ds18_readspad(unsigned int ow_pin, unsigned char *gSPad) {		//gSPad should point to an int array 9 deep.
	unsigned char k;
	//ow_init(ow_pin);						//reset the one-wire
	//ow_write(ow_pin, OW_CMD_SKIPROM);		//issue skip rom command
	//ow_write(ow_pin, OW_CMD_TEMPCON);		//start OW_TempConversion;
	//delay_ms(OW_Tconv);						//delay 750ms
	ow_init(ow_pin);						//reset the bus
	ow_write(ow_pin, OW_CMD_SKIPROM);		//issue skip rom again why?
	ow_write(ow_pin, OW_CMD_READSPAD);		//read scratchpad
	for (k=0; k<9; k++)						//read the 9 bytes;
		gSPad[k]=ow_read(ow_pin);
}


void ds18_writespad(unsigned int ow_pin, unsigned char *gSPad) {		//gSPad should point to an int array 9 deep.
	unsigned char k;
	//ow_init(ow_pin);						//reset the one-wire
	//ow_write(ow_pin, OW_CMD_SKIPROM);		//issue skip rom command
	//ow_write(ow_pin, OW_CMD_TEMPCON);		//start OW_TempConversion;
	//delay_ms(OW_Tconv);						//delay 750ms
	ow_init(ow_pin);						//reset the bus
	ow_write(ow_pin, OW_CMD_SKIPROM);		//issue skip rom again why?
	ow_write(ow_pin, OW_CMD_WRITESPAD);		//read scratchpad
	ow_write(ow_pin, gSPad[2]);				//write Th
	ow_write(ow_pin, gSPad[3]);				//write Tl
	ow_write(ow_pin, gSPad[4]);				//write configuration
}

void ds18_readrom(unsigned int ow_pin, unsigned char *ROM) {		//gSPad should point to an int array 9 deep.
	unsigned char k;
	ow_init(ow_pin);						//reset the one-wire
	ow_write(ow_pin, OW_CMD_READROM);		//read rom
	for (k=0; k<8; k++)						//read the 8 bytes;
		ROM[k]=ow_read(ow_pin);
}

//temp returned in multiple of 0.0625c
signed short ds18_readtemp(unsigned int ow_pin) {		//read the first two bytes of the spad
	unsigned char LSB, MSB;
	signed short temp;
	ow_init(ow_pin);						//reset the one-wire
	ow_write(ow_pin, OW_CMD_SKIPROM);		//issue skip rom command
	ow_write(ow_pin, OW_CMD_TEMPCON);		//start OW_TempConversion;
	delay_ms(OW_Tconv);						//delay 750ms
	ow_init(ow_pin);						//reset the bus
	ow_write(ow_pin, OW_CMD_SKIPROM);		//issue skip rom again why?
	ow_write(ow_pin, OW_CMD_READSPAD);		//read scratchpad
	LSB=ow_read(ow_pin);					//read the lsb
	MSB=ow_read(ow_pin);					//read the msb
	ow_init(ow_pin);						//termininate the transmission
	//if (MSB & 0x80) {						//negative numbers;
	//	MSB = ~MSB;
	//	LSB = ~LSB;
	//	temp=(MSB <<8) | LSB + 1;
	//	temp=-temp;
	//}
	//else temp=(MSB <<8) | LSB;
	return (MSB <<8) | LSB;					//return
}

//float ds18_readtemp_f(unsigned char ow_pin) {		//read the first two bytes of the spad
//	return OW_RESOLUTION_12BIT*ds18_readtemp_i(ow_pin);
//}
