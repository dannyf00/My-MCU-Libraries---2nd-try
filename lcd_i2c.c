/*
* LCD interface example
* Uses routines from delay.c
* This code will interface to a standard LCD controller
* like the Hitachi HD44780. It uses it in 4 bit mode, with
* the hardware connected as follows (the standard 14 pin
* LCD connector is used):
*
* LCD_DATA bits, defined by D4..7, are connected to the LCD data bits 4-7 (high nibble)
* PORTA bit 3 is connected to the LCD RS input (register select)
* PORTA bit 1 is connected to the LCD EN bit (enable)
*
* To use these routines, set up the port I/O (TRISA, TRISD) then
* call lcd_init(), then other routines as required.
*
*/

/* design parameters:
* LC / Frequency meter with user calibration capabilities
* chip: PIC12F675
* LCD: HD44780 or compatable, in 4-bit mode and in 3-wire interface
* based on Micah Carrick's hardware design (74hc164).
* compiler:picc std 9.60pl2
* IDE: hi-tide
*
* revision history:
* v0.1 initial porting to pic
*
*/

//#include <iostm8.h> //we use iar stm8
//#include <htc.h> //we use picc
//#include <avr/io.h> //we use gcc-avr
//#include <pic24.h> //we use microchip c30
//#include "gpio.h"
//#include "delay.h"

#include "lcd_i2c.h" //we use i2c in 4bit interface

//may need to adjust based on compiler optimization settings -> approximately 2ms or more per 16 characters / row
#  if F_CPU > 64000000ul
	#define lcd_delay()				{NOP64(); /*NOP();*/}	//delay(0)		//lcd delay for 20Mhz or higher
#elif F_CPU > 32000000ul
	#define lcd_delay()				{NOP32(); /*NOP();*/}	//delay(0)		//lcd delay for 20Mhz or higher
#elif F_CPU > 16000000ul
	#define lcd_delay()				{NOP16(); /*NOP();*/}	//delay(0)		//lcd delay for 20Mhz or higher
#elif F_CPU > 8000000ul
	#define lcd_delay()				{NOP8(); /*NOP();*/}	//delay(0)		//lcd delay for 20Mhz or higher
#elif F_CPU > 4000000ul
	#define lcd_delay()				{NOP4(); /*NOP();*/}	//delay(0)		//lcd delay for 20Mhz or higher
#else
	#define lcd_delay()				{NOP2(); /*NOP();*/}						//no delay needed for low speed mcu
#endif

#define LCD_STROBE(rs) do {if (rs) LCD_SET(LCD_RS); else LCD_CLR(LCD_RS); LCD_SET(LCD_EN); i2c_write(_lcd_data); lcd_delay(10); LCD_CLR(LCD_EN); i2c_write(_lcd_data); lcd_delay(10);} while (0)
#define LCD_SET(bits) IO_SET(_lcd_data, bits) //set bits on lcd_port
#define LCD_CLR(bits) IO_CLR(_lcd_data, bits) //clear bits on lcd_port

//global variable
uint8_t _lcd_data=0; //i2c output shadow register - default backlight on

/* write a byte to the LCD in 4/8 bit mode */
void lcd_write(unsigned char c, unsigned char rs) {

	i2c_start(); //send an i2c start condition
	i2c_write(LCD_I2CADDR &~I2C_CMD_READ); //send the address + write command

	//send the highest 4 bits
	if (c & 0x80) LCD_SET(LCD_D7); else LCD_CLR(LCD_D7);
	if (c & 0x40) LCD_SET(LCD_D6); else LCD_CLR(LCD_D6);
	if (c & 0x20) LCD_SET(LCD_D5); else LCD_CLR(LCD_D5);
	if (c & 0x10) LCD_SET(LCD_D4); else LCD_CLR(LCD_D4);
	LCD_STROBE(rs); //stroke out the highest 4 bits

	//now, send the lowest 4 bits
	if (c & 0x08) LCD_SET(LCD_D7); else LCD_CLR(LCD_D7);
	if (c & 0x04) LCD_SET(LCD_D6); else LCD_CLR(LCD_D6);
	if (c & 0x02) LCD_SET(LCD_D5); else LCD_CLR(LCD_D5);
	if (c & 0x01) LCD_SET(LCD_D4); else LCD_CLR(LCD_D4);
	LCD_STROBE(rs); //stroke out the lowest 4 bits

	i2c_stop(); //send the stop condition
}

