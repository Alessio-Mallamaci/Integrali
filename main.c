/** \file main.c
	\brief Numerical integration of a polynomial
	\author Paolo Gastaldo

	first version of this software; all the functions are in this file  
*/

/*! \mainpage 
 *
 * \section intro_sec Introduction
 *
 * This is a software in C language for computing numerical integration * by adopting different techniques.
   
   Available techniques: Riemann sum (Rectangular Rule), Trapezoidal Rule.
 
 *
 * \section install_sec Usage
 *
 * 
 *
 * etc...
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>


/*! \brief computes the output value of a polynomial
	\param coeff coefficients of the polynomial (pointer to) 
	\param size length of the coeff array 
	\param in the input value 
	\return the output value
	
	the polynomial is structured as follows: coeff[0] + coeff[1]*x + ....
*/
/*
	coeff --> puntatore ad array (coeff = 0 --> salto un grado del polinomio)
	size --> dimensione array = grado polinomio
*/
float Polynomial(float* coeff, int size, float in) { 
	
	int i; 				/* counter for loops */
	float out = 0.;		/* used as accumulator to compute the value of the function given an input */
	float x = in;		/* to represent the different elements of the polynomial (x, x^2, x^3,...) */	
	
	out = coeff[0];
	for (i=1; i<size; i++) {
		out += coeff[i]*x;
		x *= in;			/* x^i */
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
/*
	values--> tutti i punti intermedi tra a e b
	size --> dimensione array = grado polinomio
	
	retituisce 2 valori:
	integ1 --> valore integrale per difetto
	integ2 --> valore integrale per eccesso
*/
void Rectangular(float* values, int size, float stepsize, float* integ1, float* integ2) {
	
	int i; 	/* counter for loops */

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
	\return the computed integral  
*/
/*
	fa una cosa simile alla funzione "Rectangular", ma restituisce un solo valore
*/
float Trapezoidal(float* values, int size, float stepsize) {
	
	int i; 		/* counter for loops */

	float integ = 0.; 		/* used as accumulator to compute the integral */
	float h = stepsize/2.;	/* to avoid dividing by 2 at each round of the loop */
	
	for (i=0; i<(size-1); i++) 
		integ += h*(values[i+1]+values[i]);
	
	return integ;
}



/*! \brief the main function
		
	here we define the polynomial, set the integration range and set the number of equally spaced intervals in which the range should be divided 
	the points delimiting the intervals are defined and then the integration is finalized 
	
*/
int main() {

	/* setting all the parameters */
	float fcoeff[4] = {-10.0,1.0,0.0,2.0};	/* the polynomial */
	float xmin = 0.0; 						/* the integration range */ 
	float xmax= 5.0; 					
	int intervals = 5000; 					/* number of equally spaced intervals */ 
	
	
	float integ1, integ2;
	
	int i; 
	float in = xmin;
	float gap = (xmax-xmin)/(float)intervals; //allocazione della memoria per l'array
	float* fvalues = NULL;
	
	/* this array will store the (steps+1) values of the polynomial that are delimiting the equally spaced intervals*/
	fvalues = (float*)malloc(sizeof(float)*(intervals+1));
	if (fvalues == NULL) { //controllo se ha funzionato l'allocazione
		printf("\nERROR: cannot allocate memory\n");
		exit(-1);
	}

	/* to get the value of the polynomial at the different points that are delimiting the intervals */
	for (i=0; i<=intervals; i++) {
		fvalues[i] = Polynomial(fcoeff,4,in); //popola i valori nell'array step per step
		in += gap;
	}
	
	integ1= 0.; 
	integ2= 0.;

	/* to compute the integral according to the rectangular rule */
	Rectangular(fvalues,intervals+1,gap,&integ1,&integ2);
	printf("\nRectangular rule - The integral between %f and %f is in the interval: [%f,%f]\n", xmin,xmax,integ1,integ2);
	
	/* to compute the integral according to the trapezoidal rule */
	integ1 = Trapezoidal(fvalues,intervals+1,gap);
	printf("\nTrapezoidal rule - The integral between %f and %f is : %f\n", xmin,xmax,integ1);
	
	/* deallocation */
	if (fvalues != NULL)
		free(fvalues);

	return 0;
}

/*
	TESTING: problemi del programma, cambinado i valori di alcuni programmi durante la lezione:
		- se facciamo intervalli con valori troppo alti ==> intervalli piccoli --> problemi di instabilità numerica
		- aumentando il grado del pominomio ho un po' più problemi	
*/