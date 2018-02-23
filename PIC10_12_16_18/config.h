#ifndef __CONFIG_H
#define __CONFIG_H

//config.h - config words file
//chips covered
//10f200, 10f202, 10f204, 10f206

//12f629, 12f675
//12f683
//16F627, 16F628
//16F627A, 16F628A, 16F648A
//16f630, 16f676
//16f684
//16f631, 16f677, 16f685, 16f687, 16f689, 16f690
//16f688
//16f870, 16f871, 16f872, 16f873, 16f874, 16f876, 16f877, 
//16f873a, 16f874a, 16f876a, 16f877a
//16f882, 16f883, 16f884, 16f886, 16f887
//16f913, 16f914, 16f916, 16f917
//16f1826, 16lf1826, 16f1827, 16lf1827
//16f1936, 16lf1936
//16f1937, 16lf1937

//18f1230, 18f1330
//18f13k22, 18lf13k22, 18f14k22, 18lf14k22
//18f13k50, 18f14k50, 18lf13k50, 18lf14k50
//18f2420, 18f2520, 18f4420, 18f4520
//18f2455, 18f2550, 18f4455, 18f4550
//18f2458, 18f2553, 18f4458, 18f4553
//18F2585. 18F2680, 18F4585, 18F4680
//18f6520, 18f6620, 18f6720, 18f8520, 18f8620, 18f8720
//18F6627, 18F6722, 18F8627, 18F8722, 18F6527, 18F6622
//18F8527, 18F8622, 18F6628, 18F6723, 18F8628, 18F8723
//18f23k20, 18f24k20, 18f24k20, 18f26k20
//18f43k20, 18f44k20, 18f45k20, 18f46k20
//18f23k22, 18f24k22, 18f25k22, 18f26k22, 18f43k22, 18f44k22, 18f45k22, 18f46k22
//18f65k90, 18f66k90, 18f67k90, 18f85k90, 18f86k90, 18f87k90

//10f200, 10f202, 10f204, 10f206
#if defined(_10F200) || defined(_10F202) || defined(_10F204) || defined(_10F206)
//configuration bits
#pragma config OSC = IntRC
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF

/*
OSC =	Oscillator
IntRC	This is the only option. It is here for backward compatibility
MCLRE =	Master Clear Enable
OFF	GP3/MCLR pin fuction is digital I/O, MCLR internally tied to VDD
ON	GP3/MCLR pin function is MCLR
WDTE =	Watchdog Timer
OFF	WDT disabled
ON	WDT enabled
CP =	Code Protect
OFF	Code protection off
ON	Code protection on
*/

//12f629, 12f675
#elif	defined(_12F629)	|| defined(_12F675)
//configuration bits
#pragma config BOREN = OFF
#pragma config CPD = OFF
#pragma config FOSC = INTRCIO
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = OFF

/*
BOREN =	Brown-out Detect Enable bit
OFF	BOD disabled
ON	BOD enabled
CPD =	Data Code Protection bit
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
FOSC =	Oscillator Selection bits
EXTRCCLK	RC oscillator: CLKOUT function on GP4/OSC2/CLKOUT pin, RC on GP5/OSC1/CLKIN
INTRCIO	INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN
XT	XT oscillator: Crystal/resonator on GP4/OSC2/CLKOUT and GP5/OSC1/CLKIN
LP	LP oscillator: Low power crystal on GP4/OSC2/CLKOUT and GP5/OSC1/CLKIN
INTRCCLK	INTOSC oscillator: CLKOUT function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN
EXTRCIO	RC oscillator: I/O function on GP4/OSC2/CLKOUT pin, RC on GP5/OSC1/CLKIN
EC	EC: I/O function on GP4/OSC2/CLKOUT pin, CLKIN on GP5/OSC1/CLKIN
HS	HS oscillator: High speed crystal/resonator on GP4/OSC2/CLKOUT and GP5/OSC1/CLKIN
MCLRE =	GP3/MCLR pin function select
OFF	GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD
ON	GP3/MCLR pin function is MCLR
WDTE =	Watchdog Timer Enable bit
OFF	WDT disabled
ON	WDT enabled
CP =	Code Protection bit
OFF	Program Memory code protection is disabled
ON	Program Memory code protection is enabled
PWRTE =	Power-Up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
*/

#elif defined(_12F683)

#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FOSC = INTOSCIO	//EXTRCCLK/INTOSCCLK/XT/LP/EXTRCIO/EC/INTOSCIO/HS
#pragma config FCMEN = OFF
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = OFF
 
/*#pragma config Settings

Register: CONFIG @ 0x2007

CPD =	Data Code Protection bit
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
BOREN =	Brown Out Detect
OFF	BOR disabled
ON	BOR enabled
NSLEEP	BOR enabled during operation and disabled in Sleep
SBODEN	BOR controlled by SBOREN bit of the PCON register
IESO =	Internal External Switchover bit
OFF	Internal External Switchover mode is disabled
ON	Internal External Switchover mode is enabled
FOSC =	Oscillator Selection bits
EXTRCCLK	EXTRC oscillator: External RC on RA5/OSC1/CLKIN, CLKOUT function on RA4/OSC2/CLKOUT pin
INTOSCCLK	INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
XT	XT oscillator: Crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKINT
LP	LP oscillator: Low-power crystal on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
EXTRCIO	EXTRCIO oscillator: External RC on RA5/OSC1/CLKIN, I/O function on RA4/OSC2/CLKOUT pin
EC	EC: I/O function on RA4/OSC2/CLKOUT pin, CLKIN on RA5/OSC1/CLKIN
INTOSCIO	INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
HS	HS oscillator: High-speed crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
FCMEN =	Fail-Safe Clock Monitor Enabled bit
OFF	Fail-Safe Clock Monitor is disabled
ON	Fail-Safe Clock Monitor is enabled
MCLRE =	MCLR Pin Function Select bit
OFF	MCLR pin function is digital input, MCLR internally tied to VDD
ON	MCLR pin function is MCLR
WDTE =	Watchdog Timer Enable bit
OFF	WDT disabled
ON	WDT enabled
CP =	Code Protection bit
OFF	Program memory code protection is disabled
ON	Program memory code protection is enabled
PWRTE =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
Register: IDLOC0 @ 0x2000

Register: IDLOC1 @ 0x2001

Register: IDLOC2 @ 0x2002

Register: IDLOC3 @ 0x2003
*/
#elif defined(_16F627)	|| defined(_16F628)
//configuration bits
#pragma config BOREN = OFF
#pragma config CPD = OFF
#pragma config FOSC = INTOSCIO
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config LVP = OFF
#pragma config PWRTE = OFF

/*
BOREN =	Brown-out Reset Enable bit
OFF	BOD Reset disabled
ON	BOD Reset enabled
CPD =	Data Code Protection bit
OFF	Data memory code protection off
ON	Data memory code protected
FOSC =	Oscillator Selection bits
ERCLK	ER oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, Resistor on RA7/OSC1/CLKIN
INTOSCCLK	INTRC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN
XT	XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN
LP	LP oscillator: Low-power crystal on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN
ECIO	EC: I/O function on RA6/OSC2/CLKOUT pin, CLKIN on RA7/OSC1/CLKIN
ERIO	ER oscillator: I/O function on RA6/OSC2/CLKOUT pin, Resistor on RA7/OSC1/CLKIN
INTOSCIO	INTRC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN
HS	HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN
MCLRE =	RA5/MCLR pin function select
OFF	RA5/MCLR pin function is digital input, MCLR internally tied to VDD
ON	RA5/MCLR pin function is MCLR
WDTE =	Watchdog Timer Enable bit
OFF	WDT disabled
ON	WDT enabled
CP =	Code Protection bits
50	Program memory code protection off
OFF	Program memory code protection off
ALL	0000h-03FFh code protected
75	0200h-03FFh code protected
LVP =	Low-Voltage Programming Enable bit
OFF	RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming
ON	RB4/PGM pin has PGM function, low-voltage programming enabled
PWRTE =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
*/
#elif defined(_16F627A)	|| defined(_16F628A)	|| defined(_16F648A)
#pragma config BOREN = OFF
#pragma config CPD = OFF
#pragma config FOSC = INTOSCIO
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config LVP = OFF
#pragma config PWRTE = OFF

/*
BOREN =	Brown-out Detect Enable bit
OFF	BOD disabled
ON	BOD enabled
CPD =	Data EE Memory Code Protection bit
OFF	Data memory code protection off
ON	Data memory code-protected
FOSC =	Oscillator Selection bits
EXTRCCLK	RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, Resistor and Capacitor on RA7/OSC1/CLKIN
INTOSCCLK	INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN
XT	XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN
LP	LP oscillator: Low-power crystal on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN
EXTRCIO	RC oscillator: I/O function on RA6/OSC2/CLKOUT pin, Resistor and Capacitor on RA7/OSC1/CLKIN
ECIO	EC: I/O function on RA6/OSC2/CLKOUT pin, CLKIN on RA7/OSC1/CLKIN
INTOSCIO	INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN
HS	HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN
MCLRE =	RA5/MCLR/VPP Pin Function Select bit
OFF	RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD
ON	RA5/MCLR/VPP pin function is MCLR
WDTE =	Watchdog Timer Enable bit
OFF	WDT disabled
ON	WDT enabled
CP =	Flash Program Memory Code Protection bit
OFF	Code protection off
ON	0000h to 03FFh code-protected
LVP =	Low-Voltage Programming Enable bit
OFF	RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming
ON	RB4/PGM pin has PGM function, low-voltage programming enabled
PWRTE =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
*/
#elif defined(_16F630)	|| defined(_16F676)
#pragma config BOREN = OFF
#pragma config CPD = OFF
#pragma config FOSC = INTRCIO
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = OFF

/*
BOREN =	Brown-out Detect Enable bit
OFF	BOD disabled
ON	BOD enabled
CPD =	Data Code Protection bit
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
FOSC =	Oscillator Selection bits
EXTRCCLK	RC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN
INTRCIO	INTOSC oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
XT	XT oscillator: Crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
LP	LP oscillator: Low power crystal on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
INTRCCLK	INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
EXTRCIO	RC oscillator: I/O function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN
EC	EC: I/O function on RA4/OSC2/CLKOUT pin, CLKIN on RA5/OSC1/CLKIN
HS	HS oscillator: High speed crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
MCLRE =	RA3/MCLR pin function select
OFF	RA3/MCLR pin function is digital I/O, MCLR internally tied to VDD
ON	RA3/MCLR pin function is MCLR
WDTE =	Watchdog Timer Enable bit
OFF	WDT disabled
ON	WDT enabled
CP =	Code Protection bit
OFF	Program Memory code protection is disabled
ON	Program Memory code protection is enabled
PWRTE =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
*/

//16f684
#elif 	defined(_16F684)
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FOSC = INTOSCIO
#pragma config FCMEN = OFF
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = OFF

/*
CPD =	Data Code Protection bit
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
BOREN =	Brown Out Detect
OFF	BOR disabled
ON	BOR enabled
NSLEEP	BOR enabled during operation and disabled in Sleep
SBODEN	BOR controlled by SBOREN bit of the PCON register
IESO =	Internal External Switchover bit
OFF	Internal External Switchover mode is disabled
ON	Internal External Switchover mode is enabled
FOSC =	Oscillator Selection bits
EXTRCCLK	EXTRC oscillator: External RC on RA5/OSC1/CLKIN, CLKOUT function on RA4/OSC2/CLKOUT pin
INTOSCCLK	INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
XT	XT oscillator: Crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKINT
LP	LP oscillator: Low-power crystal on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
EXTRCIO	EXTRCIO oscillator: External RC on RA5/OSC1/CLKIN, I/O function on RA4/OSC2/CLKOUT pin
EC	EC: I/O function on RA4/OSC2/CLKOUT pin, CLKIN on RA5/OSC1/CLKIN
INTOSCIO	INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
HS	HS oscillator: High-speed crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
FCMEN =	Fail-Safe Clock Monitor Enabled bit
OFF	Fail-Safe Clock Monitor is disabled
ON	Fail-Safe Clock Monitor is enabled
MCLRE =	MCLR Pin Function Select bit
OFF	MCLR pin function is digital input, MCLR internally tied to VDD
ON	MCLR pin function is MCLR
WDTE =	Watchdog Timer Enable bit
OFF	WDT disabled
ON	WDT enabled
CP =	Code Protection bit
OFF	Program memory code protection is disabled
ON	Program memory code protection is enabled
PWRTE =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
*/
#elif 	defined(_16F631)	|| defined(_16F677)	|| defined(_16F685)	||\
    	defined(_16F687)	|| defined(_16F689)	|| defined(_16F690)
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FOSC = INTRCIO
#pragma config FCMEN = OFF
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = OFF

/*
CPD =	Data Code Protection bit
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
BOREN =	Brown-out Reset Selection bits
OFF	BOR disabled
ON	BOR enabled
NSLEEP	BOR enabled during operation and disabled in Sleep
SBODEN	BOR controlled by SBOREN bit of the PCON register
IESO =	Internal External Switchover bit
OFF	Internal External Switchover mode is disabled
ON	Internal External Switchover mode is enabled
FOSC =	Oscillator Selection bits
EXTRCCLK	RC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN
INTRCIO	INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
XT	XT oscillator: Crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
LP	LP oscillator: Low-power crystal on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
INTRCCLK	INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
EXTRCIO	RCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN
EC	EC: I/O function on RA4/OSC2/CLKOUT pin, CLKIN on RA5/OSC1/CLKIN
HS	HS oscillator: High-speed crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
FCMEN =	Fail-Safe Clock Monitor Enabled bit
OFF	Fail-Safe Clock Monitor is disabled
ON	Fail-Safe Clock Monitor is enabled
MCLRE =	MCLR Pin Function Select bit
OFF	MCLR pin function is digital input, MCLR internally tied to VDD
ON	MCLR pin function is MCLR
WDTE =	Watchdog Timer Enable bit
OFF	WDT disabled and can be enabled by SWDTEN bit of the WDTCON register
ON	WDT enabled
CP =	Code Protection bit
OFF	Program memory code protection is disabled
ON	Program memory code protection is enabled
PWRTE =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
*/

//16f688
#elif defined(_16F688)
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FOSC = INTOSCIO
#pragma config FCMEN = OFF
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = OFF
/*
CPD =	Data Code Protection bit
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
BOREN =	Brown Out Detect
OFF	BOR disabled
ON	BOR enabled
NSLEEP	BOR enabled during operation and disabled in Sleep
SBODEN	BOR controlled by SBOREN bit of the PCON register
IESO =	Internal External Switchover bit
OFF	Internal External Switchover mode is disabled
ON	Internal External Switchover mode is enabled
FOSC =	Oscillator Selection bits
EXTRCCLK	EXTRC oscillator: External RC on RA5/OSC1/CLKIN, CLKOUT function on RA4/OSC2/CLKOUT pin
INTOSCCLK	INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
XT	XT oscillator: Crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKINT
LP	LP oscillator: Low-power crystal on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
EXTRCIO	EXTRCIO oscillator: External RC on RA5/OSC1/CLKIN, I/O function on RA4/OSC2/CLKOUT pin
EC	EC: I/O function on RA4/OSC2/CLKOUT pin, CLKIN on RA5/OSC1/CLKIN
INTOSCIO	INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
HS	HS oscillator: High-speed crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
FCMEN =	Fail-Safe Clock Monitor Enabled bit
OFF	Fail-Safe Clock Monitor is disabled
ON	Fail-Safe Clock Monitor is enabled
MCLRE =	MCLR Pin Function Select bit
OFF	MCLR pin function is digital input, MCLR internally tied to VDD
ON	MCLR pin function is MCLR
WDTE =	Watchdog Timer Enable bit
OFF	WDT disabled
ON	WDT enabled
CP =	Code Protection bit
OFF	Program memory code protection is disabled
ON	Program memory code protection is enabled
PWRTE =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
*/
//16f877
#elif     defined(_16F870) ||\
    defined(_16F871)	|| defined(_16F872)	||\
    defined(_16F873)	|| \
    defined(_16F874)    || \
    defined(_16F876)    || \
    defined(_16F877)
    
#pragma config BOREN = OFF
#pragma config CPD = OFF
#pragma config DEBUG = OFF
#pragma config WRT = OFF
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config LVP = OFF
#pragma config PWRTE = OFF
/*
BOREN =	Brown-out Reset Enable bit
OFF	BOR disabled
ON	BOR enabled
CPD =	Data EE Memory Code Protection
OFF	Code Protection off
ON	Data EEPROM memory code-protected
DEBUG =	In-Circuit Debugger Mode bit
OFF	In-Circuit Debugger disabled, RB6 and RB7 are general purpose I/O pins
ON	In-Circuit Debugger enabled, RB6 and RB7 are dedicated to the debugger
WRT =	FLASH Program Memory Write Enable
OFF	Unprotected program memory may not be written to by EECON control
ALL	Unprotected program memory may be written to by EECON control
FOSC =	Oscillator Selection bits
XT	XT oscillator
LP	LP oscillator
EXTRC	RC oscillator
HS	HS oscillator
WDTE =	Watchdog Timer Enable bit
OFF	WDT disabled
ON	WDT enabled
CP =	FLASH Program Memory Code Protection bits
OFF	Code protection off
ON	All memory code protected
LVP =	Low Voltage In-Circuit Serial Programming Enable bit
OFF	RB3 is digital I/O, HV on MCLR must be used for programming
ON	RB3/PGM pin has PGM function; low-voltage programming enabled
PWRTE =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
*/

//16f877a
#elif   defined(_16F873A)	|| defined(_16F874A)	||\
	defined(_16F876A)	|| defined(_16F877A)

#pragma config BOREN = OFF, CPD = OFF, DEBUG = OFF, WRT = OFF, FOSC = HS, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF
/*
BOREN =	Brown-out Reset Enable bit
OFF	BOR disabled
ON	BOR enabled
CPD =	Data EEPROM Memory Code Protection bit
OFF	Data EEPROM code protection off
ON	Data EEPROM code-protected
DEBUG =	In-Circuit Debugger Mode bit
OFF	In-Circuit Debugger disabled, RB6 and RB7 are general purpose I/O pins
ON	In-Circuit Debugger enabled, RB6 and RB7 are dedicated to the debugger
WRT =	Flash Program Memory Write Enable bits
OFF	Write protection off; all program memory may be written to by EECON control
HALF	0000h to 0FFFh write-protected; 1000h to 1FFFh may be written to by EECON control
1FOURTH	0000h to 07FFh write-protected; 0800h to 1FFFh may be written to by EECON control
256	0000h to 00FFh write-protected; 0100h to 1FFFh may be written to by EECON control
FOSC =	Oscillator Selection bits
XT	XT oscillator
LP	LP oscillator
EXTRC	RC oscillator
HS	HS oscillator
WDTE =	Watchdog Timer Enable bit
OFF	WDT disabled
ON	WDT enabled
CP =	Flash Program Memory Code Protection bit
OFF	Code protection off
ON	All program memory code-protected
LVP =	Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit
OFF	RB3 is digital I/O, HV on MCLR must be used for programming
ON	RB3/PGM pin has PGM function; low-voltage programming enabled
PWRTE =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
*/

//16f886
#elif 	defined(_16F882)	|| defined(_16F883)	|| defined(_16F884)	||\
    	defined(_16F886)	|| defined(_16F887)
