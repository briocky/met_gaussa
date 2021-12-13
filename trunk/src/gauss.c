#include "gauss.h"
#include <math.h>

void chooseMax(int k, Matrix *mat, Matrix *b) {
    double **A = mat->data;
    double **B = b->data;
    double max = 0;
    int i_max = k;
    for (int i = k; i < mat -> c; i++) {
        if (fabs(A[i][k]) > max) {
            max = fabs(A[i][k]);
            i_max = i;
        }
    }

    double tmp;

    for (int i = 0; i < mat -> c; i++) {
        tmp = A[0][i];
        A[0][i] = A[i_max][i];
        A[i_max][i] = tmp;
    }

    tmp = B[0][0];
    B[0][0] = B[i_max][0];
    B[i_max][0] = tmp;
}

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 * Zwraca 2 - inny blad
 */
int eliminate(Matrix *mat, Matrix *b){
	double **A = mat->data;
	double **B = b->data;

	if(b->r!=mat->r || b->c!=1)
		return 2;
		
	for( int k=0 ;k<mat->c-1; k++){
        chooseMax(k, mat, b);
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

