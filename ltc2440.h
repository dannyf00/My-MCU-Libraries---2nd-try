#ifndef LTC2440_H_INCLUDED
#define LTC2440_H_INCLUDED

//hardware configuration
//ltc2440 pins
#define LTC2440_PORT	SPI_PORT
#define LTC2440_DDR		SPI_DDR
#define LTC2440_Vref	5000000ul		//Vref, in mv
//end hardware configuration

//macros for pin operations
#define ltc2440_select(cs)		{ltc2440_deselect(cs); IO_CLR(LTC2440_PORT, cs);}
#define ltc2440_deselect(cs)	{IO_SET(LTC2440_PORT, cs); IO_OUT(LTC2440_DDR, cs);}

#define LTC_EOC			(1ul<<31)	//eoc bit
#define LTC_DMY			(1ul<<30)	//dummy bit. always 0
#define LTC_SIG			(1ul<<29)	//sign bit. 1 if positive and 0 for negative
#define LTC_EXT			(1ul<<28)	//extended range indicator

//convert a 24bit type to actual voltage
#define ADC2UV(adc24)     ((((adc24) >> 6) * ((LTC2440_Vref) >> 6)) >> 12) //convert 24-bit adc value into uv

//global defines

//global variables
// initialize the library with the numbers of the interface pins

//reset ltc2440
void ltc2440_init(void);

//read data from ltc2440
unsigned long ltc2440_read(void);

#endif // LTC2440_H_INCLUDED
