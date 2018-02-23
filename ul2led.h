#ifndef UL2LED_H_INCLUDED
#define UL2LED_H_INCLUDED

//if using common cathod
//uncomment if common anode is used
#define Common_Cathode

//convert a number to vRAM[4]
//0 - 9999 -> 0 - 9999, no dot
//10,000 - 99,999 -> 1.000 - 9.999, dot @ dig1
//100,000 - 999,999 -> 10.00 - 99.99, dot @ dig2
//1,000,000 - 9,999,999 -> 100.0 - 999.9, dot @ dig3
//10,000,000 - 99,999,999 -> 1000. - 9999., dot @ dig4
void ul2led4(unsigned char * str, unsigned long ul);

//convert a number to vRAM[8]
//0 - 99,999,999
void ul2led8(unsigned char * str, unsigned long ul);

#endif // UL2LED_H_INCLUDED
