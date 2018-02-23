#ifndef __CONFIG_H
#define __CONFIG_H

#include "gpio.h"			//so device header file is included
//#include <p24fxxxx.h>			//we use 24f
//#include <p33fxxxx.h>			//we use dspic33

//configuration words for pic24f
//PIC24FJ64GA102, PIC24FJ64GA104, PIC24FJ32GA102, PIC24FJ32GA104
//PIC24FJ64GA002, PIC24FJ64GA004
//PIC24FJ48GA002, PIC24FJ48GA004
//PIC24FJ32GA002, PIC24FJ32GA004
//PIC24FJ16GA002, PIC24FJ16GA004
//PIC24FJ64GB002, PIC24FJ64GB004
//PIC24FJ48GB002, PIC24FJ48GB004
//PIC24FJ32GB002, PIC24FJ32GB004
//dsPIC33FJ32GP202, dspic33fj32gp204
//dspic33fj16gp304
//dspic33fj128gp202, dspic33fj128gp204, dspic33fj128gp802, dspic33fj128gp804
//dspic33fj64gp202,  dspic33fj64gp204,  dspic33fj64gp802,  dspic33fj64gp804
//dspic33fj32gp302,  dspic33fj32gp304
//pic24fj16mc101, pic24fj16mc102
//pic24fj32mc101, pic24fj32mc102, pic24fj32mc104
//DSPIC33FJ128MC202, DSPIC33FJ128MC204, DSPIC33FJ128MC802, DSPIC33FJ128MC804, 
//DSPIC33FJ64MC202, DSPIC33FJ64MC204, DSPIC33FJ64MC802, DSPIC33FJ64MC804, 
//DSPIC33FJ32MC302, DSPIC33FJ32MC304
//PIC24F/FV08/16KMx02/x04 - microstick I/II

#if 	defined(__PIC24FJ64GA102__) | defined (__PIC24FJ64GA104__) | \
		defined(__PIC24FJ32GA102__) | defined (__PIC24FJ32GA104__)

//config fues settings for 24fj64ga102
///config fues settings
//CONFIG1
#pragma config JTAGEN = OFF
#pragma config GCP = OFF
#pragma config GWRP = OFF
#pragma config ICS = PGx2
#pragma config FWDTEN = OFF
#pragma config WINDIS = OFF
#pragma config FWPSA = PR128
#pragma config WDTPS = PS32768

//CONFIG2
#pragma config IESO = OFF
#pragma config FNOSC = PRI
#pragma config FCKSM = CSDCMD
#pragma config OSCIOFNC = OFF
#pragma config IOL1WAY = OFF
#pragma config POSCMOD = HS
#pragma config I2C1SEL = PRI

//CONFIG3
#pragma config WPFP = WPFP0
#pragma config SOSCSEL = IO
#pragma config WUTSEL = LEG
#pragma config WPDIS = WPDIS
#pragma config WPCFG = WPCFGDIS
#pragma config WPEND = WPENDMEM

//CONFIG4
#pragma config DSWDTPS = DSWDTPSF
#pragma config DSWDTOSC = LPRC
#pragma config RTCOSC = LPRC
#pragma config DSBOREN = OFF
#pragma config DSWDTEN = OFF


/*
 DSWDT Postscale Select
DSWDTPS = DSWDTPS0	 1 : 2 (2.1 ms)
DSWDTPS = DSWDTPS1	 1 : 8 (8.3 ms)
DSWDTPS = DSWDTPS2	 1 : 32 (33 ms)
DSWDTPS = DSWDTPS3	 1 : 128 (132 ms)
DSWDTPS = DSWDTPS4	 1 : 512 (528 ms)
DSWDTPS = DSWDTPS5	 1 : 2,048 (2.1 seconds)
DSWDTPS = DSWDTPS6	 1 : 8,192 (8.5 seconds)
DSWDTPS = DSWDTPS7	 1 : 32,768 (34 seconds)
DSWDTPS = DSWDTPS8	 1 : 131,072 (135 seconds)
DSWDTPS = DSWDTPS9	 1 : 524,288 (9 minutes)
DSWDTPS = DSWDTPSA	 1 : 2,097,152 (36 minutes)
DSWDTPS = DSWDTPSB	 1 : 8,388,608 (2.4 hours)
DSWDTPS = DSWDTPSC	 1 : 33,554,432 (9.6 hours)
DSWDTPS = DSWDTPSD	 1 : 134,217,728 (38.5 hours)
DSWDTPS = DSWDTPSE	 1 : 536,870,912 (6.4 days)
DSWDTPS = DSWDTPSF	 1 : 2,147,483,648 (25.7 days)

Deep Sleep Watchdog Timer Oscillator Select
DSWDTOSC = SOSC	 DSWDT uses Secondary Oscillator (SOSC)
DSWDTOSC = LPRC	 DSWDT uses Low Power RC Oscillator (LPRC)

RTCC Reference Oscillator Select
RTCOSC = LPRC	 RTCC uses Low Power RC Oscillator (LPRC)
RTCOSC = SOSC	 RTCC uses Secondary Oscillator (SOSC)

Deep Sleep BOR Enable bit
DSBOREN = OFF	 BOR disabled in Deep Sleep
DSBOREN = ON	 BOR enabled in Deep Sleep

Deep Sleep Watchdog Timer
DSWDTEN = OFF	 DSWDT disabled
DSWDTEN = ON	 DSWDT enabled

Write Protection Flash Page Segment Boundary
WPFP = WPFP0	 Page 0 (0x0)
WPFP = WPFP1	 Page 1 (0x400)
WPFP = WPFP2	 Page 2 (0x800)
WPFP = WPFP3	 Page 3 (0xC00)
WPFP = WPFP4	 Page 4 (0x1000)
WPFP = WPFP5	 Page 5 (0x1400)
WPFP = WPFP6	 Page 6 (0x1800)
WPFP = WPFP7	 Page 7 (0x1C00)
WPFP = WPFP8	 Page 8 (0x2000)
WPFP = WPFP9	 Page 9 (0x2400)
WPFP = WPFP10	 Page 10 (0x2800)
WPFP = WPFP11	 Page 11 (0x2C00)
WPFP = WPFP12	 Page 12 (0x3000)
WPFP = WPFP13	 Page 13 (0x3400)
WPFP = WPFP14	 Page 14 (0x3800)
WPFP = WPFP15	 Page 15 (0x3C00)
WPFP = WPFP16	 Page 16 (0x4000)
WPFP = WPFP17	 Page 17 (0x4400)
WPFP = WPFP18	 Page 18 (0x4800)
WPFP = WPFP19	 Page 19 (0x4C00)
WPFP = WPFP20	 Page 20 (0x5000)
WPFP = WPFP21	 Page 21 (0x5400)
WPFP = WPFP22	 Page 22 (0x5800)
WPFP = WPFP23	 Page 23 (0x5C00)
WPFP = WPFP24	 Page 24 (0x6000)
WPFP = WPFP25	 Page 25 (0x6400)
WPFP = WPFP26	 Page 26 (0x6800)
WPFP = WPFP27	 Page 27 (0x6C00)
WPFP = WPFP28	 Page 28 (0x7000)
WPFP = WPFP29	 Page 29 (0x7400)
WPFP = WPFP30	 Page 30 (0x7800)
WPFP = WPFP31	 Page 31 (0x7C00)
WPFP = WPFP32	 Page 32 (0x8000)
WPFP = WPFP33	 Page 33 (0x8400)
WPFP = WPFP34	 Page 34 (0x8800)
WPFP = WPFP35	 Page 35 (0x8C00)
WPFP = WPFP36	 Page 36 (0x9000)
WPFP = WPFP37	 Page 37 (0x9400)
WPFP = WPFP38	 Page 38 (0x9800)
WPFP = WPFP39	 Page 39 (0x9C00)
WPFP = WPFP40	 Page 40 (0xA000)
WPFP = WPFP41	 Page 41 (0xA400)
WPFP = WPFP42	 Page 42 (0xA800)
WPFP = WPFP63	 Highest Page (same as page 42)

 * Secondary Oscillator Pin Mode Select
SOSCSEL = IO	 SOSC pins have digital I/O functions (RA4, RB4)
SOSCSEL = LPSOSC	 SOSC pins in Low-Power (low drive-strength) Oscillator Mode
SOSCSEL = SOSC	 SOSC pins in Default (high drive-strength) Oscillator Mode

Voltage Regulator Wake-up Time Select
WUTSEL = FST	 Fast regulator start-up time used
WUTSEL = LEG	 Default regulator start-up time used

Segment Write Protection Disable
WPDIS = WPEN	 Segmented code protection enabled
WPDIS = WPDIS	 Segmented code protection disabled

Write Protect Configuration Page Select
WPCFG = WPCFGEN	 Last page and Flash Configuration words are code-protected
WPCFG = WPCFGDIS	 Last page and Flash Configuration words are unprotected

Segment Write Protection End Page Select
WPEND = WPSTARTMEM	 Write Protect from page 0 to WPFP
WPEND = WPENDMEM	 Write Protect from WPFP to the last page of memory

Primary Oscillator Select
POSCMOD = EC	 EC Oscillator mode selected
POSCMOD = XT	 XT Oscillator mode selected
POSCMOD = HS	 HS Oscillator mode selected
POSCMOD = NONE	 Primary Oscillator disabled

I2C1 Pin Select bit
I2C1SEL = SEC	 Use alternate SCL1/SDA1 pins for I2C1
I2C1SEL = PRI	 Use default SCL1/SDA1 pins for I2C1

IOLOCK One-Way Set Enable
IOL1WAY = OFF	 The IOLOCK bit can be set and cleared using the unlock sequence
IOL1WAY = ON	 Once set, the IOLOCK bit cannot be cleared

 * OSCO Pin Configuration
OSCIOFNC = ON	 OSCO pin functions as port I/O (RA3)
OSCIOFNC = OFF	 OSCO pin functions as clock output (CLKO)

Clock Switching and Fail-Safe Clock Monitor
FCKSM = CSECME	 Sw Enabled, Mon Enabled
FCKSM = CSECMD	 Sw Enabled, Mon Disabled
FCKSM = CSDCMD	 Sw Disabled, Mon Disabled

Initial Oscillator Select
FNOSC = FRC	 Fast RC Oscillator (FRC)
FNOSC = FRCPLL	 Fast RC Oscillator with Postscaler and PLL module (FRCPLL)
FNOSC = PRI	 Primary Oscillator (XT, HS, EC)
FNOSC = PRIPLL	 Primary Oscillator with PLL module (XTPLL, HSPLL, ECPLL)
FNOSC = SOSC	 Secondary Oscillator (SOSC)
FNOSC = LPRC	 Low-Power RC Oscillator (LPRC)
FNOSC = FRCDIV	 Fast RC Oscillator with Postscaler (FRCDIV)

Internal External Switchover
IESO = OFF	 IESO mode (Two-Speed Start-up) disabled
IESO = ON	 IESO mode (Two-Speed Start-up) enabled

Watchdog Timer Postscaler
WDTPS = PS1	 1 : 1
WDTPS = PS2	 1 : 2
WDTPS = PS4	 1 : 4
WDTPS = PS8	 1 : 8
WDTPS = PS16	 1 : 16
WDTPS = PS32	 1 : 32
WDTPS = PS64	 1 : 64
WDTPS = PS128	 1 : 128
WDTPS = PS256	 1 : 256
WDTPS = PS512	 1 : 512
WDTPS = PS1024	 1 : 1,024
WDTPS = PS2048	 1 : 2,048
WDTPS = PS4096	 1 : 4,096
WDTPS = PS8192	 1 : 8,192
WDTPS = PS16384	 1 : 16,384
WDTPS = PS32768	 1 : 32,768

WDT Prescaler
FWPSA = PR32	 Prescaler ratio of 1 : 32
FWPSA = PR128	 Prescaler ratio of 1 : 128

Windowed WDT
WINDIS = ON	 Windowed Watchdog Timer enabled; FWDTEN must be 1
WINDIS = OFF	 Standard Watchdog Timer enabled,(Windowed-mode is disabled)

Watchdog Timer
FWDTEN = OFF	 Watchdog Timer is disabled
FWDTEN = ON	 Watchdog Timer is enabled

Emulator Pin Placement Select bits
ICS = PGx3	 Emulator functions are shared with PGEC3/PGED3
ICS = PGx2	 Emulator functions are shared with PGEC2/PGED2
ICS = PGx1	 Emulator functions are shared with PGEC1/PGED1

General Segment Write Protect
GWRP = ON	 Writes to program memory are disabled
GWRP = OFF	 Writes to program memory are allowed

General Segment Code Protect
GCP = ON	 Code protection is enabled for the entire program memory space
GCP = OFF	 Code protection is disabled

JTAG Port Enable
JTAGEN = OFF	 JTAG port is disabled
JTAGEN = ON	 JTAG port is enabled
 */
 
