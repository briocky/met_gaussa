#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
	double **A = mat->data;
	double **B = b->data;

	for( int k=0 ;k<mat->c-1; k++){
        for(int w=k+1; w<mat->c;w ++){
			if(A[k][k]==0)//dzielenie przez zero
				return 1;
            double q= A[w][k] / A[k][k];
            //fprintf(stderr,"%lf\n",q);
            for(int z=0; z<mat->c; z++)
                A[w][z] -= q * A[k][z]; 
            B[w][b->c-1]-= q * B[k][b->c-1];
        }
    }
    /**
  	 * Tutaj należy umieścić właściwą implemntację.
		 */

	return 0;
}

