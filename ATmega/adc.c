/*
 */
//#include <iccioavr.h>
//#include <avr/io.h>     //we use gcc-avr
//#include <ioavr.h>        //we use iar-avr
//#include <macros.h>
//#include "gpio.h"
//#include "delay.h"
#include "adc.h"								//we use onboard hardware adc

#if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) || defined(__ATtiny24__) || defined(__ATtiny44__) || defined(__ATtiny84__)
void adc_init(void) {							//reset the adc

    ADMUX =
#if defined(REFS2)
				(0<<REFS2) |
#endif
				(1<<REFS1) | (0<<REFS0) |		//refs2..0=010 -> Vref = 1.1v internal reference
                0x00;							//(0<<ADLAR);						//right adjusted
    ADCSRA =	(1<<ADEN) |						//enable the adc
                (0<<ADSC) |						//don't start ads, yet
                (0<<ADATE) |					//auto trigger not enabled
                (0<<ADIF) |						//clear ad interrupt flag
                (0<<ADIE) |						//adc interrupt disabled
                (1<<ADPS2) |					//ad prescaler, adps2..0=100->1:16, 010->1:4x, 111->1:128x
                (1<<ADPS1) |
                (1<<ADPS0);
//    ADCSRB =	(0<<ADHSM) |					//disable high speed adc
    ADCSRB =	(1<<BIN) |						//1=bipolar input mode. 0=unipolar input
				(0<<ADLAR) |					//1=left adjusted. 0=right adjusted
				(0<<ACME) |						//disable high speed adc
                (0<<ADTS2) |					//adc auto source, 000->free running.
                (0<<ADTS1) |
                (0<<ADTS0);
    //can be commented out
    //DIDR0 = 	0;								//set to disable digital input buffer
}

unsigned short adc_read(unsigned char ch) {					//read the adc

    //can be commented out
    /*switch (ch) {
    	case ADC_0: ADC_DDR &=~(1<<0); break;
    	case ADC_1: ADC_DDR &=~(1<<1); break;
    	case ADC_2: ADC_DDR &=~(1<<2); break;
    	case ADC_3: ADC_DDR &=~(1<<3); break;
    	case ADC_4: ADC_DDR &=~(1<<4); break;
    	case ADC_5: ADC_DDR &=~(1<<5); break;
    	case ADC_6: ADC_DDR &=~(1<<6); break;
    	case ADC_7: ADC_DDR &=~(1<<7); break;
    }*/
    ADMUX = (ADMUX & ~0x3f) | (ch & 0x3f);		//set the channel, mux3..0
    ADCSRA |= (1<<ADSC);						//start the adc
    while (ADCSRA & (1<<ADSC)) continue;		//wait for the adc to finish

    //return (ADCH << 8) | (ADCL);					//return the results
    return ADC;
}

#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__ATtiny25__) || defined(__ATtiny45__) || defined(__ATtiny85__)
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
    	case ADC_0: IO_IN(ADC_DDR, 1<<5); break;		//ADC0 on PB5
    	case ADC_1: IO_IN(ADC_DDR, 1<<2); break;		//ADC1 on PB2
    	case ADC_2: IO_IN(ADC_DDR, 1<<4); break;		//ADC2 on PB4
    	case ADC_3: IO_IN(ADC_DDR, 1<<3); break;		//ADC3 on PB3
		case ADC_2_2_1x:
		case ADC_2_2_20x: IO_IN(ADC_DDR, 1<<4); break;	//adc2 on PB4
		case ADC_2_3_1x:
		case ADC_2_3_20x: IO_IN(ADC_DDR, (1<<4) | (1<<3)); break;
		case ADC_0_0_1x:
		case ADC_0_0_20x: IO_IN(ADC_DDR, 1<<5); break;	//adc0 on pb5
		case ADC_0_1_1x:
		case ADC_0_1_20x: IO_IN(ADC_DDR, (1<<5) | (1<<2)); break;	//adc0=pb5, adc1=pb2
		case ADC_BANDGAP:
		case ADC_GND:
		case ADC_RESERVED:
		case ADC_4: break;
		//case ADC_TEMP: break;
		}
    ADMUX = (ADMUX & ~0x0f) | (ch & 0x0f);		//set the channel, mux3..0
    ADCSRA |= (1<<ADSC);						//start the adc
    while (ADCSRA & (1<<ADSC)) continue;		//wait for the adc to finish

    //return (ADCH << 8) | (ADCL);					//return the results
    return ADC;
}

