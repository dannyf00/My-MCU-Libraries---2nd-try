/***********************************************************************************
Project:          SHTxx demo program (V2.1)
Filename:         SHTxx_Sample_Code.c

Prozessor:        mega128L
Compiler:         icc avr
Cystal:           7.3728MHz

Autor:            fxl
Copyrigth:        (c) Sensirion AG
***********************************************************************************/

//#include <iccioavr.h> //Microcontroller specific library, e.g. port definitions
#include <avr/io.h>
//#include <macros.h> //Keil library (is used for _nop()_ operation)
#include <math.h>    //Keil library
//#include <stdio.h>   //Keil library
//#include "1602LCD.h"
//#include <stdlib.h>
//#include <string.h>
#include "gpio.h"
#include "delay.h"
//#include "lcd_4bit.h"
#include "sht.h"

//----------------------------per sht application note------------------------------------
   const float SHT_C1=-4.0;           // for 12 Bit
   const float SHT_C2=+0.0405;           // for 12 Bit
   const float SHT_C3=-0.0000028;        // for 12 Bit
   const float SHT_T1=+0.01;             // for 14 Bit @ 5V
   const float SHT_T2=+0.00008;           // for 14 Bit @ 5V
//----------------------------------------------------------------------------------------
//----------------------------per the datasheet-------------------------------------------
   //const float SHT_C1=-2.0468;           // for 12 Bit
   //const float SHT_C2=+0.0367;           // for 12 Bit
   //const float SHT_C3=-1.5955e-6;        // for 12 Bit
   //const float SHT_T1=+0.01;             // for 14 Bit @ 5V
   //const float SHT_T2=+0.00008;           // for 14 Bit @ 5V
//----------------------------------------------------------------------------------------
// calculates temperature [?] and humidity [%RH]
// input :  humi [Ticks] (12 bit)
//          temp [Ticks] (14 bit)
// output:  humi [%RH]
//          temp [?]
//----------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
unsigned char sht_write(unsigned char value)
//----------------------------------------------------------------------------------
// writes a byte on the Sensibus and checks the acknowledge
{
	unsigned char i,error=0;

	for (i=0x80;i>0;i/=2)             //shift bit for masking
	{
		if (i & value) SHT_HIGH(SHT_DATA)          //masking value with i , write to SENSI-BUS
		else SHT_LOW(SHT_DATA);
		SHT_SET(SHT_SCK);                          //clk for SENSI-BUS
		SHT_CLR(SHT_SCK);
	}
	SHT_HIGH(SHT_DATA);           //release DATA-line
	SHT_SET(SHT_SCK);         //clk #9 for ack
	if (SHT_PORT_IN & SHT_DATA) error = 1;
	else   error=0;                       //check ack (DATA will be pulled down by SHT11)
	SHT_CLR(SHT_SCK);
	return error;                     //error=1 in case of no acknowledge
}

//----------------------------------------------------------------------------------
unsigned char sht_read(unsigned char ack)
//----------------------------------------------------------------------------------
// reads a byte form the Sensibus and gives an acknowledge in case of "ack=1"
{
	unsigned char i,val=0;
	SHT_HIGH(SHT_DATA);                           //release DATA-line
	for (i=0x80;i>0;i/=2)                     //shift bit for masking
	{
		SHT_SET(SHT_SCK);                          //clk for SENSI-BUS
		if (SHT_PORT_IN & SHT_DATA) val=(val | i);        //read bit
    	SHT_CLR(SHT_SCK);
	}
	if(ack) SHT_LOW(SHT_DATA)                   //in case of "ack==1" pull down DATA-Line
	else SHT_HIGH(SHT_DATA);
	SHT_SET(SHT_SCK);                            //clk #9 for ack
	SHT_CLR(SHT_SCK);
  	SHT_HIGH(SHT_DATA);                         //release DATA-line
	return val;
}

