//#include <avr/io.h>							//we use gcc-avr
#include "usispi.h"								//we use usi_spi (3wire mode)

//hardware configuration
//end hardware configuration

//global defines

//global variables

//initialize spi
//software clock (strobe USICLK bit on USICR
void spi_init(void) {
	//set up the pins
	IO_CLR(USI_PORT, USI_USCK);	IO_OUT(USI_DDR, USI_USCK);	//usck idles low, output

#if defined(USI_DO)
	IO_CLR(USI_PORT, USI_DO); IO_OUT(USI_DDR, USI_DO);		//DO idles low, output
#endif

#if defined(USI_DI)
	IO_SET(USI_PORT, USI_DI); IO_IN(USI_DDR, USI_DI);		//di idles high, input
#endif

	// Configure USI to 3-wire master mode with overflow interrupt.
	USICR = (0<<USISIE) | 							//0=start condition interrupt disable
			(0<<USIOIE) | 							//0=no usi counter overflow interrupt,
			(0<<USIWM1) | (1<<USIWM0) |				//01=three wire mode / spi
	        (1<<USICS1) | (1<<USICS0) | (1<<USICLK) |//000=no clock, 101=positive edge, 111=negative edge
	        (0<<USITC);								//don't send yet
}

//write to spi
uint8_t spi_write(uint8_t dat) {
	USIDR = dat;							//load up the data register
	//clock out the data
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	return USIDR;							//return the value
}

//read from spi
uint8_t spi_read(void) {
	//USIDR = dat;							//load up the data register
	//clock out the data
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	USICR |= 1<<USITC; usispi_dly(0); USICR |= 1<<USITC; usispi_dly(0);	//strobe usiclk, to send 1 bit
	return USIDR;							//return the value

}
