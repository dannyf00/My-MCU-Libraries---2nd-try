#ifndef LTC1451_H_INCLUDED
#define LTC1451_H_INCLUDED

//hardware configuration
//ltc1451 dacs
#define LTC1451_CS		A2
#define LTC1451_DIN		A0
#define LTC1451_CLK		A1
//end hardware configuration

//macros for pin operations

//global defines

//global variables

//reset ltc1451
void ltc1451_init(void);

//write to ltc1451 - least significant 12 bits
void ltc1451_write(unsigned short dat);

#endif // LTC1451_H_INCLUDED
