#ifndef __CONFIG_C30_H
#define __CONFIG_C30_H

//#include "gpio.h"                   //so device header is included
#include <p24fxxxx.h>			//we use 24f

//configuration words for pic24f
//configuration words for pic24f
//PIC24FJ64GA102, PIC24FJ64GA104, PIC24FJ32GA102, PIC24FJ32GA104
//PIC24FJ64GA002, PIC24FJ64GA004
//PIC24FJ48GA002, PIC24FJ48GA004
//PIC24FJ32GA002, PIC24FJ32GA004
//PIC24FJ16GA002, PIC24FJ16GA004
//PIC24FJ64GB002, PIC24FJ64GB004
//PIC24FJ48GB002, PIC24FJ48GB004
//PIC24FJ32GB002, PIC24FJ32GB004
//dsPIC30F4011, dsPIC30F4012
//dsPIC33FJ12GP201, dsPIC33FJ12GP202
//dspic33fj32GP302, dsPIC33FJ32GP304
//dspic33fj64gp202, dsPIC33FJ64GP204
//dspic33fj64gp802, dsPIC33FJGP804
//dspic33fj128gp202, dPIC33FJ128GP204
//dspic33fj128gp802, dsPIC33FJ128GP804
//dsPIC33FJ32GP202, dsPIC33FJ32GP204, dsPIC33FJ16GP304
//dsPIC33FJ12MC201, dsPIC33FJ12MC202
//dsPIC33FJ32MC202, dsPIC33FJ32MC204
//dsPIC33FJ06GS101, dsPIC33FJ06GS102, dsPIC33FJ06GS202,
//dsPIC33FJ16GS402, dsPIC33FJ16GS404, dsPIC33FJ16GS502, dsPIC33FJ16GS504

#if 	defined(__PIC24FJ64GA102__) | defined (__PIC24FJ64GA104__) | \
		defined(__PIC24FJ32GA102__) | defined (__PIC24FJ32GA104__)

//config fues settings for 24fj64ga102
///config fues settings
_CONFIG1(
    JTAGEN_OFF &					//Disable JTAG port
    GCP_OFF &						//Disable code protect
    GWRP_OFF &						//Disable write protect
    ICS_PGx2 &						//EMUC/EMUD share PGC2/PGD2
    FWDTEN_OFF &					//Disable watchdog timer (WDT)
    WINDIS_OFF &					//Use standard WDT (if it is enabled)
    FWPSA_PR128 &					//Use WDT prescaler ratio of 1:128
    WDTPS_PS32768					//Use WDT postscaler ratio of 1:32,768
)

_CONFIG2(
    IESO_OFF &						//Disabled
    FNOSC_FRC &						//FNOSC_PRI = Primary oscillator (XT, HS, EC). FNOSC_FRC -> 8Mhz internal rc (default to 2Mhz)
    FCKSM_CSDCMD &					//Clock switching and clock monitor disabled
    OSCIOFNC_OFF &					//OSCO or Fosc/2
    IOL1WAY_OFF &					//Unlimited Writes To RP Registers
    POSCMOD_HS &					//High speed seeting for external oscillator
    I2C1SEL_PRI						//Use Primary I2C1 pins
    //SOSCSEL_SOSC &					//Default Secondary Oscillator
    //WUTSEL_LEG &					//Legacy Wake-up timer selected
)

_CONFIG3(
    WPFP_WPFP63 &					//Highest Page (same as page 42)
    SOSCSEL_IO &					//SOSC pins have digital I/O functions (RA4, RB4)
    WUTSEL_LEG &					//Default regulator start-up time used
    WPDIS_WPDIS &					//Segmented code protection disabled
    WPCFG_WPCFGDIS &				//Last page and Flash Configuration words are unprotected
    WPEND_WPENDMEM					//Write Protect from WPFP to the last page of memory
)

_CONFIG4(
    DSWDTPS_DSWDTPSF &				//1:2,147,483,648 (25.7 days)
    DSWDTOSC_LPRC &					//DSWDT uses Low Power RC Oscillator (LPRC)
    RTCOSC_LPRC &					//RTCC uses Low Power RC Oscillator (LPRC)
    DSBOREN_OFF &					//BOR disabled in Deep Sleep
    DSWDTEN_OFF 					//DSWDT disabled
)

/* -------------------------------------------------------- */
/* Macros for setting device configuration registers        */
/* -------------------------------------------------------- */

/* Register CONFIG4 (0xabf8)                               */

/*
** Only one invocation of CONFIG4 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set CONFIG4.
** Multiple options may be combined, as shown:
**
** _CONFIG4( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   DSWDT Postscale Select:
**     DSWDTPS_DSWDTPS0     1:2 (2.1 ms)
**     DSWDTPS_DSWDTPS1     1:8 (8.3 ms)
**     DSWDTPS_DSWDTPS2     1:32 (33 ms)
**     DSWDTPS_DSWDTPS3     1:128 (132 ms)
**     DSWDTPS_DSWDTPS4     1:512 (528 ms)
**     DSWDTPS_DSWDTPS5     1:2,048 (2.1 seconds)
**     DSWDTPS_DSWDTPS6     1:8,192 (8.5 seconds)
**     DSWDTPS_DSWDTPS7     1:32,768 (34 seconds)
**     DSWDTPS_DSWDTPS8     1:131,072 (135 seconds)
**     DSWDTPS_DSWDTPS9     1:524,288 (9 minutes)
**     DSWDTPS_DSWDTPSA     1:2,097,152 (36 minutes)
**     DSWDTPS_DSWDTPSB     1:8,388,608 (2.4 hours)
**     DSWDTPS_DSWDTPSC     1:33,554,432 (9.6 hours)
**     DSWDTPS_DSWDTPSD     1:134,217,728 (38.5 hours)
**     DSWDTPS_DSWDTPSE     1:536,870,912 (6.4 days)
**     DSWDTPS_DSWDTPSF     1:2,147,483,648 (25.7 days)
**
**   Deep Sleep Watchdog Timer Oscillator Select:
**     DSWDTOSC_SOSC        DSWDT uses Secondary Oscillator (SOSC)
**     DSWDTOSC_LPRC        DSWDT uses Low Power RC Oscillator (LPRC)
**
**   RTCC Reference Oscillator  Select:
**     RTCOSC_LPRC          RTCC uses Low Power RC Oscillator (LPRC)
**     RTCOSC_SOSC          RTCC uses Secondary Oscillator (SOSC)
**
**   Deep Sleep BOR Enable bit:
**     DSBOREN_OFF          BOR disabled in Deep Sleep
**     DSBOREN_ON           BOR enabled in Deep Sleep
**
**   Deep Sleep Watchdog Timer:
**     DSWDTEN_OFF          DSWDT disabled
**     DSWDTEN_ON           DSWDT enabled
**
*/

/* Register CONFIG3 (0xabfa)                               */

/*
** Only one invocation of CONFIG3 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set CONFIG3.
** Multiple options may be combined, as shown:
**
** _CONFIG3( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Write Protection Flash Page Segment Boundary:
**     WPFP_WPFP0           Page 0 (0x0)
**     WPFP_WPFP1           Page 1 (0x400)
**     WPFP_WPFP2           Page 2 (0x800)
**     WPFP_WPFP3           Page 3 (0xC00)
**     WPFP_WPFP4           Page 4 (0x1000)
**     WPFP_WPFP5           Page 5 (0x1400)
**     WPFP_WPFP6           Page 6 (0x1800)
**     WPFP_WPFP7           Page 7 (0x1C00)
**     WPFP_WPFP8           Page 8 (0x2000)
**     WPFP_WPFP9           Page 9 (0x2400)
**     WPFP_WPFP10          Page 10 (0x2800)
**     WPFP_WPFP11          Page 11 (0x2C00)
**     WPFP_WPFP12          Page 12 (0x3000)
**     WPFP_WPFP13          Page 13 (0x3400)
**     WPFP_WPFP14          Page 14 (0x3800)
**     WPFP_WPFP15          Page 15 (0x3C00)
**     WPFP_WPFP16          Page 16 (0x4000)
**     WPFP_WPFP17          Page 17 (0x4400)
**     WPFP_WPFP18          Page 18 (0x4800)
**     WPFP_WPFP19          Page 19 (0x4C00)
**     WPFP_WPFP20          Page 20 (0x5000)
**     WPFP_WPFP21          Page 21 (0x5400)
**     WPFP_WPFP22          Page 22 (0x5800)
**     WPFP_WPFP23          Page 23 (0x5C00)
**     WPFP_WPFP24          Page 24 (0x6000)
**     WPFP_WPFP25          Page 25 (0x6400)
**     WPFP_WPFP26          Page 26 (0x6800)
**     WPFP_WPFP27          Page 27 (0x6C00)
**     WPFP_WPFP28          Page 28 (0x7000)
**     WPFP_WPFP29          Page 29 (0x7400)
**     WPFP_WPFP30          Page 30 (0x7800)
**     WPFP_WPFP31          Page 31 (0x7C00)
**     WPFP_WPFP32          Page 32 (0x8000)
**     WPFP_WPFP33          Page 33 (0x8400)
**     WPFP_WPFP34          Page 34 (0x8800)
**     WPFP_WPFP35          Page 35 (0x8C00)
**     WPFP_WPFP36          Page 36 (0x9000)
**     WPFP_WPFP37          Page 37 (0x9400)
**     WPFP_WPFP38          Page 38 (0x9800)
**     WPFP_WPFP39          Page 39 (0x9C00)
**     WPFP_WPFP40          Page 40 (0xA000)
**     WPFP_WPFP41          Page 41 (0xA400)
**     WPFP_WPFP42          Page 42 (0xA800)
**     WPFP_WPFP63          Highest Page (same as page 42)
**
**   Secondary Oscillator Pin Mode Select:
**     SOSCSEL_IO           SOSC pins have digital I/O functions (RA4, RB4)
**     SOSCSEL_LPSOSC       SOSC pins in Low-Power (low drive-strength) Oscillator Mode
**     SOSCSEL_SOSC         SOSC pins in Default (high drive-strength) Oscillator Mode
**
**   Voltage Regulator Wake-up Time Select:
**     WUTSEL_FST           Fast regulator start-up time used
**     WUTSEL_LEG           Default regulator start-up time used
**
**   Segment Write Protection Disable:
**     WPDIS_WPEN           Segmented code protection enabled
**     WPDIS_WPDIS          Segmented code protection disabled
**
**   Write Protect Configuration Page Select:
**     WPCFG_WPCFGEN        Last page and Flash Configuration words are code-protected
**     WPCFG_WPCFGDIS       Last page and Flash Configuration words are unprotected
**
**   Segment Write Protection End Page Select:
**     WPEND_WPSTARTMEM     Write Protect from page 0 to WPFP
**     WPEND_WPENDMEM       Write Protect from WPFP to the last page of memory
**
*/

/* Register CONFIG2 (0xabfc)                               */

/*
** Only one invocation of CONFIG2 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set CONFIG2.
** Multiple options may be combined, as shown:
**
** _CONFIG2( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Primary Oscillator Select:
**     POSCMOD_EC           EC Oscillator mode selected
**     POSCMOD_XT           XT Oscillator mode selected
**     POSCMOD_HS           HS Oscillator mode selected
**     POSCMOD_NONE         Primary Oscillator disabled
**
**   I2C1 Pin Select bit:
**     I2C1SEL_SEC          Use alternate SCL1/SDA1 pins for I2C1
**     I2C1SEL_PRI          Use default SCL1/SDA1 pins for I2C1
**
**   IOLOCK One-Way Set Enable:
**     IOL1WAY_OFF          The IOLOCK bit can be set and cleared using the unlock sequence
**     IOL1WAY_ON           Once set, the IOLOCK bit cannot be cleared
**
**   OSCO Pin Configuration:
**     OSCIOFNC_ON          OSCO pin functions as port I/O (RA3)
**     OSCIOFNC_OFF         OSCO pin functions as clock output (CLKO)
**
**   Clock Switching and Fail-Safe Clock Monitor:
**     FCKSM_CSECME         Sw Enabled, Mon Enabled
**     FCKSM_CSECMD         Sw Enabled, Mon Disabled
**     FCKSM_CSDCMD         Sw Disabled, Mon Disabled
**
**   Initial Oscillator Select:
**     FNOSC_FRC            Fast RC Oscillator (FRC)
**     FNOSC_FRCPLL         Fast RC Oscillator with Postscaler and PLL module (FRCPLL)
**     FNOSC_PRI            Primary Oscillator (XT, HS, EC)
**     FNOSC_PRIPLL         Primary Oscillator with PLL module (XTPLL, HSPLL, ECPLL)
**     FNOSC_SOSC           Secondary Oscillator (SOSC)
**     FNOSC_LPRC           Low-Power RC Oscillator (LPRC)
**     FNOSC_FRCDIV         Fast RC Oscillator with Postscaler (FRCDIV)
**
**   Internal External Switchover:
**     IESO_OFF             IESO mode (Two-Speed Start-up) disabled
**     IESO_ON              IESO mode (Two-Speed Start-up) enabled
**
*/

/* Register CONFIG1 (0xabfe)                               */

