#include "led7i.h"					//we use led7

//hardware configuration
//end hardware configuration

//global defines

//segment / digit routines
//need to adjust for your specific displays -> CC vs. CA
//turn on / off segments - active high
#define SEG_ON(port, segs)        IO_SET(port, segs)
#define SEG_OFF(port, segs)       IO_CLR(port, segs)

//turn on / off digits - active low
#define DIG_ON(port, digs)        IO_CLR(port, digs)
#define DIG_OFF(port, digs)       IO_SET(port, digs)

//segment designators - do not change
#define SEG_A		(1<<0)
#define SEG_B		(1<<1)
#define SEG_C		(1<<2)
#define SEG_D		(1<<3)
#define SEG_E		(1<<4)
#define SEG_F		(1<<5)
#define SEG_G		(1<<6)
#define SEG_DP		(1<<7)

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
    //SEG_OFF(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_DP);
    SEG_OFF(SEGA_PORT, SEGA); SEG_OFF(SEGB_PORT, SEGB); SEG_OFF(SEGC_PORT, SEGC); SEG_OFF(SEGD_PORT, SEGD);
    SEG_OFF(SEGE_PORT, SEGE); SEG_OFF(SEGF_PORT, SEGF); SEG_OFF(SEGG_PORT, SEGG); SEG_OFF(SEGDP_PORT, SEGDP);
    //IO_OUT(SEG_DDR, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_DP);
    IO_OUT(SEGA_DDR, SEGA); IO_OUT(SEGB_DDR, SEGB); IO_OUT(SEGC_DDR, SEGC); IO_OUT(SEGD_DDR, SEGD);
    IO_OUT(SEGE_DDR, SEGE); IO_OUT(SEGF_DDR, SEGF); IO_OUT(SEGG_DDR, SEGG); IO_OUT(SEGDP_DDR, SEGDP);

    //dig pins idle off,a s output
    //DIG_OFF(DIG_0 | DIG_1 | DIG_2 | DIG_3 | DIG_4 | DIG_5 | DIG_6 | DIG_7);
    DIG_OFF(DIG0_PORT, DIG0); DIG_OFF(DIG1_PORT, DIG1); DIG_OFF(DIG2_PORT, DIG2); DIG_OFF(DIG3_PORT, DIG3);
    DIG_OFF(DIG4_PORT, DIG4); DIG_OFF(DIG5_PORT, DIG5); DIG_OFF(DIG6_PORT, DIG6); DIG_OFF(DIG7_PORT, DIG7);
    //IO_OUT(DIG_DDR, DIG_0 | DIG_1 | DIG_2 | DIG_3 | DIG_4 | DIG_5 | DIG_6 | DIG_7);
    IO_OUT(DIG0_DDR, DIG0); IO_OUT(DIG1_DDR, DIG1); IO_OUT(DIG2_DDR, DIG2); IO_OUT(DIG3_DDR, DIG3);
    IO_OUT(DIG4_DDR, DIG4); IO_OUT(DIG5_DDR, DIG5); IO_OUT(DIG6_DDR, DIG6); IO_OUT(DIG7_DDR, DIG7);
}

//update the display
void led7_display(void) {
    static uint8_t dig=0;         //current digit to be displayed
    uint8_t tmp;

    //blanking
    //DIG_OFF(DIG_0 | DIG_1 | DIG_2 | DIG_3 | DIG_4 | DIG_5 | DIG_6 | DIG_7);     //turn off all digits
    DIG_OFF(DIG0_PORT, DIG0); DIG_OFF(DIG1_PORT, DIG1); DIG_OFF(DIG2_PORT, DIG2); DIG_OFF(DIG3_PORT, DIG3);
    DIG_OFF(DIG4_PORT, DIG4); DIG_OFF(DIG5_PORT, DIG5); DIG_OFF(DIG6_PORT, DIG6); DIG_OFF(DIG7_PORT, DIG7);
    //SEG_OFF(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_DP);    //turn off all segments
    SEG_OFF(SEGA_PORT, SEGA); SEG_OFF(SEGB_PORT, SEGB); SEG_OFF(SEGC_PORT, SEGC); SEG_OFF(SEGD_PORT, SEGD);
    SEG_OFF(SEGE_PORT, SEGE); SEG_OFF(SEGF_PORT, SEGF); SEG_OFF(SEGG_PORT, SEGG); SEG_OFF(SEGDP_PORT, SEGDP);

    //update segment data
    //SEG_ON(led7_font[lRAM[dig]]); //update thes egment data
    tmp = led7_font[lRAM[dig]];		//obtain the font information
    if (tmp & SEG_A) SEG_ON(SEGA_PORT, SEGA); else SEG_OFF(SEGA_PORT, SEGA);
    if (tmp & SEG_B) SEG_ON(SEGB_PORT, SEGB); else SEG_OFF(SEGB_PORT, SEGB);
    if (tmp & SEG_C) SEG_ON(SEGC_PORT, SEGC); else SEG_OFF(SEGC_PORT, SEGC);
    if (tmp & SEG_D) SEG_ON(SEGD_PORT, SEGD); else SEG_OFF(SEGD_PORT, SEGD);
    if (tmp & SEG_E) SEG_ON(SEGE_PORT, SEGE); else SEG_OFF(SEGE_PORT, SEGE);
    if (tmp & SEG_F) SEG_ON(SEGF_PORT, SEGF); else SEG_OFF(SEGF_PORT, SEGF);
    if (tmp & SEG_G) SEG_ON(SEGG_PORT, SEGG); else SEG_OFF(SEGG_PORT, SEGG);
    if (tmp & SEG_DP) SEG_ON(SEGDP_PORT, SEGDP); else SEG_OFF(SEGDP_PORT, SEGDP);

    //turn on the current digit, and advance to the next
    //expand to support more digits
    //set dig to 0 to force an earlier return - to support fewer digits
    switch (dig) {
        case 0: DIG_ON(DIG0_PORT, DIG0); dig = 1; break;
        case 1: DIG_ON(DIG1_PORT, DIG1); dig = 2; break;      //only need to support 2 digits
        case 2: DIG_ON(DIG2_PORT, DIG2); dig = 3; break;
        case 3: DIG_ON(DIG3_PORT, DIG3); dig = 0; break;
        case 4: DIG_ON(DIG4_PORT, DIG4); dig = 5; break;
        case 5: DIG_ON(DIG5_PORT, DIG5); dig = 6; break;
        case 6: DIG_ON(DIG6_PORT, DIG6); dig = 7; break;
        case 7: DIG_ON(DIG7_PORT, DIG7); dig = 0; break;      //round off to digit 0 on the next round
        default: DIG_ON(DIG0_PORT, DIG0); dig = 1; break;     //default to digit 0
    }
}
