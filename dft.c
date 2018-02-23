//
// dft2.c - Basic, but slightly more efficient DFT
// Written by Ted Burke
// Last updated 10-12-2013
//
// To compile:
//    gcc dft2.c -o dft2.exe
//
// To run:
//    dft2.exe
//

#include "dft.h"						//we use dft -64 data points

// N is assumed to be greater than 4 and a power of 2
//#define _DFT64_N		64				//cannot be changed
//#define _DFT_PIx2 	(3.1415926*2)	//6.2832		//PIx2

//twiddle factors (16-point)
const float _DFT16_TF[] = {
	 1.00000, 0.92388, 0.70711, 0.38268, 0.00000,-0.38268,-0.70711,-0.92388,
	-1.00000,-0.92388,-0.70711,-0.38268, 0.00000, 0.38268, 0.70711, 0.92388,
};

//twiddle factors (32-point)
const float _DFT32_TF[] = {
	 1.00000, 0.98079, 0.92388, 0.83147, 0.70711, 0.55557, 0.38268, 0.19509,
	 0.00000,-0.19509,-0.38268,-0.55557,-0.70711,-0.83147,-0.92388,-0.98079,
	-1.00000,-0.98079,-0.92388,-0.83147,-0.70711,-0.55557,-0.38268,-0.19509,
	 0.00000, 0.19509, 0.38268, 0.55557, 0.70711, 0.83147, 0.92388, 0.98079,
};

// Twiddle factors (64th roots of unity)
const float _DFT64_TF[] = {
     1.00000, 0.99518, 0.98079, 0.95694, 0.92388, 0.88192, 0.83147, 0.77301,
     0.70711, 0.63439, 0.55557, 0.47139, 0.38268, 0.29028, 0.19509, 0.09801,
    -0.00000,-0.09802,-0.19509,-0.29029,-0.38269,-0.47140,-0.55557,-0.63440,
    -0.70711,-0.77301,-0.83147,-0.88192,-0.92388,-0.95694,-0.98079,-0.99519,
    -1.00000,-0.99518,-0.98078,-0.95694,-0.92388,-0.88192,-0.83146,-0.77300,
    -0.70710,-0.63439,-0.55556,-0.47139,-0.38267,-0.29027,-0.19508,-0.09801,
     0.00001, 0.09803, 0.19510, 0.29030, 0.38269, 0.47141, 0.55558, 0.63440,
     0.70712, 0.77302, 0.83148, 0.88193, 0.92388, 0.95694, 0.98079, 0.99519
};

//64 point dft-floating point
//x[64]: real input data
//Xre[64]: real output real elements
//Xim[64]: real output imaginary elements
//P[64]: real output power elements
void dft64(float *x, float *Xre, float *Xim/*, float *P*/) {
    // Calculate DFT and power spectrum up to Nyquist frequency
    int n, k;
    int to_sin = 3*_DFT64_N/4; // index offset for sin
    int a, b;
    for (k=0 ; k<=_DFT64_N/2 ; ++k)
    {
        Xre[k] = 0; Xim[k] = 0;
        a = 0; b = to_sin;
        for (n=0 ; n<_DFT64_N ; ++n)
        {
            Xre[k] += x[n] * _DFT64_TF[/*a%_DFT64_N*/a & (_DFT64_N-1)];
            Xim[k] -= x[n] * _DFT64_TF[/*b%_DFT64_N*/b & (_DFT64_N-1)];
            a += k; b += k;
        }
        //P[k] = Xre[k]*Xre[k] + Xim[k]*Xim[k];
    }

}

float dft64_power(float *x, float *Xre, float *Xim, float *P) {
    // Calculate DFT and power spectrum up to Nyquist frequency
    float tmp=0;
    int n, k;
    int to_sin = 3*_DFT64_N/4; // index offset for sin
    int a, b;
    for (k=0 ; k<=_DFT64_N/2 ; ++k)
    {
        Xre[k] = 0; Xim[k] = 0;
        a = 0; b = to_sin;
        for (n=0 ; n<_DFT64_N ; ++n)
        {
            Xre[k] += x[n] * _DFT64_TF[/*a%_DFT64_N*/a & (_DFT64_N-1)];
            Xim[k] -= x[n] * _DFT64_TF[/*b%_DFT64_N*/b & (_DFT64_N-1)];
            a += k; b += k;
        }
        P[k] = Xre[k]*Xre[k] + Xim[k]*Xim[k];
        tmp += P[k];
    }
    return tmp;
}

