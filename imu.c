#include "imu.h"					//6dof imu based on madgwick's work

//hardware configuration
//#define IMU_PI()					M_PI					//3.1415926				//pi
//end hardware configuration

//global defines

//global variables

//initialize IMU
IMU_T *imu_init(IMU_T *imu, float beta0, float gx0, float gy0, float gz0, float ax0, float ay0, float az0) {
    imu->beta=beta0;
    imu->gx=gx0;
    imu->gy=gy0;
    imu->gz=gz0;
    imu->ax=ax0;
    imu->ay=ay0;
    imu->az=az0;
    imu->beta=beta0;
    imu->q0=1.0f;
    imu->q1=0.0f;
    imu->q2=0.0f;
    imu->q3=0.0f;
    return imu;
}

//---------------------------------------------------------------------------------------------------
// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root

float invSqrt(float x) {
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)&y;
    i = 0x5f3759df - (i>>1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}

//calculate euler angles
//quat(x, y, z, w)
//http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
IMU_T *imu_euler(IMU_T *imu) {
    imu->roll=atan2(2.0f*(imu->q0*imu->q1 + imu->q2*imu->q3), 1.0f - 2.0f*(imu->q1*imu->q1 + imu->q2*imu->q2));
    imu->pitch=asin(2.0f*(imu->q0*imu->q2 - imu->q1*imu->q3));
    imu->yaw=atan2(2.0f*(imu->q0*imu->q3 + imu->q1*imu->q2), 1.0f - 2.0f*(imu->q2*imu->q2 + imu->q3*imu->q3));
    return imu;
}

//---------------------------------------------------------------------------------------------------
// IMU algorithm update
void imu_update(IMU_T *imu) {			//float gx, float gy, float gz, float ax, float ay, float az) {
    IMU_FLOAT recipNorm;
    IMU_FLOAT s0, s1, s2, s3;
    IMU_FLOAT qDot1, qDot2, qDot3, qDot4;
    IMU_FLOAT _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

    // Rate of change of quaternion from gyroscope
    qDot1 = 0.5f * (-imu->q1 * imu->gx - imu->q2 * imu->gy - imu->q3 * imu->gz);
    qDot2 = 0.5f * (imu->q0 * imu->gx + imu->q2 * imu->gz - imu->q3 * imu->gy);
    qDot3 = 0.5f * (imu->q0 * imu->gy - imu->q1 * imu->gz + imu->q3 * imu->gx);
    qDot4 = 0.5f * (imu->q0 * imu->gz + imu->q1 * imu->gy - imu->q2 * imu->gx);

    // Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
    if(!((imu->ax == 0.0f) && (imu->ay == 0.0f) && (imu->az == 0.0f))) {

        // Normalise accelerometer measurement
        recipNorm = invSqrt(imu->ax * imu->ax + imu->ay * imu->ay + imu->az * imu->az);
        imu->ax *= recipNorm;
        imu->ay *= recipNorm;
        imu->az *= recipNorm;

        // Auxiliary variables to avoid repeated arithmetic
        _2q0 = imu->q0 + imu->q0;					//2.0f * q0;
        _2q1 = imu->q1 + imu->q1;					//2.0f * q1;
        _2q2 = imu->q2 + imu->q2;					//2.0f * q2;
        _2q3 = imu->q3 + imu->q3;					//2.0f * q3;
        _4q0 = _2q0 + _2q0;							//4.0f * q0;
        _4q1 = _2q1 + _2q1;							//4.0f * q1;
        _4q2 = _2q2 + _2q2;							//4.0f * q2;
        _8q1 = _4q1 + _4q1;							//8.0f * q1;
        _8q2 = _4q2 + _4q2;							//8.0f * q2;
        q0q0 = imu->q0 * imu->q0;
        q1q1 = imu->q1 * imu->q1;
        q2q2 = imu->q2 * imu->q2;
        q3q3 = imu->q3 * imu->q3;

        // Gradient decent algorithm corrective step
        s0 = _4q0 * q2q2 + _2q2 * imu->ax + _4q0 * q1q1 - _2q1 * imu->ay;
        s1 = _4q1 * q3q3 - _2q3 * imu->ax + 4.0f * q0q0 * imu->q1 - _2q0 * imu->ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * imu->az;
        s2 = 4.0f * q0q0 * imu->q2 + _2q0 * imu->ax + _4q2 * q3q3 - _2q3 * imu->ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * imu->az;
        s3 = 4.0f * q1q1 * imu->q3 - _2q1 * imu->ax + 4.0f * q2q2 * imu->q3 - _2q2 * imu->ay;
        recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude
        s0 *= recipNorm;
        s1 *= recipNorm;
        s2 *= recipNorm;
        s3 *= recipNorm;

        // Apply feedback step
        qDot1 -= imu->beta * s0;
        qDot2 -= imu->beta * s1;
        qDot3 -= imu->beta * s2;
        qDot4 -= imu->beta * s3;
    }

    // Integrate rate of change of quaternion to yield quaternion
    imu->q0 += qDot1 * (1.0f / IMU_FSAMPLING);			//(1.0f / sampleFreq);
    imu->q1 += qDot2 * (1.0f / IMU_FSAMPLING);			//(1.0f / sampleFreq);
    imu->q2 += qDot3 * (1.0f / IMU_FSAMPLING);			//(1.0f / sampleFreq);
    imu->q3 += qDot4 * (1.0f / IMU_FSAMPLING);			//(1.0f / sampleFreq);

    // Normalise quaternion
    recipNorm = invSqrt(imu->q0 * imu->q0 + imu->q1 * imu->q1 + imu->q2 * imu->q2 + imu->q3 * imu->q3);
    imu->q0 *= recipNorm;
    imu->q1 *= recipNorm;
    imu->q2 *= recipNorm;
    imu->q3 *= recipNorm;

    //printf("q0=%10.2f, q1=%10.2f, q2=%10.2f, q3=%10.2f\n\r", q0, q1, q2, q3);
}