//configuration bits
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config DEBUG = OFF
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config FCMEN = OFF
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config LVP = OFF
#pragma config PWRTE = OFF
#pragma config BOR4V = BOR21V
#pragma config WRT = OFF
/*
Register: CONFIG1 @ 0x2007

CPD =	Data Code Protection bit
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
BOREN =	Brown Out Reset Selection bits
OFF	BOR disabled
ON	BOR enabled
NSLEEP	BOR enabled during operation and disabled in Sleep
SBODEN	BOR controlled by SBOREN bit of the PCON register
IESO =	Internal External Switchover bit
OFF	Internal/External Switchover mode is disabled
ON	Internal/External Switchover mode is enabled
DEBUG =	In-Circuit Debugger Mode bit
OFF	In-Circuit Debugger disabled, RB6/ICSPCLK and RB7/ICSPDAT are general purpose I/O pins
ON	In_Circuit Debugger enabled, RB6/ICSPCLK and RB7/ICSPDAT are dedicated to the debugger
FOSC =	Oscillator Selection bits
INTRC_NOCLKOUT	INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN
XT	XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN
LP	LP oscillator: Low-power crystal on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN
INTRC_CLKOUT	INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN
EXTRC_CLKOUT	RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN
EXTRC_NOCLKOUT	RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN
EC	EC: I/O function on RA6/OSC2/CLKOUT pin, CLKIN on RA7/OSC1/CLKIN
HS	HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN
FCMEN =	Fail-Safe Clock Monitor Enabled bit
OFF	Fail-Safe Clock Monitor is disabled
ON	Fail-Safe Clock Monitor is enabled
MCLRE =	RE3/MCLR pin function select bit
OFF	RE3/MCLR pin function is digital input, MCLR internally tied to VDD
ON	RE3/MCLR pin function is MCLR
WDTE =	Watchdog Timer Enable bit
OFF	WDT disabled and can be enabled by SWDTEN bit of the WDTCON register
ON	WDT enabled
CP =	Code Protection bit
OFF	Program memory code protection is disabled
ON	Program memory code protection is enabled
LVP =	Low Voltage Programming Enable bit
OFF	RB3 pin has digital I/O, HV on MCLR must be used for programming
ON	RB3/PGM pin has PGM function, low voltage programming enabled
PWRTE =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
Register: CONFIG2 @ 0x2008

BOR4V =	Brown-out Reset Selection bit
BOR40V	Brown-out Reset set to 4.0V
BOR21V	Brown-out Reset set to 2.1V
WRT =	Flash Program Memory Self Write Enable bits
HALF	0000h to 0FFFh write protected, 1000h to 1FFFh may be modified by EECON control
OFF	Write protection off
1FOURTH	0000h to 07FFh write protected, 0800h to 1FFFh may be modified by EECON control
256	0000h to 00FFh write protected, 0100h to 1FFFh may be modified by EECON control
*/

#elif 	defined(_16F913)	|| defined(_16F914)	||\
    	defined(_16F916)	|| defined(_16F917)

#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config DEBUG = OFF
#pragma config FOSC = INTOSCIO
#pragma config FCMEN = OFF
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = ON
/*
Register: CONFIG @ 0x2007

CPD =	Data Code Protection bit
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
BOREN =	Brown-out Reset Selection bits
OFF	BOR disabled
ON	BOR enabled
NSLEEP	BOR enabled during operation and disabled in Sleep
SBODEN	BOR controlled by SBOREN bit of the PCON register
IESO =	Internal External Switchover bit
OFF	Internal/External Switchover mode is disabled
ON	Internal/External Switchover mode is enabled
DEBUG =	In-Circuit Debugger Mode bit
OFF	In-Circuit Debugger disabled, RB6/ISCPCLK and RB7/ICSPDAT are general purpose I/O pins
ON	In-Circuit Debugger enabled, RB6/ICSPCLK and RB7/ICSPDAT are dedicated to the debugger
FOSC =	Oscillator Selection bits
EXTRCCLK	RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT/T1OSO pin, RC on RA7/OSC1/CLKIN/T1OSI
INTOSCCLK	INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT/T1OSO pin, I/O function on RA7/OSC1/CLKIN/T1OSI
XT	XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT/T1OSO and RA7/OSC1/CLKIN/T1OSI
LP	LP oscillator: Low-power crystal on RA6/OSC2/CLKOUT/T1OSO and RA7/OSC1/CLKIN/T1OSI
EXTRCIO	RCIO oscillator: I/O function on RA6/OSC2/CLKOUT/T1OSO pin, RC on RA7/OSC1/CLKIN/T1OSI
EC	EC: I/O function on RA6/OSC2/CLKOUT/T1OSO pin, CLKIN on RA7/OSC1/CLKIN/T1OSI
INTOSCIO	INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT/T1OSO pin, I/O function on RA7/OSC1/CLKIN/T1OSI
HS	HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT/T1OSO and RA7/OSC1/CLKIN/T1OSI
FCMEN =	Fail-Safe Clock Monitor Enabled bit
OFF	Fail-Safe Clock Monitor is disabled
ON	Fail-Safe Clock Monitor is enabled
MCLRE =	RE3/MCLR pin function select bit
OFF	RE3/MCLR pin function is digital input, MCLR internally tied to VDD
ON	RE3/MCLR pin function is MCLR
WDTE =	Watchdog Timer Enable bit
OFF	WDT disabled and can be enabled by SWDTEN bit of the WDTCON register
ON	WDT enabled
CP =	Code Protection bit
OFF	Program memory code protection is disabled
ON	Program memory code protection is enabled
PWRTE =	Power Up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
*/
//16f1826, 16lf1826 for 9.65pro
#elif 	defined(_16F1826)	|| defined(_16LF1826)

#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FOSC = INTOSC
#pragma config FCMEN = OFF
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = ON
#pragma config CLKOUTEN = OFF

/*
Register: CONFIG1 @ 0x8007

CPD =	Data Memory Code Protection
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
BOREN =	Brown-out Reset Enable
OFF	Brown-out Reset disabled
ON	Brown-out Reset enabled
NSLEEP	Brown-out Reset enabled while running and disabled in Sleep
SBODEN	Brown-out Reset controlled by the SBOREN bit in the BORCON register
IESO =	Internal/External Switchover
OFF	Internal/External Switchover mode is disabled
ON	Internal/External Switchover mode is enabled
FOSC =	Oscillator Selection
ECM	ECM, External Clock, Medium Power Mode (0.5-4 MHz): device clock supplied to CLKIN pin
XT	XT Oscillator, Crystal/resonator connected between OSC1 and OSC2 pins
LP	LP Oscillator, Low-power crystal connected between OSC1 and OSC2 pins
EXTRC	EXTRC oscillator: External RC circuit connected to CLKIN pin
ECH	ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin
ECL	ECL, External Clock, Low Power Mode (0-0.5 MHz): device clock supplied to CLKIN pin
INTOSC	INTOSC oscillator: I/O function on CLKIN pin
HS	HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins
FCMEN =	Fail-Safe Clock Monitor Enable
OFF	Fail-Safe Clock Monitor is disabled
ON	Fail-Safe Clock Monitor is enabled
MCLRE =	MCLR Pin Function Select
OFF	MCLR/VPP pin function is digital input
ON	MCLR/VPP pin function is MCLR
WDTE =	Watchdog Timer Enable
OFF	WDT disabled
ON	WDT enabled
NSLEEP	WDT enabled while running and disabled in Sleep
SWDTEN	WDT controlled by the SWDTEN bit in the WDTCON register
CP =	Flash Program Memory Code Protection
OFF	Program memory code protection is disabled
ON	Program memory code protection is enabled
PWRTE =	Power-up Timer Enable
OFF	PWRT disabled
ON	PWRT enabled
CLKOUTEN =	Clock Out Enable
OFF	CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
ON	CLKOUT function is enabled on the CLKOUT pin
*/
#pragma config PLLEN = OFF, WRT = OFF, STVREN = OFF, BORV = LO, LVP = OFF

/*
Register: CONFIG2 @ 0x8008

PLLEN =	PLL Enable
OFF	4x PLL disabled
ON	4x PLL enabled
WRT =	Flash Memory Self-Write Protection
OFF	Write protection off
BOOT	000h to 1FFh write protected, 200h to 7FFh may be modified by EECON control
HALF	000h to 3FFh write protected, 400h to 7FFh may be modified by EECON control
ALL	000h to 7FFh write protected, no addresses may be modified by EECON control
STVREN =	Stack Overflow/Underflow Reset Enable
OFF	Stack Overflow or Underflow will not cause a Reset
ON	Stack Overflow or Underflow will cause a Reset
BORV =	Brown-out Reset Voltage Selection
LO	Brown-out Reset Voltage (Vbor), low trip point selected.
HI	Brown-out Reset Voltage (Vbor), high trip point selected.
LVP =	Low-Voltage Programming Enable
OFF	High-voltage on MCLR/VPP must be used for programming
ON	Low-voltage programming enabled
*/
		
//16f1827, 16lf1827 for 9.65pro
#elif 	defined(_16F1827)	|| defined(_16LF1827)

#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FOSC = INTOSC
#pragma config FCMEN = OFF
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = ON
#pragma config CLKOUTEN = OFF

/*
Register: CONFIG1 @ 0x8007

CPD =	Data Memory Code Protection
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
BOREN =	Brown-out Reset Enable
OFF	Brown-out Reset disabled
ON	Brown-out Reset enabled
NSLEEP	Brown-out Reset enabled while running and disabled in Sleep
SBODEN	Brown-out Reset controlled by the SBOREN bit in the BORCON register
IESO =	Internal/External Switchover
OFF	Internal/External Switchover mode is disabled
ON	Internal/External Switchover mode is enabled
FOSC =	Oscillator Selection
ECM	ECM, External Clock, Medium Power Mode (0.5-4 MHz): device clock supplied to CLKIN pin
XT	XT Oscillator, Crystal/resonator connected between OSC1 and OSC2 pins
LP	LP Oscillator, Low-power crystal connected between OSC1 and OSC2 pins
EXTRC	EXTRC oscillator: External RC circuit connected to CLKIN pin
ECH	ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin
ECL	ECL, External Clock, Low Power Mode (0-0.5 MHz): device clock supplied to CLKIN pin
INTOSC	INTOSC oscillator: I/O function on CLKIN pin
HS	HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins
FCMEN =	Fail-Safe Clock Monitor Enable
OFF	Fail-Safe Clock Monitor is disabled
ON	Fail-Safe Clock Monitor is enabled
MCLRE =	MCLR Pin Function Select
OFF	MCLR/VPP pin function is digital input
ON	MCLR/VPP pin function is MCLR
WDTE =	Watchdog Timer Enable
OFF	WDT disabled
ON	WDT enabled
NSLEEP	WDT enabled while running and disabled in Sleep
SWDTEN	WDT controlled by the SWDTEN bit in the WDTCON register
CP =	Flash Program Memory Code Protection
OFF	Program memory code protection is disabled
ON	Program memory code protection is enabled
PWRTE =	Power-up Timer Enable
OFF	PWRT disabled
ON	PWRT enabled
CLKOUTEN =	Clock Out Enable
OFF	CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
ON	CLKOUT function is enabled on the CLKOUT pin
*/

#pragma config PLLEN = OFF, WRT = OFF, STVREN = OFF, BORV = LO, LVP = OFF

/*
Register: CONFIG2 @ 0x8008

PLLEN =	PLL Enable
OFF	4x PLL disabled
ON	4x PLL enabled
WRT =	Flash Memory Self-Write Protection
OFF	Write protection off
BOOT	000h to 1FFh write protected, 200h to FFFh may be modified by EECON control
HALF	000h to 7FFh write protected, 800h to FFFh may be modified by EECON control
ALL	000h to FFFh write protected, no addresses may be modified by EECON control
STVREN =	Stack Overflow/Underflow Reset Enable
OFF	Stack Overflow or Underflow will not cause a Reset
ON	Stack Overflow or Underflow will cause a Reset
BORV =	Brown-out Reset Voltage Selection
LO	Brown-out Reset Voltage (Vbor), low trip point selected.
HI	Brown-out Reset Voltage (Vbor), high trip point selected.
LVP =	Low-Voltage Programming Enable
OFF	High-voltage on MCLR/VPP must be used for programming
ON	Low-voltage programming enabled
*/

//16F1936 for 9.65pro
#elif 	defined(_16F1933) || defined(_16LF1933) || \
 	defined(_16F1934) || defined(_16LF1934) || \
 	defined(_16F1936) || defined(_16LF1936) || \
 	defined(_16F1937) || defined(_16LF1937) || \
 	defined(_16F1938) || defined(_16LF1938) || \
 	defined(_16F1939) || defined(_16LF1939)

#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FOSC = INTOSC			//INTOSC, HS, XT, LP, ECH/ECM/ECL
#pragma config FCMEN = OFF
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = ON
#pragma config CLKOUTEN = OFF

#pragma config PLLEN = OFF, WRT = OFF, STVREN = OFF, BORV = LO, LVP = OFF

#if 	defined(_16F1936) || defined(_16LF1936) //vcapen applies to 1936 only
#pragma config VCAPEN = OFF
#endif

/*
Register: CONFIG1 @ 0x8007

CPD =	Data Memory Code Protection
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
BOREN =	Brown-out Reset Enable
OFF	Brown-out Reset disabled
ON	Brown-out Reset enabled
NSLEEP	Brown-out Reset enabled while running and disabled in Sleep
SBODEN	Brown-out Reset controlled by the SBOREN bit in the BORCON register
IESO =	Internal/External Switchover
OFF	Internal/External Switchover mode is disabled
ON	Internal/External Switchover mode is enabled
FOSC =	Oscillator Selection
ECM	ECM, External Clock, Medium Power Mode (0.5-4 MHz): device clock supplied to CLKIN pin
XT	XT Oscillator, Crystal/resonator connected between OSC1 and OSC2 pins
LP	LP Oscillator, Low-power crystal connected between OSC1 and OSC2 pins
EXTRC	EXTRC oscillator: External RC circuit connected to CLKIN pin
ECH	ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin
ECL	ECL, External Clock, Low Power Mode (0-0.5 MHz): device clock supplied to CLKIN pin
INTOSC	INTOSC oscillator: I/O function on CLKIN pin
HS	HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins
FCMEN =	Fail-Safe Clock Monitor Enable
OFF	Fail-Safe Clock Monitor is disabled
ON	Fail-Safe Clock Monitor is enabled
MCLRE =	MCLR Pin Function Select
OFF	MCLR/VPP pin function is digital input
ON	MCLR/VPP pin function is MCLR
WDTE =	Watchdog Timer Enable
OFF	WDT disabled
ON	WDT enabled
NSLEEP	WDT enabled while running and disabled in Sleep
SWDTEN	WDT controlled by the SWDTEN bit in the WDTCON register
CP =	Flash Program Memory Code Protection
OFF	Program memory code protection is disabled
ON	Program memory code protection is enabled
PWRTE =	Power-up Timer Enable
OFF	PWRT disabled
ON	PWRT enabled
CLKOUTEN =	Clock Out Enable
OFF	CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
ON	CLKOUT function is enabled on the CLKOUT pin
*/


/*
Register: CONFIG2 @ 0x8008

PLLEN =	PLL Enable
OFF	4x PLL disabled
ON	4x PLL enabled
WRT =	Flash Memory Self-Write Protection
OFF	Write protection off
BOOT	000h to 1FFh write protected, 200h to 1FFFh may be modified by EECON control
HALF	000h to FFFh write protected, 1000h to 1FFFh may be modified by EECON control
ALL	000h to 1FFFh write protected, no addresses may be modified by EECON control
STVREN =	Stack Overflow/Underflow Reset Enable
OFF	Stack Overflow or Underflow will not cause a Reset
ON	Stack Overflow or Underflow will cause a Reset
BORV =	Brown-out Reset Voltage Selection
LO	Brown-out Reset Voltage (Vbor), low trip point selected.
HI	Brown-out Reset Voltage (Vbor), high trip point selected.
VCAPEN =	Voltage Regulator Capacitor Enable
RA5	VCAP functionality is enabled on RA5
OFF	All VCAP pin functionality is disabled
RA6	VCAP functionality is enabled on RA6
RA0	VCAP functionality is enabled on RA0
LVP =	Low-Voltage Programming Enable
OFF	High-voltage on MCLR/VPP must be used for programming
ON	Low-voltage programming enabled
*/

//16f1937 for 9.65pro
#elif defined(_16F1937) || defined(_16LF1937)

#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FOSC = INTOSC
#pragma config FCMEN = OFF
#pragma config MCLRE = OFF
#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config PWRTE = ON
#pragma config CLKOUTEN = OFF
/*
CPD =	Data Memory Code Protection
OFF	Data memory code protection is disabled
ON	Data memory code protection is enabled
BOREN =	Brown-out Reset Enable
OFF	Brown-out Reset disabled
ON	Brown-out Reset enabled
NSLEEP	Brown-out Reset enabled while running and disabled in Sleep
SBODEN	Brown-out Reset controlled by the SBOREN bit in the BORCON register
IESO =	Internal/External Switchover
OFF	Internal/External Switchover mode is disabled
ON	Internal/External Switchover mode is enabled
FOSC =	Oscillator Selection
ECM	ECM, External Clock, Medium Power Mode (0.5-4 MHz): device clock supplied to CLKIN pin
XT	XT Oscillator, Crystal/resonator connected between OSC1 and OSC2 pins
LP	LP Oscillator, Low-power crystal connected between OSC1 and OSC2 pins
EXTRC	EXTRC oscillator: External RC circuit connected to CLKIN pin
ECH	ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin
ECL	ECL, External Clock, Low Power Mode (0-0.5 MHz): device clock supplied to CLKIN pin
INTOSC	INTOSC oscillator: I/O function on CLKIN pin
HS	HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins
FCMEN =	Fail-Safe Clock Monitor Enable
OFF	Fail-Safe Clock Monitor is disabled
ON	Fail-Safe Clock Monitor is enabled
MCLRE =	MCLR Pin Function Select
OFF	MCLR/VPP pin function is digital input
ON	MCLR/VPP pin function is MCLR
WDTE =	Watchdog Timer Enable
OFF	WDT disabled
ON	WDT enabled
NSLEEP	WDT enabled while running and disabled in Sleep
SWDTEN	WDT controlled by the SWDTEN bit in the WDTCON register
CP =	Flash Program Memory Code Protection
OFF	Program memory code protection is disabled
ON	Program memory code protection is enabled
PWRTE =	Power-up Timer Enable
OFF	PWRT disabled
ON	PWRT enabled
CLKOUTEN =	Clock Out Enable
OFF	CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
ON	CLKOUT function is enabled on the CLKOUT pin
*/
#pragma config PLLEN = OFF, WRT = OFF, STVREN = OFF, BORV = LO, VCAPEN = OFF, LVP = OFF

/*
Register: CONFIG2 @ 0x8008

PLLEN =	PLL Enable
OFF	4x PLL disabled
ON	4x PLL enabled
WRT =	Flash Memory Self-Write Protection
OFF	Write protection off
BOOT	000h to 1FFh write protected, 200h to 1FFFh may be modified by EECON control
HALF	000h to FFFh write protected, 1000h to 1FFFh may be modified by EECON control
ALL	000h to 1FFFh write protected, no addresses may be modified by EECON control
STVREN =	Stack Overflow/Underflow Reset Enable
OFF	Stack Overflow or Underflow will not cause a Reset
ON	Stack Overflow or Underflow will cause a Reset
BORV =	Brown-out Reset Voltage Selection
LO	Brown-out Reset Voltage (Vbor), low trip point selected.
HI	Brown-out Reset Voltage (Vbor), high trip point selected.
VCAPEN =	Voltage Regulator Capacitor Enable
RA5	VCAP functionality is enabled on RA5
OFF	All VCAP pin functionality is disabled
RA6	VCAP functionality is enabled on RA6
RA0	VCAP functionality is enabled on RA0
LVP =	Low-Voltage Programming Enable
OFF	High-voltage on MCLR/VPP must be used for programming
ON	Low-voltage programming enabled
*/

