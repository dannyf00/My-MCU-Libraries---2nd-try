/*
 */
//#include <iccioavr.h>
//#include <avr/io.h>     //we use gcc-avr
//#include <ioavr.h>        //we use iar-avr
//#include <macros.h>
//#include "gpio.h"
//#include "delay.h"
#include "adc.h"								//we use onboard hardware adc

void adc_init(void) {							//reset the adc

    ADMUX =		(0<<REFS2) | (1<<REFS1) | (0<<REFS0) |		//refs2..0=010 -> Vref = 1.1v internal reference
                (0<<ADLAR);						//0=right adjusted, 1=left adjusted
    ADCSRA =	(1<<ADEN) |						//enable the adc
                (0<<ADSC) |						//don't start ads, yet
                (0<<ADATE) |					//auto trigger not enabled
                (0<<ADIF) |						//clear ad interrupt flag
                (0<<ADIE) |						//adc interrupt disabled
                (1<<ADPS2) |					//ad prescaler, adps2..0=100->1:16, 010->1:4x, 111->1:128x
                (1<<ADPS1) |
                (1<<ADPS0);
//    ADCSRB =	(0<<ADHSM) |					//disable high speed adc
    ADCSRB =	(0<<ACME) |						//disable high speed adc
                (0<<ADTS2) |					//adc auto source, 000->free running.
                (0<<ADTS1) |
                (0<<ADTS0);
    //can be commented out
    //DIDR0 = 	0;								//set to disable digital input buffer
}

unsigned short adc_read(unsigned char ch) {					//read the adc

    //can be commented out
    switch (ch) {
    	case ADC_ADC0: IO_IN(ADC_DDR, 1<<5); break;		//ADC0 on PB5
    	case ADC_ADC1: IO_IN(ADC_DDR, 1<<2); break;		//ADC1 on PB2
    	case ADC_ADC2: IO_IN(ADC_DDR, 1<<4); break;		//ADC2 on PB4
    	case ADC_ADC3: IO_IN(ADC_DDR, 1<<3); break;		//ADC3 on PB3
		case ADC_ADC2_2_1x:
		case ADC_ADC2_2_20x: IO_IN(ADC_DDR, 1<<4); break;	//adc2 on PB4
		case ADC_ADC2_3_1x:
		case ADC_ADC2_3_20x: IO_IN(ADC_DDR, (1<<4) | (1<<3)); break;
		case ADC_ADC0_0_1x:
		case ADC_ADC0_0_20x: IO_IN(ADC_DDR, 1<<5); break;	//adc0 on pb5
		case ADC_ADC0_1_1x:
		case ADC_ADC0_1_20x: IO_IN(ADC_DDR, (1<<5) | (1<<2)); break;	//adc0=pb5, adc1=pb2
		case ADC_BANDGAP:
		case ADC_GND:
		case ADC_RESERVED:
		case ADC_ADC4: break;
		//case ADC_TEMP: break;
		}
    ADMUX = (ADMUX & ~0x0f) | (ch & 0x0f);		//set the channel, mux3..0
    ADCSRA |= (1<<ADSC);						//start the adc
    while (ADCSRA & (1<<ADSC)) continue;		//wait for the adc to finish

    //return (ADCH << 8) | (ADCL);					//return the results
    return ADC;
}

