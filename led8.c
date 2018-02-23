//#include <pic24.h>						//we use pic24f
//#include <avr/io.h>						//we use gcc-avr
#include <htc.h>						//we use picc
#include "gpio.h"
#include "led8.h"						//we use led8

//hardware configuration
//end hardware configuration

//#define MAX_DIGs        4                               //total digit of led displays / digits
//hardware configuration

//control digit pins
//common cathod
#if defined(LED_CC)
#define DIG_ON(leds)    DIG_PORT &=~(leds)              //turn on leds, common cathod (active low)
#define DIG_OFF(leds)   DIG_PORT |= (leds)              //turn off leds, common cathod (active low)
#define SEG_OUT(val)	SEG_PORT = (val)
#else
#define DIG_OFF(leds)	DIG_PORT &=~(leds)              //turn on leds, common cathod (active low)
#define DIG_ON(leds)	DIG_PORT |= (leds)              //turn off leds, common cathod (active low)
#define SEG_OUT(val)	SEG_PORT =~(val)
#endif

unsigned char lRAM[8/*MAX_DIGs*/];            //display buffer

//initialize the led
void led_init(void) {
	//initilize the segments
    IO_CLR(SEG_PORT, SEGs); //clear pins
    IO_OUT(SEG_DDR, SEGs);  //pins as output

    //initialize the digits
    //IO_CLR(DIG_PORT, DIG1 | DIG2 | DIG3 | DIG4 | DIG5 | DIG6 | DIG7 | DIG8); //clear pins
    DIG_OFF(DIG1 | DIG2 | DIG3 | DIG4 | DIG5 | DIG6 | DIG7 | DIG8);
    IO_OUT(DIG_DDR, DIG1 | DIG2 | DIG3 | DIG4 | DIG5 | DIG6 | DIG7 | DIG8);  //pins as output

}

//display the string
void led_display(void) {
    static unsigned char i=0;

    DIG_OFF(DIG1 | DIG2 | DIG3 | DIG4 | DIG5 | DIG6 | DIG7 | DIG8);                                      //turn off the leds
    SEG_OUT(lRAM[i]);                                  //output the data, vRAM[] contains the display segment info
    switch (i) {                                        //turn on the leds and advance led counter
	    case 0: DIG_ON(DIG1); break;
	    case 1: DIG_ON(DIG2); break;
	    case 2: DIG_ON(DIG3); break;
	    case 3: DIG_ON(DIG4); break;
	    case 4: DIG_ON(DIG5); break;
	    case 5: DIG_ON(DIG6); break;
	    case 6: DIG_ON(DIG7); break;
	    case 7: DIG_ON(DIG8); break;
    };
	i += 1;								//increment i
	if (i==MAX_DIGs) i=0;				//reset i+
}

