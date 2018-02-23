//#include <pic24.h>						//we use pic24f
//#include "gpio.h"						//we use gpio macros
#include "cmp1.h"						//we use analog comparators

//hardware configuration
//end hardware configuration

#define _CMCON			CM1CON			//cmcon
#define _CEN			CM1CONbits.CEN	//cen bit

//initialize the comparator
void cmp1_init(unsigned short cmcon) {
	_CMPMD=0;							//turn on power to cmparators
	_CEN=0;								//turn off the comparator

	_CMCON = cmcon;						//set cmcon

	//set up CMP non-inverting pin
	if ((_CMCON & CMP_CRVREFP) == CMP_CRINA) 		//non-inverting pin on C1INA
		IO_IN(C1INA_DDR, C1INA_PIN);

	//set up cmp inverting pin
	switch (_CMCON & CMP_CRVREFN) {
		case CMP_CRINB:		IO_IN(C1INB_DDR, C1INB_PIN); break;
		case CMP_CRINC:		IO_IN(C1INC_DDR, C1INC_PIN); break;
		case CMP_CRIND:		IO_IN(C1IND_DDR, C1IND_PIN); break;
	}

	//set up the output pin
#ifdef C1OUT_PIN
	C1OUT_PIN();
#endif

	_CEN=1;								//turn on CEN
}
