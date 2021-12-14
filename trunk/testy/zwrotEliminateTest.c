#include <stdio.h>
#include "../src/gauss.h"
#include "../src/mat_io.h"
#include <stdlib.h>

int main(int argc, char **argv){
    /* generowanie macierzy 5x5 z zerami w 1 kolumnie  */
    Matrix *A, *b;
    A = createMatrix(5,5);
    b=createMatrix(5,1);
    if(A==NULL || b==NULL){
        return 1;
    }
    for(int i=0;i<A->r;i++){
        A->data[i][0] = 0.0;/*0 w 1 kolumnie*/
        b->data[i][0] = ((double)rand()+10.0)/RAND_MAX; /* losowe rzeczy w b*/
    }
    for(int k=1;k<A->c;k++){
        for(int w=0; w<A->r; w++){ /* losowe liczby w pozostalych */
            A->data[w][k]=((double)rand()+10.0)/RAND_MAX;
        }
    }
    printf("TEST 1: czy zwraca 1, gdy damy macierz z zerami w 1 kolumnie\nMacierz A:\n");
    printToScreen(A);
    if(eliminate(A,b)==1){
        printf("Zwrot 1 z funkcji eliminate, zatem musialoby nastapic dzielenie przez 0,\n");
        printf("wiec jest przerwanie wtedy.\n");
        printf("Macierz z zerami w 1 kolumnie --> Test 1 zaliczony.\n");
    }else{
        printf("Macierz z zerami w 1 kolumnie --> Test 1 niezaliczony\n");
    }
    /* rozne liczby wierszy w A i b */
    /* a zostawiamy bez zmian, generujemy nowe b o innej licznie wierszy*/
    for(int k=0;k<A->c;k++){
        for(int w=0; w<A->r; w++){ /* losowe liczby w pozostalych */
            A->data[w][k]=((double)rand()+10.0)/RAND_MAX;
        }
    }
    b=createMatrix((A->r)+7,1);
    for(int i=0;i<b->r;i++){
        b->data[i][0] = ((double)rand()+10.0)/RAND_MAX; /* losowe rzeczy w b*/
    }
    printf("TEST 2: czy zwraca 2, gdy podamy macierze A i b o roznych liczbe wierszy\nMacierz A:\n");
    printToScreen(A);
    printf("Macierz b:\n");
    printToScreen(b);
    if(eliminate(A,b)==2){
        printf("Zwrot 2 z eliminate, zatem funkcja zatrzymala sie \nkiedy otrzymala dwie macierze o roznej liczbie wierszy\n");
        printf("Test 2 zaliczony\n");
    }else{
        printf("Test 2 niezaliczony\n");
    }
    return 0;
}