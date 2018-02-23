/* 
 * File:   config.h
 * Author: Ken
 *
 * Created on March 29, 2014, 4:32 PM
 */

#ifndef __CONFIG_H
#define	__CONFIG_H

#include <p32xxxx.h>							//p32xxxx.h included here

//configuration settings
//PIC32MX110/120/130/150/170, PIC32MX210/220/230/250/270

#if   	defined(__32MX110F016B_H) || defined(__32MX110F016C_H) || defined(__32MX110F016D_H) || \
		defined(__32MX120F032B_H) || defined(__32MX120F032C_H) || defined(__32MX120F032D_H) || defined(__32MX120F064H_H) || \
		defined(__32MX130F064B_H) || defined(__32MX130F064C_H) || defined(__32MX130F064D_H) || defined(__32MX130F128H_H) || defined(__32MX130F128L_H) || \
		defined(__32MX150F128B_H) || defined(__32MX150F128C_H) || defined(__32MX150F128D_H) || defined(__32MX150F256H_H) || defined(__32MX150F256L_H) || \
		defined(__32MX170F256B_H) || defined(__32MX170F256D_H) || defined(__32MX170F256H_H) || defined(__32MX170F256L_H) || \
		defined(__32MX210F016B_H) || defined(__32MX210F016C_H) || defined(__32MX210F016D_H) || \
		defined(__32MX220F032B_H) || defined(__32MX220F032C_H) || defined(__32MX220F032D_H) || \
		defined(__32MX230F064B_H) || defined(__32MX230F064C_H) || defined(__32MX230F064D_H) || defined(__32MX230F128H_H) || defined(__32MX230F128L_H) || \
		defined(__32MX250F128B_H) || defined(__32MX250F128C_H) || defined(__32MX250F128D_H) || defined(__32MX250F256H_H) || defined(__32MX250F256L_H) || \
		defined(__32MX270F256B_H) || defined(__32MX270F256D_H) || defined(__32MX270F256H_H) || defined(__32MX270F256L_H)

#pragma config FNOSC = FRC						//oscillator selection bits = FRC/FRCPLL/PRI/PRIPLL/SOSC/LPRC/FRCDIV16/FRCDIV, 
#pragma config FSOSCEN = OFF					//secondary oscillator off
#pragma config IESO = OFF						//internal/external switch-over
#pragma config POSCMOD = HS						//primary oscilator configuration = OFF/HS/XT/EC
//PLL configuration.
//F_SYSCLK = F_OSC / FPLLIDIV * FPLLMUL / FPLLODIV.
#pragma config FPLLIDIV = DIV_2					//PLL input divider=DIV_1/2/3/4/5/6/10/12 (4Mhz < F_OSC / FPLLIDIV < 5Mhz)
#pragma config FPLLMUL = MUL_16					//PLL multiplier=MUL_15/16/17/18/19/20/21/24
#pragma config FPLLODIV = DIV_2					//PLL output divider=DIV_1/2/4/8/16/32/64/256
//end PLL configuration
//F_PBDIV = F_SYSCLK / FPBDIV
#pragma config FPBDIV = DIV_8					//peripheral bus clock divider = 8x
#pragma config OSCIOFNC = OFF, FCKSM = CSECMD	//clock output disabled, clock switching disabled
#pragma config ICESEL = RESERVED				//use PGD1/PGC1, 
#pragma config PMDL1WAY = OFF, IOL1WAY = OFF	//peripheral configuration allows multiple configuration (OFF) or one configuration (ON), PPS allows multiple configuration (OFF)/one configuration(ON)
#pragma config FUSBIDIO = OFF, FVBUSONIO = OFF	//USBID pin controoled by port functions (OFF)/or USB module (ON), Vbuson pin controlled by port function (OFF)/USB module (ON)
#pragma config FWDTEN = OFF, WDTPS = PS32768	//watchdog timer disabled, watchdog timer prescaler = 32768
#pragma config WINDIS = OFF, FWDTWINSZ = WINSZ_75		//watchdog timer window disabled, watchdog timer window size =75%
#pragma config PWP = OFF, BWP = OFF, CP = OFF	//boot flash write-protection off, power-on protection off, code protection off
//#pragma config DEBUG = OFF					//OFF = debugger disabled. ON = debugger enabled -> *****needs to be unchecked to run code under pic32prog + pickit2*****
#pragma config JTAGEN = OFF						//jtag off

//set up usb divider
#if		defined(__32MX210F016B_H) || defined(__32MX210F016C_H) || defined(__32MX210F016D_H) || \
		defined(__32MX220F032B_H) || defined(__32MX220F032C_H) || defined(__32MX220F032D_H) || \
		defined(__32MX230F064B_H) || defined(__32MX230F064C_H) || defined(__32MX230F064D_H) || defined(__32MX230F128H_H) || defined(__32MX230F128L_H) || \
		defined(__32MX250F128B_H) || defined(__32MX250F128C_H) || defined(__32MX250F128D_H) || defined(__32MX250F256H_H) || defined(__32MX250F256L_H) || \
		defined(__32MX270F256B_H) || defined(__32MX270F256D_H) || defined(__32MX270F256H_H) || defined(__32MX270F256L_H)
#pragma config UPLLIDIV = DIV_1, UPLLEN = OFF	//USB PLL div=1, USB PLL enable=off/on
#endif

/*PIC32MX130F064B
Peripheral Module Disable Configuration:
 PMDL1WAY = OFF Allow multiple reconfigurations
PMDL1WAY = ON Allow only one reconfiguration

Peripheral Pin Select Configuration:
 IOL1WAY = OFF Allow multiple reconfigurations
IOL1WAY = ON Allow only one reconfiguration

USB USID Selection:
 FUSBIDIO = OFF Controlled by Port Function
FUSBIDIO = ON Controlled by the USB Module

USB VBUS ON Selection:
 FVBUSONIO = OFF Controlled by Port Function
FVBUSONIO = ON Controlled by USB Module

PLL Input Divider:
 FPLLIDIV = DIV_1 1x Divider
FPLLIDIV = DIV_2 2x Divider
FPLLIDIV = DIV_3 3x Divider
FPLLIDIV = DIV_4 4x Divider
FPLLIDIV = DIV_5 5x Divider
FPLLIDIV = DIV_6 6x Divider
FPLLIDIV = DIV_10 10x Divider
FPLLIDIV = DIV_12 12x Divider

PLL Multiplier:
 FPLLMUL = MUL_15 15x Multiplier
FPLLMUL = MUL_16 16x Multiplier
FPLLMUL = MUL_17 17x Multiplier
FPLLMUL = MUL_18 18x Multiplier
FPLLMUL = MUL_19 19x Multiplier
FPLLMUL = MUL_20 20x Multiplier
FPLLMUL = MUL_21 21x Multiplier
FPLLMUL = MUL_24 24x Multiplier

System PLL Output Clock Divider:
 FPLLODIV = DIV_1 PLL Divide by 1
FPLLODIV = DIV_2 PLL Divide by 2
FPLLODIV = DIV_4 PLL Divide by 4
FPLLODIV = DIV_8 PLL Divide by 8
FPLLODIV = DIV_16 PLL Divide by 16
FPLLODIV = DIV_32 PLL Divide by 32
FPLLODIV = DIV_64 PLL Divide by 64
FPLLODIV = DIV_256 PLL Divide by 256

Oscillator Selection Bits:
 FNOSC = FRC Fast RC Osc (FRC)
FNOSC = FRCPLL Fast RC Osc with PLL
FNOSC = PRI Primary Osc (XT,HS,EC)
FNOSC = PRIPLL Primary Osc w/PLL (XT+,HS+,EC+PLL)
FNOSC = SOSC Low Power Secondary Osc (SOSC)
FNOSC = LPRC Low Power RC Osc (LPRC)
FNOSC = FRCDIV16 Fast RC Osc w/Div-by-16 (FRC/16)
FNOSC = FRCDIV Fast RC Osc w/Div-by-N (FRCDIV)

Secondary Oscillator Enable:
 FSOSCEN = OFF Disabled
FSOSCEN = ON Enabled

Internal/External Switch Over:
 IESO = OFF Disabled
IESO = ON Enabled

Primary Oscillator Configuration:
 POSCMOD = EC External clock mode
POSCMOD = XT XT osc mode
POSCMOD = HS HS osc mode
POSCMOD = OFF Primary osc disabled

CLKO Output Signal Active on the OSCO Pin:
 OSCIOFNC = ON Enabled
OSCIOFNC = OFF Disabled

Peripheral Clock Divisor:
 FPBDIV = DIV_1 Pb_Clk is Sys_Clk/1
FPBDIV = DIV_2 Pb_Clk is Sys_Clk/2
FPBDIV = DIV_4 Pb_Clk is Sys_Clk/4
FPBDIV = DIV_8 Pb_Clk is Sys_Clk/8

Clock Switching and Monitor Selection:
 FCKSM = CSECME Clock Switch Enable, FSCM Enabled
FCKSM = CSECMD Clock Switch Enable, FSCM Disabled
FCKSM = CSDCMD Clock Switch Disable, FSCM Disabled

Watchdog Timer Postscaler:
 WDTPS = PS1 1:1
WDTPS = PS2 1:2
WDTPS = PS4 1:4
WDTPS = PS8 1:8
WDTPS = PS16 1:16
WDTPS = PS32 1:32
WDTPS = PS64 1:64
WDTPS = PS128 1:128
WDTPS = PS256 1:256
WDTPS = PS512 1:512
WDTPS = PS1024 1:1024
WDTPS = PS2048 1:2048
WDTPS = PS4096 1:4096
WDTPS = PS8192 1:8192
WDTPS = PS16384 1:16384
WDTPS = PS32768 1:32768
WDTPS = PS65536 1:65536
WDTPS = PS131072 1:131072
WDTPS = PS262144 1:262144
WDTPS = PS524288 1:524288
WDTPS = PS1048576 1:1048576

Watchdog Timer Window Enable:
 WINDIS = ON Watchdog Timer is in Window Mode
WINDIS = OFF Watchdog Timer is in Non-Window Mode

Watchdog Timer Enable:
 FWDTEN = OFF WDT Disabled (SWDTEN Bit Controls)
FWDTEN = ON WDT Enabled

Watchdog Timer Window Size:
 FWDTWINSZ = WINSZ_75 Window Size is 75%
FWDTWINSZ = WINSZ_50 Window Size is 50%
FWDTWINSZ = WINSZ_37 Window Size is 37.5%
FWDTWINSZ = WISZ_25 Window Size is 25%

Background Debugger Enable:
 DEBUG = ON Debugger is Enabled
DEBUG = OFF Debugger is Disabled

JTAG Enable:
 JTAGEN = OFF JTAG Disabled
JTAGEN = ON JTAG Port Enabled

ICE/ICD Comm Channel Select:
 ICESEL = RESERVED Reserved
ICESEL = ICS_PGx3 Communicate on PGEC3/PGED3
ICESEL = ICS_PGx2 Communicate on PGEC2/PGED2
ICESEL = ICS_PGx1 Communicate on PGEC1/PGED1

Program Flash Write Protect:
 PWP = PWP32K First 32K
PWP = PWP31K First 31K
PWP = PWP30K First 30K
PWP = PWP29K First 29K
PWP = PWP28K First 28K
PWP = PWP27K First 27K
PWP = PWP26K First 26K
PWP = PWP25K First 25K
PWP = PWP24K First 24K
PWP = PWP23K First 23K
PWP = PWP22K First 22K
PWP = PWP21K First 21K
PWP = PWP20K First 20K
PWP = PWP19K First 19K
PWP = PWP18K First 18K
PWP = PWP17K First 17K
PWP = PWP16K First 16K
PWP = PWP15K First 15K
PWP = PWP14K First 14K
PWP = PWP13K First 13K
PWP = PWP12K First 12K
PWP = PWP11K First 11K
PWP = PWP10K First 10K
PWP = PWP9K First 9K
PWP = PWP8K First 8K
PWP = PWP7K First 7K
PWP = PWP6K First 6K
PWP = PWP5K First 5K
PWP = PWP4K First 4K
PWP = PWP3K First 3K
PWP = PWP2K First 2K
PWP = PWP1K First 1K
PWP = OFF Disable

Boot Flash Write Protect bit:
 BWP = ON Protection Enabled
BWP = OFF Protection Disabled

Code Protect:
 CP = ON Protection Enabled
CP = OFF Protection Disabled
*/

