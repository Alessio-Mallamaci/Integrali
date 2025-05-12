/*! @file io.c
	@brief Definitions of the functions declared in io.h 
	@author Paolo Gastaldo

	Details.
*/

#include "io.h" 

//inizializzo costante STRL a 150
#define STRL  150

/*! @brief Opens a file in read-text mode
	@param filePath the path to the file
	@return the FILE* (NULL if something went wrong) 
 */
//Implementazione funzione per aprire un file di testo in modalità lettura e restituire un puntatore a quel file, se l'apertura ha successo.
FILE* OpenFile(char* filePath) {
		
	FILE* fPtr;
	fPtr = fopen(filePath,"rt"); //apertura del file in modalità lettura di testo ("r" = read , "t" = text mode)
	
	//Se fopen fallisce (file non trovato o accesso negato), stampa un messaggio di errore e ritorna NULL
	if (fPtr == NULL) {
		printf("\n OpenFile - ");
		printf("ERROR: Unable to open file %s\n",filePath);
        return NULL;
	}
	
	return fPtr; //restituisce puntatore al file	
} 

/*! @brief close a FILE*
	@param fPtr the FILE pointer
	@return 1 means that everyting is ok, -1 means that something went wrong 
*/
// Implementazione funzione per chiudere un file aperto precedentemente in modo sicuro, controllando eventuali errori.
int CloseFile(FILE* fPtr) {

	if (fPtr != NULL) {	// Controlla che il puntatore al file non sia NULL, cioè che il file sia stato aperto correttamente.
      if (fclose(fPtr) != 0) { // Tenta di chiudere il file con fclose. Se fclose restituisce diverso da zero, vuol dire che c’è stato un errore nella chiusura 
		  printf("\n CloseFile - ");
          printf("Error closing file \n");
          return -1; // Restituisce -1 se c’è un errore.
	  }
	  else 
		  return 1; // Restituisce 1 se la chiusura del file ha successo.
	}

	printf("\n CloseFile - ");
    printf("NULL pointer \n");
	return -1; //Restituisce -1 se il puntatore è NULL.
		
}

/*! @brief reads info from a configuration file: cofficients of the polygon, range, number of intervals
	@param fPtr the FILE pointer 
	@param pf pointer to Poly struct  
	@param xinf pointer to the variable for the inferior limit of the integration region 
	@param xsup pointer to the variable for the superior limit of the integration region 
	@param xinf pointer to the variable for the number of intervals
	@return 1 means that everyting is ok, -1 means that something went wrong 
*/
/*
Implementazie funzione che legge un file di configurazione che descrive un polinomio da integrare numericamente. 
Il file deve contenere tre righe, ognuna con uno specifico contenuto:

- Coefficiente del polinomio (es. 2.0 -1.0 3.5 --> 2x² - x + 3.5)
- Intervallo di integrazione (es. 0.0 5.0 → da x=0 a x=5)
- Numero di sottointervalli per l'integrazione numerica (es. 100)
*/
int ReadConfigFile(FILE* fPtr, poly_s* pf, float* xinf, float* xsup, int* intervals) {
	/*
	- FILE* fPtr: puntatore al file aperto (già aperto con fopen()).
	- poly_s* pf: puntatore a una struttura che conterrà il polinomio.
	- float* xinf, *xsup: estremi dell'intervallo di integrazione.
	- int* intervals: numero di sottointervalli da usare per l’integrazione.
	*/

	char str[STRL]; 
	int rv;

	//Se il file o la struttura sono nulli, stampa un errore e restituisce -1.
	if (fPtr == NULL) {
		printf("\n ReadConfigFile - ");
        printf("NULL File Pointer \n");
        return -1;
	}
	
	if (pf == NULL) {
		printf("\n ReadConfigFile - ");
        printf("NULL Pointer \n");
        return -1;
	}
	
	/*Leggi la prima riga del file : coefficienti del polinomio*/
	if (fgets(str,STRL,fPtr) != NULL) {

		str[strcspn(str, "\n")] = 0; /*rimuovi il carattere /n (end of line) alla fine*/
		
		/*
		Chiama ParseLine, che:
		- conta i coefficienti,
		- li converte in float,
		- li alloca dinamicamente,
		- li salva in pf->coeffs,
		- imposta pf->degree.
		*/
		rv= ParseLine(pf,str); 
		/*controllo se sono stati restituiti i valori giusti*/
		if (rv == -1) {
			printf("\n ReadConfigFile - ");
			printf("unable to parse the line\n");
			return -1;
		}
	}
	else {
		printf("\n ReadConfigFile - ");
        printf("unable to read\n");
        return -1;
	}
	
	/*Leggi la prima riga del file : intervallo di integrazione*/
	if (fgets(str,STRL,fPtr) != NULL) {
		
		str[strcspn(str, "\n")] = 0; /*rimuovi il carattere /n (end of line) alla fine*/
		
		sscanf(str,"%f %f",xinf,xsup); /*Legge i due estremi (xinf, xsup) da riga come float*/
	}
	else {
		printf("\n ReadConfigFile - ");
        printf("unable to read\n");
        return -1;
	}
	
	/*Leggi la terza riga del file : numero di sottointervalli*/
	if (fgets(str,STRL,fPtr) != NULL) {
		str[strcspn(str, "\n")] = 0; /*rimuovi il carattere /n (end of line) alla fine*/
		sscanf(str,"%d",intervals);
	}
	else {
		printf("\n ReadConfigFile - ");
        printf("unable to read\n");
        return -1;
	}
	
	return 1; 

}

/*! @brief parses a string that contains the coefficents of the polynom
	@param pf pointer to Poly struct  
	@param str the string to be parsed
	@return 1 means that everyting is ok, -1 means that something went wrong 
*/
/* implementazione funzione per leggere una stringa contenente numeri (coefficienti) separati da spazi e a memorizzarli in una struttura dati polinomiale (poly_s)*/
int ParseLine(poly_s* pf, char* str) {
	
	int ctr = 0;
	float* values = NULL; 
	char copy[STRL];
	
	//Controlla se la stringa è NULL, se sì, stampa un messaggio di errore e restituisce -1.
	if (str == NULL) {
		printf("\n ParseLine - ");
		printf("unable to read\n");
        return -1;
	}
	
	/* 
	Conta quanti coefficienti ci sono nella stringa:
	- Copia la stringa in una variabile temporanea copy per non modificarla.
	- Usa strtok per dividere la stringa in token separati da spazi.
	- Conta quanti token ci sono (quindi quanti numeri).
	*/
	strcpy(copy,str);
	char* token = strtok(copy," ");
	while (token != NULL) {
		ctr++;
		token = strtok(NULL," ");
	}
	
	/* Alloca dinamicamente un array di float per memorizzare i coefficienti*/
	values = (float*)malloc(sizeof(float)*ctr);
	/*Se la memoria non può essere allocata, stampa errore e restituisce -1.*/
	if (values == NULL) {
		printf("\n ParseLine - ");
		printf("\n cannot allocate memory\n");
		return -1;
	}
	
	/* Legge di nuovo i coefficienti per memorizzarli nell'array */
	ctr = 0;
	strcpy(copy,str);
	token = strtok(copy," ");
	while (token != NULL) {
		values[ctr] = atof(token);
		ctr++;
		token = strtok(NULL," ");
	}
	
	/* 
	Aggiorna la struttura poly_s:
	- Assegna il puntatore values all’attributo coeffs.
	- Imposta degree uguale al numero di coefficienti letti. 
	*/
	pf->coeffs = values; 
	pf->degree = ctr;
		
	/*Restituisce 1 in caso di successo*/
	return 1;
}