/*
* Clear and home the LCD
*/
void lcd_clear(void) {
	//IO_CLR(LCD_CTRL_PORT, LCD_RS);
	lcd_write(0x01, 0); //clear the lcd
	delay_ms(2); //2ms delay
}

/* write a string of chars to the LCD */
void lcd_puts(unsigned char * s) {
	//IO_SET(LCD_CTRL_PORT, LCD_RS); // write characters
	while(*s) {
		lcd_write(*s++, 1);
	}
}

/* write one character to the LCD */
void lcd_putch(unsigned char c) {
	//IO_SET(LCD_CTRL_PORT, LCD_RS); // write characters
	lcd_write( c, 1);
}

/*
* Go to the specified position
*/
void lcd_goto(unsigned char pos) {
	//IO_CLR(LCD_CTRL_PORT, LCD_RS);
	lcd_write(0x80+pos, 0);
}

/* initialise the LCD - put into 4 bit mode */
void lcd_init(void) {
	//init_ctrl(); //set up the control pins
	//init_data(); //set up D4..7.
	i2c_init(); //set up the i2c pins
#ifdef LCD_RW //if RW is defined
	//IO_CLR(LCD_CTRL_PORT, LCD_RW); //clear lcd_rw
	//IO_OUT(LCD_CTRL_DDR, LCD_RW); //lcd_rw as output
#endif

	//IO_CLR(LCD_CTRL_PORT, LCD_EN);
	delay_ms(15); // wait 15mSec after power applied,
	//LCD_SET(LCD_D4 | LCD_D5); LCD_CLR(LCD_D6 | LCD_D7); //send 0x03
	_lcd_data = LCD_BL;			//default backlight on
	_lcd_data|= LCD_D4 | LCD_D5; //send lcd_d4..5
	_lcd_data&=~(LCD_D6 | LCD_D7); //clear lcd_d6.7
	_lcd_data&=~(LCD_RW); //cleara lcd_rw/lcd_rs

	i2c_start(); //send the start condition
	i2c_write(LCD_I2CADDR &~I2C_CMD_READ); //address + write command

	LCD_STROBE(0);

	delay_ms(5); //delay 5ms
	LCD_STROBE(0);

	delay_us(200); //delay 200us
	LCD_STROBE(0);

	delay_us(200); //delay 200us
	//IO_CLR(LCD_CTRL_PORT, LCD_RS);
	//LCD_SET(LCD_D5); LCD_CLR(LCD_D4 | LCD_D6 | LCD_D7); //send 0x02 -> 4 bit mode
	_lcd_data|= LCD_D5;
	_lcd_data&=~(LCD_D4 | LCD_D6 | LCD_D7);
	LCD_STROBE(0);

	i2c_stop(); //send the stop condition
	lcd_write(LCD_FOUR_BIT & LCD_LINES_5X7, 0); // function control, 4bit, 2line, 5x7 dots
	lcd_write(LCD_DISPLAY_ON & LCD_CURSOR_OFF & LCD_BLINK_OFF, 0); //display on, cursor off, blink off
	//lcd_clear(); // Clear screen
	lcd_write(LCD_SHIFT_DISPLAY_RIGHT & LCD_SHIFT_CURSOR_RIGHT, 0); // Set entry Mode, increment, don't shift.
}

void lcd_display(unsigned char LCD_Line, unsigned char * str) {
	lcd_goto(LCD_Line);
	lcd_puts(str);
}

//load a 8-byte data to cgram
void lcd_cgram(unsigned char cgaddr, unsigned char * cgdata) {
	unsigned char i;

	lcd_write(LCD_CGRAM | (cgaddr * 8), 0); //send the command
	for (i=0; i<8; i++) lcd_write(cgdata[i], 1); //send the cgdata
}

//turn on / off backlight
//not implemented
void lcd_backlight(unsigned char on_off) {
	if (on_off) _lcd_data |= LCD_BL;
	else _lcd_data &=~LCD_BL;
}