//PIC32MX320/340/360/420/440/460
#elif 		defined(__32MX320F032H_H) || defined(__32MX320F064H_H) || defined(__32MX320F128H_H) || defined(__32MX320F128L_H) || \
			defined(__32MX340F128H_H) || defined(__32MX340F128L_H) || defined(__32MX340F256H_H) || defined(__32MX340F256L_H) || \
			defined(__32MX360F256L_H) || defined(__32MX360F512L_H) || \
			defined(__32MX420F032H_H) || \
			defined(__32MX440F128H_H) || defined(__32MX440F128L_H) || defined(__32MX440F256H_H) || defined(__32MX440F512H_H) || \
			defined(__32MX460F512L_H) || defined(__32MX460F512L_H)
			
#pragma config FNOSC = FRC, FSOSCEN = OFF		//oscillator selection bits = FRC/FRCPLL/PRI/PRIPLL/SOSC/LPRC/FRCDIV16/FRCDIV, secondary oscillator off
#pragma config IESO = OFF						//internal/external switch-over
#pragma config POSCMOD = HS						//primary oscilator configuration = OFF/HS/XT/EC
//PLL configuration.
//F_SYSCLK = F_OSC / FPLLIDIV * FPLLMUL / FPLLODIV.
#pragma config FPLLIDIV = DIV_2					//PLL input divider=1/2/3/4/5/6/10/12 (4Mhz < F_OSC / FPLLIDIV < 5Mhz)
#pragma config FPLLMUL = MUL_16					//PLL multiplier=15/16/17/18/19/20/21/24
#pragma config FPLLODIV = DIV_2					//PLL output divider=1/2/4/8/16/32/64/256
//end PLL configuration
//F_PBDIV = F_SYSCLK / FPBDIV
#pragma config FPBDIV = DIV_1					//peripheral bus clock divider = 1x
#pragma config OSCIOFNC = OFF, FCKSM = CSDCMD	//clock output disabled, clock switching disabled
//#pragma config ICESEL = RESERVED				//use PGD1/PGC1, 
//#pragma config PMDL1WAY = OFF, IOL1WAY = OFF	//peripheral configuration allows multiple configuration (OFF) or one configuration (ON), PPS allows multiple configuration (OFF)/one configuration(ON)
//#pragma config FUSBIDIO = OFF, FVBUSONIO = OFF	//USBID pin controoled by port functions (OFF)/or USB module (ON), Vbuson pin controlled by port function (OFF)/USB module (ON)
#pragma config FWDTEN = OFF, WDTPS = PS32768	//watchdog timer disabled, watchdog timer prescaler = 32768
//#pragma config WINDIS = OFF, FWDTWINSZ = WINSZ_75		//watchdog timer window disabled, watchdog timer window size =75%
#pragma config PWP = OFF, BWP = OFF, CP = OFF	//boot flash write-protection off, power-on protection off, code protection off
//#pragma config DEBUG = OFF					//OFF = debugger disabled. ON = debugger enabled -> *****needs to be unchecked to run code under pic32prog + pickit2*****
//#pragma config JTAGEN = OFF						//jtag off

/*PIC32MX320F032H
PLL Input Divider:
 FPLLIDIV = DIV_1 1x Divider  
FPLLIDIV = DIV_2 2x Divider  
FPLLIDIV = DIV_3 3x Divider  
FPLLIDIV = DIV_4 4x Divider  
FPLLIDIV = DIV_5 5x Divider  
FPLLIDIV = DIV_6 6x Divider  
FPLLIDIV = DIV_10 10x Divider  
FPLLIDIV = DIV_12 12x Divider  

PLL Multiplier:
 FPLLMUL = MUL_15 15x Multiplier  
FPLLMUL = MUL_16 16x Multiplier  
FPLLMUL = MUL_17 17x Multiplier  
FPLLMUL = MUL_18 18x Multiplier  
FPLLMUL = MUL_19 19x Multiplier  
FPLLMUL = MUL_20 20x Multiplier  
FPLLMUL = MUL_21 21x Multiplier  
FPLLMUL = MUL_24 24x Multiplier  

System PLL Output Clock Divider:
 FPLLODIV = DIV_1 PLL Divide by 1  
FPLLODIV = DIV_2 PLL Divide by 2  
FPLLODIV = DIV_4 PLL Divide by 4  
FPLLODIV = DIV_8 PLL Divide by 8  
FPLLODIV = DIV_16 PLL Divide by 16  
FPLLODIV = DIV_32 PLL Divide by 32  
FPLLODIV = DIV_64 PLL Divide by 64  
FPLLODIV = DIV_256 PLL Divide by 256  

Oscillator Selection Bits:
 FNOSC = FRC Fast RC Osc (FRC)  
FNOSC = FRCPLL Fast RC Osc with PLL  
FNOSC = PRI Primary Osc (XT,HS,EC)  
FNOSC = PRIPLL Primary Osc w/PLL (XT+,HS+,EC+PLL)  
FNOSC = SOSC Low Power Secondary Osc (SOSC)  
FNOSC = LPRC Low Power RC Osc (LPRC)  
FNOSC = FRCDIV16 Fast RC Osc w/Div-by-16 (FRC/16)  
FNOSC = FRCDIV Fast RC Osc w/Div-by-N (FRCDIV)  

Secondary Oscillator Enable:
 FSOSCEN = OFF Disabled  
FSOSCEN = ON Enabled  

Internal/External Switch Over:
 IESO = OFF Disabled  
IESO = ON Enabled  

Primary Oscillator Configuration:
 POSCMOD = EC External clock mode  
POSCMOD = XT XT osc mode  
POSCMOD = HS HS osc mode  
POSCMOD = OFF Primary osc disabled  

CLKO Output Signal Active on the OSCO Pin:
 OSCIOFNC = OFF Disabled  
OSCIOFNC = ON Enabled  

Peripheral Clock Divisor:
 FPBDIV = DIV_1 Pb_Clk is Sys_Clk/1  
FPBDIV = DIV_2 Pb_Clk is Sys_Clk/2  
FPBDIV = DIV_4 Pb_Clk is Sys_Clk/4  
FPBDIV = DIV_8 Pb_Clk is Sys_Clk/8  

Clock Switching and Monitor Selection:
 FCKSM = CSECME Clock Switch Enable, FSCM Enabled  
FCKSM = CSECMD Clock Switch Enable, FSCM Disabled  
FCKSM = CSDCMD Clock Switch Disable, FSCM Disabled  

Watchdog Timer Postscaler:
 WDTPS = PS1 1:1  
WDTPS = PS2 1:2  
WDTPS = PS4 1:4  
WDTPS = PS8 1:8  
WDTPS = PS16 1:16  
WDTPS = PS32 1:32  
WDTPS = PS64 1:64  
WDTPS = PS128 1:128  
WDTPS = PS256 1:256  
WDTPS = PS512 1:512  
WDTPS = PS1024 1:1024  
WDTPS = PS2048 1:2048  
WDTPS = PS4096 1:4096  
WDTPS = PS8192 1:8192  
WDTPS = PS16384 1:16384  
WDTPS = PS32768 1:32768  
WDTPS = PS65536 1:65536  
WDTPS = PS131072 1:131072  
WDTPS = PS262144 1:262144  
WDTPS = PS524288 1:524288  
WDTPS = PS1048576 1:1048576  

Watchdog Timer Enable:
 FWDTEN = OFF WDT Disabled (SWDTEN Bit Controls)  
FWDTEN = ON WDT Enabled  

Background Debugger Enable:
 DEBUG = ON Debugger is enabled  
DEBUG = OFF Debugger is disabled  

ICE/ICD Comm Channel Select:
 ICESEL = ICS_PGx1 ICE EMUC1/EMUD1 pins shared with PGC1/PGD1  
ICESEL = ICS_PGx2 ICE EMUC2/EMUD2 pins shared with PGC2/PGD2  

Program Flash Write Protect:
 PWP = PWP512K First 512K  
PWP = PWP508K First 508K  
PWP = PWP504K First 504K  
PWP = PWP500K First 500K  
PWP = PWP496K First 496K  
PWP = PWP492K First 492K  
PWP = PWP488K First 488K  
PWP = PWP484K First 484K  
PWP = PWP480K First 480K  
PWP = PWP476K First 476K  
PWP = PWP472K First 472K  
PWP = PWP468K First 468K  
PWP = PWP464K First 464K  
PWP = PWP460K First 460K  
PWP = PWP456K First 456K  
PWP = PWP452K First 452K  
PWP = PWP448K First 448K  
PWP = PWP444K First 444K  
PWP = PWP440K First 440K  
PWP = PWP436K First 436K  
PWP = PWP432K First 432K  
PWP = PWP428K First 428K  
PWP = PWP424K First 424K  
PWP = PWP420K First 420K  
PWP = PWP416K First 416K  
PWP = PWP412K First 412K  
PWP = PWP408K First 408K  
PWP = PWP404K First 404K  
PWP = PWP400K First 400K  
PWP = PWP396K First 396K  
PWP = PWP392K First 392K  
PWP = PWP388K First 388K  
PWP = PWP384K First 384K  
PWP = PWP380K First 380K  
PWP = PWP376K First 376K  
PWP = PWP372K First 372K  
PWP = PWP368K First 368K  
PWP = PWP364K First 364K  
PWP = PWP360K First 360K  
PWP = PWP356K First 356K  
PWP = PWP352K First 352K  
PWP = PWP348K First 348K  
PWP = PWP344K First 344K  
PWP = PWP340K First 340K  
PWP = PWP336K First 336K  
PWP = PWP332K First 332K  
PWP = PWP328K First 328K  
PWP = PWP324K First 324K  
PWP = PWP320K First 320K  
PWP = PWP316K First 316K  
PWP = PWP312K First 312K  
PWP = PWP308K First 308K  
PWP = PWP304K First 304K  
PWP = PWP300K First 300K  
PWP = PWP296K First 296K  
PWP = PWP292K First 292K  
PWP = PWP288K First 288K  
PWP = PWP284K First 284K  
PWP = PWP280K First 280K  
PWP = PWP276K First 276K  
PWP = PWP272K First 272K  
PWP = PWP268K First 268K  
PWP = PWP264K First 264K  
PWP = PWP260K First 260K  
PWP = PWP256K First 256K  
PWP = PWP252K First 252K  
PWP = PWP248K First 248K  
PWP = PWP244K First 244K  
PWP = PWP240K First 240K  
PWP = PWP236K First 236K  
PWP = PWP232K First 232K  
PWP = PWP228K First 228K  
PWP = PWP224K First 224K  
PWP = PWP220K First 220K  
PWP = PWP216K First 216K  
PWP = PWP212K First 212K  
PWP = PWP208K First 208K  
PWP = PWP204K First 204K  
PWP = PWP200K First 200K  
PWP = PWP196K First 196K  
PWP = PWP192K First 192K  
PWP = PWP188K First 188K  
PWP = PWP184K First 184K  
PWP = PWP180K First 180K  
PWP = PWP176K First 176K  
PWP = PWP172K First 172K  
PWP = PWP168K First 168K  
PWP = PWP164K First 164K  
PWP = PWP160K First 160K  
PWP = PWP156K First 156K  
PWP = PWP152K First 152K  
PWP = PWP148K First 148K  
PWP = PWP144K First 144K  
PWP = PWP140K First 140K  
PWP = PWP136K First 136K  
PWP = PWP132K First 132K  
PWP = PWP128K First 128K  
PWP = PWP124K First 124K  
PWP = PWP120K First 120K  
PWP = PWP116K First 116K  
PWP = PWP112K First 112K  
PWP = PWP108K First 108K  
PWP = PWP104K First 104K  
PWP = PWP100K First 100K  
PWP = PWP96K First 96K  
PWP = PWP92K First 92K  
PWP = PWP88K First 88K  
PWP = PWP84K First 84K  
PWP = PWP80K First 80K  
PWP = PWP76K First 76K  
PWP = PWP72K First 72K  
PWP = PWP68K First 68K  
PWP = PWP64K First 64K  
PWP = PWP60K First 60K  
PWP = PWP56K First 56K  
PWP = PWP52K First 52K  
PWP = PWP48K First 48K  
PWP = PWP44K First 44K  
PWP = PWP40K First 40K  
PWP = PWP36K First 36K  
PWP = PWP32K First 32K  
PWP = PWP28K First 28K  
PWP = PWP24K First 24K  
PWP = PWP20K First 20K  
PWP = PWP16K First 16K  
PWP = PWP12K First 12K  
PWP = PWP8K First 8K  
PWP = PWP4K First 4K  
PWP = OFF Disable  

Boot Flash Write Protect bit:
 BWP = ON Protection Enabled  
BWP = OFF Protection Disabled  

Code Protect:
 CP = ON Protection Enabled  
CP = OFF Protection Disabled  
*/