#elif 	defined(__PIC24FJ64GA002__) | defined (__PIC24FJ64GA004__) | \
		defined(__PIC24FJ48GA002__) | defined (__PIC24FJ48GA004__) | \
		defined(__PIC24FJ32GA002__) | defined (__PIC24FJ32GA004__) | \
		defined(__PIC24FJ16GA002__) | defined (__PIC24FJ16GA004__)

/*config fues settings for everything else - need customization*/
//CONFIG1
#pragma config JTAGEN = OFF
#pragma config GCP = OFF
#pragma config GWRP = OFF
#pragma config BKBUG = OFF
#pragma config COE = OFF
#pragma config ICS = PGx2
#pragma config FWDTEN = OFF
#pragma config WINDIS = OFF
#pragma config FWPSA = PR128
#pragma config WDTPS = PS32768

//CONFIG2
#pragma config IESO = OFF
#pragma config SOSCSEL = SOSC
#pragma config WUTSEL = LEG
#pragma config FCKSM = CSDCMD
#pragma config OSCIOFNC = OFF
#pragma config IOL1WAY = OFF
#pragma config I2C1SEL = PRI
#pragma config POSCMOD = HS
/*
 Primary Oscillator Select
POSCMOD = EC	 EC Oscillator mode selected
POSCMOD = XT	 XT Oscillator mode selected
POSCMOD = HS	 HS Oscillator mode selected
POSCMOD = NONE	 Primary oscillator disabled

I2C1 Pin Location Select
I2C1SEL = SEC	 Use alternate SCL1/SDA1 pins
I2C1SEL = PRI	 Use default SCL1/SDA1 pins

IOLOCK Protection
IOL1WAY = OFF	 IOLOCK may be changed via unlocking seq
IOL1WAY = ON	 Once IOLOCK is set, cannot be changed

Primary Oscillator Output Function
OSCIOFNC = ON	 OSC2/CLKO/RC15 functions as port I/O (RC15)
OSCIOFNC = OFF	 OSC2/CLKO/RC15 functions as CLKO (FOSC/2)

Clock Switching and Monitor
FCKSM = CSECME	 Clock switching is enabled, Fail-Safe Clock Monitor is enabled
FCKSM = CSECMD	 Clock switching is enabled, Fail-Safe Clock Monitor is disabled
FCKSM = CSDCMD	 Clock switching and Fail-Safe Clock Monitor are disabled

Oscillator Select
FNOSC = FRC	 Fast RC Oscillator (FRC)
FNOSC = FRCPLL	 Fast RC Oscillator with PLL module (FRCPLL)
FNOSC = PRI	 Primary Oscillator (XT, HS, EC)
FNOSC = PRIPLL	 Primary Oscillator with PLL module (HSPLL, ECPLL)
FNOSC = SOSC	 Secondary Oscillator (SOSC)
FNOSC = LPRC	 Low-Power RC Oscillator (LPRC)
FNOSC = FRCDIV	 Fast RC Oscillator with Postscaler (FRCDIV)

Sec Oscillator Select
SOSCSEL = LPSOSC	 Low Power Secondary Oscillator (LPSOSC)
SOSCSEL = SOSC	 Default Secondary Oscillator (SOSC)

Wake-up timer Select
WUTSEL = FST	 Fast Wake-up Timer
WUTSEL = LEG	 Legacy Wake-up Timer

Internal External Switch Over Mode
IESO = OFF	 IESO mode (Two-Speed Start-up) disabled
IESO = ON	 IESO mode (Two-Speed Start-up) enabled

Watchdog Timer Postscaler
WDTPS = PS1	 1 : 1
WDTPS = PS2	 1 : 2
WDTPS = PS4	 1 : 4
WDTPS = PS8	 1 : 8
WDTPS = PS16	 1 : 16
WDTPS = PS32	 1 : 32
WDTPS = PS64	 1 : 64
WDTPS = PS128	 1 : 128
WDTPS = PS256	 1 : 256
WDTPS = PS512	 1 : 512
WDTPS = PS1024	 1 : 1,024
WDTPS = PS2048	 1 : 2,048
WDTPS = PS4096	 1 : 4,096
WDTPS = PS8192	 1 : 8,192
WDTPS = PS16384	 1 : 16,384
WDTPS = PS32768	 1 : 32,768

WDT Prescaler
FWPSA = PR32	 Prescaler ratio of 1 : 32
FWPSA = PR128	 Prescaler ratio of 1 : 128

Watchdog Timer Window
WINDIS = OFF	 Windowed Watchdog Timer enabled; FWDTEN must be 1
WINDIS = ON	 Standard Watchdog Timer enabled,(Windowed-mode is disabled)

Watchdog Timer Enable
FWDTEN = OFF	 Watchdog Timer is disabled
FWDTEN = ON	 Watchdog Timer is enabled

Comm Channel Select
ICS = PGx3	 Emulator EMUC3/EMUD3 pins are shared with PGC3/PGD3
ICS = PGx2	 Emulator EMUC2/EMUD2 pins are shared with PGC2/PGD2
ICS = PGx1	 Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1

Set Clip On Emulation Mode
COE = ON	 Reset Into Clip On Emulation Mode
COE = OFF	 Reset Into Operational Mode

Background Debug
BKBUG = ON	 Device resets into Debug mode
BKBUG = OFF	 Device resets into Operational mode

General Code Segment Write Protect
GWRP = ON	 Writes to program memory are disabled
GWRP = OFF	 Writes to program memory are allowed

General Code Segment Code Protect
GCP = ON	 Code protection is enabled for the entire program memory space
GCP = OFF	 Code protection is disabled

JTAG Port Enable
JTAGEN = OFF	 JTAG port is disabled
JTAGEN = ON	 JTAG port is enabled
 */

