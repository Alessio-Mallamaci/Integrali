/** \file main.c
	\brief Integrazione numerica di un polinomio
	\author Paolo Gastaldo

	Dettagli.
*/

#include <stdio.h>      // Libreria standard di I/O
#include <stdlib.h>     // Libreria per gestione memoria dinamica e funzioni di utilità
#include "io.h"         // Header personalizzato per I/O (es. apertura/lettura file)
#include "structs.h"    // Header con la definizione della struttura poly_s
#include "mathf.h"      // Header con funzioni matematiche personalizzate (es. Polynomial, Rectangular, Trapezoidal)


/*! \brief funzione principale
		
	In questa funzione viene letto il file di configurazione per: impostare il polinomio, impostare l'intervallo di integrazione e il numero di intervalli equidistanti in cui suddividere l'intervallo.
	Vengono definiti i punti che delimitano gli intervalli e infine si procede all'integrazione.
	
*/

int main() {

	int steps;               // Numero di intervalli
	float xmin, xmax;        // Estremi dell'intervallo di integrazione
	poly_s pf;               // Struttura contenente il polinomio
	
	float in;                // Variabile temporanea per iterare sui punti dell'intervallo
	float gap;               // Ampiezza di ciascun intervallo
	float* fvalues = NULL;   // Array che conterrà i valori del polinomio nei punti campionati
	
	float integ1, integ2;    // Variabili per salvare i risultati dell'integrazione
	int i;                   // Contatore
	int rv;	                 // Codice di ritorno per funzioni
	FILE* fptr = NULL;       // Puntatore al file di configurazione
	
	/* apertura del file di configurazione */
	char filePath[100]="config.txt";   // Percorso del file di configurazione
	fptr=OpenFile(filePath);           // Apertura del file
	if (fptr == NULL) {
		printf("\n Main - ");
		printf("ERRORE: impossibile aprire il file %s\n",filePath);
		exit(-1);                       // Uscita in caso di errore
	}
	
	/* lettura del file di configurazione */
	rv=ReadConfigFile(fptr,&pf,&xmin,&xmax,&steps);  // Lettura dei dati: coefficienti polinomio, intervallo, e numero di intervalli
	if (rv == -1) {
		printf("\n Main - ");
		printf("ERRORE: impossibile leggere il file di configurazione\n");
		exit(-1);                                     // Uscita in caso di errore
	}
	
	/* chiusura del file di configurazione */
	rv=CloseFile(fptr);            // Chiusura del file
	if (rv == -1) {
		printf("\n Main - ");
		printf("ERRORE: impossibile chiudere il file di configurazione\n");
		exit(-1);                 // Uscita in caso di errore
	}
	
	/* calcolo dell’ampiezza degli intervalli */
	in = xmin;                                              // Punto iniziale dell’integrazione
	gap = (float)(xmax-xmin)/(float)steps;                  // Calcolo dell’ampiezza di ciascun intervallo --> fa il CAST
	
	/* allocazione dell’array fvalues */
	fvalues = (float*)malloc(sizeof(float)*(steps+1));     // Allocazione dinamica per i valori del polinomio
	if (fvalues == NULL) {
		printf("\nERRORE: impossibile allocare memoria\n");
		exit(-1);                                           // Uscita in caso di errore
	}

	/* fvalues contiene i valori del polinomio nei punti che delimitano gli intervalli */
	for (i=0; i<=steps; i++) {
		fvalues[i] = Polynomial(pf,in);     // Calcola il valore del polinomio nel punto corrente
		in += gap;                          // Passa al punto successivo
	}
	
	integ1= 0.; 
	integ2= 0.;

	/* integrazione secondo la regola dei rettangoli */
	Rectangular(fvalues,steps+1,gap,&integ1,&integ2);  // Integrazione con regola dei rettangoli (valori minimo e massimo)
	printf("\nRegola dei rettangoli - L'integrale tra %f e %f è nell'intervallo: [%f,%f]\n", xmin,xmax,integ1,integ2);
	
	/* integrazione secondo la regola dei trapezi */
	integ1 = Trapezoidal(fvalues,steps+1,gap);         // Integrazione con la regola dei trapezi
	printf("\nRegola dei trapezi - L'integrale tra %f e %f è: %f\n", xmin,xmax,integ1);
	
	/* deallocazione della memoria: array incluso in pf */
	if (pf.coeffs != NULL)
		free(pf.coeffs);       // Libera la memoria allocata per i coefficienti del polinomio
	
	/* deallocazione della memoria: array fvalues */
	if (fvalues != NULL)
		free(fvalues);         // Libera la memoria allocata per i valori del polinomio

	return 0;                 // Fine del programma
}
