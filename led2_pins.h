/* 
 * File:   led2_bits.h
 * Author: Ken
 *
 * Created on April 15, 2014, 9:27 PM
 */

#ifndef LED2_PINS_H
#define	LED2_PINS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "gpio.h"

    
//hardware configuration
//digit pins for digit 1/2
#define LED4_PIN1			GPIOA->B0
#define LED4_PIN2			GPIOA->B1
#define LED4_PIN3			GPIOA->B2
#define LED4_PIN4			GPIOA->B3
#define LED4_PIN5			GPIOA->B4
#define LED4_PIN6			GPIOB->B2
#define LED4_PIN7			GPIOB->B3
#define LED4_PIN8			GPIOB->B4
#define LED4_PIN9			GPIOB->B5
#define LED4_PIN10			GPIOB->B6

//set up the direction registers
#define LED4_DDRs()			do {IO_OUT(TRISA, 0x3f); IO_OUT(TRISB, 0x7e); } while (0)

//#define LED_CA                          0					//1=common anode; 0=common cathode
//end hardware configuration

    
#if 0
//digit definitions
//4-digit led connection
//led pin connection
//pin 1 = SEGE
//pin 2 = SEGD
//pin 3 = SEGDOT
//pin 4 = SEGC
//pin 5 = SEGG
//pin 6 = DIG4
//pin 7 = SEGB
//pin 8 = DIG3
//pin 9 = DIG2
//pin 10= SEGF
//pin 11= SEGA
//pin 12= DIG1

//digit connection
#define LED_DIG1		LED4_PIN12
#define LED_DIG2		LED4_PIN9
#define LED_DIG3		LED4_PIN8
#define LED_DIG4		LED4_PIN6

//segment connection
#define LED_SEGA		LED4_PIN11
#define LED_SEGB		LED4_PIN7
#define LED_SEGC		LED4_PIN4
#define LED_SEGD		LED4_PIN2
#define LED_SEGE		LED4_PIN1
#define LED_SEGF		LED4_PIN10
#define LED_SEGG		LED4_PIN5
#define LED_SEGDOT		LED4_PIN3

//digit control
#define DIG_ON(pin)		pin= LED_CA			//turn on a digit
#define DIG_OFF(pin)		pin=!LED_CA		//turn off a digit

//segment control
#define SEG_ON(pin)		pin=!LED_CA		//turn on a segment
#define SEG_OFF(pin)		pin= LED_CA		//turn off a segment
#endif
    
//global defines

//global variables
extern unsigned char lRAM[];
extern const unsigned char ledfont_num[];               //led font for numerical values, '0'..'f', including blanks
extern const unsigned char ledfont_alpha[];             //led font for alphabeta values, 'a'..'z', including blanks
#ifndef LED_CA
extern unsigned char LED_CA;                            //1=led common anode, 0=common cathode
#endif

//initialize the pins
void led_init(void);

//display the ledram
void led_display(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LED4_PINS_H */