//PIC32MX330/350/370/430/450/470
#elif 		defined(__32MX330F064H_H) || defined(__32MX330F064L_H) || \
			defined(__32MX350F128H_H) || defined(__32MX350F128L_H) || defined(__32MX350F256H_H) || defined(__32MX350F256L_H) || \
			defined(__32MX370F256L_H) || defined(__32MX370F512L_H) || \
			defined(__32MX430F064H_H) || defined(__32MX430F064L_H) || \
			defined(__32MX450F128H_H) || defined(__32MX450F128L_H) || defined(__32MX450F256H_H) || defined(__32MX450F256L_H) || \
			defined(__32MX470F512L_H) || defined(__32MX470F512L_H)
			
#pragma config FNOSC = FRC, FSOSCEN = OFF		//oscillator selection bits = FRC/FRCPLL/PRI/PRIPLL/SOSC/LPRC/FRCDIV16/FRCDIV, secondary oscillator off
#pragma config IESO = OFF						//internal/external switch-over
#pragma config POSCMOD = HS						//primary oscilator configuration = OFF/HS/XT/EC
//PLL configuration.
//F_SYSCLK = F_OSC / FPLLIDIV * FPLLMUL / FPLLODIV.
#pragma config FPLLIDIV = DIV_2					//PLL input divider=1/2/3/4/5/6/10/12 (4Mhz < F_OSC / FPLLIDIV < 5Mhz)
#pragma config FPLLMUL = MUL_16					//PLL multiplier=15/16/17/18/19/20/21/24
#pragma config FPLLODIV = DIV_2					//PLL output divider=1/2/4/8/16/32/64/256
//end PLL configuration
//F_PBDIV = F_SYSCLK / FPBDIV
#pragma config FPBDIV = DIV_1					//peripheral bus clock divider = 1x
#pragma config OSCIOFNC = OFF, FCKSM = CSDCMD	//clock output disabled, clock switching disabled
//#pragma config ICESEL = RESERVED				//use PGD1/PGC1, 
#pragma config PMDL1WAY = OFF, IOL1WAY = OFF	//peripheral configuration allows multiple configuration (OFF) or one configuration (ON), PPS allows multiple configuration (OFF)/one configuration(ON)
//#pragma config FUSBIDIO = OFF, FVBUSONIO = OFF	//USBID pin controoled by port functions (OFF)/or USB module (ON), Vbuson pin controlled by port function (OFF)/USB module (ON)
#pragma config FWDTEN = OFF, WDTPS = PS32768	//watchdog timer disabled, watchdog timer prescaler = 32768
#pragma config WINDIS = OFF, FWDTWINSZ = WINSZ_75		//watchdog timer window disabled, watchdog timer window size =75%
#pragma config PWP = OFF, BWP = OFF, CP = OFF	//boot flash write-protection off, power-on protection off, code protection off
//#pragma config DEBUG = OFF					//OFF = debugger disabled. ON = debugger enabled -> *****needs to be unchecked to run code under pic32prog + pickit2*****
#pragma config JTAGEN = OFF						//jtag off
#pragma config FSRSSEL = PRIORITY_7

