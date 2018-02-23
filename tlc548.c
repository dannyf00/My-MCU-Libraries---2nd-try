#include <regx51.h>								//we use keil c51
#include "gpio.h"
#include "spi_sw.h"							//we use software spi
#include "tlc548.h"							//we use tl548

void tlc548_init(void) {
	tlc548_select(TLC548_CS);
	tlc548_read();							//start conversion
	tlc548_deselect(TLC548_CS);
	tlc548_delay();							//generate at least 17us of delay
}
