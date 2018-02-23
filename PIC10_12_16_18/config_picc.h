#ifndef __CONFIG_H
#define __CONFIG_H

//config.h - config words file
//chips covered
//10f200, 10f202, 10f204, 10f206

//12f629, 12f675

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
//18f46k22

//10f200, 10f202, 10f204, 10f206
#if defined(_10F200) || defined(_10F202) || defined(_10F204) || defined(_10F206)
//configuration bits
__CONFIG(MCLRDIS & WDTDIS & UNPROTECT);
/* MCLR Pin function */
//#define MCLREN		0xFFF	// master clear reset enable
//#define MCLRDIS		0xFEF	// master clear reset disable

/* watchdog*/
//#define WDTEN		0xFFF	// watchdog timer enable
//#define WDTDIS		0xFFB	// watchdog timer disable

/* code protection */
//#define PROTECT		0xFF7	// protect the program code
//#define UNPROTECT	0xFFF	// do not protect the program code


//12f675
#elif	defined(_12F629)	|| defined(_12F675)
//configuration bits
	//__CONFIG(BORDIS & MCLRDIS & PWRTEN & WDTDIS & HS);
	__CONFIG(
/* Protection of data block */
		//CPD		&		//0x3EFF		/* data protect on */ 
		UNPROTECT	&		//0x3FFF 	/* data protect off */

/* Protection of program code */
		//PROTECT	&		//0x3F7F 		/* code protection on */
		UNPROTECT	&		//0x3FFF 	/* code protection off */

/* Brown out detection enable */
		//BOREN		&		//0x3FFF 		/* brown out reset enabled */
		BORDIS		&		//0x3FBF 		/* brown out reset disabled */

/* Master clear reset */
		//MCLREN	&		//0x3FFF 		/* master clear reset function enabled */
		MCLRDIS		&		//0x3FDF 		/* master clear reset function disabled */

/* Power up timer enable */
		//PWRTDIS	&		//0x3FFF 		/* power up timer disabled */
		PWRTEN		&		//0x3FEF 		/* power up timer enabled */

/* Watchdog timer enable */
		//WDTEN		&		//0x3FFF 		/* watchdog timer enabled */
		WDTDIS		&		//0x3FF7 		/* watchdog timer disabled */

/* Oscillator configurations */
		//RCCLK		&		//0x3FFF 		/* GP4 = clock out signal/GP5 = RC osc */
		//RCIO		&		//0x3FFE 		/* GP4 = IO/GP5 = RC osc */
		//INTCLK	&		//0x3FFD 		/* internal osc/GP4 = clock out signal/GP5 = IO */
		INTIO		&		//0x3FFC 		/* internal osc/GP4 = IO//GP5 = IO */
		//EC		&		//0x3FFB 		/* external clock */
		//HS		&		//0x3FFA 		/* high speed crystal/resonator */
		//XT		&		//0x3FF9 		/* crystal/resonator */
		//LP		&		//0x3FF8 		/* low power crystal/resonator */

		UNPROTECT);
		
//end configuration bits
//#endif

#elif defined(_16F627)	|| defined(_16F628)
	__CONFIG(WDTDIS & PWRTEN & MCLRDIS & BORDIS & LVPDIS & DATUNPROT & HS);
	
/*watchdog*/
//#define WDTEN		0x3FFF	// enable watchdog timer
//#define WDTDIS		0x3FFB	// disable watchdog timer

/*power up timer*/
//#define PWRTEN		0x3FF7	// enable power up timer
//#define PWRTDIS		0x3FFF	// disable power up timer

/* MCLR pin function */
//#define MCLREN		0x3FFF	// master clear reset enable
//#define MCLRDIS		0x3FDF	// master clear reset disable
//alternately
//#define MCLRIO		0x3FDF // use MCLRDIS

/*brown out reset*/
//#define BOREN		0x3FFF	// enable brown out reset
//#define BORDIS		0x3FBF	// disable brown out reset

/*low voltage programming*/
//#define LVPEN		0x3FFF	// low voltage programming enable
//#define LVPDIS		0x3F7F	// low voltage programming disabled

/*data code protection*/
//#define DP		0x3EFF	// protect the data code
// alternative definitions
//#define DATPROT		0x3EFF	// use DP
//#define DATUNPROT	0x3FFF	// use UNPROTECT

/*code protection*/
//#define UNPROTECT	0x3FFF	// do not protect the code
//#define PROTECT		0x03FF	// protect the program code
	/* Code protection for 2K program memory	*/
//#ifdef _16F628		
//#define PROTECT75	0x17FF	/* Protects from 0200h-07ffh	*/
//#define PROTECT50	0x2BFF	/* Protects from 0400h-07ffh	*/
//#else	/* Code protection for 1K program memory	*/
//#define PROTECT50	0x17FF	/* Protects from 0200h-03ffh	*/
//#endif 

/*osc configurations*/
//#define ER		0x3FFF	/* external resistor, CLKOUT on CLKOUT pin, R on CLKIN */
//#define ERIO		0x3FFE	/* external resistor, IO fn on CLKOUT pin, R on CLKIN */
//#define INT		0x3FFD	/* internal resistor/capacitor, CLKOUT on CLKOUT pin, IO on CLKIN */
//#define INTIO		0x3FFC	/* internal resistor/capacitor, IO fn on CLKOUT pin, IO on CLKIN */
//#define EC		0x3FEF	/* external clock in, IO fn on CLKOUT pin, CLKIN on CLKIN */
//#define HS		0x3FEE	/* high speed crystal */
//#define XT		0x3FED	/* crystal/resonator */
//#define LP		0x3FEC	/* low power crystal */

#elif defined(_16F627A)	|| defined(_16F628A)	|| defined(_16F648A)
	__CONFIG(LVPDIS & BORDIS & MCLRDIS & PWRTEN & WDTDIS & HS);
/*
// Configuration Mask Definitions
#define CONFIG_ADDR	0x2007
// Protection of flash memory 
#define PROTECT		0x1FFF
#define UNPROTECT	0x3FFF
// Protection of EEPROM data memory 
#define CPD		0x3EFF
#define UNPROTECT	0x3FFF
// Low voltage programming enable 
#define LVPEN		0x3FFF
#define LVPDIS		0x3F7F
// Brown out detection enable 
#define BOREN		0x3FFF
#define BORDIS		0x3FBF
// Master clear reset pin function
#define MCLREN		0x3FFF
#define MCLRDIS		0x3FDF
// Power up timer enable 
#define PWRTEN		0x3FF7
#define PWRTDIS		0x3FFF
// Watchdog timer enable 
#define WDTEN		0x3FFF
#define WDTDIS		0x3FFB
// Oscillator configurations 
#define RCCLK		0x3FFF
#define RCIO		0x3FFE
#define INTCLK		0x3FFD
#define INTIO		0x3FFC
#define EC		0x3FEF
#define HS		0x3FEE
#define XT		0x3FED
#define LP		0x3FEC
*/
//#endif

#elif defined(_16F630)	|| defined(_16F676)
	//__CONFIG(BGLOW & UNPROTECT & BORDIS & MCLRDIS & PWRTEN & WDTDIS & HS);
	__CONFIG(
	// bandgap calibration
		BGHIGH		&		//0x3FFF	// highest bandgap voltage
		//BGLOW		&		//0x0FFF	// lowest bandgap volatage
// data code protection
		//CPD		&		//0x3EFF	// protect data memory
		UNPROTECT	&		//0x3FFF	// do not protect memory
// code protection
		//CPROTECT	&		//0x3F7F	// protect program memory
// brown-out detect enable
		//BOREN		&		//0x3FFF	// brown-out reset enabled
		BORDIS		&		//0x3FBF	// brown-out reset disabled
// RA3/MCLR pin function select
		//MCLREN	&		//0x3FFF	// MCLR pin function enabled
		MCLRDIS		&		//0x3FDF	// MCLR pin function disabled
// power-up timer enable
		PWRTEN		&		//0x3FEF	// power-up timer enabled
		//PWRTDIS	&		//0x3FFF	// power-up timer disabled
// watchdog timer enable
		//WDTEN		&		//0x3FFF	// watchdog timer enabled
		WDTDIS		&		//0x3FF7	// watchdog timer disabled
// oscillator selection
		//RCCLKO	&		//0x3FFF	// RC osc, RA4 pin is CLKOUT
		//RCIO		&		//0x3FFE	// RC osc, RA4 pin is IO
		//INTOSCCLKO	&		//0x3FFD	// INTOSC, RA4 pin is CLKOUT
		//INTOSCIO	&		//0x3FFC	// INTOSC, RA4 pin is IO
		//EC		&		//0x3FFB	// external clock
		HS		&		//0x3FFA	// high speed XTAL/resonator
		//XT		&		//0x3FF9	// XTAL/resonator
		//LP		&		//0x3FF8	// low power XTAL/resonator
		UNPROTECT);

//#endif

//16f684
#elif 	defined(_16F684)
//configuration bits
	//__CONFIG(BORDIS & MCLRDIS & PWRTEN & WDTDIS & HS);
	__CONFIG(
// Fail-Safe clock monitor 
		//FCMEN		&		//0x3FFF
		FCMDIS		&		//0x37FF
// Internal External Switch Over 
		//IESOEN	&		//0x3FFF
		IESODIS		&		//0x3BFF
// Brown-out detect modes 
		//BOREN		&		//0x3FFF
		//BOREN_XSLP	&	//0x3EFF
		//SBOREN	&		//0x3DFF
		BORDIS		&		//0x3CFF
// Protection of data block 
		UNPROTECT	&		//0x3FFF
		//CPD		&		//0x3F7F
// Protection of program code 
		UNPROTECT	&		//0x3FFF
		//PROTECT	&		//0x3FBF
// Master clear reset pin function 
		//MCLREN	&		//0x3FFF
		MCLRDIS		&		//0x3FDF
// Power up timer enable 
		//PWRTDIS	&		//0x3FFF
		PWRTEN	&			//0x3FEF
// Watchdog timer enable 
		//WDTEN		&		//0x3FFF
		WDTDIS		&		//0x3FF7
// Oscillator configurations 
		//RCCLK		&		//0x3FFF
		//RCIO		&		//0x3FFE
		//INTCLK	&		//0x3FFD
		INTIO		&		//0x3FFC
		//EC		&		//0x3FFB
		//HS		&		//0x3FFA
		//XT		&		//0x3FF9
		//LP		&		//0x3FF8
		UNPROTECT);
//end configuration bits
//#endif

#elif 	defined(_16F631)	|| defined(_16F677)	|| defined(_16F685)	||\
    	defined(_16F687)	|| defined(_16F689)	|| defined(_16F690)
	__CONFIG(HS & WDTDIS & PWRTEN & MCLRDIS & UNPROTECT & BORDIS & IESODIS & FCMDIS);
/*
// Configuration Mask Definitions
#define CONFIG_ADDR	0x2007
// Oscillator 
#define EXTCLK		0x3FFF	// External RC Clockout
#define EXTIO		0x3FFE	// External RC No Clock
#define INTCLK		0x3FFD	// Internal RC Clockout
#define INTIO		0x3FFC	// Internal RC No Clock
#define EC		0x3FFB	// EC
#define HS		0x3FFA	// HS
#define XT		0x3FF9	// XT
#define LP		0x3FF8	// LP
// Watchdog Timer 
#define WDTEN		0x3FFF	// On
#define WDTDIS		0x3FF7	// Off
// Power Up Timer 
#define PWRTDIS		0x3FFF	// Off
#define PWRTEN		0x3FEF	// On
// Master Clear Enable 
#define MCLREN		0x3FFF	// MCLR function is enabled
#define MCLRDIS		0x3FDF	// MCLR functions as IO
// Code Protect 
#define UNPROTECT	0x3FFF	// Code is not protected
#define CP		0x3FBF	// Code is protected
#define PROTECT		CP	//alternate
// Data EE Read Protect 
#define UNPROTECT	0x3FFF	// Do not read protect EEPROM data
#define CPD		0x3F7F	// Read protect EEPROM data
// Brown Out Detect 
#define BORDIS		0x3CFF	// BOD and SBOREN disabled
#define SWBOREN		0x3DFF	// SBOREN controls BOR function (Software control)
#define BORXSLP		0x3EFF	// BOD enabled in run, disabled in sleep, SBOREN disabled
#define BOREN		0x3FFF	// BOD Enabled, SBOREN Disabled
// Internal External Switch Over Mode 
#define IESOEN		0x3FFF	// Enabled
#define IESODIS		0x3BFF	// Disabled
// Monitor Clock Fail-safe 
#define FCMEN		0x3FFF	// Enabled
#define FCMDIS		0x37FF	// Disabled
//#endif
*/

//16f688
#elif defined(_16F688)
	__CONFIG(FCMDIS & IESODIS & BORDIS & MCLRDIS & PWRTEN & WDTDIS & INTIO);					
/*// Configuration Mask Definitions
#define CONFIG_ADDR	0x2007
// Fail-Safe clock monitor 
#define FCMEN		0x3FFF
#define FCMDIS		0x37FF
// Internal External Switch Over 
#define IESOEN		0x3FFF
#define IESODIS		0x3BFF
// Brown-out detect modes 
#define BOREN		0x3FFF
#define BOREN_XSLP	0x3EFF
#define SBOREN		0x3DFF
#define BORDIS		0x3CFF
// Protection of data block 
#define UNPROTECT	0x3FFF
#define CPD		0x3F7F
// Protection of program code 
#define UNPROTECT	0x3FFF
#define PROTECT		0x3FBF
// Master clear reset pin function
#define MCLREN		0x3FFF
#define MCLRDIS		0x3FDF
// Power up timer enable 
#define PWRTDIS		0x3FFF
#define PWRTEN		0x3FEF
// Watchdog timer enable 
#define WDTEN		0x3FFF
#define WDTDIS		0x3FF7
// Oscillator configurations 
#define RCCLK		0x3FFF
#define RCIO		0x3FFE
#define INTCLK		0x3FFD
#define INTIO		0x3FFC
#define EC		0x3FFB
#define HS		0x3FFA
#define XT		0x3FF9
#define LP		0x3FF8
*/
//#endif

//16f877
#elif defined(_16F873)	|| defined(_16F874)	||\
    defined(_16F876)	|| defined(_16F877)	||\
    defined(_16F872)	|| defined(_16F871)	||\
    defined(_16F870)
    
    __CONFIG(HS & WDTDIS & PWRTEN & BORDIS & LVPDIS & DUNPROT & WRTDIS & DEBUGDIS & UNPROTECT);
