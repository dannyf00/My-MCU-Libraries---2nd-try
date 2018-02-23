#ifndef __LCD_3WI_H
#define __LCD_3WI_H

/*
 *	LCD interface header file
 *	See lcd.c for more info
 * 	Drive the lcd with two wires
 *	LCD_EN
 *	LCD_CLK / LCD_RS tied together
 *	LCD_SI tied to LCD_CLK through a rc filter
 */

//hardware configuration
#define LCD_8BIT		0			//1=set the lcd in 8BIT mode, 0=in 4bit mode

#define LCD_PORT		PORTB			//lcd pins on portc
#define LCD_PORT_IN		PINB
#define LCD_DIR			DDRB		//output direction
#define LCD_EN			(1<<0)		//LCD_EN on RC5
#define LCD_CLK			(1<<1)		//LCD_CLK on RC6

#define delay_2wi()		{delay_us(10/2/2);}	//this delay needs to be 5x or longer than the rc constant used

#define delay_1us()		{NOP();}	//need to adjust this for speed


#define delay_2us()		{delay_1us(); delay_1us();}
#define delay_4us()		{delay_2us(); delay_2us();}
#define delay_8us()		{delay_4us(); delay_4us();}
#define delay_16us()	{delay_8us(); delay_8us();}
#define delay_32us()	{delay_16us(); delay_16us();}
#define delay_64us()	{delay_32us(); delay_32us();}
#define delay_128us()	{delay_64us(); delay_64us();}
#define delay_256us()	{delay_128us(); delay_128us();}
#define delay_512us()	{delay_256us(); delay_256us();}
#define delay_1024us()	{delay_512us(); delay_512us();}


//describe how LCD's data pins are connected to 164's pins
#define D0				Q0			//unused
#define D1				Q1			//unused
#define D2				Q2			//unused
#define D3				Q3			//unused
#define D4				Q4			//LCD's D4 connected to LCD_PORT's 7th bit
#define D5				Q5			//LCD's D5 connected to LCD_PORT's 0th bit
#define D6				Q6			//LCD's D6 connected to LCD_PORT's 5th bit
#define D7				Q7			//LCD's D7 connected to LCD_PORT's 2nd bit
//#define LCD_RS		Q3			//LCD_RS to 164's Q3/Qd
//end hardware configuration

#define LCD_SI			LCD_CLK		//spi data in on RC7
#define LCD_RS			LCD_CLK		//lcd rs tied to lcd_clk
//#define LCD_RS			LCD_SI		//RS pin tied to the SO pin
#define LCD_SET(bits)	LCD_PORT |= (bits)		//set bits on lcd_port
#define LCD_CLR(bits)	LCD_PORT &=~(bits)		//clear bits on lcd_port
#define LCD_FLP(bits)	LCD_PORT ^= (bits)		//flip bits on lcd_port
#define init_ctrl()		IO_OUT(LCD_DIR, LCD_EN | LCD_CLK | LCD_SI)	//LCD_RS, LCD_EN, LCD_RS and LCD_CLK in output mode
//if move the pins to a different port, need to revise TRISx as well

#define LCD_Line0		0x00		//lcd line 1
#define LCD_Line1		0x40		//lcd line 2
//for 16-char displays
#define LCD_Line2		0x10		//lcd line 3	0x14 for 20-char displays
#define LCD_Line3		0x50		//lcd line 4	0x54 for 20-char displays

//hardware configuration

//do not change the definitions below for Q0..7
#define Q0				(1<<0)
#define Q1				(1<<1)
#define Q2				(1<<2)
#define Q3				(1<<3)
#define Q4				(1<<4)
#define Q5				(1<<5)
#define Q6				(1<<6)
#define Q7				(1<<7)


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
void lcd_cgram(unsigned char cgaddr, unsigned char * cgdata);

#endif	//lcd_3wi_h