/*
** Only one invocation of CONFIG1 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set CONFIG1.
** Multiple options may be combined, as shown:
**
** _CONFIG1( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Watchdog Timer Postscaler:
**     WDTPS_PS1            1:1
**     WDTPS_PS2            1:2
**     WDTPS_PS4            1:4
**     WDTPS_PS8            1:8
**     WDTPS_PS16           1:16
**     WDTPS_PS32           1:32
**     WDTPS_PS64           1:64
**     WDTPS_PS128          1:128
**     WDTPS_PS256          1:256
**     WDTPS_PS512          1:512
**     WDTPS_PS1024         1:1,024
**     WDTPS_PS2048         1:2,048
**     WDTPS_PS4096         1:4,096
**     WDTPS_PS8192         1:8,192
**     WDTPS_PS16384        1:16,384
**     WDTPS_PS32768        1:32,768
**
**   WDT Prescaler:
**     FWPSA_PR32           1:32
**     FWPSA_PR128          1:128
**
**   Windowed WDT:
**     WINDIS_ON            Windowed Watchdof timer enabled
**     WINDIS_OFF           Standard Watchdog Timer is enabled
**
**   Watchdog Timer:
**     FWDTEN_OFF           Watchdog Timer is disabled
**     FWDTEN_ON            Watchdog Timer is enabled
**
**   Emulator Pin Placement Select bits:
**     ICS_PGx3             Emulator functions are shared with PGEC3/PGED3
**     ICS_PGx2             Emulator functions are shared with PGEC2/PGED2
**     ICS_PGx1             Emulator functions are shared with PGEC1/PGED1
**
**   General Segment Write Protect:
**     GWRP_ON              Writes to program memory are allowed
**     GWRP_OFF             Writes to program memory are disabled
**
**   General Segment Code Protect:
**     GCP_ON               Code protection is enabled
**     GCP_OFF              Code protection is disabled
**
**   JTAG Port Enable:
**     JTAGEN_OFF           JTAG port is Disabled
**     JTAGEN_ON            JTAG port is Enabled
**
*/

//#endif

#elif 	defined(__PIC24FJ64GA002__) | defined (__PIC24FJ64GA004__) | \
		defined(__PIC24FJ48GA002__) | defined (__PIC24FJ48GA004__) | \
		defined(__PIC24FJ32GA002__) | defined (__PIC24FJ32GA004__) | \
		defined(__PIC24FJ16GA002__) | defined (__PIC24FJ16GA004__)

//config fues settings for everything else - need customization
_CONFIG1(
    JTAGEN_OFF &					//Disable JTAG port
    GCP_OFF &						//Disable code protect
    GWRP_OFF &						//Disable write protect
    BKBUG_OFF &						//Enable background debugger
    COE_OFF &						//Device resets into operational mode
    ICS_PGx2 &						//EMUC/EMUD share PGC2/PGD2
    FWDTEN_OFF &					//Disable watchdog timer (WDT)
    WINDIS_OFF &					//Use standard WDT (if it is enabled)
    FWPSA_PR128 &					//Use WDT prescaler ratio of 1:128
    WDTPS_PS32768					//Use WDT postscaler ratio of 1:32,768
)

_CONFIG2(
    IESO_OFF &						//Disabled
    SOSCSEL_SOSC &					//Default Secondary Oscillator
    WUTSEL_LEG &					//Legacy Wake-up timer selected
    FNOSC_PRI &						//FNOSC_PRI = Primary oscillator (XT, HS, EC). FNOSC_FRC -> 8Mhz internal rc (default to 2Mhz)
    FCKSM_CSDCMD &					//Clock switching and clock monitor disabled
    OSCIOFNC_OFF &					//OSCO or Fosc/2
    IOL1WAY_OFF &					//Unlimited Writes To RP Registers
    I2C1SEL_PRI &					//Use Primary I2C1 pins
    POSCMOD_HS						//High speed seeting for external oscillator
)
/* Register CONFIG2 (0xabfc)                               */

/*
** Only one invocation of CONFIG2 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set CONFIG2.
** Multiple options may be combined, as shown:
**
** _CONFIG2( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Two Speed Start-up:
**     IESO_OFF             Disabled
**     IESO_ON              Enabled
**
**   Secondary Oscillator:
**     SOSCSEL_LPSOSC       Low Power Secondary Oscillator
**     SOSCSEL_SOSC         Default Secondary Oscillator
**
**   Voltage Regulator Standby-mode Wake-up Timer:
**     WUTSEL_FST           Fast Wake-up timer selected
**     WUTSEL_LEG           Legacy Wake-up timer selected
**
**   Oscillator Selection:
**     FNOSC_FRC            Fast RC oscillator
**     FNOSC_FRCPLL         Fast RC oscillator w/ divide and PLL
**     FNOSC_PRI            Primary oscillator (XT, HS, EC)
**     FNOSC_PRIPLL         Primary oscillator (XT, HS, EC) w/ PLL
**     FNOSC_SOSC           Secondary oscillator
**     FNOSC_LPRC           Low power RC oscillator
**     FNOSC_FRCDIV         Fast RC oscillator with divide
**
**   Clock switching and clock monitor:
**     FCKSM_CSECME         Both enabled
**     FCKSM_CSECMD         Only clock switching enabled
**     FCKSM_CSDCMD         Both disabled
**
**   OSCO/RC15 function:
**     OSCIOFNC_ON          RC15
**     OSCIOFNC_OFF         OSCO or Fosc/2
**
**   RP Register Protection:
**     IOL1WAY_OFF          Unlimited Writes To RP Registers
**     IOL1WAY_ON           Write RP Registers Once
**
**   I2C1 pins Select:
**     I2C1SEL_SEC          Use Secondary I2C1 pins
**     I2C1SEL_PRI          Use Primary I2C1 pins
**
**   Oscillator Selection:
**     POSCMOD_EC           External clock
**     POSCMOD_XT           XT oscillator
**     POSCMOD__S           HS oscillator
**     POSCMOD_NONE         Primary disabled
**
*/

/* Register CONFIG1 (0xabfe)                               */


/*
** Only one invocation of CONFIG1 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set CONFIG1.
** Multiple options may be combined, as shown:
**
** _CONFIG1( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   JTAG:
**     JTAGEN_OFF           Disabled
**     JTAGEN_ON            Enabled
**
**   Code Protect:
**     GCP_ON               Enabled
**     GCP_OFF              Disabled
**
**   Write Protect:
**     GWRP_ON              Enabled
**     GWRP_OFF             Disabled
**
**   Background Debugger:
**     BKBUG_ON             Enabled
**     BKBUG_OFF            Disabled
**
**   Clip-on Emulation mode:
**     COE_ON               Enabled
**     COE_OFF              Disabled
**
**   ICD pins select:
**     ICS_PGx3             EMUC/EMUD share PGC3/PGD3
**     ICS_PGx2             EMUC/EMUD share PGC2/PGD2
**     ICS_PGx1             EMUC/EMUD share PGC1/PGD1
**
**   Watchdog Timer:
**     FWDTEN_OFF           Disabled
**     FWDTEN_ON            Enabled
**
**   Windowed WDT:
**     WINDIS_ON            Enabled
**     WINDIS_OFF           Disabled
**
**   Watchdog prescaler:
**     FWPSA_PR32           1:32
**     FWPSA_PR128          1:128
**
**   Watchdog postscale:
**     WDTPS_PS1            1:1
**     WDTPS_PS2            1:2
**     WDTPS_PS4            1:4
**     WDTPS_PS8            1:8
**     WDTPS_PS16           1:16
**     WDTPS_PS32           1:32
**     WDTPS_PS64           1:64
**     WDTPS_PS128          1:128
**     WDTPS_PS256          1:256
**     WDTPS_PS512          1:512
**     WDTPS_PS1024         1:1,024
**     WDTPS_PS2048         1:2,048
**     WDTPS_PS4096         1:4,096
**     WDTPS_PS8192         1:8,192
**     WDTPS_PS16384        1:16,384
**     WDTPS_PS32768        1:32,768
**
*/
//#endif

#elif 	defined(__PIC24FJ64GB002__) | defined(__PIC24FJ64GB004__) | \
	defined(__PIC24FJ48GB002__) | defined(__PIC24FJ48GB004__) | \
	defined(__PIC24FJ32GB002__) | defined(__PIC24FJ32GB004__)


_CONFIG1(
    WDTPS_PS32768 &			//1:32,768
    FWPSA_PR128 &			//1:128
    WINDIS_OFF &			//Standard Watchdog Timer is enabled
    FWDTEN_OFF &			//Watchdog Timer is disabled
    ICS_PGx1 &			//Emulator functions are shared with PGEC1/PGED1
    GWRP_OFF &			//Writes to program memory are disabled
    GCP_OFF	&			//Code protection is disabled
    JTAGEN_OFF			//JTAG port is Disabled
)

_CONFIG2(
    POSCMOD__S &			//HS Oscillator mode selected
    I2C1SEL_PRI &			//Use default SCL1/SDA1 pins for I2C1
    IOL1WAY_OFF &			//The IOLOCK bit can be set and cleared using the unlock sequence
    OSCIOFNC_OFF &			//OSCO pin functions as clock output (CLKO)
    FCKSM_CSDCMD &			//Sw Disabled, Mon Disabled
    FNOSC_PRI &			//Primary Oscillator (XT, HS, EC)
    PLL96MHZ_ON &			//96 MHz PLL Startup is enabled automatically on start-up
    PLLDIV_DIV12 &			//Oscillator input divided by 12 (48 MHz input)
    IESO_OFF			//IESO mode (Two-Speed Start-up) disabled
)

_CONFIG3(
    WPFP_WPFP63 &			//Highest Page (same as page 42)
    SOSCSEL_IO &			//SOSC pins have digital I/O functions (RA4, RB4)
    WUTSEL_LEG &			//Default regulator start-up time used
    WPDIS_WPDIS &			//Segmented code protection disabled
    WPCFG_WPCFGDIS &		//Last page and Flash Configuration words are unprotected
    WPEND_WPSTARTMEM		//Write Protect from page 0 to WPFP
)

_CONFIG4(
    DSWDTPS_DSWDTPSF &		//1:2,147,483,648 (25.7 days)
    DSWDTOSC_SOSC &			//DSWDT uses Secondary Oscillator (SOSC)
    RTCOSC_LPRC &			//RTCC uses Low Power RC Oscillator (LPRC)
    DSBOREN_OFF &			//BOR disabled in Deep Sleep
    DSWDTEN_OFF			//DSWDT disabled
)
/* -------------------------------------------------------- */
/* Macros for setting device configuration registers        */
/* -------------------------------------------------------- */

/* Register CONFIG4 (0xabf8)                               */

/*
** Only one invocation of CONFIG4 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set CONFIG4.
** Multiple options may be combined, as shown:
**
** _CONFIG4( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   DSWDT Postscale Select:
**     DSWDTPS_DSWDTPS0     1:2 (2.1 ms)
**     DSWDTPS_DSWDTPS1     1:8 (8.3 ms)
**     DSWDTPS_DSWDTPS2     1:32 (33 ms)
**     DSWDTPS_DSWDTPS3     1:128 (132 ms)
**     DSWDTPS_DSWDTPS4     1:512 (528 ms)
**     DSWDTPS_DSWDTPS5     1:2,048 (2.1 seconds)
**     DSWDTPS_DSWDTPS6     1:8,192 (8.5 seconds)
**     DSWDTPS_DSWDTPS7     1:32,768 (34 seconds)
**     DSWDTPS_DSWDTPS8     1:131,072 (135 seconds)
**     DSWDTPS_DSWDTPS9     1:524,288 (9 minutes)
**     DSWDTPS_DSWDTPSA     1:2,097,152 (36 minutes)
**     DSWDTPS_DSWDTPSB     1:8,388,608 (2.4 hours)
**     DSWDTPS_DSWDTPSC     1:33,554,432 (9.6 hours)
**     DSWDTPS_DSWDTPSD     1:134,217,728 (38.5 hours)
**     DSWDTPS_DSWDTPSE     1:536,870,912 (6.4 days)
**     DSWDTPS_DSWDTPSF     1:2,147,483,648 (25.7 days)
**
**   Deep Sleep Watchdog Timer Oscillator Select:
**     DSWDTOSC_SOSC        DSWDT uses Secondary Oscillator (SOSC)
**     DSWDTOSC_LPRC        DSWDT uses Low Power RC Oscillator (LPRC)
**
**   RTCC Reference Oscillator  Select:
**     RTCOSC_LPRC          RTCC uses Low Power RC Oscillator (LPRC)
**     RTCOSC_SOSC          RTCC uses Secondary Oscillator (SOSC)
**
**   Deep Sleep BOR Enable bit:
**     DSBOREN_OFF          BOR disabled in Deep Sleep
**     DSBOREN_ON           BOR enabled in Deep Sleep
**
**   Deep Sleep Watchdog Timer:
**     DSWDTEN_OFF          DSWDT disabled
**     DSWDTEN_ON           DSWDT enabled
**
*/

/* Register CONFIG3 (0xabfa)                               */

