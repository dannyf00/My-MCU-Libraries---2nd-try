//#include <pic24.h>									//we use pic24f
#include "key.h"										//we use key debouncing routines

//hardware configuration
//end hardware configuration


//global defines

//global variables

//initialize a key
void key_init(KEY_TypeDef *key, KEY_STATE (*keyread)(void)) {
	key->keyread=keyread;								//install key read function
	key->state = KEY_NOTPRESSED;						//default state of key
	//key->cnt_key = 0;									//initialized counter
}

//return key state
KEY_STATE key_get(KEY_TypeDef *key) {
	return key->state;
}

//read key status
void key_read(KEY_TypeDef *key) {
	KEY_STATE key_read;

	key_read = (*(key->keyread))();						//read the key state now
	switch (key->state) {
	case KEY_NOTPRESSED: 								//current key is not pressed
		if (key_read == KEY_PRESSED) {					//key is pressed, start debouncing
			key->state = KEY_BOUNCE;
			key->cnt_key = 0;							//reset counter
		}
		break;
	case KEY_BOUNCE:
		if (key_read == KEY_PRESSED) {					//key is not pressed
			key->cnt_key += 1;							//increment counter
			if (key->cnt_key >= CNT_KEY_PRESSED) {		//enough continuous presses have been reached
				key->state = KEY_PRESSED;				//change the state
				key->cnt_press = 0;						//reset press counter
			};
		} else {										//key is still pressed
			key->state = KEY_NOTPRESSED;				//key is no longer pressed
			//key->cnt_key = 0;							//start  counting key presses
			}
		break;
	case KEY_PRESSED: 									//key is pressed.
	case KEY_SHORTPRESSED:
	case KEY_LONGPRESSED:
		if (key_read == KEY_PRESSED) {					//key remains pressed
			key->cnt_press+=1;							//increment press count
			if (key->cnt_press >= CNT_KEY_SHORTPRESSED) key->state = KEY_SHORTPRESSED;
			if (key->cnt_press >= CNT_KEY_LONGPRESSED) key->state = KEY_LONGPRESSED;
		} else {										//key is not pressed
			key->state = KEY_NOTPRESSED;
		}
		break;
	case KEY_DOUBLEPRESSED:	break;						//double pressed? not processed now
	}
}