#elif	defined(_18F1230) || defined(_18F1330)

#pragma config IESO = OFF
#pragma config OSC = INTIO2
#pragma config FCMEN = OFF
/*
Register: CONFIG1H @ 0x300001

IESO =	Internal/External Oscillator Switchover bit
OFF	Oscillator Switchover mode disabled
ON	Oscillator Switchover mode enabled
OSC =	Oscillator
RC	External RC oscillator, CLKO function on RA6
RCIO	External RC oscillator, port function on RA6
XT	XT Oscillator
LP	LP Oscillator
HSPLL	HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1)
INTIO1	Internal oscillator, CLKO function on RA6, port function on RA7
ECIO	EC oscillator, port function on RA6
EC	EC oscillator, CLKO function on RA6
INTIO2	Internal oscillator, port function on RA6 and RA7
HS	HS Oscillator
FCMEN =	Fail-Safe Clock Monitor Enable bit
OFF	Fail-Safe Clock Monitor disabled
ON	Fail-Safe Clock Monitor enabled
*/
#pragma config BOR = OFF
#pragma config PWRT = ON
/*
Register: CONFIG2L @ 0x300002

BOR =	Brown-out Reset Enable bits
BOHW	Brown-out Reset enabled in hardware only (SBOREN is disabled)
BOACTIVE	Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
OFF	Brown-out Reset disabled in hardware and software
SBORENCTRL	Brown-out Reset enabled and controlled by software (SBOREN is enabled)
BORV =	Brown-out Reset Voltage bits
1	
2	
3	Minimum setting
0	Maximum setting
PWRT =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
*/

#pragma config WDTPS = 32768
#pragma config WDT = OFF
/*
Register: CONFIG2H @ 0x300003

WDTPS =	Watchdog Timer Postscale Select bits
8	1:8
1	1:1
32768	1:32768
1024	1:1024
2	1:2
32	1:32
16	1:16
16384	1:16384
128	1:128
4096	1:4096
64	1:64
8192	1:8192
2048	1:2048
512	1:512
256	1:256
4	1:4
WDT =	Watchdog Timer Enable bit
OFF	WDT disabled (control is placed on the SWDTEN bit)
ON	WDT enabled
*/
#pragma config PWMPIN = OFF
#pragma config HPOL = HIGH
#pragma config LPOL = LOW
/*
Register: CONFIG3L @ 0x300004

PWMPIN =	PWM Output Pins Reset State Control bit
OFF	PWM outputs disabled upon Reset
ON	PWM outputs drive active states upon Reset
HPOL =	High Side Transistors Polarity bit (Odd PWM Output Polarity Control bit)
HIGH	PWM1, PWM3 and PWM5 are active-high (default)
LOW	PWM1, PWM3 and PWM5 are active-low
LPOL =	Low-Side Transistors Polarity bit (Even PWM Output Polarity Control bit)
HIGH	PWM0, PWM2 and PWM4 are active-high (default)
LOW	PWM0, PWM2 and PWM4 are active-low
*/
#pragma config T1OSCMX = LOW
#pragma config FLTAMX = RA7
#pragma config MCLRE = OFF
/*
Register: CONFIG3H @ 0x300005

T1OSCMX =	T1OSO/T1CKI MUX bit
HIGH	T1OSO/T1CKI pin resides on RA6
LOW	T1OSO/T1CKI pin resides on RB2
FLTAMX =	FLTA Mux bit
RA5	FLTA input is muxed onto RA5
RA7	FLTA input is muxed onto RA7
MCLRE =	Master Clear Enable bit
OFF	RA5 input pin enabled, MCLR pin disabled
ON	MCLR pin enabled, RA5 input pin disabled
*/
#pragma config DEBUG = OFF
#pragma config STVREN = OFF
#pragma config XINST = OFF
#pragma config BBSIZ = 256
/*
Register: CONFIG4L @ 0x300006

DEBUG =	Background Debugger Enable bit
OFF	Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins
ON	Background debugger enabled, RB6 and RB7 are dedicated to In-Circuit Debug
STVREN =	Stack Overflow/Underflow Reset Enable bit
OFF	Reset on stack overflow/underflow disabled
ON	Reset on stack overflow/underflow enabled
XINST =	Extended Instruction Set Enable bit
OFF	Instruction set extension and Indexed Addressing mode disabled
ON	Instruction set extension and Indexed Addressing mode enabled
BBSIZ =	Boot Block Size Select bits
BB512	512 Words (1024 Bytes) Boot Block size
BB256	256 Words (512 Bytes) Boot Block size
*/
#pragma config CP0 = OFF
#pragma config CP1 = OFF
/*
Register: CONFIG5L @ 0x300008

CP0 =	Code Protection bit Block 0 (000400-0007FF)
OFF	Block 0 is not code-protected
ON	Block 0 is code-protected
CP1 =	Code Protection bit Block 1 (000800-000FFF)
OFF	Block 1 is not code-protected
ON	Block 1 is code-protected
*/
#pragma config CPD = OFF
#pragma config CPB = OFF
/*
Register: CONFIG5H @ 0x300009

CPD =	Code Protection bit (Data EEPROM)
OFF	Data EEPROM is not code-protected
ON	Data EEPROM is code-protected
CPB =	Code Protection bit (Boot Block Memory Area)
OFF	Boot Block is not code-protected
ON	Boot Block is code-protected
*/
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
/*
Register: CONFIG6L @ 0x30000A

WRT0 =	Write Protection bit Block 0 (000400-0007FF)
OFF	Block 0 is not write-protected
ON	Block 0 is write-protected
WRT1 =	Write Protection bit Block 1 (000800-000FFF)
OFF	Block 1 is not write-protected
ON	Block 1 is write-protected
*/
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
/*
Register: CONFIG6H @ 0x30000B

WRTB =	Write Protection bit (Boot Block Memory Area)
OFF	Boot Block is not write-protected
ON	Boot Block is write-protected
WRTC =	Write Protection bit (Configuration Registers)
OFF	Configuration registers are not write-protected
ON	Configuration registers are write-protected
WRTD =	Write Protection bit (Data EEPROM)
OFF	Data EEPROM is not write-protected
ON	Data EEPROM is write-protected
*/
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
/*
Register: CONFIG7L @ 0x30000C

EBTR0 =	Table Read Protection bit Block 0 (000400-0007FF)
OFF	Block 0 is not protected from table reads executed in other blocks
ON	Block 0 is protected from table reads executed in other blocks
EBTR1 =	Table Read Protection bit Block 1 (000800-000FFF)
OFF	Block 1 is not protected from table reads executed in other blocks
ON	Block 1 is protected from table reads executed in other blocks
*/
#pragma config EBTRB = OFF
/*
Register: CONFIG7H @ 0x30000D

EBTRB =	Table Read Protection bit (Boot Block Memory Area)
OFF	Boot Block is not protected from table reads executed in other blocks
ON	Boot Block is protected from table reads executed in other blocks
*/

#elif		defined(_18F13K22) || defined(_18F14K22) || defined(_18LF13K22) || defined(_18LF14K22)

#pragma config IESO = OFF		//IESO =	Internal/External Oscillator Switchover bit: OFF	Oscillator Switchover mode disabled, ON	Oscillator Switchover mode enabled
#pragma config PLLEN = OFF		//PLLEN =	4 X PLL Enable bit, OFF	PLL is under software control, ON	Oscillator multiplied by 4
#pragma config FOSC = XT		//ECM, ERCCLKOUT, ECCLKOUTH, XT, LP, ECCLKOUTL, IRC, ECCLKOUTM, IRCCLKOUT, ECH, ECL, ERC, HS
#pragma config FCMEN = OFF		//FCMEN =	Fail-Safe Clock Monitor Enable, OFF	Fail-Safe Clock Monitor disabled, ON	Fail-Safe Clock Monitor enabled
#pragma config PCLKEN = OFF		//PCLKEN =	Primary Clock Enable bit, OFF	Primary clock is under software control, ON	Primary clock enabled
#pragma config BOREN = OFF		//BOREN =	Brown-out Reset Enable bits, NOSLP	Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled), OFF	Brown-out Reset disabled in hardware and software, ON	Brown-out Reset enabled and controlled by software (SBOREN is enabled), SBORDIS	Brown-out Reset enabled in hardware only (SBOREN is disabled)
#pragma config BORV = 19		//BORV =	Brown Out Reset Voltage bits, 19	VBOR set to 1.9 V nominal, 27	VBOR set to 2.7 V nominal, 22	VBOR set to 2.2 V nominal, 30	VBOR set to 3.0 V nominal
#pragma config PWRTEN = OFF		//PWRTEN =	Power-up Timer Enable bit, OFF	PWRT disabled, ON	PWRT enabled
#pragma config WDTPS = 32768	//WDTPS =	Watchdog Timer Postscale Select bits, 1..32768
#pragma config WDTEN = OFF		//WDTEN =	Watchdog Timer Enable bit, OFF	WDT is controlled by SWDTEN bit of the WDTCON register, ON	WDT is always enabled. SWDTEN bit has no effect.
#pragma config MCLRE = OFF		//MCLRE =	MCLR Pin Enable bit, OFF	RA3 input pin enabled; MCLR disabled, ON	MCLR pin enabled, RA3 input pin disabled
#pragma config HFOFST = OFF		//HFOFST =	HFINTOSC Fast Start-up bit, OFF	The system clock is held off until the HFINTOSC is stable., ON	HFINTOSC starts clocking the CPU without waiting for the oscillator to stablize.
#pragma config DEBUG = OFF		//DEBUG =	Background Debugger Enable bit, OFF	Background debugger disabled, RA0 and RA1 configured as general purpose I/O pins, ON	Background debugger enabled, RA0 and RA1 are dedicated to In-Circuit Debug
#pragma config STVREN = OFF		//STVREN =	Stack Full/Underflow Reset Enable bit, OFF	Stack full/underflow will not cause Reset, ON	Stack full/underflow will cause Reset
#pragma config XINST = OFF		//XINST =	Extended Instruction Set Enable bit, OFF	Instruction set extension and Indexed Addressing mode disabled (Legacy mode), ON	Instruction set extension and Indexed Addressing mode enabled
#pragma config BBSIZ = OFF		//BBSIZ =	Boot Block Size Select bit, OFF	1kW boot block size, ON	2kW boot block size
#pragma config LVP = OFF		//LVP =	Single-Supply ICSP Enable bit, OFF	Single-Supply ICSP disabled, ON	Single-Supply ICSP enabled
#pragma config CP0 = OFF		//CP0 =	Code Protection bit, OFF	Block 0 not code-protected, ON	Block 0 code-protected
#pragma config CP1 = OFF		//CP1 =	Code Protection bit, OFF	Block 1 not code-protected, ON	Block 1 code-protected
#pragma config CPD = OFF		//CPD =	Data EEPROM Code Protection bit, OFF	Data EEPROM not code-protected, ON	Data EEPROM code-protected
#pragma config CPB = OFF		//CPB =	Boot Block Code Protection bit, OFF	Boot block not code-protected, ON	Boot block code-protected
#pragma config WRT0 = OFF		//WRT0 =	Write Protection bit, OFF	Block 0 not write-protected, ON	Block 0 write-protected
#pragma config WRT1 = OFF		//WRT1 =	Write Protection bit, OFF	Block 1 not write-protected, ON	Block 1 write-protected
#pragma config WRTB = OFF		//WRTB =	Boot Block Write Protection bit, OFF	Boot block not write-protected, ON	Boot block write-protected
#pragma config WRTC = OFF		//WRTC =	Configuration Register Write Protection bit, OFF	Configuration registers not write-protected, ON	Configuration registers write-protected
#pragma config WRTD = OFF		//WRTD =	Data EEPROM Write Protection bit, OFF	Data EEPROM not write-protected, ON	Data EEPROM write-protected
#pragma config EBTR0 = OFF		//EBTR0 =	Table Read Protection bit, OFF	Block 0 not protected from table reads executed in other blocks, ON	Block 0 protected from table reads executed in other blocks
#pragma config EBTR1 = OFF		//EBTR1 =	Table Read Protection bit, OFF	Block 1 not protected from table reads executed in other blocks, ON	Block 1 protected from table reads executed in other blocks
#pragma config EBTRB = OFF		//EBTRB =	Boot Block Table Read Protection bit, OFF	Boot block not protected from table reads executed in other blocks, ON	Boot block protected from table reads executed in other blocks

/*18F14K22 Support Information

Register: CONFIG1H @ 0x300001

IESO =	Internal/External Oscillator Switchover bit
OFF	Oscillator Switchover mode disabled
ON	Oscillator Switchover mode enabled
PLLEN =	4 X PLL Enable bit
OFF	PLL is under software control
ON	Oscillator multiplied by 4
FOSC =	Oscillator Selection bits
ECM	EC (medium)
ERCCLKOUT	External RC oscillator, CLKOUT function on OSC2
ECCLKOUTH	EC, CLKOUT function on OSC2 (high)
XT	XT oscillator
LP	LP oscillator
ECCLKOUTL	EC, CLKOUT function on OSC2 (low)
IRC	Internal RC oscillator
ECCLKOUTM	EC, CLKOUT function on OSC2 (medium)
IRCCLKOUT	Internal RC oscillator, CLKOUT function on OSC2
ECH	EC (high)
ECL	EC (low)
ERC	External RC oscillator
HS	HS oscillator
FCMEN =	Fail-Safe Clock Monitor Enable
OFF	Fail-Safe Clock Monitor disabled
ON	Fail-Safe Clock Monitor enabled
PCLKEN =	Primary Clock Enable bit
OFF	Primary clock is under software control
ON	Primary clock enabled
Register: CONFIG2L @ 0x300002

BOREN =	Brown-out Reset Enable bits
NOSLP	Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
OFF	Brown-out Reset disabled in hardware and software
ON	Brown-out Reset enabled and controlled by software (SBOREN is enabled)
SBORDIS	Brown-out Reset enabled in hardware only (SBOREN is disabled)
BORV =	Brown Out Reset Voltage bits
19	VBOR set to 1.9 V nominal
27	VBOR set to 2.7 V nominal
22	VBOR set to 2.2 V nominal
30	VBOR set to 3.0 V nominal
PWRTEN =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
Register: CONFIG2H @ 0x300003

WDTPS =	Watchdog Timer Postscale Select bits
8	1:8
1	1:1
32768	1:32768
1024	1:1024
2	1:2
32	1:32
16	1:16
16384	1:16384
128	1:128
4096	1:4096
64	1:64
8192	1:8192
2048	1:2048
512	1:512
256	1:256
4	1:4
WDTEN =	Watchdog Timer Enable bit
OFF	WDT is controlled by SWDTEN bit of the WDTCON register
ON	WDT is always enabled. SWDTEN bit has no effect.
Register: CONFIG3H @ 0x300005

MCLRE =	MCLR Pin Enable bit
OFF	RA3 input pin enabled; MCLR disabled
ON	MCLR pin enabled, RA3 input pin disabled
HFOFST =	HFINTOSC Fast Start-up bit
OFF	The system clock is held off until the HFINTOSC is stable.
ON	HFINTOSC starts clocking the CPU without waiting for the oscillator to stablize.
Register: CONFIG4L @ 0x300006

DEBUG =	Background Debugger Enable bit
OFF	Background debugger disabled, RA0 and RA1 configured as general purpose I/O pins
ON	Background debugger enabled, RA0 and RA1 are dedicated to In-Circuit Debug
STVREN =	Stack Full/Underflow Reset Enable bit
OFF	Stack full/underflow will not cause Reset
ON	Stack full/underflow will cause Reset
XINST =	Extended Instruction Set Enable bit
OFF	Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
ON	Instruction set extension and Indexed Addressing mode enabled
BBSIZ =	Boot Block Size Select bit
OFF	1kW boot block size
ON	2kW boot block size
LVP =	Single-Supply ICSP Enable bit
OFF	Single-Supply ICSP disabled
ON	Single-Supply ICSP enabled
Register: CONFIG5L @ 0x300008

CP0 =	Code Protection bit
OFF	Block 0 not code-protected
ON	Block 0 code-protected
CP1 =	Code Protection bit
OFF	Block 1 not code-protected
ON	Block 1 code-protected
Register: CONFIG5H @ 0x300009

CPD =	Data EEPROM Code Protection bit
OFF	Data EEPROM not code-protected
ON	Data EEPROM code-protected
CPB =	Boot Block Code Protection bit
OFF	Boot block not code-protected
ON	Boot block code-protected
Register: CONFIG6L @ 0x30000A

WRT0 =	Write Protection bit
OFF	Block 0 not write-protected
ON	Block 0 write-protected
WRT1 =	Write Protection bit
OFF	Block 1 not write-protected
ON	Block 1 write-protected
Register: CONFIG6H @ 0x30000B

WRTB =	Boot Block Write Protection bit
OFF	Boot block not write-protected
ON	Boot block write-protected
WRTC =	Configuration Register Write Protection bit
OFF	Configuration registers not write-protected
ON	Configuration registers write-protected
WRTD =	Data EEPROM Write Protection bit
OFF	Data EEPROM not write-protected
ON	Data EEPROM write-protected
Register: CONFIG7L @ 0x30000C

EBTR0 =	Table Read Protection bit
OFF	Block 0 not protected from table reads executed in other blocks
ON	Block 0 protected from table reads executed in other blocks
EBTR1 =	Table Read Protection bit
OFF	Block 1 not protected from table reads executed in other blocks
ON	Block 1 protected from table reads executed in other blocks
Register: CONFIG7H @ 0x30000D

EBTRB =	Boot Block Table Read Protection bit
OFF	Boot block not protected from table reads executed in other blocks
ON	Boot block protected from table reads executed in other blocks
Register: IDLOC0 @ 0x200000

Register: IDLOC1 @ 0x200001

Register: IDLOC2 @ 0x200002

Register: IDLOC3 @ 0x200003

Register: IDLOC4 @ 0x200004

Register: IDLOC5 @ 0x200005

Register: IDLOC6 @ 0x200006

Register: IDLOC7 @ 0x200007
*/
#elif		defined(_18F13K50) || defined(_18F14K50) || defined(_18LF13K50) || defined(_18LF14K50)

