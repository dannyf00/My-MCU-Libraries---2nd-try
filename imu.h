#ifndef IMU_H_INCLUDED
#define IMU_H_INCLUDED

#include <math.h>

//hardware configuration
#define IMU_FLOAT					float					//data type for imu units
#define IMU_FSAMPLING				20						//IMU sampling frequency, in Hz
//end hardware configuration

//global defines
#if defined(M_PI)
#define IMU_PI()					M_PI					//3.1415926				//pi
#else
#define IMU_PI()					3.1415926f
#endif
#define IMU_R2D(r)					((r) * 180.0f/IMU_PI())	//radiant to degrees
#define IMU_D2R(d)					((d) * IMU_PI() / 180.0f)	//degrees to radiant

//define IMU struct
typedef struct {
    IMU_FLOAT gx, gy, gz;				//gyro readings
    IMU_FLOAT ax, ay, az;				//accelerometer readings
    IMU_FLOAT q0, q1, q2, q3;			//quaternions
    IMU_FLOAT beta;						//beta
    IMU_FLOAT pitch, roll, yaw;			//euler angles, in radiant readings
} IMU_T;

//initialize IMU
IMU_T *imu_init(IMU_T *imu, float beta0, float gx0, float gy0, float gz0, float ax0, float ay0, float az0);

//calculate euler angles
//quat(x, y, z, w)
//http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
IMU_T *imu_euler(IMU_T *imu);

//---------------------------------------------------------------------------------------------------
// IMU algorithm update

void imu_update(IMU_T *imu);			//float gx, float gy, float gz, float ax, float ay, float az) {

#endif // IMU_H_INCLUDED