#elif 	defined(__PIC24FJ64GB002__) | defined(__PIC24FJ64GB004__) | \
		defined(__PIC24FJ48GB002__) | defined(__PIC24FJ48GB004__) | \
		defined(__PIC24FJ32GB002__) | defined(__PIC24FJ32GB004__)

//CONFIG1
#pragma config JTAGEN = OFF
#pragma config GCP = OFF
#pragma config GWRP = OFF
#pragma config ICS = PGx2
#pragma config FWDTEN = OFF
#pragma config WINDIS = OFF
#pragma config FWPSA = PR128
#pragma config WDTPS = PS32768

//CONFIG2
#pragma config IESO = OFF
#pragma config PLLDIV = DIV12
#pragma config PLL96MHZ = ON
#pragma config FNOSC = PRI
#pragma config FCKSM = CSDCMD
#pragma config OSCIOFNC = OFF
#pragma config IOL1WAY = OFF
#pragma config POSCMOD = HS
#pragma config I2C1SEL = PRI

//CONFIG3
#pragma config WPFP = WPFP0
#pragma config SOSCSEL = IO
#pragma config WUTSEL = LEG
#pragma config WPDIS = WPDIS
#pragma config WPCFG = WPCFGDIS
#pragma config WPEND = WPENDMEM

//CONFIG4
#pragma config DSWDTPS = DSWDTPSF
#pragma config DSWDTOSC = LPRC
#pragma config RTCOSC = LPRC
#pragma config DSBOREN = OFF
#pragma config DSWDTEN = OFF




/*DSWDT Postscale Select
DSWDTPS = DSWDTPS0	 1 : 2 (2.1 ms)
DSWDTPS = DSWDTPS1	 1 : 8 (8.3 ms)
DSWDTPS = DSWDTPS2	 1 : 32 (33 ms)
DSWDTPS = DSWDTPS3	 1 : 128 (132 ms)
DSWDTPS = DSWDTPS4	 1 : 512 (528 ms)
DSWDTPS = DSWDTPS5	 1 : 2,048 (2.1 seconds)
DSWDTPS = DSWDTPS6	 1 : 8,192 (8.5 seconds)
DSWDTPS = DSWDTPS7	 1 : 32,768 (34 seconds)
DSWDTPS = DSWDTPS8	 1 : 131,072 (135 seconds)
DSWDTPS = DSWDTPS9	 1 : 524,288 (9 minutes)
DSWDTPS = DSWDTPSA	 1 : 2,097,152 (36 minutes)
DSWDTPS = DSWDTPSB	 1 : 8,388,608 (2.4 hours)
DSWDTPS = DSWDTPSC	 1 : 33,554,432 (9.6 hours)
DSWDTPS = DSWDTPSD	 1 : 134,217,728 (38.5 hours)
DSWDTPS = DSWDTPSE	 1 : 536,870,912 (6.4 days)
DSWDTPS = DSWDTPSF	 1 : 2,147,483,648 (25.7 days)

Deep Sleep Watchdog Timer Oscillator Select
DSWDTOSC = SOSC	 DSWDT uses Secondary Oscillator (SOSC)
DSWDTOSC = LPRC	 DSWDT uses Low Power RC Oscillator (LPRC)

RTCC Reference Oscillator Select
RTCOSC = LPRC	 RTCC uses Low Power RC Oscillator (LPRC)
RTCOSC = SOSC	 RTCC uses Secondary Oscillator (SOSC)

Deep Sleep BOR Enable bit
DSBOREN = OFF	 BOR disabled in Deep Sleep
DSBOREN = ON	 BOR enabled in Deep Sleep

Deep Sleep Watchdog Timer
DSWDTEN = OFF	 DSWDT disabled
DSWDTEN = ON	 DSWDT enabled

Write Protection Flash Page Segment Boundary
WPFP = WPFP0	 Page 0 (0x0)
WPFP = WPFP1	 Page 1 (0x400)
WPFP = WPFP2	 Page 2 (0x800)
WPFP = WPFP3	 Page 3 (0xC00)
WPFP = WPFP4	 Page 4 (0x1000)
WPFP = WPFP5	 Page 5 (0x1400)
WPFP = WPFP6	 Page 6 (0x1800)
WPFP = WPFP7	 Page 7 (0x1C00)
WPFP = WPFP8	 Page 8 (0x2000)
WPFP = WPFP9	 Page 9 (0x2400)
WPFP = WPFP10	 Page 10 (0x2800)
WPFP = WPFP11	 Page 11 (0x2C00)
WPFP = WPFP12	 Page 12 (0x3000)
WPFP = WPFP13	 Page 13 (0x3400)
WPFP = WPFP14	 Page 14 (0x3800)
WPFP = WPFP15	 Page 15 (0x3C00)
WPFP = WPFP16	 Page 16 (0x4000)
WPFP = WPFP17	 Page 17 (0x4400)
WPFP = WPFP18	 Page 18 (0x4800)
WPFP = WPFP19	 Page 19 (0x4C00)
WPFP = WPFP20	 Page 20 (0x5000)
WPFP = WPFP21	 Page 21 (0x5400)
WPFP = WPFP22	 Page 22 (0x5800)
WPFP = WPFP23	 Page 23 (0x5C00)
WPFP = WPFP24	 Page 24 (0x6000)
WPFP = WPFP25	 Page 25 (0x6400)
WPFP = WPFP26	 Page 26 (0x6800)
WPFP = WPFP27	 Page 27 (0x6C00)
WPFP = WPFP28	 Page 28 (0x7000)
WPFP = WPFP29	 Page 29 (0x7400)
WPFP = WPFP30	 Page 30 (0x7800)
WPFP = WPFP31	 Page 31 (0x7C00)
WPFP = WPFP32	 Page 32 (0x8000)
WPFP = WPFP33	 Page 33 (0x8400)
WPFP = WPFP34	 Page 34 (0x8800)
WPFP = WPFP35	 Page 35 (0x8C00)
WPFP = WPFP36	 Page 36 (0x9000)
WPFP = WPFP37	 Page 37 (0x9400)
WPFP = WPFP38	 Page 38 (0x9800)
WPFP = WPFP39	 Page 39 (0x9C00)
WPFP = WPFP40	 Page 40 (0xA000)
WPFP = WPFP41	 Page 41 (0xA400)
WPFP = WPFP42	 Page 42 (0xA800)
WPFP = WPFP63	 Highest Page (same as page 42)

Secondary Oscillator Pin Mode Select
SOSCSEL = IO	 SOSC pins have digital I/O functions (RA4, RB4)
SOSCSEL = LPSOSC	 SOSC pins in Low-Power (low drive-strength) Oscillator Mode
SOSCSEL = SOSC	 SOSC pins in Default (high drive-strength) Oscillator Mode

Voltage Regulator Wake-up Time Select
WUTSEL = FST	 Fast regulator start-up time used
WUTSEL = LEG	 Default regulator start-up time used

Segment Write Protection Disable
WPDIS = WPEN	 Segmented code protection enabled
WPDIS = WPDIS	 Segmented code protection disabled

Write Protect Configuration Page Select
WPCFG = WPCFGEN	 Last page and Flash Configuration words are code-protected
WPCFG = WPCFGDIS	 Last page and Flash Configuration words are unprotected

Segment Write Protection End Page Select
WPEND = WPSTARTMEM	 Write Protect from page 0 to WPFP
WPEND = WPENDMEM	 Write Protect from WPFP to the last page of memory

Primary Oscillator Select
POSCMOD = EC	 EC Oscillator mode selected
POSCMOD = XT	 XT Oscillator mode selected
POSCMOD = HS	 HS Oscillator mode selected
POSCMOD = NONE	 Primary Oscillator disabled

I2C1 Pin Select bit
I2C1SEL = SEC	 Use alternate SCL1/SDA1 pins for I2C1
I2C1SEL = PRI	 Use default SCL1/SDA1 pins for I2C1

IOLOCK One-Way Set Enable
IOL1WAY = OFF	 The IOLOCK bit can be set and cleared using the unlock sequence
IOL1WAY = ON	 Once set, the IOLOCK bit cannot be cleared

OSCO Pin Configuration
OSCIOFNC = ON	 OSCO pin functions as port I/O (RA3)
OSCIOFNC = OFF	 OSCO pin functions as clock output (CLKO)

Clock Switching and Fail-Safe Clock Monitor
FCKSM = CSECME	 Sw Enabled, Mon Enabled
FCKSM = CSECMD	 Sw Enabled, Mon Disabled
FCKSM = CSDCMD	 Sw Disabled, Mon Disabled

Initial Oscillator Select
FNOSC = FRC	 Fast RC Oscillator (FRC)
FNOSC = FRCPLL	 Fast RC Oscillator with Postscaler and PLL module (FRCPLL)
FNOSC = PRI	 Primary Oscillator (XT, HS, EC)
FNOSC = PRIPLL	 Primary Oscillator with PLL module (XTPLL, HSPLL, ECPLL)
FNOSC = SOSC	 Secondary Oscillator (SOSC)
FNOSC = LPRC	 Low-Power RC Oscillator (LPRC)
FNOSC = FRCDIV	 Fast RC Oscillator with Postscaler (FRCDIV)

96MHz PLL Startup Select
PLL96MHZ = OFF	 96 MHz PLL Startup is enabled by user in software( controlled with the PLLEN bit)
PLL96MHZ = ON	 96 MHz PLL Startup is enabled automatically on start-up

USB 96 MHz PLL Prescaler Select
PLLDIV = NODIV	 Oscillator input used directly (4 MHz input)
PLLDIV = DIV2	 Oscillator input divided by 2 (8 MHz input)
PLLDIV = DIV3	 Oscillator input divided by 3 (12 MHz input)
PLLDIV = DIV4	 Oscillator input divided by 4 (16 MHz input)
PLLDIV = DIV5	 Oscillator input divided by 5 (20 MHz input)
PLLDIV = DIV6	 Oscillator input divided by 6 (24 MHz input)
PLLDIV = DIV8	 Oscillator input divided by 8 (32 MHz input)
PLLDIV = DIV12	 Oscillator input divided by 12 (48 MHz input)

Internal External Switchover
IESO = OFF	 IESO mode (Two-Speed Start-up) disabled
IESO = ON	 IESO mode (Two-Speed Start-up) enabled

Watchdog Timer Postscaler
WDTPS = PS1	 1 : 1
WDTPS = PS2	 1 : 2
WDTPS = PS4	 1 : 4
WDTPS = PS8	 1 : 8
WDTPS = PS16	 1 : 16
WDTPS = PS32	 1 : 32
WDTPS = PS64	 1 : 64
WDTPS = PS128	 1 : 128
WDTPS = PS256	 1 : 256
WDTPS = PS512	 1 : 512
WDTPS = PS1024	 1 : 1,024
WDTPS = PS2048	 1 : 2,048
WDTPS = PS4096	 1 : 4,096
WDTPS = PS8192	 1 : 8,192
WDTPS = PS16384	 1 : 16,384
WDTPS = PS32768	 1 : 32,768

WDT Prescaler
FWPSA = PR32	 Prescaler ratio of 1 : 32
FWPSA = PR128	 Prescaler ratio of 1 : 128

Windowed WDT
WINDIS = ON	 Windowed Watchdog Timer enabled; FWDTEN must be 1
WINDIS = OFF	 Standard Watchdog Timer enabled,(Windowed-mode is disabled)

Watchdog Timer
FWDTEN = OFF	 Watchdog Timer is disabled
FWDTEN = ON	 Watchdog Timer is enabled

Emulator Pin Placement Select bits
ICS = PGx3	 Emulator functions are shared with PGEC3/PGED3
ICS = PGx2	 Emulator functions are shared with PGEC2/PGED2
ICS = PGx1	 Emulator functions are shared with PGEC1/PGED1

General Segment Write Protect
GWRP = ON	 Writes to program memory are disabled
GWRP = OFF	 Writes to program memory are allowed

General Segment Code Protect
GCP = ON	 Code protection is enabled for the entire program memory space
GCP = OFF	 Code protection is disabled

JTAG Port Enable
JTAGEN = OFF	 JTAG port is disabled
JTAGEN = ON	 JTAG port is enabled
 */

