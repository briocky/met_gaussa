#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int n;
    double **a;
    double *b;
} *ur_t; //wskaznik na strukture 

ur_t init_ur(char *nazwa_pliku){
    FILE *in = fopen(nazwa_pliku, "r");
    if(in ==NULL)
        return NULL;

    ur_t u = malloc (sizeof *u);
    if(u==NULL)
        return NULL;
    
    if(fscanf(in,"%d", &u->n)!=1)
        return NULL;

    u->a = malloc (u->n * sizeof *(u->a));
    u->b = malloc (u->n*sizeof *(u->b));
    if(u->a == NULL || u->b == NULL)
        return NULL;
    
    for( int i=0; i<u->n;i++)
        if((u->a[i] = malloc (u->n * sizeof *(u->a[i])))==NULL)
            return NULL;
    // dodawanie wartosci do macierzy
    for(int w=0; w<u->n; w++)
        for(int k=0; k<u->n; k++)
            if(fscanf(in, "%lf", u->a[w]+k)!=1)
                return NULL;
    
    //wyrazy wolne
    for(int i=0; i<u->n; i++)
        if(fscanf(in, "%lf", u->b+i)!=1)
            return NULL;
    return u;
}

double *solver(ur_t u){
    double **A= u->a;
    double *b= u->b;
    double *x = malloc (u->n * sizeof *x); // macierz x-ow (rozwiazan)
    if(x==NULL)
        return NULL;

    // przeksztalcamy macierz A do mac. gorne trojkatnej
    for( int k=0 ;k<u->n-1; k++){
        for(int w=k+1; w<u->n;w ++){
            double q= A[w][k] / A[k][k];
            //fprintf(stderr,"%lf\n",q);
            for(int z=0; z<u->n; z++)
                A[w][z] -= q * A[k][z]; 
            b[w]-= q * b[k];
        }
    }
    
    //zapisywanie rozwiazań, podstawianie wsteczne 
    for(int w=u->n-1; w>=0;w--){
        double s=0.0;
        for(int k=w+1;k<u->n;k++){
            s+=A[w][k] * x[k];
        }
        x[w] = (b[w]-s)/A[w][w];
    }

    return x;
}   



int main(int argc, char **argv){
    ur_t ur = init_ur(argv[1]);
    double *x=solver(ur);

    for(int i=0;i<ur->n;i++)
        printf("%lf ",round(x[i]) );

    /* wypisywanie macierzy A
    for(int i =0;i<ur->n;i++){
        for(int j=0;j<ur->n;j++)
            printf("%lf ", ur->a[i][j]);
        printf("\n");
    }*/

}