/*
** Only one invocation of CONFIG3 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set CONFIG3.
** Multiple options may be combined, as shown:
**
** _CONFIG3( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Write Protection Flash Page Segment Boundary:
**     WPFP_WPFP0           Page 0 (0x0)
**     WPFP_WPFP1           Page 1 (0x400)
**     WPFP_WPFP2           Page 2 (0x800)
**     WPFP_WPFP3           Page 3 (0xC00)
**     WPFP_WPFP4           Page 4 (0x1000)
**     WPFP_WPFP5           Page 5 (0x1400)
**     WPFP_WPFP6           Page 6 (0x1800)
**     WPFP_WPFP7           Page 7 (0x1C00)
**     WPFP_WPFP8           Page 8 (0x2000)
**     WPFP_WPFP9           Page 9 (0x2400)
**     WPFP_WPFP10          Page 10 (0x2800)
**     WPFP_WPFP11          Page 11 (0x2C00)
**     WPFP_WPFP12          Page 12 (0x3000)
**     WPFP_WPFP13          Page 13 (0x3400)
**     WPFP_WPFP14          Page 14 (0x3800)
**     WPFP_WPFP15          Page 15 (0x3C00)
**     WPFP_WPFP16          Page 16 (0x4000)
**     WPFP_WPFP17          Page 17 (0x4400)
**     WPFP_WPFP18          Page 18 (0x4800)
**     WPFP_WPFP19          Page 19 (0x4C00)
**     WPFP_WPFP20          Page 20 (0x5000)
**     WPFP_WPFP21          Page 21 (0x5400)
**     WPFP_WPFP22          Page 22 (0x5800)
**     WPFP_WPFP23          Page 23 (0x5C00)
**     WPFP_WPFP24          Page 24 (0x6000)
**     WPFP_WPFP25          Page 25 (0x6400)
**     WPFP_WPFP26          Page 26 (0x6800)
**     WPFP_WPFP27          Page 27 (0x6C00)
**     WPFP_WPFP28          Page 28 (0x7000)
**     WPFP_WPFP29          Page 29 (0x7400)
**     WPFP_WPFP30          Page 30 (0x7800)
**     WPFP_WPFP31          Page 31 (0x7C00)
**     WPFP_WPFP32          Page 32 (0x8000)
**     WPFP_WPFP33          Page 33 (0x8400)
**     WPFP_WPFP34          Page 34 (0x8800)
**     WPFP_WPFP35          Page 35 (0x8C00)
**     WPFP_WPFP36          Page 36 (0x9000)
**     WPFP_WPFP37          Page 37 (0x9400)
**     WPFP_WPFP38          Page 38 (0x9800)
**     WPFP_WPFP39          Page 39 (0x9C00)
**     WPFP_WPFP40          Page 40 (0xA000)
**     WPFP_WPFP41          Page 41 (0xA400)
**     WPFP_WPFP42          Page 42 (0xA800)
**     WPFP_WPFP63          Highest Page (same as page 42)
**
**   Secondary Oscillator Pin Mode Select:
**     SOSCSEL_IO           SOSC pins have digital I/O functions (RA4, RB4)
**     SOSCSEL_LPSOSC       SOSC pins in Low-Power (low drive-strength) Oscillator Mode
**     SOSCSEL_SOSC         SOSC pins in Default (high drive-strength) Oscillator Mode
**
**   Voltage Regulator Wake-up Time Select:
**     WUTSEL_FST           Fast regulator start-up time used
**     WUTSEL_LEG           Default regulator start-up time used
**
**   Segment Write Protection Disable:
**     WPDIS_WPEN           Segmented code protection enabled
**     WPDIS_WPDIS          Segmented code protection disabled
**
**   Write Protect Configuration Page Select:
**     WPCFG_WPCFGEN        Last page and Flash Configuration words are code-protected
**     WPCFG_WPCFGDIS       Last page and Flash Configuration words are unprotected
**
**   Segment Write Protection End Page Select:
**     WPEND_WPSTARTMEM     Write Protect from page 0 to WPFP
**     WPEND_WPENDMEM       Write Protect from WPFP to the last page of memory
**
*/

/* Register CONFIG2 (0xabfc)                               */
/*
** Only one invocation of CONFIG2 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set CONFIG2.
** Multiple options may be combined, as shown:
**
** _CONFIG2( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Primary Oscillator Select:
**     POSCMOD_EC           EC Oscillator mode selected
**     POSCMOD_XT           XT Oscillator mode selected
**     POSCMOD__S           HS Oscillator mode selected
**     POSCMOD_NONE         Primary Oscillator disabled
**
**   I2C1 Pin Select bit:
**     I2C1SEL_SEC          Use alternate SCL1/SDA1 pins for I2C1
**     I2C1SEL_PRI          Use default SCL1/SDA1 pins for I2C1
**
**   IOLOCK One-Way Set Enable:
**     IOL1WAY_OFF          The IOLOCK bit can be set and cleared using the unlock sequence
**     IOL1WAY_ON           Once set, the IOLOCK bit cannot be cleared
**
**   OSCO Pin Configuration:
**     OSCIOFNC_ON          OSCO pin functions as port I/O (RA3)
**     OSCIOFNC_OFF         OSCO pin functions as clock output (CLKO)
**
**   Clock Switching and Fail-Safe Clock Monitor:
**     FCKSM_CSECME         Sw Enabled, Mon Enabled
**     FCKSM_CSECMD         Sw Enabled, Mon Disabled
**     FCKSM_CSDCMD         Sw Disabled, Mon Disabled
**
**   Initial Oscillator Select:
**     FNOSC_FRC            Fast RC Oscillator (FRC)
**     FNOSC_FRCPLL         Fast RC Oscillator with Postscaler and PLL module (FRCPLL)
**     FNOSC_PRI            Primary Oscillator (XT, HS, EC)
**     FNOSC_PRIPLL         Primary Oscillator with PLL module (XTPLL, HSPLL, ECPLL)
**     FNOSC_SOSC           Secondary Oscillator (SOSC)
**     FNOSC_LPRC           Low-Power RC Oscillator (LPRC)
**     FNOSC_FRCDIV         Fast RC Oscillator with Postscaler (FRCDIV)
**
**   96MHz PLL Startup Select:
**     PLL96MHZ_OFF         96 MHz PLL Startup is enabled by user in software( controlled with the PLLEN bit)
**     PLL96MHZ_ON          96 MHz PLL Startup is enabled automatically on start-up
**
**   USB 96 MHz PLL Prescaler Select:
**     PLLDIV_NODIV         Oscillator input used directly (4 MHz input)
**     PLLDIV_DIV2          Oscillator input divided by 2 (8 MHz input)
**     PLLDIV_DIV3          Oscillator input divided by 3 (12 MHz input)
**     PLLDIV_DIV4          Oscillator input divided by 4 (16 MHz input)
**     PLLDIV_DIV5          Oscillator input divided by 5 (20 MHz input)
**     PLLDIV_DIV6          Oscillator input divided by 6 (24 MHz input)
**     PLLDIV_DIV8          Oscillator input divided by 8 (32 MHz input)
**     PLLDIV_DIV12         Oscillator input divided by 12 (48 MHz input)
**
**   Internal External Switchover:
**     IESO_OFF             IESO mode (Two-Speed Start-up) disabled
**     IESO_ON              IESO mode (Two-Speed Start-up) enabled
**
*/

/* Register CONFIG1 (0xabfe)                               */
/*
** Only one invocation of CONFIG1 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set CONFIG1.
** Multiple options may be combined, as shown:
**
** _CONFIG1( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Watchdog Timer Postscaler:
**     WDTPS_PS1            1:1
**     WDTPS_PS2            1:2
**     WDTPS_PS4            1:4
**     WDTPS_PS8            1:8
**     WDTPS_PS16           1:16
**     WDTPS_PS32           1:32
**     WDTPS_PS64           1:64
**     WDTPS_PS128          1:128
**     WDTPS_PS256          1:256
**     WDTPS_PS512          1:512
**     WDTPS_PS1024         1:1,024
**     WDTPS_PS2048         1:2,048
**     WDTPS_PS4096         1:4,096
**     WDTPS_PS8192         1:8,192
**     WDTPS_PS16384        1:16,384
**     WDTPS_PS32768        1:32,768
**
**   WDT Prescaler:
**     FWPSA_PR32           1:32
**     FWPSA_PR128          1:128
**
**   Windowed WDT:
**     WINDIS_ON            Windowed Watchdof timer enabled
**     WINDIS_OFF           Standard Watchdog Timer is enabled
**
**   Watchdog Timer:
**     FWDTEN_OFF           Watchdog Timer is disabled
**     FWDTEN_ON            Watchdog Timer is enabled
**
**   Emulator Pin Placement Select bits:
**     ICS_PGx3             Emulator functions are shared with PGEC3/PGED3
**     ICS_PGx2             Emulator functions are shared with PGEC2/PGED2
**     ICS_PGx1             Emulator functions are shared with PGEC1/PGED1
**
**   General Segment Write Protect:
**     GWRP_ON              Writes to program memory are allowed
**     GWRP_OFF             Writes to program memory are disabled
**
**   General Segment Code Protect:
**     GCP_ON               Code protection is enabled
**     GCP_OFF              Code protection is disabled
**
**   JTAG Port Enable:
**     JTAGEN_OFF           JTAG port is Disabled
**     JTAGEN_ON            JTAG port is Enabled
**
*/

//#endif

//dsPIC33FJ12GP201//dsPIC33FJ12GP202
//dsPIC33FJ12MC201/dsPIC33FJ12/MC202

#elif 	defined(__dsPIC33FJ32GP201__) || defined(__dsPIC33FJ32GP202__) ||\
		defined(__dsPIC33FJ32MC201__) || defined(__dsPIC33FJ32MC202__) || defined(__dsPIC33FJ32MC204__)

_FBS( 	BSS_NO_BOOT_CODE &	//No Boot Segment Program Memory
        BWRP_WRPROTECT_OFF	//Disabled
    )

_FGS( 	GSS_OFF &			//code protect off
        GCP_OFF &			//code protect Disabled
        GWRP_OFF         	//write protect Disabled
    )

_FOSCSEL(						//Oscillator Source Selection:
//**     FNOSC_FRC            Fast RC oscillator
//**     FNOSC_FRCPLL         Fast RC oscillator w/ divide and PLL
    FNOSC_PRI &			//Primary oscillator (XT, HS, EC)
//**     FNOSC_PRIPLL         Primary oscillator (XT, HS, EC) w/ PLL
//**     FNOSC_SOSC           Secondary oscillator
//**     FNOSC_LPRC           Low power RC oscillator
//**     FNOSC_FRCDIV16       Fast RC oscillator w/ divide by 16
//**     FNOSC_LPRCDIVN        Low power Fast RC oscillator w/divide by N

//**   Two-speed Oscillator Startup :
//**     IESO_OFF             Disabled
    IESO_ON			//Enabled
)

_FOSC( 						//Clock switching and clock monitor:
//**     FCKSM_CSECME         Both enabled
//**     FCKSM_CSECMD         Only clock switching enabled
    FCKSM_CSDCMD &		//Both disabled

//**   Single configuration for remappable I/O:
//**     IOL1WAY_OFF          Disabled
    IOL1WAY_ON & 		//Enabled

//**   OSC2 Pin function:
//**     OSCIOFNC_ON          Digital I/O
    OSCIOFNC_OFF & 		//OSC2 is clock O/P

//**   Oscillator Selection:
//**     POSCMD_EC            External clock
//**     POSCMD_XT            XT oscillator
    POSCMD_HS			//HS oscillator
//**     POSCMD_NONE          Primary disabled
)

_FWDT(
//**   Watchdog Timer:
    FWDTEN_OFF &		//Disabled
//**     FWDTEN_ON            Enabled

//**   Windowed WDT:
//**     WINDIS_ON            Enabled
    WINDIS_OFF &		//Disabled

//**   Watchdog prescaler:
//**     WDTPRE_PR32          1:32
    WDTPRE_PR128 &		//1:128

//**   Watchdog postscaler:
    WDTPOST_PS1       	//1:1
//**     WDTPOST_PS2          1:2
//**     WDTPOST_PS4          1:4
//**     WDTPOST_PS8          1:8
//**     WDTPOST_PS16         1:16
//**     WDTPOST_PS32         1:32
//**     WDTPOST_PS64         1:64
//**     WDTPOST_PS128        1:128
//**     WDTPOST_PS256        1:256
//**     WDTPOST_PS512        1:512
//**     WDTPOST_PS1024       1:1,024
//**     WDTPOST_PS2048       1:2,048
//**     WDTPOST_PS4096       1:4,096
//**     WDTPOST_PS8192       1:8,192
//**     WDTPOST_PS16384      1:16,384
//**     WDTPOST_PS32768      1:32,768
)

_FPOR(
//**   Power-on Reset Value:
    FPWRT_PWR1 & 		//Disabled
//**     FPWRT_PWR2           2ms
//**     FPWRT_PWR4           4ms
//**     FPWRT_PWR8           8ms
//**     FPWRT_PWR16          16ms
//**     FPWRT_PWR32          32ms
//**     FPWRT_PWR64          64ms
//**     FPWRT_PWR128         128ms
//**
//**   Alternate I2C pins:
//**     ALTI2C_ON            I2C mapped to ASDA1/ASCL1
    ALTI2C_OFF			//I2C mapped to SDA1/SCL1
)

