#include <stdio.h>
#include "../src/gauss.h"
#include "../src/mat_io.h"
#include <stdlib.h>
#include <math.h>

int main(){
    Matrix *A;
    Matrix *b;
    //alokacje 
    A = (Matrix *)malloc(sizeof *A);
    b=(Matrix *)malloc(sizeof *b);
    if(A==NULL || b==NULL){
        printf("Blad przy alokacji pamięci\n");
        return 1;
    }
    A->c= A->r = 4;
    b->c=1;
    b->r=4;
    A->data = (double **)malloc(A->r * sizeof *A->data);
    b->data = (double **)malloc(b->r * sizeof *b->data);
    if(A->data == NULL || b->data==NULL){
        printf("Blad przy alokacji pamięci\n");
        return 1;
    }
    for(int i=0; i<A->r ;i++){//alokacja elementow A
        if((A->data[i] = (double*)malloc(A->c * sizeof *(A->data[i])))==NULL){
            printf("Blad przy alokacji pamięci\n");
            return 1;
        }    
    }
    for(int i=0; i<b->r;i++){ //alokacja elemtow b
        if((b->data[i] = (double *)malloc(b->c * sizeof *(b->data[i])))==NULL){
            printf("Blad przy alokacji pamięci\n");
            return 1;
        }
    }
    //inicjalizacji wartosci w macierzy b ("na sztywno"):
    b->data[0][0]=1.1;
    b->data[1][0]=2.2;
    b->data[2][0]=3.3;
    b->data[3][0]=4.4;

    int czy_niezdane =0; //0 -zdane, 1 -niezdane
    //ROBIMY 5 TESTOW
    for(int i=0; i<5;i++){
        for(int w=0;w<A->r;w++){
            for(int k=0;k<A->c;k++){
                A->data[w][k] = ((double)rand()+10.0)/RAND_MAX;
            }
        }
        printf("Macierz A przed eliminacją:\n");
        printToScreen(A);
        //testujemy eliminate()
        if(eliminate(A,b)==1){
            printf("Test: niezaliczony, blad w eliminate\n");
            return 1;
        }
        printf("Macierz A po eliminacji:\n");
        printToScreen(A);
        
        for(int k=0;k<A->c-1;k++){
            if(czy_niezdane==1)
                break;
            for(int w=k+1;w<A->r;w++){
                if(round(A->data[w][k])!=0.0){
                    czy_niezdane =1;
                    break;
                }    
            }
        }
        if(czy_niezdane==1){
            break;
        }
    }
    if(czy_niezdane==1){
        printf("Test: NIEZALICZONY\n");
        return 1;
    }else{
        printf("Test: ZALICZONY\n");
        return 0;
    }
}