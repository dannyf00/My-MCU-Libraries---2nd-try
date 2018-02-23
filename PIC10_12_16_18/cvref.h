#ifndef _CVR_H
#define _CVR_H

//header file for comparator Vref on 16f684

//hardware configuration
//end hardware configuration

#if defined(_16F684)

//VRCON bits
//VREN bit
#define CVR_EN			0x80			//Vref output routed to C1VREF
#define CVR_DIS			0x00			//fixed 0.6v to C1VREF

//Vrr bit
#define CVR_RHIGH		0x00			//voltage range high
#define CVR_RLOW		0x20			//voltage range low

//VP6EN - not used
#define CVR_VP6EN		0x10			//enable 0.6v Vref
#define CVR_VP6DIS		0x00			//disable 0.6v Vref

//VR3..0
#define CVR_30MASK		0x0f			//VR range mask

//cm2con1
//#define C1_CVREF		0x20			//route CVREF to C1
//#define C1_CVP6			0x00			//route VP6 to C1

//#define C2_CVREF		0x10			//route CVREF to C2
//#define C2_CVP6			0x00			//route VP6 to C2



//initialize c1vref
//void cvref_init(unsigned char vrcon);
#define cvref_init(vrcon)	VRCON = (vrcon)

//set VR30
//void cvref_set(unsigned char vref);
#define cvref_set(vref)		VRCON = (VRCON & ~CVR_30MASK) | ((vref) & CVR_30MASK);

#else
	#warning CVR module not defined on this chip!
#endif

#endif

