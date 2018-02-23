#ifndef AD5310_H_INCLUDED
#define AD5310_H_INCLUDED

#define ad5310_select(sync)		do {ad5310_deselect(sync); IO_CLR(AD5310_PORT, sync);} while (0)
#define ad5310_deselect(sync)	do {IO_SET(AD5310_PORT, sync); IO_OUT(AD5310_DDR, sync);} while (0)

#define AD5310MODE_NORM			0x0000		//normal operation
//power down modes
#define AD5310MODE_1k			0x1000		//1k to ground
#define AD5310MODE_100k			0x2000		//100k to ground
#define AD5310MODE_TRIST		0x3000		//tri-state

//initialize the chip
#define ad5310_init()			spi_init()	//reset the spi module

//write an output
#define ad5310_write(output)	do {spi_write((output) >> 8); spi_write(output);} while (0)


#endif // AD5310_H_INCLUDED
