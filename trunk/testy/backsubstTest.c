#include <stdio.h>
#include "../src/mat_io.h"
#include "../src/backsubst.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Zerowanie macierzy A
void zeruj(Matrix *mat, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
			mat -> data[i][j] = 0;
	}
}

//Funkcja wylicza wartości macierzy b na podstawie A i x
void licz_b(Matrix *mat, Matrix *b, Matrix *x, int size) {
	double suma = 0;
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = i; j < size; j++) {
			suma += x -> data[j][0] * mat -> data[i][j];
		}
	b -> data[i][0] = suma;
	suma = 0;
	}
}

int main() {
	srand(time(NULL));
	int size = rand() % 15 + 1;
	Matrix *A = createMatrix(size, size);
	Matrix *b = createMatrix(size, 1);
	Matrix *x = createMatrix(size, 1);
	Matrix *x_obliczone = createMatrix(size, 1);

	zeruj(A, size);
	int i, j;

	//Losuje jakieś losowe rozwiązania
	for (i = 0; i < size; i++)
		x -> data[i][0] = (double)rand() / RAND_MAX * 10;

	//Losuje jakieś losowe współczynniki
	for (i = 0; i < size; i++) {
		for (j = i; j < size; j++) {
			A -> data[i][j] = (double)rand() / RAND_MAX * 10;
		}
	}

	licz_b(A, b, x, size);

	int errorlevel = backsubst(x_obliczone, A, b);

	printToScreen(A);
	printToScreen(b);
	printToScreen(x);
	printToScreen(x_obliczone);

	switch(errorlevel) {
		case 1:
			fprintf(stderr, "Błąd dzielenia przez zero!");
			break;
		case 2:
			fprintf(stderr, "Błąd, nieprawidłowe rozmiary maciery!");
			break;
		case 0:
			for (i = 0; i < size; i++) {
				printf("Różnica %d: %lf\n", i, fabs(x_obliczone -> data[i][0] - x -> data[i][0]));
			}
			break;
	}
	return 0;
}