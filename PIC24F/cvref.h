#ifndef CVREF_H_
#define CVREF_H_

//#include <p24fxxxx.h>					//we use pic24
#include "gpio.h"

//header file for comparator Vref on 16f886

//hardware configuration
//#define CVREF_PORT		LATB
#define CVREF_DDR		TRISB
#define CVREF			(1<<14)
//end hardware configuration

//VRCON bits
//C1VREN bit
#define CVR_EN			0x0080			//Vref output routed to C1VREF
#define CVR_DIS			0x0000			//fixed 0.6v to C1VREF

//C2VREN bit
#define CVR_OE			0x0040			//Vref output routed to C2VREF
#define CVR_OD			0x0000			//fixed 0.6v to C2VREF

//Vrr bit
#define CVR_RHIGH		0x0000			//voltage range high
#define CVR_RLOW		0x0020			//voltage range low

//CVRss bit
#define CVR_VREF		0x0010			//VRss set to Vref+ - Vref-
#define CVR_VDD			0x0000			//VRss set to Vdd - Vss

//VR3..0
#define CVR_30MASK		0x000f			//VR range mask


//initialize c1vref
void cvref_init(unsigned char vrcon);
//#define cvref_init(vrcon)	VRCON = (vrcon)

//set VR30
//void cvref_set(unsigned char vref);
#define cvref_set(vref)		CVRCON = ((CVRCON & ~CVR_30MASK) | ((vref) & CVR_30MASK))

#endif //cvref_h_
