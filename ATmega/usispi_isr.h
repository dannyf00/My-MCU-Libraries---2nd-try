#ifndef USISPI_ISR_H_INCLUDED
#define USISPI_ISR_H_INCLUDED

//#include <avr/io.h>							//we use gcc-avr
#include "gpio.h"

//hardware configuration
#define USI_PORT		PORTB
#define USI_DDR			DDRB
#define USI_USCK		(1<<2)				//USCK on PB2
#define USI_DO			(1<<1)				//Data_out/DO on PB1
//#define USI_DI			(1<<0)				//Data_in/DI on PB0

#define USI_CS			(1<<3)				//cs pin
//end hardware configuration

//global defines
//used to control speed
//#define usispi_dly(n)	//do {NOP();} while (0)
//read from spi
//#define spi_read()		spi_write(0)
#define spi_busy()		(_USI_BUSY)					//1=spi busy, 0=spi ready

//global variables
//volatile unsigned char *_USI_ptr;					//usi/spi transmission/receiption buffer
extern volatile unsigned char _USI_BUSY;					//transmission status. 0=done / uart available, and 1=tx in progress

//reset the usispi module
void spi_init(void);

//send a null-terminated string - \00 not sent
void spi_puts(unsigned char * str);					//put a string

#endif // USISPI_ISR_H_INCLUDED