_FICD(
//**   JTAG Enable Bit:
    JTAGEN_OFF &		//JTAG is disabled
//**     JTAGEN_ON            JTAG is enabled
//**
//**   ICD communication channel select bits:
//		ICS_NONE			//Reserved
//**     ICS_PGD3              communicate on PGC3/EMUC3 and PGD3/EMUD3
//**     ICS_PGD2             communicate on PGC2/EMUC2 and PGD2/EMUD2
    ICS_PGD1			//communicate on PGC1/EMUC1 and PGD1/EMUD1
)

//user specified id
//_FUID0(0xffff )
//_FUID1(0xffff )
//_FUID2(0xffff )
//_FUID3(0xffff )

/* -------------------------------------------------------- */
/* Macros for setting device configuration registers        */
/* -------------------------------------------------------- */


/* Register FBS (0xf80000)                               */

//extern __attribute__((space(prog))) int _FBS;
//#define _FBS(x) __attribute__((section("__FBS.sec"),space(prog))) int _FBS = (x);

/*
** Only one invocation of FBS should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FBS.
** Multiple options may be combined, as shown:
**
** _FBS( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Boot Segment Program Memory:
**     BSS__IGH_LARGE_BOOT_CODE High Security Lar Boot Flash
**     BSS_LARGE_FLASH__IGH  High Security Lar Boot Flash
**     BSS__IGH_MEDIUM_BOOT_CODE High Security Med Boot Flash
**     BSS_MEDIUM_FLASH__IGH High Security Med Boot Flash
**     BSS__IGH_SMALL_BOOT_CODE High Security Small Boot Flash
**     BSS_SMALL_FLASH__IGH  High Security Small Boot Flash
**     BSS_LARGE_FLASH_STD   Standard Security Lar Boot Flash
**     BSS_STRD_LARGE_BOOT_CODE Standard Security Lar Boot Flash
**     BSS_MEDIUM_FLASH_STD  Standard Security Med Boot Flash
**     BSS_STRD_MEDIUM_BOOT_CODE Standard Security Med Boot Flash
**     BSS_SMALL_FLASH_STD  Standard Security Small Boot Flash
**     BSS_STRD_SMALL_BOOT_CODEStandard Security Small Boot Flash
**     BSS_NO_BOOT_CODE     No Boot Segment Program Memory
**     BSS_NO_FLASH         No Boot Segment Program Memory
**
**    Write Protect :
**     BWRP_WRPROTECT_ON     Enabled
**     BWRP_WRPROTECT_OFF    Disabled
**
*/
/*
#define BSS__IGH_LARGE_BOOT_CODE 0xFFF1
#define BSS_LARGE_FLASH__IGH 0xFFF1
#define BSS__IGH_MEDIUM_BOOT_CODE 0xFFF3
#define BSS_MEDIUM_FLASH__IGH 0xFFF3
#define BSS__IGH_SMALL_BOOT_CODE 0xFFF5
#define BSS_SMALL_FLASH__IGH 0xFFF5
#define BSS_LARGE_FLASH_STD  0xFFF9
#define BSS_STRD_LARGE_BOOT_CODE 0xFFF9
#define BSS_MEDIUM_FLASH_STD 0xFFFB
#define BSS_STRD_MEDIUM_BOOT_CODE 0xFFFB
#define BSS_SMALL_FLASH_STD  0xFFFD
#define BSS_STRD_SMALL_BOOT_CODE 0xFFFD
#define BSS_NO_BOOT_CODE     0xFFFF
#define BSS_NO_FLASH         0xFFFF

#define BWRP_WRPROTECT_ON    0xFFFE
#define BWRP_WRPROTECT_OFF   0xFFFF
*/
/* Register FGS (0xf80004)                               */

//extern __attribute__((space(prog))) int _FGS;
//#define _FGS(x) __attribute__((section("__FGS.sec"),space(prog))) int _FGS = (x);

/*
** Only one invocation of FGS should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FGS.
** Multiple options may be combined, as shown:
**
** _FGS( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Code Protect:
**     GSS__IGH              high security protect on
**     GSS_STD               standard security code protect on
**     GSS_OFF              code protect off
**
**   Code Protect:
**     GCP_ON               Enabled
**     GCP_OFF              Disabled
**
**   Write Protect:
**     GWRP_ON              Enabled
**     GWRP_OFF             Disabled
**
*/
/*
#define GSS__IGH             0xFFFB
#define GSS_STD              0xFFFD
#define GSS_OFF              0xFFFF

#define GCP_ON               0xFFFD
#define GCP_OFF              0xFFFF

#define GWRP_ON              0xFFFE
#define GWRP_OFF             0xFFFF
*/
/* Register FOSCSEL (0xf80006)                               */

//extern __attribute__((space(prog))) int _FOSCSEL;
//#define _FOSCSEL(x) __attribute__((section("__FOSCSEL.sec"),space(prog))) int _FOSCSEL = (x);

/*
** Only one invocation of FOSCSEL should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FOSCSEL.
** Multiple options may be combined, as shown:
**
** _FOSCSEL( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Oscillator Source Selection:
**     FNOSC_FRC            Fast RC oscillator
**     FNOSC_FRCPLL         Fast RC oscillator w/ divide and PLL
**     FNOSC_PRI            Primary oscillator (XT, HS, EC)
**     FNOSC_PRIPLL         Primary oscillator (XT, HS, EC) w/ PLL
**     FNOSC_SOSC           Secondary oscillator
**     FNOSC_LPRC           Low power RC oscillator
**     FNOSC_FRCDIV16       Fast RC oscillator w/ divide by 16
**     FNOSC_LPRCDIVN        Low power Fast RC oscillator w/divide by N
**
**   Two-speed Oscillator Startup :
**     IESO_OFF             Disabled
**     IESO_ON              Enabled
**
*/
/*
#define FNOSC_FRC            0xFFF8
#define FNOSC_FRCPLL         0xFFF9
#define FNOSC_PRI            0xFFFA
#define FNOSC_PRIPLL         0xFFFB
#define FNOSC_SOSC           0xFFFC
#define FNOSC_LPRC           0xFFFD
#define FNOSC_FRCDIV16       0xFFFE
#define FNOSC_LPRCDIVN       0xFFFF

#define IESO_OFF             0xFF7F
#define IESO_ON              0xFFFF
*/
/* Register FOSC (0xf80008)                               */

//extern __attribute__((space(prog))) int _FOSC;
//#define _FOSC(x) __attribute__((section("__FOSC.sec"),space(prog))) int _FOSC = (x);

/*
** Only one invocation of FOSC should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FOSC.
** Multiple options may be combined, as shown:
**
** _FOSC( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Clock switching and clock monitor:
**     FCKSM_CSECME         Both enabled
**     FCKSM_CSECMD         Only clock switching enabled
**     FCKSM_CSDCMD         Both disabled
**
**   Single configuration for remappable I/O:
**     IOL1WAY_OFF          Disabled
**     IOL1WAY_ON           Enabled
**
**   OSC2 Pin function:
**     OSCIOFNC_ON          Digital I/O
**     OSCIOFNC_OFF         OSC2 is clock O/P
**
**   Oscillator Selection:
**     POSCMD_EC            External clock
**     POSCMD_XT            XT oscillator
**     POSCMD__S            HS oscillator
**     POSCMD_NONE          Primary disabled
**
*/
/*
#define FCKSM_CSECME         0xFF3F
#define FCKSM_CSECMD         0xFF7F
#define FCKSM_CSDCMD         0xFFBF

#define IOL1WAY_OFF          0xFFDF
#define IOL1WAY_ON           0xFFFF

#define OSCIOFNC_ON          0xFFFB
#define OSCIOFNC_OFF         0xFFFF

#define POSCMD_EC            0xFFFC
#define POSCMD_XT            0xFFFD
#define POSCMD__S            0xFFFE
#define POSCMD_NONE          0xFFFF
*/
/* Register FWDT (0xf8000a)                               */

//extern __attribute__((space(prog))) int _FWDT;
//#define _FWDT(x) __attribute__((section("__FWDT.sec"),space(prog))) int _FWDT = (x);

/*
** Only one invocation of FWDT should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FWDT.
** Multiple options may be combined, as shown:
**
** _FWDT( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Watchdog Timer:
**     FWDTEN_OFF           Disabled
**     FWDTEN_ON            Enabled
**
**   Windowed WDT:
**     WINDIS_ON            Enabled
**     WINDIS_OFF           Disabled
**
**   Watchdog prescaler:
**     WDTPRE_PR32          1:32
**     WDTPRE_PR128         1:128
**
**   Watchdog postscaler:
**     WDTPOST_PS1          1:1
**     WDTPOST_PS2          1:2
**     WDTPOST_PS4          1:4
**     WDTPOST_PS8          1:8
**     WDTPOST_PS16         1:16
**     WDTPOST_PS32         1:32
**     WDTPOST_PS64         1:64
**     WDTPOST_PS128        1:128
**     WDTPOST_PS256        1:256
**     WDTPOST_PS512        1:512
**     WDTPOST_PS1024       1:1,024
**     WDTPOST_PS2048       1:2,048
**     WDTPOST_PS4096       1:4,096
**     WDTPOST_PS8192       1:8,192
**     WDTPOST_PS16384      1:16,384
**     WDTPOST_PS32768      1:32,768
**
*/

/*
#define FWDTEN_OFF           0xFF7F
#define FWDTEN_ON            0xFFFF

#define WINDIS_ON            0xFFBF
#define WINDIS_OFF           0xFFFF

#define WDTPRE_PR32          0xFFEF
#define WDTPRE_PR128         0xFFFF

#define WDTPOST_PS1          0xFFF0
#define WDTPOST_PS2          0xFFF1
#define WDTPOST_PS4          0xFFF2
#define WDTPOST_PS8          0xFFF3
#define WDTPOST_PS16         0xFFF4
#define WDTPOST_PS32         0xFFF5
#define WDTPOST_PS64         0xFFF6
#define WDTPOST_PS128        0xFFF7
#define WDTPOST_PS256        0xFFF8
#define WDTPOST_PS512        0xFFF9
#define WDTPOST_PS1024       0xFFFA
#define WDTPOST_PS2048       0xFFFB
#define WDTPOST_PS4096       0xFFFC
#define WDTPOST_PS8192       0xFFFD
#define WDTPOST_PS16384      0xFFFE
#define WDTPOST_PS32768      0xFFFF
*/
/* Register FPOR (0xf8000c)                               */

//extern __attribute__((space(prog))) int _FPOR;
//#define _FPOR(x) __attribute__((section("__FPOR.sec"),space(prog))) int _FPOR = (x);

/*
** Only one invocation of FPOR should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FPOR.
** Multiple options may be combined, as shown:
**
** _FPOR( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Power-on Reset Value:
**     FPWRT_PWR1           Disabled
**     FPWRT_PWR2           2ms
**     FPWRT_PWR4           4ms
**     FPWRT_PWR8           8ms
**     FPWRT_PWR16          16ms
**     FPWRT_PWR32          32ms
**     FPWRT_PWR64          64ms
**     FPWRT_PWR128         128ms
**
**   Alternate I2C pins:
**     ALTI2C_ON            I2C mapped to ASDA1/ASCL1
**     ALTI2C_OFF           I2C mapped to SDA1/SCL1
**
*/
/*
#define FPWRT_PWR1           0xFFF8
#define FPWRT_PWR2           0xFFF9
#define FPWRT_PWR4           0xFFFA
#define FPWRT_PWR8           0xFFFB
#define FPWRT_PWR16          0xFFFC
#define FPWRT_PWR32          0xFFFD
#define FPWRT_PWR64          0xFFFE
#define FPWRT_PWR128         0xFFFF

#define ALTI2C_ON            0xFFEF
#define ALTI2C_OFF           0xFFFF
*/

/* Register FICD (0xf8000e)                               */

//extern __attribute__((space(prog))) int _FICD;
//#define _FICD(x) __attribute__((section("__FICD.sec"),space(prog))) int _FICD = (x);

/*
** Only one invocation of FICD should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FICD.
** Multiple options may be combined, as shown:
**
** _FICD( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   JTAG Enable Bit:
**     JTAGEN_OFF           JTAG is disabled
**     JTAGEN_ON            JTAG is enabled
**
**   ICD communication channel select bits:
**     ICS_NONE             Reserved
**     ICS_PGD3              communicate on PGC3/EMUC3 and PGD3/EMUD3
**     ICS_PGD2             communicate on PGC2/EMUC2 and PGD2/EMUD2
**     ICS_PGD1             communicate on PGC1/EMUC1 and PGD1/EMUD1
**
*/

/*
#define JTAGEN_OFF           0xFFDF
#define JTAGEN_ON            0xFFFF

#define ICS_NONE             0xFFFC
#define ICS_PGD3             0xFFFD
#define ICS_PGD2             0xFFFE
#define ICS_PGD1             0xFFFF
*/

/* Register FUID0 (0xf80010)                               */

