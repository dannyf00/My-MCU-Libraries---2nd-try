#ifndef AD5320_H_INCLUDED
#define AD5320_H_INCLUDED

//hardware configuration
//end hardware configuration

#define ad5320_select(sync)		do {ad5320_deselect(sync); IO_CLR(AD5320_PORT, sync);} while (0)
#define ad5320_deselect(sync)	do {IO_SET(AD5320_PORT, sync); IO_OUT(AD5320_DDR, sync);} while (0)

#define AD5320MODE_NORM			0x0000		//normal operation
//power down modes
#define AD5320MODE_1K			0x1000		//1k to ground
#define AD5320MODE_100K			0x2000		//100k to ground
#define AD5320MODE_TRIST		0x3000		//tri-state

//initialize the chip
#define ad5320_init()			spi_init()	//reset the spi module

//write an output
#define ad5320_write(output)	do {spi_write((output) >> 8); spi_write(output);} while (0)

#endif // AD5320_H_INCLUDED
