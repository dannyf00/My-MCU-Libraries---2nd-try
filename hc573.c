//#include <pic24.h>						//we use pic24f
#include "gpio.h"
#include "hc573.h"						//we use hc573

//hardware configuration
//end hardware configuration

//#define hc573_select(latch) 	IO_SET(HC573_PORT, latch)
//#define hc573_deselect(latch)	IO_CLR(HC573_PORT, latch)

//#define hc573_write(dat)		HC573_PORT = (HC573_PORT & ~(HC573s)) | (dat)

void hc573_init(void) {
	IO_CLR(HC573_PORT, HC573s);			//clear hc573
	IO_OUT(HC573_DDR, HC573s);
}
