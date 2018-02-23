#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

//generic switch / key debouncing routines
//support multiple keys / switches
//five states:
// 1. NOTPRESSED
// 2. BOUNCE
// 3. PRESSED
// 4. SHORTPRESSED
// 5. LONGPRESSED
// 6. DOUBLEPRESSED - not implemented yet

//#include "gpio.h"

//hardware configuration
//end hardware configuration


//global defines
#define CNT_KEY_PRESSED					10		//number of continuous key presses to be "pressed"
#define CNT_KEY_SHORTPRESSED			5		//number of continuous key presses to be "short pressed"
#define CNT_KEY_LONGPRESSED				10		//number of continuous key presses to be "long pressed"

typedef enum {
	KEY_NOTPRESSED,								//key not pressed
	KEY_PRESSED,								//key is pressed
	KEY_SHORTPRESSED,							//key is short pressed
	KEY_LONGPRESSED,							//long pressed
	KEY_DOUBLEPRESSED,							//key double pressed - not implemented
	KEY_BOUNCE									//key is bouncing
} KEY_STATE;

typedef struct {
	KEY_STATE (*keyread)(void);					//function pointer to get key state (call back)
	KEY_STATE state;							//current state of the key
	int cnt_key;								//counter for current state
	int cnt_press;								//count for press
} KEY_TypeDef;									//key definition

//global variables

//initialize a key
//user will have to provide keyread() routine
void key_init(KEY_TypeDef *key, KEY_STATE (*keyread)(void));

//return key state
KEY_STATE key_get(KEY_TypeDef *key);

//read key status
void key_read(KEY_TypeDef *key);

#endif /* KEY_H_INCLUDED */
