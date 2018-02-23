#include "fastinvsqrt.h"				//we use fast inverse square rout algorithm


float FastInvSqrt(float x) {
  	float xhalf = 0.5f * x;
  	int32_t i = *(int32_t*)&x;         	// evil floating point bit level hacking
  	i = 0x5f3759df - (i >> 1);  		// what the fuck?
  	x = *(float*)&i;
  	x = x*(1.5f-(xhalf*x*x));
  	//x = x*(1.5f-(xhalf*x*x));			//optional round 2
  	return x;
}