/*Configuration-Bit Settings for PIC32MX470F512L
(Data Sheet # DS-61185)

Usage:
#pragma config SETTING = VALUE


Shadow Register Set Priority Select (FSRSSEL) 
FSRSSEL = PRIORITY_0 SRS Priority 0  
FSRSSEL = PRIORITY_1 SRS Priority 1  
FSRSSEL = PRIORITY_2 SRS Priority 2  
FSRSSEL = PRIORITY_3 SRS Priority 3  
FSRSSEL = PRIORITY_4 SRS Priority 4  
FSRSSEL = PRIORITY_5 SRS Priority 5  
FSRSSEL = PRIORITY_6 SRS Priority 6  
FSRSSEL = PRIORITY_7 SRS Priority 7  


Peripheral Module Disable Configuration () 
PMDL1WAY = ON Allow only one reconfiguration  
PMDL1WAY = OFF Allow multiple reconfigurations  


Peripheral Pin Select Configuration (IOL1WAY) 
IOL1WAY = ON Allow only one reconfiguration  
IOL1WAY = OFF Allow multiple reconfigurations  


USB USID Selection (FUSBIDIO) 
FUSBIDIO = OFF Controlled by Port Function  
FUSBIDIO = ON Controlled by the USB Module  


USB VBUS ON Selection (FVBUSONIO) 
FVBUSONIO = OFF Controlled by Port Function  
FVBUSONIO = ON Controlled by USB Module  


PLL Input Divider (FPLLIDIV) 
FPLLIDIV = DIV_1 1x Divider  
FPLLIDIV = DIV_2 2x Divider  
FPLLIDIV = DIV_3 3x Divider  
FPLLIDIV = DIV_4 4x Divider  
FPLLIDIV = DIV_5 5x Divider  
FPLLIDIV = DIV_6 6x Divider  
FPLLIDIV = DIV_10 10x Divider  
FPLLIDIV = DIV_12 12x Divider  


PLL Multiplier (FPLLMUL) 
FPLLMUL = MUL_15 15x Multiplier  
FPLLMUL = MUL_16 16x Multiplier  
FPLLMUL = MUL_17 17x Multiplier  
FPLLMUL = MUL_18 18x Multiplier  
FPLLMUL = MUL_19 19x Multiplier  
FPLLMUL = MUL_20 20x Multiplier  
FPLLMUL = MUL_21 21x Multiplier  
FPLLMUL = MUL_24 24x Multiplier  


USB PLL Input Divider (UPLLIDIV) 
UPLLIDIV = DIV_1 1x Divider  
UPLLIDIV = DIV_2 2x Divider  
UPLLIDIV = DIV_3 3x Divider  
UPLLIDIV = DIV_4 4x Divider  
UPLLIDIV = DIV_5 5x Divider  
UPLLIDIV = DIV_6 6x Divider  
UPLLIDIV = DIV_10 10x Divider  
UPLLIDIV = DIV_12 12x Divider  


USB PLL Enable (UPLLEN) 
UPLLEN = ON Enabled  
UPLLEN = OFF Disabled and Bypassed  


System PLL Output Clock Divider (FPLLODIV) 
FPLLODIV = DIV_1 PLL Divide by 1  
FPLLODIV = DIV_2 PLL Divide by 2  
FPLLODIV = DIV_4 PLL Divide by 4  
FPLLODIV = DIV_8 PLL Divide by 8  
FPLLODIV = DIV_16 PLL Divide by 16  
FPLLODIV = DIV_32 PLL Divide by 32  
FPLLODIV = DIV_64 PLL Divide by 64  
FPLLODIV = DIV_256 PLL Divide by 256  


Oscillator Selection Bits (FNOSC) 
FNOSC = FRC Fast RC Osc (FRC)  
FNOSC = FRCPLL Fast RC Osc with PLL  
FNOSC = PRI Primary Osc (XT,HS,EC)  
FNOSC = PRIPLL Primary Osc w/PLL (XT+,HS+,EC+PLL)  
FNOSC = SOSC Low Power Secondary Osc (SOSC)  
FNOSC = LPRC Low Power RC Osc (LPRC)  
FNOSC = FRCDIV16 Fast RC Osc w/Div-by-16 (FRC/16)  
FNOSC = FRCDIV Fast RC Osc w/Div-by-N (FRCDIV)  


Secondary Oscillator Enable (FSOSCEN) 
FSOSCEN = OFF Disabled  
FSOSCEN = ON Enabled  


Internal/External Switch Over (IESO) 
IESO = OFF Disabled  
IESO = ON Enabled  


Primary Oscillator Configuration (POSCMOD) 
POSCMOD = EC External clock mode  
POSCMOD = XT XT osc mode  
POSCMOD = HS HS osc mode  
POSCMOD = OFF Primary osc disabled  


CLKO Output Signal Active on the OSCO Pin (OSCIOFNC) 
OSCIOFNC = OFF Disabled  
OSCIOFNC = ON Enabled  


Peripheral Clock Divisor (FPBDIV) 
FPBDIV = DIV_1 Pb_Clk is Sys_Clk/1  
FPBDIV = DIV_2 Pb_Clk is Sys_Clk/2  
FPBDIV = DIV_4 Pb_Clk is Sys_Clk/4  
FPBDIV = DIV_8 Pb_Clk is Sys_Clk/8  


Clock Switching and Monitor Selection (FCKSM) 
FCKSM = CSECME Clock Switch Enable, FSCM Enabled  
FCKSM = CSECMD Clock Switch Enable, FSCM Disabled  
FCKSM = CSDCMD Clock Switch Disable, FSCM Disabled  


Watchdog Timer Postscaler (WDTPS) 
WDTPS = PS1 1:1  
WDTPS = PS2 1:2  
WDTPS = PS4 1:4  
WDTPS = PS8 1:8  
WDTPS = PS16 1:16  
WDTPS = PS32 1:32  
WDTPS = PS64 1:64  
WDTPS = PS128 1:128  
WDTPS = PS256 1:256  
WDTPS = PS512 1:512  
WDTPS = PS1024 1:1024  
WDTPS = PS2048 1:2048  
WDTPS = PS4096 1:4096  
WDTPS = PS8192 1:8192  
WDTPS = PS16384 1:16384  
WDTPS = PS32768 1:32768  
WDTPS = PS65536 1:65536  
WDTPS = PS131072 1:131072  
WDTPS = PS262144 1:262144  
WDTPS = PS524288 1:524288  
WDTPS = PS1048576 1:1048576  


Watchdog Timer Window Enable (WINDIS) 
WINDIS = ON Watchdog Timer is in Window Mode  
WINDIS = OFF Watchdog Timer is in Non-Window Mode  


Watchdog Timer Enable (FWDTEN) 
FWDTEN = OFF WDT Disabled (SWDTEN Bit Controls)  
FWDTEN = ON WDT Enabled  


Watchdog Timer Window Size (FWDTWINSZ) 
FWDTWINSZ = WINSZ_75 Window Size is 75%  
FWDTWINSZ = WINSZ_50 Window Size is 50%  
FWDTWINSZ = WINSZ_37 Window Size is 37.5%  
FWDTWINSZ = WISZ_25 Window Size is 25%  


Background Debugger Enable (DEBUG) 
DEBUG = ON Debugger is Enabled  
DEBUG = OFF Debugger is Disabled  


JTAG Enable (JTAGEN) JTAGEN = ON 
JTAG Port Enabled  
JTAGEN = OFF JTAG Disabled  


ICE/ICD Comm Channel Select (ICESEL) 
ICESEL = ICS_PGx1 Communicate on PGEC1/PGED1  
ICESEL = ICS_PGx2 Communicate on PGEC2/PGED2  
ICESEL = ICS_PGx3 Communicate on PGEC3/PGED3  


Program Flash Write Protect (PWP) 
PWP = OFF Disable  
PWP = PWP4K First 4K  
PWP = PWP8K First 8K  
PWP = PWP12K First 12K  
PWP = PWP16K First 16K  
PWP = PWP20K First 20K  
PWP = PWP24K First 24K  
PWP = PWP28K First 28K  
PWP = PWP32K First 32K  
PWP = PWP36K First 36K  
PWP = PWP40K First 40K  
PWP = PWP44K First 44K  
PWP = PWP48K First 48K  
PWP = PWP52K First 52K  
PWP = PWP56K First 56K  
PWP = PWP60K First 60K  
PWP = PWP64K First 64K  
PWP = PWP68K First 68K  
PWP = PWP72K First 72K  
PWP = PWP76K First 76K  
PWP = PWP80K First 80K  
PWP = PWP84K First 84K  
PWP = PWP88K First 88K  
PWP = PWP92K First 92K  
PWP = PWP96K First 96K  
PWP = PWP100K First 100K  
PWP = PWP104K First 104K  
PWP = PWP108K First 108K  
PWP = PWP112K First 112K  
PWP = PWP116K First 116K  
PWP = PWP120K First 120K  
PWP = PWP124K First 124K  
PWP = PWP128K First 128K  
PWP = PWP132K First 132K  
PWP = PWP136K First 136K  
PWP = PWP140K First 140K  
PWP = PWP144K First 144K  
PWP = PWP148K First 148K  
PWP = PWP152K First 152K  
PWP = PWP156K First 156K  
PWP = PWP160K First 160K  
PWP = PWP164K First 164K  
PWP = PWP168K First 168K  
PWP = PWP172K First 172K  
PWP = PWP176K First 176K  
PWP = PWP180K First 180K  
PWP = PWP184K First 184K  
PWP = PWP188K First 188K  
PWP = PWP192K First 192K  
PWP = PWP196K First 196K  
PWP = PWP200K First 200K  
PWP = PWP204K First 204K  
PWP = PWP208K First 208K  
PWP = PWP212K First 212K  
PWP = PWP216K First 216K  
PWP = PWP220K First 220K  
PWP = PWP224K First 224K  
PWP = PWP228K First 228K  
PWP = PWP232K First 232K  
PWP = PWP236K First 236K  
PWP = PWP240K First 240K  
PWP = PWP244K First 244K  
PWP = PWP248K First 248K  
PWP = PWP252K First 252K  
PWP = PWP256K First 256K  
PWP = PWP260K First 260K  
PWP = PWP264K First 264K  
PWP = PWP268K First 268K  
PWP = PWP272K First 272K  
PWP = PWP276K First 276K  
PWP = PWP280K First 280K  
PWP = PWP284K First 284K  
PWP = PWP288K First 288K  
PWP = PWP292K First 292K  
PWP = PWP296K First 296K  
PWP = PWP300K First 300K  
PWP = PWP304K First 304K  
PWP = PWP308K First 308K  
PWP = PWP312K First 312K  
PWP = PWP316K First 316K  
PWP = PWP320K First 320K  
PWP = PWP324K First 324K  
PWP = PWP328K First 328K  
PWP = PWP332K First 332K  
PWP = PWP336K First 336K  
PWP = PWP340K First 340K  
PWP = PWP344K First 344K  
PWP = PWP348K First 348K  
PWP = PWP352K First 352K  
PWP = PWP356K First 356K  
PWP = PWP360K First 360K  
PWP = PWP364K First 364K  
PWP = PWP368K First 368K  
PWP = PWP372K First 372K  
PWP = PWP376K First 376K  
PWP = PWP380K First 380K  
PWP = PWP384K First 384K  
PWP = PWP388K First 388K  
PWP = PWP392K First 392K  
PWP = PWP396K First 396K  
PWP = PWP400K First 400K  
PWP = PWP404K First 404K  
PWP = PWP408K First 408K  
PWP = PWP412K First 412K  
PWP = PWP416K First 416K  
PWP = PWP420K First 420K  
PWP = PWP424K First 424K  
PWP = PWP428K First 428K  
PWP = PWP432K First 432K  
PWP = PWP436K First 436K  
PWP = PWP440K First 440K  
PWP = PWP444K First 444K  
PWP = PWP448K First 448K  
PWP = PWP452K First 452K  
PWP = PWP456K First 456K  
PWP = PWP460K First 460K  
PWP = PWP464K First 464K  
PWP = PWP468K First 468K  
PWP = PWP472K First 472K  
PWP = PWP476K First 476K  
PWP = PWP480K First 480K  
PWP = PWP484K First 484K  
PWP = PWP488K First 488K  
PWP = PWP492K First 492K  
PWP = PWP496K First 496K  
PWP = PWP500K First 500K  
PWP = PWP504K First 504K  
PWP = PWP508K First 508K  
PWP = PWP512K First 512K  


Boot Flash Write Protect bit (BWP) 
BWP = ON Protection Enabled  
BWP = OFF Protection Disabled  


Code Protect (CP) 
CP = ON Protection Enabled  
CP = OFF Protection Disabled  
*/

//pic32mx5xx/6xx/7xx
#elif		defined(__32MX534F064H_H) || defined(__32MX534F064L_H) || \
			defined(__32MX564F064H_H) || defined(__32MX564F064L_H) || defined(__32MX564F128H_H) || defined(__32MX564F128L_H) || \
			defined(__32MX575F256H_H) || defined(__32MX575F256L_H) || defined(__32MX575F512H_H) || defined(__32MX575F512L_H) || \
			defined(__32MX664F064H_H) || defined(__32MX664F064L_H) || defined(__32MX664F128H_H) || defined(__32MX664F128L_H) || \
			defined(__32MX675F256H_H) || defined(__32MX675F256L_H) || defined(__32MX675F512H_H) || defined(__32MX675F512L_H) || \
			defined(__32MX695F512H_H) || defined(__32MX695F512L_H) || \
			defined(__32MX764F128H_H) || defined(__32MX764F128L_H) || \
			defined(__32MX775F256H_H) || defined(__32MX775F256L_H) || defined(__32MX775F512H_H) || defined(__32MX775F512L_H) || \
			defined(__32MX795F512H_H) || defined(__32MX795F512L_H)