//dsPIC33FJ32GP202, dspic33fj32gp204
//dspic33fj16gp304
#elif defined(__dsPIC33FJ32GP202__) || defined(__dsPIC33FJ32GP204__) || defined(__dsPIC33FJ16GP304__)

#pragma config BWRP = WRPROTECT_OFF
#pragma config BSS = NO_BOOT_CODE
//#pragma config RBS = NO_BOOT_RAM
//#pragma config SWRP = WRPROTECT_OFF
//#pragma config SSS = NO_SEC_CODE
//#pragma config RSS = NO_SEC_RAM
#pragma config GWRP = OFF
#pragma config GSS = OFF
#pragma config FNOSC = PRI
#pragma config IESO = OFF
#pragma config POSCMD = HS
#pragma config OSCIOFNC = OFF
#pragma config IOL1WAY = OFF
#pragma config FCKSM = CSDCMD
#pragma config WDTPOST = PS32768
#pragma config WDTPRE = PR128
#pragma config WINDIS = OFF
#pragma config FWDTEN = OFF
#pragma config FPWRT = PWR128
#pragma config ALTI2C = OFF
#pragma config ICS = PGD2
#pragma config JTAGEN = OFF

/*Boot Segment Write Protect
BWRP = WRPROTECT_ON	 Boot segment is write-protected
BWRP = WRPROTECT_OFF	 Boot Segment may be written

Boot Segment Program Flash Code Protection
BSS = LARGE_FLASH_HIGH	 High Security, Large-sized Boot Flash
BSS = HIGH_LARGE_BOOT_CODE	 High Security, Large-sized Boot Flash
BSS = MEDIUM_FLASH_HIGH	 High Security, Medium-sized Boot Flash
BSS = HIGH_MEDIUM_BOOT_CODE	 High Security, Medium-sized Boot Flash
BSS = SMALL_FLASH_HIGH	 High Security, Small-sized Boot Flash
BSS = HIGH_SMALL_BOOT_CODE	 High Security, Small-sized Boot Flash
BSS = LARGE_FLASH_STD	 Standard Security, Large-sized Boot Flash
BSS = STRD_LARGE_BOOT_CODE	 Standard Security, Large-sized Boot Flash
BSS = MEDIUM_FLASH_STD	 Standard Security, Medium-sized Boot Flash
BSS = STRD_MEDIUM_BOOT_CODE	 Standard Security, Medium-sized Boot Flash
BSS = SMALL_FLASH_STD	 Standard Security, Small-sized Boot Flash
BSS = STRD_SMALL_BOOT_CODE	 Standard Security, Small-sized Boot Flash
BSS = NO_FLASH	 No Boot program Flash segment
BSS = NO_BOOT_CODE	 No Boot program Flash segment

General Code Segment Write Protect
GWRP = ON	 User program memory is write-protected
GWRP = OFF	 User program memory is not write-protected

General Segment Code Protection
GSS = HIGH	 High Security Code Protection is Enabled
GSS = ON	 Standard Security Code Protection is Enabled
GSS = OFF	 User program memory is not code-protected

Oscillator Mode
FNOSC = FRC	 Internal Fast RC (FRC)
FNOSC = FRCPLL	 Internal Fast RC (FRC) w/ PLL
FNOSC = PRI	 Primary Oscillator (XT, HS, EC)
FNOSC = PRIPLL	 Primary Oscillator (XT, HS, EC) w/ PLL
FNOSC = SOSC	 Secondary Oscillator (SOSC)
FNOSC = LPRC	 Low Power RC Oscillator (LPRC)
FNOSC = FRCDIV16	 Internal Fast RC (FRC) divide by 16
FNOSC = LPRCDIVN	 Internal Fast RC (FRC) with divide by N

Internal External Switch Over Mode
IESO = OFF	 Start-up device with user-selected oscillator source
IESO = ON	 Start-up device with FRC, then automatically switch to user-selected oscillator source when ready

Primary Oscillator Source
POSCMD = EC	 EC Oscillator Mode
POSCMD = XT	 XT Oscillator Mode
POSCMD = HS	 HS Oscillator Mode
POSCMD = NONE	 Primary Oscillator Disabled

OSC2 Pin Function
OSCIOFNC = ON	 OSC2 pin has digital I/O function
OSCIOFNC = OFF	 OSC2 pin has clock out function

Peripheral Pin Select Configuration
IOL1WAY = OFF	 Allow Multiple Re-configurations
IOL1WAY = ON	 Allow Only One Re-configuration

Clock Switching and Monitor
FCKSM = CSECME	 Both Clock Switching and Fail-Safe Clock Monitor are enabled
FCKSM = CSECMD	 Clock switching is enabled, Fail-Safe Clock Monitor is disabled
FCKSM = CSDCMD	 Both Clock Switching and Fail-Safe Clock Monitor are disabled

Watchdog Timer Postscaler
WDTPOST = PS1	 1 : 1
WDTPOST = PS2	 1 : 2
WDTPOST = PS4	 1 : 4
WDTPOST = PS8	 1 : 8
WDTPOST = PS16	 1 : 16
WDTPOST = PS32	 1 : 32
WDTPOST = PS64	 1 : 64
WDTPOST = PS128	 1 : 128
WDTPOST = PS256	 1 : 256
WDTPOST = PS512	 1 : 512
WDTPOST = PS1024	 1 : 1,024
WDTPOST = PS2048	 1 : 2,048
WDTPOST = PS4096	 1 : 4,096
WDTPOST = PS8192	 1 : 8,192
WDTPOST = PS16384	 1 : 16,384
WDTPOST = PS32768	 1 : 32,768

WDT Prescaler
WDTPRE = PR32	 1 : 32
WDTPRE = PR128	 1 : 128

Watchdog Timer Window
WINDIS = ON	 Watchdog Timer in Window mode
WINDIS = OFF	 Watchdog Timer in Non-Window mode

Watchdog Timer Enable
FWDTEN = OFF	 Watchdog timer enabled/disabled by user software
FWDTEN = ON	 Watchdog timer always enabled

POR Timer Value
FPWRT = PWR1	 Disabled
FPWRT = PWR2	 2ms
FPWRT = PWR4	 4ms
FPWRT = PWR8	 8ms
FPWRT = PWR16	 16ms
FPWRT = PWR32	 32ms
FPWRT = PWR64	 64ms
FPWRT = PWR128	 128ms

Alternate I2C pins
ALTI2C = ON	 I2C mapped to ASDA1/ASCL1 pins
ALTI2C = OFF	 I2C mapped to SDA1/SCL1 pins

Comm Channel Select
ICS = PGD3	 Communicate on PGC3/EMUC3 and PGD3/EMUD3
ICS = PGD2	 Communicate on PGC2/EMUC2 and PGD2/EMUD2
ICS = PGD1	 Communicate on PGC1/EMUC1 and PGD1/EMUD1

JTAG Port Enable
JTAGEN = OFF	 JTAG is Disabled
JTAGEN = ON	 JTAG is Enabled
*/

