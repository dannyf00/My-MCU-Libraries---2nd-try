#include <htc.h>						//we use picc
#include "gpio.h"
#include "cmp.h"						//we use 16f684's comparator

//hardware configuration
//end hardware configuration

//initialize the comparator
void cmp_init(unsigned char cmcon) {
	//CMP1ON = 0;						//turn off comparator
	
	//configure cm1con0
	CMCON0=cmcon;						//set up the config
	//set up CMP1IN+/CMP1IN-
	switch (CMCON0 & CMP_MODE7) {
		case CMP_MODE0:	//configure CMP1in-
						IO_IN(CMP1INN_DDR, CMP1INN); CMP1INN_ANS = 1;
						//configure CMP1in+
						IO_IN(CMP1INP_DDR, CMP1INP); CMP1INP_ANS = 1;
						//configure CMP2in-
						IO_IN(CMP2INN_DDR, CMP2INN); CMP2INN_ANS = 1;
						//configure CMP2in+
						IO_IN(CMP2INP_DDR, CMP2INP); CMP2INP_ANS = 1;
						break;			//all comparators off, do nothing
		case CMP_MODE1:	//configure CMP1IN-
						if (CIS) {
							IO_IN(CMP1INP_DDR, CMP1INP); CMP1INP_ANS = 1;
						}
						else {
							IO_IN(CMP1INN_DDR, CMP1INN); CMP1INN_ANS = 1;
						}
						//configure CMP2in-
						IO_IN(CMP2INN_DDR, CMP2INN); CMP2INN_ANS = 1;
						//configure CMP1in+/CMP2in+
						IO_IN(CMP2INP_DDR, CMP2INP); CMP2INP_ANS = 1;
						break;
		case CMP_MODE2:	//configure CMP1in+/CMP2in+
						if (CIS) {
							//configure CMP1in+
							IO_IN(CMP1INP_DDR, CMP1INP); CMP1INP_ANS = 1;
							//configure CMP2in+
							IO_IN(CMP2INP_DDR, CMP2INP); CMP2INP_ANS = 1;
						} else {
							//configure CMP1in-
							IO_IN(CMP1INN_DDR, CMP1INN); CMP1INN_ANS = 1;
							//configure CMP2in-
							IO_IN(CMP2INN_DDR, CMP2INN); CMP2INN_ANS = 1;
						}
						break;
		case CMP_MODE3:	//configure CMP1in-
						IO_IN(CMP1INN_DDR, CMP1INN); CMP1INN_ANS = 1;
						//configure CMP2in-
						IO_IN(CMP2INN_DDR, CMP2INN); CMP2INN_ANS = 1;
						//configure CMP2in+
						IO_IN(CMP2INP_DDR, CMP2INP); CMP2INP_ANS = 1;
						break;
		case CMP_MODE4:	//configure CMP1in-
						IO_IN(CMP1INN_DDR, CMP1INN); CMP1INN_ANS = 1;
						//configure CMP1in+
						IO_IN(CMP1INP_DDR, CMP1INP); CMP1INP_ANS = 1;
						//configure CMP2in-
						IO_IN(CMP2INN_DDR, CMP2INN); CMP2INN_ANS = 1;
						//configure CMP2in+
						IO_IN(CMP2INP_DDR, CMP2INP); CMP2INP_ANS = 1;
						break;
		case CMP_MODE5:	//configure CMP2in-
						IO_IN(CMP2INN_DDR, CMP2INN); CMP2INN_ANS = 1;
						//configure CMP2in+
						IO_IN(CMP2INP_DDR, CMP2INP); CMP2INP_ANS = 1;
						break;
		case CMP_MODE6:	//configure CMP1in-
						IO_IN(CMP1INN_DDR, CMP1INN); CMP1INN_ANS = 1;
						//configure CMP2in-
						IO_IN(CMP2INN_DDR, CMP2INN); CMP2INN_ANS = 1;
						//configure CMP2in+
						IO_IN(CMP2INP_DDR, CMP2INP); CMP2INP_ANS = 1;
						//configure CMP1out
						IO_OUT(CMP1OUT_DDR, CMP1OUT);
						//configure CMP2out
						IO_OUT(CMP2OUT_DDR, CMP2OUT);
						break;
		case CMP_MODE7:	//comparators off; do nothing
						break;
	}
}
						
