#ifndef _FS637X_H
#define _FS637X_H

#include "gpio.h"
#include "i2c_sw.h"						//we use software i2c

//hardware configuration
#define FS637x_PORT			PORTB
#define FS637x_DDR			TRISB
#define FS637x_MODE			(1<<3)		//mode pin - logic low to program and logic high to run
#define FS637x_SELC2D2		(1<<4)		//select c/d - logic low selects c1/d1, logic high selects c2/d2

#define FS637x_ADDR			0xb8		//0b1011 100
#define FS637x_EEPROM		0xa0		//0b1010 xxx - x = "don't care"
//end hardware configuration

//global defines
#define FS637xPDPOSTA_OFF	0x01		//post A off
#define FS637xPDPOSTB_OFF	0x02		//post B off
#define FS637xPDPOSTC_OFF	0x04		//post C off
#define FS637xPDPOSTD_OFF	0x08		//post D off

#define FS637xPDPLL_OFF		0x20		//pll off

//loop filter time constants
#define FS637x_LFTC7us		0x00
#define FS637x_LFTC20us		0x10

//charge pump constants
#define FS637x_CP2ua		0x00
#define FS637x_CP10ua		0x80

//Mux settings
#define FS637xMux_REF		0x00	//reference
#define FS637xMux_PLLA		0x01	//pll a
#define FS637xMux_PLLB		0x02	//pll b
#define FS637xMux_PLLC		0x03	//pll c

//reference divider, 1..255. 0x00 is the same as 256x

//3.1.3.
//Feedback Divider Programming
//For proper operation of the feedback divider, the A-counter must be programmed only for values that are less than or equal to the M-counter. Therefore, not all divider moduli below 56 are available for use. This is shown in Table 2.
//Above a modulus of 56, the feedback divider can be programmed to any value up to 2047.
//feedback divider: M8..0:A2..0
//post divider
#define FS637xNf_8x			((0x01<<3) | 0x00)
#define FS637xNf_9x			((0x01<<3) | 0x01)
#define FS637xNf_16x		((0x02<<3) | 0x00)
#define FS637xNf_17x		((0x02<<3) | 0x01)
#define FS637xNf_18x		((0x02<<3) | 0x02)
#define FS637xNf_24x		((0x03<<3) | 0x00)
#define FS637xNf_25x		((0x03<<3) | 0x01)
#define FS637xNf_26x		((0x03<<3) | 0x02)
#define FS637xNf_27x		((0x03<<3) | 0x03)
#define FS637xNf_32x		((0x04<<3) | 0x00)
#define FS637xNf_33x		((0x04<<3) | 0x01)
#define FS637xNf_34x		((0x04<<3) | 0x02)
#define FS637xNf_35x		((0x04<<3) | 0x03)
#define FS637xNf_36x		((0x04<<3) | 0x04)
#define FS637xNf_40x		((0x05<<3) | 0x00)
#define FS637xNf_41x		((0x05<<3) | 0x01)
#define FS637xNf_42x		((0x05<<3) | 0x02)
#define FS637xNf_43x		((0x05<<3) | 0x03)
#define FS637xNf_44x		((0x05<<3) | 0x04)
#define FS637xNf_45x		((0x05<<3) | 0x05)
#define FS637xNf_48x		((0x06<<3) | 0x00)
#define FS637xNf_49x		((0x06<<3) | 0x01)
#define FS637xNf_50x		((0x06<<3) | 0x02)
#define FS637xNf_51x		((0x06<<3) | 0x03)
#define FS637xNf_52x		((0x06<<3) | 0x04)
#define FS637xNf_53x		((0x06<<3) | 0x05)
#define FS637xNf_54x		((0x06<<3) | 0x06)
#define FS637xNf_56x		((0x07<<3) | 0x00)
#define FS637xNf_57x		((0x07<<3) | 0x01)
#define FS637xNf_58x		((0x07<<3) | 0x02)
#define FS637xNf_59x		((0x07<<3) | 0x03)
#define FS637xNf_60x		((0x07<<3) | 0x04)
#define FS637xNf_61x		((0x07<<3) | 0x05)
#define FS637xNf_62x		((0x07<<3) | 0x06)
#define FS637xNf_63x		((0x07<<3) | 0x07)
//then continuously up to 2047//

//form feedback divider based on A/M
#define AM2Nf(A, M)			(((A) & 0x07) | ((M) << 3))

//global variables

//read single bit from fs637x
uint8_t fs637x_read(uint8_t regaddr);

//write single byte to fs637x
uint8_t fs637x_write(uint8_t regaddr, uint8_t dat);

//reset fs637x
void fs637x_init(void);