#pragma config CPUDIV = NOCLKDIV
#pragma config USBDIV = OFF
#pragma config IESO = OFF
#pragma config PLLEN = OFF
#pragma config FOSC = IRC
#pragma config FCMEN = OFF
#pragma config PCLKEN = OFF
/*
Register: CONFIG1L @ 0x300000

CPUDIV =	CPU System Clock Selection bits
CLKDIV2	CPU System Clock divided by 2
CLKDIV3	CPU System Clock divided by 3
NOCLKDIV	No CPU System Clock divide
CLKDIV4	CPU System Clock divided by 4
USBDIV =	USB Clock Selection bit
OFF	USB clock comes directly from the OSC1/OSC2 oscillator block; no divide
ON	USB clock comes from the OSC1/OSC2 divided by 2

Register: CONFIG1H @ 0x300001

IESO =	Internal/External Oscillator Switchover bit
OFF	Oscillator Switchover mode disabled
ON	Oscillator Switchover mode enabled
PLLEN =	4 X PLL Enable bit
OFF	PLL is under software control
ON	Oscillator multiplied by 4
FOSC =	Oscillator Selection bits
ECM	EC (medium)
ERCCLKOUT	External RC oscillator, CLKOUT function on OSC2
ECCLKOUTH	EC, CLKOUT function on OSC2 (high)
XT	XT oscillator
LP	LP oscillator
ECCLKOUTL	EC, CLKOUT function on OSC2 (low)
IRC	Internal RC oscillator
ECCLKOUTM	EC, CLKOUT function on OSC2 (medium)
IRCCLKOUT	Internal RC oscillator, CLKOUT function on OSC2
ECH	EC (high)
ECL	EC (low)
ERC	External RC oscillator
HS	HS oscillator
FCMEN =	Fail-Safe Clock Monitor Enable
OFF	Fail-Safe Clock Monitor disabled
ON	Fail-Safe Clock Monitor enabled
PCLKEN =	Primary Clock Enable bit
OFF	Primary clock is under software control
ON	Primary clock enabled
*/
#pragma config BOREN = OFF
#pragma config BORV = 19
#pragma config PWRTEN = ON
#pragma config WDTPS = 32768
#pragma config WDTEN = OFF
/*
Register: CONFIG2L @ 0x300002

BOREN =	Brown-out Reset Enable bits
NOSLP	Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
OFF	Brown-out Reset disabled in hardware and software
ON	Brown-out Reset enabled and controlled by software (SBOREN is enabled)
SBORDIS	Brown-out Reset enabled in hardware only (SBOREN is disabled)
BORV =	Brown-out Reset Voltage bits
19	VBOR set to 1.9 V nominal
27	VBOR set to 2.7 V nominal
22	VBOR set to 2.2 V nominal
30	VBOR set to 3.0 V nominal
PWRTEN =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
Register: CONFIG2H @ 0x300003

WDTPS =	Watchdog Timer Postscale Select bits
8	1:8
1	1:1
32768	1:32768
1024	1:1024
2	1:2
32	1:32
16	1:16
16384	1:16384
128	1:128
4096	1:4096
64	1:64
8192	1:8192
2048	1:2048
512	1:512
256	1:256
4	1:4
WDTEN =	Watchdog Timer Enable bit
OFF	WDT is controlled by SWDTEN bit of the WDTCON register
ON	WDT is always enabled. SWDTEN bit has no effect.
*/
#pragma config MCLRE = OFF
#pragma config HFINTOSC = OFF
/*
Register: CONFIG3H @ 0x300005

MCLRE =	MCLR Pin Enable bit
OFF	RA3 input pin enabled; MCLR disabled
ON	MCLR pin enabled; RA3 input pin disabled
HFOFST =	HFINTOSC Fast Start-up bit
OFF	The system clock is held off until the HFINTOSC is stable.
ON	HFINTOSC starts clocking the CPU without waiting for the oscillator to stablize.
*/

#pragma config DEBUG = OFF
#pragma config STVREN = OFF
#pragma config XINST = OFF
#pragma config BBSIZ = OFF
#pragma config LVP = OFF
/*
Register: CONFIG4L @ 0x300006
DEBUG =	Background Debugger Enable bit
OFF	Background debugger disabled, RA0 and RA1 configured as general purpose I/O pins
ON	Background debugger enabled, RA0 and RA1 are dedicated to In-Circuit Debug
STVREN =	Stack Full/Underflow Reset Enable bit
OFF	Stack full/underflow will not cause Reset
ON	Stack full/underflow will cause Reset
XINST =	Extended Instruction Set Enable bit
OFF	Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
ON	Instruction set extension and Indexed Addressing mode enabled
BBSIZ =	Boot Block Size Select bit
OFF	1kW boot block size
ON	2kW boot block size
LVP =	Single-Supply ICSP Enable bit
OFF	Single-Supply ICSP disabled
ON	Single-Supply ICSP enabled
*/
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CPD = OFF
#pragma config CPB = OFF
/*
Register: CONFIG5L @ 0x300008

CP0 =	Code Protection bit
OFF	Block 0 not code-protected
ON	Block 0 code-protected
CP1 =	Code Protection bit
OFF	Block 1 not code-protected
ON	Block 1 code-protected
Register: CONFIG5H @ 0x300009

CPD =	Data EEPROM Code Protection bit
OFF	Data EEPROM not code-protected
ON	Data EEPROM code-protected
CPB =	Boot Block Code Protection bit
OFF	Boot block not code-protected
ON	Boot block code-protected
*/
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
/*
Register: CONFIG6L @ 0x30000A

WRT0 =	Table Write Protection bit
OFF	Block 0 not write-protected
ON	Block 0 write-protected
WRT1 =	Table Write Protection bit
OFF	Block 1 not write-protected
ON	Block 1 write-protected
Register: CONFIG6H @ 0x30000B

WRTB =	Boot Block Write Protection bit
OFF	Boot block not write-protected
ON	Boot block write-protected
WRTC =	Configuration Register Write Protection bit
OFF	Configuration registers not write-protected
ON	Configuration registers write-protected
WRTD =	Data EEPROM Write Protection bit
OFF	Data EEPROM not write-protected
ON	Data EEPROM write-protected
*/
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
/*Register: CONFIG7L @ 0x30000C

EBTR0 =	Table Read Protection bit
OFF	Block 0 not protected from table reads executed in other blocks
ON	Block 0 protected from table reads executed in other blocks
EBTR1 =	Table Read Protection bit
OFF	Block 1 not protected from table reads executed in other blocks
ON	Block 1 protected from table reads executed in other blocks
Register: CONFIG7H @ 0x30000D

EBTRB =	Boot Block Table Read Protection bit
OFF	Boot block not protected from table reads executed in other blocks
ON	Boot block protected from table reads executed in other blocks
*/

#elif	defined(_18F2420) || defined(_18F2520) || defined(_18F4420) || defined(_18F4520)

#pragma config IESO = OFF
#pragma config OSC = INTIO67
#pragma config FCMEN = OFF
/*
Register: CONFIG1H @ 0x300001

IESO =	Internal/External Oscillator Switchover bit
OFF	Oscillator Switchover mode disabled
ON	Oscillator Switchover mode enabled
OSC =	Oscillator Selection bits
RCIO6	External RC oscillator, port function on RA6
RC	External RC oscillator, CLKO function on RA6
INTIO7	Internal oscillator block, CLKO function on RA6, port function on RA7
XT	XT oscillator
LP	LP oscillator
HSPLL	HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1)
ECIO6	EC oscillator, port function on RA6
EC	EC oscillator, CLKO function on RA6
INTIO67	Internal oscillator block, port function on RA6 and RA7
HS	HS oscillator
FCMEN =	Fail-Safe Clock Monitor Enable bit
OFF	Fail-Safe Clock Monitor disabled
ON	Fail-Safe Clock Monitor enabled
*/
#pragma config BOREN = OFF
#pragma config BORV = 3
#pragma config PWRT = ON
#pragma config WDTPS = 32768
#pragma config WDT = OFF
/*
Register: CONFIG2L @ 0x300002

BOREN =	Brown-out Reset Enable bits
NOSLP	Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
OFF	Brown-out Reset disabled in hardware and software
ON	Brown-out Reset enabled and controlled by software (SBOREN is enabled)
SBORDIS	Brown-out Reset enabled in hardware only (SBOREN is disabled)
BORV =	Brown Out Reset Voltage bits
1	
2	
3	Minimum setting
0	Maximum setting
PWRT =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
Register: CONFIG2H @ 0x300003

WDTPS =	Watchdog Timer Postscale Select bits
8	1:8
1	1:1
32768	1:32768
1024	1:1024
2	1:2
32	1:32
16	1:16
16384	1:16384
128	1:128
4096	1:4096
64	1:64
8192	1:8192
2048	1:2048
512	1:512
256	1:256
4	1:4
WDT =	Watchdog Timer Enable bit
OFF	WDT disabled (control is placed on the SWDTEN bit)
ON	WDT enabled
*/
#pragma config CCP2MX = PORTC
#pragma config PBADEN = OFF
#pragma config LPT1OSC = OFF
#pragma config MCLRE = OFF
/*
Register: CONFIG3H @ 0x300005

CCP2MX =	CCP2 MUX bit
PORTC	CCP2 input/output is multiplexed with RC1
PORTBE	CCP2 input/output is multiplexed with RB3
PBADEN =	PORTB A/D Enable bit
OFF	PORTB<4:0> pins are configured as digital I/O on Reset
ON	PORTB<4:0> pins are configured as analog input channels on Reset
LPT1OSC =	Low-Power Timer1 Oscillator Enable bit
OFF	Timer1 configured for higher power operation
ON	Timer1 configured for low-power operation
MCLRE =	MCLR Pin Enable bit
OFF	RE3 input pin enabled; MCLR disabled
ON	MCLR pin enabled; RE3 input pin disabled
*/
#pragma config DEBUG = OFF
#pragma config STVREN = OFF
#pragma config XINST = OFF
#pragma config LVP = OFF
/*
Register: CONFIG4L @ 0x300006

DEBUG =	Background Debugger Enable bit
OFF	Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins
ON	Background debugger enabled, RB6 and RB7 are dedicated to In-Circuit Debug
STVREN =	Stack Full/Underflow Reset Enable bit
OFF	Stack full/underflow will not cause Reset
ON	Stack full/underflow will cause Reset
XINST =	Extended Instruction Set Enable bit
OFF	Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
ON	Instruction set extension and Indexed Addressing mode enabled
LVP =	Single-Supply ICSP Enable bit
OFF	Single-Supply ICSP disabled
ON	Single-Supply ICSP enabled
*/
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPD = OFF
#pragma config CPB = OFF
/*
Register: CONFIG5L @ 0x300008

CP0 =	Code Protection bit
OFF	Block 0 (000800-001FFFh) not code-protected
ON	Block 0 (000800-001FFFh) code-protected
CP1 =	Code Protection bit
OFF	Block 1 (002000-003FFFh) not code-protected
ON	Block 1 (002000-003FFFh) code-protected
CP2 =	Code Protection bit
OFF	Block 2 (004000-005FFFh) not code-protected
ON	Block 2 (004000-005FFFh) code-protected
CP3 =	Code Protection bit
OFF	Block 3 (006000-007FFFh) not code-protected
ON	Block 3 (006000-007FFFh) code-protected
Register: CONFIG5H @ 0x300009

CPD =	Data EEPROM Code Protection bit
OFF	Data EEPROM not code-protected
ON	Data EEPROM code-protected
CPB =	Boot Block Code Protection bit
OFF	Boot block (000000-0007FFh) not code-protected
ON	Boot block (000000-0007FFh) code-protected
*/
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
/*
Register: CONFIG6L @ 0x30000A

WRT0 =	Write Protection bit
OFF	Block 0 (000800-001FFFh) not write-protected
ON	Block 0 (000800-001FFFh) write-protected
WRT1 =	Write Protection bit
OFF	Block 1 (002000-003FFFh) not write-protected
ON	Block 1 (002000-003FFFh) write-protected
WRT2 =	Write Protection bit
OFF	Block 2 (004000-005FFFh) not write-protected
ON	Block 2 (004000-005FFFh) write-protected
WRT3 =	Write Protection bit
OFF	Block 3 (006000-007FFFh) not write-protected
ON	Block 3 (006000-007FFFh) write-protected
Register: CONFIG6H @ 0x30000B

WRTB =	Boot Block Write Protection bit
OFF	Boot block (000000-0007FFh) not write-protected
ON	Boot block (000000-0007FFh) write-protected
WRTC =	Configuration Register Write Protection bit
OFF	Configuration registers (300000-3000FFh) not write-protected
ON	Configuration registers (300000-3000FFh) write-protected
WRTD =	Data EEPROM Write Protection bit
OFF	Data EEPROM not write-protected
ON	Data EEPROM write-protected
*/
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF
/*
Register: CONFIG7L @ 0x30000C

EBTR0 =	Table Read Protection bit
OFF	Block 0 (000800-001FFFh) not protected from table reads executed in other blocks
ON	Block 0 (000800-001FFFh) protected from table reads executed in other blocks
EBTR1 =	Table Read Protection bit
OFF	Block 1 (002000-003FFFh) not protected from table reads executed in other blocks
ON	Block 1 (002000-003FFFh) protected from table reads executed in other blocks
EBTR2 =	Table Read Protection bit
OFF	Block 2 (004000-005FFFh) not protected from table reads executed in other blocks
ON	Block 2 (004000-005FFFh) protected from table reads executed in other blocks
EBTR3 =	Table Read Protection bit
OFF	Block 3 (006000-007FFFh) not protected from table reads executed in other blocks
ON	Block 3 (006000-007FFFh) protected from table reads executed in other blocks
Register: CONFIG7H @ 0x30000D

EBTRB =	Boot Block Table Read Protection bit
OFF	Boot block (000000-0007FFh) not protected from table reads executed in other blocks
ON	Boot block (000000-0007FFh) protected from table reads executed in other blocks
*/

//18fxxk20
#elif	defined(_18F23K20) || defined(_18F24K20) || defined(_18F25K20) || defined(_18F26K20) || \
       	defined(_18F43K20) || defined(_18F44K20) || defined(_18F45K20) || defined(_18F46K20) || \
	defined(_18LF23K20) || defined(_18LF24K20) || defined(_18LF25K20) || defined(_18LF26K20) || \
       	defined(_18LF43K20) || defined(_18LF44K20) || defined(_18LF45K20) || defined(_18LF46K20)

#pragma config IESO = OFF
#pragma config FOSC = INTIO67
#pragma config FCMEN = OFF

/*
Register: CONFIG1H @ 0x300001

IESO =	Internal/External Oscillator Switchover bit
OFF	Oscillator Switchover mode disabled
ON	Oscillator Switchover mode enabled
FOSC =	Oscillator Selection bits
RCIO6	External RC oscillator, port function on RA6
RC	External RC oscillator, CLKOUT function on RA6
INTIO7	Internal oscillator block, CLKOUT function on RA6, port function on RA7
XT	XT oscillator
LP	LP oscillator
HSPLL	HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1)
ECIO6	EC oscillator, port function on RA6
EC	EC oscillator, CLKOUT function on RA6
INTIO67	Internal oscillator block, port function on RA6 and RA7
HS	HS oscillator
FCMEN =	Fail-Safe Clock Monitor Enable bit
OFF	Fail-Safe Clock Monitor disabled
ON	Fail-Safe Clock Monitor enabled
*/
#pragma config BOREN = OFF
#pragma config BORV = 18
#pragma config PWRT = ON
#pragma config WDTPS = 32768
#pragma config WDTEN = OFF
/*
Register: CONFIG2L @ 0x300002

BOREN =	Brown-out Reset Enable bits
NOSLP	Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
OFF	Brown-out Reset disabled in hardware and software
ON	Brown-out Reset enabled and controlled by software (SBOREN is enabled)
SBORDIS	Brown-out Reset enabled in hardware only (SBOREN is disabled)
BORV =	Brown Out Reset Voltage bits
18	VBOR set to 1.8 V nominal
27	VBOR set to 2.7 V nominal
22	VBOR set to 2.2 V nominal
30	VBOR set to 3.0 V nominal
PWRT =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
Register: CONFIG2H @ 0x300003

WDTPS =	Watchdog Timer Postscale Select bits
8	1:8
1	1:1
32768	1:32768
1024	1:1024
2	1:2
32	1:32
16	1:16
16384	1:16384
128	1:128
4096	1:4096
64	1:64
8192	1:8192
2048	1:2048
512	1:512
256	1:256
4	1:4
WDTEN =	Watchdog Timer Enable bit
OFF	WDT is controlled by SWDTEN bit of the WDTCON register
ON	WDT is always enabled. SWDTEN bit has no effect
*/
#pragma config CCP2MX = PORTC
#pragma config PBADEN = OFF
#pragma config LPT1OSC = OFF
#pragma config MCLRE = OFF
#pragma config HFOFST = OFF
/*
Register: CONFIG3H @ 0x300005

CCP2MX =	CCP2 MUX bit
PORTC	CCP2 input/output is multiplexed with RC1
PORTBE	CCP2 input/output is multiplexed with RB3
PBADEN =	PORTB A/D Enable bit
OFF	PORTB<4:0> pins are configured as digital I/O on Reset
ON	PORTB<4:0> pins are configured as analog input channels on Reset
LPT1OSC =	Low-Power Timer1 Oscillator Enable bit
OFF	Timer1 configured for higher power operation
ON	Timer1 configured for low-power operation
MCLRE =	MCLR Pin Enable bit
OFF	RE3 input pin enabled; MCLR disabled
ON	MCLR pin enabled; RE3 input pin disabled
HFOFST =	HFINTOSC Fast Start-up
OFF	The system clock is held off until the HFINTOSC is stable.
ON	HFINTOSC starts clocking the CPU without waiting for the oscillator to stablize.
*/
#pragma config DEBUG = OFF
#pragma config STVREN = OFF
#pragma config XINST = OFF
#pragma config LVP = OFF
/*
Register: CONFIG4L @ 0x300006

DEBUG =	Background Debugger Enable bit
OFF	Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins
ON	Background debugger enabled, RB6 and RB7 are dedicated to In-Circuit Debug
STVREN =	Stack Full/Underflow Reset Enable bit
OFF	Stack full/underflow will not cause Reset
ON	Stack full/underflow will cause Reset
XINST =	Extended Instruction Set Enable bit
OFF	Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
ON	Instruction set extension and Indexed Addressing mode enabled
LVP =	Single-Supply ICSP Enable bit
OFF	Single-Supply ICSP disabled
ON	Single-Supply ICSP enabled
*/
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPD = OFF
#pragma config CPB = OFF
/*
Register: CONFIG5L @ 0x300008

CP0 =	Code Protection Block 0
OFF	Block 0 (000800-003FFFh) not code-protected
ON	Block 0 (000800-003FFFh) code-protected
CP1 =	Code Protection Block 1
OFF	Block 1 (004000-007FFFh) not code-protected
ON	Block 1 (004000-007FFFh) code-protected
CP2 =	Code Protection Block 2
OFF	Block 2 (008000-00BFFFh) not code-protected
ON	Block 2 (008000-00BFFFh) code-protected
CP3 =	Code Protection Block 3
OFF	Block 3 (00C000-00FFFFh) not code-protected
ON	Block 3 (00C000-00FFFFh) code-protected
Register: CONFIG5H @ 0x300009

CPD =	Data EEPROM Code Protection bit
OFF	Data EEPROM not code-protected
ON	Data EEPROM code-protected
CPB =	Boot Block Code Protection bit
OFF	Boot block (000000-0007FFh) not code-protected
ON	Boot block (000000-0007FFh) code-protected
*/
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
/*
Register: CONFIG6L @ 0x30000A

WRT0 =	Write Protection Block 0
OFF	Block 0 (000800-003FFFh) not write-protected
ON	Block 0 (000800-003FFFh) write-protected
WRT1 =	Write Protection Block 1
OFF	Block 1 (004000-007FFFh) not write-protected
ON	Block 1 (004000-007FFFh) write-protected
WRT2 =	Write Protection Block 2
OFF	Block 2 (008000-00BFFFh) not write-protected
ON	Block 2 (008000-00BFFFh) write-protected
WRT3 =	Write Protection Block 3
OFF	Block 3 (00C000h-00FFFFh) not write-protected
ON	Block 3 (00C000h-00FFFFh) write-protected
Register: CONFIG6H @ 0x30000B

WRTB =	Boot Block Write Protection bit
OFF	Boot Block (000000-0007FFh) not write-protected
ON	Boot Block (000000-0007FFh) write-protected
WRTC =	Configuration Register Write Protection bit
OFF	Configuration registers (300000-3000FFh) not write-protected
ON	Configuration registers (300000-3000FFh) write-protected
WRTD =	Data EEPROM Write Protection bit
OFF	Data EEPROM not write-protected
ON	Data EEPROM write-protected
*/
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF
/*
Register: CONFIG7L @ 0x30000C

EBTR0 =	Table Read Protection Block 0
OFF	Block 0 (000800-003FFFh) not protected from table reads executed in other blocks
ON	Block 0 (000800-003FFFh) protected from table reads executed in other blocks
EBTR1 =	Table Read Protection Block 1
OFF	Block 1 (004000-007FFFh) not protected from table reads executed in other blocks
ON	Block 1 (004000-007FFFh) protected from table reads executed in other blocks
EBTR2 =	Table Read Protection Block 2
OFF	Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks
ON	Block 2 (008000-00BFFFh) protected from table reads executed in other blocks
EBTR3 =	Table Read Protection Block 3
OFF	Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks
ON	Block 3 (00C000-00FFFFh) protected from table reads executed in other blocks
Register: CONFIG7H @ 0x30000D

EBTRB =	Boot Block Table Read Protection bit
OFF	Boot Block (000000-0007FFh) not protected from table reads executed in other blocks
ON	Boot Block (000000-0007FFh) protected from table reads executed in other blocks
*/