//extern __attribute__((space(prog))) int _FUID0;
//#define _FUID0(x) __attribute__((section("__FUID0.sec"),space(prog))) int _FUID0 = (x);

/*
** Only one invocation of FUID0 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID0.
** Multiple options may be combined, as shown:
**
** _FUID0( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
*/

/* Register FUID1 (0xf80012)                               */

//extern __attribute__((space(prog))) int _FUID1;
//#define _FUID1(x) __attribute__((section("__FUID1.sec"),space(prog))) int _FUID1 = (x);

/*
** Only one invocation of FUID1 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID1.
** Multiple options may be combined, as shown:
**
** _FUID1( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
*/

/* Register FUID2 (0xf80014)                               */

//extern __attribute__((space(prog))) int _FUID2;
//#define _FUID2(x) __attribute__((section("__FUID2.sec"),space(prog))) int _FUID2 = (x);

/*
** Only one invocation of FUID2 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID2.
** Multiple options may be combined, as shown:
**
** _FUID2( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
*/

/* Register FUID3 (0xf80016)                               */

//extern __attribute__((space(prog))) int _FUID3;
//#define _FUID3(x) __attribute__((section("__FUID3.sec"),space(prog))) int _FUID3 = (x);

/*
** Only one invocation of FUID3 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID3.
** Multiple options may be combined, as shown:
**
** _FUID3( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
*/

//dspic33fj32GP302/304
//dspic33fj64gp202/204
//dspic33fj64gp802/804
//dspic33fj128gp202/204
//dspic33fj128gp802/804
//dspic33fj32gp202/204, dspic33FJ16GP304
//dspic33fj12mc202/204
//dspic33fj32mc202/204
#elif 	defined(__dsPIC33FJ32GP302__) || defined(__dsPIC33FJ32GP304__) ||\
		defined(__dsPIC33FJ64GP202__) || defined(__dsPIC33FJ64GP204__) ||\
		defined(__dsPIC33FJ64GP802__) || defined(__dsPIC33FJ64GP804__) ||\
		defined(__dsPIC33FJ128GP202__) || defined(__dsPIC33FJ128GP204__) ||\
		defined(__dsPIC33FJ128GP802__) || defined(__dsPIC33FJ128GP804__) ||\
		defined(__dsPIC33FJ32GP202__) || defined(__dsPIC33FJ32GP204__) || defined(__dsPIC33FJ16GP304__)

_FBS(
//**   Boot Segment Data Ram:
//**     RBS_LARGE_RAM        Large Sized Boot Ram
//**     RBS_MEDIUM_RAM       Medium Sized Boot Ram
//**     RBS_SMALL_RAM        Small Sized Boot Ram
    RBS_NO_RAM &		//No Boot Ram
//**
//**   Boot Segment Program Memory:
//**     BSS__IGH_LARGE_BOOT_CODE High Security Lar Boot Flash
//**     BSS_LARGE_FLASH__IGH  High Security Lar Boot Flash
//**     BSS__IGH_MEDIUM_BOOT_CODE High Security Med Boot Flash
//**     BSS_MEDIUM_FLASH__IGH High Security Med Boot Flash
//**     BSS__IGH_SMALL_BOOT_CODE High Security Small Boot Flash
//**     BSS_SMALL_FLASH__IGH  High Security Small Boot Flash
//**     BSS_LARGE_FLASH_STD   Standard Security Lar Boot Flash
//**     BSS_STRD_LARGE_BOOT_CODE Standard Security Lar Boot Flash
//**     BSS_MEDIUM_FLASH_STD  Standard Security Med Boot Flash
//**     BSS_STRD_MEDIUM_BOOT_CODE Standard Security Med Boot Flash
//**     BSS_SMALL_FLASH_STD  Standard Security Small Boot Flash
//**     BSS_STRD_SMALL_BOOT_CODEStandard Security Small Boot Flash
    BSS_NO_BOOT_CODE &	//No Boot Segment Program Memory
//**     BSS_NO_FLASH         No Boot Segment Program Memory
//**
//**    Write Protect :
//**     BWRP_WRPROTECT_ON     Enabled
    BWRP_WRPROTECT_OFF    //Disabled
)

_FSS(
//**   Secure Segment Data Ram:
//**     RSS_LARGE_RAM         Large Sized Secure Ram
//**     RSS_MEDIUM_RAM        Medium Sized Secure Ram
//**     RSS_SMALL_RAM         Small Sized Secure Ram
    RSS_NO_RAM &		//No Secure Ram
//**
//**   Secure Segment Program Memory:
//**     SSS_LARGE_FLASH__IGH  High Security Lar Secure Flash
//**     SSS_MEDIUM_FLASH__IGH High Security Med Secure Flash
//**     SSS_SMALL_FLASH__IGH  High Security Small Secure Flash
//**     SSS_LARGE_FLASH_STD   Standard Security Large Secure Flash
//**     SSS_MEDIUM_FLASH_STD  Standard Security Med Secure Flash
//**     SSS_SMALL_FLASH_STD  Standard Security Small Secure Flash
    SSS_NO_FLASH &		//No Secure Segment
//**
//**    Write Protect :
//**     SWRP_WRPROTECT_ON     Enabled
    SWRP_WRPROTECT_OFF    //Disabled
)

_FGS(
//**   Code Protect:
//**     GSS__IGH              high security protect on
//**     GSS_STD               standard security code protect on
    GSS_OFF &			//code protect off
//**
//**   Code Protect:
//**     GCP_ON               Enabled
    GCP_OFF &			//Disabled
//**
//**   Write Protect:
//**     GWRP_ON              Enabled
    GWRP_OFF             //Disabled
)

_FOSCSEL(
//**   Oscillator Source Selection:
//**     FNOSC_FRC            Fast RC oscillator
//**     FNOSC_FRCPLL         Fast RC oscillator w/ divide and PLL
    FNOSC_PRI &			//Primary oscillator (XT, HS, EC)
//**     FNOSC_PRIPLL         Primary oscillator (XT, HS, EC) w/ PLL
//**     FNOSC_SOSC           Secondary oscillator
//**     FNOSC_LPRC           Low power RC oscillator
//**     FNOSC_FRCDIV16       Fast RC oscillator w/ divide by 16
//**     FNOSC_LPRCDIVN        Low power Fast RC oscillator w/divide by N
//**
//**   Two-speed Oscillator Startup :
    IESO_OFF             //Disabled
//**     IESO_ON              Enabled
)

_FOSC(
//**   Clock switching and clock monitor:
//**     FCKSM_CSECME         Both enabled
//**     FCKSM_CSECMD         Only clock switching enabled
    FCKSM_CSDCMD &		//Both disabled
//**
//**   Single configuration for remappable I/O:
    IOL1WAY_OFF &		//Disabled
//**     IOL1WAY_ON           Enabled
//**
//**   OSC2 Pin function:
//**     OSCIOFNC_ON          Digital I/O
    OSCIOFNC_OFF &		//OSC2 is clock O/P
//**
//**   Oscillator Selection:
//**     POSCMD_EC            External clock
//**     POSCMD_XT            XT oscillator
    POSCMD_HS            //HS oscillator
//**     POSCMD_NONE          Primary disabled
)

_FWDT(
//**   Watchdog Timer:
    FWDTEN_OFF &		//Disabled
//**     FWDTEN_ON            Enabled
//**
//**   Windowed WDT:
//**     WINDIS_ON            Enabled
    WINDIS_OFF &		//Disabled
//**
//**   Watchdog prescaler:
//**     WDTPRE_PR32          1:32
    WDTPRE_PR128 &		//1:128
//**
//**   Watchdog postscaler:
    WDTPOST_PS1          //1:1
//**     WDTPOST_PS2          1:2
//**     WDTPOST_PS4          1:4
//**     WDTPOST_PS8          1:8
//**     WDTPOST_PS16         1:16
//**     WDTPOST_PS32         1:32
//**     WDTPOST_PS64         1:64
//**     WDTPOST_PS128        1:128
//**     WDTPOST_PS256        1:256
//**     WDTPOST_PS512        1:512
//**     WDTPOST_PS1024       1:1,024
//**     WDTPOST_PS2048       1:2,048
//**     WDTPOST_PS4096       1:4,096
//**     WDTPOST_PS8192       1:8,192
//**     WDTPOST_PS16384      1:16,384
//**     WDTPOST_PS32768      1:32,768
)

_FPOR(
//**   Alternate I2C pins:
//**     ALTI2C_ON            I2C mapped to ASDA1/ASCL1
    ALTI2C_OFF &		//I2C mapped to SDA1/SCL1
//**
//**   Power-on Reset Value:
    FPWRT_PWR1           //Disabled
//**     FPWRT_PWR2           2ms
//**     FPWRT_PWR4           4ms
//**     FPWRT_PWR8           8ms
//**     FPWRT_PWR16          16ms
//**     FPWRT_PWR32          32ms
//**     FPWRT_PWR64          64ms
//**     FPWRT_PWR128         128ms
)

_FICD(
//**   JTAG Enable Bit:
    JTAGEN_OFF &		//JTAG is disabled
//**     JTAGEN_ON            JTAG is enabled
//**
//**   ICD communication channel select bits:
//**     ICS_NONE             Reserved
//**     ICS_PGD3              communicate on PGC3/EMUC3 and PGD3/EMUD3
//**     ICS_PGD2             communicate on PGC2/EMUC2 and PGD2/EMUD2
    ICS_PGD1             //communicate on PGC1/EMUC1 and PGD1/EMUD1
)

//user ids?
//_FUID0( 0xffff )
//_FUID1( 0xffff )
//_FUID2( 0xffff )
//_FUID3( 0xffff )

/* -------------------------------------------------------- */
/* Macros for setting device configuration registers        */
/* -------------------------------------------------------- */

/* Register FBS (0xf80000)                               */

//extern __attribute__((space(prog))) int _FBS;
//#define _FBS(x) __attribute__((section("__FBS.sec"),space(prog))) int _FBS = (x);

/*
** Only one invocation of FBS should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FBS.
** Multiple options may be combined, as shown:
**
** _FBS( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Boot Segment Data Ram:
**     RBS_LARGE_RAM        Large Sized Boot Ram
**     RBS_MEDIUM_RAM       Medium Sized Boot Ram
**     RBS_SMALL_RAM        Small Sized Boot Ram
**     RBS_NO_RAM           No Boot Ram
**
**   Boot Segment Program Memory:
**     BSS__IGH_LARGE_BOOT_CODE High Security Lar Boot Flash
**     BSS_LARGE_FLASH__IGH  High Security Lar Boot Flash
**     BSS__IGH_MEDIUM_BOOT_CODE High Security Med Boot Flash
**     BSS_MEDIUM_FLASH__IGH High Security Med Boot Flash
**     BSS__IGH_SMALL_BOOT_CODE High Security Small Boot Flash
**     BSS_SMALL_FLASH__IGH  High Security Small Boot Flash
**     BSS_LARGE_FLASH_STD   Standard Security Lar Boot Flash
**     BSS_STRD_LARGE_BOOT_CODE Standard Security Lar Boot Flash
**     BSS_MEDIUM_FLASH_STD  Standard Security Med Boot Flash
**     BSS_STRD_MEDIUM_BOOT_CODE Standard Security Med Boot Flash
**     BSS_SMALL_FLASH_STD  Standard Security Small Boot Flash
**     BSS_STRD_SMALL_BOOT_CODEStandard Security Small Boot Flash
**     BSS_NO_BOOT_CODE     No Boot Segment Program Memory
**     BSS_NO_FLASH         No Boot Segment Program Memory
**
**    Write Protect :
**     BWRP_WRPROTECT_ON     Enabled
**     BWRP_WRPROTECT_OFF    Disabled
**
*/
/*
#define RBS_LARGE_RAM        0xFF3F
#define RBS_MEDIUM_RAM       0xFF7F
#define RBS_SMALL_RAM        0xFFBF
#define RBS_NO_RAM           0xFFFF

#define BSS__IGH_LARGE_BOOT_CODE 0xFFF1
#define BSS_LARGE_FLASH__IGH 0xFFF1
#define BSS__IGH_MEDIUM_BOOT_CODE 0xFFF3
#define BSS_MEDIUM_FLASH__IGH 0xFFF3
#define BSS__IGH_SMALL_BOOT_CODE 0xFFF5
#define BSS_SMALL_FLASH__IGH 0xFFF5
#define BSS_LARGE_FLASH_STD  0xFFF9
#define BSS_STRD_LARGE_BOOT_CODE 0xFFF9
#define BSS_MEDIUM_FLASH_STD 0xFFFB
#define BSS_STRD_MEDIUM_BOOT_CODE 0xFFFB
#define BSS_SMALL_FLASH_STD  0xFFFD
#define BSS_STRD_SMALL_BOOT_CODE 0xFFFD
#define BSS_NO_BOOT_CODE     0xFFFF
#define BSS_NO_FLASH         0xFFFF

#define BWRP_WRPROTECT_ON    0xFFFE
#define BWRP_WRPROTECT_OFF   0xFFFF
*/
/* Register FSS (0xf80002)                               */