/*
//osc configurations
#define RC		0x3FFF	// resistor/capacitor
#define HS		0x3FFE	// high speed crystal/resonator
#define XT		0x3FFD	// crystal/resonator
#define LP		0x3FFC	// low power crystal/resonator

//watchdog
#define WDTEN		0x3FFF	// enable watchdog timer
#define WDTDIS		0x3FFB	// disable watchdog timer

//power up timer
#define PWRTEN		0x3FF7	// enable power up timer
#define PWRTDIS		0x3FFF	// disable power up timer

//brown out reset
#define BOREN		0x3FFF	// enable brown out reset
#define BORDIS		0x3FBF	// disable brown out reset

//Low Voltage Programmable
#define LVPEN		0x3FFF	// low voltage programming enabled
#define LVPDIS		0x3F7F	// low voltage programming disabled

//data code protected
#define DP		0x3EFF	// protect data code
// alternately
#define DPROT		0x3EFF	// use DP
#define DUNPROT		0x3FFF	// use UNPROTECT

// Flash memory write enable/protect 
#define WRTEN		0x3FFF	// flash memory write enabled 
#define WRTDIS		0x3DFF	// flash memory write protected/disabled 

//debug option
#define DEBUGEN		0x37FF	// debugger enabled
#define DEBUGDIS	0x3FFF	// debugger disabled

//code protection
#define PROTECT		0x0FCF	// protect program code 
#define UNPROTECT	0x3FFF	// do not protect the code 

#if !defined(_16F870) && !defined(_16F871)
#define	PROTECT_TOP	0x2FEF	// protects top 256 bytes, 1F00h to 1FFFh	
#define PROTECT50	0x1FDF	// protects upper half of address space		
				// 1000h to 1FFFh (pic16f887/876)		
				// 0800h to 0FFFh (pic16f874/873)		
*/
//#endif

//16f877a
#elif defined(_16F873A)	|| defined(_16F874A)	||\
    defined(_16F876A)	|| defined(_16F877A)
	__CONFIG(HS & WDTDIS & PWRTEN & BORDIS & LVPDIS & DUNPROT & DEBUGDIS & UNPROTECT);
/*
//osc configurations
#define RC		0x3FFF	// resistor/capacitor
#define HS		0x3FFE	// high speed crystal/resonator
#define XT		0x3FFD	// crystal/resonator
#define LP		0x3FFC	// low power crystal/resonator

//watchdog
#define WDTEN		0x3FFF	// enable watchdog timer
#define WDTDIS		0x3FFB	// disable watchdog timer

//power up timer
#define PWRTEN		0x3FF7	// enable power up timer
#define PWRTDIS		0x3FFF	// disable power up timer

//brown out reset
#define BOREN		0x3FFF	// enable brown out reset
#define BORDIS		0x3FBF	// disable brown out reset

//Low Voltage Programmable
#define LVPEN		0x3FFF	// low voltage programming enabled
#define LVPDIS		0x3F7F	// low voltage programming disabled

//data code protected
#define DP		0x3EFF	// protect data code
// alternately
#define DPROT		0x3EFF	// use DP
#define DUNPROT		0x3FFF	// use UNPROTECT

// Flash memory write enable/protect 
#define WRTEN		0x3FFF	// flash memory write enabled 
#define WP1		0x3DFF  // protect 0000 - 00FF 
#define WP2		0x3BFF  // protect 0000 - 07FF(76A/77A) / 03FF(73A/74A) 
#define WP3		0x39FF  // protect 0000 - 1FFF(76A/77A) / 0FFF(73A/74A) 

//debug option
#define DEBUGEN		0x37FF	// debugger enabled
#define DEBUGDIS	0x3FFF	// debugger disabled

//code protection
#define PROTECT		0x1FFF	// protect program code
#define UNPROTECT	0x3FFF	// do not protect the code
*/
//#endif

//16f886
#elif 	defined(_16F882)	|| defined(_16F883)	|| defined(_16F884)	||\
    	defined(_16F886)	|| defined(_16F887)
//configuration bits
	__CONFIG(BORDIS & MCLRDIS & PWRTDIS & WDTDIS & HS & LVPDIS & IESODIS & FCMDIS & DEBUGDIS);
	__CONFIG(UNPROTECT & BORV21);
/*
// Oscillator 
#define EXTCLK		0x3FFF	// External RC Clockout
#define EXTIO		0x3FFE	// External RC No Clock
#define INTCLK		0x3FFD	// Internal RC Clockout
#define INTIO		0x3FFC	// Internal RC No Clock
#define EC		0x3FFB	// EC
#define HS		0x3FFA	// HS
#define XT		0x3FF9	// XT
#define LP		0x3FF8	// LP
// Watchdog Timer 
#define WDTEN		0x3FFF	// On
#define WDTDIS		0x3FF7	// Disabled / SWDTEN control
// Power Up Timer 
#define PWRTDIS		0x3FFF	// Off
#define PWRTEN		0x3FEF	// On
// Master Clear Enable 
#define MCLREN		0x3FFF	// MCLR function is enabled
#define MCLRDIS		0x3FDF	// MCLR functions as IO
// Code Protect 
#define UNPROTECT	0x3FFF	// Code is not protected
#define CP		0x3FBF	// Code is protected
#define PROTECT		CP	//alternate
// Data EE Read Protect 
#define DUNPROTECT	0x3FFF	// Do not read protect EEPROM data
#define CPD		0x3F7F	// Read protect EEPROM data
// Brown Out Detect 
#define BORDIS		0x3CFF	// BOD and SBOREN disabled
#define SWBOREN		0x3DFF	// SBOREN controls BOR function (Software control)
#define BORXSLP		0x3EFF	// BOD enabled in run, disabled in sleep, SBOREN disabled
#define BOREN		0x3FFF	// BOD Enabled, SBOREN Disabled
// Internal External Switch Over Mode 
#define IESOEN		0x3FFF	// Enabled
#define IESODIS		0x3BFF	// Disabled
// Monitor Clock Fail-safe 
#define FCMEN		0x3FFF	// Enabled
#define FCMDIS		0x37FF	// Disabled
// Low Voltage Programming 
#define LVPDIS		0x2FFF	// Disabled
#define LVPEN		0x3FFF	// Enabled
// In-Circuit Debugger Mode 
#define DEBUGEN		0x1FFF	// Enable ICD2 debugging
#define DEBUGDIS	0x3FFF	// Disable ICD2 debugging
#define CONFIG_ADDR2	0x2008
// Brown-out Reset Voltage 
#define BORV21		0x3EFF	// 2.1 Volts
#define BORV40		0x3FFF	// 4.0 Volts
// Flash Memory Write Protection 
#if defined(_16F882)
 #define WP0		0x3BFF	// Protect 0h-0FFh
 #define WP1		0x39FF	// Protect lower half of flash
#else
 #define WP0		0x3DFF	// Protect 0h-0FFh
 #define WP1		0x3BFF	// Protect lower half of flash
 #define WP2		0x39FF	// Protect all of flash
#endif
*/
//end configuration bits
//#endif

#elif 	defined(_16F913)	|| defined(_16F914)	||\
    	defined(_16F916)	|| defined(_16F917)
		__CONFIG(
// Oscillator 
		//EXTCLK		&					//0x3FFF	// External RC Clockout
		//EXTIO			&					//0x3FFE	// External RC No Clock
		//INTCLK		&					//0x3FFD	// Internal RC Clockout
		INTIO			&					//0x3FFC	// Internal RC No Clock
		//EC			&					//0x3FFB	// EC
		//HS				&					//0x3FFA	// HS
		//XT			& 					//0x3FF9	// XT
		//LP			&					//0x3FF8	// LP
// Watchdog Timer 
		//WDTEN			&					//0x3FFF	// On
		WDTDIS			&					//0x3FF7	// Disabled / SWDTEN control
// Power Up Timer 
		//PWRTDIS		&					//0x3FFF	// Off
		PWRTEN			&					//0x3FEF	// On
// Master Clear Enable 
		//MCLREN		&					//0x3FFF	// MCLR function is enabled
		MCLRDIS			&					//0x3FDF	// MCLR functions as IO
// Code Protect 
		UNPROTECT		&					//0x3FFF	// Code is not protected
		//CP			&					//0x3FBF	// Code is protected
		//PROTECT		&					//CP	//alternate
// Data EE Read Protect 
		UNPROTECT		&					//0x3FFF	// Do not read protect EEPROM data
		//CPD			&					//0x3F7F	// Read protect EEPROM data
// Brown Out Detect 
		BORDIS			&					//0x3CFF	// BOD and SBOREN disabled
		//SWBOREN		&					//0x3DFF	// SBOREN controls BOR function (Software control)
		//BORXSLP		&					//0x3EFF	// BOD enabled in run, disabled in sleep, SBOREN disabled
		//BOREN			&					//0x3FFF	// BOD Enabled, SBOREN Disabled
// Internal External Switch Over Mode 
		//IESOEN		&					//0x3FFF	// Enabled
		IESODIS			&					//0x3BFF	// Disabled
// Monitor Clock Fail-safe 
		//FCMEN			&					//0x3FFF	// Enabled
		FCMDIS			&					//0x37FF	// Disabled
// In-Circuit Debugger Mode 
		//DEBUGEN		&					//0x2FFF	// Enable ICD2 debugging
		DEBUGDIS		&					//0x3FFF	// Disable ICD2 debugging
		UNPROTECT);
//#endif

//16f1826, 16lf1826 for 9.65pro
#elif 	defined(_16F1826)	|| defined(_16LF1826)
		__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF);

//
// Configuratoin mask definitions
//

// Config Register: CONFIG1
//#define CONFIG1              0x8007 
// Oscillator
// LP Oscillator, Low-power crystal on RA6/OSC2/CLKO pin and RA7/OSC1/CLKI
//#define FOSC_LP              0xFFF8 
// XT Oscillator, Crystal/resonator on RA6/OSC2/CLKO pin and RA7/OSC1/CLKI
//#define FOSC_XT              0xFFF9 
// HS Oscillator, High speed crystal/resonator on RA6/OSC2/CLKO pin and RA7/OSC1/CLKI
//#define FOSC_HS              0xFFFA 
// EXTRC Oscillator, RC on RA7/OSC1/CLKIN
//#define FOSC_EXTRC           0xFFFB 
// INTOSC Oscillator, I/O function on RA7/OSC1/CLKI
//#define FOSC_INTOSC          0xFFFC 
// ECL, External Clock, Low Power Mode: CLKI on RA7/OSC1/CLKI
//#define FOSC_ECL             0xFFFD 
// ECM, External Clock, Medium Power Mode: CLKI on RA7/OSC1/CLKI
//#define FOSC_ECM             0xFFFE 
// ECH, External Clock, High Power Mode: CLKI on RA7/OSC1/CLKI
//#define FOSC_ECH             0xFFFF 
// Watchdog Timer Enable bit
// WDT enabled
//#define WDTE_ON              0xFFFF 
// WDT enabled while running and disabled in Sleep
//#define WDTE_NSLEEP          0xFFF7 
// WDT controlled by the SWDTEN bit in the WDTCON register
//#define WDTE_SWDTEN          0xFFEF 
// WDT disabled
//#define WDTE_OFF             0xFFE7 
// Power-up Timer Enable bit
// PWRT disabled
//#define PWRTE_OFF            0xFFFF 
// PWRT enabled
//#define PWRTE_ON             0xFFDF 
// MCLR Pin Function Select
// RE3/MCLR/VPP pin function is MCLR
//#define MCLRE_ON             0xFFFF 
// RE3/MCLR/VPP pin function is digital input
//#define MCLRE_OFF            0xFFBF 
// Flash Program Memory Code Protection bit
// Program memory code protection is disabled
//#define CP_OFF               0xFFFF 
// Program memory code protection is enabled
//#define CP_ON                0xFF7F 
// Data EE Read Protect
// Data memory code protection is disabled
//#define CPD_OFF              0xFFFF 
// Data memory code protection is enabled
//#define CPD_ON               0xFEFF 
// Brown-out Reset Enable bits
// Brown-out Reset enabled
//#define BOREN_ON             0xFFFF 
// Brown-out Reset enabled while running and disabled in Sleep
//#define BOREN_NSLEEP         0xFDFF 
// Brown-out Reset controlled by the SBOREN bit in the PCON register
//#define BOREN_SBODEN         0xFBFF 
// Brown-out Reset disabled
//#define BOREN_OFF            0xF9FF 
// Clock Out Enable bit
// CLKOUT function is disabled. I/O or oscillator function on RA6/CLKOUT
//#define CLKOUTEN_OFF         0xFFFF 
// CLKOUT function is enabled on RA6/CLKOUT pin
//#define CLKOUTEN_ON          0xF7FF 
// Internal-External Switch Over
// Internal/External Switchover mode is enabled
//#define IESO_ON              0xFFFF 
// Internal/External Switchover mode is disabled
//#define IESO_OFF             0xEFFF 
// Fail Clock Monitor Enable
// Fail-Safe Clock Monitor is enabled
//#define FCMEN_ON             0xFFFF 
// Fail-Safe Clock Monitor is disabled
//#define FCMEN_OFF            0xDFFF 


	__CONFIG(WRT_OFF & VCAPEN_OFF & PLLEN_OFF & STVREN_OFF & BORV_19 & DEBUG_OFF & LVP_OFF);
// Config Register: CONFIG2
//#define CONFIG2              0x8009 
// Flash memory self-write protection bits
// Write protection off
//#define WRT_OFF              0xFFFF 
// 000h to 1FFh write protected, 200h to FFFh may be modified by EECON control
//#define WRT_BOOT             0xFFFE 
// 000h to 7FFh write protected, 800h to FFFh may be modified by EECON control
//#define WRT_HALF             0xFFFD 
// 000h to FFFh write protected, no addresses may be modified by EECON control
//#define WRT_ALL              0xFFFC 
// PLL Enable bit
// 4x PLL enabled
//#define PLLEN_ON             0xFFFF 
// 4x PLL disabled
//#define PLLEN_OFF            0xFF7F 
// Stack Overflow/Underflow Reset Enable bit
// Stack Overflow or underflow will cause a Reset
//#define STVREN_ON            0xFFFF 
// Stack Overflow or underflow will not cause a Reset
//#define STVREN_OFF           0xFEFF 
// Brown-out Reset Voltage selection
// Brown-out Reset Voltage (VBOR) set to 1.9 V
//#define BORV_19              0xFFFF 
// Brown-out Reset Voltage (VBOR) set to 2.7 V
//#define BORV_27              0xFDFF 
// Debugger Mode
// Background debugger is disabled
//#define DEBUG_OFF            0xFFFF 
// Background debugger is enabled
//#define DEBUG_ON             0xF7FF 
// Low Voltage Programming Enable bit
// Low voltage programming enabled
//#define LVP_ON               0xFFFF 
// HV on MCLR/VPP must be used for programming
//#define LVP_OFF              0xEFFF 
		
