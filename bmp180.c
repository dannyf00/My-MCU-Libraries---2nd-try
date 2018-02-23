#include "bmp180.h"				//we use bmp180

//global defines

//global variables

//simulate getting eeprom data
void bmp180_geteeprom(BMP180_TypeDef *bmp) {
    bmp->AC1=408;
    bmp->AC2=-72;
    bmp->AC3=-14383;
    bmp->AC4=32741;
    bmp->AC5=32757;
    bmp->AC6=23153;
    bmp->B1=6190;
    bmp->B2=4;
    bmp->MB=-32768;
    bmp->MC=-8711;
    bmp->MD=2868;
    bmp->OSS=0;
}

//simulate getting uncompensated pressure and temperature
void bmp180_getdata(BMP180_TypeDef *bmp) {
    bmp->UT=27898;
    bmp->UP=23843;
}


//calculate pressure
int32_t bmp180_getpressure(BMP180_TypeDef *bmp) {
    int32_t X1, X2, X3, B3, B5, B6;
    uint32_t B4, B7;
    
    //calculate true temperature
    X1 = ((int32_t) (bmp->UT-bmp->AC6) * bmp->AC5) >> 15;
    X2 = ((int32_t) bmp->MC << 11) / (X1 + bmp->MD);
    B5 = X1 + X2;
    bmp->T = (B5 + 8) >> 4;
    
    //calculate true pressure
    B6 = B5 - 4000;
    X1 = ((int32_t) bmp->B2 * ((B6 * B6) >> 12)) >> 11;
    X2 = (bmp->AC2 * B6) >> 11;
    X3 = X1 + X2;
    B3 = (((bmp->AC1 * 4 + X3) << bmp->OSS) + 2)/4;
    X1 = (bmp->AC3 * B6) >> 13;
    X2 = (bmp->B1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    B4 = (bmp->AC4 * ((uint32_t) (X3 + 32768)) ) >> 15;
    B7 = ((uint32_t) bmp->UP - B3) * (50000 >> bmp->OSS);
    if (B7 < 0x80000000) bmp->P = (B7 * 2) / B4;
    else bmp->P = B7 / B4 * 2;
    X1 = (bmp->P >> 8) * (bmp->P >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * bmp->P) >> 16;
    bmp->P = bmp->P + ((X1 + X2 + 3791) >> 4);
    return bmp->P;
}
