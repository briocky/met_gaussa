#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"

void chooseMax(int k, Matrix *mat, Matrix *b);

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b);

#endif
