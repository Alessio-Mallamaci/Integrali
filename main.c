/** \file main.c
	\brief Numerical integration of a polynomial
	\author Paolo Gastaldo

	Details.
*/

#include <stdio.h> 
#include <stdlib.h> 
#include "io.h"
#include "structs.h"
#include "mathf.h"


/*! \brief the main function
		
	here we read the configuration file to: set the polynomial, set the integration range and set the number of equally spaced intervals in which the range should be divided 
	the points delimiting the intervals are defined and then the integration is finalized 
	
*/

int main() {

	int steps;
	float xmin, xmax;
	poly_s pf;
	
	float in;
	float gap;
	float* fvalues = NULL;
	
	float integ1, integ2;
	int i;
	int rv;	
	FILE* fptr = NULL;
	
	/* opening the configuration file */
	char filePath[100]="config.txt";
	fptr=OpenFile(filePath);
	if (fptr == NULL) {
		printf("\n Main - ");
		printf("ERROR: Unable to open file %s\n",filePath);
		exit(-1);
	}
	
	/* reading the configuration file */
	rv=ReadConfigFile(fptr,&pf,&xmin,&xmax,&steps);
	if (rv == -1) {
		printf("\n Main - ");
		printf("ERROR: Unable to read configuration file \n");
		exit(-1);
	}
	
	/* closing the configuration file */
	rv=CloseFile(fptr);
	if (rv == -1) {
		printf("\n Main - ");
		printf("ERROR: Unable to close configuration file \n");
		exit(-1);
	}
	
		
	in = xmin;
	gap = (float)(xmax-xmin)/(float)steps;
	
	/* allocation of the array fvalues */
	fvalues = (float*)malloc(sizeof(float)*(steps+1));
	if (fvalues == NULL) {
		printf("\nERROR: cannot allocate memory\n");
		exit(-1);
	}

	/* fvalues stores the values delimiting the intervals */
	for (i=0; i<=steps; i++) {
		fvalues[i] = Polynomial(pf,in);
		in += gap;
		
	}
	
	integ1= 0.; 
	integ2= 0.;

	/* integral according to the Rectangular rule */
	Rectangular(fvalues,steps+1,gap,&integ1,&integ2);
	printf("\nRectangular rule - The integral between %f and %f is in the interval: [%f,%f]\n", xmin,xmax,integ1,integ2);
	
	/* integral according to the Trapezoidal rule */
	integ1 = Trapezoidal(fvalues,steps+1,gap);
	printf("\nTrapezoidal rule - The integral between %f and %f is : %f\n", xmin,xmax,integ1);
	
	/* memory deallocation: the array included in pf */
	if (pf.coeffs != NULL)
		free(pf.coeffs);
	
	/* memory deallocation: the array fvalues */
	if (fvalues != NULL)
		free(fvalues);

	return 0;
}