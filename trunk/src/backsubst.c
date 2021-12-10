#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	if (mat -> r != mat -> c || mat -> r != b -> r)
		return 2;

	double **A = mat->data;
    double **B = b->data;
    double **X = x->data;

	for(int w = mat -> r - 1; w >= 0; w--){
        double s = 0;
        for(int k = w + 1; k < mat -> r; k++){
            s += A[w][k] * X[0][k];
        }
        if (A[w][w] == 0)
        	return 1;
        X[0][w] = (B[w] - s) / A[w][w];
    }
    
	return 0;
}


