#include "fontnum.h"

//global variables
const uint8_t *fontbase=fontnum20x36_bebas;		//font base

//select fonts
void lcd_numsetfont(uint8_t *newfont) {
	fontbase = newfont;
}

//display a num using 20x36_bebas at rowxcol
uint8_t lcd_num(uint8_t num, uint8_t row, uint8_t col) {
    uint16_t tmp;
    uint8_t i;
    const uint8_t *fontdata;

    //boundary check
    if (num < fontbase[2]) return col;
    if (num > fontbase[3]) return col;
    
    num = num - fontbase[2];		//calculate the offset
    tmp = 4 + num * (1 + fontbase[0] * fontbase[1]);                 //100 bytes per num + 1 byte width
    fontdata=fontbase + tmp;		//point to the start of font pixel data
    //lcd_gotoxy(row, col);         //go to the starting coordinates
    //go through the rows: num = rows
	for (num = 0; num < fontbase[1]; num++) {
    	lcd_gotoxy(row + num, col); 
    	//go through all the colums
    	for (i=0; i<fontdata[0]; i++) lcd_write_data(fontdata[1 + num + i*fontbase[1]]);
    }
    return col+fontbase[0];			//fixed pitch
    //return col+fontdata[0];			//variable pitch
}

//display a string of num using 20x36_bebas at rowxcol
uint8_t lcd_nums(uint8_t *num, uint8_t row, uint8_t col) {
	while (*num) {
		col = lcd_num(*num++, row, col);
	}
	return col;
}
