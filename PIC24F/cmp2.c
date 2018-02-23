//#include <pic24.h>						//we use pic24f
//#include "gpio.h"						//we use gpio macros
#include "cmp2.h"						//we use analog comparators

//hardware configuration
//end hardware configuration

#define _CMCON			CM2CON			//cmcon
#define _CEN			CM2CONbits.CEN	//cen bit

//initialize the comparator
void cmp2_init(unsigned short cmcon) {
	_CMPMD=0;							//turn on power to cmparators
	_CEN=0;								//turn off the comparator

	_CMCON = cmcon;						//set cmcon
	
	//set up CMP non-inverting pin
	if ((_CMCON & CMP_CRVREFP) == CMP_CRINA) 		//non-inverting pin on C1INA
		IO_IN(C2INA_DDR, C2INA_PIN);
			
	//set up cmp inverting pin
	switch (_CMCON & CMP_CRVREFN) {
		case CMP_CRINB:		IO_IN(C2INB_DDR, C2INB_PIN); break;
		case CMP_CRINC:		IO_IN(C2INC_DDR, C2INC_PIN); break;
		case CMP_CRIND:		IO_IN(C2IND_DDR, C2IND_PIN); break;
	}	

	//set up the output pin
#ifdef C2OUT_PIN
	C2OUT_PIN();
#endif

	_CEN=1;								//turn on CEN
}