//dspic33fj128gp202, dspic33fj128gp204, dspic33fj128gp802, dspic33fj128gp804
//dspic33fj64gp202,  dspic33fj64gp204,  dspic33fj64gp802,  dspic33fj64gp804
//dspic33fj32gp302,  dspic33fj32gp304
#elif 	defined(__dsPIC33FJ128GP202__) || defined(__dsPIC33FJ128GP204__) || defined(__dsPIC33FJ128GP802__) || defined(__dsPIC33FJ128GP804__) || \
	defined(__dsPIC33FJ64GP202__) || defined(__dsPIC33FJ64GP204__) || defined(__dsPIC33FJ64GP802__) || defined(__dsPIC33FJ64GP804__) || \
	defined(__dsPIC33FJ32GP302__) || defined(__dsPIC33FJ32GP304__)

#pragma config BWRP = WRPROTECT_OFF
#pragma config BSS = NO_BOOT_CODE
#pragma config RBS = NO_BOOT_RAM
#pragma config SWRP = WRPROTECT_OFF
#pragma config SSS = NO_SEC_CODE
#pragma config RSS = NO_SEC_RAM
#pragma config GWRP = OFF
#pragma config GSS = OFF
#pragma config FNOSC = PRI
#pragma config IESO = OFF
#pragma config POSCMD = HS
#pragma config OSCIOFNC = OFF
#pragma config IOL1WAY = OFF
#pragma config FCKSM = CSDCMD
#pragma config WDTPOST = PS32768
#pragma config WDTPRE = PR128
#pragma config WINDIS = OFF
#pragma config FWDTEN = OFF
#pragma config FPWRT = PWR128
#pragma config ALTI2C = OFF
#pragma config ICS = PGD2
#pragma config JTAGEN = OFF

/*Boot Segment Write Protect
BWRP = WRPROTECT_ON	 Boot segment is write-protected
BWRP = WRPROTECT_OFF	 Boot Segment may be written

Boot Segment Program Flash Code Protection
BSS = LARGE_FLASH_HIGH	 High Security, Large-sized Boot Flash
BSS = HIGH_LARGE_BOOT_CODE	 High Security, Large-sized Boot Flash
BSS = MEDIUM_FLASH_HIGH	 High Security, Medium-sized Boot Flash
BSS = HIGH_MEDIUM_BOOT_CODE	 High Security, Medium-sized Boot Flash
BSS = SMALL_FLASH_HIGH	 High Security, Small-sized Boot Flash
BSS = HIGH_SMALL_BOOT_CODE	 High Security, Small-sized Boot Flash
BSS = LARGE_FLASH_STD	 Standard Security, Large-sized Boot Flash
BSS = STRD_LARGE_BOOT_CODE	 Standard Security, Large-sized Boot Flash
BSS = MEDIUM_FLASH_STD	 Standard Security, Medium-sized Boot Flash
BSS = STRD_MEDIUM_BOOT_CODE	 Standard Security, Medium-sized Boot Flash
BSS = SMALL_FLASH_STD	 Standard Security, Small-sized Boot Flash
BSS = STRD_SMALL_BOOT_CODE	 Standard Security, Small-sized Boot Flash
BSS = NO_FLASH	 No Boot program Flash segment
BSS = NO_BOOT_CODE	 No Boot program Flash segment

Boot Segment RAM Protection
RBS = LARGE_RAM	 Large-sized Boot RAM
RBS = LARGE_BOOT_RAM	 Large-sized Boot RAM
RBS = MEDIUM_RAM	 Medium-sized Boot RAM
RBS = MEDIUM_BOOT_RAM	 Medium-sized Boot RAM
RBS = SMALL_RAM	 Small-sized Boot RAM
RBS = SMALL_BOOT_RAM	 Small-sized Boot RAM
RBS = NO_RAM	 No Boot RAM
RBS = NO_BOOT_RAM	 No Boot RAM

Secure Segment Program Write Protect
SWRP = WRPROTECT_ON	 Secure segment is write-protected
SWRP = WRPROTECT_OFF	 Secure segment may be written

Secure Segment Program Flash Code Protection
SSS = LARGE_FLASH_HIGH	 High Security, Large-sized Secure Flash
SSS = HIGH_LARGE_SEC_CODE	 High Security, Large-sized Secure Flash
SSS = MEDIUM_FLASH_HIGH	 High Security, Medium-sized Secure Flash
SSS = HIGH_MEDIUM_SEC_CODE	 High Security, Medium-sized Secure Flash
SSS = SMALL_FLASH_HIGH	 High Security, Small-sized Secure Flash
SSS = HIGH_SMALL_SEC_CODE	 High Security, Small-sized Secure Flash
SSS = LARGE_FLASH_STD	 Standard Security, Large-sized Secure Flash
SSS = STRD_LARGE_SEC_CODE	 Standard Security, Large-sized Secure Flash
SSS = MEDIUM_FLASH_STD	 Standard Security, Medium-sized Secure Flash
SSS = STRD_MEDIUM_SEC_CODE	 Standard Security, Medium-sized Secure Flash
SSS = SMALL_FLASH_STD	 Standard Security, Small-sized Secure Flash
SSS = STRD_SMALL_SEC_CODE	 Standard Security, Small-sized Secure Flash
SSS = NO_FLASH	 No Secure Segment
SSS = NO_SEC_CODE	 No Secure Segment

Secure Segment Data RAM Protection
RSS = LARGE_RAM	 Large-sized Secure RAM
RSS = LARGE_SEC_RAM	 Large-sized Secure RAM
RSS = MEDIUM_RAM	 Medium-sized Secure RAM
RSS = MEDIUM_SEC_RAM	 Medium-sized Secure RAM
RSS = SMALL_RAM	 Small-sized Secure RAM
RSS = SMALL_SEC_RAM	 Small-sized Secure RAM
RSS = NO_RAM	 No Secure RAM
RSS = NO_SEC_RAM	 No Secure RAM

General Code Segment Write Protect
GWRP = ON	 User program memory is write-protected
GWRP = OFF	 User program memory is not write-protected

General Segment Code Protection
GSS = HIGH	 High Security Code Protection is Enabled
GSS = ON	 Standard Security Code Protection is Enabled
GSS = OFF	 User program memory is not code-protected

Oscillator Mode
FNOSC = FRC	 Internal Fast RC (FRC)
FNOSC = FRCPLL	 Internal Fast RC (FRC) w/ PLL
FNOSC = PRI	 Primary Oscillator (XT, HS, EC)
FNOSC = PRIPLL	 Primary Oscillator (XT, HS, EC) w/ PLL
FNOSC = SOSC	 Secondary Oscillator (SOSC)
FNOSC = LPRC	 Low Power RC Oscillator (LPRC)
FNOSC = FRCDIV16	 Internal Fast RC (FRC) divide by 16
FNOSC = LPRCDIVN	 Internal Fast RC (FRC) with divide by N

Internal External Switch Over Mode
IESO = OFF	 Start-up device with user-selected oscillator source
IESO = ON	 Start-up device with FRC, then automatically switch to user-selected oscillator source when ready

Primary Oscillator Source
POSCMD = EC	 EC Oscillator Mode
POSCMD = XT	 XT Oscillator Mode
POSCMD = HS	 HS Oscillator Mode
POSCMD = NONE	 Primary Oscillator Disabled

OSC2 Pin Function
OSCIOFNC = ON	 OSC2 pin has digital I/O function
OSCIOFNC = OFF	 OSC2 pin has clock out function

Peripheral Pin Select Configuration
IOL1WAY = OFF	 Allow Multiple Re-configurations
IOL1WAY = ON	 Allow Only One Re-configuration

Clock Switching and Monitor
FCKSM = CSECME	 Both Clock Switching and Fail-Safe Clock Monitor are enabled
FCKSM = CSECMD	 Clock switching is enabled, Fail-Safe Clock Monitor is disabled
FCKSM = CSDCMD	 Both Clock Switching and Fail-Safe Clock Monitor are disabled

Watchdog Timer Postscaler
WDTPOST = PS1	 1 : 1
WDTPOST = PS2	 1 : 2
WDTPOST = PS4	 1 : 4
WDTPOST = PS8	 1 : 8
WDTPOST = PS16	 1 : 16
WDTPOST = PS32	 1 : 32
WDTPOST = PS64	 1 : 64
WDTPOST = PS128	 1 : 128
WDTPOST = PS256	 1 : 256
WDTPOST = PS512	 1 : 512
WDTPOST = PS1024	 1 : 1,024
WDTPOST = PS2048	 1 : 2,048
WDTPOST = PS4096	 1 : 4,096
WDTPOST = PS8192	 1 : 8,192
WDTPOST = PS16384	 1 : 16,384
WDTPOST = PS32768	 1 : 32,768

WDT Prescaler
WDTPRE = PR32	 1 : 32
WDTPRE = PR128	 1 : 128

Watchdog Timer Window
WINDIS = ON	 Watchdog Timer in Window mode
WINDIS = OFF	 Watchdog Timer in Non-Window mode

Watchdog Timer Enable
FWDTEN = OFF	 Watchdog timer enabled/disabled by user software
FWDTEN = ON	 Watchdog timer always enabled

POR Timer Value
FPWRT = PWR1	 Disabled
FPWRT = PWR2	 2ms
FPWRT = PWR4	 4ms
FPWRT = PWR8	 8ms
FPWRT = PWR16	 16ms
FPWRT = PWR32	 32ms
FPWRT = PWR64	 64ms
FPWRT = PWR128	 128ms

Alternate I2C pins
ALTI2C = ON	 I2C mapped to ASDA1/ASCL1 pins
ALTI2C = OFF	 I2C mapped to SDA1/SCL1 pins

Comm Channel Select
ICS = PGD3	 Communicate on PGC3/EMUC3 and PGD3/EMUD3
ICS = PGD2	 Communicate on PGC2/EMUC2 and PGD2/EMUD2
ICS = PGD1	 Communicate on PGC1/EMUC1 and PGD1/EMUD1

JTAG Port Enable
JTAGEN = OFF	 JTAG is Disabled
JTAGEN = ON	 JTAG is Enabled
*/