#pragma config FNOSC = FRC, FSOSCEN = OFF		//oscillator selection bits = FRC/FRCPLL/PRI/PRIPLL/SOSC/LPRC/FRCDIV16/FRCDIV, secondary oscillator off
#pragma config IESO = OFF						//internal/external switch-over
#pragma config POSCMOD = HS						//primary oscilator configuration = OFF/HS/XT/EC
//PLL configuration.
//F_SYSCLK = F_OSC / FPLLIDIV * FPLLMUL / FPLLODIV.
#pragma config FPLLIDIV = DIV_2					//PLL input divider=1/2/3/4/5/6/10/12 (4Mhz < F_OSC / FPLLIDIV < 5Mhz)
#pragma config FPLLMUL = MUL_16					//PLL multiplier=15/16/17/18/19/20/21/24
#pragma config FPLLODIV = DIV_2					//PLL output divider=1/2/4/8/16/32/64/256
//end PLL configuration
//F_PBDIV = F_SYSCLK / FPBDIV
#pragma config FPBDIV = DIV_1					//peripheral bus clock divider = 1x
#pragma config OSCIOFNC = OFF, FCKSM = CSDCMD	//clock output disabled, clock switching disabled
//#pragma config ICESEL = RESERVED				//use PGD1/PGC1, 
//#pragma config PMDL1WAY = OFF, IOL1WAY = OFF	//peripheral configuration allows multiple configuration (OFF) or one configuration (ON), PPS allows multiple configuration (OFF)/one configuration(ON)
#pragma config FUSBIDIO = OFF, FVBUSONIO = OFF	//USBID pin controoled by port functions (OFF)/or USB module (ON), Vbuson pin controlled by port function (OFF)/USB module (ON)
#pragma config WDTPS = PS32768					//watchdog timer prescaler = 32768
//#pragma config FWDTEN = OFF					//watchdog timer disabled
//#pragma config WINDIS = OFF, FWDTWINSZ = WINSZ_75		//watchdog timer window disabled, watchdog timer window size =75%
#pragma config PWP = OFF, BWP = OFF, CP = OFF	//boot flash write-protection off, power-on protection off, code protection off
//#pragma config DEBUG = OFF					//OFF = debugger disabled. ON = debugger enabled -> *****needs to be unchecked to run code under pic32prog + pickit2*****
//#pragma config JTAGEN = OFF						//jtag off
#pragma config FSRSSEL = PRIORITY_7

/*
PIC32MX795F512L 
SRS Select:
 FSRSSEL = PRIORITY_0 SRS Priority 0  
FSRSSEL = PRIORITY_1 SRS Priority 1  
FSRSSEL = PRIORITY_2 SRS Priority 2  
FSRSSEL = PRIORITY_3 SRS Priority 3  
FSRSSEL = PRIORITY_4 SRS Priority 4  
FSRSSEL = PRIORITY_5 SRS Priority 5  
FSRSSEL = PRIORITY_6 SRS Priority 6  
FSRSSEL = PRIORITY_7 SRS Priority 7  

Ethernet RMII/MII Enable:
 FMIIEN = OFF RMII Enabled  
FMIIEN = ON MII Enabled  

Ethernet I/O Pin Select:
 FETHIO = OFF Alternate Ethernet I/O  
FETHIO = ON Default Ethernet I/O  

CAN I/O Pin Select:
 FCANIO = OFF Alternate CAN I/O  
FCANIO = ON Default CAN I/O  

USB USID Selection:
 FUSBIDIO = OFF Controlled by Port Function  
FUSBIDIO = ON Controlled by the USB Module  

USB VBUS ON Selection:
 FVBUSONIO = OFF Controlled by Port Function  
FVBUSONIO = ON Controlled by USB Module  

PLL Input Divider:
 FPLLIDIV = DIV_1 1x Divider  
FPLLIDIV = DIV_2 2x Divider  
FPLLIDIV = DIV_3 3x Divider  
FPLLIDIV = DIV_4 4x Divider  
FPLLIDIV = DIV_5 5x Divider  
FPLLIDIV = DIV_6 6x Divider  
FPLLIDIV = DIV_10 10x Divider  
FPLLIDIV = DIV_12 12x Divider  

PLL Multiplier:
 FPLLMUL = MUL_15 15x Multiplier  
FPLLMUL = MUL_16 16x Multiplier  
FPLLMUL = MUL_17 17x Multiplier  
FPLLMUL = MUL_18 18x Multiplier  
FPLLMUL = MUL_19 19x Multiplier  
FPLLMUL = MUL_20 20x Multiplier  
FPLLMUL = MUL_21 21x Multiplier  
FPLLMUL = MUL_24 24x Multiplier  

USB PLL Input Divider:
 UPLLIDIV = DIV_1 1x Divider  
UPLLIDIV = DIV_2 2x Divider  
UPLLIDIV = DIV_3 3x Divider  
UPLLIDIV = DIV_4 4x Divider  
UPLLIDIV = DIV_5 5x Divider  
UPLLIDIV = DIV_6 6x Divider  
UPLLIDIV = DIV_10 10x Divider  
UPLLIDIV = DIV_12 12x Divider  

USB PLL Enable:
 UPLLEN = ON Enabled  
UPLLEN = OFF Disabled and Bypassed  

System PLL Output Clock Divider:
 FPLLODIV = DIV_1 PLL Divide by 1  
FPLLODIV = DIV_2 PLL Divide by 2  
FPLLODIV = DIV_4 PLL Divide by 4  
FPLLODIV = DIV_8 PLL Divide by 8  
FPLLODIV = DIV_16 PLL Divide by 16  
FPLLODIV = DIV_32 PLL Divide by 32  
FPLLODIV = DIV_64 PLL Divide by 64  
FPLLODIV = DIV_256 PLL Divide by 256  

Oscillator Selection Bits:
 FNOSC = FRC Fast RC Osc (FRC)  
FNOSC = FRCPLL Fast RC Osc with PLL  
FNOSC = PRI Primary Osc (XT,HS,EC)  
FNOSC = PRIPLL Primary Osc w/PLL (XT+,HS+,EC+PLL)  
FNOSC = SOSC Low Power Secondary Osc (SOSC)  
FNOSC = LPRC Low Power RC Osc (LPRC)  
FNOSC = FRCDIV16 Fast RC Osc w/Div-by-16 (FRC/16)  
FNOSC = FRCDIV Fast RC Osc w/Div-by-N (FRCDIV)  

Secondary Oscillator Enable:
 FSOSCEN = OFF Disabled  
FSOSCEN = ON Enabled  

Internal/External Switch Over:
 IESO = OFF Disabled  
IESO = ON Enabled  

Primary Oscillator Configuration:
 POSCMOD = EC External clock mode  
POSCMOD = XT XT osc mode  
POSCMOD = HS HS osc mode  
POSCMOD = OFF Primary osc disabled  

CLKO Output Signal Active on the OSCO Pin:
 OSCIOFNC = ON Enabled  
OSCIOFNC = OFF Disabled  

Peripheral Clock Divisor:
 FPBDIV = DIV_1 Pb_Clk is Sys_Clk/1  
FPBDIV = DIV_2 Pb_Clk is Sys_Clk/2  
FPBDIV = DIV_4 Pb_Clk is Sys_Clk/4  
FPBDIV = DIV_8 Pb_Clk is Sys_Clk/8  

Clock Switching and Monitor Selection:
 FCKSM = CSECME Clock Switch Enable, FSCM Enabled  
FCKSM = CSECMD Clock Switch Enable, FSCM Disabled  
FCKSM = CSDCMD Clock Switch Disable, FSCM Disabled  

Watchdog Timer Postscaler:
 WDTPS = PS1 1:1  
WDTPS = PS2 1:2  
WDTPS = PS4 1:4  
WDTPS = PS8 1:8  
WDTPS = PS16 1:16  
WDTPS = PS32 1:32  
WDTPS = PS64 1:64  
WDTPS = PS128 1:128  
WDTPS = PS256 1:256  
WDTPS = PS512 1:512  
WDTPS = PS1024 1:1024  
WDTPS = PS2048 1:2048  
WDTPS = PS4096 1:4096  
WDTPS = PS8192 1:8192  
WDTPS = PS16384 1:16384  
WDTPS = PS32768 1:32768  
WDTPS = PS65536 1:65536  
WDTPS = PS131072 1:131072  
WDTPS = PS262144 1:262144  
WDTPS = PS524288 1:524288  
WDTPS = PS1048576 1:1048576  

Watchdog Timer Enable:
 FWDTEN = OFF WDT Disabled (SWDTEN Bit Controls)  
FWDTEN = ON WDT Enabled  

Background Debugger Enable:
 DEBUG = ON Debugger is enabled  
DEBUG = OFF Debugger is disabled  

ICE/ICD Comm Channel Select:
 ICESEL = ICS_PGx1 ICE EMUC1/EMUD1 pins shared with PGC1/PGD1  
ICESEL = ICS_PGx2 ICE EMUC2/EMUD2 pins shared with PGC2/PGD2  

Program Flash Write Protect:
 PWP = PWP512K First 512K  
PWP = PWP508K First 508K  
PWP = PWP504K First 504K  
PWP = PWP500K First 500K  
PWP = PWP496K First 496K  
PWP = PWP492K First 492K  
PWP = PWP488K First 488K  
PWP = PWP484K First 484K  
PWP = PWP480K First 480K  
PWP = PWP476K First 476K  
PWP = PWP472K First 472K  
PWP = PWP468K First 468K  
PWP = PWP464K First 464K  
PWP = PWP460K First 460K  
PWP = PWP456K First 456K  
PWP = PWP452K First 452K  
PWP = PWP448K First 448K  
PWP = PWP444K First 444K  
PWP = PWP440K First 440K  
PWP = PWP436K First 436K  
PWP = PWP432K First 432K  
PWP = PWP428K First 428K  
PWP = PWP424K First 424K  
PWP = PWP420K First 420K  
PWP = PWP416K First 416K  
PWP = PWP412K First 412K  
PWP = PWP408K First 408K  
PWP = PWP404K First 404K  
PWP = PWP400K First 400K  
PWP = PWP396K First 396K  
PWP = PWP392K First 392K  
PWP = PWP388K First 388K  
PWP = PWP384K First 384K  
PWP = PWP380K First 380K  
PWP = PWP376K First 376K  
PWP = PWP372K First 372K  
PWP = PWP368K First 368K  
PWP = PWP364K First 364K  
PWP = PWP360K First 360K  
PWP = PWP356K First 356K  
PWP = PWP352K First 352K  
PWP = PWP348K First 348K  
PWP = PWP344K First 344K  
PWP = PWP340K First 340K  
PWP = PWP336K First 336K  
PWP = PWP332K First 332K  
PWP = PWP328K First 328K  
PWP = PWP324K First 324K  
PWP = PWP320K First 320K  
PWP = PWP316K First 316K  
PWP = PWP312K First 312K  
PWP = PWP308K First 308K  
PWP = PWP304K First 304K  
PWP = PWP300K First 300K  
PWP = PWP296K First 296K  
PWP = PWP292K First 292K  
PWP = PWP288K First 288K  
PWP = PWP284K First 284K  
PWP = PWP280K First 280K  
PWP = PWP276K First 276K  
PWP = PWP272K First 272K  
PWP = PWP268K First 268K  
PWP = PWP264K First 264K  
PWP = PWP260K First 260K  
PWP = PWP256K First 256K  
PWP = PWP252K First 252K  
PWP = PWP248K First 248K  
PWP = PWP244K First 244K  
PWP = PWP240K First 240K  
PWP = PWP236K First 236K  
PWP = PWP232K First 232K  
PWP = PWP228K First 228K  
PWP = PWP224K First 224K  
PWP = PWP220K First 220K  
PWP = PWP216K First 216K  
PWP = PWP212K First 212K  
PWP = PWP208K First 208K  
PWP = PWP204K First 204K  
PWP = PWP200K First 200K  
PWP = PWP196K First 196K  
PWP = PWP192K First 192K  
PWP = PWP188K First 188K  
PWP = PWP184K First 184K  
PWP = PWP180K First 180K  
PWP = PWP176K First 176K  
PWP = PWP172K First 172K  
PWP = PWP168K First 168K  
PWP = PWP164K First 164K  
PWP = PWP160K First 160K  
PWP = PWP156K First 156K  
PWP = PWP152K First 152K  
PWP = PWP148K First 148K  
PWP = PWP144K First 144K  
PWP = PWP140K First 140K  
PWP = PWP136K First 136K  
PWP = PWP132K First 132K  
PWP = PWP128K First 128K  
PWP = PWP124K First 124K  
PWP = PWP120K First 120K  
PWP = PWP116K First 116K  
PWP = PWP112K First 112K  
PWP = PWP108K First 108K  
PWP = PWP104K First 104K  
PWP = PWP100K First 100K  
PWP = PWP96K First 96K  
PWP = PWP92K First 92K  
PWP = PWP88K First 88K  
PWP = PWP84K First 84K  
PWP = PWP80K First 80K  
PWP = PWP76K First 76K  
PWP = PWP72K First 72K  
PWP = PWP68K First 68K  
PWP = PWP64K First 64K  
PWP = PWP60K First 60K  
PWP = PWP56K First 56K  
PWP = PWP52K First 52K  
PWP = PWP48K First 48K  
PWP = PWP44K First 44K  
PWP = PWP40K First 40K  
PWP = PWP36K First 36K  
PWP = PWP32K First 32K  
PWP = PWP28K First 28K  
PWP = PWP24K First 24K  
PWP = PWP20K First 20K  
PWP = PWP16K First 16K  
PWP = PWP12K First 12K  
PWP = PWP8K First 8K  
PWP = PWP4K First 4K  
PWP = OFF Disable  

Boot Flash Write Protect bit:
 BWP = ON Protection Enabled  
BWP = OFF Protection Disabled  

Code Protect:
 CP = ON Protection Enabled  
CP = OFF Protection Disabled  
*/

