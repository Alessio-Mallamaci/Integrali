/*! @file mathf.h
	@brief Library of functions for computing integrals 
	@author Paolo Gastaldo

	Details.
*/ 

//GUARDIA
#ifndef MATHF_H 
#define MATHF_H

//includo librerie e file.h
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "structs.h"

//prototipo funzione per realizzare unpolinomio
float Polynomial(poly_s polyf, float in); 
//prototipo funzione per fare l'integrale di un polinomio con il metodo dei rettangoli
void Rectangular(float* values, int size, float stepsize, float* integ1, float* integ2); 
//prototipo funzione per fare l'integrale di un polinomio con il metodo del trapezio
float Trapezoidal(float* values, int size, float stepsize); 


#endif