//18f2550/4550
#elif	defined(_18F2455) || defined(_18F2550) || defined(_18F4455) || defined(_18F4550) || \
		defined(_18F2458) || defined(_18F2553) || defined(_18F4458) || defined(_18F4553)

#pragma config CPUDIV = OSC1_PLL2
#pragma config PLLDIV = 5
#pragma config USBDIV = 2
#pragma config IESO = OFF
#pragma config FOSC = XT_XT
#pragma config FCMEN = OFF
/*
Register: CONFIG1L @ 0x300000

CPUDIV =	System Clock Postscaler Selection bits
OSC2_PLL3	[Primary Oscillator Src: /2][96 MHz PLL Src: /3]
OSC4_PLL6	[Primary Oscillator Src: /4][96 MHz PLL Src: /6]
OSC3_PLL4	[Primary Oscillator Src: /3][96 MHz PLL Src: /4]
OSC1_PLL2	[Primary Oscillator Src: /1][96 MHz PLL Src: /2]
PLLDIV =	PLL Prescaler Selection bits
1	No prescale (4 MHz oscillator input drives PLL directly)
5	Divide by 5 (20 MHz oscillator input)
12	Divide by 12 (48 MHz oscillator input)
2	Divide by 2 (8 MHz oscillator input)
6	Divide by 6 (24 MHz oscillator input)
3	Divide by 3 (12 MHz oscillator input)
10	Divide by 10 (40 MHz oscillator input)
4	Divide by 4 (16 MHz oscillator input)
USBDIV =	USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1)
1	USB clock source comes directly from the primary oscillator block with no postscale
2	USB clock source comes from the 96 MHz PLL divided by 2
Register: CONFIG1H @ 0x300001

IESO =	Internal/External Oscillator Switchover bit
OFF	Oscillator Switchover mode disabled
ON	Oscillator Switchover mode enabled
FOSC =	Oscillator Selection bits
INTOSC_EC	Internal oscillator, CLKO function on RA6, EC used by USB (INTCKO)
ECPLLIO_EC	EC oscillator, PLL enabled, port function on RA6 (ECPIO)
XT_XT	XT oscillator (XT)
INTOSC_HS	Internal oscillator, HS oscillator used by USB (INTHS)
ECPLL_EC	EC oscillator, PLL enabled, CLKO function on RA6 (ECPLL)
INTOSC_XT	Internal oscillator, XT used by USB (INTXT)
EC_EC	EC oscillator, CLKO function on RA6 (EC)
ECIO_EC	EC oscillator, port function on RA6 (ECIO)
XTPLL_XT	XT oscillator, PLL enabled (XTPLL)
HSPLL_HS	HS oscillator, PLL enabled (HSPLL)
HS	HS oscillator (HS)
INTOSCIO_EC	Internal oscillator, port function on RA6, EC used by USB (INTIO)
FCMEN =	Fail-Safe Clock Monitor Enable bit
OFF	Fail-Safe Clock Monitor disabled
ON	Fail-Safe Clock Monitor enabled
*/
#pragma config VREGEN = OFF
#pragma config BOR = OFF
#pragma config BORV = 3
#pragma config PWRT = ON
#pragma config WDTPS = 32768
#pragma config WDT = OFF
/*
Register: CONFIG2L @ 0x300002

VREGEN =	USB Voltage Regulator Enable bit
OFF	USB voltage regulator disabled
ON	USB voltage regulator enabled
BOR =	Brown-out Reset Enable bits
SOFT	Brown-out Reset enabled and controlled by software (SBOREN is enabled)
OFF	Brown-out Reset disabled in hardware and software
ON	Brown-out Reset enabled in hardware only (SBOREN is disabled)
ON_ACTIVE	Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
BORV =	Brown-out Reset Voltage bits
1	
2	
3	Minimum setting
0	Maximum setting
PWRT =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
Register: CONFIG2H @ 0x300003

WDTPS =	Watchdog Timer Postscale Select bits
8	1:8
1	1:1
32768	1:32768
1024	1:1024
2	1:2
32	1:32
16	1:16
16384	1:16384
128	1:128
4096	1:4096
64	1:64
8192	1:8192
2048	1:2048
512	1:512
256	1:256
4	1:4
WDT =	Watchdog Timer Enable bit
OFF	WDT disabled (control is placed on the SWDTEN bit)
ON	WDT enabled
*/
#pragma config CCP2MX = OFF
#pragma config PBADEN = OFF
#pragma config LPT1OSC = OFF
#pragma config MCLRE = OFF
/*
Register: CONFIG3H @ 0x300005

CCP2MX =	CCP2 MUX bit
OFF	CCP2 input/output is multiplexed with RB3
ON	CCP2 input/output is multiplexed with RC1
PBADEN =	PORTB A/D Enable bit
OFF	PORTB<4:0> pins are configured as digital I/O on Reset
ON	PORTB<4:0> pins are configured as analog input channels on Reset
LPT1OSC =	Low-Power Timer 1 Oscillator Enable bit
OFF	Timer1 configured for higher power operation
ON	Timer1 configured for low-power operation
MCLRE =	MCLR Pin Enable bit
OFF	RE3 input pin enabled; MCLR pin disabled
ON	MCLR pin enabled; RE3 input pin disabled
*/
#pragma config DEBUG = OFF
#pragma config STVREN = OFF
#if	defined(_18F4455) || defined(_18F4550) || defined(_18F4458) || defined(_18F4553)
#pragma config ICPRT = OFF			//only for 18F4xxx chips
#endif
#pragma config XINST = OFF
#pragma config LVP = OFF
/*
Register: CONFIG4L @ 0x300006

DEBUG =	Background Debugger Enable bit
OFF	Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins
ON	Background debugger enabled, RB6 and RB7 are dedicated to In-Circuit Debug
STVREN =	Stack Full/Underflow Reset Enable bit
OFF	Stack full/underflow will not cause Reset
ON	Stack full/underflow will cause Reset
ICPRT =	Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit
OFF	ICPORT disabled
ON	ICPORT enabled
XINST =	Extended Instruction Set Enable bit
OFF	Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
ON	Instruction set extension and Indexed Addressing mode enabled
LVP =	Single-Supply ICSP Enable bit
OFF	Single-Supply ICSP disabled
ON	Single-Supply ICSP enabled
*/
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPD = OFF
#pragma config CPB = OFF
/*
Register: CONFIG5L @ 0x300008

CP0 =	Code Protection bit
OFF	Block 0 (000800-001FFFh) is not code-protected
ON	Block 0 (000800-001FFFh) is code-protected
CP1 =	Code Protection bit
OFF	Block 1 (002000-003FFFh) is not code-protected
ON	Block 1 (002000-003FFFh) is code-protected
CP2 =	Code Protection bit
OFF	Block 2 (004000-005FFFh) is not code-protected
ON	Block 2 (004000-005FFFh) is code-protected
CP3 =	Code Protection bit
OFF	Block 3 (006000-007FFFh) is not code-protected
ON	Block 3 (006000-007FFFh) is code-protected
Register: CONFIG5H @ 0x300009

CPD =	Data EEPROM Code Protection bit
OFF	Data EEPROM is not code-protected
ON	Data EEPROM is code-protected
CPB =	Boot Block Code Protection bit
OFF	Boot block (000000-0007FFh) is not code-protected
ON	Boot block (000000-0007FFh) is code-protected
*/
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
/*
Register: CONFIG6L @ 0x30000A

WRT0 =	Write Protection bit
OFF	Block 0 (000800-001FFFh) is not write-protected
ON	Block 0 (000800-001FFFh) is write-protected
WRT1 =	Write Protection bit
OFF	Block 1 (002000-003FFFh) is not write-protected
ON	Block 1 (002000-003FFFh) is write-protected
WRT2 =	Write Protection bit
OFF	Block 2 (004000-005FFFh) is not write-protected
ON	Block 2 (004000-005FFFh) is write-protected
WRT3 =	Write Protection bit
OFF	Block 3 (006000-007FFFh) is not write-protected
ON	Block 3 (006000-007FFFh) is write-protected
Register: CONFIG6H @ 0x30000B

WRTB =	Boot Block Write Protection bit
OFF	Boot block (000000-0007FFh) is not write-protected
ON	Boot block (000000-0007FFh) is write-protected
WRTC =	Configuration Register Write Protection bit
OFF	Configuration registers (300000-3000FFh) are not write-protected
ON	Configuration registers (300000-3000FFh) are write-protected
WRTD =	Data EEPROM Write Protection bit
OFF	Data EEPROM is not write-protected
ON	Data EEPROM is write-protected
*/
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF
/*
Register: CONFIG7L @ 0x30000C

EBTR0 =	Table Read Protection bit
OFF	Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks
ON	Block 0 (000800-001FFFh) is protected from table reads executed in other blocks
EBTR1 =	Table Read Protection bit
OFF	Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks
ON	Block 1 (002000-003FFFh) is protected from table reads executed in other blocks
EBTR2 =	Table Read Protection bit
OFF	Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks
ON	Block 2 (004000-005FFFh) is protected from table reads executed in other blocks
EBTR3 =	Table Read Protection bit
OFF	Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks
ON	Block 3 (006000-007FFFh) is protected from table reads executed in other blocks
Register: CONFIG7H @ 0x30000D

EBTRB =	Boot Block Table Read Protection bit
OFF	Boot block (000000-0007FFh) is not protected from table reads executed in other blocks
ON	Boot block (000000-0007FFh) is protected from table reads executed in other blocks
*/

#elif	defined(_18F6627) || defined(_18F6722) || defined(_18F8627) || defined(_18F8722) || \
		defined(_18F6527) || defined(_18F6622) || defined(_18F8527) || defined(_18F8622) || \
		defined(_18F6628) || defined(_18F6723) || defined(_18F8628) || defined(_18F8723)

#pragma config IESO = OFF
#pragma config OSC = INTIO67
#pragma config FCMEN = OFF
/*
Register: CONFIG1H @ 0x300001

IESO =	Internal/External Oscillator Switchover bit
OFF	Two-Speed Start-up disabled
ON	Two-Speed Start-up enabled
OSC =	Oscillator Selection bits
RCIO6	External RC oscillator, port function on RA6
RC	External RC oscillator, CLKO function on RA6
INTIO7	Internal oscillator block, CLKO function on RA6, port function on RA7
XT	XT oscillator
LP	LP oscillator
HSPLL	HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1)
ECIO6	EC oscillator, port function on RA6
EC	EC oscillator, CLKO function on RA6
INTIO67	Internal oscillator block, port function on RA6 and RA7
HS	HS oscillator
FCMEN =	Fail-Safe Clock Monitor Enable bit
OFF	Fail-Safe Clock Monitor disabled
ON	Fail-Safe Clock Monitor enabled
*/
#pragma config BOREN = OFF
#pragma config BORV = 3
#pragma config PWRT = ON
#pragma config WDTPS = 32768
#pragma config WDT = OFF
/*
Register: CONFIG2L @ 0x300002

BOREN =	Brown-out Reset Enable bits
NOSLP	Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
OFF	Brown-out Reset disabled in hardware and software
ON	Brown-out Reset enabled and controlled by software (SBOREN is enabled)
SBORDIS	Brown-out Reset enabled in hardware only (SBOREN is disabled)
BORV =	Brown-out Voltage bits
1	
2	
3	Minimum setting
0	Maximum setting
PWRT =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
Register: CONFIG2H @ 0x300003

WDTPS =	Watchdog Timer Postscale Select bits
8	1:8
1	1:1
32768	1:32768
1024	1:1024
2	1:2
32	1:32
16	1:16
16384	1:16384
128	1:128
4096	1:4096
64	1:64
8192	1:8192
2048	1:2048
512	1:512
256	1:256
4	1:4
WDT =	Watchdog Timer
OFF	WDT disabled (control is placed on the SWDTEN bit)
ON	WDT enabled
*/
#if defined(_18F8627) || defined(_18F8722) || \
	defined(_18F8527) || defined(_18F8622) || \
	defined(_18F8628) || defined(_18F8723)

#pragma config MODE = MC
#pragma config WAIT = OFF
#pragma config DATABW = DATA8BIT
#pragma config ADDRBW = ADDR8BIT
#pragma config ECCPMX = PORTH
#endif
/*
Register: CONFIG3L @ 0x300004

MODE =	Processor Data Memory Mode Select bits
MC	Microcontroller mode
EM	Extended Microcontroller mode
MPB	Microprocessor with Boot Block mode
MP	Microprocessor mode
WAIT =	External Bus Data Wait Enable bit
OFF	Wait selections are unavailable for table reads and table writes
ON	Wait selections for table reads and table writes are determined by the WAIT1:WAIT0 bits
DATABW =	Data Bus Width Select bit
DATA16BIT	16-bit External Bus mode
DATA8BIT	8-bit External Bus mode
ADDRBW =	Address Bus Width Select bits
ADDR8BIT	8-bit Address Bus
ADDR20BIT	20-bit Address Bus
ADDR12BIT	12-bit Address Bus
ADDR16BIT	16-bit Address Bus
Register: CONFIG3H @ 0x300005
*/

#pragma config CCP2MX = PORTC
#pragma config LPT1OSC = OFF
#pragma config MCLRE = OFF

/*CCP2MX =	CCP2 MUX bit
PORTC	ECCP2 input/output is multiplexed with RC1
PORTBE	ECCP2 is multiplexed with RB3 in Extended Microcontroller, Microprocessor or Microprocessor with Boot Block mode. Or with RE7 in Microcontroller mode.
LPT1OSC =	Low-Power Timer1 Oscillator Enable bit
OFF	Timer1 configured for higher power operation
ON	Timer1 configured for low-power operation
ECCPMX =	ECCP MUX bit
PORTH	ECCP1/3 (P1B/P1C/P3B/P3C) are multiplexed onto RH7, RH6, RH5 and RH4 respectively
PORTE	ECCP1/3 (P1B/P1C/P3B/P3C) are multiplexed onto RE6, RE5, RE4 and RE3 respectively
MCLRE =	MCLR Pin Enable bit
OFF	RG5 input pin enabled; MCLR disabled
ON	MCLR pin enabled; RG5 input pin disabled
*/
#pragma config DEBUG = OFF
#pragma config STVREN = OFF
#pragma config XINST = OFF
#pragma config BBSIZ = BB2K
#pragma config LVP = OFF
/*
Register: CONFIG4L @ 0x300006

DEBUG =	Background Debugger Enable bit
OFF	Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins
ON	Background debugger enabled, RB6 and RB7 are dedicated to In-Circuit Debug
STVREN =	Stack Full/Underflow Reset Enable bit
OFF	Stack full/underflow will not cause Reset
ON	Stack full/underflow will cause Reset
XINST =	Extended Instruction Set Enable bit
OFF	Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
ON	Instruction set extension and Indexed Addressing mode enabled
BBSIZ =	Boot Block Size Select bits
BB2K	1K word (2 Kbytes) Boot Block size
BB4K	2K words (4 Kbytes) Boot Block size
BB8K	4K words (8 Kbytes) Boot Block size
LVP =	Single-Supply ICSP Enable bit
OFF	Single-Supply ICSP disabled
ON	Single-Supply ICSP enabled
*/
#if defined(_18F8627) || defined(_18F8722) || \
	defined(_18F8527) || defined(_18F8622) || \
	defined(_18F8628) || defined(_18F8723)

#pragma config CP4 = OFF
#pragma config CP5 = OFF
#pragma config CP6 = OFF
#pragma config CP7 = OFF
#endif

#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPD = OFF
#pragma config CPB = OFF

/*
Register: CONFIG5L @ 0x300008

CP5 =	Code Protection bit Block 5
OFF	Block 5 (014000-017FFFh) not code-protected
ON	Block 5 (014000-017FFFh) code-protected
CP6 =	Code Protection bit Block 6
OFF	Block 6 (01BFFF-018000h) not code-protected
ON	Block 6 (01BFFF-018000h) code-protected
CP7 =	Code Protection bit Block 7
OFF	Block 7 (01C000-01FFFFh) not code-protected
ON	Block 7 (01C000-01FFFFh) code-protected
CP0 =	Code Protection bit Block 0
OFF	Block 0 (000800, 001000 or 002000-003FFFh) not code-protected
ON	Block 0 (000800, 001000 or 002000-003FFFh) code-protected
CP1 =	Code Protection bit Block 1
OFF	Block 1 (004000-007FFFh) not code-protected
ON	Block 1 (004000-007FFFh) code-protected
CP2 =	Code Protection bit Block 2
OFF	Block 2 (008000-00BFFFh) not code-protected
ON	Block 2 (008000-00BFFFh) code-protected
CP3 =	Code Protection bit Block 3
OFF	Block 3 (00C000-00FFFFh) not code-protected
ON	Block 3 (00C000-00FFFFh) code-protected
CP4 =	Code Protection bit Block 4
OFF	Block 4 (010000-013FFFh) not code-protected
ON	Block 4 (010000-013FFFh) code-protected
Register: CONFIG5H @ 0x300009

CPD =	Data EEPROM Code Protection bit
OFF	Data EEPROM not code-protected
ON	Data EEPROM code-protected
CPB =	Boot Block Code Protection bit
OFF	Boot Block (000000-0007FFh) not code-protected
ON	Boot Block (000000-0007FFh) code-protected
*/
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF

#if defined(_18F8627) || defined(_18F8722) || \
	defined(_18F8527) || defined(_18F8622) || \
	defined(_18F8628) || defined(_18F8723)
#pragma config WRT4 = OFF
#pragma config WRT5 = OFF
#pragma config WRT7 = OFF
#endif

