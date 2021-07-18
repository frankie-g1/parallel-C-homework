#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

// TO COMPILE:    tau_cc.sho -o A5MPI A5MPI.c

int is_prime(int n);

int main(int argc, char** argv){
	int rank, numranks;
	MPI_Init(&argc,&argv);
    	MPI_Comm_size(MPI_COMM_WORLD,&numranks);
    	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int n=10000000;
    	int numprimes = 0;
	int myWork = n/numranks; 
	if(n%numranks !=0 && (rank==(numranks-1)))
	{
		myWork += n - (myWork * numranks);
	}
	int myStart = rank * myWork;
	int myEnd = myStart + myWork;
    	int i;
    	for (i = myStart; i < myEnd; i++)
    	{
        	if (is_prime(i) == 1)
            	numprimes ++;
    	}
	MPI_Allreduce(MPI_IN_PLACE, &numprimes, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    	printf("Number of Primes: %d\n",numprimes);
	MPI_Finalize();
	}

int is_prime(int n)
{
    	/* handle special cases */
    	if      (n == 0) return 0;
    	else if (n == 1) return 0;
    	else if (n == 2) return 1;

    	int i;
    	for(i=2;i<=(int)(sqrt((double) n));i++)
        	if (n%i==0) return 0;

    	return 1;
}