//16f1827, 16lf1827 for 9.65pro
#elif 	defined(_16F1827)	|| defined(_16LF1827)
		__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF);
		
//
// Configuratoin mask definitions
//

// Config Register: CONFIG1
//#define CONFIG1              0x8007 
// Oscillator
// LP Oscillator, Low-power crystal on RA6/OSC2/CLKO pin and RA7/OSC1/CLKI
//#define FOSC_LP              0xFFF8 
// XT Oscillator, Crystal/resonator on RA6/OSC2/CLKO pin and RA7/OSC1/CLKI
//#define FOSC_XT              0xFFF9 
// HS Oscillator, High speed crystal/resonator on RA6/OSC2/CLKO pin and RA7/OSC1/CLKI
//#define FOSC_HS              0xFFFA 
// EXTRC Oscillator, RC on RA7/OSC1/CLKIN
//#define FOSC_EXTRC           0xFFFB 
// INTOSC Oscillator, I/O function on RA7/OSC1/CLKI
//#define FOSC_INTOSC          0xFFFC 
// ECL, External Clock, Low Power Mode: CLKI on RA7/OSC1/CLKI
//#define FOSC_ECL             0xFFFD 
// ECM, External Clock, Medium Power Mode: CLKI on RA7/OSC1/CLKI
//#define FOSC_ECM             0xFFFE 
// ECH, External Clock, High Power Mode: CLKI on RA7/OSC1/CLKI
//#define FOSC_ECH             0xFFFF 
// Watchdog Timer Enable bit
// WDT enabled
//#define WDTE_ON              0xFFFF 
// WDT enabled while running and disabled in Sleep
//#define WDTE_NSLEEP          0xFFF7 
// WDT controlled by the SWDTEN bit in the WDTCON register
//#define WDTE_SWDTEN          0xFFEF 
// WDT disabled
//#define WDTE_OFF             0xFFE7 
// Power-up Timer Enable bit
// PWRT disabled
//#define PWRTE_OFF            0xFFFF 
// PWRT enabled
//#define PWRTE_ON             0xFFDF 
// MCLR Pin Function Select
// RE3/MCLR/VPP pin function is MCLR
//#define MCLRE_ON             0xFFFF 
// RE3/MCLR/VPP pin function is digital input
//#define MCLRE_OFF            0xFFBF 
// Flash Program Memory Code Protection bit
// Program memory code protection is disabled
//#define CP_OFF               0xFFFF 
// Program memory code protection is enabled
//#define CP_ON                0xFF7F 
// Data EE Read Protect
// Data memory code protection is disabled
//#define CPD_OFF              0xFFFF 
// Data memory code protection is enabled
//#define CPD_ON               0xFEFF 
// Brown-out Reset Enable bits
// Brown-out Reset enabled
//#define BOREN_ON             0xFFFF 
// Brown-out Reset enabled while running and disabled in Sleep
//#define BOREN_NSLEEP         0xFDFF 
// Brown-out Reset controlled by the SBOREN bit in the PCON register
//#define BOREN_SBODEN         0xFBFF 
// Brown-out Reset disabled
//#define BOREN_OFF            0xF9FF 
// Clock Out Enable bit
// CLKOUT function is disabled. I/O or oscillator function on RA6/CLKOUT
//#define CLKOUTEN_OFF         0xFFFF 
// CLKOUT function is enabled on RA6/CLKOUT pin
//#define CLKOUTEN_ON          0xF7FF 
// Internal-External Switch Over
// Internal/External Switchover mode is enabled
//#define IESO_ON              0xFFFF 
// Internal/External Switchover mode is disabled
//#define IESO_OFF             0xEFFF 
// Fail Clock Monitor Enable
// Fail-Safe Clock Monitor is enabled
//#define FCMEN_ON             0xFFFF 
// Fail-Safe Clock Monitor is disabled
//#define FCMEN_OFF            0xDFFF 

	__CONFIG(WRT_OFF & VCAPEN_OFF & PLLEN_OFF & STVREN_OFF & BORV_19 & DEBUG_OFF & LVP_OFF);
// Config Register: CONFIG2
//#define CONFIG2              0x8009 
// Flash memory self-write protection bits
// Write protection off
//#define WRT_OFF              0xFFFF 
// 000h to 1FFh write protected, 200h to FFFh may be modified by EECON control
//#define WRT_BOOT             0xFFFE 
// 000h to 7FFh write protected, 800h to FFFh may be modified by EECON control
//#define WRT_HALF             0xFFFD 
// 000h to FFFh write protected, no addresses may be modified by EECON control
//#define WRT_ALL              0xFFFC 
// Voltage Regulator Capacitor Enable bit
// VCAP pin function is disabled
//#define VCAPEN_OFF           0xFFFF 
// VCAP functionality is enabled on VCAP pin
//#define VCAPEN_ON            0xFFEF 
// PLL Enable bit
// 4x PLL enabled
//#define PLLEN_ON             0xFFFF 
// 4x PLL disabled
//#define PLLEN_OFF            0xFEFF 
// Stack Overflow/Underflow Reset Enable bit
// Stack Overflow or underflow will cause a Reset
//#define STVREN_ON            0xFFFF 
// Stack Overflow or underflow will not cause a Reset
//#define STVREN_OFF           0xFDFF 
// Brown-out Reset Voltage selection
// Brown-out Reset Voltage (VBOR) set to 1.9 V
//#define BORV_19              0xFFFF 
// Brown-out Reset Voltage (VBOR) set to 2.7 V
//#define BORV_27              0xFBFF 
// Debugger Mode
// Background debugger is disabled
//#define DEBUG_OFF            0xFFFF 
// Background debugger is enabled
//#define DEBUG_ON             0xEFFF 
// Low Voltage Programming Enable bit
// Low voltage programming enabled
//#define LVP_ON               0xFFFF 
// HV on MCLR/VPP must be used for programming
//#define LVP_OFF              0xDFFF 

//16F1936 for 9.65pro
#elif 	defined(_16F1936) || defined(_16LF1936)
#pragma config CPD = OFF, BOREN = OFF, IESO = OFF, FOSC = HS, FCMEN = OFF, MCLRE = OFF, WDTE = OFF, CP = OFF, PWRTE = ON, CLKOUTEN = OFF
        //__CONFIG(FOSC_HS & WDTE_OFF & nPWRTE_ON & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF);
#pragma config PLLEN = OFF, WRT = OFF, STVREN = OFF, BORV = LO, LVP = OFF
#if defined(_16F1936)
#pragma config VCAPEN = OFF
#endif
        //__CONFIG(WRT_OFF & VCAPEN_OFF & PLLEN_OFF & STVREN_OFF & BORV_19 & nDEBUG_OFF & LVP_OFF);
/*
// Config Register: CONFIG1
#define CONFIG1              0x8007 
// Oscillator
// LP Oscillator, Low-power crystal on RA6/OSC2/CLKO pin and RA7/OSC1/CLKI
#define FOSC_LP              0xFFF8 
// XT Oscillator, Crystal/resonator on RA6/OSC2/CLKO pin and RA7/OSC1/CLKI
#define FOSC_XT              0xFFF9 
// HS Oscillator, High speed crystal/resonator on RA6/OSC2/CLKO pin and RA7/OSC1/CLKI
#define FOSC_HS              0xFFFA 
// EXTRC Oscillator, RC on RA7/OSC1/CLKIN
#define FOSC_EXTRC           0xFFFB 
// INTOSC Oscillator, I/O function on RA7/OSC1/CLKI
#define FOSC_INTOSC          0xFFFC 
// ECL, External Clock, Low Power Mode: CLKI on RA7/OSC1/CLKI
#define FOSC_ECL             0xFFFD 
// ECM, External Clock, Medium Power Mode: CLKI on RA7/OSC1/CLKI
#define FOSC_ECM             0xFFFE 
// ECH, External Clock, High Power Mode: CLKI on RA7/OSC1/CLKI
#define FOSC_ECH             0xFFFF 
// Watchdog Timer Enable bit
// WDT enabled
#define WDTE_ON              0xFFFF 
// WDT enabled while running and disabled in Sleep
#define WDTE_NSLEEP          0xFFF7 
// WDT controlled by the SWDTEN bit in the WDTCON register
#define WDTE_SWDTEN          0xFFEF 
// WDT disabled
#define WDTE_OFF             0xFFE7 
// Power-up Timer Enable bit
// PWRT disabled
#define nPWRTE_ON            0xFFFF 
// PWRT enabled
#define nPWRTE_OFF           0xFFDF 
// MCLR Pin Function Select
// RE3/MCLR/VPP pin function is MCLR
#define MCLRE_ON             0xFFFF 
// RE3/MCLR/VPP pin function is digital input
#define MCLRE_OFF            0xFFBF 
// Flash Program Memory Code Protection bit
// Program memory code protection is disabled
#define CP_OFF               0xFFFF 
// Program memory code protection is enabled
#define CP_ON                0xFF7F 
// Data EE Read Protect
// Data memory code protection is disabled
#define CPD_OFF              0xFFFF 
// Data memory code protection is enabled
#define CPD_ON               0xFEFF 
// Brown-out Reset Enable bits
// Brown-out Reset enabled
#define BOREN_ON             0xFFFF 
// Brown-out Reset enabled while running and disabled in Sleep
#define BOREN_NSLEEP         0xFDFF 
// Brown-out Reset controlled by the SBOREN bit in the PCON register
#define BOREN_SBODEN         0xFBFF 
// Brown-out Reset disabled
#define BOREN_OFF            0xF9FF 
// Clock Out Enable bit
// CLKOUT function is disabled. I/O or oscillator function on RA6/CLKOUT
#define CLKOUTEN_ON          0xF7FF 
// CLKOUT function is enabled on RA6/CLKOUT pin
#define CLKOUTEN_OFF         0xFFFF 
// Internal-External Switch Over
// Internal/External Switchover mode is enabled
#define IESO_ON              0xFFFF 
// Internal/External Switchover mode is disabled
#define IESO_OFF             0xEFFF 
// Fail Clock Monitor Enable
// Fail-Safe Clock Monitor is enabled
#define FCMEN_ON             0xFFFF 
// Fail-Safe Clock Monitor is disabled
#define FCMEN_OFF            0xDFFF 


// Config Register: CONFIG2
#define CONFIG2              0x8009 
// Flash memory self-write protection bits
// Write protection off
#define WRT_OFF              0xFFFF 
// 000h to 1FFh write protected, 200h to 1FFFh may be modified by EECON control
#define WRT_BOOT             0xFFFE 
// 000h to FFFh write protected, 1000h to 1FFFh may be modified by EECON control
#define WRT_HALF             0xFFFD 
// 000h to 1FFFh write protected, no addresses may be modified by EECON control
#define WRT_ALL              0xFFFC 
// Voltage Regulator Capacitor Enable bits
// VCAP functionality is enabled on RA0
#define VCAPEN_RA0           0xFFCF 
// VCAP functionality is enabled on RA5
#define VCAPEN_RA5           0xFFDF 
// VCAP functionality is enabled on RA6
#define VCAPEN_RA6           0xFFEF 
// All VCAP pin functions are disabled
#define VCAPEN_OFF           0xFFFF 
// PLL Enable bit
// 4x PLL enabled
#define PLLEN_ON             0xFFFF 
// 4x PLL disabled
#define PLLEN_OFF            0xFEFF 
// Stack Overflow/Underflow Reset Enable bit
// Stack Overflow or underflow will cause a Reset
#define STVREN_ON            0xFFFF 
// Stack Overflow or underflow will not cause a Reset
#define STVREN_OFF           0xFDFF 
// Brown-out Reset Voltage selection
// Brown-out Reset Voltage (VBOR) set to 1.9 V
#define BORV_19              0xFFFF 
// Brown-out Reset Voltage (VBOR) set to 2.7 V
#define BORV_27              0xFBFF 
// Debugger Mode
// Background debugger is disabled
#define nDEBUG_OFF           0xFFFF 
// Background debugger is enabled
#define nDEBUG_ON            0xEFFF 
// Low Voltage Programming Enable bit
// Low voltage programming enabled
#define LVP_ON               0xFFFF 
// HV on MCLR/VPP must be used for programming
#define LVP_OFF              0xDFFF 
*/
//#endif

//16f1937 for 9.65pro
#elif defined(_16F1937) || defined(_16LF1937)
	__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_ON & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF);
	__CONFIG(WRT_OFF & VCAPEN_OFF & PLLEN_OFF & STVREN_OFF & BORV_19 & DEBUG_OFF & LVP_OFF);

