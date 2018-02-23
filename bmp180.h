#ifndef _BMP180_H
#define _BMP180_H

//bmp180 routines
//data input routines not inclulded
//only implemented the routine to calculate true pressure: bmp180_getpressure()

#include <stdint.h>				//we use int_t types

//global defines

typedef struct {
    //EEPROM data
    int16_t AC1, AC2, AC3;
    uint16_t AC4, AC5, AC6;
    int16_t B1, B2;
    int16_t MB, MC, MD;
    int16_t OSS;
    uint16_t UT;                //uncompensated temperature
    uint16_t UP;                //uncompensated pressure
    int32_t T;                  //temperature
    int32_t P;                  //pressure
} BMP180_TypeDef;

//global variables

//simulate getting eeprom data
void bmp180_geteeprom(BMP180_TypeDef *bmp);

//simulate getting uncompensated pressure and temperature
void bmp180_getdata(BMP180_TypeDef *bmp);


//calculate pressure
int32_t bmp180_getpressure(BMP180_TypeDef *bmp);
    
#endif
