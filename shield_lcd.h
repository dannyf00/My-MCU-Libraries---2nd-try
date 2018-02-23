#ifndef __SHIELD_KEYPAD_H
#define __SHIELD_KEYPAD_H

/*
 *	LCD interface header file
 *	for arduino lcd shields
 *	See lcd.c for more info
 */

#include "gpio.h"								//we use io functions
#include "delay.h"								//we use software delay

//hardware configuration
//describe how LCD's data pins are connected to the mcu
//for lcd d4 pin
#define LCDD4_PORT			PORTD
#define LCDD4_DDR			DDRD
#define LCDD4				(1<<7)				//LCD's LCDD4 connected to LCD_PORT's 4th bit

//for lcd d5 pin
#define LCDD5_PORT			PORTD
#define LCDD5_DDR			DDRD
#define LCDD5				(1<<6)				//LCD's LCDD4 connected to LCD_PORT's 4th bit

//for lcd d6 pin
#define LCDD6_PORT			PORTD
#define LCDD6_DDR			DDRD
#define LCDD6				(1<<5)				//LCD's LCDD4 connected to LCD_PORT's 4th bit

//for lcd d7 pin
#define LCDD7_PORT			PORTD
#define LCDD7_DDR			DDRD
#define LCDD7				(1<<4)				//LCD's LCDD4 connected to LCD_PORT's 4th bit

//for lcd EN pin
#define LCDEN_PORT			PORTB
#define LCDEN_DDR			DDRB
#define LCDEN				(1<<0)				//LCD's LCDD4 connected to LCD_PORT's 4th bit

//for lcd RS pin
#define LCDRS_PORT			PORTB
#define LCDRS_DDR			DDRB
#define LCDRS				(1<<2)				//LCD's LCDD4 connected to LCD_PORT's 4th bit

//#define KEYPAD_ADC			ADC_AN0					//buttons on adc0
//end hardware configuration

//rw pin tied to ground

#define LCD_Line0			0x00		//lcd line 1
#define LCD_Line1			0x40		//lcd line 2
//for 16-char displays
#define LCD_Line2			0x10		//lcd line 3	0x14 for 20-char displays
#define LCD_Line3			0x50		//lcd line 4	0x54 for 20-char displays

//LCD control signals
/* Display ON/OFF Control defines */
#define LCD_DISPLAY_ON         	0x0f		//0b00001111  /* Display on      */
#define LCD_DISPLAY_DOFF        0x0b		//0b00001011  /* Display off     */
#define LCD_CURSOR_ON   		0x0f		//0b00001111  /* Cursor on       */
#define LCD_CURSOR_OFF  		0x0d		//0b00001101  /* Cursor off      */
#define LCD_BLINK_ON    		0x0f		//0b00001111  /* Cursor Blink    */
#define LCD_BLINK_OFF   		0x0e		//0b00001110  /* Cursor No Blink */

/* Cursor or Display Shift defines */
//#define LCD_SHIFT_CURSOR_LEFT    0b00010011  /* Cursor shifts to the left   */
//#define LCD_SHIFT_CURSOR_RIGHT   0b00010111  /* Cursor shifts to the right  */
//#define LCD_SHIFT_DISPLAY_LEFT   0b00011011  /* Display shifts to the left  */
//#define LCD_SHIFT_DISPLAY_RIGHT  0b00011111  /* Display shifts to the right */

/* entry mode set */
#define LCD_SHIFT_CURSOR_LEFT   0x05		//0b00000101  /* Cursor shifts to the left   */
#define LCD_SHIFT_CURSOR_RIGHT  0x07		//0b00000111  /* Cursor shifts to the right  */
#define LCD_SHIFT_DISPLAY_ON   	0x07		//0b00000111  /* Display shifts to the left  */
#define LCD_SHIFT_DISPLAY_OFF   0x06		//0b00000110  /* Display shifts to the right */

/* Function Set defines */
#define LCD_FOUR_BIT   			0x2f		//0b00101111  /* 4-bit Interface               */
#define LCD_EIGHT_BIT  			0x3f		//0b00111111  /* 8-bit Interface               */
#define LCD_LINE_5X7   			0x33		//0b00110011  /* 5x7 characters, single line   */
#define LCD_LINE_5X10  			0x37		//0b00110111  /* 5x10 characters               */
#define LCD_LINES_5X7  			0x3b		//0b00111011  /* 5x7 characters, multiple line */

//cgram
#define LCD_CGRAM				0x40		//0b01000000  /* to send cgram data


/* write a byte to the LCD in 4 bit mode */
void lcd_write(unsigned char, unsigned char rs);

/* Clear and home the LCD */
void lcd_clear(void);

/* write a string of characters to the LCD */
void lcd_puts(unsigned char * s);

/* Go to the specified position */
void lcd_goto(unsigned char pos);

/* intialize the LCD - call before anything else */
void lcd_init(void);

/* write a char on the lcd*/
void lcd_putch(unsigned char ch);

/*display a str on the lcd*/
void lcd_display(unsigned char LCD_Line, unsigned char * str);

/*	Set the cursor position */
#define	lcd_cursor(x)	lcd_write(((x)&0x7F)|0x80)

//load a 8-byte data to cgram
void lcd_cgram(unsigned char cgaddr, unsigned char * cgdata);

#endif