/*
//
// Configuratoin mask definitions
//

// Config Register: CONFIG1
#define CONFIG1              0x8007 
// Oscillator
// LP Oscillator, Low-power crystal on RA6/OSC2/CLKO pin and RA7/OSC1/CLKI
#define FOSC_LP              0xFFF8 
// XT Oscillator, Crystal/resonator on RA6/OSC2/CLKO pin and RA7/OSC1/CLKI
#define FOSC_XT              0xFFF9 
// HS Oscillator, High speed crystal/resonator on RA6/OSC2/CLKO pin and RA7/OSC1/CLKI
#define FOSC_HS              0xFFFA 
// EXTRC Oscillator, RC on RA7/OSC1/CLKIN
#define FOSC_EXTRC           0xFFFB 
// INTOSC Oscillator, I/O function on RA7/OSC1/CLKI
#define FOSC_INTOSC          0xFFFC 
// ECL, External Clock, Low Power Mode: CLKI on RA7/OSC1/CLKI
#define FOSC_ECL             0xFFFD 
// ECM, External Clock, Medium Power Mode: CLKI on RA7/OSC1/CLKI
#define FOSC_ECM             0xFFFE 
// ECH, External Clock, High Power Mode: CLKI on RA7/OSC1/CLKI
#define FOSC_ECH             0xFFFF 
// Watchdog Timer Enable bit
// WDT enabled
#define WDTE_ON              0xFFFF 
// WDT enabled while running and disabled in Sleep
#define WDTE_NSLEEP          0xFFF7 
// WDT controlled by the SWDTEN bit in the WDTCON register
#define WDTE_SWDTEN          0xFFEF 
// WDT disabled
#define WDTE_OFF             0xFFE7 
// Power-up Timer Enable bit
// PWRT disabled
#define PWRTE_OFF            0xFFFF 
// PWRT enabled
#define PWRTE_ON             0xFFDF 
// MCLR Pin Function Select
// RE3/MCLR/VPP pin function is MCLR
#define MCLRE_ON             0xFFFF 
// RE3/MCLR/VPP pin function is digital input
#define MCLRE_OFF            0xFFBF 
// Flash Program Memory Code Protection bit
// Program memory code protection is disabled
#define CP_OFF               0xFFFF 
// Program memory code protection is enabled
#define CP_ON                0xFF7F 
// Data EE Read Protect
// Data memory code protection is disabled
#define CPD_OFF              0xFFFF 
// Data memory code protection is enabled
#define CPD_ON               0xFEFF 
// Brown-out Reset Enable bits
// Brown-out Reset enabled
#define BOREN_ON             0xFFFF 
// Brown-out Reset enabled while running and disabled in Sleep
#define BOREN_NSLEEP         0xFDFF 
// Brown-out Reset controlled by the SBOREN bit in the PCON register
#define BOREN_SBODEN         0xFBFF 
// Brown-out Reset disabled
#define BOREN_OFF            0xF9FF 
// Clock Out Enable bit
// CLKOUT function is disabled. I/O or oscillator function on RA6/CLKOUT
#define CLKOUTEN_ON          0xF7FF 
// CLKOUT function is enabled on RA6/CLKOUT pin
#define CLKOUTEN_OFF         0xFFFF 
// Internal-External Switch Over
// Internal/External Switchover mode is enabled
#define IESO_ON              0xFFFF 
// Internal/External Switchover mode is disabled
#define IESO_OFF             0xEFFF 
// Fail Clock Monitor Enable
// Fail-Safe Clock Monitor is enabled
#define FCMEN_ON             0xFFFF 
// Fail-Safe Clock Monitor is disabled
#define FCMEN_OFF            0xDFFF 


// Config Register: CONFIG2
#define CONFIG2              0x8009 
// Flash memory self-write protection bits
// Write protection off
#define WRT_OFF              0xFFFF 
// 000h to 1FFh write protected, 200h to 1FFFh may be modified by EECON control
#define WRT_BOOT             0xFFFE 
// 000h to FFFh write protected, 1000h to 1FFFh may be modified by EECON control
#define WRT_HALF             0xFFFD 
// 000h to 1FFFh write protected, no addresses may be modified by EECON control
#define WRT_ALL              0xFFFC 
// Voltage Regulator Capacitor Enable bits
// VCAP functionality is enabled on RA0
#define VCAPEN_RA0           0xFFCF 
// VCAP functionality is enabled on RA5
#define VCAPEN_RA5           0xFFDF 
// VCAP functionality is enabled on RA6
#define VCAPEN_RA6           0xFFEF 
// All VCAP pin functions are disabled
#define VCAPEN_OFF           0xFFFF 
// PLL Enable bit
// 4x PLL enabled
#define PLLEN_ON             0xFFFF 
// 4x PLL disabled
#define PLLEN_OFF            0xFEFF 
// Stack Overflow/Underflow Reset Enable bit
// Stack Overflow or underflow will cause a Reset
#define STVREN_ON            0xFFFF 
// Stack Overflow or underflow will not cause a Reset
#define STVREN_OFF           0xFDFF 
// Brown-out Reset Voltage selection
// Brown-out Reset Voltage (VBOR) set to 1.9 V
#define BORV_19              0xFFFF 
// Brown-out Reset Voltage (VBOR) set to 2.7 V
#define BORV_27              0xFBFF 
// Debugger Mode
// Background debugger is disabled
#define DEBUG_OFF            0xFFFF 
// Background debugger is enabled
#define DEBUG_ON             0xEFFF 
// Low Voltage Programming Enable bit
// Low voltage programming enabled
#define LVP_ON               0xFFFF 
// HV on MCLR/VPP must be used for programming
#define LVP_OFF              0xDFFF 

*/
//#endif

#elif	defined(_18F1230) || defined(_18F1330)
		__CONFIG(1, IESODIS & FCMDIS & RCIO);
		__CONFIG(2, BORDIS & BORV20 & PWRTEN & WDTDIS & WDTPS32K);
		__CONFIG(3, PWMOUTDIS & LOWPOLHI & HIPOLHI & T1RB2 & FLTARA7 & MCLRDIS);
		__CONFIG(4, XINSTDIS & STVRDIS & BBSIZ256 & DEBUGDIS);
		__CONFIG(5, UNPROTECT);
		__CONFIG(6, WRTEN);
		__CONFIG(7, UNPROTECT);
/*
// Configuration register 1
// Internal External Switch Over Mode
 #define IESOEN		0x7FFF 	// Internal/External switch over mode enabled 
 #define IESODIS	0xFFFF 	// Internal/External switch over mode disabled 
// Fail-Safe Clock Monitor Enable
 #define FCMEN		0xBFFF 	// Fail-safe clock monitor enabled 
 #define FCMDIS		0xFFFF 	// Fail-safe clock monitor disabled 
// Oscillator
 #define EXTCLKO	0xF7FF 	// External RC, RA6=CLKOUT 
 #define RCCLKO		0xF1FF 	// Internal RC, RA6=CLKOUT 
 #define RCIO		0xF0FF 	// Internal RC, RA6=IO 
 #define EXTIO		0xFFFF 	// External RC, RA6=IO 
 #define HSPLL		0xFEFF 	// HS with PLL enabled 
 #define ECIO		0xFDFF 	// EC, RA6=IO 
 #define ECCLKO		0xFCFF 	// EC, RA6=CLKOUT 
 #define HS		0xFAFF 	// HS osc 
 #define XT		0xF9FF 	// XT osc 
 #define LP		0xF8FF 	// LP osc 

// Configuration register 2
// Brown Out Detect
 #define BOREN		0xFFFF 	// Enabled in hardware, SBOREN disabled 
 #define BOREN_XSLP	0xFFFD 	// Enabled while active,disabled in SLEEP,SBOREN disabled 
 #define SWBOREN	0xFFFB 	// Controlled with SBOREN bit 
 #define BORDIS		0xFFF9 	// Disabled in hardware, SBOREN disabled 
// Brown Out Voltage
 #define BORV20		0xFFFF 	// 2.0V 
 #define BORV27		0xFFF7 	// 2.7V 
 #define BORV42		0xFFEF 	// 4.2V 
 #define BORV45		0xFFE7 	// 4.5V 
// Power Up Timer
 #define PWRTEN		0xFFFE 	// Power-up timer enable 
 #define PWRTDIS	0xFFFF 	// Power-up timer disable 
// Watchdog Timer
 #define WDTEN		0xFFFF 	// Enabled 
 #define WDTDIS		0xFEFF 	// Disabled-Controlled by SWDTEN bit 
// Watchdog Postscaler
 #define WDTPS32K	0xFFFF 	// 1:32768 
 #define WDTPS16K	0xFDFF 	// 1:16384 
 #define WDTPS8K	0xFBFF 	// 1:8192 
 #define WDTPS4K	0xF9FF 	// 1:4096 
 #define WDTPS2K	0xF7FF 	// 1:2048 
 #define WDTPS1K	0xF5FF 	// 1:1024 
 #define WDTPS512	0xF3FF 	// 1:512 
 #define WDTPS256	0xF1FF 	// 1:256 
 #define WDTPS128	0xEFFF 	// 1:128 
 #define WDTPS64	0xEDFF 	// 1:64 
 #define WDTPS32	0xEBFF 	// 1:32 
 #define WDTPS16	0xE9FF 	// 1:16 
 #define WDTPS8		0xE7FF 	// 1:8 
 #define WDTPS4		0xE5FF 	// 1:4 
 #define WDTPS2		0xE3FF 	// 1:2 
 #define WDTPS1		0xE1FF 	// 1:1 

// Configuration register 3
// PWM output pin reset state
 #define PWMOUTDIS	0xFFFF 	// PWM outputs disabled on reset 
 #define PWMOUTEN	0xFFFD 	// PWM outputs active on reset 
// Low-side transistor polarity
 #define LOWPOLLO	0xFFFB 	// Low side transistor polarity: PWM 0,2,4 are active low 
 #define LOWPOLHI	0xFFFF 	// Low side transistor polarity: PWM 0,2,4 are active high 
// High-side transistor polarity
 #define HIPOLLO	0xFFF7 	// High side transistor polarity: PWM 1,3,5 are active low 
 #define HIPOLHI	0xFFFF 	// High side transistor polarity: PWM 1,3,5 are active high 
// T1CKI multiplex
 #define T1RA6		0xF7FF 	// Timer 1 input multiplexed on RA6 
 #define T1RB2		0xFFFF 	// Timer 1 input multiplexed on RB2 
// FLTA multiplex
 #define FLTARA5	0xFFFF 	// FLTA input is RA5 
 #define FLTARA7	0xFEFF 	// FLTA input is RA7 
// MCLR pin enable
 #define MCLREN		0xFFFF 	// MCLR pin enabled 
 #define MCLRDIS	0x7FFF 	// Disable MCLR 

// Configuration register 4
// Extended CPU Enable
 #define XINSTEN	0xFFBF 	// Enabled 
 #define XINSTDIS	0xFFFF 	// Disabled 
// Stack Overflow Reset
 #define STVREN		0xFFFF 	// Enabled 
 #define STVRDIS	0xFFFE 	// Disabled 
// Boot block size select
 #define BBSIZ1K	0xFFCF 	// Boot block is 1K words 
 #define BBSIZ512	0xFFEF 	// Boot block is 512 words 
 #define BBSIZ256	0xFFFF 	// Boot block is 256 words 
// Background debugger
 #define DEBUGEN	0xFF7F 	// Debugger enabled 
 #define DEBUGDIS	0xFFFF 	// Debugger disabled 

// Configuration register 5
// Code protection
 #define UNPROTECT	0xFFFF 	// Do not protect memory 
 #define CPA		0xFFFC 	// Protect program memory sections 
 #define CP1		0xFFFD 	// Protect program memory block 1 
 #define CP0		0xFFFE 	// Protect program memory block 0 
 #define CPD		0x7FFF 	// Protect EEPROM data 
 #define CPB		0xBFFF 	// Protect boot block 
 #define CPALL		0x3FFC 	// Protect all of the above 

// Configuration register 6
// Write protection
 #define WRTEN		0xFFFF 	// Write enabled 
 #define WPA		0xFFFC 	// Write protect program memory sections 
 #define WP1		0xFFFD 	// Write protect program memory block 1 
 #define WP0		0xFFFE 	// Write protect program memory block 0 
 #define WPD		0x7FFF 	// Write protect EEPROM data 
 #define WPB		0xBFFF 	// Write protect boot block 
 #define WPC		0xDFFF 	// Write protect configuration registers 
 #define WPALL		0x1FFC 	// Write protect all of the above 

// Configuration register 7
// Table read protection
 #define TRPA		0xFFFC 	// Table read protect program memory sections 
 #define TRP1		0xFFFD 	// Table read protect program memory block 1 
 #define TRP0		0xFFFE 	// Table read protect program memory block 0 
 #define TRPB		0xBFFF 	// Table read protect boot block 
 #define TRPALL		0xBFFC 	// Table read protect all of the above 
*/
//#endif


#elif		defined(_18F13K50) || defined(_18F14K50) || defined(_18LF13K50) || defined(_18LF14K50)
		__CONFIG(1, IESODIS & FCMDIS & PCLKEN & PLLDIS & HS);
		__CONFIG(2, BORDIS & PWRTEN & WDTDIS);
		__CONFIG(3, MCLRDIS & HFSTART);
		__CONFIG(4, XINSTDIS & DEBUGDIS & LVPDIS & STVRDIS);
		__CONFIG(5, UNPROTECT);
		__CONFIG(6, WRTEN);
		__CONFIG(7, UNPROTECT);
