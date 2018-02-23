#ifndef LED8_H_INCLUDED
#define LED8_H_INCLUDED

//module to drive 8 7segment led
//common cathod

//hardware configuration
#define MAX_DIGs        8                               //total digit of led displays / digits

//uncomment to turn on common anode
//#define LED_CC		                                  //common cathod: default driver.

#define SEG_PORT        PORTC
#define SEG_DDR         TRISC
#define SEGs            0xff							//segment pins lowest 8 bits

//define digits
//use lower digits first
//if higher pins are not used, define them as the lower digit pins
#define DIG_PORT		PORTB
#define DIG_DDR			TRISB
#define DIG1            (1<<0)
#define DIG2            (1<<1)
#define DIG3            (1<<2)
#define DIG4            (1<<3)
#define DIG5            (1<<4)
#define DIG6            (1<<5)
#define DIG7            (1<<6)
#define DIG8            (1<<7)

//control digit pins

//common cathod
//#define LED_ON(leds)    LED_PORT &=~(leds)              //turn on leds, common cathod (active low)
//#define LED_OFF(leds)   LED_PORT |= (leds)              //turn off leds, common cathod (active low)
//end hardware configuration

//hardware configuration

extern unsigned char lRAM[8/*MAX_DIGs*/];            	//display buffer

//initialize the led
void led_init(void);

//display the string
void led_display(void);

#endif // LED4_H_INCLUDED
