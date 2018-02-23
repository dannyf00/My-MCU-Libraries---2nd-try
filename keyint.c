//#include <pic24.h>									//we use pic24f
#include "keyint.h"										//we use key debouncing routines / kenneth kuhn's integrator

//hardware configuration
//end hardware configuration


//global defines

//global variables

//initialize a key
void key_init(KEY_TypeDef *key, KEY_STATE (*keyread)(void)) {
	key->keyread=keyread;								//install key read function
	//key->state = KEY_NOTPRESSED;						//default state of key
	key->cnt_key = 0;									//initialized counter / integrator
}

//return key state
KEY_STATE key_get(KEY_TypeDef *key) {
	return (key->cnt_key == CNT_MAX)?KEY_PRESSED:KEY_NOTPRESSED;	//could be made to return KEY_BOUNCE
	//if you want to respond instantly to key presses
	//return (key->cnt_key != 0      )?KEY_PRESSED:KEY_NOTPRESSED;	//could be made to return KEY_BOUNCE
}

//read key status
void key_read(KEY_TypeDef *key) {
	//update the integrator [0..CNT_MAX]
	if ((*(key->keyread))()==KEY_NOTPRESSED) key->cnt_key -= (key->cnt_key <= 0)?0:1;		//decrement cnt_key if key is not pressed
	else key->cnt_key += (key->cnt_key >= CNT_MAX)?0:1;										//increment cnt_key if key is pressed

}

