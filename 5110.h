#ifndef _5110_H
#define _5110_H

#include "gpio.h"                           //we use gpio functions
#include "delay.h"                          //we use software delays

//hardware configuration
// change this section if your pin connection is different
//#define lcd_port	PORTB			//lcd connections on PortC
//#define lcd_dir		DDRB			//lcd_port's direction register
#define lcdres_port		PORTC
#define lcdres_ddr		TRISC
#define lcdres 			(1<<4)			//lcd_res connected to p0, pin13. Not ncessary as long as it is held high

#define lcdsda_port		PORTC
#define lcdsda_ddr		TRISC
#define lcdsda 			(1<<1)			//lcd_sda connected to p1, pin14

#define lcdsclk_port	PORTC
#define lcdsclk_ddr		TRISC
#define lcdsclk 		(1<<0)			//lcd_sclk connected to p2, pin21

#define lcddc_port		PORTC
#define lcddc_ddr		TRISC
#define lcddc 			(1<<2)			//lcd_dc connected to p3, pin22

#define lcdcs_port		PORTC
#define lcdcs_ddr		TRISC
#define lcdcs 			(1<<3)			//lcd_cs/sce connected to p4, pin23

#define lcdled_port		PORTA
#define lcdled_ddr		TRISA
#define lcdled			(1<<7)			//led backlight connected to p52, pin18. not used. should be connected to LED-
//end hardware configuration

//global defines
#define LCD_CMD			0				//dc=0 to send lcd command
#define LCD_DATA		1				//dc=1 to send lcd data

#define LCD_NORMAL		0x00		// normal black on green
#define LCD_UNDERLINE	0x80
#define LCD_STRIKE		0x08
#define LCD_OVERLINE	0x01
#define LCD_REVERSE		0xff		//green on black
#define LCD_SET			0x02		//set
#define LCD_CLR			0x04		//clear
#define LCD_XOR			0x08		//xor

//LCD display lines
#define LCD_Line0		0		//1st line of lcd display
#define LCD_Line1		1		//1st line of lcd display
#define LCD_Line2		2		//1st line of lcd display
#define LCD_Line3		3		//1st line of lcd display
#define LCD_Line4		4		//1st line of lcd display
#define LCD_Line5		5		//1st line of lcd display
#define LCD_Line6		6		//1st line of lcd display
#define LCD_Line7		7		//1st line of lcd display

//global variables
extern const unsigned char font5x7[];

//write to the lcd
void lcd_write(uint8_t dat);


//write command
void lcd_write_command(uint8_t cmd);

//write data
void lcd_write_data(uint8_t dat);


//go to xy
//row: 0..5
//col: 0..83 (6 columns per char)
void lcd_gotoxy(uint8_t row, uint8_t col);

//send a char to current position
void lcd_chr(uint8_t chr, uint8_t attribute);

//put strings
void lcd_str(uint8_t row, uint8_t col, uint8_t *str, uint8_t attribute);

/**********************************************************
           Write a string at current screen position
**********************************************************/
//void lcd_display_attr(uint8_t LCD_Line, uint8_t *str, uint8_t attribute);
#define lcd_display_attr(LCD_Line, str, attribute)	lcd_str(LCD_Line, 0, str, attribute)
#define lcd_display_normal(LCD_Line, str)			lcd_display_attr(LCD_Line, str, LCD_NORMAL)
#define lcd_display_underline(LCD_Line, str)		lcd_display_attr(LCD_Line, str, LCD_UNDERLINE)
#define lcd_display_strike(LCD_Line, str)			lcd_display_attr(LCD_Line, str, LCD_STRIKE)
#define lcd_display_overline(LCD_Line, str)			lcd_display_attr(LCD_Line, str, LCD_OVERLINE)
#define lcd_display_reverse(LCD_Line, str)			lcd_display_attr(LCD_Line, str, LCD_REVERSE)
#define lcd_display(LCD_Line, str)					lcd_display_normal(LCD_Line, str)

//clear the lcd
void lcd_clear(void);

//soft reset the lcd
void lcd_reset(void);

//reset the lcd
void lcd_init(void);

//turn on the led - active low
#define lcd_ledon()			do {IO_CLR(lcdled_port, lcdled); IO_OUT(lcdled_ddr, lcdled);} while (0)
#define lcd_ledoff()		do {IO_SET(lcdled_port, lcdled); IO_OUT(lcdled_ddr, lcdled);} while (0)

#define lcd_display(line, str)		lcd_display_attr(line, str, LCD_NORMAL)

//send an image to current position
void lcd_img(uint8_t *img, uint8_t col_pix);
#endif