//----------------------------------------------------------------------------------
void sht_start(void)
//----------------------------------------------------------------------------------
// generates a transmission start
//       _____         ________
// DATA:      |_______|
//           ___     ___
// SCK : ___|   |___|   |______
{
	SHT_HIGH(SHT_DATA); SHT_CLR(SHT_SCK);                   //Initial state
	SHT_DELAY();
	SHT_SET(SHT_SCK);
	SHT_DELAY();
	SHT_LOW(SHT_DATA);
   	SHT_DELAY();
   	SHT_CLR(SHT_SCK);
   	SHT_DELAY();
   	SHT_SET(SHT_SCK);
   	SHT_DELAY();
   	SHT_HIGH(SHT_DATA);
   	SHT_DELAY();
   	SHT_CLR(SHT_SCK);
}

//----------------------------------------------------------------------------------
void sht_reset(void)
//----------------------------------------------------------------------------------
// communication reset: DATA-line=1 and at least 9 SCK cycles followed by transstart
//       _____________________________________________________         ________
// DATA:                                                      |_______|
//          _    _    _    _    _    _    _    _    _        ___     ___
// SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______
{
	unsigned char i;
	SHT_HIGH(SHT_DATA); SHT_CLR(SHT_SCK);                    //Initial state
	for(i=0;i<9;i++)                  //9 SCK cycles
	{
		SHT_SET(SHT_SCK);
		SHT_DELAY();
		SHT_CLR(SHT_SCK);
		SHT_DELAY();
	}
	sht_start();                  //transmission start
}

//----------------------------------------------------------------------------------
unsigned char sht_softreset(void)
//----------------------------------------------------------------------------------
// resets the sensor by a softreset
{
	unsigned char error=0;
	sht_reset();              //reset communication
	error+=sht_write(SHT_CMD_RESET);       //send RESET-command to sensor
	return error;                     //error=1 in case of no response form the sensor
}

//----------------------------------------------------------------------------------
unsigned char sht_read_statusreg(unsigned char *p_value, unsigned char *p_checksum)
//----------------------------------------------------------------------------------
// reads the status register with checksum (8-bit)
{
	unsigned char error=0;
	sht_start();                   //transmission start
	error=sht_write(SHT_CMD_STATUS_REG_R); //send command to sensor
	*p_value=sht_read(SHT_ACK);        //read status register (8-bit)
	*p_checksum=sht_read(SHT_noACK);   //read checksum (8-bit)
	return error;                     //error=1 in case of no response form the sensor
}

//----------------------------------------------------------------------------------
unsigned char sht_write_statusreg(unsigned char *p_value)
//----------------------------------------------------------------------------------
// writes the status register with checksum (8-bit)
{
	unsigned char error=0;
	sht_start();                   //transmission start
	error+=sht_write(SHT_CMD_STATUS_REG_W);//send command to sensor
	error+=sht_write(*p_value);    //send value of status register
	return error;                     //error>=1 in case of no response form the sensor
}

//----------------------------------------------------------------------------------
unsigned char sht_measure(unsigned short *p_value, unsigned char *p_checksum, unsigned char mode)
//----------------------------------------------------------------------------------
// makes a measurement (humidity/temperature) with checksum
{
	unsigned error=0;
	unsigned int i;

	sht_start();                   //transmission start
  	switch(mode){                     //send command to sensor
		case SHT_TEMP        : error+=sht_write(SHT_CMD_MEASURE_TEMP); break;
		case SHT_HUMI        : error+=sht_write(SHT_CMD_MEASURE_HUMI); break;
		default     		 : break;
	}
	for(i=0;i<200;i++) {
		delay_ms(10);				//small delays
   		if(SHT_PORT_IN & SHT_DATA) {}
 		else break;
	} //wait until sensor has finished the measurement  or timeout (~2 sec.) is reached

	if(SHT_PORT_IN & SHT_DATA) error+=1;
	if(error!=0)
	{
		while (1) {}				//hang the mcu. need better trap
	}
	*(p_value)   =sht_read(SHT_ACK)<<8;    //read the first byte (MSB)
	*(p_value)  |=sht_read(SHT_ACK);    //read the second byte (LSB)
	*p_checksum  =sht_read(SHT_noACK);  //read checksum
	return error;
}