#elif		defined(__32MZ1024ECG064_H) || defined(__32MZ1024ECH064_H) || defined(__32MZ1024ECM064_H) || defined(__32MZ2048ECG064_H) || defined(__32MZ2048ECH064_H) || defined(__32MZ2048ECM064_H) ||\
		defined(__32MZ1024ECG100_H) || defined(__32MZ1024ECH100_H) || defined(__32MZ1024ECM100_H) || defined(__32MZ2048ECG100_H) || defined(__32MZ2048ECH100_H) || defined(__32MZ2048ECM100_H) ||\
		defined(__32MZ1024ECG124_H) || defined(__32MZ1024ECH124_H) || defined(__32MZ1024ECM124_H) || defined(__32MZ2048ECG124_H) || defined(__32MZ2048ECH124_H) || defined(__32MZ2048ECM124_H) ||\
		defined(__32MZ1024ECG144_H) || defined(__32MZ1024ECH144_H) || defined(__32MZ1024ECM144_H) || defined(__32MZ2048ECG144_H) || defined(__32MZ2048ECH144_H) || defined(__32MZ2048ECM144_H)

//Configuration-Bit Settings for PIC32MZ2048ECG064

#pragma config FMIIEN = OFF			//Ethernet RMII/MII: off=rmii enabled; on =  mii enabled
#pragma config FETHIO = OFF			//ethernet I/O pin select: off=alternate ethernet i/o; on = default thernet i/o
#pragma config PGL1WAY = OFF		//permission group lock on way configuration: ON = allow only one reconfiguration; off=allow multiple reconfigurations
#pragma config PMDL1WAY = OFF		//peripheral module disable configuration: ON = allow only one reconfiguration; off=allow multiple reconfigurations
#pragma config IOL1WAY = OFF		//peripheral pin select configuration: ON = allow only one reconfiguration; off = allow multiple reconfiguration
#pragma config FUSBIDIO = OFF		//usb usbid selection: OFF = controlled by port function; ON controlled by the usb module
#pragma config FPLLIDIV = DIV_1		//system PLL input divider: DIV_1..8
#pragma config FPLLRNG = RANGE_BYPASS	//Bypass, RANGE_5_10_MHZ, RANGE_8_16_MHZ, RANGE_13_26_MHZ, RANGE_21_42_MHZ, RANGE_34_68_MHZ
#pragma config FPLLICLK = PLL_FRC	//System PLL Input Clock Selection (FPLLICLK), PLL_FRC	FRC is input to the System PLL / PLL_POSC	POSC is input to the System PLL
#pragma config FPLLMULT = MUL_1		//System PLL Multiplier (FPLLMULT): MUL_1..128	PLL Multiply by 1..128
#pragma config FPLLODIV = DIV_2		//System PLL Output Clock Divider (FPLLODIV): DIV_2/4/8/16/32	2x Divider
#pragma config UPLLFSEL = FREQ_24MHZ	//USB PLL Input Frequency Selection (UPLLFSEL): FREQ_24MHZ	USB PLL input is 24 MHz; FREQ_12MHZ	USB PLL input is 12 MHz
#pragma config UPLLEN = OFF			//USB PLL Enable (UPLLEN): ON=	USB PLL is enabled; OFF=	USB PLL is disabled
#pragma config FNOSC = FRCDIV		//Oscillator Selection Bits (FNOSC): FRCDIV=	Fast RC Osc w/Div-by-N (FRCDIV); SPLL=	System PLL; POSC=	Primary Osc (HS,EC); SOSC=	Low Power Secondary Osc (SOSC); LPRC=	Low Power RC Osc (LPRC)
#pragma config DMTINTV = WIN_0		//DMT Count Window Interval (DMTINTV): WIN_0/WIN_1_2/WIN_3_4/WIN_7_8/WIN_15_16/WIN_31_32/WIN_63_64/WIN_127_128	Window/Interval value is 127/128 counter value
#pragma config FSOSCEN = OFF		//Secondary Oscillator Enable (FSOSCEN): FSOSCEN = OFF	Disable SOSC; FSOSCEN = ON	Enable SOSC
#pragma config IESO = OFF			//Internal/External Switch Over (IESO): IESO = OFF	Disabled; IESO = ON	Enabled
#pragma config POSCMOD = OFF		//Primary Oscillator Configuration (POSCMOD): POSCMOD = EC	External clock mode; POSCMOD = HS	HS osc mode; POSCMOD = OFF	Primary osc disabled
#pragma config OSCIOFNC = OFF		//CLKO Output Signal Active on the OSCO Pin (OSCIOFNC): OSCIOFNC = OFF	Disabled; OSCIOFNC = ON	Enabled
#pragma config FCKSM = CSDCMD		//Clock Switching and Monitor Selection (FCKSM): FCKSM = CSDCMD	Clock Switch Disabled, FSCM Enabled; FCKSM = CSECMD	Clock Switch Enabled, FSCM Disabled; FCKSM = CSDCME	Clock Switch Disabled, FSCM Enabled; FCKSM = CSECME	Clock Switch Enabled, FSCM Enabled
#pragma config WDTPS = PS1048576	//Watchdog Timer Postscaler (WDTPS): WDTPS = PS1/2/4/8/16/32/64.../1048675/WDTPS = PS1048576	1:1048576
#pragma config WDTSPGM = STOP		//Watchdog Timer Stop During Flash Programming (WDTSPGM): WDTSPGM = RUN	WDT runs during Flash programming;WDTSPGM = STOP	WDT stops during Flash programming
#pragma config WINDIS = NORMAL		//Watchdog Timer Window Mode (WINDIS): WINDIS = NORMAL	Watchdog Timer is in non-Window mode; WINDIS = WINDOW	Watchdog Timer is in Window mode
#pragma config FWDTEN = OFF			//Watchdog Timer Enable (FWDTEN): FWDTEN = OFF	WDT Disabled; FWDTEN = ON	WDT Enabled
#pragma config FWDTWINSZ = WINSZ_25	//Watchdog Timer Window Size (FWDTWINSZ): FWDTWINSZ = WINSZ_25	Window size is 25%; FWDTWINSZ = WINSZ_37	Window size is 37.5%; FWDTWINSZ = WINSZ_50	Window size is 50%; FWDTWINSZ = WINSZ_75	Window size is 75%
#pragma config DMTCNT = DMT8		//Deadman Timer Count Selection (DMTCNT): DMT8..31: DMTCNT = DMT31	2^31 (2147483648)
#pragma config FDMTEN = OFF			//Deadman Timer Enable (FDMTEN): FDMTEN = ON	Deadman Timer is enabled; FDMTEN = OFF	Deadman Timer is disabled
#pragma config DEBUG = OFF			//Background Debugger Enable (DEBUG): DEBUG = ON	Debugger is enabled; DEBUG = OFF	Debugger is disabled
#pragma config JTAGEN = OFF			//JTAG Enable (JTAGEN): JTAGEN = ON	JTAG Port Enabled; JTAGEN = OFF	JTAG Disabled
#pragma config ICESEL = ICS_PGx1	//ICE/ICD Comm Channel Select (ICESEL): ICESEL = ICS_PGx1	Communicate on PGEC1/PGED1; ICESEL = ICS_PGx2	Communicate on PGEC2/PGED2
#pragma config TRCEN = OFF			//Trace Enable (TRCEN): TRCEN = ON	Trace features in the CPU are enabled; TRCEN = OFF	Trace features in the CPU are disabled
#pragma config BOOTISA = MIPS32		//Boot ISA Selection (BOOTISA); BOOTISA = MIPS32	Boot code and Exception code is MIPS32; BOOTISA = MICROMIPS	Boot code and Exception code is microMIPS
#pragma config FECCCON = OFF_UNLOCKED	//Dynamic Flash ECC Configuration (FECCCON): FECCCON = ON	Flash ECC is enabled (ECCCON bits are locked); FECCCON = DYNAMIC	Dynamic Flash ECC is enabled (ECCCON bits are locked); FECCCON = OFF_LOCKED	ECC and Dynamic ECC are disabled (ECCCON bits are locked); FECCCON = OFF_UNLOCKED	ECC and Dynamic ECC are disabled (ECCCON bits are writable)
#pragma config FSLEEP = OFF			//Flash Sleep Mode (FSLEEP): FSLEEP = OFF	Flash is powered down when the device is in Sleep mode; FSLEEP = VREGS	Flash power down is controlled by the VREGS bit
#pragma config DBGPER = PG_ALL		//Debug Mode CPU Access Permission (DBGPER): DBGPER = ALLOW_PG2	Allow CPU access to Permission Group 2 permission regions; DBGPER = ALLOW_PG1	Allow CPU access to Permission Group 1 permission regions; DBGPER = ALLOW_PG0	Allow CPU access to Permission Group 0 permission regions; DBGPER = DENY_PG2	Deny CPU access to Permission Group 2 permission regions; DBGPER = DENY_PG1	Deny CPU access to Permission Group 1 permission regions; DBGPER = DENY_PG0	Deny CPU access to Permission Group 0 permission regions; DBGPER = PG_2_1	PG0: Deny PG1: Allow PG2: Allow; DBGPER = PG_ALL	Allow CPU access to all permission regions
#pragma config EJTAGBEN = NORMAL		//EJTAG Boot (EJTAGBEN): EJTAGBEN = NORMAL	Normal EJTAG functionality; EJTAGBEN = REDUCED	Reduced EJTAG functionality
#pragma config CP = OFF				//Code Protect (CP): CP = ON	Protection Enabled; CP = OFF	Protection Disabled

