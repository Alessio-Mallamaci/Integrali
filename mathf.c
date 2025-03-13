/** \file mathf.c
	\brief defintions of the functions declared in mathf.h
	\author Paolo Gastaldo

	Details.
*/

#include "mathf.h"


/*! \brief computes the output value of a polynomial
	\param polyf the polynomial
	\param in the input value 
	\return the output value
*/
float Polynomial(poly_s polyf, float in) {
	
	int i;
	float out = 0.;
	float x = in;	
	
	out = polyf.coeffs[0];
	for (i=1; i<polyf.degree; i++) {
		out += polyf.coeffs[i]*x;
		x *= in;
	}

	return out;

}


/*! \brief numerical integration according to the rectangular rule 
	\param values points that set the equally spaced intervals (pointer to) 
	\param size length of the values array 
	\param stepsize the interval between two points 
	\param integ1 integral computed using as reference the first point of each interval 
	\param integ2 integral computed using as reference the second point of each interval	
*/
void Rectangular(float* values, int size, float stepsize, float* integ1, float* integ2) {
	
	int i;

	(*integ1) = 0.;
	(*integ2) = 0.;	
	
	(*integ1) += stepsize*values[0];
	for (i=1; i<(size-1); i++) {
		(*integ1) += stepsize*values[i];
		(*integ2) += stepsize*values[i];
	}
	(*integ2) += stepsize*values[i];
	
	return;
}


/*! \brief numerical integration according to the trapezoidal rule 
	\param values points that set the equally spaced intervals (pointer to) 
	\param size length of the values array 
	\param stepsize the interval between two points 
	\return the integral computed  
*/
float Trapezoidal(float* values, int size, float stepsize) {
	
	int i;

	float integ = 0.;
	float h = stepsize/2.;
	
	for (i=0; i<(size-1); i++) 
		integ += h*(values[i+1]+values[i]);
	
	return integ;
}