/*
// Configuration register 1
// Internal/External Switch Over
 #define IESOEN		0x7FFF 	// Internal/External switch over mode enabled 
 #define IESODIS	0xFFFF 	// Internal/External switch over mode disabled 
// Failsafe Clock Monitor
 #define FCMEN		0xBFFF 	// enabled 
 #define FCMDIS		0xFFFF 	// disabled 
// Primary Clock Enable
 #define PCLKEN		0xFFFF 	// enabled 
 #define PCLKDIS	0xDFFF 	// under software control 
// 4 x PLL enable
 #define PLLEN		0xEFFF 	// Oscillator multiplied by 4 
 #define PLLDIS		0xFFFF 	// PLL is under software control 
// Oscillator Selection
 #define EXTCLKO	0xF7FF 	// External RC, OSC2=CLKOUT 
 #define ECLOW		0xF5FF 	// EC (low) 
 #define ECLOWCLKO	0xF4FF 	// EC, CLKOUT function on OSC2 (low) 
 #define ECMED		0xF3FF 	// EC (medium) 
 #define ECMEDCLKO	0xF2FF 	// EC, CLKOUT function on OSC2 (medium) 
 #define RCCLKO		0xF1FF 	// Internal RC, OSC2=CLKOUT 
 #define RCIO		0xF0FF 	// Internal RC, OSC2=IO 
 #define EXTIO		0xFFFF 	// External RC, OSC2=IO 
 #define ECIO		0xFDFF 	// EC, OSC2=IO 
 #define ECCLKO		0xFCFF 	// EC, OSC2=CLKOUT 
 #define HS		0xFAFF 	// HS osc 
 #define XT		0xF9FF 	// XT osc 
 #define LP		0xF8FF 	// LP osc 

#define	USBDIV_2	0xFFDF
#define USBDIV_0	0xFFFF
#define CPUDIV_4	0xFFE7
#define CPUDIV_3	0xFFF7
#define CPUDIV_2	0xFFEF
#define CPUDIV_0	0xFFFF


// Configuration register 2
// Brown-out Voltage Level
 #define BORV30		0xFFE7 	// Brown out reset enabled, reset at 3.0V 
 #define BORV27		0xFFEF 	// Brown out reset enabled, reset at 2.7V 
 #define BORV22		0xFFF7 	// Brown out reset enabled, reset at 2.2V 
 #define BORV19		0xFFFF 	// Brown out reset enabled, reset at 1.9V 
// Brown-out Detection
 #define BOREN		0xFFFF 	// enabled in H'ware only (S'ware disabled) 
 #define BOREN_XSLP	0xFFFD 	// enabled in H'ware disabled in sleep 
 #define SWBOREN	0xFFFB 	// enabled and controlled by S'ware 
 #define BORDIS		0xFFF9 	// Brown out reset disabled 
// Power-up Timer
 #define PWRTEN		0xFFFE 	// enable 
 #define PWRTDIS	0xFFFF 	// disable 
// Watchdog Prescaler
 #define WDTPS1		0xE1FF 	// Watchdog timer enabled with prescaler(s) 
 #define WDTPS2		0xE3FF 
 #define WDTPS4		0xE5FF 
 #define WDTPS8		0xE7FF 
 #define WDTPS16	0xE9FF 
 #define WDTPS32	0xEBFF 
 #define WDTPS64	0xEDFF 
 #define WDTPS128	0xEFFF 
 #define WDTPS256	0xF1FF 
 #define WDTPS512	0xF3FF 
 #define WDTPS1K	0xF5FF 
 #define WDTPS2K	0xF7FF 
 #define WDTPS4K	0xF9FF 
 #define WDTPS8K	0xFBFF 
 #define WDTPS16K	0xFDFF 
 #define WDTPS32K	0xFFFF 
// Watchdog Timer
 #define WDTDIS		0xFEFF 	// Watchdog timer under S'ware control 
 #define WDTEN		0xFFFF 	// enabled 

// Configuration register 3
// MCLR Pin Function
 #define MCLREN		0xFFFF 	// enabled 
 #define MCLRDIS	0x7FFF 	// disabled 
// HF Oscillator Fast Startup
 #define HFSTART	0xFFFF 	// Faster startup - do not wait for HF osc to stabilize 
 #define HFSTABLE	0xF7FF 	// Wait for HF osc to stabilize before clocking CPU 

// Configuration register 4
// Extended CPU Enable
 #define XINSTEN	0xFFBF 	// Enable extended instruction set 
 #define XINSTDIS	0xFFFF 	// Disable extended instruction set (Legacy mode) 
// Background Debug
 #define DEBUGEN	0xFF7F 	// Debugger enabled 
 #define DEBUGDIS	0xFFFF	// Debugger disabled 
// Boot block size
#if defined(_18F13K50) || defined(_18LF13K50)
 #define BBSIZ512	0xFFFF 	// 512 word boot block 
 #define BBSIZ1K	0xFFF7	// 1K word boot block 
#else
 #define BBSIZ1K	0xFFFF 	// 1K word boot block 
 #define BBSIZ2K	0xFFF7 	// 2K word boot block 
#endif
// Low Voltage Programming
 #define LVPEN		0xFFFF 	// Low voltage ISP enabled 
 #define LVPDIS		0xFFFB 	// Low voltage ISP disabled 
// Stack Overflow Reset
 #define STVREN		0xFFFF 	// Stack over/underflow will cause reset 
 #define STVRDIS	0xFFFE 	// Stack over/underflow will not cause reset 

// Configuration register 5
// Code Protection
 #define UNPROTECT	0xFFFF 	// Do not protect memory 
 #define CPA		0xFFFC 	// Protect program memory sections 
 #define CP1		0xFFFD 	// Protect program memory block 1 
 #define CP0		0xFFFE 	// Protect program memory block 0 
 #define CPD		0x7FFF 	// Protect EEPROM data 
 #define CPB		0xBFFF 	// Protect boot block 
 #define CPALL		0x3FFC 	// Protect all of the above 

// Configuration register 6
// Write Protection
 #define WRTEN		0xFFFF 	// Write enabled 
 #define WPA		0xFFFC 	// Write protect program memory sections 
 #define WP1		0xFFFD 	// Write protect program memory block 1 
 #define WP0		0xFFFE 	// Write protect program memory block 0 
 #define WPD		0x7FFF 	// Write protect EEPROM data 
 #define WPB		0xBFFF 	// Write protect boot block 
 #define WPC		0xDFFF 	// Write protect configuration registers 
 #define WPALL		0x1FFC 	// Write protect all of the above 

// Configuration register 7
// Read Protection
 #define TRPA		0xFFFC 	// Table read protect program memory sections 
 #define TRP1		0xFFFD 	// Table read protect program memory block 1 
 #define TRP0		0xFFFE 	// Table read protect program memory block 0 
 #define TRPB		0xBFFF 	// Table read protect boot block 
 #define TRPALL		0xBFFC 	// Table read protect all of the above 
*/
//#endif

#elif	defined(_18F2420) || defined(_18F2520) || defined(_18F4420) || defined(_18F4520)
	__CONFIG(1, HS & FCMDIS & IESODIS);
	__CONFIG(2, PWRTEN & BORDIS & BORV20 & WDTDIS & WDTPS32K);
	__CONFIG(3, CCP2RC1 & PBDIGITAL & LPT1DIS & MCLRDIS);
	__CONFIG(4, XINSTDIS & STVRDIS & LVPDIS & DEBUGDIS);
	__CONFIG(5, UNPROTECT);
	__CONFIG(6, UNPROTECT);
	__CONFIG(7, UNPROTECT);
/*
// Configuration Bit Values
// config word 1
// Oscillator
 #define EXTCLKO	0xF7FF 	// 11XX EXT RC-CLKOUT on RA6 
 #define INTCLKO	0xF1FF 	// INT RC-CLKOUT on RA6,Port on RA7 
 #define INTIO		0xF0FF 	// INT RC-Port on RA6,Port on RA7 
 #define EXTIO		0xFFFF 	// EXT RC-Port on RA6 
 #define HSPLL		0xFEFF 	// HS-PLL enabled freq=4xFosc1 
 #define ECIO		0xFDFF 	// EC-Port on RA6 
 #define ECCLKO		0xFCFF 	// EC-CLKOUT on RA6 
 #define HS		0xFAFF 	// HS Oscillator 
 #define XT		0xF9FF 	// XT Oscillator 
 #define LP		0xF8FF 	// LP Oscillator 
// Fail-Safe Clock Monitor Enable
 #define FCMDIS		0xFFFF 	// Disabled 
 #define FCMEN		0xBFFF 	// Enabled 
// Internal External Switch Over Mode
 #define IESODIS	0xFFFF 	// Disabled 
 #define IESOEN		0x7FFF 	// Enabled 

// config word 2
// Power Up Timer
 #define PWRTDIS	0xFFFF 	// Disabled 
 #define PWRTEN		0xFFFE 	// Enabled 
// Brown Out Detect
 #define BOREN		0xFFFF 	// Enabled in hardware, SBOREN disabled 
 #define BOREN_XSLP	0xFFFD 	// Enabled while active,disabled in SLEEP,SBOREN disabled 
 #define SWBOREN	0xFFFB 	// Controlled with SBOREN bit 
 #define BORDIS		0xFFF9 	// Disabled in hardware, SBOREN disabled 
// Brown Out Voltage
 #define BORV20		0xFFFF 	// 2.0V 
 #define BORV27		0xFFF7 	// 2.7V 
 #define BORV42		0xFFEF 	// 4.2V 
 #define BORV45		0xFFE7 	// 4.5V 

// Watchdog Timer
 #define WDTEN		0xFFFF 	// Enabled 
 #define WDTDIS		0xFEFF 	// Disabled-Controlled by SWDTEN bit 
// Watchdog Postscaler
 #define WDTPS32K	0xFFFF 	// 1:32768 
 #define WDTPS16K	0xFDFF 	// 1:16384 
 #define WDTPS8K	0xFBFF 	// 1:8192 
 #define WDTPS4K	0xF9FF 	// 1:4096 
 #define WDTPS2K	0xF7FF 	// 1:2048 
 #define WDTPS1K	0xF5FF 	// 1:1024 
 #define WDTPS512	0xF3FF 	// 1:512 
 #define WDTPS256	0xF1FF 	// 1:256 
 #define WDTPS128	0xEFFF 	// 1:128 
 #define WDTPS64	0xEDFF 	// 1:64 
 #define WDTPS32	0xEBFF 	// 1:32 
 #define WDTPS16	0xE9FF 	// 1:16 
 #define WDTPS8		0xE7FF 	// 1:8 
 #define WDTPS4		0xE5FF 	// 1:4 
 #define WDTPS2		0xE3FF 	// 1:2 
 #define WDTPS1		0xE1FF 	// 1:1 

// config word 3
// CCP2 Mux
 #define CCP2RC1	0xFFFF 	// RC1 
 #define CCP2RB3	0xFEFF 	// RB3 
// PortB A/D Enable
 #define PBDIGITAL	0xFDFF 	// PORTB<4:0> configured as digital I/O on RESET 
 #define PBADDIS	PBDIGITAL 	// Deprecated
 #define PBANALOG	0xFFFF 	// PORTB<4:0> configured as analog inputs on RESET 
 #define PBADEN		PBANALOG 	// Deprecated
// Low Power Timer1 Osc enable
 #define LPT1EN		0xFBFF 	// Enabled 
 #define LPT1DIS	0xFFFF 	// Disabled 
// Master Clear Enable
 #define MCLREN		0xFFFF 	// MCLR Enabled,RE3 Disabled 
 #define MCLRDIS	0x7FFF 	// MCLR Disabled,RE3 Enabled 

// config word 4
// Extended CPU Enable
 #define XINSTEN	0xFFBF 	// Enabled 
 #define XINSTDIS	0xFFFF 	// Disabled 
// Stack Overflow Reset
 #define STVREN		0xFFFF 	// Enabled 
 #define STVRDIS	0xFFFE 	// Disabled 
// Low Voltage Program
 #define LVPEN		0xFFFF 	// Enabled 
 #define LVPDIS		0xFFFB 	// Disabled 
// Background Debug
 #define DEBUGDIS	0xFFFF 	// Disabled 
 #define DEBUGEN	0xFF7F 	// Enabled 

// config word 5
// Code Protection
 #define UNPROTECT	0xFFFF 	// Do not protect code 
 #define CP0		0xFFFE 	// Code Protect 00800-01FFF 
 #define CP1		0xFFFD 	// Code Protect 02000-03FFF 
#if defined(_18F2520) || defined(_18F4520)
 #define CP2		0xFFFB 	// Code Protect 04000-05FFF 
 #define CP3		0xFFF7 	// Code Protect 06000-07FFF 
 #define CPA		CP0 & CP1 & CP2 & CP3
#else
 #define CPA		CP0 & CP1
#endif
 #define CPD		0x7FFF 	// Data EEPROM Code Protect 
 #define CPB		0xBFFF 	// Code Protect Boot 
 #define CPALL		CPA & CPB & CPD		// Protect all of the above 

// config word 6
// Table Write Protection
// to disable protection use UNPROTECT
 #define WP0		0xFFFE 	// Table Write Protect 00800-01FFF 
 #define WP1		0xFFFD 	// Table Write Protect 02000-03FFF 
#if defined(_18F2520) || defined(_18F4520)
 #define WP2		0xFFFB 	// Table Write Protect 04000-05FFF 
 #define WP3		0xFFF7 	// Table Write Protect 06000-07FFF 
 #define WPA		WP0 & WP1 & WP2 & WP3
#else
 #define WPA		WP0 & WP1
#endif
 #define WPD		0x7FFF 	// Data EEPROM Write Protect 
 #define WPB		0xBFFF 	// Table Write Protect Boot 
 #define WPC		0xDFFF 	// Config. Write Protect 
 #define WPALL		WPA & WPB & WPD	& WPC	// Protect all of the above 

// config word 7
// Table Read Protection
// to disable protection use UNPROTECT
 #define TRP0		0xFFFE 	// Table Read Protect 00800-01FFF 
 #define TRP1		0xFFFD 	// Table Read Protect 02000-03FFF 
#if defined(_18F2520) || defined(_18F4520)
 #define TRP2		0xFFFB 	// Table Read Protect 04000-05FFF 
 #define TRP3		0xFFF7 	// Table Read Protect 06000-07FFF 
 #define TRPA		TRP0 & TRP1 & TRP2 & TRP3
#else
 #define TRPA		TRP0 & TRP1
#endif
 #define TRPB		0xBFFF 	// Table Read Protect Boot 
 #define TRPALL		TRPA & TRPB	// Protect all of the above 
//#endif
*/

//18fxxk20
#elif	defined(_18F23K20) || defined(_18F24K20) || defined(_18F25K20) || defined(_18F26K20) || \
       	defined(_18F43K20) || defined(_18F44K20) || defined(_18F45K20) || defined(_18F46K20)
//configuration bits
	__CONFIG(1, IESODIS & FCMDIS & HS);
	__CONFIG(2, BORV18 & BORDIS & PWRTEN & WDTDIS);
	__CONFIG(3, MCLRDIS & HFSTABLE & PBANALOG);
	__CONFIG(4, XINSTDIS & DEBUGDIS & LVPDIS & STVRDIS);
	__CONFIG(5, UNPROTECT);
	__CONFIG(6, WRTEN);
	__CONFIG(7, TRPB);
