/** \file structs.h
	\brief defines the structs 
	\author Paolo Gastaldo

	Details.
*/

//GUARDIA
#ifndef STRUCTS_H 
#define STRUCTS_H

/*! \struct Poly
	\brief stores the coefficients of a polynomial

	coeffs[0] + coeffs[1]*x + coeffs[2]*x^2 + ......	
*/

// definisci struttura polinomio
typedef struct Poly {
	float* coeffs; 	/* the coefficients, starting from the bias value  */
	int degree; 	/* the number of elements in the array */
} poly_s;

#endif