//pic24fj16mc101, pic24fj16mc102
//pic24fj32mc101, pic24fj32mc102, pic24fj32mc104
#elif	defined(__PIC24FJ16MC101__) || defined(__PIC24FJ16MC102__) || \
		defined(__PIC24FJ32MC101__) || defined(__PIC24FJ32MC102__) || defined(__PIC24FJ32MC104__)

#pragma config POSCMOD = HS
#pragma config ALTI2C = OFF
#pragma config LPOL = OFF
#pragma config IOL1WAY = OFF
#pragma config OSCIOFNC = OFF
#pragma config FCKSM = CSDCMD
#pragma config FNOSC = FRC
#pragma config WDTWIN = WDTWIN75
#pragma config PWMPIN = OFF
#pragma config PWMLOCK = OFF
#pragma config IESO = OFF
#pragma config WDTPOST=PS32768
#pragma config WDTPRE=PR128
#pragma config PLLKEN = OFF
#pragma config WINDIS = OFF
#pragma config FWDTEN = OFF
#pragma config ICS = PGD1
#pragma config HPOL = OFF
#pragma config GWRP = OFF
#pragma config GCP = OFF
/*
Primary Oscillator Select
POSCMOD = EC	EC Oscillator mode selected
POSCMOD = MS	MS Oscillator mode selected
POSCMOD = HS	HS Oscillator mode selected
POSCMOD = NONE	Primary oscillator disabled

Alternate I2C pins
ALTI2C = ON	I2C mapped to ASDA1/ASCL1
ALTI2C = OFF	I2C mapped to SDA1/SCL1

Motor Control PWM Low Side Polarity bit
LPOL = OFF	PWM module low side output pins have active-low output polarity
LPOL = ON	PWM module low side output pins have active-high output polarity

IOLOCK Protection
IOL1WAY = OFF	Allow Multiple Re-configurations
IOL1WAY = ON	Allow Only One Re-configuration

Primary Oscillator Output Function
OSCIOFNC = ON	OSC2 pin has digital I/O function
OSCIOFNC = OFF	OSC2 pin has clock out function

Clock Switching and Monitor
FCKSM = CSECME	Clock switching is enabled, Fail-Safe Clock Monitor is enabled
FCKSM = CSECMD	Clock switching is enabled, Fail-Safe Clock Monitor is disabled
FCKSM = CSDCMD	Clock switching and Fail-Safe Clock Monitor are disabled

Oscillator Mode
FNOSC = FRC	Internal Fast RC (FRC)
FNOSC = FRCPLL	Internal Fast RC (FRC) w/ PLL
FNOSC = PRI	Primary Oscillator (MS, HS, EC)
FNOSC = PRIPLL	Primary Oscillator (MS, HS, EC) w/ PLL
FNOSC = SOSC	Secondary Oscillator (SOSC)
FNOSC = LPRC	Low Power RC Oscillator (LPRC)
FNOSC = FRCDIVN	Internal Fast RC (FRC) with divide by N

Watchdog Window Select
WDTWIN = WDTWIN75	Watchdog Window is 75% of WDT period
WDTWIN = WDTWIN50	Watchdog Window is 50% of WDT period
WDTWIN = WDTWIN37	Watchdog Window is 37.5% of WDT period
WDTWIN = WDTWIN25	Watchdog Window is 25% of WDT period

Motor Control PWM Module Pin Mode bit
PWMPIN = OFF	PWM module pins controlled by PWM module at device Reset
PWMPIN = ON	PWM module pins controlled by PORT register at device Reset

PWM Lock Enable
PWMLOCK = OFF	PWM registers may be written without key sequence
PWMLOCK = ON	Certain PWM registers may only be written after key sequence

Internal External Switch Over Mode
IESO = OFF	Start-up device with user-selected oscillator source
IESO = ON	Start-up device with FRC, then automatically switch to user-selected oscillator source when ready

Watchdog Timer Postscaler
WDTPOST = PS1	1 : 1
WDTPOST = PS2	1 : 2
WDTPOST = PS4	1 : 4
WDTPOST = PS8	1 : 8
WDTPOST = PS16	1 : 16
WDTPOST = PS32	1 : 32
WDTPOST = PS64	1 : 64
WDTPOST = PS128	1 : 128
WDTPOST = PS256	1 : 256
WDTPOST = PS512	1 : 512
WDTPOST = PS1024	1 : 1,024
WDTPOST = PS2048	1 : 2,048
WDTPOST = PS4096	1 : 4,096
WDTPOST = PS8192	1 : 8,192
WDTPOST = PS16384	1 : 16,384
WDTPOST = PS32768	1 : 32,768

WDT Prescaler
WDTPRE = PR32	Prescaler ratio of 1 : 32
WDTPRE = PR128	Prescaler ratio of 1 : 128

PLL Lock Enable
PLLKEN = OFF	Clock switch will not wait for the PLL lock signal.
PLLKEN = ON	Clock switch to PLL source will wait until the PLL lock signal is valid.

Watchdog Timer Window
WINDIS = ON	Watchdog Timer in Window mode
WINDIS = OFF	Watchdog Timer in Non-Window mode

Watchdog Timer Enable
FWDTEN = OFF	Watchdog timer enabled/disabled by user software
FWDTEN = ON	Watchdog timer always enabled

Comm Channel Select
ICS = PGD3	Communicate on PGEC3/PGED3
ICS = PGD2	Communicate on PGEC2/PGED2
ICS = PGD1	Communicate on PGEC1/PGED1

Motor Control PWM High Side Polarity bit
HPOL = OFF	PWM module high side output pins have active-low output polarity
HPOL = ON	PWM module high side output pins have active-high output polarity

General Code Segment Write Protect
GWRP = ON	Writes to program memory are disabled
GWRP = OFF	Writes to program memory are allowed

General Segment Code Protection
GCP = ON	Standard Security Code protection Enabled
GCP = OFF	General Segment Code protect is disabled
*/
//DSPIC33FJ128MC202, DSPIC33FJ128MC204, DSPIC33FJ128MC802, DSPIC33FJ128MC804, 
//DSPIC33FJ64MC202, DSPIC33FJ64MC204, DSPIC33FJ64MC802, DSPIC33FJ64MC804, 
//DSPIC33FJ32MC302, DSPIC33FJ32MC304
#elif	defined(__dsPIC33FJ128MC202__) || defined(__dsPIC33FJ128MC204__) || defined(__dsPIC33FJ128MC802__) || defined(__dsPIC33FJ128MC804__) || \
		defined(__dsPIC33FJ64MC202__) || defined(__dsPIC33FJ64MC204__) || defined(__dsPIC33FJ64MC802__) || defined(__dsPIC33FJ64MC804__) || \
		defined(__dsPIC33FJ32MC302__) || defined(__dsPIC33FJ32MC304__)

