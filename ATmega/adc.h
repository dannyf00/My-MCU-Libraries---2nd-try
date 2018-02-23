#ifndef _ADC_H
#define _ADC_H

#include "gpio.h"
//#include <avr/io.h>     //we use gcc-avr

//hardware configuration
#define ADC_DDR					DDRB		//adc on portb
//end hardware configuration

//input channels - attiny25/45/85: gcc-avr and iar-avr
#if (__AVR_ATtiny24__) || (__AVR_ATtiny44_) || (__AVR_ATtiny84__) || (__ATtiny24__) || (__ATtiny44__) || (__ATtiny84__)
//unipolar mode
#define ADC_0			0x00			//singled ended, adc0/pb5
#define ADC_1			0x01			//singled ended, adc1/pb2
#define ADC_2			0x02			//singled ended, adc2/pb4
#define ADC_3			0x03			//singled ended, adc3/pb3
#define ADC_4			0x04			//singled ended, adc4/pb3
#define ADC_5			0x05			//singled ended, adc5/pb3
#define ADC_6			0x06			//singled ended, adc6/pb3
#define ADC_7			0x07			//singled ended, adc7/pb3
#define ADC_GND				0x20			//gnd/0v
#define ADC_BANDGAP			0x21			//1.1v band gap
#define ADC_8			0x22			//temperature sensor
//bipolar mode
#define ADC_0_0_20x		0x23			//+=ADC0, -=ADC0, 20x
#define ADC_0_1_1x		0x08			//+=ADC0, -=ADC1, 1x
#define ADC_0_1_20x		0x09			//+=ADC0, -=ADC1, 20x
#define ADC_0_3_1x		0x0a			//+=ADC0, -=ADC3, 1x
#define ADC_0_3_20x		0x0b			//+=ADC0, -=ADC3, 20x
#define ADC_1_0_1x		0x28			//+=ADC1, -=ADC0, 1x
#define ADC_1_0_20x		0x29			//+=ADC1, -=ADC0, 20x
#define ADC_1_2_1x		0x0c			//+=ADC1, -=ADC2, 1x
#define ADC_1_2_20x		0x0d			//+=ADC1, -=ADC2, 20x
#define ADC_1_3_1x		0x0e			//+=ADC1, -=ADC3, 1x
#define ADC_1_3_20x		0x0f			//+=ADC1, -=ADC3, 20x
#define ADC_2_1_1x		0x2c			//+=ADC2, -=ADC1, 1x
#define ADC_2_1_20x		0x2d			//+=ADC2, -=ADC1, 20x
#define ADC_2_3_1x		0x10			//+=ADC2, -=ADC3, 1x
#define ADC_2_3_20x		0x11			//+=ADC2, -=ADC3, 20x
#define ADC_3_0_1x		0x2a			//+=ADC3, -=ADC0, 1x
#define ADC_3_0_20x		0x2b			//+=ADC3, -=ADC0, 20x
#define ADC_3_1_1x		0x2e			//+=ADC3, -=ADC1, 1x
#define ADC_3_1_20x		0x2f			//+=ADC3, -=ADC1, 20x
#define ADC_3_2_1x		0x30			//+=ADC3, -=ADC2, 1x
#define ADC_3_2_20x		0x31			//+=ADC3, -=ADC2, 20x
#define ADC_3_3_1x		0x24			//+=ADC3, -=ADC3, 1x
#define ADC_3_3_20x		0x25			//+=ADC3, -=ADC3, 20x
#define ADC_3_4_1x		0x12			//+=ADC3, -=ADC4, 1x
#define ADC_3_4_20x		0x13			//+=ADC3, -=ADC4, 20x
#define ADC_3_5_1x		0x14			//+=ADC3, -=ADC5, 1x
#define ADC_3_5_20x		0x15			//+=ADC3, -=ADC5, 20x
#define ADC_3_6_1x		0x16			//+=ADC3, -=ADC6, 1x
#define ADC_3_6_20x		0x17			//+=ADC3, -=ADC6, 20x
#define ADC_3_7_1x		0x18			//+=ADC3, -=ADC7, 1x
#define ADC_3_7_20x		0x19			//+=ADC3, -=ADC7, 20x

