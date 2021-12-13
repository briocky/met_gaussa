#include "gauss.h"
#include <stdio.h>
#include "mat_io.h"

void wyb_glowny_elem(Matrix *mat, Matrix *b, int kol){
	int max_wartosc = kol; //wiersz w ktorym wystapila najwieksza liczba(licząc od przekatnej w doł)
	int w, c;
	double tmp; // do petli w ktorej zapisujemy aktualny element

	for(w =kol+1; w<mat->r;w++){
		if(mat->data[w][kol]>mat->data[max_wartosc][kol])
			max_wartosc=w; // wpisujemy numer wiersza w ktorym wystapila liczba wieksza od wartosci na przekatnej
	}
	if(max_wartosc != kol){
		//zamieniamy wiersz "k-ty" z wierszem zapisanym w max_wartosc
		for(c=0;c<mat->c;c++){ //macierz A
			tmp = mat->data[kol][c];
			mat->data[kol][c] = mat->data[max_wartosc][c];
			mat->data[max_wartosc][c] = tmp;
		}
		//macierz b
		tmp = b->data[kol][b->c-1];
		b->data[kol][b->c-1]=b->data[max_wartosc][b->c-1];
		b->data[max_wartosc][b->c-1] = tmp;
	}

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
		wyb_glowny_elem(mat, b, k);
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

	return 0;
}

