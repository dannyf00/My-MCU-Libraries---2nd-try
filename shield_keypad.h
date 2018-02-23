#ifndef __SHIELD_KEYPAD_H
#define __SHIELD_KEYPAD_H

//hardware configuration

//adc channel for the keypads//buttons
#define KEYPAD_ADC			ADC_AN0					//buttons on adc0

//button definitions
#define BUTTON_NOPRESS		0
#define BUTTON_RIGHT		1
#define BUTTON_UP			2
#define BUTTON_DOWN			3
#define BUTTON_LEFT			4
#define BUTTON_SELECT		5
//end hardware configuration

//shield has 5 keys
//reset the key
void keypad_init(void);
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
unsigned short keypad_read(void);
#endif
