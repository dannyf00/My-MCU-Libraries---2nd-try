#include <regx51.h>
#include "gpio.h"
#include "ad5220.h"							//we use ad5220

void ad5220_init(void) {
	IO_SET(AD5220_PORT, AD5220_CLK | AD5220_UD);
	IO_OUT(AD5220_DDR, AD5220_CLK | AD5220_UD);
}