#pragma config BWRP = WRPROTECT_OFF
#pragma config BSS = NO_FLASH
#pragma config RBS = NO_RAM
#pragma config SWRP = WRPROTECT_OFF
#pragma config SSS = NO_FLASH
#pragma config RSS = NO_RAM
#pragma config GWRP = OFF
#pragma config GSS = OFF
#pragma config FNOSC = FRC
#pragma config IESO = OFF
#pragma config POSCMD = HS
#pragma config OSCIOFNC = OFF
#pragma config IOL1WAY = OFF
#pragma config FCKSM = CSDCMD
#pragma config WDTPOST = PS32768
#pragma config WDTPRE = PR128
#pragma config WINDIS = OFF
#pragma config FWDTEN = OFF
#pragma config FPWRT = PWR1
#pragma config ALTI2C = OFF
#pragma config LPOL = OFF
#pragma config HPOL = OFF
#pragma config PWMPIN = OFF
#pragma config ICS = PGD1
#pragma config JTAGEN = OFF
/*
Boot Segment Write Protect
BWRP = WRPROTECT_ON	Boot segment is write-protected
BWRP = WRPROTECT_OFF	Boot Segment may be written

Boot Segment Program Flash Code Protection
BSS = LARGE_FLASH_HIGH	High Security, Large-sized Boot Flash
BSS = HIGH_LARGE_BOOT_CODE	High Security, Large-sized Boot Flash
BSS = MEDIUM_FLASH_HIGH	High Security, Medium-sized Boot Flash
BSS = HIGH_MEDIUM_BOOT_CODE	High Security, Medium-sized Boot Flash
BSS = SMALL_FLASH_HIGH	High Security, Small-sized Boot Flash
BSS = HIGH_SMALL_BOOT_CODE	High Security, Small-sized Boot Flash
BSS = LARGE_FLASH_STD	Standard Security, Large-sized Boot Flash
BSS = STRD_LARGE_BOOT_CODE	Standard Security, Large-sized Boot Flash
BSS = MEDIUM_FLASH_STD	Standard Security, Medium-sized Boot Flash
BSS = STRD_MEDIUM_BOOT_CODE	Standard Security, Medium-sized Boot Flash
BSS = SMALL_FLASH_STD	Standard Security, Small-sized Boot Flash
BSS = STRD_SMALL_BOOT_CODE	Standard Security, Small-sized Boot Flash
BSS = NO_FLASH	No Boot program Flash segment
BSS = NO_BOOT_CODE	No Boot program Flash segment

Boot Segment RAM Protection
RBS = LARGE_RAM	Large-sized Boot RAM
RBS = LARGE_BOOT_RAM	Large-sized Boot RAM
RBS = MEDIUM_RAM	Medium-sized Boot RAM
RBS = MEDIUM_BOOT_RAM	Medium-sized Boot RAM
RBS = SMALL_RAM	Small-sized Boot RAM
RBS = SMALL_BOOT_RAM	Small-sized Boot RAM
RBS = NO_RAM	No Boot RAM
RBS = NO_BOOT_RAM	No Boot RAM

Secure Segment Program Write Protect
SWRP = WRPROTECT_ON	Secure segment is write-protected
SWRP = WRPROTECT_OFF	Secure segment may be written

Secure Segment Program Flash Code Protection
SSS = LARGE_FLASH_HIGH	High Security, Large-sized Secure Flash
SSS = HIGH_LARGE_SEC_CODE	High Security, Large-sized Secure Flash
SSS = MEDIUM_FLASH_HIGH	High Security, Medium-sized Secure Flash
SSS = HIGH_MEDIUM_SEC_CODE	High Security, Medium-sized Secure Flash
SSS = SMALL_FLASH_HIGH	High Security, Small-sized Secure Flash
SSS = HIGH_SMALL_SEC_CODE	High Security, Small-sized Secure Flash
SSS = LARGE_FLASH_STD	Standard Security, Large-sized Secure Flash
SSS = STRD_LARGE_SEC_CODE	Standard Security, Large-sized Secure Flash
SSS = MEDIUM_FLASH_STD	Standard Security, Medium-sized Secure Flash
SSS = STRD_MEDIUM_SEC_CODE	Standard Security, Medium-sized Secure Flash
SSS = SMALL_FLASH_STD	Standard Security, Small-sized Secure Flash
SSS = STRD_SMALL_SEC_CODE	Standard Security, Small-sized Secure Flash
SSS = NO_FLASH	No Secure Segment
SSS = NO_SEC_CODE	No Secure Segment

Secure Segment Data RAM Protection
RSS = LARGE_RAM	Large-sized Secure RAM
RSS = LARGE_SEC_RAM	Large-sized Secure RAM
RSS = MEDIUM_RAM	Medium-sized Secure RAM
RSS = MEDIUM_SEC_RAM	Medium-sized Secure RAM
RSS = SMALL_RAM	Small-sized Secure RAM
RSS = SMALL_SEC_RAM	Small-sized Secure RAM
RSS = NO_RAM	No Secure RAM
RSS = NO_SEC_RAM	No Secure RAM

General Code Segment Write Protect
GWRP = ON	User program memory is write-protected
GWRP = OFF	User program memory is not write-protected

General Segment Code Protection
GSS = HIGH	High Security Code Protection is Enabled
GSS = ON	Standard Security Code Protection is Enabled
GSS = OFF	User program memory is not code-protected

Oscillator Mode
FNOSC = FRC	Internal Fast RC (FRC)
FNOSC = FRCPLL	Internal Fast RC (FRC) w/ PLL
FNOSC = PRI	Primary Oscillator (XT, HS, EC)
FNOSC = PRIPLL	Primary Oscillator (XT, HS, EC) w/ PLL
FNOSC = SOSC	Secondary Oscillator (SOSC)
FNOSC = LPRC	Low Power RC Oscillator (LPRC)
FNOSC = FRCDIV16	Internal Fast RC (FRC) divide by 16
FNOSC = LPRCDIVN	Internal Fast RC (FRC) with divide by N

Internal External Switch Over Mode
IESO = OFF	Start-up device with user-selected oscillator source
IESO = ON	Start-up device with FRC, then automatically switch to user-selected oscillator source when ready

Primary Oscillator Source
POSCMD = EC	EC Oscillator Mode
POSCMD = XT	XT Oscillator Mode
POSCMD = HS	HS Oscillator Mode
POSCMD = NONE	Primary Oscillator Disabled

OSC2 Pin Function
OSCIOFNC = ON	OSC2 pin has digital I/O function
OSCIOFNC = OFF	OSC2 pin has clock out function

Peripheral Pin Select Configuration
IOL1WAY = OFF	Allow Multiple Re-configurations
IOL1WAY = ON	Allow Only One Re-configuration

Clock Switching and Monitor
FCKSM = CSECME	Both Clock Switching and Fail-Safe Clock Monitor are enabled
FCKSM = CSECMD	Clock switching is enabled, Fail-Safe Clock Monitor is disabled
FCKSM = CSDCMD	Both Clock Switching and Fail-Safe Clock Monitor are disabled

Watchdog Timer Postscaler
WDTPOST = PS1	1 : 1
WDTPOST = PS2	1 : 2
WDTPOST = PS4	1 : 4
WDTPOST = PS8	1 : 8
WDTPOST = PS16	1 : 16
WDTPOST = PS32	1 : 32
WDTPOST = PS64	1 : 64
WDTPOST = PS128	1 : 128
WDTPOST = PS256	1 : 256
WDTPOST = PS512	1 : 512
WDTPOST = PS1024	1 : 1,024
WDTPOST = PS2048	1 : 2,048
WDTPOST = PS4096	1 : 4,096
WDTPOST = PS8192	1 : 8,192
WDTPOST = PS16384	1 : 16,384
WDTPOST = PS32768	1 : 32,768

WDT Prescaler
WDTPRE = PR32	1 : 32
WDTPRE = PR128	1 : 128

Watchdog Timer Window
WINDIS = ON	Watchdog Timer in Window mode
WINDIS = OFF	Watchdog Timer in Non-Window mode

Watchdog Timer Enable
FWDTEN = OFF	Watchdog timer enabled/disabled by user software
FWDTEN = ON	Watchdog timer always enabled

POR Timer Value
FPWRT = PWR1	Disabled
FPWRT = PWR2	2ms
FPWRT = PWR4	4ms
FPWRT = PWR8	8ms
FPWRT = PWR16	16ms
FPWRT = PWR32	32ms
FPWRT = PWR64	64ms
FPWRT = PWR128	128ms

Alternate I2C pins
ALTI2C = ON	I2C mapped to ASDA1/ASCL1 pins
ALTI2C = OFF	I2C mapped to SDA1/SCL1 pins

Motor Control PWM Low Side Polarity bit
LPOL = OFF	PWM module low side output pins have active-low output polarity
LPOL = ON	PWM module low side output pins have active-high output polarity

Motor Control PWM High Side Polarity bit
HPOL = OFF	PWM module high side output pins have active-low output polarity
HPOL = ON	PWM module high side output pins have active-high output polarity

Motor Control PWM Module Pin Mode bit
PWMPIN = OFF	PWM module pins controlled by PWM module at device Reset
PWMPIN = ON	PWM module pins controlled by PORT register at device Reset

Comm Channel Select
ICS = PGD3	Communicate on PGC3/EMUC3 and PGD3/EMUD3
ICS = PGD2	Communicate on PGC2/EMUC2 and PGD2/EMUD2
ICS = PGD1	Communicate on PGC1/EMUC1 and PGD1/EMUD1

JTAG Port Enable
JTAGEN = OFF	JTAG is Disabled
JTAGEN = ON	JTAG is Enabled
*/		