//32 point dft-floating point
//x[64]: real input data
//Xre[64]: real output real elements
//Xim[64]: real output imaginary elements
//P[64]: real output power elements
void dft32(float *x, float *Xre, float *Xim/*, float *P*/) {
    // Calculate DFT and power spectrum up to Nyquist frequency
    int n, k;
    int to_sin = 3*_DFT32_N/4; // index offset for sin
    int a, b;
    for (k=0 ; k<=_DFT32_N/2 ; ++k)
    {
        Xre[k] = 0; Xim[k] = 0;
        a = 0; b = to_sin;
        for (n=0 ; n<_DFT32_N ; ++n)
        {
            Xre[k] += x[n] * _DFT32_TF[/*a%_DFT64_N*/a & (_DFT32_N-1)];
            Xim[k] -= x[n] * _DFT32_TF[/*b%_DFT64_N*/b & (_DFT32_N-1)];
            a += k; b += k;
        }
        //P[k] = Xre[k]*Xre[k] + Xim[k]*Xim[k];
    }

}

float dft32_power(float *x, float *Xre, float *Xim, float *P) {
    // Calculate DFT and power spectrum up to Nyquist frequency
    float tmp=0;
    int n, k;
    int to_sin = 3*_DFT32_N/4; // index offset for sin
    int a, b;
    for (k=0 ; k<=_DFT32_N/2 ; ++k)
    {
        Xre[k] = 0; Xim[k] = 0;
        a = 0; b = to_sin;
        for (n=0 ; n<_DFT32_N ; ++n)
        {
            Xre[k] += x[n] * _DFT32_TF[/*a%_DFT64_N*/a & (_DFT32_N-1)];
            Xim[k] -= x[n] * _DFT32_TF[/*b%_DFT64_N*/b & (_DFT32_N-1)];
            a += k; b += k;
        }
        P[k] = Xre[k]*Xre[k] + Xim[k]*Xim[k];
        tmp += P[k];
    }
	return tmp;
}

//16 point dft-floating point
//x[16]: real input data
//Xre[16]: real output real elements
//Xim[16]: real output imaginary elements
//P[16]: real output power elements
void dft16(float *x, float *Xre, float *Xim/*, float *P*/) {
    // Calculate DFT and power spectrum up to Nyquist frequency
    int n, k;
    int to_sin = 3*_DFT16_N/4; // index offset for sin
    int a, b;
    for (k=0 ; k<=_DFT16_N/2 ; ++k)
    {
        Xre[k] = 0; Xim[k] = 0;
        a = 0; b = to_sin;
        for (n=0 ; n<_DFT16_N ; ++n)
        {
            Xre[k] += x[n] * _DFT16_TF[/*a%_DFT64_N*/a & (_DFT16_N-1)];
            Xim[k] -= x[n] * _DFT16_TF[/*b%_DFT64_N*/b & (_DFT16_N-1)];
            a += k; b += k;
        }
        //P[k] = Xre[k]*Xre[k] + Xim[k]*Xim[k];
    }

}

float dft16_power(float *x, float *Xre, float *Xim, float *P) {
    // Calculate DFT and power spectrum up to Nyquist frequency
    float tmp=0;
    int n, k;
    int to_sin = 3*_DFT16_N/4; // index offset for sin
    int a, b;
    for (k=0 ; k<=_DFT16_N/2 ; ++k)
    {
        Xre[k] = 0; Xim[k] = 0;
        a = 0; b = to_sin;
        for (n=0 ; n<_DFT16_N ; ++n)
        {
            Xre[k] += x[n] * _DFT16_TF[/*a%_DFT64_N*/a & (_DFT16_N-1)];
            Xim[k] -= x[n] * _DFT16_TF[/*b%_DFT64_N*/b & (_DFT16_N-1)];
            a += k; b += k;
        }
        P[k] = Xre[k]*Xre[k] + Xim[k]*Xim[k];
        tmp += P[k];
    }
	return tmp;
}