//read feedback register
#define fs637xa_getNf()					(((fs637x_read(2) & 0x07) << 8) | fs637x_read(1))
#define fs637xb_getNf()					(((fs637x_read(5) & 0x07) << 8) | fs637x_read(4))
#define fs637xc1_getNf()				(((fs637x_read(8) & 0x07) << 8) | fs637x_read(7))
#define fs637xc2_getNf()				(((fs637x_read(11) & 0x07) << 8) | fs637x_read(10))

//write feedback register
#define fs637xa_setNf(Nf)				do {fs637x_write(1, Nf); fs637x_write(2, ((Nf) >> 8) & 0x07);} while (0)
#define fs637xb_setNf(Nf)				do {fs637x_write(4, Nf); fs637x_write(5, ((Nf) >> 8) & 0x07);} while (0)
#define fs637xc1_setNf(Nf)				do {fs637x_write(7, Nf); fs637x_write(8, ((Nf) >> 8) & 0x07);} while (0)
#define fs637xc2_setNf(Nf)				do {fs637x_write(10, Nf); fs637x_write(11, ((Nf) >> 8) & 0x07);} while (0)

//read reference divider
#define fs637xa_getNr()					(fs637x_read(0))
#define fs637xb_getNr()					(fs637x_read(3))
#define fs637xc1_getNr()				(fs637x_read(6))
#define fs637xc2_getNr()				(fs637x_read(9))

//write reference divider
#define fs637xa_setNr(Nr)				fs637x_write(0, Nr)
#define fs637xb_setNr(Nr)				fs637x_write(3, Nr)
#define fs637xc1_setNr(Nr)				fs637x_write(6, Nr)
#define fs637xc2_setNr(Nr)				fs637x_write(9, Nr)

//read post divider (Np)
#define fs637xa_getNp()					(fs637x_read(12) & 0x0f)
#define fs637xb_getNp()					(fs637x_read(12) >> 4)
#define fs637xc1_getNp()				(fs637x_read(13) & 0x0f)
#define fs637xc2_getNp()				(fs637x_read(14) & 0x0f)
#define fs637xd1_getNp()				(fs637x_read(13) >> 4)
#define fs637xd2_getNp()				(fs637x_read(14) >> 4)

//set post divider (Np)
#define fs637xa_setNp(Np)				fs637x_write(12, ((fs637x_read(12) & ~0x0f) | ((Np) & 0x0f)))
#define fs637xb_setNp(Np)				fs637x_write(12, ((fs637x_read(12) & ~0xf0) | (((Np) & 0x0f) << 4)))
#define fs637xc1_setNp(Np)				fs637x_write(13, ((fs637x_read(13) & ~0x0f) | ((Np) & 0x0f)))
#define fs637xc2_setNp(Np)				fs637x_write(14, ((fs637x_read(14) & ~0x0f) | ((Np) & 0x0f)))
#define fs637xd1_setNp(Np)				fs637x_write(13, ((fs637x_read(13) & ~0xf0) | (((Np) & 0x0f) << 4)))
#define fs637xd2_setNp(Np)				fs637x_write(14, ((fs637x_read(14) & ~0xf0) | (((Np) & 0x0f) << 4)))

//read mux
#define fs637xa_getMux()				(fs637x_read(2) >> 6)
#define fs637xb_getMux()				(fs637x_read(5) >> 6)
#define fs637xc1_getMux()				(fs637x_read(8) >> 6)
#define fs637xc2_getMux()				((fs637x_read(15) & 0x30)>> 4)
#define fs637xd1_getMux()				(fs637x_read(11) >> 6)
#define fs637xd2_getMux()				(fs637x_read(15) >> 6)

//write mux
#define fs637xa_setMux(Mux)				fs637x_write(2, ((fs637x_read(2) & ~0xc0) | (((Mux) << 6) & 0xc0)))
#define fs637xb_setMux(Mux)				fs637x_write(5, ((fs637x_read(5) & ~0xc0) | (((Mux) << 6) & 0xc0)))
#define fs637xc1_setMux(Mux)			fs637x_write(8, ((fs637x_read(8) & ~0xc0) | (((Mux) << 6) & 0xc0)))
#define fs637xc2_setMux(Mux)			fs637x_write(15, ((fs637x_read(15) & ~0x30) | (((Mux) << 4) & 0x30)))
#define fs637xd1_setMux(Mux)			fs637x_write(11, ((fs637x_read(11) & ~0xc0) | (((Mux) << 6) & 0xc0)))
#define fs637xd2_setMux(Mux)			fs637x_write(15, ((fs637x_read(15) & ~0xc0) | (((Mux) << 6) & 0xc0)))

