#include <regx51.h>							//we use keil c51
#include "gpio.h"
//#include "delay.h"
#include "led7x8.h"							//we use led7x8

//hardware configuration
//end hardware configuration

//global variables
//display font for common cathode display - active high
unsigned char const led7_font[]= {
	0x3f,									//0
	0x06,									//1
	0x5b,									//2
	0x4f,									//3
	0x66,									//4
	0x6d,									//5
	0x7d,									//6
	0x07,									//7
	0x7f,									//8
	0x6f,									//9
	0x77,									//A
	0x7c,									//b
	0x39,									//C
	0x5e,									//d
	0x79,									//E
	0x71,									//F
	0x40									//???????
};

//initialize the led7 display
void led7_init(void) {
	LED_OFF(LED7_DATA);						//turn off the led
	IO_OUT(LED7_DATA_PORT, LED7_DATA);		//pins as output

	IO_CLR(HC164_PORT, HC164_SCK | HC164_SDA);	//clear sck/sda
	IO_OUT(HC164_DDR, HC164_SCK | HC164_SDA);	//sck / sda as output
}

//display a char
void led7_write(unsigned char dat) {
	static unsigned char led7_dig = 0;		//digit counter
	
	LED_OFF(LED7_DATA);						//turn off the leds
	IO_CLR(HC164_PORT, HC164_SCK);			//clear sck
	if (led7_dig) {
#if defined(LED7_CA)
		IO_CLR(HC164_PORT, HC164_SDA);		//clear sda
#else
		IO_SET(HC164_PORT, HC164_SDA);		//clear sda
#endif
		led7_dig -= 1;						//update led_dig
	} else {
#if defined(LED7_CA)
		IO_SET(HC164_PORT, HC164_SDA);		//set sda
#else
		IO_CLR(HC164_PORT, HC164_SDA);		//clear sda
#endif
		led7_dig = LED7_DIG;				//update led_dig
	}
	IO_SET(HC164_PORT, HC164_SCK);			//set sck -> strobe out sda
	LED_ON(led7_font[dat & 0x0f]);			//turn on the led
}

