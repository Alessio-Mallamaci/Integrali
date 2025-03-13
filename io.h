/*! @file io.h
	@brief Library of functions for I/O 
	@author Paolo Gastaldo

	Details.
*/


#ifndef IO_H 
#define IO_H

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "structs.h"


//apri file
FILE* OpenFile(char* filePath);
//chiude il file
int CloseFile(FILE* fPtr);
//leggi polinomio nel file
int ReadConfigFile(FILE* fPtr, poly_s* pf, float* xinf, float* xsup, int* intervals);
//?? 
int ParseLine(poly_s* pf, char* str);

#endif