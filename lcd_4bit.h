#ifndef __LCD_4BIT_H
#define __LCD_4BIT_H

/*
 *	LCD interface header file
 *	See lcd.c for more info
 */

//hardware configuration
#define LCD_8BIT		0				//1=set the lcd in 8BIT mode, 0=in 4bit mode

#define LCD_PORT		PORTA			//lcd pins on portc
#define LCD_DDR			DDRA			//lcd pin's direction register
//describe how LCD's data pins are connected to the mcu
#define LCD_D0				Q0				//unused in 4-bit mode
#define LCD_D1				Q1				//unused in 4-bit mode
#define LCD_D2				Q2				//unused in 4-bit mode
#define LCD_D3				Q3				//unused in 4-bit mode
#define LCD_D4				(1<<3)				//LCD's D4 connected to LCD_PORT's 4th bit
#define LCD_D5				(1<<2)		//LCD's D5 connected to LCD_PORT's 5th bit
#define LCD_D6				(1<<1)			//LCD's D6 connected to LCD_PORT's 6th bit
#define LCD_D7				(1<<0)			//LCD's D7 connected to LCD_PORT's 7nd bit

//how control lines (EN and RS) are connected
#define LCD_CTRL_PORT	PORTA			//lcd_EN/_RS on port
#define LCD_CTRL_DDR	DDRA
#define LCD_RS			(1<<5)			//RS pin tied to the SO pin
//#define LCD_RW			(1<<3)			//RW pin. hardware to ground
#define LCD_EN			(1<<4)			//LCD_EN on portc.2
//end of hardware configuration

//do not change the definitions below for Q0..7
#define Q0				(1<<0)
#define Q1				(1<<1)
#define Q2				(1<<2)
#define Q3				(1<<3)
#define Q4				(1<<4)
#define Q5				(1<<5)
#define Q6				(1<<6)
#define Q7				(1<<7)

#define LCD_SET(bits)	IO_SET(LCD_PORT, bits)			//set bits on lcd_port
#define LCD_CLR(bits)	IO_CLR(LCD_PORT, bits)			//clear bits on lcd_port
#define LCD_FLP(bits)	IO_FLP(LCD_PORT, bits)			//flip bits on lcd_port

#if LCD_8BIT == 1		//in 8-bit mode
#define init_data()		IO_OUT(LCD_DDR, LCD_D0 | LCD_D1 | LCD_D2 | LCD_D3 | LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7)	//set the data lines
#else					//in 4-bit mode
#define init_data()		IO_OUT(LCD_DDR, LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7)	//set the data lines
#endif

#define init_ctrl()		IO_OUT(LCD_CTRL_DDR, LCD_EN | LCD_RS)	//LCD_RS, LCD_EN, LCD_RS and LCD_CLK in output mode

#define LCD_Line0		0x00		//lcd line 1
#define LCD_Line1		0x40		//lcd line 2
//for 16-char displays
#define LCD_Line2		0x10		//lcd line 3	0x14 for 20-char displays
#define LCD_Line3		0x50		//lcd line 4	0x54 for 20-char displays

//LCD control signals
/* Display ON/OFF Control defines */
/* note: commands in AND style */
#define LCD_DISPLAY_CLEAR		0x01		//clear display and return to 0x00

#define LCD_RETURN_HOME			0x02		//return home

/* entry mode set */
#define LCD_SHIFT_CURSOR_LEFT   0x05		//0b00000101  /* Cursor shifts to the left   */
#define LCD_SHIFT_CURSOR_RIGHT  0x07		//0b00000111  /* Cursor shifts to the right  */
#define LCD_SHIFT_DISPLAY_LEFT 	0x07		//0b00000111  /* Display shifts to the left  */
#define LCD_SHIFT_DISPLAY_RIGHT 0x06		//0b00000110  /* Display shifts to the right */

/* display on/off control */
#define LCD_DISPLAY_ON         	0x0f		//0b00001111  /* Display on      */
#define LCD_DISPLAY_OFF       	0x0b		//0b00001011  /* Display off     */
#define LCD_CURSOR_ON   		0x0f		//0b00001111  /* Cursor on       */
#define LCD_CURSOR_OFF  		0x0d		//0b00001101  /* Cursor off      */
#define LCD_BLINK_ON    		0x0f		//0b00001111  /* Cursor Blink    */
#define LCD_BLINK_OFF   		0x0e		//0b00001110  /* Cursor No Blink */

/* Cursor or Display Shift defines */
//#define LCD_SHIFT_CURSOR_LEFT    0b00010011  /* Cursor shifts to the left   */
//#define LCD_SHIFT_CURSOR_RIGHT   0b00010111  /* Cursor shifts to the right  */
//#define LCD_SHIFT_DISPLAY_LEFT   0b00011011  /* Display shifts to the left  */
//#define LCD_SHIFT_DISPLAY_RIGHT  0b00011111  /* Display shifts to the right */

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

/* write a char on the lcd*/
void lcd_putch(unsigned char ch);

/*display a str on the lcd*/
void lcd_display(unsigned char LCD_Line, unsigned char * str);

/*	Set the cursor position */
#define	lcd_cursor(x)	lcd_write(((x)&0x7F)|0x80)


//load a 8-byte data to cgram
void lcd_cgram(unsigned char cgaddr, unsigned char * cgdata);

#endif