//for mega48/88/168/328
#elif 	defined (__AVR_ATmega48P__) || defined (__AVR_ATmega48__) || defined(__AVR_ATmega88P__) || defined (__AVR_ATmega88__) || \
	defined(__AVR_ATmega168P__) || defined (__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined (__AVR_ATmega328__) || \
	defined(__ATmega48P__) || defined(__ATmega88P__) || defined(__ATmega168P__) || defined(__ATmega328P__)

void adc_init(void) {							//reset the adc

    ADMUX =		(0<<REFS2) | (1<<REFS1) | (0<<REFS0) |		//refs2..0=010 -> Vref = 1.1v internal reference
                (0<<ADLAR);						//right adjusted
    ADCSRA =	(1<<ADEN) |						//enable the adc
                (0<<ADSC) |						//don't start ads, yet
                (0<<ADATE) |					//auto trigger not enabled
                (0<<ADIF) |						//clear ad interrupt flag
                (0<<ADIE) |						//adc interrupt disabled
                (0<<ADPS2) |					//ad prescaler, adps2..0=100->1:16, 010->1:4x, 111->1:128x
                (1<<ADPS1) |
                (0<<ADPS0);
//    ADCSRB =	(0<<ADHSM) |					//disable high speed adc
    ADCSRB =	(0<<ACME) |						//disable high speed adc
                (0<<ADTS2) |					//adc auto source, 000->free running
                (0<<ADTS1) |
                (0<<ADTS0);
    //can be commented out
    //DIDR0 = 	0;								//set to disable digital input buffer
}

unsigned short adc_read(unsigned char ch) {					//read the adc

    //can be commented out
    /*switch (ch) {
    	case ADC_0: ADC_DDR &=~(1<<0); break;
    	case ADC_1: ADC_DDR &=~(1<<1); break;
    	case ADC_2: ADC_DDR &=~(1<<2); break;
    	case ADC_3: ADC_DDR &=~(1<<3); break;
    	case ADC_4: ADC_DDR &=~(1<<4); break;
    	case ADC_5: ADC_DDR &=~(1<<5); break;
    	case ADC_6: ADC_DDR &=~(1<<6); break;
    	case ADC_7: ADC_DDR &=~(1<<7); break;
    }*/
    ADMUX = (ADMUX & ~0x0f) | (ch & 0x0f);		//set the channel, mux3..0
    ADCSRA |= (1<<ADSC);						//start the adc
    while (ADCSRA & (1<<ADSC)) continue;		//wait for the adc to finish

    //return (ADCH << 8) | (ADCL);					//return the results
    return ADC;
}

//for mega8/16/32
#elif 	defined(__AVR_ATmega8__) || defined (__AVR_ATmega16__) || defined(__AVR_ATmega32__) || \
	defined(__AVR_ATmega8L__) || defined (__AVR_ATmega16L__) || defined(__AVR_ATmega32L__) || \
	defined(__ATmega8__) || defined (__ATmega16__) || defined(__ATmega32__)					//for iar avr

void adc_init(void) {							//reset the adc

    ADMUX =		(1<<REFS1) | (1<<REFS0) |		//refs1..0=00(AREF pin), 01=Vcc, 10=reserved, 11=2.56v internal bandgap
                (0<<ADLAR);						//right adjusted
    ADCSRA =	(1<<ADEN) |						//enable the adc
                (0<<ADSC) |						//don't start ads, yet
                (0<<ADATE) |					//auto trigger not enabled
                (0<<ADIF) |						//clear ad interrupt flag
                (0<<ADIE) |						//adc interrupt disabled
                (0<<ADPS2) |					//ad prescaler, adps2..0=100->1:16, 010->1:4x, 111->1:128x
                (1<<ADPS1) |
                (0<<ADPS0);
    ADCSRB =	(0<<ADHSM) |					//disable high speed adc
				(0<<ACME) |						//disable high speed adc
                (0<<ADTS3) |					//0000->free running
                (0<<ADTS2) |					//adc auto source, 000->free running
                (0<<ADTS1) |
                (0<<ADTS0);
    //can be commented out
    //DIDR0 = 	0;								//set to disable digital input buffer
}

unsigned short adc_read(unsigned char ch) {					//read the adc

    //can be commented out
    /*switch (ch) {
    	case ADC_0: ADC_DDR &=~(1<<0); break;
    	case ADC_1: ADC_DDR &=~(1<<1); break;
    	case ADC_2: ADC_DDR &=~(1<<2); break;
    	case ADC_3: ADC_DDR &=~(1<<3); break;
    	case ADC_4: ADC_DDR &=~(1<<4); break;
    	case ADC_5: ADC_DDR &=~(1<<5); break;
    	case ADC_6: ADC_DDR &=~(1<<6); break;
    	case ADC_7: ADC_DDR &=~(1<<7); break;
    }*/
    ADMUX = (ADMUX & ~0x1f) | (ch & 0x1f);		//set the channel mux4..0
    ADCSRB = (ADCSRB & ~(1<<MUX5)) | (ch & (1<<MUX5));	//set mux5 in ADCSRB
    ADCSRA |= (1<<ADSC);						//start the adc
    while (ADCSRA & (1<<ADSC)) continue;		//wait for the adc to finish

    //return (ADCH << 8) | (ADCL);					//return the results
    return ADC;
}

//usb646/647/1286/1287
#elif defined (__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined (__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)

void adc_init(void) {							//reset the adc

    ADMUX =		(1<<REFS1) | (1<<REFS0) |		//refs1..0=11 -> Vref = 2.56v internal reference
                (0<<ADLAR);						//right adjusted
    ADCSRA =	(1<<ADEN) |						//enable the adc
                (0<<ADSC) |						//don't start ads, yet
                (0<<ADATE) |					//auto trigger not enabled
                (0<<ADIF) |						//clear ad interrupt flag
                (0<<ADIE) |						//adc interrupt disabled
                (0<<ADPS2) |					//ad prescaler, adps2..0=000(2x), 001(2x), 010(4x), 011(8x), 100(16x), 101(32x), 110(64x), 111(128x)
                (1<<ADPS1) |
                (0<<ADPS0);
//    ADCSRB =	(0<<ADHSM) |					//disable high speed adc
    ADCSRB =	(0<<ACME) |						//disable high speed adc
                (0<<ADTS2) |					//adc auto source, 000->free running
                (0<<ADTS1) |
                (0<<ADTS0);
    //can be commented out
    //DIDR0 = 	0;								//set to disable digital input buffer
}

unsigned short adc_read(unsigned char ch) {					//read the adc

    //can be commented out
    /*switch (ch) {
    	case ADC_0: ADC_DDR &=~(1<<0); break;
    	case ADC_1: ADC_DDR &=~(1<<1); break;
    	case ADC_2: ADC_DDR &=~(1<<2); break;
    	case ADC_3: ADC_DDR &=~(1<<3); break;
    	case ADC_4: ADC_DDR &=~(1<<4); break;
    	case ADC_5: ADC_DDR &=~(1<<5); break;
    	case ADC_6: ADC_DDR &=~(1<<6); break;
    	case ADC_7: ADC_DDR &=~(1<<7); break;
    }*/
    ADMUX = (ADMUX & ~0x1f) | (ch & 0x1f);		//set the channel,  mux4..0
    ADCSRA |= (1<<ADSC);						//start the adc
    while (ADCSRA & (1<<ADSC)) continue;		//wait for the adc to finish

    //return (ADCH << 8) | (ADCL);					//return the results
    return ADC;
}

#else
//missing channel definition information
  #warning adc.h - adc routines not implemented for this mcu
#endif
