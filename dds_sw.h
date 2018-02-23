#ifndef DDS_SW_H_
#define DDS_SW_H_

//hardware configuration
#define OUT_PORT		PORTB
#define OUT_DDR			TRISB
#define OUT_PINs		0xff
#define OUT(val)		OUT_PORT = (val)
//end hardware configuration

//global defines
//need to test to decide. Better to start with higher frequencies
//#define DDS_10Hz		(1936886ul)			//based on tests for 16F886 @ 4Mhz crystal
#define DDS_10Hz		(78716ul)			//based on tests for 24f @ 24Mhz crystal
#define DDS_100mHz		(DDS_1Hz / 10)			//increment to get to 0.1hz
#define DDS_1Hz			(DDS_10Hz / 10)		//increment to get to 1hz
#define DDS_100Hz		(DDS_10Hz * 10)
#define DDS_1KHz		(DDS_100Hz * 10)
#define DDS_10KHz		(DDS_1KHz * 10)

//global variables
//sine table
extern const unsigned char wf_sine0[];
extern const unsigned char wf_sine[];
extern const unsigned char wf_cosine[];
extern const unsigned char wf_square[];
extern const unsigned char wf_sawtooth[];
extern const unsigned char wf_revsawtooth[];
extern const unsigned char wf_triangle[];
extern const unsigned char wf_ECG[];
extern const unsigned char wf_random[];

//dds variables
extern unsigned long dds_accumulator;		//phase accumulator
extern unsigned char *dds_msb;				//accumulator's most significant byte. little endian
extern unsigned long dds_increment;			//dds increment
extern const unsigned char *dds_waveform;			//output waveform

//reset the dds
void dds_init(void);

//set dds increment / frequency
#define dds_freq(increment)	dds_increment = (increment)

//set output waveform
#define dds_waveform(wf_ptr)	dds_waveform = wf_ptr

//two key statement to be included in the main loop
//		dds_accumulator +=dds_increment;
//		OUT(dds_waveform[*dds_msb]);					//output the msb

#endif /*DDS_SW_H_*/
