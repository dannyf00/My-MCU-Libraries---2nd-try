#include "revar.h"				//recursive calculation of sum, mean and variance statistics
//#include "xc.h"				//we use pic24

//recursive calculation of variance

//initialize var struct with the first sample value
void var_init(REVAR_TypeDef *var, double x0) {
    var->sum = x0;
    var->mean = x0;
    var->var = 0;
    var->n = 1;
}

//calculate var
double var_calc(REVAR_TypeDef *var, double xi) {
    double tmp, tmp1;
    int n1;

    n1 = var->n + 1;			//update the number of observations
    var->sum += xi;             //update sum
    tmp1 = var->sum / n1;    	//calculate the new mean
    tmp = tmp1 - var->mean;     //tmp = mean(n+1)-mean(n)
    tmp = tmp * tmp * n1;     	//tmp = (mean(n+1)-mean(n))^2 * (1+n)
    tmp = (1 - 1.0 / var->n) * var->var + tmp;
    var->mean = tmp1;			//update average
    var->var = tmp;				//update var
    var->n = n1;				//update the number of observations
    return tmp;
}