/*

// Configuration register 1
// Internal/External Switch Over
 #define IESOEN		0x7FFF 	// Internal/External switch over mode enabled 
 #define IESODIS	0xFFFF 	// Internal/External switch over mode disabled 
// Failsafe Clock Monitor
 #define FCMEN		0xBFFF 	// Fail-safe clock monitor enabled 
 #define FCMDIS		0xFFFF 	// Fail-safe clock monitor disabled 
// Oscillator Selection
 #define EXTCLKO	0xF7FF 	// External RC, RA6=CLKOUT 
 #define RCCLKO		0xF1FF 	// Internal RC, RA6=CLKOUT, RA7=IO 
 #define RCIO		0xF0FF 	// Internal RC, RA6=IO, RA7=IO 
 #define EXTIO		0xFFFF 	// External RC, RA6=IO 
 #define HSPLL		0xFEFF 	// HS with PLL enabled 
 #define ECIO		0xFDFF 	// EC, RA6=IO 
 #define ECCLKO		0xFCFF 	// EC, RA6=CLKOUT 
 #define HS		0xFAFF 	// HS osc 
 #define XT		0xF9FF 	// XT osc 
 #define LP		0xF8FF 	// LP osc 

// Configuration register 2
// Brown-out Voltage Level
 #define BORV30		0xFFE7 	// Brown out reset enabled, reset at 3.0V 
 #define BORV27		0xFFEF 	// Brown out reset enabled, reset at 2.7V 
 #define BORV22		0xFFF7 	// Brown out reset enabled, reset at 2.2V 
 #define BORV18		0xFFFF 	// Brown out reset enabled, reset at 1.8V 
// Brown-out Detection
 #define BOREN		0xFFFF 	// enabled in H'ware only (S'ware disabled) 
 #define BOREN_XSLP	0xFFFD 	// enabled in H'ware disabled in sleep 
 #define SWBOREN	0xFFFB 	// enabled and controlled by S'ware 
 #define BORDIS		0xFFF9 	// Brown out reset disabled 
// Power-up Timer
 #define PWRTEN		0xFFFE 	// enable 
 #define PWRTDIS	0xFFFF 	// disable 
// Watchdog Prescaler
 #define WDTPS1		0xE1FF 	// Watchdog timer enabled with prescaler(s) 
 #define WDTPS2		0xE3FF 
 #define WDTPS4		0xE5FF 
 #define WDTPS8		0xE7FF 
 #define WDTPS16	0xE9FF 
 #define WDTPS32	0xEBFF 
 #define WDTPS64	0xEDFF 
 #define WDTPS128	0xEFFF 
 #define WDTPS256	0xF1FF 
 #define WDTPS512	0xF3FF 
 #define WDTPS1K	0xF5FF 
 #define WDTPS2K	0xF7FF 
 #define WDTPS4K	0xF9FF 
 #define WDTPS8K	0xFBFF 
 #define WDTPS16K	0xFDFF 
 #define WDTPS32K	0xFFFF 
// Watchdog Timer
 #define WDTDIS		0xFEFF 	// Watchdog timer under S'ware control 
 #define WDTEN		0xFFFF 	// included only for completeness 

// Configuration register 3
// MCLR Pin Function
 #define MCLREN		0xFFFF 	// MCLR pin enabled 
 #define MCLRDIS	0x7FFF 	// Disable MCLR 
// HF Oscillator Fast Startup
 #define HFSTART	0xFFFF 	// Faster startup - do not wait for HF osc to stabilize 
 #define HFSTABLE	0xF7FF 	// Wait for HF osc to stabilize before clocking CPU 
// Low-power Timer 1 Oscillator
 #define LPT1EN		0xFBFF 	// Timer 1 in low power configuration 
 #define LPT1DIS	0xFFFF 	// Timer 1 not in low power configuration 
// Port B Analog/Digital Configuration
 #define PBANALOG	0xFFFF 	// PortB<4:0> pins are analog on reset 
 #define PBDIGITAL	0xFDFF 	// PortB<4:0> pins are digital I/O on reset 
// CCP2 Mux
 #define CCP2RC1	0xFFFF 	// CCP2 is multiplexed on RC1 
 #define CCP2RB3	0xFEFF 	// CCP2 is multiplexed on RB3 

// Configuration register 4
// Extended CPU Enable
 #define XINSTEN	0xFFBF 	// Enable extended instruction set 
 #define XINSTDIS	0xFFFF 	// Disable extended instruction set (Legacy mode) 
// Background Debug
 #define DEBUGEN	0xFF7F 	// Debugger enabled 
 #define DEBUGDIS	0xFFFF 	// Debugger disabled 
// Low Voltage Programming
 #define LVPEN		0xFFFF 	// Low voltage ISP enabled 
 #define LVPDIS		0xFFFB 	// Low voltage ISP disabled 
// Stack Overflow Reset
 #define STVREN		0xFFFF 	// Stack over/underflow will cause reset 
 #define STVRDIS	0xFFFE 	// Stack over/underflow will not cause reset 

// Configuration register 5
// Code Protection
 #define UNPROTECT	0xFFFF 	// Do not protect memory 
#if defined(_18F25K20) || defined(_18F26K20) || defined(_18F45K20) || defined(_18F46K20)
 #define CPA		0xFFF0 	// Protect program memory sections 
 #define CP3		0xFFF7 	// Protect program memory block 3 
 #define CP2		0xFFFB 	// Protect program memory block 2 
#else
 #define CPA		0xFFFC 	// Protect program memory sections 
#endif
 #define CP1		0xFFFD 	// Protect program memory block 1 
 #define CP0		0xFFFE 	// Protect program memory block 0 
 #define CPD		0x7FFF 	// Protect EEPROM data 
 #define CPB		0xBFFF 	// Protect boot block 
 #define CPALL	CPA & CPB & CPD 	// Protect all of the above 

// Configuration register 6
// Write Protection
 #define WRTEN		0xFFFF 	// Write enabled 
#if defined(_18F25K20) || defined(_18F26K20) || defined(_18F45K20) || defined(_18F46K20)
 #define WPA		0xFFF0 	// Write protect program memory sections 
 #define WP3		0xFFF7 	// Write protect program memory block 3 
 #define WP2		0xFFFB 	// Write protect program memory block 2 
#else
 #define WPA		0xFFFC 	// Write protect program memory sections 
#endif
 #define WP1		0xFFFD 	// Write protect program memory block 1 
 #define WP0		0xFFFE 	// Write protect program memory block 0 
 #define WPD		0x7FFF 	// Write protect EEPROM data 
 #define WPB		0xBFFF 	// Write protect boot block 
 #define WPC		0xDFFF 	// Write protect configuration registers 
 #define WPALL	WPA & WPB & WPC & WPD 	// Write protect all of the above 

// Configuration register 7
// Read Protection
#if defined(_18F25K20) || defined(_18F26K20) || defined(_18F45K20) || defined(_18F46K20)
 #define TRPA		0xFFF0 	// Table read protect program memory sections 
 #define TRP3		0xFFF7 	// Table read protect program memory block 3 
 #define TRP2		0xFFFB 	// Table read protect program memory block 2 
#else
 #define TRPA		0xFFFC 	// Table read protect program memory sections 
#endif
 #define TRP1		0xFFFD 	// Table read protect program memory block 1 
 #define TRP0		0xFFFE 	// Table read protect program memory block 0 
 #define TRPB		0xBFFF 	// Table read protect boot block 
 #define TRPALL	TRPA & TRPB 	// Table read protect all of the above 
*/
//end configuration bits
//#endif

//18f2550/4550
#elif	defined(_18F2455) || defined(_18F2550) || defined(_18F4455) || defined(_18F4550) || \
	defined(_18F2458) || defined(_18F2553) || defined(_18F4458) || defined(_18F4553)
//configuration bits
	__CONFIG(1, USBOSC & IESODIS & FCMDIS & HS & CPUDIV2 & PLLDIV1); 
	__CONFIG(2, VREGDIS & PWRTEN & BORDIS & BORV20 & WDTDIS & WDTPS32K); 
	__CONFIG(3, CCP2RC1 & PBDIGITAL & LPT1DIS & MCLRDIS); 
	__CONFIG(4, XINSTDIS & STVREN & LVPDIS & ICPORTDIS & DEBUGDIS); 
	__CONFIG(5, UNPROTECT); 
	__CONFIG(6, UNPROTECT); 
	__CONFIG(7, UNPROTECT); 
/*
// Configuration Bit Values
// config word 1
// USB Clock Selection
 #define USBPLL		0xFFDF 	// clk src from 96MHz PLL/2 
 #define USBOSC		0xFFFF 	// clk src from OSC1/OSC2 
// CPU Sys CLK Select
 #define CPUDIV4	0xFFE7 	// div by 4 
 #define CPUDIV3	0xFFEF 	// div by 3 
 #define CPUDIV2	0xFFF7 	// div by 2 
 #define CPUDIV1	0xFFFF 	// no divide 
 #define PLLPOSTDIV6	CPUDIV4	// 96 MHz PLL div by 6
 #define PLLPOSTDIV4	CPUDIV3	// 96 MHz PLL div by 4
 #define PLLPOSTDIV3	CPUDIV2	// 96 MHz PLL div by 3
 #define PLLPOSTDIV2	CPUDIV1	// 96 MHz PLL div by 2
// OSC Select
 #define PLLDIV12	0xFFF8 	// div by 12 {48MHz input} 
 #define PLLDIV10	0xFFF9 	// div by 10 {40MHz input} 
 #define PLLDIV6	0xFFFA 	// div by 6 {24MHz input} 
 #define PLLDIV5	0xFFFB 	// div by 5 {20MHz input} 
 #define PLLDIV4	0xFFFC 	// div by 4 {16MHz input} 
 #define PLLDIV3	0xFFFD 	// div by 3 {12MHz input} 
 #define PLLDIV2	0xFFFE 	// div by 2 {8MHz input} 
 #define PLLDIV1	0xFFFF 	// no divide {4MHz input} 

// Oscillator
 #define HSPLL		0xF4FF 	// HS: HS+PLL, USB-HS 
 #define HS		0xF6FF 	// HS: USB-HS 
 #define INT_USBHS	0xF1FF 	// INTOSC: USB-HS 
 #define INT_USBXT	0xFAFF 	// INTOSC: USB-XT 
 #define INTCLKO	0xF3FF 	// INTOSC: INTOSC+CLK0{RA6}, USB-EC 
 #define INTIO		0xF2FF 	// INTOSC: INTOSC+RA6, USB-EC 
 #define ECPLLCLKO	0xFDFF 	// EC: EC+PLL, EC+PLL+CLKO{RA6}, USB-EC 
 #define ECPLLIO	0xFCFF 	// EC: EC+PLL, EC+PLL+RA6, USB-EC 
 #define ECCLKO		0xFFFF 	// EC: EC+CLKO{RA6}, USB-EC 
 #define ECIO		0xFEFF 	// EC: EC+RA6, USB-EC 
 #define XTPLL		0xF8FF 	// XT: XT+PLL, USB-XT 
 #define XT		0xFAFF 	// XT: USB-XT 
// Fail-Safe Clock Monitor Enable
 #define FCMDIS		0xFFFF 	// Disabled 
 #define FCMEN		0xBFFF 	// Enabled 
// Internal External Switch Over Mode
 #define IESODIS	0xFFFF 	// Disabled 
 #define IESOEN		0x7FFF 	// Enabled 

// config word 2
// USB Voltage Regulator
 #define VREGEN		0xFFDF 	// Enabled 
 #define VREGDIS	0xFFFF 	// Disabled 
// Power Up Timer
 #define PWRTDIS	0xFFFF	// disable
 #define PWRTEN		0xFFFE	// enable
// Brown Out Detect
 #define BOREN		0xFFFF 	// Enabled in hardware, SBOREN disabled 
 #define BOREN_XSLP	0xFFFD 	// enabled in H'ware disabled in sleep 
 #define SWBOREN	0xFFFB 	// enabled and controlled by S'ware 
 #define BORDIS		0xFFF9 	// Disabled in hardware, SBOREN disabled 
// Brown Out Voltage
 #define BORV20		0xFFFF 	// 2.0V 
 #define BORV27		0xFFF7 	// 2.7V 
 #define BORV42		0xFFEF 	// 4.2V 
 #define BORV45		0xFFE7 	// 4.5V 

// Watchdog Timer
 #define WDTEN		0xFFFF 	// Enabled 
 #define WDTDIS		0xFEFF 	// Disabled-Controlled by SWDTEN bit 
// Watchdog Postscaler
 #define WDTPS32K	0xFFFF 	// 1:32768 
 #define WDTPS16K	0xFDFF 	// 1:16384 
 #define WDTPS8K	0xFBFF 	// 1:8192 
 #define WDTPS4K	0xF9FF 	// 1:4096 
 #define WDTPS2k	0xF7FF 	// 1:2048 
 #define WDTPS1K	0xF5FF 	// 1:1024 
 #define WDTPS512	0xF3FF 	// 1:512 
 #define WDTPS256	0xF1FF 	// 1:256 
 #define WDTPS128	0xEFFF 	// 1:128 
 #define WDTPS64	0xEDFF 	// 1:64 
 #define WDTPS32	0xEBFF 	// 1:32 
 #define WDTPS16	0xE9FF 	// 1:16 
 #define WDTPS8		0xE7FF 	// 1:8 
 #define WDTPS4		0xE5FF 	// 1:4 
 #define WDTPS2		0xE3FF 	// 1:2 
 #define WDTPS1		0xE1FF 	// 1:1 

// config word 3
// CCP2 Mux
 #define CCP2RC1	0xFFFF 	// RC1 
 #define CCP2RB3	0xFEFF 	// RB3 
// PortB A/D Enable
 #define PBDIGITAL	0xFDFF 	// PORTB<4:0> configured as digital I/O on RESET 
 #define PBADDIS	PBDIGITAL 	// Deprecated
 #define PBANALOG	0xFFFF 	// PORTB<4:0> configured as analog inputs on RESET 
 #define PBADEN		PBANALOG 	// Deprecated
// Low Power Timer1 Osc enable
 #define LPT1EN		0xFBFF 	// Timer 1 in low power configuration 
 #define LPT1DIS	0xFFFF 	// Timer 1 not in low power configuration 
// Master Clear Enable
 #define MCLREN		0xFFFF 	// MCLR Enabled,RE3 Disabled 
 #define MCLRDIS	0x7FFF 	// MCLR Disabled,RE3 Enabled 

// config word 4
// Extended CPU Enable
 #define XINSTEN	0xFFBF 	// Enable extended instruction set 
 #define XINSTDIS	0xFFFF 	// Disable extended instruction set (Legacy mode) 
// Stack Overflow Reset
 #define STVREN		0xFFFF 	// Enabled 
 #define STVRDIS	0xFFFE 	// Disabled 
// Low Voltage Program
 #define LVPEN		0xFFFF 	// Enabled 
 #define LVPDIS		0xFFFB 	// Disabled 
// Dedicated In-Circuit Port {ICD/ICSP}
 #define ICPORTEN	0xFFDF 	// Enabled 
 #define ICPORTDIS	0xFFFF 	// Disabled 
// Background Debug
 #define DEBUGDIS	0xFFFF 	// Disabled 
 #define DEBUGEN	0xFF7F 	// Enabled 

// config word 5
// Code protection
 #define UNPROTECT	0xFFFF 	// Disabled 
#if defined(_18F2550) || defined(_18F4550) || defined(_18F2553) || defined(_18F4553)
 #define CPA		0xFFF0 	// Protect all code blocks
 #define CP3		0xFFF7 	// Code Protect 06000-07FFF
#else
 #define CPA		0xFFF8 	// Protect all code blocks
#endif
 #define CP0		0xFFFE  // Code Protect 00800-01FFF
 #define CP1		0xFFFD 	// Code Protect 02000-03FFF
 #define CP2		0xFFFB 	// Code Protect 04000-05FFF 	
 #define CPD		0x7FFF 	// Data EE Read Protect
 #define CPB		0xBFFF 	// Code Protect Boot
 #define CPALL		CPA & CPB & CPD	// Protect all of the above 

// config word 6
// Table Write Protection
 #define UNPROTECT	0xFFFF 	// Disabled 
#if defined(_18F2550) || defined(_18F4550) || defined(_18F2553) || defined(_18F4553)
 #define WPA		0xFFF0 	// Protect all code blocks
 #define WP3		0xFFF8 	// Write Protect 06000-07FFF
#else
 #define WPA		0xFFF0 	// Protect all code blocks
#endif
 #define WP0		0xFFFE  // Write Protect 00800-01FFF
 #define WP1		0xFFFD 	// Write Protect 02000-03FFF
 #define WP2		0xFFFB 	// Write Protect 04000-05FFF 	
 #define WPD		0x7FFF 	// Write EE Read Protect
 #define WPB		0xBFFF 	// Write Protect Boot
 #define WPC		0xDFFF 	// Write protect Configs
 #define WPALL		WPA & WPB & WPD & WPC	// Protect all of the above 

// config word 7
// Table Read Protection
 #define UNPROTECT	0xFFFF 	// Disabled 
#if defined(_18F2550) || defined(_18F4550) || defined(_18F2553) || defined(_18F4553)
 #define TRPA		0xFFF0 	// Protect all code blocks
 #define TRP3		0xFFF7 	// Write Protect 06000-07FFF
#else
 #define TRPA		0xFFF8 	// Protect all code blocks
#endif
 #define TRP0		0xFFFE  // Write Protect 00800-01FFF
 #define TRP1		0xFFFD 	// Write Protect 02000-03FFF
 #define TRP2		0xFFFB 	// Write Protect 04000-05FFF 	
 #define TRPB		0xBFFF 	// Write Protect Boot
 #define TRPALL		TRPA & TRPB	// Protect all of the above 
*/
//end configuration bits

