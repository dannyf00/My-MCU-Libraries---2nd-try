#ifndef _FONTNUM_H
#define _FONTNUM_H

#include <stdint.h>
#include "5110.h"

//only include fonts to be used
#include "fontnum11x14_sans.h"
#include "fontnum15x21_sans.h"
#include "fontnum20x28_sans.h"
#include "fontnum27x36_sans.h"
#include "fontnum18x36_bebas.h"
#include "fontnum20x36_bebas.h"

//select fonts
void lcd_numsetfont(uint8_t *newfont);

//display a num using 20x36_bebas at rowxcol
uint8_t lcd_num(uint8_t num, uint8_t row, uint8_t col);

//display a string of num using 20x36_bebas at rowxcol
uint8_t lcd_nums(uint8_t *num, uint8_t row, uint8_t col);

#endif
