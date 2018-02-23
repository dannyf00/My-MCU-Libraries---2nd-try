//#include <regx51.h>
#include <avr/io.h>
#include "gpio.h"
#include "delay.h"
#include "spi_sw.h"
#include "ltc186x.h"

unsigned short ltc186x_read(void) {					//read ltc186x
	unsigned char adc_h, adc_l;

	IO_OUT(SPI_DDR, SPI_CONV);						//spi_conv as output
	IO_CLR(SPI_PORT, SPI_CONV);						//clear spi_conv
	IO_SET(SPI_PORT, SPI_CONV);						//set spi_conv - start the conversion
	LTC186x_TCONV();								//wait for the conversion to finish
	IO_CLR(SPI_PORT, SPI_CONV);						//read the data
	adc_h=spi_read();								//read the msb
	adc_l=spi_read();								//read the lsb
	return (adc_h<<4) | (adc_l>>4);					//return the data - 12-bit adc, last four bits are 0s

}

unsigned short ltc186x_read_mv(void) {				//return the adc reading, in mv
	//unsigned short adc=ltc186x_read();
	return ((ltc186x_read()*LTC186x_VREF) >> 12);
}
