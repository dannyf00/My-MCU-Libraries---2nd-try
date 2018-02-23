//#include <Arduino.h>
#include <htc.h>					//we use picc
#include "gpio.h"					//we use gpio
#include "delay.h"					//we use software delay
#include "spi_sw.h"					//we use soft spi
#include "ltc2440.h"				//we use ltc2440

//hardware configuration
//end hardware configuration

//macros for pin operations

//global defines
#define LTC2400_DLY()				delay(10)		//to conform to t3 in datasheet (typical 5us)

//global variables

//reset ltc2440
void ltc2440_init(void) {
	//set cs as output, idles high
	//done in spi routines
}

//read data from ltc2440
//cs select outside of this routine
unsigned long ltc2440_read(void) {
	unsigned long tmp=0;			//temporary variable, 32-bit
	//PIN_CLR(LTC2440_SCK);			//sck idles low
	//PIN_SET(LTC2440_CS); PIN_CLR(LTC2440_CS);	//create a high->low transistion
	//delayMicroseconds(10);						//t3 typical 5us
	LTC2400_DLY();
	//tmp |= shiftIn(LTC2440_SDO, LTC2440_SCK, MSBFIRST); tmp <<= 8;
	tmp |= spi_read(); tmp <<=8;
	//tmp |= shiftIn(LTC2440_SDO, LTC2440_SCK, MSBFIRST); tmp <<= 8;
	tmp |= spi_read(); tmp <<=8;
	//tmp |= shiftIn(LTC2440_SDO, LTC2440_SCK, MSBFIRST); tmp <<= 8;
	tmp |= spi_read(); tmp <<=8;
	//tmp |= shiftIn(LTC2440_SDO, LTC2440_SCK, MSBFIRST);
	tmp |=  spi_read();
	//PIN_SET(LTC2440_CS);			//stop reading the chip
	//return (tmp & ~(LTC_EOC | LTC_SIG | LTC_EXT));	//eliminate leading 1s
	return tmp;						//return the whole 32 bits
}
