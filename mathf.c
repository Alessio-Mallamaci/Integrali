/** \file mathf.c
	\brief defintions of the functions declared in mathf.h
	\author Paolo Gastaldo

	Details.
*/

// includo "mathf.h"che contiene anche il file "structs.h"
#include "mathf.h"



/*! \brief computes the output value of a polynomial
	\param polyf the polynomial
	\param in the input value 
	\return the output value
*/
// Implementazione della funzione polinomio per costruire la funzione polinomio
float Polynomial(poly_s polyf, float in) {
	
	int i;
	float out = 0.;
	float x = in;	
	
	out = polyf.coeffs[0];	// coefficiente del polinomio
	for (i=1; i<polyf.degree; i++) {	// for controllato dal grado del polinomio 
		
		// Sta calcolando: out=coeffs[0] + coeffs[1]⋅in + coeffs[2]⋅in^2 + ⋯ + coeffs[n]⋅in^n
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
// Implementazione della funzione RETTANGOLARE che esegue due forme di integrazione numerica approssimata, basata sulla regola del rettangolo, su un array di valori.
void Rectangular(float* values, int size, float stepsize, float* integ1, float* integ2) {
	
	/*
	- values: array di valori (ad es. valori di una funzione campionata).
	- size: numero di elementi nell'array values.
	- stepsize: la distanza (costante) tra i punti, usata per approssimare l’integrale.
	- integ1, integ2: puntatori ai risultati delle due approssimazioni di integrale
	*/
	int i;

	//inizializza i due array a 0
	(*integ1) = 0.; //somma rettangolare sinistra (includendo il primo punto ma non l’ultimo)
	(*integ2) = 0.;	//somma rettangolare destra (includendo l’ultimo punto ma non il primo)
	
	//L'integrale integ1 include solo il primo valore (inizio dell'intervallo).
	(*integ1) += stepsize*values[0];

	//Per tutti i valori intermedi (dal secondo all’ultimo escluso), li aggiunge a entrambi gli integrali.
	for (i=1; i<(size-1); i++) {
		(*integ1) += stepsize*values[i];
		(*integ2) += stepsize*values[i];
	}
	//L'ultima iterazione (quando i == size-1) aggiunge solo all'integrale integ2 l’ultimo valore.
	(*integ2) += stepsize*values[i];
	
	return;
}



/*! \brief numerical integration according to the trapezoidal rule 
	\param values points that set the equally spaced intervals (pointer to) 
	\param size length of the values array 
	\param stepsize the interval between two points 
	\return the integral computed  
*/
//implementazione della  funzione TRAPEZIOIDALE che esegue la regola del trapezio per approssimare l'integrale definito di una funzione campionata in punti equidistanti.
float Trapezoidal(float* values, int size, float stepsize) {
	/*
	- values: array contenente i valori della funzione (campionati).
	- size: numero di valori nell’array.
	- stepsize: distanza tra i punti (cioè la larghezza di ciascun intervallo).
	- integ: restituisce il valore float dell’approssimazione dell’integrale.
	*/

	int i;

	float integ = 0.; //Inizializza la variabile integ che accumula il risultato.
	float h = stepsize/2.; //h è metà del passo: serve perché la formula del trapezio è: area= (stepsize/2)*(f(Xi)+f(Xi+1))

	//Somma tutte le aree per ottenere l’integrale approssimato.
	for (i=0; i<(size-1); i++) 
		integ += h*(values[i+1]+values[i]); //sommatoria delle aree
	
	return integ;
}
