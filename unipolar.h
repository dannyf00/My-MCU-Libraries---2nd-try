//module to driver unipolar motors

//hardware configuration
#define UNI_PORT			P2
#define UNI_DDR			P2
#define UNI_A				(1<<1)		//winding A
#define UNI_B				(1<<0)		//winding B
#define UNI_C				(1<<2)		//winding C
#define UNI_D				(1<<3)		//winding D
//motor rotation: A->B->C->D
//end hardware configuration

#define UNI_ON(pins)		IO_SET(UNI_PORT, pins)	//low to drive the winding
#define UNI_OFF(pins)		IO_CLR(UNI_PORT, pins)	//high to stop the drive

#define UNI_FORWARD		0			//go forward
#define UNI_BACKWARD		1			//going backward
#define UNI_STOP			2			//stop - don't move

//initialize the ports
void uni_init(void);

//drive the motor in one direction
void uni_drive(unsigned char direction);
