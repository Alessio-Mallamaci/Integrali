/*! @file io.h
	@brief Library of functions for I/O 
	@author Paolo Gastaldo

	Details.
*/

//GUARDIA
#ifndef IO_H 
#define IO_H

//includo librerie e file.h 
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "structs.h"


//Prototipo funzione "APRI FILE"
FILE* OpenFile(char* filePath);

//Prototipo funzione "CHIUDI IL FILE"
int CloseFile(FILE* fPtr);


/*
Prototipo funzione "LEGGI FILE DI CONFIGURAZIONE" che contiene:
- I coefficienti di un polinomio.
- L’intervallo di integrazione [xinf, xsup].
- Il numero di sottointervalli per l’integrazione numerica.
*/
int ReadConfigFile(FILE* fPtr, poly_s* pf, float* xinf, float* xsup, int* intervals);


/*
Prototipo funzione che:
-legge una stringa contenente i coefficienti di un polinomio
- li parsa, li memorizza dinamicamente in un array
- aggiorna una struttura poly_s con questi dati. È una funzione tipica per analizzare input testuali numerici e trasformarli in dati utilizzabili.
*/
int ParseLine(poly_s* pf, char* str);

#endif