#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
/*
Register: CONFIG6L @ 0x30000A

WRT0 =	Write Protection bit Block 0
OFF	Block 0 (000800, 001000 or 002000-003FFFh) not write-protected
ON	Block 0 (000800, 001000 or 002000-003FFFh) write-protected
WRT1 =	Write Protection bit Block 1
OFF	Block 1 (004000-007FFFh) not write-protected
ON	Block 1 (004000-007FFFh) write-protected
WRT2 =	Write Protection bit Block 2
OFF	Block 2 (008000-00BFFFh) not write-protected
ON	Block 2 (008000-00BFFFh) write-protected
WRT3 =	Write Protection bit Block 3
OFF	Block 3 (00C000-00FFFFh) not write-protected
ON	Block 3 (00C000-00FFFFh) write-protected
WRT4 =	Write Protection bit Block 4
OFF	Block 4 (010000-013FFFh) not write-protected
ON	Block 4 (010000-013FFFh) write-protected
WRT5 =	Write Protection bit Block 5
OFF	Block 5 (014000-017FFFh) not write-protected
ON	Block 5 (014000-017FFFh) write-protected
WRT6 =	Write Protection bit Block 6
OFF	Block 6 (01BFFF-018000h) not write-protected
ON	Block 6 (01BFFF-018000h) write-protected
WRT7 =	Write Protection bit Block 7
OFF	Block 7 (01C000-01FFFFh) not write-protected
ON	Block 7 (01C000-01FFFFh) write-protected
Register: CONFIG6H @ 0x30000B

WRTB =	Boot Block Write Protection bit
OFF	Boot Block (000000-007FFF, 000FFF or 001FFFh) not write-protected
ON	Boot Block (000000-007FFF, 000FFF or 001FFFh) write-protected
WRTC =	Configuration Register Write Protection bit
OFF	Configuration registers (300000-3000FFh) not write-protected
ON	Configuration registers (300000-3000FFh) write-protected
WRTD =	Data EEPROM Write Protection bit
OFF	Data EEPROM not write-protected
ON	Data EEPROM write-protected
*/
#if defined(_18F8627) || defined(_18F8722) || \
	defined(_18F8527) || defined(_18F8622) || \
	defined(_18F8628) || defined(_18F8723)

#pragma config EBTR4 = OFF
#pragma config EBTR5 = OFF
#pragma config EBTR6 = OFF
#pragma config EBTR7 = OFF
#endif

#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF

/*
Register: CONFIG7L @ 0x30000C

EBTR6 =	Table Read Protection bit Block 6
OFF	Block 6 (018000-01BFFFh) not protected from table reads executed in other blocks
ON	Block 6 (018000-01BFFFh) protected from table reads executed in other blocks
EBTR7 =	Table Read Protection bit Block 7
OFF	Block 7 (01C000-01FFFFh) not protected from table reads executed in other blocks
ON	Block 7 (01C000-01FFFFh) protected from table reads executed in other blocks
EBTR0 =	Table Read Protection bit Block 0
OFF	Block 0 (000800, 001000 or 002000-003FFFh) not protected from table reads executed in other blocks
ON	Block 0 (000800, 001000 or 002000-003FFFh) protected from table reads executed in other blocks
EBTR1 =	Table Read Protection bit Block 1
OFF	Block 1 (004000-007FFFh) not protected from table reads executed in other blocks
ON	Block 1 (004000-007FFFh) protected from table reads executed in other blocks
EBTR2 =	Table Read Protection bit Block 2
OFF	Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks
ON	Block 2 (008000-00BFFFh) protected from table reads executed in other blocks
EBTR3 =	Table Read Protection bit Block 3
OFF	Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks
ON	Block 3 (00C000-00FFFFh) protected from table reads executed in other blocks
EBTR4 =	Table Read Protection bit Block 4
OFF	Block 4 (010000-013FFFh) not protected from table reads executed in other blocks
ON	Block 4 (010000-013FFFh) protected from table reads executed in other blocks
EBTR5 =	Table Read Protection bit Block 5
OFF	Block 5 (014000-017FFFh) not protected from table reads executed in other blocks
ON	Block 5 (014000-017FFFh) protected from table reads executed in other blocks
Register: CONFIG7H @ 0x30000D

EBTRB =	Boot Block Table Read Protection bit
OFF	Boot Block (000000-007FFF, 000FFF or 001FFFh) not protected from table reads executed in other blocks
ON	Boot Block (000000-007FFF, 000FFF or 001FFFh) protected from table reads executed in other blocks
*/
#elif	defined(_18F2585) || defined(_18F2680) || defined(_18F4585) || defined(_18F4680)

#pragma config IESO = OFF, OSC = IRCIO67, FCMEN = OFF
/*
Register: CONFIG1H @ 0x300001

IESO =	Internal/External Oscillator Switchover bit
OFF	Oscillator Switchover mode disabled
ON	Oscillator Switchover mode enabled
OSC =	Oscillator Selection bits
RC	External RC oscillator, CLKO function on RA6
RCIO	External RC oscillator, port function on RA6
XT	XT oscillator
LP	LP oscillator
HSPLL	HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1)
IRCIO67	Internal oscillator block, port function on RA6 and RA7
ECIO	EC oscillator, port function on RA6
EC	EC oscillator, CLKO function on RA6
IRCIO7	Internal oscillator block, CLKO function on RA6, port function on RA7
HS	HS oscillator
FCMEN =	Fail-Safe Clock Monitor Enable bit
OFF	Fail-Safe Clock Monitor disabled
ON	Fail-Safe Clock Monitor enabled
*/
#pragma config BOREN = OFF
#pragma config BORV = 3
#pragma config PWRT = ON
#pragma config WDTPS = 32768
#pragma config WDT = OFF
/*
Register: CONFIG2L @ 0x300002

BOREN =	Brown-out Reset Enable bits
BOHW	Brown-out Reset enabled in hardware only (SBOREN is disabled)
BOACTIVE	Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
OFF	Brown-out Reset disabled in hardware and software
SBORENCTRL	Brown-out Reset enabled and controlled by software (SBOREN is enabled)
BORV =	Brown-out Reset Voltage bits
1	VBOR set to 4.3V
2	VBOR set to 2.8V
3	VBOR set to 2.1V
0	VBOR set to 4.6V
PWRT =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
Register: CONFIG2H @ 0x300003

WDTPS =	Watchdog Timer Postscale Select bits
8	1:8
1	1:1
32768	1:32768
1024	1:1024
2	1:2
32	1:32
16	1:16
16384	1:16384
128	1:128
4096	1:4096
64	1:64
8192	1:8192
2048	1:2048
512	1:512
256	1:256
4	1:4
WDT =	Watchdog Timer Enable bit
OFF	WDT disabled (control is placed on the SWDTEN bit)
ON	WDT enabled
*/
#pragma config PBADEN = OFF
#pragma config LPT1OSC = OFF
#pragma config MCLRE = OFF
/*
Register: CONFIG3H @ 0x300005

PBADEN =	PORTB A/D Enable bit
OFF	PORTB<4:0> pins are configured as digital I/O on Reset
ON	PORTB<4:0> pins are configured as analog input channels on Reset
LPT1OSC =	Low-Power Timer 1 Oscillator Enable bit
OFF	Timer1 configured for higher power operation
ON	Timer1 configured for low-power operation
MCLRE =	MCLR Pin Enable bit
OFF	RE3 input pin enabled; MCLR disabled
ON	MCLR pin enabled; RE3 input pin disabled
*/
#pragma config DEBUG = OFF
#pragma config STVREN = OFF
#pragma config XINST = OFF
#pragma config BBSIZ = 1024
#pragma config LVP = OFF
/*
Register: CONFIG4L @ 0x300006

DEBUG =	Background Debugger Enable bit
OFF	Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins
ON	Background debugger enabled, RB6 and RB7 are dedicated to In-Circuit Debug
STVREN =	Stack Full/Underflow Reset Enable bit
OFF	Stack full/underflow will not cause Reset
ON	Stack full/underflow will cause Reset
XINST =	Extended Instruction Set Enable bit
OFF	Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
ON	Instruction set extension and Indexed Addressing mode enabled
BBSIZ =	Boot Block Size Select bits
1024	1K words (2K bytes) Boot Block
4096	4K words (8K bytes) Boot Block
2048	2K words (4K bytes) Boot Block
LVP =	Single-Supply ICSP Enable bit
OFF	Single-Supply ICSP disabled
ON	Single-Supply ICSP enabled
*/
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPD = OFF
#pragma config CPB = OFF
/*
Register: CONFIG5L @ 0x300008

CP0 =	Code Protection bit
OFF	Block 0 (000800-003FFFh) not code-protected
ON	Block 0 (000800-003FFFh) code-protected
CP1 =	Code Protection bit
OFF	Block 1 (004000-007FFFh) not code-protected
ON	Block 1 (004000-007FFFh) code-protected
CP2 =	Code Protection bit
OFF	Block 2 (008000-00BFFFh) not code-protected
ON	Block 2 (008000-00BFFFh) code-protected
CP3 =	Code Protection bit
OFF	Block 3 (00C000-00FFFFh) not code-protected
ON	Block 3 (00C000-00FFFFh) code-protected
Register: CONFIG5H @ 0x300009

CPD =	Data EEPROM Code Protection bit
OFF	Data EEPROM not code-protected
ON	Data EEPROM code-protected
CPB =	Boot Block Code Protection bit
OFF	Boot block (000000-0007FFh) not code-protected
ON	Boot block (000000-0007FFh) code-protected
*/
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
/*
Register: CONFIG6L @ 0x30000A

WRT0 =	Write Protection bit
OFF	Block 0 (000800-003FFFh) not write-protected
ON	Block 0 (000800-003FFFh) write-protected
WRT1 =	Write Protection bit
OFF	Block 1 (004000-007FFFh) not write-protected
ON	Block 1 (004000-007FFFh) write-protected
WRT2 =	Write Protection bit
OFF	Block 2 (008000-00BFFFh) not write-protected
ON	Block 2 (008000-00BFFFh) write-protected
WRT3 =	Write Protection bit
OFF	Block 3 (00C000-00FFFFh) not write-protected
ON	Block 3 (00C000-00FFFFh) write-protected
Register: CONFIG6H @ 0x30000B

WRTB =	Boot Block Write Protection bit
OFF	Boot block (000000-0007FFh) not write-protected
ON	Boot block (000000-0007FFh) write-protected
WRTC =	Configuration Register Write Protection bit
OFF	Configuration registers (300000-3000FFh) not write-protected
ON	Configuration registers (300000-3000FFh) write-protected
WRTD =	Data EEPROM Write Protection bit
OFF	Data EEPROM not write-protected
ON	Data EEPROM write-protected
*/
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF
/*
Register: CONFIG7L @ 0x30000C

EBTR0 =	Table Read Protection bit
OFF	Block 0 (000800-003FFFh) not protected from table reads executed in other blocks
ON	Block 0 (000800-003FFFh) protected from table reads executed in other blocks
EBTR1 =	Table Read Protection bit
OFF	Block 1 (004000-007FFFh) not protected from table reads executed in other blocks
ON	Block 1 (004000-007FFFh) protected from table reads executed in other blocks
EBTR2 =	Table Read Protection bit
OFF	Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks
ON	Block 2 (008000-00BFFFh) protected from table reads executed in other blocks
EBTR3 =	Table Read Protection bit
OFF	Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks
ON	Block 3 (00C000-00FFFFh) protected from table reads executed in other blocks
Register: CONFIG7H @ 0x30000D

EBTRB =	Boot Block Table Read Protection bit
OFF	Boot block (000000-0007FFh) not protected from table reads executed in other blocks
ON	Boot block (000000-0007FFh) protected from table reads executed in other blocks
*/
#elif	defined(_18F6520) || defined(_18F6620) || defined(_18F6720) || \
	defined(_18F8520) || defined(_18F8620) || defined(_18F8720)

#pragma config OSCS = OFF
#pragma config OSC = RCIO

/*Register: CONFIG1H @ 0x300001

OSCS =	Oscillator System Clock Switch Enable bit
OFF	Oscillator system clock switch option is disabled (main oscillator is source)
ON	Timer1 Oscillator system clock switch option is enabled (oscillator switching is enabled)
OSC =	Oscillator Selection bits
RC	RC oscillator w/ OSC2 configured as divide-by-4 clock output
RCIO	RC oscillator w/ OSC2 configured as RA6
XT	XT oscillator
LP	LP oscillator
HSPLL	HS oscillator with PLL enabled; clock frequency = (4 x FOSC)
ECIO	EC oscillator w/ OSC2 configured as RA6
EC	EC oscillator w/ OSC2 configured as divide-by-4 clock output
HS	HS oscillator
*/
#pragma config BOR = OFF
#pragma config BORV = 25
#pragma config PWRT = ON
#pragma config WDTPS = 128
#pragma config WDT = OFF
/*
Register: CONFIG2L @ 0x300002

BOR =	Brown-out Reset Enable bit
OFF	Brown-out Reset disabled
ON	Brown-out Reset enabled
BORV =	Brown-out Reset Voltage bits
42	VBOR set to 4.2V
27	VBOR set to 2.7V
25	VBOR set to 2.5V
45	VBOR set to 4.5V
PWRT =	Power-up Timer Enable bit
OFF	PWRT disabled
ON	PWRT enabled
Register: CONFIG2H @ 0x300003

WDTPS =	Watchdog Timer Postscale Select bits
8	1:8
1	1:1
2	1:2
32	1:32
16	1:16
128	1:128
64	1:64
4	1:4
WDT =	Watchdog Timer Enable bit
OFF	WDT disabled (control is placed on the SWDTEN bit)
ON	WDT enabled
*/
#pragma config MODE = MC
#pragma config WAIT = OFF
#pragma config CCP2MUX = OFF
/*
Register: CONFIG3L @ 0x300004

MODE =	Processor Mode Select bits
MC	Microcontroller mode
EM	Extended Microcontroller mode
MPB	Microprocessor with Boot Block mode
MP	Microprocessor mode
WAIT =	External Bus Data Wait Enable bit
OFF	Wait selections unavailable for table reads and table writes
ON	Wait selections for table reads and table writes are determined by the WAIT1:WAIT0 bits (MEMCOM<5:4>)
Register: CONFIG3H @ 0x300005

CCP2MUX =	CCP2 Mux bit
OFF	CCP2 is multiplexed with RB3 in Extended Microcontroller, Microprocessor or Microprocessor with Boot Block mode. Or with RE7 in Microcontroller mode.
ON	CCP2 input/output is multiplexed with RC1
*/
#pragma config DEBUG = OFF
#pragma config LVP = OFF
#pragma config STVR = OFF
/*
Register: CONFIG4L @ 0x300006

DEBUG =	Background Debugger Enable bit
OFF	Background debugger disabled. RB6 and RB7 configured as general purpose I/O pins.
ON	Background debugger enabled. RB6 and RB7 are dedicated to In-Circuit Debug.
LVP =	Low-Voltage ICSP Enable bit
OFF	Low-voltage ICSP disabled
ON	Low-voltage ICSP enabled
STVR =	Stack Full/Underflow Reset Enable bit
OFF	Stack full/underflow will not cause Reset
ON	Stack full/underflow will cause Reset
*/
#pragma config CP5 = OFF
#pragma config CP6 = OFF
#pragma config CP7 = OFF
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CP4 = OFF
#pragma config CPD = OFF
#pragma config CPB = OFF
/*
Register: CONFIG5L @ 0x300008

CP5 =	Code Protection bit
OFF	Block 5 (014000-017FFFh) not code-protected
ON	Block 5 (014000-017FFFh) code-protected
CP6 =	Code Protection bit
OFF	Block 6 (018000-01BFFFh) not code-protected
ON	Block 6 (018000-01BFFFh) code-protected
CP7 =	Code Protection bit
OFF	Block 7 (01C000-01FFFFh) not code-protected
ON	Block 7 (01C000-01FFFFh) code-protected
CP0 =	Code Protection bit
OFF	Block 0 (000200-003FFFh) not code-protected
ON	Block 0 (000200-003FFFh) code-protected
CP1 =	Code Protection bit
OFF	Block 1 (004000-007FFFh) not code-protected
ON	Block 1 (004000-007FFFh) code-protected
CP2 =	Code Protection bit
OFF	Block 2 (008000-00BFFFh) not code-protected
ON	Block 2 (008000-00BFFFh) code-protected
CP3 =	Code Protection bit
OFF	Block 3 (00C000-00FFFFh) not code-protected
ON	Block 3 (00C000-00FFFFh) code-protected
CP4 =	Code Protection bit
OFF	Block 4 (010000-013FFFh) not code-protected
ON	Block 4 (010000-013FFFh) code-protected
Register: CONFIG5H @ 0x300009

CPD =	Data EEPROM Code Protection bit
OFF	Data EEPROM not code-protected
ON	Data EEPROM code-protected
CPB =	Boot Block Code Protection bit
OFF	Boot Block (000000-0001FFh) not code-protected
ON	Boot Block (000000-0001FFh) code-protected
*/
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRT4 = OFF
#pragma config WRT5 = OFF
#pragma config WRT6 = OFF
#pragma config WRT7 = OFF
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
/*
Register: CONFIG6L @ 0x30000A

WRT0 =	Write Protection bit
OFF	Block 0 (000200-003FFFh) not write-protected
ON	Block 0 (000200-003FFFh) write-protected
WRT1 =	Write Protection bit
OFF	Block 1 (004000-007FFFh) not write-protected
ON	Block 1 (004000-007FFFh) write-protected
WRT2 =	Write Protection bit
OFF	Block 2 (008000-00BFFFh) not write-protected
ON	Block 2 (008000-00BFFFh) write-protected
WRT3 =	Write Protection bit
OFF	Block 3 (00C000-00FFFFh) not write-protected
ON	Block 3 (00C000-00FFFFh) write-protected
WRT4 =	Write Protection bit
OFF	Block 4 (010000-013FFFh) not write-protected
ON	Block 4 (010000-013FFFh) write-protected
WRT5 =	Write Protection bit
OFF	Block 5 (014000-017FFFh) not write-protected
ON	Block 5 (014000-017FFFh) write-protected
WRT6 =	Write Protection bit
OFF	Block 6 (018000-01BFFFh) not write-protected
ON	Block 6 (018000-01BFFFh) write-protected
WRT7 =	Write Protection bit
OFF	Block 7 (01C000-01FFFFh) not write-protected
ON	Block 7 (01C000-01FFFFh) write-protected
Register: CONFIG6H @ 0x30000B

WRTB =	Boot Block Write Protection bit
OFF	Boot Block (000000-0001FFh) not write-protected
ON	Boot Block (000000-0001FFh) write-protected
WRTC =	Configuration Register Write Protection bit
OFF	Configuration registers (300000-3000FFh) not write-protected
ON	Configuration registers (300000-3000FFh) write-protected
WRTD =	Data EEPROM Write Protection bit
OFF	Data EEPROM not write-protected
ON	Data EEPROM write-protected
*/
#pragma config EBTR6 = OFF
#pragma config EBTR7 = OFF
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTR4 = OFF
#pragma config EBTR5 = OFF
#pragma config EBTRB = OFF
/*
Register: CONFIG7L @ 0x30000C

EBTR6 =	Table Read Protection bit
OFF	Block 6 (018000-01BFFFh) not protected from table reads executed in other blocks
ON	Block 6 (018000-01BFFFh) protected from table reads executed in other blocks
EBTR7 =	Table Read Protection bit
OFF	Block 7 (01C000-01FFFFh) not protected from table reads executed in other blocks
ON	Block 7 (01C000-01FFFFh) protected from table reads executed in other blocks
EBTR0 =	Table Read Protection bit
OFF	Block 0 (000200-003FFFh) not protected from table reads executed in other blocks
ON	Block 0 (000200-003FFFh) protected from table reads executed in other blocks
EBTR1 =	Table Read Protection bit
OFF	Block 1 (004000-007FFFh) not protected from table reads executed in other blocks
ON	Block 1 (004000-007FFFh) protected from table reads executed in other blocks
EBTR2 =	Table Read Protection bit
OFF	Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks
ON	Block 2 (008000-00BFFFh) protected from table reads executed in other blocks
EBTR3 =	Table Read Protection bit
OFF	Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks
ON	Block 3 (00C000-00FFFFh) protected from table reads executed in other blocks
EBTR4 =	Table Read Protection bit
OFF	Block 4 (010000-013FFFh) not protected from table reads executed in other blocks
ON	Block 4 (010000-013FFFh) protected from table reads executed in other blocks
EBTR5 =	Table Read Protection bit
OFF	Block 5 (014000-017FFFh) not protected from table reads executed in other blocks
ON	Block 5 (014000-017FFFh) protected from table reads executed in other blocks
Register: CONFIG7H @ 0x30000D

EBTRB =	Boot Block Table Read Protection bit
OFF	Boot Block (000000-0001FFh) not protected from table reads executed in other blocks
ON	Boot Block (000000-0001FFh) protected from table reads executed in other blocks
*/

