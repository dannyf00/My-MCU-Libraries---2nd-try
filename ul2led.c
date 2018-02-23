#include <pic24.h>						//we use pic24f
//#include "gpio.h"
//#include "delay.h"						//software delaya routines
//#include "lcd_3wi.h"					//we use lcd 3wire interface
//#include "misc.h"						//we use ultoa_s
//#include "tmr1.h"						//we use timer1 to drive led4
#include "led4.h"						//we use 4x 7-segment leds
//#include "led8.h"						//we use 8x 7-segment leds

//hardware configuration
//end hardware configuration

//segment data
#define SEG_A           0x01                            //Segment A
#define SEG_B           0x02                            //segment b
#define SEG_C           0x04                            //segment c
#define SEG_D           0x08                            //segment d
#define SEG_E           0x10                            //segment e
#define SEG_F           0x20                            //segment f
#define SEG_G           0x40                            //segment g
#define SEG_DOT         0x80                            //segment dot

const unsigned char led_font[]= {
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | 0,            //digit 0
	SEG_B | SEG_C                         | 0,            //digit 1
	SEG_A | SEG_B | 0     | SEG_D | SEG_E | 0     | SEG_G,        //digit 2
	SEG_A | SEG_B | SEG_C | SEG_D | 0     | 0     | SEG_G,        //digit 3
	0     | SEG_B | SEG_C | 0     | 0     | SEG_F | SEG_G,        //digit 4
	SEG_A | 0     | SEG_C | SEG_D | 0     | SEG_F | SEG_G,        //digit 5
	SEG_A | 0     | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,        //digit 6
	SEG_A | SEG_B | SEG_C | 0     | 0     | 0     | 0    ,        //digit 7
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,        //digit 8
	SEG_A | SEG_B | SEG_C | 0     | 0     | SEG_F | SEG_G,        //digit 9

	SEG_A | SEG_B | SEG_C | 0     | SEG_E | SEG_F | SEG_G,        //digit A
	0     | 0     | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,        //digit b
	0     | 0     | 0     | SEG_D | SEG_E | 0     | SEG_G,        //digit c
	0     | SEG_B | SEG_C | SEG_D | SEG_E | 0     | SEG_G,        //digit d
	SEG_A | 0     | 0     | SEG_D | SEG_E | SEG_F | SEG_G,        //digit E
	SEG_A | 0     | 0     | 0     | SEG_E | SEG_F | SEG_G,        //digit F

	0     | 0     | 0     | 0     | 0     | 0     | 0    ,        //[Space]

	0     | 0     | 0     | SEG_D | 0     | 0     | 0    ,        //_
	0     | 0     | 0     | 0     | 0     | 0     | SEG_G,        //-
	SEG_A | 0     | 0     | 0     | 0     | 0     | 0    ,        //-[top]

	0     | 0     | 0     | SEG_D | 0     | 0     | SEG_G,        //_ + -
	SEG_A | 0     | 0     | 0     | 0     | 0     | SEG_G,        //_ + -[top]
	SEG_A | 0     | 0     | 0     | 0     | 0     | SEG_G,        //- + -[top]

	SEG_A | 0     | 0     | SEG_D | 0     | 0     | SEG_G,        //_ + - + -[top]

	SEG_A,                                                          //seg_a
	SEG_B,                                                          //seg_b
	SEG_C,                                                          //seg_c
	SEG_D,                                                          //seg_d
	SEG_E,                                                          //seg_e
	SEG_F,                                                          //seg_f
	SEG_G,                                                          //seg_g
	SEG_DOT,                                                          //seg_dot


	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,        //digit a
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,        //digit a
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,        //digit a
};                                                                //led segment data

//convert a number to vRAM[4]
//0 - 9999 -> 0 - 9999, no dot
//10,000 - 99,999 -> 1.000 - 9.999, dot @ dig1
//100,000 - 999,999 -> 10.00 - 99.99, dot @ dig2
//1,000,000 - 9,999,999 -> 100.0 - 999.9, dot @ dig3
//10,000,000 - 99,999,999 -> 1000. - 9999., dot @ dig4
void ul2led4(unsigned char * str, unsigned long ul) {
	unsigned char dot = 0;

	//rang-limit ul
	if (ul > 9999999ul) {ul = ul / 10000; dot = 4;}
	else if (ul > 999999ul) {ul = ul / 1000; dot = 3;}
	else if (ul > 99999ul) {ul = ul / 100; dot = 2;}
	else if (ul > 9999ul) {ul = ul / 10; dot = 1;}
	//else {/*ul = ul;*/ dot = 0;}

	//fill the str with segment information
#if defined(Common_Cathode)
        str[3] = (led_font[(unsigned char) ul % 10] | ((dot==4)?SEG_DOT:0x00)); ul = ul / 10;
	str[2] = (led_font[(unsigned char) ul % 10] | ((dot==3)?SEG_DOT:0x00)); ul = ul / 10;
	str[1] = (led_font[(unsigned char) ul % 10] | ((dot==2)?SEG_DOT:0x00)); ul = ul / 10;
	str[0] = (led_font[(unsigned char) ul % 10] | ((dot==1)?SEG_DOT:0x00));
#else
        str[3] =~(led_font[(unsigned char) ul % 10] | ((dot==4)?SEG_DOT:0x00)); ul = ul / 10;
	str[2] =~(led_font[(unsigned char) ul % 10] | ((dot==3)?SEG_DOT:0x00)); ul = ul / 10;
	str[1] =~(led_font[(unsigned char) ul % 10] | ((dot==2)?SEG_DOT:0x00)); ul = ul / 10;
	str[0] =~(led_font[(unsigned char) ul % 10] | ((dot==1)?SEG_DOT:0x00));
#endif
}

//convert a number to vRAM[8]
//0 - 99,999,999 -> 1000. - 9999., dot @ dig4
void ul2led8(unsigned char * str, unsigned long ul) {
	//unsigned char dot = 0;

	//fill the str with segment information
#if defined(Common_Cathode)
        str[7] = led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[6] = led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[5] = led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[4] = led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[3] = led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[2] = led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[1] = led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[0] = led_font[(unsigned char) ul % 10];
#else
        str[7] =~led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[6] =~led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[5] =~led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[4] =~led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[3] =~led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[2] =~led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[1] =~led_font[(unsigned char) ul % 10]; ul = ul / 10;
	str[0] =~led_font[(unsigned char) ul % 10];
#endif
}
