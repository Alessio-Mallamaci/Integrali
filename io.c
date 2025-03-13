/*! @file io.c
	@brief Definitions of the functions declared in io.h 
	@author Paolo Gastaldo

	Details.
*/


#include "io.h" 

#define STRL  150

/*! @brief Opens a file in read-text mode
	@param filePath the path to the file
	@return the FILE* (NULL if something went wrong) 
 */
FILE* OpenFile(char* filePath) {
		
	FILE* fPtr;
	fPtr = fopen(filePath,"rt");
	if (fPtr == NULL) {
		printf("\n OpenFile - ");
		printf("ERROR: Unable to open file %s\n",filePath);
        return NULL;
	}
	
	return fPtr;
		
} 

/*! @brief close a FILE*
	@param fPtr the FILE pointer
	@return 1 means that everyting is ok, -1 means that something went wrong 
*/
int CloseFile(FILE* fPtr) {
		
	if (fPtr != NULL) {	
      if (fclose(fPtr) != 0) {
		  printf("\n CloseFile - ");
          printf("Error closing file \n");
          return -1;
	  }
	  else 
		  return 1;
	}

	printf("\n CloseFile - ");
    printf("NULL pointer \n");
	return -1;
		
}

/*! @brief reads info from a configuration file: cofficients of the polygon, range, number of intervals
	@param fPtr the FILE pointer 
	@param pf pointer to Poly struct  
	@param xinf pointer to the variable for the inferior limit of the integration region 
	@param xsup pointer to the variable for the superior limit of the integration region 
	@param xinf pointer to the variable for the number of intervals
	@return 1 means that everyting is ok, -1 means that something went wrong 
*/
int ReadConfigFile(FILE* fPtr, poly_s* pf, float* xinf, float* xsup, int* intervals) {
	
	char str[STRL]; 
	int rv;
	
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
	
	
	/*first line of the file: coefficients of the polynom*/
	if (fgets(str,STRL,fPtr) != NULL) {
		str[strcspn(str, "\n")] = 0; /* removing end of line */
		rv= ParseLine(pf,str); 
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
	
	/*second line of the file: interval of integration*/
	if (fgets(str,STRL,fPtr) != NULL) {
		str[strcspn(str, "\n")] = 0; /* removing end of line */
		sscanf(str,"%f %f",xinf,xsup);
	}
	else {
		printf("\n ReadConfigFile - ");
        printf("unable to read\n");
        return -1;
	}
	
	/*third line of the file: number of subintervals*/
	if (fgets(str,STRL,fPtr) != NULL) {
		str[strcspn(str, "\n")] = 0; /* removing end of line */
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
int ParseLine(poly_s* pf, char* str) {
	
	int ctr = 0;
	float* values = NULL; 
	char copy[STRL];
	
	if (str == NULL) {
		printf("\n ParseLine - ");
		printf("unable to read\n");
        return -1;
	}
	
	/* counting the number of coefficents (which is unknown) */
	strcpy(copy,str);
	char* token = strtok(copy," ");
	while (token != NULL) {
		ctr++;
		token = strtok(NULL," ");
	}
	
	/* allocating an array to store the coefficients */
	values = (float*)malloc(sizeof(float)*ctr);
	if (values == NULL) {
		printf("\n ParseLine - ");
		printf("\n cannot allocate memory\n");
		return -1;
	}
	
	/* reading again the coefficients to store them in the array */
	ctr = 0;
	strcpy(copy,str);
	token = strtok(copy," ");
	while (token != NULL) {
		values[ctr] = atof(token);
		ctr++;
		token = strtok(NULL," ");
	}
	
	/* updating pf */
	pf->coeffs = values; 
	pf->degree = ctr;
		
	
	return 1;
}