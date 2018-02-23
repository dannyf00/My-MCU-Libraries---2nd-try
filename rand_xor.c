#include "rand_xor.h"					//we use rand_xorshift generator

//hardware configuration
//end hardware configuration

//global defines

//global variables

//random number generator - xorshift
uint32_t rand_xor(void) {
	//xor random
	static uint32_t _randxor_seed = 7;  // 100% random seed value
  	_randxor_seed ^= _randxor_seed << 13;
 	_randxor_seed ^= _randxor_seed >> 17;
  	_randxor_seed ^= _randxor_seed << 5;
  	return _randxor_seed;
}