void sht_calc(float *p_humidity ,float *p_temperature)
{
	float rh=*p_humidity;             // rh:      Humidity [Ticks] 12 Bit
	//float t=*p_temperature;           // t:       Temperature [Ticks] 14 Bit
	//float rh_lin;                     // rh_lin:  Humidity linear
	//float rh_true;                    // rh_true: Temperature compensated humidity
	//float t_C;                        // t_C   :  Temperature [?]

	//t_C=t*0.01 - 40.1;                  //calc. temperature from ticks to [?]
	*p_temperature=(*p_temperature)*0.01-40;		//*p_temperature = t_C
	//rh_lin=SHT_C3*rh*rh + SHT_C2*rh + SHT_C1;     //calc. humidity from ticks to [%RH]
	*p_humidity=SHT_C3*rh*rh + SHT_C2*rh + SHT_C1;	//*p_humidity = rh_lin
	*p_humidity=((*p_temperature)-25)*(SHT_T1+SHT_T2*rh)+(*p_humidity);   //calc. temperature compensated humidity [%RH]
	//if(rh_true>100)rh_true=100;       //cut if the value is outside of
	if ((*p_humidity)>100) *p_humidity=100;
	//if(rh_true<0.1)rh_true=0.1;       //the physical possible range
	if ((*p_humidity)<0.1) *p_humidity=0.1;

	//*p_temperature=t_C;               //return temperature [?]
	//*p_humidity=rh_true;              //return humidity[%RH ]
}

//--------------------------------------------------------------------
float sht_calc_dewpoint(float h,float t)
//--------------------------------------------------------------------
// calculates dew point
// input:   humidity [%RH], temperature [?]
// output:  dew point [?]
{
	float logEx,dew_point;
	logEx=0.66077+7.5*t/(237.3+t)+(log10(h)-2);
	dew_point = (logEx - 0.66077)*237.3/(0.66077+7.5-logEx);
	return dew_point;
}

unsigned char sht_ez(SHT_t * sht_ptr)
{
	unsigned short rh_i, t_i;
	unsigned char error, checksum;
	float rh;             				// rh:      Humidity [Ticks] 12 Bit
	float t;           					// t:       Temperature [Ticks] 14 Bit
	//float rh_lin;                     // rh_lin:  Humidity linear
	//float rh_true;                    // rh_true: Temperature compensated humidity
	//float t_C;                        // t_C   :  Temperature [C]

	//float dew_point;
	//float logEx;
	//do {								//alternative error handling regiment
		error=0;
		error+=sht_measure(&rh_i, &checksum, SHT_HUMI);
		error+=sht_measure(&t_i, &checksum, SHT_TEMP);
		if (error) sht_reset();			//reset the device is there is an error
	//} while (error);
	rh=rh_i, t=t_i;

	//calculate temperature
	//t_C=t*0.01 - 40.1;                //calc. temperature from ticks to [?]

	//calculate uhlinear
	//rh_lin=SHT_C3*rh*rh + SHT_C2*rh + SHT_C1;     //calc. humidity from ticks to [%RH]

	//add correction term
	//rh_true=(t_C-25)*(SHT_T1+SHT_T2*rh)+rh_lin;   //calc. temperature compensated humidity [%RH]

	//range limit rhtrue
	//if(rh_true>100)rh_true=100;       //cut if the value is outside of
	//if(rh_true<0.1)rh_true=0.1;       //the physical possible range
	sht_calc(&rh, &t);

	//calculate dew point
	//logEx=0.66077+7.5*t_C/(237.3+t_C)+(log10(rh_true)-2);
	//dew_point = (logEx - 0.66077)*237.3/(0.66077+7.5-logEx);
	//dew_point = sht_calc_dewpoint(rh, t);


//	*p_temperature=t_C;               	//return temperature [?]
//	*p_humidity=rh_true;              	//return humidity[%RH ]
	(*sht_ptr).Temp=t;
	(*sht_ptr).Humi=rh;
	(*sht_ptr).DewPoint=sht_calc_dewpoint(rh, t);
	return error;						//0=no error.
}
