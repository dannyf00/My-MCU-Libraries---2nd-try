/*
 */

#include <avr/io.h>						//we use gcc avr
#include "gpio.h"
#include "cd4051.h"						//we use cd4051

//hardware configuration
//potentially implement the ENABLE line here
//end hardware configuration


//initialize cd4051
void cd4051_init(void) {
#if defined(CD4051_INH)
	IO_SET(CD4051_PORT, CD4051_INH);
	IO_OUT(CD4051_DDR, CD4051_INH);
#endif

    IO_CLR(CD4051_PORT, CD4051_S0 | CD4051_S1 | CD4051_S2);	//clear pins
    IO_OUT(CD4051_DDR , CD4051_S0 | CD4051_S1 | CD4051_S2);	//pins as output

}

//select a channel
void cd4051_select(unsigned char ch) {
    unsigned char tmp=0;						//tmp variable

#if defined(CD4051_INH)
	IO_SET(CD4051_PORT, CD4051_INH);			//deactive the chip
#endif

    switch (ch & 0x07) {
    case CD4051_A0:
        IO_SET(tmp, 0         | 0         | 0        );
        break;
    case CD4051_A1:
        IO_SET(tmp, 0         | 0         | CD4051_S0);
        break;
    case CD4051_A2:
        IO_SET(tmp, 0         | CD4051_S1 | 0        );
        break;
    case CD4051_A3:
        IO_SET(tmp, 0         | CD4051_S1 | CD4051_S0);
        break;
    case CD4051_A4:
        IO_SET(tmp, CD4051_S2 | 0         | 0        );
        break;
    case CD4051_A5:
        IO_SET(tmp, CD4051_S2 | 0         | CD4051_S0);
        break;
    case CD4051_A6:
        IO_SET(tmp, CD4051_S2 | CD4051_S1 | 0        );
        break;
    case CD4051_A7:
        IO_SET(tmp, CD4051_S2 | CD4051_S1 | CD4051_S0);
        break;
    }
    //update the port
    CD4051_PORT = (CD4051_PORT & ~(CD4051_S0 | CD4051_S1 | CD4051_S2)) | tmp;

#if defined(CD4051_INH)
	IO_CLR(CD4051_PORT, CD4051_INH);	//active the channels
#endif

}