#elif   defined (_18F23K22) || defined (_18F24K22) || defined (_18F25K22) || defined (_18F26K22) || \
        defined (_18F43K22) || defined (_18F44K22) || defined (_18F45K22) || defined (_18F46K22) || \
        defined (_18LF23K22) || defined (_18LF24K22) || defined (_18LF25K22) || defined (_18LF26K22) || \
        defined (_18LF43K22) || defined (_18LF44K22) || defined (_18LF45K22) || defined (_18LF46K22)

#pragma config FOSC = INTIO67
#pragma config PLLCFG = OFF
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRTEN = ON
#pragma config BOREN = OFF
#pragma config BORV = 190
#pragma config WDTEN = OFF
#pragma config WDTPS = 32768
#pragma config MCLRE = INTMCLR //RE3 input pin enabled; MCLR disabled
#pragma config STVREN = OFF //Stack full/underflow will not cause Reset
#pragma config LVP = OFF //Single-Supply ICSP disabled
#pragma config XINST = OFF //Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
#pragma config DEBUG = OFF //Disabled
#pragma config CP0 = OFF, CP1 = OFF, /*CP2 = OFF, CP3 = OFF*/
#pragma config CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, /*WRT2 = OFF, WRT3 = OFF*/
#pragma config WRTC = OFF, WRTB = OFF, WRTD = OFF
#pragma config EBTR0 = OFF, EBTR1 = OFF, /*EBTR2 = OFF, EBTR3 = OFF, */EBTRB = OFF


/*
Oscillator Selection bits:
FOSC = LP	//LP oscillator
FOSC = XT XT oscillator
FOSC = HSHP HS oscillator (high power > 16 MHz)
FOSC = HSMP HS oscillator (medium power 4-16 MHz)
FOSC = ECHP EC oscillator, CLKOUT function on OSC2 (high power, >16 MHz)
FOSC = ECHPIO6 EC oscillator (high power, >16 MHz)
FOSC = RC External RC oscillator, CLKOUT function on OSC2
FOSC = RCIO6 External RC oscillator
FOSC = INTIO67 Internal oscillator block
FOSC = INTIO7 Internal oscillator block, CLKOUT function on OSC2
FOSC = ECMP EC oscillator, CLKOUT function on OSC2 (medium power, 500 kHz-16 MHz)
FOSC = ECMPIO6 EC oscillator (medium power, 500 kHz-16 MHz)
FOSC = ECLP EC oscillator, CLKOUT function on OSC2 (low power, <500 kHz)
FOSC = ECLPIO6 EC oscillator (low power, <500 kHz)

4X PLL Enable:
PLLCFG = OFF Oscillator used directly
PLLCFG = ON Oscillator multiplied by 4

Primary clock enable bit:
PRICLKEN = OFF Primary clock can be disabled by software
PRICLKEN = ON Primary clock is always enabled

Fail-Safe Clock Monitor Enable bit:
 FCMEN = OFF Fail-Safe Clock Monitor disabled
FCMEN = ON Fail-Safe Clock Monitor enabled

Internal/External Oscillator Switchover bit:
 IESO = OFF Oscillator Switchover mode disabled
IESO = ON Oscillator Switchover mode enabled

Power-up Timer Enable bit:
 PWRTEN = ON Power up timer enabled
PWRTEN = OFF Power up timer disabled

Brown-out Reset Enable bits:
 BOREN = OFF Brown-out Reset disabled in hardware and software
BOREN = ON Brown-out Reset enabled and controlled by software (SBOREN is enabled)
BOREN = NOSLP Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
BOREN = SBORDIS Brown-out Reset enabled in hardware only (SBOREN is disabled)

Brown Out Reset Voltage bits:
 BORV = 285 VBOR set to 2.85 V nominal
BORV = 250 VBOR set to 2.50 V nominal
BORV = 220 VBOR set to 2.20 V nominal
BORV = 190 VBOR set to 1.90 V nominal

Watchdog Timer Enable bits:
 WDTEN = OFF Watch dog timer is always disabled. SWDTEN has no effect.
WDTEN = NOSLP WDT is disabled in sleep, otherwise enabled. SWDTEN bit has no effect
WDTEN = SWON WDT is controlled by SWDTEN bit of the WDTCON register
WDTEN = ON WDT is always enabled. SWDTEN bit has no effect

Watchdog Timer Postscale Select bits:
 WDTPS = 1 1:1
WDTPS = 2 1:2
WDTPS = 4 1:4
WDTPS = 8 1:8
WDTPS = 16 1:16
WDTPS = 32 1:32
WDTPS = 64 1:64
WDTPS = 128 1:128
WDTPS = 256 1:256
WDTPS = 512 1:512
WDTPS = 1024 1:1024
WDTPS = 2048 1:2048
WDTPS = 4096 1:4096
WDTPS = 8192 1:8192
WDTPS = 16384 1:16384
WDTPS = 32768 1:32768

CCP2 MUX bit:
 CCP2MX = PORTB3 CCP2 input/output is multiplexed with RB3
CCP2MX = PORTC1 CCP2 input/output is multiplexed with RC1

PORTB A/D Enable bit:
 PBADEN = OFF PORTB<5:0> pins are configured as digital I/O on Reset
PBADEN = ON PORTB<5:0> pins are configured as analog input channels on Reset

P3A/CCP3 Mux bit:
 CCP3MX = PORTE0 P3A/CCP3 input/output is mulitplexed with RE0
CCP3MX = PORTB5 P3A/CCP3 input/output is multiplexed with RB5

HFINTOSC Fast Start-up:
 HFOFST = OFF HFINTOSC output and ready status are delayed by the oscillator stable status
HFOFST = ON HFINTOSC output and ready status are not delayed by the oscillator stable status

Timer3 Clock input mux bit:
 T3CMX = PORTB5 T3CKI is on RB5
T3CMX = PORTC0 T3CKI is on RC0

ECCP2 B output mux bit:
 P2BMX = PORTC0 P2B is on RC0
P2BMX = PORTD2 P2B is on RD2

MCLR Pin Enable bit:
 MCLRE = INTMCLR RE3 input pin enabled; MCLR disabled
MCLRE = EXTMCLR MCLR pin enabled, RE3 input pin disabled

Stack Full/Underflow Reset Enable bit:
 STVREN = OFF Stack full/underflow will not cause Reset
STVREN = ON Stack full/underflow will cause Reset

Single-Supply ICSP Enable bit:
 LVP = OFF Single-Supply ICSP disabled
LVP = ON Single-Supply ICSP enabled if MCLRE is also 1

Extended Instruction Set Enable bit:
 XINST = OFF Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
XINST = ON Instruction set extension and Indexed Addressing mode enabled

Background Debug:
 DEBUG = ON Enabled
DEBUG = OFF Disabled

Code Protection Block 0:
 CP0 = ON Block 0 (000800-003FFFh) code-protected
CP0 = OFF Block 0 (000800-003FFFh) not code-protected

Code Protection Block 1:
 CP1 = ON Block 1 (004000-007FFFh) code-protected
CP1 = OFF Block 1 (004000-007FFFh) not code-protected

Code Protection Block 2:
 CP2 = ON Block 2 (008000-00BFFFh) code-protected
CP2 = OFF Block 2 (008000-00BFFFh) not code-protected

Code Protection Block 3:
 CP3 = ON Block 3 (00C000-00FFFFh) code-protected
CP3 = OFF Block 3 (00C000-00FFFFh) not code-protected

Boot Block Code Protection bit:
 CPB = ON Boot block (000000-0007FFh) code-protected
CPB = OFF Boot block (000000-0007FFh) not code-protected

Data EEPROM Code Protection bit:
 CPD = ON Data EEPROM code-protected
CPD = OFF Data EEPROM not code-protected

Write Protection Block 0:
 WRT0 = ON Block 0 (000800-003FFFh) write-protected
WRT0 = OFF Block 0 (000800-003FFFh) not write-protected

Write Protection Block 1:
 WRT1 = ON Block 1 (004000-007FFFh) write-protected
WRT1 = OFF Block 1 (004000-007FFFh) not write-protected

Write Protection Block 2:
 WRT2 = ON Block 2 (008000-00BFFFh) write-protected
WRT2 = OFF Block 2 (008000-00BFFFh) not write-protected

Write Protection Block 3:
 WRT3 = ON Block 3 (00C000-00FFFFh) write-protected
WRT3 = OFF Block 3 (00C000-00FFFFh) not write-protected

Configuration Register Write Protection bit:
 WRTC = ON Configuration registers (300000-3000FFh) write-protected
WRTC = OFF Configuration registers (300000-3000FFh) not write-protected

Boot Block Write Protection bit:
 WRTB = ON Boot Block (000000-0007FFh) write-protected
WRTB = OFF Boot Block (000000-0007FFh) not write-protected

Data EEPROM Write Protection bit:
 WRTD = ON Data EEPROM write-protected
WRTD = OFF Data EEPROM not write-protected

Table Read Protection Block 0:
 EBTR0 = ON Block 0 (000800-003FFFh) protected from table reads executed in other blocks
EBTR0 = OFF Block 0 (000800-003FFFh) not protected from table reads executed in other blocks

Table Read Protection Block 1:
 EBTR1 = ON Block 1 (004000-007FFFh) protected from table reads executed in other blocks
EBTR1 = OFF Block 1 (004000-007FFFh) not protected from table reads executed in other blocks

Table Read Protection Block 2:
 EBTR2 = ON Block 2 (008000-00BFFFh) protected from table reads executed in other blocks
EBTR2 = OFF Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks

Table Read Protection Block 3:
 EBTR3 = ON Block 3 (00C000-00FFFFh) protected from table reads executed in other blocks
EBTR3 = OFF Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks

Boot Block Table Read Protection bit:
 EBTRB = ON Boot Block (000000-0007FFh) protected from table reads executed in other blocks
EBTRB = OFF Boot Block (000000-0007FFh) not protected from table reads executed in other blocks
*/

#elif   defined (_18F65K90) || defined (_18F66K90) || defined (_18F67K90) || \
        defined (_18F85K90) || defined (_18F86K90) || defined (_18F87K90)

#pragma config RETEN = 0FF
#pragma config INTOSCSEL = LOW
#pragma config SOSCSEL = DIG
#pragma config XINST = OFF
#pragma config FOSC = HS1
#pragma config PLLCFG = OFF
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRTEN = ON
#pragma config BOREN = OFF
#pragma config BORV = 3
#pragma config BORPWR = LOW
#pragma config WDTEN = OFF
#pragma config WDTPS = 7C
#pragma config RTCOSC = INTOSCREF
#pragma config CCP2MX = PORTC
#pragma config ECCPMX = PORTE
#pragma config MSSPMSK = MSK7
#pragma config MCLRE = OFF
#pragma config STVREN = OFF
#pragma config BBSIZ = BB1K
#pragma config DEBUG = OFF
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CP4 = OFF, CP5 = OFF, CP6 = OFF, CP7 = OFF
#pragma config CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRT4 = OFF, WRT5 = OFF, WRT6 = OFF, WRT7 = OFF
#pragma config WRTC = OFF, WRTB = OFF, WRTD = OFF
#pragma config EBRT0 = OFF, EBRT1 = OFF, EBRT2 = OFF, EBRT3 = OFF, EBRT4 = OFF, EBRT5 = OFF, EBRT6 = OFF, EBRT7 = OFF
#pragma config EBRTB = OFF

/*
 * CWORD:300000:5D:5D:CONFIG1L

 * CSETTING:1:RETEN:VREG Sleep Enable bit
CVALUE:1:ON:Enabled
CVALUE:0:OFF:Disabled - Controlled by SRETEN bit


 * CSETTING:4:INTOSCSEL:LF-INTOSC Low-power Enable bit
CVALUE:4:HIGH:LF-INTOSC in High-power mode during Sleep
CVALUE:0:LOW:LF-INTOSC in Low-power mode during Sleep
 * 
CSETTING:18:SOSCSEL:SOSC Power Selection and mode Configuration bits
CVALUE:18:HIGH:High Power SOSC circuit selected
CVALUE:8:LOW:Low Power SOSC circuit selected
CVALUE:10:DIG:Digital (SCLKI) mode

 * CSETTING:40:XINST:Extended Instruction Set
CVALUE:40:ON:Enabled
CVALUE:0:OFF:Disabled

 * CWORD:300001:DF:8:CONFIG1H

 * CSETTING:F:FOSC:Oscillator
CVALUE:7:RCIO:External RC oscillator
CVALUE:6:RC:External RC oscillator, CLKOUT function on OSC2
CVALUE:D:EC1:EC oscillator (Low power, DC - 160 kHz)
CVALUE:C:EC1IO:EC oscillator, CLKOUT function on OSC2 (Low power, DC - 160 kHz)
CVALUE:B:EC2:EC oscillator (Medium power, 160 kHz - 16 MHz)
CVALUE:A:EC2IO:EC oscillator, CLKOUT function on OSC2 (Medium power, 160 kHz - 16 MHz)
CVALUE:9:INTIO1:Internal RC oscillator, CLKOUT function on OSC2
CVALUE:8:INTIO2:Internal RC oscillator
CVALUE:5:EC3:EC oscillator (High power, 16 MHz - 64 MHz)
CVALUE:4:EC3IO:EC oscillator, CLKOUT function on OSC2 (High power, 16 MHz - 64 MHz)
CVALUE:3:HS1:HS oscillator (Medium power, 4 MHz - 16 MHz)
CVALUE:2:HS2:HS oscillator (High power, 16 MHz - 25 MHz)
CVALUE:1:XT:XT oscillator
CVALUE:0:LP:LP oscillator

 * CSETTING:10:PLLCFG:PLL x4 Enable bit
CVALUE:10:ON:Enabled
CVALUE:0:OFF:Disabled

 * CSETTING:40:FCMEN:Fail-Safe Clock Monitor
CVALUE:0:OFF:Disabled
CVALUE:40:ON:Enabled

 * CSETTING:80:IESO:Internal External Oscillator Switch Over Mode
CVALUE:0:OFF:Disabled
CVALUE:80:ON:Enabled

 * CWORD:300002:7F:7F:CONFIG2L

 * CSETTING:1:PWRTEN:Power Up Timer
CVALUE:1:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:6:BOREN:Brown Out Detect
CVALUE:6:SBORDIS:Enabled in hardware, SBOREN disabled
CVALUE:4:NOSLP:Enabled while active, disabled in SLEEP, SBOREN disabled
CVALUE:2:ON:Controlled with SBOREN bit
CVALUE:0:OFF:Disabled in hardware, SBOREN disabled

 * CSETTING:18:BORV:Brown-out Reset Voltage bits
CVALUE:18:3:1.8V
CVALUE:10:2:2.0V
CVALUE:8:1:2.7V
CVALUE:0:0:3.0V

 * CSETTING:60:BORPWR:BORMV Power level
CVALUE:60:ZPBORMV:ZPBORMV instead of BORMV is selected
CVALUE:40:HIGH:BORMV set to high power level
CVALUE:20:MEDIUM:BORMV set to medium power level
CVALUE:0:LOW:BORMV set to low power level

 * CWORD:300003:7F:7F:CONFIG2H

 * CSETTING:3:WDTEN:Watchdog Timer
CVALUE:3:SWDTDIS:WDT enabled in hardware; SWDTEN bit disabled
CVALUE:2:ON:WDT controlled by SWDTEN bit setting
CVALUE:1:NOSLP:WDT enabled only while device is active and disabled in Sleep mode; SWDTEN bit disabled
CVALUE:0:OFF:WDT disabled in hardware; SWDTEN bit disabled

 * CSETTING:7C:WDTPS:Watchdog Postscaler
CVALUE:7C:1048576:1:1048576
CVALUE:4C:524288:1:524288
CVALUE:48:262144:1:262144
CVALUE:44:131072:1:131072
CVALUE:40:65536:1:65536
CVALUE:3C:32768:1:32768
CVALUE:38:16384:1:16384
CVALUE:34:8192:1:8192
CVALUE:30:4096:1:4096
CVALUE:2C:2048:1:2048
CVALUE:28:1024:1:1024
CVALUE:24:512:1:512
CVALUE:20:256:1:256
CVALUE:1C:128:1:128
CVALUE:18:64:1:64
CVALUE:14:32:1:32
CVALUE:10:16:1:16
CVALUE:C:8:1:8
CVALUE:8:4:1:4
CVALUE:4:2:1:2
CVALUE:0:1:1:1

 * CWORD:300004:1:1:CONFIG3L

 * CSETTING:1:RTCOSC:RTCC Clock Select
CVALUE:1:SOSCREF:RTCC uses SOSC
CVALUE:0:INTOSCREF:RTCC uses INTRC

 * CWORD:300005:8B:8B:CONFIG3H
CSETTING:1:CCP2MX:CCP2 Mux
CVALUE:1:PORTC:RC1
CVALUE:0:PORTBE:RE7-Microcontroller Mode/RB3-All other modes

 * CSETTING:2:ECCPMX:ECCP Mux
CVALUE:2:PORTE:Enhanced CCP1/3 [P1B/P1C/P3B/P3C] muxed with RE6/RE5/RE4/RE3
CVALUE:0:PORTH:Enhanced CCP1/3 [P1B/P1C/P3B/P3C] muxed with RH7/RH6/RH5/RH4

 * CSETTING:8:MSSPMSK:MSSP address masking
CVALUE:8:MSK7:7 Bit address masking mode
CVALUE:0:MSK5:5 bit address masking mode

 * CSETTING:80:MCLRE:Master Clear Enable
CVALUE:80:ON:MCLR Enabled, RG5 Disabled
CVALUE:0:OFF:MCLR Disabled, RG5 Enabled

 * CWORD:300006:91:91:CONFIG4L

 * CSETTING:1:STVREN:Stack Overflow Reset
CVALUE:1:ON:Enabled
CVALUE:0:OFF:Disabled

 * CSETTING:10:BBSIZ:Boot Block Size
CVALUE:10:BB2K:2K word Boot Block size
CVALUE:0:BB1K:1K word Boot Block size

 * CSETTING:80:DEBUG:Background Debug
CVALUE:80:OFF:Disabled
CVALUE:0:ON:Enabled

 * CWORD:300008:FF:FF:CONFIG5L

 * CSETTING:1:CP0:Code Protect 00800-03FFF
CVALUE:1:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:2:CP1:Code Protect 04000-07FFF
CVALUE:2:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:4:CP2:Code Protect 08000-0BFFF
CVALUE:4:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:8:CP3:Code Protect 0C000-0FFFF
CVALUE:8:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:10:CP4:Code Protect 10000-13FFF
CVALUE:10:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:20:CP5:Code Protect 14000-17FFF
CVALUE:20:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:40:CP6:Code Protect 18000-1BFFF
CVALUE:40:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:80:CP7:Code Protect 1C000-1FFFF
CVALUE:80:OFF:Disabled
CVALUE:0:ON:Enabled

 * CWORD:300009:C0:C0:CONFIG5H

 * CSETTING:40:CPB:Code Protect Boot
CVALUE:40:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:80:CPD:Data EE Read Protect
CVALUE:80:OFF:Disabled
CVALUE:0:ON:Enabled

 * CWORD:30000A:FF:FF:CONFIG6L

 * CSETTING:1:WRT0:Table Write Protect 00800-03FFF
CVALUE:1:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:2:WRT1:Table Write Protect 04000-07FFF
CVALUE:2:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:4:WRT2:Table Write Protect 08000-0BFFF
CVALUE:4:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:8:WRT3:Table Write Protect 0C000-0FFFF
CVALUE:8:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:10:WRT4:Table Write Protect 10000-13FFF
CVALUE:10:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:20:WRT5:Table Write Protect 14000-17FFF
CVALUE:20:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:40:WRT6:Table Write Protect 18000-1BFFF
CVALUE:40:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:80:WRT7:Table Write Protect 1C000-1FFFF
CVALUE:80:OFF:Disabled
CVALUE:0:ON:Enabled

 * CWORD:30000B:E0:E0:CONFIG6H
CSETTING:20:WRTC:Config. Write Protect
CVALUE:20:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:40:WRTB:Table Write Protect Boot
CVALUE:40:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:80:WRTD:Data EE Write Protect
CVALUE:80:OFF:Disabled
CVALUE:0:ON:Enabled

 * CWORD:30000C:FF:FF:CONFIG7L
CSETTING:1:EBRT0:Table Read Protect 00800-03FFF
CVALUE:1:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:2:EBRT1:Table Read Protect 04000-07FFF
CVALUE:2:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:4:EBRT2:Table Read Protect 08000-0BFFF
CVALUE:4:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:8:EBRT3:Table Read Protect 0C000-0FFFF
CVALUE:8:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:10:EBRT4:Table Read Protect 10000-13FFF
CVALUE:10:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:20:EBRT5:Table Read Protect 14000-17FFF
CVALUE:20:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:40:EBRT6:Table Read Protect 18000-1BFFF
CVALUE:40:OFF:Disabled
CVALUE:0:ON:Enabled

 * CSETTING:80:EBRT7:Table Read Protect 1C000-1FFFF
CVALUE:80:OFF:Disabled
CVALUE:0:ON:Enabled

 * CWORD:30000D:40:40:CONFIG7H

 * CSETTING:40:EBRTB:Table Read Protect Boot
CVALUE:40:OFF:Disabled
CVALUE:0:ON:Enabled
CWORD:200000:F:FF:IDLOC0
CWORD:200001:F:FF:IDLOC1
CWORD:200002:F:FF:IDLOC2
CWORD:200003:F:FF:IDLOC3
CWORD:200004:F:FF:IDLOC4
CWORD:200005:F:FF:IDLOC5
CWORD:200006:F:FF:IDLOC6
CWORD:200007:F:FF:IDLOC7
*/

