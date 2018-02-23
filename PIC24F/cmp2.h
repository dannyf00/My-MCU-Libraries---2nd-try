#ifndef CMP2_H_
#define CMP_H_

#include <p24fxxxx.h>						//we use pic24f
#include "gpio.h"						//we use gpio macros

//hardware configuration
//comparator 1 inputs
#define C2INA_DDR		TRISB
#define C2INA_PIN		(1<<1)			//C1INA on pb.1
#define C2INB_DDR		TRISB
#define C2INB_PIN		(1<<0)			//C1INA on pb.0
#define C2INC_DDR		TRISA
#define C2INC_PIN		(1<<4)			//C1INA on pa.4
#define C2IND_DDR		TRISB
#define C2IND_PIN		(1<<4)			//C1INA on pb.4
#define C2OUT_PIN()		PPS_C2OUT_TO_RP(12)	//C1OUT to rp12
//end hardware configuration

#define _CMPMD			PMD3bits.CMPMD	//power mgmt for comparators

//COE bit
#define CMP_OE			0x4000			//output enable
#define CMP_OD			0x0000			//output disable

//CPOL bit
#define CMP_POLP		0x0000			//normal polarity
#define CMP_POLN		0x2000			//negative polarity

//CREF bit
#define CMP_CRVREFP		0x0010			//non-inverting input to Cref+
#define CMP_CRINA		0x0000			//non-inverting input to CxINA

//CH1..0 bits
#define CMP_CRVREFN		0x0003			//inverting input to Cref-
#define CMP_CRIND		0x0002			//inverting input to CxIND
#define CMP_CRINC		0x0001			//inverting input to CxINC
#define CMP_CRINB		0x0000			//inverting input to CxINB

//initialize the comparator
void cmp2_init(unsigned short cmcon);

#endif //cmp_h_
