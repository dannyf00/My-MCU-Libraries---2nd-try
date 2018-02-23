//#include <avr/io.h>							//we use gcc-avr
#include "usispi_isr.h"

//hardware configuration
//end hardware configuration

//global defines
//used to control speed
#define usispi_dly(n)	do {NOP();} while (0)
//read from spi
#define spi_read()		spi_write(0)
//#define spi_busy()		(_USI_BUSY)					//1=spi busy, 0=spi ready

//global variables
volatile unsigned char *_USI_ptr;					//usi/spi transmission/receiption buffer
volatile unsigned char _USI_BUSY;					//transmission status. 0=done / uart available, and 1=tx in progress

uint8_t spi_write(uint8_t dat);

//usi ovf interrupt
ISR(USI_OVF_vect) {
	//USISR |= (1<<USIOIF);							//clear the flag by writing 1 to it
	*_USI_ptr = USIDR;								//save the returned data
	if (*++_USI_ptr==0) {							//last non-zero char has been sent
		USICR &=~(1<<USIOIE);						//disable the interrupt
		_USI_BUSY = 0;								//usi no long busy
		IO_SET(USI_PORT, USI_CS);					//terminate spi chip select
	}
	else spi_write(*_USI_ptr);						//send the next byte
}

//reset the usispi module
void spi_init(void) {
	//set up the pins
	IO_SET(USI_PORT, USI_CS); IO_OUT(USI_DDR, USI_CS);		//cs pin as output, idles high

	IO_CLR(USI_PORT, USI_USCK);	IO_OUT(USI_DDR, USI_USCK);	//usck idles low, output

#if defined(USI_DO)
	IO_CLR(USI_PORT, USI_DO); IO_OUT(USI_DDR, USI_DO);		//DO idles low, output
#endif

#if defined(USI_DI)
	IO_SET(USI_PORT, USI_DI); IO_IN(USI_DDR, USI_DI);		//di idles high, input
#endif

	//initialize usi counters to zero
	USISR &=~((1<<USICNT3) | (1<<USICNT2) | (1<<USICNT1) | (1<<USICNT0));

	// Configure USI to 3-wire master mode with overflow interrupt.
	USICR = (0<<USISIE) | 							//0=start condition interrupt disable
			(0<<USIOIE) | 							//0=no usi counter overflow interrupt,
			(0<<USIWM1) | (1<<USIWM0) |				//01=three wire mode / spi
	        (1<<USICS1) | (0<<USICS0) | (1<<USICLK) |//000=no clock, 101=positive edge, 111=negative edge
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
	return USIDR;							//return the value. can use USIBR
}

//send a null-terminated string - \00 not sent
void spi_puts(unsigned char * str) {			//put a string
	//create a falling edge on CS
	//IO_SET(USI_PORT, USI_CS);
	IO_CLR(USI_PORT, USI_CS);

	_USI_ptr = str;
	_USI_BUSY = 1;								//transmission in progress

	//enable usi overflow interrupt
	USICR |= (1<<USIOIE);

	//send the first byte - cannot be zero
	spi_write(*_USI_ptr);

	//ISR should take over from here.
}

