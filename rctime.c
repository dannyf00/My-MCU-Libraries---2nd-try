//measuring r with an rc network
//connection:
//R: Vcc to RC_PIN
//C: RC_PIN to ground
#include <pic24.h>					//we use pic24
#include "gpio.h"					//gpio operations
#include "delay.h"					//we use software delay
#include "rctime.h"					//rc time module

//hardware configuration
//end hardware configuration


#define RC_DLY()			{delay_ms(1);}
#define RC_TIMEOUT			30000		//rc time out


//initialize the module
void rctime_init(unsigned char pin) {
	IO_IN(RC_DDR, pin);				//pin as input
}

//measure the time
unsigned short rctime_read(unsigned char pin) {
	unsigned short tmp=0;

	IO_CLR(RC_PORT, pin);			//clear the pin
	IO_OUT(RC_DDR , pin);			//pin as output
	RC_DLY();							//some delay

	//start measurement
	IO_IN(RC_DDR, pin);

	//increment tmp until it is high or overtime
	while ((tmp < RC_TIMEOUT) && (~RC_PORT_IN & pin)) tmp+=1;

	return tmp;
}
