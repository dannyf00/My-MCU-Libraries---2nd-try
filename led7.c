#include "led7.h"					//we use led7

//hardware configuration
//end hardware configuration

//global defines

//segment / digit routines
//need to adjust for your specific displays -> CC vs. CA
//turn on / off segments - active low
#define SEG_ON(segs)        IO_CLR(SEG_PORT, segs)
#define SEG_OFF(segs)       IO_SET(SEG_PORT, segs)

//turn on / off digits - active high
#define DIG_ON(digs)        IO_SET(DIG_PORT, digs)
#define DIG_OFF(digs)       IO_CLR(DIG_PORT, digs)

//global variables
uint8_t lRAM[DIG_CNT];              //display buffer
//turn 0..f numeric value to segment data
const uint8_t led7_font[]={         //display fount
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | 0x00 ,  //'0'
    0x00  | SEG_B | SEG_C | 0x00  | 0x00  | 0x00  | 0x00 ,  //'1'
    SEG_A | SEG_B | 0x00  | SEG_D | SEG_E | 0x00  | SEG_G,  //'2'
    SEG_A | SEG_B | SEG_C | SEG_D | 0x00  | 0x00  | SEG_G,  //'3'
    0x00  | SEG_B | SEG_C | 0x00  | 0x00  | SEG_F | SEG_G,  //'4'
    SEG_A | 0x00  | SEG_C | SEG_D | 0x00  | SEG_F | SEG_G,  //'5'
    SEG_A | 0x00  | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,  //'6'
    SEG_A | SEG_B | SEG_C | 0x00  | 0x00  | 0x00  | 0x00 ,  //'7'
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,  //'8'
    SEG_A | SEG_B | SEG_C | SEG_D | 0x00  | SEG_F | SEG_G,  //'9'
    SEG_A | SEG_B | SEG_C | 0x00  | SEG_E | SEG_F | SEG_G,  //'A'
    0x00  | 0x00  | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,  //'b'
    SEG_A | 0x00  | 0x00  | SEG_D | SEG_E | SEG_F | 0x00 ,  //'C'
    0x00  | SEG_B | SEG_C | SEG_D | SEG_E | 0x00  | SEG_G,  //'d'
    SEG_A | 0x00  | 0x00  | SEG_D | SEG_E | SEG_F | SEG_G,  //'E'
    SEG_A | 0x00  | 0x00  | 0x00  | SEG_E | SEG_F | SEG_G,  //'F'
};

//initialize the module
void led7_init(void) {
    //seg pins idle off, as output
    SEG_OFF(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_DP);
    IO_OUT(SEG_DDR, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_DP);

    //dig pins idle off,a s output
    DIG_OFF(DIG_0 | DIG_1 | DIG_2 | DIG_3 | DIG_4 | DIG_5 | DIG_6 | DIG_7);
    IO_OUT(DIG_DDR, DIG_0 | DIG_1 | DIG_2 | DIG_3 | DIG_4 | DIG_5 | DIG_6 | DIG_7);
}

//update the display
void led7_display(void) {
    static uint8_t dig=0;         //current digit to be displayed

    //blanking
    DIG_OFF(DIG_0 | DIG_1 | DIG_2 | DIG_3 | DIG_4 | DIG_5 | DIG_6 | DIG_7);     //turn off all digits
    SEG_OFF(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_DP);    //turn off all segments

    //update segment data
    SEG_ON(led7_font[lRAM[dig]]); //update thes egment data

    //turn on the current digit, and advance to the next
    //expand to support more digits
    //set dig to 0 to force an earlier return - to support fewer digits
    switch (dig) {
        case 0: DIG_ON(DIG_0); dig = 1; break;
        case 1: DIG_ON(DIG_1); dig = 2; break;      //only need to support 2 digits
        case 2: DIG_ON(DIG_2); dig = 3; break;
        case 3: DIG_ON(DIG_3); dig = 0; break;
        case 4: DIG_ON(DIG_4); dig = 5; break;
        case 5: DIG_ON(DIG_5); dig = 6; break;
        case 6: DIG_ON(DIG_6); dig = 7; break;
        case 7: DIG_ON(DIG_7); dig = 0; break;      //round off to digit 0 on the next round
        default: DIG_ON(DIG_0); dig = 1; break;     //default to digit 0
    }
}
