#include <regx51.h>								//we use keil c51
#include "gpio.h"
#include "dac083x.h"							//we use dac08

void dac_init(void) {
	//IO_SET(DAC_CTRL_PORT, DAC_CTRL_CS);	//cs/wr1 high
	//IO_OUT(DAC_CTRL_DDR, DAC_CTRL_CS);	//cs/wr1 as output

	IO_CLR(DAC_DATA_PORT, DAC_DATA_PINs);				//data pins low
	IO_OUT(DAC_DATA_DDR, DAC_DATA_PINs);				//data pins as output


}
