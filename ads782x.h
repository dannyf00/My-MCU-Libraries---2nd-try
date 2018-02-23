#ifndef ADS782X_H_INCLUDED
#define ADS782X_H_INCLUDED

#include "gpio.h"
#include "spi1_sw.h"					//we use software spi1

//using serial data mode to read ads7824/7825
//PAR/SER: low
//BYTE: low
//CONT: low
//PWRD: low

//hardware configuration
#define ADS782X_PORT		PORTB
#define ADS782X_DDR			TRISB
#define ADS782X_RC			(1<<10)		//mcu output/idles high. falling edge starts a conversion, rising edge starts transmission
#define ADS782X_BUSY		(1<<8)		//mcu input. 1=data ready. 0=busy. Optional
#define ADS782X_A0			(1<<14)		//mcu output/idles low -> channel select
#define ADS782X_A1			(1<<15)		//mcu output/idles low -> channel select
//A1..A0=00 -> data available from ain3, ain0 to convert
//A1..A0=01 -> data available from ain0, ain1 to convert
//A1..A0=10 -> data available from ain1, ain2 to convert
//A1..A0=11 -> data available from ain2, ain3 to convert

//end hardware configuration

//global defines
#define ADC782X_CH0		0x00			//adc channel 0/1/2/3
#define ADC782X_CH1		0x01
#define ADC782X_CH2		0x02
#define ADC782X_CH3		0x03


//global variables

//reset ads782x
void ads782x_init(void);

//select a channel, and start the conversion
void ads782x_startch(uint8_t ch);

//read current adc channel
uint16_t ads782x_read(void);

//returns 1 if ads782x is still busy
#define ads782x_busy()					(IO_GET(ADS782X_PORT_IN, ADS782X_BUSY))?0:1)


#endif /* ADS782X_H_INCLUDED */