//extern __attribute__((space(prog))) int _FSS;
//#define _FSS(x) __attribute__((section("__FSS.sec"),space(prog))) int _FSS = (x);

/*
** Only one invocation of FSS should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FSS.
** Multiple options may be combined, as shown:
**
** _FSS( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Secure Segment Data Ram:
**     RSS_LARGE_RAM         Large Sized Secure Ram
**     RSS_MEDIUM_RAM        Medium Sized Secure Ram
**     RSS_SMALL_RAM         Small Sized Secure Ram
**     RSS_NO_RAM           No Secure Ram
**
**   Secure Segment Program Memory:
**     SSS_LARGE_FLASH__IGH  High Security Lar Secure Flash
**     SSS_MEDIUM_FLASH__IGH High Security Med Secure Flash
**     SSS_SMALL_FLASH__IGH  High Security Small Secure Flash
**     SSS_LARGE_FLASH_STD   Standard Security Large Secure Flash
**     SSS_MEDIUM_FLASH_STD  Standard Security Med Secure Flash
**     SSS_SMALL_FLASH_STD  Standard Security Small Secure Flash
**     SSS_NO_FLASH         No Secure Segment
**
**    Write Protect :
**     SWRP_WRPROTECT_ON     Enabled
**     SWRP_WRPROTECT_OFF    Disabled
**
*/
/*
#define RSS_LARGE_RAM        0xFF3F
#define RSS_MEDIUM_RAM       0xFF7F
#define RSS_SMALL_RAM        0xFFBF
#define RSS_NO_RAM           0xFFFF

#define SSS_LARGE_FLASH__IGH 0xFFF1
#define SSS_MEDIUM_FLASH__IGH 0xFFF3
#define SSS_SMALL_FLASH__IGH 0xFFF5
#define SSS_LARGE_FLASH_STD  0xFFF9
#define SSS_MEDIUM_FLASH_STD 0xFFFB
#define SSS_SMALL_FLASH_STD  0xFFFD
#define SSS_NO_FLASH         0xFFFF

#define SWRP_WRPROTECT_ON    0xFFFE
#define SWRP_WRPROTECT_OFF   0xFFFF
*/
/* Register FGS (0xf80004)                               */

//extern __attribute__((space(prog))) int _FGS;
//#define _FGS(x) __attribute__((section("__FGS.sec"),space(prog))) int _FGS = (x);

/*
** Only one invocation of FGS should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FGS.
** Multiple options may be combined, as shown:
**
** _FGS( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Code Protect:
**     GSS__IGH              high security protect on
**     GSS_STD               standard security code protect on
**     GSS_OFF              code protect off
**
**   Code Protect:
**     GCP_ON               Enabled
**     GCP_OFF              Disabled
**
**   Write Protect:
**     GWRP_ON              Enabled
**     GWRP_OFF             Disabled
**
*/
/*
#define GSS__IGH             0xFFFB
#define GSS_STD              0xFFFD
#define GSS_OFF              0xFFFF

#define GCP_ON               0xFFFD
#define GCP_OFF              0xFFFF

#define GWRP_ON              0xFFFE
#define GWRP_OFF             0xFFFF
*/
/* Register FOSCSEL (0xf80006)                               */

//extern __attribute__((space(prog))) int _FOSCSEL;
//#define _FOSCSEL(x) __attribute__((section("__FOSCSEL.sec"),space(prog))) int _FOSCSEL = (x);

/*
** Only one invocation of FOSCSEL should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FOSCSEL.
** Multiple options may be combined, as shown:
**
** _FOSCSEL( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Oscillator Source Selection:
**     FNOSC_FRC            Fast RC oscillator
**     FNOSC_FRCPLL         Fast RC oscillator w/ divide and PLL
**     FNOSC_PRI            Primary oscillator (XT, HS, EC)
**     FNOSC_PRIPLL         Primary oscillator (XT, HS, EC) w/ PLL
**     FNOSC_SOSC           Secondary oscillator
**     FNOSC_LPRC           Low power RC oscillator
**     FNOSC_FRCDIV16       Fast RC oscillator w/ divide by 16
**     FNOSC_LPRCDIVN        Low power Fast RC oscillator w/divide by N
**
**   Two-speed Oscillator Startup :
**     IESO_OFF             Disabled
**     IESO_ON              Enabled
**
*/
/*
#define FNOSC_FRC            0xFFF8
#define FNOSC_FRCPLL         0xFFF9
#define FNOSC_PRI            0xFFFA
#define FNOSC_PRIPLL         0xFFFB
#define FNOSC_SOSC           0xFFFC
#define FNOSC_LPRC           0xFFFD
#define FNOSC_FRCDIV16       0xFFFE
#define FNOSC_LPRCDIVN       0xFFFF

#define IESO_OFF             0xFF7F
#define IESO_ON              0xFFFF
*/
/* Register FOSC (0xf80008)                               */

//extern __attribute__((space(prog))) int _FOSC;
//#define _FOSC(x) __attribute__((section("__FOSC.sec"),space(prog))) int _FOSC = (x);

/*
** Only one invocation of FOSC should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FOSC.
** Multiple options may be combined, as shown:
**
** _FOSC( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Clock switching and clock monitor:
**     FCKSM_CSECME         Both enabled
**     FCKSM_CSECMD         Only clock switching enabled
**     FCKSM_CSDCMD         Both disabled
**
**   Single configuration for remappable I/O:
**     IOL1WAY_OFF          Disabled
**     IOL1WAY_ON           Enabled
**
**   OSC2 Pin function:
**     OSCIOFNC_ON          Digital I/O
**     OSCIOFNC_OFF         OSC2 is clock O/P
**
**   Oscillator Selection:
**     POSCMD_EC            External clock
**     POSCMD_XT            XT oscillator
**     POSCMD__S            HS oscillator
**     POSCMD_NONE          Primary disabled
**
*/
/*
#define FCKSM_CSECME         0xFF3F
#define FCKSM_CSECMD         0xFF7F
#define FCKSM_CSDCMD         0xFFBF

#define IOL1WAY_OFF          0xFFDF
#define IOL1WAY_ON           0xFFFF

#define OSCIOFNC_ON          0xFFFB
#define OSCIOFNC_OFF         0xFFFF

#define POSCMD_EC            0xFFFC
#define POSCMD_XT            0xFFFD
#define POSCMD__S            0xFFFE
#define POSCMD_NONE          0xFFFF
*/
/* Register FWDT (0xf8000a)                               */

//extern __attribute__((space(prog))) int _FWDT;
//#define _FWDT(x) __attribute__((section("__FWDT.sec"),space(prog))) int _FWDT = (x);

/*
** Only one invocation of FWDT should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FWDT.
** Multiple options may be combined, as shown:
**
** _FWDT( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Watchdog Timer:
**     FWDTEN_OFF           Disabled
**     FWDTEN_ON            Enabled
**
**   Windowed WDT:
**     WINDIS_ON            Enabled
**     WINDIS_OFF           Disabled
**
**   Watchdog prescaler:
**     WDTPRE_PR32          1:32
**     WDTPRE_PR128         1:128
**
**   Watchdog postscaler:
**     WDTPOST_PS1          1:1
**     WDTPOST_PS2          1:2
**     WDTPOST_PS4          1:4
**     WDTPOST_PS8          1:8
**     WDTPOST_PS16         1:16
**     WDTPOST_PS32         1:32
**     WDTPOST_PS64         1:64
**     WDTPOST_PS128        1:128
**     WDTPOST_PS256        1:256
**     WDTPOST_PS512        1:512
**     WDTPOST_PS1024       1:1,024
**     WDTPOST_PS2048       1:2,048
**     WDTPOST_PS4096       1:4,096
**     WDTPOST_PS8192       1:8,192
**     WDTPOST_PS16384      1:16,384
**     WDTPOST_PS32768      1:32,768
**
*/
/*
#define FWDTEN_OFF           0xFF7F
#define FWDTEN_ON            0xFFFF

#define WINDIS_ON            0xFFBF
#define WINDIS_OFF           0xFFFF

#define WDTPRE_PR32          0xFFEF
#define WDTPRE_PR128         0xFFFF

#define WDTPOST_PS1          0xFFF0
#define WDTPOST_PS2          0xFFF1
#define WDTPOST_PS4          0xFFF2
#define WDTPOST_PS8          0xFFF3
#define WDTPOST_PS16         0xFFF4
#define WDTPOST_PS32         0xFFF5
#define WDTPOST_PS64         0xFFF6
#define WDTPOST_PS128        0xFFF7
#define WDTPOST_PS256        0xFFF8
#define WDTPOST_PS512        0xFFF9
#define WDTPOST_PS1024       0xFFFA
#define WDTPOST_PS2048       0xFFFB
#define WDTPOST_PS4096       0xFFFC
#define WDTPOST_PS8192       0xFFFD
#define WDTPOST_PS16384      0xFFFE
#define WDTPOST_PS32768      0xFFFF
*/
/* Register FPOR (0xf8000c)                               */

//extern __attribute__((space(prog))) int _FPOR;
//#define _FPOR(x) __attribute__((section("__FPOR.sec"),space(prog))) int _FPOR = (x);

/*
** Only one invocation of FPOR should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FPOR.
** Multiple options may be combined, as shown:
**
** _FPOR( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Alternate I2C pins:
**     ALTI2C_ON            I2C mapped to ASDA1/ASCL1
**     ALTI2C_OFF           I2C mapped to SDA1/SCL1
**
**   Power-on Reset Value:
**     FPWRT_PWR1           Disabled
**     FPWRT_PWR2           2ms
**     FPWRT_PWR4           4ms
**     FPWRT_PWR8           8ms
**     FPWRT_PWR16          16ms
**     FPWRT_PWR32          32ms
**     FPWRT_PWR64          64ms
**     FPWRT_PWR128         128ms
**
*/
/*
#define ALTI2C_ON            0xFFEF
#define ALTI2C_OFF           0xFFFF

#define FPWRT_PWR1           0xFFF8
#define FPWRT_PWR2           0xFFF9
#define FPWRT_PWR4           0xFFFA
#define FPWRT_PWR8           0xFFFB
#define FPWRT_PWR16          0xFFFC
#define FPWRT_PWR32          0xFFFD
#define FPWRT_PWR64          0xFFFE
#define FPWRT_PWR128         0xFFFF
*/
/* Register FICD (0xf8000e)                               */

//extern __attribute__((space(prog))) int _FICD;
//#define _FICD(x) __attribute__((section("__FICD.sec"),space(prog))) int _FICD = (x);

/*
** Only one invocation of FICD should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FICD.
** Multiple options may be combined, as shown:
**
** _FICD( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   JTAG Enable Bit:
**     JTAGEN_OFF           JTAG is disabled
**     JTAGEN_ON            JTAG is enabled
**
**   ICD communication channel select bits:
**     ICS_NONE             Reserved
**     ICS_PGD3              communicate on PGC3/EMUC3 and PGD3/EMUD3
**     ICS_PGD2             communicate on PGC2/EMUC2 and PGD2/EMUD2
**     ICS_PGD1             communicate on PGC1/EMUC1 and PGD1/EMUD1
**
*/
/*
#define JTAGEN_OFF           0xFFDF
#define JTAGEN_ON            0xFFFF

#define ICS_NONE             0xFFFC
#define ICS_PGD3             0xFFFD
#define ICS_PGD2             0xFFFE
#define ICS_PGD1             0xFFFF
*/
/* Register FUID0 (0xf80010)                               */

//extern __attribute__((space(prog))) int _FUID0;
//#define _FUID0(x) __attribute__((section("__FUID0.sec"),space(prog))) int _FUID0 = (x);

/*
** Only one invocation of FUID0 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID0.
** Multiple options may be combined, as shown:
**
** _FUID0( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
*/

/* Register FUID1 (0xf80012)                               */

//extern __attribute__((space(prog))) int _FUID1;
//#define _FUID1(x) __attribute__((section("__FUID1.sec"),space(prog))) int _FUID1 = (x);

/*
** Only one invocation of FUID1 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID1.
** Multiple options may be combined, as shown:
**
** _FUID1( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
*/

/* Register FUID2 (0xf80014)                               */

//extern __attribute__((space(prog))) int _FUID2;
//#define _FUID2(x) __attribute__((section("__FUID2.sec"),space(prog))) int _FUID2 = (x);

/*
** Only one invocation of FUID2 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID2.
** Multiple options may be combined, as shown:
**
** _FUID2( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
*/

/* Register FUID3 (0xf80016)                               */

//extern __attribute__((space(prog))) int _FUID3;
//#define _FUID3(x) __attribute__((section("__FUID3.sec"),space(prog))) int _FUID3 = (x);

/*
** Only one invocation of FUID3 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID3.
** Multiple options may be combined, as shown:
**
** _FUID3( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
*/

//dspic33fj32mc302/304
//dspic33fj64mc202/204
//dspic33fj65mc802/804
//dspic33fj128mc202/204
//dspic33fj128mc802/804

