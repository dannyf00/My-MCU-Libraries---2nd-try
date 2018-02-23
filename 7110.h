#ifndef _7110_H
#define _7110_H

#include "gpio.h"				//we use gpio modules
#include "delay.h"				//we use software delays


// hardware configuration
// change this section if your pin connection is different
#define lcdres_port		PORTC			//lcd connections on PortC
#define lcdres_ddr		TRISC			//lcd_port's direction register
#define lcdres 			(1<<4)			//lcd_res connected to p0, pin13. Not ncessary as long as it is held high

#define lcdsda_port		PORTC			//lcd connections on PortC
#define lcdsda_ddr		TRISC			//lcd_port's direction register
#define lcdsda 			(1<<1)			//lcd_sda connected to p1, pin14

#define lcdsclk_port	PORTC			//lcd connections on PortC
#define lcdsclk_ddr		TRISC			//lcd_port's direction register
#define lcdsclk 		(1<<0)			//lcd_sclk connected to p2, pin21

#define lcddc_port		PORTC			//lcd connections on PortC
#define lcddc_ddr		TRISC			//lcd_port's direction register
#define lcddc 			(1<<2)			//lcd_dc connected to p3, pin22

#define lcdcs_port		PORTC			//lcd connections on PortC
#define lcdcs_ddr		TRISC			//lcd_port's direction register
#define lcdcs	 		(1<<3)			//lcd_cs connected to p4, pin23

#define lcdled_port		PORTA			//lcd connections on PortC
#define lcdled_ddr		TRISA			//lcd_port's direction register
#define lcdled			(1<<3)			//led backlight connected to p52, pin18. not used. should be connected to LED-
// end hardware configuration


// display attributes
#define LCD_NORMAL		0x00		// normal black on green
#define LCD_UNDERLINE	0x80
#define LCD_STRIKE		0x08
#define LCD_OVERLINE	0x01
#define LCD_REVERSE		0xff		//green on black
#define LCD_SET			0x02		//set
#define LCD_CLR			0x04		//clear
#define LCD_XOR			0x08		//xor

#define negative_lcd    lcd_write_command(lcd_reverse)
#define normal_lcd      lcd_write_command(lcd_normal)

//LCD display lines
#define LCD_Line0		0		//1st line of lcd display
#define LCD_Line1		1		//1st line of lcd display
#define LCD_Line2		2		//1st line of lcd display
#define LCD_Line3		3		//1st line of lcd display
#define LCD_Line4		4		//1st line of lcd display
#define LCD_Line5		5		//1st line of lcd display
#define LCD_Line6		6		//1st line of lcd display
#define LCD_Line7		7		//1st line of lcd display


/**********************************************************
               LCD Commands
**********************************************************/
#define pow_ctrl				0x20	// (16) power control set value (contrast level --> 0x00 lightest to 0x3F darkest), from 0b00101000 to 0b00101111.
#define v5_ratio				0x20	//(17) V5 resistor ratio, from 0b00100000 to 0b00100111. need to add some ratio
#define start_line				0x40	// start line - set the display line start address.
#define elec_vol				0x81	// (18) electronic volume mode, followed by a number 0x00 .. 0x3f. used to enter the mode to select brightness
#define adc_normal 				0xA0	// (8) <ADC select> (0xA1/0b10100001 reverse lcd - 0xA0/0b10100000 select normal)
#define adc_reverse				0xA1
#define lcd_bias_1_over_9		0xA2	// (11) lcd bias (1/9 0xA2/0b10100010 - 1/7 0xA3/0b10100011)
#define lcd_bias_1_over_7		0xA3
#define lcd_all_off				0xA4	//turn all pixels off, normal display
#define lcd_all_on				0xA5	//lcd all points on - turn on all pixels. 0xA4: normal display.
#define lcd_normal 				0xA6 	// 0b10100110 = 0xA6, lcd in normal display mode (0xA7/0b10100111 negative mode)
#define lcd_reverse				0xA7	// 0b10100111 = 0xa7, lcd in reverse display
#define lcd_off					0xAE	//
#define lcd_on					0xAF	// lcd on - display on. 0xAE: display off.
#define comm_normal 			0xC0	// (15) common output normal (0xC8 reverse)
#define comm_reverse 			0xC8	// reverse horizontally
#define lcd_nop					0xE3	// nop (command for no-operation, 0b11100011.

//you may need to change this section if the porting to a different platform
#define LCD_PAGE_MIN			0							//1st row of the display
#define LCD_PAGE_MAX			8							//max page, on the bottom
#define LCD_COL_MIN				0							//min column. 0
#define LCD_COL_MAX				96							//max column. 95 or 96?
#define LCD_COL_OFFSET			0x12						//first  displayable column. datasheet didn't mention this. WEIRD!
//#define LCD_LST_COL				(LCD_1ST_COL+COL_RES)		//last displayable column

/**********************************************************
               Function Prototype
**********************************************************/
void lcd_write_dorc(unsigned char byteforlcd);
void lcd_write_command(unsigned char byteforlcd_command);
void lcd_write_data(unsigned char byteforlcd_data);
void lcd_gotoxy(unsigned char lcd_row, unsigned char lcd_col);	//go to lcd_row / 0-8; and lcd_col / 0-95
#define lcd_goto(row)	lcd_gotoxy(row, 0)	//go to lcd_row, to be compatible with 16x2 lcd drivers
void lcd_chr(unsigned char charsel, unsigned char attribute);
void lcd_str(unsigned char lcd_row, unsigned char lcd_col, unsigned char *str, unsigned char attribute);
//void lcd_display(unsigned char LCD_Line, unsigned char *str, unsigned char attribute);
#define lcd_display_attr(LCD_Line, str, attribute)		lcd_str(LCD_Line, 0, str, attribute)
#define lcd_display(LCD_Line, str)						lcd_display_attr(LCD_Line, str, LCD_NORMAL)
#define lcd_display_underline(LCD_Line, str)			lcd_display_attr(LCD_Line, str, LCD_UNDERLINE)
#define lcd_display_strike(LCD_Line, str)				lcd_display_attr(LCD_Line, str, LCD_STRIKE)
#define lcd_display_overline(LCD_Line, str)				lcd_display_attr(LCD_Line, str, LCD_OVERLINE)
#define lcd_display_reverse(LCD_Line, str)				lcd_display_attr(LCD_Line, str, LCD_REVERSE)

void lcd_reset(void);
void lcd_clear(void);
void lcd_init(void);
void lcd_pixel(unsigned char lcd_row, unsigned char lcd_col, unsigned char attribute);
#endif
