#include <pic24.h>						//we use pic24f
#include "gpio.h"
#include "led4.h"						//we use led4

//hardware configuration
//end hardware configuration

//control digit pins
//common cathod
#if defined(Common_Cathode)
#define LED_ON(leds)    LED_PORT &=~(leds)              //turn on leds, common cathod (active low)
#define LED_OFF(leds)   LED_PORT |= (leds)              //turn off leds, common cathod (active low)
#else
#define LED_OFF(leds)    LED_PORT &=~(leds)              //turn on leds, common cathod (active low)
#define LED_ON(leds)   LED_PORT |= (leds)              //turn off leds, common cathod (active low)
#endif

//#define MAX_DIGs        4                               //total digit of led displays / digits
//hardware configuration

unsigned char vRAM[MAX_DIGs] = {0, 0, 0, 0};            //display buffer

//initialize the led
void led_init(void) {
	IO_CLR(LED_PORT, LEDs | LED1 | LED2 | LED3 | LED4); //clear pins
	IO_OUT(LED_DDR, LEDs | LED1 | LED2 | LED3 | LED4);  //pins as output

}

//display the string
void led_display(void) {
	static unsigned char i=0;

	LED_OFF(LED1 | LED2 | LED3 | LED4);                                      //turn off the leds
        LEDs_OUT(vRAM[i]);                                  //output the data, vRAM[] contains the display segment info

        switch (i) {                                        //turn on the leds and advance led counter
	case 0:
		LED_ON(LED1);
		i = 1;
		break;
	case 1:
		LED_ON(LED2);
		i = 2;
		break;
	case 2:
		LED_ON(LED3);
		i = 3;
		break;
	case 3:
		LED_ON(LED4);
		i = 0;
		break;
	};
}
