#ifndef LED4_H_INCLUDED
#define LED4_H_INCLUDED

//module to drive 4 7segment led

//hardware configuration
//uncomment to turn on common anode
#define Common_Cathode                                  //common cathod: default driver.

#define MAX_DIGs        4                               //total digit of led displays / digits

#define LED_PORT        PORTB
#define LED_DDR         TRISB
#define LEDs            0x00ff							//segment pins lowest 8 bits
#define LED1            (1<<10)
#define LED2            (1<<11)
#define LED3            (1<<12)
#define LED4            (1<<13)

//output segment data
#define LEDs_OUT(val)   LED_PORT = (LED_PORT & ~LEDs) | (val)
//end hardware configuration

//hardware configuration

extern unsigned char vRAM[MAX_DIGs];            //display buffer

//initialize the led
void led_init(void);

//display the string
void led_display(void);

#endif // LED4_H_INCLUDED
