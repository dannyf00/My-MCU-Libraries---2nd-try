//#include <pic24.h>						//we use pic24f
//#include "gpio.h"						//we use gpio macros
#include "cmp3.h"						//we use analog comparators

//hardware configuration
//end hardware configuration

#define _CMCON			CM3CON			//cmcon
#define _CEN			CM3CONbits.CEN	//cen bit

//initialize the comparator
void cmp3_init(unsigned short cmcon) {
	_CMPMD=0;							//turn on power to cmparators
	_CEN=0;								//turn off the comparator

	_CMCON = cmcon;						//set cmcon
	
	//set up CMP non-inverting pin
	if ((_CMCON & CMP_CRVREFP) == CMP_CRINA) 		//non-inverting pin on C1INA
		IO_IN(C3INA_DDR, C3INA_PIN);
			
	//set up cmp inverting pin
	switch (_CMCON & CMP_CRVREFN) {
		case CMP_CRINB:		IO_IN(C3INB_DDR, C3INB_PIN); break;
		case CMP_CRINC:		IO_IN(C3INC_DDR, C3INC_PIN); break;
		case CMP_CRIND:		IO_IN(C3IND_DDR, C3IND_PIN); break;
	}	

	//set up the output pin
#ifdef C3OUT_PIN
	C3OUT_PIN();
#endif

	_CEN=1;								//turn on CEN
}
