//analog keypad reads
#include "adc.h"								//we use adc for the buttons
#include "shield_keypad.h"						//we use keypad

//shield has 5 keys
//reset the key
void keypad_init(void) {
	adc_init();									//reset the adc module
}

//reset the keypad_
//return values
//  0: no key pressed
//  1: RIGHT
//  2: UP
//  3: DOWN
//  4: LEFT
//  5: SELECT
//adc values are:
//  0: RIGHT
//145: UP
//330: DOWN
//506: LEFT
//741: SELECT
unsigned short keypad_read(void) {
	unsigned short tmp=adc_read(KEYPAD_ADC);		//read adc channel
	//return tmp;								//if you need the raw adc value
	if (tmp < (  0 + 145) / 2) return 1;		//RIGHT pressed
	if (tmp < (145 + 330) / 2) return 2;		//UP pressed
	if (tmp < (330 + 506) / 2) return 3;		//DOWN pressed
	if (tmp < (506 + 741) / 2) return 4;		//LEFT pressed
	if (tmp < (741 + 1023) / 2) return 5;		//SELECT pressed
	return 0;									//no key is pressed
}
