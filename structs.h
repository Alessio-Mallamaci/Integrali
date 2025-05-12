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

//definisce struttura di un polinomio
typedef struct Poly {
	float* coeffs; 	/*i coefficienti, partendo dal valaore di bias --> Questo è un puntatore a float, ovvero un array dinamico di coefficienti.
																	   Contiene i coefficienti del polinomio, a partire dal termine noto (bias).*/

	int degree; 	/* numero di elementi in un array --> Questo campo indica il grado del polinomio (cioè, quanti coefficienti ci sono).*/
} poly_s; //etichetta

#endif