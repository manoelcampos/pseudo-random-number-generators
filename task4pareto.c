/**
 * Program of the Task 4: Pareto Pseudo Random Number Generator
 * 
 * @file task4pareto.c
 * @author manoelcampos
 * @date March 25, 2014, 8:55 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "lib/commonslib.h"

/**
* Initializes the Pareto generator
*/
void pareto_init(){
	srand(time(NULL));
}

/**
* Generate a pareto random number 
* @return Returns the generated number
*/
double pareto(){
	#define RAND() ( rand()/(double)RAND_MAX )
	double alpha=2.2, m = 1.0;
	return m/(pow(RAND(), 1.0/alpha));
	//return (alpha/pow((1.0+RAND()),(1.0+alpha)))+0.8;
}

//The amount of pseudo random numbers to be generated
#define SIZE 400
//The maximum value that can be generated by the distribution
#define MAX_VALUE 10.0

/**
 * Starts the application.
 * @param[in] argc Command line argument count
 * @param[in] argv Command line argument array
 * @return Returns the application exit code
 */
int main(int argc, char** argv) {
	unsigned int i;
	double x=1; //must be a negative number
	double inc = (MAX_VALUE)/(SIZE*0.2);
	double array[SIZE];
		
	double sum=0, mean, sdev;
	pareto_init();
	for(i=0; i < SIZE; i++)
		sum += (array[i] = pareto());

	mean = sum / (double)SIZE;
	sdev = stddev(array, mean, SIZE);
	printf("#Pareto Random Number Generator (PRNG)\n");
	printf("#ParetoRN\tNorm of PRN\tstd value\tStandardNorm\tDiff\n");
	double normX, normx;
	for(i=0; i < SIZE; i++){
		normX = count(array, x, SIZE);
		//normX = cnormdist(array[i], mean, sdev);
		normx = 1.0-pow(1.0/x, 2);
		printf("%lf\t%lf\t%lf\t%lf\t%lf\n", 
			array[i], normX, 
			x, normx, doubleAbs(normX, normx));
		x+=inc;
	}
		
    return (EXIT_SUCCESS);
}