#elif   defined (_18F46K22)
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

#elif	defined(_18F6627) || defined(_18F6722) || defined(_18F8627) || defined(_18F8722) || \
		defined(_18F6527) || defined(_18F6622) || defined(_18F8527) || defined(_18F8622) || \
		defined(_18F6628) || defined(_18F6723) || defined(_18F8628) || defined(_18F8723)

// Configuration Bit Values
// Configuration register 1H
	__CONFIG(1, HS & FCMDIS & IESODIS);
/*
// Oscillator
 #define EXTCLKO	0xF7FF 	// 11XX EXT RC-CLKOUT on RA6 
 #define INTCLKO	0xF1FF 	// INT RC-CLKOUT on RA6,Port on RA7 
 #define INTIO		0xF0FF 	// INT RC-Port on RA6,Port on RA7 
 #define EXTIO		0xFFFF 	// EXT RC-Port on RA6 
 #define HSPLL		0xFEFF 	// HS-PLL enabled freq=4xFosc1 
 #define ECIO		0xFDFF 	// EC-Port on RA6 
 #define ECCLKO		0xFCFF 	// EC-CLKOUT on RA6 
 #define HS		0xFAFF 	// HS Oscillator 
 #define XT		0xF9FF 	// XT Oscillator 
 #define LP		0xF8FF 	// LP Oscillator 
// Fail-Safe Clock Monitor Enable
 #define FCMDIS		0xFFFF 	// Disabled 
 #define FCMEN		0xBFFF 	// Enabled 
// Internal External Switch Over Mode
 #define IESODIS	0xFFFF 	// Disabled 
 #define IESOEN		0x7FFF 	// Enabled 
*/

	__CONFIG(2, PWRTDIS & BORDIS & BORV21 & WDTDIS & WDTPS32K);
// Configuration register 2L
// Power Up Timer
/*
 #define PWRTDIS	0xFFFF 	// Disabled 
 #define PWRTEN		0xFFFE 	// Enabled 
// Brown Out Detect
 #define BOREN		0xFFFF 	// Enabled in hardware, SBOREN disabled 
 #define BOREN_XSLP	0xFFFD 	// Enabled while active,disabled in SLEEP,SBOREN disabled 
 #define SWBOREN	0xFFFB 	// Controlled with SBOREN bit 
 #define BORDIS		0xFFF9 	// Disabled in hardware, SBOREN disabled 
// Brown Out Voltage
 #define BORV21		0xFFFF 	// 2.1V 
 #define BORV28		0xFFF7 	// 2.8V 
 #define BORV43		0xFFEF 	// 4.3V 
 #define BORV46		0xFFE7 	// 4.6V 
*/

// Configuration register 2H
	//__CONFIG(2H, WDTDIS & WDTPS32K);
// Watchdog Timer
/*
 #define WDTEN		0xFFFF 	// Enabled 
 #define WDTDIS		0xFEFF 	// Disabled-Controlled by SWDTEN bit 
// Watchdog Postscaler
 #define WDTPS32K	0xFFFF 	// 1:32768 
 #define WDTPS16K	0xFDFF 	// 1:16384 
 #define WDTPS8K	0xFBFF 	// 1:8192 
 #define WDTPS4K	0xF9FF 	// 1:4096 
 #define WDTPS2K	0xF7FF 	// 1:2048 
 #define WDTPS1K	0xF5FF 	// 1:1024 
 #define WDTPS512	0xF3FF 	// 1:512 
 #define WDTPS256	0xF1FF 	// 1:256 
 #define WDTPS128	0xEFFF 	// 1:128 
 #define WDTPS64	0xEDFF 	// 1:64 
 #define WDTPS32	0xEBFF 	// 1:32 
 #define WDTPS16	0xE9FF 	// 1:16 
 #define WDTPS8		0xE7FF 	// 1:8 
 #define WDTPS4		0xE5FF 	// 1:4 
 #define WDTPS2		0xE3FF 	// 1:2 
 #define WDTPS1		0xE1FF 	// 1:1 

#if defined(_18F8527) || defined(_18F8622) || defined(_18F8627) || defined(_18F8722) ||\
	defined(_18F8628) || defined(_18F8723)
// Configuration register 3L
// External bus wait enable
 #define WAITEN		0xFF7F 	// WAIT mode active & determined by WAIT1:WAIT0 bits 
 #define WAITDIS	0xFFFF 	// WAIT mode inactive 
// External data bus width select
 #define BW16		0xFFFF 	// 16-Bit external data bus width 
 #define BW8		0xFFBF 	// 8-Bit external data bus width 
// External Address bus width select
 #define ABW20		0xFFFF 	// 20-Bit external address bus width 
 #define ABW16		0xFFEF 	// 16-Bit external address bus width 
 #define ABW12		0xFFDF 	// 12-Bit external address bus width 
 #define ABW8		0xFFCF 	// 8-Bit external address bus width 
// Processor data mode
 #define MCU		0xFFFF 	// select microcontroller mode 
 #define MPU		0xFFFE 	// select microprocessor mode 
 #define MPUBB		0xFFFD 	// select microprocessor mode with boot block mode 
 #define XMCU		0xFFFC 	// select extended microcontroller mode 
#endif
*/

	__CONFIG(3, CCP2RC1 & CCP2RB3 & LPT1DIS & MCLRDIS);
// Configuration register 3H
// CCP2 Mux
/*
 #define CCP2RC1	0xFFFF 	// RC1 
 #define CCP2RE7	0xFEFF 	// RE7 
// if in XMCU or MPUB modes
 #define CCP2RB3	0xFEFF 	// RB3 
#if defined(_18F8527) || defined(_18F8622) || defined(_18F8627) || defined(_18F8722) ||\
	defined(_18F8628) || defined(_18F8723)
// ECCP Mux
 #define ECCPRE		0xFFFF 	// ECCP multiplexed on Port E 
 #define ECCPRH		0xFDFF 	// ECCP multiplexed on Port H 
#endif
// Low Power Timer1 Osc enable
 #define LPT1EN		0xFBFF 	// Enabled 
 #define LPT1DIS	0xFFFF 	// Disabled 
// Master Clear Enable
 #define MCLREN		0xFFFF 	// MCLR Enabled,RE3 Disabled 
 #define MCLRDIS	0x7FFF 	// MCLR Disabled,RE3 Enabled 
*/

	__CONFIG(4, XINSTDIS & STVRDIS & LVPDIS & BBSIZ1K & DEBUGDIS);
// Configuration register 4L
/*
// Extended CPU Enable
 #define XINSTEN	0xFFBF 	// Enabled 
 #define XINSTDIS	0xFFFF 	// Disabled 
// Stack Overflow Reset
 #define STVREN		0xFFFF	// Enabled 
 #define STVRDIS	0xFFFE 	// Disabled 
// Low voltage program enable
 #define LVPEN		0xFFFF 	// Low voltage ISP enabled 
 #define LVPDIS		0xFFFB 	// Low voltage ISP disabled 
// Boot block size select
 #define BBSIZ4K	0xFFCF 	// Boot block is 4K 
 #define BBSIZ2K	0xFFEF 	// Boot block is 2K 
 #define BBSIZ1K	0xFFFF	// Boot block is 1K 
// Background Debug
 #define DEBUGDIS	0xFFFF 	// Disabled 
 #define DEBUGEN	0xFF7F 	// Enabled 
*/

// Configuration register 5L
	__CONFIG(5, UNPROTECT);
/*
// Code Protection
 #define UNPROTECT	0xFFFF 	// Do not protect code 
 #define CP0		0xFFFE 	// Code Protect block 0 
 #define CP1		0xFFFD 	// Code Protect block 1 
 #define CP2		0xFFFB 	// Code Protect block 2 
#if !defined(_18F6527) && !defined(_18F8527)
 #define CP3		0xFFF7 	// Code Protect block 3 
#if !defined(_18F6622) && !defined(_18F8622)
 #define CP4		0xFFEF 	// Code Protect block 4 
 #define CP5		0xFFDF 	// Code Protect block 5 
#if !defined(_18F6627) && !defined(_18F8627) &&  !defined(_18F6628) && !defined(_18F8628)
 #define CP6		0xFFBF 	// Code Protect block 6 
 #define CP7		0xFF7F 	// Code Protect block 7 
#endif
#endif
#endif
 #define CPA		0xFF00	// protect all code blocks
 #define CPD		0x7FFF 	// Code Protect data 
 #define CPB		0xBFFF 	// Code Protect boot block 
 #define CPALL		(CPA & CPD & CPB)
*/

// Configuration register 6L
	__CONFIG(6, WRTEN);
/*
// Write Protection
 #define WRTEN		0xFFFF 	// Do write protect 
 #define WP0		0xFFFE 	// Write Protect block 0 
 #define WP1		0xFFFD 	// Write Protect block 1 
 #define WP2		0xFFFB 	// Write Protect block 2 
#if !defined(_18F6527) && !defined(_18F8527)
 #define WP3		0xFFF7 	// Write Protect block 3 
#if !defined(_18F6622) && !defined(_18F8622)
 #define WP4		0xFFEF 	// Write Protect block 4 
 #define WP5		0xFFDF 	// Write Protect block 5 
#if !defined(_18F6627) && !defined(_18F8627) &&  !defined(_18F6628) && !defined(_18F8628)
 #define WP6		0xFFBF 	// Write Protect block 6 
 #define WP7		0xFF7F 	// Write Protect block 7 
#endif
#endif
#endif
 #define WPA		0xFF00	// Write Protect all code blocks
 #define WPD		0x7FFF 	// Write Protect data 
 #define WPB		0xBFFF 	// Write Protect boot block 
 #define WPC		0xDFFF 	// Write Protect config area 
 #define WPALL		(WPA & WPD & WPB & WPC)
*/

// Configuration register 7L
	__CONFIG(7, TREN);
/*
// Table read Protection
 #define TREN		0xFFFF 	// Do table read protect 
 #define TRP0		0xFFFE 	// Table read protect block 0 
 #define TRP1		0xFFFD 	// Table read protect block 1 
 #define TRP2		0xFFFB 	// Table read protect block 2 
#if !defined(_18F6527) && !defined(_18F8527)
 #define TRP3		0xFFF7 	// Table read protect block 3 
#if !defined(_18F6622) && !defined(_18F8622)
 #define TRP4		0xFFEF 	// Table read protect block 4 
 #define TRP5		0xFFDF 	// Table read protect block 5 
#if !defined(_18F6627) && !defined(_18F8627) &&  !defined(_18F6628) && !defined(_18F8628)
 #define TRP6		0xFFBF 	// Table read protect block 6 
 #define TRP7		0xFF7F 	// Table read protect block 7 
#endif
#endif
#endif
 #define TRPA		0xFF00	// Table read protect all code blocks
 #define TRPB		0xBFFF 	// Table read protect boot block 
 #define TRPALL		(TRPA & TRPB)
*/

#elif	defined(_18F2585) || defined(_18F2680) || defined(_18F4585) || defined(_18F4680)

// Configuration Bit Values

// Configuration register 1
__CONFIG(1, IESODIS & FCMDIS & HS);

/*
 #define IESOEN		0x7FFF 	// Internal/External switch over mode enabled 
 #define IESODIS	0xFFFF 	// Internal/External switch over mode disabled 
 #define FCMEN		0xBFFF 	// Fail-safe clock monitor enabled 
 #define FCMDIS		0xFFFF 	// Fail-safe clock monitor disabled 
 #define EXTCLKO	0xF7FF 	// External RC, RA6=CLKOUT 
 #define RCCLKO		0xF1FF 	// Internal RC, RA6=CLKOUT 
 #define RCIO		0xF0FF 	// Internal RC, RA6=IO 
 #define EXTIO		0xFFFF 	// External RC, RA6=IO 
 #define HSPLL		0xFEFF 	// HS with PLL enabled 
 #define ECIO		0xFDFF 	// EC, RA6=IO 
 #define ECCLKO		0xFCFF 	// EC, RA6=CLKOUT 
 #define HS		0xFAFF 	// HS osc 
 #define XT		0xF9FF 	// XT osc 
 #define LP		0xF8FF 	// LP osc 
*/

// Configuration register 2
__CONFIG(2, BORDIS & PWRTEN & WDTPS2K & WDTDIS);

