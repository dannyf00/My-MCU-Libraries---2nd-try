#ifndef REVAR_H_INCLUDED
#define REVAR_H_INCLUDED

//recusrive calculation of sum/mean/variance
//full credit to http://mathworld.wolfram.com/SampleVarianceComputation.html

typedef struct {
    double sum;                 //sum of all samples
    double mean;                //sample's mean
    double var;                 //sample's variance = s^2 = sigma(xi - mean)^2/(n-1)
    int n;                      //number of samples, at least 2
} REVAR_TypeDef;				//recursive variance calculation

//initialize var struct with the first sample value
void var_init(REVAR_TypeDef *var, double x0);

//calculate var
double var_calc(REVAR_TypeDef *var, double xi);


#endif // REVAR_H_INCLUDED