#define ADC_4_3_1x		0x32			//+=ADC4, -=ADC3, 1x
#define ADC_4_3_20x		0x33			//+=ADC4, -=ADC3, 20x
#define ADC_4_5_1x		0x1a			//+=ADC4, -=ADC5, 1x
#define ADC_4_5_20x		0x1b			//+=ADC4, -=ADC5, 20x

#define ADC_5_3_1x		0x34			//+=ADC5, -=ADC3, 1x
#define ADC_5_3_20x		0x35			//+=ADC5, -=ADC3, 20x
#define ADC_5_4_1x		0x3a			//+=ADC5, -=ADC4, 1x
#define ADC_5_4_20x		0x3b			//+=ADC5, -=ADC4, 20x
#define ADC_5_6_1x		0x1c			//+=ADC5, -=ADC5, 1x
#define ADC_5_6_20x		0x1d			//+=ADC5, -=ADC5, 20x

#define ADC_6_3_1x		0x36			//+=ADC6, -=ADC3, 1x
#define ADC_6_3_20x		0x37			//+=ADC6, -=ADC3, 20x
#define ADC_6_5_1x		0x3c			//+=ADC6, -=ADC5, 1x
#define ADC_6_5_20x		0x3d			//+=ADC6, -=ADC5, 20x
#define ADC_6_7_1x		0x1e			//+=ADC6, -=ADC7, 1x
#define ADC_6_7_20x		0x1f			//+=ADC6, -=ADC7, 20x

#define ADC_7_3_1x		0x38			//+=ADC7, -=ADC3, 1x
#define ADC_7_3_20x		0x39			//+=ADC7, -=ADC3, 20x
#define ADC_7_6_1x		0x3e			//+=ADC7, -=ADC6, 1x
#define ADC_7_6_20x		0x3f			//+=ADC7, -=ADC6, 20x
#define ADC_7_7_1x		0x26			//+=ADC7, -=ADC7, 1x
#define ADC_7_7_20x		0x27			//+=ADC7, -=ADC7, 20x
#define ADC_TEMP			ADC_8		//measure internal temperature sensor/adc4

#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__ATtiny25__) || defined(__ATtiny45__) || defined(__ATtiny85__)
#define ADC_0			0x00			//singled ended, adc0/pb5
#define ADC_1			0x01			//singled ended, adc1/pb2
#define ADC_2			0x02			//singled ended, adc2/pb4
#define ADC_3			0x03			//singled ended, adc3/pb3
#define ADC_2_2_1x		0x04			//diff. adc, 1x gain, +=adc2, -=adc2 - offset measurement for adc2 x 1
#define ADC_2_2_20x		0x05			//diff. adc, 20x gain, +=adc2, -=adc3 - offset measurement for adc2 x 20
#define ADC_2_3_1x		0x06			//diff. adc, 1x gain, +=adc2, -=adc3 - actual measurement at x1 gain
#define ADC_2_3_20x		0x07			//diff. adc, 20x gain: +=adc2, -=adc3 - actual measurement at x20 gain
#define ADC_0_0_1x		0x08			//diff. adc, 1x gain, +=adc0, -=adc0 - offset measurement for adc0 x 1
#define ADC_0_0_20x		0x09			//diff. adc, 20x gain, +=adc0, -=adc0 - offset measurement at x20 gain
#define ADC_0_1_1x		0x0a			//diff. adc, 20x gain, +=adc0, -=adc1 - actual measurement for adc0 x1
#define ADC_0_1_20x		0x0b			//diff. adc, 20x gain: +=adc0, -=adc1 - actual measurement at x20 gain
#define ADC_BANDGAP			0x0c			//MEASURE THE INTERNAL BANDGAP
#define ADC_GND				0x0d			//ground
#define ADC_RESERVED		0x0e			//reserved
#define ADC_4			0x0f			//measure internal temperature sensor/adc4
#define ADC_TEMP			ADC_4		//measure internal temperature sensor/adc4