/*
 #define BOREN		0xFFFF 	// enabled in H'ware only (S'ware disabled) 
 #define BOREN_XSLP	0xFFFD 	// enabled in H'ware disabled in sleep 
 #define SWBOREN	0xFFFB 	// enabled and controlled by S'ware 
 #define BORDIS		0xFFF9 	// Brown out reset disabled 
 #define BORV46		0xFFE7 	// Brown out reset enabled, reset at 4.6V 
 #define BORV43		0xFFEF 	// Brown out reset enabled, reset at 4.3V 
 #define BORV28		0xFFF7 	// Brown out reset enabled, reset at 2.8V 
 #define BORV21		0xFFFF 	// Brown out reset enabled, reset at 2.6V 
 #define PWRTEN		0xFFFE 	// Power-up timer enable 
 #define PWRTDIS	0xFFFF 	// Power-up timer disable 
 #define WDTPS1		0xE1FF 	// Watchdog timer enabled with prescaler(s) 
 #define WDTPS2		0xE3FF 
 #define WDTPS4		0xE5FF 
 #define WDTPS8		0xE7FF 
 #define WDTPS16	0xE9FF 
 #define WDTPS32	0xEBFF 
 #define WDTPS64	0xEDFF 
 #define WDTPS128	0xEFFF 
 #define WDTPS256	0xF1FF 
 #define WDTPS512	0xF3FF 
 #define WDTPS1K	0xF5FF 
 #define WDTPS2K	0xF7FF 
 #define WDTPS4K	0xF9FF 
 #define WDTPS8K	0xFBFF 
 #define WDTPS16K	0xFDFF 
 #define WDTPS32K	0xFFFF 
 #define WDTDIS		0xFEFF 	// Watchdog timer under S'ware control 
 #define WDTEN		0xFFFF 	// included only for completeness 
*/

// Configuration register 3
__CONFIG(3, MCLRDIS & LPT1DIS & PBDIGITAL);

/*
 #define MCLREN		0xFFFF 	// MCLR pin enabled 
 #define MCLRDIS	0x7FFF 	// Disable MCLR 
 #define LPT1EN		0xFBFF 	// Timer 1 in low power configuration 
 #define LPT1DIS	0xFFFF 	// Timer 1 not in low power configuration 
 #define PBDIGITAL	0xFDFF 	// PORTB<4:0> configured as digital I/O on RESET 
 #define PBANDIS	PBDIGITAL 	// Deprecated
 #define PBANALOG	0xFFFF 	// PORTB<4:0> configured as analog inputs on RESET 
 #define PBANEN		PBANALOG 	// Deprecated
*/

// Configuration register 4
__CONFIG(4, XINSTDIS & DEBUGDIS & BBSIZ1K & LVPDIS & STVRDIS);

/*
 #define XINSTEN	0xFF0F 	// Enable extended instruction set 
 #define XINSTDIS	0xFFFF 	// Disable extended instruction set (Legacy mode) 
 #define DEBUGEN	0xFF7F 	// Debugger enabled 
 #define DEBUGDIS	0xFFFF 	// Debugger disabled
 #define BBSIZ4K	0xFFCF 	// Boot block is 4K 
 #define BBSIZ2K	0xFFEF	// Boot block is 2K 
 #define BBSIZ1K	0xFFFF 	// Boot block is 1K 
 #define LVPEN		0xFFFF 	// Low voltage ISP enabled 
 #define LVPDIS		0xFFFB	// Low voltage ISP disabled 
 #define STVREN		0xFFFF 	// Stack over/underflow will cause reset 
 #define STVRDIS	0xFFFE 	// Stack over/underflow will not cause reset 
*/

// Configuration register 5
__CONFIG(5, UNPROTECT);

/* #define UNPROTECT	0xFFFF 	// Do not protect memory 
#ifndef __PIC18FX585
 #define CPALL		0x3FF0 	// Protect all memory sections
 #define CPA		0xFFF0 	// Protect program memory sections 
 #define CP3		0xFFF7 	// Protect program memory block 3 
#else
 #define CPALL		0x3FF8 	// Protect all memory sections
 #define CPA		0xFFF8 	// Protect program memory sections 
#endif
 #define CP2		0xFFFB 	// Protect program memory block 2 
 #define CP1		0xFFFD 	// Protect program memory block 1 
 #define CP0		0xFFFE 	// Protect program memory block 0 
 #define CPD		0x7FFF 	// Protect EEPROM data 
 #define CPB		0xBFFF 	// Protect boot block 
*/

// Configuration register 6
__CONFIG(6, UNPROTECT);

/* #define WRTEN		0xFFFF 	// Write enabled 
#ifndef __PIC18FX585
 #define WPALL		0x1FF0 	// Write protect all memory sections
 #define WPA		0xFFF0 	// Write protect program memory sections 
 #define WP3		0xFFF7 	// Write protect program memory block 3 
#else
 #define WPALL		0x1FF8 	// Write protect all memory sections
 #define WPA		0xFFF8 	// Write protect program memory sections 
#endif
 #define WP2		0xFFFB 	// Write protect program memory block 2 
 #define WP1		0xFFFD 	// Write protect program memory block 1 
 #define WP0		0xFFFE 	// Write protect program memory block 0 
 #define WPD		0x7FFF 	// Write protect EEPROM data 
 #define WPB		0xBFFF 	// Write protect boot block 
 #define WPC		0xDFFF 	// Write protect configuration registers 
*/

// Configuration register 7
__CONFIG(7, UNPROTECT);

/*
#ifndef __PIC18FX585
 #define TRPALL		0xBFF0 	// Table read protect all memory sections
 #define TRPA		0xFFF0 	// Table read protect program memory sections 
 #define TRP3		0xFFF7 	// Table read protect program memory block 3 
#else
 #define TRPALL		0xBFF8 	// Table read protect all memory sections
 #define TRPA		0xFFF8 	// Table read protect program memory sections 
#endif
 #define TRP2		0xFFFB 	// Table read protect program memory block 2 
 #define TRP1		0xFFFD 	// Table read protect program memory block 1 
 #define TRP0		0xFFFE 	// Table read protect program memory block 0 
 #define TRPB		0xBFFF 	// Table read protect boot block 
*/
#elif	defined(_18F6520) || defined(_18F6620) || defined(_18F6720) || \
	defined(_18F8520) || defined(_18F8620) || defined(_18F8720)

// Configuration Bit Values

// config. register 1

__CONFIG(1, OSCSDIS & HS);

/*
// oscillator system clock switch
#define OSCSEN		0xDFFF	// enable
#define OSCSDIS		0xFFFF	// disable
// oscillator configuration types
#define RCIO		0xFFFF	// RC with osc2 = RA6
#define RCRA6		RCIO	// deprecated
#define HSPLL		0xFEFF	// HS with PLL enabled
#define ECIO		0xFDFF	// EC with osc2 = RA6
#define ECRA6		ECIO	// deprecated
#define ECDB4		0xFCFF	// EC with osc2 = div by 4 clk out
#define RC		0xFBFF
#define HS		0xFAFF
#define XT		0xF9FF
#define LP		0xF8FF
*/

// config. register 2

__CONFIG(2, PWRTEN & BORDIS & WDTPS128 & WDTDIS);

/*
// power-up timer
#define PWRTEN		0xFFFE	// enable
#define PWRTDIS		0xFFFF	// disable
// brown-out reset voltage
#define BORV25		0xFFFF	// 2.5 volts
#define BORV27		0xFFFB	// 2.7 volts
#define BORV42		0xFFF7	// 4.2 volts
#define BORV45		0xFFF3	// 4.5 volts
#define BOREN		0xFFFF	// enabled
#define BORDIS		0xFFFD	// disabled
// watchdog postscale
#define WDTPS128	0xFFFF	// 1:128
#define WDTPS64		0xFDFF	// 1:64
#define WDTPS32		0xFBFF	// 1:32
#define WDTPS16		0xF9FF	// 1:16
#define WDTPS8		0xF7FF	// 1:8
#define WDTPS4		0xF5FF	// 1:4
#define WDTPS2		0xF3FF	// 1:2
#define WDTPS1		0xF1FF	// 1:1
// watchdog timer
#define WDTEN		0xFFFF	// enable
#define WDTDIS		0xFEFF	// disable
*/

// config. register 3

#ifndef __PIC18F6X20				//FOR 18F8X20 CHIPS
__CONFIG(3, /*WAITDIS & MCU & */CCP2RE7);
#else
__CONFIG(3, CCP2RE7);
#endif
/*
#ifndef __PIC18F6X20 
// external bus data wait enable
#define WAITEN		0xFF7F	// WAIT mode active & determined by WAIT1:WAIT0 bits
#define WAITDIS		0xFFFF	// WAIT mode inactive
// microcontroller/processor operation mode
#define MCU		0xFFFF	// select microcontroller mode
#define MPU		0xFFFE	// select microprocessor mode
#define MPUBB		0xFFFD	// select microprocessor mode with boot block mode
#define XMCU		0xFFFC	// select extended microcontroller mode
#endif
// CCP2 multiplex selection
#define CCP2RC1		0xFFFF	// CCP2 multiplexed to RC1
#define CCP2RE7		0xFEFF	// CCP2 multiplexed to RE7
#ifdef __PIC18F8X20
#define CCP2RB3		0xFEFF	// CCP2 multiplexed to RB3
#endif
#ifdef __PIC18FX520
// Timer1 oscillation mode bit
#define T1STD		0xFFFF	// Standard (Legacy) Timer1 operation
#define T1OSCSTD	T1STD	// Deprecated - use T1STD
#define T1LOWPOWER	0xFDFF	// Low power Timer1 operation when MCU is in SLEEP mode
#define T1OSCLP		T1LOWPOWER	// Deprecated - use T1LOWPOWER
#endif
*/

// config. register 4

__CONFIG(4, DEBUGDIS & LVPDIS & STVRDIS);

/*
// background debugger
#define DEBUGEN		0xFF7F	// enable
#define DEBUGDIS	0xFFFF	// disable
// low voltage ICSP
#define LVPEN		0xFFFF	// enable
#define LVPDIS		0xFFFB	// disable
// stack full/underflow reset enable
#define STVREN		0xFFFF	// stack full/under will cause reset
#define STVRDIS		0xFFFE	// stack full/under will not cause reset
*/

// config. register 5

__CONFIG(5, UNPROTECT);

/*
// general code protection
#ifdef __PIC18FX720
#define CPALL		0x3F00	// protect all blocks (incl. boot, data, config)
#define CPA		0xFF00	// protect 000200-01FFFFh
#define CP7		0xFF7F	// protect 01C000-01FFFFh
#define CP6		0xFFBF	// protect 018000-01BFFFh
#define CP5		0xFFDF	// protect 014000-017FFFh
#define CP4		0xFFEF	// protect 010000-013FFFh
#else
#define CPALL		0x3FF0	// protect all blocks (incl. boot, data, config)
#define CPA		0xFFF0	// protect 000200-00FFFFh (0800-7FFF in 18Fx520)
#endif
#define CP3		0xFFF7	// protect 00C000-00FFFFh (6000-7FFF in 18Fx520)
#define CP2		0xFFFB	// protect 008000-00BFFFh (4000-5FFF in 18Fx520)
#define CP1		0xFFFD	// protect 004000-007FFFh (2000-3FFF in 18Fx520)
#define CP0		0xFFFE	// protect 000200-003FFFh (0800-1FFF in 18Fx520)
#define UNPROTECT	0xFFFF	// unprotected code
// protect EEPROM data
#define CPD		0x7FFF	// protect EEPROM data
// protect boot block
#define CPB		0xBFFF	// protect boot code 00000-001FFh
*/


// config. register 6

__CONFIG(6, WPU);

/*
// write protection
#if defined(__PIC18FX720)
#define WPALL		0x1F00	// protect all blocks (incl. boot, data, config)
#define WPA		0xFF00	// protect 000200-01FFFFh
#define WP7		0xFF7F	// protect 01C000-01FFFFh
#define WP6		0xFFBF	// protect 018000-01BFFFh
#define WP5		0xFFDF	// protect 014000-017FFFh
#define WP4		0xFFEF	// protect 010000-013FFFh
#else
#define WPALL		0x1FF0	// protect all blocks (incl. boot, data, config)
#define WPA		0xFFF0	// protect 000200-00FFFFh
#endif
#define WP3		0xFFF7	// protect 00C000-00FFFFh (6000-7FFF in 18Fx520)
#define WP2		0xFFFB	// protect 008000-00BFFFh (4000-5FFF in 18Fx520)
#define WP1		0xFFFD	// protect 004000-007FFFh (2000-3FFF in 18Fx520)
#define WP0		0xFFFE	// protect 000200-003FFFh (0800-1FFF in 18Fx520)
// unprotect
#define WPU		0xFFFF	// write enabled
#define WRTEN		0xFFFF	// alternate definition
// write protection EEPROM data
#define WPD		0x7FFF	// write protect EEPROM data
// write protection boot section
#define WPB		0xBFFF	// write protect boot section
// write protection configuration registers
#define WPC		0xDFFF	// write protect config. regs
*/

// config. register 7

__CONFIG(7, TRU);

/*
//  table read protection
#if defined(__PIC18FX720)
#define TRPALL		0xBF00	// protect all blocks (incl. boot, data, config)
#define TRPA		0xFF00	// protect 000200-01FFFFh
#define TRP7		0xFF7F	// protect 01C000-01FFFFh
#define TRP6		0xFFBF	// protect 018000-01BFFFh
#define TRP5		0xFFDF	// protect 014000-017FFFh
#define TRP4		0xFFEF	// protect 010000-013FFFh
#else
#define TRPALL		0xBFF0	// protect all blocks (incl. boot, data, config)
#define TRPA		0xFFF0	// protect 000200-00FFFFh
#endif
#define TRP3		0xFFF7	// protect 00C000-00FFFFh (6000-7FFF in 18Fx520)
#define TRP2		0xFFFB	// protect 008000-00BFFFh (4000-5FFF in 18Fx520)
#define TRP1		0xFFFD	// protect 004000-007FFFh (2000-3FFF in 18Fx520)
#define TRP0		0xFFFE	// protect 000200-003FFFh (0800-1FFF in 18Fx520)
#define TRPB		0xBFFF	// Protect Boot Block
#define TRU		0xFFFF	// table read unprotected
*/

#else
//missing header files
	#warning no device header file defined!
#endif

#endif //config_h_