#elif   defined (_18F2331) || defined (_18F2431) || defined (_18F4331) || defined (_18F4431)

//#pragma config <setting>=<named value>

#pragma config IESO = OFF		//OFF	Internal External Switchover mode disabled
#pragma config OSC = IRCIO		//RC, RC1, IRCIO, RCIO, RC2, XT, LP, IRC, HSPLL, ECIO, EC, HS
#pragma config FCMEN = OFF		//OFF	Fail-Safe Clock Monitor disabled
#pragma config BOREN = OFF		//OFF	Brown-out Reset disabled
#pragma config BORV = 27		//27=2.7V, 42=4.2V, 45=4.5V
#pragma config PWRTEN = OFF		//OFF	PWRT disabled
#pragma config WDPS = 32768
#pragma config WDTEN = OFF		//OFF	WDT disabled (control is placed on the SWDTEN bit)
#pragma config WINEN = OFF		//OFF	WDT window disabled
#pragma config T1OSCMX = OFF	//OFF	Standard (legacy) Timer1 oscillator operation
#pragma config PWMPIN = OFF		//OFF	PWM outputs disabled upon Reset (default)
#pragma config HPOL = HIGH		//High-Side Transistors Polarity / HIGH	PWM1, 3, 5 and 7 are active-high / LOW	PWM1, 3, 5 and 7 are active-low
#pragma config LPOL = HIGH		//Low-Side Transistors Polarity / HIGH	PWM0, 2, 4 and 6 are active-high / LOW	PWM0, 2, 4 and 6 are active-low
#pragma config FLTAMX =	RC1		//FLTA MUX bit / RC1	FLTA input is multiplexed with RC1 / RD4	FLTA input is multiplexed with RD4
#pragma config MCLRE = OFF		//MCLR Pin Enable bit / OFF	Disabled / ON	Enabled
#pragma config PWM4MX =	RB5		//PWM4 MUX bit / RB5	PWM4 output is multiplexed with RB5 / RD5	PWM4 output is multiplexed with RD5
#pragma config SSPMX = RD1		//SSP I/O MUX bit / RD1	SCK/SCL clocks and SDA/SDI data are multiplexed with RD3 and RD2, respectively. SDO output is multiplexed with RD1. / RC7	SCK/SCL clocks and SDA/SDI data are multiplexed with RC5 and RC4, respectively. SDO output is multiplexed with RC7.
#pragma config EXCLKMX = RD0	//TMR0/T5CKI External clock MUX bit / RD0	TMR0/T5CKI external clock input is multiplexed with RD0 / RC3	TMR0/T5CKI external clock input is multiplexed with RC3
#pragma config DEBUG = OFF		//Background Debugger Enable bit / OFF	Background debugger disabled; RB6 and RB7 configured as general purpose I/O pins / ON	Background debugger enabled; RB6 and RB7 are dedicated to In-Circuit Debug
#pragma config STVREN = OFF		//Stack Full/Underflow Reset Enable bit / OFF	Stack full/underflow will not cause Reset / ON	Stack full/underflow will cause Reset
#pragma config LVP = OFF		//Low-Voltage ICSP Enable bit / OFF	Low-voltage ICSP disabled / ON	Low-voltage ICSP enabled
#pragma config CP0 = OFF		//Code Protection bit / OFF	Block 0 (000200-000FFFh) not code-protected / ON	Block 0 (000200-000FFFh) code-protected
#pragma config CP1 = OFF		//Code Protection bit / OFF	Block 1 (001000-001FFF) not code-protected / ON	Block 1 (001000-001FFF) code-protected
#pragma config CP2 = OFF		//Code Protection bit / OFF	Block 2 (002000-002FFFh) not code-protected / ON	Block 2 (002000-002FFFh) code-protected
#pragma config CP3 = OFF		//Code Protection bit / OFF	Block 3 (003000-003FFFh) not code-protected / ON	Block 3 (003000-003FFFh) code-protected
#pragma config CPD = OFF		//Data EEPROM Code Protection bit / OFF	Data EEPROM not code-protected / ON	Data EEPROM code-protected
#pragma config CPB = OFF		//Boot Block Code Protection bit / OFF	Boot Block (000000-0001FFh) not code-protected / ON	Boot Block (000000-0001FFh) code-protected
#pragma config WRT0 = OFF		//Write Protection bit / OFF	Block 0 (000200-000FFFh) not write-protected / ON	Block 0 (000200-000FFFh) write-protected
#pragma config WRT1 = OFF		//Write Protection bit / OFF	Block 1 (001000-001FFF) not write-protected / ON	Block 1 (001000-001FFF) write-protected
#pragma config WRT2 = OFF		//Write Protection bit / OFF	Block 2 (002000-002FFFh) not write-protected / ON	Block 2 (002000-002FFFh) write-protected
#pragma config WRT3 = OFF		//Write Protection bit / OFF	Block 3 (003000-003FFFh) not write-protected / ON	Block 3 (003000-003FFFh) write-protected
#pragma config WRTB = OFF		//Boot Block Write Protection bit / OFF	Boot Block (000000-0001FFh) not write-protected / ON	Boot Block (000000-0001FFh) write-protected
#pragma config WRTC = OFF		//Configuration Register Write Protection bit / OFF	Configuration registers (300000-3000FFh) not write-protected / ON	Configuration registers (300000-3000FFh) write-protected
#pragma config WRTD = OFF		//Data EEPROM Write Protection bit / OFF	Data EEPROM not write-protected / ON	Data EEPROM write-protected
#pragma config EBTR0 = OFF		//Table Read Protection bit / OFF	Block 0 (000200-000FFFh) not protected from table reads executed in other blocks / ON	Block 0 (000200-000FFFh) protected from table reads executed in other blocks
#pragma config EBTR1 = OFF		//Table Read Protection bit / OFF	Block 1 (001000-001FFF) not protected from table reads executed in other blocks / ON	Block 1 (001000-001FFF) protected from table reads executed in other blocks
#pragma config EBTR2 = OFF		//Table Read Protection bit / OFF	Block 2 (002000-002FFFh) not protected from table reads executed in other blocks / ON	Block 2 (002000-002FFFh) protected from table reads executed in other blocks
#pragma config EBTR3 = OFF		//Table Read Protection bit / OFF	Block 3 (003000-003FFFh) not protected from table reads executed in other blocks / ON	Block 3 (003000-003FFFh) protected from table reads executed in other blocks
#pragma config EBTRB = OFF		//Boot Block Table Read Protection bit / OFF	Boot Block (000000-0001FFh) not protected from table reads executed in other blocks / ON	Boot Block (000000-0001FFh) not protected from table reads executed in other blocks


//For example:
// Internal External Oscillator Switchover bit: Internal External Switchover mode disabled
// Oscillator Selection bits: 11XX External RC oscillator, CLKO function on RA6
// Fail-Safe Clock Monitor Enable bit: Fail-Safe Clock Monitor disabled
//#pragma config IESO = OFF, OSC = RC, FCMEN = OFF
//#pragma config <setting>=<literal constant>

//For example:
// Internal External Oscillator Switchover bit: Internal External Switchover mode disabled
// Oscillator Selection bits: 11XX External RC oscillator, CLKO function on RA6
// Fail-Safe Clock Monitor Enable bit: Fail-Safe Clock Monitor disabled
//#pragma config IESO = 0x0, OSC = 0xC, FCMEN = 0x0
//#pragma config <register>=<literal constant>

//For example: 
// Internal External Oscillator Switchover bit: Internal External Switchover mode disabled
// Oscillator Selection bits: 11XX External RC oscillator, CLKO function on RA6
// Fail-Safe Clock Monitor Enable bit: Fail-Safe Clock Monitor disabled
//#pragma config CONFIG1H = 0xC

//For example: 
// IDLOC @ 0x200000
//#pragma config IDLOC0 = 0xFF
//#pragma config Settings

//Register: CONFIG1H @ 0x300001

//IESO =	Internal External Oscillator Switchover bit
//OFF	Internal External Switchover mode disabled
//ON	Internal External Switchover mode enabled
//OSC =	Oscillator Selection bits
//RC	11XX External RC oscillator, CLKO function on RA6
//RC1	101X External RC oscillator, CLKO function on RA6
//IRCIO	Internal oscillator block, port function on RA6 and port function on RA7
//RCIO	External RC oscillator, port function on RA6
//RC2	External RC oscillator, CLKO function on RA6
//XT	XT oscillator
//LP	LP oscillator
//IRC	Internal oscillator block, CLKO function on RA6 and port function on RA7
//HSPLL	HS oscillator, PLL enabled (clock frequency = 4 x FOSC1)
//ECIO	EC oscillator, port function on RA6
//EC	EC oscillator, CLKO function on RA6
//HS	HS oscillator
//FCMEN =	Fail-Safe Clock Monitor Enable bit
//OFF	Fail-Safe Clock Monitor disabled
//ON	Fail-Safe Clock Monitor enabled
//Register: CONFIG2L @ 0x300002

//BOREN =	Brown-out Reset Enable bits
//OFF	Brown-out Reset disabled
//ON	Brown-out Reset enabled
//BORV =	Brown Out Reset Voltage bits
//42	VBOR set to 4.2V
//27	VBOR set to 2.7V
//45	VBOR set to 4.5V
//PWRTEN =	Power-up Timer Enable bit
//OFF	PWRT disabled
//ON	PWRT enabled
//Register: CONFIG2H @ 0x300003

//WDPS =	Watchdog Timer Postscale Select bits
//8	1:8
//1	1:1
//32768	1:32768
//1024	1:1024
//2	1:2
//32	1:32
//16	1:16
//16384	1:16384
//128	1:128
//4096	1:4096
//64	1:64
//8192	1:8192
//2048	1:2048
//512	1:512
//256	1:256
//4	1:4
//WDTEN =	Watchdog Timer Enable bit
//OFF	WDT disabled (control is placed on the SWDTEN bit)
//ON	WDT enabled
//WINEN =	Watchdog Timer Window Enable bit
//OFF	WDT window disabled
//ON	WDT window enabledbled
//Register: CONFIG3L @ 0x300004

//T1OSCMX =	Timer1 Oscillator MUX
//OFF	Standard (legacy) Timer1 oscillator operation
//ON	Low-power Timer1 operation when microcontroller is in Sleep mode
//PWMPIN =	PWM output pins Reset state control
//OFF	PWM outputs disabled upon Reset (default)
//ON	PWM outputs drive active states upon Reset
//HPOL =	High-Side Transistors Polarity
//HIGH	PWM1, 3, 5 and 7 are active-high
//LOW	PWM1, 3, 5 and 7 are active-low
//LPOL =	Low-Side Transistors Polarity
//HIGH	PWM0, 2, 4 and 6 are active-high
//LOW	PWM0, 2, 4 and 6 are active-low
//Register: CONFIG3H @ 0x300005

//FLTAMX =	FLTA MUX bit
//RC1	FLTA input is multiplexed with RC1
//RD4	FLTA input is multiplexed with RD4
//MCLRE =	MCLR Pin Enable bit
//OFF	Disabled
//ON	Enabled
//PWM4MX =	PWM4 MUX bit
//RB5	PWM4 output is multiplexed with RB5
//RD5	PWM4 output is multiplexed with RD5
//SSPMX =	SSP I/O MUX bit
//RD1	SCK/SCL clocks and SDA/SDI data are multiplexed with RD3 and RD2, respectively. SDO output is multiplexed with RD1.
//RC7	SCK/SCL clocks and SDA/SDI data are multiplexed with RC5 and RC4, respectively. SDO output is multiplexed with RC7.
//EXCLKMX =	TMR0/T5CKI External clock MUX bit
//RD0	TMR0/T5CKI external clock input is multiplexed with RD0
//RC3	TMR0/T5CKI external clock input is multiplexed with RC3
//Register: CONFIG4L @ 0x300006

//DEBUG =	Background Debugger Enable bit
//OFF	Background debugger disabled; RB6 and RB7 configured as general purpose I/O pins
//ON	Background debugger enabled; RB6 and RB7 are dedicated to In-Circuit Debug
//STVREN =	Stack Full/Underflow Reset Enable bit
//OFF	Stack full/underflow will not cause Reset
//ON	Stack full/underflow will cause Reset
//LVP =	Low-Voltage ICSP Enable bit
//OFF	Low-voltage ICSP disabled
//ON	Low-voltage ICSP enabled
//Register: CONFIG5L @ 0x300008

//CP0 =	Code Protection bit
//OFF	Block 0 (000200-000FFFh) not code-protected
//ON	Block 0 (000200-000FFFh) code-protected
//CP1 =	Code Protection bit
//OFF	Block 1 (001000-001FFF) not code-protected
//ON	Block 1 (001000-001FFF) code-protected
//CP2 =	Code Protection bit
//OFF	Block 2 (002000-002FFFh) not code-protected
//ON	Block 2 (002000-002FFFh) code-protected
//CP3 =	Code Protection bit
//OFF	Block 3 (003000-003FFFh) not code-protected
//ON	Block 3 (003000-003FFFh) code-protected
//Register: CONFIG5H @ 0x300009

//CPD =	Data EEPROM Code Protection bit
//OFF	Data EEPROM not code-protected
//ON	Data EEPROM code-protected
//CPB =	Boot Block Code Protection bit
//OFF	Boot Block (000000-0001FFh) not code-protected
//ON	Boot Block (000000-0001FFh) code-protected
//Register: CONFIG6L @ 0x30000A

//WRT0 =	Write Protection bit
//OFF	Block 0 (000200-000FFFh) not write-protected
//ON	Block 0 (000200-000FFFh) write-protected
//WRT1 =	Write Protection bit
//OFF	Block 1 (001000-001FFF) not write-protected
//ON	Block 1 (001000-001FFF) write-protected
//WRT2 =	Write Protection bit
//OFF	Block 2 (002000-002FFFh) not write-protected
//ON	Block 2 (002000-002FFFh) write-protected
//WRT3 =	Write Protection bit
//OFF	Block 3 (003000-003FFFh) not write-protected
//ON	Block 3 (003000-003FFFh) write-protected
//Register: CONFIG6H @ 0x30000B

//WRTB =	Boot Block Write Protection bit
//OFF	Boot Block (000000-0001FFh) not write-protected
//ON	Boot Block (000000-0001FFh) write-protected
//WRTC =	Configuration Register Write Protection bit
//OFF	Configuration registers (300000-3000FFh) not write-protected
//ON	Configuration registers (300000-3000FFh) write-protected
//WRTD =	Data EEPROM Write Protection bit
//OFF	Data EEPROM not write-protected
//ON	Data EEPROM write-protected
//Register: CONFIG7L @ 0x30000C

//EBTR0 =	Table Read Protection bit
//OFF	Block 0 (000200-000FFFh) not protected from table reads executed in other blocks
//ON	Block 0 (000200-000FFFh) protected from table reads executed in other blocks
//EBTR1 =	Table Read Protection bit
//OFF	Block 1 (001000-001FFF) not protected from table reads executed in other blocks
//ON	Block 1 (001000-001FFF) protected from table reads executed in other blocks
//EBTR2 =	Table Read Protection bit
//OFF	Block 2 (002000-002FFFh) not protected from table reads executed in other blocks
//ON	Block 2 (002000-002FFFh) protected from table reads executed in other blocks
//EBTR3 =	Table Read Protection bit
//OFF	Block 3 (003000-003FFFh) not protected from table reads executed in other blocks
//ON	Block 3 (003000-003FFFh) protected from table reads executed in other blocks
//Register: CONFIG7H @ 0x30000D

//EBTRB =	Boot Block Table Read Protection bit
//OFF	Boot Block (000000-0001FFh) not protected from table reads executed in other blocks
//ON	Boot Block (000000-0001FFh) not protected from table reads executed in other blocks
//Register: IDLOC0 @ 0x200000

//Register: IDLOC1 @ 0x200001

//Register: IDLOC2 @ 0x200002

//Register: IDLOC3 @ 0x200003

//Register: IDLOC4 @ 0x200004

//Register: IDLOC5 @ 0x200005

//Register: IDLOC6 @ 0x200006

//Register: IDLOC7 @ 0x200007

#else
//missing header files
	#warning no device header file defined!
#endif

#endif //config_h_