//for mega48/88/168/328, gcc-avr and iar-avr
#elif defined (__AVR_ATmega48P__) || defined (__AVR_ATmega48__) || (__AVR_ATmega88P__) || defined (__AVR_ATmega88__) || (__AVR_ATmega168P__) || defined (__AVR_ATmega168__) || (__AVR_ATmega328P__) || defined (__AVR_ATmega328__) || (__ATmega48P__) || (__ATmega88P__) || (__ATmega168P__) || (__ATmega328P__)
//input channel - for atmega48/88/168/328
#define ADC_0			0x00			//adc channels
#define ADC_1			0x01			//adc channels
#define ADC_2			0x02			//adc channels
#define ADC_3			0x03			//adc channels
#define ADC_4			0x04			//adc channels
#define ADC_5			0x05			//adc channels
#define ADC_6			0x06			//adc channels
#define ADC_7			0x07			//adc channels
#define ADC_8			0x08			//adc channels - temperature sensor
//0X09 - 0X0D RESERVED
#define ADC_BANDGAP			0x0E			//1.1v internal bandgap
#define ADC_GND				0x00			//gnd


//atmega16/32
#elif defined (__AVR_ATmega16__) || (__AVR_ATmega32__) || defined (__ATmega16__) || (__ATmega32__)
//se channels
#define ADC_0			0x00			//adc0, 1x
#define ADC_1			0x01			//adc1, 1x
//#define ADC_2			0x02			//adc2, 1x
//#define ADC_3			0x03			//adc3, 1x
#define ADC_4			0x04			//adc4, 1x
#define ADC_5			0x05			//adc5, 1x
#define ADC_6			0x06			//adc6, 1x
#define ADC_7			0x07			//adc7, 1x

//diff channels
//#define ADC_0_0_10x		0x08			//adc0, 10x
#define ADC_1_0_10x		0x09			//adc1-adc0, 10x
//#define ADC_0_0_200x		0x0a			//adc0, 200x
#define ADC_1_0_200x		0x0b			//adc1-adc0, 200x
//reserved - 0x0c
//#define ADC_2_2_10x		0x0c			//adc2-adc0 // reserved
//#define ADC_3_2_10x		0x0d			//adc3-adc2, 10x
//#define ADC_2_2_200x		0x0e			//adc2, 200x
//#define ADC_3_2_200x		0x0f			//adc3-adc2, 200x
#define ADC_0_1_1x		0x10			//adc0-adc1, 1x
//#define ADC_1_1_1x		0x11			//adc1-adc1, 1x
//#define ADC_2_1_1x		0x12			//adc2-adc1, 1x
//#define ADC_3_1_1x		0x13			//adc3-adc1, 1x
#define ADC_4_1_1x		0x14			//adc4-adc1, 1x
#define ADC_5_1_1x		0x15			//adc5-adc1, 1x
#define ADC_6_1_1x		0x16			//adc6-adc1, 1x
#define ADC_7_1_1x		0x17			//adc7-adc1, 1x
//#define ADC_0_2_1x		0x18			//adc0-adc2, 1x
//#define ADC_1_2_1x		0x19			//adc1-adc2, 1x
//#define ADC_2_2_1x		0x1a			//adc2-adc2, 1x
//#define ADC_3_2_1x		0x1b			//adc3-adc2, 1x
//#define ADC_4_2_1x		0x1c			//adc4-adc2, 1x
//#define ADC_5_2_1x		0x1d			//adc5-adc2, 1x

//bandgap channels
#define ADC_BANDGAP			0x1e			//adc the 1.1v bandgap
#define ADC_GND				0x1f			//adc the 0v GND

//usb646/647/1286/1287
#elif defined (__AVR_AT90USB646__) || (__AVR_AT90USB647__) || defined (__AVR_AT90USB1286__) || (__AVR_AT90USB1287__)
//se channels
#define ADC_0			0x00			//adc0, 1x
#define ADC_1			0x01			//adc1, 1x
#define ADC_2			0x02			//adc2, 1x
#define ADC_3			0x03			//adc3, 1x
#define ADC_4			0x04			//adc4, 1x
#define ADC_5			0x05			//adc5, 1x
#define ADC_6			0x06			//adc6, 1x
#define ADC_7			0x07			//adc7, 1x

