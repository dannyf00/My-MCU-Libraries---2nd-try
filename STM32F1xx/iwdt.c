#include "iwdt.h"

//initialize / enable iwdt
//ps: 3-bit, 1:1->256:1
//pr: 12-bit
void iwdt_init(uint16_t ps, uint16_t pr) {
	RCC -> CSR = RCC -> CSR | 0x00000001; //Enable LSI Clock
	while((RCC -> CSR & (1<<1))==0) {
		//add timeout code here
	}
	IWDG -> KR = 0x0000CCCC; 	//Enable IWDG
	IWDG -> KR = 0x00005555; 	//Enable register access
	IWDG -> PR = ps; 			//Set Prescaler /16
	IWDG -> RLR = pr - 1; 		//Set Reload Value for 2.048 seconds
	while(IWDG -> SR) { 		//Check if flags are reset
		//add timeout code here
	}
	IWDG -> KR = 0x0000AAAA; 	//Refresh the counter
}
