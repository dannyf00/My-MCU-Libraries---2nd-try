//header file for ltc1456/2/3

#define ltc1655_select(cs)			{spi_select(cs);}
#define ltc1655_deselect(cs)		{spi_deselect(cs);}

#define ltc1655_write(word_t)		{spi_write(word_t >> 8); spi_write(word_t);}