#elif 	defined(__dsPIC33FJ32MC302__) || defined(__dsPIC33FJ32MC304__) ||\
		defined(__dsPIC33FJ64MC202__) || defined(__dsPIC33FJ64MC204__) || defined(__dsPIC33FJ64MC802__) || defined(__dsPIC33FJ64MC804__) ||\
		defined(__dsPIC33FJ128MC202__) || defined(__dsPIC33FJ128MC204__) || defined(__dsPIC33FJ128MC802__) || defined(__dsPIC33FJ128MC804__)

#warning need to put config bits here
/* -------------------------------------------------------- */
/* Macros for setting device configuration registers        */
/* -------------------------------------------------------- */

/* Register FBS (0xf80000)                               */

//extern __attribute__((space(prog))) int _FBS;
//#define _FBS(x) __attribute__((section("__FBS.sec"),space(prog))) int _FBS = (x);
_FBS(BSS_NO_BOOT_CODE & BWRP_WRPROTECT_OFF)

/*
** Only one invocation of FBS should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FBS.
** Multiple options may be combined, as shown:
**
** _FBS( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Boot Segment Program Memory:
**     BSS_HIGH_LARGE_BOOT_CODE High Security Lar Boot Flash
**     BSS_LARGE_FLASH_HIGH  High Security Lar Boot Flash
**     BSS_HIGH_MEDIUM_BOOT_CODE High Security Med Boot Flash
**     BSS_MEDIUM_FLASH_HIGH High Security Med Boot Flash
**     BSS_HIGH_SMALL_BOOT_CODE High Security Small Boot Flash
**     BSS_SMALL_FLASH_HIGH  High Security Small Boot Flash
**     BSS_LARGE_FLASH_STD   Standard Security Lar Boot Flash
**     BSS_STRD_LARGE_BOOT_CODE Standard Security Lar Boot Flash
**     BSS_MEDIUM_FLASH_STD  Standard Security Med Boot Flash
**     BSS_STRD_MEDIUM_BOOT_CODE Standard Security Med Boot Flash
**     BSS_SMALL_FLASH_STD  Standard Security Small Boot Flash
**     BSS_STRD_SMALL_BOOT_CODEStandard Security Small Boot Flash
**     BSS_NO_BOOT_CODE     No Boot Segment Program Memory
**     BSS_NO_FLASH         No Boot Segment Program Memory
**
**    Write Protect :
**     BWRP_WRPROTECT_ON     Enabled
**     BWRP_WRPROTECT_OFF    Disabled
**
*/

/* Register FGS (0xf80004)                               */

//extern __attribute__((space(prog))) int _FGS;
//#define _FGS(x) __attribute__((section("__FGS.sec"),space(prog))) int _FGS = (x);

_FGS(GSS_OFF & GCP_OFF & GWRP_OFF)

/*
** Only one invocation of FGS should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FGS.
** Multiple options may be combined, as shown:
**
** _FGS( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Code Protect:
**     GSS_HIGH              high security protect on
**     GSS_STD               standard security code protect on
**     GSS_OFF              code protect off
**
**   Code Protect:
**     GCP_ON               Enabled
**     GCP_OFF              Disabled
**
**   Write Protect:
**     GWRP_ON              Enabled
**     GWRP_OFF             Disabled
**
*/

/* Register FOSCSEL (0xf80006)                               */

//extern __attribute__((space(prog))) int _FOSCSEL;
//#define _FOSCSEL(x) __attribute__((section("__FOSCSEL.sec"),space(prog))) int _FOSCSEL = (x);
_FOSCSEL(FNOSC_FRC & IESO_OFF)
/*
** Only one invocation of FOSCSEL should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FOSCSEL.
** Multiple options may be combined, as shown:
**
** _FOSCSEL( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Oscillator Source Selection:
**     FNOSC_FRC            Fast RC oscillator
**     FNOSC_FRCPLL         Fast RC oscillator w/ divide and PLL
**     FNOSC_PRI            Primary oscillator (XT, HS, EC)
**     FNOSC_PRIPLL         Primary oscillator (XT, HS, EC) w/ PLL
**     FNOSC_SOSC           Secondary oscillator
**     FNOSC_LPRC           Low power RC oscillator
**     FNOSC_FRCDIV16       Fast RC oscillator w/ divide by 16
**     FNOSC_LPRCDIVN        Low power Fast RC oscillator w/divide by N
**
**   Two-speed Oscillator Startup :
**     IESO_OFF             Disabled
**     IESO_ON              Enabled
**
*/

/* Register FOSC (0xf80008)                               */

//extern __attribute__((space(prog))) int _FOSC;
//#define _FOSC(x) __attribute__((section("__FOSC.sec"),space(prog))) int _FOSC = (x);
_FOSC(FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMD_NONE)
/*
** Only one invocation of FOSC should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FOSC.
** Multiple options may be combined, as shown:
**
** _FOSC( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Clock switching and clock monitor:
**     FCKSM_CSECME         Both enabled
**     FCKSM_CSECMD         Only clock switching enabled
**     FCKSM_CSDCMD         Both disabled
**
**   Single configuration for remappable I/O:
**     IOL1WAY_OFF          Disabled
**     IOL1WAY_ON           Enabled
**
**   OSC2 Pin function:
**     OSCIOFNC_ON          Digital I/O
**     OSCIOFNC_OFF         OSC2 is clock O/P
**
**   Oscillator Selection:
**     POSCMD_EC            External clock
**     POSCMD_XT            XT oscillator
**     POSCMD_HS            HS oscillator
**     POSCMD_NONE          Primary disabled
**
*/

/* Register FWDT (0xf8000a)                               */

//extern __attribute__((space(prog))) int _FWDT;
//#define _FWDT(x) __attribute__((section("__FWDT.sec"),space(prog))) int _FWDT = (x);
_FWDT(FWDTEN_OFF & WINDIS_OFF & WDTPRE_PR128 & WDTPOST_PS32768)

/*
** Only one invocation of FWDT should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FWDT.
** Multiple options may be combined, as shown:
**
** _FWDT( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Watchdog Timer:
**     FWDTEN_OFF           Disabled
**     FWDTEN_ON            Enabled
**
**   Windowed WDT:
**     WINDIS_ON            Enabled
**     WINDIS_OFF           Disabled
**
**   Watchdog prescaler:
**     WDTPRE_PR32          1:32
**     WDTPRE_PR128         1:128
**
**   Watchdog postscaler:
**     WDTPOST_PS1          1:1
**     WDTPOST_PS2          1:2
**     WDTPOST_PS4          1:4
**     WDTPOST_PS8          1:8
**     WDTPOST_PS16         1:16
**     WDTPOST_PS32         1:32
**     WDTPOST_PS64         1:64
**     WDTPOST_PS128        1:128
**     WDTPOST_PS256        1:256
**     WDTPOST_PS512        1:512
**     WDTPOST_PS1024       1:1,024
**     WDTPOST_PS2048       1:2,048
**     WDTPOST_PS4096       1:4,096
**     WDTPOST_PS8192       1:8,192
**     WDTPOST_PS16384      1:16,384
**     WDTPOST_PS32768      1:32,768
**
*/

/* Register FPOR (0xf8000c)                               */

//extern __attribute__((space(prog))) int _FPOR;
//#define _FPOR(x) __attribute__((section("__FPOR.sec"),space(prog))) int _FPOR = (x);

_FPOR(PWMPIN_OFF & HPOL_OFF & LPOL_OFF & ALTI2C_OFF & FPWRT_PWR128)

/*
** Only one invocation of FPOR should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FPOR.
** Multiple options may be combined, as shown:
**
** _FPOR( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   PWM Mode Select:
**     PWMPIN_OFF           PWM Module
**     PWMPIN_ON            Port Register
**
**   PWM High Side Polarity:
**     HPOL_OFF             Active Low
**     HPOL_ON              Active High
**
**   PWM Low Side Polarity:
**     LPOL_OFF             Active Low
**     LPOL_ON              Active High
**
**   Alternate I2C pins:
**     ALTI2C_ON            I2C mapped to ASDA1/ASCL1
**     ALTI2C_OFF           I2C mapped to SDA1/SCL1
**
**   Power-on Reset Value:
**     FPWRT_PWR1           Disabled
**     FPWRT_PWR2           2ms
**     FPWRT_PWR4           4ms
**     FPWRT_PWR8           8ms
**     FPWRT_PWR16          16ms
**     FPWRT_PWR32          32ms
**     FPWRT_PWR64          64ms
**     FPWRT_PWR128         128ms
**
*/

/* Register FICD (0xf8000e)                               */

//extern __attribute__((space(prog))) int _FICD;
//#define _FICD(x) __attribute__((section("__FICD.sec"),space(prog))) int _FICD = (x);

_FICD(JTAGEN_OFF & ICS_PGD1)
/*
** Only one invocation of FICD should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FICD.
** Multiple options may be combined, as shown:
**
** _FICD( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   JTAG Enable Bit:
**     JTAGEN_OFF           JTAG is disabled
**     JTAGEN_ON            JTAG is enabled
**
**   ICD communication channel select bits:
**     ICS_NONE             Reserved
**     ICS_PGD3              communicate on PGC3/EMUC3 and PGD3/EMUD3
**     ICS_PGD2             communicate on PGC2/EMUC2 and PGD2/EMUD2
**     ICS_PGD1             communicate on PGC1/EMUC1 and PGD1/EMUD1
**
*/

//KL-user defined id
//_FUID0(0xffff)
//_FUID1(0xffff)
//_FUID2(0xffff)
//_FUID3(0xffff)

/* Register FUID0 (0xf80010)                               */

//extern __attribute__((space(prog))) int _FUID0;
//#define _FUID0(x) __attribute__((section("__FUID0.sec"),space(prog))) int _FUID0 = (x);

/*
** Only one invocation of FUID0 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID0.
** Multiple options may be combined, as shown:
**
** _FUID0( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
*/

/* Register FUID1 (0xf80012)                               */

//extern __attribute__((space(prog))) int _FUID1;
//#define _FUID1(x) __attribute__((section("__FUID1.sec"),space(prog))) int _FUID1 = (x);

/*
** Only one invocation of FUID1 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID1.
** Multiple options may be combined, as shown:
**
** _FUID1( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
*/

/* Register FUID2 (0xf80014)                               */

//extern __attribute__((space(prog))) int _FUID2;
//#define _FUID2(x) __attribute__((section("__FUID2.sec"),space(prog))) int _FUID2 = (x);

/*
** Only one invocation of FUID2 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID2.
** Multiple options may be combined, as shown:
**
** _FUID2( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
*/

/* Register FUID3 (0xf80016)                               */

//extern __attribute__((space(prog))) int _FUID3;
//#define _FUID3(x) __attribute__((section("__FUID3.sec"),space(prog))) int _FUID3 = (x);

/*
** Only one invocation of FUID3 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID3.
** Multiple options may be combined, as shown:
**
** _FUID3( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
*/

//dsPIC33FJ06GS101, dsPIC33FJ06GS102, dsPIC33FJ06GS202,
//dsPIC33FJ16GS402, dsPIC33FJ16GS404, dsPIC33FJ16GS502, dsPIC33FJ16GS504
#elif	defined(__dsPIC33FJ06GS101__) || defined(__dsPIC33FJ06GS102__) || defined(__dsPIC33FJ06GS202__) ||\
		defined(__dsPIC33FJ16GS402__) || defined(__dsPIC33FJ16GS404__) || defined(__dsPIC33FJ16GS502__) || defined(__dsPIC33FJ16GS504__)

/* -------------------------------------------------------- */
/* Macros for setting device configuration registers        */
/* -------------------------------------------------------- */

/* Register FBS (0xf80000)                               */

//extern __attribute__((space(prog))) int _FBS;
//#define _FBS(x) __attribute__((section("__FBS.sec"),space(prog))) int _FBS = (x);
_FBS(BWRP_WRPROTECT_OFF & BSS_NO_BOOT_CODE)
/*
** Only one invocation of FBS should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FBS.
** Multiple options may be combined, as shown:
**
** _FBS( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Boot Segment Write Protect:
**     BWRP_WRPROTECT_ON    Boot Segment is write protected
**     BWRP_WRPROTECT_OFF   Boot Segment may be written
**
**   Boot Segment Program Flash Code Protection:
**     BSS_HIGH_LARGE_BOOT_CODEHigh Security, Large-sized Boot Flash
**     BSS_LARGE_FLASH_HIGH High Security, Large-sized Boot Flash
**     BSS_HIGH_MEDIUM_BOOT_CODEHigh Security, Medium-sized Boot Flash
**     BSS_MEDIUM_FLASH_HIGHHigh Security, Medium-sized Boot Flash
**     BSS_HIGH_SMALL_BOOT_CODEHigh Security, Small-sized Boot Flash
**     BSS_SMALL_FLASH_HIGH High Security, Small-sized Boot Flash
**     BSS_LARGE_FLASH_STD  Standard Security, Large-sized Boot Flash
**     BSS_STRD_LARGE_BOOT_CODEStandard Security, Large-sized Boot Flash
**     BSS_MEDIUM_FLASH_STD Standard Security, Medium-sized Boot Flash
**     BSS_STRD_MEDIUM_BOOT_CODEStandard Security, Medium-sized Boot Flash
**     BSS_SMALL_FLASH_STD  Standard Security, Small-sized Boot Flash
**     BSS_STRD_SMALL_BOOT_CODEStandard Security, Small-sized Boot Flash
**     BSS_NO_BOOT_CODE     No Boot Segment
**     BSS_NO_FLASH         No Boot Segment Program Memory
**
*/

