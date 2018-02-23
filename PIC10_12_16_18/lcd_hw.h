#ifndef LCD_HW_H_
#define LCD_HW_H_

//header file for on-board lcd hardware

//hardware configuration
#define LCD_PS			LCD_PS1x		//lcd prescaler
#define LCD_COM			LCD_COM1		//lcd com
//#define LCD_DIGs		8				//number of lcd digits
//end hardware configuration

#define LCD_COM0		0x00			//com0 - static
#define LCD_COM1		0x01			//com0..1 -> 1/2
#define LCD_COM2		0x02			//com0..2 -> 1/3
#define LCD_COM3		0x03			//com0..3 -> 1/4

//prescaler settings
#define LCD_PS1x		0x00
#define LCD_PS2x		0x01
#define LCD_PS3x		0x02
#define LCD_PS4x		0x03
#define LCD_PS5x		0x04
#define LCD_PS6x		0x05
#define LCD_PS7x		0x06
#define LCD_PS8x		0x07
#define LCD_PS9x		0x08
#define LCD_PS10x		0x09
#define LCD_PS11x		0x0a
#define LCD_PS12x		0x0b
#define LCD_PS13x		0x0c
#define LCD_PS14x		0x0d
#define LCD_PS15x		0x0e
#define LCD_PS16x		0x0f

//global variable

//initialize the lcd
void lcd_init(void);

//display data on lcd
//vRAM is an array containing the numerical digits
void lcd_display(unsigned char * vRAM);

//display a ul
void lcd_display_ul(unsigned long ul);

#endif
