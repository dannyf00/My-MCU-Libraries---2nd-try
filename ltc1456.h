//header file for ltc1456/2/3

#define ltc1456_select(cs)			{spi_select(cs);}
#define ltc1456_deselect(cs)		{spi_deselect(cs);}

#define ltc1456_write(word_t)		{spi_write(word_t >> 8); spi_write(word_t);}
