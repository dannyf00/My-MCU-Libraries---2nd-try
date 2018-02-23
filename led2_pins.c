#include "led2_pins.h"				  //we use 4-digit 7-segment leds

//hardware configuration
//end hardware configuration

//NOTE: there are two popular connections / pinouts for 2-digit 7segment leds
//implemented below is just one of them
//digit definitions
//2-digit led connection
//led pin connection
//pin 1 = SEGG
//pin 2 = SEGDOT
//pin 3 = SEGA
//pin 4 = SEGF
//pin 5 = DIG2
//pin 6 = SEGD
//pin 7 = SEGE
//pin 8 = SEGC
//pin 9 = SEGB
//pin 10= DIG1

//digit connection
#define LED_DIG1		LED4_PIN10
#define LED_DIG2		LED4_PIN5

//segment connection
#define LED_SEGA		LED4_PIN3
#define LED_SEGB		LED4_PIN9
#define LED_SEGC		LED4_PIN8
#define LED_SEGD		LED4_PIN6
#define LED_SEGE		LED4_PIN7
#define LED_SEGF		LED4_PIN4
#define LED_SEGG		LED4_PIN1
#define LED_SEGDOT		LED4_PIN2

//digit control
#define DIG_ON(pin)		pin= LED_CA			//turn on a digit
#define DIG_OFF(pin)	pin=!LED_CA		//turn off a digit

//segment control
#define SEG_ON(pin)		pin=!LED_CA		//turn on a segment
#define SEG_OFF(pin)	pin= LED_CA		//turn off a segment

//global defines

//global variables
#ifndef LED_CA
unsigned char LED_CA = 0;                               //1=common anode, 0=common cathode
#endif
unsigned char lRAM[2];				//led display buffer
//led font.
//SEGDOT = 0x80
//SEGG   = 0x40
//SEGF   = 0x20
//SEGE   = 0x10
//SEGD   = 0x08
//SEGC   = 0x04
//SEGB   = 0x02
//SEGA   = 0x01
//led font for numerical display '0'..'9''a'..'f'
const unsigned char ledfont_num[]={		//led font, for common anode
	0x3f,								//'0'
	0x06,								//'1'
	0x5b,								//'2'
	0x4f,								//'3'
	0x66,								//'4'
	0x6d,								//'5'
	0x7d,								//'6'
	0x07,								//'7'
	0x7f,								//'8'
	0x6f,								//'9'
	0x5f,								//'a'
	0x7c,								//'b'
	0x58,								//'c'
	0x5e,								//'d'
	0x79,								//'e'
	0x71,								//'f'
	0x00								//' ' blank
};
//led font for alphabetic display 'a'..'z'
const unsigned char ledfont_alpha[]={		//led font, for common anode
	0x5f,								//'a'
	0x7c,								//'b'
	0x58,								//'c'
	0x5e,								//'d'
	0x79,								//'e'
	0x71,								//'f'
	0x6f,								//'g'
	0x07,								//'h'
	0x74,								//'i'
	0x0e,								//'j'
	0x00,								//'k'
	0x38,								//'l'
	0x00,								//'m'
	0x54,								//'n'
	0x5c,								//'o'
	0x73,								//'p'
    0x67,								//'q'
    0x77,								//'r'
    0x6d,								//'s'
    0x00,								//'t'
    0x1c,								//'u'
    0x00,								//'v'
    0x00,								//'w'
    0x00,								//'x'
    0x6e,								//'y'
    0x00,								//'z'
	0x00								//' ' blank
};

//initialize the pins
void led_init(void) {
	//turn off the digits
	DIG_OFF(LED_DIG1);
	DIG_OFF(LED_DIG2);

	//turn off the segments, optional
	SEG_OFF(LED_SEGA);
	SEG_OFF(LED_SEGB);
	SEG_OFF(LED_SEGC);
	SEG_OFF(LED_SEGD);
	SEG_OFF(LED_SEGE);
	SEG_OFF(LED_SEGF);
	SEG_OFF(LED_SEGG);
	SEG_OFF(LED_SEGDOT);

	//set all pins to output
	//put your code here
	LED4_DDRs();
}

//display the ledram
void led_display(void) {
	static unsigned char dig;		//current digit
	unsigned char tmp;

	//turn off the digits
	DIG_OFF(LED_DIG1);
	DIG_OFF(LED_DIG2);

	tmp=lRAM[dig];
		//tmp=0x00;
	//turn on/off the segments
	if (tmp & 0x01) SEG_ON(LED_SEGA); else SEG_OFF(LED_SEGA);
	if (tmp & 0x02) SEG_ON(LED_SEGB); else SEG_OFF(LED_SEGB);
	if (tmp & 0x04) SEG_ON(LED_SEGC); else SEG_OFF(LED_SEGC);
	if (tmp & 0x08) SEG_ON(LED_SEGD); else SEG_OFF(LED_SEGD);
	if (tmp & 0x10) SEG_ON(LED_SEGE); else SEG_OFF(LED_SEGE);
	if (tmp & 0x20) SEG_ON(LED_SEGF); else SEG_OFF(LED_SEGF);
	if (tmp & 0x40) SEG_ON(LED_SEGG); else SEG_OFF(LED_SEGG);
	if (tmp & 0x80) SEG_ON(LED_SEGDOT); else SEG_OFF(LED_SEGDOT);

	//turn on the digit
	switch (dig) {
		case 0: DIG_ON(LED_DIG1); dig=1; break;
		case 1: DIG_ON(LED_DIG2); dig=0; break;
		default: DIG_ON(LED_DIG1); dig=1; break;
	}
}