/*(Data Sheet # DS-)

Usage:
#pragma config SETTING = VALUE
#pragma config_alt SETTING = VALUE
#pragma config_bf1 SETTING = VALUE
#pragma config_abf1 SETTING = VALUE
#pragma config_bf2 SETTING = VALUE
#pragma config_abf2 SETTING = VALUE

Ethernet RMII/MII Enable (FMIIEN)
FMIIEN = OFF	RMII Enabled
FMIIEN = ON	MII Enabled

Ethernet I/O Pin Select (FETHIO)
FETHIO = OFF	Alternate Ethernet I/O
FETHIO = ON	Default Ethernet I/O

Permission Group Lock One Way Configuration (PGL1WAY)
PGL1WAY = ON	Allow only one reconfiguration
PGL1WAY = OFF	Allow multiple reconfigurations

Peripheral Module Disable Configuration (PMDL1WAY)
PMDL1WAY = ON	Allow only one reconfiguration
PMDL1WAY = OFF	Allow multiple reconfigurations

Peripheral Pin Select Configuration (IOL1WAY)
IOL1WAY = ON	Allow only one reconfiguration
IOL1WAY = OFF	Allow multiple reconfigurations

USB USBID Selection (FUSBIDIO)
FUSBIDIO = OFF	Controlled by Port Function
FUSBIDIO = ON	Controlled by the USB Module

System PLL Input Divider (FPLLIDIV)
FPLLIDIV = DIV_1	1x Divider
FPLLIDIV = DIV_2	2x Divider
FPLLIDIV = DIV_3	3x Divider
FPLLIDIV = DIV_4	4x Divider
FPLLIDIV = DIV_5	5x Divider
FPLLIDIV = DIV_6	6x Divider
FPLLIDIV = DIV_7	7x Divider
FPLLIDIV = DIV_8	8x Divider

System PLL Input Range (FPLLRNG)
FPLLRNG = RANGE_BYPASS	Bypass
FPLLRNG = RANGE_5_10_MHZ	5-10 MHz Input
FPLLRNG = RANGE_8_16_MHZ	8-16 MHz Input
FPLLRNG = RANGE_13_26_MHZ	13-26 MHz Input
FPLLRNG = RANGE_21_42_MHZ	21-42 MHz Input
FPLLRNG = RANGE_34_68_MHZ	34-68 MHz Input

System PLL Input Clock Selection (FPLLICLK)
FPLLICLK = PLL_FRC	FRC is input to the System PLL
FPLLICLK = PLL_POSC	POSC is input to the System PLL

System PLL Multiplier (FPLLMULT)
FPLLMULT = MUL_1	PLL Multiply by 1
FPLLMULT = MUL_2	PLL Multiply by 2
FPLLMULT = MUL_3	PLL Multiply by 3
FPLLMULT = MUL_4	PLL Multiply by 4
FPLLMULT = MUL_5	PLL Multiply by 5
FPLLMULT = MUL_6	PLL Multiply by 6
FPLLMULT = MUL_7	PLL Multiply by 7
FPLLMULT = MUL_8	PLL Multiply by 8
FPLLMULT = MUL_9	PLL Multiply by 9
FPLLMULT = MUL_10	PLL Multiply by 10
FPLLMULT = MUL_11	PLL Multiply by 11
FPLLMULT = MUL_12	PLL Multiply by 12
FPLLMULT = MUL_13	PLL Multiply by 13
FPLLMULT = MUL_14	PLL Multiply by 14
FPLLMULT = MUL_15	PLL Multiply by 15
FPLLMULT = MUL_16	PLL Multiply by 16
FPLLMULT = MUL_17	PLL Multiply by 17
FPLLMULT = MUL_18	PLL Multiply by 18
FPLLMULT = MUL_19	PLL Multiply by 19
FPLLMULT = MUL_20	PLL Multiply by 20
FPLLMULT = MUL_21	PLL Multiply by 21
FPLLMULT = MUL_22	PLL Multiply by 22
FPLLMULT = MUL_23	PLL Multiply by 23
FPLLMULT = MUL_24	PLL Multiply by 24
FPLLMULT = MUL_25	PLL Multiply by 25
FPLLMULT = MUL_26	PLL Multiply by 26
FPLLMULT = MUL_27	PLL Multiply by 27
FPLLMULT = MUL_28	PLL Multiply by 28
FPLLMULT = MUL_29	PLL Multiply by 29
FPLLMULT = MUL_30	PLL Multiply by 30
FPLLMULT = MUL_31	PLL Multiply by 31
FPLLMULT = MUL_32	PLL Multiply by 32
FPLLMULT = MUL_33	PLL Multiply by 33
FPLLMULT = MUL_34	PLL Multiply by 34
FPLLMULT = MUL_35	PLL Multiply by 35
FPLLMULT = MUL_36	PLL Multiply by 36
FPLLMULT = MUL_37	PLL Multiply by 37
FPLLMULT = MUL_38	PLL Multiply by 38
FPLLMULT = MUL_39	PLL Multiply by 39
FPLLMULT = MUL_40	PLL Multiply by 40
FPLLMULT = MUL_41	PLL Multiply by 41
FPLLMULT = MUL_42	PLL Multiply by 42
FPLLMULT = MUL_43	PLL Multiply by 43
FPLLMULT = MUL_44	PLL Multiply by 44
FPLLMULT = MUL_45	PLL Multiply by 45
FPLLMULT = MUL_46	PLL Multiply by 46
FPLLMULT = MUL_47	PLL Multiply by 47
FPLLMULT = MUL_48	PLL Multiply by 48
FPLLMULT = MUL_49	PLL Multiply by 49
FPLLMULT = MUL_50	PLL Multiply by 50
FPLLMULT = MUL_51	PLL Multiply by 51
FPLLMULT = MUL_52	PLL Multiply by 52
FPLLMULT = MUL_53	PLL Multiply by 53
FPLLMULT = MUL_54	PLL Multiply by 54
FPLLMULT = MUL_55	PLL Multiply by 55
FPLLMULT = MUL_56	PLL Multiply by 56
FPLLMULT = MUL_57	PLL Multiply by 57
FPLLMULT = MUL_58	PLL Multiply by 58
FPLLMULT = MUL_59	PLL Multiply by 59
FPLLMULT = MUL_60	PLL Multiply by 60
FPLLMULT = MUL_61	PLL Multiply by 61
FPLLMULT = MUL_62	PLL Multiply by 62
FPLLMULT = MUL_63	PLL Multiply by 63
FPLLMULT = MUL_64	PLL Multiply by 64
FPLLMULT = MUL_65	PLL Multiply by 65
FPLLMULT = MUL_66	PLL Multiply by 66
FPLLMULT = MUL_67	PLL Multiply by 67
FPLLMULT = MUL_68	PLL Multiply by 68
FPLLMULT = MUL_69	PLL Multiply by 69
FPLLMULT = MUL_70	PLL Multiply by 70
FPLLMULT = MUL_71	PLL Multiply by 71
FPLLMULT = MUL_72	PLL Multiply by 72
FPLLMULT = MUL_73	PLL Multiply by 73
FPLLMULT = MUL_74	PLL Multiply by 74
FPLLMULT = MUL_75	PLL Multiply by 75
FPLLMULT = MUL_76	PLL Multiply by 76
FPLLMULT = MUL_77	PLL Multiply by 77
FPLLMULT = MUL_78	PLL Multiply by 78
FPLLMULT = MUL_79	PLL Multiply by 79
FPLLMULT = MUL_80	PLL Multiply by 80
FPLLMULT = MUL_81	PLL Multiply by 81
FPLLMULT = MUL_82	PLL Multiply by 82
FPLLMULT = MUL_83	PLL Multiply by 83
FPLLMULT = MUL_84	PLL Multiply by 84
FPLLMULT = MUL_85	PLL Multiply by 85
FPLLMULT = MUL_86	PLL Multiply by 86
FPLLMULT = MUL_87	PLL Multiply by 87
FPLLMULT = MUL_88	PLL Multiply by 88
FPLLMULT = MUL_89	PLL Multiply by 89
FPLLMULT = MUL_90	PLL Multiply by 90
FPLLMULT = MUL_91	PLL Multiply by 91
FPLLMULT = MUL_92	PLL Multiply by 92
FPLLMULT = MUL_93	PLL Multiply by 93
FPLLMULT = MUL_94	PLL Multiply by 94
FPLLMULT = MUL_95	PLL Multiply by 95
FPLLMULT = MUL_96	PLL Multiply by 96
FPLLMULT = MUL_97	PLL Multiply by 97
FPLLMULT = MUL_98	PLL Multiply by 98
FPLLMULT = MUL_99	PLL Multiply by 99
FPLLMULT = MUL_100	PLL Multiply by 100
FPLLMULT = MUL_101	PLL Multiply by 101
FPLLMULT = MUL_102	PLL Multiply by 102
FPLLMULT = MUL_103	PLL Multiply by 103
FPLLMULT = MUL_104	PLL Multiply by 104
FPLLMULT = MUL_105	PLL Multiply by 105
FPLLMULT = MUL_106	PLL Multiply by 106
FPLLMULT = MUL_107	PLL Multiply by 107
FPLLMULT = MUL_108	PLL Multiply by 108
FPLLMULT = MUL_109	PLL Multiply by 109
FPLLMULT = MUL_110	PLL Multiply by 110
FPLLMULT = MUL_111	PLL Multiply by 111
FPLLMULT = MUL_112	PLL Multiply by 112
FPLLMULT = MUL_113	PLL Multiply by 113
FPLLMULT = MUL_114	PLL Multiply by 114
FPLLMULT = MUL_115	PLL Multiply by 115
FPLLMULT = MUL_116	PLL Multiply by 116
FPLLMULT = MUL_117	PLL Multiply by 117
FPLLMULT = MUL_118	PLL Multiply by 118
FPLLMULT = MUL_119	PLL Multiply by 119
FPLLMULT = MUL_120	PLL Multiply by 120
FPLLMULT = MUL_121	PLL Multiply by 121
FPLLMULT = MUL_122	PLL Multiply by 122
FPLLMULT = MUL_123	PLL Multiply by 123
FPLLMULT = MUL_124	PLL Multiply by 124
FPLLMULT = MUL_125	PLL Multiply by 125
FPLLMULT = MUL_126	PLL Multiply by 126
FPLLMULT = MUL_127	PLL Multiply by 127
FPLLMULT = MUL_128	PLL Multiply by 128

System PLL Output Clock Divider (FPLLODIV)
FPLLODIV = DIV_2	2x Divider
FPLLODIV = DIV_4	4x Divider
FPLLODIV = DIV_8	8x Divider
FPLLODIV = DIV_16	16x Divider
FPLLODIV = DIV_32	32x Divider

USB PLL Input Frequency Selection (UPLLFSEL)
UPLLFSEL = FREQ_24MHZ	USB PLL input is 24 MHz
UPLLFSEL = FREQ_12MHZ	USB PLL input is 12 MHz

USB PLL Enable (UPLLEN)
UPLLEN = ON	USB PLL is enabled
UPLLEN = OFF	USB PLL is disabled

Oscillator Selection Bits (FNOSC)
FNOSC = FRCDIV	Fast RC Osc w/Div-by-N (FRCDIV)
FNOSC = SPLL	System PLL
FNOSC = POSC	Primary Osc (HS,EC)
FNOSC = SOSC	Low Power Secondary Osc (SOSC)
FNOSC = LPRC	Low Power RC Osc (LPRC)

DMT Count Window Interval (DMTINTV)
DMTINTV = WIN_0	Window/Interval value is zero
DMTINTV = WIN_1_2	Window/Interval value is 1/2 counter value
DMTINTV = WIN_3_4	Window/Interval value is 3/4 counter value
DMTINTV = WIN_7_8	Window/Interval value is 7/8 counter value
DMTINTV = WIN_15_16	Window/Interval value is 15/16 counter value
DMTINTV = WIN_31_32	Window/Interval value is 31/32 counter value
DMTINTV = WIN_63_64	Window/Interval value is 63/64 counter value
DMTINTV = WIN_127_128	Window/Interval value is 127/128 counter value

Secondary Oscillator Enable (FSOSCEN)
FSOSCEN = OFF	Disable SOSC
FSOSCEN = ON	Enable SOSC

Internal/External Switch Over (IESO)
IESO = OFF	Disabled
IESO = ON	Enabled

Primary Oscillator Configuration (POSCMOD)
POSCMOD = EC	External clock mode
POSCMOD = HS	HS osc mode
POSCMOD = OFF	Primary osc disabled

CLKO Output Signal Active on the OSCO Pin (OSCIOFNC)
OSCIOFNC = OFF	Disabled
OSCIOFNC = ON	Enabled

Clock Switching and Monitor Selection (FCKSM)
FCKSM = CSDCMD	Clock Switch Disabled, FSCM Enabled
FCKSM = CSECMD	Clock Switch Enabled, FSCM Disabled
FCKSM = CSDCME	Clock Switch Disabled, FSCM Enabled
FCKSM = CSECME	Clock Switch Enabled, FSCM Enabled

Watchdog Timer Postscaler (WDTPS)
WDTPS = PS1	1:1
WDTPS = PS2	1:2
WDTPS = PS4	1:4
WDTPS = PS8	1:8
WDTPS = PS16	1:16
WDTPS = PS32	1:32
WDTPS = PS64	1:64
WDTPS = PS128	1:128
WDTPS = PS256	1:256
WDTPS = PS512	1:512
WDTPS = PS1024	1:1024
WDTPS = PS2048	1:2048
WDTPS = PS4096	1:4096
WDTPS = PS8192	1:8192
WDTPS = PS16384	1:16384
WDTPS = PS32768	1:32768
WDTPS = PS65536	1:65536
WDTPS = PS131072	1:131072
WDTPS = PS262144	1:262144
WDTPS = PS524288	1:524288
WDTPS = PS1048576	1:1048576

Watchdog Timer Stop During Flash Programming (WDTSPGM)
WDTSPGM = RUN	WDT runs during Flash programming
WDTSPGM = STOP	WDT stops during Flash programming

Watchdog Timer Window Mode (WINDIS)
WINDIS = NORMAL	Watchdog Timer is in non-Window mode
WINDIS = WINDOW	Watchdog Timer is in Window mode

Watchdog Timer Enable (FWDTEN)
FWDTEN = OFF	WDT Disabled
FWDTEN = ON	WDT Enabled

Watchdog Timer Window Size (FWDTWINSZ)
FWDTWINSZ = WINSZ_25	Window size is 25%
FWDTWINSZ = WINSZ_37	Window size is 37.5%
FWDTWINSZ = WINSZ_50	Window size is 50%
FWDTWINSZ = WINSZ_75	Window size is 75%

Deadman Timer Count Selection (DMTCNT)
DMTCNT = DMT8	2^8 (256)
DMTCNT = DMT9	2^9 (512)
DMTCNT = DMT10	2^10 (1024)
DMTCNT = DMT11	2^11 (2048)
DMTCNT = DMT12	2^12 (4096)
DMTCNT = DMT13	2^13 (8192)
DMTCNT = DMT14	2^14 (16384)
DMTCNT = DMT15	2^15 (32768)
DMTCNT = DMT16	2^16 (65536)
DMTCNT = DMT17	2^17 (131072)
DMTCNT = DMT18	2^18 (262144)
DMTCNT = DMT19	2^19 (524288)
DMTCNT = DMT20	2^20 (1048576)
DMTCNT = DMT21	2^21 (2097152)
DMTCNT = DMT22	2^22 (4194304)
DMTCNT = DMT23	2^23 (8388608)
DMTCNT = DMT24	2^24 (16777216)
DMTCNT = DMT25	2^25 (33554432)
DMTCNT = DMT26	2^26 (67108864)
DMTCNT = DMT27	2^27 (134217728)
DMTCNT = DMT28	2^28 (268435456)
DMTCNT = DMT29	2^29 (536870912)
DMTCNT = DMT30	2^30 (1073741824)
DMTCNT = DMT31	2^31 (2147483648)

Deadman Timer Enable (FDMTEN)
FDMTEN = ON	Deadman Timer is enabled
FDMTEN = OFF	Deadman Timer is disabled

Background Debugger Enable (DEBUG)
DEBUG = ON	Debugger is enabled
DEBUG = OFF	Debugger is disabled

JTAG Enable (JTAGEN)
JTAGEN = ON	JTAG Port Enabled
JTAGEN = OFF	JTAG Disabled

ICE/ICD Comm Channel Select (ICESEL)
ICESEL = ICS_PGx1	Communicate on PGEC1/PGED1
ICESEL = ICS_PGx2	Communicate on PGEC2/PGED2

Trace Enable (TRCEN)
TRCEN = ON	Trace features in the CPU are enabled
TRCEN = OFF	Trace features in the CPU are disabled

Boot ISA Selection (BOOTISA)
BOOTISA = MIPS32	Boot code and Exception code is MIPS32
BOOTISA = MICROMIPS	Boot code and Exception code is microMIPS

Dynamic Flash ECC Configuration (FECCCON)
FECCCON = ON	Flash ECC is enabled (ECCCON bits are locked)
FECCCON = DYNAMIC	Dynamic Flash ECC is enabled (ECCCON bits are locked)
FECCCON = OFF_LOCKED	ECC and Dynamic ECC are disabled (ECCCON bits are locked)
FECCCON = OFF_UNLOCKED	ECC and Dynamic ECC are disabled (ECCCON bits are writable)

Flash Sleep Mode (FSLEEP)
FSLEEP = OFF	Flash is powered down when the device is in Sleep mode
FSLEEP = VREGS	Flash power down is controlled by the VREGS bit

Debug Mode CPU Access Permission (DBGPER)
DBGPER = ALLOW_PG2	Allow CPU access to Permission Group 2 permission regions
DBGPER = ALLOW_PG1	Allow CPU access to Permission Group 1 permission regions
DBGPER = ALLOW_PG0	Allow CPU access to Permission Group 0 permission regions
DBGPER = DENY_PG2	Deny CPU access to Permission Group 2 permission regions
DBGPER = DENY_PG1	Deny CPU access to Permission Group 1 permission regions
DBGPER = DENY_PG0	Deny CPU access to Permission Group 0 permission regions
DBGPER = PG_2_1	PG0: Deny PG1: Allow PG2: Allow
DBGPER = PG_ALL	Allow CPU access to all permission regions

EJTAG Boot (EJTAGBEN)
EJTAGBEN = NORMAL	Normal EJTAG functionality
EJTAGBEN = REDUCED	Reduced EJTAG functionality

Code Protect (CP)
CP = ON	Protection Enabled
CP = OFF	Protection Disabled

Boot Flash True Sequence Number (TSEQ)

Boot Flash Complement Sequence Number (CSEQ)

*/

#else                               //no chip identified
//no header file found
#warning no device header file specified in config.h
#endif

#endif	/* CONFIG_H */

