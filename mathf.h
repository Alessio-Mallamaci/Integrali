/**
  \file mathf.h
  \brief Library of functions for computing integrals
  \author Alessio Mallamaci
*/

//controllo-->"GUARDIA"
#ifndef MATHF_H
#define MATHF_H

#include <stdio.h>
#include <stdlib.h>

//Prototipi delle tre funzioni che erano presenti nel main
float Polynomial(float* coeff, int size, float in);
void Rectangular(float* values, int size, float stepsize, float* integ1, float* integ2);
float Trapezoidal(float* values, int size, float stepsize);

#endif