//read power down post bits
#define fs637x_getPDPOST()				(fs637x_read(15) & 0x0f)
//set power down post bits
#define fs637x_setPDPOST(PDPOST)		(fs637x_write(15, ((fs637x_read(15) & ~0x0f) | ((PDPOST) & 0x0f))))

//read pdpll bits
#define fs637xa_getPDPLL()				(fs637x_read(2) & 0x20)
#define fs637xb_getPDPLL()				(fs637x_read(5) & 0x20)
#define fs637xc_getPDPLL()				(fs637x_read(8) & 0x20)

//set pdpll bits
#define fs637xa_setPDPLL(PDPLL)			(fs637x_write(2, ((fs637x_read(2) & ~0x20) | ((PDPLL) & 0x20)))
#define fs637xb_setPDPLL(PDPLL)			(fs637x_write(5, ((fs637x_read(5) & ~0x20) | ((PDPLL) & 0x20)))
#define fs637xc_setPDPLL(PDPLL)			(fs637x_write(8, ((fs637x_read(8) & ~0x20) | ((PDPLL) & 0x20)))

//read loop filter time constants
#define fs637xa_getLFTC()				(fs637x_read(2) & 0x10)
#define fs637xb_getLFTC()				(fs637x_read(5) & 0x10)
#define fs637xc1_getLFTC()				(fs637x_read(8) & 0x10)
#define fs637xc2_getLFTC()				(fs637x_read(11) & 0x10)

//set loop filter time constants
#define fs637xa_setLFTC(LFTC)			(fs637x_write(2, ((fs637x_read(2) & ~0x10) | ((LFTC) & 0x10))))
#define fs637xb_setLFTC(LFTC)			(fs637x_write(5, ((fs637x_read(5) & ~0x10) | ((LFTC) & 0x10))))
#define fs637xc1_setLFTC(LFTC)			(fs637x_write(8, ((fs637x_read(8) & ~0x10) | ((LFTC) & 0x10))))
#define fs637xc2_setLFTC(LFTC)			(fs637x_write(11, ((fs637x_read(11) & ~0x10) | ((LFTC) & 0x10))))

//read Charge Pump bits
#define fs637xa_getCP()					(fs637x_read(2) & 0x08)
#define fs637xb_getCP()					(fs637x_read(5) & 0x08)
#define fs637xc1_getCP()				(fs637x_read(8) & 0x08)
#define fs637xc2_getCP()				(fs637x_read(11) & 0x08)

//set Charge Pump bits
#define fs637xa_setCP(CP)				(fs637x_write(2, (fs637x_read(2) & ~0x08) | ((CP) & 0x08)))
#define fs637xb_setCP(CP)				(fs637x_write(5, (fs637x_read(5) & ~0x08) | ((CP) & 0x08)))
#define fs637xc1_setCP(CP)				(fs637x_write(8, (fs637x_read(8) & ~0x08) | ((CP) & 0x08)))
#define fs637xc2_setCP(CP)				(fs637x_write(11, (fs637x_read(11) & ~0x08) | ((CP) & 0x08)))

//turn on/off post dividers
#define fs637xa_poston()				fs637x_setPDPOST(fs637x_getPDPOST() & ~FS637xPDPOSTA_OFF)
#define fs637xa_postoff()				fs637x_setPDPOST(fs637x_getPDPOST() |  FS637xPDPOSTA_OFF)
#define fs637xb_poston()				fs637x_setPDPOST(fs637x_getPDPOST() & ~FS637xPDPOSTB_OFF)
#define fs637xb_postoff()				fs637x_setPDPOST(fs637x_getPDPOST() |  FS637xPDPOSTB_OFF)
#define fs637xc_poston()				fs637x_setPDPOST(fs637x_getPDPOST() & ~FS637xPDPOSTC_OFF)
#define fs637xc_postoff()				fs637x_setPDPOST(fs637x_getPDPOST() |  FS637xPDPOSTC_OFF)
#define fs637xd_poston()				fs637x_setPDPOST(fs637x_getPDPOST() & ~FS637xPDPOSTD_OFF)
#define fs637xd_postoff()				fs637x_setPDPOST(fs637x_getPDPOST() |  FS637xPDPOSTD_OFF)