//config bits for //PIC24FV08KM102/202/204, PIC24FV16KM102/104/202/204, PIC24F08KM102/202/204, PIC24F16KM102/104/202/204
//chip used on microstick I/II
#elif 	defined(__PIC24FV08KM102__) | defined(__PIC24FV08KM202__) | defined(__PIC24FV16KM102__) | defined(__PIC24FV16KM202__) | defined(__PIC24F08KM102__)  | defined (__PIC24F08KM202__)  | defined(__PIC24F16KM102__)  | defined (__PIC24F16KM202__) | \
		defined(__PIC24FV08KM204__) | defined(__PIC24FV16KM104__) | defined(__PIC24FV16KM204__) | defined(__PIC24F08KM204__)  | defined(__PIC24F16KM104__) | defined(__PIC24F16KM204__)

#pragma config BWRP = OFF
#pragma config BSS = OFF
#pragma config GWRP = OFF
#pragma config GCP = OFF
#pragma config FNOSC = PRI			//PRI, PRIPLL, FRC, FRCPLL, SOSC, LPRC, LPFRC, FRCDIV
#pragma config SOSCSRC = DIG
#pragma config LPRCSEL = HP
#pragma config IESO = OFF
#pragma config POSCMOD = HS			//EC, HS, XT, NONE
#pragma config OSCIOFNC = IO
#pragma config POSCFREQ = HS			//HS (>8Mhz), MS, LS (<100K)
#pragma config SOSCSEL = SOSCLP
#pragma config FCKSM = CSDCMD
#pragma config WDTPS = PS32768
#pragma config FWPSA = PR128
#pragma config FWDTEN = OFF
#pragma config WINDIS = OFF
#pragma config BOREN = BOR0
#pragma config RETCFG = OFF
#pragma config PWRTEN = OFF
#pragma config I2C1SEL = PRI
#pragma config BORV = V18
#pragma config MCLRE = OFF
#pragma config ICS = PGx1			//PGx1, PGx2, PGx3

/*
Boot Segment Write Protect
BWRP = ON	Enabled
BWRP = OFF	Disabled

Boot segment Protect
BSS = HI2K	High Security Boot Protect 000200h - 0015FEh
BSS = HI1K	High Security Boot Protect 000200h - 000AFEh
BSS = STD2K	Standard Security Boot Protect 000200h - 0015FEh
BSS = STD1K	Standard Security Boot Protect 000200h - 000AFEh
BSS = OFF	No boot program flash segment

General Segment Write Protect
GWRP = ON	General segment is write-protected
GWRP = OFF	General segment may be written

General Segment Code Protect
GCP = ON	Standard security enabled
GCP = OFF	No Protection

Oscillator Select
FNOSC = FRC	Fast RC Oscillator (FRC)
FNOSC = FRCPLL	Fast RC Oscillator with Postscaler and PLL Module (FRCDIV+PLL)
FNOSC = PRI	Primary Oscillator (XT, HS, EC)
FNOSC = PRIPLL	Primary oscillator with PLL Module (HS+PLL, EC+PLL)
FNOSC = SOSC	Secondary oscillator (SOSC)
FNOSC = LPRC	Low Power RC oscillator (LPRC)
FNOSC = LPFRC	500kHz Low-Power FRC oscillator with Postscaler(LPFRCDIV)
FNOSC = FRCDIV	8MHz FRC oscillator With Postscaler (FRCDIV)

SOSC Source Type
SOSCSRC = DIG	Digital Mode for use with external source
SOSCSRC = ANA	Analog Mode for use with crystal

LPRC Oscillator Power and Accuracy
LPRCSEL = LP	Low Power, Low Accuracy Mode
LPRCSEL = HP	High Power, High Accuracy Mode

Internal External Switch Over bit
IESO = OFF	Internal External Switchover mode disabled (Two-speed Start-up disabled)
IESO = ON	Internal External Switchover mode enabled (Two-speed Start-up enabled)

Primary Oscillator Configuration bits
POSCMOD = EC	External clock mode selected
POSCMOD = XT	XT oscillator mode selected
POSCMOD = HS	HS oscillator mode selected
POSCMOD = NONE	Primary oscillator disabled

CLKO Enable Configuration bit
OSCIOFNC = IO	Port I/O enabled (CLKO disabled)
OSCIOFNC = CLKO	CLKO output signal enabled

Primary Oscillator Frequency Range Configuration bits
POSCFREQ = LS	Primary oscillator/external clock input frequency less than 100kHz
POSCFREQ = MS	Primary oscillator/external clock input frequency between 100kHz and 8MHz
POSCFREQ = HS	Primary oscillator/external clock input frequency greater than 8MHz

SOSC Power Selection Configuration bits
SOSCSEL = SOSCLP	Secondary Oscillator configured for low-power operation
SOSCSEL = SOSCHP	Secondary Oscillator configured for high-power operation

Clock Switching and Monitor Selection
FCKSM = CSECME	Both Clock Switching and Fail-safe Clock Monitor are enabled
FCKSM = CSECMD	Clock Switching is enabled, Fail-safe Clock Monitor is disabled
FCKSM = CSDCMD	Both Clock Switching and Fail-safe Clock Monitor are disabled

Watchdog Timer Postscale Select bits
WDTPS = PS1	1 : 1
WDTPS = PS2	1 : 2
WDTPS = PS4	1 : 4
WDTPS = PS8	1 : 8
WDTPS = PS16	1 : 16
WDTPS = PS32	1 : 32
WDTPS = PS64	1 : 64
WDTPS = PS128	1 : 128
WDTPS = PS256	1 : 256
WDTPS = PS512	1 : 512
WDTPS = PS1024	1 : 1024
WDTPS = PS2048	1 : 2048
WDTPS = PS4096	1 : 4096
WDTPS = PS8192	1 : 8192
WDTPS = PS16384	1 : 16384
WDTPS = PS32768	1 : 32768

WDT Prescaler bit
FWPSA = PR32	WDT prescaler ratio of 1 : 32
FWPSA = PR128	WDT prescaler ratio of 1 : 128

Watchdog Timer Enable bits
FWDTEN = OFF	WDT disabled in hardware; SWDTEN bit disabled
FWDTEN = NOSLP	WDT enabled while device is active and disabled in Sleep; SWDTEN bit disabled
FWDTEN = SWON	WDT controlled with the SWDTEN bit setting
FWDTEN = ON	WDT enabled in hardware

Windowed Watchdog Timer Disable bit
WINDIS = ON	Windowed WDT enabled
WINDIS = OFF	Standard WDT selected(windowed WDT disabled)

Brown-out Reset Enable bits
BOREN = BOR0	Brown-out Reset disabled in hardware, SBOREN bit disabled
BOREN = BOR1	Brown-out Rest controlled by SBOREN bit
BOREN = BOR2	Brown-out Reset enabled only while device is active and disabled in SLEEP, SBOREN bit disabled
BOREN = BOR3	Brown-out Reset enabled in hardware, SBOREN bit disabled

RETCFG = ON	Retention regulator is available and controlled by RETEN bit
RETCFG = OFF	Retention regulator is not available

Power-up Timer Enable bit
PWRTEN = OFF	PWRT disabled
PWRTEN = ON	PWRT enabled

Alternate I2C1 Pin Mapping bit
I2C1SEL = SEC	Use Alternate ASCL1/ASDA1 Pins For I2C1
I2C1SEL = PRI	Use Default SCL1/SDA1 Pins For I2C1

Brown-out Reset Voltage bits
BORV = LPBOR	Low-power Brown-Out Reset occurs around 2.0V
BORV = V30	Brown-out Reset set to Highest Voltage (3.0V)
BORV = V27	Brown-out Reset set at 2.7V
BORV = V18	Brown-out Reset set to lowest voltage (1.8V)

MCLR Pin Enable bit
MCLRE = OFF	RA5 input pin enabled, MCLR disabled
MCLRE = ON	RA5 input pin disabled, MCLR pin enabled

ICD Pin Placement Select bits
ICS = PGx3	EMUC/EMUD share PGC3/PGD3
ICS = PGx2	EMUC/EMUD share PGC2/PGD2
ICS = PGx1	EMUC/EMUD share PGC1/PGD1
*/
#else
//no header file found
#warning no device header file specified
#endif

#endif	//config__