/* Register FGS (0xf80004)                               */

//extern __attribute__((space(prog))) int _FGS;
//#define _FGS(x) __attribute__((section("__FGS.sec"),space(prog))) int _FGS = (x);
_FGS(GWRP_OFF & GSS_OFF)
/*
** Only one invocation of FGS should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FGS.
** Multiple options may be combined, as shown:
**
** _FGS( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   General Code Segment Write Protect:
**     GWRP_ON              General Segment is write protected
**     GWRP_OFF             General Segment may be written
**
**   General Segment Code Protection:
**     GSS_HIGH             High Security Code Protection Enabled
**     GSS_STD              Standard Security Code Protection Enabled
**     GSS_OFF              User program memory is not code-protected
**
*/

/* Register FOSCSEL (0xf80006)                               */

//extern __attribute__((space(prog))) int _FOSCSEL;
//#define _FOSCSEL(x) __attribute__((section("__FOSCSEL.sec"),space(prog))) int _FOSCSEL = (x);
_FOSCSEL(FNOSC_FRC & IESO_OFF)
/*
** Only one invocation of FOSCSEL should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FOSCSEL.
** Multiple options may be combined, as shown:
**
** _FOSCSEL( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Oscillator Source Selection:
**     FNOSC_FRC            Internal Fast RC (FRC) oscillator
**     FNOSC_FRCPLL         Internal Fast RC (FRC) with PLL
**     FNOSC_PRI            Primary Oscillator (XT, HS, EC)
**     FNOSC_PRIPLL         Primary Oscillator (XT, HS, EC) with PLL
**     FNOSC_SOSC           Secondary Oscillator (SOSC)
**     FNOSC_LPRC           Low Power RC oscillator (LPRC)
**     FNOSC_FRCDIV16       Internal Fast RC (FRC) with divide by 16
**     FNOSC_FRCDIVN        Internal Fast RC (FRC) oscillator with postscaler
**
**   Internal External Switch Over Mode:
**     IESO_OFF             Start up device with user-selected oscillator source
**     IESO_ON              Start up device with FRC, then automatically switch to user-selected oscillator source
**
*/

/* Register FOSC (0xf80008)                               */

//extern __attribute__((space(prog))) int _FOSC;
//#define _FOSC(x) __attribute__((section("__FOSC.sec"),space(prog))) int _FOSC = (x);
_FOSC(POSCMD_NONE & OSCIOFNC_OFF & IOL1WAY_OFF & FCKSM_CSDCMD)
/*
** Only one invocation of FOSC should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FOSC.
** Multiple options may be combined, as shown:
**
** _FOSC( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Primary Oscillator Source:
**     POSCMD_EC            EC (External Clock) Mode
**     POSCMD_XT            XT Crystal Oscillator Mode
**     POSCMD_HS            HS Crystal Oscillator Mode
**     POSCMD_NONE          Primary oscillator disabled
**
**   OSC2 Pin Function:
**     OSCIOFNC_ON          OSC2 is general purpose digital I/O pin
**     OSCIOFNC_OFF         OSC2 is clock output
**
**   Peripheral Pin Select Configuration:
**     IOL1WAY_OFF          Allow multiple reconfigurations
**     IOL1WAY_ON           Allow only one reconfiguration
**
**   Clock Switching and Monitor:
**     FCKSM_CSECME         Clock switching and Fail-Safe Clock Monitor are enabled
**     FCKSM_CSECMD         Clock switching is enabled, Fail-Safe Clock Monitor is Disabled
**     FCKSM_CSDCMD         Clock switching and Fail-Safe Clock Monitor are disabled, Mon Disabled
**
*/

/* Register FWDT (0xf8000a)                               */

//extern __attribute__((space(prog))) int _FWDT;
//#define _FWDT(x) __attribute__((section("__FWDT.sec"),space(prog))) int _FWDT = (x);
_FWDT(WDTPOST_PS32768 & WDTPRE_PR128 & WINDIS_OFF & FWDTEN_OFF)
/*
** Only one invocation of FWDT should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FWDT.
** Multiple options may be combined, as shown:
**
** _FWDT( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Watchdog Timer Postscaler:
**     WDTPOST_PS1          1:1
**     WDTPOST_PS2          1:2
**     WDTPOST_PS4          1:4
**     WDTPOST_PS8          1:8
**     WDTPOST_PS16         1:16
**     WDTPOST_PS32         1:32
**     WDTPOST_PS64         1:64
**     WDTPOST_PS128        1:128
**     WDTPOST_PS256        1:256
**     WDTPOST_PS512        1:512
**     WDTPOST_PS1024       1:1,024
**     WDTPOST_PS2048       1:2,048
**     WDTPOST_PS4096       1:4,096
**     WDTPOST_PS8192       1:8,192
**     WDTPOST_PS16384      1:16,384
**     WDTPOST_PS32768      1:32,768
**
**   WDT Prescaler:
**     WDTPRE_PR32          1:32
**     WDTPRE_PR128         1:128
**
**   Watchdog Timer Window:
**     WINDIS_ON            Watchdog Timer in Window mode
**     WINDIS_OFF           Watchdog Timer in Non-Window mode
**
**   Watchdog Timer Enable:
**     FWDTEN_OFF           Watchdog timer enabled/disabled by user software
**     FWDTEN_ON            Watchdog timer always enabled
**
*/

/* Register FPOR (0xf8000c)                               */

//extern __attribute__((space(prog))) int _FPOR;
//#define _FPOR(x) __attribute__((section("__FPOR.sec"),space(prog))) int _FPOR = (x);
_FPOR(FPWRT_PWR1)
/*
** Only one invocation of FPOR should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FPOR.
** Multiple options may be combined, as shown:
**
** _FPOR( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   POR Timer Value:
**     FPWRT_PWR1           Disabled
**     FPWRT_PWR2           2ms
**     FPWRT_PWR4           4ms
**     FPWRT_PWR8           8ms
**     FPWRT_PWR16          16ms
**     FPWRT_PWR32          32ms
**     FPWRT_PWR64          64ms
**     FPWRT_PWR128         128ms
**
*/

/* Register FICD (0xf8000e)                               */

//extern __attribute__((space(prog))) int _FICD;
//#define _FICD(x) __attribute__((section("__FICD.sec"),space(prog))) int _FICD = (x);
_FICD(JTAGEN_OFF & ICS_PGD1)
/*
** Only one invocation of FICD should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FICD.
** Multiple options may be combined, as shown:
**
** _FICD( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   Comm Channel Select:
**     ICS_NONE             Reserved, do not use
**     ICS_PGD3             Communicate on PGC3/EMUC3 and PGD3/EMUD3
**     ICS_PGD2             Communicate on PGC2/EMUC2 and PGD2/EMUD2
**     ICS_PGD1             Communicate on PGC1/EMUC1 and PGD1/EMUD1
**
**   JTAG Port Enable:
**     JTAGEN_OFF           JTAG is disabled
**     JTAGEN_ON            JTAG is enabled
**
*/

//KL-user defined id
//_FUID0(0xffff)
//_FUID1(0xffff)

/* Register FUID0 (0xf80010)                               */

//extern __attribute__((space(prog))) int _FUID0;
//#define _FUID0(x) __attribute__((section("__FUID0.sec"),space(prog))) int _FUID0 = (x);

/*
** Only one invocation of FUID0 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID0.
** Multiple options may be combined, as shown:
**
** _FUID0( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   :
**
*/


/* Register FUID1 (0xf80012)                               */

//extern __attribute__((space(prog))) int _FUID1;
//#define _FUID1(x) __attribute__((section("__FUID1.sec"),space(prog))) int _FUID1 = (x);

/*
** Only one invocation of FUID1 should appear in a project,
** at the top of a C source file (outside of any function).
**
** The following constants can be used to set FUID1.
** Multiple options may be combined, as shown:
**
** _FUID1( OPT1_ON & OPT2_OFF & OPT3_PLL )
**
**   :
**
*/

//dsPIC30F4011, dsPIC30F4012
#elif defined(__dsPIC30F4011__) || defined(__dsPIC30F4012__)
/* -------------------------------------------- */
/* Macros for Device Configuration Registers    */
/* -------------------------------------------- */

/* FOSC */
_FOSC(FRC & CSW_FSCM_OFF)

//#define _FOSC(x) __attribute__((section("__FOSC.sec,code"))) int _FOSC = (x);
/*
#define CSW_FSCM_OFF    0xFFFF
#define CSW_ON_FSCM_OFF 0x7FFF
#define CSW_FSCM_ON     0x3FFF
#define EC              0xFFFB
#define ECIO            0xFFFC
#define EC_PLL4         0xFFFD
#define EC_PLL8         0xFFFE
#define EC_PLL16        0xFFFF
#define ERC             0xFFF9
#define ERCIO           0xFFF8
#define XT              0xFFF4
#define XT_PLL4         0xFFF5
#define XT_PLL8         0xFFF6
#define XT_PLL16        0xFFF7
#define XTL             0xFFF0
#define FRC_PLL4        0xFFF1
#define FRC_PLL8        0xFFFA
#define FRC_PLL16       0xFFF3
#define HS              0xFFF2
#define LP              0xFCFF
#define FRC             0xFDFF
#define LPRC            0xFEFF
*/

/* FWDT */
_FWDT(WDT_OFF & WDTPSA_512)
//#define _FWDT(x) __attribute__((section("__FWDT.sec,code"))) int _FWDT = (x);
/*
#define WDT_ON         0xFFFF
#define WDT_OFF        0x7FFF
#define WDTPSA_1       0xFFCF
#define WDTPSA_8       0xFFDF
#define WDTPSA_64      0xFFEF
#define WDTPSA_512     0xFFFF
#define WDTPSB_1       0xFFF0
#define WDTPSB_2       0xFFF1
#define WDTPSB_3       0xFFF2
#define WDTPSB_4       0xFFF3
#define WDTPSB_5       0xFFF4
#define WDTPSB_6       0xFFF5
#define WDTPSB_7       0xFFF6
#define WDTPSB_8       0xFFF7
#define WDTPSB_9       0xFFF8
#define WDTPSB_10      0xFFF9
#define WDTPSB_11      0xFFFA
#define WDTPSB_12      0xFFFB
#define WDTPSB_13      0xFFFC
#define WDTPSB_14      0xFFFD
#define WDTPSB_15      0xFFFE
#define WDTPSB_16      0xFFFF
*/

/* FBORPOR */
_FBORPOR(MCLR_DIS & RST_IOPIN & PWMxH_ACT_HI & PWMxL_ACT_LO & PBOR_OFF & BORV_20 & PWRT_OFF)
//#define _FBORPOR(x) __attribute__((section("__FBORPOR.sec,code"))) int _FBORPOR = (x);
/*
#define MCLR_EN        0xFFFF
#define MCLR_DIS       0x7FFF
#define RST_IOPIN      0xFFFF
#define RST_PWMPIN     0xFBFF
#define PWMxH_ACT_HI   0xFFFF
#define PWMxH_ACT_LO   0xFDFF
#define PWMxL_ACT_HI   0xFFFF
#define PWMxL_ACT_LO   0xFEFF
#define PBOR_ON        0xFFFF
#define PBOR_OFF       0xFF7F
#define BORV_20        0xFFFF
#define BORV_27        0xFFEF
#define BORV_42        0xFFDF
#define BORV_45        0xFFCF
#define PWRT_OFF       0xFFFC
#define PWRT_4         0xFFFD
#define PWRT_16        0xFFFE
#define PWRT_64        0xFFFF
*/

/* FGS */
_FGS(CODE_PROT_OFF & GWRP_OFF)
//#define _FGS(x) __attribute__((section("__FGS.sec,code"))) int _FGS = (x);
/*
#define CODE_PROT_OFF  0xFFFF
#define CODE_PROT_ON   0xFFFD
#define GWRP_OFF  0xFFFF
#define GWRP_ON   0xFFFE
*/
/* FICD */
_FICD(ICS_PGD)
//#define _FICD(x) __attribute__((section("__FICD.sec, code"))) int _FICD = (x);
/*
#define ICS_PGD3         0xFFFC
#define ICS_PGD2         0xFFFD
#define ICS_PGD1         0xFFFE
#define ICS_PGD          0xFFFF
*/

//user id settings
//_FUID0(0xffff)
//_FUID1(0xffff)
//_FUID2(0xffff)
//_FUID3(0xffff)
//#define _FUID0(x) __attribute__((section("__FUID0.sec,code"))) int _FUID0 = (x);
//#define _FUID1(x) __attribute__((section("__FUID1.sec,code"))) int _FUID1 = (x);
//#define _FUID2(x) __attribute__((section("__FUID2.sec,code"))) int _FUID2 = (x);
//#define _FUID3(x) __attribute__((section("__FUID3.sec,code"))) int _FUID3 = (x);

#else
//no header file found
#warning no device header file specified
#endif

#endif	//config__