//turn of / off pll 
#define fs637xa_pllon()					fs637xa_setPDPLL(fs637xa_getPDPLL() & ~FS637xPDPLL_OFF)
#define fs637xa_plloff()				fs637xa_setPDPLL(fs637xa_getPDPLL() |  FS637xPDPLL_OFF)
#define fs637xb_pllon()					fs637xb_setPDPLL(fs637xb_getPDPLL() & ~FS637xPDPLL_OFF)
#define fs637xb_plloff()				fs637xb_setPDPLL(fs637xb_getPDPLL() |  FS637xPDPLL_OFF)
#define fs637xc_pllon()					fs637xc_setPDPLL(fs637xc_getPDPLL() & ~FS637xPDPLL_OFF)
#define fs637xc_plloff()				fs637xc_setPDPLL(fs637xc_getPDPLL() |  FS637xPDPLL_OFF)

//change loop filter time constant
#define fs637xa_lftc7us()				fs637xa_setLFTC(FS637x_LFTC7us)
#define fs637xa_lftc20us()				fs637xa_setLFTC(FS637x_LFTC20us)
#define fs637xb_lftc7us()				fs637xb_setLFTC(FS637x_LFTC7us)
#define fs637xb_lftc20us()				fs637xb_setLFTC(FS637x_LFTC20us)
#define fs637xc1_lftc7us()				fs637xc1_setLFTC(FS637x_LFTC7us)
#define fs637xc1_lftc20us()				fs637xc1_setLFTC(FS637x_LFTC20us)
#define fs637xc2_lftc7us()				fs637xc2_setLFTC(FS637x_LFTC7us)
#define fs637xc2_lftc20us()				fs637xc2_setLFTC(FS637x_LFTC20us)

//change charge pump current settings
#define fs637xa_cp2ua()					fs637xa_setCP(FS637x_CP2ua)
#define fs637xa_cp10ua()				fs637xa_setCP(FS637x_CP10ua)
#define fs637xb_cp2ua()					fs637xb_setCP(FS637x_CP2ua)
#define fs637xb_cp10ua()				fs637xb_setCP(FS637x_CP10ua)
#define fs637xc1_cp2ua()				fs637xc1_setCP(FS637x_CP2ua)
#define fs637xc1_cp10ua()				fs637xc1_setCP(FS637x_CP10ua)
#define fs637xc2_cp2ua()				fs637xc2_setCP(FS637x_CP2ua)
#define fs637xc2_cp10ua()				fs637xc2_setCP(FS637x_CP10ua)

//set the mux
#define fs637xa_MuxREF()				fs637xa_setMux(FS637xMux_REF)
#define fs637xa_MuxPLLA()				fs637xa_setMux(FS637xMux_PLLA)
#define fs637xa_MuxPLLB()				fs637xa_setMux(FS637xMux_PLLB)
#define fs637xa_MuxPLLC()				fs637xa_setMux(FS637xMux_PLLC)
#define fs637xb_MuxREF()				fs637xb_setMux(FS637xMux_REF)
#define fs637xb_MuxPLLA()				fs637xb_setMux(FS637xMux_PLLA)
#define fs637xb_MuxPLLB()				fs637xb_setMux(FS637xMux_PLLB)
#define fs637xb_MuxPLLC()				fs637xb_setMux(FS637xMux_PLLC)
#define fs637xc1_MuxREF()				fs637xc1_setMux(FS637xMux_REF)
#define fs637xc1_MuxPLLA()				fs637xc1_setMux(FS637xMux_PLLA)
#define fs637xc1_MuxPLLB()				fs637xc1_setMux(FS637xMux_PLLB)
#define fs637xc1_MuxPLLC()				fs637xc1_setMux(FS637xMux_PLLC)
#define fs637xc2_MuxREF()				fs637xc2_setMux(FS637xMux_REF)
#define fs637xc2_MuxPLLA()				fs637xc2_setMux(FS637xMux_PLLA)
#define fs637xc2_MuxPLLB()				fs637xc2_setMux(FS637xMux_PLLB)
#define fs637xc2_MuxPLLC()				fs637xc2_setMux(FS637xMux_PLLC)
#define fs637xd1_MuxREF()				fs637xd1_setMux(FS637xMux_REF)
#define fs637xd1_MuxPLLA()				fs637xd1_setMux(FS637xMux_PLLA)
#define fs637xd1_MuxPLLB()				fs637xd1_setMux(FS637xMux_PLLB)
#define fs637xd1_MuxPLLC()				fs637xd1_setMux(FS637xMux_PLLC)
#define fs637xd2_MuxREF()				fs637xd2_setMux(FS637xMux_REF)
#define fs637xd2_MuxPLLA()				fs637xd2_setMux(FS637xMux_PLLA)
#define fs637xd2_MuxPLLB()				fs637xd2_setMux(FS637xMux_PLLB)
#define fs637xd2_MuxPLLC()				fs637xd2_setMux(FS637xMux_PLLC)

#endif