//diff channels
#define ADC_0_0_10x		0x08			//adc0, 10x
#define ADC_1_0_10x		0x09			//adc1-adc0, 10x
#define ADC_0_0_200x		0x0a			//adc0, 200x
#define ADC_1_0_200x		0x0b			//adc1-adc0, 200x
//reserved - 0x0c
#define ADC_2_2_10x		0x0c			//adc2-adc0 // reserved
#define ADC_3_2_10x		0x0d			//adc3-adc2, 10x
#define ADC_2_2_200x		0x0e			//adc2, 200x
#define ADC_3_2_200x		0x0f			//adc3-adc2, 200x
#define ADC_0_1_1x		0x10			//adc0-adc1, 1x
#define ADC_1_1_1x		0x11			//adc1-adc1, 1x
#define ADC_2_1_1x		0x12			//adc2-adc1, 1x
#define ADC_3_1_1x		0x13			//adc3-adc1, 1x
#define ADC_4_1_1x		0x14			//adc4-adc1, 1x
#define ADC_5_1_1x		0x15			//adc5-adc1, 1x
#define ADC_6_1_1x		0x16			//adc6-adc1, 1x
#define ADC_7_1_1x		0x17			//adc7-adc1, 1x
#define ADC_0_2_1x		0x18			//adc0-adc2, 1x
#define ADC_1_2_1x		0x19			//adc1-adc2, 1x
#define ADC_2_2_1x		0x1a			//adc2-adc2, 1x
#define ADC_3_2_1x		0x1b			//adc3-adc2, 1x
#define ADC_4_2_1x		0x1c			//adc4-adc2, 1x
#define ADC_5_2_1x		0x1d			//adc5-adc2, 1x

//se channels
#define ADC_8			0x20			//adc0, 1x
#define ADC_9			0x21			//adc1, 1x
#define ADC_10			0x22			//adc2, 1x
#define ADC_11			0x23			//adc3, 1x
#define ADC_12			0x24			//adc4, 1x
#define ADC_13			0x25			//adc5, 1x
#define ADC_1_0_40x		0x26			//adc6, 1x
#define ADC_TEMP			0x27			//adc7, 1x
//differential channels
#define ADC_4_0_10x		0x28			//adc6, 1x
#define ADC_5_0_10x		0x29			//adc6, 1x
#define ADC_6_0_10x		0x2a			//adc6, 1x
#define ADC_7_0_10x		0x2b			//adc6, 1x
#define ADC_4_1_10x		0x2c			//adc6, 1x
#define ADC_5_1_10x		0x2d			//adc6, 1x
#define ADC_6_1_10x		0x2e			//adc6, 1x
#define ADC_7_1_10x		0x2f			//adc6, 1x
#define ADC_4_0_40x		0x30			//adc6, 1x
#define ADC_5_0_40x		0x31			//adc6, 1x
#define ADC_6_0_40x		0x32			//adc6, 1x
#define ADC_7_0_40x		0x33			//adc6, 1x
#define ADC_4_1_40x		0x34			//adc6, 1x
#define ADC_5_1_40x		0x35			//adc6, 1x
#define ADC_6_1_40x		0x36			//adc6, 1x
#define ADC_7_1_40x		0x37			//adc6, 1x
#define ADC_4_0_200x		0x38			//adc6, 1x
#define ADC_5_0_200x		0x39			//adc6, 1x
#define ADC_6_0_200x		0x3a			//adc6, 1x
#define ADC_7_0_200x		0x3b			//adc6, 1x
#define ADC_4_1_200x		0x3c			//adc6, 1x
#define ADC_5_1_200x		0x3d			//adc6, 1x
#define ADC_6_1_200x		0x3e			//adc6, 1x
#define ADC_7_1_200x		0x3f			//adc6, 1x

#else
//missing channel definition information
  #warning adc.h - no channel definitions for this mcu
#endif

//define ADC_VBG to be ADC_BANDGAP
#if defined(ADC_BANDGAP)
#define ADC_VBG				ADC_BANDGAP		//define Vbg
#endif

void adc_init(void);							//reset the adc

unsigned short adc_read(unsigned char ch);					//read the adc
#endif
