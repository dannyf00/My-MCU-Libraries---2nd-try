/***********
* Includes *
***********/
//#include <stdio.h>
//#include <stdlib.h>
#include <math.h>

#include "ntc.h"

/*
 * NTC thermistor library
 * Version 1.0
 * Copyright (C) 2007, 2013 - SoftQuadrat GmbH, Germany
 * Contact: thermistor (at) softquadrat.de
 * Web site: thermistor.sourceforge.net
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 * USA
 */

/** @file ttor.c
 * Program calculating the resistance from temperature value of an NTC thermistor.
 * The Steinhart-Hart polynom allows calculation of absolute temperature
 * from resistance of an NTC thermistor
 *
 * <center><i>
 * 1/t = 1/t<sub>0</sub>
 *       + c<sub>1</sub> &middot; ln(r/r<sub>0</sub>)
 *       + c<sub>2</sub> &middot; ln(r/r<sub>0</sub>)<sup>2</sup>
 *       + c<sub>3</sub> &middot; ln(r/r<sub>0</sub>)<sup>3</sup>
 * </i></center>
 *
 * where (<b>r<sub>0</sub></b>,<b>t<sub>0</sub></b>) is a fixed resistance temperature pair.
 *
 * By substitution
 *
 * <center><i>
 * ln(r/r<sub>0</sub>) = ln(r) - ln(r<sub>0</sub>)
 * </i></center>
 *
 * this leads to a polynom in <b>ln(r)</b>
 *
 * <center><i>
 * 1/t = a<sub>0</sub>
 *       + a<sub>1</sub> &middot; ln r
 *       + a<sub>2</sub> &middot; (ln r)<sup>2</sup>
 *       + a<sub>3</sub> &middot; (ln r)<sup>3</sup>
 * </i></center>
 *
 *
 * With substitutions
 *
 * <center><i>
 * b = a<sub>2</sub>/a<sub>3</sub>
 * </i></center>
 *
 * <center><i>
 * c = a<sub>1</sub>/a<sub>3</sub>
 * </i></center>
 *
 * <center><i>
 * d = (a<sub>0</sub> - 1/t)/a<sub>3</sub>
 * </i></center>
 *
 * <center><i>
 * p = c - 1/3 * b<sup>2</sup>
 * </i></center>
 *
 * <center><i>
 * q = 2/27 &middot; b<sup>3</sup> - 1/3 * b &middot; c + d
 * </i></center>
 *
 * <center><i>
 * u = [ -q/2 + ( q<sup>2</sup>/4 + p<sup>3</sup>/27 ) <sup>1/2</sup> ] <sup>1/3</sup>
 * </i></center>
 *
 * <center><i>
 * v = [ -q/2 - ( q<sup>2</sup>/4 + p<sup>3</sup>/27 ) <sup>1/2</sup> ] <sup>1/3</sup>
 * </i></center>
 *
 * this gives
 *
 * <center><i>
 * r = e<sup>u + v - b/3</sup>
 * </i></center>
 *
 * The program calculates the calculates the temperature from a given resistance value of an NTC
 * according to that formula.
 */

/**********
* Defines *
**********/
/** Absolute Zero. */
#define TABS (-273.15)

/************
* Variables *
************/
/** Coefficients of Steinhart-Hart polynom. */
double a[] = {
	4.524024725919526e-004,
	3.934722516618191e-004,
	-7.642331765196044e-006,
	4.048572707661904e-007,
};

/**************
* Prototyping *
**************/
/* Conversion from temperature to resistance. */
//double ntc_t2r(double t);

/************
* Functions *
************/
/**
/* Conversion from temperature to resistance.
 * Calculates and returns resistance for given temperature.
 * @param t temperature (in degree Celsius).
 * @return corresponding resistance.
 */
double ntc_t2r(double t)
{
	double r;
	double u, v, p, q, b, c, d;

	t = t - TABS;
	d = (a[0] - 1.0 / t) / a[3];
	c = a[1] / a[3];
	b = a[2] / a[3];
	q = 2.0 / 27.0 * b * b * b - 1.0 / 3.0 * b * c + d;
	p = c - 1.0 / 3.0 * b * b;
	v = - pow(q / 2.0 + sqrt(q * q / 4.0 + p * p * p / 27.0), 1.0 / 3.0);
	u =   pow(-q / 2.0 + sqrt(q * q / 4.0 + p * p * p / 27.0), 1.0 / 3.0);
	r  = exp(u + v - b / 3.0);
	return r;
}

/*
 * NTC thermistor library
 * Version 1.0
 * Copyright (C) 2007, 2013 - SoftQuadrat GmbH, Germany
 * Contact: thermistor (at) softquadrat.de
 * Web site: thermistor.sourceforge.net
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 * USA
 */

/** @file rtot.c
 * Program calculating the temperature from resistance value of an NTC thermistor.
 * The Steinhart-Hart polynom allows calculation of absolute temperature
 * from resistance of an NTC thermistor
 *
 * <center><i>
 * 1/t = 1/t<sub>0</sub>
 *       + c<sub>1</sub> &middot; ln(r/r<sub>0</sub>)
 *       + c<sub>2</sub> &middot; ln(r/r<sub>0</sub>)<sup>2</sup>
 *       + c<sub>3</sub> &middot; ln(r/r<sub>0</sub>)<sup>3</sup>
 * </i></center>
 *
 * where (<b>r<sub>0</sub></b>,<b>t<sub>0</sub></b>) is a fixed resistance temperature pair.
 *
 * By substitution
 *
 * <center><i>
 * ln(r/r<sub>0</sub>) = ln(r) - ln(r<sub>0</sub>)
 * </i></center>
 *
 * this leads to a polynom in <b>ln(r)</b>
 *
 * <center><i>
 * 1/t = a<sub>0</sub>
 *       + a<sub>1</sub> &middot; ln r
 *       + a<sub>2</sub> &middot; (ln r)<sup>2</sup>
 *       + a<sub>3</sub> &middot; (ln r)<sup>3</sup>
 * </i></center>
 *
 * The program calculates the calculates the temperature from a given resistance value of an NTC
 * according to that formula.
 */

/**********
* Defines *
**********/
/** Absolute Zero. */
#define TABS (-273.15)

/************
* Variables *
************/
/** Coefficients of Steinhart-Hart polynom. */
//double a[] = {
//	4.524024725919526e-004,
//	3.934722516618191e-004,
//	-7.642331765196044e-006,
//	4.048572707661904e-007,
//};

/**************
* Prototyping *
**************/
/* Evaluates p(x) for a polynom p. */
//double poly(double x, int degree, double p[]);
/* Conversion from resistance to temperature. */
//double rtot(double r);

/************
* Functions *
************/
/**
 * Evaluates p(x) for a polynom p.
 * Calculates the value of polynom p at x accordings to
 * Horners schema.
 * @param p polynom.
 * @param x value to be inserted into the polynom.
 * @return calculated polynom value.
 */
double poly(double x, int degree, double p[]) {
	double retval = 0.0;
	int i;

	for (i = degree; i >= 0; i--)
		retval = retval * x + p[i];
	return retval;
}

/* Conversion from resistance to temperature.
 * Calculates and returns temperature for given resistance.
 * @param t resistance (in Ohm).
 * @return corresponding temperature.
 */
double ntc_r2t(double r)
{
	double ti;

	ti = poly(log(r), 3, a);
	ti = 1.0 / ti + TABS;
	return ti;
}

