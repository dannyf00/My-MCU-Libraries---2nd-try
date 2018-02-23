//#include <htc.h>						//we use picc
//#include <p24fxxxx.h>					//we use pic24
//#include "gpio.h"
#include "cvref.h"						//we use comparator reference voltage generator

//hardware configuration
//end hardware configuration

//initialize c1vref
void cvref_init(unsigned char cvrcon) {
	_CMPMD = 0;							//turn on the comparators
	
#if defined(__24FJ64GA102_H)
	_CVREFP = 0;						//0->CVref+ = CVREF. 1->CVref+=Vref+
	_CVREFM1=0, _CVREFM0 = 0;			//00->CVref-=Vbg/2
										//01->CVref-=Vbg
										//10->CVref-=Vbg/6
										//11->CVref-=Vref+
#endif
	CVRCON |= cvrcon;					//load up vrcon
	//if (CVRCON & CVR_VROE) {			//output enabled
		//IO_OUT(CVREF_DDR, CVREF);		//set CVREF pin as output - not needed
	//}	
}

//set VR30
//void cvref_set(unsigned char vref) {
	//set cvref range
//	VRCON = (VRCON & ~VR_VR30MASK) | (vref & VR_VR30MASK);
//}
