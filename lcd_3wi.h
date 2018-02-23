#ifndef __LCD_3WI_H
#define __LCD_3WI_H

/*
 *	LCD interface header file
 *	See lcd.c for more info
 */

#include "gpio.h"					//we use gpio
#include "delay.h"					//we use software delays

//hardware configuration
#define LCD_8BIT		0			//1=set the lcd in 8BIT mode, 0=in 4bit mode

#define LCD_PORT		LATB			//lcd pins on portc
#define LCD_DIR			TRISB		//output direction
#define LCD_EN			(1<<1)		//LCD_EN on RC5
#define LCD_SCK			(1<<2)		//LCD_CLK on RC6
#define LCD_SI			(1<<3)		//spi data in on RC7

//describe how LCD's data pins are connected to 164's pins
#define LCD_D0				HC164_Q0			//unused
#define LCD_D1				HC164_Q1			//unused
#define LCD_D2				HC164_Q2			//unused
#define LCD_D3				HC164_Q3			//unused
#define LCD_D4				HC164_Q7			//LCD's D4 connected to LCD_PORT's 7th bit
#define LCD_D5				HC164_Q6			//LCD's D5 connected to LCD_PORT's 0th bit
#define LCD_D6				HC164_Q5			//LCD's D6 connected to LCD_PORT's 5th bit
#define LCD_D7				HC164_Q4			//LCD's D7 connected to LCD_PORT's 2nd bit
//#define LCD_RS		Q3			//LCD_RS to 164's Q3/Qd
//end hardware configuration

#define LCD_RS			LCD_SI		//RS pin tied to the SO pin
#define LCD_SET(bits)	LCD_PORT |= (bits)		//set bits on lcd_port
#define LCD_CLR(bits)	LCD_PORT &=~(bits)		//clear bits on lcd_port
#define LCD_FLP(bits)	LCD_PORT ^= (bits)		//flip bits on lcd_port
//if move the pins to a different port, need to revise TRISx as well

#define LCD_Line0		0x00		//lcd line 1
#define LCD_Line1		0x40		//lcd line 2
//for 16-char displays
#define LCD_Line2		0x10		//lcd line 3	0x14 for 20-char displays
#define LCD_Line3		0x50		//lcd line 4	0x54 for 20-char displays

//hardware configuration

//do not change the definitions below for Q0..7
#define HC164_Q0				(1<<0)
#define HC164_Q1				(1<<1)
#define HC164_Q2				(1<<2)
#define HC164_Q3				(1<<3)
#define HC164_Q4				(1<<4)
#define HC164_Q5				(1<<5)
#define HC164_Q6				(1<<6)
#define HC164_Q7				(1<<7)


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

void lcd_putch(unsigned char ch);

void lcd_display(unsigned char LCD_Line, unsigned char * str);

/*	Set the cursor position */

#define	lcd_cursor(x)	lcd_write(((x)&0x7F)|0x80)

//load a 8-byte data to cgram
void lcd_cgram(unsigned char cgaddr, const unsigned char * cgdata);

#endif	//lcd_3wi_h
